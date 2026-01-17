/* iig(DriverKit-107.100.6) generated from IOTimerDispatchSource.iig */

/* IOTimerDispatchSource.iig:1-69 */
/*
 * Copyright (c) 2019-2019 Apple Inc. All rights reserved.
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

#ifndef _IOKIT_UIOTIMERDISPATCHSOURCE_H
#define _IOKIT_UIOTIMERDISPATCHSOURCE_H

#include <DriverKit/IODispatchQueue.h>  /* .iig include */

/*!
 * @enum Clock type to pass in IOTimerDispatchSource::WakeAtTime() `options`
 * @discussion Determines how `deadline` and `leeway` arguments are interpreted.
 *
 * @constant kIOTimerClockUptimeRaw
 * Type of a clock value from clock_gettime_nsec_np(CLOCK_UPTIME_RAW).
 * Equivalent to a value from mach_absolute_time() but in nanoseconds.
 *
 * @constant kIOTimerClockMonotonicRaw
 * Type of a clock value from clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW).
 * Equivalent to a value from mach_continuous_time() but in nanoseconds.
 *
 * @constant kIOTimerClockRealTime
 * @constant kIOTimerClockWallTime
 * Type of a clock value from clock_gettime_nsec_np(CLOCK_REALTIME).
 * Equivalent to a value from gettimeofday() but in nanoseconds.
 *
 * @constant kIOTimerClockMachAbsoluteTime
 * Type of a clock value from mach_absolute_time() in tick units.
 * Prefer to use equivalent clock_gettime_nsec_np(CLOCK_UPTIME_RAW) in
 * nanoseconds.
 *
 * @constant kIOTimerClockMachContinuousTime
 * Type of a clock value from mach_continuous_time() in tick units.
 * Prefer to use equivalent clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW) in
 * nanoseconds.
 */
enum {
	kIOTimerClockUptimeRaw = 0x88ull,
	kIOTimerClockMonotonicRaw = 0x84ull,
	kIOTimerClockRealTime = 0x80ull,
	kIOTimerClockWallTime = 0x80ull,
	kIOTimerClockMachAbsoluteTime = 0xC8ull,
	kIOTimerClockMachContinuousTime = 0xC4ull,
};

/* source class IOTimerDispatchSource IOTimerDispatchSource.iig:70-158 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class IOTimerDispatchSource
 *
 * @abstract
 * IOTimerDispatchSource delivers timer notifications to a handler block on a dispatch queue.
 *
 * @discussion
 * A driver can run code in response to an timer. There are several available timebases, but the
 * most commonly used is kIOTimerClockMachAbsoluteTime.
 */

class LOCAL IOTimerDispatchSource : public IODispatchSource
{
public:

    /*!
     * @brief       Create an IOTimerDispatchSource for a timer.
     * @param       queue Target queue to run the handler block.
     * @param       source Created source with +1 retain count to be released by the caller.
     * @return      kIOReturnSuccess on success. See IOReturn.h for error codes.
     */
	static kern_return_t
	Create(
		IODispatchQueue * queue,
		IOTimerDispatchSource ** source);

	virtual bool
	init() override;

	virtual void
	free() override;

    /*!
     * @brief       Set the handler block to run when the timer fires.
     * @param       action OSAction instance specifying the callback method. The OSAction object will be retained
     *              until SetHandler is called again or the event source is cancelled.
     * @return      kIOReturnSuccess on success. See IOReturn.h for error codes.
     */
	virtual kern_return_t
	    SetHandler(
		OSAction * action TYPE(TimerOccurred));

    /*!
     * @brief       Control the enable state of the timer.
     * @param       enable Pass true to enable the source or false to disable.
     * @param       handler Optional block to be executed after the timer has been disabled and any pending
     *              handlers completed.
     * @return      kIOReturnSuccess on success. See IOReturn.h for error codes.
     */
	virtual kern_return_t
	SetEnableWithCompletion(
		bool enable,
		IODispatchSourceCancelHandler handler) override;

    /*!
     * @brief       Cancel all callbacks from the event source.
     * @discussion  After cancellation, the source can only be freed. It cannot be reactivated.
     * @param       handler Handler block to be invoked after any callbacks have completed.
     * @return      kIOReturnSuccess on success. See IOReturn.h for error codes.
     */
	virtual kern_return_t
	Cancel(IODispatchSourceCancelHandler handler) override;

    /*!
     * @brief       Schedule a callback from the timer.
     * @discussion  Schedule a callback from the timer given a time in a timebase. This should be called
     *              on the queue the timer will be delivered on. If a timer was already scheduled but not fired
     *              it will not fire and be replaced by the new deadline.
     * @param       options Pass one of the kIOTimerClock* options to specify the timebase for the
     *              deadline and leeway arguments.
     * @param       deadline Pass the time the timer should fire.
     * @param       leeway The leeway argument allows the system to defer the timer if advantageous for power cost,
     *              at most by the leeway specified time.
     * @return      kIOReturnSuccess on success. See IOReturn.h for error codes.
     */
	virtual kern_return_t
	WakeAtTime(
		uint64_t options,
		uint64_t deadline,
		uint64_t leeway);

private:
	virtual kern_return_t
	CheckForWork(bool synchronous) override;

