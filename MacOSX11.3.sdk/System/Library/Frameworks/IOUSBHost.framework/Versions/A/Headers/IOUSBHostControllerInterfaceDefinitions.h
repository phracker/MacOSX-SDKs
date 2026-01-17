//
//  IOUSBHostControllerInterfaceDefinitions.h
//  IOUSBHostFamily
//
//  Created by Dan Wilson on 3/5/20.
//

#ifndef IOUSBHostControllerInterfaceDefinitions_h
#define IOUSBHostControllerInterfaceDefinitions_h

#include <IOKit/usb/AppleUSBDefinitions.h>
#include <IOKit/usb/IOUSBHostFamilyDefinitions.h>

#pragma pack(push, 1)

typedef enum
{
    IOUSBHostCIUserClientVersion100 = 0
} IOUSBHostCIUserClientVersion;

typedef enum
{
    IOUSBHostCIExceptionTypeUnknown = 0,
    IOUSBHostCIExceptionTypeCapabilitiesInvalid,
    IOUSBHostCIExceptionTypeTerminated,
    IOUSBHostCIExceptionTypeCommandReadCollision,
    IOUSBHostCIExceptionTypeCommandWriteFailed,
    IOUSBHostCIExceptionTypeCommandTimeout,
    IOUSBHostCIExceptionTypeCommandFailure,
    IOUSBHostCIExceptionTypeInterruptInvalid,
    IOUSBHostCIExceptionTypeInterruptOverflow,
    IOUSBHostCIExceptionTypeDoorbellReadCollision,
    IOUSBHostCIExceptionTypeDoorbellOverflow,
    IOUSBHostCIExceptionTypeProtocolError,
    IOUSBHostCIExceptionTypeFrameUpdateError,
} IOUSBHostCIExceptionType;

typedef struct IOUSBHostCIMessage
{
    uint32_t control;
    uint32_t data0;
    uint64_t data1;
} IOUSBHostCIMessage;

// Common fields for messages
enum
{
    IOUSBHostCIMessageControlType                  = IOUSBBitRange(0, 5),
    IOUSBHostCIMessageControlTypePhase             = IOUSBBitRangePhase(0, 5),
    IOUSBHostCIMessageControlStatus                = IOUSBBitRange(8, 11),
    IOUSBHostCIMessageControlStatusPhase           = IOUSBBitRangePhase(8, 11),
    IOUSBHostCIMessageControlNoResponse            = IOUSBBit(14),
    IOUSBHostCIMessageControlValid                 = IOUSBBit(15),
};

// PortEvent
enum
{
    IOUSBHostCIPortEventMessageData0PortNumber         = IOUSBBitRange(0, 3),
    IOUSBHostCIPortEventMessageData0PortNumberPhase    = IOUSBBitRangePhase(0, 3)
};

// Capabilities
enum
{
    IOUSBHostCICapabilitiesMessageControlPortCount                     = IOUSBBitRange(16, 19),
    IOUSBHostCICapabilitiesMessageControlPortCountPhase                = IOUSBBitRangePhase(16, 19),
    
    IOUSBHostCICapabilitiesMessageData0CommandTimeoutThreshold         = IOUSBBitRange(0, 1),
    IOUSBHostCICapabilitiesMessageData0CommandTimeoutThresholdPhase    = IOUSBBitRangePhase(0, 1),
    IOUSBHostCICapabilitiesMessageData0ConnectionLatency               = IOUSBBitRange(4, 7),
    IOUSBHostCICapabilitiesMessageData0ConnectionLatencyPhase          = IOUSBBitRangePhase(4, 7)
};

// PortCapabilities
enum
{
    IOUSBHostCIPortCapabilitiesMessageControlPortNumber                 = IOUSBBitRange(16, 19),
    IOUSBHostCIPortCapabilitiesMessageControlPortNumberPhase            = IOUSBBitRangePhase(16, 19),
    IOUSBHostCIPortCapabilitiesMessageControlInternalConnector          = IOUSBBit(23),
    IOUSBHostCIPortCapabilitiesMessageControlConnectorType              = IOUSBBitRange(24, 31),
    IOUSBHostCIPortCapabilitiesMessageControlConnectorTypePhase         = IOUSBBitRangePhase(24, 31),

