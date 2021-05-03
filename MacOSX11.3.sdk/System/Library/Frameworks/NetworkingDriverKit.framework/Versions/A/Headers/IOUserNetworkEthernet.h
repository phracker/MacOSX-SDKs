/* iig(DriverKit-107.100.6) generated from IOUserNetworkEthernet.iig */

/* IOUserNetworkEthernet.iig:1-46 */
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

#ifndef _IOUSERNETWORKETHERNET_IIG
#define _IOUSERNETWORKETHERNET_IIG

#include <net/ethernet.h>

#include <DriverKit/IOService.h>  /* .iig include */
#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <DriverKit/IODataQueueDispatchSource.h>  /* .iig include */

#include <NetworkingDriverKit/IOUserNetworkTypes.h>
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */

struct _IOUserNetworkEthernetInterfaceDescriptor;
struct nicproxy_limits_info_s;
struct offload_info_s;

/* source class IOUserNetworkEthernet IOUserNetworkEthernet.iig:47-148 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
*/

class KERNEL IOUserNetworkEthernet : public IOService
{
public:
    virtual bool
    init() override;

    virtual void
    free() override;

    kern_return_t
    SetTxPacketHeadroom(uint16_t numBytes) LOCALONLY;

    kern_return_t
    SetTxPacketTailroom(uint16_t numBytes) LOCALONLY;

    kern_return_t
    SetWakeOnMagicPacketSupport(bool isSupported) LOCALONLY;

    kern_return_t
    SetSoftwareVlanSupport(bool isSupported) LOCALONLY;

    virtual kern_return_t
    RegisterEthernetInterface(
        IOUserNetworkMACAddress macAddress,
        IOUserNetworkPacketBufferPool * pool,
        IOUserNetworkPacketQueue ** queues,
        uint32_t queueCount) LOCALONLY;

    virtual kern_return_t
    ReportLinkStatus(
        IOUserNetworkLinkStatus linkStatus,
        IOUserNetworkMediaType  activeMediaType);

    virtual kern_return_t
    ReportLinkQuality(IOUserNetworkLinkQuality linkQuality);

    virtual kern_return_t
    ReportDataBandwidths(
        uint64_t    maxInputBandwidth,
        uint64_t    maxOutputBandwidth,
        uint64_t    effectiveInputBandwidth,
        uint64_t    effectiveOutputBandwidth);

    virtual kern_return_t
    SetInterfaceEnable(bool isEnable) = 0;

    virtual kern_return_t
    SetPromiscuousModeEnable(bool enable) = 0;

    /** @deprecated, use  setMulticastAddresses instead */
    virtual kern_return_t
    SetMulticastAddresses(
        const IOUserNetworkMACAddress * addresses,
        uint32_t count);

    virtual kern_return_t
    setMulticastAddresses(
        const ether_addr_t * addresses,
        uint32_t count) LOCALONLY;

    virtual kern_return_t
    SetAllMulticastModeEnable(bool enable) = 0;

    virtual kern_return_t
    ReportAvailableMediaTypes(
        const IOUserNetworkMediaType * mediaTypes,
        uint32_t count) LOCALONLY;

    virtual kern_return_t
    SelectMediaType(IOUserNetworkMediaType mediaType) = 0;

    virtual kern_return_t
    SetWakeOnMagicPacketEnable(bool enable) = 0;

    virtual kern_return_t
    SetMTU( uint32_t mtu ) LOCAL = 0;

    virtual kern_return_t
    GetMaxTransferUnit( uint32_t *mtu ) LOCAL = 0;
    
    virtual kern_return_t
    SetHardwareAssists( uint32_t hardwareAssists ) LOCAL = 0;

    virtual kern_return_t
    GetHardwareAssists( uint32_t *hardwareAssists ) LOCAL = 0;

    virtual kern_return_t
    ReportNicProxyLimits(nicproxy_limits_info_s nicproxy_limits_info);
    
    virtual kern_return_t SetPowerState(uint32_t powerstate) override;

