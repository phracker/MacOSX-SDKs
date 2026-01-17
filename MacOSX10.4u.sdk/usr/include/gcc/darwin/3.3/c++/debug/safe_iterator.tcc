/* APPLE LOCAL file libstdc++ debug mode */
// Debugging iterator implementation (out of line) -*- C++ -*-

/** @file safe_iterator.tcc
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */

#ifndef _GLIBCXX_DEBUG_SAFE_ITERATOR_TCC
#define _GLIBCXX_DEBUG_SAFE_ITERATOR_TCC

namespace std
{
  namespace __debug
  {
    template<typename _Iterator, typename _Sequence>
      bool 
      _Safe_iterator<_Iterator, _Sequence>::
      _M_can_advance(const difference_type& __n) const
      {
	typedef typename _Sequence::const_iterator const_iterator;
	
	if (this->_M_singular())
	  return false;
	if (__n == 0)
	  return true;
	if (__n < 0) 
	{
	  const_iterator __begin = 
	    static_cast<const _Sequence*>(_M_sequence)->begin();
	  pair<difference_type, _Distance_precision> __dist =
	    this->_M_get_distance(__begin, *this);
	  bool __ok =  (__dist.second == __dp_exact && __dist.first >= -__n
			|| __dist.second != __dp_exact && __dist.first > 0);
	  return __ok;
	}
	else
	{
	  const_iterator __end = 
	    static_cast<const _Sequence*>(_M_sequence)->end();
	  pair<difference_type, _Distance_precision> __dist = 
	    this->_M_get_distance(*this, __end);
	  bool __ok = (__dist.second == __dp_exact && __dist.first >= __n
		       || __dist.second != __dp_exact && __dist.first > 0);
	  return __ok;
	}
      }

    template<typename _Iterator, typename _Sequence>
    template<typename _Other>
      bool 
      _Safe_iterator<_Iterator, _Sequence>::
      _M_valid_range(const _Safe_iterator<_Other, _Sequence>& __rhs) const
      {
	if (!_M_can_compare(__rhs))
	  return false;
	
	/* Determine if we can order the iterators without the help of
	   the container */
	pair<difference_type, _Distance_precision> __dist = 
	  this->_M_get_distance(*this, __rhs);
	switch (__dist.second) {
	case __dp_equality:
	  if (__dist.first == 0)
	    return true;
	  break;
	  
	case __dp_sign:
	case __dp_exact:
	  return __dist.first >= 0;
	}
	
	/* We can only test for equality and these iterators are not
	   equal, so check if one of the iterators is at the wrong
	   extreme, making this an invalid range. */
	if (_M_is_begin() || __rhs._M_is_end())
	  return true;
	else if (_M_is_end() || __rhs._M_is_begin())
	  return false;
	
	// Assume that this is a valid range; we can't check anything else
	return true;
      }

    template<typename _Iterator, typename _Sequence>
      void
      _Safe_iterator<_Iterator, _Sequence>::
      _M_invalidate()
      {
	typedef typename _Sequence::iterator iterator;
	typedef typename _Sequence::const_iterator const_iterator;
	
	if (!this->_M_singular())
	{
	  for (_Safe_iterator_base* iter = _M_sequence->_M_iterators; iter; )
	  {
	    iterator* __victim = static_cast<iterator*>(iter);
	    iter = iter->_M_next;
	    if (this->base() == __victim->base())
	      __victim->_M_version = 0;
	  }
	  for (_Safe_iterator_base* iter = _M_sequence->_M_const_iterators;
	       iter; /* increment in loop */)
	  {
	    const_iterator* __victim = static_cast<const_iterator*>(iter);
	    iter = iter->_M_next;
	    if (this->base() == __victim->base())
	      __victim->_M_version = 0;
	  }
	  _M_version = 0;
	}
      }
  } // namespace __debug
} // namespace std

#endif /* _GLIBCXX_DEBUG_SAFE_ITERATOR_TCC */

