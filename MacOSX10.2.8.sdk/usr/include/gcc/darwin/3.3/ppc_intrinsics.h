/* APPLE LOCAL PPC_INTRINSICS */

/* Definitions for PowerPC intrinsic instructions
   Copyright (C) 2002 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

/* As a special exception, if you include this header file into source
   files compiled by GCC, this header file does not by itself cause
   the resulting executable to be covered by the GNU General Public
   License.  This exception does not however invalidate any other
   reasons why the executable file might be covered by the GNU General
   Public License.  */

/*
 * The following PowerPC intrinsics are provided by this header:
 *
 * Low-Level Processor Synchronization
 *   __eieio    - Enforce In-Order Execution of I/O
 *   __isync    - Instruction Synchronize
 *   __sync     - Synchronize
 *
 * Manipulating the Contents of a Variable or Register
 *   __cntlzw   - Count Leading Zeros Word
 *   __rlwimi   - Rotate Left Word Immediate then Mask Insert
 *   __rlwinm   - Rotate Left Word Immediate then AND with Mask
 *   __rlwnm    - Rotate Left Word then AND with Mask
 *
 * Byte-Reversing Functions
 *   __lhbrx    - Load Half Word Byte-Reverse Indexed
 *   __lwbrx    - Load Word Byte-Reverse Indexed
 *   __sthbrx   - Store Half Word Byte-Reverse Indexed
 *   __stwbrx   - Store Word Byte-Reverse Indexed
 *
 * Data Cache Manipulation
 *   __dcba     - Data Cache Block Allocate
 *   __dcba     - Data Cache Block Flush
 *   __dcbst    - Data Cache Block Store
 *   __dcbt     - Data Cache Block Touch
 *   __dcbtst   - Data Cache Block Touch for Store
 *   __dcbz     - Data Cache Block Set to Zero
 *
 * Setting the Floating-Point Environment
 *   __setflm   - Set Floating-point Mode
 *
 * Math Functions
 *   __fabs     - Floating-Point Absolute Value
 *   __fnabs    - Floating Negative Absolute Value
 *   __fctiw    - Floating Convert to Integer Word
 *   __fctiwz   - Floating Convert to Integer Word with Round toward Zero
 *   __fmadd    - Floating Multiply-Add (Double-Precision)
 *   __fmadds   - Floating Multiply-Add Single
 *   __fmsub    - Floating Multiply-Subract (Double-Precision)
 *   __fmsubs   - Floating Multiply-Subract Single
 *   __fmul     - Floating Multiply (Double-Precision)
 *   __fmuls    - Floating Multiply Single
 *   __fnmadd   - Floating Negative Multiply-Add (Double-Precision)
 *   __fnmadds  - Floating Negative Multiply-Add Single
 *   __fnmsub   - Floating Negative Multiply-Subtract (Double-Precision)
 *   __fnmsubs  - Floating Negative Multiply-Subtract Single
 *   __fres     - Floating Reciprocal Estimate
 *   __frsp     - Floating Round to Single-Precision
 *   __frsqrte  - Floating Reciprocal Square Root Estimate
 *   __frsqrtes - Floating Reciprocal Square Root Estimate Single
 *   __fsel     - Floating Select
 *   __fsels    - Floating Select (Single-Precision variant)
 *   __fsqrt    - Floating-Point Square Root (Double-Precision)
 *   __fsqrts   - Floating-Point Square Root Single-Precision
 *   __mulhw    - Multiply High Word
 *   __mulhwu   - Multiply High Word Unsigned
 *   __stfiwx   - Store Floating-Point as Integer Word Indexed
 *
 * Miscellaneous Functions
 *   __astrcmp  - assembly strcmp
 *   __icbi     - Instruction Cache Block Invalidate
 *   __mffs     - Move from FPSCR
 *   __mfspr    - Move from Special Purpose Register
 *   __mtfsf    - Move to SPSCR Fields
 *   __mtspr    - Move to Special Purpose Register
 *   __OSReadSwapSInt16 - lhbrx for signed shorts
 *   __OSReadSwapUInt16 - lhbrx for unsigned shorts
 *
 * TO DO:
 * - Desired:
 *   mullw
 * - Available in CodeWarrior, not yet implemented here:
 *   abs, labs, fabsf, fnabsf
 *
 * NOTES:
 * - Some of the intrinsics need to be macros because certain 
 *   parameters MUST be integer constants and not values in registers.
 * - The declarations use __asm__ instead of asm and __inline__ instead
 *   of inline to prevent errors when -ansi is specified.
 * - Some of the intrinsic definitions use the "volatile" specifier on
 *   the "asm" statements in order to work around what appears to be
 *   a bug in the compiler/optimizer.  In general we have avoided the
 *   use of "volatile" because it suppresses optimization on the
 *   generated instructions.  The instructions to which "volatile"
 *   has been added where it appears that it should not be needed are
 *   lhbrx and lwbrx.
 *
 * Contributors: Fred Forsman (editor), Turly O'Connor, Ian Ollmann
 * Last modified: June 4, 2002
 */

