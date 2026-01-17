//
//  client.h
//  Airship
//
//  Created by Jason McElrath on 9/18/20.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__client_h
#define airship__core__api__client_h

/**
 * @file client.h
 * @brief Public client interface.
 */

#include <Airship/base.h>
#include <Airship/driver.h>
#include <Airship/monitor.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/// Airship client handle type.
typedef struct airship_client *airship_client_t;

/**
 * @brief Creates a client handle with a direct connection to a driver.
 *
 * The returned handle must be released with `::airship_client_destroy`.
 *
 * The driver must first be activated with `::airship_driver_activate`.
 *
 * @param driver The driver to which to connect.
 * @param name A string used to identify the client.
 * @returns The newly created client handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_client_t AIRSHIP_NULLABLE airship_client_create_direct(airship_driver_t driver, airship_string_t name);

/**
 * @brief Destroys a client handle, releasing any associated resources.
 *
 * Destroying a client handle implicitly releases any resources that were
 * previously acquired with `::airship_client_acquire_resource`.
 *
 * @pre All subordinate object handles created with the client handle are
 * destroyed.
 *
 * @param client The client handle to be destroyed.
 */
AIRSHIP_EXPORT
void airship_client_destroy(airship_client_t client);

/**
 * @brief Acquires access to a resource within the connected driver.
 *
 * Airship uses a resource mechanism to arbitrate client access to driver
 * resources.
 *
 * Most resources have only a single selector with value zero, but some may have
 * multiple selectors.
 *
 * Most resources enforce exclusive access per selector, but some may allow
 * multiple clients to acquire concurrent access to the same selector.
 *
 * Some resources may be gated by additional permission mechanisms, e.g.
 * process entitlements.
 *
 * @param client The client to be granted ownership of the resource.
 * @param resource_name The name of the resource.
 * @param selector The selector within the resource to acquire.
 * @retval ::AIRSHIP_OK if the resource was successfully acquired.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_EEXCLUSIVEACCESS if the resource is already exclusively
 * owned by another client.
 * @retval ::AIRSHIP_ENOTPRIVILEGED if the client is not permitted to acquire
 * the resource.
 * @retval ::AIRSHIP_EBADARGUMENT if the specified resource does not exist.
 */
AIRSHIP_EXPORT
airship_result_t airship_client_acquire_resource(airship_client_t client, airship_string_t resource_name, uint32_t selector);

/**
 * @brief Releases access to a resource within the connected driver.
 * @param client The client to release ownership of the resource.
 * @param resource_name The name of the resource.
 * @param selector The selector within the resource to release.
 */
AIRSHIP_EXPORT
void airship_client_release_resource(airship_client_t client, airship_string_t resource_name, uint32_t selector);

/**
 * @brief Resource states for use with monitors created by
 * `::airship_client_create_resource_monitor`.
 */
typedef enum airship_resource_state
{
    /// Resource is not held by any client.
    AIRSHIP_RESOURCE_FREE,
    /// Resource is held by some client.
    AIRSHIP_RESOURCE_BUSY,
} airship_resource_state_t;

/**
 * @brief Creates a monitor tracking whether a resource is available.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param client The client for which to evaluate resource availability.
 * @param resource_name The name of the resource to monitor.
 * @param selector The selector within the resource to monitor.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_client_create_resource_monitor(airship_client_t client, airship_string_t resource_name, uint32_t selector);

/**
 * @brief Create a monitor tracking the current exec stage send by the device. 
 * 
 * The returned handle must be released with `::airship_monitor_destroy`. 
 * 
 * @param client The client through which the exec stage monitor will be created.
 * @returns The newly created monitor handle, or `NULL` if an error occurs. 
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_client_create_exec_stage_monitor(airship_client_t client);

/**
 * @brief Retrieve the current execution stage value for a client's driver. 
 * 
 * This function only retrieves the most recent execution stage observed by the
 * driver; it does not cause the driver to access the device to check for an
 * update.
 * 
 * @param client The client used to access the exec stage value. 
 * @returns The current exec stage value. 
 */
AIRSHIP_EXPORT
uint32_t airship_client_get_exec_stage(airship_client_t client);

#ifdef __cplusplus
namespace airship {
/// C++ wrapper for automatic lifecycle management of clients.
using client = wrapper<airship_client, airship_client_destroy>;
} // namespace airship
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__client_h */
