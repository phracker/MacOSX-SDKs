/* iig(DriverKit-107.40.8) generated from IOUserHIDEventService.iig */

/* IOUserHIDEventService.iig:1-38 */
/*
 * Copyright (c) 2018-2019 Apple Inc. All rights reserved.
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

#ifndef _HIDDRIVERKIT_IOUSERHIDEVENTSERVICE_H
#define _HIDDRIVERKIT_IOUSERHIDEVENTSERVICE_H

#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <HIDDriverKit/IOHIDInterface.h>  /* .iig include */
#include <HIDDriverKit/IOHIDEventService.h>  /* .iig include */

class OSArray;

/* source class IOUserHIDEventService IOUserHIDEventService.iig:39-244 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

class  IOUserHIDEventService : public IOHIDEventService
{

public:
    /*!
     * @function init
     *
     * @abstract
     * Initializes IOUserHIDEventService object.
     *
     * @return
     * true on success.
     */
    virtual bool init() override;
    
    /*!
     * @function free
     *
     * @abstract
     * frees the IOUserHIDEventService object.
     */
    virtual void free() override;
    
    /*!
     * @function Start
     *
     * @abstract
     * Function called after initialization to start the IOService.
     *
     * @param provider
     * The IOService that is provider for this object.
     *
     * @return
     * returns kIOReturnSucess on sucess.
     */
    virtual kern_return_t Start(IOService * provider) override;
    
    /*!
     * @function Start
     *
     * @abstract
     * Function called during termination to stop the IOService.
     *
     * @param provider
     * The IOService that is provider for this object.
     *
     * @return
     * returns kIOReturnSucess on sucess.
     */
    virtual kern_return_t Stop(IOService * provider) override;
    
    /*!
     * @function conformsTo
     *
     * @abstract
     * Checks if a service conforms to a certain usage page/usage by iterating
     * through the device usage pairs.
     *
     * @param usagePage
     * The usage page to conform to.
     *
     * @param usage
     * The usage to conform to.
     *
     * @result
     * True if the service conforms to the specified usage page/usage.
     */
    virtual bool conformsTo(uint32_t usagePage, uint32_t usage) LOCALONLY;
    
    /*!
     * @function dispatchDigitizerStylusEvent
     *
     * @abstract
     * Dispatches a digitizer stylus event.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param stylusData
     * A struct containing the stylus data. See IOHIDDigtizerStructs.h for more 
     * info.
     */
    virtual kern_return_t dispatchDigitizerStylusEvent(
                                        uint64_t timeStamp,
                                        IOHIDDigitizerStylusData *stylusData) override LOCALONLY;
    
    /*!
     * @function dispatchDigitizerTouchEvent
     *
     * @abstract
     * Dispatches a digitizer touch pad event.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param touchData
     * An array of touch data, where each struct represents a surface contact. 
     * See IOHIDDigtizerStructs.h for more info.
     *
     * @param touchDataCount
     * The touchData array count.
     */
    virtual kern_return_t dispatchDigitizerTouchEvent(
                                            uint64_t timeStamp,
                                            IOHIDDigitizerTouchData *touchData,
                                            uint32_t touchDataCount) override LOCALONLY;
    
protected:
    
    /*!
     * @function handleStart
     * @abstract
     * method called from Start and can be use to initlialize the service.
     *
     * @param provider
     * The IOService that is provider for this object.
     *
     * @return
     * true on success.
     */
    virtual bool handleStart(IOService * provider) LOCALONLY;
    
    /*!
     * @function handleReport
     *
     * @abstract
     * Callback invoked when an input report is received from the device.
     *
     * @param timestamp
     * The timestamp of the report.
     *
     * @param report
     * Bytes that describe the report.
     *
     * @param reportLength
     * The length of the report.
     *
     * @param type
     * The report type.
     *
     * @param reportID
     * The report ID.
     */
    virtual void handleReport (uint64_t                    timestamp,
                               uint8_t                     *report,
                               uint32_t                    reportLength,
                               IOHIDReportType             type,
                               uint32_t                    reportID) LOCALONLY;
    
    /*!
     * @function getElements
     *
     * @abstract
     * Returns an array of IOHIDElement objects. The element values will be
     * updates on calls to the handleReport() function.
     *
     * @return
     * Returns an array of IOHIDElement objects.
     */
    virtual OSArray *getElements() LOCALONLY;

private:
    bool createReportPool() LOCALONLY;
    
    /*!
     * @function dispatchEvent
     *
     * @abstract
     * Dispatches an event.
     *
     * @param event
     * The IOHIDEvent to dispatch.
     */
    virtual void dispatchEvent(IOHIDEvent *event) override LOCALONLY;
    
    /*!
     * @function ReportAvailable
     *
     * @abstract
     * Callback invoked when an input report is received from the device.
     *
     * @param timestamp
     * The timestamp of the report.
     *
     * @param reportID
     * The report ID.
     *
     * @param reportLength
     * The length of the report.
     *
     * @param type
     * The report type.
     *
     * @param report
     * A memory descriptor that describes the report.
     *
     * @param action
     * The OSAction object that will handle the asynchronous report callback.
     */
    virtual void ReportAvailable(uint64_t timestamp,
                                 uint32_t reportID,
                                 uint32_t reportLength,
                                 IOHIDReportType type,
                                 IOMemoryDescriptor *report,
                                 OSAction *action) LOCAL
                                 TYPE(IOHIDInterface::ReportAvailable);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserHIDEventService IOUserHIDEventService.iig:39-244 */