#ifndef _PPC_INTRINSICS_H_
#define _PPC_INTRINSICS_H_

#if defined(__ppc__) && ! defined(__MWERKS__)

/*******************************************************************
 *                 Special Purpose Registers (SPRs)                *
 *******************************************************************/

#define __SPR_MQR       0               /* PPC 601 only */
#define __SPR_XER       1               
#define __SPR_RTCU      4               /* Real time clock upper. PPC 601 only.*/
#define __SPR_RTCL      5               /* Real time clock lower. PPC 601 only.*/
#define __SPR_LR        8               
#define __SPR_CTR       9               
#define __SPR_VRSAVE    256             /* AltiVec */
#define __SPR_TBL       268             /* Time-base Lower. Not on PPC 601 */
#define __SPR_TBU       269             /* Time-base Upper. Not on PPC 601 */
#define __SPR_UMMCR2    928             /* PPC 74xx */
#define __SPR_UPMC5     929             /* PPC 745x */
#define __SPR_UPMC6     930             /* PPC 745x */
#define __SPR_UBAMR     935             /* PPC 7400 and 7410 */
#define __SPR_UMMCR0    936             /* PPC 74xx and 750 */
#define __SPR_UPMC1     937             /* PPC 74xx and 750 */
#define __SPR_UPMC2     938             /* PPC 74xx and 750 */
#define __SPR_USIAR     939             /* PPC 74xx and 750 */
#define __SPR_UMMCR1    940             /* PPC 74xx and 750 */
#define __SPR_UPMC3     941             /* PPC 74xx and 750 */
#define __SPR_UPMC4     942             /* PPC 74xx and 750 */
#define __SPR_PIR       1023            /* supervisor level only! */

/*
 * Shorthand macros for some commonly used SPR's.
 */
#define __mfxer()               __mfspr(__SPR_XER)
#define __mflr()                __mfspr(__SPR_LR)
#define __mfctr()               __mfspr(__SPR_CTR)
#define __mfvrsave()            __mfspr(__SPR_VRSAVE)
#define __mftb()                __mfspr(__SPR_TBL)
#define __mftbu()               __mfspr(__SPR_TBU)

#define __mtlr(value)           __mtspr(__SPR_LR, value)
#define __mtxer(value)          __mtspr(__SPR_XER, value)
#define __mtctr(value)          __mtspr(__SPR_CTR, value)
#define __mtvrsave(value)       __mtspr(__SPR_VRSAVE, value)


/*******************************************************************
 *               Low-Level Processor Synchronization               *
 *******************************************************************/

/*
 * __eieio - Enforce In-Order Execution of I/O
 *
 *   void __eieio (void);
 */
#define __eieio() __asm__ ("eieio" : : : "memory")

/*
 * __isync - Instruction Synchronize
 *
 *   void __isync (void);
 */
#define __isync()       \
  __asm__ volatile ("isync")

/*
 * __sync - Synchronize
 *
 *  void __sync (void);
 */
#define __sync() __asm__ volatile ("sync")


/*******************************************************************
 *                     Byte-Reversing Functions                    *
 *******************************************************************/

