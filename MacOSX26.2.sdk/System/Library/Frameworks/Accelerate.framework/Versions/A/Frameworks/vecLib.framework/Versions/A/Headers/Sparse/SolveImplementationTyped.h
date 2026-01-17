// This file expects the below preprocessor symbols to be defined prior to
// inclusion, which specifies which precision to generate implementations for.
#ifndef _SPARSE_IMPLEMENTATION_TYPE
# error "_SPARSE_IMPLEMENTATION_TYPE must be defined prior to inclusion"
#endif /* _SPARSE_IMPLEMENTATION_TYPE */
#ifndef _SPARSE_VARIANT
# error "_SPARSE_VARIANT must be defined prior to inclusion"
#endif /* _SPARSE_VARIANT */

/******************************************************************************
 *  External functions used to implement public API
 ******************************************************************************/
#if defined __cplusplus
extern "C" {
#endif

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern _SPARSE_VARIANT(SparseMatrix) _SPARSE_VARIANT(_SparseConvertFromCoordinate)
(int m, int n, long nBlock, uint8_t blockSize, _SPARSE_ATTRIBUTES attributes, const int *row,
 const int *col, const _SPARSE_IMPLEMENTATION_TYPE *val, char *storage, int *workspace);

#if defined __SPARSE_TYPES_H
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
  extern _SPARSE_VARIANT(SparseMatrix) _SPARSE_VARIANT(_SparseConvertFromOpaque)(_SPARSE_OLDSTYLE(sparse_matrix) matrix);
#endif /* defined __SPARSE_TYPES_H */

#ifdef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
#else
API_AVAILABLE( macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0) )
#endif
extern _SPARSE_VARIANT(SparseOpaqueFactorization)
_SPARSE_VARIANT(_SparseNumericFactorSymmetric)
(SparseOpaqueSymbolicFactorization *symbolicFactor,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseNumericFactorOptions *options,
 void *factorStorage,
 void *workspace);

#ifndef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
extern _SPARSE_VARIANT(SparseOpaqueFactorization)
_SPARSE_VARIANT(_SparseNumericFactorHermitian)
(SparseOpaqueSymbolicFactorization *symbolicFactor,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseNumericFactorOptions *options,
 void *factorStorage,
 void *workspace);
#endif

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern _SPARSE_VARIANT(SparseOpaqueFactorization) _SPARSE_VARIANT(_SparseNumericFactorQR)
(SparseOpaqueSymbolicFactorization *symbolicFactor,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseNumericFactorOptions *options,
 void *factorStorage,
 void *workspace);

API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
extern _SPARSE_VARIANT(SparseOpaqueFactorization) _SPARSE_VARIANT(_SparseNumericFactorLU)
(SparseOpaqueSymbolicFactorization *symbolicFactor,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseNumericFactorOptions *options,
 void *factorStorage,
 void *workspace);

#ifdef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
#else
API_AVAILABLE( macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0) )
#endif
extern _SPARSE_VARIANT(SparseOpaqueFactorization)
_SPARSE_VARIANT(_SparseFactorSymmetric)
(SparseFactorization_t factorType,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseSymbolicFactorOptions *sfoptions,
 const SparseNumericFactorOptions *nfoptions);

#ifndef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
extern _SPARSE_VARIANT(SparseOpaqueFactorization)
_SPARSE_VARIANT(_SparseFactorHermitian)
(SparseFactorization_t factorType,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
const SparseSymbolicFactorOptions *sfoptions,
const SparseNumericFactorOptions *nfoptions);
#endif

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern _SPARSE_VARIANT(SparseOpaqueFactorization) _SPARSE_VARIANT(_SparseFactorQR)
(SparseFactorization_t factorType,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseSymbolicFactorOptions *sfoptions,
 const SparseNumericFactorOptions *nfoptions);

API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
extern _SPARSE_VARIANT(SparseOpaqueFactorization) _SPARSE_VARIANT(_SparseFactorLU)
(SparseFactorization_t factorType,
 const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 const SparseSymbolicFactorOptions *sfoptions,
 const SparseNumericFactorOptions *nfoptions);

#ifdef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
#else
API_AVAILABLE( macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0) )
#endif
extern void _SPARSE_VARIANT(_SparseRefactorSymmetric)
(const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 _SPARSE_VARIANT(SparseOpaqueFactorization) *Factorization,
 const SparseNumericFactorOptions *nfoptions,
 void *workspace);

#ifndef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
extern void _SPARSE_VARIANT(_SparseRefactorHermitian)
(const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 _SPARSE_VARIANT(SparseOpaqueFactorization) *Factorization,
 const SparseNumericFactorOptions *nfoptions,
 void *workspace);
#endif

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseRefactorQR)
(const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 _SPARSE_VARIANT(SparseOpaqueFactorization) *Factorization,
 const SparseNumericFactorOptions *nfoptions,
 void *workspace);

API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
extern void _SPARSE_VARIANT(_SparseRefactorLU)
(const _SPARSE_VARIANT(SparseMatrix) *Matrix,
 _SPARSE_VARIANT(SparseOpaqueFactorization) *Factorization,
 const SparseNumericFactorOptions *nfoptions,
 void *workspace);

API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
extern void _SPARSE_VARIANT(_SparseUpdatePartialRefactorLU)
(_SPARSE_VARIANT(SparseOpaqueFactorization) *Opaque,
 int updateCount,
 const int *updatedIndices,
 _SPARSE_VARIANT(SparseMatrix) newMatrix);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseMultiplySubfactor)
(const _SPARSE_VARIANT(SparseOpaqueSubfactor) *Subfactor,
 const _SPARSE_VARIANT(DenseMatrix) *_Nullable x,
 const _SPARSE_VARIANT(DenseMatrix) *y,
 char *workspace);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseSolveSubfactor)
(const _SPARSE_VARIANT(SparseOpaqueSubfactor) *Subfactor,
 const _SPARSE_VARIANT(DenseMatrix) *_Nullable b,
 const _SPARSE_VARIANT(DenseMatrix) *x,
 char *workspace);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseSolveOpaque)
(const _SPARSE_VARIANT(SparseOpaqueFactorization) *Factored,
 const _SPARSE_VARIANT(DenseMatrix) *_Nullable RHS,
 const _SPARSE_VARIANT(DenseMatrix) *Soln,
 void *workspace);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseDestroyOpaqueNumeric)(_SPARSE_VARIANT(SparseOpaqueFactorization) *toFree);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseRetainNumeric)
(_SPARSE_VARIANT(SparseOpaqueFactorization) *_Nonnull numericFactor);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseNumericFactorOptions _SPARSE_VARIANT(_SparseGetOptionsFromNumericFactor)(_SPARSE_VARIANT(SparseOpaqueFactorization) *factor);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseGetWorkspaceRequired)
(SparseSubfactor_t Subfactor, _SPARSE_VARIANT(SparseOpaqueFactorization) Factor, size_t *workStatic,
 size_t *workPerRHS);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern size_t _SPARSE_VARIANT(_SparseGetIterativeStateSize)
(const SparseIterativeMethod *method, bool preconditioner, int m, int n, int nrhs);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseCGIterate)
(const SparseCGOptions *options,
 int iteration,
 char *state,
 const bool *converged,
 _SPARSE_VARIANT(DenseMatrix) *X,
 _SPARSE_VARIANT(DenseMatrix) *B,
 _SPARSE_VARIANT(DenseMatrix) *R,
 const _SPARSE_VARIANT(SparseOpaquePreconditioner) *_Nullable Preconditioner,
 void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)));

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseIterativeStatus_t _SPARSE_VARIANT(_SparseCGSolve)
(const SparseCGOptions *options,
 _SPARSE_VARIANT(DenseMatrix) *X,
 _SPARSE_VARIANT(DenseMatrix) *B,
 void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)),
 const _SPARSE_VARIANT(SparseOpaquePreconditioner) *_Nullable Preconditioner);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseGMRESIterate)
(const SparseGMRESOptions *options,
 int iteration,
 char *state,
 const bool *converged,
 _SPARSE_VARIANT(DenseMatrix) *X,
 _SPARSE_VARIANT(DenseMatrix) *B,
 _SPARSE_VARIANT(DenseMatrix) *R,
 const _SPARSE_VARIANT(SparseOpaquePreconditioner) *_Nullable Preconditioner,
 void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)));

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseIterativeStatus_t _SPARSE_VARIANT(_SparseGMRESSolve)
(SparseGMRESOptions *options,
 _SPARSE_VARIANT(DenseMatrix) *X,
 _SPARSE_VARIANT(DenseMatrix) *B,
 void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)),
 const _SPARSE_VARIANT(SparseOpaquePreconditioner) *_Nullable Preconditioner);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseLSMRIterate)
(const SparseLSMROptions *options,
 int iteration,
 char *state,
 const bool *converged,
 _SPARSE_VARIANT(DenseMatrix) *X,
 _SPARSE_VARIANT(DenseMatrix) *B,
 _SPARSE_VARIANT(DenseMatrix) *R,
 const _SPARSE_VARIANT(SparseOpaquePreconditioner) *_Nullable Preconditioner,
 void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)));

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern SparseIterativeStatus_t _SPARSE_VARIANT(_SparseLSMRSolve)
(SparseLSMROptions *options,
 _SPARSE_VARIANT(DenseMatrix) *X,
 _SPARSE_VARIANT(DenseMatrix) *B,
 void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)),
 const _SPARSE_VARIANT(SparseOpaquePreconditioner) *_Nullable Preconditioner);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern _SPARSE_VARIANT(SparseOpaquePreconditioner) _SPARSE_VARIANT(_SparseCreatePreconditioner)
