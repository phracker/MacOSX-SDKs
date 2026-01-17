//
//  AirshipDaleBasebandPublic.h
//  Airship
//
//  Created by Soonseop Yang on 5/11/23.
//

#ifndef airship__DaleBasebandKext__AirshipDaleBasebandPublic_h
#define airship__DaleBasebandKext__AirshipDaleBasebandPublic_h

#include <IOKit/IOMessage.h>


#define kAirshipDaleBasebandControl               "AirshipDaleBasebandControl"
#define kAirshipDaleBasebandControlExecStage      "AirshipDaleBasebandControlExecStage"

#define kAirshipDaleBasebandControlExecStageNODEV "NODEV"
#define kAirshipDaleBasebandControlExecStageROM   "ROM"
#define kAirshipDaleBasebandControlExecStagePL    "PL"
#define kAirshipDaleBasebandControlExecStageLK    "LK"
#define kAirshipDaleBasebandControlExecStageMD    "MD"
#define kAirshipDaleBasebandControlExecStageCCCI  "CCCI"
#define kAirshipDaleBasebandControlExecStageOS    "OS"


#define kAirshipDaleBasebandControlInterfaceUser          "AirshipDaleBasebandControlInterfaceUser"
#define kAirshipDaleBasebandControlInterfaceProtocol      "AirshipDaleBasebandControlInterfaceProtocol"
#define kAirshipDaleBasebandControlInterfaceTxMTU         "AirshipDaleBasebandControlInterfaceTxMTU"
#define kAirshipDaleBasebandControlInterfaceRxMTU         "AirshipDaleBasebandControlInterfaceRxMTU"
#define kAirshipDaleBasebandControlInterfaceTxChannelSize "AirshipDaleBasebandControlInterfaceTxChannelSize"
#define kAirshipDaleBasebandControlInterfaceRxChannelSize "AirshipDaleBasebandControlInterfaceRxChannelSize"


#define kAirshipDaleBasebandControlROMBoot   "rom_boot"   /* handshake and image download */
#define kAirshipDaleBasebandControlROMLog    "rom_log"    /* boot log */

#define kAirshipDaleBasebandControlPLBoot    "pl_boot"    /* image download */
#define kAirshipDaleBasebandControlPLLog     "pl_log"     /* boot log */

#define kAirshipDaleBasebandControlLKDump    "lk_dump"    /* AEE memory dump */
#define kAirshipDaleBasebandControlLKLog     "lk_log"

#define kAirshipDaleBasebandControlMDCcci    "md_ccci"    /* CCCI control path */

#define kAirshipDaleBasebandControlOSFep     "os_fep"     /* FEP for NVRAM/MCF */
#define kAirshipDaleBasebandControlOSLog     "os_log"     /* modem log */
#define kAirshipDaleBasebandControlOSMipc    "os_mipc"    /* telephony MIPC */
#define kAirshipDaleBasebandControlOSFac     "os_fac"     /* factory MIPC */
#define kAirshipDaleBasebandControlOSAt      "os_at"      /* at command */
#define kAirshipDaleBasebandControlOSPass    "os_pass"    /* paththough */
#define kAirshipDaleBasebandControlOSIqTrace "os_iqtrace" /* IQ Trace */
#define kAirshipDaleBasebandControlOSFrc     "os_frc"     /* FRC */
#define kAirshipDaleBasebandControlOSNWClock "os_nwclock" /* NW clock */


enum
{
    kAirshipDaleBasebandControlUserClientOpen,
    kAirshipDaleBasebandControlUserClientClose,
    kAirshipDaleBasebandControlUserClientMax
};

enum
{
    kAirshipDaleBasebandControlInterfaceUserClientOpen,
    kAirshipDaleBasebandControlInterfaceUserClientClose,
    kAirshipDaleBasebandControlInterfaceUserClientRead,
    kAirshipDaleBasebandControlInterfaceUserClientReadAsync,
    kAirshipDaleBasebandControlInterfaceUserClientWrite,
    kAirshipDaleBasebandControlInterfaceUserClientWriteAsync,
    kAirshipDaleBasebandControlInterfaceUserClientGetDeviceTimeAsync,
    kAirshipDaleBasebandControlInterfaceUserClientMax
};

