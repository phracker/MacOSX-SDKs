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
 * LU
 * ===
 * The LU factorization scales and reorders the real or complex matrix `A` as
 * ```
 * S_r A S_c = P Ā Q
 * ```
 * where:
 * `S_r` and `S_c` are diagonal row and column scaling matrices respectively that are (by default)
 * automatically calculated by the solver (see options.scalingMethod for details).
 * `P` and `Q` are row and column  permutation matrices respectively that are (by default) automatically
 * calculated by the solver (see options.orderMethod for details).
 * such that `Ā` has the following block lower triangular form (Dulmage-Mendelshon decomposition):
 * ```
 *     ( A_rs                     )
 * Ā = ( A_10 A_11                )
 *     (   ⋮    ⋮    ⋱            )
 *     ( A_i0 A_i2   ⋯  A_ii      )
 *     ( A_n0 A_n2   ⋯  A_ni A_cs )
 * ```
 * where `A_rs` and `A_cs` correspond to lower triangular blocks of row and column singletons
 * respectively, and each diagonal block matrix corresponds to a strongly connected component.
 * We then factorize each strongly connected component as `A_ii = L_ii * U_ii` where
 * each `L_ii` is unit lower-triangular and each `U_ii` is non-unit upper triangular.
 * In a pivoted factorization additional row and column permtuation may be applied during the LU
 * factorization of each component to ensure numerical stability.
 *
 * SparseSolve() will solve Ax = b.
 * SparseCreateSubfactor() allows the following subfactors to be extracted:
 * - SparseSubfactorP    returns an opaque object representing P. Both Multiply and Solve are valid.
 * - SparseSubfactorQ    returns an opaque object representing Q. Both Multiply and Solve are valid.
 * - SparseSubfactorSr   returns an opaque object representing S_r. Both Multiply and Solve are valid.
 * - SparseSubfactorSc  returns an opaque object representing S_c. Both Multiply and Solve are valid.
 *
 * =====================================
 * Iterative Methods and Preconditioners
 * =====================================
 *
 * We offer the following iterative methods:
 * CG:    Conjugate Gradient method for symmetric (Hermitian) positive-definite matrices.
 * GMRES: Generalised Minimum RESidual method and variants (FGMRES, DQGMRES) for
 *        symmetric (Hermitian) indefinite and unsymmetric matrices.
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
# define API_AVAILABLE(...) /* nothing */
#endif

#ifdef __cplusplus
    #include <complex>
    typedef std::complex<float>  __SPARSE_float_complex;
    typedef std::complex<double> __SPARSE_double_complex;
#else
    typedef float _Complex   __SPARSE_float_complex;
    typedef double _Complex  __SPARSE_double_complex;
#endif

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

/*******************************************************************************
 * @group Sparse Matrix Type Definitions
 ******************************************************************************/

/**
 *  A flag to describe the type of matrix represented.
 *
 *   A `SparseMatrixStructure` object can represent several types of
 *  matrices:
 *
 *  - term `SparseOrdinary`: A "normal" sparse matrix without special structure.
 *
 *  - term `SparseTriangular`: A triangular sparse matrix with non-unit diagonal.
 *    The `SparseTriangle_t:` field indicates which triangle (upper or lower)
 *    is used.
 *
 *  - term `SparseUnitTriangular`: A triangular sparse matrix with unit diagonal.
 *    The `SparseTriangle_t`: field indicates which triangle (upper or lower)
 *    is used.
 *
 *  - term `SparseSymmetric`: A symmetric  sparse matrix.  The `SparseTriangle_t`
 *    field indicates which triangle (upper or lower) is used to represent
 *    the matrix.
 *
 *  - term `SparseHermitian`: A Hermitian  sparse matrix.  The `SparseTriangle_t`
 *    field indicates which triangle (upper or lower) is used to represent
 *    the matrix.
 *     */
SPARSE_ENUM(SparseKind, unsigned int,
  SparseOrdinary       API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )     = 0,
  SparseTriangular     API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )     = 1,
  SparseUnitTriangular API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )     = 2,
  SparseSymmetric      API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )     = 3,
  SparseHermitian      API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )  = 7,
);

/**
 *  A flag to indicate which triangle of a matrix is used.
 *
 *  - term  `SparseUpperTriangle`:
 *            For triangular and unit-triangular matrices, indicates that the
 *            upper triangle is to be used, and the lower triangle is implicitly
 *            zero.
 *            For symmetric (Hermitian) matrices, indicates that the upper triangle is to
 *            be used; the lower triangle is implicitly defined by reflection.
 *
 *  - term  `SparseLowerTriangle`:
 *            For triangular matrices, indicates that the lower triangle is to
 *            be used, and the upper triangle is implicitly zero.
 *            For symmetric (Hermitian) matrices, indicates that the lower triangle is to
 *            be used; the upper triangle is implicitly defined by reflection.*/
SPARSE_CLOSED_ENUM(SparseTriangle, unsigned char,
  SparseUpperTriangle API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )     = 0,
  SparseLowerTriangle API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )     = 1
);

/** A type representing the attributes of a matrix.
 *
 *  - term `transpose`: If `true`, the matrix is implicitly transposed when used
 *  in any functions.
 *
 *  - term `triangle`: If `kind` is `SparseOrdinary`, this field is ignored.
 *  Otherwise it indicates which triangle (upper or lower) represents the
 *  matrix.
 *
 *  - term `kind`: Identifies the matrix as being full (`SparseOrdinary`), [unit-]
 *  triangular (`SparseTriangular`, `SparseUnitTriangular`), or symmetric (Hermitian)
 *  (`SparseSymmetric`, `SparseHermitian`).
 *
 *  - term `_reserved`: for future expansion. Must be zero.
 *
 *  - term `_allocatedBySparse`: an implementation detail. Should be zero for any
 *  matrix you allocate.
 *   */
typedef struct {
  bool            transpose: 1;
  SparseTriangle_t triangle: 1;
  SparseKind_t         kind: 2;
  unsigned int    _reserved: 11;
  bool   _allocatedBySparse: 1;
} SparseAttributes_t;

/** A type representing the attributes of a matrix.
 *
 * - term `transpose`: If `true`, the matrix is implicitly transposed when used
 *  in any functions.
 *
 * - term `triangle`: If `kind` is `SparseOrdinary`, this field is ignored.
 *  Otherwise it indicates which triangle (upper or lower) represents the
 *  matrix.
 *
 * - term `kind`: Identifies the matrix as being full (`SparseOrdinary`), [unit-]
 *  triangular (`SparseTriangular`, `SparseUnitTriangular`), or symmetric (Hermitian)
 *  (`SparseSymmetric`, `SparseHermitian`).
 *
 * - term `conjugate_transpose`: If `true`, the matrix is implicitly conjugate transposed, otherwise
 *  it is simply transposed. This field has no meaning if `transpose` field is `false`.
 *
 * - term `_reserved`: for future expansion. Must be zero.
 *
 * - term `_allocatedBySparse`: an implementation detail. Should be zero for any
 *  matrix you allocate.
 *   */
typedef struct {
  bool            transpose: 1;
  SparseTriangle_t triangle: 1;
  SparseKind_t         kind: 3;
  bool  conjugate_transpose: 1;
  unsigned int    _reserved: 9;
  bool   _allocatedBySparse: 1;
} SparseAttributesComplex_t;


/** A type representing the sparsity structure of a sparse matrix.
 *
 *   The sparsity structure is represented in *block compressed
 *  sparse column* (block CSC) format. The matrix is divided into a regular
 *  grid of `rowCount x columnCount` blocks each of size `blockSize x blockSize`,
 *  and only blocks containing a non-zero entry are stored. CSC format is
 *  used to store the locations of these blocks. For each block column, a list
 *  of block row indices for non-zero blocks are stored, and the lists for each
 *  column are stored contiguously one after the other. Hence the row indices
 *  for column j are given by rowIndices`[columnStarts[j]:columnStarts[j+1]]`,
 *  where `columnStarts[]` is storing the location of the first index in each
 *  column.
 *
 *  If the blockSize is `1`, then this format is exactly equivalent to standard
 *  CSC format.
 *
 *  CSR format data can be simulated by using a blockSize of `1` and setting
 *  the transpose attribute (strictly this is still a transposed CSC matrix, so
 *  `rowCount` and `columnCount` will be transposed compared to true CSR).
 *
 *  - term `rowCount` : Number of (block) rows in matrix.
 *
 *  - term `columnCount` : Number of (block) columns in matrix.
 *
 *  - term `columnStarts` : Specifies where each (block) column starts in rowIndices
 *         array.
 *
 *  - term `rowIndices` : Specifies the (block) row indices of the matrix.
 *
 *  - term `attributes` : The attribute meta-data for the matrix, for example
 *         whether the matrix is symmetric (Hermitian) and only half the entries are stored.
 *
 *  - term `blockSize` :  The block size of the matrix.
 *  */
typedef struct {
  int rowCount;
  int columnCount;
  long *columnStarts;
  int *rowIndices;
  SparseAttributes_t attributes;
  uint8_t blockSize;
} SparseMatrixStructure;

/** A type representing the sparsity structure of a sparse complex matrix.
 *
 *   The sparsity structure is represented in *block compressed
 *  sparse column* (block CSC) format. The matrix is divided into a regular
 *  grid of `rowCount x columnCount` blocks each of size `blockSize x blockSize`,
 *  and only blocks containing a non-zero entry are stored. CSC format is
 *  used to store the locations of these blocks. For each block column, a list
 *  of block row indices for non-zero blocks are stored, and the lists for each
 *  column are stored contiguously one after the other. Hence the row indices
 *  for column j are given by rowIndices`[columnStarts[j]:columnStarts[j+1]]`,
 *  where `columnStarts[]` is storing the location of the first index in each
 *  column.
 *
 *  If the blockSize is `1`, then this format is exactly equivalent to standard
 *  CSC format.
 *
 *  CSR format data can be simulated by using a blockSize of `1` and setting
 *  the transpose attribute (strictly this is still a transposed CSC matrix, so
 *  `rowCount` and `columnCount` will be transposed compared to true CSR).
 *
 *  - term `rowCount` : Number of (block) rows in matrix.
 *
 *  - term `columnCount` : Number of (block) columns in matrix.
 *
 *  - term `columnStarts` : Specifies where each (block) column starts in rowIndices
 *         array.
 *
 *  - term `rowIndices` : Specifies the (block) row indices of the matrix.
 *
 *  - term `attributes` : The attribute meta-data for the matrix, for example
 *         whether the matrix is symmetric (Hermitian) and only half the entries are stored.
 *
 *  - term `blockSize` :  The block size of the matrix.
 *  */
typedef struct {
  int rowCount;
  int columnCount;
  long *columnStarts;
  int *rowIndices;
  SparseAttributesComplex_t attributes;
  uint8_t blockSize;
} SparseMatrixStructureComplex;

/** A type representing a sparse matrix.
 *
 *  `data` is the array of values in the non-zero blocks of the matrix stored
 *  contiguously, each block in column-major order. If there are `N` structural
 *  non-zero blocks in the matrix, `data` holds `blockSize * blockSize * N`
 *  doubles.
 *
 * - term  `structure` The symbolic structure of the matrix.
 *
 * - term  `data` The numerical values of the matrix. If `structure.blockSize > 1`,
 *        blocks are stored contiguously in column-major format.               */
typedef struct {
  SparseMatrixStructure structure;
  double *data;
} SparseMatrix_Double;

/*! A type representing a sparse matrix.
 *  
 *  `data` is the array of values in the non-zero blocks of the matrix stored
 *  contiguously, each block in column-major order. If there are `N` structural
 *  non-zero blocks in the matrix, `data` holds `blockSize * blockSize * N`
 *  doubles.
 *
 * - term  `structure` The symbolic structure of the matrix.
 *
 * - term  `data` The numerical values of the matrix. If `structure.blockSize > 1`,
 *        blocks are stored contiguously in column-major format.               */
typedef struct {
  SparseMatrixStructure structure;
  float *data;
} SparseMatrix_Float;

/*! A type representing a sparse complex matrix.
 *
 *  `data` is the array of values in the non-zero blocks of the matrix stored
 *  contiguously, each block in column-major order. If there are `N` structural
 *  non-zero blocks in the matrix, `data` holds `blockSize * blockSize * N`
 *  doubles.
 *
 * - term  `structure` The symbolic structure of the matrix.
 *
 * - term  `data` The numerical values of the matrix. If `structure.blockSize > 1`,
 *        blocks are stored contiguously in column-major format.               */
typedef struct {
  SparseMatrixStructureComplex structure;
  __SPARSE_double_complex *data;
} SparseMatrix_Complex_Double;

/*! A type representing a sparse complex matrix.
 *
 *  `data` is the array of values in the non-zero blocks of the matrix stored
 *  contiguously, each block in column-major order. If there are `N` structural
 *  non-zero blocks in the matrix, `data` holds `blockSize * blockSize * N`
 *  doubles.
 *
 * - term  `structure` The symbolic structure of the matrix.
 *
 * - term  `data` The numerical values of the matrix. If `structure.blockSize > 1`,
 *        blocks are stored contiguously in column-major format.               */
typedef struct {
  SparseMatrixStructureComplex structure;
  __SPARSE_float_complex *data;
} SparseMatrix_Complex_Float;

/******************************************************************************
 *  @group Conversion From Other Formats
 ******************************************************************************
 *   In the conversion functions below, the variables `rowCount`,
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
 *  If `attributes.kind` is `SparseHermitian`, any entries in the wrong
 *  triangle are conjugate transposed and summed into the block at `(column[i], row[i])`
 *  if one is present.
 *
 *  In all cases, if any duplicate coordinates are present, the elements are
 *  summed and replaced with a single entry.
 *
 *  There are two variants of each converter; one which allocates its own
 *  workspace internally, and also allocates space for the resulting sparse
 *  matrix, and one which requires you to pass storage for the new matrix and
 *  a separate workspace for precise control over allocations.                */

/*! Convert from coordinate format arrays to a matrix of double values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  - Parameter rowCount: Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  ouput.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Returns: A new `SparseMatrix_Double` object. When you are done with this
 *  matrix, release the memory that has been allocated by calling
 *  `SparseCleanup` on it.                                                   */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Double SparseConvertFromCoordinate(int rowCount, int columnCount,
  long blockCount, uint8_t blockSize, SparseAttributes_t attributes,
  const int *row, const int *column, const double *data)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Convert from coordinate format arrays to a matrix of float values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  output.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Returns: A new `SparseMatrix_Float` object. When you are done with this
 *  matrix, release the memory that has been allocated by calling
 *  `SparseCleanup` on it.                                                   */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Float SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributes_t attributes, const int *row,
  const int *column, const float *data)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Convert from coordinate format arrays to a matrix of complex double values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  output.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Returns: A new `SparseMatrix_Complex_Double` object. When you are done with this
 *  matrix, release the memory that has been allocated by calling
 *  `SparseCleanup` on it.                                                   */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Complex_Double SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributesComplex_t attributes, const int *row,
  const int *column, const __SPARSE_double_complex *data)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Convert from coordinate format arrays to a  matrix of complex float values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  output.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Returns: A new `SparseMatrix_Complex_Float` object. When you are done with this
 *  matrix, release the memory that has been allocated by calling
 *  `SparseCleanup` on it.                                                   */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Complex_Float SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributesComplex_t attributes, const int *row,
  const int *column, const __SPARSE_float_complex *data)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Convert from coordinate format arrays to a  matrix of double values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as 
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  `attributes.triangle` are treated as out-of-range and dropped.
 *
 *  Define `storage` as a block of memory of size at least:
 *
 *  ```
 *    48 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int)
 *      + blockCount*blockSize*blockSize*sizeof(double)
 *  ```
 *  The returned structures `.structure.columnStarts`, `.structure.rowIndices`,
 *  and `.data` will point into this storage. You are responsible for managing
 *  the allocation and cleanup of this memory.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  ouput.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Parameter storage: (output) The output storage.
 *
 *  - Parameter workspace: (scratch) Workspace of size `rowCount*sizeof(int)`.
 *
 *  - Returns: A new `SparseMatrix_Double` object, using the memory you provided in
 *  the `storage` parameter.                                                  */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Double SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributes_t attributes, const int *row,
  const int *column, const double *data, void *storage, void *workspace)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Convert from coordinate format arrays to a  matrix of float values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  Define `storage` as a block of memory of size at least:
 *
 *  ```
 *    48 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int)
 *      + blockCount*blockSize*blockSize*sizeof(float)
 *  ```
 *  The returned structures `.structure.columnStarts`, `.structure.rowIndices`,
 *  and `.data` will point into this storage. You are responsible for managing
 *  the allocation and cleanup of this memory.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  output.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Parameter storage: (output) The output storage.
 *
 *  - Parameter workspace: (scratch) Workspace of size `rowCount*sizeof(int)`.
 *
 *  - Returns: A new `SparseMatrix_Float` object, using the memory you provided in
 *  the `storage` parameter.                                                  */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Float SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributes_t attributes, const int *row,
  const int *column, const float *data, void *storage, void *workspace)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Convert from coordinate format arrays to a  matrix of complex double values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  Define `storage` as a block of memory of size at least:
 *
 *  ```
 *    48 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int)
 *      + blockCount*blockSize*blockSize*sizeof(float) * 2
 *  ```
 *  The returned structures `.structure.columnStarts`, `.structure.rowIndices`,
 *  and `.data` will point into this storage. You are responsible for managing
 *  the allocation and cleanup of this memory.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  output.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Parameter storage: (output) The output storage.
 *
 *  - Parameter workspace: (scratch) Workspace of size `rowCount*sizeof(int)`.
 *
 *  - Returns: A new `SparseMatrix_Complex_Double` object, using the memory you provided in
 *  the `storage` parameter.                                                  */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Complex_Double SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributesComplex_t attributes, const int *row,
  const int *column, const __SPARSE_double_complex *data, void *storage, void *workspace)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Convert from coordinate format arrays to a  matrix of complex float values,
 *  dropping out-of-range entries and summing duplicates.
 *
 *   For symmetric (Hermitian) matrices, entries are accepted in either triangle
 *  (if they are in the "wrong" triangle as specified by attributes.triangle,
 *  they are transposed, and if an entry is already present, are treated as
 *  duplicates and summed).
 *  For triangular matrices, entries in the "wrong" triangle as specified by
 *  attributes.triangle are treated as out-of-range and dropped.
 *
 *  Define `storage` as a block of memory of size at least:
 *
 *  ```
 *    48 + (columnCount+1)*sizeof(long) + blockCount*sizeof(int)
 *      + blockCount*blockSize*blockSize*sizeof(float) * 2
 *  ```
 *  The returned structures `.structure.columnStarts`, `.structure.rowIndices`,
 *  and `.data` will point into this storage. You are responsible for managing
 *  the allocation and cleanup of this memory.
 *
 *  - Parameter rowCount: (input) Number of rows in structure.
 *
 *  - Parameter columnCount: (input) Number of columns in structure.
 *
 *  - Parameter blockCount: (input) Number of blocks in matrix.
 *
 *  - Parameter blockSize: (input) Block size for data storage on both input and
 *  output.
 *
 *  - Parameter attributes: (input) Attributes of matrix to create. The matrix will
 *  be forced to conform to the specified attributes by copying or dropping
 *  elements as needed.
 *
 *  - Parameter row: (input) Row indices of matrix structure.
 *
 *  - Parameter column: (input) Column indices of matrix structure.
 *
 *  - Parameter data: (input) The contents of the structurally non-zero (block)
 *  matrix elements.
 *
 *  - Parameter storage: (output) The output storage.
 *
 *  - Parameter workspace: (scratch) Workspace of size `rowCount*sizeof(int)`.
 *
 *  - Returns: A new `SparseMatrix_Complex_Float` object, using the memory you provided in
 *  the `storage` parameter.                                                  */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Complex_Float SparseConvertFromCoordinate(int rowCount, int columnCount, long blockCount,
  uint8_t blockSize, SparseAttributesComplex_t attributes, const int *row,
  const int *column, const __SPARSE_float_complex *data, void *storage, void *workspace)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

