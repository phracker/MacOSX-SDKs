//
//  `cipc.h
//  Airship
//
//  Created by Jason McElrath on 1/17/23.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__acipc_h
#define airship__core__api__acipc_h

/**
 * @file acipc.h
 * @brief Public ACIPC interface.
 * @namespace airship::acipc
 * @brief Public ACIPC interface.
 */

#include <Airship/base.h>
#include <Airship/buffer.h>
#include <Airship/client.h>
#include <Airship/interrupt.h>
#include <Airship/monitor.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

/// Size in bytes of transfer descriptors.
#define AIRSHIP_ACIPC_TD_SIZE 16
/// Size in bytes of completion descriptors.
#define AIRSHIP_ACIPC_CD_SIZE 16

/**
 * @Brief Detailed status flags returned by `::airship_driver_get_error_state`
 * for ACIPC.
 */
typedef enum airship_acipc_ipc_error_flag
{
    /// The device signalled an IPC error.
    AIRSHIP_ACIPC_IPC_ERROR_DEVICE_SIGNALLED = (1 << 0),
    /// The device transport was unexpectedly revoked.
    AIRSHIP_ACIPC_IPC_ERROR_UNEXPECTED_TRANSPORT_REVOCATION = (1 << 1),
    /// Some external failure or resource shortage occurred.
    AIRSHIP_ACIPC_IPC_ERROR_SYSTEM_FAILURE = (1 << 2),
    /// An unexpected *IPC Status* value was received.
    AIRSHIP_ACIPC_IPC_ERROR_UNEXPECTED_IPC_STATUS = (1 << 3),
    /// An unexpected *Sleep Status* value was received.
    AIRSHIP_ACIPC_IPC_ERROR_UNEXPECTED_SLEEP_STATUS = (1 << 4),
    /// Timed out waiting to reach *IPC Status* of *Running*.
    AIRSHIP_ACIPC_IPC_ERROR_RUNNING_TIMEOUT = (1 << 5),
    /// Received invalid transfer ring tail index update.
    AIRSHIP_ACIPC_IPC_ERROR_BAD_TR_TI_UPDATE = (1 << 6),
    /// Received invalid in-place completion.
    AIRSHIP_ACIPC_IPC_ERROR_BAD_INPLACE_COMPLETION = (1 << 7),
    /// Received invalid completion ring head index update.
    AIRSHIP_ACIPC_IPC_ERROR_BAD_CR_HI_UPDATE = (1 << 8),
    /// Received invalid completion descriptor.
    AIRSHIP_ACIPC_IPC_ERROR_BAD_CD = (1 << 9),
} airship_acipc_ipc_error_flag_t;

/**
 * @brief Retrieve a textual description for an ACIPC error code.
 *
 * The contents of the strings returned by this function are subject to change
 * without notice.
 *
 * @param error An ACIPC error code.
 * @returns A string representing the error.
 */
AIRSHIP_EXPORT
const char *airship_acipc_get_ipc_error_description(uint32_t error);

/**
 * @brief Provides runtime insights into the health of the airship driver.
 */
typedef enum airship_acipc_health_status_flag
{
    /// Indicates if the doorbell coordinator is in a healthy state.
    AIRSHIP_ACIPC_HEALTH_STATUS_ERROR_DOORBELL_COORDINATOR = (1 << 0),
} airship_acipc_health_status_flag_t;

/**
 * @brief Populates a `airship_acipc_health_status_t` instance with driver health checks.
 *
 * @param client A client handle connected to the driver.
 * @param detail The `airship_acipc_health_status_flag_t` state.
 * @retval ::AIRSHIP_OK If all checks are in a health state.
 * @retval ::AIRSHIP_ERROR If any of the checks in `airship_acipc_health_status_flag_t` are true.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_get_health_status(airship_client_t client, AIRSHIP_NOESCAPE uint32_t *detail);

/// ACIPC boot handle type.
typedef struct airship_acipc_boot *airship_acipc_boot_t;

/**
 * @brief Creates a handle to interact with a boot context.
 *
 * The returned handle must be released with `::airship_acipc_boot_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param name The name of the boot context to access, usually "boot".
 * @returns The newly created boot handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_acipc_boot_t AIRSHIP_NULLABLE airship_acipc_boot_create(airship_client_t client, airship_string_t name);

/**
 * @brief Destroys a boot context, releasing any associated resources.
 * @param boot The boot context to be destroyed.
 */
AIRSHIP_EXPORT
void airship_acipc_boot_destroy(airship_acipc_boot_t boot);

/**
 * @brief Boot context states returned by `::airship_acipc_boot_get_state`.
 *
 * ```
 *  -·-·- Autonomous transition
 *  ----- Directed transition
 *
 *  +-------------+
 *  | UNAVAILABLE |<------+
 *  +-------------+       |
 *    ¦ ^                 |
 *    v ¦                 | reset()
 *  +-------+           +--------------+
 *  | READY |           | DEAD_SETTLED |
 *  +-------+           +--------------+
 *    | send_image()      ^
 *    v                   ¦
 *  +------------+      +----------------+
 *  | IMAGE_SENT |-·-·->| DEAD_UNSETTLED |
 *  +------------+      +----------------+
 *    ¦                   ^
 *    v                   ¦
 *  +------------+        ¦
 *  | IMAGE_DONE |-·-·-·-·+
 *  +------------+
 * ```
 */
typedef enum airship_acipc_boot_state
{
    /**
     * @brief The boot context is not available for use.
     *
     * See `::airship_acipc_boot_state_detail_flag_t` for reasons a boot context
     * may be unavailable.
     *
     * Allowed transitions:
     *  - `::AIRSHIP_ACIPC_BOOT_STATE_READY` if the boot context becomes ready
     * for use.
     */
    AIRSHIP_ACIPC_BOOT_STATE_UNAVAILABLE,
    /**
     * @brief The boot context is ready to send an image.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_SENT` with
     * `::airship_acipc_boot_send_image`.
     * - `::AIRSHIP_ACIPC_BOOT_STATE_UNAVAILABLE` if the boot context becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_BOOT_STATE_READY,
    /**
     * @brief The boot context is awaiting the device's response to an image.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_DONE` if the device sends an image
     * response.
     * - `::AIRSHIP_ACIPC_BOOT_STATE_DEAD_UNSETTLED` if the boot context becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_BOOT_STATE_IMAGE_SENT,
    /**
     * @brief The device has responded to an image.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_BOOT_STATE_DEAD_UNSETTLED` if the boot context becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_BOOT_STATE_IMAGE_DONE,
    /**
     * @brief The boot context is unusable, but it is not yet safe to reset its
     * state.
     *
     * Even when otherwise unusable, it is not safe to reset a boot context's
     * state while a pending image buffer could still be accessed by the device.
     *
     * See `::airship_acipc_boot_state_detail_flag_t` for reasons a boot context
     * may become "dead".
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED` when it becomes safe to reset
     * the ring state.
     */
    AIRSHIP_ACIPC_BOOT_STATE_DEAD_UNSETTLED,
    /**
     * @brief The boot context is unusable, and its state can be safely reset.
     *
     * See `::airship_acipc_boot_state_detail_flag_t` for reasons a boot context
     * may become "dead".
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_BOOT_STATE_UNAVAILABLE` with
     * `::airship_acipc_boot_reset`.
     * - `::AIRSHIP_ACIPC_BOOT_STATE_READY` with `::airship_acipc_boot_reset`.
     */
    AIRSHIP_ACIPC_BOOT_STATE_DEAD_SETTLED,
    /**
     * @brief Value returned by `::airship_acipc_boot_get_state` if the
     * connection to the driver is broken.
     */
    AIRSHIP_ACIPC_BOOT_STATE_EDISCONNECTED,
} airship_acipc_boot_state_t;

/// Detailed status flags returned by `::airship_acipc_boot_get_state`
typedef enum airship_acipc_boot_state_detail_flag
{
    /// The device is not in the appropriate execution stage.
    AIRSHIP_ACIPC_BOOT_STATE_UNAVAILABLE_EXECSTAGE = (1 << 0),
    /// The boot context became unusable because the driver entered reset.
    AIRSHIP_ACIPC_BOOT_STATE_DEAD_DEVICERESET = (1 << 1),
    /// The boot context became unusable because the device execution stage changed.
    AIRSHIP_ACIPC_BOOT_STATE_DEAD_EXECSTAGE = (1 << 2),
} airship_acipc_boot_state_detail_flag_t;

/**
 * @brief Retrieves a boot context's current state.
 * @param boot The boot context to be accessed.
 * @param out_detail Optional output parameter used to return detailed status
 * information. The returned value will be a bitmask of values from
 * `::airship_acipc_boot_state_detail_flag_t`.
 * @returns The boot context's current state.
 */
AIRSHIP_EXPORT
airship_acipc_boot_state_t airship_acipc_boot_get_state(airship_acipc_boot_t boot, AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_detail);

/**
 * @brief Creates a monitor associated with a boot context's state.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param boot The boot context to be tracked.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_boot_create_state_monitor(airship_acipc_boot_t boot);

/**
 * @brief Reads from a boot register.
 * @param boot The boot context to be accessed.
 * @param register_name The name of the register to be accessed.
 * @param register_offset The offset within the register at which to begin
 * reading.
 * @param register_length The amount of data to be read from the register.
 * @param dst Output buffer to be filled with the data read from the register.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the boot context state is not one of
 * `::AIRSHIP_ACIPC_BOOT_STATE_READY`, `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_SENT`,
 * or `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_DONE`.
 * @retval ::AIRSHIP_EBADARGUMENT if the register name does not correspond to a
 * known register, or if the offset and length are beyond the register's bounds.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_boot_read_register(airship_acipc_boot_t boot, airship_string_t register_name, uint32_t register_offset, uint32_t register_length,
                                                  AIRSHIP_NOESCAPE void *dst);

/**
 * @brief Writes to a boot register.
 * @param boot The boot context to be accessed.
 * @param register_name The name of the register to be accessed.
 * @param register_offset The offset within the register at which to begin
 * writing.
 * @param register_length The amount of data to be written to the register.
 * @param src The data to be written to the register.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the boot context state is not one of
 * `::AIRSHIP_ACIPC_BOOT_STATE_READY`, `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_SENT`,
 * or `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_DONE`.
 * @retval ::AIRSHIP_EBADARGUMENT if the register name does not correspond to a
 * known register, or if the offset and length are beyond the register's bounds.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_boot_write_register(airship_acipc_boot_t boot, airship_string_t register_name, uint32_t register_offset,
                                                   uint32_t register_length, AIRSHIP_NOESCAPE const void *src);

/**
 * @brief Sends a boot image.
 *
 * The content of `image` is not copied. The caller must guarantee that the
 * content of the relevant range is valid until an image response is received.
 * The driver will ensure that the backing memory for `image` remains accessible
 * to the device until the image transaction is complete, even if `boot` is
 * destroyed.
 *
 * This function only updates *Image Address*, *Image Size*, and
 * *Image Doorbell*; it does not wait for the device's response. The response
 * can be retrieved with `::airship_acipc_boot_get_image_response` after the
 * boot context state changes to `::AIRSHIP_ACIPC_BOOT_STATE_IMAGE_DONE`.
 *
 * @param boot The boot context to be accessed.
 * @param image The image data to be sent.
 * @param image_offset The offset of the image payload within the image buffer.
 * @param image_length The length of the image payload within the image buffer.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the boot context state is not
 * `::AIRSHIP_ACIPC_BOOT_STATE_READY`.
 * @retval ::AIRSHIP_ECANTMAP if the image buffer mapping is expired.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_boot_send_image(airship_acipc_boot_t boot, airship_buffer_t image, uint32_t image_offset, uint32_t image_length);

/// Image responses returned by `::airship_acipc_boot_get_image_response`.
typedef enum airship_acipc_boot_image_response
{
    /// No image response has been received.
    AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_NONE,
    /// A successful image response was received.
    AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_SUCCESS,
    /// An unsuccessful image response was received.
    AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_FAILURE,
    /// An unrecognized image response was received.
    AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_UNKNOWN,
    /**
     * @brief Value returned by `::airship_acipc_boot_get_image_response` if the
     * connection to the driver is broken.
     */
    AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_EDISCONNECT,
} airship_acipc_boot_image_response_t;

