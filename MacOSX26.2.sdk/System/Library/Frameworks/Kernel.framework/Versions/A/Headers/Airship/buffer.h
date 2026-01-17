//
//  buffer.h
//  Airship
//
//  Created by Jason McElrath on 9/18/20.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__buffer_h
#define airship__core__api__buffer_h

/**
 * @file buffer.h
 * @brief Public buffer interface.
 */

#include <Airship/base.h>
#include <Airship/client.h>
#include <Airship/monitor.h>

#include <IOKit/IOMemoryDescriptor.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/// Airship buffer handle type.
typedef struct airship_buffer *airship_buffer_t;

/// Buffer directionality options.
typedef enum airship_buffer_direction
{
    /// Device will write to the buffer but not read from it.
    AIRSHIP_BUFFER_DIR_IN,
    /// Device will read from the buffer but not write to it.
    AIRSHIP_BUFFER_DIR_OUT,
    /// Device will both read from and write to the buffer.
    AIRSHIP_BUFFER_DIR_INOUT,
} airship_buffer_direction_t;

/**
 * @brief Creates a device-accessible buffer.
 *
 * The created buffer is zero-filled before it is returned to the caller or made
 * accessible to the device.
 *
 * @warning Buffer contents may be read by the device at any time. Never copy
 * sensitive information like kernel VM pointers into an `airship_buffer_t`.
 *
 * @warning Buffer contents may be modified by the device at any time. The
 * content of an `airship_buffer_t` may be malicious or may become malicious
 * after validation.
 *
 * @warning Buffer directionality is advisory and may not be enforceable. Assume
 * that the device can both read and modify buffer contents, regardless of the
 * value of `dir`.
 *
 * The returned handle must be released with `::airship_buffer_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param size The size of the buffer to create.
 * @param dir Directionality of the created buffer.
 * @returns The newly created buffer handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_buffer_t AIRSHIP_NULLABLE airship_buffer_create(airship_client_t client, uint32_t size, airship_buffer_direction_t dir);

/**
 * @brief Creates a buffer backed by the provided memory descriptor.
 *
 * Airship does not modify the contents of the memory descriptor before making
 * it accessible to the device.
 *
 * @warning All warnings for `::airship_buffer_create` also apply to this
 * function.
 *
 * The returned handle must be released with `::airship_buffer_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param iomd The backing memory descriptor for the buffer.
 * @param dir Directionality of the created buffer.
 * @returns The newly created buffer handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_buffer_t AIRSHIP_NULLABLE airship_buffer_create_with_iomd(airship_client_t client, IOMemoryDescriptor *iomd, airship_buffer_direction_t dir);

/**
 * @brief Destroys a buffer, releasing any associated resources.
 * @param buffer The buffer handle to be destroyed.
 */
AIRSHIP_EXPORT
void airship_buffer_destroy(airship_buffer_t buffer);

/**
 * @brief Retrieves the size of a buffer.
 * @param buffer The buffer to be accessed.
 * @returns The size of the buffer in bytes.
 */
AIRSHIP_EXPORT
uint32_t airship_buffer_get_size(airship_buffer_t buffer);

/**
 * @brief Retrieves a pointer to a buffer's data.
 * @param buffer The buffer to be accessed.
 * @returns A pointer to the buffer's data, or `NULL` if the buffer is not
 * directly accessible.
 */
AIRSHIP_EXPORT
void *AIRSHIP_NULLABLE airship_buffer_get_addr(airship_buffer_t buffer);

/**
 * @brief Copies data out of a buffer.
 * @param buffer The buffer to be accessed.
 * @param dst Destination for data read from the buffer.
 * @param offset The offset within the buffer at which to begin reading.
 * @param length The amount of data to read from the buffer.
 * @retval ::AIRSHIP_OK if the buffer was successfully accessed.
 * @retval ::AIRSHIP_ECANTMAP if the buffer is not mapped in the local address
 * space.
 */
AIRSHIP_EXPORT
airship_result_t airship_buffer_read(airship_buffer_t buffer, AIRSHIP_NOESCAPE void *dst, uint32_t offset, uint32_t length);

/**
 * @brief Copies data into a buffer.
 * @param buffer The buffer to be accessed.
 * @param src Source of data to write to the buffer.
 * @param offset The offset within the buffer at which to begin writing.
 * @param length The amount of data to be written into the buffer.
 * @retval ::AIRSHIP_OK if the buffer was successfully accessed.
 * @retval ::AIRSHIP_ECANTMAP if the buffer is not mapped in the local address
 * space. 
 */
AIRSHIP_EXPORT
airship_result_t airship_buffer_write(airship_buffer_t buffer, AIRSHIP_NOESCAPE const void *src, uint32_t offset, uint32_t length);

/**
 * @brief Attempts to refresh a buffer's device mapping.
 *
 * Buffers are automatically mapped to the device when created, but in some
 * scenarios the mapping can expire, causing the device to lose access to the
 * underlying memory. When that occurs, `::airship_buffer_map` can be used to
 * restore the mapping.
 *
 * See protocol-specific documentation for more information about scenarios that
 * may cause mappings to expire.
 *
 * @param buffer The buffer to be mapped.
 * @retval ::AIRSHIP_OK if the buffer mapping was successfully restored.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the device is not ready to map buffers.
 * @retval ::AIRSHIP_ECANTMAP if the map operation otherwise fails.
 */
AIRSHIP_EXPORT
airship_result_t airship_buffer_map(airship_buffer_t buffer);

#ifdef __cplusplus
namespace airship {
/// C++ wrapper for automatic lifecycle management of buffers.
using buffer = wrapper<airship_buffer, airship_buffer_destroy>;
} // namespace airship
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__buffer_h */