/*
 * __lhbrx - Load Half Word Byte-Reverse Indexed
 *
 *   int __lhbrx(void *, int);
 */
#define __lhbrx(base, index)   \
  ({ unsigned short lhbrxResult;       \
     __asm__ volatile ("lhbrx %0, %1, %2" : "=r" (lhbrxResult) : "b%" (index), "r" (base) : "memory"); \
     /*return*/ lhbrxResult; })

/*
 * __lwbrx - Load Word Byte-Reverse Indexed
 *
 *   int __lwbrx(void *, int);
 */
#define __lwbrx(base, index)    \
  ({ unsigned long lwbrxResult; \
     __asm__ volatile ("lwbrx %0, %1, %2" : "=r" (lwbrxResult) : "b%" (index), "r" (base) : "memory"); \
     /*return*/ lwbrxResult; })

/*
 * __sthbrx - Store Half Word Byte-Reverse Indexed
 *
 *   int __sthbrx(unsigned short, void *, int);
 */
#define __sthbrx(value, base, index)    \
  __asm__ ("sthbrx %0, %1, %2" : : "r" (value), "b%" (index), "r" (base) : "memory")

/*
 * __stwbrx - Store Word Byte-Reverse Indexed
 *
 *   int __sthbrx(unsigned int, void *, int);
 */
#define __stwbrx(value, base, index)    \
  __asm__ ("stwbrx %0, %1, %2" : : "r" (value), "b%" (index), "r" (base) : "memory")


/*******************************************************************
 *       Manipulating the Contents of a Variable or Register       *
 *******************************************************************/

/*
 * __cntlzw - Count Leading Zeros Word
 */
static inline int __cntlzw (int value) __attribute__((always_inline));
static inline int 
__cntlzw (int value)
{
  long result;
  __asm__ ("cntlzw %0, %1" 
           /* outputs:  */ : "=r" (result) 
           /* inputs:   */ : "r" (value));
  return result;
}

/*
 * __rlwimi - Rotate Left Word Immediate then Mask Insert
 *
 *   int __rlwimi(int, int, int, int, int);
 *
 * We don't mention "%1" below: operand[1] needs to be skipped as 
 * it's just a placeholder to let the compiler know that rA is read 
 * from as well as written to. 
 */
#define __rlwimi(rA, rS, cnt, mb, me)                               \
  ({ __asm__ ("rlwimi %0,%2,%3,%4,%5" : "=r" (rA)                   \
              : "0" (rA), "r" (rS), "n" (cnt), "n" (mb), "n" (me)); \
     /*return*/ rA;})

/*
 * __rlwinm - Rotate Left Word Immediate then AND with Mask
 *
 *   int __rlwinm(int, int, int, int);
 */
#define __rlwinm(rS, cnt, mb, me)                          \
  ({ unsigned long val, src = (rS);                        \
     __asm__ ("rlwinm %0,%1,%2,%3,%4" : "=r" (val)         \
              : "r" (src), "n" (cnt), "n" (mb), "n" (me)); \
     /*return*/ val;})

/*
 * __rlwnm - Rotate Left Word then AND with Mask
 *
 *   int __rlwnm(int, int, int, int);
 */
#define __rlwnm(value, leftRotateBits, maskStart, maskEnd)                        \
  ({ long result;                                                        \
     __asm__ ("rlwnm %0, %1, %2, %3, %4" : "=r" (result) :                        \
              "r" (value), "r" (leftRotateBits), "n" (maskStart), "n" (maskEnd)); \
     /*return */ result; })


/*******************************************************************
 *                     Data Cache Manipulation                     *
 *******************************************************************/

/* 
 * --- Data Cache Block instructions ---
 *
 * Please see Motorola's "The Programming Environments for 32-Bit 
 * Microprocessors" for a description of what these do.
 *
 *   Parameter descriptions:
 *
 *     base             starting address for figuring out where the 
 *                      cacheline is
 *
 *     index            byte count to be added to the base address for 
 *                      purposes of calculating the effective address 
 *                      of the cacheline to be operated on.  
 *                                      
 *   Effective Address of cacheline to be manipulated = 
 *     (char*) base + index
 *      
 *   WARNING: The size and alignment of cachelines are subject to 
 *     change on future processors!  Cachelines are 32 bytes in 
 *     size and are aligned to 32 bytes on PowerPC 601, 603, 604, 
 *     750, 7400, 7410, 7450, and 7455.
 *
 */
 
