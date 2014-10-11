/*
     File:       vecLib/vBigNum.h
 
     Contains:   Algebraic and logical operations on large operands.
 
     Version:    vecLib-138.1~9
 
     Copyright:  © 1999-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VBIGNUM__
#define __VBIGNUM__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

#ifdef __VEC__
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
  vector unsigned int  v;
  struct {
    unsigned long       MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       LSW;
  }                       s;
};
typedef union vU128                     vU128;
union vS128 {
  vector unsigned int  v;
  struct {
    signed long         MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       LSW;
  }                       s;
};
typedef union vS128                     vS128;
union vU256 {
  vector unsigned int  v[2];
  struct {
    unsigned long       MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       d4;
    unsigned long       d5;
    unsigned long       d6;
    unsigned long       d7;
    unsigned long       LSW;
  }                       s;
};
typedef union vU256                     vU256;
union vS256 {
  vector unsigned int  v[2];
  struct {
    signed long         MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       d4;
    unsigned long       d5;
    unsigned long       d6;
    unsigned long       d7;
    unsigned long       LSW;
  }                       s;
};
typedef union vS256                     vS256;
union vU512 {
  vector unsigned int  v[4];
  struct {
    unsigned long       MSB;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       d4;
    unsigned long       d5;
    unsigned long       d6;
    unsigned long       d7;
    unsigned long       d8;
    unsigned long       d9;
    unsigned long       d10;
    unsigned long       d11;
    unsigned long       d12;
    unsigned long       d13;
    unsigned long       d14;
    unsigned long       d15;
    unsigned long       LSB;
  }                       s;
};
typedef union vU512                     vU512;
union vS512 {
  vector unsigned int  v[4];
  struct {
    signed long         MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       d4;
    unsigned long       d5;
    unsigned long       d6;
    unsigned long       d7;
    unsigned long       d8;
    unsigned long       d9;
    unsigned long       d10;
    unsigned long       d11;
    unsigned long       d12;
    unsigned long       d13;
    unsigned long       d14;
    unsigned long       d15;
    unsigned long       LSW;
  }                       s;
};
typedef union vS512                     vS512;
union vU1024 {
  vector unsigned int  v[8];
  struct {
    unsigned long       MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       d4;
    unsigned long       d5;
    unsigned long       d6;
    unsigned long       d7;
    unsigned long       d8;
    unsigned long       d9;
    unsigned long       d10;
    unsigned long       d11;
    unsigned long       d12;
    unsigned long       d13;
    unsigned long       d14;
    unsigned long       d15;
    unsigned long       d16;
    unsigned long       d17;
    unsigned long       d18;
    unsigned long       d19;
    unsigned long       d20;
    unsigned long       d21;
    unsigned long       d22;
    unsigned long       d23;
    unsigned long       d24;
    unsigned long       d25;
    unsigned long       d26;
    unsigned long       d27;
    unsigned long       d28;
    unsigned long       d29;
    unsigned long       d30;
    unsigned long       d31;
    unsigned long       LSW;
  }                       s;
};
typedef union vU1024                    vU1024;
union vS1024 {
  vector unsigned int  v[8];
  struct {
    signed long         MSW;
    unsigned long       d2;
    unsigned long       d3;
    unsigned long       d4;
    unsigned long       d5;
    unsigned long       d6;
    unsigned long       d7;
    unsigned long       d8;
    unsigned long       d9;
    unsigned long       d10;
    unsigned long       d11;
    unsigned long       d12;
    unsigned long       d13;
    unsigned long       d14;
    unsigned long       d15;
    unsigned long       d16;
    unsigned long       d17;
    unsigned long       d18;
    unsigned long       d19;
    unsigned long       d20;
    unsigned long       d21;
    unsigned long       d22;
    unsigned long       d23;
    unsigned long       d24;
    unsigned long       d25;
    unsigned long       d26;
    unsigned long       d27;
    unsigned long       d28;
    unsigned long       d29;
    unsigned long       d30;
    unsigned long       d31;
    unsigned long       LSW;
  }                       s;
};
typedef union vS1024                    vS1024;

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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Divide(
  const vU256 *  numerator,
  const vU256 *  divisor,
  vU256 *        result,
  vU256 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Divide(
  const vS256 *  numerator,
  const vS256 *  divisor,
  vS256 *        result,
  vS256 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Divide(
  const vU512 *  numerator,
  const vU512 *  divisor,
  vU512 *        result,
  vU512 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Divide(
  const vS512 *  numerator,
  const vS512 *  divisor,
  vS512 *        result,
  vS512 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Divide(
  const vU1024 *  numerator,
  const vU1024 *  divisor,
  vU1024 *        result,
  vU1024 *        remainder)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Divide(
  const vS1024 *  numerator,
  const vS1024 *  divisor,
  vS1024 *        result,
  vS1024 *        remainder)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU128FullMultiply(
  const vU128 *  a,
  const vU128 *  b,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS128FullMultiply(
  const vS128 *  a,
  const vS128 *  b,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU256FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256FullMultiply(
  const vU256 *  a,
  const vU256 *  b,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256FullMultiply(
  const vS256 *  a,
  const vS256 *  b,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512FullMultiply(
  const vU512 *  a,
  const vU512 *  b,
  vU1024 *       result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512FullMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512FullMultiply(
  const vS512 *  a,
  const vS512 *  b,
  vS1024 *       result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU256HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256HalfMultiply(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256HalfMultiply(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512HalfMultiply(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512HalfMultiply(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024HalfMultiply(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024HalfMultiply(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Sub(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Sub(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU256SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256SubS(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256SubS(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Sub(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Sub(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512SubS(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512SubS(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Sub(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Sub(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024SubS(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024SubS(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Neg(
  const vU256 *  a,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Neg(
  const vS256 *  a,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Neg(
  const vU512 *  a,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Neg(
  const vS512 *  a,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Neg(
  const vU1024 *  a,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024Neg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Neg(
  const vS1024 *  a,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Add(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Add(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU256AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256AddS(
  const vU256 *  a,
  const vU256 *  b,
  vU256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256AddS(
  const vS256 *  a,
  const vS256 *  b,
  vS256 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Add(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Add(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512AddS(
  const vU512 *  a,
  const vU512 *  b,
  vU512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512AddS(
  const vS512 *  a,
  const vS512 *  b,
  vS512 *        result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Add(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Add(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024AddS(
  const vU1024 *  a,
  const vU1024 *  b,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024AddS(
  const vS1024 *  a,
  const vS1024 *  b,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU256Mod(
  const vU256 *  numerator,
  const vU256 *  divisor,
  vU256 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS256Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS256Mod(
  const vS256 *  numerator,
  const vS256 *  divisor,
  vS256 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU512Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU512Mod(
  const vU512 *  numerator,
  const vU512 *  divisor,
  vU512 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS512Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS512Mod(
  const vS512 *  numerator,
  const vS512 *  divisor,
  vS512 *        remainder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU1024Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vU1024Mod(
  const vU1024 *  numerator,
  const vU1024 *  divisor,
  vU1024 *        remainder)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS1024Mod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vS1024Mod(
  const vS1024 *  numerator,
  const vS1024 *  divisor,
  vS1024 *        remainder)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLL256Shift(
  const vU256 *   a,
  unsigned long   shiftAmount,
  vU256 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLL512Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLL512Shift(
  const vU512 *   a,
  unsigned long   shiftAmount,
  vU512 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLL1024Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLL1024Shift(
  const vU1024 *  a,
  unsigned long   shiftAmount,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLR256Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLR256Shift(
  const vU256 *   a,
  unsigned long   shiftAmount,
  vU256 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLR512Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLR512Shift(
  const vU512 *   a,
  unsigned long   shiftAmount,
  vU512 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLR1024Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vLR1024Shift(
  const vU1024 *  a,
  unsigned long   shiftAmount,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vA256Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vA256Shift(
  const vS256 *   a,
  unsigned long   shiftAmount,
  vS256 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vA512Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vA512Shift(
  const vS512 *   a,
  unsigned long   shiftAmount,
  vS512 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vA1024Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vA1024Shift(
  const vS1024 *  a,
  unsigned long   shiftAmount,
  vS1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vL256Rotate(
  const vU256 *   a,
  unsigned long   rotateAmount,
  vU256 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vL512Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vL512Rotate(
  const vU512 *   a,
  unsigned long   rotateAmount,
  vU512 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vL1024Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vL1024Rotate(
  const vU1024 *  a,
  unsigned long   rotateAmount,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vR256Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vR256Rotate(
  const vU256 *   a,
  unsigned long   rotateAmount,
  vU256 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vR512Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vR512Rotate(
  const vU512 *   a,
  unsigned long   rotateAmount,
  vU512 *         result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vR1024Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vR1024Rotate(
  const vU1024 *  a,
  unsigned long   rotateAmount,
  vU1024 *        result)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#endif  /* defined(__VEC__) */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __VBIGNUM__ */

