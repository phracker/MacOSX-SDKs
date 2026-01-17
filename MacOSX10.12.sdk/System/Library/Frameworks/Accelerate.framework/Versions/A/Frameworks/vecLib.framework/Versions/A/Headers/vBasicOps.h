/*
     File:       vecLib/vBasicOps.h
 
     Contains:   Basic Algebraic Operations for AltiVec
 
     Version:    vecLib-600.0
 
     Copyright:  Copyright (c) 1999-2016 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VBASICOPS__
#define __VBASICOPS__

#include <stdint.h>

#include "vecLibTypes.h"

#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if !defined __has_feature
    #define __has_feature(f)    0
#endif
#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull begin")
#else
    #define __nullable
    #define __nonnull
#endif


#if defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)
#if defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE2__

/*                                                                                  
  This section is a collection of algebraic functions that uses the AltiVec       
  instruction set, and is designed to facilitate vector processing in             
  mathematical programming. Following table indicates which functions are covered
  by AltiVec instruction set and which ones are performed by vBasicOps library:

Legend:
    H/W   = Hardware
    LIB  = vBasicOps Library
    NRel  = Next Release of vBasicOps Library
    N/A   = Not Applicable

+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
| Data Type/    | U8  | S8  | U16 | S16 | U32 | S32 | U64 | S64 | U128 | S128 |
| Function      |     |     |     |     |     |     |     |     |      |      |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Add        | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  |  LIB |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    AddS       | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Sub        | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    SubS       | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|  Mul(Half)    | LIB | LIB | LIB | LIB | LIB | LIB | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|Mul Even (Full)| H/W | H/W | H/W | H/W | LIB | LIB | LIB | LIB |  N/A |  N/A |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|Mul Odd  (Full)| H/W | H/W | H/W | H/W | LIB | LIB | LIB | LIB |  N/A |  N/A |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Divide     | LIB | LIB | LIB | LIB | LIB | LIB | LIB |NRel | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Shift      | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Rotate     | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+



Following is a short description of functions in this section:
                                                                         
      Add:      It takes two vectors of data elements and adds each element         
                of the second vector to the corresponding element of the first      
                vector and puts the result in the associated data element of the    
                destination register.

      Subtract: It takes two vectors of data elements and subtracts each element    
                of the second vector from the corresponding element of the first    
                vector and puts the result in the associated data element of the    
                destination register.

      Multiply: It takes two vectors of data elements and multiplies each element   
                of the first vector by the corresponding element of the second      
                vector and puts the result in the associated data element of the    
                destination register. 

      Divide:   It takes two vectors of data elements and divides each element      
                of the first vector by the corresponding element of the second      
                vector and puts the result in the associated data element of the    
                destination register. A pointer is passed to the function to get   
                the remainder.

      Shift:    It takes a vector of two 64-bit data elements or one 128-bit
                data element and shifts it to right or left, in a logical or 
                algebraic manner, using a shift factor that is passed as an
                arguement to the function.

      Rotate:   It takes a vector of two 64-bit data elements or one 128-bit
                data element and rotates it to right or left, using a shift 
               factor that is passed as an arguement to the function.


   Following abbreviations are used in the names of functions in this section:   
                                                                                 
      v            Vector                                                        
      U            Unsigned                                                      
      S            Signed                                                        
      8            8-bit                                                         
      16           16-bit                                                        
      32           32-bit                                                        
      64           64-bit                                                        
      128          128-bit                                                       
      Add          Addition                                                      
      AddS         Addition with Saturation                                      
      Sub          Subtraction                                                   
      SubS         Subtraction with Saturation                                   
      Mul          Multiplication                                                
      Divide       Division                                                      
      Half         Half (multiplication, width of result is the same as width of 
                      operands)                                                  
      Full         Full (multiplication, width of result is twice width of each  
                      operand)                                                   
      Even         Multiplication is performed on EVEN data elements of vector   
                      (Please note that Big endian is used. So the left-most     
                      data element is labled as element 0)                       
      Odd          Multiplication is performed on ODD  data elements of vector.  
      A            Algebraic      
      LL           Logical Left     
      LR           Logical Right     
      Shift        Shift by one factor     
      Shift2       Shift by two factors( only apply to 64 bit operation )     
      Rotate       Rotate by one factor     
      Rotate2      Rotate by two factors( only apply to 64 bit operation )     
                                                                                 
*/

// There are certain routines (namely vS64Add and vU64Add) with 1
// instruction implementations. There is no point in having a function
// call occur and then return after executing 1 instruction. Thus we
// introduce this conditional define to allow for certain inline
// attributes to be defined.
#if defined __SSE2__

