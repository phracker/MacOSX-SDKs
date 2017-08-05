/*
     File:       vecLib/vectorOps.h
 
     Contains:   vector and matrix functions for AltiVec
 
     Version:    vecLib-622.0
 
     Copyright:  Copyright (c) 1999-2017 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECTOROPS__
#define __VECTOROPS__

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


#if !defined __has_feature
    #define __has_feature(f)    0
#endif
#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull begin")
#else
    #define __nullable
    #define __nonnull
#endif


/*
-------------------------------------------------------------------------------------
                                                                                                                                                                  
 This section is a collection of Basic Linear Algebra Subprograms (BLAS), which   
 use AltiVec technology for their implementations. The functions are grouped into 
 three categories (called levels), as follows:                                    
                                                                                  
    1) Vector-scalar linear algebra subprograms                                   
    2) Matrix-vector linear algebra subprograms                                   
    3) Matrix operations                                                          
                                                                                  
 Following is a list of subprograms and a short description of each one.          
-------------------------------------------------------------------------------------
*/
#if defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE__
/*
-------------------------------------------------------------------------------------
     Level 1
-------------------------------------------------------------------------------------
*/
/**************************************************
  vIsamax finds the position of the first vector
  element having the largest magnitude.         
     count  length of vector x (count is a      
            multiple of 4)                      
     x      array of floats                     
**************************************************/
/*
 *  vIsamax()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern int32_t 
vIsamax(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/**************************************************
  vIsamin finds the position of the first vector
  element having minimum absolute value.        
     count  length of vector x (count is a      
            multiple of 4)                      
     x      array of floats                     
**************************************************/
/*
 *  vIsamin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern int32_t 
vIsamin(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/**************************************************
  vIsmax finds the position of the first vector 
  element having maximum value.                 
     count  length of vector x (count is a      
            multiple of 4)                      
     x      array of floats                     
**************************************************/
/*
 *  vIsmax()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern int32_t 
vIsmax(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/**************************************************
  vIsmin finds the position of the first vector 
  element having minimum value.                 
     count  length of vector x (count is a      
            multiple of 4)                      
     x      array of floats                     
**************************************************/
/*
 *  vIsmin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern int32_t 
vIsmin(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/**************************************************
  vSasum finds the sum of the magnitudes of the 
  elements in a vector.                         
     count  length of vector x (count is a      
            multiple of 4)                      
     x      array of floats                     
**************************************************/
/*
 *  vSasum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSasum(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/**************************************************
  vSsum is the vector version of sasum but without  
  the absolute value. It takes the value of each
  element of the array and adds them together.      
            multiple of 4)                      
     x      array of floats                     
**************************************************/
/*
 *  vSsum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSsum(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/**************************************************
  vSaxpy multiplies a vector x, by a scalar and 
  adds it to a vector y and stores the result in y
     n      number of floats in x (n is a       
            multiple of 4)                      
     alpha  scalar number is single-precision   
            floating-point                      
     x      array of vFloats              
     y      array of vFloats, where the   
            the result is stored                
**************************************************/
/*
 *  vSaxpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSaxpy(
  int32_t        n,
  float          alpha,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
  vScopy copies a vector x, into another vector y.  
     n      mumber of floats in x and y (n is a 
            multiple of 4)                      
     x      array of vFloats              
     y      array of vFloats              
*************************************************************/
/*
 *  vScopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vScopy(
  int32_t        n,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*************************************************************
 vSdot finds the dot product of two vectors.      
    n       mumber of floats in x and y (n is a 
                multiple of 4)                      
    x       array of vFloats              
    y       array of vFloats              
*************************************************************/
/*
 *  vSdot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSdot(
  int32_t        n,
  const vFloat   *x,
  const vFloat   *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*************************************************************
 vSnaxpy computes saxpy "n" times.               
   n            number of saxpyV computations to be 
                performed and the number of elements
                in vector A (n is a multiple of 4)  
   m            number of floats in each vector x(i)
                or y(i)                             
   a            array of vFloats containing   
                scalars a(i)                        
   x            matrix containing arrays of vector- 
                floats x(i)                         
   y            matrix containing vectors y(i)      
*************************************************************/
/*
 *  vSnaxpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSnaxpy(
  int32_t        n,
  int32_t        m,
  const vFloat   *a,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSndot computes the dot products "n" times.     
    n       number of dot product computations  
            to be performed and the number of   
                elements in vector S                
    m       number of elements in vectors x(i)  
                and y(i) for each dot product       
                computation (m is a multiple of 4)  
    s       array of floats. Depending on the   
                value of "isw" different computations/
                are performed and the results are   
                stored in the array S               
    isw     indicates the type of computation   
                to perform.                         
                if isw=1, S(i) <--   x(i)   y(i)    
                if isw=2, S(i) <-- - x(i)   y(i)    
                if isw=3, S(i) <-- S(i) + x(i)   y(i)/
                if isw=4, S(i) <-- S(i) - x(i)   y(i)/
    x       matrix containing arrays x(i)       
    y       matrix containing arrays y(i)       
*************************************************************/
/*
 *  vSndot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSndot(
  int32_t        n,
  int32_t        m,
  float          *s,
  int32_t        isw,
  const vFloat   *x,
  const vFloat   *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSnrm2 finds the Euclidean length of a vector   
 with scaling of input to avoid destructive      
 underflow and overflow.                         
    count   length of vector (multiple of 4)    
    x       array of vFloats              
*************************************************************/
/*
 *  vSnrm2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSnrm2(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSnorm2 finds the Euclidean length of a vector  
 with no scaling of input.                       
    count   length of vector (multiple of 4)    
    x       array of vFloats              
*************************************************************/
/*
 *  vSnorm2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSnorm2(
  int32_t        count,
  const vFloat   *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSrot applies a plane rotation.                 
    n       number of points to be rotated, also
                number of elements in x and y (n is 
                a multiple of 4)                    
    x       array of vFloats. It is a     
                vector of length n, containing x(i) 
                coordinates of points to be rotated 
    y       array of vFloats. It is a     
                vector of length n, containing y(i) 
                coordinates of points to be rotated 
    c       cosine of angle of rotation         
    s       sine of angle of rotation           
*************************************************************/
/*
 *  vSrot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSrot(
  int32_t   n,
  vFloat    *x,
  vFloat    *y,
  float     c,
  float     s) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSscal multiplies a vector x, by a scalar and   
 stores the result in the vector x.              
    n       number of floats in x (n is a       
                multiple of 4)                      
    alpha   scalar number is single-precision   
                floating-point                      
    x       array of vFloats              
*************************************************************/
/*
 *  vSscal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSscal(
  int32_t   n,
  float     alpha,
  vFloat    *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSswap interchanges the elements of vectors x   
 and y                                           
    n       number of floats in x and y (n is a 
                multiple of 4)                      
    x       array of vFloats              
    y       array of vFloats              
*************************************************************/
/*
 *  vSswap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSswap(
  int32_t   n,
  vFloat    *x,
  vFloat    *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSyax multiplies a vector x, by a scalar and    
 stores the result in a vector y.                
    n       number of floats in x (n is a       
                multiple of 4)                      
    alpha   scalar number is single-precision   
                floating-point                      
    x       array of vFloats              
    y       array of vFloats              
*************************************************************/
/*
 *  vSyax()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSyax(
  int32_t        n,
  float          alpha,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSzaxpy multiplies a vector x, by a scalar and  
 adds it to a vector y and stores the result in  
 vector Z.                                       
    n       number of floats in x (n is a       
                multiple of 4)                      
    alpha   scalar number is single-precision   
                floating-point                      
    x       array of vFloats              
    y       array of vFloats              
    Z       array of vFloats, where the   
                is stored                           
*************************************************************/
/*
 *  vSzaxpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSzaxpy(
  int32_t        n,
  float          alpha,
  const vFloat   *x,
  const vFloat   *y,
  vFloat         *z) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);





/*
-------------------------------------------------------------------------------------
     Level 2
-------------------------------------------------------------------------------------
*/
/*************************************************************
 vSgemv multiplies an array of vFloats y by
 a  scalar beta, and takes the result and adds it
 to the product of a scalar alpha multiplied by  
 a matrix A multiplied by a vector x. The above  
 result is stored in array y. Futhermore, the    
 same function also performs the above calculation/
 with the transpose of matrix A, instead of      
 matrix A. In this function argument "forma"     
 distinguishes between the above two cases.      
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                If forma = "n", Matrix A is used    
                If forma = "T", Transpose of Matrix 
                 A is used                          
    m       number of rows in matrix A and      
                depending on value of forma         
                if forma = "n", it is the length of 
                 vector y                           
                if forma = "T", it is the length of 
                 vector x. m is a multiple of 4     
    n       number of columns in matrix A and   
                depending on value of forma         
                if forma = "n", it is the length of 
                 vector x                           
                if forma = "T", it is the length of 
                 vector y. m is a multiple of 4     
    alpha   is a scaling constant               
    A       is an m by n matrix. Its elements   
                are vFloats                   
    x       is an array of vFloats        
    beta        is a scaling constant               
    y       is an array of vFloats        
*************************************************************/
/*
 *  vSgemv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemv(
  char           forma,
  int32_t        m,
  int32_t        n,
  float          alpha,
  const vFloat   *a,
  const vFloat   *x,
  float          beta,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);





/*************************************************************
 vSgemx adds an array of vFloats y to the  
 product of an scalar alpha by a mtrix A         
 multiplied by an array of vFloats x. It   
 then stores the result in the vector y.         
    m       number of rows in matrix A and      
                the length of vector y. m is a      
            multiple of 4                       
    n       number of columns in matrix A and   
                the length of vector x. m is a      
            multiple of 4                       
    alpha   is a scaling constant               
    a       is an m by n matrix. Its elements   
                are vFloats                   
    x       is an array of vFloats        
    y       is an array of vFloats        
*************************************************************/
/*
 *  vSgemx()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemx(
  int32_t        m,
  int32_t        n,
  float          alpha,
  const vFloat   *a,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSgemtx takes the transpose of a mtrix A and    
 multiplies it by an array x. It then multiplies 
 the result by a scalar alpha. Finally adds the  
 above result to an array y and stores the result
 in array y.                                     
    m       number of rows in matrix A and      
                the length of vector x. m is a      
            multiple of 4                       
    n       number of columns in matrix A and   
                the length of vector y. m is a      
            multiple of 4                       
    alpha   is a scaling constant               
    a       is an m by n matrix. Its elements   
                are vFloats                   
    x       is an array of vFloats        
    y       is an array of vFloats        
*************************************************************/
/*
 *  vSgemtx()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemtx(
  int32_t        m,
  int32_t        n,
  float          alpha,
  const vFloat   *a,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
-------------------------------------------------------------------------------------
     Level 3
-------------------------------------------------------------------------------------
*/