#if defined __SPARSE_TYPES_H
/*! @group Conversions from opaque sparse matrix types
 *
 *   The older sparse headers on iOS and OS X (Sparse/BLAS.h) use
 *  a separate set of types that do not expose the internal storage of the
 *  sparse matrix. To assist in interoperation with the newer interfaces here,
 *  we provide a set of conversion functions from those types.                */

/** Converts an opaque matrix of double values object to a transparent
 *  sparse matrix object. When you are done with this matrix, release
 *  the memory that has been allocated by calling `SparseCleanup` on it.
 *
 *  - Parameter matrix: The matrix to be converted.                                 */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Double SparseConvertFromOpaque(sparse_matrix_double matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/** Converts an opaque matrix of float values object to a transparent
 *  sparse matrix object. When you are done with this matrix, release
 *  the memory that has been allocated by calling `SparseCleanup` on it.
 *
 *  - Parameter matrix: The matrix to be converted.                                 */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Float SparseConvertFromOpaque(sparse_matrix_float matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

#if !0
/** Converts an opaque matrix of complex double values object to a transparent
 *  sparse matrix object. When you are done with this matrix, release
 *  the memory that has been allocated by calling `SparseCleanup` on it.
 *
 *  - Parameter matrix: The matrix to be converted.                                 */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Complex_Double SparseConvertFromOpaque(sparse_matrix_double_complex matrix)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/** Converts an opaque matrix of complex float values object to a transparent
 *  sparse matrix object. When you are done with this matrix, release
 *  the memory that has been allocated by calling `SparseCleanup` on it.
 *
 *  - Parameter matrix: The matrix to be converted.                                 */
static inline SPARSE_PUBLIC_INTERFACE
SparseMatrix_Complex_Float SparseConvertFromOpaque(sparse_matrix_float_complex matrix)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;
#endif // !TARGET_OS_BRIDGE
#endif /* defined __SPARSE_TYPES_H */

/******************************************************************************
 *  @group Dense Matrices and Vectors
 ******************************************************************************/

/*! Contains a dense vector of double values.
 *
 *  - term `count`  :  Number of entries in the vector.
 *  - term  `data`  : The array of double values.                               */
typedef struct {
  int count;
  double *data;
} DenseVector_Double;

/*! Contains a dense vector of float values.
 *
 *  - term `count`  :  Number of entries in the vector.
 *  - term  `data`  : The array of float values.                               */
typedef struct {
  int count;
  float *data;
} DenseVector_Float;

/*! Contains a dense vector of double complex values.
 *
 *  - term `count`  :  Number of entries in the vector.
 *  - term  `data`  : The array of complex double values.                               */
typedef struct {
  int count;
  __SPARSE_double_complex *data;
} DenseVector_Complex_Double;

/*! Contains a dense vector of float complex values.
 *
 *  - term `count`  :  Number of entries in the vector.
 *  - term  `data`  : The array of complex float values.                               */
typedef struct {
  int count;
  __SPARSE_float_complex *data;
} DenseVector_Complex_Float;

/*! Contains a dense `rowCount` x `columnCount` matrix of double
 *            values stored in column-major order.
 *
 *  - term `rowCount`:   Number of rows in the matrix.
 *  - term `columnCount`:  Number of columns in the matrix.
 *  - term `columnStride`: The column stride of the matrix.
 *  - term `attributes`:  The attributes of the matrix, for example whether the matrix is symmetrical (Hermitian) or triangular.
 *  - term `data` :        The array of double values in column-major order.     */
typedef struct {
  int rowCount;
  int columnCount;
  int columnStride;
  SparseAttributes_t attributes;
  double *data;
} DenseMatrix_Double;

/*! Contains a dense `rowCount` x `columnCount` matrix of float
 *            values stored in column-major order.
 *
 *  - term `rowCount`:   Number of rows in the matrix.
 *  - term `columnCount`:  Number of columns in the matrix.
 *  - term `columnStride`:  The column stride of the matrix.
 *  - term `attributes`:   The attributes of the matrix, for example whether the matrix is symmetrical (Hermitian) or triangular.
 *  - term `data`: The array of float values in column-major order.      */
typedef struct {
  int rowCount;
  int columnCount;
  int columnStride;
  SparseAttributes_t attributes;
  float *data;
} DenseMatrix_Float;

/*! Contains a dense `rowCount` x `columnCount` matrix of complex double
 *            values stored in column-major order.
 *
 *  - term `rowCount`:     Number of rows in the matrix.
 *  - term `columnCount`:  Number of columns in the matrix.
 *  - term `columnStride`: The column stride of the matrix.
 *  - term `attributes`:   The attributes of the matrix, for example whether the matrix is symmetrical (Hermitian) or triangular.
 *  - term `data`: The array of float values in column-major order.      */
typedef struct {
  int rowCount;
  int columnCount;
  int columnStride;
  SparseAttributesComplex_t attributes;
  __SPARSE_double_complex *data;
} DenseMatrix_Complex_Double;

/*! Contains a dense `rowCount` x `columnCount` matrix of complex float
 *            values stored in column-major order.
 *
 *  - term `rowCount`:     Number of rows in the matrix.
 *  - term `columnCount`:  Number of columns in the matrix.
 *  - term `columnStride`:  The column stride of the matrix.
 *  - term `attributes`: The attributes of the matrix, for example whether the  matrix is symmetrical (Hermitian) or triangular.
 *  - term `data`: The array of float values in column-major order.      */
typedef struct {
  int rowCount;
  int columnCount;
  int columnStride;
  SparseAttributesComplex_t attributes;
  __SPARSE_float_complex *data;
} DenseMatrix_Complex_Float;
/******************************************************************************
 *  @group Sparse Factorization Related Types
 ******************************************************************************/

/** Status field for a factorization.
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

/** Types of factorization than can be performed.
 *
 *  - term `SparseFactorizationCholesky` :
 *              Cholesky (LL^T) factorization.
 *  - term `SparseFactorizationLDLT` :
 *              Default LDL^T factorization (currently LDL^T with TPP).
 *  - term `SparseFactorizationLDLTUnpivoted` :
 *              Cholesky-like LDL^T with only 1x1 pivots and no pivoting.
 *  - term `SparseFactorizationLDLTSBK` :
 *              LDL^T with Supernode Bunch-Kaufman and static pivoting.
 *  - term `SparseFactorizationLDLTTPP` :
 *              LDL^T with full threshold partial pivoting.
 *  - term `SparseFactorizationQR` :
 *              QR factorization.
 *  - term `SparseFactorizationCholeskyAtA` :
 *              QR factorization without storing Q (equivalent to A^TA = R^T R).
 *  - term `SparseFactorizationLU` :
 *              Default LU factorization (currently LU with TPP).
 *  - term `SparseFactorizationLUUnpivoted` :
 *              LU factorization with no numerical pivoting.
 *  - term `SparseFactorizationLUSPP` :
 *              LU factorization with partial pivoting restricted to within supernodes only.
 *  - term `SparseFactorizationLUTPP` :
 *              LU factorization with threshold partial pivoting.
 */
SPARSE_ENUM(SparseFactorization, uint8_t,
  SparseFactorizationCholesky       API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       =  0,
  SparseFactorizationLDLT           API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       =  1,
  SparseFactorizationLDLTUnpivoted  API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       =  2,
  SparseFactorizationLDLTSBK        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       =  3,
  SparseFactorizationLDLTTPP        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       =  4,
  SparseFactorizationQR             API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       = 40,
  SparseFactorizationCholeskyAtA    API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))       = 41,
  SparseFactorizationLU             API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 80,
  SparseFactorizationLUUnpivoted    API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 81,
  SparseFactorizationLUSPP          API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 82,
  SparseFactorizationLUTPP          API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 83,
);

/** Control flags for matrix factorization.
 *
 *  - term `SparseDefaultControl` : Use default values.
 */
SPARSE_ENUM(SparseControl, uint32_t,
  SparseDefaultControl = 0
);

/** Specifies type of fill-reducing ordering.
 *
 *   The order in which variables are eliminated (i.e. the column/row ordering) in a
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
 *  The AMD and MeTiS orderings provide good orderings for symmetric (Hermitian) matrices. They can be used
 *  for the QR factorizations, but this involves forming A^TA explicitly, which is expensive.
 *  COLAMD on the other hand finds an ordering for `A^T A` whilst only working with A. For this
 *  reason, COLAMD cannot be used for symmetric (Hermitian) factorizations.
 *
 *  - term  `SparseOrderDefault`:
 *              Default ordering (AMD for symmetric factorizations, COLAMD for QR/CholeskyAtA,
 *              and MT-METIS for LU. Defaults may change in future releases if better algorithms
 *              become available).
 *  - term  `SparseOrderUser`:
 *              User-supplied ordering, or identity if options->order is NULL
 *  - term  `SparseOrderAMD`:
 *              AMD ordering. Large overhead cost if used for QR-based
 *              factorization due to explicit formation of `A^T A`.
 *  - term  `SparseOrderMetis`:
 *              MeTiS Nested Dissection ordering. Large overhead cost if used
 *              for QR-based factorization due to explicit formation of `A^T A`.
 *  - term `SparseOrderMTMetis`:
 *              MT-MeTiS Nested Dissection ordering. Similar to `SparseOrderMetis`,
 *              but uses multiple threads to increase performance at cost of slightly worse
 *              ordering quality.
 *  - term  `SparseOrderCOLAMD`:
 *              Column AMD ordering for `A^T A`. Not valid for symmetric (Hermitian)
 *              factorizations (use AMD instead).                             */
SPARSE_ENUM(SparseOrder, uint8_t,
  SparseOrderDefault  API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 0,
  SparseOrderUser     API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 1,
  SparseOrderAMD      API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 2,
  SparseOrderMetis    API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 3,
  SparseOrderCOLAMD   API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 4,
  SparseOrderMTMetis  API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0))  = 5,
);

/*! Specifies type of scaling to be performed.
 *
 *  - term  `SparseScalingDefault`:
 *              Default scaling.
 *
 *    The defaults for `SparseScalingDefault` are:
 *
 *    *  LDL^T : `SparseScalingEquilibriationInf`
 *    * Cholesky : None
 *    * QR : Scaling is not currently supported
 *    * LU : None
 *
 *  - term  `SparseScalingUser`:
 *              User scaling if options.scaling is non-NULL, otherwise no
 *              scaling.
 *  - term  `SparseScalingEquilibriationInf`:
 *              Norm equilibriation scaling using inf norm.
 *  - term `SparseScalingHungarianScalingOnly`:
 *              Scaling using the Hungarian algorithm (similar to MC64).
 *  - term `SparseScalingHungarianScalingAndOrdering`:
 *              Scaling using the Hungarian algorithm (similar to MC64).
 *              Further, the associated matching is used to place large entries on the diagonal.
 *              This option is only valid if a combined symbolic and numeric call to SparseFactor()
 *              is used.
 *              This option is only supported for LU factorizations.
 *
 */
SPARSE_ENUM(SparseScaling, uint8_t,
  SparseScalingDefault                     API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 0,
  SparseScalingUser                        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 1,
  SparseScalingEquilibriationInf           API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11)) = 2,
  SparseScalingHungarianScalingOnly        API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0))  = 3,
  SparseScalingHungarianScalingAndOrdering API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0))  = 4,
);

/*! SparseSymbolicFactorOptions
 *
 *  Options that affect the symbolic stage of a sparse factorization.
 *
 *  - term `control` :
 *    Flags controlling the computation.
 *
 *  - term `orderMethod` :
 *    Ordering algorithm to use.
 *
 *  - term `order` :
 *    User-supplied array for ordering.
 *
 *    Either NULL or a pointer to a permutation that reduces fill in the
 *    matrix being factored.
 *
 *    In the symmetric (Hermitian)  and QR cases order provides a symmetric (Hermitian) row and column permutation.
 *    In the LU case case, the first rowCount entries provide a row permutation,
 *    and the subsequent columnCount entries provide a column permutation.
 *
 *    * If `orderMethod` is `SparseOrderUser`, and this pointer is NULL, the
 *      original matrix ordering is used.
 *    * If `orderMethod` is `SparseOrderUser`, and this pointer is non-NULL,
 *      the user-provided permutation is used to order the matrix before
 *      factorization.
 *    * If `orderMethod` is not `SparseOrderUser`, the factor function will
 *      compute its own fill reducing ordering.
 *    * If this pointer is non-NULL, the computed permutation will be returned in
 *      the array.
 *
 *  - term `ignoreRowsAndColumns` :
 *    Ignore rows and columns listed in this array.
 *
 *    In some cases it is useful to ignore specified rows and columns,
 *    if this array is not NULL, it provides a list of rows and columns to
 *    ignore, terminated by a negative index.
 *
 *    Note that this the row and column indices are for the actual matrix, not
 *    of its block structure, so 0 indicates the first row, not the first
 *    blockSize rows.
 *
 *    In the symmetric (Hermitian) case (Cholesky, LDL^T) each entry indicates that the
 *    matching row AND column should be ignored.
 *
 *    In the unsymmetric case (QR, Cholesky A^TA, LU) an index `i<m` indicates that
 *    row m should be ignored and an index i>=m indicates that column `(i-m)`
 *    should be ignored (where `m` is the number of rows in `A`,
 *    i.e. `m=A.structure.rowCount*A.blockSize` if `A` is not transposed, or
 *    `m=A.structure.columnCount*A.blockSize` if `A` is transposed).
 *
 *    Note that for LU factorization, the use of `ignoreRowsAndColumns` with
 *    `blockSize > 1 `is not supported.
 *
 *  - term `malloc` :
 *    Function to use for allocation of internal memory.
 *
 *    Memory will be freed through the `free()` callback. If this function pointer is `NULL`, the system `malloc()` will be used.
 *
 *    The  `size` parameter specifies the amount of space to allocate in bytes.
 *
 *    The callback returns a pointer to newly allocated memory, or `NULL` if allocation failed.
 *      The returned pointer must be 16-byte aligned (this requirement is
 *      satisfied by the system `malloc()`).
 *
 *  - term `free`  :
 *    Function to use to free memory allocated by malloc() callback.
 *    If this function pointer is `NULL`, the system `free()` will be used.
 *
 *    The `pointer` parameter specifies the to memory to be freed.
 *
 *  - term `reportError`  :
 *    Function to use to report parameter errors.
 *
 *    If `NULL`, errors are logged via `<os/log.h>` and execution is
 *      halted via `__builtin_trap()`.  If non-`NULL`, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *      */
typedef struct {
  SparseControl_t control;
  SparseOrder_t orderMethod;
  int * _Nullable order;
  int *_Nullable ignoreRowsAndColumns;
  void * _Nullable(* _Nonnull malloc)(size_t size);
  void (* _Nonnull free)(void * _Nullable pointer);
  void (* _Nullable reportError)(const char *message);
} SparseSymbolicFactorOptions;

/*! Options that affect the numerical stage of a sparse factorization.
 *
 *  - term `control`:
 *    Flags controlling the computation.
 *
 *  - term `scalingMethod`:
 *    Scaling method to use.
 *
 *  - term `scaling`:      User-supplied array for scaling.
 *    Either NULL or a pointer to an array of real values as follows:
 *    - For symmetric (Hermitian) factorizations, a length n array that is applied as a row scaling `SAx = Sb`.
 *    - For QR factorization, this argument is currently ignored.
 *    - For LU factorizations, a length `m+n` array. The first m entries contain a row scaling,
 *      whilst the subsequent `n` entries contain a column scaling.
 *    The type of the array values is the element type of the matrix.
 *    * If `scalingMethod` is `SparseScalingUser`, and this pointer is `NULL`, no
 *      scaling is applied.
 *    * If `scalingMethod` is `SparseScalingUser`, and this pointer is non-`NULL`,
 *      the user-provided array is used to scale the matrix before factorization.
 *    * If `scalingMethod` is not `SparseScalingUser`, the factor function will
 *      compute its own scaling.
 *    * If this pointer is non-NULL, the computed scaling will be returned in the
 *      array.
 *
 *  - term `pivotTolerance`:
 *    Pivot tolerance used by threshold partial pivoting.
 *
 *    Clamped to range `[0,0.5]`.
 *
 *  - term `zeroTolerance`:
 *    Zero tolerance used by some pivoting modes.
 *
 *    Values less than zeroTolerance in absolute value will be treated as zero.
 */
typedef struct {
  SparseControl_t control;
  SparseScaling_t scalingMethod;
  void * _Nullable scaling;
  double pivotTolerance;
  double zeroTolerance;
} SparseNumericFactorOptions;

