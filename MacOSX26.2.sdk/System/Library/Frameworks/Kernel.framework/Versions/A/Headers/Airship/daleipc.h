//
//  daleipc.h
//  Airship
//
//  Created by Jason McElrath on 4/5/23.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__daleipc_h
#define airship__core__api__daleipc_h

/**
 * @file daleipc.h
 * @brief Public DaleIPC interface.
 * @namespace airship::daleipc
 * @brief Public DaleIPC interface.
 */

#include <Airship/base.h>
#include <Airship/buffer.h>

#include <IOKit/skywalk/IOSkywalkPacket.h>

AIRSHIP_ASSUME_NONNULL_BEGIN

typedef enum daleipc_exec_stage
{
    DALEIPC_EXEC_STAGE_NODEV,
    DALEIPC_EXEC_STAGE_ROM,
    DALEIPC_EXEC_STAGE_PL,
    DALEIPC_EXEC_STAGE_LK,
    DALEIPC_EXEC_STAGE_MD,
    DALEIPC_EXEC_STAGE_CCCI,
    DALEIPC_EXEC_STAGE_OS,
    DALEIPC_EXEC_STAGE_INVALID,

} daleipc_exec_stage_t;


typedef struct daleipc_channel_controller *daleipc_channel_controller_t;
typedef struct daleipc_uplink_controller *daleipc_uplink_controller_t;
typedef struct daleipc_downlink_controller *daleipc_downlink_controller_t;
typedef struct daleipc_device_controller *daleipc_device_controller_t;
typedef struct daleipc_network_clock_controller *daleipc_network_clock_controller_t;


/* channel controller api */

typedef enum airship_daleipc_channel_sync_operation
{
    AIRSHIP_DALEIPC_CHANNEL_SYNC_FETCH_COMPLETIONS = (1 << 0),
    AIRSHIP_DALEIPC_UPLINK_SYNC_FETCH_COMPLETIONS = (1 << 1),
    AIRSHIP_DALEIPC_DOWNLINK_SYNC_FETCH_COMPLETIONS = (1 << 2),
    AIRSHIP_DALEIPC_NETWORK_CLOCK_UPDATES = (1 << 3),
} airship_daleipc_channel_sync_operation_t;

typedef enum airship_daleipc_channel_state
{
    AIRSHIP_DALEIPC_STATE_UNAVAILABLE,
    AIRSHIP_DALEIPC_STATE_AVAILABLE,
    AIRSHIP_DALEIPC_STATE_STARTED,
    AIRSHIP_DALEIPC_STATE_STOPPED,
    AIRSHIP_DALEIPC_STATE_DEAD
} airship_daleipc_channel_state_t;

typedef struct airship_daleipc_channel_transfer_completion
{
    uint32_t size;
    uint16_t tag;
} airship_daleipc_channel_transfer_completion_t;

typedef struct airship_daleipc_uplink_packet_completion
{
    uint32_t size;
    uint16_t tag;
    uint16_t channel_id;
} airship_daleipc_uplink_packet_completion_t;

typedef struct airship_daleipc_downlink_packet_completion
{
    uint16_t tag;
    uint16_t data_length;
    uint16_t data_offset;
    uint16_t channel_id:8;
    uint16_t checksum:2;
    uint16_t protocol:2;
    uint16_t drop:1;
    uint16_t ignore:1;
    uint16_t error:1;
    uint16_t wake_packet:1;
} airship_daleipc_downlink_packet_completion_t;