#define IOUserHIDEventService_ReportAvailable_ID            0x64b213ea6ab88649ULL

#define IOUserHIDEventService_Start_Args \
        IOService * provider

#define IOUserHIDEventService_Stop_Args \
        IOService * provider

#define IOUserHIDEventService_ReportAvailable_Args \
        uint64_t timestamp, \
        uint32_t reportID, \
        uint32_t reportLength, \
        IOHIDReportType type, \
        IOMemoryDescriptor * report, \
        OSAction * action

#define IOUserHIDEventService_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserHIDEventService * self, const IORPC rpc);\
\
    bool\
    createReportPool(\
);\
\
    kern_return_t\
    CreateActionReportAvailable(size_t referenceSize, OSAction ** action);\
\
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    Start_Impl(IOService_Start_Args);\
\
    kern_return_t\
    Stop_Impl(IOService_Stop_Args);\
\
    void\
    ReportAvailable_Impl(IOUserHIDEventService_ReportAvailable_Args);\
\
\
public:\
    /* _Invoke methods */\
\


#define IOUserHIDEventService_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOUserHIDEventService_VirtualMethods \
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
    virtual bool\
    conformsTo(\
        uint32_t usagePage,\
        uint32_t usage) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchDigitizerStylusEvent(\
        uint64_t timeStamp,\
        IOHIDDigitizerStylusData * stylusData) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchDigitizerTouchEvent(\
        uint64_t timeStamp,\
        IOHIDDigitizerTouchData * touchData,\
        uint32_t touchDataCount) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    handleStart(\
        IOService * provider) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleReport(\
        uint64_t timestamp,\
        uint8_t * report,\
        uint32_t reportLength,\
        IOHIDReportType type,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual OSArray *\
    getElements(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    dispatchEvent(\
        IOHIDEvent * event) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserHIDEventServiceMetaClass;
extern const OSClassLoadInformation IOUserHIDEventService_Class;

class IOUserHIDEventServiceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserHIDEventServiceInterface : public OSInterface
{
public:
    virtual bool
    conformsTo(uint32_t usagePage,
        uint32_t usage) = 0;

    virtual bool
    handleStart(IOService * provider) = 0;

    virtual void
    handleReport(uint64_t timestamp,
        uint8_t * report,
        uint32_t reportLength,
        IOHIDReportType type,
        uint32_t reportID) = 0;

    virtual OSArray *
    getElements() = 0;

};

struct IOUserHIDEventService_IVars;
struct IOUserHIDEventService_LocalIVars;

class IOUserHIDEventService : public IOHIDEventService, public IOUserHIDEventServiceInterface
{
#if !KERNEL
    friend class IOUserHIDEventServiceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserHIDEventService_IVars * ivars;
        IOUserHIDEventService_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOHIDEventService;

#if !KERNEL
    IOUserHIDEventService_Methods
    IOUserHIDEventService_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#define OSAction_IOUserHIDEventService_ReportAvailable_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(OSAction_IOUserHIDEventService_ReportAvailable * self, const IORPC rpc);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSAction_IOUserHIDEventService_ReportAvailable_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSAction_IOUserHIDEventService_ReportAvailable_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gOSAction_IOUserHIDEventService_ReportAvailableMetaClass;
extern const OSClassLoadInformation OSAction_IOUserHIDEventService_ReportAvailable_Class;

class OSAction_IOUserHIDEventService_ReportAvailableMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

class OSAction_IOUserHIDEventService_ReportAvailableInterface : public OSInterface
{
public:
};

struct OSAction_IOUserHIDEventService_ReportAvailable_IVars;
struct OSAction_IOUserHIDEventService_ReportAvailable_LocalIVars;

class OSAction_IOUserHIDEventService_ReportAvailable : public OSAction, public OSAction_IOUserHIDEventService_ReportAvailableInterface
{
#if KERNEL
    OSDeclareDefaultStructorsWithDispatch(OSAction_IOUserHIDEventService_ReportAvailable);
#endif /* KERNEL */

#if !KERNEL
    friend class OSAction_IOUserHIDEventService_ReportAvailableMetaClass;
#endif /* !KERNEL */

public:
    union
    {
        OSAction_IOUserHIDEventService_ReportAvailable_IVars * ivars;
        OSAction_IOUserHIDEventService_ReportAvailable_LocalIVars * lvars;
    };
#if !KERNEL
    virtual const OSMetaClass *
    getMetaClass() const APPLE_KEXT_OVERRIDE { return OSTypeID(OSAction_IOUserHIDEventService_ReportAvailable); };
#endif /* KERNEL */

    using super = OSAction;

#if !KERNEL
    OSAction_IOUserHIDEventService_ReportAvailable_Methods
#endif /* !KERNEL */

    OSAction_IOUserHIDEventService_ReportAvailable_VirtualMethods
};

#endif /* !__DOCUMENTATION__ */

/* IOUserHIDEventService.iig:246- */

#endif /* ! _HIDDRIVERKIT_IOUSERHIDEVENTSERVICE_H */