(SparsePreconditioner_t type,
 _SPARSE_VARIANT(SparseMatrix) *A);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseReleaseOpaquePreconditioner)
(_SPARSE_VARIANT(SparseOpaquePreconditioner) *toFree);

API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
extern void _SPARSE_VARIANT(_SparseSpMV)
(_SPARSE_IMPLEMENTATION_TYPE alpha,
 _SPARSE_VARIANT(SparseMatrix) A,
 _SPARSE_VARIANT(DenseMatrix) x,
 bool accumulate,
 _SPARSE_VARIANT(DenseMatrix) y);

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

#if defined __cplusplus
} /* extern "C" */
#endif

/******************************************************************************
 *  Implementation helper definitions and types
 ******************************************************************************/
static inline __attribute__((__const__))
_SPARSE_VARIANT(DenseMatrix) _SPARSE_VARIANT(_DenseMatrixFromVector)(_SPARSE_VARIANT(DenseVector) x) {
  return (_SPARSE_VARIANT(DenseMatrix)){
    .rowCount = x.count,
    .columnCount = 1,
    .columnStride = x.count,
    .data = x.data,
  };
}

// This function just provides a shorthand way of delivering an invalid subfactor
static inline __attribute__((__const__))
_SPARSE_VARIANT(SparseOpaqueSubfactor) _SPARSE_VARIANT(_SparseInvalidSubfactor)(void) {
  return (_SPARSE_VARIANT(SparseOpaqueSubfactor)) {
    .contents = SparseSubfactorInvalid,
    .factor = {
      .status = SparseInternalError,
      .symbolicFactorization = { .status = SparseInternalError },
    }
  };
}

// This function just provides a shorthand way of delivering a valid failed factor matrix
static inline __attribute__((__const__))
_SPARSE_VARIANT(SparseOpaqueFactorization) _SPARSE_VARIANT(_SparseFailedFactor)(SparseStatus_t status) {
  return (_SPARSE_VARIANT(SparseOpaqueFactorization)) {
    .status = status,
    .symbolicFactorization = { .status = status },
  };
}

// Null matrix for return on bad function calls
static const _SPARSE_VARIANT(SparseMatrix) _SPARSE_VARIANT(_SparseNullMatrix) = {
  .structure = {
    .rowCount = -1,
    .columnCount = -1,
    .blockSize = 0,
  },
  .data = NULL
};


/*! @abstract Return dimensions of matrix for the part of the factorization represented by Subfactor */
static inline
void _SPARSE_VARIANT(_SparseSubFactorGetDimn)(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, int *_Nonnull m, int *_Nonnull n) {
  uint8_t blockSize = Subfactor.factor.symbolicFactorization.blockSize;
  *m = Subfactor.factor.symbolicFactorization.rowCount * blockSize;
  *n = Subfactor.factor.symbolicFactorization.columnCount * blockSize;

  // We always factor a matrix where m>=n. Swap them so this is so.
  if(*m < *n) {
    int temp = *m;
    *m = *n;
    *n = temp;
  }

  // All Subfactors are n x n, except Q in SparseFactorizationQR, which is m x n
  if(!(Subfactor.factor.symbolicFactorization.type == SparseFactorizationQR && Subfactor.contents == SparseSubfactorQ)) {
    // Not the Q factor of QR => n x n
    *m = *n;
  }

  // If Subfactor is transposed, swap m and n
  if(Subfactor.attributes.transpose) {
    int temp = *m;
    *m = *n;
    *n = temp;
  }
}

/******************************************************************************
 *  Conversion From Other Formats
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseMatrix) SparseConvertFromCoordinate(
    int rowCount, int columnCount, long blockCount, uint8_t blockSize, _SPARSE_ATTRIBUTES attributes,
    const int *_Nonnull row, const int *_Nonnull column, const _SPARSE_IMPLEMENTATION_TYPE *_Nonnull data) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions;
  SPARSE_PARAMETER_CHECK(rowCount>=0, _SPARSE_VARIANT(_SparseNullMatrix),
                         "rowCount (%d) must be non-negative.\n", rowCount);
  SPARSE_PARAMETER_CHECK(columnCount>=0, _SPARSE_VARIANT(_SparseNullMatrix),
                         "columnCount (%d) must be non-negative.\n", columnCount);
  SPARSE_PARAMETER_CHECK(blockCount>=0, _SPARSE_VARIANT(_SparseNullMatrix),
                         "blockCount (%ld) must be non-negative.\n", blockCount);
  SPARSE_PARAMETER_CHECK(attributes.kind==SparseOrdinary || rowCount==columnCount,
                         _SPARSE_VARIANT(_SparseNullMatrix),
                         "attributes.kind must be SparseOrdinary if matrix is not square.\n");
  // NB: Whilst we request 48+ actual space from user, this is for alignment
  //     as malloc() returns 16-byte aligned data anyway, 2*16-4=28 is actually sufficient
  char *storage = (char *)malloc(28 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int) +
                                 blockCount*blockSize*blockSize*sizeof(data[0]));
  SPARSE_PARAMETER_CHECK(storage, _SPARSE_VARIANT(_SparseNullMatrix),
                         "Failed to allocate storage for result.\n");
  int *workspace = (int *)malloc(rowCount*sizeof(int));
  if(!workspace) free(storage);
  SPARSE_PARAMETER_CHECK(workspace, _SPARSE_VARIANT(_SparseNullMatrix),
                         "Failed to allocate workspace of size %ld.\n", rowCount*sizeof(int));
  _SPARSE_VARIANT(SparseMatrix) result =  _SPARSE_VARIANT(_SparseConvertFromCoordinate)(rowCount, columnCount, blockCount, blockSize, attributes, row, column, data, storage, workspace);
  result.structure.columnStarts = (long *)storage; // redundant to assignment in _SparseConvertFromCoordinate call, used to suppress static analyzer warning
  free(workspace);
  result.structure.attributes._allocatedBySparse = true;
  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseMatrix) SparseConvertFromCoordinate(int rowCount,
    int columnCount, long blockCount, uint8_t blockSize, _SPARSE_ATTRIBUTES attributes,
    const int *_Nonnull row, const int *_Nonnull column, const _SPARSE_IMPLEMENTATION_TYPE *_Nonnull data,
    void *_Nonnull storage, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions;
  SPARSE_PARAMETER_CHECK(rowCount>=0, _SPARSE_VARIANT(_SparseNullMatrix),
                         "rowCount (%d) must be non-negative.\n", rowCount);
  SPARSE_PARAMETER_CHECK(columnCount>=0, _SPARSE_VARIANT(_SparseNullMatrix),
                         "columnCount (%d) must be non-negative.\n", columnCount);
  SPARSE_PARAMETER_CHECK(blockCount>=0, _SPARSE_VARIANT(_SparseNullMatrix),
                         "blockCount (%ld) must be non-negative.\n", blockCount);
  SPARSE_PARAMETER_CHECK(attributes.kind==SparseOrdinary || rowCount==columnCount,
                         _SPARSE_VARIANT(_SparseNullMatrix),
                         "attributes.kind must be SparseOrdinary if matrix is not square.\n");
  return _SPARSE_VARIANT(_SparseConvertFromCoordinate)(rowCount, columnCount, blockCount, blockSize, attributes, row, column, data, (char*)storage, (int*)workspace);
}

#if defined __SPARSE_TYPES_H
static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseMatrix) SparseConvertFromOpaque(_Nonnull _SPARSE_OLDSTYLE(sparse_matrix) matrix) {
  return _SPARSE_VARIANT(_SparseConvertFromOpaque)(matrix);
}
#endif /* defined __SPARSE_TYPES_H */

/******************************************************************************
 *  Matrix and Vector Operations (Sparse BLAS Wrappers)
 ******************************************************************************/

/**** Multiplication **********************************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_IMPLEMENTATION_TYPE alpha, _SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseMatrix) X, _SPARSE_VARIANT(DenseMatrix) Y) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor

  int Am = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int An = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(Am, An, Y, X, /* no result */, "matrix A");
  _SPARSE_VARIANT(_SparseSpMV)(alpha, A, X, false, Y);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_IMPLEMENTATION_TYPE alpha, _SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseVector) x, _SPARSE_VARIANT(DenseVector) y) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor

  int m = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int n = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_PARAMETER_CHECK(n == x.count, /* No result */,
                         "Matrix dimensions (%dx%d) do not match x vector dimensions %dx%d\n",
                         m, n, x.count, 1);
  SPARSE_PARAMETER_CHECK(m == y.count, /* No result */,
                         "Matrix dimensions (%dx%d) do not match y vector dimensions %dx%d\n",
                         m, n, y.count, 1);
  _SPARSE_VARIANT(_SparseSpMV)(alpha, A, _SPARSE_VARIANT(_DenseMatrixFromVector)(x),
                               false, _SPARSE_VARIANT(_DenseMatrixFromVector)(y));
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseMatrix) X, _SPARSE_VARIANT(DenseMatrix) Y) {
  SparseMultiply(1, A, X, Y);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseVector) x, _SPARSE_VARIANT(DenseVector) y) {
  SparseMultiply(1, A, x, y);
}

/**** Multipy-Add *************************************************************/


