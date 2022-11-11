//
//  MXSignpost.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#ifndef MXSignpost_h
#define MXSignpost_h

#if defined(__cplusplus)
extern "C" {
#endif
#include <MetricKit/MXSignpost_Private.h>
    
#pragma mark - Public MXSignpost* API surface
/*!
 * @header MXSignpost
 *
 * The MXSignpost API surface wraps calls to normal os_signpost in order to
 * gather snapshots of process-level metrics. THESE CALLS ARE MUCH MORE
 * EXPENSIVE THAN NORMAL OS_SIGNPOST_* CALLS and are meant to be called
 * sparingly. Bulk replacing of calls to os_signpost with MXSignpost will lead
 * to potentially large performance regressions.
 *
 * This API surface functions identically to os_signpost. Please see
 * <os/signpost.h> for more information on usage of os_signpost.
 */

/*!
 * @function MXSignpostEventEmit
 *
 * @abstract
 * Emits a standalone os_signpost event with @c os_signpost_event_emit() and
 * includes a snapshot of performance metrics of the emitting process.
 *
 * This function is *much more expensive* than a direct call to
 * os_signpost_event_emit() and should be used only sparingly at points of
 * interest.
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostEventEmit(log, event_id, name, ...) _MXSignpostEventEmit_guaranteed_args(log, event_id, name, "" __VA_ARGS__)
/*!
 * @function MXSignpostIntervalBegin
 *
 * @abstract
 * Begins an os_signpost interval with @c os_signpost_interval_begin() and
 * includes a snapshot of performance metrics of the emitting process.
 *
 * This function is *much more expensive* than a direct call to
 * os_signpost_interval_begin() and should be used only sparingly at points of
 * interest.
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostIntervalBegin(log, event_id, name, ...) _MXSignpostIntervalBegin_guaranteed_args(log, event_id, name, "" __VA_ARGS__)

/*!
 * @function MXSignpostAnimationIntervalBegin
 *
 * @abstract
 * Begins an os_signpost animation interval with @c os_signpost_animation_interval_begin() and
 * includes a snapshot of performance metrics of the emitting process.
 *
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostAnimationIntervalBegin(log, event_id, name, ...) _MXSignpostAnimationIntervalBegin_guaranteed_args(log, event_id, name, "" __VA_ARGS__)

/*!
 * @function MXSignpostIntervalEnd
 *
 * @abstract
 * Ends an os_signpost interval with @c os_signpost_interval_end() and includes
 * a snapshot of performance metrics of the emitting process.
 *
 * This function is *much more expensive* than a direct call to
 * os_signpost_interval_end() and should be used only sparingly at points of
 * interest.
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostIntervalEnd(log, event_id, name, ...) _MXSignpostIntervalEnd_guaranteed_args(log, event_id, name, "" __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //MXSignpost_h
