//
//  device_transport.h
//  Airship
//
//  Created by Jason McElrath on 9/18/20.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__device_transport_h
#define airship__core__api__device_transport_h

/**
 * @file device_transport.h
 * @brief Public device transport interface.
 */

#include <Airship/base.h>

#include <IOKit/pci/IOPCIDevice.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/// Airship device transport handle type.
typedef struct airship_device_transport *airship_device_transport_t;

/**
 * @brief Creates a device transport handle backed by an IOPCIDevice.
 *
 * The returned handle must be released with
 * `::airship_device_transport_destroy`.
 *
 * @param device The backing IOPCIDevice for the transport.
 * @returns The newly created device transport handle, or `NULL` if an error
 * occurs.
 */
AIRSHIP_EXPORT
airship_device_transport_t AIRSHIP_NULLABLE airship_device_transport_create_with_iopcidevice(IOPCIDevice *device);

/**
 * @brief Destroys a device transport handle, releasing any associated resources.
 * @param transport The device transport handle to be destroyed.
 */
AIRSHIP_EXPORT
void airship_device_transport_destroy(airship_device_transport_t transport);

/**
 * @brief Suspends a device transport handle, blocking all device access.
 *
 * Device transport handles are initialized in a non-suspended state.
 *
 * @param transport The device transport handle to be suspended.
 */
AIRSHIP_EXPORT
void airship_device_transport_suspend(airship_device_transport_t transport);

/**
 * @brief Resumes a device transport handle, restoring device access.
 * @param transport The device transport handle to be suspended.
 */
AIRSHIP_EXPORT
void airship_device_transport_resume(airship_device_transport_t transport);

#ifdef __cplusplus
namespace airship {
/// C++ wrapper for automatic lifecycle management of device transport handles.
using device_transport = wrapper<airship_device_transport, airship_device_transport_destroy>;
} // namespace airship
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__device_transport_h */
