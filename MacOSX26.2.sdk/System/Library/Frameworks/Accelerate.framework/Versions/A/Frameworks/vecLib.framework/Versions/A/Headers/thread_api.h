#pragma once

#if __has_include(<os/availability.h>)
#   include <os/availability.h>
#else // __has_include(<os/availability.h>)
#   undef API_AVAILABLE
#   define API_AVAILABLE(...) /* Nothing */
#endif // __has_include(<os/availability.h>)

#ifdef __cplusplus
extern "C" {
#endif

enum BLAS_THREADING: unsigned int
{
    BLAS_THREADING_MULTI_THREADED API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 0, // Accelerate decides how many threads to use
    BLAS_THREADING_SINGLE_THREADED API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)),    // Single threaded only

    BLAS_THREADING_MAX_OPTIONS API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0))
};

/*! @abstract Set the threading model to use for BLAS and LAPACK
 *
 *  @discussion
 *  Set the threading model to use for the subsequent calls into BLAS and LAPACK.
 *  This setting is per thread, saved in a thread local variable.
 *
 *  @param threading (input) The desired threading model.
 *
 *  @return
 *        0:  Success <br>
 *        -1: Option is not supported on this platform
 */
int BLASSetThreading(const enum BLAS_THREADING threading)
API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/*! @abstract Query what the currently selected threading model is.
 *
 *  @discussion
 *  This routine will return what the currently selected threading model is.
 *  This setting is per thread, saved in a thread local variable.
 *
 *  @return An enum representing the currently selected threading model.
 */
enum BLAS_THREADING BLASGetThreading()
API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#ifdef __cplusplus
}
#endif
