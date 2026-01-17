/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_LINEAR_SYSTEMS_HEADER__
#define __LA_LINEAR_SYSTEMS_HEADER__

#if __has_feature(assume_nonnull)
////  If assume_nonnull is available, use it and use nullability qualifiers.
_Pragma("clang assume_nonnull begin")
#else
////  Otherwise, neuter the nullability qualifiers.
#define __nullable
#define __nonnull
#endif

/*!
 @abstract
 Solves a system of linear equations
 
 @param matrix_system
 A matrix describing the left-hand side of the system.
 
 @param obj_rhs
 A vector or matrix describing one or more right-hand sides for which the
 equations are to be solved.
 
 @return
 A matrix of the solution(s) of the system of equations.

 @discussion
 If matrix_system represents a matrix A, and obj_rhs represents a vector
 B, la_solve returns a vector X representing a solution to the equation
 AX = B, if such a solution exists.  If obj_rhs represents a matrix, then
 la_solve returns a matrix representing the solution of the same equation.
 
 There are several different cases, and different algorithms are chosen
 depending on the specifics:
 
 If the matrix has a special structure that allows us to solve the system
 without factoring (e.g. if the matrix is diagonal or triangular), we may
 use that structure to compute the solution.
 
 If the matrix is symmetric and all diagonal entries are positive, or if we
 know, either via a hint parameter or by how earlier computations were
 structured, that the matrix is positive definite, we attempt a Cholesky
 factorization.  If this succeeds, it is used to compute the solution via
 forward- and back-substitution.
 
 If the matrix is square, we try to perform Gaussian elimination to construct
 a triangular factorization with pivoting.  If this factorization succeeds,
 we use it to solve the system.  If it fails, the returned object has the
 error status LA_SINGULAR_ERROR.
 
 If the matrix is not square, we return a least-squares solution computed by
 performing a QR factorization of the matrix.
 
 If the number of rows of the matrix does not match the number of rows of
 the right hand side object, the returned object has status 
 LA_DIMENSION_MISMATCH_ERROR.
 
 If the object describing the matrix is not a matrix, or if the right hand
 side is not a matrix or vector, the returned object has status
 LA_INVALID_PARAMETER_ERROR.
 
 If you want to solve the system XA = B, which is less common (but still
 occurs fairly frequently), you may accomplish this by transposing A and B,
 solving, and then transposing the result of the solve.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_solve(la_object_t matrix_system, la_object_t obj_rhs);

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#endif

#endif // __LA_ARITHMETIC_HEADER__