/**
 * @brief Retrieves the response to a boot image.
 * @param boot The boot context to be accessed.
 * @param out_code Optional output parameter used to return the status code
 * received from the device. Valid only if the return value is one of:
 * - `::AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_SUCCESS`
 * - `::AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_FAILURE`
 * - `::AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_UNKNOWN`.
 * @returns The boot image response.
 */
AIRSHIP_EXPORT
airship_acipc_boot_image_response_t airship_acipc_boot_get_image_response(airship_acipc_boot_t boot, AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_code);

/**
 * @brief Causes a boot context to check for an image response.
 *
 * Generally a driver will detect an image response autonomously when the device
 * issues an interrupt, but this function can be used to probe the response
 * manually.
 *
 * @param boot The boot context that should check for an image response.
 */
AIRSHIP_EXPORT
void airship_acipc_boot_probe_image_response(airship_acipc_boot_t boot);

/**
 * @brief Resets an inactive boot context.
 *
 * On reset:
 * - The boot context state is changed to `::AIRSHIP_ACIPC_BOOT_STATE_READY` or
 * `::AIRSHIP_ACIPC_BOOT_STATE_UNAVAILABLE`.
 * - The image response is reset to `::AIRSHIP_ACIPC_BOOT_IMAGE_RESPONSE_NONE`.
 *
 * @param boot The boot context to be reset.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the boot context state is not
 * `::AIRSHIP_ACIPC_BOOT_STATE_DEAD_UNSETTLED`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_boot_reset(airship_acipc_boot_t boot);

/**
 * @brief Ring states returned by `::airship_acipc_tr_get_state` and
 * `::airship_acipc_cr_get_state`.
 *
 * ```
 *  -·-·- Autonomous transition
 *  ----- Directed transition
 *
 *     +-------------+
 *     | UNAVAILABLE |<------+
 *     +-------------+       |
 *       ¦ ^                 |
 *       v ¦                 | reset()
 *     +-----------+       +--------------+
 *  +·-| AVAILABLE |       | DEAD_SETTLED |
 *  ¦  +-----------+       +--------------+
 *  ¦    | open()            ^
 *  ¦    v                   ¦
 *  ¦  +---------+         +----------------+
 *  ¦  | OPENING |-·-·-·-·>| DEAD_UNSETTLED |
 *  ¦  +---------+         +----------------+
 *  ¦    ¦ | close()         ^ ^ ^
 *  ¦    ¦ +-------+         ¦ ¦ ¦
 *  ¦    v         |         ¦ ¦ ¦
 *  ¦  +------+    |         ¦ ¦ ¦
 *  +·>| OPEN |-·-·+·-·-·-·-·+ ¦ ¦
 *     +------+    |           ¦ ¦
 *       | close() |           ¦ ¦
 *       v         v           ¦ ¦
 *     +-------------+         ¦ ¦
 *     | CLOSING     |-·-·-·-·-+ ¦
 *     +-------------+           ¦
 *       ¦ ^                     ¦
 *       v | close()             ¦
 *     +--------+                ¦
 *     | LIMBO  |-·-·-·-·-·-·-·-·+
 *     +--------+
 * ```
 */
typedef enum airship_acipc_ring_state
{
    /**
     * @brief The ring is closed and not available to be opened.
     *
     * See `::airship_acipc_ring_state_detail_flag_t` for reasons a ring may be
     * unavailable.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_AVAILABLE` if the ring becomes available.
     */
    AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE,
    /**
     * @brief The ring is closed and available to be opened.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_OPENING` with `::airship_acipc_tr_open` or
     * `::airship_acipc_cr_open`.
     * - `::AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE` if the ring becomes
     * unavailable.
     * - `::AIRSHIP_ACIPC_RING_STATE_OPEN` if the ring is configured to open
     * automatically (very uncommon).
     */
    AIRSHIP_ACIPC_RING_STATE_AVAILABLE,
    /**
     * @brief The ring is awaiting the device's response to an open message.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_OPEN` if the device acknowledges the open
     * message.
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED` if the ring becomes
     * unavailable or the device rejects the open message.
     * - `::AIRSHIP_ACIPC_RING_STATE_CLOSING` with `::airship_acipc_tr_close` or
     * `::airship_acipc_cr_close`.
     */
    AIRSHIP_ACIPC_RING_STATE_OPENING,
    /**
     * @brief The ring is open and ready for use.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_CLOSING` with `::airship_acipc_tr_close` or
     * `::airship_acipc_cr_close`.
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED` if the ring becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_RING_STATE_OPEN,
    /**
     * @brief The ring is awaiting the device's response to a close message.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED` if the ring becomes
     * unavailable or the device acknowledges the close message.
     * - `::AIRSHIP_ACIPC_RING_STATE_LIMBO` if the device rejects the close
     * message.
     */
    AIRSHIP_ACIPC_RING_STATE_CLOSING,
    /**
     * @brief The device has rejected a close message for the ring. The ring is
     * not usable.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_CLOSING` with `::airship_acipc_tr_close` or
     * `::airship_acipc_cr_close`.
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED` if the ring becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_RING_STATE_LIMBO,
    /**
     * @brief The ring is closed, but it is not yet safe to reset its state.
     *
     * Even when closed, it is not safe to reset a ring's state while it could
     * still be affected by activity in other contexts. For example, it is not
     * safe to reset a transfer ring until either all its transfers have
     * completed or all its associated completion rings are closed and empty.
     *
     * See `::airship_acipc_ring_state_detail_flag_t` for reasons a ring may
     * become "dead".
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED` when it becomes safe to reset
     * the ring state.
     */
    AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED,
    /**
     * @brief The ring is closed, and its state can be safely reset.
     *
     * See `::airship_acipc_ring_state_detail_flag_t` for reasons a ring may
     * become "dead".
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_AVAILABLE` with `::airship_acipc_tr_reset`
     * or `::airship_acipc_cr_reset`.
     * - `::AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE` with `::airship_acipc_tr_reset`
     * or `::airship_acipc_cr_reset`.
     */
    AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED,
    /**
     * @brief Value returned by `::airship_acipc_tr_get_state` and
     * `::airship_acipc_cr_get_state` if the connection to the driver is broken.
     */
    AIRSHIP_ACIPC_RING_STATE_EDISCONNECTED,
} airship_acipc_ring_state_t;

/**
 * @brief Detailed status flags returned by `::airship_acipc_tr_get_state` and
 * `::airship_acipc_cr_get_state`.
 */
typedef enum airship_acipc_ring_state_detail_flag
{
    /// The device is not in the appropriate execution stage.
    AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE_EXECSTAGE = (1 << 0),
    /// The ring parameters conflict with a ring that is already open.
    AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE_CONFLICT = (1 << 1),
    /// The ring dependencies not available.
    AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE_DEPENDENCY = (1 << 2),
    /// The device rejected the open message.
    AIRSHIP_ACIPC_RING_STATE_DEAD_OPENREJECT = (1 << 3),
    /**
     * @brief The ring was explicitly closed by `::airship_acipc_tr_close` or
     * `::airship_acipc_cr_close`.
     */
    AIRSHIP_ACIPC_RING_STATE_DEAD_BYREQUEST = (1 << 4),
    /// The ring was closed because the driver entered reset.
    AIRSHIP_ACIPC_RING_STATE_DEAD_DEVICERESET = (1 << 5),
    /// The ring was closed because the device execution stage changed.
    AIRSHIP_ACIPC_RING_STATE_DEAD_EXECSTAGE = (1 << 6),
} airship_acipc_ring_state_detail_flag_t;

/// ACIPC transfer ring handle type.
typedef struct airship_acipc_tr *airship_acipc_tr_t;

/**
 * @brief Creates a handle to interact with a transfer ring.
 *
 * The returned handle must be released with `::airship_acipc_tr_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param name The name of the transfer ring to be accessed.
 * @param selector Numerical selector of the transfer ring to be accessed.
 * @returns The newly created transfer ring handle, or `NULL` if an error
 * occurs.
 */
AIRSHIP_EXPORT
airship_acipc_tr_t AIRSHIP_NULLABLE airship_acipc_tr_create(airship_client_t client, airship_string_t name, uint32_t selector);