    virtual void hwConfigNicProxyData(offload_info_s *handoff) LOCALONLY;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserNetworkEthernet IOUserNetworkEthernet.iig:47-148 */

#define IOUserNetworkEthernet_ReleaseNicProxyData_ID            0x9f4819c35f444e74ULL
#define IOUserNetworkEthernet_RetainNicProxyData_ID            0xaa273d9e353db313ULL
#define IOUserNetworkEthernet__DataAvailable_ID            0xf1fe93bc0f089f02ULL
#define IOUserNetworkEthernet__ReportAvailableMediaTypes_ID            0xb48b4ba3f53fbc2aULL
#define IOUserNetworkEthernet__SetMulticastAddresses_ID            0xfce8a9ef10e7e262ULL
#define IOUserNetworkEthernet__RegisterEthernetInterface_ID            0xd3a4f5774bc98335ULL
#define IOUserNetworkEthernet_ReportLinkStatus_ID            0xbfd68fa3f5c86c4dULL
#define IOUserNetworkEthernet_ReportLinkQuality_ID            0xb0a7fe8ebb582f72ULL
#define IOUserNetworkEthernet_ReportDataBandwidths_ID            0xbac3a625104c3526ULL
#define IOUserNetworkEthernet_SetInterfaceEnable_ID            0xf421a9d80f9a1fdaULL
#define IOUserNetworkEthernet_SetPromiscuousModeEnable_ID            0xe072fcc26cf639acULL
#define IOUserNetworkEthernet_SetMulticastAddresses_ID            0xa1b551fe3b8a09c1ULL
#define IOUserNetworkEthernet_SetAllMulticastModeEnable_ID            0xe042a87972611225ULL
#define IOUserNetworkEthernet_SelectMediaType_ID            0xc3e63ac546ebd1feULL
#define IOUserNetworkEthernet_SetWakeOnMagicPacketEnable_ID            0xb23ee0228705fb95ULL
#define IOUserNetworkEthernet_SetMTU_ID            0xed7ce2ca0df8ed0eULL
#define IOUserNetworkEthernet_GetMaxTransferUnit_ID            0xa49568f23ee8efd5ULL
#define IOUserNetworkEthernet_SetHardwareAssists_ID            0xe397b741b15a61d6ULL
#define IOUserNetworkEthernet_GetHardwareAssists_ID            0xe77a9aa5db9c706cULL
#define IOUserNetworkEthernet_ReportNicProxyLimits_ID            0xa4ee315532585173ULL

#define IOUserNetworkEthernet_ReleaseNicProxyData_Args \


#define IOUserNetworkEthernet_RetainNicProxyData_Args \
        uint64_t * handoff

#define IOUserNetworkEthernet__DataAvailable_Args \
        OSAction * action

#define IOUserNetworkEthernet__ReportAvailableMediaTypes_Args \
        const unsigned int * mediaTypes, \
        uint32_t mediaTypesCount

#define IOUserNetworkEthernet__SetMulticastAddresses_Args \
        IOMemoryDescriptor * md

#define IOUserNetworkEthernet__RegisterEthernetInterface_Args \
        _IOUserNetworkEthernetInterfaceDescriptor descriptor, \
        IOUserNetworkPacketBufferPool * pool, \
        IOUserNetworkPacketQueue * queue1, \
        IOUserNetworkPacketQueue * queue2, \
        IOUserNetworkPacketQueue * queue3, \
        IOUserNetworkPacketQueue * queue4

#define IOUserNetworkEthernet_ReportLinkStatus_Args \
        IOUserNetworkLinkStatus linkStatus, \
        IOUserNetworkMediaType activeMediaType

#define IOUserNetworkEthernet_ReportLinkQuality_Args \
        IOUserNetworkLinkQuality linkQuality

#define IOUserNetworkEthernet_ReportDataBandwidths_Args \
        uint64_t maxInputBandwidth, \
        uint64_t maxOutputBandwidth, \
        uint64_t effectiveInputBandwidth, \
        uint64_t effectiveOutputBandwidth

#define IOUserNetworkEthernet_SetInterfaceEnable_Args \
        bool isEnable

#define IOUserNetworkEthernet_SetPromiscuousModeEnable_Args \
        bool enable

#define IOUserNetworkEthernet_SetMulticastAddresses_Args \
        const IOUserNetworkMACAddress * addresses, \
        uint32_t count

#define IOUserNetworkEthernet_SetAllMulticastModeEnable_Args \
        bool enable

#define IOUserNetworkEthernet_SelectMediaType_Args \
        IOUserNetworkMediaType mediaType

#define IOUserNetworkEthernet_SetWakeOnMagicPacketEnable_Args \
        bool enable

#define IOUserNetworkEthernet_SetMTU_Args \
        uint32_t mtu

#define IOUserNetworkEthernet_GetMaxTransferUnit_Args \
        uint32_t * mtu

#define IOUserNetworkEthernet_SetHardwareAssists_Args \
        uint32_t hardwareAssists

#define IOUserNetworkEthernet_GetHardwareAssists_Args \
        uint32_t * hardwareAssists

#define IOUserNetworkEthernet_ReportNicProxyLimits_Args \
        nicproxy_limits_info_s nicproxy_limits_info

#define IOUserNetworkEthernet_SetPowerState_Args \
        uint32_t powerstate

#define IOUserNetworkEthernet_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkEthernet * self, const IORPC rpc);\
\
    kern_return_t\
    ReleaseNicProxyData(\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    RetainNicProxyData(\
        uint64_t * handoff,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CreateAction_DataAvailable(size_t referenceSize, OSAction ** action);\
\
    kern_return_t\
    _ReportAvailableMediaTypes(\
        const unsigned int * mediaTypes,\
        uint32_t mediaTypesCount,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _SetMulticastAddresses(\
        IOMemoryDescriptor * md,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _RegisterEthernetInterface(\
        _IOUserNetworkEthernetInterfaceDescriptor descriptor,\
        IOUserNetworkPacketBufferPool * pool,\
        IOUserNetworkPacketQueue * queue1,\
        IOUserNetworkPacketQueue * queue2,\
        IOUserNetworkPacketQueue * queue3,\
        IOUserNetworkPacketQueue * queue4,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetTxPacketHeadroom(\
        uint16_t numBytes);\
\
    kern_return_t\
    SetTxPacketTailroom(\
        uint16_t numBytes);\
\
    kern_return_t\
    SetWakeOnMagicPacketSupport(\
        bool isSupported);\
\
    kern_return_t\
    SetSoftwareVlanSupport(\
        bool isSupported);\
\
    kern_return_t\
    ReportLinkStatus(\
        IOUserNetworkLinkStatus linkStatus,\
        IOUserNetworkMediaType activeMediaType,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    ReportLinkQuality(\
        IOUserNetworkLinkQuality linkQuality,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    ReportDataBandwidths(\
        uint64_t maxInputBandwidth,\
        uint64_t maxOutputBandwidth,\
        uint64_t effectiveInputBandwidth,\
        uint64_t effectiveOutputBandwidth,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetInterfaceEnable(\
        bool isEnable,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetPromiscuousModeEnable(\
        bool enable,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetMulticastAddresses(\
        const IOUserNetworkMACAddress * addresses,\
        uint32_t count,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetAllMulticastModeEnable(\
        bool enable,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SelectMediaType(\
        IOUserNetworkMediaType mediaType,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetWakeOnMagicPacketEnable(\
        bool enable,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetMTU(\
        uint32_t mtu,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    GetMaxTransferUnit(\
        uint32_t * mtu,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetHardwareAssists(\
        uint32_t hardwareAssists,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    GetHardwareAssists(\
        uint32_t * hardwareAssists,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    ReportNicProxyLimits(\
        nicproxy_limits_info_s nicproxy_limits_info,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    _SetMulticastAddresses_Impl(IOUserNetworkEthernet__SetMulticastAddresses_Args);\
\
    kern_return_t\
    SetPowerState_Impl(IOService_SetPowerState_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*ReleaseNicProxyData_Handler)(OSMetaClassBase * targetIOUserNetworkEthernet_ReleaseNicProxyData_Args);\
    static kern_return_t\
    ReleaseNicProxyData_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        ReleaseNicProxyData_Handler func);\
\
    typedef kern_return_t (*RetainNicProxyData_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_RetainNicProxyData_Args);\
    static kern_return_t\
    RetainNicProxyData_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        RetainNicProxyData_Handler func);\
\
    typedef kern_return_t (*_ReportAvailableMediaTypes_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet__ReportAvailableMediaTypes_Args);\
    static kern_return_t\
    _ReportAvailableMediaTypes_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _ReportAvailableMediaTypes_Handler func);\
\
    typedef kern_return_t (*_SetMulticastAddresses_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet__SetMulticastAddresses_Args);\
    static kern_return_t\
    _SetMulticastAddresses_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _SetMulticastAddresses_Handler func);\
\
    typedef kern_return_t (*_RegisterEthernetInterface_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet__RegisterEthernetInterface_Args);\
    static kern_return_t\
    _RegisterEthernetInterface_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _RegisterEthernetInterface_Handler func);\
\
    typedef kern_return_t (*ReportLinkStatus_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_ReportLinkStatus_Args);\
    static kern_return_t\
    ReportLinkStatus_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        ReportLinkStatus_Handler func);\
\
    typedef kern_return_t (*ReportLinkQuality_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_ReportLinkQuality_Args);\
    static kern_return_t\
    ReportLinkQuality_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        ReportLinkQuality_Handler func);\
\
    typedef kern_return_t (*ReportDataBandwidths_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_ReportDataBandwidths_Args);\
    static kern_return_t\
    ReportDataBandwidths_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        ReportDataBandwidths_Handler func);\
\
    typedef kern_return_t (*SetInterfaceEnable_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetInterfaceEnable_Args);\
    static kern_return_t\
    SetInterfaceEnable_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetInterfaceEnable_Handler func);\
\
    typedef kern_return_t (*SetPromiscuousModeEnable_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetPromiscuousModeEnable_Args);\
    static kern_return_t\
    SetPromiscuousModeEnable_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetPromiscuousModeEnable_Handler func);\
\
    typedef kern_return_t (*SetMulticastAddresses_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetMulticastAddresses_Args);\
    static kern_return_t\
    SetMulticastAddresses_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetMulticastAddresses_Handler func);\
\
    typedef kern_return_t (*SetAllMulticastModeEnable_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetAllMulticastModeEnable_Args);\
    static kern_return_t\
    SetAllMulticastModeEnable_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetAllMulticastModeEnable_Handler func);\
\
    typedef kern_return_t (*SelectMediaType_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SelectMediaType_Args);\
    static kern_return_t\
    SelectMediaType_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SelectMediaType_Handler func);\
\
    typedef kern_return_t (*SetWakeOnMagicPacketEnable_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetWakeOnMagicPacketEnable_Args);\
    static kern_return_t\
    SetWakeOnMagicPacketEnable_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetWakeOnMagicPacketEnable_Handler func);\
\
    typedef kern_return_t (*SetMTU_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetMTU_Args);\
    static kern_return_t\
    SetMTU_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetMTU_Handler func);\
\
    typedef kern_return_t (*GetMaxTransferUnit_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_GetMaxTransferUnit_Args);\
    static kern_return_t\
    GetMaxTransferUnit_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        GetMaxTransferUnit_Handler func);\
\
    typedef kern_return_t (*SetHardwareAssists_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_SetHardwareAssists_Args);\
    static kern_return_t\
    SetHardwareAssists_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetHardwareAssists_Handler func);\
\
    typedef kern_return_t (*GetHardwareAssists_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_GetHardwareAssists_Args);\
    static kern_return_t\
    GetHardwareAssists_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        GetHardwareAssists_Handler func);\
\
    typedef kern_return_t (*ReportNicProxyLimits_Handler)(OSMetaClassBase * target, IOUserNetworkEthernet_ReportNicProxyLimits_Args);\
    static kern_return_t\
    ReportNicProxyLimits_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        ReportNicProxyLimits_Handler func);\
\


#define IOUserNetworkEthernet_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    ReleaseNicProxyData_Impl(IOUserNetworkEthernet_ReleaseNicProxyData_Args);\
\
    kern_return_t\
    RetainNicProxyData_Impl(IOUserNetworkEthernet_RetainNicProxyData_Args);\
\
    void\
    _DataAvailable_Impl(IOUserNetworkEthernet__DataAvailable_Args);\
\
    kern_return_t\
    _ReportAvailableMediaTypes_Impl(IOUserNetworkEthernet__ReportAvailableMediaTypes_Args);\
\
    kern_return_t\
    _RegisterEthernetInterface_Impl(IOUserNetworkEthernet__RegisterEthernetInterface_Args);\
\
    kern_return_t\
    ReportLinkStatus_Impl(IOUserNetworkEthernet_ReportLinkStatus_Args);\
\
    kern_return_t\
    ReportLinkQuality_Impl(IOUserNetworkEthernet_ReportLinkQuality_Args);\
\
    kern_return_t\
    ReportDataBandwidths_Impl(IOUserNetworkEthernet_ReportDataBandwidths_Args);\
\
    kern_return_t\
    SetMulticastAddresses_Impl(IOUserNetworkEthernet_SetMulticastAddresses_Args);\
\
    kern_return_t\
    ReportNicProxyLimits_Impl(IOUserNetworkEthernet_ReportNicProxyLimits_Args);\
\


#define IOUserNetworkEthernet_VirtualMethods \
\
public:\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    RegisterEthernetInterface(\
        IOUserNetworkMACAddress macAddress,\
        IOUserNetworkPacketBufferPool * pool,\
        IOUserNetworkPacketQueue ** queues,\
        uint32_t queueCount) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setMulticastAddresses(\
        const ether_addr_t * addresses,\
        uint32_t count) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    ReportAvailableMediaTypes(\
        const IOUserNetworkMediaType * mediaTypes,\
        uint32_t count) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    hwConfigNicProxyData(\
        offload_info_s * handoff) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserNetworkEthernetMetaClass;
extern const OSClassLoadInformation IOUserNetworkEthernet_Class;

class IOUserNetworkEthernetMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkEthernetInterface : public OSInterface
{
public:
    virtual kern_return_t
    RegisterEthernetInterface(IOUserNetworkMACAddress macAddress,
        IOUserNetworkPacketBufferPool * pool,
        IOUserNetworkPacketQueue ** queues,
        uint32_t queueCount) = 0;