    IOUSBHostCIPortCapabilitiesMessageData0MaxPower                     = IOUSBBitRange(0, 7),
    IOUSBHostCIPortCapabilitiesMessageData0MaxPowerPhase                = IOUSBBitRangePhase(0, 7),
};

// Common fields for command messages
enum
{
    IOUSBHostCICommandMessageControlStatus             = IOUSBHostCIMessageControlStatus,
    IOUSBHostCICommandMessageControlStatusPhase        = IOUSBHostCIMessageControlStatusPhase,
    
    IOUSBHostCICommandMessageData0RootPort             = IOUSBBitRange(0, 3),
    IOUSBHostCICommandMessageData0RootPortPhase        = IOUSBBitRangePhase(0, 3),
    
    IOUSBHostCICommandMessageData0DeviceAddress        = IOUSBBitRange(0, 7),
    IOUSBHostCICommandMessageData0DeviceAddressPhase   = IOUSBBitRangePhase(0, 7),
    IOUSBHostCICommandMessageData0EndpointAddress      = IOUSBBitRange(8, 15),
    IOUSBHostCICommandMessageData0EndpointAddressPhase = IOUSBBitRangePhase(8, 15),
    IOUSBHostCICommandMessageData0StreamID             = IOUSBBitRange(16, 31),
    IOUSBHostCICommandMessageData0StreamIDPhase        = IOUSBBitRangePhase(16, 31)
};

// PortStatus
enum
{
    IOUSBHostCIPortStatusCommandData1Powered                               = IOUSBBit(0),
    IOUSBHostCIPortStatusCommandData1Overcurrent                           = IOUSBBit(1),
    IOUSBHostCIPortStatusCommandData1Connected                             = IOUSBBit(2),
    IOUSBHostCIPortStatusCommandData1LinkState                             = IOUSBBitRange64(4, 7),
    IOUSBHostCIPortStatusCommandData1LinkStatePhase                        = IOUSBBitRangePhase(4, 7),
    IOUSBHostCIPortStatusCommandData1Speed                                 = IOUSBBitRange64(8, 10),
    IOUSBHostCIPortStatusCommandData1SpeedPhase                            = IOUSBBitRangePhase(8, 10),
    IOUSBHostCIPortStatusCommandData1OvercurrentChange                     = IOUSBBit(17),
    IOUSBHostCIPortStatusCommandData1ConnectChange                         = IOUSBBit(18),
    IOUSBHostCIPortStatusCommandData1LinkStateChange                       = IOUSBBit(20),
    
    IOUSBHostCIPortStatusCommandData1ChangeMask = IOUSBHostCIPortStatusCommandData1LinkStateChange | IOUSBHostCIPortStatusCommandData1ConnectChange | IOUSBHostCIPortStatusCommandData1OvercurrentChange,
};

// DeviceCreate
enum
{
    IOUSBHostCIDeviceCreateCommandData0RootPort                            = IOUSBBitRange(0, 3),
    IOUSBHostCIDeviceCreateCommandData0RootPortPhase                       = IOUSBBitRangePhase(0, 3),
    IOUSBHostCIDeviceCreateCommandData0Route                               = IOUSBBitRange(4, 23),
    IOUSBHostCIDeviceCreateCommandData0RoutePhase                          = IOUSBBitRangePhase(4, 23),
    IOUSBHostCIDeviceCreateCommandData1DeviceAddress                       = IOUSBBitRange64(0, 7),
    IOUSBHostCIDeviceCreateCommandData1DeviceAddressPhase                  = IOUSBBitRangePhase(0, 7)
};

// EndpointCreate
enum
{
    IOUSBHostCIEndpointCreateCommandData1Descriptor                        = IOUSBBitRange64(0, 63),
    IOUSBHostCIEndpointCreateCommandData1DescriptorPhase                   = IOUSBBitRangePhase(0, 63)
};

// EndpointReset
enum
{
    IOUSBHostCIEndpointResetCommandData1ClearState                         = IOUSBBit(0)
};