/**
 * @brief Destroys a transfer ring, releasing any associated resources.
 *
 * Destroying a transfer ring handle automatically closes the ring if it is
 * open.
 *
 * @param tr The transfer ring to be destroyed.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_destroy(airship_acipc_tr_t tr);

/**
 * @brief Returns the logical size of a transfer ring.
 *
 * By default the logical size of a transfer ring is the same as the size of the
 * underlying *Transfer Ring* data structure, but it may be changed with
 * `::airship_acipc_tr_set_size`.
 *
 * @param tr The transfer ring to be accessed.
 * @returns The logical size (element count) of the transfer ring.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_size(airship_acipc_tr_t tr);

/**
 * @brief Configures the logical size of a transfer ring.
 *
 * By default the logical size of a transfer ring is the same as the size of the
 * underlying *Transfer Ring* data structure, but this function can be used to
 * configure a different size.
 *
 * Configuring a logical size smaller than that of the underlying *Transfer
 * Ring* data structure reduces the ring capacity but may be useful to reduce
 * driver memory consumption, or---for out-of-order rings---to restrict the
 * range of permissible transfer tag values.
 *
 * Configuring a logical size larger than that of the underlying *Transfer
 * Ring* data structure does not generally increase the ring capacity but may be
 * useful for out-of-order rings to extend the range of permissible transfer tag
 * values.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param count The new logical size (elemnt count) of the transfer ring.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_size(airship_acipc_tr_t tr, uint16_t count);

/**
 * @brief Returns the size of a transfer ring's underlying *Transfer Ring* data
 * structure.
 * @param tr The transfer ring to be accessed.
 * @returns The size (element count) of the underlying *Transfer Ring* data
 * structure.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_backing_ring_size(airship_acipc_tr_t tr);

/**
 * @brief Configures the size of a transfer ring's underlying *Transfer Ring*
 * data structure.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param count The new size (elemnt count) of the underlying *Transfer Ring*
 * data structure.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_backing_ring_size(airship_acipc_tr_t tr, uint16_t count);

/**
 * @brief Returns the size of the optional footer for transfers in a transfer
 * ring.
 * @param tr The transfer ring to be accessed.
 * @returns The length in bytes of the optional footer for transfers in the
 * ring.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_tr_get_transfer_footer_size(airship_acipc_tr_t tr);

/**
 * @brief Configures the size of the optional footer for transfers in a transfer
 * ring.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param length The new length in bytes of the optional footer for transfers in
 * the ring.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_transfer_footer_size(airship_acipc_tr_t tr, uint32_t length);

/**
 * @brief Returns the maximum size of optional footers for completions of
 * transfers in a transfer ring.
 *
 * This function returns the amount of space reserved by the driver for storing
 * optional footer content received in a completion context. For the optional
 * footer size of the underlying *Transfer Ring* data structure itself, use
 * `::airship_acipc_tr_get_transfer_footer_size`.
 *
 * @param tr The transfer ring to be accessed.
 * @returns The maximum length in bytes of optional footers for completions of
 * transfers in the ring.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_tr_get_completion_footer_size(airship_acipc_tr_t tr);

/**
 * @brief Configures the maximum size of optional footers for completions of
 * transfers in a transfer ring.
 *
 * This function configures the amount of space reserved by the driver for
 * storing optional footer content received in a completion context. For the
 * optional footer size of the underlying *Transfer Ring* data structure itself,
 * use `::airship_acipc_tr_set_transfer_footer_size`.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param length The new maximum length in bytes of optional footers for
 * completions of transfers in the ring.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_completion_footer_size(airship_acipc_tr_t tr, uint32_t length);

/**
 * @brief Returns the nominal transfer size for a transfer ring.
 *
 * This value is not used by ACIPC. It is provided as a convenience for
 * higher-layer software.
 *
 * @param tr The transfer ring to be accessed.
 * @returns The nominal transfer size in bytes of for the transfer ring.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_tr_get_nominal_transfer_size(airship_acipc_tr_t tr);

/**
 * @brief Returns the completion ring associated with a transfer ring.
 * @param tr The transfer ring to be accessed.
 * @param out_selector Output param used to return the numerical selector of the
 * associated completion ring, or zero if `NULL` is returned.
 * @returns The name of the associated completion ring, or `NULL` on error or if
 * the transfer ring is not associated with any completion ring. The caller is
 * responsible for releasing the returned string.
 */
AIRSHIP_EXPORT
AIRSHIP_RETURNS_RETAINED airship_string_t AIRSHIP_NULLABLE airship_acipc_tr_get_completion_ring(airship_acipc_tr_t tr,
                                                                                                AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_selector);

/**
 * @brief Configures the completion ring associated with a transfer ring.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param name The name of the completion ring to be associated with the
 * transfer ring. Pass `NULL` to not associate the transfer ring with any
 * completion ring.
 * @param selector The numerical selector of the completion ring to be
 * associated with the transfer ring. Pass zero if `name` is `NULL`.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_completion_ring(airship_acipc_tr_t tr, airship_string_t AIRSHIP_NULLABLE name, uint32_t selector);

/**
 * @brief Returns the completion group associated with a transfer ring.
 * @param tr The transfer ring to be accessed.
 * @param out_selector Output param used to return the numerical selector of the
 * associated completion group, or zero if `NULL` is returned.
 * @returns The name of the associated completion group, or `NULL` on error or
 * if the transfer ring is associated with the default completion group. The
 * caller is responsible for releasing the returned string.
 */
AIRSHIP_EXPORT
AIRSHIP_RETURNS_RETAINED airship_string_t AIRSHIP_NULLABLE airship_acipc_tr_get_completion_group(airship_acipc_tr_t tr,
                                                                                                 AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_selector);

/**
 * @brief Configures the completion group associated with a transfer ring.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param name The name of the completion group to be associated with the
 * transfer ring. Pass `NULL` to associate the transfer ring with the default
 * completion group.
 * @param selector The numerical selector of the completion group to be
 * associated with the transfer ring. Pass zero if `name` is `NULL`.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_completion_group(airship_acipc_tr_t tr, airship_string_t AIRSHIP_NULLABLE name, uint32_t selector);

/**
 * @brief Returns whether transfers on a transfer ring may complete out of
 * order.
 * @param tr The transfer ring to be accessed.
 * @returns Whether transfers on the ring may complete in a different order than
 * they were enqueued.
 */
AIRSHIP_EXPORT
bool airship_acipc_tr_get_out_of_order(airship_acipc_tr_t tr);

/**
 * @brief Returns whether a transfer ring uses in-place completion.
 * @param tr The transfer ring to be accessed.
 * @returns Whether the transfer ring uses in-place completion.
 */
AIRSHIP_EXPORT
bool airship_acipc_tr_get_in_place(airship_acipc_tr_t tr);

/**
 * @brief Sets *TR Open* message client data for a transfer ring.
 *
 * This function may not be invoked after activation.
 *
 * @param tr The transfer ring to be accessed.
 * @param data Client data to be appended to the *TR Open* message when the ring
 * is opened.
 * @param length Length of the client data in bytes.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_open_clientdata(airship_acipc_tr_t tr, AIRSHIP_NOESCAPE const void *AIRSHIP_NULLABLE data, uint32_t length);

/**
 * @brief Get the transfer ring ID (TRID) for a transfer ring.
 * @param tr The transfer ring owning the returned TRID value.
 * @returns The transfer ring's ID value.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_trid(airship_acipc_tr_t tr);

/**
 * @brief Returns the name of the transfer ring as it appears in the plist configuration.
 * @param tr The transfer ring handle to be accessed.
 * @returns The name of the transfer ring. The caller is responsible for releasing the
 * returned string.
 */
AIRSHIP_EXPORT
AIRSHIP_RETURNS_RETAINED airship_string_t airship_acipc_tr_get_name(airship_acipc_tr_t tr);

/**
 * @brief Get the selector of the transfer ring.
 * @param tr The transfer ring handle to query.
 * @returns The selector value for the transfer ring instance.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_tr_get_selector(airship_acipc_tr_t tr);

/**
 * @brief Override the doorbell moderation specification for a transfer ring.
 *
 * @note Passing an interval value equal to `UINT32_MAX` will cause doorbell writes for this tr to not be scheduled,
 * Instead they wil only be written when another ring (not configured with the max interval) schedules a write.
 *
 * @param tr The transfer ring that is being modified.
 * @param interval_usec The new doorbell moderation interval value, in microseconds.
 * @param leeway_usec The new doorbell moderation leeway value, in microseconds.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_doorbell_moderation(airship_acipc_tr_t tr, uint32_t interval_usec, uint32_t leeway_usec);

/// Transfer ring modes used with `airship_acipc_tr_set_mode`.
typedef enum airship_acipc_tr_mode_t
{
    /**
     * @brief Standard transfer ring.
     *
     * Transfer rings in standard mode are restricted from using the following
     * APIs:
     *  - `::airship_acipc_tr_enqueue_batch`
     *  - `::airship_acipc_tr_dequeue_batch`
     */
    AIRSHIP_ACIPC_TR_MODE_STANDARD = 0,
    /**
     * @brief Batch mode transfer ring.
     *
     * Transfer rings configured in batch mode have the added requirement that
     * they must be in `::AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED` or
     * `::AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED`before the transfer ring
     * handle can be destroyed. This is to prevent inflight packets from being
     * deallocated while they are still pending.
     *
     * Transfer rings expect to have unique ownership of packets that have been
     * enqueued using batch mode. All packets must have a +1 reference count when
     * enqueued using `::airship_acipc_tr_enqueue_batch`, airship will hold onto
     * this reference until the packet is added to the output queue in
     * `::airship_acipc_tr_dequeue_batch`. If any packets have not been dequeued
     * when the transfer ring is destroyed, the ring will deallocate any remaining
     * packets, which decrements the refcount.
     *
     * Transfer rings configured for batch mode are required to use the following
     * APIs for enqueuing transfers and retrieving completions:
     *  - `::airship_acipc_tr_enqueue_batch`
     *  - `::airship_acipc_tr_dequeue_batch`
     *
     * Batch mode also restricts use to the following APIs:
     *  - `::airship_acipc_tr_enqueue_transfer_with_iosk_packet`
     *  - `::airship_acipc_tr_enqueue_transfer_with_ioun_packet`
     *  - `::airship_acipc_tr_enqueue_transfer`
     *  - `::airship_acipc_tr_sync`
     */
    AIRSHIP_ACIPC_TR_MODE_BATCH = 1,
} airship_acipc_tr_mode_t;

