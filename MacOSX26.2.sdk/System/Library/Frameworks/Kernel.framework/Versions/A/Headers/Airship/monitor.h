//
//  monitor.h
//  Airship
//
//  Created by Jason McElrath on 1/15/20.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__monitor_h
#define airship__core__api__monitor_h

/**
 * @file monitor.h
 * @brief Public monitor interface.
 */

#include <Airship/base.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/**
 * @brief Airship monitor handle type.
 *
 * Airship monitors are used by clients to wait for or respond to changes in an
 * Airship driver. Each monitor is associated with a particular numerical value
 * within a driver.
 */
typedef struct airship_monitor *airship_monitor_t;

/**
 * @brief Sets the execution context on which the event and cancellation
 * handlers will be invoked.
 *
 * This function may not be called after the monitor is activated.
 *
 * @param monitor The monitor to be configured.
 * @param queue The execution context to use for handler invocations.
 */
AIRSHIP_EXPORT
void airship_monitor_set_queue(airship_monitor_t monitor, airship_execution_queue_t queue);

/**
 * @brief Sets the handler to be invoked when the tracked condition changes from
 * unsatisfied to satisfied.
 *
 * Handler invocations are serialized, even if the execution context configured
 * with `::airship_monitor_set_queue` is concurrent. If the tracked condition
 * changes from unsatisfied to satisfied while the event handler is executing,
 * the handler will be invoked again after the current invocation returns.
 *
 * Multiple changes of the tracked condition's status may be coalesced into a
 * single handler invocation.
 *
 * This function may not be called after the monitor is activated.
 *
 * @param monitor The monitor to be configured.
 * @param handler The handler to be invoked when the monitored condition becomes
 * satisfied.
 */
AIRSHIP_EXPORT
void airship_monitor_set_event_handler(airship_monitor_t monitor, airship_block_t handler);

/**
 * @brief Sets the handler to be invoked when the monitor is canceled.
 *
 * The cancellation handler is asynchronously invoked after the monitor is
 * canceled and all pending event handler invocations are finished. Handler
 * invocations are serialized, even if the execution context configured with
 * `::airship_monitor_set_queue` is concurrent.
 *
 * This function may not be called after the monitor is activated.
 *
 * @param monitor The monitor to be configured.
 * @param handler The handler to be invoked after the monitor is canceled and
 * all pending event handler invocations are finished.
 */
AIRSHIP_EXPORT
void airship_monitor_set_cancel_handler(airship_monitor_t monitor, airship_block_t handler);

/**
 * @brief Activates a monitor, locking its configuration and enabling handler
 * invocation.
 *
 * Monitors are created in an inactive state, and must be activated before they
 * will invoke any handlers. Upon activation, a monitor that is not otherwise
 * suspended will begin handler invocation according to the same semantics as
 * `::airship_monitor_resume`.
 *
 * Calls to these functions are prohibited after activation:
 * - `::airship_monitor_set_queue`
 * - `::airship_monitor_set_event_handler`
 * - `::airship_monitor_set_cancel_handler`
 *
 * @param monitor The monitor to be activated.
 */
AIRSHIP_EXPORT
void airship_monitor_activate(airship_monitor_t monitor);

/**
 * @brief Suspends a monitor, pausing handler invocation.
 *
 * Suspension prevents further invocation of the event handler until resumption,
 * but does not interrupt invocations that are already in progress.
 *
 * Calling `::airship_monitor_suspend` on a monitor that is already suspended
 * has no effect.
 *
 * @param monitor The monitor to be suspended.
 */
AIRSHIP_EXPORT
void airship_monitor_suspend(airship_monitor_t monitor);

/**
 * @brief Un-suspends a monitor, resuming handler invocation.
 *
 * Resumption causes a monitor to resume invoking its handler when the tracked
 * condition becomes satisfied. Upon resumption, a monitor will invoke its
 * handler if and only if the tracked condition is satisfied at the
 * time or resumption. I.e.:
 * - The event handler will be invoked if the tracked condition is satisfied
 * upon resumption, even if the tracked condition was satisfied during the
 * entire period of suspension.
 * - The event handler will not be invoked if the tracked condition is not
 * satisfied upon resumption, even if the tracked condition was at some point
 * satisfied during the period of suspension.
 *
 * Calling `::airship_monitor_resume` on a monitor that is not suspended has no
 * effect.
 *
 * @param monitor The monitor to be resumed.
 */
AIRSHIP_EXPORT
void airship_monitor_resume(airship_monitor_t monitor);

/**
 * @brief Cancels a monitor, unblocking waiters and preventing further
 * invocations of its handler.
 *
 * Cancellation prevents any further invocations of the event handler, but does
 * not interrupt invocations that are already in progress.
 *
 * Cancellation causes any pending or future calls to `::airship_monitor_wait`
 * or `::airship_monitor_timedwait` to immediately unblock.
 *
 * @param monitor The monitor to be canceled.
 */
AIRSHIP_EXPORT
void airship_monitor_cancel(airship_monitor_t monitor);

/**
 * @brief Destroys a monitor, releasing any associated resources.
 *
 * Destruction implicitly cancels a monitor, though concurrent calls to
 * `::airship_monitor_destroy` and `::airship_monitor_wait` or
 * `::airship_monitor_timedwait` are inherently unsafe.
 *
 * @param monitor The monitor to be destroyed.
 */