typedef enum airship_daleipc_ipc_error_flag
{
    AIRSHIP_DALEIPC_IPC_ERROR_CHANNEL_SYNC_FAILURE = (1 << 0),
    AIRSHIP_DALEIPC_IPC_ERROR_CLDMA_LINK_ERROR = (1 << 1),
    AIRSHIP_DALEIPC_IPC_ERROR_DEVICE_SLEEP_FAILURE = (1 << 2),
    AIRSHIP_DALEIPC_IPC_ERROR_DEVICE_SLEEP_EXIT_TIMEOUT = (1 << 3),
    AIRSHIP_DALEIPC_IPC_ERROR_DOWNLINK_BUFFER_COUNT_LENGTH_ERROR = (1 << 4),
    AIRSHIP_DALEIPC_IPC_ERROR_IO_TIMEOUT = (1 << 5),
    AIRSHIP_DALEIPC_IPC_ERROR_CLDMA_RX_ERROR = (1 << 6),
    AIRSHIP_DALEIPC_IPC_ERROR_CLDMA_TX_ERROR = (1 << 7),
    AIRSHIP_DALEIPC_IPC_ERROR_SYSTEM_FAILURE = (1 << 8),
    AIRSHIP_DALEIPC_IPC_ERROR_HOST_SLEEP_FAILURE = (1 << 9),
    AIRSHIP_DALEIPC_IPC_ERROR_HOST_WAKE_FAILURE = (1 << 10),
    AIRSHIP_DALEIPC_IPC_ERROR_CHANNEL_UPDATE_FAILURE = (1 << 11),
    AIRSHIP_DALEIPC_IPC_ERROR_UPLINK_UPDATE_FAILURE = (1 << 12),
    AIRSHIP_DALEIPC_IPC_ERROR_CHANNEL_QUIESCE_FAILURE = (1 << 13),
    AIRSHIP_DALEIPC_IPC_ERROR_DOWNLINK_UPDATE_FAILURE = (1 << 14),
    /* Add support for more error flags */
} airship_daleipc_ipc_error_flag_t;

/**
 * @brief Retrieve a textual description for a Dale IPC error code.
 *
 * The contents of the strings returned by this function are subject to change
 * without notice.
 *
 * @param error A Dale IPC error code.
 * @returns A string representing the error.
 */
AIRSHIP_EXPORT
const char *airship_daleipc_get_ipc_error_description(uint32_t error);

AIRSHIP_EXPORT
daleipc_channel_controller_t airship_daleipc_create_channel_controller(airship_client_t client, airship_string_t channel_name);