enum
{
    kAirshipDaleBasebandTraceUserClientOpen,
    kAirshipDaleBasebandTraceUserClientClose,
    kAirshipDaleBasebandTraceUserClientRegisterTraceBuffer,
    kAirshipDaleBasebandTraceUserClientFlushTraceBuffers,
    kAirshipDaleBasebandTraceUserClientGetTraceInfo,
    kAirshipDaleBasebandTraceUserClientMax
};

struct AirshipDaleBasebandTraceInfo
{
    uint32_t version;
    uint32_t trace_code_count;
    uint32_t trace_code_size;
    uint32_t min_trace_buffer_size;
    uint32_t max_trace_buffer_size;
    uint32_t snapshot_buffer_size;
    uint32_t max_trace_buffers_in_flight;
};

enum
{
    kAirshipDaleBasebandControlErrorMsg = iokit_vendor_specific_msg(0x100),
    kAirshipDaleBasebandControlInterfaceErrorMsg = iokit_vendor_specific_msg(0x101)
};

typedef uint32_t AirshipDaleBasebandError;

struct AirshipDaleBasebandErrorInfo
{
    AirshipDaleBasebandError error;
    uint64_t                 param1;
    uint64_t                 param2;
};

typedef struct
{
    uint32_t seq;
    uint32_t duration;
    uint64_t ap_time;
    uint64_t frc_time;
    uint64_t host_begin_abs_time;
    uint64_t host_begin_continuous_time;
} AirshipDaleBasebandDeviceTimeMeasurement;

enum
{
    kDALEIPCBBTimeDomainGNSS,
    kDALEIPCBBTimeDomainNetwork,
};

enum
{
    // boot errors
    kAirshipDaleBasebandErrorInvalidBootStage,
    kAirshipDaleBasebandErrorCreateInterfaceFailure,

    // CCCI handshake errors
    kAirshipDaleBasebandErrorCCCIHandshakeTimeout,
    kAirshipDaleBasebandErrorCCCIHandshakeError,
    kAirshipDaleBasebandErrorCCCIInvalidMessage,
    kAirshipDaleBasebandErrorCCCIInternalError,

    // dataplane errors
    kAirshipDaleBasebandErrorTxConsumeFailure,
    kAirshipDaleBasebandErrorRxConsumeFailure,
    kAirshipDaleBasebandErrorTxEnqueueFailure,
    kAirshipDaleBasebandErrorRxEnqueueFailure,
    kAirshipDaleBasebandErrorTxGetCompletionFailure,
    kAirshipDaleBasebandErrorRxGetCompletionFailure,
    // TODO: add more error type

    // airship core driver errors
    kAirshipDaleBasebandErrorIpcErrorOccurred,
    kAirshipDaleBasebandErrorIpcSetTransportFailed,
    kAirshipDaleBasebandErrorIpcPowerOffTimedOut,
    kAirshipDaleBasebandErrorIpcPowerOnTimedOut,
    kAirshipDaleBasebandErrorDevicePowerOffTimedOut,
    kAirshipDaleBasebandDevicePowerOnTimedOut,

    // pcie errors
    kAirshipDaleBasebandErrorPortEnableFailure,
    kAirshipDaleBasebandErrorDARTFailure,
    kAirshipDaleBasebandErrorPCIBadRequest,
    kAirshipDaleBasebandErrorPCIAER,
    kAirshipDaleBasebandErrorPCICplTimeout,
    kAirshipDaleBasebandErrorPCILinkDown,
    kAirshipDaleBasebandErrorPCILinkResumeFail,

    kAirshipDaleBasebandErrorMax
};

#define kAirshipDaleBasebandDataPlane                  "AirshipDaleBasebandDataPlane"
#define kAirshipDaleBasebandNetworkInterfaceNamePrefix "pdp_ip"

#endif /* airship__DaleBasebandKext__AirshipDaleBasebandPublic_h */
