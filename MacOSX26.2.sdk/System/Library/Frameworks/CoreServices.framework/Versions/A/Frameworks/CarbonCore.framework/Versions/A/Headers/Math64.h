/*
     File:       CarbonCore/Math64.h
 
     Contains:   64-bit integer math Interfaces.
                 The contents of this header file are deprecated.
 
     Copyright:  © 1994-2011 by Apple Inc. All rights reserved.
*/
#ifndef __MATH64__
#define __MATH64__

#ifndef __CONDITIONALMACROS__
#include <ConditionalMacros.h>
#endif

#ifndef __MACTYPES__
#include <MacTypes.h>
#endif



#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

//	If this compiler supports inline functions, then we define static inline versions of most of
//	the functions in this header so that no actually calls into CarbonCore are generated for any call.
//	If the compiler does not support inline functions, then we define the functions as externs but in most
//	cases define a macro with the name of the function which performs the operation, again to avoid a
//	function call.  These macros are careful never to use a parameter multiple times, to avoid an issue
//	where a parameter has a side effect.
#ifndef MATH64_USE_INLINE
	#if defined(__cplusplus) || ( defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L )
	#define MATH64_USE_INLINE	1
	#endif
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns largest possible SInt64 value
	 *	@result	the largest SInt64 value */
    static inline SInt64 S64Max(void) { return 9223372036854775807LL; }
  #else
	/*!	@brief	Returns largest possible SInt64 value
	 *	@result	the largest SInt64 value */
	extern SInt64 S64Max(void);
    #define S64Max() (9223372036854775807LL)
  #endif
#else
/*!	@brief	Returns largest possible SInt64 value
 *	@result	the largest SInt64 value */
extern SInt64 S64Max(void);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Returns smallest possible SInt64 value
	    @result	the smallest SInt64 value */
    static inline SInt64 S64Min(void) { return -S64Max() - 1; }
  #else
	/*! @brief	Returns smallest possible SInt64 value
		@result	the smallest SInt64 value */
	extern SInt64 S64Min(void);
    #define S64Min() (-S64Max() - 1)
  #endif
#else
/*! @brief	Returns smallest possible SInt64 value
 @result	the smallest SInt64 value */
extern SInt64 S64Min(void);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief Adds two integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the operands an result were unsigned.  No overflow is signaled.
	 @result	the result, with truncation, of adding left and right as SInt64 values
	 */
    static inline SInt64 S64Add(SInt64 left, SInt64 right) { return (SInt64)(left) + (SInt64)(right); }
  #else
	/*!	@brief Adds two integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the operands an result were unsigned.  No overflow is signaled.
	 @result	the result, with truncation, of adding left and right as SInt64 values
	 */
	extern SInt64 S64Add( SInt64   left, SInt64   right);
    #define S64Add(left, right) ((SInt64)(left) + (SInt64)(right))
  #endif
#else
/*!	@brief Adds two integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the operands an result were unsigned.  No overflow is signaled.
 @result	the result, with truncation, of adding left and right as SInt64 values
 */
extern SInt64 S64Add( SInt64   left, SInt64   right);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief Subtracts the second integer from the first integer, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the operands and result were unsigned.  No overflow is signaled.
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result the result of subsracting the value right from the value left  */
    static inline SInt64 S64Subtract(SInt64 left, SInt64 right) { return (SInt64)(left) - (SInt64)(right); }
  #else
	/*! @brief Subtracts the second integer from the first integer, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the operands and result were unsigned.  No overflow is signaled.
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result the result of subsracting the value right from the value left  */
	extern SInt64  S64Subtract( SInt64   left, SInt64   right);
    #define S64Subtract(left, right) ((SInt64)(left) - (SInt64)(right))
  #endif
#else
/*! @brief Subtracts the second integer from the first integer, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the operands and result were unsigned.  No overflow is signaled.
	 @param	left	a SInt64 value
	 @param	right	a SInt64 value
	 @result the result of subsracting the value right from the value left  */
extern SInt64  S64Subtract( SInt64   left, SInt64   right);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief Returns the additive inverse of a signed number (i.e. it returns 0 - the number).  S64Negate (S64Min) is not representable (in fact, it returns S64Min).
		@param value the value to negate
		@result	the additive inverse of the given value */
     static inline SInt64 S64Negate(SInt64 value) { return -(SInt64)(value); }
  #else
	/*! @brief Returns the additive inverse of a signed number (i.e. it returns 0 - the number).  S64Negate (S64Min) is not representable (in fact, it returns S64Min).
		@param	the value to negate
		@result	the additive inverse of the given value */
	extern SInt64  S64Negate(SInt64 value);
    #define S64Negate(value) (-(SInt64)(value))
  #endif
#else
/*! @brief Returns the additive inverse of a signed number (i.e. it returns 0 - the number).  S64Negate (S64Min) is not representable (in fact, it returns S64Min).
	@param	the value to negate
	@result	the additive inverse of the given value */
extern SInt64  S64Negate(SInt64 value);
#endif



#if !TYPE_LONGLONG

  #if MATH64_USE_INLINE
	/*!	@brief Returns the absolute value of the number (i.e. the number if it is positive, or 0 - the number if it is negative).
		@param	value	a SInt64 value
		@result	the absolute value of value */
    static inline SInt64 S64Absolute(SInt64 value) { return llabs((SInt64)value); }
  #else
	/*!	@brief Returns the absolute value of the number (i.e. the number if it is positive, or 0 - the number if it is negative).
		@param	value	a SInt64 value
		@result	the absolute value of value */
	extern SInt64  S64Absolute(SInt64 value);
    #define S64Absolute(value) (llabs((SInt64)value))
  #endif
#else
/*!	@brief Returns the absolute value of the number (i.e. the number if it is positive, or 0 - the number if it is negative).
	@param	value	a SInt64 value
	@result	the absolute value of value */
extern SInt64  S64Absolute(SInt64 value);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Multiplies two signed numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
				returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result	The result of multiplying left by right, truncated to a SInt64 value */
    static inline SInt64 S64Multiply(SInt64 left, SInt64 right) { return (SInt64)(left) * (SInt64)(right); }
  #else
	/*!	@brief	Multiplies two signed numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
				returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
	 	@param	left	a SInt64 value
	 	@param	right	a SInt64 value
	 	@result	The result of multiplying left by right, truncated to a SInt64 value */
	extern SInt64  S64Multiply( SInt64   left, SInt64   right);
    #define S64Multiply(left, right) ((SInt64)(left) * (SInt64)(right))
  #endif
#else
/*!	@brief	Multiplies two signed numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
			returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	The result of multiplying left by right, truncated to a SInt64 value */