/*! A semi-opaque type representing symbolic matrix factorization.
 *
 *   Represents a symbolic matrix factorization (i.e. the pattern of
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
 *  - term `status` :
 *    Indicates status of factorization object.
 *
 *  - term `type` :
 *    Type fo factorization this represents.
 *
 *  - term `rowCount` :
 *    Copy of field from `SparseMatrixStructure` passed to `SparseFactor` call
 *    used to construct this symbolic factorization.
 *
 *  - term `columnCount` :
 *    Copy of field from `SparseMatrixStructure` passed to `SparseFactor` call
 *    used to construct this symbolic factorization.
 *
 *  - term `attributes` :
 *    Copy of field from `SparseMatrixStructure` passed to `SparseFactor` call
 *    used to construct this symbolic factorization.
 *
 *  - term `blockSize` :
 *    Copy of field from `SparseMatrixStructure` passed to `SparseFactor` call
 *    used to construct this symbolic factorization.
 *
 *  - term `factorization` :
 *    Pointer to private internal representation of symbolic factor.
 *
 *  - term `workspaceSize_Float` :
 *    Size, in bytes, of workspace required to perform numerical factorization
 *    in float. Double the size when used in complex float.
 *
 *  - term `workspaceSize_Double` :
 *    Size, in bytes, of workspace required to perform numerical factorization
 *    in double. Double the size when used in complex double.
 *
 *  - term `factorSize_Float` :
 *    Minimum size, in bytes, required to store numerical factors in float.
 *    If numerical pivoting requires a pivot to be delayed, the actual size
 *    required may be larger. Double the size when used in complex float.
 *
 *  - term `factorSize_Double` :
 *    Minimum size, in bytes, required to store numerical factors in double.
 *    If numerical pivoting requires a pivot to be delayed, the actual size
 *    required may be larger. Double the size when used in complex double.
 */
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

/*! A semi-opaque type representing a matrix factorization in double.
 *
 *   Use the `SparseCleanup` function to free resources held
 *  by these objects.
 *
 *  The object can be in one of the following states:
 *  1) Something went wrong with symbolic factorization, nothing is valid.
 *     - indicated by `.symbolicFactorization.status < 0`
 *  2) Symbolic factorization was good, but failed in numeric factorization
 *     initialization.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization == NULL`
 *     - symbolic factorization may be used for future calls.
 *  3) Symbolic factorization was good, factor allocated/initialized correctly,
 *     but numeric factorization failed
 *     e.g. a Cholesky factorization of an indefinite matrix was attempted.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization not NULL`
 *     - user may pass this object to `SparseRefactor_Double` with a modified matrix
 *  4) Symbolic and numeric factorizations are both good
 *     - indicated by `.status >= 0`
 *
 * - term `status` :
 *    Indicates status of factorization object.
 *
 * - term `attributes` :
 *    Flags associated with this factorization object. In particular, transpose
 *    field indicates whether object is considered to be factorization of A or
 *    A^T.
 *
 * - term `symbolicFactorization` :
 *    Symbolic Factorization upon which this Numeric Factorization depends.
 *
 * - term `userFactorStorage` :
 *    Flag that indicates if user provided storage backing this object. If
 *    true, then factor storage must be freed by the user once all references
 *    are finished with (though any additional storage allocated due to pivoting
 *    will still be freed by `SparseCleanup`).
 *
 * - term `numericFactorization` :
 *    Pointer to private internal representation of numeric factor.
 *
 * - term `solveWorkspaceRequiredStatic` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.
 *
 * - term `solveWorkspaceRequiredPerRHS` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.                    */
typedef struct {
  SparseStatus_t status;
  SparseAttributes_t attributes;
  SparseOpaqueSymbolicFactorization symbolicFactorization;
  bool userFactorStorage;
  void *_Nullable numericFactorization;
  size_t solveWorkspaceRequiredStatic;
  size_t solveWorkspaceRequiredPerRHS;
} SparseOpaqueFactorization_Double;

/*! A semi-opaque type representing a matrix factorization in float.
 *
 *   Use the `SparseCleanup` function to free resources held
 *  by these objects.
 *
 *  The object can be in one of the following states:
 *  1) Something went wrong with symbolic factorization, nothing is valid.
 *     - indicated by `.symbolicFactorization.status < 0`
 *  2) Symbolic factorization was good, but failed in numeric factorization
 *     initialization.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization == NULL`
 *     - symbolic factorization may be used for future calls.
 *  3) Symbolic factorization was good, factor allocated/initialized correctly,
 *     but numeric factorization failed
 *     e.g. a Cholesky factorization of an indefinite matrix was attempted.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization not NULL`
 *     - user may pass this object to `SparseRefactor_Double` with a modified matrix
 *  4) Symbolic and numeric factorizations are both good
 *     - indicated by `.status >= 0`
 *
 * - term `status` :
 *    Indicates status of factorization object.
 *
 * - term `attributes` :
 *    Flags associated with this factorization object. In particular, transpose
 *    field indicates whether object is considered to be factorization of A or
 *    A^T.
 *
 * - term `symbolicFactorization` :
 *    Symbolic Factorization upon which this Numeric Factorization depends.
 *
 * - term `userFactorStorage` :
 *    Flag that indicates if user provided storage backing this object. If
 *    true, then factor storage must be freed by the user once all references
 *    are finished with (though any additional storage allocated due to pivoting
 *    will still be freed by `SparseCleanup`).
 *
 * - term `numericFactorization` :
 *    Pointer to private internal representation of numeric factor.
 *
 * - term `solveWorkspaceRequiredStatic` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.
 *
 * - term `solveWorkspaceRequiredPerRHS` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.                    */
typedef struct {
  SparseStatus_t status;
  SparseAttributes_t attributes;
  SparseOpaqueSymbolicFactorization symbolicFactorization;
  bool userFactorStorage;
  void *_Nullable numericFactorization;
  size_t solveWorkspaceRequiredStatic;
  size_t solveWorkspaceRequiredPerRHS;
} SparseOpaqueFactorization_Float;

/*! A semi-opaque type representing a matrix factorization in complex double.
 *
 *   Use the `SparseCleanup` function to free resources held
 *  by these objects.
 *
 *  The object can be in one of the following states:
 *  1) Something went wrong with symbolic factorization, nothing is valid.
 *     - indicated by `.symbolicFactorization.status < 0`
 *  2) Symbolic factorization was good, but failed in numeric factorization
 *     initialization.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization == NULL`
 *     - symbolic factorization may be used for future calls.
 *  3) Symbolic factorization was good, factor allocated/initialized correctly,
 *     but numeric factorization failed
 *     e.g. a Cholesky factorization of an indefinite matrix was attempted.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization not NULL`
 *     - user may pass this object to `SparseRefactor_Double` with a modified matrix
 *  4) Symbolic and numeric factorizations are both good
 *     - indicated by `.status >= 0`
 *
 * - term `status` :
 *    Indicates status of factorization object.
 *
 * - term `attributes` :
 *    Flags associated with this factorization object. In particular, transpose
 *    field indicates whether object is considered to be factorization of A or
 *    A^T.
 *
 * - term `symbolicFactorization` :
 *    Symbolic Factorization upon which this Numeric Factorization depends.
 *
 * - term `userFactorStorage` :
 *    Flag that indicates if user provided storage backing this object. If
 *    true, then factor storage must be freed by the user once all references
 *    are finished with (though any additional storage allocated due to pivoting
 *    will still be freed by `SparseCleanup`).
 *
 * - term `numericFactorization` :
 *    Pointer to private internal representation of numeric factor.
 *
 * - term `solveWorkspaceRequiredStatic` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.
 *
 * - term `solveWorkspaceRequiredPerRHS` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.                    */
typedef struct {
  SparseStatus_t status;
  SparseAttributesComplex_t attributes;
  SparseOpaqueSymbolicFactorization symbolicFactorization;
  bool userFactorStorage;
  void *_Nullable numericFactorization;
  size_t solveWorkspaceRequiredStatic;
  size_t solveWorkspaceRequiredPerRHS;
} SparseOpaqueFactorization_Complex_Double;

/*! A semi-opaque type representing a matrix factorization in complex float.
 *
 *   Use the `SparseCleanup` function to free resources held
 *  by these objects.
 *
 *  The object can be in one of the following states:
 *  1) Something went wrong with symbolic factorization, nothing is valid.
 *     - indicated by `.symbolicFactorization.status < 0`
 *  2) Symbolic factorization was good, but failed in numeric factorization
 *     initialization.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization == NULL`
 *     - symbolic factorization may be used for future calls.
 *  3) Symbolic factorization was good, factor allocated/initialized correctly,
 *     but numeric factorization failed
 *     e.g. a Cholesky factorization of an indefinite matrix was attempted.
 *     - indicated by `.symbolicFactorization.status >= 0 && .status < 0 && .numericFactorization not NULL`
 *     - user may pass this object to `SparseRefactor_Double` with a modified matrix
 *  4) Symbolic and numeric factorizations are both good
 *     - indicated by `.status >= 0`
 *
 * - term `status` :
 *    Indicates status of factorization object.
 *
 * - term `attributes` :
 *    Flags associated with this factorization object. In particular, transpose
 *    field indicates whether object is considered to be factorization of A or
 *    A^T.
 *
 * - term `symbolicFactorization` :
 *    Symbolic Factorization upon which this Numeric Factorization depends.
 *
 * - term `userFactorStorage` :
 *    Flag that indicates if user provided storage backing this object. If
 *    true, then factor storage must be freed by the user once all references
 *    are finished with (though any additional storage allocated due to pivoting
 *    will still be freed by `SparseCleanup`).
 *
 * - term `numericFactorization` :
 *    Pointer to private internal representation of numeric factor.
 *
 * - term `solveWorkspaceRequiredStatic` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.
 *
 * - term `solveWorkspaceRequiredPerRHS` :
 *    The required size of workspace, in bytes, for a call to `SparseSolve` is
 *    `solveWorkspaceRequiredStatic + nrhs * solveWorkspaceRequiredPerRHS`
 *    where `nrhs` is the number of right-hand side vectors.                    */
typedef struct {
  SparseStatus_t status;
  SparseAttributesComplex_t attributes;
  SparseOpaqueSymbolicFactorization symbolicFactorization;
  bool userFactorStorage;
  void *_Nullable numericFactorization;
  size_t solveWorkspaceRequiredStatic;
  size_t solveWorkspaceRequiredPerRHS;
} SparseOpaqueFactorization_Complex_Float;
/*******************************************************************************
 * @group Sub-factor Types
 ******************************************************************************/

/*! Types of sub-factor object.
 *
 *  - term `SparseSubfactorInvalid` :
 *    Invalid subfactor (requested type not compatible with supplied factorization
 *    or already destroyed).
 *  - term `SparseSubfactorP` :
 *    Permutation subfactor, valid for all factorization types.
 *    (this is the row permutation for LU factorization)
 *  - term `SparseSubfactorS` :
 *    Diagonal scaling subfactor, valid for Cholesky and LDL^T only.
 *  - term `SparseSubfactorL` :
 *    L factor subfactor, valid for Cholesky and LDL^T only.
 *  - term `SparseSubfactorD` :
 *    D factor subfactor, valid for LDL^T only.
 *  - term `SparseSubfactorPLPS` :
 *    Half-solve subfactor, valid for Cholesky and LDL^T only.
 *    Corresponds to PLP' on forward (non-transpose) solve, and
 *    corresponds to PLDP' on backward (transpose) solve (D=I for Chokesky).
 *  - term `SparseSubfactorQ` :
 *    Q factor subfactor, valid for QR only.
 *    Column permutation, valid for LU only.
 *  - term `SparseSubfactorR` :
 *    R factor subfactor, valid for QR and CholeskyAtA only.
 *  - term `SparseSubfactorRP` :
 *    Half-solve subfactor, valid for QR and CholeskyAtA only.
 *  - term `SparseSubfactorSr` :
 *    Diagonal row scaling subfactor, valid for LU only.
 *  - term `SparseSubfactorSc` :
 *    Diagonal column scaling subfactor, valid for LU only.
 */
SPARSE_ENUM(SparseSubfactor, uint8_t,
        SparseSubfactorInvalid  API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 0,
        SparseSubfactorP        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 1,
        SparseSubfactorS        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 2,
        SparseSubfactorL        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 3,
        SparseSubfactorD        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 4,
        SparseSubfactorPLPS     API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 5,
        SparseSubfactorQ        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 6,
        SparseSubfactorR        API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 7,
        SparseSubfactorRP       API_AVAILABLE(macos(10.13), ios(11), watchos(4), tvos(11))        = 8,
        SparseSubfactorSr       API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 9,
        SparseSubfactorSc       API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 10,
        );

/*! Represents a sub-factor of the factorization (for example,  `L` from `LDL^T`).
 *
 *  - term `attributes` :
 *    Attributes of subfactor. Notably transpose indicates whether it should be
 *    considered as the transpose of its underlying contents (e.g. should it
 *    count as L or L^T if `.contents=SparseSubfactorL`).
 *  - term `contents` :
 *    Subfactor this represents, e.g. L or Q.
 *  - term `factor` :
 *    Underlying factorization this subfactor is part of.
 *  - term `workspaceRequiredStatic` :
 *    The size of the workspace, in bytes, required to perform `SparseMultiply`
 *    or `SparseSolve` with this subfactor is given by the expression:
 *    `workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs`
 *    where `nrhs` is the number of right-hand side vectors.
 *  - term `workspaceRequiredPerRHS` :
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

/*! Represents a sub-factor of the factorization (for example,  `L` from `LDL^T`).
 *
 *  - term `attributes` :
 *    Attributes of subfactor. Notably transpose indicates whether it should be
 *    considered as the transpose of its underlying contents (e.g. should it
 *    count as L or L^T if `.contents=SparseSubfactorL`).
 *  - term `contents` :
 *    Subfactor this represents, e.g. L or Q.
 *  - term `factor` :
 *    Underlying factorization this subfactor is part of.
 *  - term `workspaceRequiredStatic` :
 *    The size of the workspace, in bytes, required to perform `SparseMultiply`
 *    or `SparseSolve` with this subfactor is given by the expression:
 *    `workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs`
 *    where `nrhs` is the number of right-hand side vectors.
 *  - term `workspaceRequiredPerRHS` :
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

/*! Represents a sub-factor of the factorization (for example,  `L` from `LDL^T`).
 *
 *  - term `attributes` :
 *    Attributes of subfactor. Notably transpose indicates whether it should be
 *    considered as the transpose of its underlying contents (e.g. should it
 *    count as L or L^T if `.contents=SparseSubfactorL`).
 *  - term `contents` :
 *    Subfactor this represents, e.g. L or Q.
 *  - term `factor` :
 *    Underlying factorization this subfactor is part of.
 *  - term `workspaceRequiredStatic` :
 *    The size of the workspace, in bytes, required to perform `SparseMultiply`
 *    or `SparseSolve` with this subfactor is given by the expression:
 *    `workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs`
 *    where `nrhs` is the number of right-hand side vectors.
 *  - term `workspaceRequiredPerRHS` :
 *    The size of the workspace, in bytes, required to perform SparseMultiply()
 *    or SparseSolve() with this subfactor is given by the expression:
 *    workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs
 *    where nrhs is the number of right-hand side vectors.
 */
typedef struct {
  SparseAttributesComplex_t attributes;
  SparseSubfactor_t contents;
  SparseOpaqueFactorization_Complex_Double factor;
  size_t workspaceRequiredStatic;
  size_t workspaceRequiredPerRHS;
} SparseOpaqueSubfactor_Complex_Double;

/*! Represents a sub-factor of the factorization (for example,  `L` from `LDL^T`).
 *
 *  - term `attributes` :
 *    Attributes of subfactor. Notably transpose indicates whether it should be
 *    considered as the transpose of its underlying contents (e.g. should it
 *    count as L or L^T if `.contents=SparseSubfactorL`).
 *  - term `contents` :
 *    Subfactor this represents, e.g. L or Q.
 *  - term `factor` :
 *    Underlying factorization this subfactor is part of.
 *  - term `workspaceRequiredStatic` :
 *    The size of the workspace, in bytes, required to perform `SparseMultiply`
 *    or `SparseSolve` with this subfactor is given by the expression:
 *    `workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs`
 *    where `nrhs` is the number of right-hand side vectors.
 *  - term `workspaceRequiredPerRHS` :
 *    The size of the workspace, in bytes, required to perform SparseMultiply()
 *    or SparseSolve() with this subfactor is given by the expression:
 *    workspaceRequiredStatic + nrhs*workspaceRequiredPerRhs
 *    where nrhs is the number of right-hand side vectors.
 */
typedef struct {
  SparseAttributesComplex_t attributes;
  SparseSubfactor_t contents;
  SparseOpaqueFactorization_Complex_Float factor;
  size_t workspaceRequiredStatic;
  size_t workspaceRequiredPerRHS;
} SparseOpaqueSubfactor_Complex_Float;

/*******************************************************************************
 * @group Low-rank Update Types
 ******************************************************************************/

/*! Low-rank update algorithm selector
 *
 *  
 *  See `SparseUpdateFactor()` for a full description of these updates.
 *
 *  - term `SparseUpdatePartialRefactor`:
 *    Perform update using a partial refactorization of the matrix
 *
 **/
SPARSE_ENUM(SparseUpdate, uint8_t,
  SparseUpdatePartialRefactor       API_AVAILABLE(macos(15.5), ios(18.5), watchos(11.5), tvos(18.5))  = 0,
);

/******************************************************************************
 *  @group Matrix and Vector Operations (Sparse BLAS Wrappers)
 ******************************************************************************/

/**** Multiplication **********************************************************/

