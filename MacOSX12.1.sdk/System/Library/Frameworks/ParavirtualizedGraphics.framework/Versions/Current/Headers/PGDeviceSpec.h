//
//  PGDeviceSpec.h
//  ParavirtualizedGraphics
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#ifndef PGDeviceSpec_H
#define PGDeviceSpec_H

/*
 The AppleParavirtGPU is presented to the guest as a PCI device.

 Memory BARS:
 
 PG_PCI_BAR_MMIO:
  - Should be sized to 16KB
  - MSI interrupt vectors in first 0x1000 bytes
  - MMIO mapped registers starting at 0x1000 from the BAR address
     - Reads and writes should be mapped to [hostDevice mmioReadAtOffset:], [hostDevice mmioWriteAtOffset:value:]
     - All reads/writes are 4 byte aligned and 4 byte size
 */

#define PG_PCI_BAR_MMIO 0

#define PG_PCI_MAX_MSI_VECTORS 1

#define PG_PCI_VENDOR_ID 0x106b
#define PG_PCI_DEVICE_ID 0xeeee

#endif // PGDeviceSpec_H
