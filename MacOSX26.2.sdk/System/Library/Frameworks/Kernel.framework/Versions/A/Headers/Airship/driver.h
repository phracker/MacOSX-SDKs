//
//  driver.h
//  Airship
//
//  Created by Jason McElrath on 9/18/20.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__driver_h
#define airship__core__api__driver_h

/**
 * @file driver.h
 * @brief Public driver interface.
 */

#include <Airship/base.h>
#include <Airship/device_transport.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/// Airship driver handle type.
typedef struct airship_driver *airship_driver_t;

/**
 * @brief Probes a device to determine its properties.
 *
 * The returned dictionary always contains the following items:
 * - `::kAirshipVendor`: A string indicating the device vendor.
 * - `::kAirshipChipset`: A string indicating the device chipset.
 *
 * The returned dictionary may also contain the following items:
 * - `::kAirshipRole`: A string that represents the device's chipset-specific role.
 *
 * The returned dictionary must be released by the caller.
 *
 * @param transport The transport mechanism for the device to be probed.
 * @param vendor_id The vendor ID of the device.
 * @param device_id The device ID of the device.
 * @returns A dictionary containing the probed properties, or `NULL` on error.
 */
AIRSHIP_EXPORT
airship_dictionary_t AIRSHIP_NULLABLE airship_driver_probe_device(airship_device_transport_t transport, uint16_t vendor_id, uint16_t device_id);

/**
 * @brief Creates an airship driver instance.
 *
 * The returned handle must be released with `::airship_driver_destroy`.
 *
 * @param protocol The name of the ipc protocol to be instantiated.
 * @returns The newly created driver handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_driver_t AIRSHIP_NULLABLE airship_driver_create(airship_string_t protocol);

/**
 * @brief Destroys a driver, releasing any associated resources.
 *
 * It is unsafe to destroy a driver without first permanently revoking the
 * associated device's access to shared resources.
 *
 * Once destroyed, a driver will not invoke any handlers.
 *
 * @pre All connected client handles created with
 * `::airship_client_create_direct` are destroyed.
 *
 * @param driver The driver handle to be destroyed.
 */
AIRSHIP_EXPORT
void airship_driver_destroy(airship_driver_t driver);

/**
 * @brief Sets a driver's configuration dictionary.
 * @param driver The driver handle to be configured.
 * @param config The configuration dictionary to be applied.
 */
AIRSHIP_EXPORT
void airship_driver_set_configuration(airship_driver_t driver, airship_dictionary_t AIRSHIP_NULLABLE config);

/**
 * @brief Sets one of the driver's execution contexts.
 *
 * @param driver The driver handle to be configured.
 * @param role The protocol- or chipset-specific role to be configured.
 * @param queue The execution context to be used.
 */
AIRSHIP_EXPORT
void airship_driver_set_queue(airship_driver_t driver, airship_string_t role, airship_execution_queue_t AIRSHIP_NULLABLE queue);

/**
 * @brief Sets the handler to be invoked upon execution stage changes.
 *
 * The driver will invoke the provided handler when it observes a change in the
 * device's execution stage.
 *
 * Handler invocations are serialized. The handler may be invoked from any
 * thread context or with locks held. It is unsafe for the handler to invoke or
 * block on the invocation of any Airship API unless otherwise noted.
 *
 * @param driver The driver handle to be configured.
 * @param handler The handler to be invoked on exec stage changes.
 */
AIRSHIP_EXPORT
void airship_driver_set_exec_stage_change_handler(airship_driver_t driver, airship_block_t AIRSHIP_NULLABLE handler);

/**
 * @brief Sets the handler to be invoked upon power state changes.
 *
 * The driver will invoke the provided handler when it observes a change in the
 * device's power state.
 *
 * Handler invocations are serialized. The handler may be invoked from any
 * thread context or with locks held. It is unsafe for the handler to invoke or
 * block on the invocation of any Airship API unless otherwise noted.
 *
 * @param driver The driver handle to be configured.
 * @param handler The handler to be invoked on power state changes.
 */
