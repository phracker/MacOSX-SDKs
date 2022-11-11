/*
     File:       vecLib/vBigNum.h
 
     Contains:   Algebraic and logical operations on large operands.
 
     Version:    vecLib-794.100
 
     Copyright:  Copyright (c) 1999-2022 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VBIGNUM__
#define __VBIGNUM__

#include <stdint.h>
#include "vecLibTypes.h"

#include <os/availability.h>

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

#pragma options align=power

/************************************************************************************
*                                                                                   *
*  This library provides a set of subroutines for basic algebraic and some logical  *
*  operations performed on operands with the following sizes:                       *
*                                                                                   *
*            128 - bits                                                             *
*            256 - bits                                                             *
*            512 - bits                                                             *
*           1024 - bits                                                             *
*                                                                                   *
*  Following basic and algebraic operations are included:                           *
*                                                                                   *
*            Addition                                                               *
*            Subtraction                                                            *
*            Multiplication                                                         *
*            Division                                                               *
*            Mod                                                                    *
*            Shift Right                                                            *
*            Shift Right Arithmatic                                                 *
*            Shift Left                                                             *
*            Rotate Right                                                           *
*            Rotate Left                                                            *
*                                                                                   *
*                                                                                   *
************************************************************************************/
/***********************************************************************************
*   Following abbreviations are used in the names of functions in this library:    *
*                                                                                  *
*      v            Vector                                                         *
*      U            Unsigned                                                       *
*      S            Signed                                                         *
*      128          128  - bit                                                     *
*      256          256  - bit                                                     *
*      512          512  - bit                                                     *
*      1024         1024 - bit                                                     *
*      Add          Addition, modular arithmetic                                   *
*      AddS         Addition with Saturation                                       *
*      Sub          Subtraction, modular arithmetic                                *
*      SubS         Subtraction with Saturation                                    *
*      Multiply     Multiplication                                                 *
*      Divide       Division                                                       *
*      Half         Half (multiplication, width of result is the same as width of  *
*                      operands)                                                   *                         
*      Full         Full (multiplication, width of result is twice width of each   *
*                      operand)                                                    *
*                                                                                  *
*      Mod          Modular operation                                              *
*      Neg          Negate a number                                                *
*      A            Algebraic                                                      *
*      LL           Logical Left                                                   *
*      LR           Logical Right                                                  *
*      Shift        Shift                                                          *
*      Rotate       Rotation                                                       *
*                                                                                  *
***********************************************************************************/
/************************************************************************************
*                                                                                   *
*  A few explanations for the choices made in naming, passing arguments, and        *
*  various functions.                                                               *
*                                                                                   *
*      1) Names for the functions are made compatible with the names used in the    *
*      vBasicOps library. The format of the names are the same and include a        *
*      designation to show a vector operation, then a symbol for the type of data   *
*      (signed or unsigned), followed by the size of operands, then the operation   *
*      performed.                                                                   *
*                                                                                   *
*      2) Note that the logical and arithmetic shiftLeft operation are the same.    *
*                                                                                   *
*      3) Rotate operation is performed on unsigned and signed numbers.             *
*                                                                                   *
************************************************************************************/

/************************************************************************************
*                                                                                   *
*  Following are a set of structures for vector data types and scalar data types    *
*                                                                                   *
************************************************************************************/