static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(_SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseMatrix) X, _SPARSE_VARIANT(DenseMatrix) Y) {
  SparseMultiplyAdd(1, A, X, Y);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(_SPARSE_IMPLEMENTATION_TYPE alpha, _SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseMatrix) X, _SPARSE_VARIANT(DenseMatrix) Y) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor

  int Am = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int An = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(Am, An, Y, X, /* no result */, "matrix A");
  _SPARSE_VARIANT(_SparseSpMV)(alpha, A, X, true, Y);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(_SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseVector) x, _SPARSE_VARIANT(DenseVector) y) {
  SparseMultiplyAdd(1, A, x, y);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(_SPARSE_IMPLEMENTATION_TYPE alpha, _SPARSE_VARIANT(SparseMatrix) A, _SPARSE_VARIANT(DenseVector) x, _SPARSE_VARIANT(DenseVector) y) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor

  int m = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int n = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_PARAMETER_CHECK(n == x.count, /* No result */,
                         "Matrix dimensions (%dx%d) do not match x vector dimensions %dx%d\n",
                         m, n, x.count, 1);
  SPARSE_PARAMETER_CHECK(m == y.count, /* No result */,
                         "Matrix dimensions (%dx%d) do not match y vector dimensions %dx%d\n",
                         m, n, y.count, 1);
  _SPARSE_VARIANT(_SparseSpMV)(alpha, A, _SPARSE_VARIANT(_DenseMatrixFromVector)(x),
                               true, _SPARSE_VARIANT(_DenseMatrixFromVector)(y));
}

/******************************************************************************
 *  Transposition
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE _SPARSE_VARIANT(SparseMatrix) SparseGetTranspose(_SPARSE_VARIANT(SparseMatrix) Matrix) {
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
  // if the matrix is marked as conjugate transposed, cannot perform transpose, since the net result is only conjugate
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(!(Matrix.structure.attributes.transpose && Matrix.structure.attributes.conjugate_transpose), Matrix,
                         "Cannot transpose matrix marked as conjugate transposed\n");
  Matrix.structure.attributes.conjugate_transpose = false;
#endif
  Matrix.structure.attributes.transpose = !Matrix.structure.attributes.transpose;
  return Matrix;
}
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
static inline SPARSE_PUBLIC_INTERFACE _SPARSE_VARIANT(SparseMatrix) SparseGetConjugateTranspose(_SPARSE_VARIANT(SparseMatrix) Matrix) {
  // if the matrix is marked as transposed, cannot perform conjugate transpose, since the net result is only conjugate
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(!(Matrix.structure.attributes.transpose && !Matrix.structure.attributes.conjugate_transpose), Matrix,
                         "Cannot conjugate transpose matrix marked as transposed\n");
  Matrix.structure.attributes.conjugate_transpose = true;
  Matrix.structure.attributes.transpose = !Matrix.structure.attributes.transpose;
  return Matrix;
}
#endif
static inline SPARSE_PUBLIC_INTERFACE _SPARSE_VARIANT(SparseOpaqueFactorization) SparseGetTranspose(_SPARSE_VARIANT(SparseOpaqueFactorization) Factor) {
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
  // if the factor is marked as conjugate transposed, cannot perform transpose, since the net result is only conjugate
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(!(Factor.attributes.transpose && Factor.attributes.conjugate_transpose), Factor,
                         "Cannot transpose factor marked as conjugate transposed\n");
  Factor.attributes.conjugate_transpose = false;
#endif
  Factor.attributes.transpose = !Factor.attributes.transpose;
  _SPARSE_VARIANT(_SparseRetainNumeric)(&Factor); // we're taking an additional reference
  return Factor;
}
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
static inline SPARSE_PUBLIC_INTERFACE _SPARSE_VARIANT(SparseOpaqueFactorization) SparseGetConjugateTranspose(_SPARSE_VARIANT(SparseOpaqueFactorization) Factor) {
  // if the factor is marked as transposed, cannot perform conjugate transpose, since the net result is only conjugate
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(!(Factor.attributes.transpose && !Factor.attributes.conjugate_transpose), Factor,
                         "Cannot conjugate transpose factor marked as transposed\n");
  Factor.attributes.conjugate_transpose = true;
  Factor.attributes.transpose = !Factor.attributes.transpose;
  _SPARSE_VARIANT(_SparseRetainNumeric)(&Factor); // we're taking an additional reference
  return Factor;
}
#endif
static inline SPARSE_PUBLIC_INTERFACE _SPARSE_VARIANT(SparseOpaqueSubfactor) SparseGetTranspose(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor) {
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
  // if the subfactor is marked as conjugate transposed, cannot perform transpose, since the net result is only conjugate
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(!(Subfactor.attributes.transpose && Subfactor.attributes.conjugate_transpose), Subfactor,
                         "Cannot transpose factor marked as conjugate transposed\n");
  Subfactor.attributes.conjugate_transpose = false;
#endif
  Subfactor.attributes.transpose = !Subfactor.attributes.transpose;
  _SPARSE_VARIANT(_SparseRetainNumeric)(&Subfactor.factor); // we're taking an additional reference
  return Subfactor;
}
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
static inline SPARSE_PUBLIC_INTERFACE _SPARSE_VARIANT(SparseOpaqueSubfactor) SparseGetConjugateTranspose(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor) {
  // if the subfactor is marked as transposed, cannot perform conjugate transpose, since the net result is only conjugate
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(!(Subfactor.attributes.transpose && !Subfactor.attributes.conjugate_transpose), Subfactor,
                         "Cannot conjugate transpose factor marked as transposed\n");
  Subfactor.attributes.conjugate_transpose = true;
  Subfactor.attributes.transpose = !Subfactor.attributes.transpose;
  _SPARSE_VARIANT(_SparseRetainNumeric)(&Subfactor.factor); // we're taking an additional reference
  return Subfactor;
}
#endif

/******************************************************************************
 *  Sparse Factor Functions
 ******************************************************************************/

/**** All-in-one Sparse Factor Functions **************************************/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueFactorization) SparseFactor(SparseFactorization_t type,
    _SPARSE_VARIANT(SparseMatrix) Matrix) {
  return SparseFactor(type, Matrix, _SparseDefaultSymbolicFactorOptions,
                      _SPARSE_VARIANT(_SparseDefaultNumericFactorOptions));
}

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueFactorization) SparseFactor(SparseFactorization_t type,
    _SPARSE_VARIANT(SparseMatrix) Matrix, SparseSymbolicFactorOptions options,
    SparseNumericFactorOptions nfoptions) {
  SPARSE_CHECK_VALID_MATRIX_STRUCTURE(Matrix.structure, _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError));
  switch(type) {
    case SparseFactorizationCholeskyAtA:
    case SparseFactorizationQR:
      return _SPARSE_VARIANT(_SparseFactorQR)(type, &Matrix, &options, &nfoptions);
#if !0
    case SparseFactorizationLU:
    case SparseFactorizationLUUnpivoted:
    case SparseFactorizationLUSPP:
    case SparseFactorizationLUTPP:
      if(__builtin_available(macOS 15.5, macCatalyst 18.5, iOS 18.5, watchOS 11.5, tvOS 18.5, visionOS 2.5, *)) {
        return _SPARSE_VARIANT(_SparseFactorLU)(type, &Matrix, &options, &nfoptions);
      } else {
        __builtin_verbose_trap("unsupported", "LU factorization is not supported on this OS version");
      }
#endif // !TARGET_OS_BRIDGE
    default:
#if (defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL) || 0
      SPARSE_PARAMETER_CHECK(Matrix.structure.attributes.kind == SparseSymmetric,
                             _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError),
                             "Cannot perform symmetric matrix factorization of non-symmetric matrix.\n");
      return _SPARSE_VARIANT(_SparseFactorSymmetric)(type, &Matrix, &options, &nfoptions);
#else
      if (Matrix.structure.attributes.kind == SparseSymmetric) {
        if(__builtin_available(macOS 26.0, macCatalyst 26.0, iOS 26.0, watchOS 26.0, tvOS 26.0, visionOS 26.0, *)) {
          return _SPARSE_VARIANT(_SparseFactorSymmetric)(type, &Matrix, &options, &nfoptions);
        } else {
          __builtin_verbose_trap("unsupported", "Complex Symmetric matrices are not supported on this OS version");
        }
      } else {
        SPARSE_PARAMETER_CHECK(Matrix.structure.attributes.kind == SparseHermitian,
                               _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError),
                               "Cannot perform Hermitian matrix factorization of non-Hermitian matrix.\n");
        return _SPARSE_VARIANT(_SparseFactorHermitian)(type, &Matrix, &options, &nfoptions);
      }
#endif
  }
}

/**** Sparse Factor Functions using pre-calculated symbolic factors ***********/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueFactorization) SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor,
    _SPARSE_VARIANT(SparseMatrix) Matrix) {
  return SparseFactor(SymbolicFactor, Matrix, _SPARSE_VARIANT(_SparseDefaultNumericFactorOptions), NULL, NULL);
}

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueFactorization) SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor,
    _SPARSE_VARIANT(SparseMatrix) Matrix, SparseNumericFactorOptions nfoptions) {
  return SparseFactor(SymbolicFactor, Matrix, nfoptions, NULL, NULL);
}

