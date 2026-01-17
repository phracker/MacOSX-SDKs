/*
     File:       vecLib/vectorOps.h
 
     Contains:   vector and matrix functions for AltiVec
 
     Version:    vecLib-138.1~9
 
     Copyright:  © 1999-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECTOROPS__
#define __VECTOROPS__

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
#ifdef __VEC__
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern long 
vIsamax(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern long 
vIsamin(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern long 
vIsmax(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern long 
vIsmin(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSasum(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSsum(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/**************************************************
  vSaxpy multiplies a vector x, by a scalar and 
  adds it to a vector y and stores the result in y
     n      number of floats in x (n is a       
            multiple of 4)                      
     alpha  scalar number is single-precision   
            floating-point                      
     x      array of vector floats              
     y      array of vector floats, where the   
            the result is stored                
**************************************************/
/*
 *  vSaxpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSaxpy(
  long                 n,
  float                alpha,
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
  vScopy copies a vector x, into another vector y.  
     n      mumber of floats in x and y (n is a 
            multiple of 4)                      
     x      array of vector floats              
     y      array of vector floats              
*************************************************************/
/*
 *  vScopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vScopy(
  long                 n,
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************************************************
 vSdot finds the dot product of two vectors.      
    n       mumber of floats in x and y (n is a 
                multiple of 4)                      
    x       array of vector floats              
    y       array of vector floats              
*************************************************************/
/*
 *  vSdot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSdot(
  long                 n,
  const vector float   x[],
  const vector float   y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************************************************
 vSnaxpy computes saxpy "n" times.               
   n            number of saxpyV computations to be 
                performed and the number of elements
                in vector A (n is a multiple of 4)  
   m            number of floats in each vector x(i)
                or y(i)                             
   a            array of vector floats containing   
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSnaxpy(
  long                 n,
  long                 m,
  const vector float   a[],
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSndot(
  long                 n,
  long                 m,
  float                s[],
  long                 isw,
  const vector float   x[],
  const vector float   y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSnrm2 finds the Euclidean length of a vector   
 with scaling of input to avoid destructive      
 underflow and overflow.                         
    count   length of vector (multiple of 4)    
    x       array of vector floats              
*************************************************************/
/*
 *  vSnrm2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSnrm2(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSnorm2 finds the Euclidean length of a vector  
 with no scaling of input.                       
    count   length of vector (multiple of 4)    
    x       array of vector floats              
*************************************************************/
/*
 *  vSnorm2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern float 
vSnorm2(
  long                 count,
  const vector float   x[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSrot applies a plane rotation.                 
    n       number of points to be rotated, also
                number of elements in x and y (n is 
                a multiple of 4)                    
    x       array of vector floats. It is a     
                vector of length n, containing x(i) 
                coordinates of points to be rotated 
    y       array of vector floats. It is a     
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSrot(
  long           n,
  vector float   x[],
  vector float   y[],
  float          c,
  float          s)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSscal multiplies a vector x, by a scalar and   
 stores the result in the vector x.              
    n       number of floats in x (n is a       
                multiple of 4)                      
    alpha   scalar number is single-precision   
                floating-point                      
    x       array of vector floats              
*************************************************************/
/*
 *  vSscal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSscal(
  long           n,
  float          alpha,
  vector float   x[])                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSswap interchanges the elements of vectors x   
 and y                                           
    n       number of floats in x and y (n is a 
                multiple of 4)                      
    x       array of vector floats              
    y       array of vector floats              
*************************************************************/
/*
 *  vSswap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSswap(
  long           n,
  vector float   x[],
  vector float   y[])                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSyax multiplies a vector x, by a scalar and    
 stores the result in a vector y.                
    n       number of floats in x (n is a       
                multiple of 4)                      
    alpha   scalar number is single-precision   
                floating-point                      
    x       array of vector floats              
    y       array of vector floats              
*************************************************************/
/*
 *  vSyax()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSyax(
  long                 n,
  float                alpha,
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSzaxpy multiplies a vector x, by a scalar and  
 adds it to a vector y and stores the result in  
 vector Z.                                       
    n       number of floats in x (n is a       
                multiple of 4)                      
    alpha   scalar number is single-precision   
                floating-point                      
    x       array of vector floats              
    y       array of vector floats              
    Z       array of vector floats, where the   
                is stored                           
*************************************************************/
/*
 *  vSzaxpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSzaxpy(
  long                 n,
  float                alpha,
  const vector float   x[],
  const vector float   yY[],
  vector float         z[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*
-------------------------------------------------------------------------------------
     Level 2
-------------------------------------------------------------------------------------
*/
/*************************************************************
 vSgemv multiplies an array of vector floats y by
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
                are vector floats                   
    x       is an array of vector floats        
    beta        is a scaling constant               
    y       is an array of vector floats        
*************************************************************/
/*
 *  vSgemv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemv(
  char                 forma,
  long                 m,
  long                 n,
  float                alpha,
  const vector float   a[],
  const vector float   x[],
  float                beta,
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*************************************************************
 vSgemx adds an array of vector floats y to the  
 product of an scalar alpha by a mtrix A         
 multiplied by an array of vector floats x. It   
 then stores the result in the vector y.         
    m       number of rows in matrix A and      
                the length of vector y. m is a      
            multiple of 4                       
    n       number of columns in matrix A and   
                the length of vector x. m is a      
            multiple of 4                       
    alpha   is a scaling constant               
    a       is an m by n matrix. Its elements   
                are vector floats                   
    x       is an array of vector floats        
    y       is an array of vector floats        
*************************************************************/
/*
 *  vSgemx()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemx(
  long                 m,
  long                 n,
  float                alpha,
  const vector float   a[],
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
                are vector floats                   
    x       is an array of vector floats        
    y       is an array of vector floats        
*************************************************************/
/*
 *  vSgemtx()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemtx(
  long                 m,
  long                 n,
  float                alpha,
  const vector float   a[],
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
                if forma='n', A is used in  the     
                computation, and A has m rows and   
                n columns                           
                if forma='T', A(T) is used in the   
                computation, and A has n rows and   
                m columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='n', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='n', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='n', b is used in  the     
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgeadd(
  long                 height,
  long                 width,
  const vector float   a[],
  char                 forma,
  const vector float   b[],
  char                 formb,
  vector float         c[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSgesub performs matrix subtraction for general 
 matrices or their transposes.                   
    height  height of the matrix (it is multiple
                of 4)                               
    width   width of the matrix (it is multiple 
                of 4)                               
    A       matrix A, and depending on forma:   
                if forma='n', A is used in  the     
                computation, and A has m rows and   
                n columns                           
                if forma='T', A(T) is used in the   
                computation, and A has n rows and   
                m columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='n', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='n', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='n', b is used in  the     
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgesub(
  long                 height,
  long                 width,
  const vector float   a[],
  char                 forma,
  const vector float   b[],
  char                 formb,
  vector float         c[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
                if forma='n', A is used in  the     
                computation, and A has l rows and   
                m columns                           
                if forma='T', A(T) is used in the   
                computation, and A has m rows and   
                l columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='n', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='n', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='n', b is used in  the     
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemul(
  long                 l,
  long                 m,
  long                 n,
  const vector float   a[],
  char                 forma,
  const vector float   b[],
  char                 formb,
  vector float         matrix[])                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************************************************
 vSgemm performs combined matrix multiplication  
 and addition for general matrices or their transposes.                                     
    l       number of rows in matrix c (it is   
                multiple of 4)                      
    m       has the following meaning:          
                if forma='n', it is the number of   
                columns in matrix A                 
                if forma='T', it is the number of   
                rows in matrix A. In addition       
                if formb='n', it is the number of   
                rows in matrix b                    
                if formb='T', it is the number of   
                columns in matrix b                 
    n       columns in  matrix c                
    A       matrix A, and depending on forma:   
                if forma='n', A is used in  the     
                computation, and A has l rows and   
                m columns                           
                if forma='T', A(T) is used in the   
                computation, and A has m rows and   
                l columns                           
    forma   indicates the form of matrix A to   
                use in the computation, where:      
                if forma='n', A is used in  the     
                computation                         
                if forma='T', A(T) is used in  the  
                computation                         
    b       matrix b, and depending on formb:   
                if formb='n', b is used in  the     
                computation, and b has m rows and   
                n columns                           
                if formb='T', b(T) is used in the   
                computation, and b has n rows and   
                m columns                           
    formb   indicates the form of matrix b to   
                use in the computation, where:      
                if forma='n', b is used in  the     
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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgemm(
  long                 l,
  long                 m,
  long                 n,
  const vector float   a[],
  char                 forma,
  const vector float   b[],
  char                 formb,
  vector float         c[],
  float                alpha,
  float                beta,
  vector float         matrix[])                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgetmi(
  long           size,
  vector float   x[])                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*************************************************************
 vSgetmo performs general matrix transpose (out-of-place).                                      
    height  is the height of the matrix         
    width   is the width of the matrix          
    x       array of vector floats              
    y       array of vector floats              
*************************************************************/
/*
 *  vSgetmo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgetmo(
  long                 height,
  long                 width,
  const vector float   x[],
  vector float         y[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*************************************************************
 vSgevv is a new function. It takes matrix A and 
 multiplies it by matrix b and puts the result in
 matrix m.                                       
    l       is the height of the matrix         
    n       is the width of the matrix          
    A       array of vector floats of at least  
                l *  m in length                                 
    b       array of vector floats of at least  
                m * n in length                                 
    m       array of vector floats, containing  
                the results of multiplication. It   
                is m * n in size                                
*************************************************************/
/*
 *  vSgevv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vSgevv(
  long                 l,
  long                 n,
  const vector float   a[],
  const vector float   b[],
  vector float         m[])                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif  /* defined(__VEC__) */


#ifdef __cplusplus
}
#endif

#endif /* __VECTOROPS__ */

