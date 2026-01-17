/*! @header
 *  This header provides sparse matrix solvers using "transparent" types
 *  (i.e. types where the matrix structure is exposed to the caller, in
 *  contrast to the opaque types used in the Sparse/BLAS.h header). A subset
 *  of the BLAS operations are also defined on these types.
 *
 *  @copyright 2016-2017 Apple, Inc.  All rights reserved.
 *  @unsorted
 */

/******************************************************************************
 *
 * We offer two different techniques for solving AX=B where A is sparse and
 * X, B are dense.
 *
 * DIRECT METHODS:    These perform a factorization of the matrix A, and are the
 *                    most reliable and easiest to use. It is recommended that
 *                    users try these first, and only resort to iterative methods
 *                    if time or memory constraints make these methods infeasible.
 *                    Once a factorization is performed additional solves with the
 *                    same A can be performed cheaply.
 *
 * ITERATIVE METHODS: These apply an iterative numerical algorithm to solve the
 *                    problem. They use less memory than direct methods, and can
 *                    be considerably faster if the problem is numerically well
 *                    conditioned or a good preconditioner is known. To safely
 *                    and correctly use these methods a greater degree of
 *                    mathematial knoweldge and effort is required of the user.
 *                    Subsequent solves require the same amount of computational
 *                    work, unless a good approximate solution is available.
 *                    For the best performance, a problem specific preconditioner
 *                    will need to be supplied by the user.
 *
 * ======================================
 * Direct Methods (Matrix Factorizations)
 * ======================================
 *
 * We offer the factorizations detailed below, but all use the same interface,
 * with the variant specified by the argument `type`. The most basic solution
 * sequence is:
 *   factors = SparseFactor(type, Matrix)
 *   SparseSolve(factors, rhs, soln)
 *   SparseCleanup(factors)
 *
 * It is sometimes required to perform repeated factorizations with the same
 * non-zero pattern but different numerical values. A SparseRefactor() entry
 * point is supplied that allows the reuse of an existing factor object and
 * its associated memory with different numerical values.
 *
 * If multiple different numeric factorizations with the same symbolic pattern
 * are required, or if the user wishes to perform ordering before numeric
 * values are known, a symbolic factorization object can be obtained by passing
 * a SparseMatrixStructure object to SparseFactor() in place of the full
 * SparseMatrix that also includes the numeric values. The underlying object
 * is reference counted, so this object may be safely destroyed by calling
 * SparseOpaqueDestroy() even if numeric factorizations that depend on it are
 * still in use. Due to this reference counting, if the user wishes to make a
 * shallow copy of the underlying object they should call SparseRetain().
 *
 * If the user wishes to apply matrix factors individually, they may obtain
 * opaque objects through the SparseCreateSubfactor() routine. These objects
 * may then be used through calls to SparseMultiply() and SparseSove().
 *
 * Cholesky
 * ========
 * A = PLL'P'
 * for real symmetric or complex Hermitian positive-definite matrices A.
 * If A is not positive-definite the factorization will detect this and fail,
 * potentially after significant computation.
 * P is a permutation matrix that is (by default) automatically calculated by
 * the solver (see options.orderMethod for further details).
 * L is the lower triangular factorization matrix.
 * By default no diagonal scaling matrix is applied to A, but one may be
 * enabled through options.scalingMethod.
 *
 * SparseSolve() will solve Ax = b.
 * SparseCreateSubfactor() allows the following subfactors to be extracted:
 * - SparseSubfactorL    returns an opaque object representing L. Both Multiply and Solve are valid.
 * - SparseSubfactorP    returns an opaque object representing P. Both Multiply and Solve are valid.
 * - SparseSubfactorPLPS returns an opaque object representing PLP'. Only Solve is valid, and
 *                       transpose solve followed by non-transpose solve is equivalent to a full
 *                       system solve with A.
 *
 * Symmetric Indefinite
 * ====================
 * SAS = PLDL'P'
 * for real symmetric or complex Hermitian matrices A.
 * P is a permutation matrix that is (by default) automatically calculated by
 * the solver (see options.orderMethod for further details).
 * S is a diagonal scaling matrix that is (by default) automatically calculated
 * by the solver (see options.scalingMethod for further details).
 * L is a unit lower triangular factorization matrix.
 * D is a block diagonal factorization matrix, with 1x1 and 2x2 diagonal blocks.
 * A variety of different pivoting options are offered:
 * - Unpivoted performs no numerical pivoting, and D only has 1x1 pivots. Only
 *   suitable for well behaved systems with full rank, otherwise very unstable.
 * - Supernode Bunch-Kaufmann (SBK) restricts pivoting to operations that do not
 *   alter the symbolic structure of the factors. Static pivoting (the addition
 *   (of sqrt(eps) to small diagonal entries) is used in the presence of small
 *   pivots. This method is often effective for well scaled matrices, but is
 *   not numerically stable for some systems.
 * - Threshold Partial Pivoting (TPP) is provably numerically stable, but at the
 *   cost of (potentially) increased factor size and number of operations.
 *
 * SparseSolve() will solve Ax = b.
 * SparseCreateSubfactor() allows the following sunfactors to be extracted:
 * - SparseSubfactorL    returns an opaque object representing L. Both Multiply and Solve are valid.
 * - SparseSubfactorD    returns an opaque object representing D. Both Multiply and Solve are valid.
 * - SparseSubfactorP    returns an opaque object representing P. Both Multiply and Solve are valid.
 * - SparseSubfactorS    returns an opaque object representing S. Both Multiply and Solve are valid.
 * - SparseSubfactorPLPS returns an opaque object representing PLP'S. When tranposed represents PLDP'S.
 *                    Only Solve is valid, and transpose solve followed by non-transpose solve is
 *                    equivalent to a full system solve with A.
 *
 * QR
 * ==
 * A = QRP      if m >= n so A is overdetermined or square
 * A = P'R'Q'   if m <  n so A is underdetermined
 * for real or complex matrices A of size m x n.
 * P is a column permutation that is (by default) automatically calculated by
 * the solver (see options.orderMethod for further details).
 * Q is an m x n (or n x m if underdetermined) orthagonal factor matrix.
 * R is an n x n (or m x m if underdetermined) upper triangular factor matrix.
 *
 * If a Cholesky factorization of A^T A is desired (being the factor R) consider
 * using the CholeskyAtA options below instead. This performs the same factorization but
 * without the overhead of storing the Q factor.
 *
 * We note that in many cases other methods of solving a given problem are normally faster
 * than the use of a Sparse QR factorization:
 * - For least squares, use a dedicated least squares solution method
 *   (e.g. Diagonally preconditioned LSMR).
 * - If a low rank approximation is required, multiply rank+5 random vectors by A and
 *   perform a dense QR of the result.
 *
 * SparseSolve() will solve either:
 * - x = arg min_x || Ax - b ||_2      if A is overdetermined.
 * - x = arg min_x || x ||_2 s.t. Ax=b if A is underdetermined.
 * SparseCreateSubfactor() allows the following sunfactors to be extracted:
 * - SparseSubfactorQ  returns an opaque object representing Q. Both Multiply and Solve are valid.
 * - SparseSubfactorR  returns an opaque object representing R. Both Multiply and Solve are valid.
 * - SparseSubfactorP  returns an opaque object representing P. Both Multiply and Solve are valid.
 * - SparseSubfactorRP returns an opaque object representing RP (or P'R'). Only Solve is valid.
 *
 * CholeskyAtA
 * ===========
 * A^TA = P'R'RP
 * for real matrices A.
 * This performs the same factorization as QR above, but avoids storing the Q factor resulting
 * in a significant storage saving. The number of rows in A must be greater than or equal to the
 * number of columns (otherwise A^T A is singular).
 *
 * SparseSolve() will solve A^TA x = b.
 * SparseCreateSubfactor() allows the following subfactors to be extracted:
 * - SparseSubfactorR  returns an opaque object representing R. Both Multiply and Solve are valid.
 * - SparseSubfactorP  returns an opaque object representing P. Both Multiply and Solve are valid.
 * - SparseSubfactorRP returns an opaque object representing RP (or P'R'). Only Solve is valid.
 *
 *
 * =====================================
 * Iterative Methods and Preconditioners
 * =====================================
 *
 * We offer the following iterative methods:
 * CG:    Conjugate Gradient method for symmetric positive-definite matrices.
 * GMRES: Generalised Minimum RESidual method and variants (FGMRES, DQGMRES) for
 *        symmetric indefinite and unsymmetric matrices.
 * LSMR:  Least Squares Minimum Residual method for solving least squares problems.
 *
 * The most basic solution sequence is:
 *
 *   SparseSolve( SparseCG(), X, B, A );
 *
 * However:
 * - Various method-specific options may be passed as the argument of SparseCG(), SparseGMRES()
 *   or SparseLSMR() in the first argument:
 *     SparseSolve( SparseCG( (SparseCGOptions) { .maxIterations=10 } ), X, B, A);
 * - The SparseMatrix argument A may be replaced by a block that applies the operator
 *   Y = Y + op(A) X where op(A) represents the application of the operator A or its transpose:
 *     SparseSolve( SparseLSMR(), X, B,
 *       ^void (enum CBLAS_TRANSPOSE trans, DenseMatrix_Double X, DenseMatrix_Double Y) {
 *         // Code to perform Y += op(A) X
 *       } );
 * - An optional Preconditioner may be supplied. If A is a SparseMatrix, this can be a predefined
 *   preconditioner supplied by the Accelerate library:
 *     SparseSolve( SparseCG(), X, B, SparsePreconditionerDiagonal, A );
 *   or be user specified (i.e. if a better preconditioner is available, or a routine for applying
 *   an operator is supplied by the user instead of a SparseMatrix A):
 *     SparseSolve( SparseCG(), X, B, (SparseOpaquePreconditioner) {
 *         .type  = SparsePreconditionerUser,
 *         .mem   = userDataPointer,
 *         .apply = userFunctionPointer
 *       }, A);
 *
 * If the user requires more control over convergence testing, or otherwise wishes to single-step
 * the method, they may instead perform a single iteration through a call of the form:
 *
 *  SparseIterate( SparseCG(), iteration, state, converged, X, B, R, Preconditioner, ApplyOperator);
 *
 * Users should note that solutions may not be available at all iterations, and a call with
 * iteration=-1 may be required to retrieve the current solution. Refer to the documentation for
 * individual methods before attempting to use this form.
 *
 * Further note that convience forms of this call using SparseMatrix data types and predefined
 * preconditioners are not offered.
 *
 * At present the following preconditioners are offered by this package:
 * SparsePreconditionerDiagonal     - Applies y=D^-1x, where D is the matrix containing only
 *                                    the diagonal elements of A. It provides a simple
 *                                    preconditioner for CG and GMRES methods.
 * SparsePreconditionerDiagScaling  - Applies y=D^-1x, where D is the diagonal matrix such that
 *                                    d_ii = || A_j ||_2 with A_j the j-th column of A. It provides
 *                                    a simple preconditioner for LSMR.
 *
 *****************************************************************************/


#ifndef SPARSE_SOLVE_HEADER
#define SPARSE_SOLVE_HEADER

#ifndef __has_include
# define __has_include(_) 0
#endif

#ifndef __has_feature
# define __has_feature(_) 0
#endif

#ifndef __has_attribute
# define __has_attribute(_) 0
#endif

/*  Standard attributes for public sparse interfaces.                         */
#if __has_attribute(overloadable)
#define SPARSE_PUBLIC_INTERFACE __attribute__((overloadable))

#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined __VECLIB__ /* Included via Accelerate */
# define SPARSE_INCLUDED_VIA_ACCELERATE
#endif

#if __has_include(<Accelerate/Accelerate.h>)
# include <Accelerate/Accelerate.h>
#else
# include <cblas.h>
#endif

// Due to changes in the implementation of OS_ENUM that would break ABI,
// we now define our own SPARSE_ENUM instead.
// Note that as specifying an enum_extensibility attribute causes Swift to import things
// differently compared to previous versions of Sparse, we disable it here to avoid
// breaking backwards compatability.
#if __has_attribute(enum_extensibility) && !defined(__swift__)
#  define __SPARSE_ENUM_ATTR __attribute__((enum_extensibility(open)))
#  define __SPARSE_ENUM_ATTR_CLOSED __attribute__((enum_extensibility(closed)))
#else
#  define __SPARSE_ENUM_ATTR
#  define __SPARSE_ENUM_ATTR_CLOSED
#endif // __has_attribute(enum_extensibility)

#if __has_feature(objc_fixed_enum) || __has_extension(cxx_strong_enums)
# define SPARSE_ENUM(_name, _type, ...) \
         typedef enum : _type { __VA_ARGS__ } _name##_t
# define SPARSE_CLOSED_ENUM(_name, _type, ...) \
         typedef enum : _type { __VA_ARGS__ } \
             __SPARSE_ENUM_ATTR_CLOSED _name##_t
#else
# define __SPARSE_ENUM_C_FALLBACK(_name, _type, ...) \
         typedef _type _name##_t; enum _name { __VA_ARGS__ }
# define SPARSE_ENUM(_name, _type, ...) \
         typedef _type _name##_t; enum { __VA_ARGS__ }