/**** Sparse Factor Functions with user-defined workspace *********************/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueFactorization) SparseFactor(SparseOpaqueSymbolicFactorization symbolicFactor,
    _SPARSE_VARIANT(SparseMatrix) Matrix, SparseNumericFactorOptions nfoptions,
    void *_Nullable factorStorage, void *_Nullable workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions;
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(symbolicFactor,
                                     _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError),
                                     "Bad symbolic factor.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&symbolicFactor);
  SPARSE_CHECK_MATCH_SYMB_FACTOR(Matrix, symbolicFactor,
                                 _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError));
  // User may or may not have supplied storage for factors and workspace. If they haven't, we
  // allocate our own, the following two variables track which case we're in.
  bool userFactorStorage = (factorStorage != NULL);
  bool userWorkspace     = (workspace != NULL);
  if(!userFactorStorage) {
    factorStorage = options.malloc(_SPARSE_REAL_SIZE(symbolicFactor.factorSize));
    SPARSE_PARAMETER_CHECK(factorStorage != NULL,
                           _SPARSE_VARIANT(_SparseFailedFactor)(SparseInternalError),
                           "Failed to allocate factor storage of size %ld bytes.",
                           _SPARSE_REAL_SIZE(symbolicFactor.factorSize));
  }
  if(!userWorkspace) {
    workspace = options.malloc(_SPARSE_REAL_SIZE(symbolicFactor.workspaceSize));
    if(!workspace && !userFactorStorage) options.free(factorStorage);
    SPARSE_PARAMETER_CHECK(workspace != NULL,
                           _SPARSE_VARIANT(_SparseFailedFactor)(SparseInternalError),
                           "Failed to allocate workspace of size %ld bytes.",
                           _SPARSE_REAL_SIZE(symbolicFactor.workspaceSize));
  }
  _SPARSE_VARIANT(SparseOpaqueFactorization) result;
  switch(symbolicFactor.type) {
    case SparseFactorizationCholeskyAtA:
    case SparseFactorizationQR:
      result = _SPARSE_VARIANT(_SparseNumericFactorQR)(&symbolicFactor, &Matrix, &nfoptions, factorStorage, workspace);
      break;
#if !0
    case SparseFactorizationLU:
    case SparseFactorizationLUUnpivoted:
    case SparseFactorizationLUSPP:
    case SparseFactorizationLUTPP:
      if(__builtin_available(macOS 15.5, macCatalyst 18.5, iOS 18.5, watchOS 11.5, tvOS 18.5, visionOS 2.5, *)) {
        result = _SPARSE_VARIANT(_SparseNumericFactorLU)(&symbolicFactor, &Matrix, &nfoptions, factorStorage, workspace);
      } else {
        __builtin_verbose_trap("unsupported", "LU factorization is not supported on this OS version");
      }
      break;
#endif // !TARGET_OS_BRIDGE
    default:
#ifdef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
      result = _SPARSE_VARIANT(_SparseNumericFactorSymmetric)(&symbolicFactor, &Matrix, &nfoptions, factorStorage, workspace);
#else
      if (Matrix.structure.attributes.kind == SparseSymmetric) {
        if(__builtin_available(macOS 26.0, macCatalyst 26.0, iOS 26.0, watchOS 26.0, tvOS 26.0, visionOS 26.0, *)) {
          result = _SPARSE_VARIANT(_SparseNumericFactorSymmetric)(&symbolicFactor, &Matrix, &nfoptions, factorStorage, workspace);
        } else {
          __builtin_verbose_trap("unsupported", "Complex Symmetric matrices are not supported on this OS version");
        }
      } else {
        result = _SPARSE_VARIANT(_SparseNumericFactorHermitian)(&symbolicFactor, &Matrix, &nfoptions, factorStorage, workspace);
      }
#endif
  }
  result.userFactorStorage = userFactorStorage; // Flag whether we should free memory on destruction or not
  if(!userWorkspace) options.free(workspace); // If we allocated workspace, free it
  return result;
}

/******************************************************************************
 *  Sparse Direct Solve Functions (DenseMatrix)
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseMatrix) XB) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                    "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_MAT_IN_PLACE(Factored, XB, /* no result */);
  int nrhs = (XB.attributes.transpose) ? XB.rowCount : XB.columnCount; // number of rhs
  size_t lworkspace = Factored.solveWorkspaceRequiredStatic + nrhs*Factored.solveWorkspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /*no result*/, "Failed to allocate workspace of size %ld for SparseSolve().\n", lworkspace);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, NULL, &XB, workspace);
  options.free(workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_MAT_OUT_PLACE(Factored, B, X, /* no result */);
  int nrhs = (B.attributes.transpose) ? B.rowCount : B.columnCount; // number of rhs
  size_t lworkspace = Factored.solveWorkspaceRequiredStatic + nrhs*Factored.solveWorkspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /*no result*/,
                         "Failed to allocate workspace of size %ld for SparseSolve().\n",
                         lworkspace);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, &B, &X, workspace);
  options.free(workspace);
}

/**** Solving Systems with User Defined Workspace *****************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseMatrix) XB, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_MAT_IN_PLACE(Factored, XB, /* no result */);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, NULL, &XB, workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_MAT_OUT_PLACE(Factored, B, X, /* no result */);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, &B, &X, workspace);
}

/******************************************************************************
 *  Sparse Direct Solve Functions (DenseVector)
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseVector) xb) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_VEC_IN_PLACE(Factored, xb, /* no result */);
  _SPARSE_VARIANT(DenseMatrix) XB = _SPARSE_VARIANT(_DenseMatrixFromVector)(xb);
  size_t lworkspace = Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /*no result*/, "Failed to allocate workspace of size %ld for SparseSolve().\n", lworkspace);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, NULL, &XB, workspace);
  options.free(workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_VEC_OUT_PLACE(Factored, b, x, /* no result */);
  _SPARSE_VARIANT(DenseMatrix) B = _SPARSE_VARIANT(_DenseMatrixFromVector)(b);
  _SPARSE_VARIANT(DenseMatrix) X = _SPARSE_VARIANT(_DenseMatrixFromVector)(x);
  size_t lworkspace = Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /*no result*/,
                         "Failed to allocate workspace of size %ld for SparseSolve().\n",
                         lworkspace);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, &B, &X, workspace);
  options.free(workspace);
}

/**** Solving Systems with User Defined Workspace *****************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseVector) xb, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_VEC_IN_PLACE(Factored, xb, /* no result */);
  _SPARSE_VARIANT(DenseMatrix) XB = _SPARSE_VARIANT(_DenseMatrixFromVector)(xb);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, NULL, &XB, workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueFactorization) Factored, _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored.symbolicFactorization, /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factored.symbolicFactorization);
  SPARSE_CHECK_VALID_NUMERIC_FACTOR(Factored, /* no result */);
  SPARSE_CHECK_CONSISTENT_DS_VEC_OUT_PLACE(Factored, b, x, /* no result */);
  _SPARSE_VARIANT(DenseMatrix) B = _SPARSE_VARIANT(_DenseMatrixFromVector)(b);
  _SPARSE_VARIANT(DenseMatrix) X = _SPARSE_VARIANT(_DenseMatrixFromVector)(x);
  _SPARSE_VARIANT(_SparseSolveOpaque)(&Factored, &B, &X, workspace);
}

/******************************************************************************
 *  Advanced Solving Functions
 ******************************************************************************/