// EndpointSetNextTransfer
enum
{
    IOUSBHostCIEndpointSetNextTransferCommandData1Address                  = IOUSBBitRange64(0, 63),
    IOUSBHostCIEndpointSetNextTransferCommandData1AddressPhase             = IOUSBBitRangePhase(0, 63)
};

// SetupTransfer
enum
{
    IOUSBHostCISetupTransferData1bmRequestType                              = IOUSBBitRange64(0, 7),
    IOUSBHostCISetupTransferData1bmRequestTypePhase                         = IOUSBBitRangePhase(0, 7),
    IOUSBHostCISetupTransferData1bRequest                                   = IOUSBBitRange64(8, 15),
    IOUSBHostCISetupTransferData1bRequestPhase                              = IOUSBBitRangePhase(8, 15),
    IOUSBHostCISetupTransferData1wValue                                     = IOUSBBitRange64(16, 31),
    IOUSBHostCISetupTransferData1wValuePhase                                = IOUSBBitRangePhase(16, 31),
    IOUSBHostCISetupTransferData1wIndex                                     = IOUSBBitRange64(32, 47),
    IOUSBHostCISetupTransferData1wIndexPhase                                = IOUSBBitRangePhase(32, 47),
    IOUSBHostCISetupTransferData1wLength                                    = IOUSBBitRange64(48, 63),
    IOUSBHostCISetupTransferData1wLengthPhase                               = IOUSBBitRangePhase(48, 63)
};

// NormalTransfer
enum
{
    IOUSBHostCINormalTransferData0Length                                    = IOUSBBitRange(0, 27),
    IOUSBHostCINormalTransferData0LengthPhase                               = IOUSBBitRangePhase(0, 27),
};

// IsochronousTransfer
enum
{
    IOUSBHostCIIsochronousTransferControlFrameNumber                        = IOUSBBitRange(16, 23),
    IOUSBHostCIIsochronousTransferControlFrameNumberPhase                   = IOUSBBitRangePhase(16, 23),
    IOUSBHostCIIsochronousTransferControlASAP                               = IOUSBBit(24),
    IOUSBHostCIIsochronousTransferData0Length                               = IOUSBHostCINormalTransferData0Length,
    IOUSBHostCIIsochronousTransferData0LengthPhase                          = IOUSBHostCINormalTransferData0LengthPhase,
};

// TransferCompletion
enum
{
    IOUSBHostCITransferCompletionMessageControlStatus                      = IOUSBHostCIMessageControlStatus,
    IOUSBHostCITransferCompletionMessageControlStatusPhase                 = IOUSBHostCIMessageControlStatusPhase,
    IOUSBHostCITransferCompletionMessageControlDeviceAddress               = IOUSBBitRange(16, 23),
    IOUSBHostCITransferCompletionMessageControlDeviceAddressPhase          = IOUSBBitRangePhase(16, 23),
    IOUSBHostCITransferCompletionMessageControlEndpointAddress             = IOUSBBitRange(24, 31),
    IOUSBHostCITransferCompletionMessageControlEndpointAddressPhase        = IOUSBBitRangePhase(24, 31),
    
    IOUSBHostCITransferCompletionMessageData0TransferLength                = IOUSBBitRange(0, 27),
    IOUSBHostCITransferCompletionMessageData0TransferLengthPhase           = IOUSBBitRangePhase(0, 27),
    
    IOUSBHostCITransferCompletionMessageData1TransferStructure             = IOUSBBitRange64(0, 63),
    IOUSBHostCITransferCompletionMessageData1TransferStructurePhase        = IOUSBBitRangePhase(0, 63)
};