	virtual void
	TimerOccurred(
		OSAction      * action TARGET,
		uint64_t        time) REPLY LOCAL;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOTimerDispatchSource IOTimerDispatchSource.iig:70-158 */

#define IOTimerDispatchSource_Create_ID            0x5703101ba090eaf0ULL
#define IOTimerDispatchSource_SetHandler_ID            0x487f4f13f1a0a074ULL
#define IOTimerDispatchSource_WakeAtTime_ID            0x1da868f27d5d7d37ULL
#define IOTimerDispatchSource_TimerOccurred_ID            0x0f4ab1c3cbb5ae47ULL

#define IOTimerDispatchSource_Create_Args \
        IODispatchQueue * queue, \
        IOTimerDispatchSource ** source

#define IOTimerDispatchSource_SetHandler_Args \
        OSAction * action

#define IOTimerDispatchSource_SetEnableWithCompletion_Args \
        bool enable, \
        IODispatchSourceCancelHandler handler

#define IOTimerDispatchSource_Cancel_Args \
        IODispatchSourceCancelHandler handler

#define IOTimerDispatchSource_WakeAtTime_Args \
        uint64_t options, \
        uint64_t deadline, \
        uint64_t leeway

#define IOTimerDispatchSource_CheckForWork_Args \
        const IORPC rpc, \
        bool synchronous

#define IOTimerDispatchSource_TimerOccurred_Args \
        OSAction * action, \
        uint64_t time

#define IOTimerDispatchSource_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOTimerDispatchSource * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        IODispatchQueue * queue,\
        IOTimerDispatchSource ** source);\
\
    kern_return_t\
    SetHandler(\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    WakeAtTime(\
        uint64_t options,\
        uint64_t deadline,\
        uint64_t leeway,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    TimerOccurred(\
        IORPC rpc,\
        OSAction * action,\
        uint64_t time,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IOTimerDispatchSource_Create_Args);\
\
    kern_return_t\
    SetHandler_Impl(IOTimerDispatchSource_SetHandler_Args);\
\
    kern_return_t\
    SetEnableWithCompletion_Impl(IODispatchSource_SetEnableWithCompletion_Args);\
\
    kern_return_t\
    Cancel_Impl(IODispatchSource_Cancel_Args);\
\
    kern_return_t\
    WakeAtTime_Impl(IOTimerDispatchSource_WakeAtTime_Args);\
\
    kern_return_t\
    CheckForWork_Impl(IODispatchSource_CheckForWork_Args);\
\
    void\
    TimerOccurred_Impl(IOTimerDispatchSource_TimerOccurred_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IOTimerDispatchSource_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\
    typedef kern_return_t (*SetHandler_Handler)(OSMetaClassBase * target, IOTimerDispatchSource_SetHandler_Args);\
    static kern_return_t\
    SetHandler_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetHandler_Handler func);\
\
    typedef kern_return_t (*WakeAtTime_Handler)(OSMetaClassBase * target, IOTimerDispatchSource_WakeAtTime_Args);\
    static kern_return_t\
    WakeAtTime_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        WakeAtTime_Handler func);\
\
    typedef void (*TimerOccurred_Handler)(OSMetaClassBase * target, IOTimerDispatchSource_TimerOccurred_Args);\
    static kern_return_t\
    TimerOccurred_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        TimerOccurred_Handler func,\
        const OSMetaClass * targetActionClass);\
\
    static kern_return_t\
    TimerOccurred_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        TimerOccurred_Handler func);\
\


#define IOTimerDispatchSource_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOTimerDispatchSource_VirtualMethods \
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


#if !KERNEL

extern OSMetaClass          * gIOTimerDispatchSourceMetaClass;
extern const OSClassLoadInformation IOTimerDispatchSource_Class;

class IOTimerDispatchSourceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOTimerDispatchSourceInterface : public OSInterface
{
public:
};

struct IOTimerDispatchSource_IVars;
struct IOTimerDispatchSource_LocalIVars;

class IOTimerDispatchSource : public IODispatchSource, public IOTimerDispatchSourceInterface
{
#if !KERNEL
    friend class IOTimerDispatchSourceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOTimerDispatchSource_IVars * ivars;
        IOTimerDispatchSource_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IODispatchSource;

#if !KERNEL
    IOTimerDispatchSource_Methods
    IOTimerDispatchSource_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOTimerDispatchSource.iig:160- */


#endif /* ! _IOKIT_UIOTIMERDISPATCHSOURCE_H */
