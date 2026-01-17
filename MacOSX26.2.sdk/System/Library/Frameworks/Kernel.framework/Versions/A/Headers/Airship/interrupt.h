//
//  interrupt.h
//  Airship
//
//  Created by Jason McElrath on 3/14/25.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__interrupt_h
#define airship__core__api__interrupt_h

/**
 * @file interrupt.h
 * @brief Public interrupt interface.
 */

#include <Airship/base.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/**
 * @brief Airship interrupt handle type.
 *
 * Airship interrupt handles are used by clients respond to interrupts generated
 * by a device. Interrupts may occur supriously and may be coalesced. There is
 * no way to reliably guarantee that no interrupts are pending. Clients of this
 * interface *must* behave accordingly.
 */
typedef struct airship_interrupt *airship_interrupt_t;

/**
 * @brief Creates a interrupt associated with a transfer ring's state.
 *
 * The returned handle must be released with `::airship_interrupt_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param name The name of the interrupt to be accessed.
 * @param selector Numerical selector of the interrupt to be accessed.
 * @returns The newly created interrupt handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_interrupt_t AIRSHIP_NULLABLE airship_interrupt_create(airship_client_t client, airship_string_t name, uint32_t selector);

/**
 * @brief Destroys a interrupt, releasing any associated resources.
 *
 * Destruction implicitly cancels a interrupt.
 *
 * @param interrupt The interrupt to be destroyed.
 */
AIRSHIP_EXPORT
void airship_interrupt_destroy(airship_interrupt_t interrupt);

/**
 * @brief Sets the execution context on which the event and cancellation
 * handlers will be invoked.
 *
 * This function may not be called after the interrupt is activated.
 *
 * @param interrupt The interrupt to be configured.
 * @param queue The execution context to use for handler invocations.
 */
AIRSHIP_EXPORT
void airship_interrupt_set_queue(airship_interrupt_t interrupt, airship_execution_queue_t queue);

/**
 * @brief Sets the handler to be invoked when the tracked condition changes from
 * unsatisfied to satisfied.
 *
 * Handler invocations are serialized, even if the execution context configured
 * with `::airship_interrupt_set_queue` is concurrent. If the tracked condition
 * changes from unsatisfied to satisfied while the event handler is executing,
 * the handler will be invoked again after the current invocation returns.
 *
 * Multiple changes of the tracked condition's status may be coalesced into a
 * single handler invocation.
 *
 * This function may not be called after the interrupt is activated.
 *
 * This function replaces `::airship_driver_set_interrupt_handler`.
 *
 * @param interrupt The interrupt to be configured.
 * @param handler The handler to be invoked when the interrupted condition becomes
 * satisfied.
 */
AIRSHIP_EXPORT
void airship_interrupt_set_event_handler(airship_interrupt_t interrupt, airship_block_t handler);

/**
 * @brief Sets the handler to be invoked when the interrupt is canceled.
 *
 * The cancellation handler is asynchronously invoked after the interrupt is
 * canceled and all pending event handler invocations are finished. Handler
 * invocations are serialized, even if the execution context configured with
 * `::airship_interrupt_set_queue` is concurrent.
 *
 * This function may not be called after the interrupt is activated.
 *
 * @param interrupt The interrupt to be configured.
 * @param handler The handler to be invoked after the interrupt is canceled and
 * all pending event handler invocations are finished.
 */
AIRSHIP_EXPORT
void airship_interrupt_set_cancel_handler(airship_interrupt_t interrupt, airship_block_t handler);

/**
 * @brief Fetches the numeric vector for the interrupt.
 *
 * @param interrupt The interrupt to be accessed.
 * @returns The numeric vector associated with the interrupt.
 */
AIRSHIP_EXPORT
uint32_t airship_interrupt_get_device_vector(airship_interrupt_t interrupt);

/**
 * @brief Activates a interrupt, locking its configuration and enabling handler
 * invocation.
 *
 * interrupts are created in an inactive state, and must be activated before
 * they will invoke any handlers. Upon activation, a interrupt that is not
 * otherwise suspended will begin handler invocation according to the same
 * semantics as `::airship_interrupt_resume`.
 *
 * Calls to these functions are prohibited after activation:
 * - `::airship_interrupt_set_queue`
 * - `::airship_interrupt_set_event_handler`
 * - `::airship_interrupt_set_cancel_handler`
 *
 * @param interrupt The interrupt to be activated.
 */
AIRSHIP_EXPORT
void airship_interrupt_activate(airship_interrupt_t interrupt);

/**
 * @brief Suspends a interrupt, pausing handler invocation.
 *
 * Suspension prevents further invocation of the event handler until resumption,
 * but does not interrupt invocations that are already in progress.
 *
 * Calling `::airship_interrupt_suspend` on a interrupt that is already
 * suspended has no effect.
 *
 * @param interrupt The interrupt to be suspended.
 */
AIRSHIP_EXPORT
void airship_interrupt_suspend(airship_interrupt_t interrupt);

/**
 * @brief Un-suspends a interrupt, resuming handler invocation.
 *
 * Resumption causes a interrupt to resume invoking its handler when the device
 * generates an interrupt. Upon resumption, the event handler is re-armed and
 * will be invoked for any new interrupts generated by the device. The event
 * handler will not be invoked for interrupts that were generated by the device
 * while the interrupt was suspended.
 *
 * Calling `::airship_interrupt_resume` on a interrupt that is not suspended has
 * no effect.
 *
 * @param interrupt The interrupt to be resumed.
 */
AIRSHIP_EXPORT
void airship_interrupt_resume(airship_interrupt_t interrupt);

/**
 * @brief Cancels a interrupt, preventing further invocations of its handler.
 *
 * Cancellation prevents any further invocations of the event handler, but does
 * not interrupt invocations that are already in progress.
 *
 * @param interrupt The interrupt to be canceled.
 */
AIRSHIP_EXPORT
void airship_interrupt_cancel(airship_interrupt_t interrupt);

#ifdef __cplusplus
namespace airship {
/// C++ wrapper for automatic lifecycle management of interrupt handles.
using interrupt = wrapper<airship_interrupt, airship_interrupt_destroy>;
} // namespace airship
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__interrupt_h */