# define SPARSE_CLOSED_ENUM(_name, _type, ...) \
         __SPARSE_ENUM_C_FALLBACK(_name, _type, ## __VA_ARGS__) \
         __SPARSE_ENUM_ATTR_CLOSED
#endif

#if __has_include(<os/availability.h>)
# include <os/availability.h>
#else
# define API_AVAILABLE(_) /* nothing */
#endif

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

/*******************************************************************************
 * @group Sparse Matrix Type Definitions
 ******************************************************************************/

/*! @abstract A flag to describe the type of matrix represented.
 *
 *  @discussion A SparseMatrixStructure object can represent several types of
 *  matrices:
 *
 *  @constant SparseOrdinary A "normal" sparse matrix without special structure.
 *
 *  @constant SparseTriangular A triangular sparse matrix with non-unit diagonal.
 *    The SparseTriangle_t field indicates which triangle (upper or lower)
 *    is used.
 *
 *  @constant SparseUnitTriangular A triangular sparse matrix with unit diagonal.
 *    The SparseTriangle_t field indicates which triangle (upper or lower)
 *    is used.
 *
 *  @constant SparseSymmetric A symmetric sparse matrix.  The SparseTriangle_t
 *    field indicates which triangle (upper or lower) is used to represent
 *    the matrix.                                                             */
SPARSE_ENUM(SparseKind, unsigned int,
  SparseOrdinary       = 0,
  SparseTriangular     = 1,
  SparseUnitTriangular = 2,
  SparseSymmetric      = 3,
);

/*! @abstract A flag to indicate which triangle of a matrix is used.
 *
 *  @constant SparseUpperTriangle
 *            For triangular and unit-triangular matrices, indicates that the
 *            upper triangle is to be used, and the lower triangle is implicitly
 *            zero.
 *            For symmetric matrices, indicates that the upper triangle is to
 *            be used; the lower triangle is implicitly defined by reflection.
 *
 *  @constant SparseLowerTriangle
 *            For triangular matrices, indicates that the lower triangle is to
 *            be used, and the upper triangle is implicitly zero.
 *            For symmetric matrices, indicates that the lower triangle is to
 *            be used; the upper triangle is implicitly defined by reflection.*/
SPARSE_CLOSED_ENUM(SparseTriangle, unsigned char,
  SparseUpperTriangle = 0,
  SparseLowerTriangle = 1
);

/*! @abstract A type representing the attributes of a matrix.
 *
 *  @field transpose If `true`, the matrix is implicitly transposed when used
 *  in any functions.
 *
 *  @field triangle If `kind` is `SparseOrdinary`, this field is ignored.
 *  Otherwise it indicates which triangle (upper or lower) represents the
 *  matrix.
 *
 *  @field kind Identifies the matrix as being full (`SparseOrdinary`), [unit-]
 *  triangular (`SparseTriangular`, `SparseUnitTriangular`), or symmetric
 *  (`SparseSymmetric`).
 *
 *  @field _reserved for future expansion. Must be zero.
 *
 *  @field _allocatedBySparse an implementation detail. Should be zero for any
 *  matrix you allocate.                                                      */
typedef struct {
  bool            transpose: 1;
  SparseTriangle_t triangle: 1;
  SparseKind_t         kind: 2;
  unsigned int    _reserved: 11;
  bool   _allocatedBySparse: 1;
} SparseAttributes_t;

/*! @abstract A type representing the sparsity structure of a sparse matrix.
 *
 *  @discussion The sparsity structure is represented in *block compressed
 *  sparse column* (block CSC) format. The matrix is divided into a regular
 *  grid of rowCount x columnCount blocks each of size `blockSize x blockSize`,
 *  and only blocks containing a non-zero entry are stored. CSC format is
 *  used to store the locations of these blocks. For each block column, a list
 *  of block row indices for non-zero blocks are stored, and the lists for each
 *  column are stored contigously one after the other. Hence the row indices
 *  for column j are given by rowIndices[columnStarts[j]:columnStarts[j+1]],
 *  where columnStarts[] is storing the location of the first index in each
 *  column.
 *  If the blockSize is 1, then this format is exactly equivalent to standard
 *  CSC format.
 *  CSR format data can be simulated by using a blockSize of 1 and setting
 *  the transpose attribute (strictly this is still a transposed CSC matrix, so
 *  rowCount and columnCount will be transposed compared to true CSR).
 *
 *  @field rowCount Number of (block) rows in matrix.
 *
 *  @field columnCount Number of (block) columns in matrix.
 *
 *  @field columnStarts Specifies where each (block) column starts in rowIndices
 *         array.
 *
 *  @field rowIndices Specifies the (block) row indices of the matrix.
 *
 *  @field attributes The attribute meta-data for the matrix, for example
 *         whether the matrix is symmetric and only half the entries are stored.
 *
 *  @field blockSize The block size of the matrix.                            */
typedef struct {
  int rowCount;
  int columnCount;
  long *columnStarts;
  int *rowIndices;
  SparseAttributes_t attributes;
  uint8_t blockSize;
} SparseMatrixStructure;

/*! @abstract A type representing a sparse matrix.
 *
 *  @discussion
 *  `data` is the array of values in the non-zero blocks of the matrix stored
 *  contiguously, each block in column-major order. If there are N structural
 *  non-zero blocks in the matrix, `data` holds `blockSize`*`blockSize`*`N`
 *  doubles.
 *
 * @field structure The symbolic structure of the matrix.
 *
 * @field data The numerical values of the matrix. If structure.blockSize > 1,
 *        blocks are stored contigously in column-major format.               */
typedef struct {
  SparseMatrixStructure structure;
  double *data;
} SparseMatrix_Double;

/*! @abstract A type representing a sparse matrix.
 *
 *  @discussion
 *  `data` is the array of values in the non-zero blocks of the matrix stored
 *  contiguously, each block in column-major order. If there are N structural
 *  non-zero blocks in the matrix, `data` holds `blockSize`*`blockSize`*`N`
 *  doubles.
 *
 * @field structure The symbolic structure of the matrix.
 *
 * @field data The numerical values of the matrix. If structure.blockSize > 1,
 *        blocks are stored contigously in column-major format.               */
typedef struct {
  SparseMatrixStructure structure;
  float *data;
} SparseMatrix_Float;

/******************************************************************************
 *  @group Conversion From Other Formats
 ******************************************************************************
 *  @discussion In the conversion functions below, the variables `rowCount`,
 *  `columnCount`, `blockCount`, `row[]` and `col[]` describe a sparse matrix
 *  structure with `blockCount` structurally non-zero entries, each of which
 *  is a "block".
 *
 *  The matrix described has `rowCount*blockSize` rows and
 *  `columnCount*blockSize` columns. For each `i` in `0..<blockCount`, there
 *  is a a structurally non-zero block at block position `(row[i], column[i])`
 *  with numerical values `data[i*blockSize*blockSize:(i+1)*blockSize*blockSize-1]`
 *  interpreted as the elements of a dense column-major matrix with `blockSize`
 *  rows and columns.
 *
 *  If the coordinates `(row[i], column[i])` are invalid (meaning that they
 *  lie outside the ranges `0..<rowCount` or `0..<columnCount`, respectively),
 *  or `attributes.kind` is `SparseTriangular` or `SparseUnitTriangular` and
 *  they lie in the wrong triangle, then that block element is ignored and
 *  not included in the returned matrix.
 *
 *  If `attributes.kind` is `SparseSymmetric`, any entries in the wrong
 *  triangle are transposed and summed into the block at `(column[i], row[i])`
 *  if one is present.
 *
 *  In all cases, if any duplicate coordinates are present, the elements are
 *  summed and replaced with a single entry.
 *
 *  There are two variants of each converter; one which allocates its own
 *  workspace internally, and also allocates space for the resulting sparse
 *  matrix, and one which requires you to pass storage for the new matrix and
 *  a separate workspace for precise control over allocations.                */

/*! @abstract Convert from coordinate format arrays to a SparseMatrix_Double
 *  object, dropping out-of-range entries and summing duplicates.
 *
 *  @discussion For symmetric matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  @param rowCount (input) Number of rows in structure.
 *
 *  @param columnCount (input) Number of columns in structure.
 *
 *  @param blockCount (input) Number of blocks in matrix.
 *
 *  @param blockSize (input) Block size for data storage on both input and
 *  ouput.
 *
 *  @param attributes (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  @param row (input) Row indices of matrix structure.
 *
 *  @param column (input) Column indices of matrix structure.
 *
 *  @param data (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  @return A new SparseMatrix_Double object. When you are done with this
 *  matrix, release the memory that has been allocated by calling
 *  SparseCleanup( ) on it.                                                   */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Double SparseConvertFromCoordinate(int rowCount, int columnCount,
  long blockCount, uint8_t blockSize, SparseAttributes_t attributes,
  const int *row, const int *column, const double *data)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Convert from coordinate format arrays to a SparseMatrix_Float
 *  object, dropping out-of-range entries and summing duplicates.
 *
 *  @discussion For symmetric matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  @param rowCount (input) Number of rows in structure.
 *
 *  @param columnCount (input) Number of columns in structure.
 *
 *  @param blockCount (input) Number of blocks in matrix.
 *
 *  @param blockSize (input) Block size for data storage on both input and
 *  ouput.
 *
 *  @param attributes (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  @param row (input) Row indices of matrix structure.
 *
 *  @param column (input) Column indices of matrix structure.
 *
 *  @param data (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  @return A new SparseMatrix_Float object. When you are done with this
 *  matrix, release the memory that has been allocated by calling
 *  SparseCleanup( ) on it.                                                   */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Float SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributes_t attributes, const int *row,
  const int *column, const float *data)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Convert from coordinate format arrays to a SparseMatrix_Double
 *  object, dropping out-of-range entries and summing duplicates.
 *
 *  @discussion For symmetric matrices, entries are accepted in either triangle 
 *  (if they are in the "wrong" triangle as specified by attributes.triangle, 
 *  they are transposed, and if an entry is already present, are treated as 
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  @param rowCount (input) Number of rows in structure.
 *
 *  @param columnCount (input) Number of columns in structure.
 *
 *  @param blockCount (input) Number of blocks in matrix.
 *
 *  @param blockSize (input) Block size for data storage on both input and
 *  ouput.
 *
 *  @param attributes (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  @param row (input) Row indices of matrix structure.
 *
 *  @param column (input) Column indices of matrix structure.
 *
 *  @param data (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  @param storage (output) A block of memory of size at least:
 *
 *    48 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int)
 *      + blockCount*blockSize*blockSize*sizeof(double)
 *
 *  The returned structures .structure.columnStarts, .structure.rowIndices,
 *  and .data will point into this storage. You are responsible for managing
 *  the allocation and cleanup of this memory.
 *
 *  @param workspace (scratch) Workspace of size rowCount*sizeof(int).
 *
 *  @return A new SparseMatrix_Double object, using the memory you provided in
 *  the `storage` parameter.                                                  */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Double SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributes_t attributes, const int *row,
  const int *column, const double *data, void *storage, void *workspace)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Convert from coordinate format arrays to a SparseMatrix_Float
 *  object, dropping out-of-range entries and summing duplicates.
 *
 *  @discussion For symmetric matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  @param rowCount (input) Number of rows in structure.
 *
 *  @param columnCount (input) Number of columns in structure.
 *
 *  @param blockCount (input) Number of blocks in matrix.
 *
 *  @param blockSize (input) Block size for data storage on both input and
 *  ouput.
 *
 *  @param attributes (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  @param row (input) Row indices of matrix structure.
 *
 *  @param column (input) Column indices of matrix structure.
 *
 *  @param data (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  @param storage (output) A block of memory of size at least:
 *
 *    48 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int)
 *      + blockCount*blockSize*blockSize*sizeof(float)
 *
 *  The returned structures .structure.columnStarts, .structure.rowIndices,
 *  and .data will point into this storage. You are responsible for managing
 *  the allocation and cleanup of this memory.
 *
 *  @param workspace (scratch) Workspace of size rowCount*sizeof(int).
 *
 *  @return A new SparseMatrix_Float object, using the memory you provided in
 *  the `storage` parameter.                                                  */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Float SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributes_t attributes, const int *row,
  const int *column, const float *data, void *storage, void *workspace)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

#if defined __SPARSE_TYPES_H
/*! @group Conversions from opaque sparse matrix types
 *
 *  @discussion The older sparse headers on iOS and OS X (Sparse/BLAS.h) use
 *  a separate set of types that do not expose the internal storage of the
 *  sparse matrix. To assist in interoperation with the newer interfaces here,
 *  we provide a set of conversion functions from those types.                */

/*! @abstract Converts an opaque sparse_matrix_double object to a transparent
 *  SparseMatrix_Double object. When you are done with this matrix, release
 *  the memory that has been allocated by calling SparseCleanup( ) on it.
 *
 *  @param matrix The matrix to be converted.                                 */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Double SparseConvertFromOpaque(sparse_matrix_double matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Converts an opaque sparse_matrix_float object to a transparent
 *  SparseMatrix_Float object. When you are done with this matrix, release
 *  the memory that has been allocated by calling SparseCleanup( ) on it.
 *
 *  @param matrix The matrix to be converted.                                 */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Float SparseConvertFromOpaque(sparse_matrix_float matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );
#endif /* defined __SPARSE_TYPES_H */

/******************************************************************************
 *  @group Dense Matrices and Vectors
 ******************************************************************************/

/*! @abstract Contains a dense vector of double values.
 *
 *  @field count    Number of entries in the vector.
 *  @field data     The array of double values.                               */
typedef struct {
  int count;
  double *data;
} DenseVector_Double;

/*! @abstract Contains a dense vector of float values.
 *
 *  @field count    Number of entries in the vector.
 *  @field data     The array of float values.                                */
typedef struct {
  int count;
  float *data;
} DenseVector_Float;

/*! @abstract Contains a dense `rowCount` x `columnCount` matrix of double
 *            values stored in column-major order.
 *
 *  @field rowCount     Number of rows in the matrix.
 *  @field columnCount  Number of columns in the matrix.
 *  @field columnStride The column stride of the matrix.
 *  @field attributes   The attributes of the matrix, for example whether the
 *                      matrix is symmetrical or triangular.
 *  @field data         The array of double values in column-major order.     */
typedef struct {
  int rowCount;
  int columnCount;
  int columnStride;
  SparseAttributes_t attributes;
  double *data;
} DenseMatrix_Double;

/*! @abstract Contains a dense `rowCount` x `columnCount` matrix of float
 *            values stored in column-major order.
 *
 *  @field rowCount     Number of rows in the matrix.
 *  @field columnCount  Number of columns in the matrix.
 *  @field columnStride The column stride of the matrix.
 *  @field attributes   The attributes of the matrix, for example whether the
 *                      matrix is symmetrical or triangular.
 *  @field data         The array of float values in column-major order.      */
typedef struct {
  int rowCount;
  int columnCount;
  int columnStride;
  SparseAttributes_t attributes;
  float *data;
} DenseMatrix_Float;

/******************************************************************************
 *  @group Sparse Factorization Related Types
 ******************************************************************************/

/*! @abstract Status field for a factorization.
 *
 *  @constant SparseStatusOK              Factorization was successful.
 *  @constant SparseFactorizationFailed   Factorization failed due to a
 *                                        numerical issue.
 *  @constant SparseMatrixIsSingular      Factorization aborted as matrix is
 *                                        singular.
 *  @constant SparseInternalError         Factorization encountered an internal
 *                                        error (e.g. failed to allocate memory).
 *  @constant SparseParameterError        Error in user-supplied parameter.
 *  @constant SparseStatusReleased        Factorization object has been freed.
 */
SPARSE_ENUM(SparseStatus, int,
  SparseStatusOK            =  0,
  SparseFactorizationFailed = -1,
  SparseMatrixIsSingular    = -2,
  SparseInternalError       = -3,
  SparseParameterError      = -4,
  SparseStatusReleased      = -INT_MAX,
);

/*! @abstract Types of factorization than can be performed.
 *
 *  @constant SparseFactorizationCholesky
 *              Cholesky (LL^T) factorization.
 *  @constant SparseFactorizationLDLT
 *              Default LDL^T factorization (currently LDL^T with TPP).
 *  @constant SparseFactorizationLDLTUnpivoted
 *              Cholesky-like LDL^T with only 1x1 pivots and no pivoting.
 *  @constant SparseFactorizationLDLTSBK
 *              LDL^T with Supernode Bunch-Kaufman and static pivoting.
 *  @constant SparseFactorizationLDLTTPP
 *              LDL^T with full threshold partial pivoting.
 *  @constant SparseFactorizationQR
 *              QR factorization.
 *  @constant SparseFactorizationCholeskyAtA
 *              QR factorization without storing Q (equivalent to A^TA = R^T R).
 */
SPARSE_ENUM(SparseFactorization, uint8_t,
  SparseFactorizationCholesky = 0,
  SparseFactorizationLDLT = 1,
  SparseFactorizationLDLTUnpivoted = 2,
  SparseFactorizationLDLTSBK = 3,
  SparseFactorizationLDLTTPP = 4,
  SparseFactorizationQR = 40,
  SparseFactorizationCholeskyAtA = 41
);

/*! @abstract Control flags for matrix factorization.
 *
 *  @constant SparseDefaultControl  Use default values.
 */
SPARSE_ENUM(SparseControl, uint32_t,
  SparseDefaultControl = 0
);

/*! @abstract Specifies type of fill-reducing ordering.
 *
 *  @discussion The order in which variables are eliminated (i.e. the column/row ordering) in a
 *  sparse factorization makes a big difference to the size of the resulting factors and amount of
 *  work required to calculate them (it is probably the biggest single factor). Minimizing the size
 *  or work required is an NP-complete problem, so only heuristics are implemented in this library.
 *
 *  We note that AMD-based orderings tend to be fast and provide good quality for small matrices,
 *  whilst nested dissection based orderings (such as metis) are normally considerably slower to
 *  compute, but provide better quality orderings for larger problems, and expose more parallelism
 *  during the factorization. We recommend AMD is used unless the problem is very large (millions
 *  of rows and columns) or you will perform many repeated factorizations. If you are uncertain,
 *  try both and see which gives better performance for your usage.
 *
 *  The AMD and MeTiS orderings provide good orderings for symmetric matrices. They can be used
 *  for the QR factorizations, but this involves forming A^TA explicitly, which is expensive.
 *  COLAMD on the other hand finds an ordering for A^T A whilst only working with A. For this
 *  reason, COLAMD cannot be used for symmetric factorizations.
 *
 *  @constant SparseOrderDefault
 *              Default ordering (AMD for symmetric and COLAMD for unsymmetric
 *              factorizations, but this may change if better algorithms become
 *              available).
 *  @constant SparseOrderUser
 *              User-supplied ordering, or identity if options->order is NULL
 *  @constant SparseOrderAMD
 *              AMD ordering. Large overhead cost if used for QR-based
 *              factorization due to explicit formation of A^T A.
 *  @constant SparseOrderMetis
 *              MeTiS Nested Dissection ordering. Large overhead cost if used
 *              for QR-based factorization due to explicit formation of A^T A.
 *  @constant SparseOrderCOLAMD
 *              Column AMD ordering for A^T A. Not valid for symmetric
 *              factorizations (use AMD instead).                             */
SPARSE_ENUM(SparseOrder, uint8_t,
  SparseOrderDefault = 0,
  SparseOrderUser = 1,
  SparseOrderAMD = 2,
  SparseOrderMetis = 3,
  SparseOrderCOLAMD = 4,
);

/*! @abstract Specifies type of scaling to be performed.
 *
 *  @constant SparseScalingDefault
 *              Default scaling (at present EquilibriationInf if LDL^T, or no
 *              scaling if Cholesky).
 *  @constant SparseScalingUser
 *              User scaling if options.scaling is non-NULL, otherwise no
 *              scaling.
 *  @constant SparseScalingEquilibriationInf
 *              Norm equilibriation scaling using inf norm.                   */
SPARSE_ENUM(SparseScaling, uint8_t,
  SparseScalingDefault = 0,
  SparseScalingUser = 1,
  SparseScalingEquilibriationInf = 2,
);

/*! @typedef SparseSymbolicFactorOptions
 *  @abstract Options that affect the symbolic stage of a sparse factorization.
 *
 *  @field control
 *    Flags controlling the computation.
 *
 *  @field orderMethod
 *    Ordering algorithm to use.
 *
 *  @field order    User-supplied array for ordering.
 *    Either NULL or a pointer to a row permutation that reduces fill in the
 *    matrix being factored.
 *    If `orderMethod` is `SparseOrderUser`, and this pointer is NULL, the
 *      original matrix ordering is used.
 *    If `orderMethod` is `SparseOrderUser`, and this pointer is non-NULL,
 *      the user-provided permutation is used to order the matrix before
 *      factorization.
 *    If `orderMethod` is not `SparseOrderUser`, the factor function will
 *      compute its own fill reducing ordering.
 *    If this pointer is non-NULL, the computed permutation will be returned in
 *      the array.
 *
 *  @field ignoreRowsAndColumns  Ignore rows and columns listed in this array.
 *    In some cases it is useful to ignore specified rows and columns,
 *    if this array is not NULL, it provides a list of rows and columns to
 *    ignore, terminated by a negative index.
 *    Note that this the row and column indices are for the actual matrix, not
 *    of its block structure, so 0 indicates the first row, not the first
 *    blockSize rows.
 *    In the symmetric case (Cholesky, LDL^T) each entry indicates that the
 *    matching row AND column should be ignored.
 *    In the unsymmetric case (QR, Cholesky A^TA) an index i<m indicates that
 *    row m should be ignored and an index i>=m indicates that column (i-m)
 *    should be ignored (where m is the number of rows in A,
 *    i.e. m=A.structure.rowCount*A.blockSize if A is not transposed, or
 *    m=A.structure.columnCount*A.blockSize if A is transposed).
 *
 *  \@callback malloc Function to use for allocation of internal memory
 *    \@discussion Memory will be freed through the free() callback. If this
 *      function pointer is NULL, the system malloc() will be used.
 *    \@param size Size of space to allocate in bytes.
 *    \@result Pointer to newly allocated memory, or NULL if allocation failed.
 *      The returned pointer must be 16-byte aligned (this requirement is
 *      satisfied by the system malloc()).
 *
 *  \@callback free Function to use to free memory allocated by malloc() callback.
 *    @discussion If this function pointer is NULL, the system free() will be
 *      used.
 *    \@param pointer Pointer to memory to be freed.
 *
 *  \@callback reportError Function to use to report parameter errors.
 *    \@param message
 *    \@discussion If NULL, errors are logged via <os/log.h> and execution is
 *      halted via __builtin_trap().  If non-NULL, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).            */
typedef struct {
  SparseControl_t control;
  SparseOrder_t orderMethod;
  int * _Nullable order;
  int *_Nullable ignoreRowsAndColumns;
  void * _Nullable(* _Nonnull malloc)(size_t size);
  void (* _Nonnull free)(void * _Nullable pointer);
  void (* _Nullable reportError)(const char *message);
} SparseSymbolicFactorOptions;

/*! @abstract Options that affect the numerical stage of a sparse factorization.
 *
 *  @field control
 *    Flags controlling the computation.
 *
 *  @field scalingMethod
 *    Scaling method to use.
 *
 *  @field scaling      User-supplied array for scaling.
 *    Either NULL or a pointer to an array of real values with length greater
 *    than or equal to the size of the matrix being factored. The type of the
 *    array values is the element type of the matrix.
 *    If `scalingMethod` is `SparseScalingUser`, and this pointer is NULL, no
 *      scaling is applied.
 *    If `scalingMethod` is `SparseScalingUser`, and this pointer is non-NULL,
 *      the user-provided array is used to scale the matrix before factorization.
 *    If `scalingMethod` is not `SparseScalingUser`, the factor function will
 *      compute its own scaling.
 *    If this pointer is non-NULL, the computed scaling will be returned in the
 *      array.
 *
 *  @field pivotTolerance
 *    Pivot tolerance used by threshold partial pivoting.
 *    Clamped to range [0,0.5].
 *
 *  @field zeroTolerance
 *    Zero tolerance used by some pivoting modes.
 *    Values less than zeroTolerance in absolute value will be treated as zero.
 */
typedef struct {
  SparseControl_t control;
  SparseScaling_t scalingMethod;
  void * _Nullable scaling;
  double pivotTolerance;
  double zeroTolerance;
} SparseNumericFactorOptions;

/*! @abstract A semi-opaque type representing symbolic matrix factorization.
 *
 *  @discussion Represents a symbolic matrix factorization (i.e. the pattern of
 *              the factors without the values). A single symbolic factorization
 *              may be the basis for multiple numerical factorizations of
 *              matrices with the same pattern but different values non-zero
 *              values.
 *
 *              Use the `SparseCleanup` function to free resources held by these
 *              objects. The internal factorization pointer is refence counted,
 *              so it is safe to destroy this object even if numeric
 *              factorizations exist that still depend on it.
 *
 *  @field status
 *    Indicates status of factorization object.
 *
 *  @field type
 *    Type fo factorization this represents.
 *
 *  @field rowCount
 *    Copy of field from SparseMatrixStructure passed to SparseFactor() call
 *    used to construct this symbolic factorization.
 *
 *  @field columnCount
 *    Copy of field from SparseMatrixStructure passed to SparseFactor() call
 *    used to construct this symbolic factorization.
 *
 *  @field attributes
 *    Copy of field from SparseMatrixStructure passed to SparseFactor() call
 *    used to construct this symbolic factorization.
 *
 *  @field blockSize
 *    Copy of field from SparseMatrixStructure passed to SparseFactor() call
 *    used to construct this symbolic factorization.
 *
 *  @field factorization
 *    Pointer to private internal representation of symbolic factor.
 *
 *  @field workspaceSize_Float
 *    Size, in bytes, of workspace required to perform numerical factorization
 *    in float.
 *
 *  @field workspaceSize_Double
 *    Size, in bytes, of workspace required to perform numerical factorization
 *    in double.
 *
 *  @field factorSize_Float
 *    Minimum size, in bytes, required to store numerical factors in float.
 *    If numerical pivoting requires a pivot to be delayed, the actual size
 *    required may be larger.
 *
 *  @field factorSize_Double
 *    Minimum size, in bytes, required to store numerical factors in double.
 *    If numerical pivoting requires a pivot to be delayed, the actual size
 *    required may be larger.                                                 */
typedef struct {
  SparseStatus_t status;
  int rowCount;
  int columnCount;
  SparseAttributes_t attributes;
  uint8_t blockSize;
  SparseFactorization_t type;
  void *_Nullable factorization;
  size_t workspaceSize_Float;
  size_t workspaceSize_Double;
  size_t factorSize_Float;
  size_t factorSize_Double;
} SparseOpaqueSymbolicFactorization;

/*! @abstract A semi-opaque type representing a matrix factorization in double.
 *
 *  @discussion Use the `SparseCleanup` function to free resources held
 *  by these objects.
 *
 *  The object can be in one of the following states:
 *  1) Something went wrong with symbolic factorization, nothing is valid.
 *     - indicated by .symbolicFactorization.status < 0
 *  2) Symbolic factorization was good, but failed in numeric factorization
 *     initialization.
 *     - indicated by .symbolicFactorization.status >= 0 && .status < 0 &&
 *                    .numericFactorization == NULL
 *     - symbolic factorization may be used for future calls.
 *  3) Symbolic factorization was good, factor allocated/initialized correctly,
 *     but numeric factorization failed
 *     e.g. a Cholesky factorization of an indefinite matrix was attempted.
 *     - indicated by .symbolicFactorization.status >= 0 && .status < 0 &&
 *                    .numericFactorization not NULL
 *     - user may pass this object to SparseRefactor_Double() with a modified
 *       matrix
 *  4) Symbolic and numeric factorizations are both good
 *     - indicated by .status >= 0
 *
 * @field status
 *    Indicates status of factorization object.
 *
 * @field attributes
 *    Flags associated with this factorization object. In particular, transpose
 *    field indicates whether object is considered to be factorization of A or
 *    A^T.
 *
 * @field symbolicFactorization
 *    Symbolic Factorization upon which this Numeric Factorization depends.
 *
 * @field userFactorStorage
 *    Flag that indicates if user provided storage backing this object. If
 *    true, then factor storage must be freed by the user once all references
 *    are finished with (though any additional storage allocated due to pivoting
 *    will still be freed by SparseCleanup()).
 *
 * @field numericFactorization
 *    Pointer to private internal representation of numeric factor.
 *
 * @field solveWorkspaceRequiredStatic
 *    The required size of workspace, in bytes) for a call to SparseSolve is
 *    solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS
 *    where nrhs is the number of right-hand side vectors.
 *
 * @field solveWorkspaceRequiredPerRHS
 *    The required size of workspace, in bytes) for a call to SparseSolve is
 *    solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS
 *    where nrhs is the number of right-hand side vectors.                    */
typedef struct {
  SparseStatus_t status;
  SparseAttributes_t attributes;
  SparseOpaqueSymbolicFactorization symbolicFactorization;
  bool userFactorStorage;
  void *_Nullable numericFactorization;
  size_t solveWorkspaceRequiredStatic;
  size_t solveWorkspaceRequiredPerRHS;
} SparseOpaqueFactorization_Double;

/*! @abstract A semi-opaque type representing a matrix factorization in float.
 *
 *  @discussion Use the `SparseCleanup` function to free resources held
 *  by these objects.
 *
 *  The object can be in one of the following states:
 *  1) Something went wrong with symbolic factorization, nothing is valid.
 *     - indicated by .symbolicFactorization.status < 0
 *  2) Symbolic factorization was good, but failed in numeric factorization
 *     initialization.
 *     - indicated by .symbolicFactorization.status >= 0 && .status < 0 &&
 *                    .numericFactorization == NULL
 *     - symbolic factorization may be used for future calls.
 *  3) Symbolic factorization was good, factor allocated/initialized correctly,
 *     but numeric factorization failed
 *     e.g. a Cholesky factorization of an indefinite matrix was attempted.
 *     - indicated by .symbolicFactorization.status >= 0 && .status < 0 &&
 *                    .numericFactorization not NULL
 *     - user may pass this object to SparseRefactor_Double() with a modified
 *       matrix
 *  4) Symbolic and numeric factorizations are both good
 *     - indicated by .status >= 0
 *
 * @field status
 *    Indicates status of factorization object.
 *
 * @field attributes
 *    Flags associated with this factorization object. In particular, transpose
 *    field indicates whether object is considered to be factorization of A or
 *    A^T.
 *
 * @field symbolicFactorization
 *    Symbolic Factorization upon which this Numeric Factorization depends.
 *
 * @field userFactorStorage
 *    Flag that indicates if user provided storage backing this object. If
 *    true, then factor storage must be freed by the user once all references
 *    are finished with (though any additional storage allocated due to pivoting
 *    will still be freed by SparseCleanup()).
 *
 * @field numericFactorization
 *    Pointer to private internal representation of numeric factor.
 *
 * @field solveWorkspaceRequiredStatic
 *    The required size of workspace, in bytes) for a call to SparseSolve is
 *    solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS
 *    where nrhs is the number of right-hand side vectors.
 *
 * @field solveWorkspaceRequiredPerRHS
 *    The required size of workspace, in bytes) for a call to SparseSolve is
 *    solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS
 *    where nrhs is the number of right-hand side vectors.                    */
typedef struct {
  SparseStatus_t status;
  SparseAttributes_t attributes;
  SparseOpaqueSymbolicFactorization symbolicFactorization;
  bool userFactorStorage;
  void *_Nullable numericFactorization;
  size_t solveWorkspaceRequiredStatic;
  size_t solveWorkspaceRequiredPerRHS;
} SparseOpaqueFactorization_Float;

/*******************************************************************************
 * @group Sub-factor Types
 ******************************************************************************/

/*! @abstract Types of sub-factor object.
 *
 *  @constant SparseSubfactorInvalid
 *    Invalid subfactor (requested type not compatible with supplied factorization
 *    or already destroyed).
 *  @constant SparseSubfactorP
 *    Permutation subfactor, valid for all factorization types.
 *  @constant SparseSubfactorS
 *    Diagonal scaling subfactor, valid for Cholesky and LDL^T only.
 *  @constant SparseSubfactorL
 *    L factor subfactor, valid for Cholesky and LDL^T only.
 *  @constant SparseSubfactorD
 *    D factor subfactor, valid for LDL^T only.
 *  @constant SparseSubfactorPLPS
 *    Half-solve subfactor, valid for Cholesky and LDL^T only.
 *    Corresponds to PLP' on forward (non-transpose) solve, and
 *    corresponds to PLDP' on backward (transpose) solve (D=I for Chokesky).
 *  @constant SparseSubfactorQ
 *    Q factor subfactor, valid for QR only.
 *  @constant SparseSubfactorR
 *    R factor subfactor, valid for QR and CholeskyAtA only.
 *  @constant SparseSubfactorRP
 *    Half-solve subfactor, valid for QR and CholeskyAtA only.                   */
SPARSE_ENUM(SparseSubfactor, uint8_t,
        SparseSubfactorInvalid = 0,
        SparseSubfactorP = 1,
        SparseSubfactorS = 2,
        SparseSubfactorL = 3,
        SparseSubfactorD = 4,
        SparseSubfactorPLPS = 5,
        SparseSubfactorQ = 6,
        SparseSubfactorR = 7,
        SparseSubfactorRP = 8
        );

/*! @abstract Represents a sub-factor of the factorization (eg  L from LDL^T).
 *
 *  @field attributes
 *    Attributes of subfactor. Notably transpose indicates whether it should be
 *    considered as the transpose of its underlying contents (e.g. should it
 *    count as L or L^T if .contents=SparseSubfactorL).
 *  @field contents
 *    Subfactor this represents, e.g. L or Q.
 *  @field factor
 *    Underlying factorization this subfactor is part of.
 *  @field workspaceRequiredStatic
 *    The size of the workspace, in bytes, required to perform SparseMultiply()
 *    or SparseSolve() with this subfactor is given by the expression:
 *    workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs
 *    where nrhs is the number of right-hand side vectors.
 *  @field workspaceRequiredPerRHS
 *    The size of the workspace, in bytes, required to perform SparseMultiply()
 *    or SparseSolve() with this subfactor is given by the expression:
 *    workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs
 *    where nrhs is the number of right-hand side vectors.
 */
typedef struct {
  SparseAttributes_t attributes;
  SparseSubfactor_t contents;
  SparseOpaqueFactorization_Double factor;
  size_t workspaceRequiredStatic;
  size_t workspaceRequiredPerRHS;
} SparseOpaqueSubfactor_Double;

/*! @abstract Represents a sub-factor of the factorization (eg  L from LDL^T).
 *
 *  @field attributes
 *    Attributes of subfactor. Notably transpose indicates whether it should be
 *    considered as the transpose of its underlying contents (e.g. should it
 *    count as L or L^T if .contents=SparseSubfactorL).
 *  @field contents
 *    Subfactor this represents, e.g. L or Q.
 *  @field factor
 *    Underlying factorization this subfactor is part of.
 *  @field workspaceRequiredStatic
 *    The size of the workspace, in bytes, required to perform SparseMultiply()
 *    or SparseSolve() with this subfactor is given by the expression:
 *    workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs
 *    where nrhs is the number of right-hand side vectors.
 *  @field workspaceRequiredPerRHS
 *    The size of the workspace, in bytes, required to perform SparseMultiply()
 *    or SparseSolve() with this subfactor is given by the expression:
 *    workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs
 *    where nrhs is the number of right-hand side vectors.
 */
typedef struct {
  SparseAttributes_t attributes;
  SparseSubfactor_t contents;
  SparseOpaqueFactorization_Float factor;
  size_t workspaceRequiredStatic;
  size_t workspaceRequiredPerRHS;
} SparseOpaqueSubfactor_Float;

/******************************************************************************
 *  @group Matrix and Vector Operations (Sparse BLAS Wrappers)
 ******************************************************************************/

/**** Multiplication **********************************************************/

/*! @abstract Performs the multiplication Y = AX for double values
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication Y = AX for float values.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication Y = alpha * AX for double values
 *
 *  @param alpha (input) scale to apply to the result.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with alpha * AX.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(double alpha, SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication Y = alpha * AX for float values.
 *
 *  @param alpha (input) scale to apply to the result.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with alpha * AX.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(float alpha, SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication y = Ax for double values
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication y = Ax for float values
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication y = alpha * Ax for double values
 *
 *  @param alpha (input) scale to apply to the result.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(double alpha, SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Performs the multiplication y = alpha * Ax for float values.
 *
 *  @param alpha (input) scale to apply to the result.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(float alpha, SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/**** Multipy-Add *************************************************************/

/*! @abstract Y += AX for double values
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Y += AX for float values.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Y += alpha * AX for double values
 *
 *  @param alpha (input) scale to apply to the product of A and X.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with alpha * AX.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(double alpha, SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Y += alpha * AX for float values.
 *
 *  @param alpha (input) scale to apply to the product of A and X.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param X (input) dense matrix. Inner dimensions of A and X must match.
 *
 *  @param Y (output) dense matrix. Dimensions must match the outer dimensions
 *  of A and X. Overwritten with alpha * AX.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(float alpha, SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract y += Ax for double values
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract y += Ax for float values.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract y += alpha * Ax for double values
 *
 *  @param alpha (input) scale to apply to the product of A and x.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(double alpha, SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract y += alpha * Ax for float values.
 *
 *  @param alpha (input) scale to apply to the product of A and x.
 *
 *  @param A (input) sparse matrix.
 *
 *  @param x (input) dense vector.
 *
 *  @param y (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(float alpha, SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/******************************************************************************
 *  @group Transposition
 ******************************************************************************/

/*! @abstract Returns a transposed copy of the specified SparseMatrix_Double.
 *
 *  @discussion Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  @param Matrix The matrix to transpose.
 *
 *  @returns A copy of matrix with A.structure.attributes.transpose flipped.  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseMatrix_Double SparseGetTranspose(SparseMatrix_Double Matrix);

/*! @abstract Returns a transposed copy of the specified SparseMatrix_Float.
 *
 *  @discussion Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  @param Matrix The matrix to transpose.
 *
 *  @returns A copy of matrix with matrix.structure.attributes.transpose bit
 *           flipped.                                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseMatrix_Float SparseGetTranspose(SparseMatrix_Float Matrix);

/*! @abstract Returns a transposed, reference-counted copy of a factorization.
 *
 *  @param Factor The factorization to transpose.
 *
 *  @returns A matrix factorization of A^T, where the original was of A. As
 *           this is reference counted, it must be freed through a call to
 *           SparseCleanup() once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseGetTranspose(SparseOpaqueFactorization_Double Factor);

/*! @abstract Returns a transposed, reference-counted copy of a factorization.
 *
 *  @param Factor The factorization to transpose.
 *
 *  @returns A matrix factorization of A^T, where the original was of A. As
 *           this is reference counted, it must be freed through a call to
 *           SparseCleanup() once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseGetTranspose(SparseOpaqueFactorization_Float Factor);

/*! @abstract Returns a transposed, reference-counted copy of a subfactor.
 *
 *  @param Subfactor The object to transpose.
 *
 *  @returns A subfactor equivalent to the transpose of the one provided. As
 *           this is reference counted, it must be freed through a call to
 *           SparseCleanup() once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Double SparseGetTranspose(SparseOpaqueSubfactor_Double Subfactor);

/*! @abstract Returns a transposed, reference-counted copy of a subfactor.
 *
 *  @param Subfactor The object to transpose.
 *
 *  @returns A subfactor equivalent to the transpose of the one provided. As
 *           this is reference counted, it must be freed through a call to
 *           SparseCleanup() once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Float SparseGetTranspose(SparseOpaqueSubfactor_Float Subfactor);

/******************************************************************************
 *  @group Sparse Factor Functions
 ******************************************************************************/

/**** All-in-one Sparse Factor Functions **************************************/

/*! @abstract Returns the specified factorization of a sparse matrix of double
 *            values.
 *
 *  @param type The type of factorization to perform.
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseFactorization_t type, SparseMatrix_Double Matrix);

/*! @abstract Returns the specified factorization of a sparse matrix of float
 *            values.
 *
 *  @param type The type of factorization to perform.
 *
 *  @param Matrix The matrix to factorize.                                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseFactorization_t type, SparseMatrix_Float Matrix);

/*! @abstract Returns the specified factorization of a sparse matrix of double
 *            values, using the specified options.
 *
 *  @param type The type of factorization to perform.
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @param sfoptions Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseFactorization_t type, SparseMatrix_Double Matrix, SparseSymbolicFactorOptions sfoptions, SparseNumericFactorOptions nfoptions);

/*! @abstract Returns the specified factorization of a sparse matrix of float
 *            values, using the specified options.
 *
 *  @param type The type of factorization to perform.
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @param sfoptions Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseFactorization_t type, SparseMatrix_Float Matrix, SparseSymbolicFactorOptions sfoptions, SparseNumericFactorOptions nfoptions);

/**** Sparse Factor Functions using pre-calculated symbolic factors ***********/

/*! @abstract Returns the factorization of a sparse matrix of double values
 *            corresponding to the supplied symbolic factorization.
 *
 *  @param SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form SymbolicFactor = SparseFactor(Matrix.structure).
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Double Matrix);

/*! @abstract Returns the factorization of a sparse matrix of float values
 *            corresponding to the supplied symbolic factorization.
 *
 *  @param SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form SymbolicFactor = SparseFactor(Matrix.structure).
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Float Matrix);

/*! @abstract Returns the factorization of a sparse matrix of double values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options.
 *
 *  @param SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form SymbolicFactor = SparseFactor(Matrix.structure).
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Double Matrix, SparseNumericFactorOptions nfoptions);

/*! @abstract Returns the factorization of a sparse matrix of float values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options.
 *
 *  @param SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form SymbolicFactor = SparseFactor(Matrix.structure).
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Float Matrix, SparseNumericFactorOptions nfoptions);

/**** Sparse Factor Functions with user-defined workspace *********************/

/*! @abstract Returns the factorization of a sparse matrix of double values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options and without any internal memory allocations.
 *
 *  @discussion Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a sfoptions.malloc() function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if sfoptions.malloc() returns NULL the
 *  factorization will abort immediately.
 *
 *  @param SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form SymbolicFactor = SparseFactor(Matrix.structure).
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @param factorStorage A pointer to space used to store the factorization
 *         of size at least SymbolicFactor.factorSize_Double bytes. This storage
 *         should not be altered by the user during the lifetime of the return
 *         value. This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *
 *  @param workspace A pointer to a workspace of size at least
 *         SymbolicFactor.workspaceSize_Double bytes. This workspace may be
 *         reused or destroyed by the user as soon as the function returns.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(
  SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Double Matrix,
  SparseNumericFactorOptions nfoptions, void *_Nullable factorStorage,
  void *_Nullable workspace);

/*! @abstract Returns the factorization of a sparse matrix of float values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options and without any internal memory allocations.
 *
 *  @discussion Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a sfoptions.malloc() function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if sfoptions.malloc() returns NULL the
 *  factorization will abort immediately.
 *
 *  @param SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form SymbolicFactor = SparseFactor(Matrix.structure).
 *
 *  @param Matrix The matrix to factorize.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @param factorStorage A pointer to space used to store the factorization
 *         of size at least SymbolicFactor.factorSize_Float bytes. This storage
 *         should not be altered by the user during the lifetime of the return
 *         value. This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *
 *  @param workspace A pointer to a workspace of size at least
 *         SymbolicFactor.workspaceSize_Float bytes. This workspace may be
 *         reused or destroyed by the user as soon as the function returns.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *
 *  @returns Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(
  SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Float Matrix,
  SparseNumericFactorOptions nfoptions, void *_Nullable factorStorage,
  void *_Nullable workspace);

/******************************************************************************
 *  @group Sparse Direct Solve Functions (DenseMatrix)
 ******************************************************************************/

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param XB On entry, the right-hand sides B. On return, the solution vectors
 *         X. If A has dimension m x n, then XB must have dimension k x nrhs,
 *         where k=max(m,n) and nrhs is the number of right-hand sides to find
 *         solutions for.                                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored, DenseMatrix_Double XB);

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param XB On entry, the right-hand sides B. On return, the solution vectors
 *         X. If A has dimension m x n, then XB must have dimension k x nrhs,
 *         where k=max(m,n) and nrhs is the number of right-hand sides to find
 *         solutions for.                                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float XB);

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X Matrix in which to return solutions. If A has dimension m x n, and
 *         B has dimension m x nrhs, then X must have dimension n x nrhs.     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored, DenseMatrix_Double B, DenseMatrix_Double X);

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X Matrix in which to return solutions. If A has dimension m x n, and
 *         B has dimension m x nrhs, then X must have dimension n x nrhs.     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float B, DenseMatrix_Float X);