/*! Performs the multiplication `Y = AX` for double values
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.
 *  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `Y = AX` for float values.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.
 *  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `Y = AX` for complex double values.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.
 * */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `Y = AX` for complex float values.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.
 * */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `Y = alpha * AX` for double values
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(double alpha, SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `Y = alpha * AX` for float values
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(float alpha, SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `Y = alpha * AX` for complex double values
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(__SPARSE_double_complex alpha, SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `Y = alpha * AX` for complex float values
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(__SPARSE_float_complex alpha, SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `y = Ax` for double values
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `y = Ax` for float values
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `y = Ax` for complex double values
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Complex_Double A, DenseVector_Complex_Double x, DenseVector_Complex_Double y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `y = Ax` for complex float values
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseMatrix_Complex_Float A, DenseVector_Complex_Float x, DenseVector_Complex_Float y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `y = alpha * Ax` for double values
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(double alpha, SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `y = alpha * Ax` for float values.
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(float alpha, SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs the multiplication `y = alpha * Ax` for complex double values.
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(__SPARSE_double_complex alpha, SparseMatrix_Complex_Double A, DenseVector_Complex_Double x, DenseVector_Complex_Double y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs the multiplication `y = alpha * Ax` for complex float values.
 *
 *  - Parameter alpha: (input) scale to apply to the result.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(__SPARSE_float_complex alpha, SparseMatrix_Complex_Float A, DenseVector_Complex_Float x, DenseVector_Complex_Float y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/**** Multipy-Add *************************************************************/

/*! Performs `Y += AX` for double values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `X`: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter `Y`: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `Y += AX` for float values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `X`: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter `Y`: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `Y += AX` for complex double values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `X`: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter `Y`: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `Y += AX` for complex float values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `X`: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter `Y`: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with their product.                               */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `Y += alpha * AX` for double values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `X`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(double alpha, SparseMatrix_Double A, DenseMatrix_Double X, DenseMatrix_Double Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `Y += alpha * AX` for float values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `X`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(float alpha, SparseMatrix_Float A, DenseMatrix_Float X, DenseMatrix_Float Y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `Y += alpha * AX` for complex double values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `X`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(__SPARSE_double_complex alpha, SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `Y += alpha * AX` for complex float values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `X`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter X: (input) dense matrix. Inner dimensions of `A` and `X` must match.
 *
 *  - Parameter Y: (output) dense matrix. Dimensions must match the outer dimensions
 *  of `A` and `X`. Overwritten with `alpha * AX`.                                  */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(__SPARSE_float_complex alpha, SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `y += Ax` for double values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `x`: (input) dense vector.
 *
 *  - Parameter `y`: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `y += Ax` for float values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `x`: (input) dense vector.
 *
 *  - Parameter `y`: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `y += Ax` for complex double values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `x`: (input) dense vector.
 *
 *  - Parameter `y`: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Complex_Double A, DenseVector_Complex_Double x, DenseVector_Complex_Double y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `y += Ax` for complex float values
 *
 *  - Parameter `A`: (input) sparse matrix.
 *
 *  - Parameter `x`: (input) dense vector.
 *
 *  - Parameter `y`: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(SparseMatrix_Complex_Float A, DenseVector_Complex_Float x, DenseVector_Complex_Float y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `y += alpha * Ax` for double values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `x`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(double alpha, SparseMatrix_Double A, DenseVector_Double x, DenseVector_Double y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `y += alpha * Ax` for float values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `x`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(float alpha, SparseMatrix_Float A, DenseVector_Float x, DenseVector_Float y)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Performs `y += alpha * Ax` for complex double values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `x`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(__SPARSE_double_complex alpha, SparseMatrix_Complex_Double A, DenseVector_Complex_Double x, DenseVector_Complex_Double y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Performs `y += alpha * Ax` for complex float values
 *
 *  - Parameter alpha: (input) scale to apply to the product of `A` and `x`.
 *
 *  - Parameter A: (input) sparse matrix.
 *
 *  - Parameter x: (input) dense vector.
 *
 *  - Parameter y: (output) dense vector.                                           */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiplyAdd(__SPARSE_float_complex alpha, SparseMatrix_Complex_Float A, DenseVector_Complex_Float x, DenseVector_Complex_Float y)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/******************************************************************************
 *  @group Transposition
 ******************************************************************************/

/*! Returns a transposed copy of the specified matrix of double values.
 *
 *   Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  - Parameter Matrix: The matrix to transpose.
 *
 *  - Returns: A copy of matrix with `A.structure.attributes.transpose` flipped.  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseMatrix_Double SparseGetTranspose(SparseMatrix_Double Matrix);

/*! Returns a transposed copy of the specified matrix of float values.
 *
 *   Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  - Parameter Matrix: The matrix to transpose.
 *
 *  - Returns: A copy of matrix with `matrix.structure.attributes.transpose` bit
 *           flipped.                                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseMatrix_Float SparseGetTranspose(SparseMatrix_Float Matrix);

/*! Returns a transposed copy of the specified matrix of complex double values.
 *
 *   Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  - Parameter Matrix: The matrix to transpose.
 *
 *  - Returns: A copy of matrix with `matrix.structure.attributes.transpose` bit
 *           flipped and `matrix.structure.attributes.conjugate_transpose` bit cleared.    */

static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseMatrix_Complex_Double SparseGetTranspose(SparseMatrix_Complex_Double Matrix) ;

/*! Returns a transposed copy of the specified matrix of complex float values.
 *
 *   Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  - Parameter Matrix: The matrix to transpose.
 *
 *  - Returns: A copy of matrix with `matrix.structure.attributes.transpose` bit
 *           flipped and `matrix.structure.attributes.conjugate_transpose` bit cleared.    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseMatrix_Complex_Float SparseGetTranspose(SparseMatrix_Complex_Float Matrix) ;

/*! Returns a conjugate transposed copy of the specified specified matrix of complex double values.
 *
 *   Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  - Parameter Matrix: The matrix to conjugate transpose.
 *
 *  - Returns: A copy of matrix with `matrix.structure.attributes.transpose` bit
 *           flipped and `matrix.structure.attributes.conjugate_transpose` bit set.    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseMatrix_Complex_Double SparseGetConjugateTranspose(SparseMatrix_Complex_Double Matrix) ;

/*! Returns a conjugate transposed copy of the specified matrix of complex float values.
 *
 *   Note that the underlying storage is *not* reference counted,
 *  so users must ensure the original matrix (or at least its underlying
 *  storage) is not destroyed before they are finished with the matrix returned
 *  by this routine.
 *
 *  - Parameter Matrix: The matrix to conjugate transpose.
 *
 *  - Returns: A copy of matrix with `matrix.structure.attributes.transpose` bit
 *           flipped and `matrix.structure.attributes.conjugate_transpose` bit set.    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseMatrix_Complex_Float SparseGetConjugateTranspose(SparseMatrix_Complex_Float Matrix) ;


/*! Returns a transposed, reference-counted copy of a `SparseOpaqueFactorization_Double`.
 *
 *  - Parameter Factor: The factorization to transpose.
 *
 *  - Returns: A matrix factorization of `A^T`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseGetTranspose(SparseOpaqueFactorization_Double Factor);

/*! Returns a transposed, reference-counted copy of a `SparseOpaqueFactorization_Float`.
 *
 *  - Parameter Factor: The factorization to transpose.
 *
 *  - Returns: A matrix factorization of `A^T`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseGetTranspose(SparseOpaqueFactorization_Float Factor);

/*! Returns a transposed, reference-counted copy of a `SparseOpaqueFactorization_Complex_Double`.
 *
 *  - Parameter Factor: The factorization to transpose.
 *
 *  - Returns: A matrix factorization of `A^T`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseGetTranspose(SparseOpaqueFactorization_Complex_Double Factor) ;

/*! Returns a transposed, reference-counted copy of a `SparseOpaqueFactorization_Complex_Float`.
 *
 *  - Parameter Factor: The factorization to transpose.
 *
 *  - Returns: A matrix factorization of `A^T`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseGetTranspose(SparseOpaqueFactorization_Complex_Float Factor) ;

/*! Returns a conjugate transposed, reference-counted copy of a `SparseOpaqueFactorization_Complex_Double`.
 *
 *  - Parameter Factor: The factorization to conjugate transpose.
 *
 *  - Returns: A matrix factorization of `A^H`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseGetConjugateTranspose(SparseOpaqueFactorization_Complex_Double Factor) ;

/*! Returns a conjugate transposed, reference-counted copy of a `SparseOpaqueFactorization_Complex_Float`.
 *
 *  - Parameter Factor: The factorization to conjugate transpose.
 *
 *  - Returns: A matrix factorization of `A^H`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseGetConjugateTranspose(SparseOpaqueFactorization_Complex_Float Factor) ;


/*! Returns a transposed, reference-counted copy of a `SparseOpaqueSubfactor_Double`.
 *
 *  - Parameter Subfactor: The object to transpose.
 *
 *  - Returns: A subfactor equivalent to the transpose of the one provided. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Double SparseGetTranspose(SparseOpaqueSubfactor_Double Subfactor);

/*! Returns a transposed, reference-counted copy of a `SparseOpaqueSubfactor_Float`.
 *
 *  - Parameter Subfactor: The object to transpose.
 *
 *  - Returns: A subfactor equivalent to the transpose of the one provided. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Float SparseGetTranspose(SparseOpaqueSubfactor_Float Subfactor);

/*! Returns a transposed, reference-counted copy of a `SparseOpaqueSubfactor_Complex_Double`.
 *
 *  - Parameter Subfactor: The object to transpose.
 *
 *  - Returns: A subfactor equivalent to the transpose of the one provided. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueSubfactor_Complex_Double SparseGetTranspose(SparseOpaqueSubfactor_Complex_Double Subfactor) ;

/*! Returns a transposed, reference-counted copy of a `SparseOpaqueSubfactor_Complex_Float`.
 *
 *  - Parameter Subfactor: The object to transpose.
 *
 *  - Returns: A subfactor equivalent to the transpose of the one provided. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueSubfactor_Complex_Float SparseGetTranspose(SparseOpaqueSubfactor_Complex_Float Subfactor) ;

/*! Returns a conjugate transposed, reference-counted copy of a `SparseOpaqueSubfactor_Complex_Double`.
 *
 *  - Parameter Subfactor: The object to conjugate transpose.
 *
 *  - Returns: A matrix factorization of `A^H`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueSubfactor_Complex_Double SparseGetConjugateTranspose(SparseOpaqueSubfactor_Complex_Double Subfactor) ;

/*! Returns a conjugate transposed, reference-counted copy of a `SparseOpaqueSubfactor_Complex_Float`.
 *
 *  - Parameter Subfactor: The object to conjugate transpose.
 *
 *  - Returns: A matrix factorization of `A^H`, where the original was of `A`. As
 *           this is reference counted, it must be freed through a call to
 *           `SparseCleanup` once it is no longer required.                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueSubfactor_Complex_Float SparseGetConjugateTranspose(SparseOpaqueSubfactor_Complex_Float Subfactor) ;


/******************************************************************************
 *  @group Sparse Factor Functions
 ******************************************************************************/

/**** All-in-one Sparse Factor Functions **************************************/

/*! Returns the specified factorization of a sparse matrix of double
 *            values.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseFactorization_t type, SparseMatrix_Double Matrix);

/*! Returns the specified factorization of a sparse matrix of float
 *            values.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.                                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseFactorization_t type, SparseMatrix_Float Matrix);

/*! Returns the specified factorization of a sparse matrix of complex double
 *            values.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.                                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseFactor(SparseFactorization_t type, SparseMatrix_Complex_Double Matrix) ;

/*! Returns the specified factorization of a sparse matrix of complex float
 *            values.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.                                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseFactor(SparseFactorization_t type, SparseMatrix_Complex_Float Matrix) ;

/*! Returns the specified factorization of a sparse matrix of double
 *            values, using the specified options.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter sfoptions: Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseFactorization_t type, SparseMatrix_Double Matrix, SparseSymbolicFactorOptions sfoptions, SparseNumericFactorOptions nfoptions);

/*! Returns the specified factorization of a sparse matrix of float
 *            values, using the specified options.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter sfoptions: Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseFactorization_t type, SparseMatrix_Float Matrix, SparseSymbolicFactorOptions sfoptions, SparseNumericFactorOptions nfoptions);

/*! Returns the specified factorization of a sparse matrix of complex double
 *            values, using the specified options.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter sfoptions: Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseFactor(SparseFactorization_t type, SparseMatrix_Complex_Double Matrix, SparseSymbolicFactorOptions sfoptions, SparseNumericFactorOptions nfoptions) ;

/*! Returns the specified factorization of a sparse matrix of complex float
 *            values, using the specified options.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter sfoptions: Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseFactor(SparseFactorization_t type, SparseMatrix_Complex_Float Matrix, SparseSymbolicFactorOptions sfoptions, SparseNumericFactorOptions nfoptions) ;

/**** Sparse Factor Functions using pre-calculated symbolic factors ***********/

/*! Returns the factorization of a sparse matrix of double values
 *            corresponding to the supplied symbolic factorization.
 *
 *  - Parameter SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix The matrix to factorize.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Double Matrix);

/*! Returns the factorization of a sparse matrix of float values
 *            corresponding to the supplied symbolic factorization.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Float Matrix);

/*! Returns the factorization of a sparse matrix of complex double values
 *            corresponding to the supplied symbolic factorization.
 *
 *  - Parameter SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix The matrix to factorize.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Complex_Double Matrix) ;

/*! Returns the factorization of a sparse matrix of complex float values
 *            corresponding to the supplied symbolic factorization.
 *
 *  - Parameter SymbolicFactor A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix The matrix to factorize.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Complex_Float Matrix) ;

/*! Returns the factorization of a sparse matrix of double values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Double Matrix, SparseNumericFactorOptions nfoptions);

/*! Returns the factorization of a sparse matrix of float values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Float Matrix, SparseNumericFactorOptions nfoptions);

/*! Returns the factorization of a sparse matrix of complex double values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Complex_Double Matrix, SparseNumericFactorOptions nfoptions) ;

/*! Returns the factorization of a sparse matrix of complex float values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseFactor(SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Complex_Float Matrix, SparseNumericFactorOptions nfoptions) ;

/**** Sparse Factor Functions with user-defined workspace *********************/

/*! Returns the factorization of a sparse matrix of double values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options and without any internal memory allocations.
 *
 *   Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a `sfoptions.malloc()` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc()` returns NULL the
 *  factorization will abort immediately.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter factorStorage: A pointer to space used to store the factorization
 *         of size at least `SymbolicFactor.factorSize_Double` bytes. This storage
 *         should not be altered by the user during the lifetime of the return
 *         value. This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `SymbolicFactor.workspaceSize_Double` bytes. This workspace may be
 *         reused or destroyed by the user as soon as the function returns.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseFactor(
  SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Double Matrix,
  SparseNumericFactorOptions nfoptions, void *_Nullable factorStorage,
  void *_Nullable workspace);

/*! Returns the factorization of a sparse matrix of float values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options and without any internal memory allocations.
 *
 *   Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a `sfoptions.malloc()` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc()` returns NULL the
 *  factorization will abort immediately.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter factorStorage: A pointer to space used to store the factorization
 *         of size at least `SymbolicFactor.factorSize_Float` bytes. This storage
 *         should not be altered by the user during the lifetime of the return
 *         value. This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `SymbolicFactor.workspaceSize_Float` bytes. This workspace may be
 *         reused or destroyed by the user as soon as the function returns.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseFactor(
  SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Float Matrix,
  SparseNumericFactorOptions nfoptions, void *_Nullable factorStorage,
  void *_Nullable workspace);

/*! Returns the factorization of a sparse matrix of complex double values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options and without any internal memory allocations.
 *
 *   Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a `sfoptions.malloc()` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc()` returns NULL the
 *  factorization will abort immediately.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter factorStorage: A pointer to space used to store the factorization
 *         of size at least `SymbolicFactor.factorSize_Double * 2` bytes. This storage
 *         should not be altered by the user during the lifetime of the return
 *         value. This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `SymbolicFactor.workspaceSize_Double * 2` bytes. This workspace may be
 *         reused or destroyed by the user as soon as the function returns.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Double SparseFactor(
  SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Complex_Double Matrix,
  SparseNumericFactorOptions nfoptions, void *_Nullable factorStorage,
  void *_Nullable workspace) ;

/*! Returns the factorization of a sparse matrix of complex float values
 *            corresponding to the supplied symbolic factorization, using the
 *            specified options and without any internal memory allocations.
 *
 *   Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply a `sfoptions.malloc()` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc()` returns NULL the
 *  factorization will abort immediately.
 *
 *  - Parameter SymbolicFactor: A symbolic factorization, as returned by a call of the
 *         form `SymbolicFactor = SparseFactor(Matrix.structure)`.
 *
 *  - Parameter Matrix: The matrix to factorize.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter factorStorage: A pointer to space used to store the factorization
 *         of size at least `SymbolicFactor.factorSize_Float * 2` bytes. This storage
 *         should not be altered by the user during the lifetime of the return
 *         value. This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `SymbolicFactor.workspaceSize_Float * 2` bytes. This workspace may be
 *         reused or destroyed by the user as soon as the function returns.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 *
 *  - Returns: Factorization of Matrix.                                         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) )
SparseOpaqueFactorization_Complex_Float SparseFactor(
  SparseOpaqueSymbolicFactorization SymbolicFactor, SparseMatrix_Complex_Float Matrix,
  SparseNumericFactorOptions nfoptions, void *_Nullable factorStorage,
  void *_Nullable workspace) ;

/******************************************************************************
 *  @group Sparse Direct Solve Functions (DenseMatrix)
 ******************************************************************************/

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.                                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored, DenseMatrix_Double XB);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.                                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float XB);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.                                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored, DenseMatrix_Complex_Double XB);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.                                                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored, DenseMatrix_Complex_Float XB);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Double`
 *            of A`,` in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored, DenseMatrix_Double B, DenseMatrix_Double X);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Float`
 *            of A`,` in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float B, DenseMatrix_Float X);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of A`,` in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored, DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double X);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of A`,` in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is A=QR and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored, DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float X);

/**** Solving Systems with User Defined Workspace *****************************/

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`, in place, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseMatrix_Double XB, void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`, in place, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float XB,
  void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`, in place, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored,
  DenseMatrix_Complex_Double XB, void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`, in place, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter XB: On entry, the right-hand sides `B`. On return, the solution vectors
 *         `X`. If `A` has dimension `m x n`, then `XB` must have dimension `k x nrhs`,
 *         where `k=max(m,n)` and nrhs is the number of right-hand sides to find
 *         solutions for.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored,
  DenseMatrix_Complex_Float XB, void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseMatrix_Double X, DenseMatrix_Double B, void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseMatrix_Float X,
  DenseMatrix_Float B, void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored,
  DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double B, void *workspace);

/*! Solves the system `AX=B` for `X`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`, and without any internal memory allocations.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: Matrix in which to return solutions. If `A` has dimension `m x n`, and
 *         `B` has dimension `m x nrhs`, then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + nrhs * Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored,
  DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float B, void *workspace);

/******************************************************************************
 *  @group Sparse Direct Solve Functions (DenseVector)
 ******************************************************************************/

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`, in place.
 *
 *   If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a `factorization of type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If A has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.                                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double xb);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`, in place.
 *
 *   If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a `factorization of type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If A has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.                                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float xb);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`, in place.
 *
 *   If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a `factorization of type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If A has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.                                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored,
  DenseVector_Complex_Double xb);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`, in place.
 *
 *   If the factorization is A=QR and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a `factorization of type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If A has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.                                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored,
  DenseVector_Complex_Float xb);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double b, DenseVector_Double x);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float b,
  DenseVector_Float x);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored,
  DenseVector_Complex_Double b, DenseVector_Complex_Double x);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.                                              */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored,
  DenseVector_Complex_Float b, DenseVector_Complex_Float x);