#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
	#include <immintrin.h>
    _Pragma("clang assume_nonnull begin")
#else
	#include <immintrin.h>
#endif

#define __VBASICOPS_INLINE_ATTR__ __attribute__((__always_inline__, __nodebug__))
#endif // defined __SSE2__


/*
 *  vU8Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt8 
vU8Divide(
  vUInt8    vN,
  vUInt8    vD,
  vUInt8 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS8Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt8 
vS8Divide(
  vSInt8    vN,
  vSInt8    vD,
  vSInt8 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU16Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt16 
vU16Divide(
  vUInt16    vN,
  vUInt16    vD,
  vUInt16 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS16Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt16 
vS16Divide(
  vSInt16    vN,
  vSInt16    vD,
  vSInt16 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU32Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU32Divide(
  vUInt32    vN,
  vUInt32    vD,
  vUInt32 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32Divide(
  vSInt32    vN,
  vSInt32    vD,
  vSInt32 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64Divide(
  vUInt32    vN,
  vUInt32    vD,
  vUInt32 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64Divide(
  vSInt32    vN,
  vSInt32    vD,
  vSInt32 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128Divide(
  vUInt32    vN,
  vUInt32    vD,
  vUInt32 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128Divide(
  vSInt32    vN,
  vSInt32    vD,
  vSInt32 * __nullable vRemainder)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU8HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt8 
vU8HalfMultiply(
  vUInt8   vA,
  vUInt8   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS8HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt8 
vS8HalfMultiply(
  vSInt8   vA,
  vSInt8   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU16HalfMultiply()
 *  
 *  Currently on Intel, we inline a one instruction implementation of vU16HalfMultiply.
 *  An implementation is also exported in the library for legacy applications.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined __SSE2__
static __inline__ vUInt16 __VBASICOPS_INLINE_ATTR__
vU16HalfMultiply(
  vUInt16   __vbasicops_vA,
  vUInt16   __vbasicops_vB) { return _mm_mullo_epi16(__vbasicops_vA, __vbasicops_vB); }
#else // defined __SSE2__
extern vUInt16 
vU16HalfMultiply(
  vUInt16   vA,
  vUInt16   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif // defined __SSE2__


/*
 *  vS16HalfMultiply()
 *  
 *  On Intel, this function has a one instruction implementation that we inline. An
 *  implementation is also available via an exported symbol in the library for legacy
 *  applications.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined __SSE2__
static __inline__ vSInt16 __VBASICOPS_INLINE_ATTR__
vS16HalfMultiply(
  vSInt16   __vbasicops_vA,
  vSInt16   __vbasicops_vB) { return _mm_mullo_epi16(__vbasicops_vA, __vbasicops_vB); }
#else // defined __SSE2__
extern vSInt16 
vS16HalfMultiply(
  vSInt16   vA,
  vSInt16   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif // defined __SSE2__


/*
 *  vU32HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU32HalfMultiply(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32HalfMultiply(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU32FullMulEven()
 *  
 *  Currently we use a 3 instruction inlined implementation for vU32FullMulEven
 *  on Intel. Note that for legacy applications, there is still a compiled 
 *  implementation available in the library via an exported symbol.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined (__SSE2__)
static __inline__ vUInt32 __VBASICOPS_INLINE_ATTR__
vU32FullMulEven(
  vUInt32   __vbasicops_vA,
  vUInt32   __vbasicops_vB)
{
    __vbasicops_vA = _mm_srli_epi64(__vbasicops_vA, 32);
    __vbasicops_vB = _mm_srli_epi64(__vbasicops_vB, 32);
    return _mm_mul_epu32(__vbasicops_vA, __vbasicops_vB);
}
#else // defined __SSE2__
extern vUInt32 
vU32FullMulEven(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif // defined __SSE2__


/*
 *  vU32FullMulOdd()
 *  
 *  Currently on Intel, we inline a one instruction implementation of vU32FullMulOdd.
 *  An implementation is also exported in the library for legacy applications.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined __SSE2__
static __inline__ vUInt32 __VBASICOPS_INLINE_ATTR__
vU32FullMulOdd(
  vUInt32   __vbasicops_vA,
  vUInt32   __vbasicops_vB) { return _mm_mul_epu32(__vbasicops_vA, __vbasicops_vB); }
#else // defined __SSE2__
extern vUInt32 
vU32FullMulOdd(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif // defined __SSE2__


/*
 *  vS32FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32FullMulEven(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32FullMulOdd(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64FullMulEven(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64FullMulOdd(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64HalfMultiply(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64HalfMultiply(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64FullMulEven(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64FullMulOdd(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128HalfMultiply(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128HalfMultiply(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU64Sub()
 *  
 *  When SSE2 code generation is enabled on Intel architectures,
 *  vU64Sub has a single instruction implementation provided by an
 *  inlined function. On other architectures, the extern declaration
 *  will be provided and on all architectures, an exported vU64Sub
 *  routine is provided. This ensures that legacy applications are
 *  supported on Intel.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined __SSE2__
static __inline__ vUInt32 __VBASICOPS_INLINE_ATTR__
vU64Sub(
  vUInt32   __vbasicops_vA,
  vUInt32   __vbasicops_vB) { return _mm_sub_epi64(__vbasicops_vA, __vbasicops_vB); }
#else
extern vUInt32 
vU64Sub(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif


/*
 *  vU64SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64SubS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128Sub(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128SubS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Sub()
 *
 *  When SSE2 code generation is enabled on Intel architectures,
 *  vS64Sub has a single instruction implementation provided by an
 *  inlined function. On other architectures, the extern declaration
 *  will be provided and on all architectures, an exported vS64Sub
 *  routine is provided. This ensures that legacy applications are
 *  supported on Intel.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined __SSE2__
static __inline__ vSInt32 __VBASICOPS_INLINE_ATTR__
vS64Sub(
  vSInt32   __vbasicops_vA,
  vSInt32   __vbasicops_vB) { return _mm_sub_epi64(__vbasicops_vA, __vbasicops_vB); }
#else
extern vSInt32 
vS64Sub(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif


/*
 *  vS128Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128Sub(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64SubS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128SubS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU64Add()
 *  
 *  When SSE2 code generation is enabled on Intel architectures, single-instruction
 *  implementations of vU64Add is inlined instead of making an external function call. 
 * 
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined (__SSE2__)
static __inline__ vUInt32 __VBASICOPS_INLINE_ATTR__
vU64Add(
  vUInt32   __vbasicops_vA,
  vUInt32   __vbasicops_vB) { return _mm_add_epi64(__vbasicops_vA, __vbasicops_vB); }
#else
extern vUInt32
vU64Add(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif

/*
 *  vU64AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64AddS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128Add(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128AddS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Add()
 *
 *  When SSE2 code generation is enabled on Intel architectures, single-instruction
 *  implementations of vS64Add is inlined instead of making an external function call. 
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined __SSE2__
static __inline__ vSInt32 __VBASICOPS_INLINE_ATTR__
vS64Add(
  vSInt32   __vbasicops_vA,
  vSInt32   __vbasicops_vB) { return _mm_add_epi64(__vbasicops_vA, __vbasicops_vB); }
#else // defined __SSE2__
extern vSInt32 
vS64Add(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif // defined __SSE2__


/*
 *  vS64AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64AddS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128Add(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128AddS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU64Neg()
 */  