union vU128 {
  vUInt32             v;
  struct {
    vUInt32             v1;
  }                       vs;
  struct {
    uint32_t            LSW;                  /*MSW;*/
    uint32_t            d3;                   /*d2;*/
    uint32_t            d2;                   /*d3;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vU128                     vU128 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vS128 {
  vUInt32             v;
  struct {
    vUInt32             v1;
  }                       vs;
  struct {
    int32_t             LSW;                  /*MSW;*/
    uint32_t            d3;                   /*d2;*/
    uint32_t            d2;                   /*d3;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vS128                     vS128 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vU256 {
  vUInt32             v[2];
  struct {
    vUInt32             v2;
    vUInt32             v1;
  }                       vs;
  struct {
    uint32_t            LSW;                  /*MSW;*/
    uint32_t            d7;                   /*d2;*/
    uint32_t            d6;                   /*d3;*/
    uint32_t            d5;                   /*d4;*/
    uint32_t            d4;                   /*d5;*/
    uint32_t            d3;                   /*d6;*/
    uint32_t            d2;                   /*d7;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vU256                     vU256 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vS256 {
  vUInt32             v[2];
  struct {
    vUInt32             v2;
    vUInt32             v1;
  }                       vs;
  struct {
    int32_t             LSW;                  /*MSW;*/
    uint32_t            d7;                   /*d2;*/
    uint32_t            d6;                   /*d3;*/
    uint32_t            d5;                   /*d4;*/
    uint32_t            d4;                   /*d5;*/
    uint32_t            d3;                   /*d6;*/
    uint32_t            d2;                   /*d7;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vS256                     vS256 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vU512 {
  vUInt32             v[4];
  struct {
    vUInt32             v4;
    vUInt32             v3;
    vUInt32             v2;
    vUInt32             v1;
  }                       vs;
  struct {
    uint32_t            LSW;                  /*MSB;*/
    uint32_t            d15;                  /*d2;*/
    uint32_t            d14;                  /*d3;*/
    uint32_t            d13;                  /*d4;*/
    uint32_t            d12;                  /*d5;*/
    uint32_t            d11;                  /*d6;*/
    uint32_t            d10;                  /*d7;*/
    uint32_t            d9;                   /*d8;*/
    uint32_t            d8;                   /*d9;*/
    uint32_t            d7;                   /*d10;*/
    uint32_t            d6;                   /*d11;*/
    uint32_t            d5;                   /*d12;*/
    uint32_t            d4;                   /*d13;*/
    uint32_t            d3;                   /*d14;*/
    uint32_t            d2;                   /*d15;*/
    uint32_t            MSW;                  /*LSB;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vU512                     vU512 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vS512 {
  vUInt32             v[4];
  struct {
    vUInt32             v4;
    vUInt32             v3;
    vUInt32             v2;
    vUInt32             v1;
  }                       vs;
  struct {
    int32_t             LSW;                  /*MSW;*/
    uint32_t            d15;                  /*d2;*/
    uint32_t            d14;                  /*d3;*/
    uint32_t            d13;                  /*d4;*/
    uint32_t            d12;                  /*d5;*/
    uint32_t            d11;                  /*d6;*/
    uint32_t            d10;                  /*d7;*/
    uint32_t            d9;                   /*d8;*/
    uint32_t            d8;                   /*d9;*/
    uint32_t            d7;                   /*d10;*/
    uint32_t            d6;                   /*d11;*/
    uint32_t            d5;                   /*d12;*/
    uint32_t            d4;                   /*d13;*/
    uint32_t            d3;                   /*d14;*/
    uint32_t            d2;                   /*d15;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vS512                     vS512 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vU1024 {
  vUInt32             v[8];
  struct {
    vUInt32             v8;
    vUInt32             v7;
    vUInt32             v6;
    vUInt32             v5;
    vUInt32             v4;
    vUInt32             v3;
    vUInt32             v2;
    vUInt32             v1;
  }                       vs API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
  struct {
    uint32_t            LSW;                  /*MSW;*/
    uint32_t            d31;                  /*d2;*/
    uint32_t            d30;                  /*d3;*/
    uint32_t            d29;                  /*d4;*/
    uint32_t            d28;                  /*d5;*/
    uint32_t            d27;                  /*d6;*/
    uint32_t            d26;                  /*d7;*/
    uint32_t            d25;                  /*d8;*/
    uint32_t            d24;                  /*d9;*/
    uint32_t            d23;                  /*d10;*/
    uint32_t            d22;                  /*d11;*/
    uint32_t            d21;                  /*d12;*/
    uint32_t            d20;                  /*d13;*/
    uint32_t            d19;                  /*d14;*/
    uint32_t            d18;                  /*d15;*/
    uint32_t            d17;                  /*d16;*/
    uint32_t            d16;                  /*d17;*/
    uint32_t            d15;                  /*d18;*/
    uint32_t            d14;                  /*d19;*/
    uint32_t            d13;                  /*d20;*/
    uint32_t            d12;                  /*d21;*/
    uint32_t            d11;                  /*d22;*/
    uint32_t            d10;                  /*d23;*/
    uint32_t            d9;                   /*d24;*/
    uint32_t            d8;                   /*d25;*/
    uint32_t            d7;                   /*d26;*/
    uint32_t            d6;                   /*d27;*/
    uint32_t            d5;                   /*d28;*/
    uint32_t            d4;                   /*d29;*/
    uint32_t            d3;                   /*d30;*/
    uint32_t            d2;                   /*d31;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vU1024                    vU1024 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
union vS1024 {
  vUInt32             v[8];
  struct {
    vUInt32             v8;
    vUInt32             v7;
    vUInt32             v6;
    vUInt32             v5;
    vUInt32             v4;
    vUInt32             v3;
    vUInt32             v2;
    vUInt32             v1;
  }                       vs;
  struct {
    int32_t             LSW;                  /*MSW;*/
    uint32_t            d31;                  /*d2;*/
    uint32_t            d30;                  /*d3;*/
    uint32_t            d29;                  /*d4;*/
    uint32_t            d28;                  /*d5;*/
    uint32_t            d27;                  /*d6;*/
    uint32_t            d26;                  /*d7;*/
    uint32_t            d25;                  /*d8;*/
    uint32_t            d24;                  /*d9;*/
    uint32_t            d23;                  /*d10;*/
    uint32_t            d22;                  /*d11;*/
    uint32_t            d21;                  /*d12;*/
    uint32_t            d20;                  /*d13;*/
    uint32_t            d19;                  /*d14;*/
    uint32_t            d18;                  /*d15;*/
    uint32_t            d17;                  /*d16;*/
    uint32_t            d16;                  /*d17;*/
    uint32_t            d15;                  /*d18;*/
    uint32_t            d14;                  /*d19;*/
    uint32_t            d13;                  /*d20;*/
    uint32_t            d12;                  /*d21;*/
    uint32_t            d11;                  /*d22;*/
    uint32_t            d10;                  /*d23;*/
    uint32_t            d9;                   /*d24;*/
    uint32_t            d8;                   /*d25;*/
    uint32_t            d7;                   /*d26;*/
    uint32_t            d6;                   /*d27;*/
    uint32_t            d5;                   /*d28;*/
    uint32_t            d4;                   /*d29;*/
    uint32_t            d3;                   /*d30;*/
    uint32_t            d2;                   /*d31;*/
    uint32_t            MSW;                  /*LSW;*/
  }                       s;
} API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);
typedef union vS1024                    vS1024 API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);