/**** Solving Systems with User Defined Workspace *****************************/

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, in place, and without any internal memory allocations.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param XB On entry, the right-hand sides B. On return, the solution vectors
 *         X. If A has dimension m x n, then XB must have dimension k x nrhs,
 *         where k=max(m,n) and nrhs is the number of right-hand sides to find
 *         solutions for.
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseMatrix_Double XB, void *workspace);

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, in place, and without any internal memory allocations.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param XB On entry, the right-hand sides B. On return, the solution vectors
 *         X. If A has dimension m x n, then XB must have dimension k x nrhs,
 *         where k=max(m,n) and nrhs is the number of right-hand sides to find
 *         solutions for.
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float XB,
  void *workspace);

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, and without any internal memory allocations.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X Matrix in which to return solutions. If A has dimension m x n, and
 *         B has dimension m x nrhs, then X must have dimension n x nrhs.
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseMatrix_Double X, DenseMatrix_Double B, void *workspace);

/*! @abstract Solves the system AX=B for X, using the supplied factorization
 *            of A, and without any internal memory allocations.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || X ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_X || AX - B ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAX=B.
 *
 *  @param Factored A factorization of A.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X Matrix in which to return solutions. If A has dimension m x n, and
 *         B has dimension m x nrhs, then X must have dimension n x nrhs.
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float X,
  DenseMatrix_Float B, void *workspace);

/******************************************************************************
 *  @group Sparse Direct Solve Functions (DenseVector)
 ******************************************************************************/

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param xb On entry, the right-hand side b. On return, the solution vector
 *         x. If A has dimension m x n, then xb must have length k, where
 *         k=max(m,n).                                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double xb);

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param xb On entry, the right-hand side b. On return, the solution vector
 *         x. If A has dimension m x n, then xb must have length k, where
 *         k=max(m,n).                                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float xb);

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x Vector in which to return solution. If A has dimension m x n, then
 *         x must have length n.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double b, DenseVector_Double x);

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x Vector in which to return solution. If A has dimension m x n, then
 *         x must have length n.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float b,
  DenseVector_Float x);