extern vUInt32 
vU64Neg (
  vUInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Neg()
 */  
extern vSInt32 
vS64Neg (
  vSInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vU1284Neg()
 */  
extern vUInt32 
vU128Neg (
  vUInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vS1284Neg()
 */  
extern vSInt32 
vS128Neg (
  vSInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);



/*
 *  vLL64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined (__SSE2__)
static __inline__ vUInt32 __VBASICOPS_INLINE_ATTR__
vLL64Shift(
  vUInt32   __vbasicops_vA,
  vUInt8    __vbasicops_vShiftFactor)
{
    return _mm_sll_epi64(__vbasicops_vA,
                         _mm_and_si128(__vbasicops_vShiftFactor, _mm_cvtsi32_si128( 0x3F )));
}
#else
extern vUInt32 
vLL64Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif

/*
 *  vA64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vA64Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLR64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
#if defined (__SSE2__)
static __inline__ vUInt32 __VBASICOPS_INLINE_ATTR__
vLR64Shift(
    vUInt32   __vbasicops_vA,
    vUInt8    __vbasicops_vShiftFactor)
{
    return _mm_srl_epi64(__vbasicops_vA,
                         _mm_and_si128(__vbasicops_vShiftFactor, _mm_cvtsi32_si128( 0x3F )));
}
#else
extern vUInt32 
vLR64Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
#endif

/*
 *  vLL64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLL64Shift2(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vA64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vA64Shift2(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLR64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLR64Shift2(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLL128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLL128Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vLR128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLR128Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vA128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vA128Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vL64Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vL64Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vR64Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vR64Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vL64Rotate2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vL64Rotate2(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vR64Rotate2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vR64Rotate2(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vL128Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vL128Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vR128Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vR128Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


#endif  // defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE2__

#endif  /* defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__) */


#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
#endif


#ifdef __cplusplus
}
#endif

#endif /* __VBASICOPS__ */
