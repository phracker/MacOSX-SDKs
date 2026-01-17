/*
     File:       vecLib/vfp.h
 
     Contains:   MathLib style functions for vectors
 
     Version:    vecLib-325.4
 
     Copyright:  © 1999-2011 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VFP__
#define __VFP__

#include <stdint.h>
/*
#ifndef __VECLIBTYPES__
#include <vecLib/vecLibTypes.h>
#endif

*/
#include "vecLibTypes.h"

#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)
#if defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE__
/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    A collection of numerical functions designed to facilitate a wide         
    range of numerical programming for the Altivec Programming model.       
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/

/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Computational Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vdivf        C = A Ö B                                                          
    vsqrtf       B = ÃA                                                         
    vrsqrtf      B = 1/ÃA                                                       
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vceilf() -- vector ceilf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vceilf( vFloat A ) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*
 *  vfloorf()  -- vector floorf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vfloorf( vFloat A ) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*
 *  vintf()  -- vector truncf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vintf( vFloat A ) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*
 *  vnintf()  -- vector rintf()   (round-to-nearest-even rounding mode)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vnintf( vFloat A ) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vrecf() -- vector reciprocal  1.0f / v
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vrecf( vFloat A ) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vdivf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vdivf(vFloat A, vFloat B) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vsqrtf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vsqrtf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vrsqrtf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vrsqrtf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Exponential Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vexpf       B = Exp(A)                                                      
    vexpm1f     ExpM1(x) = Exp(x) - 1.  But, for small enough arguments,        
                ExpM1(x) is expected to be more accurate than Exp(x) - 1.       
    vlogf       B = Log(A)                                                      
    vlog10f     B = Log10(A)                                                      
    vlog1pf     Log1P = Log(1 + x). But, for small enough arguments,            
                Log1P is expected to be more accurate than Log(1 + x).          
    vlogbf      Extracts the exponent of its argument, as a signed integral     
                value. A subnormal argument is treated as though it were first  
                normalized. Thus:                                               
                1   <=   x * 2^(-logb(x))   <   2                           
    vscalbf     Computes x * 2^n efficently.  This is not normally done by      
                computing 2^n explicitly.                                       
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vexpf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vexpf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vexpm1f()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vexpm1f(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vlogf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vlogf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 *  vlogf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vlog10f(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vlog1pf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vlog1pf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vlogbf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vlogbf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vscalbf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vscalbf(vFloat X, vSInt32 n) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Auxiliary Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vfabf           Absolute value is part of the programming model, however    
                    completeness it is included in the library.                 
    vcopysignf      Produces a value with the magnitude of its first argument   
                    and sign of its second argument.  NOTE: the order of the    
                    arguments matches the recommendation of the IEEE 754        
                    floating point standard,  which is opposite from the SANE   
                    copysign function.                                          
    vnextafterf     Computes the next representable value after 'x' in the      
                    direction of 'y'.  if x == y, then y is returned.           
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vfabf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vfabf(vFloat v) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vcopysignf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vcopysignf(vFloat arg2, vFloat arg1) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vnextafterf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vnextafterf(vFloat x, vFloat y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Inquiry Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vclassifyf      Returns one of the FP_Å values.                             
    vsignbitf       Non-zero if and only if the sign of the argument x is       
                    negative.  This includes, NaNs, infinities and zeros.       
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vclassifyf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32  vclassifyf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vsignbitf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32  vsignbitf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Transcendental Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vsinf           B = Sin(A). 
    vcosf           B = Cos(A).                                                 
    vtanf           B = Tan(A).                                                 
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vsinf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vsinf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 *  vsincosf()   -- simultaneous calculation of sine and cosine of input. (Cheaper than doing these separately.)
 *                  sine_result must be a valid pointer and must be at least 16 byte aligned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vsincosf( vFloat arg, vFloat *sine_result) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vcosf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vcosf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vtanf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vtanf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Trigonometric Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vasinf      result is in [-pi/2,pi/2].                                      
    vacosf      result is in [0,pi].                                            
    vatanf      result is in [-pi/2,pi/2].                                      
    vatan2f     Computes the arc tangent of y/x in [-pi,pi] using the sign of   
                both arguments to determine the quadrant of the computed value. 
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vasinf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vasinf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vacosf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vacosf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vatanf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vatanf(vFloat arg) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vatan2f()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vatan2f(vFloat arg1, vFloat arg2) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Hyperbolic Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vsinhf      Sine Hyperbolic.                                                
    vcoshf      Cosine Hyperbolic.                                              
    vtanhf      Tangent Hyperbolic.                                             
    vasinhf     Arcsine Hyperbolic.
    vacoshf     Arccosine Hyperbolic.
    vatanhf     Atctangent Hyperbolic.
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vsinhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vsinhf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vcoshf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vcoshf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vtanhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vtanhf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vasinhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vasinhf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vacoshf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vacoshf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vatanhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vatanhf(vFloat X) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Remainder Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vfmodf          B = X mod Y.                                                
    vremainderf     IEEE 754 floating point standard for remainder.             
    vremquof        SANE remainder.  It stores into 'quotient' the 7 low-order  
                    bits of the integer quotient x/y, such that:                
                    -127 <= quotient <= 127.                                
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vfmodf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vfmodf(vFloat X, vFloat Y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vremainderf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vremainderf(vFloat X, vFloat Y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vremquof()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vremquof(vFloat X, vFloat Y, vUInt32 *QUO) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Power Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vipowf          Returns x raised to the integer power of y.                 
    vpowf           Returns x raised to the power of y.  Result is more         
                    accurate than using exp(log(x)*y).                          
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vipowf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vipowf(vFloat X, vSInt32 Y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vpowf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vpowf(vFloat X, vFloat Y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Useful                                                                      
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vtablelookup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32  vtablelookup(vSInt32 Index_Vect, uint32_t *Table) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


#endif	// defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE__

#endif  /* defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__) */


#ifdef __cplusplus
}
#endif

#endif /* __VFP__ */