/**** Solving Systems with User Defined Workspace *****************************/

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param xb On entry, the right-hand side b. On return, the solution vector
 *         x. If A has dimension m x n, then xb must have length k, where
 *         k=max(m,n).
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double xb, void *workspace);

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param xb On entry, the right-hand side b. On return, the solution vector
 *         x. If A has dimension m x n, then xb must have length k, where
 *         k=max(m,n).
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float xb,
                 void *workspace);

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x Vector in which to return solution. If A has dimension m x n, then
 *         x must have length n.
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double x, DenseVector_Double b, void *workspace);

/*! @abstract Solves the system Ax=b for x, using the supplied factorization
 *            of A, in place.
 *
 *  @discussion If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm || x ||_2 is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution arg min_x || Ax - b ||_2 is returned.
 *  In the case of a factorization of type=SparseCholeskyAtA, the factorization
 *  is in fact of A^T A, so the solution returned is for the system A^TAx=b.
 *
 *  @param Factored A factorization of A.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x Vector in which to return solution. If A has dimension m x n, then
 *         x must have length n.
 *
 *  @param workspace Scratch space of size
 *         Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float x,
  DenseVector_Float b, void *workspace);

/******************************************************************************
 *  @group Advanced Solving Functions
 ******************************************************************************/

/**** Symbolic Factorization Functions ****************************************/