extern SInt64  S64Multiply( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
				it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
		@param	dividend	a SInt64 value
		@param	divisor	a SInt64 value
		@result	the integer remainder after dividing dividend by divisor */
    static inline SInt64 S64Mod(SInt64 dividend, SInt64 divisor) { return (SInt64)(dividend) % (SInt64)(divisor); }
  #else
/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
			it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
	@param	dividend	a SInt64 value
	@param	divisor	a SInt64 value
	@result	the integer remainder after dividing dividend by divisor */
	extern SInt64  S64Mod( SInt64   dividend, SInt64   divisor);
    #define S64Mod(dividend, divisor) ((SInt64)(dividend) % (SInt64)(divisor))
  #endif
#else
/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
			it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
	@param	dividend	a SInt64 value
	@param	divisor	a SInt64 value
	@result	the integer remainder after dividing dividend by divisor */
extern SInt64  S64Mod( SInt64   dividend, SInt64   divisor);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Divides dividend by divisor, returning the quotient.  The remainder is returned in remainder if remainder (the pointer) is
			non-NULL. The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
			does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then S64Max() will be
			returned (or S64Min() if the dividend is negative), and the remainder will be the dividend; no error is reported.
	 @param	dividend	a SInt64 value
	 @param	divisor		a SInt64 value
	 @param	remainderP	on return, if non-NULL, the integer remainder after dividing dividend by divisor
	 @result	the integer result of dividing dividend by divisor */
    static inline SInt64 S64Divide(SInt64 dividend, SInt64 divisor, SInt64 *remainderP) { return ( (void)((remainderP) && (*((SInt64*)(remainderP)) = ((SInt64)(dividend) % (SInt64)(divisor)))), ((SInt64)(dividend) / (SInt64)(divisor)) ); }
  #else
	/*!	@brief	Divides dividend by divisor, returning the quotient.  The remainder is returned in remainder if remainder (the pointer) is
				non-NULL. The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
				does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then S64Max() will be
				returned (or S64Min() if the dividend is negative), and the remainder will be the dividend; no error is reported.
		 @param	dividend	a SInt64 value
		 @param	divisor		a SInt64 value
		 @param	remainderP	on return, the integer remainder after dividing dividend by divisor
		 @result	the integer result of dividing dividend by divisor */
	extern SInt64  S64Divide( SInt64    dividend, SInt64    divisor, SInt64 *  remainderP);
    #define S64Divide(dividend, divisor, remainder) (( (void)((remainder) && (*((SInt64*)(remainder)) = ((SInt64)(dividend) % (SInt64)(divisor)))), ((SInt64)(dividend) / (SInt64)(divisor)) ))
  #endif
#else
/*!	@brief	Divides dividend by divisor, returning the quotient.  The remainder is returned in remainder if remainder (the pointer) is
			non-NULL. The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
			does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then S64Max() will be
			returned (or S64Min() if the dividend is negative), and the remainder will be the dividend; no error is reported.
	@param	dividend	a SInt64 value
	@param	divisor		a SInt64 value
	@param	remainderP	on return, the integer remainder after dividing dividend by divisor
	@result	the integer result of dividing dividend by divisor */
extern SInt64  S64Divide( SInt64    dividend, SInt64    divisor, SInt64 *  remainderP);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Divides dividend by divisor, returning the quotient.
		@param	dividend	a SInt64 value
		@param	divisor		a SInt64 value
		@result	the integer result of dividing dividend by divisor */
    static inline SInt64 S64Div(SInt64 dividend, SInt64 divisor) { return S64Divide((dividend), (divisor), NULL); }
  #else
	/*!	@brief	Divides dividend by divisor, returning the quotient.
		@param	dividend	a SInt64 value
		@param	divisor		a SInt64 value
		@result	the integer result of dividing dividend by divisor */
	extern SInt64  S64Div( SInt64   dividend, SInt64   divisor);
    #define S64Div(dividend, divisor) (S64Divide((dividend), (divisor), NULL))
  #endif
#else
/*!	@brief	Divides dividend by divisor, returning the quotient.
	@param	dividend	a SInt64 value
	@param	divisor		a SInt64 value
	@result	the integer result of dividing dividend by divisor */
extern SInt64  S64Div( SInt64   dividend, SInt64   divisor);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Given an SInt32, returns an SInt64 with the same value.  Use this routine instead of coding 64-bit constants (at least when the
	 constant will fit in an SInt32).
		@param	value	a SInt32 value
		@result	the SInt64 equivalent of value  */
    static inline SInt64 S64Set(SInt32 value) { return (SInt64)(value); }
  #else
/*!	@brief	Given an SInt32, returns an SInt64 with the same value.  Use this routine instead of coding 64-bit constants (at least when the
 constant will fit in an SInt32).
	@param	value	a SInt32 value
	@result	the SInt64 equivalent of value  */
	extern SInt64  S64Set(SInt32 value);
    #define S64Set(value) ((SInt64)(value))
  #endif
#else
/*!	@brief	Given an SInt32, returns an SInt64 with the same value.  Use this routine instead of coding 64-bit constants (at least when the
 constant will fit in an SInt32).
	@param	value	a SInt32 value
	@result	the SInt64 equivalent of value  */
extern SInt64  S64Set(SInt32 value);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given a UInt32, returns a SInt64 with the same value.
	@param	value	A UInt32 value
	@result	the SInt64 equivalent of value */
    static inline SInt64 S64SetU(UInt32 value) { return (SInt64)(value); }
  #else
/*!	@brief	Given a UInt32, returns a SInt64 with the same value.
	@param	value	A UInt32 value
	@result	the SInt64 equivalent of value */
	extern SInt64  S64SetU(UInt32 value);
    #define S64SetU(value) ((SInt64)(value))
  #endif
#else
/*!	@brief	Given a UInt32, returns a SInt64 with the same value.
	@param	value	A UInt32 value
	@result	the SInt64 equivalent of value */
extern SInt64  S64SetU(UInt32 value);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief Given an SInt64, returns an SInt32 by discarding the high-order 32 bits.
		@param	value	A SInt64 value
		@result	return the lowest 32 bits of value as a SInt32 */
    static inline SInt32 S32Set(SInt64 value) { return (SInt32)(value); }
  #else
	/*!	@brief Given an SInt64, returns an SInt32 by discarding the high-order 32 bits.
		@param	value	A SInt64 value
		@result	return the lowest 32 bits of value as a SInt32 */
	extern SInt32  S32Set(SInt64 value);
    #define S32Set(value) ((SInt32)(value))
  #endif
#else
/*!	@brief Given an SInt64, returns an SInt32 by discarding the high-order 32 bits.
	@param	value	A SInt64 value
	@result	return the lowest 32 bits of value as a SInt32 */
extern SInt32  S32Set(SInt64 value);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns one if left and right are non-zero, otherwise returns zero
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result	return the value 1 if both left and right are non-zero, and 0 if not  */
    static inline Boolean S64And(SInt64 left, SInt64 right) { return ((SInt64)(left) && (SInt64)(right)) ? 1 : 0 ; }
  #else
	/*!	@brief	Returns one if left and right are non-zero, otherwise returns zero
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result	return the value 1 if both left and right are non-zero, and 0 if not  */
	extern Boolean  S64And( SInt64   left, SInt64   right);
    #define S64And(left, right) ((SInt64)(left) && (SInt64)(right))
  #endif
#else
/*!	@brief	Returns one if left and right are non-zero, otherwise returns zero
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	return the value 1 if both left and right are non-zero, and 0 if not  */
extern Boolean  S64And( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief Returns one if left or right are non-zero, otherwise returns zero
		 @param	left	a SInt64 value
		 @param	right	a SInt64 value
		 @result	return the value 1 if either left is non-zero or right is non-zero and 0 if not  */
    static inline Boolean S64Or(SInt64 left, SInt64 right) { return ((SInt64)(left) || (SInt64)(right)) ? 1 : 0; }
  #else
/*! @brief Returns one if left or right are non-zero, otherwise returns zero
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	return the value 1 if either left is non-zero or right is non-zero and 0 if not  */
	extern Boolean  S64Or( SInt64   left, SInt64   right);
    #define S64Or(left, right) ((SInt64)(left) || (SInt64)(right))
  #endif
#else
/*! @brief Returns one if left or right are non-zero, otherwise returns zero
	 @param	left	a SInt64 value
	 @param	right	a SInt64 value
	 @result	return the value 1 if either left is non-zero or right is non-zero and 0 if not  */
extern Boolean  S64Or( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Returns one if left xor right are non-zero, otherwise returns zero
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result	return the value 1 if left EOR right is non-zero, 0 otherwise */
    static inline Boolean S64Eor(SInt64 left, SInt64 right) { return (Boolean)(((SInt64)(left) ? 1 : 0) ^ ((SInt64)(right) ? 1 : 0)); }
  #else
	/*! @brief	Returns one if left xor right are non-zero, otherwise returns zero
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result	return the value 1 if left EOR right is non-zero, 0 otherwise */
	extern Boolean  S64Eor( SInt64   left, SInt64   right);
    #define S64Eor(left, right) ((Boolean)(((SInt64)(left) ? 1 : 0) ^ ((SInt64)(right) ? 1 : 0)))
  #endif
#else
/*! @brief	Returns one if left xor right are non-zero, otherwise returns zero
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	return the value 1 if left EOR right is non-zero, 0 otherwise */
extern Boolean  S64Eor( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns one if value is non-zero, otherwise returns zero.
		@param	value	a SInt64 value
		@result	return 1 if value is non-zero, 0 if it is zero */
    static inline Boolean S64Not(SInt64 value) { return !((SInt64)(value)); }
  #else
	/*!	@brief	Returns one if value is non-zero, otherwise returns zero.
		@param	value	a SInt64 value
		@result	return 1 if value is non-zero, 0 if it is zero */
	extern Boolean  S64Not(SInt64 value);
    #define S64Not(value) (!((SInt64)(value)))
  #endif
#else
/*!	@brief	Returns one if value is non-zero, otherwise returns zero.
	@param	value	a SInt64 value
	@result	return 1 if value is non-zero, 0 if it is zero */
extern Boolean  S64Not(SInt64 value);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given two signed numbers, left and right, returns an SInt32 that compares with zero the same way left compares with right.  If you
			wanted to perform a comparison on 64-bit integers of the  form:
				left OPERATION right
			then you could use an expression of the form:
				S64Compare( left,right ) OPERATION 0
			to test for the same condition. CAUTION: DO NOT depend on the exact value returned by this routine. Only the sign (i.e.
			positive, zero, or negative) of the result is guaranteed.
		@param	left	a SInt64 value
		@param	right	a SInt64 value
		@result	if left is less than right, a negative value; if left is equal to right, then 0, if left is greater than right, a positive value */
	static inline SInt32 S64Compare( SInt64   left, SInt64   right) { if (left < right) { return -1; } else if (left > right) { return 1; } else { return 0; } };
  #else
/*!	@brief	Given two signed numbers, left and right, returns an SInt32 that compares with zero the same way left compares with right.  If you
			wanted to perform a comparison on 64-bit integers of the  form:
				left OPERATION right
			then you could use an expression of the form:
				S64Compare( left,right ) OPERATION 0
			to test for the same condition. CAUTION: DO NOT depend on the exact value returned by this routine. Only the sign (i.e.
			positive, zero, or negative) of the result is guaranteed.
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	if left is less than right, a negative value; if left is equal to right, then 0, if left is greater than right, a positive value */
	extern SInt32 S64Compare( SInt64   left, SInt64   right);
  #endif
#else
/*!	@brief	Given two signed numbers, left and right, returns an SInt32 that compares with zero the same way left compares with right.  If you
			wanted to perform a comparison on 64-bit integers of the  form:
				left OPERATION right
			then you could use an expression of the form:
				S64Compare( left,right ) OPERATION 0
			to test for the same condition. CAUTION: DO NOT depend on the exact value returned by this routine. Only the sign (i.e.
			positive, zero, or negative) of the result is guaranteed.
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	if left is less than right, a negative value; if left is equal to right, then 0, if left is greater than right, a positive value */
SInt32 S64Compare( SInt64   left, SInt64   right);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*! @brief	Given two signed numbers, return the bitwise AND of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise AND of left and right, treating both values as 64 bit unsigned values  */
    static inline SInt64 S64BitwiseAnd(SInt64 left, SInt64 right) { return (SInt64)(left) & (SInt64)(right); }
  #else
/*! @brief	Given two signed numbers, return the bitwise AND of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise AND of left and right, treating both values as 64 bit unsigned values  */
	extern SInt64  S64BitwiseAnd( SInt64   left, SInt64   right);
    #define S64BitwiseAnd(left, right) ((SInt64)(left) & (SInt64)(right))
  #endif
#else
/*! @brief	Given two signed numbers, return the bitwise AND of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise AND of left and right, treating both values as 64 bit unsigned values  */
extern SInt64  S64BitwiseAnd( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given two signed numbers, return the bitwise OR of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise OR of left and right, treating both values as 64 bit unsigned values */
    static inline SInt64 S64BitwiseOr(SInt64 left, SInt64 right) { return (SInt64)(left) | (SInt64)(right); }
  #else
/*!	@brief	Given two signed numbers, return the bitwise OR of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise OR of left and right, treating both values as 64 bit unsigned values */
	extern SInt64 S64BitwiseOr( SInt64   left, SInt64   right);
    #define S64BitwiseOr(left, right) ((SInt64)(left) | (SInt64)(right))
  #endif
#else
/*!	@brief	Given two signed numbers, return the bitwise OR of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise OR of left and right, treating both values as 64 bit unsigned values */
extern SInt64 S64BitwiseOr( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given two signed numbers, return the bitwise XOR of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise XOR of left and right, treating both values as 64 bit unsigned values */
    static inline SInt64 S64BitwiseEor(SInt64 left, SInt64 right) { return (SInt64)(left) ^ (SInt64)(right); }
  #else
/*!	@brief	Given two signed numbers, return the bitwise XOR of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise XOR of left and right, treating both values as 64 bit unsigned values */
	extern SInt64  S64BitwiseEor( SInt64   left, SInt64   right);
    #define S64BitwiseEor(left, right) ((SInt64)(left) ^ (SInt64)(right))
  #endif
#else
/*!	@brief	Given two signed numbers, return the bitwise XOR of the two values
	@param	left	a SInt64 value
	@param	right	a SInt64 value
	@result	the SInt64 result of a bitwise XOR of left and right, treating both values as 64 bit unsigned values */
extern SInt64  S64BitwiseEor( SInt64   left, SInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given a SInt64 value, return the bitwise negation of value
	@param	value	a SInt64 value
	@result	the bitwise negation of value */
    static inline SInt64 S64BitwiseNot(SInt64 value) { return ~((SInt64)(value)); }
  #else
/*!	@brief	Given a SInt64 value, return the bitwise negation of value
	@param	value	a SInt64 value
	@result	the bitwise negation of value */
	extern SInt64  S64BitwiseNot(SInt64 value);
    #define S64BitwiseNot(value) (~((SInt64)(value)))
  #endif
#else
/*!	@brief	Given a SInt64 value, return the bitwise negation of value
	@param	value	a SInt64 value
	@result	the bitwise negation of value */
extern SInt64  S64BitwiseNot(SInt64 value);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given a SInt64 value, return the arithmetic shift right of value by the lower 7 bits of the shift.
	@param	value	a SInt64 value
	@param	shift	an unsigned amount to shift value by
	@result	the result of shifting value right by shift bits */
    static inline SInt64 S64ShiftRight(SInt64 value, UInt32 shift) { return (SInt64)(value) >> ((shift) & 0x7F); }
  #else
/*!	@brief	Given a SInt64 value, return the arithmetic shift right of value by the lower 7 bits of the shift.
	@param	value	a SInt64 value
	@param	shift	an unsigned amount to shift value by
	@result	the result of shifting value right by shift bits */
	extern SInt64  S64ShiftRight( SInt64   value, UInt32   shift);
    #define S64ShiftRight(value, shift) ((SInt64)(value) >> ((shift) & 0x7F))
  #endif
#else
/*!	@brief	Given a SInt64 value, return the arithmetic shift right of value by the lower 7 bits of the shift.
	@param	value	a SInt64 value
	@param	shift	an unsigned amount to shift value by
	@result	the result of shifting value right by shift bits */
extern SInt64  S64ShiftRight( SInt64   value, UInt32   shift);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Given a SInt64 value, return the arithmetic shift left of value by the lower 7 bits of the shift.
	@param	value	a SInt64 value
	@param	shift	an unsigned amount to shift value by
	@result	the result of shifting value left by shift bits */
    static inline SInt64 S64ShiftLeft(SInt64 value, UInt32 shift) { return (SInt64)(value) << ((shift) & 0x7F); }
  #else
/*!	@brief	Given a SInt64 value, return the arithmetic shift left of value by the lower 7 bits of the shift.
	@param	value	a SInt64 value
	@param	shift	an unsigned amount to shift value by
	@result	the result of shifting value left by shift bits */
	extern SInt64  S64ShiftLeft( SInt64   value, UInt32   shift);
    #define S64ShiftLeft(value, shift) ((SInt64)(value) << ((shift) & 0x7F))
  #endif
#else
/*!	@brief	Given a SInt64 value, return the arithmetic shift left of value by the lower 7 bits of the shift.
	@param	value	a SInt64 value
	@param	shift	an unsigned amount to shift value by
	@result	the result of shifting value left by shift bits */
extern SInt64  S64ShiftLeft( SInt64   value, UInt32   shift);
#endif

#if !TYPE_LONGDOUBLE_IS_DOUBLE
#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Converts SInt64 to long double.  Note all SInt64s fit exactly into long doubles, thus, the binary -> decimal conversion
			routines in fp.h can be used to achieve SInt64 -> long double ->  decimal conversions.
	@param	value	a SInt64 value
	@result	a double equivalent of value */
    static inline long double SInt64ToLongDouble(SInt64 value) { return (long double)(value); }
  #else
/*!	@brief	Converts SInt64 to long double.  Note all SInt64s fit exactly into long doubles, thus, the binary -> decimal conversion
			routines in fp.h can be used to achieve SInt64 -> long double ->  decimal conversions.
	@param	value	a SInt64 value
	@result	a double equivalent of value */
	extern long double  SInt64ToLongDouble(SInt64 value);
    #define SInt64ToLongDouble(value) ((long double)(value))
  #endif
#else
/*!	@brief	Converts SInt64 to long double.  Note all SInt64s fit exactly into long doubles, thus, the binary -> decimal conversion
			routines in fp.h can be used to achieve SInt64 -> long double ->  decimal conversions.
	@param	value	a SInt64 value
	@result	a double equivalent of value */
extern long double  SInt64ToLongDouble(SInt64 value);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*! @brief	Converts a long double to a SInt64.  Any decimal string that fits into a SInt64 can be converted exactly into a long double, using
			the conversion routines found in fp.h.  Then this routine can be used to complete the conversion to SInt64.
	@param	value	a long double value
	@result	the closest SInt64 value to value */
    inline SInt64 LongDoubleToSInt64(long double value) { return (SInt64)(value); }
  #else
/*! @brief	Converts a long double to a SInt64.  Any decimal string that fits into a SInt64 can be converted exactly into a long double, using
			the conversion routines found in fp.h.  Then this routine can be used to complete the conversion to SInt64.
	@param	value	a long double value
	@result	the closest SInt64 value to value */
	extern SInt64  LongDoubleToSInt64(long double value);
    #define LongDoubleToSInt64(value) ((SInt64)(value))
  #endif
#else
/*! @brief	Converts a long double to a SInt64.  Any decimal string that fits into a SInt64 can be converted exactly into a long double, using
			the conversion routines found in fp.h.  Then this routine can be used to complete the conversion to SInt64.
	@param	value	a long double value
	@result	the closest SInt64 value to value */
extern SInt64  LongDoubleToSInt64(long double value);
#endif

#endif  /* !TYPE_LONGDOUBLE_IS_DOUBLE */

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns largest possible UInt64 value
		@result	the largest SInt64 value  */
    static inline UInt64 U64Max(void) { return 0xffffffffffffffffULL; }
  #else
	/*!	@brief	Returns largest possible UInt64 value
		@result	the largest SInt64 value  */
	extern UInt64  U64Max(void);
    #define U64Max() (0xffffffffffffffffULL)
  #endif
#else
/*!	@brief	Returns largest possible UInt64 value
	@result	the largest SInt64 value  */
extern UInt64  U64Max(void);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Adds two unsigned integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the
				operands and result were unsigned.  No overflow is signaled.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of adding left to right, ignoring overflow and truncating to a UInt64  */
    static inline UInt64 U64Add(UInt64 left, UInt64 right) { return (UInt64)(left) + (UInt64)(right); }
  #else
	/*!	@brief	Adds two unsigned integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the
				operands and result were unsigned.  No overflow is signaled.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of adding left to right, ignoring overflow and truncating to a UInt64  */
	extern UInt64  U64Add( UInt64   left, UInt64   right);
    #define U64Add(left, right) ((UInt64)(left) + (UInt64)(right))
  #endif
#else
/*!	@brief	Adds two unsigned integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the
			operands and result were unsigned.  No overflow is signaled.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of adding left to right, ignoring overflow and truncating to a UInt64  */
extern UInt64  U64Add( UInt64   left, UInt64   right);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Subtracts two unsigned integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the
				operands and result were unsigned.  No overflow is signaled.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of subtracting the value right from left, ignoring underflow */
    static inline UInt64 U64Subtract(UInt64 left, UInt64 right) { return (UInt64)(left) - (UInt64)(right); }
  #else
	/*!	@brief	Subtracts two unsigned integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the
				operands and result were unsigned.  No overflow is signaled.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of subtracting the value right from left, ignoring underflow */
	extern UInt64  U64Subtract( UInt64   left, UInt64   right);
    #define U64Subtract(left, right) ((UInt64)(left) - (UInt64)(right))
  #endif
#else
/*!	@brief	Subtracts two unsigned integers, producing an integer result.  If an overflow occurs the result is congruent mod (2^64) as if the
			operands and result were unsigned.  No overflow is signaled.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of subtracting the value right from left, ignoring underflow */
extern UInt64  U64Subtract( UInt64   left, UInt64   right);
#endif

/*!	@brief	Multiplies two unsigned numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
@param	left	a \c UInt64 value
@param	right	a \c UInt64 value
@result	the result of multiplying left by right, truncated to a \c UInt64 value. */
#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
/*!	@brief	Multiplies two unsigned numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
			returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of multiplying left by right, truncated to a \c UInt64 value. */
    static inline UInt64 U64Multiply(UInt64 left, UInt64 right) { return (UInt64)(left) * (UInt64)(right); }
  #else
/*!	@brief	Multiplies two unsigned numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
			returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of multiplying left by right, truncated to a \c UInt64 value. */
	extern UInt64  U64Multiply( UInt64   left, UInt64   right);
    #define U64Multiply(left, right) ((UInt64)(left) * (UInt64)(right))
  #endif
#else
/*!	@brief	Multiplies two unsigned numbers, producing a signed result. Overflow is ignored and the low-order part of the product is
			returned.  The sign of the result is not guaranteed to be correct if the magnitude of the product is not representable.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of multiplying left by right, truncated to a \c UInt64 value. */
extern UInt64  U64Multiply( UInt64   left, UInt64   right);
#endif

/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
@param	dividend	a \c UInt64 value
@param	divisor		a \c UInt64 value
@result	the remainder after dividing dividend by divisor */
#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
				it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
		 @param	dividend	a \c UInt64 value
		 @param	divisor		a \c UInt64 value
		 @result the remainder after dividing dividend by divisor */
    static inline UInt64 U64Mod(UInt64 dividend, UInt64 divisor) { return (UInt64)(dividend) % (UInt64)(divisor); }
  #else
	/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
				it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
		@param	dividend	a \c UInt64 value
		@param	divisor		a \c UInt64 value
		@result	the remainder after dividing dividend by divisor */
	extern UInt64  U64Mod( UInt64   dividend, UInt64   divisor);
    #define U64Mod(dividend, divisor) ((UInt64)(dividend) % (UInt64)(divisor))
  #endif
#else
/*!	@brief	Returns the remainder of divide of dividend by divisor.  The sign of the remainder is the same as the sign of the dividend (i.e.,
			it takes the absolute values of the operands, does the division, then fixes the sign of the quotient and remainder).
	@param	dividend	a \c UInt64 value
	@param	divisor		a \c UInt64 value
	@result	the remainder after dividing dividend by divisor */
extern UInt64  U64Mod( UInt64   dividend, UInt64   divisor);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Divides dividend by divisor, returning the quotient.  The remainder is returned in remainder if remainder (the pointer) is
				non-NULL. The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
				does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then U64Max() will be
				returned (or U64Min() if the dividend is negative), and the remainder will be the dividend; no error is reported.
		@param	dividend the value to be divided
		@param	divisor	the value to divide by
		@param	remainder	if non-null, on exit the remainder of the operation
		@result	the \c UInt64 value ( divident / divisor )  */
	static inline UInt64 U64Divide(UInt64 dividend, UInt64 divisor, UInt64 *remainder) { return ( (void)((remainder) && (*((UInt64*)(remainder)) = ((UInt64)(dividend) % (UInt64)(divisor)))), ((UInt64)(dividend) / (UInt64)(divisor)) ); }
  #else
	/*!	@brief	Divides dividend by divisor, returning the quotient.  The remainder is returned in remainder if remainder (the pointer) is
				non-NULL. The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
				does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then U64Max() will be
				returned (or U64Min() if the dividend is negative), and the remainder will be the dividend; no error is reported.
		 @param	dividend the value to be divided
		 @param	divisor	the value to divide by
		 @param	remainder	if non-null, on exit the remainder of the operation
		 @result	the \c UInt64 value ( divident / divisor )  */
	extern UInt64  U64Divide( UInt64    dividend, UInt64    divisor, UInt64 *  remainder);
    #define U64Divide(dividend, divisor, remainder) (( (void)((remainder) && (*((UInt64*)(remainder)) = ((UInt64)(dividend) % (UInt64)(divisor)))), ((UInt64)(dividend) / (UInt64)(divisor)) ))
  #endif
#else
/*!	@brief	Divides dividend by divisor, returning the quotient.  The remainder is returned in remainder if remainder (the pointer) is
			non-NULL. The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
			does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then U64Max() will be
			returned (or U64Min() if the dividend is negative), and the remainder will be the dividend; no error is reported.
	@param	dividend the value to be divided
	@param	divisor	the value to divide by
	@param	remainder	if non-null, on exit the remainder of the operation
	@result	the \c UInt64 value ( divident / divisor )  */
extern UInt64  U64Divide( UInt64    dividend, UInt64    divisor, UInt64 *  remainder);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Divides dividend by divisor, returning the quotient.  The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
				does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then U64Max() will be returned (or U64Min() if the dividend is negative), and
				the remainder will be the dividend; no error is reported.
		@param	dividend	the value to be divided
		@param	divisor		the value to divide by
		@result	the \c UInt64 value ( dividend / divisor ) */
	static inline UInt64 U64Div(UInt64 dividend, UInt64 divisor) { return U64Divide((dividend), (divisor), NULL); }
  #else
	/*!	@brief	Divides dividend by divisor, returning the quotient.  The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
				does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then U64Max() will be returned (or U64Min() if the dividend is negative), and
				the remainder will be the dividend; no error is reported.
		@param	dividend	the value to be divided
		@param	divisor		the value to divide by
		@result	the \c UInt64 value ( dividend / divisor ) */
	extern UInt64  U64Div( UInt64   dividend, UInt64   divisor);
    #define U64Div(dividend, divisor) (U64Divide((dividend), (divisor), NULL))
  #endif
#else
/*!	@brief	Divides dividend by divisor, returning the quotient.  The sign of the remainder is the same as the sign of the dividend (i.e. it takes the absolute values of the operands,
			does the division, then fixes the sign of the quotient and remainder).  If the divisor is zero, then U64Max() will be returned (or U64Min() if the dividend is negative), and
			the remainder will be the dividend; no error is reported.
	@param	dividend	the value to be divided
	@param	divisor		the value to divide by
	@result	the \c UInt64 value ( dividend / divisor ) */
extern UInt64  U64Div( UInt64   dividend, UInt64   divisor);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Given an\c SInt32, returns an UInt64 with the same value.  Use this routine instead of coding 64-bit constants (at least when the constant will fit in an SInt32).
		@discussion	If value is negative, this returns the equivalent bit 32 bit value as an unsigned value
		@param	value	the \c SInt32 value to coerce to a \c UInt64
		@result	the \c UInt64 equivalent of the SInt32 value */
	static inline UInt64 U64Set(SInt32 value) { return (UInt64)(value); }
  #else
	/*!	@brief	Given an\c SInt32, returns an UInt64 with the same value.  Use this routine instead of coding 64-bit constants (at least when the constant will fit in an SInt32).
		@discussion	If value is negative, this returns the equivalent bit 32 bit value as an unsigned value
		@param	value	the \c SInt32 value to coerce to a \c UInt64
		@result	the \c UInt64 equivalent of the SInt32 value */
	extern UInt64  U64Set(SInt32 value);
    #define U64Set(value) ((UInt64)(value))
  #endif
#else
/*!	@brief	Given an\c SInt32, returns an UInt64 with the same value.  Use this routine instead of coding 64-bit constants (at least when the constant will fit in an SInt32).
	@discussion	If value is negative, this returns the equivalent bit 32 bit value as an unsigned value
	@param	value	the \c SInt32 value to coerce to a \c UInt64
	@result	the \c UInt64 equivalent of the SInt32 value */
extern UInt64  U64Set(SInt32 value);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Given a UInt32, returns a UInt64 with the same value.
		@param	value	A \c UInt32 value
		@result	A UInt64 value equivalent to value  */
    static inline UInt64 U64SetU(UInt32 value) { return (UInt64)(value); }
  #else
	/*!	@brief	Given a UInt32, returns a UInt64 with the same value.
		@param	value	A \c UInt32 value
		@result	A UInt64 value equivalent to value  */
	extern UInt64  U64SetU(UInt32 value);
    #define U64SetU(value) ((UInt64)(value))
  #endif
#else
/*!	@brief	Given a UInt32, returns a UInt64 with the same value.
	@param	value	A \c UInt32 value
	@result	A UInt64 value equivalent to value  */
extern UInt64  U64SetU(UInt32 value);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Given an UInt64, returns an UInt32 by discarding the high-order 32 bits.
		@param	value	A \c UInt64 value
		@result	the \c SInt32 value created by discarding the high-order 32 bits of value */
    static inline UInt32 U32SetU(UInt64 value) { return (UInt32)(value); }
  #else
	/*!	@brief	Given an UInt64, returns an UInt32 by discarding the high-order 32 bits.
		@param	value	A \c UInt64 value
		@result	the \c SInt32 value created by discarding the high-order 32 bits of value */
	extern UInt32  U32SetU(UInt64 value);
    #define U32SetU(value) ((UInt32)(value))
  #endif
#else
/*!	@brief	Given an UInt64, returns an UInt32 by discarding the high-order 32 bits.
	@param	value	A \c UInt64 value
	@result	the \c SInt32 value created by discarding the high-order 32 bits of value */
extern UInt32  U32SetU(UInt64 value);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns true if left and right are non-zero, otherwise returns false
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	returns true if either left or right is non-zero, false otherwise */
    static inline Boolean U64And(UInt64 left, UInt64 right) { return (UInt64)(left) && (UInt64)(right); }
  #else
	/*!	@brief	Returns true if left and right are non-zero, otherwise returns false
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	returns true if either left or right is non-zero, false otherwise */
	extern Boolean  U64And( UInt64   left, UInt64   right);
    #define U64And(left, right) ((UInt64)(left) && (UInt64)(right))
  #endif
#else
/*!	@brief	Returns true if left and right are non-zero, otherwise returns false
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	returns true if either left or right is non-zero, false otherwise */
extern Boolean  U64And( UInt64   left, UInt64   right);
#endif

#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Returns true if left or right are non-zero, otherwise returns false
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	returns true if both left or right is non-zero, false otherwise */
    static inline Boolean U64Or(UInt64 left, UInt64 right) { return (UInt64)(left) || (UInt64)(right); }
  #else
	/*!	@brief	Returns true if left or right are non-zero, otherwise returns false
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	returns true if both left or right is non-zero, false otherwise */
	extern Boolean  U64Or( UInt64   left, UInt64   right);
    #define U64Or(left, right) ((UInt64)(left) || (UInt64)(right))
  #endif
#else
/*!	@brief	Returns true if left or right are non-zero, otherwise returns false
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	returns true if both left or right is non-zero, false otherwise */
extern Boolean  U64Or( UInt64   left, UInt64   right);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief  Returns one if left xor right are non-zero, otherwise returns zero
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	return true if both left and right are zero, or if both left and right are non-zero; false otherwise  */
    static inline Boolean U64Eor(UInt64 left, UInt64 right) { return (Boolean)(((UInt64)(left) ? 1 : 0) ^ ((UInt64)(right) ? 1 : 0)); }
  #else
	/*!	@brief  Returns one if left xor right are non-zero, otherwise returns zero
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	return true if both left and right are zero, or if both left and right are non-zero; false otherwise  */
	extern Boolean  U64Eor( UInt64   left, UInt64   right);
    #define U64Eor(left, right) ((Boolean)(((UInt64)(left) ? 1 : 0) ^ ((UInt64)(right) ? 1 : 0)))
  #endif
#else
/*!	@brief  Returns one if left xor right are non-zero, otherwise returns zero
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	return true if both left and right are zero, or if both left and right are non-zero; false otherwise  */
extern Boolean  U64Eor( UInt64   left, UInt64   right);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief Returns true if value is non-zero, otherwisze returns false.
		@param	value	a \c UInt64 value
		@result	return true if value is non-zero, true otherwise  */
    static inline Boolean U64Not(UInt64 value) { return !((UInt64)(value)); }
  #else
	/*!	@brief Returns true if value is non-zero, otherwisze returns false.
		@param	value	a \c UInt64 value
		@result	return true if value is non-zero, true otherwise  */
	extern Boolean  U64Not(UInt64 value);
    #define U64Not(value) (!((UInt64)(value)))
  #endif
#else
/*!	@brief Returns true if value is non-zero, otherwisze returns false.
	@param	value	a \c UInt64 value
	@result	return true if value is non-zero, true otherwise  */
extern Boolean  U64Not(UInt64 value);
#endif



/*!	@brief	Given two unsigned numbers, left and right, returns an SInt32  that compares with zero the same way left compares with right.  Do not depend on the actual value returned, only on its sign or whether it is zero.
 @param	left	a \c UInt64 value
 @param	right	a \c UInt64 value
 @result	If left is less than right, then a negative value; if left is larger than right then a positive value, and if left == right then the value zero. */
extern SInt32  U64Compare( UInt64   left, UInt64   right)                                             __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_8, __IPHONE_NA, __IPHONE_NA);


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Return the bitwise AND value of the two parameters.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of the bitwise AND of left and right */
    static inline UInt64 U64BitwiseAnd(UInt64 left, UInt64 right) { return (UInt64)(left) & (UInt64)(right); }
  #else
	/*! @brief	Return the bitwise AND value of the two parameters.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of the bitwise AND of left and right */
	extern UInt64  U64BitwiseAnd( UInt64   left, UInt64   right);
    #define U64BitwiseAnd(left, right) ((UInt64)(left) & (UInt64)(right))
  #endif
#else
/*! @brief	Return the bitwise AND value of the two parameters.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of the bitwise AND of left and right */
extern UInt64  U64BitwiseAnd( UInt64   left, UInt64   right);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Return the bitwise OR value of the two parameters.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of the bitwise OR of left and right */
    static inline UInt64 U64BitwiseOr(UInt64 left, UInt64 right) { return (UInt64)(left) | (UInt64)(right); }
  #else
	/*! @brief	Return the bitwise OR value of the two parameters.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of the bitwise OR of left and right */
	extern UInt64  U64BitwiseOr( UInt64   left, UInt64   right);
    #define U64BitwiseOr(left, right) ((UInt64)(left) | (UInt64)(right))
  #endif
#else
/*! @brief	Return the bitwise OR value of the two parameters.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of the bitwise OR of left and right */
extern UInt64  U64BitwiseOr( UInt64   left, UInt64   right);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Return the bitwise EOR value of the two parameters.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of the bitwise EOR of left and right */
	static inline UInt64 U64BitwiseEor(UInt64 left, UInt64 right) { return (UInt64)(left) ^ (UInt64)(right); }
  #else
	/*! @brief	Return the bitwise EOR value of the two parameters.
		@param	left	a \c UInt64 value
		@param	right	a \c UInt64 value
		@result	the result of the bitwise OR of left and right */
	extern UInt64  U64BitwiseEor( UInt64   left, UInt64   right);
    #define U64BitwiseEor(left, right) ((UInt64)(left) ^ (UInt64)(right))
  #endif
#else
/*! @brief	Return the bitwise EOR value of the two parameters.
	@param	left	a \c UInt64 value
	@param	right	a \c UInt64 value
	@result	the result of the bitwise OR of left and right */
extern UInt64  U64BitwiseEor( UInt64   left, UInt64   right);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Return the bitwise NOT value of the given value
		@param	value	a \c UInt64 value
		@result	the result of the bitwise NOT of value */
	static inline UInt64 U64BitwiseNot(UInt64 value) { return ~((UInt64)(value)); }
  #else
	/*! @brief	Return the bitwise NOT value of the given value
		@param	value	a \c UInt64 value
		@result	the result of the bitwise NOT of value */
	extern UInt64  U64BitwiseNot(UInt64 value);
    #define U64BitwiseNot(value) (~((UInt64)(value)))
  #endif
#else
/*! @brief	Return the bitwise NOT value of the given value
	@param	value	a \c UInt64 value
	@result	the result of the bitwise NOT of value */
extern UInt64  U64BitwiseNot(UInt64 value);
#endif


#if TYPE_LONGLONG
#if MATH64_USE_INLINE
	/*! @brief	Return a \c UInt64 value created by shifting a given value right by a given number of bit positions
		@param	value	a \c UInt64 value
		@param	shift	a \c UInt32 number of positions to shift, between 0 and 127
		@result	the result of shifting value to the right by shift bit positions */
    static inline UInt64 U64ShiftRight(UInt64 value, UInt32 shift) { return (UInt64)(value) >> ((shift) & 0x7F); }
  #else
	/*! @brief	Return a \c UInt64 value created by shifting a given value right by a given number of bit positions
		@param	value	a \c UInt64 value
		@param	shift	a \c UInt32 number of positions to shift, between 0 and 127
		@result	the result of shifting value to the right by shift bit positions */
	extern UInt64  U64ShiftRight( UInt64   value, UInt32   shift);
    #define U64ShiftRight(value, shift) ((UInt64)(value) >> ((shift) & 0x7F))
  #endif
#else
/*! @brief	Return a \c UInt64 value created by shifting a given value right by a given number of bit positions
	@param	value	a \c UInt64 value
	@param	shift	a \c UInt32 number of positions to shift, between 0 and 127
	@result	the result of shifting value to the right by shift bit positions */
extern UInt64  U64ShiftRight( UInt64   value, UInt32   shift);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*! @brief	Return a \c UInt64 value created by shifting a given value left by a given number of bit positions
		@param	value	a \c UInt64 value
		@param	shift	a \c UInt32 number of positions to shift, between 0 and 127
		@result	the result of shifting value to the left by shift bit positions */
    static inline UInt64 U64ShiftLeft(UInt64 value, UInt32 shift) { return (UInt64)(value) << ((shift) & 0x7F); }
  #else
	/*! @brief	Return a \c UInt64 value created by shifting a given value left by a given number of bit positions
		@param	value	a \c UInt64 value
		@param	shift	a \c UInt32 number of positions to shift, between 0 and 127
		@result	the result of shifting value to the left by shift bit positions */
	extern UInt64  U64ShiftLeft( UInt64   value, UInt32   shift);
    #define U64ShiftLeft(value, shift) ((UInt64)(value) << ((shift) & 0x7F))
  #endif
#else
/*! @brief	Return a \c UInt64 value created by shifting a given value left by a given number of bit positions
	@param	value	a \c UInt64 value
	@param	shift	a \c UInt32 number of positions to shift, between 0 and 127
	@result	the result of shifting value to the left by shift bit positions */
extern UInt64  U64ShiftLeft( UInt64   value, UInt32   shift);
#endif



#if !TYPE_LONGDOUBLE_IS_DOUBLE
#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief Convert an signed 64 bit integer to a long double
		@param	value	a \c UInt64 value
		@result	a long double equivalent to double */
    static inline long double UInt64ToLongDouble(UInt64 value) { return (long double)(value); }
  #else
	/*!	@brief Convert an signed 64 bit integer to a long double
		@param	value	a \c UInt64 value
		@result	a long double equivalent to double */
	extern long double  UInt64ToLongDouble(UInt64 value);
    #define UInt64ToLongDouble(value) ((long double)(value))
  #endif
#else
/*!	@brief Convert an signed 64 bit integer to a long double
	@param	value	a \c UInt64 value
	@result	a long double equivalent to double */
extern long double  UInt64ToLongDouble(UInt64 value);
#endif


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief Convert long double (128-bit on PowerPC floating point) to a signed 64-bit integer
		@param	value	a \c long \c double value
		@result	a \c UInt64 value created by truncating value to a UInt64 */
    static inline UInt64 LongDoubleToUInt64(long double value) { return (UInt64)(value); }
  #else
	/*!	@brief Convert long double (128-bit on PowerPC floating point) to a signed 64-bit integer
		@param	value	a \c long \c double value
		@result	a \c UInt64 value created by truncating value to a UInt64 */
	extern UInt64  LongDoubleToUInt64(long double value);
    #define LongDoubleToUInt64(value) ((UInt64)(value))
  #endif
#else
/*!	@brief Convert long double (128-bit on PowerPC floating point) to a signed 64-bit integer
	@param	value	a \c long \c double value
	@result	a \c UInt64 value created by truncating value to a UInt64 */
extern UInt64  LongDoubleToUInt64(long double value);
#endif


#endif  /* !TYPE_LONGDOUBLE_IS_DOUBLE */


#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Coerces a \c UInt64 -> \c SInt64
		@param	value	a \c UInt64 value
		@result	the result of coercing value into a \c SInt64; if value is > SIntMax() then a negavite value */
    static inline SInt64 UInt64ToSInt64(UInt64 value) { return (SInt64)(value); }
  #else
	/*!	@brief	Coerces a \c UInt64 -> \c SInt64
		@param	value	a \c UInt64 value
		@result	the result of coercing value into a \c SInt64; if value is > SIntMax() then a negavite value */
	extern SInt64  UInt64ToSInt64(UInt64 value);
    #define UInt64ToSInt64(value) ((SInt64)(value))
  #endif
#else
/*!	@brief	Coerces a \c UInt64 -> \c SInt64
	@param	value	a \c UInt64 value
	@result	the result of coercing value into a \c SInt64; if value is > SIntMax() then a negavite value */
extern SInt64  UInt64ToSInt64(UInt64 value);
#endif



#if TYPE_LONGLONG
  #if MATH64_USE_INLINE
	/*!	@brief	Coerce a \c SInt64 -> \c UInt64
		@param	value	a \c SInt64 value
		@result	a UInt64 value; if value is less than zero then a positive value greater than SIntMax()  */
    static inline UInt64 SInt64ToUInt64(SInt64 value) { return (UInt64)(value); }
  #else
	/*!	@brief	Coerce a \c SInt64 -> \c UInt64
		@param	value	a \c SInt64 value
		@result	a UInt64 value; if value is less than zero then a positive value greater than SIntMax()  */
	extern UInt64  SInt64ToUInt64(SInt64 value);
    #define SInt64ToUInt64(value) ((UInt64)(value))
  #endif
#else
/*!	@brief	Coerce a \c SInt64 -> \c UInt64
	@param	value	a \c SInt64 value
	@result	a UInt64 value; if value is less than zero then a positive value greater than SIntMax()  */
extern UInt64  SInt64ToUInt64(SInt64 value);
#endif


/* 
   Functions to convert between [Unsigned]Wide and [S|U]Int64 types.
  
   These functions are necessary if source code which uses both
   wide and SInt64 is to compile under a compiler that supports
   long long, where SInt64 and UInt64 are supported natively as
   64 bit values by the compiler.
 
   SInt64ToWide
   
               Converts a SInt64 to a wide struct.  If SInt64 is implemented
              as a typedef of wide, the macro does nothing. If SInt64 is 
                implemented as a long long, it returns the long long in a 
             wide struct.
   
   WideToSInt64
   
               Converts a wide struct into a SInt64.  If SInt64 is implemented
                as a typedef of wide, the macro does nothing. If SInt64 is 
                implemented as a long long, it returns the value in the struct
             as a long long.
*/

#if TYPE_LONGLONG
		
	#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L
		
		static inline wide SInt64ToWide(SInt64 s) { wide result; result.hi = (SInt32)(((UInt64)s >> 32) & 0xffffffffUL); result.lo = (UInt32)((UInt64)s & 0xffffffffUL); return result; }
		static inline SInt64 WideToSInt64(wide w) { SInt64 result = w.hi; result = (result << 32) | w.lo; return result; }
		
		static inline UnsignedWide UInt64ToUnsignedWide(UInt64 u) { UnsignedWide result; result.hi = (UInt32)((u >> 32) & 0xffffffffUL); result.lo = (UInt32)(u & 0xffffffffUL); return result; }
		static inline UInt64 UnsignedWideToUInt64(UnsignedWide uw) { UInt64 result = uw.hi; result = (result << 32) | uw.lo; return result; }
		
	#elif defined(__GNUC__)
		
		static __inline wide SInt64ToWide(SInt64 s) { wide result; result.hi = (SInt32)(((UInt64)s >> 32) & 0xffffffffUL); result.lo = (UInt32)((UInt64)s & 0xffffffffUL); return result; }
		static __inline SInt64 WideToSInt64(wide w) { SInt64 result = w.hi; result = (result << 32) | w.lo; return result; }
		
		static __inline UnsignedWide UInt64ToUnsignedWide(UInt64 u) { UnsignedWide result; result.hi = (UInt32)((u >> 32) & 0xffffffffUL); result.lo = (UInt32)(u & 0xffffffffUL); return result; }
		static __inline UInt64 UnsignedWideToUInt64(UnsignedWide uw) { UInt64 result = uw.hi; result = (result << 32) | uw.lo; return result; }
		
	#else
		//  Although this isn't as efficent as it could be, there's no safe way to do this in a way which complies with both -ansi and -pedantic,
		//  on all the compilers I know about, so CarbonCore.framework just exports these so folks can link to them.  Only applications built with
		//  TYPE_LONGLONG defined though should call them, since the ABI is different in those cases.
		extern wide _SInt64ToWideLL(SInt64 s);
		extern SInt64 _WideToSInt64LL(wide w);
		
		extern wide _UInt64ToUnsignedWide(UInt64 u);
		extern UInt64 _UnsignedWideToUInt64(UnsignedWide uw);
			
		#define SInt64ToWide(x)         _SInt64ToWide(x)
		#define WideToSInt64(x)         _WideToSInt64(x)
		#define UInt64ToUnsignedWide(x) _UInt64ToUnsignedWide(x)
		#define UnsignedWideToUInt64(x) _UnsignedWideToUInt64(x)
			
	#endif

#else
	
	#define SInt64ToWide(x)         (x)
	#define WideToSInt64(x)         (x)
	#define UInt64ToUnsignedWide(x) (x)
	#define UnsignedWideToUInt64(x) (x)
	
#endif


#ifdef __cplusplus
}
#endif

#endif /* __MATH64__ */