/**** Symbolic Refactor Functions *********************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseRefactor(_SPARSE_VARIANT(SparseMatrix) Matrix, _SPARSE_VARIANT(SparseOpaqueFactorization) *_Nonnull Factorization) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factorization->symbolicFactorization,
                                     /* no result */,
                                     "Factorization does not hold a completed matrix factorization.\n");
  SparseNumericFactorOptions nfoptions = _SPARSE_VARIANT(_SparseGetOptionsFromNumericFactor)(Factorization);
  SparseRefactor(Matrix, Factorization, nfoptions);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseRefactor(_SPARSE_VARIANT(SparseMatrix) Matrix, _SPARSE_VARIANT(SparseOpaqueFactorization) *_Nonnull Factorization, SparseNumericFactorOptions nfoptions) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factorization->symbolicFactorization,
                                     /* no result */,
                                     "Factorization does not hold a valid symbolic matrix factorization.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factorization->symbolicFactorization);
  void *workspace = options.malloc(_SPARSE_REAL_SIZE(Factorization->symbolicFactorization.workspaceSize));
  if(!workspace) Factorization->status = SparseInternalError;
  SPARSE_PARAMETER_CHECK(workspace,
                         /* no return value */,
                         "Failed to allocate workspace of size %ld.",
                         _SPARSE_REAL_SIZE(Factorization->symbolicFactorization.workspaceSize));

  SparseRefactor(Matrix, Factorization, nfoptions, workspace);
  options.free(workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseRefactor(_SPARSE_VARIANT(SparseMatrix) Matrix, _SPARSE_VARIANT(SparseOpaqueFactorization) *_Nonnull Factored, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(Factored->symbolicFactorization,
                                     /* no result */,
                                     "Factored does not hold a completed matrix factorization.\n");
  SparseNumericFactorOptions nfoptions = _SPARSE_VARIANT(_SparseGetOptionsFromNumericFactor)(Factored);
  return SparseRefactor(Matrix, Factored, nfoptions, workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseRefactor(_SPARSE_VARIANT(SparseMatrix) Matrix, _SPARSE_VARIANT(SparseOpaqueFactorization) *_Nonnull Factored, SparseNumericFactorOptions nfoptions, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_MATCH_SYMB_FACTOR(Matrix, Factored->symbolicFactorization, /* no result */);
  switch(Factored->symbolicFactorization.type) {
    case SparseFactorizationCholeskyAtA:
    case SparseFactorizationQR:
      _SPARSE_VARIANT(_SparseRefactorQR)(&Matrix, Factored, &nfoptions, workspace);
      break;
#if !0
    case SparseFactorizationLU:
    case SparseFactorizationLUUnpivoted:
    case SparseFactorizationLUSPP:
    case SparseFactorizationLUTPP:
      if(__builtin_available(macOS 15.5, macCatalyst 18.5, iOS 18.5, watchOS 11.5, tvOS 18.5, visionOS 2.5, *)) {
        _SPARSE_VARIANT(_SparseRefactorLU)(&Matrix, Factored, &nfoptions, workspace);
      } else {
        __builtin_verbose_trap("unsupported", "LU factorization is not supported on this OS version");
      }
      break;
#endif // !TARGET_OS_BRIDGE
    default:
#ifdef _SPARSE_IMPLEMENTATION_TYPE_IS_REAL
      _SPARSE_VARIANT(_SparseRefactorSymmetric)(&Matrix, Factored, &nfoptions, workspace);
#else
      if (Matrix.structure.attributes.kind == SparseSymmetric) {
        if(__builtin_available(macOS 26.0, macCatalyst 26.0, iOS 26.0, watchOS 26.0, tvOS 26.0, visionOS 26.0, *)) {
          _SPARSE_VARIANT(_SparseRefactorSymmetric)(&Matrix, Factored, &nfoptions, workspace);
        } else {
          __builtin_verbose_trap("unsupported", "Complex Symmetric matrices are not supported on this OS version");
        }
      } else {
        _SPARSE_VARIANT(_SparseRefactorHermitian)(&Matrix, Factored, &nfoptions, workspace);
      }
#endif
  }
}

/******************************************************************************
 *  Sparse Update Functions
 ******************************************************************************/
static inline SPARSE_PUBLIC_INTERFACE
void SparseUpdateFactor(SparseUpdate_t updateAlgorithm,
                        _SPARSE_VARIANT(SparseOpaqueFactorization) *_Nonnull Factorization,
                        int updateCount,
                        const int *_Nonnull updatedIndices,
                        _SPARSE_VARIANT(SparseMatrix) Update) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_MATCH_SYMB_FACTOR(Update, Factorization->symbolicFactorization, /* no result */);
  switch(Factorization->symbolicFactorization.type) {
    case SparseFactorizationLUUnpivoted:
    case SparseFactorizationLUSPP:
    case SparseFactorizationLUTPP:
      _SPARSE_VARIANT(_SparseUpdatePartialRefactorLU)(Factorization, updateCount, updatedIndices, Update);
      break;
    default:
      Factorization->status = SparseParameterError;
      SPARSE_PARAMETER_CHECK(false, /* no result */, "SparseUpdate is only supported on LU factorizations");
  }
}

/******************************************************************************
 *  Extracting Sub-factors of Factors
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueSubfactor) SparseCreateSubfactor(SparseSubfactor_t subfactor,
                                                        _SPARSE_VARIANT(SparseOpaqueFactorization) Factor) {
  // Check user supplied a valid factorization object
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Factor.symbolicFactorization.status == SparseStatusOK &&
                         Factor.symbolicFactorization.factorization &&
                         Factor.status == SparseStatusOK &&
                         Factor.numericFactorization,
                         _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                         "Bad factor.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Factor.symbolicFactorization);
  // Check user is requesting a valid combination of subfactor and Factor
  _SPARSE_ATTRIBUTES attributes = {
    .transpose = false,
    .triangle = SparseLowerTriangle,
    .kind = SparseOrdinary,
  };
  SparseFactorization_t type = Factor.symbolicFactorization.type;
  switch(subfactor) {
    case SparseSubfactorP:
      break; // Valid for all factor types

    case SparseSubfactorL:
      // Valid for Cholesky and LDL^T only
      attributes.kind = SparseTriangular;
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationCholesky ||
                             type == SparseFactorizationLDLTUnpivoted ||
                             type == SparseFactorizationLDLTSBK ||
                             type == SparseFactorizationLDLTTPP,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "Subfactor Type only valid for Cholesky and LDL^T factorizations.\n");
      break;

    case SparseSubfactorPLPS:
      // Valid for Cholesky and LDL^T only
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationCholesky ||
                             type == SparseFactorizationLDLTUnpivoted ||
                             type == SparseFactorizationLDLTSBK ||
                             type == SparseFactorizationLDLTTPP,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "Subfactor Type only valid for Cholesky and LDL^T factorizations.\n");
      break;

    case SparseSubfactorS:
      // Valid for LDL^T only
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationLDLTUnpivoted ||
                             type == SparseFactorizationLDLTSBK ||
                             type == SparseFactorizationLDLTTPP,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "Subfactor Type only valid for LDL^T factorization.\n");
      break;

#if !0
    case SparseSubfactorSr:
    case SparseSubfactorSc:
      // Valid for LDL^T only
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationLUUnpivoted ||
                             type == SparseFactorizationLUSPP ||
                             type == SparseFactorizationLUTPP,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "Subfactor Type only valid for LU factorization.\n");
      break;
#endif // !TARGET_OS_BRIDGE

    case SparseSubfactorD:
      // Valid for LDL^T only
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationLDLTUnpivoted ||
                             type == SparseFactorizationLDLTSBK ||
                             type == SparseFactorizationLDLTTPP,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "Subfactor Type only valid for LDL^T factorizations.\n");
      break;

    case SparseSubfactorQ:
      // Valid for QR or LU only
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationQR
#if !0
                             || type == SparseFactorizationLUUnpivoted
                             || type == SparseFactorizationLUSPP
                             || type == SparseFactorizationLUTPP
#endif // !TARGET_OS_BRIDGE
                             ,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "SparseSubfactorQ only valid for QR or LU factorizations.\n");
      break;

    case SparseSubfactorR:
    case SparseSubfactorRP:
      // Valid for QR and CholeskyAtA only
      attributes.kind = SparseTriangular;
      attributes.triangle = SparseUpperTriangle;
      SPARSE_PARAMETER_CHECK(type == SparseFactorizationQR ||
                             type == SparseFactorizationCholeskyAtA,
                             _SPARSE_VARIANT(_SparseInvalidSubfactor)(),
                             "Subfactor Type only valid for QR and CholeskyAtA factorizations.\n");
      break;

    default:
      SPARSE_PARAMETER_CHECK(false, _SPARSE_VARIANT(_SparseInvalidSubfactor)(), "Invalid subfactor type.");
  }
  _SPARSE_VARIANT(_SparseRetainNumeric)(&Factor); // count new reference
  size_t workspaceRequiredStatic, workspaceRequiredPerRHS;
  _SPARSE_VARIANT(_SparseGetWorkspaceRequired)(subfactor, Factor, &workspaceRequiredStatic, &workspaceRequiredPerRHS);
  return (_SPARSE_VARIANT(SparseOpaqueSubfactor)) {
    .attributes = attributes,
    .contents = subfactor,
    .factor = Factor,
    .workspaceRequiredStatic = workspaceRequiredStatic,
    .workspaceRequiredPerRHS = workspaceRequiredPerRHS
  };
}

/******************************************************************************
 *  Sub-factor Multiplication and Solve Functions
 ******************************************************************************/

/**** Matrix solve functions **************************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) XB) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factorization.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and b
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  // Check XY agrees
  int XBCount = (XB.attributes.transpose) ? XB.rowCount : XB.columnCount;
  int XBsize  = (XB.attributes.transpose) ? XB.columnCount : XB.rowCount;
  SPARSE_PARAMETER_CHECK(XBCount > 0, /* none */, "XB must have non-zero dimension.\n");
  int maxmn = (m > n) ? m : n;
  SPARSE_PARAMETER_CHECK(XBsize == maxmn, /* none */,
                         "XB dimension (%d) must match maximum subfactor dimension (%d).\n",
                         XBsize, maxmn);
  size_t lworkspace = Subfactor.workspaceRequiredStatic + XBCount*Subfactor.workspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /* none */,
                         "Failed to allocate workspace of size %ld.\n", lworkspace);
  _SPARSE_VARIANT(_SparseSolveSubfactor)(&Subfactor, NULL, &XB, (char*)workspace);
  options.free(workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factorization.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and y
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(m, n, B, X, /* no result */, "subfactor dimension");
  int nrhs = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  size_t lworkspace = Subfactor.workspaceRequiredStatic + nrhs*Subfactor.workspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /* none */,
                         "Failed to allocate workspace of size %ld.\n",
                         lworkspace);
  _SPARSE_VARIANT(_SparseSolveSubfactor)(&Subfactor, &B, &X, (char*)workspace);
  options.free(workspace);
}

/**** Matrix solve functions with user-supplied workspace *********************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) XB, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factor subobject.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and b
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  // Check XY agrees
  int XBCount = (XB.attributes.transpose) ? XB.rowCount : XB.columnCount;
  int XBsize  = (XB.attributes.transpose) ? XB.columnCount : XB.rowCount;
  SPARSE_PARAMETER_CHECK(XBCount > 0, /* none */, "XB must have non-zero dimension.\n");
  int maxmn = (m > n) ? m : n;
  SPARSE_PARAMETER_CHECK(XBsize == maxmn, /* none */,
                         "XB dimension (%d) must match maximum subfactor dimension (%d).\n",
                         XBsize, maxmn);
  _SPARSE_VARIANT(_SparseSolveSubfactor)(&Subfactor, NULL, &XB, (char*)workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X,
                 void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factor subobject.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and y
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(m, n, B, X, /* no result */, "subfactor dimension");
  _SPARSE_VARIANT(_SparseSolveSubfactor)(&Subfactor, &B, &X, (char*)workspace);
}