/*! @abstract Returns a symbolic factorization of the requested type for a
 *            matrix with the given structure.
 *
 *  @discussion The resulting symbolic factorization may be used for multiple
 *  numerical factorizations with different numerical values but the same
 *  non-zero structure.
 *
 *  @param type The type of factorization to perform.
 *
 *  @param Matrix The structure of the sparse matrix to be factorized.
 *
 *  @returns The requested symbolic factorization of Matrix.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
  SparseMatrixStructure Matrix);

/*! @abstract Returns a symbolic factorization of the requested type for a
 *            matrix with the given structure, with the supplied options.
 *
 *  @discussion The resulting symbolic factorization may be used for multiple
 *  numerical factorizations with different numerical values but the same
 *  non-zero structure.
 *
 *  @param type The type of factorization to perform.
 *
 *  @param Matrix The structure of the sparse matrix to be factorized.
 *
 *  @param sfoptions Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  @returns The requested symbolic factorization of Matrix.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
  SparseMatrixStructure Matrix, SparseSymbolicFactorOptions sfoptions);

/**** Symbolic Refactor Functions *********************************************/


/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix, using different options.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters. */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization,
  SparseNumericFactorOptions nfoptions);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix, using different options.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters. */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization,
  SparseNumericFactorOptions nfoptions);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix, without any internal
 *            allocations.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a sfoptions.malloc() function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if sfoptions.malloc() returns NULL the
 *  factorization will abort immediately.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization, void *workspace);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix, without any internal
 *            allocations.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a sfoptions.malloc() function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if sfoptions.malloc() returns NULL the
 *  factorization will abort immediately.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization, void *workspace);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix, using updated options and
 *            without any internal allocations.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.

 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a sfoptions.malloc() function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if sfoptions.malloc() returns NULL the
 *  factorization will abort immediately.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @param workspace A pointer to a workspace of size at least
 *         Factorization->symbolicFactorization.workspaceSize_Double bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.                                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization,
  SparseNumericFactorOptions nfoptions, void *workspace);

/*! @abstract Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix, using updated options and
 *            without any internal allocations.
 *
 *  @discussion Matrix must have the same non-zero structure as that used for
 *  the original factorization.

 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to SparseFactor() as the argument
 *  factorStorage. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a sfoptions.malloc() function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if sfoptions.malloc() returns NULL the
 *  factorization will abort immediately.
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  SparseGetTranspose() or SparseCreateSubfactor() that have not been destroyed
 *  through a call to SparseCleanup()), then new storage will be allocated
 *  regardless.
 *
 *  @param Matrix The matrix to be factorized.
 *
 *  @param Factorization The factorization to be updated.
 *
 *  @param nfoptions Numeric factor options, for example pivoting parameters.
 *
 *  @param workspace A pointer to a workspace of size at least
 *         Factorization->symbolicFactorization.workspaceSize_Float bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.                                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization,
  SparseNumericFactorOptions nfoptions, void *workspace);

/******************************************************************************
 *  @group Extracting Sub-factors of Factors
 ******************************************************************************/

/*! @abstract Returns an opaque object representing a sub-factor of a
 *            factorization.
 *
 *  @discussion Here the term "sub-factor" is used to mean one or more parts of
 *  the whole factorization. For example, just the Q factor from A=QRP.
 *  The returned object is a wrapper around the orignal factorization, and does
 *  not actually perform any extraction (sub-factors are stored in non-standard
 *  formats that exploit implicit structure for efficiency, and formation of the
 *  sub-factor explicitly can be expensive). It is intended to be used as an
 *  argument to SparseMultiply() and SparseSolve() functions only.
 *  As Factor is contained in the returned object, its underlying reference
 *  count in incremented, and the returned object must hence be destroyed
 *  through a call to SparseCleanup() to prevent a memory leak (however it is
 *  safe to call SparseCleanup() on the original factorization whilst this
 *  object is still being used).
 *
 *  @param subfactor The sub-factor the new object shuold represent.
 *
 *  @param Factor The factorization to extract the sub-factor from.
 *
 *  @returns Object representing the requested sub-factor. Must be cleaned up
 *  by a call to SparseCleanup() once it is no longer required.               */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Double SparseCreateSubfactor(SparseSubfactor_t subfactor,
  SparseOpaqueFactorization_Double Factor);

/*! @abstract Returns an opaque object representing a sub-factor of a
 *            factorization.
 *
 *  @discussion Here the term "sub-factor" is used to mean one or more parts of
 *  the whole factorization. For example, just the Q factor from A=QRP.
 *  The returned object is a wrapper around the orignal factorization, and does
 *  not actually perform any extraction (sub-factors are stored in non-standard
 *  formats that exploit implicit structure for efficiency, and formation of the
 *  sub-factor explicitly can be expensive). It is intended to be used as an
 *  argument to SparseMultiply() and SparseSolve() functions only.
 *  As Factor is contained in the returned object, its underlying reference
 *  count in incremented, and the returned object must hence be destroyed
 *  through a call to SparseCleanup() to prevent a memory leak (however it is
 *  safe to call SparseCleanup() on the original factorization whilst this
 *  object is still being used).
 *
 *  @param subfactor The sub-factor the new object shuold represent.
 *
 *  @param Factor The factorization to extract the sub-factor from.
 *
 *  @returns Object representing the requested sub-factor. Must be cleaned up
 *  by a call to SparseCleanup() once it is no longer required.               */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Float SparseCreateSubfactor(SparseSubfactor_t subfactor,
  SparseOpaqueFactorization_Float Factor);

/******************************************************************************
 *  @group Sub-factor Multiplication and Solve Functions
 ******************************************************************************/

/**** Matrix solve functions **************************************************/

/*! @abstract Solve the equation Subfactor * X = B for the matrix X, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XB (input/output) On input, the matrix B. On return it is overwritten
 *         with the matrix X. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         sides. If m != n, then only the first min(m,n) entries are used for
 *         input or output as approriate.                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XB);

/*! @abstract Solve the equation Subfactor * X = B for the matrix X, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XB (input/output) On input, the matrix B. On return it is overwritten
 *         with the matrix X. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         sides. If m != n, then only the first min(m,n) entries are used for
 *         input or output as approriate.                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XB);

/*! @abstract Solve the equation Subfactor * X = B for the matrix X.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by SparseCreateSubfactor().
 *
 *  @param B (input) The right-hand sides B. If Subfactor is m x n, then B must
 *         have dimension m x nrhs, where nrhs is the number of right-hand
 *         sides.
 *
 *  @param X (output) The solutions X. If Subfactor is m x n, and B is m x nrhs,
 *         then X must have dimension n x nrhs.                               */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double B,
  DenseMatrix_Double X);

/*! @abstract Solve the equation Subfactor * X = B for the matrix X.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by SparseCreateSubfactor().
 *
 *  @param B (input) The right-hand sides B. If Subfactor is m x n, then B must
 *         have dimension m x nrhs, where nrhs is the number of right-hand
 *         sides.
 *
 *  @param X (output) The solutions X. If Subfactor is m x n, and B is m x nrhs,
 *         then X must have dimension n x nrhs.                               */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float B,
  DenseMatrix_Float X);

/**** Matrix solve functions with user-supplied workspace *********************/

/*! @abstract Solve the equation Subfactor * X = B for the matrix X, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XB (input/output) On input, the matrix B. On return it is overwritten
 *         with the matrix X. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         sides. If m != n, then only the first min(m,n) entries are used for
 *         input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XB,
  void *workspace);

/*! @abstract Solve the equation Subfactor * X = B for the matrix X, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XB (input/output) On input, the matrix B. On return it is overwritten
 *         with the matrix X. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         sides. If m != n, then only the first min(m,n) entries are used for
 *         input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XB,
  void *workspace);

/*! @abstract Solve the equation Subfactor * X = B for the matrix X.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param B (input) The right-hand sides B. If Subfactor is m x n, then B must
 *         have dimension m x nrhs, where nrhs is the number of right-hand
 *         sides.
 *
 *  @param X (output) The solutions X. If Subfactor is m x n, and B is m x nrhs,
 *         then X must have dimension n x nrhs.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double B,
  DenseMatrix_Double X, void *workspace);

/*! @abstract Solve the equation Subfactor * X = B for the matrix X.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param B (input) The right-hand sides B. If Subfactor is m x n, then B must
 *         have dimension m x nrhs, where nrhs is the number of right-hand
 *         sides.
 *
 *  @param X (output) The solutions X. If Subfactor is m x n, and B is m x nrhs,
 *         then X must have dimension n x nrhs.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float B,
  DenseMatrix_Float X, void *workspace);

/**** Vector solve ************************************************************/

/*! @abstract Solve the equation Subfactor * x = b for the vector x, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xb (input/output) On input, the vector b. On return it is overwritten
 *         with the solution vector x. If Subfactor is m x n, then xb must have
 *         length k, where k = max(m, n). If m != n, then only the first
 *         min(m,n) entries are used for input or output as approriate.       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xb);

/*! @abstract Solve the equation Subfactor * x = b for the vector x, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xb (input/output) On input, the vector b. On return it is overwritten
 *         with the solution vector x. If Subfactor is m x n, then xb must have
 *         length k, where k = max(m, n). If m != n, then only the first
 *         min(m,n) entries are used for input or output as approriate.       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xb);

/*! @abstract Solve the equation Subfactor * x = b for the vector x.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param b (input) The right-hand side b. If Subfactor is m x n, then b must
 *         have length m.
 *
 *  @param x (output) The solution x. If Subfactor is m x n, then x must have
 *         length n.                                                          */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double b,
  DenseVector_Double x);