/**
 * @brief Configures the operation mode of a transfer ring.
 *
 * see `airship_acipc_tr_mode_t` for mode information.
 *
 * @param tr The transfer ring that is being configured.
 * @param mode The selected mode of operation.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_mode(airship_acipc_tr_t tr, airship_acipc_tr_mode_t mode);

/**
 * @brief Override the interrupt specification for a transfer ring.
 *
 * This function may not be invoked after activation.
 *
 * @note The desired interrupt specification can be applied to multiple transfer rings.
 *
 * @param tr The transfer ring that is being modified.
 * @param interrupt The name of the interrupt specification to apply.
 * @param selector The interrupt selector to apply.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_set_interrupt(airship_acipc_tr_t tr, airship_string_t interrupt, uint32_t selector);

/**
 * @brief Activates a transfer ring.
 *
 * Transfer rings are initialized in an inactive state and must be activated
 * before use.
 *
 * Calls to these functions are prohibited after activation:
 * - `::airship_acipc_tr_set_size`
 * - `::airship_acipc_tr_set_backing_ring_size`
 * - `::airship_acipc_tr_set_transfer_footer_size`
 * - `::airship_acipc_tr_set_completion_footer_size`
 * - `::airship_acipc_tr_set_completion_ring`
 * - `::airship_acipc_tr_set_completion_group`
 * - `::airship_acipc_tr_set_open_clientdata`
 * - `::airship_acipc_tr_set_doorbell_moderation`
 * - `::airship_acipc_tr_set_mode`
 * - `::airship_acipc_tr_set_interrupt`
 *
 * @param tr The transfer ring handle to be activated.
 * @retval ::AIRSHIP_OK if the ring was successfully activated.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_EBADARGUMENT if the ring configuration is invalid.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_activate(airship_acipc_tr_t tr);

/**
 * @brief Retrieves a transfer ring's current state.
 * @param tr The transfer ring to be accessed.
 * @param out_detail Optional output parameter used to return detailed status
 * information. The returned value will be a bitmask of values from
 * `::airship_acipc_ring_state_detail_flag_t`.
 * @returns The transfer ring's current state.
 */
AIRSHIP_EXPORT
airship_acipc_ring_state_t airship_acipc_tr_get_state(airship_acipc_tr_t tr, AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_detail);

/**
 * @brief Creates a monitor associated with a transfer ring's state.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param tr The transfer ring to be tracked.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_tr_create_state_monitor(airship_acipc_tr_t tr);

/**
 * @brief Opens a transfer ring.
 *
 * This function only sends a *TR Open* message; it does not wait for the
 * device's response.
 *
 * @param tr The transfer ring to be opened.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the transfer ring state is not
 * `::AIRSHIP_ACIPC_RING_STATE_AVAILABLE`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_open(airship_acipc_tr_t tr);

/**
 * @brief Closes a transfer ring.
 *
 * This function only sends a *TR Close* message; it does not wait for the
 * device's response.
 *
 * @param tr The transfer ring to be closed.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the transfer ring state is not one of:
 * - `::AIRSHIP_ACIPC_RING_STATE_OPENING`
 * - `::AIRSHIP_ACIPC_RING_STATE_OPEN`
 * - `::AIRSHIP_ACIPC_RING_STATE_LIMBO`
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_close(airship_acipc_tr_t tr);

/// Operation flags for use with `::airship_acipc_tr_sync`.
typedef enum airship_acipc_tr_sync_operation
{
    /// Sends queued transfers to the driver, making them visible to the device.
    AIRSHIP_ACIPC_TR_SYNC_FLUSH_TRANSFERS = (1 << 0),
    /**
     * @brief Processes changes in the tail index.
     *
     * This operation clears descriptors from the underlying *Transfer Ring*
     * data structure, making space to enqueue new transfers. For transfer rings
     * that use in-place completion, it also makes completions availalble to be
     * fetched.
     *
     * The value tracked by `::airship_acipc_tr_create_sync_monitor` sets this
     * flag to indicate that there is a pending tail index update waiting to be
     * processed.
     *
     * This operation occurs before `::AIRSHIP_ACIPC_TR_SYNC_FETCH_COMPLETIONS`
     * if both are requested.
     */
    AIRSHIP_ACIPC_TR_SYNC_PROCESS_TI_UPDATE = (1 << 1),
    /**
     * @brief Fetches completions from the driver, completing pending transfers.
     *
     * The value tracked by `::airship_acipc_tr_create_sync_monitor` sets this
     * flag to indicate that there are pending completions waiting to be
     * fetched.
     *
     * This operation occurs after `::AIRSHIP_ACIPC_TR_SYNC_PROCESS_TI_UPDATE`
     * if both are requested.
     */
    AIRSHIP_ACIPC_TR_SYNC_FETCH_COMPLETIONS = (1 << 2),
} airship_acipc_tr_sync_operation_t;

/**
 * @brief Synchronizes local transfer ring state with the driver.
 * @param tr The transfer ring to be synchronized.
 * @param flags Bitmask of `::airship_acipc_tr_sync_operation_t` values.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_sync(airship_acipc_tr_t tr, uint32_t flags);

/**
 * @brief Creates a monitor associated with pending sync operations on a
 * transfer ring.
 *
 * The tracked value is a bitmask of `::airship_acipc_tr_sync_operation_t`
 * values indicating which operations are pending.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param tr The transfer ring to be tracked.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_tr_create_sync_monitor(airship_acipc_tr_t tr);

/**
 * @brief Resets a transfer ring.
 *
 * On reset:
 * - The transfer ring state is changed to
 * `::AIRSHIP_ACIPC_RING_STATE_AVAILABLE` or
 * `::AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE`.
 * - All transfers are discarded.
 *
 * @param tr The transfer ring to be reset.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the transfer ring state is not
 * `::AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_reset(airship_acipc_tr_t tr);

/**
 * @brief Synthesizes completions for incomplete transfers.
 *
 * The Airship ACIPC implementation always delivers exactly one completion for
 * each enqueued transfer, except when transfers are discarded with
 * `::airship_acipc_tr_reset`.
 *
 * Clients can use `::airship_acipc_tr_synthesize_reset_completions` together
 * with the normal completion flow to ensure that all transfers are complete
 * before calling `::airship_acipc_tr_reset`, so that nothing is *ever*
 * discarded.
 *
 * Completions are still synthesized if the connection to the driver is broken,
 * though in that case the device may continue to read or modify the payload
 * buffers of the transfers for which completions were synthesized.
 *
 * Transfers completed by this function have result code
 * `::AIRSHIP_ACIPC_IO_RESULT_RESET`.
 *
 * @param tr The transfer ring for which to synthesize completions.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the transfer ring state is not
 * `::AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_synthesize_reset_completions(airship_acipc_tr_t tr);

/**
 * @brief Breaks a transfer ring handle's connection to the driver.
 *
 * This function has the same effect on the driver as calling
 * `::airship_acipc_tr_destroy`. It can be used together with
 * `::airship_acipc_tr_synthesize_reset_completions` to synthesize completions
 * regardless of the transfer ring state.
 *
 * @param tr The transfer ring handle to be disconected from the driver.
 */
AIRSHIP_EXPORT
void airship_acipc_tr_disconnect(airship_acipc_tr_t tr);

/// Option flags for use with `::airship_acipc_tr_enqueue_transfer`.
typedef enum airship_acipc_tr_enqueue_option
{
    /**
     * @brief Chains the transfer with the next transfer, so they are both
     * received by the device as a single I/O.
     *
     * The transfer must not be flushed until the full chain is queued. ACIPC
     * §3.12.2.1 effectively limits the number of chained transfers in a single
     * I/O to 256 for most ring configurations.
     */
    AIRSHIP_ACIPC_TR_ENQUEUE_OPTION_CHAIN = (1 << 0),
} airship_acipc_tr_enqueue_option_t;

/**
 * @brief Enqueues a transfer in a transfer ring.
 *
 * This function enqueues a transfer in a transfer ring. The lifetime of a
 * transfer begins when it is enqueued with
 * `::airship_acipc_tr_enqueue_transfer` and ends when it is consumed with
 * `::airship_acipc_tr_consume_transfers`. A "pending" transfer is one that ha
 *  been enqueued but for which a completion has not been received.
 *
 * Enqueued transfers are not immediately sent to the driver---a call to
 * `::airship_acipc_tr_sync` is required to make them visible to the device.
 *
 * The content of `extbuf` is not copied. The caller must guarantee that the
 * content of the relevant range is valid until a completion for the transfer is
 * received. The driver will ensure that the backing memory for `extbuf` remains
 * accessible to the device until the transfer is complete, even if `tr` is
 * destroyed.
 *
 * Header and footer content is copied. The caller may immediatelly re-use or
 * free the `header` and `footer` buffers after this function returns. Header
 * and footer content is truncated or zero-extended as needed to match the size
 * of the underlying *Transfer Ring* data structure's header and footer.
 *
 * ### Tags
 *
 * Every transfer has a 16-bit identifier called a tag. The tag can be assigned
 * automatically, or it can be specified by the caller. ACIPC §3.5.2.1 requires
 * that tag values among pending transfers in a transfer ring are unique.
 *
 * #### In-Order
 *
 * For in-order transfer rings, ACIPC §3.5.2.1 requires that the tag value for a
 * transfer is equal to the index of slot its descriptor occupies within the
 * ring. I.e. the tag value must be zero for the first transfer and increase by
 * one---modulo the size of the underlying *Transfer Ring* data structure---for
 * each subsequent transfer.
 *
 * The Airship ACIPC implementation further requires that tag values are unique
 * among live transfers on the transfer ring, limiting the effective size of the
 * transfer ring to that of the underlying *Transfer Ring* data structure.
 *
 * #### Out-of-Order
 *
 * For out-of-order transfer rings, the Airship ACIPC implementation
 * distinguishes between the lower tag bits (those bits required to represent
 * the value `<transfer ring size> - 1`) and the upper tag bits (the others).
 * It further requires the value of the lower bits to be less than or equal to
 * `<transfer ring size> - 1` and unique among live transfers on the transfer
 * ring. It does not impose any restriction on the value of the upper bits.
 *
 * | Transfer ring size | Upper tag mask | Lower tag mask |
 * | ------------------ | -------------- | -------------- |
 * | 2                  | `0xfffe`       | `0x0001`       |
 * | 3--4               | `0xfffc`       | `0x0003`       |
 * | 5--8               | `0xfff8`       | `0x0007`       |
 * | 9--16              | `0xfff0`       | `0x000f`       |
 * | 17--32             | `0xffe0`       | `0x001f`       |
 * | 33--64             | `0xffc0`       | `0x003f`       |
 * | 65--128            | `0xff80`       | `0x007f`       |
 * | 129--256           | `0xff00`       | `0x00ff`       |
 * | 257--512           | `0xfe00`       | `0x01ff`       |
 * | 513--1024          | `0xfc00`       | `0x03ff`       |
 * | 1025--2048         | `0xf800`       | `0x07ff`       |
 * | 2049--4096         | `0xf000`       | `0x0fff`       |
 * | 4097--8192         | `0xe000`       | `0x1fff`       |
 * | 8193--16384        | `0xc000`       | `0x3fff`       |
 * | 16385--32768       | `0x8000`       | `0x7fff`       |
 * | 32769--65535       | `0x0000`       | `0xffff`       |
 *
 * @param tr The transfer ring in which to enqueue the transfer.
 * @param tag Tag value for the transfer.
 * @param flags Bitmask of `::airship_acipc_tr_enqueue_option_t` values.
 * @param extbuf The payload buffer for the transfer.
 * @param extbuf_offset The offset in bytes of the payload in the payload
 * buffer.
 * @param extbuf_length The length in bytes of the payload in the payload
 * buffer.
 * @param header The header content for the transfer.
 * @param header_length The length in bytes of the header content. Nonzero
 * header length may be supplied with null `header`, in which case the length is
 * used to compute the descriptor length but no content is copied into the
 * descriptor header.
 * @param footer The footer content for the transfer.
 * @param footer_length The length in bytes of the footer content. Nonzero
 * footer length may be supplied with null `footer`, in which case the length is
 * used to compute the descriptor length but no content is copied into the
 * descriptor footer.
 * @retval ::AIRSHIP_ENOSPACE if there is no available space in the transfer
 * ring.
 * @retval ::AIRSHIP_EBADARGUMENT if a parameter is invalid.
 * @retval ::AIRSHIP_ECANTMAP if the payload buffer mapping is expired.
 * @retval ::AIRSHIP_ENOTREADY if the transfer ring has not been successfully
 * opened.
 * @retval ::AIRSHIP_OK if the transfer was successfully enqueued.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_enqueue_transfer(airship_acipc_tr_t tr, uint16_t tag, uint32_t flags, airship_buffer_t AIRSHIP_NULLABLE extbuf,
                                                   uint32_t extbuf_offset, uint32_t extbuf_length, AIRSHIP_NOESCAPE const void *AIRSHIP_NULLABLE header,
                                                   uint32_t header_length, AIRSHIP_NOESCAPE const void *AIRSHIP_NULLABLE footer, uint32_t footer_length);

/**
 * @brief Retrieves the number of free spaces in a transfer ring.
 *
 * The returned value is the number of transfers that can be enqueued with
 * `::airship_acipc_tr_enqueue_transfer` before it returns `::AIRSHIP_ENOSPACE`.
 *
 * @param tr The transfer ring to be accessed.
 * @returns The number of free spaces in the transfer ring.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_free_space(airship_acipc_tr_t tr);

/**
 * @brief Creates a monitor associated with the amount of free space in a
 * transfer ring.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param tr The transfer ring to be tracked.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_tr_create_free_space_monitor(airship_acipc_tr_t tr);

/**
 * @brief Retrieves the first tag available for enqueuing a new transfer.
 * @pre Free space for a transfer is available.
 *
 * See `::airship_acipc_tr_enqueue_transfer` for tag assignment details. The
 * ordering of tags returned by this function for out-of-order rings is
 * unspecified and subject to change without notice.
 *
 * @param tr The transfer ring to be accessed.
 * @returns The first tag available for enqueuing a new transfer.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_first_free_tag(airship_acipc_tr_t tr);

/// Result codes returned by `::airship_acipc_tr_get_transfer_completion`.
typedef enum airship_acipc_io_result
{
    /// Transfer completed successfully.
    AIRSHIP_ACIPC_IO_RESULT_SUCCESS,
    /// Transfer completed with a code indicating an error.
    AIRSHIP_ACIPC_IO_RESULT_ERROR,
    /// Transfer completed with a code indicating overflow.
    AIRSHIP_ACIPC_IO_RESULT_OVERFLOW,
    /// Transfer completed with a code indicating cancellation.
    AIRSHIP_ACIPC_IO_RESULT_CANCELED,
    /**
     * Transfer completion was synthesized with
     * `::airship_acipc_tr_synthesize_reset_completions`.
     */
    AIRSHIP_ACIPC_IO_RESULT_RESET,
} airship_acipc_io_result_t;

