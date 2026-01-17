#ifndef SPARSE_SOLVE_HEADER
#error "Do not include this header directly."
#endif

/*  MARK: Implementation of the option-less public interfaces; simply defer
 *  to the versions with options, using the `_SparseDefaultXXXOptions` objects
 *  defined here.                                                             */
static const SparseSymbolicFactorOptions _SparseDefaultSymbolicFactorOptions = {
  .control = SparseDefaultControl,
  .orderMethod = SparseOrderDefault,
  .order = NULL,
  .ignoreRowsAndColumns = NULL,
  .malloc = malloc,
  .free = free
};
static const SparseNumericFactorOptions _SparseDefaultNumericFactorOptions_Double = {
  .control = SparseDefaultControl,
  .scalingMethod = SparseScalingDefault,
  .scaling = NULL,
  .pivotTolerance = 0.01,                   // Recommended value for difficult matrices in double
  .zeroTolerance = 1e-4 * __DBL_EPSILON__,  // "A few" orders of magnitude below epsilon.
};
static const SparseNumericFactorOptions _SparseDefaultNumericFactorOptions_Float = {
  .control = SparseDefaultControl,
  .scalingMethod = SparseScalingDefault,
  .scaling = NULL,
  .pivotTolerance = 0.1,                    // Recommended value for difficult matrices in float
  .zeroTolerance = 1e-4 * __FLT_EPSILON__,  // "A few" orders of magnitude below epsilon.
};

static inline SPARSE_PUBLIC_INTERFACE
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
                                               SparseMatrixStructure Matrix) {
  return SparseFactor(type, Matrix, _SparseDefaultSymbolicFactorOptions);
}

/*  MARK: Macros and inlines used to implement the public interfaces.         */
#include <stdlib.h>
#include <stdio.h>

#ifndef __has_builtin
# define __has_builtin(_) 0
#endif

#if __has_builtin(__builtin_mul_overflow)
# define sparse_mul_overflow(a, b, res) __builtin_mul_overflow((a), (b), (res))
#else
/*  Workaround if mul_overflow is unavailable.                                */
# define sparse_mul_overflow(a, b, res) (*(res) = (long)(a)*(b), false)
#endif

#if __has_include(<os/log.h>)
# include <os/log.h>
#else
# define os_log_error(_, format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#endif