/*! @abstract Solve the equation Subfactor * x = b for the vector x.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param b (input) The right-hand side b. If Subfactor is m x n, then b must
 *         have length m.
 *
 *  @param x (output) The solution x. If Subfactor is m x n, then x must have
 *         length n.                                                          */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float b,
  DenseVector_Float x);

/**** Vector solve functions with user-supplied workspace *********************/

/*! @abstract Solve the equation Subfactor * x = b for the vector x, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xb (input/output) On input, the vector b. On return it is overwritten
 *         with the solution vector x. If Subfactor is m x n, then xb must have
 *         length k, where k = max(m, n). If m != n, then only the first
 *         min(m,n) entries are used for input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xb,
  void *workspace);

/*! @abstract Solve the equation Subfactor * x = b for the vector x, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xb (input/output) On input, the vector b. On return it is overwritten
 *         with the solution vector x. If Subfactor is m x n, then xb must have
 *         length k, where k = max(m, n). If m != n, then only the first
 *         min(m,n) entries are used for input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xb,
  void *workspace);

/*! @abstract Solve the equation Subfactor * x = b for the vector x, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param b (input) The right-hand side b. If Subfactor is m x n, then b must
 *         have length m.
 *
 *  @param x (output) The solution x. If Subfactor is m x n, then x must have
 *         length n.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double b,
  DenseVector_Double x, void *workspace);

/*! @abstract Solve the equation Subfactor * x = b for the vector x, in place.
 *
 *  @param Subfactor (input) The subfactor to solve a system involving, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param b (input) The right-hand side b. If Subfactor is m x n, then b must
 *         have length m.
 *
 *  @param x (output) The solution x. If Subfactor is m x n, then x must have
 *         length n.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float b,
  DenseVector_Float x, void *workspace);

/**** Matrix multiply functions ***********************************************/

/*! @abstract Perform the multiply operation Y = Subfactor * X in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XY (input/output) On input, the matrix X. On return it is overwritten
 *         with the matrix Y. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         side vectors. If m != n, then only the first min(m,n) entries are
 *         used for input or output as approriate.                            */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XY);

/*! @abstract Perform the multiply operation Y = Subfactor * X in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XY (input/output) On input, the matrix X. On return it is overwritten
 *         with the matrix Y. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         side vectors. If m != n, then only the first min(m,n) entries are
 *         used for input or output as approriate.                            */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XY);

/*! @abstract Perform the multiply operation Y = Subfactor * X.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param X (input) The right-hand side vectors X. If Subfactor is m x n, then X
 *         must have dimension n x nrhs, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  @param Y (output) The result vectors Y. If Subfactor is m x n, and X is
 *         m x nrhs, then Y must have dimension m x nrhs.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double X,
  DenseMatrix_Double Y);

/*! @abstract Perform the multiply operation Y = Subfactor * X.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param X (input) The right-hand side vectors X. If Subfactor is m x n, then X
 *         must have dimension n x nrhs, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  @param Y (output) The result vectors Y. If Subfactor is m x n, and X is
 *         m x nrhs, then Y must have dimension m x nrhs.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float X,
  DenseMatrix_Float Y);

/**** Matrix multiply functions with user-supplied workspace ******************/

/*! @abstract Perform the multiply operation Y = Subfactor * X in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XY (input/output) On input, the matrix X. On return it is overwritten
 *         with the matrix Y. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         side vectors. If m != n, then only the first min(m,n) entries are
 *         used for input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XY,
  void *workspace);

/*! @abstract Perform the multiply operation Y = Subfactor * X in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param XY (input/output) On input, the matrix X. On return it is overwritten
 *         with the matrix Y. If Subfactor is m x n, then XB must have dimension
 *         k x nrhs, where k = max(m, n) and nrhs is the number of right-hand
 *         side vectors. If m != n, then only the first min(m,n) entries are
 *         used for input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XY,
  void *workspace);

/*! @abstract Perform the multiply operation Y = Subfactor * X.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param X (input) The right-hand side vectors X. If Subfactor is m x n, then X
 *         must have dimension n x nrhs, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  @param Y (output) The result vectors Y. If Subfactor is m x n, and X is
 *         m x nrhs, then Y must have dimension m x nrhs.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double X,
  DenseMatrix_Double Y, void *workspace);

/*! @abstract Perform the multiply operation Y = Subfactor * X.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param X (input) The right-hand side vectors X. If Subfactor is m x n, then X
 *         must have dimension n x nrhs, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  @param Y (output) The result vectors Y. If Subfactor is m x n, and X is
 *         m x nrhs, then Y must have dimension m x nrhs.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float X,
  DenseMatrix_Float Y, void *workspace);

/**** Vector multiply functions ***********************************************/

/*! @abstract Perform the multiply operation y = Subfactor * x in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xy (input/output) On input, the vector x. On return it is overwritten
 *         with the vector y. If Subfactor is m x n, then xb must have length
 *         k, where k = max(m, n). If m != n, then only the first min(m,n)
 *         entries are used for input or output as approriate.                */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xy)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Perform the multiply operation y = Subfactor * x in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xy (input/output) On input, the vector x. On return it is overwritten
 *         with the vector y. If Subfactor is m x n, then xb must have length
 *         k, where k = max(m, n). If m != n, then only the first min(m,n)
 *         entries are used for input or output as approriate.                */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xy)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Perform the multiply operation y = Subfactor * x.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param x (input) The right-hand side vector x. If Subfactor is m x n, then x
 *         must have length n.
 *
 *  @param y (output) The result vector y. If Subfactor is m x n, then y must have
 *         length m.                                                          */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double x,
  DenseVector_Double y);

/*! @abstract Perform the multiply operation y = Subfactor * x.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param x (input) The right-hand side vector x. If Subfactor is m x n, then x
 *         must have length n.
 *
 *  @param y (output) The result vector y. If Subfactor is m x n, then y must have
 *         length m.                                                          */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float x,
  DenseVector_Float y);

/**** Vector multiply functions with user-supplied workspace ******************/

/*! @abstract Perform the multiply operation y = Subfactor * x in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xy (input/output) On input, the vector x. On return it is overwritten
 *         with the vector y. If Subfactor is m x n, then xb must have length
 *         k, where k = max(m, n). If m != n, then only the first min(m,n)
 *         entries are used for input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xy,
  void *workspace);

/*! @abstract Perform the multiply operation y = Subfactor * x in place.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param xy (input/output) On input, the vector x. On return it is overwritten
 *         with the vector y. If Subfactor is m x n, then xb must have length
 *         k, where k = max(m, n). If m != n, then only the first min(m,n)
 *         entries are used for input or output as approriate.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xy,
  void *workspace);

/*! @abstract Perform the multiply operation y = Subfactor * x.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param x (input) The right-hand side vector x. If Subfactor is m x n, then x
 *         must have length n.
 *
 *  @param y (output) The result vector y. If Subfactor is m x n, then y must have
 *         length m.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double x,
  DenseVector_Double y, void *workspace);

/*! @abstract Perform the multiply operation y = Subfactor * x.
 *
 *  @param Subfactor (input) The subfactor to multiply by, as returned by
 *         SparseCreateSubfactor().
 *
 *  @param x (input) The right-hand side vector x. If Subfactor is m x n, then x
 *         must have length n.
 *
 *  @param y (output) The result vector y. If Subfactor is m x n, then y must have
 *         length m.
 *
 *  @param workspace (scratch) A workspace of size
 *         Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float x,
  DenseVector_Float y, void *workspace);

/******************************************************************************
 *  @group Preconditioners
 ******************************************************************************/

/*! @abstract Types of preconditioner.
 *
 *  @const SparsePreconditionerNone
 *    No preconditioner, used to flag an empty type as required.
 *  @const SparsePreconditionerUser
 *    User-defined preconditioner.
 *  @const SparsePreconditionerDiagonal
 *    Diagonal (Jacobi) preconditioner D_ii = 1.0 / A_ii.
 *    Zero entries on the diagonal of A are replaced with 1.0.
 *  @cont SparsePreconditionerDiagScaling
 *    Diagonal scaling preconditioner D_ii = 1.0 / || A_i ||_2, where A_i is
 *    i-th column of A.
 */
SPARSE_ENUM(SparsePreconditioner, int,
  SparsePreconditionerNone = 0,
  SparsePreconditionerUser = 1,
  SparsePreconditionerDiagonal = 2,
  SparsePreconditionerDiagScaling = 3
);

/*! @abstract Represents a preconditioner.
 *
 *  @field type The type of preconditioner represented.
 *
 *  @field mem Block of memory that will be passed unaltered as the first
 *         argument of the apply() callback.
 *
 *  \@callback apply(mem, trans, X, Y) Function to call to apply the
 *             preconditioner as Y = PX (trans=false) or Y = P^TX (trans=true).
 *    \@param mem   The unaltered pointer mem from this struct.
 *    \@param trans Flags whether to apply the preconditioner or its transpose.
 *    \@param X     The right-hand side vectors X.
 *    \@param Y     The result vectors Y.                                     */
typedef struct {
  SparsePreconditioner_t type;
  void *mem;
  void (*apply) (void*, enum CBLAS_TRANSPOSE trans, DenseMatrix_Double X, DenseMatrix_Double Y);
} SparseOpaquePreconditioner_Double;

/*! @abstract Represents a preconditioner.
 *
 *  @field type The type of preconditioner represented.
 *
 *  @field mem Block of memory that will be passed unaltered as the first
 *         argument of the apply() callback.
 *
 *  \@callback apply(mem, trans, X, Y) Function to call to apply the
 *             preconditioner as Y = PX (trans=false) or Y = P^TX (trans=true).
 *    \@param mem   The unaltered pointer mem from this struct.
 *    \@param trans Flags whether to apply the preconditioner or its transpose.
 *    \@param X     The right-hand side vectors X.
 *    \@param Y     The result vectors Y.                                     */
typedef struct {
  SparsePreconditioner_t type;
  void *mem;
  void (*apply) (void*, enum CBLAS_TRANSPOSE trans, DenseMatrix_Float X, DenseMatrix_Float);
} SparseOpaquePreconditioner_Float;

/*! @abstract Create a preconditioner for the given matrix.
 *
 *  @param type (input) The type of preconditioner to create.
 *
 *  @param A (input) The matrix to construct a preconditioner for.
 *
 *  @returns The constructed preconditioner object. Resource must be freed
 *           through a call to SparseCleanup() once the user is finished with
 *           the preconditioner.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaquePreconditioner_Double SparseCreatePreconditioner(
  SparsePreconditioner_t type, SparseMatrix_Double A);

/*! @abstract Create a preconditioner for the given matrix.
 *
 *  @param type (input) The type of preconditioner to create.
 *
 *  @param A (input) The matrix to construct a preconditioner for.
 *
 *  @returns The constructed preconditioner object. Resource must be freed
 *           through a call to SparseCleanup() once the user is finished with
 *           the preconditioner.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaquePreconditioner_Float SparseCreatePreconditioner(
  SparsePreconditioner_t type, SparseMatrix_Float A);

/******************************************************************************
 *  @group Sparse Iterative Methods
 ******************************************************************************
 * @discussion
 * Sparse Iterative methods solve Ax=b through an iterative process that only
 * requires multiplication by A or A^T. However, if A is numerically difficult,
 * the iterative process may fail to converge to a solution. Further, even for
 * problems where the process converges, it may do so slowly. Both of these
 * issues can be fixed through the application of a problem-specific
 * preconditioner that cheaply approximates the inverse of A (though good
 * preconditioners are not known for all probelms).
 *
 * More information on iterative methods is available on wikipedia:
 * https://en.wikipedia.org/wiki/Iterative_method
 *
 * The following book provides a more in-depth treatment of the subject:
 * [1] Y. Saad (2003), "Iterative Methods for Sparse Linear Systems",
 *     2nd Edition, Published by SIAM.                                        */

/**** Type definitions ********************************************************/

/*! @abstract Exit status definitions for sparse iterative methods.
 *
 *  @const SparseIterativeConverged
 *    All solution vectors converged.
 *  @const SparseIterativeMaxIterations
 *    One or more solutions failed to converge in the maximum number of
 *    iterations.
 *  @const SparseIterativeParameterError
 *    There was an error with one or more user-supplied parameters.
 *  @const SparseIterativeIllConditioned
 *    Problem determined to be sufficiently ill conditioned convergence is
 *    unlikely.
 *  @const SparseIterativeInternalError
 *    Some internal failure occured (e.g. memory allocation failed).          */
SPARSE_ENUM(SparseIterativeStatus, int,
  SparseIterativeConverged = 0,
  SparseIterativeMaxIterations = 1,
  SparseIterativeParameterError = -1,
  SparseIterativeIllConditioned = -2,
  SparseIterativeInternalError = -99,
);

/*! @internal This type required for implementation use only.
 *
 *  @abstract Base type for iterative method options structures.
 *
 *  @discussion In the SparseIterativeMethod datatype, all possible options
 *  structures are held as a union. Defining this base type allows easy access
 *  to the reportError() method regardless of which particular method the
 *  structure represents, so long as reportError() is the first entry in each
 *  options structure.
 *
 *  \@callback reportError Function to use to report parameter errors.
 *    \@param message
 *    \@discussion If NULL, errors are logged via <os/log.h> and execution is
 *      halted via __builtin_trap().  If non-NULL, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).            */
struct _SparseIterativeMethodBaseOptions {
  // reportError should always be FIRST member in below structs
  void (* _Nullable reportError)(const char *message);
};

/*! @abstract Conjugate Gradient Options.
 *
 *  @discussion Use CG to solve Ax=b when A is symmetric positive-definite (the method may break
 *  down or fail to converge if A is not positive-definite).
 *
 *  For square, full rank unsymmetric or indefinite equations, use GMRES instead.
 *  For rectangular or singular systems, use LSMR instead.
 *
 *  More information on the CG algorithm can be found on wikipedia:
 *  https://en.wikipedia.org/wiki/Conjugate_gradient_method
 *
 *  A more detailed review of CG is available in the paper:
 *  [1] J. Shewchuk (1994), "An Introduction to the Conjugate Gradient Method Without the
 *      Agonizing Pain", Technical Report, Carnegie Mellon University.
 *
 *  \@callback reportError Function to use to report parameter errors.
 *    \@param message
 *    \@discussion If NULL, errors are logged via <os/log.h> and execution is
 *      halted via __builtin_trap().  If non-NULL, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *
 *  \field maxIterations
 *    Maximum number of iterations to perform. If 0, the default value of 100
 *    is used.
 *
 *  \field atol
 *    Absolute convergence tolerance. Iterate is considered to have converged if
 *              || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol.
 *  \field rtol
 *    Relative convergence tolerance. Iterate is considered to have converged if
 *              || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol.
 *    If rtol = 0.0, default value of sqrt(epsilon) is used.
 *    If negative, rtol is treated as 0.0 (default is not used).
 *
 *  \@callback reportStatus Function to use to report status (iteration count
 *             and residual of first right-hand side) every few iterations.
 *    \@param message
 *    \@discussion If NULL, status is not reported.                           */
