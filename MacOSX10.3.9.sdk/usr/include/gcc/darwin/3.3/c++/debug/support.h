/* APPLE LOCAL file libstdc++ debug mode */
// Copyright (C) 2003
// Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.
#ifndef _GLIBCXX_DEBUG_SUPPORT_H
#define _GLIBCXX_DEBUG_SUPPORT_H

// Internal macros 
#ifdef _GLIBCXX_DEBUG
#  define _GLIBCXX_STRINGIFY(X) #X
#  define _GLIBCXX_DEBUG_NAMESPACE_OPEN(_Ns) namespace _Ns {
#  define _GLIBCXX_DEBUG_NAMESPACE_CLOSE }
#  define _GLIBCXX_DEBUG_BASE(_Ns, _Class) _Ns::_Release_##_Class
#  define _GLIBCXX_RELEASE_CLASS(Name) __attribute__((__link_name__(#Name)))
#  define _GLIBCXX_DEBUG_CLASS(Name) __attribute__((__link_name__(_GLIBCXX_STRINGIFY(_Debug_##Name))))
#else
#  define _GLIBCXX_DEBUG_NAMESPACE_OPEN(_Ns) namespace __gnu_debug {
#  define _GLIBCXX_DEBUG_NAMESPACE_CLOSE }
#  define _GLIBCXX_DEBUG_BASE(_Ns, _Class) _Ns::_Class
#  define _GLIBCXX_RELEASE_CLASS(Name)
#  define _GLIBCXX_DEBUG_CLASS(Name)
#endif

#endif /* _GLIBCXX_DEBUG_SUPPORT_H */
