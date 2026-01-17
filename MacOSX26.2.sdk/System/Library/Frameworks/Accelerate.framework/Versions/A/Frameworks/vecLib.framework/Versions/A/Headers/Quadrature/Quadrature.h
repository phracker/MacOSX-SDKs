// Numerical Analysis Library

#ifndef __QUADRATURE_PUBLIC_HEADER__
#define __QUADRATURE_PUBLIC_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

/*! @enum quadrature_status

@abstract Quadrature return status

@discussion Success is 0, and errors have a negative value.

@constant QUADRATURE_SUCCESS Success.
@constant QUADRATURE_ERROR Generic error.
@constant QUADRATURE_INVALID_ARG_ERROR Invalid argument.
@constant QUADRATURE_ALLOC_ERROR Memory allocation failed.
@constant QUADRATURE_INTERNAL_ERROR This is a bug in the Quadrature code, please file a bug report.
@constant QUADRATURE_INTEGRATE_MAX_EVAL_ERROR The requested accuracy limit could not be reached with the allowed number of evals/subdivisions.
@constant QUADRATURE_INTEGRATE_BAD_BEHAVIOUR_ERROR Extremely bad integrand behaviour, or excessive roundoff error occurs at some points of the integration interval.
*/
typedef enum {

  QUADRATURE_SUCCESS                          =    0,
  
  QUADRATURE_ERROR                            =   -1,
  QUADRATURE_INVALID_ARG_ERROR                =   -2,
  QUADRATURE_ALLOC_ERROR                      =   -3,
  QUADRATURE_INTERNAL_ERROR                   =  -99,

  QUADRATURE_INTEGRATE_MAX_EVAL_ERROR         = -101,
  QUADRATURE_INTEGRATE_BAD_BEHAVIOUR_ERROR    = -102

} quadrature_status;

#include "Integration.h"

#ifdef __cplusplus
}
#endif

#endif // __QUADRATURE_PUBLIC_HEADER__