typedef struct {
  void (* _Nullable reportError)(const char *message);
  int maxIterations;
  double atol;
  double rtol;
  void (* _Nullable reportStatus)(const char *message);
} SparseCGOptions;

/*! @abstract Specify different variants of GMRES that can be used.
 *
 *  @discussion Basic GMRES requires restarting (as otherwise memory and
 *  calculation costs to keep vectors orthagonal become prohibitive). Upon
 *  restarting all information from previous iterations is discarded.
 *  DQGMRES implements a quasi-GMRES method that does not restart, but instead
 *  only performs orthagonalization against vectors from the most recent
 *  iterations.
 *  Basic GMRES also requires that the same preconditioner is used at every
 *  iteration. At the cost of some additional storage and work, it can be
 *  made flexible (able to cope with different preconditioners at each
 *  iteration) this variant is known as FGMRES.
 *  DGMRES is inherently flexible, so no additional flexible variant is
 *  required.
 *
 *  DQGMRES is the default variant, though for some problems, GMRES or FGMRES
 *  may converge faster and require less computation, particualrly if the
 *  number of orthagonalization vectors nvec is small (< 16).
 *
 *  @const SparseVariantDQGMRES
 *    Use DQGMRES variant. This method is flexible.
 *  @const SparseVariantGMRES
 *    Use standard restarted GMRES. This method is not flexible.
 *  @const SparseVariantFGMRES
 *    Use Flexible GMRES. This method is flexible.                            */
SPARSE_ENUM(SparseGMRESVariant, uint8_t,
  SparseVariantDQGMRES = 0,
  SparseVariantGMRES = 1,
  SparseVariantFGMRES = 2
);

/*! @abstract (right-preconditioned) (F/DQ)GMRES Parameters Options.
 *
 *  @discussion Use (F/DQ)GMRES to solve Ax=b when A is symmetric indefinite or unsymmetric.
 *
 *  For symmetric positive-definite systems, use CG instead.
 *  For rectangular or singular systems, use LSMR instead.
 *
 *  More information about GMRES can be found on wikipedia:
 *  https://en.wikipedia.org/wiki/Generalized_minimal_residual_method
 *
 *  A more detailed description of GMRES and its variants is available in the book:
 *  [1] Y. Saad (2003), "Iterative Methods for Sparse Linear Systems", 2nd Edition,
 *      Published by SIAM.
 *
 *  \@callback reportError Function to use to report parameter errors.
 *    \@param message
 *    \@discussion If NULL, errors are logged via <os/log.h> and execution is
 *      halted via __builtin_trap().  If non-NULL, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *
 *  \field variant
 *    Variant of GMRES to use. See definition of SparseGMRESVariant_t for
 *    further information on the available variants.
 *
 *  \field nvec
 *    Number of orthagonal vectors maintained. For GMRES and FGMRES variants,
 *    this is the number of iterations between restarts. For DQGMRES it is the
 *    number of historical vectors maintained in memory.
 *    If nvec<=0, the default value of 16 is used.
 *
 *  \field maxIterations
 *    Maximum number of iterations to perform. If 0, the default value of 100
 *    is used.
 *
 *  \field atol
 *    Absolute convergence tolerance. Iterate is considered to have converged if
 *              || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol.
 *  \field rtol
 *    Relative convergence tolerance. Iterate is considered to have converged if
 *              || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol.
 *    If rtol = 0.0, default value of sqrt(epsilon) is used.
 *    If negative, rtol is treated as 0.0 (default is not used).
 *
 *  \@callback reportStatus Function to use to report status (iteration count
 *             and residual of first right-hand side) every few iterations.
 *    \@param message
 *    \@discussion If NULL, status is not reported.                           */
typedef struct {
  void (* _Nullable reportError)(const char *message);
  SparseGMRESVariant_t variant;
  int nvec;
  int maxIterations;
  double atol;
  double rtol;
  void (* _Nullable reportStatus)(const char *message);
} SparseGMRESOptions;

/*! @abstract Available types of convergence test for LSMR.
 *
 *  @discussion In addition to accelerate's default convergence test
 *  applied to the normal equations, the original more specializated
 *  convergence test of Fong and Saunders is offered.
 *
 *  @const SparseLSMRCTDefault
 *    Use accelerate's default convergence test:
 *      || A^Tb - A^TAx ||_2 < rtol * || A^Tb - A^TAx_0 ||_2 + atol.
 *
 *  @const SparseLSMRCTFongSaunders
 *    Use the convergence test of Fong and Saunders:
 *      Either || b-Ax ||_2 < btol * || b ||_2 + atol * || A ||_2 || x ||_2
 *      or     || A^T (b-Ax) ||_2 < atol * || A ||_2 * || A-bx ||_2
 *      or     Estimated condition of matrix >= conditionLimit                */
SPARSE_ENUM(SparseLSMRConvergenceTest, int,
  SparseLSMRCTDefault = 0,
  SparseLSMRCTFongSaunders = 1,
);

/*! @abstract LSMR is MINRES specialised for solving least squares.
 *
 *  @discussion Use LSMR to solve equations of the form Ax=b where an exact
 *  solution does not exist. The returned solution minimises || b-Ax ||_2.
 *
 *  Whilst LSMR is equivalent to MINRES applied to the normal equations
 *  A^TAx = A^Tb in exact arithmetic, it has superior numerical behaviour and
 *  should be used in preference.
 *
 *  We note that due to the implicit squaring of the condition of A in the
 *  normal equations, LSMR may struggle to converge in single precision, and
 *  double precision arithmetic is recommended.
 *
 *  For symmetric positive-definite systems, use CG instead.
 *  For square, full rank unsymmetric or indefinite equations, use GMRES instead.
 *
 *  LSMR is described in the following paper:
 *  [1] D.C.-L. Fong and M.A. Saunders (2011), "LSMR: An iterative algoirthm for
 *      sparse least-squares problems", SIAM J. Scientific Computing 33(5),
 *      pp 2950--2971.
 *
 *  \@callback reportError Function to use to report parameter errors.
 *    \@param message
 *    \@discussion If NULL, errors are logged via <os/log.h> and execution is
 *      halted via __builtin_trap().  If non-NULL, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *
 *  \field lambda
 *    Damping parameter, if non-zero the actual problem solved is
 *          min_x || Ax-b ||_2 + lambda || x ||_2.
 *    Using damping can often allow the iteration to converge on ill-conditioned
 *    systems.
 *
 *  \field variant
 *    Variant of GMRES to use. See definition of SparseGMRESVariant_t for
 *    further information on the available variants.
 *
 *  \field nvec
 *    Number of vectors used for local orthagonalization.
 *    If nvec<=0, no orthagonalization is performed.
 *
 *  \field convergenceTest
 *    Which convergence test to use. See definition of
 *    SparseLSMRConvergenceTest_t for further information.
 *
 *  \field maxIterations
 *    Maximum number of iterations to perform. If 0, the default value of 4n
 *    is used.
 *    However, if a good preconditioner is available and/or the matrix is well
 *    conditioned such that singular values are clustered, a value of n/2 may
 *    be more approriate.
 *
 *  \field atol
 *    Either absolute tolerance (default test) or A tolerance (Fong-Saunders
 *    test). In the Fong and Saunders case, it should hold an estimate of the
 *    relative error in the data defining the matrix A. For example, if A is
 *    accurate to about 6 digits, set atol = 1.0e-6. In the Fong and Saunders
 *    case, if atol is 0.0, it is treated as machine epsilon. If using the
 *    default test, a value of 0.0 is treated as 0.0.
 *
 *  \field rtol
 *    Relative convergence tolerance (default test only).
 *    If rtol = 0.0, default value of sqrt(epsilon) is used.
 *    If negative, rtol is treated as 0.0 (default is not used).
 *
 *  \field btol
 *    b tolerance (Fong-Saunders test only). It should hold an estimate of the
 *    relative error in the data defining the rhs b. For example, if b is
 *    accurate to about 6 digits, set btol = 1.0e-6. If btol is zero, it
 *    is treated as machine epsilon.
 *
 *  \field conditionLimit
 *    Condition number limit (Fong-Saunders test). Iterations will be terminated
 *    if a computed estimate of cond(Abar) exceeds this value. This is intended
 *    to prevent certain small or zero singular values of A or Abar from coming
 *    into effect and causing unwanted growth in the computed solution.
 *    conditionLimit and lambda may be used separately or together to regularize
 *    ill-conditioned systems.
 *    Normally, conlim should be in the range 1000 to 1/eps.
 *    Suggested value:
 *    conlim = 1/(100*eps)  for compatible systems,
 *    conlim = 1/(10*sqrt(eps)) for least squares.
 *    If conditionLimit is 0.0, it is treated as 1/eps.
 *
 *  \@callback reportStatus Function to use to report status (iteration count
 *             and residual of first right-hand side) every few iterations.
 *    \@param message
 *    \@discussion If NULL, status is not reported.                           */
typedef struct {
  void (* _Nullable reportError)(const char *message);
  double lambda;
  int nvec;
  SparseLSMRConvergenceTest_t convergenceTest;
  double atol;
  double rtol;
  double btol;
  double conditionLimit;
  int maxIterations;
  void (* _Nullable reportStatus)(const char *message);
} SparseLSMROptions;

/*! @abstract General description object for all iterative methods.
 *
 *  @discussion This object is intended to be constructed through a call to an
 *  iterative method factory function, such as SparseConjugateGradient() or
 *  SparseLSMR().
 *
 *  @field method The type of method the object represents.
 *
 *  @field options The options to be used for the method.                     */
typedef struct {
  /*! @abstract Specify type of method described */
  int method;
  union {
    struct _SparseIterativeMethodBaseOptions base;
    SparseCGOptions cg;
    SparseGMRESOptions gmres;
    SparseLSMROptions lsmr;
    char padding[256]; /* Ensure union big enough for future method options */
  } options;
} SparseIterativeMethod;

/**** Iterative Method Factory Functions **************************************/

/*! @abstract Return a Conjugate Gradient Method with default options.        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseConjugateGradient(void);

/*! @abstract Return a Conjugate Gradient Method with specified options.
 *
 *  @param options Options for conjugate gradient method.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseConjugateGradient(SparseCGOptions options);

/*! @abstract Return a GMRES Method with default options.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseGMRES(void);

/*! @abstract Return a GMRES Method with specified options.
 *
 *  @param options Options for GMRES method.                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseGMRES(SparseGMRESOptions options);

/*! @abstract Return a LSMR Method with default options.                      */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseLSMR(void);

/*! @abstract Return a LSMR Method with specified options
 *
 *  @param options Options for LSMR method.                                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseLSMR(SparseLSMROptions options);

/******************************************************************************
 *  @group Iterative Sparse Solve Functions
 ******************************************************************************/

/**** Solve without preconditioner ********************************************/

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseMatrix_Double B, DenseMatrix_Double X);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseMatrix_Float B, DenseMatrix_Float X);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseVector_Double b, DenseVector_Double x);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseVector_Float b, DenseVector_Float x);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double X);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float X);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, x, y)
 *             should perform the operation y = op(A)x if accumulate is false,
 *             or y += op(A)x if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform y += op(A)x (if
 *            true) or y = op(A)x (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param x The vector to multiply.
 *    \@param y The vector in which to accumulate or store the result.
 *
 *  @param b The right-hand side b to solve for. If a has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Double x, DenseVector_Double y),
  DenseVector_Double b, DenseVector_Double x);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, x, y)
 *             should perform the operation y = op(A)x if accumulate is false,
 *             or y += op(A)x if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform y += op(A)x (if
 *            true) or y = op(A)x (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param x The vector to multiply.
 *    \@param y The vector in which to accumulate or store the result.
 *
 *  @param b The right-hand side b to solve for. If a has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Float x, DenseVector_Float y),
  DenseVector_Float b, DenseVector_Float x);