/**** Vector solve ************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseVector) XB) {
  _SPARSE_VARIANT(DenseMatrix) XBMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(XB);
  SparseSolve(Subfactor, XBMatrix);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseVector) B, _SPARSE_VARIANT(DenseVector) X) {
  _SPARSE_VARIANT(DenseMatrix) BMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(B);
  _SPARSE_VARIANT(DenseMatrix) XMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(X);
  SparseSolve(Subfactor, BMatrix, XMatrix);
}

/**** Vector solve functions with user-supplied workspace *********************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseVector) XB, void *_Nonnull workspace) {
  _SPARSE_VARIANT(DenseMatrix) XBMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(XB);
  SparseSolve(Subfactor, XBMatrix, workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseSolve(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseVector) B, _SPARSE_VARIANT(DenseVector) X,
                 void *_Nonnull workspace) {
  _SPARSE_VARIANT(DenseMatrix) BMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(B);
  _SPARSE_VARIANT(DenseMatrix) XMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(X);
  SparseSolve(Subfactor, BMatrix, XMatrix, workspace);
}

/**** Matrix multiply functions ***********************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) XY) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factor subobject.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and y
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  // Check XY agrees
  int XYCount = (XY.attributes.transpose) ? XY.rowCount : XY.columnCount;
  int XYsize  = (XY.attributes.transpose) ? XY.columnCount : XY.rowCount;
  SPARSE_PARAMETER_CHECK(XYCount > 0, /* none */, "XY must have non-zero dimension.\n");
  int maxmn = (m > n) ? m : n;
  SPARSE_PARAMETER_CHECK(XYsize == maxmn, /* none */,
                         "XY dimension (%d) must match maximum subfactor dimension (%d).\n",
                         XYsize, maxmn);
  size_t lworkspace = Subfactor.workspaceRequiredStatic + XYCount*Subfactor.workspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /* none */,
                         "Failed to allocate workspace of size %ld.\n", lworkspace);
  _SPARSE_VARIANT(_SparseMultiplySubfactor)(&Subfactor, NULL, &XY, (char*)workspace);
  options.free(workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) X, _SPARSE_VARIANT(DenseMatrix) Y) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factor subobject.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and y
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(n, m, X, Y, /* no result */, "subfactor dimension");

  int nrhs = (Y.attributes.transpose) ? Y.rowCount : Y.columnCount;
  size_t lworkspace = Subfactor.workspaceRequiredStatic + nrhs*Subfactor.workspaceRequiredPerRHS;
  void *workspace = options.malloc(lworkspace);
  SPARSE_PARAMETER_CHECK(workspace, /* none */,
                         "Failed to allocate workspace of size %ld.\n", lworkspace);
  _SPARSE_VARIANT(_SparseMultiplySubfactor)(&Subfactor, &X, &Y, (char*)workspace);
  options.free(workspace);
}

/**** Matrix multiply functions with user-supplied workspace ******************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) XY, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factor subobject.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and y
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  // Check XY agrees
  int XYCount = (XY.attributes.transpose) ? XY.rowCount : XY.columnCount;
  int XYsize  = (XY.attributes.transpose) ? XY.columnCount : XY.rowCount;
  SPARSE_PARAMETER_CHECK(XYCount > 0, /* none */, "XY must have non-zero dimension.\n");
  int maxmn = (m > n) ? m : n;
  SPARSE_PARAMETER_CHECK(XYsize == maxmn, /* none */,
                         "XY dimension (%d) must match maximum subfactor dimension (%d).\n",
                         XYsize, maxmn);
  _SPARSE_VARIANT(_SparseMultiplySubfactor)(&Subfactor, NULL, &XY, (char*)workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseMatrix) X, _SPARSE_VARIANT(DenseMatrix) Y, void *_Nonnull workspace) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.contents != SparseSubfactorInvalid, /* none */,
                         "Subfactor does not hold a valid factor subobject.\n");
  // The only way to construct a valid Subfactor is to have a valid factorization.
  // We assume this from this point on.
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  // Figure out expected dimensions of x and y
  int m, n;
  _SPARSE_VARIANT(_SparseSubFactorGetDimn)(Subfactor, &m, &n);
  SPARSE_CHECK_CONSISTENT_MAT_OUT_PLACE(m, n, Y, X, /* no result */, "subfactor dimension");
  _SPARSE_VARIANT(_SparseMultiplySubfactor)(&Subfactor, &X, &Y, (char*)workspace);
}

/**** Vector multiply functions ***********************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseVector) XY) {
  _SPARSE_VARIANT(DenseMatrix) XYMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(XY);
  SparseMultiply(Subfactor, XYMatrix);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor,
                    _SPARSE_VARIANT(DenseVector) X, _SPARSE_VARIANT(DenseVector) Y) {
  _SPARSE_VARIANT(DenseMatrix) XMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(X);
  _SPARSE_VARIANT(DenseMatrix) YMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(Y);
  SparseMultiply(Subfactor, XMatrix, YMatrix);
}

/**** Vector multiply functions with user-supplied workspace ******************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor, _SPARSE_VARIANT(DenseVector) XY, void *_Nonnull workspace) {
  _SPARSE_VARIANT(DenseMatrix) XYMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(XY);
  SparseMultiply(Subfactor, XYMatrix, workspace);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor,
                     _SPARSE_VARIANT(DenseVector) X, _SPARSE_VARIANT(DenseVector) Y,
                     void *_Nonnull workspace) {
  _SPARSE_VARIANT(DenseMatrix) XMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(X);
  _SPARSE_VARIANT(DenseMatrix) YMatrix = _SPARSE_VARIANT(_DenseMatrixFromVector)(Y);
  SparseMultiply(Subfactor, XMatrix, YMatrix, workspace);
}

/******************************************************************************
 *  Preconditioners
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaquePreconditioner) SparseCreatePreconditioner(
    SparsePreconditioner_t type, _SPARSE_VARIANT(SparseMatrix) A) {
  SparseIterativeMethod nullMethod = {};
  struct _SparseIterativeMethodBaseOptions options = nullMethod.options.base;
  int Am = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int An = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_PARAMETER_CHECK(Am>0 && An>0,
                         (_SPARSE_VARIANT(SparseOpaquePreconditioner)) { .type = SparsePreconditionerNone },
                         "Bad matrix dimensions %dx%d\n", Am, An);

  return _SPARSE_VARIANT(_SparseCreatePreconditioner) (type, &A);
}

/******************************************************************************
 *  Iterative Sparse Solve Functions
 ******************************************************************************/

/**** Solve without preconditioner ********************************************/

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method, _SPARSE_VARIANT(SparseMatrix) A,
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Am = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int An = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_PARAMETER_CHECK(Am>0 && An>0, SparseIterativeParameterError,
                         "Bad matrix dimensions %dx%d\n", Am, An);

  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Xn == Bn, SparseIterativeParameterError,
                         "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
  SPARSE_PARAMETER_CHECK(Xm==An, SparseIterativeParameterError,
                         "Dimensions of A (%dx%d) and X (%dx%d) do not match.", Am, An, Xm, Xn);
  SPARSE_PARAMETER_CHECK(Bm==Am, SparseIterativeParameterError,
                         "Dimensions of A (%dx%d) and B (%dx%d) do not match.", Am, An, Bm, Bn);

  switch(method.method) {
    case _SparseMethodCG:
      // For CG A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          // For CG, trans is only ever false (and requires A==A^T anyway)
          if(accumulate) SparseMultiplyAdd(A, X_, Y);
          else           SparseMultiply(A, X_, Y);
        }, NULL);
    case _SparseMethodGMRES:
      // For GMRES A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          // For GMRES, trans is only ever false
          if(accumulate) SparseMultiplyAdd(A, X_, Y);
          else           SparseMultiply(A, X_, Y);        }, NULL);
    case _SparseMethodLSMR:
      return _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          if(accumulate) {
            if(trans==CblasNoTrans) SparseMultiplyAdd(A, X_, Y);
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
            else                    SparseMultiplyAdd(SparseGetConjugateTranspose(A), X_, Y);
#else
            else                    SparseMultiplyAdd(SparseGetTranspose(A), X_, Y);
#endif
          } else {
            if(trans==CblasNoTrans) SparseMultiply(A, X_, Y);
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
            else                    SparseMultiply(SparseGetConjugateTranspose(A), X_, Y);
#else
            else                    SparseMultiply(SparseGetTranspose(A), X_, Y);
#endif
          }
        }, NULL);
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method, _SPARSE_VARIANT(SparseMatrix) A,
    _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x) {
  return SparseSolve(method, A, _SPARSE_VARIANT(_DenseMatrixFromVector)(b),
                     _SPARSE_VARIANT(_DenseMatrixFromVector)(x));
}


static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
    void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)),
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Xm > 0 && Xn > 0, SparseIterativeParameterError,
                         "Bad dimensions for X (%dx%d)\n", Xm, Xn);
  SPARSE_PARAMETER_CHECK(Bm > 0 && Bn > 0, SparseIterativeParameterError,
                         "Bad dimensions for B (%dx%d)\n", Bm, Bn);
  SPARSE_PARAMETER_CHECK(Xn == Bn, SparseIterativeParameterError,
                         "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);

  switch(method.method) {
    case _SparseMethodCG:
      // For CG A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
      return _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B, ApplyOperator, NULL);
    case _SparseMethodGMRES:
      // For GMRES A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
      return _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B, ApplyOperator, NULL);
    case _SparseMethodLSMR:
      return _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B, ApplyOperator, NULL);
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
    void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,_SPARSE_VARIANT(DenseVector), _SPARSE_VARIANT(DenseVector)),
    _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Xm = x.count;
  int Bm = b.count;
  SPARSE_PARAMETER_CHECK(Xm > 0, SparseIterativeParameterError,
                         "Bad dimension for x (%dx%d)\n", Xm, 1);
  SPARSE_PARAMETER_CHECK(Bm > 0, SparseIterativeParameterError,
                         "Bad dimensions for b (%dx%d)\n", Bm, 1);

  _SPARSE_VARIANT(DenseMatrix) X = _SPARSE_VARIANT(_DenseMatrixFromVector)(x);
  _SPARSE_VARIANT(DenseMatrix) B = _SPARSE_VARIANT(_DenseMatrixFromVector)(b);
  // Note: we rely on the fact that neither X nor Y is transpose in calls to ApplyOperator()
  // and Precondition()
  switch(method.method) {
    case _SparseMethodCG:
      // Must be symmetric for CG
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
         ApplyOperator(accumulate, trans,
           (_SPARSE_VARIANT(DenseVector)) { .count=X_.rowCount, .data=X_.data },
           (_SPARSE_VARIANT(DenseVector)) { .count=Y.rowCount, .data=Y.data }
           );
        }, NULL );
    case _SparseMethodGMRES:
      // Must be square for GMRES
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          ApplyOperator(accumulate, trans,
            (_SPARSE_VARIANT(DenseVector)) { .count=X_.rowCount, .data=X_.data },
            (_SPARSE_VARIANT(DenseVector)) { .count=Y.rowCount, .data=Y.data }
            );
        }, NULL );
    case _SparseMethodLSMR:
      return _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          ApplyOperator(accumulate, trans,
            (_SPARSE_VARIANT(DenseVector)) { .count=X_.rowCount, .data=X_.data },
            (_SPARSE_VARIANT(DenseVector)) { .count=Y.rowCount, .data=Y.data }
            );
        }, NULL );
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

