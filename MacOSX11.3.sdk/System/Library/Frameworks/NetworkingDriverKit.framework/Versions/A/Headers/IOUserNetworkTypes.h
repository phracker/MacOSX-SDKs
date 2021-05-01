/*
 * Copyright (c) 2019-2020 Apple, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _IOUSERNETWORKTYPES_H
#define _IOUSERNETWORKTYPES_H

#include <stdint.h>

/** @deprecated use ether_addr_t instead */
struct __deprecated IOUserNetworkMACAddress {
    uint8_t octet[6];
};

typedef uint32_t IOUserNetworkMediaType;
typedef uint32_t IOUserNetworkLinkStatus;
typedef uint32_t IOUserNetworkLinkQuality;

enum {
    kIOUserNetworkLinkStatusInvalid         = 0x00000000,
    kIOUserNetworkLinkStatusInactive        = 0x00000001,
    kIOUserNetworkLinkStatusActive          = 0x00000003,
    kIOUserNetworkLinkStatusWakeSameNet     = 0x00000004
};

enum {
    kIOUserNetworkLinkQualityOff            = (-2),
    kIOUserNetworkLinkQualityUnknown        = (-1),
    kIOUserNetworkLinkQualityBad            = 10,
    kIOUserNetworkLinkQualityPoor           = 50,
    kIOUserNetworkLinkQualityGood           = 100
};

enum {
    kIOUserNetworkMediaOptionFullDuplex     = 0x00100000,
    kIOUserNetworkMediaOptionHalfDuplex     = 0x00200000,
    kIOUserNetworkMediaOptionFlowControl    = 0x00400000,
    kIOUserNetworkMediaOptionEEE            = 0x00800000,
    kIOUserNetworkMediaOptionLoopback       = 0x08000000
};

enum {
    kIOUserNetworkMediaEthernetAuto         = 0x00000020,
    kIOUserNetworkMediaEthernetManual       = 0x00000021,
    kIOUserNetworkMediaEthernetNone         = 0x00000022,
    kIOUserNetworkMediaEthernet10BaseT      = 0x00000023,
    kIOUserNetworkMediaEthernet10Base2      = 0x00000024,
    kIOUserNetworkMediaEthernet10Base5      = 0x00000025,
    kIOUserNetworkMediaEthernet100BaseTX    = 0x00000026,
    kIOUserNetworkMediaEthernet100BaseFX    = 0x00000027,
    kIOUserNetworkMediaEthernet100BaseT4    = 0x00000028,
    kIOUserNetworkMediaEthernet100BaseVG    = 0x00000029,
    kIOUserNetworkMediaEthernet100BaseT2    = 0x0000002a,
    kIOUserNetworkMediaEthernet1000BaseSX   = 0x0000002b,
    kIOUserNetworkMediaEthernet10BaseSTP    = 0x0000002c,
    kIOUserNetworkMediaEthernet10BaseFL     = 0x0000002d,
    kIOUserNetworkMediaEthernet1000BaseLX   = 0x0000002e,
    kIOUserNetworkMediaEthernet1000BaseCX   = 0x0000002f,
    kIOUserNetworkMediaEthernet1000BaseT    = 0x00000030,
    kIOUserNetworkMediaEthernetHomePNA1     = 0x00000031,
    kIOUserNetworkMediaEthernet10GBaseSR    = 0x00000032,
    kIOUserNetworkMediaEthernet10GBaseLR    = 0x00000033,
    kIOUserNetworkMediaEthernet10GBaseCX4   = 0x00000034,
    kIOUserNetworkMediaEthernet10GBaseT     = 0x00000035,
    kIOUserNetworkMediaEthernet2500BaseT    = 0x00000036,
    kIOUserNetworkMediaEthernet5000BaseT    = 0x00000037,
    kIOUserNetworkMediaEthernet1000BaseCX_SGMII = 0x00000038,
    kIOUserNetworkMediaEthernet1000BaseKX   = 0x00000039,
    kIOUserNetworkMediaEthernet10GBaseKX4   = 0x0000003a,
    kIOUserNetworkMediaEthernet10GBaseKR    = 0x0000003b,
    kIOUserNetworkMediaEthernet10GBaseCR1   = 0x0000003c,
    kIOUserNetworkMediaEthernet10GBaseER    = 0x0000003d,
    kIOUserNetworkMediaEthernet20GBaseKR2   = 0x0000003e,
    kIOUserNetworkMediaEthernet25GBaseCR    = 0x0000003f,
    kIOUserNetworkMediaEthernet25GBaseKR    = 0x00000820,
    kIOUserNetworkMediaEthernet25GBaseSR    = 0x00000821,
    kIOUserNetworkMediaEthernet25GBaseLR    = 0x00000822,
    kIOUserNetworkMediaEthernet40GBaseCR4   = 0x00000823,
    kIOUserNetworkMediaEthernet40GBaseSR4   = 0x00000824,
    kIOUserNetworkMediaEthernet40GBaseLR4   = 0x00000825,
    kIOUserNetworkMediaEthernet40GBaseKR4   = 0x00000826,
    kIOUserNetworkMediaEthernet50GBaseCR2   = 0x00000827,
    kIOUserNetworkMediaEthernet50GBaseKR2   = 0x00000828,
    kIOUserNetworkMediaEthernet50GBaseSR2   = 0x00000829,
    kIOUserNetworkMediaEthernet50GBaseLR2   = 0x0000082a,
    kIOUserNetworkMediaEthernet56GBaseR4    = 0x0000082b,
    kIOUserNetworkMediaEthernet100GBaseCR4  = 0x0000082c,
    kIOUserNetworkMediaEthernet100GBaseSR4  = 0x0000082d,
    kIOUserNetworkMediaEthernet100GBaseKR4  = 0x0000082e,
    kIOUserNetworkMediaEthernet100GBaseLR4  = 0x0000082f,
    kIOUserNetworkMediaEthernetMask         = 0x00000fff,
};

enum {
    kIOUserNetworkFeatureFlagSoftwareVlan = 0x00020000,
    kIOUserNetworkFeatureFlagWOMP = 0x04000000,
    kIOUserNetworkFeatureFlagNicProxy = 0x08000000,
};
 
#endif /* !_IOUSERNETWORKTYPES_H */