/*
 * __dcba - Data Cache Block Allocate
 *
 *   void __dcba(void *, int)
 *
 * WARNING: dcba is a valid instruction only on PowerPC 7400, 7410, 
 *          7450 and 7455.
 */
#define __dcba(base, index)     \
  __asm__ ("dcba %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")

/*
 * __dcbf - Data Cache Block Flush
 *
 *   void __dcbf(void *, int);
 */
#define __dcbf(base, index)     \
  __asm__ ("dcbf %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")

/*
 * __dcbst - Data Cache Block Store
 *
 *   void __dcbst(void *, int);
 */
#define __dcbst(base, index)    \
  __asm__ ("dcbst %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")

/*
 * __dcbt - Data Cache Block Touch
 *
 *   void __dcbt(void *, int);
 */
#define __dcbt(base, index)     \
  __asm__ ("dcbt %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")

/*
 * __dcbtst - Data Cache Block Touch for Store
 *
 *   void __dcbtst(void *, int);
 */
#define __dcbtst(base, index)   \
  __asm__ ("dcbtst %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")

/*
 * __dcbz - Data Cache Block Set to Zero
 *
 *   void __dcbz(void *, int);
 */
#define __dcbz(base, index)     \
  __asm__ ("dcbz %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")


/*******************************************************************
 *              Setting the Floating-Point Environment             *
 *******************************************************************/

/*
 * __setflm - Set Floating-point Mode
 *
 * Sets the FPSCR (floating-point status and control register),
 * returning the original value.
 *
 *   ??? CW: float __setflm(float);
 */
static inline double __setflm (double newflm) __attribute__((always_inline));
static inline double 
__setflm(double newflm)
{
  double original;

  __asm__ ("mffs %0" 
           /* outputs:  */ : "=f" (original));
  __asm__ ("mtfsf 255,%0" 
           /* outputs:  */ : /* none */ 
           /* inputs:   */ : "f" (newflm));
  return original;
}


/*******************************************************************
 *                          Math Functions                         *
 *******************************************************************/

/*
 * __fabs - Floating-Point Absolute Value
 */