/**
 * @brief Transfer completion information returned by
 * `::airship_acipc_tr_get_transfer_completion`.
 */
typedef struct airship_acipc_tr_transfer_completion
{
    /**
     * @brief Result code.
     *
     * Guaranteed to be the same for an entire transfer chain.
     */
    airship_acipc_io_result_t io_result;
    /**
     * @brief Completion ring ID.
     *
     * Ring ID of the completion ring on which the completion for the transfer
     * was received. Guaranteed to be the same for an entire transfer chain.
     *
     * Not valid if `io_result` is `::AIRSHIP_ACIPC_IO_RESULT_RESET`, or if the
     * transfer ring uses in-place completion.
     */
    uint16_t cr_id;

    /**
     * @brief *Status* value from the transfer descriptor or completion
     * descriptor.
     *
     * Not valid if `io_result` is `::AIRSHIP_ACIPC_IO_RESULT_RESET`.
     */
    uint8_t status_code;
    /**
     * @brief *Type* value from the transfer descriptor or completion
     * descriptor.
     *
     * Not valid if `io_result` is `::AIRSHIP_ACIPC_IO_RESULT_RESET`.
     */
    uint8_t descriptor_type;
    /**
     * @brief *Size* value from the transfer descriptor or completion
     * descriptor.
     *
     * Not valid if `io_result` is `::AIRSHIP_ACIPC_IO_RESULT_RESET`.
     */
    uint32_t size;
    /**
     * @brief *Client Data* value from the completion descriptor.
     *
     * Not valid if `io_result` is `::AIRSHIP_ACIPC_IO_RESULT_RESET`, or if the
     * transfer ring uses in-place completion.
     */
    uint32_t client_data;

    /// Whether this is the final completed transfer.
    bool last_completed_transfer;
    /// Whether this is the final transfer in a transfer chain.
    bool last_in_chain;
    /**
     * @brief Tag of the next completed transfer.
     *
     * Not valid if `last_completed_transfer` is true.
     */
    uint16_t next_tag;
} airship_acipc_tr_transfer_completion_t;

/**
 * @brief Retrieves completion information for a transfer.
 *
 * For in-order transfer rings, completions are guaranteed to arrive in the same
 * order the associated transfers were enqueued. For out-of-order transfer
 * rings, completions may arrive in any order.
 *
 * For a transfer chain, completions are guaranteed to arrive simultaneously,
 * contiguously, and in the same order as the chained transfers were enqueued.
 *
 * Header and footer content is copied from the completion descriptor that
 * completed a transfer. For transfer rings using in-place completion, it is
 * copied from the transfer descriptor itself. Header and footer content is
 * truncated or zero-extended as needed to match the size of the `header` and
 * `footer` buffers.
 *
 * @param tr The transfer ring to be accessed.
 * @param tag The tag of the transfer to be accessed.
 * @param out_completion Output parameter used to return the completion
 * information. Valid only if the return value is `::AIRSHIP_OK`.
 * @param out_header Optional buffer into which to copy header content. Valid
 * only if the return value is `::AIRSHIP_OK`.
 * @param header_size Maximum size of the header content to copy.
 * @param out_footer Optional buffer into which to copy footer content. Valid
 * only if the return value is `::AIRSHIP_OK`.
 * @param footer_size Maximum size of the footer content to copy.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EBADARGUMENT if the tag does not correspond to a completed
 * transfer.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_get_transfer_completion(airship_acipc_tr_t tr, uint16_t tag,
                                                          AIRSHIP_NOESCAPE airship_acipc_tr_transfer_completion_t *AIRSHIP_NULLABLE out_completion,
                                                          AIRSHIP_NOESCAPE void *AIRSHIP_NULLABLE out_header, uint32_t header_size,
                                                          AIRSHIP_NOESCAPE void *AIRSHIP_NULLABLE out_footer, uint32_t footer_size);

/**
 * @brief Retrieves the number of unconsumed completed transfers.
 * @param tr The transfer ring to be accessed.
 * @returns The number of completed transfers present in the ring.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_completed_transfer_count(airship_acipc_tr_t tr);

/**
 * @brief Retrieves the tag for the first unconsumed completed transfer.
 * @pre A completed transfer is present.
 *
 * See `::airship_acipc_tr_get_transfer_completion` for ordering details.
 *
 * @param tr The transfer ring to be accessed.
 * @returns The tag of the first completed transfer.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_tr_get_first_completed_tag(airship_acipc_tr_t tr);

/**
 * @brief Consumes completed transfers, clearing space in a ring.
 *
 * Chained transfers must be consumed together---a chain may not be partially
 * consumed.
 *
 * @param tr The transfer ring to be accessed.
 * @param tag The tag of the first transfer to be consumed.
 * @param count The number of transfers to be consumed.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EBADARGUMENT if a parameter is invalid.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_tr_consume_transfers(airship_acipc_tr_t tr, uint16_t tag, uint16_t count);

/// ACIPC completion ring handle type.
typedef struct airship_acipc_cr *airship_acipc_cr_t;

/**
 * @brief Creates a handle to interact with a completion ring.
 *
 * The returned handle must be released with `::airship_acipc_cr_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param name The name of the completion ring to be accessed.
 * @param selector Numerical selector of the completion ring to be accessed.
 * @returns The newly created completion ring handle, or `NULL` if an error
 * occurs.
 */
AIRSHIP_EXPORT
airship_acipc_cr_t AIRSHIP_NULLABLE airship_acipc_cr_create(airship_client_t client, airship_string_t name, uint32_t selector);

/**
 * @brief Destroys a completion ring, releasing any associated resources.
 *
 * Destroying a completion ring handle automatically closes the ring if it is
 * open.
 *
 * @param cr The completion ring to be destroyed.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_destroy(airship_acipc_cr_t cr);

/**
 * @brief Returns the size of a completion ring's underlying *Completion Ring*
 * data structure.
 * @param cr The completion ring to be accessed.
 * @returns The size (element count) of the underlying *Completion Ring* data
 * structure.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_cr_get_backing_ring_size(airship_acipc_cr_t cr);

/**
 * @brief Configures the size of a completion ring's underlying *Completion
 * Ring* data structure.
 *
 * This function may not be invoked after activation.
 *
 * @param cr The completion ring to be accessed.
 * @param count The new size (elemnt count) of the underlying *Completion Ring*
 * data structure.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_backing_ring_size(airship_acipc_cr_t cr, uint16_t count);

/**
 * @brief Returns the size of the optional footer for completions in a
 * completion ring.
 * @param cr The completion ring to be accessed.
 * @returns The length in bytes of the optional footer for completions in the
 * ring.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_cr_get_footer_size(airship_acipc_cr_t cr);

/**
 * @brief Configures the size of the optional footer for completions in a
 * completion ring.
 *
 * This function may not be invoked after activation.
 *
 * @param cr The completion ring to be accessed.
 * @param length The new length in bytes of the optional footer for completions
 * in the ring.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_footer_size(airship_acipc_cr_t cr, uint32_t length);

/**
 * @brief Returns the completion group associated with a completion ring.
 * @param cr The completion ring to be accessed.
 * @param out_selector Output param used to return the numerical selector of the
 * associated completion group, or zero if `NULL` is returned.
 * @returns The name of the associated completion group, or `NULL` on error or
 * if the completion ring is associated with the default completion group. The
 * caller is responsible for releasing the returned string.
 */