AIRSHIP_EXPORT
void airship_driver_set_power_state_change_handler(airship_driver_t driver, airship_block_t AIRSHIP_NULLABLE handler);

/**
 * @brief Sets the handler to be invoked when an IPC error occurs.
 *
 * The driver will invoke the provided handler when an IPC error occurs.
 *
 * Handler invocations are serialized. The handler may be invoked from any
 * thread context or with locks held. It is unsafe for the handler to invoke or
 * block on the invocation of any Airship API unless otherwise noted.
 *
 * @param driver The driver handle to be configured.
 * @param handler The handler to be invoked when an IPC error occurs.
 */
AIRSHIP_EXPORT
void airship_driver_set_ipc_error_handler(airship_driver_t driver, airship_block_t AIRSHIP_NULLABLE handler);

/**
 * @brief Activates a driver.
 *
 * Drivers are initialized in an inactive state and must be activated to begin
 * operation.
 *
 * Calls to these functions are prohibited after activation:
 * - `::airship_driver_set_configuration`
 * - `::airship_driver_set_queue`
 * - `::airship_driver_set_exec_stage_change_handler`
 * - `::airship_driver_set_power_state_change_handler`
 * - `::airship_driver_set_ipc_error_handler`
 *
 * @param driver The driver handle to be activated.
 * @returns `::AIRSHIP_OK` if successful, or an error code on failure.
 */
AIRSHIP_EXPORT
airship_result_t airship_driver_activate(airship_driver_t driver);

/**
 * @brief Places a driver in reset, clearing internal state and suspending
 * device interaction.
 *
 * It is unsafe to place a driver in reset without first permanently revoking
 * the associated device's access to shared resources.
 *
 * A driver will not invoke any handlers while held in reset. This function
 * waits for any currently-executing handlers to finish before returning.
 *
 * Drivers are initialized in reset.
 *
 * The driver must first be activated with `::airship_driver_activate`.
 *
 * @param driver The driver handle to be placed into reset.
 */
AIRSHIP_EXPORT
void airship_driver_enter_reset(airship_driver_t driver);

/**
 * @brief Releases a driver from reset, resuming device interaction from a
 * reinitialized state.
 *
 * The driver must first be activated with `::airship_driver_activate`.
 *
 * @param driver The driver handle to be released from reset.
 */
AIRSHIP_EXPORT
void airship_driver_exit_reset(airship_driver_t driver);

/**
 * @brief Sets a driver's device transport.
 *
 * The provided transport is used by the driver to access device registers and
 * set up shared memory buffers.
 *
 * @param driver The driver handle to be modified.
 * @param transport The transport mechanism to be used for device interaction.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the current state of the driver does not
 * permit changing to the new transport instance.
 */
AIRSHIP_EXPORT
airship_result_t airship_driver_set_transport(airship_driver_t driver, airship_device_transport_t transport);

/**
 * @brief Clears a driver's device transport, preventing further device
 * interaction.
 *
 * @param driver The driver handle to be modified.
 */
AIRSHIP_EXPORT
void airship_driver_clear_transport(airship_driver_t driver);

/**
 * @brief Retrieves a driver's current execution stage.
 *
 * This function only retrieves the most recent execution stage observed by the
 * driver; it does not cause the driver to access the device to check for an
 * update.
 *
 * This function may be invoked prior to driver activation and reentrantly from
 * from driver event handlers.
 *
 * @param driver The driver handle to be accessed.
 * @returns The driver's current execution stage.
 */
AIRSHIP_EXPORT
uint32_t airship_driver_get_exec_stage(airship_driver_t driver);

/**
 * @brief Causes a driver to check its device for an execution stage update.
 *
 * The driver must first be activated with `::airship_driver_activate`.
 *
 * @param driver The driver handle which should check for an execution stage
 * update.
 */
AIRSHIP_EXPORT
void airship_driver_probe_exec_stage(airship_driver_t driver);