AIRSHIP_EXPORT
void airship_monitor_destroy(airship_monitor_t monitor);

/**
 * @brief Waits indefinitely for a monitor's condition to become satisfied.
 *
 * Blocks the caller until the monitor's tracked condition becomes satisifed.
 * Returns immediately if the tracked condition is already satisfied.
 *
 * Note that the status of the tracked condition may change after this function
 * returns.
 *
 * @param monitor The monitor tracking the condition to be awaited.
 * @retval ::AIRSHIP_OK if the tracked condition is satisfied.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ECANCELED if unblocked by `::airship_monitor_cancel`.
 */
AIRSHIP_EXPORT
airship_result_t airship_monitor_wait(airship_monitor_t monitor);

/**
 * @brief Waits with timeout for a monitor's condition to become satisfied.
 *
 * Blocks the caller until the monitor's tracked condition becomes satisifed, or
 * until a timeout occurs. Returns immediately if the tracked condition is
 * already satisfied.
 *
 * Note that the status of the tracked condition may change after this function
 * returns.
 *
 * @param monitor The monitor tracking the condition to be awaited.
 * @param timeout_msec Timeout interval in milliseconds.
 * @retval ::AIRSHIP_OK if the tracked condition is satisfied.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ECANCELED if unblocked by `::airship_monitor_cancel`.
 * @retval ::AIRSHIP_ETIMEOUT if timeout occurred.
 */
AIRSHIP_EXPORT
airship_result_t airship_monitor_timedwait(airship_monitor_t monitor, uint32_t timeout_msec);

/**
 * @brief Abort-safe variant of `airship_monitor_wait`.
 *
 * This function is equivalent to `airship_monitor_wait`, except that it waits
 * interruptibly with `THREAD_INTERRUPTIBLE` (see kern_types.h).
 *
 * Blocks the caller until the monitor's tracked condition becomes satisifed.
 * Returns immediately if the tracked condition is already satisfied.
 *
 * Note that the status of the tracked condition may change after this function
 * returns.
 *
 * @param monitor The monitor tracking the condition to be awaited.
 * @retval ::AIRSHIP_OK if the tracked condition is satisfied.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ECANCELED if unblocked by `::airship_monitor_cancel` or for
 * any reason listed in the description for `THREAD_INTERRUPTIBLE`.
 */
AIRSHIP_EXPORT
airship_result_t airship_monitor_wait_interruptible(airship_monitor_t monitor);

/**
 * @brief Abort-safe variant of `airship_monitor_timedwait`.
 *
 * This function is equivalent to `airship_monitor_timedwait`, except that it
 * waits interruptibly with `THREAD_INTERRUPTIBLE` (see kern_types.h).
 *
 * Blocks the caller until the monitor's tracked condition becomes satisifed, or
 * until a timeout occurs. Returns immediately if the tracked condition is
 * already satisfied.
 *
 * Note that the status of the tracked condition may change after this function
 * returns.
 *
 * @param monitor The monitor tracking the condition to be awaited.
 * @param timeout_msec Timeout interval in milliseconds.
 * @retval ::AIRSHIP_OK if the tracked condition is satisfied.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ECANCELED if unblocked by `::airship_monitor_cancel` or for
 * any reason listed in the description for `THREAD_INTERRUPTIBLE`.
 * @retval ::AIRSHIP_ETIMEOUT if timeout occurred.
 */
AIRSHIP_EXPORT
airship_result_t airship_monitor_timedwait_interruptible(airship_monitor_t monitor, uint32_t timeout_msec);

/// Comparators for use with `::airship_monitor_set_criterion`.
typedef enum airship_monitor_comparator
{
    /// Tracks whether the associated value is equal to the comparand.
    AIRSHIP_MONITOR_CMP_EQ,
    /// Tracks whether the associated value is not equal to the comparand.
    AIRSHIP_MONITOR_CMP_NEQ,
    /// Tracks whether the associated value is less than to the comparand.
    AIRSHIP_MONITOR_CMP_LT,
    /**
     * @brief Tracks whether the associated value is less than or equal to the
     * comparand.
     */
    AIRSHIP_MONITOR_CMP_LE,
    /// Tracks whether the associated value is greater than the comparand.
    AIRSHIP_MONITOR_CMP_GT,
    /**
     * @brief Tracks whether the associated value is greater than or equal to
     * the comparand.
     */
    AIRSHIP_MONITOR_CMP_GE,
} airship_monitor_comparator_t;

/**
 * @brief Sets the criterion for a monitor.
 *
 * This function sets the criterion to be applied to the associated driver
 * value to form the tracked condition.
 *
 * @param monitor The monitor to be configured.
 * @param comparator The comparator to be used.
 * @param comparand The value to be compared with the associated driver value.
 * @param mask The mask to be applied to the associated driver value before it
 * is compared with the comparand.
 */
AIRSHIP_EXPORT
void airship_monitor_set_criterion(airship_monitor_t monitor, airship_monitor_comparator_t comparator, uint64_t comparand, uint64_t mask);

#ifdef __cplusplus
namespace airship {
/// C++ wrapper for automatic lifecycle management of monitor handles.
using monitor = wrapper<airship_monitor, airship_monitor_destroy>;
} // namespace airship
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__monitor_h */