AIRSHIP_EXPORT
AIRSHIP_RETURNS_RETAINED airship_string_t AIRSHIP_NULLABLE airship_acipc_cr_get_completion_group(airship_acipc_cr_t cr,
                                                                                                 AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_selector);

/**
 * @brief Configures the completion group associated with a completion ring.
 *
 * This function may not be invoked after activation.
 *
 * @param cr The completion ring to be accessed.
 * @param name The name of the completion group to be associated with the
 * completion ring. Pass `NULL` to associate the completion ring with the
 * default completion group.
 * @param selector The numerical selector of the completion group to be
 * associated with the completion ring. Pass zero if `name` is `NULL`.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_completion_group(airship_acipc_cr_t cr, airship_string_t AIRSHIP_NULLABLE name, uint32_t selector);

/**
 * @brief Returns whether a completion ring's mirror is enabled.
 * @param cr The completion ring to be accessed.
 * @returns Whether the ring's mirror is enabled.
 */
AIRSHIP_EXPORT
bool airship_acipc_cr_get_mirror_enabled(airship_acipc_cr_t cr);

/**
 * @brief Enables or disables a completion ring's mirror.
 *
 * Many clients do not need to manually process completion descriptors---they
 * can make completions available to associated transfer rings just by calling
 * `::airship_acipc_cr_sync`. Clients that do have a need to examine descriptors
 * can use this function to enable the completion ring mirror.
 *
 * If enabled, the mirror will record each completion descriptor processed by
 * `::airship_acipc_cr_sync` and make it accessible via
 * `::airship_acipc_cr_get_mirror_element`. The mirror capacity is the same as
 * the underlying *Completion Ring* data structure. `::airship_acipc_cr_sync`
 * will stop processing descriptors if the mirror is full. Clients are
 * responsible for clearing space in the mirror with
 * `::airship_acipc_cr_consume_mirror_elements`.
 *
 * By default the mirror is disabled.
 *
 * This function may not be invoked after activation.
 *
 * @param cr The completion ring to be configured.
 * @param enable Whether to enable the mirror.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_mirror_enabled(airship_acipc_cr_t cr, bool enable);

/**
 * @brief Sets *CR Open* message client data for a completion ring.
 *
 * This function may not be invoked after activation.
 *
 * @param cr The completion ring to be accessed.
 * @param data Client data to be appended to the *CR Open* message when the ring
 * is opened.
 * @param length Length of the client data in bytes.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_open_clientdata(airship_acipc_cr_t cr, AIRSHIP_NOESCAPE const void *AIRSHIP_NULLABLE data, uint32_t length);

/**
 * @brief Get the completion ring ID (CRID) for a completion ring.
 * @param cr The completion ring owning the returned CRID value.
 * @returns The completion ring's ID value.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_cr_get_crid(airship_acipc_cr_t cr);

/**
 * @brief Get the name of the completion ring.
 * @param cr The completion ring handle to query.
 * @returns A string containing the name of the completion ring.
 */
AIRSHIP_EXPORT
AIRSHIP_RETURNS_RETAINED airship_string_t airship_acipc_cr_get_name(airship_acipc_cr_t cr);

/**
 * @brief Get the selector of the completion ring.
 * @param cr The completion ring handle to query.
 * @returns The selector value for the completion ring instance.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_cr_get_selector(airship_acipc_cr_t cr);

/**
 * @brief Override the doorbell moderation specification for a completion ring.
 *
 * @note Passing an interval value equal to `UINT32_MAX` will cause doorbell writes for this cr to not be scheduled,
 * Instead they wil only be written when another ring (not configured with the max interval) schedules a write.
 *
 * @param cr The completion ring that is being modified.
 * @param interval_usec The new doorbell moderation interval value, in microseconds.
 * @param leeway_usec The new doorbell moderation leeway value, in microseconds.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_doorbell_moderation(airship_acipc_cr_t cr, uint32_t interval_usec, uint32_t leeway_usec);

/**
 * @brief Override the interrupt specification for a completion ring.
 *
 * This function may not be invoked after activation.
 *
 * @note The desired interrupt specification can be applied to multiple completion rings.
 *
 * @param cr The completion ring that is being modified.
 * @param interrupt The name of the interrupt specification to apply.
 * @param selector The interrupt selector to apply.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_set_interrupt(airship_acipc_cr_t cr, airship_string_t interrupt, uint32_t selector);

/**
 * @brief Activates a completion ring.
 *
 * Completion rings are initialized in an inactive state and must be activated
 * before use.
 *
 * Calls to these functions are prohibited after activation:
 * - `::airship_acipc_cr_set_backing_ring_size`
 * - `::airship_acipc_cr_set_footer_size`
 * - `::airship_acipc_cr_set_completion_group`
 * - `::airship_acipc_cr_set_mirror_enabled`
 * - `::airship_acipc_cr_set_open_clientdata`
 * - `::airship_acipc_cr_set_interrupt`
 *
 * @param cr The completion ring handle to be activated.
 * @retval ::AIRSHIP_OK if the ring was successfully activated.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_EBADARGUMENT if the ring configuration is invalid.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_cr_activate(airship_acipc_cr_t cr);

/**
 * @brief Retrieves a completion ring's current state.
 * @param cr The completion ring to be accessed.
 * @param out_detail Optional output parameter used to return detailed status
 * information. The returned value will be a bitmask of values from
 * `::airship_acipc_ring_state_detail_flag_t`.
 * @returns The completion ring's current state.
 */
AIRSHIP_EXPORT
airship_acipc_ring_state_t airship_acipc_cr_get_state(airship_acipc_cr_t cr, AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_detail);

/**
 * @brief Creates a monitor associated with a completion ring's state.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param cr The completion ring to be tracked.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_cr_create_state_monitor(airship_acipc_cr_t cr);

/**
 * @brief Opens a completion ring.
 *
 * This function only sends a *CR Open* message; it does not wait for the
 * device's response.
 *
 * @param cr The completion ring to be opened.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the completion ring state is not
 * `::AIRSHIP_ACIPC_RING_STATE_AVAILABLE`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_cr_open(airship_acipc_cr_t cr);

/**
 * @brief Closes a completion ring.
 *
 * This function only sends a *CR Close* message; it does not wait for the
 * device's response.
 *
 * @param cr The completion ring to be closed.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the completion ring state is not one of:
 * - `::AIRSHIP_ACIPC_RING_STATE_OPENING`
 * - `::AIRSHIP_ACIPC_RING_STATE_OPEN`
 * - `::AIRSHIP_ACIPC_RING_STATE_LIMBO`
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_cr_close(airship_acipc_cr_t cr);

/**
 * @brief Resets a completion ring.
 *
 * On reset:
 * - The completion ring state is changed to
 * `::AIRSHIP_ACIPC_RING_STATE_AVAILABLE` or
 * `::AIRSHIP_ACIPC_RING_STATE_UNAVAILABLE`.
 * - All unprocessed completion descriptors are discarded.
 * - All unconsumed mirror elements are discarded.
 *
 * @param cr The completion ring to be reset.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the completion ring state is not
 * `::AIRSHIP_ACIPC_RING_STATE_DEAD_SETTLED`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_cr_reset(airship_acipc_cr_t cr);

/// Operation flags for use with `::airship_acipc_cr_sync`.
typedef enum airship_acipc_cr_sync_operation
{
    /**
     * @brief Processes changes in the head index.
     *
     * This operation clears descriptors from the underlying *Completion Ring*
     * data structure, making space for the device to send new completions. It
     * also makes completions available to associated transfer rings, and makes
     * mirror elements available.
     *
     * The value tracked by `::airship_acipc_cr_create_sync_monitor` sets this
     * flag to indicate that there is a pending head index update waiting to be
     * processed.
     */
    AIRSHIP_ACIPC_CR_SYNC_PROCESS_HI_UPDATE = (1 << 0),
} airship_acipc_cr_sync_operation_t;

/**
 * @brief Synchronizes local completion ring state with the driver.
 * @param cr The completion ring to be synchronized.
 * @param flags Bitmask of `::airship_acipc_cr_sync_operation_t` values.
 */
AIRSHIP_EXPORT
void airship_acipc_cr_sync(airship_acipc_cr_t cr, uint32_t flags);

/**
 * @brief Creates a monitor associated with pending sync operations on a
 * completion ring.
 *
 * The tracked value is a bitmask of `::airship_acipc_cr_sync_operation_t`
 * values indicating which operations are pending.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param cr The completion ring to be tracked.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_cr_create_sync_monitor(airship_acipc_cr_t cr);

/// Mirror element types.
typedef enum airship_acipc_cr_mirror_element_type
{
    /// Element is a completion record.
    AIRSHIP_ACIPC_CR_MIRROR_ELEMENT_COMPLETION_RECORD,
    /// Element is a raw completion descriptor.
    AIRSHIP_ACIPC_CR_MIRROR_ELEMENT_RAW_DESCRIPTOR,
} airship_acipc_cr_mirror_element_type_t;

/// Completion record mirror element.
typedef struct airship_acipc_cr_mirror_completion_record
{
    /// *Type* field from original *Completion Descriptor* data structure.
    uint8_t desctype;
    /// Ring ID of the associated transfer ring.
    uint16_t tr_id;
    /// Number of transfer chains completed by the descriptor.
    uint16_t io_count;
    /**
     * @brief Tag of the first transfer in the first transfer chain completed by
     * the descriptor.
     *
     * Valid only if `io_count` is greater than zero.
     */
    uint16_t first_tag;
} airship_acipc_cr_mirror_completion_record_t;

/// Raw descriptor mirror element.
typedef struct airship_acipc_cr_mirror_raw_descriptor
{
    /// Copy of original *Completion Descriptor* data structure.
    uint8_t bytes[AIRSHIP_ACIPC_CD_SIZE];
} airship_acipc_cr_mirror_raw_descriptor_t;

/// Mirror element data.
typedef union airship_acipc_cr_mirror_element_data
{
    /**
     * @brief Data for completion record elements.
     *
     * Valid only if element type is
     * `::AIRSHIP_ACIPC_CR_MIRROR_ELEMENT_COMPLETION_RECORD`.
     */
    airship_acipc_cr_mirror_completion_record_t completion_record;
    /**
     * @brief Data for raw descriptor elements.
     *
     * Valid only if element type is
     * `::AIRSHIP_ACIPC_CR_MIRROR_ELEMENT_RAW_DESCRIPTOR`.
     */
    airship_acipc_cr_mirror_raw_descriptor_t raw_descriptor;
} airship_acipc_cr_mirror_element_data_t;