AIRSHIP_EXPORT
void airship_daleipc_channel_controller_destroy(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_channel_controller_activate(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
airship_monitor_t airship_daleipc_channel_controller_create_sync_monitor(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
airship_monitor_t airship_daleipc_channel_controller_create_state_monitor(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
uint32_t airship_daleipc_channel_controller_get_mtu_size(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
uint32_t airship_daleipc_channel_controller_get_channel_size(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_channel_controller_get_free_space(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
airship_monitor_t airship_daleipc_channel_controller_create_free_space_monitor(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_channel_controller_enqueue_transfer(daleipc_channel_controller_t channel_ctrl,
                                                                     airship_buffer_t buffer,
                                                                     uint32_t offset,
                                                                     uint32_t length,
                                                                     uint16_t tag);

AIRSHIP_EXPORT
void airship_daleipc_channel_controller_sync(daleipc_channel_controller_t channel_ctrl, uint32_t flags);

AIRSHIP_EXPORT
uint16_t airship_daleipc_channel_controller_get_completed_transfer_count(daleipc_channel_controller_t channel_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_channel_controller_get_transfer_completion(daleipc_channel_controller_t channel_ctrl,
                                                                            uint16_t index,
                                                                            airship_daleipc_channel_transfer_completion_t *out_completion);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_channel_controller_consume_transfers(daleipc_channel_controller_t channel_ctrl, uint16_t count);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_channel_controller_synthesize_reset_completions(daleipc_channel_controller_t channel_ctrl);


/* uplink controller api */

AIRSHIP_EXPORT
daleipc_uplink_controller_t airship_daleipc_create_uplink_controller(airship_client_t client, airship_string_t channel_name);

AIRSHIP_EXPORT
void airship_daleipc_uplink_controller_destroy(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_uplink_controller_activate(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
airship_monitor_t airship_daleipc_uplink_controller_create_sync_monitor(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_uplink_controller_get_free_space(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_uplink_controller_enqueue_iosk_packet(daleipc_uplink_controller_t uplink_ctrl,
                                                                     IOSkywalkPacket *extbuf,
                                                                     uint32_t extbuf_offset,
                                                                     uint32_t length,
                                                                     uint16_t tag,
                                                                     uint16_t channel_id);

AIRSHIP_EXPORT
void airship_daleipc_uplink_controller_sync(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_uplink_controller_get_completed_packet_count(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_uplink_controller_get_packet_completion(daleipc_uplink_controller_t uplink_ctrl,
                                                                            uint16_t index,
                                                                            airship_daleipc_uplink_packet_completion_t *out_completion);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_uplink_controller_consume_packets(daleipc_uplink_controller_t uplink_ctrl, uint16_t count);

AIRSHIP_EXPORT
void airship_daleipc_uplink_controller_synthesize_reset_completions(daleipc_uplink_controller_t uplink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_uplink_controller_get_channel_size(daleipc_uplink_controller_t uplink_ctrl);

/* downlink controller api */

AIRSHIP_EXPORT
daleipc_downlink_controller_t airship_daleipc_create_downlink_controller(airship_client_t client, airship_string_t channel_name);

AIRSHIP_EXPORT
void airship_daleipc_downlink_controller_destroy(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_downlink_controller_activate(daleipc_downlink_controller_t downlink_ctrl, uint32_t buffer_size);

AIRSHIP_EXPORT
airship_monitor_t airship_daleipc_downlink_controller_create_sync_monitor(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_downlink_controller_get_free_space(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_downlink_controller_enqueue_iosk_packet_buffer(daleipc_downlink_controller_t downlink_ctrl,
                                                                     IOSkywalkPacket *buffer,
                                                                     uint16_t tag);

AIRSHIP_EXPORT
void airship_daleipc_downlink_controller_sync(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_downlink_controller_get_completed_packet_count(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_downlink_controller_get_packet_completion(daleipc_downlink_controller_t downlink_ctrl,
                                                                            uint16_t index,
                                                                            airship_daleipc_downlink_packet_completion_t *out_completion);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_downlink_controller_consume_packets(daleipc_downlink_controller_t downlink_ctrl, uint16_t count);

AIRSHIP_EXPORT
void airship_daleipc_downlink_controller_synthesize_reset_completions(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_downlink_controller_get_channel_size(daleipc_downlink_controller_t downlink_ctrl);

AIRSHIP_EXPORT
uint16_t airship_daleipc_downlink_controller_get_min_buffer_count(daleipc_downlink_controller_t downlink_ctrl);

/* device controller api */

AIRSHIP_EXPORT
daleipc_device_controller_t airship_daleipc_create_device_controller(airship_client_t client, airship_string_t channel_name);

AIRSHIP_EXPORT
void airship_daleipc_device_controller_destroy(daleipc_device_controller_t device_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_device_controller_activate(daleipc_device_controller_t device_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_device_controller_get_device_timings(daleipc_device_controller_t device_ctrl, uint64_t *frc, uint64_t *ap, uint64_t *host_begin_abs, uint64_t *host_end_abs);

/* netwprk clock controller api */

AIRSHIP_EXPORT
daleipc_network_clock_controller_t airship_daleipc_create_network_clock_controller(airship_client_t client, airship_string_t channel_name);

AIRSHIP_EXPORT
void airship_daleipc_network_clock_controller_destroy(daleipc_network_clock_controller_t network_clock_ctrl);

AIRSHIP_EXPORT
airship_result_t airship_daleipc_network_clock_controller_activate(daleipc_network_clock_controller_t network_clock_ctrl);

AIRSHIP_EXPORT
airship_monitor_t airship_daleipc_network_clock_controller_create_clock_monitor(daleipc_network_clock_controller_t network_clock_ctrl);

AIRSHIP_EXPORT
airship_result_t
airship_daleipc_network_clock_controller_get_network_clock_updates(daleipc_network_clock_controller_t network_clock_ctrl, uint64_t *frc, uint64_t *ap, uint64_t *host_begin_abs, uint64_t *host_end_abs);

AIRSHIP_EXPORT
void
airship_daleipc_network_clock_controller_reset(daleipc_network_clock_controller_t network_clock_ctrl);

#ifdef __cplusplus
namespace airship::daleipc {} // namespace airship::daleipc
#endif

AIRSHIP_ASSUME_NONNULL_END

#endif /* airship__core__api__daleipc_h */
