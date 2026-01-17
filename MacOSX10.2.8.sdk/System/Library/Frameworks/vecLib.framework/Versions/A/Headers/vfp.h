/*
     File:       vecLib/vfp.h
 
     Contains:   MathLib style functions for vectors
 
     Version:    vecLib-138.1~9
 
     Copyright:  © 1999-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VFP__
#define __VFP__

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

/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    A collection of numerical functions designed to facilitate a wide         
    range of numerical programming for the Altivec Programming model.       
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
#ifdef __VEC__
/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Computational Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vdivf        C = A Ö B                                                          
    vsqrtf       B = ÃA                                                         
    vrsqrtf      B = 1/ÃA                                                       
                                                                                
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vdivf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vdivf(vector float A, vector float B)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsqrtf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vsqrtf(vector float X)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vrsqrtf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vrsqrtf(vector float X)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ[ Exponential Functions]ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
                                                                                
    vexpf       B = Exp(A)                                                      
    vexpm1f     ExpM1(x) = Exp(x) - 1.  But, for small enough arguments,        
                ExpM1(x) is expected to be more accurate than Exp(x) - 1.       
    vlogf       B = Log(A)                                                      
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vexpf(vector float X)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vexpm1f()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vexpm1f(vector float X)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vlogf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vlogf(vector float X)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vlog1pf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vlog1pf(vector float X)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vlogbf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vlogbf(vector float X)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vscalbf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vscalbf(vector float X, vector signed int n)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vfabf(vector float v)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vcopysignf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vcopysignf(vector float arg2, vector float arg1)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vnextafterf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vnextafterf(vector float x, vector float y)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int  vclassifyf(vector float arg)      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsignbitf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int  vsignbitf(vector float arg)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vsinf(vector float arg)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vcosf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vcosf(vector float arg)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vtanf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vtanf(vector float arg)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vasinf(vector float arg)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vacosf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vacosf(vector float arg)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vatanf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vatanf(vector float arg)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vatan2f()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vatan2f(vector float arg1, vector float arg2)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vsinhf(vector float X)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vcoshf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vcoshf(vector float X)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vtanhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vtanhf(vector float X)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vasinhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vasinhf(vector float X)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vacoshf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vacoshf(vector float X)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vatanhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vatanhf(vector float X)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vfmodf(vector float X, vector float Y)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vremainderf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vremainderf(vector float X, vector float Y)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vremquof()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vremquof(vector float X, vector float Y, vector unsigned int *QUO)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vipowf(vector float X, vector signed int Y)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vpowf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector float  vpowf(vector float X, vector float Y)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int  vtablelookup(vector signed int Index_Vect, unsigned long *Table)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif  /* defined(__VEC__) */


#ifdef __cplusplus
}
#endif

#endif /* __VFP__ */