/**
 * @brief Mirror element information returned by
 * `::airship_acipc_cr_get_mirror_element`.
 */
typedef struct airship_acipc_cr_mirror_element
{
    /// Mirror element type.
    airship_acipc_cr_mirror_element_type_t type;
    /// Mirror element data.
    airship_acipc_cr_mirror_element_data_t data;
} airship_acipc_cr_mirror_element_t;

/**
 * @brief Retrieves a mirror element.
 *
 * If a completion descriptor completes transfers (i.e. if it is not marked as
 * *Async* or *Null* per ACIPC §3.12.3.5), the mirror records its effect as an
 * element of type `::AIRSHIP_ACIPC_CR_MIRROR_ELEMENT_COMPLETION_RECORD`.
 * Otherwise, the mirror records a copy of the full descriptor as an element of
 * type `::AIRSHIP_ACIPC_CR_MIRROR_ELEMENT_RAW_DESCRIPTOR`.
 *
 * Header and footer content is truncated or zero-extended as needed to match
 * the size of the `header` and `footer` buffers.
 *
 * @param cr The completion ring to be accessed.
 * @param index The index of the element to be accessed.
 * @param out_element Output parameter used to return the element. Valid only if
 * the return value is `::AIRSHIP_OK`.
 * @param out_header Optional buffer into which to copy header content. Valid
 * only if the return value is `::AIRSHIP_OK`.
 * @param header_size Maximum size of the header content to copy.
 * @param out_footer Optional buffer into which to copy footer content. Valid
 * only if the return value is `::AIRSHIP_OK`.
 * @param footer_size Maximum size of the footer content to copy.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EBADARGUMENT if the index is out of range.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_cr_get_mirror_element(airship_acipc_cr_t cr, uint16_t index,
                                                     AIRSHIP_NOESCAPE airship_acipc_cr_mirror_element_t *AIRSHIP_NULLABLE out_element,
                                                     AIRSHIP_NOESCAPE void *AIRSHIP_NULLABLE out_header, uint32_t header_size,
                                                     AIRSHIP_NOESCAPE void *AIRSHIP_NULLABLE out_footer, uint32_t footer_size);

/**
 * @brief Retrieves the number of available mirror elements.
 * @param cr The completion ring to be accessed.
 * @returns The number of available mirror elements.
 */
AIRSHIP_EXPORT
uint16_t airship_acipc_cr_get_mirror_count(airship_acipc_cr_t cr);

/**
 * @brief Consumes mirror elements, clearing space in the mirror.
 *
 * The first `count` mirror elements are consumed.
 *
 * @param cr The completion ring to be accessed.
 * @param count The number of mirror elements to be consumed.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EBADARGUMENT if the count is greater than the number of
 * available elements.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_cr_consume_mirror_elements(airship_acipc_cr_t cr, uint16_t count);

/// ACIPC shared memory region handle type.
typedef struct airship_acipc_memregion *airship_acipc_memregion_t;

/**
 * @brief Creates a handle to interact with a shared memory region.
 *
 * The returned handle must be released with
 * `::airship_acipc_memregion_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param name The name of the shared memory region to be accessed.
 * @param selector Numerical selector of the shared memory region to be
 * accessed.
 * @returns The newly created shared memory region handle, or `NULL` if an error
 * occurs.
 */
AIRSHIP_EXPORT
airship_acipc_memregion_t AIRSHIP_NULLABLE airship_acipc_memregion_create(airship_client_t client, airship_string_t name, uint32_t selector);

/**
 * @brief Destroys a shared memory region, releasing any associated resources.
 * @param region The shared memory region to be destroyed.
 */
AIRSHIP_EXPORT
void airship_acipc_memregion_destroy(airship_acipc_memregion_t region);

/**
 * @brief Sets the backing memory for a shared memory region.
 *
 * This function may not be invoked after activation.
 *
 * The content of `memory` is not copied. The caller must guarantee that the
 * content of the relevant range is valid for the entire duration that the
 * region is mapped. The driver will ensure that the backing memory remains
 * accessible to the device until the region is unmapped, even if `memregion` is
 * destroyed.
 *
 * @param region The shared memory region to be accessed.
 * @param buffer The backing memory buffer to use for the region.
 * @param offset The offset in bytes at which the region should begin in the
 * backing memory buffer.
 * @param length The length in bytes of the region in the backing memory buffer.
 */
AIRSHIP_EXPORT
void airship_acipc_memregion_set_backing_memory(airship_acipc_memregion_t region, airship_buffer_t AIRSHIP_NULLABLE buffer, uint32_t offset, uint32_t length);

/**
 * @brief Sets *Memory Map* message client data for a shared memory region.
 *
 * This function may not be invoked after activation.
 *
 * @param region The shared memory region to be accessed.
 * @param data Client data to be appended to the *Memory Map* message when the
 * ring is mapped.
 * @param length Length of the client data in bytes.
 */
AIRSHIP_EXPORT
void airship_acipc_memregion_set_map_clientdata(airship_acipc_memregion_t region, AIRSHIP_NOESCAPE const void *AIRSHIP_NULLABLE data, uint32_t length);

/**
 * @brief Activates a shared memory region .
 *
 * Shared memory regions are initialized in an inactive state and must be
 * activated before use.
 *
 * Calls to these functions are prohibited after activation:
 * - `::airship_acipc_memregion_set_backing_memory`
 * - `::airship_acipc_memregion_set_map_clientdata`
 *
 * @param region The shared memory region handle to be activated.
 * @retval ::AIRSHIP_OK if the region was successfully activated.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_EBADARGUMENT if the region configuration is invalid.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_memregion_activate(airship_acipc_memregion_t region);

/**
 * @brief Shared memory region states returned by
 * `::airship_acipc_memregion_get_state`.
 *
 * ```
 *  -·-·- Autonomous transition
 *  ----- Directed transition
 *
 *     +-------------+
 *     | UNAVAILABLE |<------+
 *     +-------------+       |
 *       ¦ ^                 |
 *       v ¦                 | reset()
 *     +-----------+       +--------------+
 *  +·-| AVAILABLE |       | DEAD_SETTLED |
 *  ¦  +-----------+       +--------------+
 *  ¦    | map()             ^
 *  ¦    v                   ¦
 *  ¦  +---------+         +----------------+
 *  ¦  | MAPPING |-·-·-·-·>| DEAD_UNSETTLED |
 *  ¦  +---------+         +----------------+
 *  ¦    ¦ | unmap()         ^ ^ ^
 *  ¦    ¦ +-------+         ¦ ¦ ¦
 *  ¦    v         |         ¦ ¦ ¦
 *  ¦  +--------+  |         ¦ ¦ ¦
 *  +·>| MAPPED |-·+·-·-·-·-·+ ¦ ¦
 *     +--------+  |           ¦ ¦
 *       | unmap() |           ¦ ¦
 *       v         v           ¦ ¦
 *     +-------------+         ¦ ¦
 *     | UNMAPPING   |-·-·-·-·-+ ¦
 *     +-------------+           ¦
 *       ¦ ^                     ¦
 *       v | unmap()             ¦
 *     +--------+                ¦
 *     | LIMBO  |-·-·-·-·-·-·-·-·+
 *     +--------+
 * ```
 */