/**** Solve with preconditioner ***********************************************/

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method, _SPARSE_VARIANT(SparseMatrix) A,
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X, SparsePreconditioner_t Preconditioner) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Am = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int An = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_PARAMETER_CHECK(Am>0 && An>0, SparseIterativeParameterError,
                         "Bad matrix dimensions %dx%d\n", Am, An);

  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Xn == Bn, SparseIterativeParameterError,
                         "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
  SPARSE_PARAMETER_CHECK(Xm==An, SparseIterativeParameterError,
                         "Dimensions of A (%dx%d) and X (%dx%d) do not match.", Am, An, Xm, Xn);
  SPARSE_PARAMETER_CHECK(Bm==Am, SparseIterativeParameterError,
                         "Dimensions of A (%dx%d) and B (%dx%d) do not match.", Am, An, Bm, Bn);

  SPARSE_PARAMETER_CHECK(Preconditioner != SparsePreconditionerNone &&
                         Preconditioner != SparsePreconditionerUser, SparseIterativeParameterError,
                         "Invalid preconditioner type for this call: for no preconditioner, omit "
                         "the parameter. User-supplied preconditioners must supply apply() method.");

  // Create preconditioner
  _SPARSE_VARIANT(SparseOpaquePreconditioner) P =
    _SPARSE_VARIANT(_SparseCreatePreconditioner) (Preconditioner, &A);
  if(P.type == SparsePreconditionerNone) return SparseIterativeInternalError;

  // Call CG
  SparseIterativeStatus_t result;
  switch(method.method) {
    case _SparseMethodCG:
      result = _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          // For CG, trans is only ever false
          if(accumulate) SparseMultiplyAdd(A, X_, Y);
          else           SparseMultiply(A, X_, Y);
        }, &P);
      break;
    case _SparseMethodGMRES:
      result = _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          // For GMRES, trans is only ever false
          if(accumulate) SparseMultiplyAdd(A, X_, Y);
          else           SparseMultiply(A, X_, Y);
        }, &P);
      break;
    case _SparseMethodLSMR:
      result = _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B,
      ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
        if(accumulate) {
          if(trans==CblasNoTrans) SparseMultiplyAdd(A, X_, Y);
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
          else                    SparseMultiplyAdd(SparseGetConjugateTranspose(A), X_, Y);
#else
          else                    SparseMultiplyAdd(SparseGetTranspose(A), X_, Y);
#endif
        } else {
          if(trans==CblasNoTrans) SparseMultiply(A, X_, Y);
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
          else                    SparseMultiply(SparseGetConjugateTranspose(A), X_, Y);
#else
          else                    SparseMultiply(SparseGetTranspose(A), X_, Y);
#endif
        }
      }, &P);
      break;
    default:
      __builtin_unreachable(); // All options considered above.
  }

  // Release preconditioner
  _SPARSE_VARIANT(_SparseReleaseOpaquePreconditioner)(&P);

  return result;
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method, _SPARSE_VARIANT(SparseMatrix) A,
    _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x,
    SparsePreconditioner_t Preconditioner) {
  return SparseSolve(method, A, _SPARSE_VARIANT(_DenseMatrixFromVector)(b),
                     _SPARSE_VARIANT(_DenseMatrixFromVector)(x));
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method, _SPARSE_VARIANT(SparseMatrix) A,
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X,
    _SPARSE_VARIANT(SparseOpaquePreconditioner) Preconditioner) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;

  int Am = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.columnCount : A.structure.rowCount);
  int An = A.structure.blockSize * ((A.structure.attributes.transpose) ? A.structure.rowCount : A.structure.columnCount);
  SPARSE_PARAMETER_CHECK(Am>0 && An>0, SparseIterativeParameterError,
                         "Bad matrix dimensions %dx%d\n", Am, An);
  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Xn == Bn, SparseIterativeParameterError,
                         "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
  SPARSE_PARAMETER_CHECK(Xm==An, SparseIterativeParameterError,
                         "Dimensions of A (%dx%d) and X (%dx%d) do not match.", Am, An, Xm, Xn);
  SPARSE_PARAMETER_CHECK(Bm==Am, SparseIterativeParameterError,
                         "Dimensions of A (%dx%d) and B (%dx%d) do not match.", Am, An, Bm, Bn);

  switch(method.method) {
    case _SparseMethodCG:
      // For CG A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          // For CG, trans is only ever false (and requires A==A^T anyway)
          if(accumulate) SparseMultiplyAdd(A, X_, Y);
          else           SparseMultiply(A, X_, Y);
        }, &Preconditioner);
    case _SparseMethodGMRES:
      // For GMRES A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          // For GMRES, trans is only ever false
          if(accumulate) SparseMultiplyAdd(A, X_, Y);
          else           SparseMultiply(A, X_, Y);
        }, &Preconditioner);
    case _SparseMethodLSMR:
      return _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
        if(accumulate) {
          if(trans==CblasNoTrans) SparseMultiplyAdd(A, X_, Y);
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
          else                    SparseMultiplyAdd(SparseGetConjugateTranspose(A), X_, Y);
#else
          else                    SparseMultiplyAdd(SparseGetTranspose(A), X_, Y);
#endif
        } else {
          if(trans==CblasNoTrans) SparseMultiply(A, X_, Y);
#if !defined _SPARSE_IMPLEMENTATION_TYPE_IS_REAL && !0
          else                    SparseMultiply(SparseGetConjugateTranspose(A), X_, Y);
#else
          else                    SparseMultiply(SparseGetTranspose(A), X_, Y);
#endif
        }
    }, &Preconditioner);
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method, _SPARSE_VARIANT(SparseMatrix) A,
    _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x,
    _SPARSE_VARIANT(SparseOpaquePreconditioner) Preconditioner) {
  return SparseSolve(method, A, _SPARSE_VARIANT(_DenseMatrixFromVector)(b),
                     _SPARSE_VARIANT(_DenseMatrixFromVector)(x), Preconditioner);
}

static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
    void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)) ,
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) X,
    _SPARSE_VARIANT(SparseOpaquePreconditioner) Preconditioner) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Xm > 0 && Xn > 0, SparseIterativeParameterError,
                         "Bad dimensions for X (%dx%d)\n", Xm, Xn);
  SPARSE_PARAMETER_CHECK(Bm > 0 && Bn > 0, SparseIterativeParameterError,
                         "Bad dimensions for B (%dx%d)\n", Bm, Bn);
  SPARSE_PARAMETER_CHECK(Xn == Bn, SparseIterativeParameterError,
                         "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);

  switch(method.method) {
    case _SparseMethodCG:
      // For CG A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
      return _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B, ApplyOperator, &Preconditioner);
    case _SparseMethodGMRES:
      // For GMRES A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Dimensions of X (%dx%d) and B (%dx%d) do not match.", Xm, Xn, Bm, Bn);
      return _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B, ApplyOperator, &Preconditioner);
    case _SparseMethodLSMR:
      return _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B, ApplyOperator, &Preconditioner);
    default:
      __builtin_unreachable(); // All options considered above.
  }
}


static inline SPARSE_PUBLIC_INTERFACE
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
    void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseVector), _SPARSE_VARIANT(DenseVector)),
    _SPARSE_VARIANT(DenseVector) b, _SPARSE_VARIANT(DenseVector) x,
    _SPARSE_VARIANT(SparseOpaquePreconditioner) Preconditioner) {

  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Xm = x.count;
  int Bm = b.count;

  SPARSE_PARAMETER_CHECK(Xm > 0, SparseIterativeParameterError,
                         "Bad dimension for x (%dx%d)\n", Xm, 1);
  SPARSE_PARAMETER_CHECK(Bm > 0, SparseIterativeParameterError,
                         "Bad dimensions for b (%dx%d)\n", Bm, 1);

  _SPARSE_VARIANT(DenseMatrix) X = _SPARSE_VARIANT(_DenseMatrixFromVector)(x);
  _SPARSE_VARIANT(DenseMatrix) B = _SPARSE_VARIANT(_DenseMatrixFromVector)(b);

  // Note: we rely on the fact that neither X nor Y is transpose in calls to ApplyOperator()
  // and Precondition() (true as input matrices are not-transpose)
  switch(method.method) {
    case _SparseMethodCG:
      // For CG A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseCGSolve)(&method.options.cg, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          ApplyOperator(accumulate, trans,
            (_SPARSE_VARIANT(DenseVector)) { .count=X_.rowCount, .data=X_.data },
            (_SPARSE_VARIANT(DenseVector)) { .count=Y.rowCount, .data=Y.data }
            );
        }, &Preconditioner );
    case _SparseMethodGMRES:
      // For GMRES A must be square, so X and B must have matching dimensions
      SPARSE_PARAMETER_CHECK(Xm == Bm, SparseIterativeParameterError,
                             "Counts of X (%d) and B (%d) do not match.", Xm, Bm);
      return _SPARSE_VARIANT(_SparseGMRESSolve)(&method.options.gmres, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          ApplyOperator(accumulate, trans,
            (_SPARSE_VARIANT(DenseVector)) { .count=X_.rowCount, .data=X_.data },
            (_SPARSE_VARIANT(DenseVector)) { .count=Y.rowCount, .data=Y.data }
            );
          }, &Preconditioner );
    case _SparseMethodLSMR:
      return _SPARSE_VARIANT(_SparseLSMRSolve)(&method.options.lsmr, &X, &B,
        ^void(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix) X_, _SPARSE_VARIANT(DenseMatrix) Y) {
          ApplyOperator(accumulate, trans,
            (_SPARSE_VARIANT(DenseVector)) { .count=X_.rowCount, .data=X_.data },
            (_SPARSE_VARIANT(DenseVector)) { .count=Y.rowCount, .data=Y.data }
            );
        }, &Preconditioner );
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