/**** Solving Systems with User Defined Workspace *****************************/

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If `A` has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double xb, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If `A` has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored,
  DenseVector_Float xb, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If `A` has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored,
  DenseVector_Complex_Double xb, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter xb: On entry, the right-hand side `b`. On return, the solution vector
 *         `x`. If `A` has dimension `m x n`, then `xb` must have length `k`, where
 *         `k=max(m,n)`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored,
  DenseVector_Complex_Float xb, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Double`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Double Factored,
  DenseVector_Double x, DenseVector_Double b, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Float`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueFactorization_Float Factored, DenseVector_Float x,
  DenseVector_Float b, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Double`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Double Factored,
  DenseVector_Complex_Double x, DenseVector_Complex_Double b, void *workspace);

/*! Solves the system `Ax=b` for `x`, using the supplied `SparseOpaqueFactorization_Complex_Float`
 *            of `A`, in place.
 *
 *   If the factorization is `A=QR` and the system is underdetermined,
 *  the solution of minimum norm `|| x ||_2` is returned.
 *  If the factorization is `A=QR` and the system is overdetermined, the least
 *  squares solution `arg min_x || Ax - b ||_2` is returned.
 *  In the case of a factorization of `type=SparseCholeskyAtA`, the factorization
 *  is in fact of `A^T A`, so the solution returned is for the system `A^TAx=b`.
 *
 *  - Parameter Factored: A factorization of `A`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: Vector in which to return solution. If `A` has dimension `m x n`, then
 *         `x` must have length `n`.
 *
 *  - Parameter workspace: Scratch space of size
 *         `Factored.solveWorkspaceRequiredStatic + 1*Factored.solveWorkspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by malloc() has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueFactorization_Complex_Float Factored,
  DenseVector_Complex_Float x, DenseVector_Complex_Float b, void *workspace);

/******************************************************************************
 *  @group Advanced Solving Functions
 ******************************************************************************/

/**** Symbolic Factorization Functions ****************************************/

/*! Returns a symbolic factorization of the requested type for a
 *            matrix with the given structure.
 *
 *   The resulting symbolic factorization may be used for multiple
 *  numerical factorizations with different numerical values but the same
 *  non-zero structure.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The structure of the sparse matrix to be factorized.
 *
 *  - Returns: The requested symbolic factorization of Matrix.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
  SparseMatrixStructure Matrix);

/*! Returns a symbolic factorization of the requested type for a
 *            complex matrix with the given structure.
 *
 *   The resulting symbolic factorization may be used for multiple
 *  numerical factorizations with different numerical values but the same
 *  non-zero structure.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The structure of the sparse matrix to be factorized.
 *
 *  - Returns: The requested symbolic factorization of Matrix.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
  SparseMatrixStructureComplex Matrix);


/*! Returns a symbolic factorization of the requested type for a
 *            matrix with the given structure, with the supplied options.
 *
 *   The resulting symbolic factorization may be used for multiple
 *  numerical factorizations with different numerical values but the same
 *  non-zero structure.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The structure of the sparse matrix to be factorized.
 *
 *  - Parameter sfoptions: Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  - Returns: The requested symbolic factorization of Matrix.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
  SparseMatrixStructure Matrix, SparseSymbolicFactorOptions sfoptions);

/*! Returns a symbolic factorization of the requested type for a
 *            complex matrix with the given structure, with the supplied options.
 *
 *   The resulting symbolic factorization may be used for multiple
 *  numerical factorizations with different numerical values but the same
 *  non-zero structure.
 *
 *  - Parameter type: The type of factorization to perform.
 *
 *  - Parameter Matrix: The structure of the sparse matrix to be factorized.
 *
 *  - Parameter sfoptions: Symbolic factor options, for example the ordering algorithm
 *         to use.
 *
 *  - Returns: The requested symbolic factorization of Matrix.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueSymbolicFactorization SparseFactor(SparseFactorization_t type,
  SparseMatrixStructureComplex Matrix, SparseSymbolicFactorOptions sfoptions);

/**** Symbolic Refactor Functions *********************************************/


/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of double values.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of float values.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex double values.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Double Matrix,
  SparseOpaqueFactorization_Complex_Double *Factorization);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex float values.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of Factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Float Matrix,
  SparseOpaqueFactorization_Complex_Float *Factorization);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of double values, using different options.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization,
  SparseNumericFactorOptions nfoptions);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of float values, using different options.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization,
  SparseNumericFactorOptions nfoptions);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex double values, using different options.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Double Matrix,
  SparseOpaqueFactorization_Complex_Double *Factorization,
  SparseNumericFactorOptions nfoptions);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex float values, using different options.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Float Matrix,
  SparseOpaqueFactorization_Complex_Float *Factorization,
  SparseNumericFactorOptions nfoptions);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of double values, without any internal
 *            allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of `Factorization`.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns `NULL` the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *  - Parameter Factorization: The factorization to be updated.
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Double` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of float values, without any internal
 *            allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of `Factorization`.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns `NULL` the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *  - Parameter Factorization: The factorization to be updated.
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Float` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex double values, without any internal
 *            allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of `Factorization`.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns `NULL` the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *  - Parameter Factorization: The factorization to be updated.
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Double * 2` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Double Matrix,
  SparseOpaqueFactorization_Complex_Double *Factorization, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex float values, without any internal
 *            allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.
 *
 *  The same numerical factorization options will be used as in the original
 *  construction of `Factorization`.
 *
 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns `NULL` the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *  - Parameter Factorization: The factorization to be updated.
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Float * 2` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Float Matrix,
  SparseOpaqueFactorization_Complex_Float *Factorization, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of double values, using updated options and
 *            without any internal allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.

 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns NULL the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Double` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.                                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Double Matrix,
  SparseOpaqueFactorization_Double *Factorization,
  SparseNumericFactorOptions nfoptions, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of float values, using updated options and
 *            without any internal allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.

 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns NULL the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Float` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.                                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseRefactor(SparseMatrix_Float Matrix,
  SparseOpaqueFactorization_Float *Factorization,
  SparseNumericFactorOptions nfoptions, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex double values, using updated options and
 *            without any internal allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.

 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns NULL the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Double * 2` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.                                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Double Matrix,
  SparseOpaqueFactorization_Complex_Double *Factorization,
  SparseNumericFactorOptions nfoptions, void *workspace);

/*! Reuses supplied factorization object's storage to compute a new
 *            factorization of the supplied matrix of complex float values, using updated options and
 *            without any internal allocations.
 *
 *   `Matrix` must have the same non-zero structure as that used for
 *  the original factorization.

 *  This call provides very similar behavior to that which can be achieved by
 *  reusing explicit storage supplied to `SparseFactor` as the argument
 *  `factorStorage`. However, in addition to providing a simplified call sequence,
 *  this call can also reuse any additional storage allocated to accomodate
 *  delayed pivots.
 *
 *  Note that internal memory allocations may occur in the case of
 *  pivoted factorizations that result in delayed pivots. If you require closer
 *  control over memory allocations, supply an `sfoptions.malloc` function that
 *  implements the required behaviour, or use an alternative non-pivoted
 *  factorization returns. Note that if `sfoptions.malloc` returns NULL the
 *  factorization will abort immediately.
 *
 *  Note that if the reference count of the underlying object is not
 *  exactly one (i.e. if there are any implict copies as a result of calls to
 *  `SparseGetTranspose` or `SparseCreateSubfactor()` that have not been destroyed
 *  through a call to `SparseCleanup`), then new storage will be allocated
 *  regardless.
 *
 *  - Parameter Matrix: The matrix to be factorized.
 *
 *  - Parameter Factorization: The factorization to be updated.
 *
 *  - Parameter nfoptions: Numeric factor options, for example pivoting parameters.
 *
 *  - Parameter workspace: A pointer to a workspace of size at least
 *         `Factorization->symbolicFactorization.workspaceSize_Float * 2` bytes.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc` has this property).
 *         This workspace may be reused or destroyed by the user as soon as the
 *         function returns.                                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseRefactor(SparseMatrix_Complex_Float Matrix,
  SparseOpaqueFactorization_Complex_Float *Factorization,
  SparseNumericFactorOptions nfoptions, void *workspace);

/*! Apply a low-rank update to an existing factorization of a matrix of float values.
 *
 *  If we have a factorization `A = LU` and now wish to solve a system `ĀX = B` where
 *  `Ā = A + UV^T` for some low-rank update matrices `U` of size `m x k` and `V` of size
 *  `k x n` for some small `k` there exist methods to modify (update) the original factors at a
 *  lower cost than a full factorization.
 *
 *  Supported techniques are:
 *  - `SparseUpdatePartialRefactor`:
 *    The most stable, but most expensive, method is to perform a partial refactorization that
 *    will recalculate the L and U factor values that would be different if performing an LU
 *    factorization from scratch.
 *
 *    For the partial refactorization, `updatedIndices` should be a list of `updateCount`
 *    (row, column) pairs indicating modified values (i.e. a total of `2*updateCount` integers),
 *    and `Update` should be a full copy of the original matrix with those value modified to their
 *    new values. The structure of `Update` must be identical to that of the original matrix.
 *
 *   - Parameter updateAlgorithm:the update algorithm to use
 *   - Parameter Factorization: the existing factorization to be updated. The existing factorization will
 *          be modified and will no longer solve `AX=B`.
 *   - Parameter updateCount:number of updated entries or columns
 *   - Parameter updatedIndices: list of updated indices, interpreted as described above
 *   - Parameter Update: the updated entries.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5)) 
void SparseUpdateFactor(SparseUpdate_t updateAlgorithm,
                        SparseOpaqueFactorization_Float *Factorization,
                        int updateCount,
                        const int *updatedIndices,
                        SparseMatrix_Float Update);

/*! Apply a low-rank update to an existing factorization of a matrix of double values.
 *
 *  If we have a factorization `A = LU` and now wish to solve a system `ĀX = B` where
 *  `Ā = A + UV^T` for some low-rank update matrices `U` of size `m x k` and `V` of size
 *  `k x n` for some small `k` there exist methods to modify (update) the original factors at a
 *  lower cost than a full factorization.
 *
 *  Supported techniques are:
 *  - `SparseUpdatePartialRefactor`:
 *    The most stable, but most expensive, method is to perform a partial refactorization that
 *    will recalculate the L and U factor values that would be different if performing an LU
 *    factorization from scratch.
 *
 *    For the partial refactorization, `updatedIndices` should be a list of `updateCount`
 *    (row, column) pairs indicating modified values (i.e. a total of `2*updateCount` integers),
 *    and `Update` should be a full copy of the original matrix with those value modified to their
 *    new values. The structure of `Update` must be identical to that of the original matrix.
 *
 *   - Parameter updateAlgorithm:the update algorithm to use
 *   - Parameter Factorization: the existing factorization to be updated. The existing factorization will
 *          be modified and will no longer solve `AX=B`.
 *   - Parameter updateCount:number of updated entries or columns
 *   - Parameter updatedIndices: list of updated indices, interpreted as described above
 *   - Parameter Update: the updated entries.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5)) 
void SparseUpdateFactor(SparseUpdate_t updateAlgorithm,
                        SparseOpaqueFactorization_Double *Factorization,
                        int updateCount,
                        const int *updatedIndices,
                        SparseMatrix_Double Update);

/*! Apply a low-rank update to an existing factorization of a matrix of complex float values.
 *
 *  If we have a factorization `A = LU` and now wish to solve a system `ĀX = B` where
 *  `Ā = A + UV^T` for some low-rank update matrices `U` of size `m x k` and `V` of size
 *  `k x n` for some small `k` there exist methods to modify (update) the original factors at a
 *  lower cost than a full factorization.
 *
 *  Supported techniques are:
 *  - `SparseUpdatePartialRefactor`:
 *    The most stable, but most expensive, method is to perform a partial refactorization that
 *    will recalculate the L and U factor values that would be different if performing an LU
 *    factorization from scratch.
 *
 *    For the partial refactorization, `updatedIndices` should be a list of `updateCount`
 *    (row, column) pairs indicating modified values (i.e. a total of `2*updateCount` integers),
 *    and `Update` should be a full copy of the original matrix with those value modified to their
 *    new values. The structure of `Update` must be identical to that of the original matrix.
 *
 *   - Parameter updateAlgorithm:the update algorithm to use
 *   - Parameter Factorization: the existing factorization to be updated. The existing factorization will
 *          be modified and will no longer solve `AX=B`.
 *   - Parameter updateCount:number of updated entries or columns
 *   - Parameter updatedIndices: list of updated indices, interpreted as described above
 *   - Parameter Update: the updated entries.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5)) 
void SparseUpdateFactor(SparseUpdate_t updateAlgorithm,
                        SparseOpaqueFactorization_Complex_Float *Factorization,
                        int updateCount,
                        const int *updatedIndices,
                        SparseMatrix_Complex_Float Update);

/*! Apply a low-rank update to an existing factorization of a matrix of complex double values.
 *
 *  If we have a factorization `A = LU` and now wish to solve a system `ĀX = B` where
 *  `Ā = A + UV^T` for some low-rank update matrices `U` of size `m x k` and `V` of size
 *  `k x n` for some small `k` there exist methods to modify (update) the original factors at a
 *  lower cost than a full factorization.
 *
 *  Supported techniques are:
 *  - `SparseUpdatePartialRefactor`:
 *    The most stable, but most expensive, method is to perform a partial refactorization that
 *    will recalculate the L and U factor values that would be different if performing an LU
 *    factorization from scratch.
 *
 *    For the partial refactorization, `updatedIndices` should be a list of `updateCount`
 *    (row, column) pairs indicating modified values (i.e. a total of `2*updateCount` integers),
 *    and `Update` should be a full copy of the original matrix with those value modified to their
 *    new values. The structure of `Update` must be identical to that of the original matrix.
 *
 *   - Parameter updateAlgorithm:the update algorithm to use
 *   - Parameter Factorization: the existing factorization to be updated. The existing factorization will
 *          be modified and will no longer solve `AX=B`.
 *   - Parameter updateCount:number of updated entries or columns
 *   - Parameter updatedIndices: list of updated indices, interpreted as described above
 *   - Parameter Update: the updated entries.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5)) 
void SparseUpdateFactor(SparseUpdate_t updateAlgorithm,
                        SparseOpaqueFactorization_Complex_Double *Factorization,
                        int updateCount,
                        const int *updatedIndices,
                        SparseMatrix_Complex_Double Update);

/**** Factor Query Functions *********************************************/

/*! Returns the inertia of an LDLT factorization in float.
 *
 *  
 *  For a given LDLT factorization, this function returns the number of
 *  negative, zero and positive pivots taken during the factorization.
 *  Note that in some cases, particularly when eigenvalues are close to
 *  zero, the computed numerical inertia may not be an accurate reflection
 *  of the true inertia of the system, and in particular can be highly dependent
 *  on the zeroTolerance (and to a less degree the pivotTolerance) specified
 *  in the factorization options.
 *
 *  This call is only supported for factorizations of type `SparseFactorizationLDLTTPP`.
 *
 *  - Parameter Factored: The factorization to be queried.
 *
 *  - Parameter num_positive: Upon return `*num_positive` has been set to the number
 *         of positive pivots.
 *
 *  - Parameter num_zero: Upon return `*num_zero` has been set to the number
 *         of zero pivots.
 *
 *  - Parameter num_negative: Upon return `*num_negative` has been set to the number
 *         of negative pivots.
 *
 *  - Returns: 0 on success, non-zero on error
 */
SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(13.0), ios(16.0), watchos(9.0), tvos(16.0) )
int SparseGetInertia(SparseOpaqueFactorization_Float Factored, int *num_positive, int *num_zero, int *num_negative);

/*! Returns the inertia of an LDLT factorization in double.
 *
 *
 *  For a given LDLT factorization, this function returns the number of
 *  negative, zero and positive pivots taken during the factorization.
 *  Note that in some cases, particularly when eigenvalues are close to
 *  zero, the computed numerical inertia may not be an accurate reflection
 *  of the true inertia of the system, and in particular can be highly dependent
 *  on the zeroTolerance (and to a less degree the pivotTolerance) specified
 *  in the factorization options.
 *
 *  This call is only supported for factorizations of type `SparseFactorizationLDLTTPP`.
 *
 *  - Parameter Factored: The factorization to be queried.
 *
 *  - Parameter num_positive: Upon return `*num_positive` has been set to the number
 *         of positive pivots.
 *
 *  - Parameter num_zero: Upon return `*num_zero` has been set to the number
 *         of zero pivots.
 *
 *  - Parameter num_negative: Upon return `*num_negative` has been set to the number
 *         of negative pivots.
 *
 *  - Returns: 0 on success, non-zero on error
 */
SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(13.0), ios(16.0), watchos(9.0), tvos(16.0) )
int SparseGetInertia(SparseOpaqueFactorization_Double Factored, int *num_positive, int *num_zero, int *num_negative);

/*! Returns the inertia of an LDLT factorization in complex float.
 *
 *
 *  For a given LDLT factorization, this function returns the number of
 *  negative, zero and positive pivots taken during the factorization.
 *  Note that in some cases, particularly when eigenvalues are close to
 *  zero, the computed numerical inertia may not be an accurate reflection
 *  of the true inertia of the system, and in particular can be highly dependent
 *  on the zeroTolerance (and to a less degree the pivotTolerance) specified
 *  in the factorization options.
 *
 *  This call is only supported for factorizations of type `SparseFactorizationLDLTTPP`.
 *
 *  - Parameter Factored: The factorization to be queried.
 *
 *  - Parameter num_positive: Upon return `*num_positive` has been set to the number
 *         of positive pivots.
 *
 *  - Parameter num_zero: Upon return `*num_zero` has been set to the number
 *         of zero pivots.
 *
 *  - Parameter num_negative: Upon return `*num_negative` has been set to the number
 *         of negative pivots.
 *
 *  - Returns: 0 on success, non-zero on error
 */
SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
int SparseGetInertia(SparseOpaqueFactorization_Complex_Float Factored, int *num_positive, int *num_zero, int *num_negative);

/*! Returns the inertia of an LDLT factorization in complex double.
 *
 *
 *  For a given LDLT factorization, this function returns the number of
 *  negative, zero and positive pivots taken during the factorization.
 *  Note that in some cases, particularly when eigenvalues are close to
 *  zero, the computed numerical inertia may not be an accurate reflection
 *  of the true inertia of the system, and in particular can be highly dependent
 *  on the zeroTolerance (and to a less degree the pivotTolerance) specified
 *  in the factorization options.
 *
 *  This call is only supported for factorizations of type `SparseFactorizationLDLTTPP`.
 *
 *  - Parameter Factored: The factorization to be queried.
 *
 *  - Parameter num_positive: Upon return `*num_positive` has been set to the number
 *         of positive pivots.
 *
 *  - Parameter num_zero: Upon return `*num_zero` has been set to the number
 *         of zero pivots.
 *
 *  - Parameter num_negative: Upon return `*num_negative` has been set to the number
 *         of negative pivots.
 *
 *  - Returns: 0 on success, non-zero on error
 */
SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
int SparseGetInertia(SparseOpaqueFactorization_Complex_Double Factored, int *num_positive, int *num_zero, int *num_negative);

/******************************************************************************
 *  @group Extracting Sub-factors of Factors
 ******************************************************************************/

/*! Returns an opaque object representing a sub-factor of a
 *            factorization in double.
 *
 *   Here the term "sub-factor" is used to mean one or more parts of
 *  the whole factorization. For example, just the `Q` factor from `A=QRP`.
 *  The returned object is a wrapper around the orignal factorization, and does
 *  not actually perform any extraction (sub-factors are stored in non-standard
 *  formats that exploit implicit structure for efficiency, and formation of the
 *  sub-factor explicitly can be expensive). It is intended to be used as an
 *  argument to `SparseMultiply` and `SparseSolve` functions only.
 *
 *  As `Factor` is contained in the returned object, its underlying reference
 *  count in incremented, and the returned object must hence be destroyed
 *  through a call to `SparseCleanup` to prevent a memory leak (however it is
 *  safe to call `SparseCleanup` on the original factorization whilst this
 *  object is still being used).
 *
 *  - Parameter subfactor: The sub-factor the new object should represent.
 *
 *  - Parameter Factor: The factorization to extract the sub-factor from.
 *
 *  - Returns: Object representing the requested sub-factor. Must be cleaned up
 *  by a call to `SparseCleanup` once it is no longer required.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Double SparseCreateSubfactor(SparseSubfactor_t subfactor,
  SparseOpaqueFactorization_Double Factor);

/*! Returns an opaque object representing a sub-factor of a
 *            factorization in float.
 *
 *   Here the term "sub-factor" is used to mean one or more parts of
 *  the whole factorization. For example, just the `Q` factor from `A=QRP`.
 *  The returned object is a wrapper around the orignal factorization, and does
 *  not actually perform any extraction (sub-factors are stored in non-standard
 *  formats that exploit implicit structure for efficiency, and formation of the
 *  sub-factor explicitly can be expensive). It is intended to be used as an
 *  argument to `SparseMultiply` and `SparseSolve` functions only.
 *
 *  As `Factor` is contained in the returned object, its underlying reference
 *  count in incremented, and the returned object must hence be destroyed
 *  through a call to `SparseCleanup` to prevent a memory leak (however it is
 *  safe to call `SparseCleanup` on the original factorization whilst this
 *  object is still being used).
 *
 *  - Parameter subfactor: The sub-factor the new object should represent.
 *
 *  - Parameter Factor: The factorization to extract the sub-factor from.
 *
 *  - Returns: Object representing the requested sub-factor. Must be cleaned up
 *  by a call to `SparseCleanup` once it is no longer required.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Float SparseCreateSubfactor(SparseSubfactor_t subfactor,
  SparseOpaqueFactorization_Float Factor);

/*! Returns an opaque object representing a sub-factor of a
 *            factorization in complex double.
 *
 *   Here the term "sub-factor" is used to mean one or more parts of
 *  the whole factorization. For example, just the `Q` factor from `A=QRP`.
 *  The returned object is a wrapper around the orignal factorization, and does
 *  not actually perform any extraction (sub-factors are stored in non-standard
 *  formats that exploit implicit structure for efficiency, and formation of the
 *  sub-factor explicitly can be expensive). It is intended to be used as an
 *  argument to `SparseMultiply` and `SparseSolve` functions only.
 *
 *  As `Factor` is contained in the returned object, its underlying reference
 *  count in incremented, and the returned object must hence be destroyed
 *  through a call to `SparseCleanup` to prevent a memory leak (however it is
 *  safe to call `SparseCleanup` on the original factorization whilst this
 *  object is still being used).
 *
 *  - Parameter subfactor: The sub-factor the new object should represent.
 *
 *  - Parameter Factor: The factorization to extract the sub-factor from.
 *
 *  - Returns: Object representing the requested sub-factor. Must be cleaned up
 *  by a call to `SparseCleanup` once it is no longer required.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueSubfactor_Complex_Double SparseCreateSubfactor(SparseSubfactor_t subfactor,
  SparseOpaqueFactorization_Complex_Double Factor);

/*! Returns an opaque object representing a sub-factor of a
 *            factorization in complex float.
 *
 *   Here the term "sub-factor" is used to mean one or more parts of
 *  the whole factorization. For example, just the `Q` factor from `A=QRP`.
 *  The returned object is a wrapper around the orignal factorization, and does
 *  not actually perform any extraction (sub-factors are stored in non-standard
 *  formats that exploit implicit structure for efficiency, and formation of the
 *  sub-factor explicitly can be expensive). It is intended to be used as an
 *  argument to `SparseMultiply` and `SparseSolve` functions only.
 *
 *  As `Factor` is contained in the returned object, its underlying reference
 *  count in incremented, and the returned object must hence be destroyed
 *  through a call to `SparseCleanup` to prevent a memory leak (however it is
 *  safe to call `SparseCleanup` on the original factorization whilst this
 *  object is still being used).
 *
 *  - Parameter subfactor: The sub-factor the new object should represent.
 *
 *  - Parameter Factor: The factorization to extract the sub-factor from.
 *
 *  - Returns: Object representing the requested sub-factor. Must be cleaned up
 *  by a call to `SparseCleanup` once it is no longer required.
 *  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueSubfactor_Complex_Float SparseCreateSubfactor(SparseSubfactor_t subfactor,
  SparseOpaqueFactorization_Complex_Float Factor);

/******************************************************************************
 *  @group Sub-factor Multiplication and Solve Functions
 ******************************************************************************/

/**** Matrix solve functions **************************************************/

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XB);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XB);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double XB);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of complex float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float XB);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double B,
  DenseMatrix_Double X);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float B,
  DenseMatrix_Float X);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double B,
  DenseMatrix_Complex_Double X);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of complex float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float B,
  DenseMatrix_Complex_Float X);

/**** Matrix solve functions with user-supplied workspace *********************/

/*! Solve the equation `Subfactor * X` = B for the matrix `X` of double values in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If Subfactor is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XB,
  void *workspace);

/*! Solve the equation `Subfactor * X` = B for the matrix `X` of float values in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If Subfactor is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XB,
  void *workspace);

/*! Solve the equation `Subfactor * X` = B for the matrix `X` of complex double values in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If Subfactor is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double XB,
  void *workspace);

/*! Solve the equation `Subfactor * X` = B for the matrix `X` of complex float values in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XB: (input/output) On input, the matrix `B`. On return it is overwritten
 *         with the matrix `X`. If Subfactor is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         sides. If `m != n`, then only the first `min(m,n)` entries are used for
 *         input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float XB,
  void *workspace);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double B,
  DenseMatrix_Double X, void *workspace);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float B,
  DenseMatrix_Float X, void *workspace);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double B,
  DenseMatrix_Complex_Double X, void *workspace);

/*! Solve the equation `Subfactor * X = B` for the matrix `X` of complex float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter B: (input) The right-hand sides `B`. If `Subfactor` is `m x n`, then `B` must
 *         have dimension `m x nrhs`, where `nrhs` is the number of right-hand
 *         sides.
 *
 *  - Parameter X: (output) The solutions `X`. If `Subfactor` is `m x n`, and `B` is `m x nrhs`,
 *         then `X` must have dimension `n x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float B,
  DenseMatrix_Complex_Float X, void *workspace);

/**** Vector solve ************************************************************/

/*! Solve the equation `Subfactor * x = b` for the vector `x` of double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xb);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xb);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double xb);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float xb);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`).
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then `x` must have
 *         length `n`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double b,
  DenseVector_Double x);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`).
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then `x` must have
 *         length `n`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float b,
  DenseVector_Float x);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`).
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then `x` must have
 *         length `n`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double b,
  DenseVector_Complex_Double x);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`).
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then `x` must have
 *         length `n`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float b,
  DenseVector_Complex_Float x);

/**** Vector solve functions with user-supplied workspace *********************/

/*! Solve the equation `Subfactor * x = b` for the vector `x` of double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xb,
  void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xb,
  void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double xb,
  void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xb: (input/output) On input, the vector `b`. On return it is overwritten
 *         with the solution vector `x`. If `Subfactor` is `m x n`, then `xb` must have
 *         length `k`, where `k = max(m, n)`. If `m != n`, then only the first
 *         `min(m,n)` entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float xb,
  void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then x must have
 *         length n.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double b,
  DenseVector_Double x, void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then x must have
 *         length n.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseSolve(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float b,
  DenseVector_Float x, void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then x must have
 *         length n.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double b,
  DenseVector_Complex_Double x, void *workspace);

/*! Solve the equation `Subfactor * x = b` for the vector `x` of complex float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to solve a system involving, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter b: (input) The right-hand side `b`. If `Subfactor` is `m x n`, then `b` must
 *         have length `m`.
 *
 *  - Parameter x: (output) The solution `x`. If `Subfactor` is `m x n`, then x must have
 *         length n.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseSolve(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float b,
  DenseVector_Complex_Float x, void *workspace);

/**** Matrix multiply functions ***********************************************/

/*! Perform the multiply operation `Y = Subfactor * X` in place for double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XY);

/*! Perform the multiply operation `Y = Subfactor * X` in place for float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XY);

/*! Perform the multiply operation `Y = Subfactor * X` in place for complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double XY);

/*! Perform the multiply operation `Y = Subfactor * X` in place for complex float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float XY);

/*! Perform the multiply operation `Y = Subfactor * X` for double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double X,
  DenseMatrix_Double Y);

/*! Perform the multiply operation `Y = Subfactor * X` for float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float X,
  DenseMatrix_Float Y);

/*! Perform the multiply operation `Y = Subfactor * X` for complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double X,
  DenseMatrix_Complex_Double Y);

/*! Perform the multiply operation `Y = Subfactor * X` for complex float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float X,
  DenseMatrix_Complex_Float Y);

/**** Matrix multiply functions with user-supplied workspace ******************/

/*! Perform the multiply operation `Y = Subfactor * X `for double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double XY,
  void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X `for float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float XY,
  void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X `for complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double XY,
  void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X `for complex float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter XY: (input/output) On input, the matrix `X`. On return it is overwritten
 *         with the matrix `Y`. If `Subfactor` is `m x n`, then `XB` must have dimension
 *         `k x nrhs`, where `k = max(m, n)` and `nrhs` is the number of right-hand
 *         side vectors. If `m != n`, then only the first `min(m,n)` entries are
 *         used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float XY,
  void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X` for double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseMatrix_Double X,
  DenseMatrix_Double Y, void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X` for double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseMatrix_Float X,
  DenseMatrix_Float Y, void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X` for complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseMatrix_Complex_Double X,
  DenseMatrix_Complex_Double Y, void *workspace);

/*! Perform the multiply operation `Y = Subfactor * X` for complex float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter X: (input) The right-hand side vectors `X`. If `Subfactor` is `m x n`, then `X`
 *         must have dimension `n x nrhs`, where nrhs is the number of right-hand
 *         side vectors.
 *
 *  - Parameter Y: (output) The result vectors `Y`. If `Subfactor` is `m x n`, and `X` is
 *         `m x nrhs`, then `Y` must have dimension `m x nrhs`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + nrhs * Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseMatrix_Complex_Float X,
  DenseMatrix_Complex_Float Y, void *workspace);

/**** Vector multiply functions ***********************************************/

/*! Perform the multiply operation `y = Subfactor * x` for double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xy)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Perform the multiply operation `y = Subfactor * x` for float values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xy)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Perform the multiply operation `y = Subfactor * x` for complex double values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double xy)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Perform the multiply operation `y = Subfactor * x` for complex floatr values, in place.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 */
static inline SPARSE_PUBLIC_INTERFACE
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float xy)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Perform the multiply operation `y = Subfactor * x` for double values..
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector y. If `Subfactor` is `m x n`, then `y` must have
 *         length `m`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double x,
  DenseVector_Double y);

/*! Perform the multiply operation `y = Subfactor * x` for float values..
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector y. If `Subfactor` is `m x n`, then `y` must have
 *         length `m`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float x,
  DenseVector_Float y);

/*! Perform the multiply operation `y = Subfactor * x` for complex double values..
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector y. If `Subfactor` is `m x n`, then `y` must have
 *         length `m`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double x,
  DenseVector_Complex_Double y);

/*! Perform the multiply operation `y = Subfactor * x` for complex float values..
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector y. If `Subfactor` is `m x n`, then `y` must have
 *         length `m`.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float x,
  DenseVector_Complex_Float y);

/**** Vector multiply functions with user-supplied workspace ******************/

/*! Perform the multiply operation `y = Subfactor * x` in place for double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double xy,
  void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` in place for float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float xy,
  void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` in place for complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double xy,
  void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` in place for complex float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter xy: (input/output) On input, the vector `x`. On return it is overwritten
 *         with the vector `y`. If `Subfactor` is `m x n`, then `xb` must have length
 *         `k`, where `k = max(m, n)`. If `m != n`, then only the first `min(m,n)`
 *         entries are used for input or output as approriate.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float xy,
  void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` for double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector `y`. If `Subfactor` is `m x n`, then y must have
 *         length `m`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Double Subfactor, DenseVector_Double x,
  DenseVector_Double y, void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` for float values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector `y`. If `Subfactor` is `m x n`, then y must have
 *         length `m`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseMultiply(SparseOpaqueSubfactor_Float Subfactor, DenseVector_Float x,
  DenseVector_Float y, void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` for complex double values.
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector `y`. If `Subfactor` is `m x n`, then y must have
 *         length `m`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Double Subfactor, DenseVector_Complex_Double x,
  DenseVector_Complex_Double y, void *workspace);

/*! Perform the multiply operation `y = Subfactor * x` for complex float values..
 *
 *  - Parameter Subfactor: (input) The subfactor to multiply by, as returned by
 *         `SparseCreateSubfactor()`.
 *
 *  - Parameter x: (input) The right-hand side vector `x`. If `Subfactor` is `m x n`, then `x`
 *         must have length `n`.
 *
 *  - Parameter y: (output) The result vector `y`. If `Subfactor` is `m x n`, then y must have
 *         length `m`.
 *
 *  - Parameter workspace: (scratch) A workspace of size
 *         `Subfactor.workspaceRequiredStatic + 1*Subfactor.workspaceRequiredPerRHS * 2`.
 *         This memory must be 16-byte aligned (any allocation returned
 *         by `malloc()` has this property).
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseMultiply(SparseOpaqueSubfactor_Complex_Float Subfactor, DenseVector_Complex_Float x,
  DenseVector_Complex_Float y, void *workspace);

/******************************************************************************
 *  @group Preconditioners
 ******************************************************************************/

/*! Types of preconditioner.
 *
 *  - term `SparsePreconditionerNone` :
 *    No preconditioner, used to flag an empty type as required.
 *  - term `SparsePreconditionerUser` :
 *    User-defined preconditioner.
 *  - term `SparsePreconditionerDiagonal` :
 *    Diagonal (Jacobi) preconditioner `D_ii = 1.0 / A_ii`.
 *    Zero entries on the diagonal of `A` are replaced with `1.0`.
 *  - term `SparsePreconditionerDiagScaling` :
 *    Diagonal scaling preconditioner `D_ii = 1.0 / || A_i ||_2`, where `A_i` is
 *    `i`-th column of `A`.
 */
SPARSE_ENUM(SparsePreconditioner, int,
  SparsePreconditionerNone = 0,
  SparsePreconditionerUser = 1,
  SparsePreconditionerDiagonal = 2,
  SparsePreconditionerDiagScaling = 3
);

/*! Represents a preconditioner for matrices of double values .
 *
 *  - term `type` :  The type of preconditioner represented.
 *
 *  - term `mem` : Block of memory that will be passed unaltered as the first
 *         argument of the `apply()` callback.
 *
 *  - term `apply(mem, trans, X, Y)` :
 *          Function to call to apply the preconditioner as `Y = PX` (`trans=false`) or `Y = P^TX` (`trans`=`true`).
 *    * `mem` : The unaltered pointer mem from this struct.
 *    * `trans` : Flags whether to apply the preconditioner or its transpose.
 *    * `X`: The right-hand side vectors X.
 *    * `Y`: The result vectors Y.
 */
typedef struct {
  SparsePreconditioner_t type;
  void *mem;
  void (*apply) (void*, enum CBLAS_TRANSPOSE trans, DenseMatrix_Double X, DenseMatrix_Double Y);
} SparseOpaquePreconditioner_Double;

/*! Represents a preconditioner for matrices of float values .
 *
 *  - term `type` :  The type of preconditioner represented.
 *
 *  - term `mem` : Block of memory that will be passed unaltered as the first
 *         argument of the `apply()` callback.
 *
 *  - term `apply(mem, trans, X, Y)` :
 *          Function to call to apply the preconditioner as `Y = PX` (`trans=false`) or `Y = P^TX` (`trans`=`true`).
 *    * `mem` : The unaltered pointer mem from this struct.
 *    * `trans` : Flags whether to apply the preconditioner or its transpose.
 *    * `X`: The right-hand side vectors X.
 *    * `Y`: The result vectors Y.
 */
