//
// Created by Daniel Barthels on 22/08/2020.
//

#ifndef VIRTUAL_PCI_H
#define VIRTUAL_PCI_H

#include <IOKit/IOMessage.h>

#define kVirtualPCIStringLengthMax 240
#define kVirtualPCIDeviceFactory "IOVirtualPCIDeviceFactory"

enum VirtualPCIRequest {
    kVirtualPCIOpenRequest,
    kVirtualPCICloseRequeset,
    kVirtualPCICreateDeviceRequest,
    kVirtualPCIRemoveDeviceRequest,
    kVirtualPCIRegisterMemoryRequest,
    kVirtualPCITriggerMSIRequest,
    kVirtualPCIAckReadRequest,

    kVirtualPCIRequestCount
};

enum VirtualPCITargetMemory : uint32_t {
    kVirtualPCIBar0,
    kVirtualPCIBar1,
    kVirtualPCIBar2,
    kVirtualPCIBar3,
    kVirtualPCIBar4,
    kVirtualPCIBar5,
    kVirtualPCIConfigSpace,

    kVirtualPCITargetMemoryCount
};

enum VirtualPCIMSI {
    kVirtualPCIMSI00, kVirtualPCIMSI01, kVirtualPCIMSI02, kVirtualPCIMSI03,
    kVirtualPCIMSI04, kVirtualPCIMSI05, kVirtualPCIMSI06, kVirtualPCIMSI07,
    kVirtualPCIMSI08, kVirtualPCIMSI09, kVirtualPCIMSI10, kVirtualPCIMSI11,
    kVirtualPCIMSI12, kVirtualPCIMSI13, kVirtualPCIMSI14, kVirtualPCIMSI15,

    kVirtualPCIMSI16, kVirtualPCIMSI17, kVirtualPCIMSI18, kVirtualPCIMSI19,
    kVirtualPCIMSI20, kVirtualPCIMSI21, kVirtualPCIMSI22, kVirtualPCIMSI23,
    kVirtualPCIMSI24, kVirtualPCIMSI25, kVirtualPCIMSI26, kVirtualPCIMSI27,
    kVirtualPCIMSI28, kVirtualPCIMSI29, kVirtualPCIMSI30, kVirtualPCIMSI31,

    kVirtualPCIMSICount
};

enum VirtualPCIMessages {
    kVirtualPCIWriteEvent = iokit_vendor_specific_msg(0x100),
    kVirtualPCIReadEvent = iokit_vendor_specific_msg(0x101),
};

struct VirtualPCICreateDeviceRequest {
    uint32_t version;
    char deviceName[kVirtualPCIStringLengthMax];
    uint32_t memorySize;
    uint32_t reserved2;
    uint32_t reserved3;
};

struct VirtualPCIRegisterMemoryRequest {
    uint32_t version;
    uint32_t type;
    uint64_t address;
    uint32_t size;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
};

struct VirtualPCITriggerMSIRequest {
    uint32_t version;
    uint32_t index;
    uint32_t reserved1;
    uint32_t reserved2;
};

struct VirtualPCIWriteEvent {
    uint16_t target; /* VirtualPCITargetMemory */
	uint16_t size;
    uint32_t offset;
	uint32_t reserved1;
    uint32_t reserved2;
};

struct VirtualPCIReadEvent {
    uint16_t target; /* VirtualPCITargetMemory */
	uint16_t size;
    uint32_t offset;
	uint32_t seq;
	uint32_t reserved1;
};

#endif  // VIRTUAL_PCI_H