/************************************************************************************
*                                                                                   *
*                                Division operations                                *
*                                                                                   *
************************************************************************************/
/*
 *  vU256Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Divide(
  const vU256       *numerator,
  const vU256       *divisor,
  vU256             *result,
  vU256 * __nullable remainder)
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Divide(
  const vS256       *numerator,
  const vS256       *divisor,
  vS256             *result,
  vS256 * __nullable remainder)
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Divide(
  const vU512       *numerator,
  const vU512       *divisor,
  vU512             *result,
  vU512 * __nullable remainder)
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Divide(
  const vS512       *numerator,
  const vS512       *divisor,
  vS512             *result,
  vS512 * __nullable remainder)
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Divide(
  const vU1024       *numerator,
  const vU1024       *divisor,
  vU1024             *result,
  vU1024 * __nullable remainder)
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Divide(
  const vS1024       *numerator,
  const vS1024       *divisor,
  vS1024             *result,
  vS1024 * __nullable remainder)
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                              Multiply operations                                  *
*                                                                                   *
************************************************************************************/

/*
 *  vU128FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU128FullMultiply(
  const vU128 *  a,
  const vU128 *  b,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS128FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS128FullMultiply(
  const vS128 *  a,
  const vS128 *  b,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU256FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256FullMultiply(
  const vU256 *  a,
  const vU256 *  b,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256FullMultiply(
  const vS256 *  a,
  const vS256 *  b,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512FullMultiply(
  const vU512 *  a,
  const vU512 *  b,
  vU1024 *       result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512FullMultiply(
  const vS512 *  a,
  const vS512 *  b,
  vS1024 *       result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU256HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256HalfMultiply(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256HalfMultiply(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512HalfMultiply(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512HalfMultiply(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024HalfMultiply(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024HalfMultiply(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                             Subtraction operations                                *
*                                                                                   *
************************************************************************************/