typedef struct {
  SparsePreconditioner_t type;
  void *mem;
  void (*apply) (void*, enum CBLAS_TRANSPOSE trans, DenseMatrix_Float X, DenseMatrix_Float);
} SparseOpaquePreconditioner_Float;

/*! Represents a preconditioner for matrices of complex double values .
 *
 *  - term `type` :  The type of preconditioner represented.
 *
 *  - term `mem` : Block of memory that will be passed unaltered as the first
 *         argument of the `apply()` callback.
 *
 *  - term `apply(mem, trans, X, Y)` :
 *          Function to call to apply the preconditioner as `Y = PX` (`trans=false`) or `Y = P^TX` (`trans`=`true`).
 *    * `mem` : The unaltered pointer mem from this struct.
 *    * `trans` : Flags whether to apply the preconditioner or its transpose.
 *    * `X`: The right-hand side vectors X.
 *    * `Y`: The result vectors Y.
 */
typedef struct {
  SparsePreconditioner_t type;
  void *mem;
  void (*apply) (void*, enum CBLAS_TRANSPOSE trans, DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y);
} SparseOpaquePreconditioner_Complex_Double;

/*! Represents a preconditioner for matrices of complex float values .
 *
 *  - term `type` :  The type of preconditioner represented.
 *
 *  - term `mem` : Block of memory that will be passed unaltered as the first
 *         argument of the `apply()` callback.
 *
 *  - term `apply(mem, trans, X, Y)` :
 *          Function to call to apply the preconditioner as `Y = PX` (`trans=false`) or `Y = P^TX` (`trans`=`true`).
 *    * `mem` : The unaltered pointer mem from this struct.
 *    * `trans` : Flags whether to apply the preconditioner or its transpose.
 *    * `X`: The right-hand side vectors X.
 *    * `Y`: The result vectors Y.
 */
typedef struct {
  SparsePreconditioner_t type;
  void *mem;
  void (*apply) (void*, enum CBLAS_TRANSPOSE trans, DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y);
} SparseOpaquePreconditioner_Complex_Float;

/*! Create a preconditioner for the given matrix of double values.
 *
 *  - Parameter type: (input) The type of preconditioner to create.
 *
 *  - Parameter A: (input) The matrix to construct a preconditioner for.
 *
 *  - Returns: The constructed preconditioner object. Resource must be freed
 *           through a call to `SparseCleanup()` once the user is finished with
 *           the preconditioner.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaquePreconditioner_Double SparseCreatePreconditioner(
  SparsePreconditioner_t type, SparseMatrix_Double A);

/*! Create a preconditioner for the given matrix of float values.
 *
 *  - Parameter type: (input) The type of preconditioner to create.
 *
 *  - Parameter A: (input) The matrix to construct a preconditioner for.
 *
 *  - Returns: The constructed preconditioner object. Resource must be freed
 *           through a call to `SparseCleanup()` once the user is finished with
 *           the preconditioner.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaquePreconditioner_Float SparseCreatePreconditioner(
  SparsePreconditioner_t type, SparseMatrix_Float A);

/*! Create a preconditioner for the given matrix of complex double values.
 *
 *  - Parameter type: (input) The type of preconditioner to create.
 *
 *  - Parameter A: (input) The matrix to construct a preconditioner for.
 *
 *  - Returns: The constructed preconditioner object. Resource must be freed
 *           through a call to `SparseCleanup()` once the user is finished with
 *           the preconditioner.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaquePreconditioner_Complex_Double SparseCreatePreconditioner(
  SparsePreconditioner_t type, SparseMatrix_Complex_Double A);

/*! Create a preconditioner for the given matrix of complex float values.
 *
 *  - Parameter type: (input) The type of preconditioner to create.
 *
 *  - Parameter A: (input) The matrix to construct a preconditioner for.
 *
 *  - Returns: The constructed preconditioner object. Resource must be freed
 *           through a call to `SparseCleanup()` once the user is finished with
 *           the preconditioner.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaquePreconditioner_Complex_Float SparseCreatePreconditioner(
  SparsePreconditioner_t type, SparseMatrix_Complex_Float A);

/******************************************************************************
 *  @group Sparse Iterative Methods
 ******************************************************************************
 *
 * Sparse Iterative methods solve Ax=b through an iterative process that only
 * requires multiplication by A or A^T. However, if A is numerically difficult,
 * the iterative process may fail to converge to a solution. Further, even for
 * problems where the process converges, it may do so slowly. Both of these
 * issues can be fixed through the application of a problem-specific
 * preconditioner that cheaply approximates the inverse of A (though good
 * preconditioners are not known for all probelms).
 *
 */

/**** Type definitions ********************************************************/

/*! Exit status definitions for sparse iterative methods.
 *
 *  - term `SparseIterativeConverged` :
 *    All solution vectors converged.
 *  - term `SparseIterativeMaxIterations` :
 *    One or more solutions failed to converge in the maximum number of
 *    iterations.
 *  - term `SparseIterativeParameterError` :
 *    There was an error with one or more user-supplied parameters.
 *  - term `SparseIterativeIllConditioned` :
 *    Problem determined to be sufficiently ill conditioned convergence is
 *    unlikely.
 *  - term `SparseIterativeInternalError` :
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
 *  Base type for iterative method options structures.
 *
 *   In the SparseIterativeMethod datatype, all possible options
 *  structures are held as a union. Defining this base type allows easy access
 *  to the reportError() method regardless of which particular method the
 *  structure represents, so long as reportError() is the first entry in each
 *  options structure.
 *
 *  \@callback reportError Function to use to report parameter errors.
 *    \- Parameter message
 *    \ If NULL, errors are logged via `<os/log.h>` and execution is
 *      halted via `__builtin_trap()`.  If non-NULL, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).            */
struct _SparseIterativeMethodBaseOptions {
  // reportError should always be FIRST member in below structs
  void (* _Nullable reportError)(const char *message);
};

/*! Conjugate Gradient Options.
 *
 *   Use CG to solve Ax=b when A is symmetric (Hermitian) positive-definite (the method may break
 *  down or fail to converge if A is not positive-definite).
 *
 *  For square, full rank unsymmetric or indefinite equations, use GMRES instead.
 *  For rectangular or singular systems, use LSMR instead.
 *
 *  - term `reportError`  :
 *    Function to use to report parameter errors.
 *
 *    If `NULL`, errors are logged via `<os/log.h>` and execution is
 *      halted via `__builtin_trap()`.  If non-`NULL`, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *
 *  - term `maxIterations` :
 *    Maximum number of iterations to perform. If 0, the default value of 100
 *    is used.
 *
 *  - term `atol` :
 *    Absolute convergence tolerance. Iterate is considered to have converged if
 *    ```
 *    || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol
 *    ```
 *  - term `rtol` :
 *    Relative convergence tolerance. Iterate is considered to have converged if
 *    ```
 *    || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol
 *    ```
 *    If `rtol = 0.0`, default value of `sqrt(epsilon)` is used.
 *
 *    If negative, `rtol` is treated as `0.0` (default is not used).
 *
 *  - term  `reportStatus` :
 *    Function to use to report status (iteration count
 *             and residual of first right-hand side) every few iterations.
 *    If `NULL`, status is not reported.
 *     */
typedef struct {
  void (* _Nullable reportError)(const char *message);
  int maxIterations;
  double atol;
  double rtol;
  void (* _Nullable reportStatus)(const char *message);
} SparseCGOptions;

/*! Specify different variants of GMRES that can be used.
 *
 *   Basic GMRES requires restarting (as otherwise memory and
 *  calculation costs to keep vectors orthagonal become prohibitive). Upon
 *  restarting all information from previous iterations is discarded.
 *
 *  DQGMRES implements a quasi-GMRES method that does not restart, but instead
 *  only performs orthagonalization against vectors from the most recent
 *  iterations.
 *
 *  Basic GMRES also requires that the same preconditioner is used at every
 *  iteration. At the cost of some additional storage and work, it can be
 *  made flexible (able to cope with different preconditioners at each
 *  iteration) this variant is known as FGMRES.
 *  DGMRES is inherently flexible, so no additional flexible variant is
 *  required.
 *
 *  DQGMRES is the default variant, though for some problems, GMRES or FGMRES
 *  may converge faster and require less computation, particualrly if the
 *  number of orthagonalization vectors `nvec` is small (`< 16`).
 *
 *  - term `SparseVariantDQGMRES`:
 *    Use DQGMRES variant. This method is flexible.
 *  - term `SparseVariantGMRES`:
 *    Use standard restarted GMRES. This method is not flexible.
 *  - term `SparseVariantFGMRES`:
 *    Use Flexible GMRES. This method is flexible.                            */
SPARSE_ENUM(SparseGMRESVariant, uint8_t,
  SparseVariantDQGMRES = 0,
  SparseVariantGMRES = 1,
  SparseVariantFGMRES = 2
);

/*! Right-preconditioned (F/DQ)GMRES Parameters Options.
 *
 *   Use (F/DQ)GMRES to solve `Ax=b` when `A` is symmetric (Hermitian) indefinite or unsymmetric.
 *
 *  For symmetric (Hermitian) positive-definite systems, use CG instead.
 *  For rectangular or singular systems, use LSMR instead.
 *
 *
 *  - term `reportError`  :
 *    Function to use to report parameter errors.
 *
 *    If `NULL`, errors are logged via `<os/log.h>` and execution is
 *      halted via `__builtin_trap()`.  If non-`NULL`, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *
 *  - term `variant`:
 *    Variant of GMRES to use. See definition of `SparseGMRESVariant_t` for
 *    further information on the available variants.
 *
 *  - term `nvec`:
 *    Number of orthagonal vectors maintained. For GMRES and FGMRES variants,
 *    this is the number of iterations between restarts. For DQGMRES it is the
 *    number of historical vectors maintained in memory.
 *
 *    If `nvec<=0`, the default value of 16 is used.
 *
 *  - term `maxIterations` :
 *    Maximum number of iterations to perform. If 0, the default value of 100
 *    is used.
 *
 *  - term `atol`:
 *    Absolute convergence tolerance. Iterate is considered to have converged if
 *    ```
 *    || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol
 *    ```
 *  - term `rtol`:
 *    Relative convergence tolerance. Iterate is considered to have converged if
 *    ```
 *    || b-Ax ||_2 < rtol * || b-Ax_0 ||_2 + atol
 *    ```
 *    If r`tol = 0.0`, default value of `sqrt(epsilon)` is used.
 *    If negative, `rtol` is treated as `0.0 `(default is not used).
 *
 *  - term `reportStatus` :
 *    Function to use to report status (iteration count
 *             and residual of first right-hand side) every few iterations.
 *
 *    If NULL, status is not reported.                           */
typedef struct {
  void (* _Nullable reportError)(const char *message);
  SparseGMRESVariant_t variant;
  int nvec;
  int maxIterations;
  double atol;
  double rtol;
  void (* _Nullable reportStatus)(const char *message);
} SparseGMRESOptions;

/*! Available types of convergence test for LSMR.
 *
 *   In addition to accelerate's default convergence test
 *  applied to the normal equations, the original more specializated
 *  convergence test of Fong and Saunders is offered.
 *
 *  - term `SparseLSMRCTDefault`:
 *    Use accelerate's default convergence test:
 *      ```
 *      || A^Tb - A^TAx ||_2 < rtol * || A^Tb - A^TAx_0 ||_2 + atol.
 *      ```
 *
 *  - term `SparseLSMRCTFongSaunders`:
 *    Use the convergence test of Fong and Saunders:
 *
 *    Either
 *    ```
 *    || b-Ax ||_2 < btol * || b ||_2 + atol * || A ||_2 || x ||_2
 *    ```
 *      or
 *    ```
 *    || A^T (b-Ax) ||_2 < atol * || A ||_2 * || A-bx ||_2
 *    ```
 *    or Estimated condition of `matrix >= conditionLimit`.
 *    */
SPARSE_ENUM(SparseLSMRConvergenceTest, int,
  SparseLSMRCTDefault = 0,
  SparseLSMRCTFongSaunders = 1,
);

/*! LSMR is MINRES specialised for solving least squares.
 *
 *   Use LSMR to solve equations of the form Ax=b where an exact
 *  solution does not exist. The returned solution minimises || b-Ax ||_2.
 *
 *  Whilst LSMR is equivalent to MINRES applied to the normal equations
 *  `A^TAx = A^Tb` in exact arithmetic, it has superior numerical behaviour and
 *  should be used in preference.
 *
 *  We note that due to the implicit squaring of the condition of A in the
 *  normal equations, LSMR may struggle to converge in single precision, and
 *  double precision arithmetic is recommended.
 *
 *  For symmetric (Hermitian) positive-definite systems, use CG instead.
 *  For square, full rank unsymmetric or indefinite equations, use GMRES instead.
 *
 *  - term `reportError`  :
 *    Function to use to report parameter errors.
 *
 *    If `NULL`, errors are logged via `<os/log.h>` and execution is
 *      halted via `__builtin_trap()`.  If non-`NULL`, the provided function is
 *      called with a human-readable string describing the error condition.
 *      If the callback returns, control will be returned to the caller with
 *      any outputs in a safe but undefined state (i.e. they may hold partial
 *      results or garbage, but all sizes and pointers are valid).
 *
 *  - term `lambda`:
 *    Damping parameter, if non-zero the actual problem solved is
 *    ```
 *          min_x || Ax-b ||_2 + lambda || x ||_2.
 *    ```
 *    Using damping can often allow the iteration to converge on ill-conditioned
 *    systems.
 *
 *  - term  `variant`:
 *    Variant of GMRES to use. See definition of `SparseGMRESVariant_t` for
 *    further information on the available variants.
 *
 *  - term  `nvec`:
 *    Number of vectors used for local orthogonalization.
 *    If n`vec<=0`, no orthogonalization is performed.
 *
 *  - term `convergenceTest`:
 *    Which convergence test to use. See definition of
 *    `SparseLSMRConvergenceTest_t` for further information.
 *
 *  - term  `maxIterations`:
 *    Maximum number of iterations to perform. If 0, the default value of 4n
 *    is used.
 *
 *    However, if a good preconditioner is available and/or the matrix is well
 *    conditioned such that singular values are clustered, a value of n/2 may
 *    be more appropriate.
 *
 *  - term `atol`:
 *    Either absolute tolerance (default test) or A tolerance (Fong-Saunders
 *    test). In the Fong and Saunders case, it should hold an estimate of the
 *    relative error in the data defining the matrix A. For example, if A is
 *    accurate to about 6 digits, set atol = 1.0e-6. In the Fong and Saunders
 *    case, if atol is 0.0, it is treated as machine epsilon. If using the
 *    default test, a value of 0.0 is treated as 0.0.
 *
 *  - term `rtol`:
 *    Relative convergence tolerance (default test only).
 *    If `rtol = 0.0`, default value of `sqrt(epsilon)` is used.
 *    If negative, `rtol` is treated as 0.0 (default is not used).
 *
 *  - term `btol`:
 *    b tolerance (Fong-Saunders test only). It should hold an estimate of the
 *    relative error in the data defining the rhs b. For example, if b is
 *    accurate to about 6 digits, set btol = 1.0e-6. If btol is zero, it
 *    is treated as machine epsilon.
 *
 *  - term  `conditionLimit`:
 *    Condition number limit (Fong-Saunders test). Iterations will be terminated
 *    if a computed estimate of cond(Abar) exceeds this value. This is intended
 *    to prevent certain small or zero singular values of A or Abar from coming
 *    into effect and causing unwanted growth in the computed solution.
 *
 *    conditionLimit and lambda may be used separately or together to regularize
 *    ill-conditioned systems.
 *
 *    Normally, conlim should be in the range 1000 to 1/eps.
 *    Suggested value:
 *    * `conditionLimit = 1/(100*eps)`  for compatible systems,
 *    * `conditionLimit = 1/(10*sqrt(eps))` for least squares.
 *
 *    If `conditionLimit` is `0.0,` it is treated as `1/eps`.
 *
 *  - term `reportStatus` :
 *  Function to use to report status (iteration count
 *             and residual of first right-hand side) every few iterations.
 *    If NULL, status is not reported.                           */
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

/*! General description object for all iterative methods.
 *
 *   This object is intended to be constructed through a call to an
 *  iterative method factory function, such as `SparseConjugateGradient()` or
 *  `SparseLSMR()`.
 *
 *  - term `method` : The type of method the object represents.
 *
 *  - term `options` : The options to be used for the method.                     */
typedef struct {
  /*! Specify type of method described */
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

/*! Return a Conjugate Gradient Method with default options.        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseConjugateGradient(void);

/*! Return a Conjugate Gradient Method with specified options.
 *
 *  - Parameter options: Options for conjugate gradient method.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseConjugateGradient(SparseCGOptions options);

/*! Return a GMRES Method with default options.                     */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseGMRES(void);

/*! Return a GMRES Method with specified options.
 *
 *  - Parameter options: Options for GMRES method.                                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseGMRES(SparseGMRESOptions options);

/*! Return a LSMR Method with default options.                      */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseLSMR(void);

/*! Return a LSMR Method with specified options
 *
 *  - Parameter options Options for LSMR method.                                   */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeMethod SparseLSMR(SparseLSMROptions options);

/******************************************************************************
 *  @group Iterative Sparse Solve Functions
 ******************************************************************************/

/**** Solve without preconditioner ********************************************/

/*! Solve `AX=B` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If A
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseMatrix_Double B, DenseMatrix_Double X);

/*! Solve `AX=B` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If A
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseMatrix_Float B, DenseMatrix_Float X);

/*! Solve `AX=B` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If A
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double X);

/*! Solve `AX=B` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If A
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float X);

/*! Solve `Ax=b` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseVector_Double b, DenseVector_Double x);

/*! Solve `Ax=b` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseVector_Float b, DenseVector_Float x);

/*! Solve `Ax=b` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Double A, DenseVector_Complex_Double b, DenseVector_Complex_Double x);

/*! Solve `Ax=b` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Float A, DenseVector_Complex_Float b, DenseVector_Complex_Float x);

/*! Solve `AX=B` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double X);

/*! Solve `AX=B` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float X);

/*! Solve `AX=B` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y),
  DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double X);

/*! Solve `AX=B` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.                */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y),
  DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float X);