/**** Solve with preconditioner ***********************************************/

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  @param Preconditioner Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseMatrix_Double B, DenseMatrix_Double X,
  SparsePreconditioner_t Preconditioner);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  @param Preconditioner Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseMatrix_Float B, DenseMatrix_Float X,
  SparsePreconditioner_t Preconditioner);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  @param Preconditioner Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseVector_Double b, DenseVector_Double x,
  SparsePreconditioner_t Preconditioner);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  @param Preconditioner Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseVector_Float b, DenseVector_Float x,
  SparsePreconditioner_t Preconditioner);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  @parameter Preconditioner The preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseMatrix_Double B, DenseMatrix_Double X,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  @parameter Preconditioner The preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseMatrix_Float B, DenseMatrix_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  @param Preconditioner The preconditioner to apply.                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseVector_Double b, DenseVector_Double x,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  @param A (input) The matrix A to solve the system for. Only used for
 *         multiplication by A or A^T.
 *
 *  @param b The right-hand side b to solve for. If A has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  @param Preconditioner The preconditioner to apply.                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseVector_Float b, DenseVector_Float x,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  @param Preconditioner (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double X,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! @abstract Solve AX=B using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B The right-hand sides B to solve for. If A has dimension m x n, then
 *         B must have dimension m x nrhs, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  @param X On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, and B has dimension m x nrhs, then X must have
 *         dimension n x nrhs. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  @param Preconditioner (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, x, y)
 *             should perform the operation y = op(A)x if accumulate is false,
 *             or y += op(A)x if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform y += op(A)x (if
 *            true) or y = op(A)x (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param x The vector to multiply.
 *    \@param y The vector in which to accumulate or store the result.
 *
 *  @param b The right-hand side b to solve for. If a has dimension m x n, then
 *         b must have length m.
 *
 *  @param x On entry, initial guess for solution, on return the solution. If A
 *         has dimension m x n, then x must have length n. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  @param Preconditioner (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Double x, DenseVector_Double y),
  DenseVector_Double b, DenseVector_Double x,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! @abstract Solve Ax=b using the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, x, y)
 *             should perform the operation y = op(A)x if accumulate is false,
 *             or y += op(A)x if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform y += op(A)x (if
 *            true) or y = op(A)x (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param x The vector to multiply.
 *    \@param y The vector in which to accumulate or store the result.
 *
 *  \@param b The right-hand side b to solve for. If a has dimension m x n, then
 *          b must have length m.
 *
 *  \@param x On entry, initial guess for solution, on return the solution. If A
 *          has dimension m x n, then x must have length n. If no good initial
 *          estimate is available, user should set the initial guess to be the
 *          zero vector.
 *
 *  @param Preconditioner (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Float x, DenseVector_Float y),
  DenseVector_Float B, DenseVector_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/******************************************************************************
 *  @group Sparse Single-step Iteration  Functions
 ******************************************************************************
 *
 *  @discussion These functions are provided for expert uses who wish to execute
 *  iterative methods a single step at a time, for example to perform their own
 *  custom convergence tests.
 *
 *  A typical use of this routine might be as follows:
 *
 *  <pre>
 *  // Setup
 *  SparseIterativeMethod cg = SparseConjugateGradient();
 *  void *state = malloc( SparseGetStateSize_Double(cg, true, n, nrhs) );
 *  bool *converged = malloc(nrhs*sizeof(bool));
 *  memset(converged, false, nrhs*sizeof(bool)); // Initialize all as not converged
 *  SparseOpaquePreconditioner_Double Preconditioner = {
 *    .type  = SparsePreconditionerUser,
 *    .apply = myApplyFunction,
 *    .mem   = myDataBlock
 *  };
 *  for(long i=0; i<n*nrhs; i++) X->data[i] = 0.0; // Set X to initial guess of 0.0.
 *  memcpy(R->data, B->data, n*nrhs*sizeof(double)); // Set R = B   (X=0 => B-AX=B)
 *
 *  // Main iteration
 *  for(int iteration=0; iteration<maxIterations; iteration++) {
 *    SparseIterate(cg, iteration, converged, state, ApplyOperator, B, R, X, Preconditioner);
 *    bool all_converged = true;
 *    for(int j=0; j<nrhs; j++) {
 *      double residual2NormEstimate = R->data[j*R.columnStride];
 *      converged[j] = converged[j] || (residual2NormEstimate < convergenceTolerance);
 *      all_converged &= converged[j];
 *    }
 *    if(all_converged) break;
 *  }
 *
 *  // Finalise values
 *  SparseIterate(cg, -1, converged, state, ApplyOperator, B, R, X, Preconditioner);
 *
 *  // Free memory
 *  free(converged);
 *  free(state);
 *  </pre>
 */

/*! @abstract Returns size in bytes of state space required for call to
 *  SparseIterate().
 *
 *  @param method (input) Method to return required state space size for.
 *
 *  @param preconditioner (input) True if a preconditioner will be supplied,
 *         false otherwise.
 *
 *  @param m (input) Number of entries in right-hand side (rows in matrix A).
 *
 *  @param n (input) Number of variables to solve for (columns in matrix A).
 *
 *  @param nrhs (input) Number of right-hand sides to be solved for.
 *
 *  @returns Size of state space required in bytes.                           */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
size_t SparseGetStateSize_Double(SparseIterativeMethod method,
  bool preconditioner, int m, int n, int nrhs);

/*! @abstract Returns size in bytes of state space required for call to
 *  SparseIterate().
 *
 *  @param method (input) Method to return required state space size for.
 *
 *  @param preconditioner (input) True if a preconditioner will be supplied,
 *         false otherwise.
 *
 *  @param m (input) Number of entries in right-hand side (rows in matrix A).
 *
 *  @param n (input) Number of variables to solve for (columns in matrix A).
 *
 *  @param nrhs (input) Number of right-hand sides to be solved for.
 *
 *  @returns Size of state space required in bytes.                           */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
size_t SparseGetStateSize_Float(SparseIterativeMethod method,
  bool preconditioner, int m, int n, int nrhs);

/*! @abstract Perform a single iteration of the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *         Note that the options related to convergence testing (e.g.
 *         maxIterations, atol, rtol) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  @param iteration (input) The current iteration number, starting from 0. If
 *         iteration<0, then the current iterate is finalised, and the value of
 *         X is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  @param state (input/output) A pointer to a state-space of size returned by
 *         SparseGetStateSize_Double(). This memory must be 16-byte aligned
 *         (any allocation returned by malloc() has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to SparseIterate().
 *
 *  @param converged (input) Convergence status of each solution vector.
 *         converged[j]=true indicates that the vector stored as column j of X
 *         has converged, and it should be ignored in this iteration.
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B (input) The right-hand sides to solve for.
 *
 *  @param R (output) Residual estimate. On entry with iteration=0, it must hold
 *         the residuals b-Ax (equal to B if X=0). On return from each call with
 *         iteration>=0, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *         For CG and GMRES:
 *           R(0,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *         For LSMR:
 *           R(0,j) holds an estimate of || A^T(b-Ax) ||_2 for the j-th rhs.
 *           R(1,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *           R(2,j) holds an estimate of || A ||_F, the Frobenius norm of A,
 *                  estimated using calculations related to the j-th rhs.
 *           R(3,j) holds an estimate of cond(A), the condition number of A,
 *                  estimated using calculations related to the j-th rhs.
 *         Other entries of R may be used by the routine as a workspace.
 *         On return from a call with iteration<0, the exact residual vector
 *         b-Ax is returned.
 *
 *  @param X (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 *
 *  @param Preconditioner (input) Preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double R, DenseMatrix_Double X,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! @abstract Perform a single iteration of the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *         Note that the options related to convergence testing (e.g.
 *         maxIterations, atol, rtol) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  @param iteration (input) The current iteration number, starting from 0. If
 *         iteration<0, then the current iterate is finalised, and the value of
 *         X is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  @param state (input/output) A pointer to a state-space of size returned by
 *         SparseGetStateSize_Double(). This memory must be 16-byte aligned
 *         (any allocation returned by malloc() has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to SparseIterate().
 *
 *  @param converged (input) Convergence status of each solution vector.
 *         converged[j]=true indicates that the vector stored as column j of X
 *         has converged, and it should be ignored in this iteration.
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B (input) The right-hand sides to solve for.
 *
 *  @param R (output) Residual estimate. On entry with iteration=0, it must hold
 *         the residuals b-Ax (equal to B if X=0). On return from each call with
 *         iteration>=0, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *         For CG and GMRES:
 *           R(0,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *         For LSMR:
 *           R(0,j) holds an estimate of || A^T(b-Ax) ||_2 for the j-th rhs.
 *           R(1,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *           R(2,j) holds an estimate of || A ||_F, the Frobenius norm of A,
 *                  estimated using calculations related to the j-th rhs.
 *           R(3,j) holds an estimate of cond(A), the condition number of A,
 *                  estimated using calculations related to the j-th rhs.
 *         Other entries of R may be used by the routine as a workspace.
 *         On return from a call with iteration<0, the exact residual vector
 *         b-Ax is returned.
 *
 *  @param X (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 *
 *  @param Preconditioner (input) Preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float R, DenseMatrix_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! @abstract Perform a single iteration of the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *         Note that the options related to convergence testing (e.g.
 *         maxIterations, atol, rtol) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  @param iteration (input) The current iteration number, starting from 0. If
 *         iteration<0, then the current iterate is finalised, and the value of
 *         X is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  @param state (input/output) A pointer to a state-space of size returned by
 *         SparseGetStateSize_Double(). This memory must be 16-byte aligned
 *         (any allocation returned by malloc() has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to SparseIterate().
 *
 *  @param converged (input) Convergence status of each solution vector.
 *         converged[j]=true indicates that the vector stored as column j of X
 *         has converged, and it should be ignored in this iteration.
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B (input) The right-hand sides to solve for.
 *
 *  @param R (output) Residual estimate. On entry with iteration=0, it must hold
 *         the residuals b-Ax (equal to B if X=0). On return from each call with
 *         iteration>=0, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *         For CG and GMRES:
 *           R(0,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *         For LSMR:
 *           R(0,j) holds an estimate of || A^T(b-Ax) ||_2 for the j-th rhs.
 *           R(1,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *           R(2,j) holds an estimate of || A ||_F, the Frobenius norm of A,
 *                  estimated using calculations related to the j-th rhs.
 *           R(3,j) holds an estimate of cond(A), the condition number of A,
 *                  estimated using calculations related to the j-th rhs.
 *         Other entries of R may be used by the routine as a workspace.
 *         On return from a call with iteration<0, the exact residual vector
 *         b-Ax is returned.
 *
 *  @param X (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.                               */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double R, DenseMatrix_Double X);

/*! @abstract Perform a single iteration of the specified iterative method.
 *
 *  @param method (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *         Note that the options related to convergence testing (e.g.
 *         maxIterations, atol, rtol) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  @param iteration (input) The current iteration number, starting from 0. If
 *         iteration<0, then the current iterate is finalised, and the value of
 *         X is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  @param state (input/output) A pointer to a state-space of size returned by
 *         SparseGetStateSize_Double(). This memory must be 16-byte aligned
 *         (any allocation returned by malloc() has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to SparseIterate().
 *
 *  @param converged (input) Convergence status of each solution vector.
 *         converged[j]=true indicates that the vector stored as column j of X
 *         has converged, and it should be ignored in this iteration.
 *
 *  \@callback ApplyOperator (block) ApplyOperator(accumulate, trans, X, Y)
 *             should perform the operation Y = op(A)X if accumulate is false,
 *             or Y += op(A)X if accumulate is true.
 *    \@param accumulate (input) Indicates whether to perform Y += op(A)X (if
 *            true) or Y = op(A)X (if false).
 *    \@param trans (input) Indicates whether op(A) is the application of A
 *            (trans=CblasNoTrans) or A^T (trans=CblasTrans).
 *    \@param X The matrix to multiply.
 *    \@param Y The matrix in which to accumulate or store the result.
 *
 *  @param B (input) The right-hand sides to solve for.
 *
 *  @param R (output) Residual estimate. On entry with iteration=0, it must hold
 *         the residuals b-Ax (equal to B if X=0). On return from each call with
 *         iteration>=0, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *         For CG and GMRES:
 *           R(0,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *         For LSMR:
 *           R(0,j) holds an estimate of || A^T(b-Ax) ||_2 for the j-th rhs.
 *           R(1,j) holds an estimate of || b-Ax ||_2 for the j-th rhs.
 *           R(2,j) holds an estimate of || A ||_F, the Frobenius norm of A,
 *                  estimated using calculations related to the j-th rhs.
 *           R(3,j) holds an estimate of cond(A), the condition number of A,
 *                  estimated using calculations related to the j-th rhs.
 *         Other entries of R may be used by the routine as a workspace.
 *         On return from a call with iteration<0, the exact residual vector
 *         b-Ax is returned.
 *
 *  @param X (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.                               */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float R, DenseMatrix_Float X);

/******************************************************************************
 *  @group Memory Management
 ******************************************************************************
 *  @discussion
 *  Underlying many object in sparse is a private data type references by a
 *  void* component on an opaque type. These are reference counted so that more
 *  than one opaque type can reference the same private object. For example,
 *  SparseCreateSubfactor() increments the refence count of the underlying type
 *  so that the returned SparseOpaqueSubfactor will still be valid even if the
 *  original factorization is destroyed.
 *
 *  Most users do not need to worry about the details of these objects, and
 *  should just ensure that they call SparseCleanup() on any object created
 *  by accelerate once they are done with it.
 *
 *  For advanced users, a SparseRetain() function is provided so they can create
 *  their own copies using the underlying reference counting. Whilst these
 *  functions return a copy, this can be discarded so long as a SparseCleanup()
 *  is invoked in some other fashion to release the reference.                */

/**** Retaining resources *****************************************************/

/*! @abstract Increase reference count on a symbolic factorization object,
 *            returning a copy.
 *
 *  @param SymbolicFactor The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  @returns A copy of SymbolicFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSymbolicFactorization SparseRetain(
  SparseOpaqueSymbolicFactorization SymbolicFactor);

/*! @abstract Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  @param NumericFactor The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  @returns A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseRetain(
  SparseOpaqueFactorization_Double NumericFactor);

/*! @abstract Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  @param NumericFactor The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  @returns A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseRetain(
  SparseOpaqueFactorization_Float NumericFactor);

/*! @abstract Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  @param NumericFactor The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  @returns A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Double SparseRetain(SparseOpaqueSubfactor_Double NumericFactor);

/*! @abstract Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  @param NumericFactor The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  @returns A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Float SparseRetain(SparseOpaqueSubfactor_Float NumericFactor);

/**** Cleaning up resources ***************************************************/

/*! @abstract Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSymbolicFactorization Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueFactorization_Double Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueFactorization_Float Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSubfactor_Double Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSubfactor_Float Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse matrix's references to any memory allocated
 *  by the Sparse library.
 *
 *  @discussion Reports an error if the matrix was not allocated by Sparse.
 *
 *  @param Matrix The matrix to be freed.                                     */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseMatrix_Double Matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse matrix's references to any memory allocated
 *  by the Sparse library.
 *
 *  @discussion Reports an error if the matrix was not allocated by Sparse.
 *
 *  @param Matrix The matrix to be freed.                                     */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseMatrix_Float Matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse Preconditioner's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The Preconditioner to be freed.                             */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaquePreconditioner_Double Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! @abstract Release a Sparse Preconditioner's references to any memory allocated
 *  by the sparse library.
 *
 *  @param Opaque The Preconditioner to be freed.                             */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaquePreconditioner_Float Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*********************************** END **************************************/

#if __has_feature(nullability)
# pragma clang assume_nonnull end
#endif

#if defined SPARSE_INCLUDED_VIA_ACCELERATE /* Included via Accelerate */
# include <vecLib/Sparse/SolveImplementation.h>
#else /* Standalone environments */
# include "SolveImplementation.h"
#endif

#endif /* __has_attribute(overloadable) */
#endif /* SPARSE_SOLVE_HEADER */