/*************************************************************
 vSgeadd performs matrix addition for general    
 matrices or their transposes.                   
    height  height of the matrix (it is multiple
                of 4)                               
    width   width of the matrix (it is multiple 
                of 4)                               
    A       matrix A, and depending on forma:   
                if forma='N', A is used in  the     
                computation, and A has m rows and   
                n columns                           
                if forma='T', A(T) is used in the   
                computation, and A has n rows and   
                m columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='N', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='N', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='N', b is used in  the     
                computation                         
                if forma='T', b(T) is used in  the  
                computation                         
    c       is an m by n matrix c, containing   
                the reults of the computation       
*************************************************************/
/*
 *  vSgeadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgeadd(
  int32_t        height,
  int32_t        width,
  const vFloat   *a,
  char           forma,
  const vFloat   *b,
  char           formb,
  vFloat         *c) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSgesub performs matrix subtraction for general 
 matrices or their transposes.                   
    height  height of the matrix (it is multiple
                of 4)                               
    width   width of the matrix (it is multiple 
                of 4)                               
    A       matrix A, and depending on forma:   
                if forma='N', A is used in  the     
                computation, and A has m rows and   
                n columns                           
                if forma='T', A(T) is used in the   
                computation, and A has n rows and   
                m columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='N', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='N', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='N', b is used in  the     
                computation                         
                if forma='T', b(T) is used in  the  
                computation                         
    c       is an m by n matrix c, containing   
                the reults of the computation       
*************************************************************/
/*
 *  vSgesub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgesub(
  int32_t        height,
  int32_t        width,
  const vFloat   *a,
  char           forma,
  const vFloat   *b,
  char           formb,
  vFloat         *c) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSgemul performs matrix multiplication for      
 general matrices or their transposes.           
    l       height of the matrix A (it is       
                multiple of 4)                      
    m       width of  matrix A  (it is multiple 
                of 4)                               
    n       width of  matrix b  (it is multiple 
                of 4)                               
    A       matrix A, and depending on forma:   
                if forma='N', A is used in  the     
                computation, and A has l rows and   
                m columns                           
                if forma='T', A(T) is used in the   
                computation, and A has m rows and   
                l columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='N', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='N', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='N', b is used in  the     
                computation                         
                if forma='T', b(T) is used in  the  
                computation                         
    matrix  is the matrix containing the     
                results of the computation           
*************************************************************/
/*
 *  vSgemul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemul(
  int32_t        l,
  int32_t        m,
  int32_t        n,
  const vFloat   *a,
  char           forma,
  const vFloat   *b,
  char           formb,
  vFloat         *matrix) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*************************************************************
 vSgemm performs combined matrix multiplication  
 and addition for general matrices or their transposes.                                     
    l       number of rows in matrix c (it is   
                multiple of 4)                      
    m       has the following meaning:          
                if forma='N', it is the number of   
                columns in matrix A                 
                if forma='T', it is the number of   
                rows in matrix A. In addition       
                if formb='N', it is the number of   
                rows in matrix b                    
                if formb='T', it is the number of   
                columns in matrix b                 
    n       columns in  matrix c                
    A       matrix A, and depending on forma:   
                if forma='N', A is used in  the     
                computation, and A has l rows and   
                m columns                           
                if forma='T', A(T) is used in the   
                computation, and A has m rows and   
                l columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='N', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='N', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='N', b is used in  the     
                computation                         
                if forma='T', b(T) is used in  the  
                computation                         
    alpha   is a scalar                         
    beta        is a scalar                         
    matrix      is the l by n matrix          
*************************************************************/
/*
 *  vSgemm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemm(
  int32_t        l,
  int32_t        m,
  int32_t        n,
  const vFloat   *a,
  char           forma,
  const vFloat   *b,
  char           formb,
  vFloat         *c,
  float          alpha,
  float          beta,
  vFloat         *matrix) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);





/*************************************************************
 vSgetmi performs general matrix transpose (in place).                                         
    size        is the number of rows and columns   
                in matrix x                         
*************************************************************/
/*
 *  vSgetmi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgetmi(
  int32_t   size,
  vFloat    *x) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);





/*************************************************************
 vSgetmo performs general matrix transpose (out-of-place).                                      
    height  is the height of the matrix         
    width   is the width of the matrix          
    x       array of vFloats              
    y       array of vFloats              
*************************************************************/
/*
 *  vSgetmo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgetmo(
  int32_t        height,
  int32_t        width,
  const vFloat   *x,
  vFloat         *y) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);





/*
	vsGevv puts the outer product of vectors A and B into matrix M.

	Input:

		l is the number of elements in A and the number of rows in M.
		n is the number of elements in B and the number of columns in N.
		A is a vector of L floating-point numbers.
		B is a vector of M floating-point numbers.
		M is an array with space for L*N floating-point numbers.

	Output:

		For 0 <= i < l and 0 <= j < n, C[i*n + j] = A[i] * B[j].

	Note:

		In the comments above, array elements are floating-point objects, in
		spite of the fact that the arrays are passed to the routine as pointers
		to vFloat.  For example, if A contains four floating-point numbers, l
		is 4, even though A contains only one vFloat object.

	Availability:

		Mac OS X:        In version 10.0 and later in vecLib.framework.
		CarbonLib:       Not in Carbon, but vecLib is compatible with CarbonLib.
		Non-Carbon CFM:  In vecLib 1.0 and later.
*/
extern void 
vSgevv(
  int32_t        l,
  int32_t        n,
  const vFloat   *A,
  const vFloat   *B,
  vFloat         *M) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


#endif	// defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE__


#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
#endif
 

#ifdef __cplusplus
}
#endif

#endif /* __VECTOROPS__ */