#ifndef SPARSE_PARAMETER_CHECK
#define SPARSE_PARAMETER_CHECK(condition, result, format, ...)  \
  do {                                                          \
    if (!(condition)) {                                         \
      if (options.reportError) {                                \
        char message[256] = { 0 };                              \
        snprintf(message, 256, format, ##__VA_ARGS__);          \
        options.reportError(message);                           \
      } else {                                                  \
        os_log_error(OS_LOG_DEFAULT, format, ##__VA_ARGS__);    \
        _SparseTrap();                                          \
      }                                                         \
      return result;                                            \
    }                                                           \
  } while (0)
#endif /* SPARSE_PARAMETER_CHECK*/

// Do O(1) validity tests for matrix structure
#ifndef SPARSE_CHECK_VALID_MATRIX_STRUCTURE
#define SPARSE_CHECK_VALID_MATRIX_STRUCTURE(S, result) \
  SPARSE_PARAMETER_CHECK((S).rowCount > 0, result, "%s.rowCount must be > 0, but is %d.\n", #S, (S).rowCount); \
  SPARSE_PARAMETER_CHECK((S).columnCount > 0, result, "%s.columnCount must be > 0, but is %d.\n", #S, (S).rowCount); \
  SPARSE_PARAMETER_CHECK((S).blockSize > 0, result, "%s.blockSize must be > 0, but is %d.]n", #S, (S).blockSize); \
  SPARSE_PARAMETER_CHECK((S).attributes.kind != SparseSymmetric || \
                         (S).rowCount == (S).columnCount, result, \
                         "%s.attributes.kind=SparseSymmetric, but %s.rowCount (%d) != %s.columnCount (%d).\n", \
                         #S, #S, (S).rowCount, #S, (S).columnCount);
#endif /* SPARSE_CHECK_VALID_MATRIX_STRUCTURE */

// Check matrix matches symbolic factor
#ifndef SPARSE_CHECK_MATCH_SYMB_FACTOR
#define SPARSE_CHECK_MATCH_SYMB_FACTOR(A, sf, result) \
  SPARSE_PARAMETER_CHECK((A).structure.rowCount             == (sf).rowCount && \
                         (A).structure.columnCount          == (sf).columnCount && \
                         (A).structure.blockSize            == (sf).blockSize && \
                         (A).structure.attributes.transpose == (sf).attributes.transpose, \
                         result, "%s does not match that used for symbolic factorization stored in %s.\n", \
                         #A, #sf);
#endif /* SPARSE_CHECK_MATCH_SYMB_FACTOR */

// Check symbolic factorization is valid for use
#ifndef SPARSE_CHECK_VALID_SYMBOLIC_FACTOR
#define SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(sf, result, format, ...) \
SPARSE_PARAMETER_CHECK((sf).status == SparseStatusOK && \
                       (sf).factorization, \
                       result, format, ##__VA_ARGS__);
#endif /* SPARSE_CHECK_VALID_SYMBOLIC_FACTOR */

// Check numeric factorization is valid for use
#ifndef SPARSE_CHECK_VALID_NUMERIC_FACTOR
#define SPARSE_CHECK_VALID_NUMERIC_FACTOR(nf, result) \
  SPARSE_PARAMETER_CHECK((nf).symbolicFactorization.status == SparseStatusOK && \
                         (nf).symbolicFactorization.factorization && \
                         (nf).status == SparseStatusOK && \
                         (nf).numericFactorization, \
                         result, \
                         "%s does not hold a completed matrix factorization.\n", #nf);
#endif /* SPARSE_CHECK_VALID_NUMERIC_FACTOR */

// Check if two vectors are consistent with operation Y = (Op) X.
// (Op) is given as an expected xSize and and expected ySize in this case.
#ifndef SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE
#define SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(expectedXSize, expectedYSize, X, Y, result, opName) \
  do { \
    SPARSE_PARAMETER_CHECK((X).columnStride >= (X).rowCount, result, \
      "%s.columnStride (%d) must be at least %s.rowCount (%d).\n", \
      #X, (X).columnStride, #X, (X).rowCount); \
    SPARSE_PARAMETER_CHECK((Y).columnStride >= (Y).rowCount, result, \
      "%s.columnStride (%d) must be at least %s.rowCount (%d).\n", \
      #Y, (Y).columnStride, #Y, (Y).rowCount); \
    int xCount = ((X).attributes.transpose) ? (X).rowCount : (X).columnCount; \
    int yCount = ((Y).attributes.transpose) ? (Y).rowCount : (Y).columnCount; \
    int xSize = ((X).attributes.transpose) ? (X).columnCount : (X).rowCount; \
    int ySize = ((Y).attributes.transpose) ? (Y).columnCount : (Y).rowCount; \
    SPARSE_PARAMETER_CHECK(xCount == yCount, result, \
      "%s (%dx%d) and %s (%dx%d) do not represent the same number of right-hand sides.\n", \
      #X, xSize, xCount, #Y, ySize, yCount); \
    SPARSE_PARAMETER_CHECK(xCount > 0, result, \
      "%s (%dx%d) must represent at least one right-hand side.\n", \
      #X, xSize, xCount); \
    SPARSE_PARAMETER_CHECK(xSize == expectedXSize, result, \
      "%s (size %dx%d) does not match dimensions of %s (%d x %d).\n", \
      #X, xSize, xCount, opName, expectedYSize, expectedXSize); \
    SPARSE_PARAMETER_CHECK(ySize == expectedYSize, result, \
      "%s (size %dx%d) does not match dimensions of %s (%d x %d).\n", \
      #Y, ySize, yCount, opName, expectedYSize, expectedXSize); \
  } while(0)
#endif /* SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE */

// Check if vector is consistent with numeric factor for in-place solve
#ifndef SPARSE_CHECK_CONSISTENT_DS_VEC_IN_PLACE
#define SPARSE_CHECK_CONSISTENT_DS_VEC_IN_PLACE(nf, vec, result) \
  do { \
    int blockSize = (nf).symbolicFactorization.blockSize; \
    int m = (nf).symbolicFactorization.rowCount * blockSize; \
    int n = (nf).symbolicFactorization.columnCount * blockSize; \
    int maxmn = (m>n) ? m : n; \
    SPARSE_PARAMETER_CHECK((vec).count == maxmn, result, \
      "%s.count (%d) is not equal to largest dimension of matrix factorization %s.\n", \
      #vec, (vec).count, #nf); \
  } while(0)
#endif /* SPARSE_CHECK_CONSISTENT_DS_VEC_IN_PLACE */

// Check if matrix is consistent with numeric factor for in-place solve
#ifndef SPARSE_CHECK_CONSISTENT_DS_MAT_IN_PLACE
#define SPARSE_CHECK_CONSISTENT_DS_MAT_IN_PLACE(nf, mat, result) \
  do { \
    SPARSE_PARAMETER_CHECK((mat).columnStride >= (mat).rowCount, result, \
                           "%s.columnStride (%d) must be at least %s.rowCount (%d).\n", \
                           #mat, (mat).columnStride, #mat, (mat).rowCount); \
    int matSize  = ((mat).attributes.transpose) ? (mat).columnCount : (mat).rowCount; \
    int matCount = ((mat).attributes.transpose) ? (mat).rowCount : (mat).columnCount; \
    SPARSE_PARAMETER_CHECK(matCount > 0, result, \
                           "%s (%dx%d) must represent at least one right-hand side.\n", \
                           #mat, matSize, matCount); \
    int blockSize = (nf).symbolicFactorization.blockSize; \
    int m = (nf).symbolicFactorization.rowCount * blockSize; \
    int n = (nf).symbolicFactorization.columnCount * blockSize; \
    int maxmn = (m>n) ? m : n; \
    SPARSE_PARAMETER_CHECK(matSize == maxmn, result, \
      "%s (%dx%d) is not consistent with largest dimension of matrix factorization %s (%d).\n", \
      #mat, matSize, matCount, #nf, maxmn); \
  } while(0)
#endif /* SPARSE_CHECK_CONSISTENT_DS_MAT_IN_PLACE */

// Check if vectors are consistent with numeric factor for out-of-place solve
#ifndef SPARSE_CHECK_CONSISTENT_DS_VEC_OUT_PLACE
#define SPARSE_CHECK_CONSISTENT_DS_VEC_OUT_PLACE(nf, b, x, result) \
  do { \
    bool trans = Factored.symbolicFactorization.attributes.transpose ^ Factored.attributes.transpose; \
    int blockSize = (nf).symbolicFactorization.blockSize; \
    int rc = (nf).symbolicFactorization.rowCount * blockSize; \
    int cc = (nf).symbolicFactorization.columnCount * blockSize; \
    int m = trans ? cc : rc; \
    int n = trans ? rc : cc; \
    int expectXSize = n; \
    int expectBSize = ((nf).symbolicFactorization.type == SparseFactorizationQR) ? m : n; \
    SPARSE_PARAMETER_CHECK((x).count == expectXSize, result, \
      "%s (size %dx1) does not match dimensions of matrix factorization %s (%d x %d).\n", \
      #x, (x).count, #nf, expectBSize, expectXSize); \
    SPARSE_PARAMETER_CHECK((b).count == expectBSize, result, \
      "%s (size %dx1) does not match dimensions of matrix factorization %s (%d x %d).\n", \
      #b, (b).count, #nf, expectBSize, expectXSize); \
  } while(0)
#endif /* SPARSE_CHECK_CONSISTENT_DS_VEC_OUT_PLACE */

// Check if matrices are consistent with numeric factor and each other for out-of-place solve
#ifndef SPARSE_CHECK_CONSISTENT_DS_MAT_OUT_PLACE
#define SPARSE_CHECK_CONSISTENT_DS_MAT_OUT_PLACE(nf, B, X, result) \
  do { \
    bool trans = Factored.symbolicFactorization.attributes.transpose ^ Factored.attributes.transpose; \
    int blockSize = (nf).symbolicFactorization.blockSize; \
    int rc = (nf).symbolicFactorization.rowCount * blockSize; \
    int cc = (nf).symbolicFactorization.columnCount * blockSize; \
    int m = trans ? cc : rc; \
    int n = trans ? rc : cc; \
    int expectedXSize = n; \
    int expectedBSize = ((nf).symbolicFactorization.type == SparseFactorizationQR) ? m : n; \
    SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(expectedBSize, expectedXSize, B, X, result, "matrix factorization "#nf); \
  } while(0)
#endif /* SPARSE_CHECK_CONSISTENT_DS_VEC_OUT_PLACE */

/* Iterative Methods */
OS_ENUM(_SparseIterativeMethod, int,
  /*! @abstract Conjugate Gradient */
  _SparseMethodCG = 0,
  /*! @abstract GMRES or variant */
  _SparseMethodGMRES = 1,
  /*! @abstract LSMR (Least Squares MINRES) */
  _SparseMethodLSMR = 2,
  );

/*  MARK: External functions used to implement the public interfaces.         */
#if defined __cplusplus
extern "C" {
#endif

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseOpaqueSymbolicFactorization _SparseSymbolicFactorSymmetric
(SparseFactorization_t factorType,
 const SparseMatrixStructure *Matrix,
 const SparseSymbolicFactorOptions *options);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseOpaqueSymbolicFactorization _SparseSymbolicFactorQR
(SparseFactorization_t factorType,
 const SparseMatrixStructure *Matrix,
 const SparseSymbolicFactorOptions *options);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SparseRetainSymbolic(SparseOpaqueSymbolicFactorization *_Nonnull symbolicFactor);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SparseDestroyOpaqueSymbolic(SparseOpaqueSymbolicFactorization *toFree);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseSymbolicFactorOptions _SparseGetOptionsFromSymbolicFactor(SparseOpaqueSymbolicFactorization *factor);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SparseTrap(void);

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

#if defined __cplusplus
} /* extern "C" */
#endif

/*  MARK: Implementation of the expert-mode public interfaces.                */
static inline SPARSE_PUBLIC_INTERFACE
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type, SparseMatrixStructure Matrix, SparseSymbolicFactorOptions options) {
  SPARSE_PARAMETER_CHECK(Matrix.columnCount > 0,
                         (SparseOpaqueSymbolicFactorization){ .status = SparseParameterError },
                         ".structure.columnCount must be greater than 0.\n");
  switch(type) {
    case SparseFactorizationCholeskyAtA:
    case SparseFactorizationQR:
      return _SparseSymbolicFactorQR(type, &Matrix, &options);

    default:
      SPARSE_PARAMETER_CHECK(Matrix.attributes.kind == SparseSymmetric,
                             (SparseOpaqueSymbolicFactorization){ .status = SparseParameterError },
                             "Requested symmetric factorization of unsymmetric matrix.\n");
      SPARSE_PARAMETER_CHECK(Matrix.rowCount == Matrix.columnCount,
                             (SparseOpaqueSymbolicFactorization){ .status = SparseParameterError },
                             "Matrix purports to be symmetric, but rowCount != columnCount.\n");
      return _SparseSymbolicFactorSymmetric(type, &Matrix, &options);
  }
}

static inline SPARSE_PUBLIC_INTERFACE
SparseOpaqueSymbolicFactorization SparseRetain(SparseOpaqueSymbolicFactorization SymbolicFactor) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions;
  SPARSE_PARAMETER_CHECK(SymbolicFactor.status == SparseStatusOK && SymbolicFactor.factorization,
                         (SparseOpaqueSymbolicFactorization){ .status = SparseParameterError },
                         "Can only retain valid symbolic factorizations.\n");
  _SparseRetainSymbolic(&SymbolicFactor);
  return SymbolicFactor;
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSymbolicFactorization toFree) {
  _SparseDestroyOpaqueSymbolic(&toFree);
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeMethod SparseConjugateGradient(void) {
  SparseIterativeMethod result = {
    .method = _SparseMethodCG,
    .options.cg = (SparseCGOptions) {}
  };
  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeMethod SparseConjugateGradient(SparseCGOptions options) {
  SparseIterativeMethod result = {
    .method = _SparseMethodCG,
    .options.cg = options
  };
  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeMethod SparseGMRES(void) {
  SparseIterativeMethod result = {
    .method = _SparseMethodGMRES,
    .options.gmres = (SparseGMRESOptions) {}
  };
  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeMethod SparseGMRES(SparseGMRESOptions options) {
  SparseIterativeMethod result = {
    .method = _SparseMethodGMRES,
    .options.gmres = options
  };
  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeMethod SparseLSMR(void) {
  SparseIterativeMethod result = {
    .method = _SparseMethodLSMR,
    .options.lsmr = (SparseLSMROptions) {}
  };
  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeMethod SparseLSMR(SparseLSMROptions options) {
  SparseIterativeMethod result = {
    .method = _SparseMethodLSMR,
    .options.lsmr = options
  };
  return result;
}

// Include type-specifc implementation for double
#define _SPARSE_IMPLEMENTATION_TYPE double
#define _SPARSE_OLDSTYLE(NAME) NAME ## _double
#define _SPARSE_VARIANT(NAME) NAME ## _Double
#include "SolveImplementationTyped.h"
#undef _SPARSE_IMPLEMENTATION_TYPE
#undef _SPARSE_VARIANT
#undef _SPARSE_OLDSTYLE

// Include type-specifc implementation for float
#define _SPARSE_IMPLEMENTATION_TYPE float
#define _SPARSE_OLDSTYLE(NAME) NAME ## _float
#define _SPARSE_VARIANT(NAME) NAME ## _Float
#include "SolveImplementationTyped.h"
#undef _SPARSE_IMPLEMENTATION_TYPE
#undef _SPARSE_VARIANT
#undef _SPARSE_OLDSTYLE

#undef sparse_mul_overflow