/*
 *  vU256Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Sub(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Sub(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU256SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256SubS(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256SubS(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Sub(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Sub(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512SubS(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512SubS(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Sub(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Sub(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024SubS(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024SubS(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                                Negate operations                                  *
*                                                                                   *
************************************************************************************/

/*
 *  vU256Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Neg(
  const vU256 *  a,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Neg(
  const vS256 *  a,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Neg(
  const vU512 *  a,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Neg(
  const vS512 *  a,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Neg(
  const vU1024 *  a,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Neg(
  const vS1024 *  a,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                                Addition operations                                *
*                                                                                   *
************************************************************************************/

/*
 *  vU256Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Add(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Add(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU256AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256AddS(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256AddS(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Add(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Add(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512AddS(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512AddS(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Add(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Add(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024AddS(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024AddS(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                                   Mod operations                                  *
*                                                                                   *
************************************************************************************/

/*
 *  vU256Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Mod(
  const vU256 *  numerator,
  const vU256 *  divisor,
  vU256 *        remainder) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS256Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Mod(
  const vS256 *  numerator,
  const vS256 *  divisor,
  vS256 *        remainder) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU512Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Mod(
  const vU512 *  numerator,
  const vU512 *  divisor,
  vU512 *        remainder) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS512Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Mod(
  const vS512 *  numerator,
  const vS512 *  divisor,
  vS512 *        remainder) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vU1024Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Mod(
  const vU1024 *  numerator,
  const vU1024 *  divisor,
  vU1024 *        remainder) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vS1024Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Mod(
  const vS1024 *  numerator,
  const vS1024 *  divisor,
  vS1024 *        remainder) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                                Shift operations                                   *
*                                                                                   *
************************************************************************************/

/*
 *  vLL256Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLL256Shift(
  const vU256 *  a,
  uint32_t       shiftAmount,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vLL512Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLL512Shift(
  const vU512 *  a,
  uint32_t       shiftAmount,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vLL1024Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLL1024Shift(
  const vU1024 *  a,
  uint32_t        shiftAmount,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vLR256Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLR256Shift(
  const vU256 *  a,
  uint32_t       shiftAmount,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vLR512Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLR512Shift(
  const vU512 *  a,
  uint32_t       shiftAmount,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vLR1024Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLR1024Shift(
  const vU1024 *  a,
  uint32_t        shiftAmount,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vA256Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vA256Shift(
  const vS256 *  a,
  uint32_t       shiftAmount,
  vS256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vA512Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vA512Shift(
  const vS512 *  a,
  uint32_t       shiftAmount,
  vS512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vA1024Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vA1024Shift(
  const vS1024 *  a,
  uint32_t        shiftAmount,
  vS1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);



/************************************************************************************
*                                                                                   *
*                                  Rotate operations                                *
*                                                                                   *
************************************************************************************/

/*
 *  vL256Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vL256Rotate(
  const vU256 *  a,
  uint32_t       rotateAmount,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vL512Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vL512Rotate(
  const vU512 *  a,
  uint32_t       rotateAmount,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vL1024Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vL1024Rotate(
  const vU1024 *  a,
  uint32_t        rotateAmount,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vR256Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vR256Rotate(
  const vU256 *  a,
  uint32_t       rotateAmount,
  vU256 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vR512Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vR512Rotate(
  const vU512 *  a,
  uint32_t       rotateAmount,
  vU512 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);


/*
 *  vR1024Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vR1024Rotate(
  const vU1024 *  a,
  uint32_t        rotateAmount,
  vU1024 *        result) API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios);

#pragma options align=reset

#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
#endif

#ifdef __cplusplus
}
#endif

#endif /* __VBIGNUM__ */