/******************************************************************************
 *  Sparse Single-step Iteration  Functions
 ******************************************************************************/

static inline SPARSE_PUBLIC_INTERFACE
size_t _SPARSE_VARIANT(SparseGetStateSize)(SparseIterativeMethod method, bool preconditioner, int m, int n, int nrhs) {
  return _SPARSE_VARIANT(_SparseGetIterativeStateSize)(&method, preconditioner, m, n, nrhs);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseIterate(SparseIterativeMethod method, int iteration, const bool *_Nonnull converged, void *_Nonnull state,
    void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)),
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) R, _SPARSE_VARIANT(DenseMatrix) X,
    _SPARSE_VARIANT(SparseOpaquePreconditioner) Preconditioner) {
  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  SPARSE_PARAMETER_CHECK(Xm>0 && Xn>0, /* no result */, "Invalid size for X (%dx%d).", Xm, Xn);
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Bm>0 && Bn>0, /* no result */, "Invalid size for B (%dx%d).", Bm, Bn);
  int Rm = (R.attributes.transpose) ? R.columnCount : R.rowCount;
  int Rn = (R.attributes.transpose) ? R.rowCount : R.columnCount;
  SPARSE_PARAMETER_CHECK(Rm>0 && Rn>0, /* no result */, "Invalid size for R (%dx%d).", Rm, Rn);
  SPARSE_PARAMETER_CHECK(Xn==Bn && Bn==Rn, /* no result */,
                         "Sizes of X (%dx%d), B (%dx%d) and R (%dx%d) are inconsistent.", Xm, Xn, Bm, Bn, Rm, Bn);
  SPARSE_PARAMETER_CHECK(Rm>=Bm, /* no result */,
                         "Sizes of residual matrix R(%dx%d) must be at least as large as right-hand side B (%dx%d).",
                         Rm, Rn, Bm, Rn);

  switch(method.method) {
    case _SparseMethodCG:
      _SPARSE_VARIANT(_SparseCGIterate) (&method.options.cg, iteration, (char*)state, converged,
                                         &X, &B, &R, &Preconditioner, ApplyOperator);
      break;
    case _SparseMethodGMRES:
      _SPARSE_VARIANT(_SparseGMRESIterate) (&method.options.gmres, iteration, (char*)state, converged,
                                            &X, &B, &R, &Preconditioner, ApplyOperator);
      break;
    case _SparseMethodLSMR:
      _SPARSE_VARIANT(_SparseLSMRIterate) (&method.options.lsmr, iteration, (char*)state, converged,
                                           &X, &B, &R, &Preconditioner, ApplyOperator);
      break;
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseIterate(SparseIterativeMethod method, int iteration, const bool *_Nonnull converged, void *_Nonnull state,
    void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, _SPARSE_VARIANT(DenseMatrix), _SPARSE_VARIANT(DenseMatrix)),
    _SPARSE_VARIANT(DenseMatrix) B, _SPARSE_VARIANT(DenseMatrix) R, _SPARSE_VARIANT(DenseMatrix) X) {
  struct _SparseIterativeMethodBaseOptions options = method.options.base;
  int Xm = (X.attributes.transpose) ? X.columnCount : X.rowCount;
  int Xn = (X.attributes.transpose) ? X.rowCount : X.columnCount;
  SPARSE_PARAMETER_CHECK(Xm>0 && Xn>0, /* no result */, "Invalid size for X (%dx%d).", Xm, Xn);
  int Bm = (B.attributes.transpose) ? B.columnCount : B.rowCount;
  int Bn = (B.attributes.transpose) ? B.rowCount : B.columnCount;
  SPARSE_PARAMETER_CHECK(Bm>0 && Bn>0, /* no result */, "Invalid size for B (%dx%d).", Bm, Bn);
  int Rm = (R.attributes.transpose) ? R.columnCount : R.rowCount;
  int Rn = (R.attributes.transpose) ? R.rowCount : R.columnCount;
  SPARSE_PARAMETER_CHECK(Rm>0 && Rn>0, /* no result */, "Invalid size for R (%dx%d).", Rm, Rn);
  SPARSE_PARAMETER_CHECK(Xn==Bn && Bn==Rn, /* no result */,
                         "Sizes of X (%dx%d), B (%dx%d) and R (%dx%d) are inconsistent.", Xm, Xn, Bm, Bn, Rm, Bn);
  SPARSE_PARAMETER_CHECK(Rm>=Bm, /* no result */,
                         "Sizes of residual matrix R(%dx%d) must be at least as large as right-hand side B (%dx%d).",
                         Rm, Rn, Bm, Rn);

  switch(method.method) {
    case _SparseMethodCG:
      _SPARSE_VARIANT(_SparseCGIterate) (&method.options.cg, iteration, (char*)state, converged,
                                         &X, &B, &R, NULL, ApplyOperator);
      break;
    case _SparseMethodGMRES:
      _SPARSE_VARIANT(_SparseGMRESIterate) (&method.options.gmres, iteration, (char*)state, converged,
                                            &X, &B, &R, NULL, ApplyOperator);
      break;
    case _SparseMethodLSMR:
      _SPARSE_VARIANT(_SparseLSMRIterate) (&method.options.lsmr, iteration, (char*)state, converged,
                                           &X, &B, &R, NULL, ApplyOperator);
      break;
    default:
      __builtin_unreachable(); // All options considered above.
  }
}

/******************************************************************************
 *  Memory Management
 ******************************************************************************/

/**** Retaining resources *****************************************************/

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueFactorization) SparseRetain(_SPARSE_VARIANT(SparseOpaqueFactorization) NumericFactor) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_CHECK_VALID_SYMBOLIC_FACTOR(NumericFactor.symbolicFactorization,
                                     _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError),
                                     "Can only retain valid numeric factorizations.\n")
  options = _SparseGetOptionsFromSymbolicFactor(&NumericFactor.symbolicFactorization);
  SPARSE_PARAMETER_CHECK(NumericFactor.status == SparseStatusOK && NumericFactor.numericFactorization,
                         _SPARSE_VARIANT(_SparseFailedFactor)(SparseParameterError),
                         "Can only retain valid numeric factorizations.\n");
  _SPARSE_VARIANT(_SparseRetainNumeric)(&NumericFactor);
  return NumericFactor;
}

static inline SPARSE_PUBLIC_INTERFACE
_SPARSE_VARIANT(SparseOpaqueSubfactor) SparseRetain(_SPARSE_VARIANT(SparseOpaqueSubfactor) Subfactor) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // We need default error reporting until we verify valid factor
  SPARSE_PARAMETER_CHECK(Subfactor.factor.symbolicFactorization.status == SparseStatusOK &&
                         Subfactor.factor.symbolicFactorization.factorization,
                         _SPARSE_VARIANT(_SparseInvalidSubfactor)(), "Can only retain valid objects.\n");
  options = _SparseGetOptionsFromSymbolicFactor(&Subfactor.factor.symbolicFactorization);
  SPARSE_PARAMETER_CHECK(Subfactor.factor.status == SparseStatusOK && Subfactor.factor.numericFactorization,
                         _SPARSE_VARIANT(_SparseInvalidSubfactor)(), "Can only retain valid objects.\n");
  _SPARSE_VARIANT(_SparseRetainNumeric)(&Subfactor.factor);
  return Subfactor;
}

/**** Cleaning up resources ***************************************************/

static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(_SPARSE_VARIANT(SparseOpaqueFactorization) toFree) {
  _SPARSE_VARIANT(_SparseDestroyOpaqueNumeric)(&toFree);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(_SPARSE_VARIANT(SparseOpaqueSubfactor) toFree) {
  _SPARSE_VARIANT(_SparseDestroyOpaqueNumeric)(&toFree.factor);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(_SPARSE_VARIANT(SparseMatrix) toFree) {
  SparseSymbolicFactorOptions options = _SparseDefaultSymbolicFactorOptions; // Default error reporting.
  SPARSE_PARAMETER_CHECK(toFree.structure.attributes._allocatedBySparse == true, ,
                         "Attempting to call SparseCleanup on a matrix that was not allocated by the Sparse library.\n");
  free(toFree.structure.columnStarts);
}

static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(_SPARSE_VARIANT(SparseOpaquePreconditioner) Preconditioner) {
  SparseIterativeMethod nullMethod = {};
  struct _SparseIterativeMethodBaseOptions options = nullMethod.options.base;
  SPARSE_PARAMETER_CHECK(Preconditioner.type!=SparsePreconditionerNone && Preconditioner.type!=SparsePreconditionerUser,
                         /* no result */, "Cannot cleanup this kind of Preconditioner.");

  _SPARSE_VARIANT(_SparseReleaseOpaquePreconditioner) (&Preconditioner);
}

/*********************************** END **************************************/