static inline double __fabs (double value) __attribute__((always_inline));
static inline double 
__fabs (double value)
{
  double result;
  __asm__ ("fabs %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (value));
  return result;
}

/*
 * __fnabs - Floating Negative Absolute Value
 */
static inline double __fnabs (double b) __attribute__((always_inline));
static inline double 
__fnabs (double b)
{
  double result;
  __asm__ ("fnabs %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (b));
  return result;
}

/*
 * fctiw - Floating Convert to Integer Word
 *
 * Convert the input value to a signed long and place in the low 32 
 * bits of the FP register.  Clip to LONG_MIN or LONG_MAX if the FP 
 * value exceeds the range representable by a long.  Use the rounding
 * mode indicated in the FPSCR.
 */
static inline double __fctiw (double b) __attribute__((always_inline));
static inline double 
__fctiw (double b)
{
  double result;
  __asm__ ("fctiw %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (b));
  return result;
}

/*
 * fctiwz - Floating Convert to Integer Word with Round toward Zero
 *
 * Convert the input value to a signed long and place in the low 32 
 * bits of the FP register.  Clip to LONG_MIN or LONG_MAX if the FP 
 * value exceeds the range representable by a long.
 */
static inline double __fctiwz (double b) __attribute__((always_inline));
static inline double 
__fctiwz (double b)
{
  double result;
  __asm__ ("fctiwz %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (b));
  return result;
}

/*
 * fmadd - Floating Multiply-Add (Double-Precision)
 *
 *   (a * c + b) double precision
 */
static inline double __fmadd (double a, double c, double b) __attribute__((always_inline));
static inline double 
__fmadd (double  a, double c, double b)
{
  double result;
  __asm__ ("fmadd %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * fmadds - Floating Multiply-Add Single
 *
 *   (a * c + b) single precision
 *
 * Double precision arguments are used to prevent the compiler from
 * issuing frsp instructions upstream.
 */
static inline float __fmadds (double a, double c, double b) __attribute__((always_inline));
static inline float 
__fmadds (double  a, double c, double b)
{
  float result;
  __asm__ ("fmadds %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * fmsub - Floating Multiply-Subract (Double-Precision)
 *
 *   (a * c - b) double precision
 */
static inline double __fmsub (double a, double c, double b) __attribute__((always_inline));
static inline double 
__fmsub (double  a, double c, double b)
{
  double result;
  __asm__ ("fmsub %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * fmsubs - Floating Multiply-Subract Single
 *
 *   (a * c - b) single precision
 *
 * Double precision arguments are used to prevent the compiler from
 * issuing frsp instructions upstream.
 */
static inline float __fmsubs (double a, double c, double b) __attribute__((always_inline));
static inline float 
__fmsubs (double  a, double c, double b)
{
  float result;
  __asm__ ("fmsubs %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * fmul - Floating Multiply (Double-Precision)
 *
 *   (a * c) double precision
 */
static inline double __fmul (double a, double c) __attribute__((always_inline));
static inline double 
__fmul (double  a, double c)
{
  double result;
  __asm__ ("fmul %0, %1, %2" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c));
  return result;
}

/*
 * fmuls - Floating Multiply Single
 *
 *   (a * c) single precision
 *
 * Double precision arguments are used to prevent the compiler from
 * issuing frsp instructions upstream.
 */
static inline float __fmuls (double a, double c) __attribute__((always_inline));
static inline float 
__fmuls (double  a, double c)
{
  float result;
  __asm__ ("fmuls %0, %1, %2" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c));
  return result;
}

/*
 * __fnmadd - Floating Negative Multiply-Add (Double-Precision)
 *
 *   -(a * c + b) double precision
 */
static inline double __fnmadd (double a, double c, double b) __attribute__((always_inline));
static inline double 
__fnmadd (double  a, double c, double b)
{
  double result;
  __asm__ ("fnmadd %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * __fnmadds - Floating Negative Multiply-Add Single
 *
 *   -(a * c + b) single precision
 *
 * Double precision arguments are used to prevent the compiler from
 * issuing frsp instructions upstream.
 */
static inline float __fnmadds (double a, double c, double b) __attribute__((always_inline));
static inline float 
__fnmadds (double  a, double c, double b)
{
  float result;
  __asm__ ("fnmadds %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * __fnmsub - Floating Negative Multiply-Subtract (Double-Precision)
 *
 *   -(a * c - B) double precision
 */
static inline double __fnmsub (double a, double c, double b) __attribute__((always_inline));
static inline double 
__fnmsub (double  a, double c, double b)
{
  double result;
  __asm__ ("fnmsub %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * __fnmsubs - Floating Negative Multiply-Subtract Single
 *
 *   -(a * c - b) single precision
 *
 * Double precision arguments are used to prevent the compiler from
 * issuing frsp instructions upstream.
 */
static inline float __fnmsubs (double a, double c, double b) __attribute__((always_inline));
static inline float 
__fnmsubs (double  a, double c, double b)
{
  float result;
  __asm__ ("fnmsubs %0, %1, %2, %3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (a), "f" (c), "f" (b));
  return result;
}

/*
 * __fres - Floating Reciprocal Estimate
 *
 * Produces a double precision result with 5 bits of accuracy.
 * Note: not valid on the PowerPC 601.
 *
 * ??? CW: float __fres(float)
 */
static inline float __fres (float val) __attribute__((always_inline));
static inline float 
__fres (float val)
{
  float estimate;
  __asm__ ("fres %0,%1" 
           /* outputs:  */ : "=f" (estimate) 
           /* inputs:   */ : "f" (val));
  return estimate;
}

/*
 * __frsp - Floating Round to Single-Precision
 */
static inline float __frsp (double d) __attribute__((always_inline));
static inline float 
__frsp (double d)
{
  float result;
  __asm__ ("frsp %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (d));
  return result;
}

/*
 * __frsqrte - Floating Reciprocal Square Root Estimate
 *
 * Note: not valid on the PowerPC 601.
 */
static inline double __frsqrte (double val) __attribute__((always_inline));
static inline double 
__frsqrte (double val)
{
  double estimate;

  __asm__ ("frsqrte %0,%1" 
           /* outputs:  */ : "=f" (estimate) 
           /* inputs:   */ : "f" (val));
  return estimate;
}

/*
 * __frsqrtes - Floating Reciprocal Square Root Estimate Single
 */
static inline float __frsqrtes (double f) __attribute__((always_inline));
static inline float 
__frsqrtes (double f)
{
  float result;
  __asm__ ("frsqrte %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (f));
  return result;
}

/*
 * __fsel - Floating Select
 *
 *   if (test >= 0) return a; else return b;
 *
 * Note: not valid on the PowerPC 601.
 */
static inline double __fsel (double test, double a, double b) __attribute__((always_inline));
static inline double 
__fsel (double test, double a, double b)
{
  double result;
  __asm__ ("fsel %0,%1,%2,%3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (test), "f" (a), "f" (b));
  return result;
}

/*
 * __fsels - Floating Select (Single-Precision variant)
 *
 * An artificial single precision variant of fsel. This produces the 
 * same results as fsel, but is useful because the result is cast as 
 * a float, discouraging the compiler from issuing a frsp instruction 
 * afterward.
 */
static inline float __fsels (double test, double a, double b) __attribute__((always_inline));
static inline float 
__fsels (double test, double a, double b)
{
  float result;
  __asm__ ("fsel %0,%1,%2,%3" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (test), "f" (a), "f" (b));
  return result;
}

/*
 * __fsqrt - Floating-Point Square Root (Double-Precision)
 *
 * WARNING: Illegal instruction for PowerPC 603, 604, 750, 7400, 7410, 
 * 7450, and 7455
 */
static inline double __fsqrt (double b) __attribute__((always_inline));
static inline double
__fsqrt(double d)
{
  double result;
  __asm__ ("fsqrt %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (d));
  return result;
}

/*
 * __fsqrts - Floating-Point Square Root Single-Precision
 *
 * WARNING: Illegal instruction for PowerPC 603, 604, 750, 7400, 7410, 
 * 7450, and 7455
 */
static inline float __fsqrts (float f) __attribute__((always_inline));
static inline float 
__fsqrts (float f)
{
  float result;
  __asm__ ("fsqrts %0, %1" 
           /* outputs:  */ : "=f" (result) 
           /* inputs:   */ : "f" (f));
  return result;
}

/*
 * __mulhw - Multiply High Word
 */
static inline int __mulhw (int a, int b) __attribute__((always_inline));
static inline int 
__mulhw (int a, int b)
{
  long result;
  __asm__ ("mulhw %0, %1, %2" 
           /* outputs:  */ : "=r" (result) 
           /* inputs:   */ : "r" (a), "r"(b));
  return result;
}

/*
 * __mulhwu - Multiply High Word Unsigned
 */
static inline unsigned int __mulhwu (unsigned int a, unsigned int b) __attribute__((always_inline));
static inline unsigned int 
__mulhwu (unsigned int a, unsigned int b)
{
  unsigned long result;
  __asm__ ("mulhwu %0, %1, %2" 
           /* outputs:  */ : "=r" (result) 
           /* inputs:   */ : "r" (a), "r"(b));
  return result;
}

/*
 * __stfiwx - Store Floating-Point as Integer Word Indexed
 *
 *   void x(int, void *, int);
 */
#define __stfiwx(value, base, index)    \
  __asm__ ("stfiwx %0, %1, %2" : /*no result*/  \
           : "f" (value), "b%" (index), "r" (base) : "memory")


/*******************************************************************
 *                     Miscellaneous Functions                     *
 *******************************************************************/

/*
 * __icbi - Instruction Cache Block Invalidate
 *
 *   void __icbi(void *, int);
 */
#define __icbi(base, index)    \
  __asm__ ("icbi %0, %1" : /*no result*/ : "b%" (index), "r" (base) : "memory")

/*
 * __mffs - Move from FPSCR
 */
static inline double __mffs (void) __attribute__((always_inline));
static inline double 
__mffs (void)
{
  double result;
  __asm__ volatile ("mffs %0" 
                    /* outputs:  */ : "=f" (result));
  return result;
}

/*
 * __mfspr - Move from Special Purpose Register
 *
 *   int __mfspr(int);
 */
#define __mfspr(spr)    \
  ({ long mfsprResult; \
     __asm__ volatile ("mfspr %0, %1" : "=r" (mfsprResult) : "n" (spr)); \
     /*return*/ mfsprResult; })

/*
 * __mtfsf - Move to SPSCR Fields
 *
 *   void __mtfsf(int, int);
 */
#define __mtfsf(mask, newValue) \
  __asm__ volatile ("mtfsf %0, %1" : : "n" (mask), "f" (newValue))

/*
 * __mtspr - Move to Special Purpose Register
 *
 *   __mtspr x(int, int);
 */
#define __mtspr(spr, value)     \
  __asm__ volatile ("mtspr %0, %1" : : "n" (spr), "r" (value))

/*
 * __OSReadSwapSInt16
 *
 * lhbrx for signed shorts.  This will do the required sign 
 * extension after load and byteswap.
 */
static inline signed short __OSReadSwapSInt16 (signed short *base, int index) __attribute__((always_inline));
static inline signed short 
__OSReadSwapSInt16 (signed short *base, int index)
{
  signed long result;
  __asm__ volatile ("lhbrx %0, %1, %2" 
		    /* outputs:  */ : "=r" (result) 
		    /* inputs:   */ : "b%" (index), "r" (base) 
		    /* clobbers: */ : "memory");
  return result;
}

/*
 * __OSReadSwapUInt16
 */
static inline unsigned short __OSReadSwapUInt16 (volatile void *base, int inex) __attribute__((always_inline));
static inline unsigned short 
__OSReadSwapUInt16 (volatile void *base, int index)
{
  unsigned long result;
  __asm__ volatile ("lhbrx %0, %1, %2"
		    /* outputs:  */ : "=r" (result)
		    /* inputs:   */ : "b" (index), "r" (base)
		    /* clobbers: */ : "memory");
  return result;
}

/*
 * __astrcmp - assembly strcmp
 */
static inline int astrcmp (const char *in_s1, const char *in_s2) __attribute__((always_inline));
static inline int 
astrcmp (const char *in_s1, const char *in_s2)
{
  int result, temp;
  register const char *s1 = in_s1 - 1;
  register const char *s2 = in_s2 - 1;

  __asm__ ("1:lbzu %0,1(%1)\n"
           "\tcmpwi cr1,%0,0\n"
           "\tlbzu %3,1(%2)\n"
           "\tsubf. %0,%3,%0\n"
           "\tbeq- cr1,2f\n"
           "\tbeq+ 1b\n2:"
            /* outputs: */  : "=&r" (result), "+b" (s1), "+b" (s2), "=r" (temp)
            /* inputs: */   : 
            /* clobbers: */ : "cr0", "cr1", "memory");

  return result;

  /*
   * "=&r" (result)     means: 'result' is written on (the '='), it's any GP
   *                    register (the 'r'), and it must not be the same as
   *                    any of the input registers (the '&').
   * "+b" (s1)          means: 's1' is read from and written to (the '+'),
   *                    and it must be a base GP register (i.e., not R0.)
   * "=r" (temp)        means: 'temp' is any GP reg and it's only written to.
   * 
   * "memory"           in the 'clobbers' section means that gcc will make
   *                    sure that anything that should be in memory IS there
   *                    before calling this routine.
   */
}

#endif  /* defined(__ppc__) && ! defined(__MWERKS__) */

#endif /* _PPC_INTRINSICS_H_ */