    virtual kern_return_t
    setMulticastAddresses(const ether_addr_t * addresses,
        uint32_t count) = 0;

    virtual kern_return_t
    ReportAvailableMediaTypes(const IOUserNetworkMediaType * mediaTypes,
        uint32_t count) = 0;

    virtual void
    hwConfigNicProxyData(offload_info_s * handoff) = 0;

};

struct IOUserNetworkEthernet_IVars;
struct IOUserNetworkEthernet_LocalIVars;

class IOUserNetworkEthernet : public IOService, public IOUserNetworkEthernetInterface
{
#if !KERNEL
    friend class IOUserNetworkEthernetMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkEthernet_IVars * ivars;
        IOUserNetworkEthernet_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOService;

#if !KERNEL
    IOUserNetworkEthernet_Methods
    IOUserNetworkEthernet_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#define OSAction_IOUserNetworkEthernet__DataAvailable_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(OSAction_IOUserNetworkEthernet__DataAvailable * self, const IORPC rpc);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSAction_IOUserNetworkEthernet__DataAvailable_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSAction_IOUserNetworkEthernet__DataAvailable_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gOSAction_IOUserNetworkEthernet__DataAvailableMetaClass;
extern const OSClassLoadInformation OSAction_IOUserNetworkEthernet__DataAvailable_Class;

class OSAction_IOUserNetworkEthernet__DataAvailableMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

class OSAction_IOUserNetworkEthernet__DataAvailableInterface : public OSInterface
{
public:
};

struct OSAction_IOUserNetworkEthernet__DataAvailable_IVars;
struct OSAction_IOUserNetworkEthernet__DataAvailable_LocalIVars;

class __attribute__((availability(driverkit,introduced=20,message="Type-safe OSAction factory methods are available in DriverKit 20 and newer"))) OSAction_IOUserNetworkEthernet__DataAvailable : public OSAction, public OSAction_IOUserNetworkEthernet__DataAvailableInterface
{
#if KERNEL
    OSDeclareDefaultStructorsWithDispatch(OSAction_IOUserNetworkEthernet__DataAvailable);
#endif /* KERNEL */

#if !KERNEL
    friend class OSAction_IOUserNetworkEthernet__DataAvailableMetaClass;
#endif /* !KERNEL */

public:
    union
    {
        OSAction_IOUserNetworkEthernet__DataAvailable_IVars * ivars;
        OSAction_IOUserNetworkEthernet__DataAvailable_LocalIVars * lvars;
    };
#if !KERNEL
    virtual const OSMetaClass *
    getMetaClass() const APPLE_KEXT_OVERRIDE { return OSTypeID(OSAction_IOUserNetworkEthernet__DataAvailable); };
#endif /* KERNEL */

    using super = OSAction;

#if !KERNEL
    OSAction_IOUserNetworkEthernet__DataAvailable_Methods
#endif /* !KERNEL */

    OSAction_IOUserNetworkEthernet__DataAvailable_VirtualMethods
};

#endif /* !__DOCUMENTATION__ */


/* IOUserNetworkEthernet.iig:179- */

struct _IOUserNetworkEthernetInterfaceDescriptor {
    ether_addr_t macAddress;
    uint32_t                featureFlags;
    uint32_t                 _reserved;
    uint16_t                txPacketHeadroomBytes;
    uint16_t                txPacketTailroomBytes;
} __attribute__((packed));

typedef struct nicproxy_limits_info_s {
    uint8_t ipv4_cnt;
    uint8_t ipv6_cnt;
    uint16_t kaIPv4Count;
    uint16_t kaIPv6Count;
    uint16_t wakeUDPCount;
    uint16_t wakeTCPCount;
    uint16_t rr_cnt;
    uint8_t mDnsMaxDomainLen;
    uint8_t ethCount;
    uint16_t rr_buf_size;
} __attribute__((packed)) nicproxy_limits_info_t;

#endif /* ! _IOUSERNETWORKETHERNET_H */