typedef enum
{
    IOUSBHostCIMessageTypeControllerCapabilities    = 0x0,
    IOUSBHostCIMessageTypePortCapabilities,
    
    IOUSBHostCIMessageTypePortEvent                 = 0x8,
    IOUSBHostCIMessageTypeFrameNumberUpdate,
    IOUSBHostCIMessageTypeFrameTimestampUpdate,

    IOUSBHostCIMessageTypeCommandMin                = 0x10,
    
    IOUSBHostCIMessageTypeControllerPowerOn         = 0x10,
    IOUSBHostCIMessageTypeControllerPowerOff,
    IOUSBHostCIMessageTypeControllerStart,
    IOUSBHostCIMessageTypeControllerPause,
    IOUSBHostCIMessageTypeControllerFrameNumber,
    
    IOUSBHostCIMessageTypePortPowerOn               = 0x18,
    IOUSBHostCIMessageTypePortPowerOff,
    IOUSBHostCIMessageTypePortResume,
    IOUSBHostCIMessageTypePortSuspend,
    IOUSBHostCIMessageTypePortReset,
    IOUSBHostCIMessageTypePortDisable,
    IOUSBHostCIMessageTypePortStatus,
    
    IOUSBHostCIMessageTypeDeviceCreate              = 0x20,
    IOUSBHostCIMessageTypeDeviceDestroy,
    IOUSBHostCIMessageTypeDeviceStart,
    IOUSBHostCIMessageTypeDevicePause,
    IOUSBHostCIMessageTypeDeviceUpdate,
    
    IOUSBHostCIMessageTypeEndpointCreate            = 0x28,
    IOUSBHostCIMessageTypeEndpointDestroy,
    IOUSBHostCIMessageTypeEndpoint_reserved_,
    IOUSBHostCIMessageTypeEndpointPause,
    IOUSBHostCIMessageTypeEndpointUpdate,
    IOUSBHostCIMessageTypeEndpointReset,
    IOUSBHostCIMessageTypeEndpointSetNextTransfer,

    IOUSBHostCIMessageTypeCommandMax                = 0x37,
    
    IOUSBHostCIMessageTypeSetupTransfer             = 0x38,
    IOUSBHostCIMessageTypeNormalTransfer,
    IOUSBHostCIMessageTypeStatusTransfer,
    IOUSBHostCIMessageTypeIsochronousTransfer,
    IOUSBHostCIMessageTypeLink,
    IOUSBHostCIMessageTypeTransferComplete,
} IOUSBHostCIMessageType;

typedef enum
{
    IOUSBHostCIMessageStatusReserved               = 0, // Reserved, do not use this value
    IOUSBHostCIMessageStatusSuccess,                    // The operation was successful
    IOUSBHostCIMessageStatusOffline,                    // The request cannot be completed because the controller is unreachable
    IOUSBHostCIMessageStatusNotPermitted,               // The request cannot be performed in the current state
    IOUSBHostCIMessageStatusBadArgument,                // The request did not pass validation checks
    IOUSBHostCIMessageStatusTimeout,                    // The request did not complete in the time expected
    IOUSBHostCIMessageStatusNoResources,                // The request cannot be completed due to resource limitations
    IOUSBHostCIMessageStatusEndpointStopped,            // The transfer generated an event due to an EndpointStop command, not due to a completed transfer
    IOUSBHostCIMessageStatusProtocolError,              // The transfer completed due to a protocol error
    IOUSBHostCIMessageStatusTransactionError,           // The transfer completed due to a USB transaction error
    IOUSBHostCIMessageStatusOverrunError,               // The transfer completed due to a USB babble (overrun) error
    IOUSBHostCIMessageStatusStallError,                 // The transfer completed due to a STALL handshake from the device
    IOUSBHostCIMessageStatusMissedServiceError,         // The isochronous transfer was not able to be serviced in the specified frame number
    IOUSBHostCIMessageStatusError                       // Unspecified error
} IOUSBHostCIMessageStatus;

typedef enum
{
     IOUSBHostCIDeviceSpeedNone         = kIOUSBHostConnectionSpeedNone,
     IOUSBHostCIDeviceSpeedFull         = kIOUSBHostConnectionSpeedFull,
     IOUSBHostCIDeviceSpeedLow          = kIOUSBHostConnectionSpeedLow,
     IOUSBHostCIDeviceSpeedHigh         = kIOUSBHostConnectionSpeedHigh,
     IOUSBHostCIDeviceSpeedSuper        = kIOUSBHostConnectionSpeedSuper,
     IOUSBHostCIDeviceSpeedSuperPlus    = kIOUSBHostConnectionSpeedSuperPlus,
     IOUSBHostCIDeviceSpeedSuperPlusBy2 = kIOUSBHostConnectionSpeedSuperPlusBy2
} IOUSBHostCIDeviceSpeed;