/*! Solve `Ax=b` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, x, y)`
 *             should perform the operation `y = op(A)x` if `accumulate` is `false`,
 *             or `y += op(A)x` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Double x, DenseVector_Double y),
  DenseVector_Double b, DenseVector_Double x);

/*! Solve `Ax=b` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, x, y)`
 *             should perform the operation `y = op(A)x` if `accumulate` is `false`,
 *             or `y += op(A)x` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Float x, DenseVector_Float y),
  DenseVector_Float b, DenseVector_Float x);

/*! Solve `Ax=b` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, x, y)`
 *             should perform the operation `y = op(A)x` if `accumulate` is `false`,
 *             or `y += op(A)x` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Complex_Double x, DenseVector_Complex_Double y),
  DenseVector_Complex_Double b, DenseVector_Complex_Double x);

/*! Solve `Ax=b` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, x, y)`
 *             should perform the operation `y = op(A)x` if `accumulate` is `false`,
 *             or `y += op(A)x` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.                                                       */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Complex_Float x, DenseVector_Complex_Float y),
  DenseVector_Complex_Float b, DenseVector_Complex_Float x);

/**** Solve with preconditioner ***********************************************/

/*! Solve `AX=B` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseMatrix_Double B, DenseMatrix_Double X,
  SparsePreconditioner_t Preconditioner);

/*! Solve `AX=B` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseMatrix_Float B, DenseMatrix_Float X,
  SparsePreconditioner_t Preconditioner);

/*! Solve `AX=B` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double X,
  SparsePreconditioner_t Preconditioner);

/*! Solve `AX=B` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float X,
  SparsePreconditioner_t Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseVector_Double b, DenseVector_Double x,
  SparsePreconditioner_t Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseVector_Float b, DenseVector_Float x,
  SparsePreconditioner_t Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Double A, DenseVector_Complex_Double b, DenseVector_Complex_Double x,
  SparsePreconditioner_t Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: Type of preconditioner to create and apply.         */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Float A, DenseVector_Complex_Float b, DenseVector_Complex_Float x,
  SparsePreconditioner_t Preconditioner);

/*! Solve `AX=B` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T.`
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseMatrix_Double B, DenseMatrix_Double X,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! Solve `AX=B` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T.`
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseMatrix_Float B, DenseMatrix_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! Solve `AX=B` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T.`
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Double A, DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double X,
  SparseOpaquePreconditioner_Complex_Double Preconditioner);

/*! Solve `AX=B` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T.`
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where nrhs is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Float A, DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float X,
  SparseOpaquePreconditioner_Complex_Float Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Double A, DenseVector_Double b, DenseVector_Double x,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Float A, DenseVector_Float b, DenseVector_Float x,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Double A, DenseVector_Complex_Double b, DenseVector_Complex_Double x,
  SparseOpaquePreconditioner_Complex_Double Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter A: (input) The matrix `A` to solve the system for. Only used for
 *         multiplication by `A` or `A^T`.
 *
 *  - Parameter b: The right-hand side b to solve for. If `A` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: The preconditioner to apply.                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  SparseMatrix_Complex_Float A, DenseVector_Complex_Float b, DenseVector_Complex_Float x,
  SparseOpaquePreconditioner_Complex_Float Preconditioner);

/*! Solve `AX=B` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n,` and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double X,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! Solve `AX=B` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n,` and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! Solve `AX=B` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n,` and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y),
  DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double X,
  SparseOpaquePreconditioner_Complex_Double Preconditioner);

/*! Solve `AX=B` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         SparseConjugateGradient().
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: The right-hand sides `B` to solve for. If `A` has dimension `m x n`, then
 *         `B` must have dimension `m x nrhs`, where `nrhs` is the number of
 *         right-hand sides to find solutions for.
 *
 *  - Parameter X: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n,` and `B` has dimension `m x nrhs`, then `X` must have
 *         dimension `n x nrhs`. If no good initial estimate is available, user
 *         should set the initial guess to be the zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y),
  DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float X,
  SparseOpaquePreconditioner_Complex_Float Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `x`: The vector to multiply.
 *    - term  `y`: The vector in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Double x, DenseVector_Double y),
  DenseVector_Double b, DenseVector_Double x,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `x`: The vector to multiply.
 *    - term  `y`: The vector in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Float x, DenseVector_Float y),
  DenseVector_Float B, DenseVector_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `x`: The vector to multiply.
 *    - term  `y`: The vector in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Complex_Double x, DenseVector_Complex_Double y),
  DenseVector_Complex_Double b, DenseVector_Complex_Double x,
  SparseOpaquePreconditioner_Complex_Double Preconditioner);

/*! Solve `Ax=b` using the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `x`: The vector to multiply.
 *    - term  `y`: The vector in which to accumulate or store the result.
 *
 *  - Parameter b: The right-hand side `b` to solve for. If `a` has dimension `m x n`, then
 *         `b` must have length `m`.
 *
 *  - Parameter x: On entry, initial guess for solution, on return the solution. If `A`
 *         has dimension `m x n`, then `x` must have length `n`. If no good initial
 *         estimate is available, user should set the initial guess to be the
 *         zero vector.
 *
 *  - Parameter Preconditioner: (input) The preconditioner to use.                  */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseIterativeStatus_t SparseSolve(SparseIterativeMethod method,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseVector_Complex_Float x, DenseVector_Complex_Float y),
  DenseVector_Complex_Float b, DenseVector_Complex_Float x,
  SparseOpaquePreconditioner_Complex_Float Preconditioner);

/******************************************************************************
 *  @group Sparse Single-step Iteration  Functions
 ******************************************************************************
 *
 *   These functions are provided for expert uses who wish to execute
 *  iterative methods a single step at a time, for example to perform their own
 *  custom convergence tests.
 *
 *  A typical use of this routine might be as follows:
 *
 *  ```
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
 *  ```</pre>```
 */

/*! Returns size in bytes of state space required for call to
 *  `SparseIterate()` for double values.
 *
 *  - Parameter method: (input) Method to return required state space size for.
 *
 *  - Parameter preconditioner: (input) True if a preconditioner will be supplied,
 *         false otherwise.
 *
 *  - Parameter m: (input) Number of entries in right-hand side (rows in matrix `A`).
 *
 *  - Parameter n: (input) Number of variables to solve for (columns in matrix `A`).
 *
 *  - Parameter nrhs: (input) Number of right-hand sides to be solved for.
 *
 *  - Returns: Size of state space required in bytes.                           */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
size_t SparseGetStateSize_Double(SparseIterativeMethod method,
  bool preconditioner, int m, int n, int nrhs);

/*! Returns size in bytes of state space required for call to
 *  `SparseIterate()` for float values.
 *
 *  - Parameter method: (input) Method to return required state space size for.
 *
 *  - Parameter preconditioner: (input) True if a preconditioner will be supplied,
 *         false otherwise.
 *
 *  - Parameter m: (input) Number of entries in right-hand side (rows in matrix `A`).
 *
 *  - Parameter n: (input) Number of variables to solve for (columns in matrix `A`).
 *
 *  - Parameter nrhs: (input) Number of right-hand sides to be solved for.
 *
 *  - Returns: Size of state space required in bytes.                           */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
size_t SparseGetStateSize_Float(SparseIterativeMethod method,
  bool preconditioner, int m, int n, int nrhs);

/*! Returns size in bytes of state space required for call to
 *  `SparseIterate()` for complex double values.
 *
 *  - Parameter method: (input) Method to return required state space size for.
 *
 *  - Parameter preconditioner: (input) True if a preconditioner will be supplied,
 *         false otherwise.
 *
 *  - Parameter m: (input) Number of entries in right-hand side (rows in matrix `A`).
 *
 *  - Parameter n: (input) Number of variables to solve for (columns in matrix `A`).
 *
 *  - Parameter nrhs: (input) Number of right-hand sides to be solved for.
 *
 *  - Returns: Size of state space required in bytes.                           */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
size_t SparseGetStateSize_Complex_Double(SparseIterativeMethod method,
  bool preconditioner, int m, int n, int nrhs);

/*! Returns size in bytes of state space required for call to
 *  `SparseIterate()` for complex float values.
 *
 *  - Parameter method: (input) Method to return required state space size for.
 *
 *  - Parameter preconditioner: (input) True if a preconditioner will be supplied,
 *         false otherwise.
 *
 *  - Parameter m: (input) Number of entries in right-hand side (rows in matrix `A`).
 *
 *  - Parameter n: (input) Number of variables to solve for (columns in matrix `A`).
 *
 *  - Parameter nrhs: (input) Number of right-hand sides to be solved for.
 *
 *  - Returns: Size of state space required in bytes.                           */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
size_t SparseGetStateSize_Complex_Float(SparseIterativeMethod method,
  bool preconditioner, int m, int n, int nrhs);

/*! Perform a single iteration of the specified iterative method for double values with preconditioner.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Double()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 *
 *  - Parameter Preconditioner: (input) Preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double R, DenseMatrix_Double X,
  SparseOpaquePreconditioner_Double Preconditioner);

/*! Perform a single iteration of the specified iterative method for float values with preconditioner.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Float()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 *
 *  - Parameter Preconditioner: (input) Preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans, DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float R, DenseMatrix_Float X,
  SparseOpaquePreconditioner_Float Preconditioner);

/*! Perform a single iteration of the specified iterative method for complex double values with preconditioner.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Complex_Double()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 *
 *  - Parameter Preconditioner: (input) Preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y),
  DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double R, DenseMatrix_Complex_Double X,
  SparseOpaquePreconditioner_Complex_Double Preconditioner);

/*! Perform a single iteration of the specified iterative method for complex float values with preconditioner.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Complex_Float()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 *
 *  - Parameter Preconditioner: (input) Preconditioner to apply.                    */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y),
  DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float R, DenseMatrix_Complex_Float X,
  SparseOpaquePreconditioner_Complex_Float Preconditioner);

/*! Perform a single iteration of the specified iterative method for double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Double()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Double X, DenseMatrix_Double Y),
  DenseMatrix_Double B, DenseMatrix_Double R, DenseMatrix_Double X);

/*! Perform a single iteration of the specified iterative method for float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Double()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Float X, DenseMatrix_Float Y),
  DenseMatrix_Float B, DenseMatrix_Float R, DenseMatrix_Float X);

/*! Perform a single iteration of the specified iterative method for complex double values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Double()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Double X, DenseMatrix_Complex_Double Y),
  DenseMatrix_Complex_Double B, DenseMatrix_Complex_Double R, DenseMatrix_Complex_Double X);

/*! Perform a single iteration of the specified iterative method for complex float values.
 *
 *  - Parameter method: (input) Iterative method specification, eg return value of
 *         `SparseConjugateGradient()`.
 *
 *         Note that the options related to convergence testing (e.g.
 *         `maxIterations`, `atol`, `rtol`) are ignored as convergence tests must be
 *         performed by the user.
 *
 *  - Parameter iteration: (input) The current iteration number, starting from 0. If
 *         `iteration<0`, then the current iterate is finalised, and the value of
 *         `X` is updated (note that this may force some methods to restart,
 *         slowing convergence).
 *
 *  - Parameter state: (input/output) A pointer to a state-space of size returned by
 *         `SparseGetStateSize_Double()`. This memory must be 16-byte aligned
 *         (any allocation returned by `malloc()` has this property). It must not
 *         be altered by the user between iterations, but may be safely discarded
 *         after the final call to `SparseIterate()`.
 *
 *  - Parameter converged: (input) Convergence status of each solution vector.
 *         `converged[j]=true` indicates that the vector stored as column `j` of `X`
 *         has converged, and it should be ignored in this iteration.
 *
 *  - Parameter ApplyOperator: `ApplyOperator(accumulate, trans, X, Y)`
 *             should perform the operation `Y = op(A)X` if `accumulate` is `false`,
 *             or `Y += op(A)X` if `accumulate` is `true`.
 *    - term `accumulate` : (input) Indicates whether to perform `Y += op(A)X` (if
 *            true) or `Y = op(A)X` (if false).
 *    - term `trans`: (input) Indicates whether `op(A)` is the application of `A`
 *            (`trans=CblasNoTrans`) or `A^T` (`trans=CblasTrans`).
 *    - term  `X`: The matrix to multiply.
 *    - term  `Y`: The matrix in which to accumulate or store the result.
 *
 *  - Parameter B: (input) The right-hand sides to solve for.
 *
 *  - Parameter R: (output) Residual estimate. On entry with `iteration=0`, it must hold
 *         the residuals `b-Ax` (equal to `B` if `X=0`). On return from each call with
 *         `iteration>=0`, the first entry(s) of each vector contain various
 *         estimates of norms to be used in convergence testing.
 *    - term For CG and GMRES:
 *          `R(0,j) `holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(0,j)`:
 *          `R(0,j)` holds an estimate of` || A^T(b-Ax) ||_2` for the j-th rhs.
 *    - term For LSMR  - `R(1,j)`:
 *          `R(1,j)` holds an estimate of` || b-Ax ||_2` for the j-th rhs.
 *    - term For LSMR - `R(2,j)`:
 *          `R(2,j)` holds an estimate of `|| A ||_F`, the Frobenius norm of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *    - term For LSMR - `R(3,j)`:
 *          `R(3,j) `holds an estimate of `cond(A)`, the condition number of `A`,
 *                  estimated using calculations related to the j-th rhs.
 *
 *         Other entries of `R` may be used by the routine as a workspace.
 *         On return from a call with `iteration<0`, the exact residual vector
 *         b-Ax is returned.
 *
 *  - Parameter X: (input/output) The current estimate of the solution vectors X.
 *         On entry with iteration=0, this should be an initial estimate for the
 *         solution. If no good estimate is available, use X = 0.0.
 *         Depending on the method used, X may not be updated at each iteration,
 *         or may be used to store some other vector.
 *         The user should make a call with iteration<0 once convergence has
 *         been achieved to bring X up to date.
 */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
void SparseIterate(SparseIterativeMethod method, int iteration,
  const bool *converged, void *state,
  void (^_Nonnull ApplyOperator)(bool accumulate, enum CBLAS_TRANSPOSE trans,
    DenseMatrix_Complex_Float X, DenseMatrix_Complex_Float Y),
  DenseMatrix_Complex_Float B, DenseMatrix_Complex_Float R, DenseMatrix_Complex_Float X);

/******************************************************************************
 *  @group Memory Management
 ******************************************************************************
 *
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

/*! Increase reference count on a symbolic factorization object,
 *            returning a copy.
 *
 *  - Parameter SymbolicFactor The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of SymbolicFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSymbolicFactorization SparseRetain(
  SparseOpaqueSymbolicFactorization SymbolicFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Double SparseRetain(
  SparseOpaqueFactorization_Double NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueFactorization_Float SparseRetain(
  SparseOpaqueFactorization_Float NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueFactorization_Complex_Double SparseRetain(
  SparseOpaqueFactorization_Complex_Double NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueFactorization_Complex_Float SparseRetain(
  SparseOpaqueFactorization_Complex_Float NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Double SparseRetain(SparseOpaqueSubfactor_Double NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) )
SparseOpaqueSubfactor_Float SparseRetain(SparseOpaqueSubfactor_Float NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueSubfactor_Complex_Double SparseRetain(SparseOpaqueSubfactor_Complex_Double NumericFactor);

/*! Increase reference count on a numeric factorization object,
 *            returning a copy.
 *
 *  - Parameter NumericFactor: The symbolic factorization to increase the underlying
 *         reference count of.
 *
 *  - Returns: A copy of NumericFactor.                                        */
static inline SPARSE_PUBLIC_INTERFACE API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) 
SparseOpaqueSubfactor_Complex_Float SparseRetain(SparseOpaqueSubfactor_Complex_Float NumericFactor);

/**** Cleaning up resources ***************************************************/

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSymbolicFactorization Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueFactorization_Double Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueFactorization_Float Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueFactorization_Complex_Double Opaque)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueFactorization_Complex_Float Opaque)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSubfactor_Double Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSubfactor_Float Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSubfactor_Complex_Double Opaque)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse Object's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The resource to be freed.                                   */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaqueSubfactor_Complex_Float Opaque)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse matrix's references to any memory allocated
 *  by the Sparse library.
 *
 *   Reports an error if the matrix was not allocated by Sparse.
 *
 *  - Parameter Matrix: The matrix to be freed.                                     */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseMatrix_Double Matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse matrix's references to any memory allocated
 *  by the Sparse library.
 *
 *   Reports an error if the matrix was not allocated by Sparse.
 *
 *  - Parameter Matrix: The matrix to be freed.                                     */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseMatrix_Float Matrix)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse matrix's references to any memory allocated
 *  by the Sparse library.
 *
 *   Reports an error if the matrix was not allocated by Sparse.
 *
 *  - Parameter Matrix: The matrix to be freed.                                     */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseMatrix_Complex_Double Matrix)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse matrix's references to any memory allocated
 *  by the Sparse library.
 *
 *   Reports an error if the matrix was not allocated by Sparse.
 *
 *  - Parameter Matrix: The matrix to be freed.                                     */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseMatrix_Complex_Float Matrix)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse Preconditioner's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The Preconditioner to be freed.                             */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaquePreconditioner_Double Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Preconditioner's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The Preconditioner to be freed.                             */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaquePreconditioner_Float Opaque)
API_AVAILABLE( macos(10.13), ios(11), watchos(4), tvos(11) );

/*! Release a Sparse Preconditioner's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The Preconditioner to be freed.                             */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaquePreconditioner_Complex_Double Opaque)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*! Release a Sparse Preconditioner's references to any memory allocated
 *  by the sparse library.
 *
 *  - Parameter Opaque: The Preconditioner to be freed.                             */
static inline SPARSE_PUBLIC_INTERFACE
void SparseCleanup(SparseOpaquePreconditioner_Complex_Float Opaque)
API_AVAILABLE( macos(15.5), ios(18.5), watchos(11.5), tvos(18.5), visionos(2.5) ) ;

/*********************************** END **************************************/

#if __has_feature(nullability)
# pragma clang assume_nonnull end
#endif

#if defined SPARSE_INCLUDED_VIA_ACCELERATE /* Included via Accelerate */
# include <vecLib/Sparse/SolveImplementation.h>
#else /* Standalone environments */
# include "SolveImplementation.h"
#endif

#if !__has_include( <Availability.h> )
  #undef __API_AVAILABLE
#endif

#endif /* __has_attribute(overloadable) */
#endif /* SPARSE_SOLVE_HEADER */