/// Power targets for use with `::airship_driver_set_power_target`
typedef enum airship_driver_power_target
{
    /**
     * @brief Target *Active*, allowing *Device Sleep*.
     *
     * The driver will attempt to enter `::AIRSHIP_DRIVER_POWER_STATE_ACTIVE`,
     * but will permit transitions into
     * `::AIRSHIP_DRIVER_POWER_STATE_DEVICE_SLEEP` if requested by the device.
     */
    AIRSHIP_DRIVER_POWER_TARGET_ACTIVE,
    /**
     * @brief Target *Active*, disallowing *Device Sleep*.
     *
     * The driver will attempt to enter `::AIRSHIP_DRIVER_POWER_STATE_ACTIVE`,
     * and will not acknowledge any request by the device to enter
     * `::AIRSHIP_DRIVER_POWER_STATE_DEVICE_SLEEP`.
     */
    AIRSHIP_DRIVER_POWER_TARGET_ACTIVE_PREVENTING_DEVICE_SLEEP,
    /**
     * @brief Target *Host Sleep*.
     *
     * The driver will attempt to enter
     * `::AIRSHIP_DRIVER_POWER_STATE_HOST_SLEEP`.
     */
    AIRSHIP_DRIVER_POWER_TARGET_HOST_SLEEP,
} airship_driver_power_target_t;

/**
 * @brief Sets a driver's desired power state.
 *
 * IPC power state transitions usually involve device handshakes; they cannot
 * generally be unilaterally imposed by a driver. A driver will
 * opportunistically take any action necessary to enter its target power state,
 * and will not exit it once it is achieved.
 *
 * The initial power target is `::AIRSHIP_DRIVER_POWER_TARGET_ACTIVE`.
 *
 * @param driver The driver handle to be modified.
 * @param target The power target to apply.
 */
AIRSHIP_EXPORT
void airship_driver_set_power_target(airship_driver_t driver, airship_driver_power_target_t target);

/// Power states returned by `::airship_driver_get_power_state`
typedef enum airship_driver_power_state
{
    /// IPC is ready---neither host nor device may enter a low power state.
    AIRSHIP_DRIVER_POWER_STATE_ACTIVE,
    /// The device may enter a low power state.
    AIRSHIP_DRIVER_POWER_STATE_DEVICE_SLEEP,
    /// The host may enter a low power state.
    AIRSHIP_DRIVER_POWER_STATE_HOST_SLEEP,
    /**
     * @brief Awaiting device acknowledgement of *Host Sleep* entry.
     *
     * This state indicates that the host has infomed the device of its intent
     * to enter `::AIRSHIP_DRIVER_POWER_STATE_HOST_SLEEP` but that the device
     * has not yet responded.
     */
    AIRSHIP_DRIVER_POWER_STATE_HOST_SLEEP_WAIT,
    /**
     * @brief Awaiting device acknowledgement of *Host Sleep* exit.
     *
     * This state indicates that the host has infomed the device of its intent
     * to exit `::AIRSHIP_DRIVER_POWER_STATE_HOST_SLEEP` but that the device
     * has not yet responded.
     */
    AIRSHIP_DRIVER_POWER_STATE_HOST_WAKE_WAIT,
} airship_driver_power_state_t;

/**
 * @brief Retrieves a driver's current IPC power state.
 *
 * This function may be invoked prior to driver activation and reentrantly from
 * from driver event handlers.
 *
 * @param driver The driver handle to be accessed.
 * @returns The driver's current IPC power state.
 */
AIRSHIP_EXPORT
airship_driver_power_state_t airship_driver_get_power_state(airship_driver_t driver);

/**
 * @brief Retrieves a driver's error status.
 *
 * This function may be invoked prior to driver activation and reentrantly from
 * from driver event handlers.
 *
 * The driver error status is cleared on `::airship_driver_enter_reset`.
 *
 * @param driver The driver handle to be accessed.
 * @returns A bitmask of implementation-specific status flags, or zero if no
 * error has occurred.
 */
AIRSHIP_EXPORT
uint32_t airship_driver_get_error_state(airship_driver_t driver);

#ifdef __cplusplus
namespace airship {
/// C++ wrapper for automatic lifecycle management of driver handles.
using driver = wrapper<airship_driver, airship_driver_destroy>;
} // namespace airship
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__driver_h */