typedef enum
{
    IOUSBHostCIControllerStateOff       = 0,
    IOUSBHostCIControllerStatePaused,
    IOUSBHostCIControllerStateActive
} IOUSBHostCIControllerState;

typedef enum
{
    IOUSBHostCIPortStateOff             = 0,
    IOUSBHostCIPortStatePowered,
    IOUSBHostCIPortStateSuspended,
    IOUSBHostCIPortStateActive
} IOUSBHostCIPortState;

typedef enum
{
    IOUSBHostCILinkStateU0              = 0,
    IOUSBHostCILinkStateU1              = 1,
    IOUSBHostCILinkStateU2              = 2,
    IOUSBHostCILinkStateU3              = 3,
    IOUSBHostCILinkStateDisabled        = 4,
    IOUSBHostCILinkStateRxDetect        = 5,
    IOUSBHostCILinkStateInactive        = 6,
    IOUSBHostCILinkStatePolling         = 7,
    IOUSBHostCILinkStateRecovery        = 8,
    IOUSBHostCILinkStateReset           = 9,
    IOUSBHostCILinkStateCompliance      = 10,
    IOUSBHostCILinkStateTest            = 11,
    IOUSBHostCILinkStateResume          = 15,
    
} IOUSBHostCILinkState;

typedef enum
{
    IOUSBHostCIDeviceStateDestroyed = 0,
    IOUSBHostCIDeviceStatePaused,
    IOUSBHostCIDeviceStateActive
} IOUSBHostCIDeviceState;

typedef enum
{
    IOUSBHostCIEndpointStateDestroyed = 0,
    IOUSBHostCIEndpointStateHalted,
    IOUSBHostCIEndpointStatePaused,
    IOUSBHostCIEndpointStateActive,
} IOUSBHostCIEndpointState;

typedef uint32_t IOUSBHostCIDoorbell;

enum
{
    IOUSBHostCIDoorbellDeviceAddress               = IOUSBBitRange(0, 7),
    IOUSBHostCIDoorbellDeviceAddressPhase          = IOUSBBitRangePhase(0, 7),
    IOUSBHostCIDoorbellEndpointAddress             = IOUSBBitRange(8, 15),
    IOUSBHostCIDoorbellEndpointAddressPhase        = IOUSBBitRangePhase(8, 15),
    IOUSBHostCIDoorbellStreamID                    = IOUSBBitRange(16, 31),
    IOUSBHostCIDoorbellStreamIDPhase               = IOUSBBitRangePhase(16, 31)
};

typedef uint32_t IOUSBHostCIPortStatus;

enum
{
    IOUSBHostCIPortStatusPowered                    = IOUSBBit(0),
    IOUSBHostCIPortStatusOvercurrent                = IOUSBBit(1),
    IOUSBHostCIPortStatusConnected                  = IOUSBBit(2),
    IOUSBHostCIPortStatusLinkState                  = IOUSBBitRange64(4, 7),
    IOUSBHostCIPortStatusLinkStatePhase             = IOUSBBitRangePhase(4, 7),
    IOUSBHostCIPortStatusSpeed                      = IOUSBBitRange64(8, 10),
    IOUSBHostCIPortStatusSpeedPhase                 = IOUSBBitRangePhase(8, 10),
    IOUSBHostCIPortStatusOvercurrentChange          = IOUSBBit(17),
    IOUSBHostCIPortStatusConnectChange              = IOUSBBit(18),
    IOUSBHostCIPortStatusLinkStateChange            = IOUSBBit(20),
    
    IOUSBHostCIPortStatusChangeMask = IOUSBHostCIPortStatusLinkStateChange | IOUSBHostCIPortStatusConnectChange | IOUSBHostCIPortStatusOvercurrentChange,
};

#pragma pack(pop)

#endif /* IOUSBHostControllerInterfaceDefinitions_h */