typedef enum airship_acipc_memregion_state
{
    /**
     * @brief The memory region is unmapped and not available to be mapped.
     *
     * See `::airship_acipc_memregion_state_detail_flag_t` for reasons a region
     * may be unavailable.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_AVAILABLE` if the ring becomes
     * available.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_UNAVAILABLE,
    /**
     * @brief The memory region is unmapped and available to be mapped.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_MAPPING` with
     * `::airship_acipc_memregion_map`.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_UNAVAILABLE` if the region becomes
     * unavailable.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_MAPPED` if the memory region is
     * configured to map automatically (very uncommon).
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_AVAILABLE,
    /**
     * @brief The memory region is awaiting the device's response to a map
     * message.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_MAPPED` if the device acknowledges the
     * map message.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_UNSETTLED` if the region becomes
     * unavailable or the device rejects the map message.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_UNMAPPING` with
     * `::airship_acipc_memregion_unmap`.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_MAPPING,
    /**
     * @brief The memory region is mapped.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_UNMAPPING` with
     * `::airship_acipc_memregion_unmap`.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_UNSETTLED` if the region becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_MAPPED,
    /**
     * @brief The memory region is awaiting the device's response to an unmap
     * message.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_RING_STATE_DEAD_UNSETTLED` if the ring becomes
     * unavailable or the device acknowledges the close message.
     * - `::AIRSHIP_ACIPC_RING_STATE_LIMBO` if the device rejects the close
     * message.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_UNMAPPING,
    /**
     * @brief The device has rejected an unmap message for the memory region.
     * The region is not usable.
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_UNMAPPING` with
     * `::airship_acipc_memregion_unmap`.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_UNSETTLED` if the region becomes
     * unavailable.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_LIMBO,
    /**
     * @brief The memory region is not usable, but it is not yet safe to reset
     * its state.
     *
     * Even when otherwise unusable, it is not safe to reset a memory region's
     * state while its underlying memory could still be accessed by the device.
     *
     * See `::airship_acipc_memregion_state_detail_flag_t` for reasons a region
     * may become "dead".
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_SETTLED` when it becomes safe to
     * reset the region state.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_UNSETTLED,
    /**
     * @brief The memory region is unmapped, and its state can be safely reset.
     *
     * See `::airship_acipc_memregion_state_detail_flag_t` for reasons a region
     * may become "dead".
     *
     * Allowed transitions:
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_AVAILABLE` with
     * `::airship_acipc_memregion_reset`.
     * - `::AIRSHIP_ACIPC_MEMREGION_STATE_UNAVAILABLE` with
     * `::airship_acipc_memregion_reset`.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_SETTLED,
    /**
     * @brief Value returned by `::airship_acipc_memregion_get_state` if the
     * connection to the driver is broken.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_EDISCONNECTED,
} airship_acipc_memregion_state_t;

/**
 * @brief Detailed status flags returned by
 * `::airship_acipc_memregion_get_state`.
 */
typedef enum airship_acipc_memregion_state_detail_flag
{
    /// The device is not in the appropriate execution stage.
    AIRSHIP_ACIPC_MEMREGION_STATE_UNAVAILABLE_EXECSTAGE = (1 << 0),
    /// The region parameters conflict with a region that is already mapped.
    AIRSHIP_ACIPC_MEMREGION_STATE_UNAVAILABLE_CONFLICT = (1 << 1),
    /// The device rejected the map message.
    AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_MAPREJECT = (1 << 2),
    /**
     * @brief The region was explicitly unmapped by
     * `::airship_acipc_memregion_unmap`.
     */
    AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_BYREQUEST = (1 << 3),
    /// The ring was unmapped because the driver entered reset.
    AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_DEVICERESET = (1 << 4),
    /// The ring was unmapped because the device execution stage changed.
    AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_EXECSTAGE = (1 << 5),
} airship_acipc_memregion_state_detail_flag_t;

/**
 * @brief Retrieves a shared memory region's current state.
 * @param region The shared memory region to be accessed.
 * @param out_detail Optional output parameter used to return detailed status
 * information. The returned value will be a bitmask of values from
 * `::airship_acipc_memregion_state_detail_flag_t`.
 * @returns The shared memory region's current state.
 */
AIRSHIP_EXPORT
airship_acipc_memregion_state_t airship_acipc_memregion_get_state(airship_acipc_memregion_t region, AIRSHIP_NOESCAPE uint32_t *AIRSHIP_NULLABLE out_detail);

/**
 * @brief Creates a monitor associated with a shared memory region's state.
 *
 * The returned handle must be released with `::airship_monitor_destroy`.
 *
 * @param region The shared memory region to be accessed.
 * @returns The newly created monitor handle, or `NULL` if an error occurs.
 */
AIRSHIP_EXPORT
airship_monitor_t AIRSHIP_NULLABLE airship_acipc_memregion_create_state_monitor(airship_acipc_memregion_t region);

/**
 * @brief Maps a shared memory region.
 *
 * This function only sends a *Memory Map* message; it does not wait for the
 * device's response.
 *
 * @param region The shared memory region to be mapped.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_EBARARGUMENT if the backing memory region is not set.
 * @retval ::AIRSHIP_ENOTREADY if the region state is not
 * `::AIRSHIP_ACIPC_MEMREGION_STATE_AVAILABLE`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_memregion_map(airship_acipc_memregion_t region);

/**
 * @brief Unmaps a shared memory region.
 *
 * This function only sends a *Memory Unmap* message; it does not wait for the
 * device's response.
 *
 * @param region The shared memory region to be unmapped.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the region state is not one of:
 * - `::AIRSHIP_ACIPC_MEMREGION_STATE_MAPPING`
 * - `::AIRSHIP_ACIPC_MEMREGION_STATE_MAPPED`
 * - `::AIRSHIP_ACIPC_MEMREGION_STATE_LIMBO`
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_memregion_unmap(airship_acipc_memregion_t region);

/**
 * @brief Resets an inactive shared memory region.
 *
 * On reset:
 * - The region state is changed to `::AIRSHIP_ACIPC_MEMREGION_STATE_AVAILABLE`
 * or `::AIRSHIP_ACIPC_MEMREGION_STATE_UNAVAILABLE`.
 *
 * @param region The shared memory region to be reset.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_EDISCONNECTED if the connection to the driver is broken.
 * @retval ::AIRSHIP_ENOTREADY if the region state is not
 * `::AIRSHIP_ACIPC_MEMREGION_STATE_DEAD_UNSETTLED`.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_memregion_reset(airship_acipc_memregion_t region);

/// ACIPC doorbell handle type.
typedef struct airship_acipc_doorbell *airship_acipc_doorbell_t;

/**
 * @brief Creates a handle to write to an ACIPC doorbell.
 *
 * The returned handle must be released with
 * `::airship_acipc_doorbell_destroy`.
 *
 * @param client A client handle connected to the driver.
 * @param name The name of the doorbell to be accessed.
 * @param selector Numerical selector of the doorbell to be accessed.
 * @returns The newly created doorbell handle, or `NULL` if an error
 * occurs.
 */
AIRSHIP_EXPORT
airship_acipc_doorbell_t AIRSHIP_NULLABLE airship_acipc_doorbell_create(airship_client_t client, airship_string_t name, uint32_t selector);

/**
 * @brief Destroys a doorbell handle, releasing any associated resources.
 * @param doorbell The doorbell handle to be destroyed.
 */
AIRSHIP_EXPORT
void airship_acipc_doorbell_destroy(airship_acipc_doorbell_t doorbell);

/**
 * @brief Returns the bank value for a doorbell handle.
 * @param doorbell The doorbell handle to query.
 * @returns The bank value for `doorbell`.
 */
AIRSHIP_EXPORT
uint8_t airship_acipc_doorbell_get_bank(airship_acipc_doorbell_t doorbell);

/**
 * @brief Returns the offset value for a doorbell handle.
 * @param doorbell The doorbell handle to query.
 * @returns The offset value for `doorbell`.
 */
AIRSHIP_EXPORT
uint32_t airship_acipc_doorbell_get_offset(airship_acipc_doorbell_t doorbell);

/**
 * @brief Returns the width value for a doorbell handle.
 * @param doorbell The doorbell handle to query.
 * @returns The width value for `doorbell`.
 */
AIRSHIP_EXPORT
uint8_t airship_acipc_doorbell_get_width(airship_acipc_doorbell_t doorbell);

/**
 * @brief Activates a doorbell, saving any configuration changes and preventing
 * any further changes.
 *
 * @note This function must be called before `airship_acipc_doorbell_open`.
 *
 * @param doorbell The doorbell handle to activate.
 * @retval ::AIRSHIP_OK if successful.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_activate(airship_acipc_doorbell_t doorbell);

/**
 * @brief Open a doorbell handle, which connects the handle to the doorbell manager, and
 * grants exclusive access to index mode doorbells.
 *
 * @note This function must be called before any of the following API
 *  - `airship_acipc_doorbell_schedule_update`
 *  - `airship_acipc_doorbell_write`
 *  - `airship_acipc_shared_doorbell_schedule_update`
 *  - `airship_acipc_shared_doorbell_write`
 *
 * @param doorbell The doorbell handle to open.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the doorbell handle is not activated, or if the driver is in reset.
 * @retval ::AIRSHIP_EEXCLUSIVEACCESS if the index mode doorbell is already in use.
 * @retval ::AIRSHIP_EBADARGUMENT if the doorbell does not exist.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_open(airship_acipc_doorbell_t doorbell);

/**
 * @brief Close an opened doorbell handle.
 *
 * @param doorbell The doorbell handle to activate.
 * @retval ::AIRSHIP_OK if successful, or the handle is already closed.
 * @retval ::AIRSHIP_ENOTREADY if the doorbell handle is not activated.
 * @retval ::AIRSHIP_ENOTOPEN if the doorbell handle is not open.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_close(airship_acipc_doorbell_t doorbell);

/**
 * @brief Schedule a doorbell write update, to occur within the interval (since last write)
 * and leeway specified.
 *
 * @note This function does not check if the doorbell is in a shared mode, or index mode.
 * If the doorbell is in shared mode, the `value` parameter is ignored.
 * @note `interval_us` is subject to the doorbell's minimum allowed interval, if it is less
 * than the min interval, the min interval will be used to schedule the write.
 *
 * @param doorbell The doorbell handle to write to.
 * @param interval_us The desired interval (in microseconds) to schedule the write at.
 * @param leeway_us The desired leenway (in microseconds), which provides an upper-bound for the write interval.
 * @param value The value to write to the doorbell, shared doorbells will ignore this.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the doorbell handle is not activated, or if the driver is in reset.
 * @retval ::AIRSHIP_ENOTOPEN if the doorbell handle is not open.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_schedule_update(airship_acipc_doorbell_t doorbell, uint32_t interval_us, uint32_t leeway_us, uint16_t value);

/**
 * @brief Write a doorbell immediately, or in the minimum allowed interval.
 *
 * @note This function does not check if the doorbell is in a shared mode, or index mode.
 * If the doorbell is in shared mode, the `value` param is ignored.
 * @note This function is subject to the doorbell's minimum allowed interval, if the doorbell
 * specifies a minimum write interval, the doorbell write will be deferred.
 *
 * @param doorbell The doorbell handle to write to.
 * @param value The value to write to the doorbell, shared doorbells will ignore this.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the doorbell handle is not activated, or if the driver is in reset.
 * @retval ::AIRSHIP_ENOTOPEN if the doorbell handle is not open.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_write(airship_acipc_doorbell_t doorbell, uint16_t value);

/**
 * @brief Schedule a doorbell write update for a shared doorbell, which does not require a value.
 *
 * @note See `airship_acipc_doorbell_schedule_update` for details.
 *
 * @param doorbell The doorbell handle to write to.
 * @param interval_us The desired interval (in microseconds) to schedule the write at.
 * @param leeway_us The desired leenway (in microseconds), which provides an upper-bound for the write interval.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the doorbell handle is not activated, or if the driver is in reset.
 * @retval ::AIRSHIP_ENOTOPEN if the doorbell handle is not open.
 * @retval ::AIRSHIP_EBADARGUMENT if the doorbell handle is an index mode doorbell.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_schedule_update_shared(airship_acipc_doorbell_t doorbell, uint32_t interval_us, uint32_t leeway_us);

/**
 * @brief Write a shared doorbell immediately, or in the minimum allowed interval.
 *
 * @note See `airship_acipc_doorbell_write` for details.
 *
 * @param doorbell The doorbell handle to write to.
 * @retval ::AIRSHIP_OK if successful.
 * @retval ::AIRSHIP_ENOTREADY if the doorbell handle is not activated, or if the driver is in reset.
 * @retval ::AIRSHIP_ENOTOPEN if the doorbell handle is not open.
 * @retval ::AIRSHIP_EBADARGUMENT if the doorbell handle is an index mode doorbell.
 */
AIRSHIP_EXPORT
airship_result_t airship_acipc_doorbell_write_shared(airship_acipc_doorbell_t doorbell);

#ifdef __cplusplus
namespace airship::acipc {
/// C++ wrapper for automatic lifecycle management of boot handles.
using boot = wrapper<airship_acipc_boot, airship_acipc_boot_destroy>;
/// C++ wrapper for automatic lifecycle management of transfer ring handles.
using tr = wrapper<airship_acipc_tr, airship_acipc_tr_destroy>;
/// C++ wrapper for automatic lifecycle management of completion ring handles.
using cr = wrapper<airship_acipc_cr, airship_acipc_cr_destroy>;
/// C++ wrapper for automatic lifecycle management of shared memory region handles.
using memregion = wrapper<airship_acipc_memregion, airship_acipc_memregion_destroy>;
} // namespace airship::acipc
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__acipc_h */
