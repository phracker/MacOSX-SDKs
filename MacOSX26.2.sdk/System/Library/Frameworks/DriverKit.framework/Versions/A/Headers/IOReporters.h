/* iig(DriverKit-451) generated from IOReporters.iig */

/* IOReporters.iig:1-113 */
/*
 * Copyright (c) 2012-2016 Apple Inc.  All Rights Reserved.
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


#ifndef _DRIVERKIT_REPORTERS_H_
#define _DRIVERKIT_REPORTERS_H_

#include <machine/limits.h>

#include <DriverKit/OSPtr.h>
#include <DriverKit/IOReportTypes.h>
#include <DriverKit/IOKernelReportStructs.h>
#include <DriverKit/IOLib.h>

#include <DriverKit/OSDictionary.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <DriverKit/OSCollection.h>  /* .iig include */


typedef OSDictionary IOReportLegendEntry;

/*******************************
*   TOC: this file contains
*    1. Introduction
*    2a. IOReporter class declaration (public & non-public members)
*    2b. static IOReporter methods unrelated to the class
*    3. IOReporter subclass declarations (public & non-public members)
*    4. IOReportLegend class declaration
*******************************/

/*!
 *  1. Introduction
 *
 *  IOReporting is a mechanism for I/O Kit drivers to gather statistics
 *  (or other information) and make it available to various "observers,"
 *  which are generally in user space. Requests for information come
 *  through two new IOService methods: ::configureReport(...) and
 *  ::updateReport(...). While not required (see IOReportTypes.h), drivers
 *  will generally use IOReporter subclass instances to track the requested
 *  information and respond to IOReporting requests. Drivers can use these
 *  classes to track information, either all the time or between "enable"
 *  and "disable" calls to IOService::configureReport().
 *
 *  Available information is organized into "channels." A channel is
 *  uniquely identified by both driver (registry) ID and a 64-bit channel
 *  ID. One way drivers can advertise their channels is by publishing
 *  "legends" in the I/O Kit registry. In addition to collecting
 *  information and responding to queries, IOReporter objects can produce
 *  legend entries describing their channels. The IOReportLegend class
 *  helps manage legend entries from multiple reporter objects as well
 *  as with grouping channels logically for observers.
 *
 *  An important basic constraint of the current implementation is that
 *  all channels reported by a particular reporter instance must share all
 *  traits except channel ID and name.  Specifically, the channel type
 *  (including report class, categories, & size) and units.  Additionally,
 *  IOHistogramReporter currently only supports one channel at a time.
 *
 *  Currently, ::{configure/update}Report() can be called any time between
 *  when a driver calls registerService() and when free() is called on
 *  your driver. 12960947 tracks improvements / recommendations for
 *  correctly handling these calls during termination.
 *
 * Locking
 *  IOReporting only imposes concurrent access constraints when multiple
 *  threads are accessing the same object.  Three levels of constraint apply
 *  depending on a method's purpose:
 *  1. Allocation/Teardown - same-instance concurrency UNSAFE, MAY BLOCK
 *  2. Configuration - same-instance concurrency SAFE, MAY BLOCK
 *  3. Update - same-instance concurrency SAFE, WILL NOT BLOCK
 *
 *  Configuration requires memory management which can block and must
 *  be invoked with interrupts ENABLED (for example, NOT in the interrupt
 *  context NOR with a spin lock -- like IOSimpleLock -- held).
 *
 *  Updates can be performed with interrupts disabled, but clients should
 *  take into account that IOReporters' non-blocking currenency is achieved
 *  with IOSimpleLockLockDisable/UnlockEnableInterrupts(): that is, by
 *  disabling interrupts and taking a spin lock.  While IOReporting will
 *  never hold a lock beyond a call into it, some time may be spent within
 *  the call spin-waiting for the lock.  Clients holding their own
 *  spin locks should carefully consider the impact of IOReporting's
 *  (small) additional latency before calling it while holding a spin lock.
 *
 *  The documentation for each method indicates any concurrency guarantees.
 */


/* source class IOReporter IOReporters.iig:114-311 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*********************************/
/*** 2a. IOReporter Base Class ***/
/*********************************/

class LOCALONLY IOReporter : public OSObject
{
public:

/*! @function   IOReporter::addChannel
 *   @abstract   add an additional, similar channel to the reporter
 *
 *   @param  channelID - identifier for the channel to be added
 *   @param  channelName - an optional human-readble name for the channel
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       The reporter will allocate memory to track a new channel with the
 *       provided ID and name (if any).  Its other traits (type, etc) will
 *       be those provided when the reporter was initialized.  If no channel
 *       name is provided and the channelID consists solely of ASCII bytes,
 *       those bytes (ignoring any NUL bytes) will be used as the
 *       human-readable channel name in user space.  The IOREPORT_MAKEID()
 *       macro in IOReportTypes.h can be used to create ASCII channel IDs.
 *
 *   Locking: same-instance concurrency SAFE, MAY BLOCK
 */
	IOReturn addChannel(uint64_t channelID, const char *channelName = NULL);

/*! @function   IOReporter::createLegend
 *   @abstract   create a legend entry represending this reporter's channels
 *   @result     An IOReportLegendEntry object or NULL on failure.
 *   @discussion
 *       All channels added to the reporter will be represented
 *       in the resulting legend entry.
 *
 *       Legends must be published together as an array under the
 *       kIOReportLegendKey in the I/O Kit registry.  The IOReportLegend
 *       class can be used to properly combine legend entries from multiple
 *       reporters as well as to put channels into groups of interest to
 *       observers.  When published, individual legend entries share
 *       characteristics such as group and sub-group.  Multiple IOReporter
 *       instances are required to produce independent legend entries which
 *       can then be published with different characteristics.
 *
 *       Drivers wishing to publish legends should do so as part of their
 *       ::start() routine.  As superclasses *may* have installed legend
 *       entries, any existing existing legend should be retrieved and
 *       IOReportLegend used to merge it with the new entries.
 *
 *       Recommendations for best practices are forthcoming.
 *
 *       Instead of calling createLegend on your reporter object and then
 *       appending it manually to IOReportLegend, one may prefer to call
 *       IOReportLegend::appendReporterLegend which creates and appends a
 *       reporter's IOReportLegendEntry in a single call.
 *
 *   Locking: same-instance concurrency SAFE, MAY BLOCK
 */
	OSPtr<IOReportLegendEntry> createLegend(void);

/*! @function   IOReporter::configureReport
 *   @abstract   track IOService::configureReport(), provide sizing info
 *
 *   @param  channelList - channels to configure
 *   @param  action - enable/disable/size, etc (see IOReportTypes.h)
 *   @param  result - *incremented* for kIOReportGetDimensions
 *   @param  destination - action-specific default destination
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       Any time a reporting driver's ::configureReport method is invoked,
 *       this method should be invoked on each IOReporter that is being
 *       used by that driver to report channels in channelList.
 *
 *       Any channels in channelList which are not tracked by this reporter
 *       are ignored.  ::configureReport(kIOReportGetDimensions) expects
 *       the full size of all channels, including any reported by
 *       superclasses.  It is valid to call this routine on multiple
 *       reporter objects in succession and they will increment 'result'
 *       to provide the correct total.
 *
 *       In the initial release, this routine is only required to calculate
 *       the response to kIOReportGetDimensions, but in the future it will
 *       will enable functionality like "triggered polling" via
 *       kIOReportNotifyHubOnChange.  Internally, it is already keeping
 *       track of the number of times each channel has been enabled and
 *       disabled.  13073064 tracks adding a method to see whether any
 *       channels are currently being observed.
 *
 *       The static IOReporter::configureAllReports() will call this method
 *       on multiple reporters grouped in an OSSet.
 *
 *   Locking: same-instance concurrency SAFE, MAY BLOCK
 */
	IOReturn configureReport(IOReportChannelList *channelList,
	    IOReportConfigureAction action,
		uint32_t &elementCount);

/*! @function   IOReporter::updateReport
 *   @abstract   Produce standard reply to IOService::updateReport()
 *
 *   @param  channelList - channels to update
 *   @param  action - copy/trace data (see IOReportTypes.h)
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       This method searches channelList for channels tracked by this
 *       reporter, writes the corresponding data into 'destination', and
 *       updates 'result'.  It should be possible to pass a given set of
 *       IOService::updateReport() arguments to any and all reporters as
 *       well as to super::updateReport() and get the right result.
 *
 *       The static IOReporter::updateAllReports() will call this method
 *       on an OSSet of reporters.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn updateReport(IOReportChannelList *channelList,
	    IOReportConfigureAction action,
		uint32_t &elementCount,
		uint8_t *&buffer,
		size_t &capacity);


/*! @function   IOReporter::free
 *   @abstract   Releases the object and all its resources.
 *
 *   @discussion
 *       ::free() [called on last ->release()] assumes that init() [called
 *       by static ::with() methods] has completed successfully.
 *
 *   Locking: same-instance concurrency UNSAFE
 */
	virtual void free(void) override;



/*********************************/
/*** 2b. Useful Static Methods ***/
/*********************************/

/* The following static functions are intended to simplify the management
 * of multiple reporters.  They may be superseded in the future by an
 * IOReportManager class.
 */

/*! @function   IOReporter::configureAllReports
 *   @abstract   call configureReport() on multiple IOReporter objects
 *
 *   @param  reporters - OSSet of IOReporter objects
 *   @param  channelList - full list of channels to configure
 *   @param  action - enable/disable/size, etc
 *   @param  result - action-specific returned value
 *   @param  destination - action-specific default destination
 *   @result     success if all objects successfully complete
 *               IOReporter::configureReport()
 *
 *   @discussion
 *       The OSSet must only contain IOReporter instances.  The presence
 *       of non-IOReporter instances will cause this function to return
 *       kIOReturnBadArgument.  If any reporter returns an error, the
 *       function will immediately return that error.
 *
 *       Per the IOReporter::configureReport() documentation, each
 *       reporter will search channelList for channels it is reporting
 *       and provide a partial response.
 */
	static IOReturn configureAllReports(OSCollection *reporters,
	    OSData *channels,
	    IOReportConfigureAction action,
	    uint32_t *outCount);


/*! @function   IOReporter::updateAllReports
 *   @abstract   call updateReport() on multiple IOReporter objects
 *
 *   @param  reporters - OSSet of IOReporter objects
  *   @param  action - type/style of update
  *   @result     IOReturn code
 *   @discussion
 *       The OSSet must only contain IOReporter instances.  The presence
 *       of non-IOReporter instances will cause this function to return
 *       kIOReturnBadArgument.  If any reporter returns an error, the
 *       function will immediately return that error.
 *
 *       Per the IOReporter::configureReport() documentation, each
 *       reporter will search channelList for channels it is reporting
 *       and provide a partial response.
 */
	static IOReturn updateAllReports(OSCollection *reporters,
		OSData *channels,
	    IOReportConfigureAction action,
		uint32_t *outElementCount,
		uint64_t offset, uint64_t capacity,
		IOMemoryDescriptor *buffer);



};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOReporter IOReporters.iig:114-311 */


#define IOReporter_Methods \
\
public:\
\
    IOReturn\
    addChannel(\
        uint64_t channelID,\
        const char * channelName = NULL);\
\
    OSPtr<IOReportLegendEntry>\
    createLegend(\
);\
\
    IOReturn\
    configureReport(\
        IOReportChannelList * channelList,\
        IOReportConfigureAction action,\
        uint32_t & elementCount);\
\
    IOReturn\
    updateReport(\
        IOReportChannelList * channelList,\
        IOReportConfigureAction action,\
        uint32_t & elementCount,\
        uint8_t *& buffer,\
        size_t & capacity);\
\
    static IOReturn\
    configureAllReports(\
        OSCollection * reporters,\
        OSData * channels,\
        IOReportConfigureAction action,\
        uint32_t * outCount);\
\
    static IOReturn\
    updateAllReports(\
        OSCollection * reporters,\
        OSData * channels,\
        IOReportConfigureAction action,\
        uint32_t * outElementCount,\
        uint64_t offset,\
        uint64_t capacity,\
        IOMemoryDescriptor * buffer);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOReporter_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOReporter_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOReporterMetaClass;
extern const OSClassLoadInformation IOReporter_Class;

class IOReporterMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  IOReporterInterface : public OSInterface
{
public:
};

struct IOReporter_IVars;
struct IOReporter_LocalIVars;

class IOReporter : public OSObject, public IOReporterInterface
{
#if !KERNEL
    friend class IOReporterMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOReporter_DECLARE_IVARS
IOReporter_DECLARE_IVARS
#else /* IOReporter_DECLARE_IVARS */
    union
    {
        IOReporter_IVars * ivars;
        IOReporter_LocalIVars * lvars;
    };
#endif /* IOReporter_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOReporterMetaClass; };
#endif /* KERNEL */

    using super = OSObject;

#if !KERNEL
    IOReporter_Methods
    IOReporter_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOReporters.iig:313-318 */


/************************************/
/***** 3. IOReporter Subclasses *****/
/************************************/

/* source class IOSimpleReporter IOReporters.iig:319-393 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 *   @class      IOSimpleReporter
 *   @abstract   Report simple integers
 *   @discussion
 *       Each IOSimpleReporter can have an arbitrary number of channels,
 *       each publishing a single integer value at any given time.
 */

class LOCALONLY IOSimpleReporter : public IOReporter
{

public:

/*! @function   IOSimpleReporter::with
 *   @abstract   create an initialized simple reporter
 *
 *   @param  reportingService - IOService associated with all channels
 *   @param  categories - The category in which the report should be classified
 *   @param  unit - The unit for the quantity recorded by the reporter object
 *   @result     On success, an instance of IOSimpleReporter, else NULL
 *
 *   @discussion
 *       Creates an instance of IOSimpleReporter object
 *
 *   Locking: SAFE to call concurrently (no static globals), MAY BLOCK.
 */
	static OSPtr<IOSimpleReporter> with(IOService *reportingService,
	    IOReportCategories categories,
	    IOReportUnit unit);

	bool initWith(IOService *reportingService,
	    IOReportCategories categories,
	    IOReportUnit unit);


/*! @function   IOSimpleReporter::setValue
 *   @abstract   Thread safely set a channel's value
 *
 *   @param  channel_id - ID of the channel for which the value needs to be set
 *   @param  value - New channel value
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Updates the value of a channel to the provided value.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setValue(uint64_t channel_id,
	    int64_t value);

/*! @function   IOSimpleReporter::incrementValue
 *   @abstract   Thread safely increment a channel's value by a given amount
 *
 *   @param  channel_id - ID of the channel for which the value needs to be incremented
 *   @param  increment - Amount to be added to the current channel value
 *   @result     Appropriate IOReturn code
 *   @discussion
 *       Increments the value of the channel ID by the provided amount.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn incrementValue(uint64_t channel_id,
	    int64_t increment);

/*! @function   IOSimpleReporter::getValue
 *   @abstract   Thread safely access a channel value
 *
 *   @param  channel_id - ID of the channel to get a value from
 *   @result     Returns the current value stored in the channel
 *   @discussion
 *       Accessor method to a channel's current stored value
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	int64_t getValue(uint64_t channel_id);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOSimpleReporter IOReporters.iig:319-393 */


#define IOSimpleReporter_Methods \
\
public:\
\
    static OSPtr<IOSimpleReporter>\
    with(\
        IOService * reportingService,\
        IOReportCategories categories,\
        IOReportUnit unit);\
\
    bool\
    initWith(\
        IOService * reportingService,\
        IOReportCategories categories,\
        IOReportUnit unit);\
\
    IOReturn\
    setValue(\
        uint64_t channel_id,\
        int64_t value);\
\
    IOReturn\
    incrementValue(\
        uint64_t channel_id,\
        int64_t increment);\
\
    int64_t\
    getValue(\
        uint64_t channel_id);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOSimpleReporter_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOSimpleReporter_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gIOSimpleReporterMetaClass;
extern const OSClassLoadInformation IOSimpleReporter_Class;

class IOSimpleReporterMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  IOSimpleReporterInterface : public OSInterface
{
public:
};

struct IOSimpleReporter_IVars;
struct IOSimpleReporter_LocalIVars;

class IOSimpleReporter : public IOReporter, public IOSimpleReporterInterface
{
#if !KERNEL
    friend class IOSimpleReporterMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOSimpleReporter_DECLARE_IVARS
IOSimpleReporter_DECLARE_IVARS
#else /* IOSimpleReporter_DECLARE_IVARS */
    union
    {
        IOSimpleReporter_IVars * ivars;
        IOSimpleReporter_LocalIVars * lvars;
    };
#endif /* IOSimpleReporter_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOSimpleReporterMetaClass; };
#endif /* KERNEL */

    using super = IOReporter;

#if !KERNEL
    IOSimpleReporter_Methods
    IOSimpleReporter_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOReporters.iig:395-404 */


enum IOStateReporter_valueSelector {
	kInTransitions,
	kResidencyTime,
	kLastTransitionTime
};



/* source class IOStateReporter IOReporters.iig:405-820 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 *   @class      IOStateReporter
 *   @abstract   Report state machine data
 *   @discussion
 *       Each IOStateReporter can report information for an arbitrary number
 *       of similar state machines.  All must have the same number of states.
 */
class LOCALONLY IOStateReporter : public IOReporter
{

public:

/*! @function   IOStateReporter::with
 *   @abstract   State reporter static creation method
 *
 *   @param  reportingService - The I/O Kit service for this reporter's channels
 *   @param  categories - The categories for this reporter's channels
 *   @param  nstates - Maximum number of states for this reporter's channels
 *   @param  unit - optional parameter if using override/increment...()
 *   @result     on success, an IOStateReporter instance, else NULL
 *
 *   @discussion
 *       Creates an instance of IOStateReporter.  The default time scale
 *       is the current system's notion of mach_absolute_time().  Using a
 *       non-default time scale requires the use of
 *       override/incrementChannelState() instead of setState().
 *       setState() always updates using mach_absolute_time().
 *
 *   Locking: SAFE to call concurrently (no static globals), MAY BLOCK
 */
	static OSPtr<IOStateReporter> with(IOService *reportingService,
	    IOReportCategories categories,
	    int nstates,
	    IOReportUnit unit = kIOReportUnitHWTicks);

	bool initWith(IOService *reportingService,
	    IOReportCategories categories,
	    int nstates,
	    IOReportUnit unit = kIOReportUnitHWTicks);

/*! @function   IOStateReporter::setStateID
 *   @abstract   Assign a non-default ID to a state
 *
 *   @param  channel_id - ID of channel containing the state in question
 *   @param  state_index - index of state to give an ID: [0..(nstates-1)]
 *   @param  state_id - 64-bit state ID, for ASCII, use IOREPORT_MAKEID
 *
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       By default, IOStateReporter identifies its channel states by
 *       numbering them from 0 to <nstates - 1>.  If setStateID is not
 *       called to customize the state IDs, the numbered states will be
 *       kept throughout the life of the object and it is safe to reference
 *       those states by their indices.  Otherwise, after setStateID() has
 *       been called, the ordering of states is no longer guaranteed and
 *       the client must reference states by their assigned state ID.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setStateID(uint64_t channel_id,
	    int state_index,
	    uint64_t state_id);

/*! @function   IOStateReporter::setChannelState
 *   @abstract   Updates the current state of a channel to a new state
 *
 *   @param  channel_id - ID of the channel which is updated to a new state
 *   @param  new_state_id - ID of the target state for this channel
 *   @param  last_intransition - deprecated: time of most recent entry
 *   @param  prev_state_residency - deprecated: time spent in previous state
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       setChannelState() updates the amount of time spent in the previous
 *       state (if any) and increments the number of transitions into the
 *       new state.  It also sets the target state's last transition time to
 *       the current time and enables internal time-keeping for the channel.
 *       In this mode, calls like getStateResidencyTime() and updateReport()
 *       automatically update a channel's time in state.
 *
 *       new_state_id identifies the target state as initialized
 *       (0..<nstates-1>) or as configured by setStateID().
 *
 *       Drivers wishing to compute and report their own time in state
 *       should use incrementChannelState() or overrideChannelState().  It
 *       is not currently possible for a driver to synchronize with the
 *       automatic time-keeping enabled by setChannelState().  The
 *       4-argument version of setChannelState() is thus impossible to
 *       use correctly.  In the future, there may be a setChannelState()
 *       which accepts a last_intransition parameter and uses it to
 *       automatically calculate time in state (ERs -> IOReporting / X).
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setChannelState(uint64_t channel_id,
	    uint64_t new_state_id,
	    uint64_t last_intransition,
	    uint64_t prev_state_residency) __deprecated;

/*! @function   IOStateReporter::setChannelState
 *   @abstract   Updates the current state of a channel to a new state
 *
 *   @param  channel_id - ID of the channel which is updated to a new state
 *   @param  new_state_id - ID of the target state for this channel
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       setChannelState() updates the amount of time spent in the previous
 *       state (if any) and increments the number of transitions into the
 *       new state.  It also sets the target state's last transition time to
 *       the current time and enables internal time-keeping for the channel.
 *       In this mode, calls like getStateResidencyTime() and updateReport()
 *       automatically update a channel's time in state.
 *
 *       new_state_id identifies the target state as initialized
 *       (0..<nstates-1>) or as configured by setStateID().
 *
 *       Drivers wishing to compute and report their own time in state
 *       should use incrementChannelState() or overrideChannelState().  It
 *       is not currently possible for a driver to synchronize with the
 *       automatic time-keeping enabled by setChannelState().  The
 *       4-argument version of setChannelState() is thus impossible to
 *       use correctly.  In the future, there may be a setChannelState()
 *       which accepts a last_intransition parameter and uses it to
 *       automatically calculate time in state (ERs -> IOReporting / X).
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setChannelState(uint64_t channel_id,
	    uint64_t new_state_id);


/*! @function   IOStateReporter::setState
 *   @abstract   Updates state for single channel reporters
 *
 *   @param  new_state_id - New state for the channel
 *   @result     Appropriate IOReturn code.
 *
 *   @discussion
 *       setState() is a convenience method for single-channel state
 *       reporter instances.  An error will be returned if the reporter
 *       in question has more than one channel.
 *
 *       See further discussion at setChannelState().
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setState(uint64_t new_state_id);

/*! @function   IOStateReporter::setState
 *   @abstract   Updates state for single channel reporters
 *
 *   @param  new_state_id - New state for the channel
 *   @param  last_intransition - deprecated: time of most recent entry
 *   @param  prev_state_residency - deprecated: spent in previous state
 *   @result     Appropriate IOReturn code.
 *
 *   @discussion
 *       setState() is a convenience method for single-channel state
 *       reporter instances.  An error will be returned if the reporter
 *       in question has more than one channel.
 *
 *       See further discussion at setChannelState().
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setState(uint64_t new_state_id,
	    uint64_t last_intransition,
	    uint64_t prev_state_residency) __deprecated;

/*! @function   IOStateReporter::overrideChannelState
 *   @abstract   Overrides state data for a channel with passed arguments
 *
 *   @param  channel_id - ID of the channel which state is to be updated
 *   @param  state_id - state id for the channel
 *   @param  time_in_state - time used as new total time in state
 *   @param  intransitions - total number of transitions into state
 *   @param  last_intransition - mach_absolute_time of most recent entry (opt)
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       overrideChannelState() sets a particular state's time in state
 *       and transition count to the values provided.  The optional
 *       last_intransition records the last time the channel transitioned
 *       into the given state.  Passing 0 for time_in_state and
 *       intransitions will force the current values to 0.  Passing 0
 *       for last_intransition for all states will disable the notion
 *       of a channel's "current state."
 *
 *       The most recent last_intransition (amongst all states in a channel)
 *       logically determines the current state.  If last_intransition is
 *       not provided for any state, the channel will not report a current
 *       For consistent results, it is important to either never specify
 *       last_intransition or to always specify it.
 *
 *       There is currently a bug in determining current state (13423273).
 *       The IOReportMacros.h macros only update the state's metadata
 *       timestamp and libIOReport only looks at the metadata timestamps
 *       to determine the current state.  Until that bug is fixed, whichever
 *       state is updated most recently will be considered the "current"
 *       state by libIOReport.
 *
 *       ::setState()'s automatic "time in state" updates are not supported
 *       when using overrideChannelState().  Clients must not use
 *       overrideChannelState() on any channel that has ::setState() called
 *       on it.  Unlike with ::setState(), clients using
 *       overrideChannelState() are responsible for ensuring that data is
 *       up to date for updateReport() calls.  The correct way to do this
 *       is for a driver's ::updateReport() method to push the most up to
 *       date values into the reporters before calling
 *       super::updateReport().
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn overrideChannelState(uint64_t channel_id,
	    uint64_t state_id,
	    uint64_t time_in_state,
	    uint64_t intransitions,
	    uint64_t last_intransition = 0);

/*! @function   IOStateReporter::incrementChannelState
 *   @abstract   Updates state data for a channel with passed arguments
 *
 *   @param  channel_id - ID of the channel which state is to be updated
 *   @param  state_id - state id for the channel
 *   @param  time_in_state - time to be accumulated for time in state
 *   @param  intransitions - number of transitions into state to be added
 *   @param  last_intransition - mach_absolute_time of most recent entry (opt)
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       incrementChannelState() adds time_in_state and intransitions
 *       to the current values stored for a particular state.  If provided,
 *       last_intransition overwrites the time the state was most recently
 *       entered.  Passing 0 for time_in_state and intransitions will have
 *       no effect.  Passing 0 for last_intransition for all states will
 *       disable the notion of a channel's "current state."
 *
 *       The most recent last_intransition (amongst all states in a channel)
 *       logically determines the current state.  If last_intransition is
 *       not provided for any state, the channel will not report a current
 *       For consistent results, it is important to either never specify
 *       last_intransition or to always specify it.
 *
 *       There is currently a bug in determining current state (13423273).
 *       The IOReportMacros.h macros only update the state's metadata
 *       timestamp and libIOReport only looks at the metadata timestamps
 *       to determine the current state.  Until that bug is fixed, whichever
 *       state is updated most recently will be considered the "current"
 *       state by libIOReport.
 *
 *       ::setState()'s automatic "time in state" updates are not supported
 *       when using incrementChannelState().  Clients must not use
 *       incrementChannelState() on any channel that has ::setState()
 *       called on it.  Unlike with ::setState(), clients using
 *       incrementChannelState() are responsible for ensuring that data
 *       is up to date for updateReport() calls.  The correct way to do
 *       this is for a driver's ::updateReport() method to push the most
 *       up to date values into the reporters before calling
 *       super::updateReport().
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn incrementChannelState(uint64_t channel_id,
	    uint64_t state_id,
	    uint64_t time_in_state,
	    uint64_t intransitions,
	    uint64_t last_intransition = 0);

/*! @function   IOStateReporter::setStateByIndices
 *   @abstract   update a channel state without validating channel_id
 *
 *   @param  channel_index - 0..<nChannels>, available from getChannelIndex()
 *   @param  new_state_index - New state (by index) for the channel
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Similar to setState(), setStateByIndices() sets a channel's state
 *       without searching for the channel or state IDs.  It will perform
 *       bounds checking, but relies on the caller to properly indicate
 *       the indices of the channel and state.  Clients can rely on channels
 *       being added to IOStateReporter in order: the first channel will
 *       have index 0, the second index 1, etc.  Like ::setState(),
 *       "time in state" calculations are handled automatically.
 *
 *       setStateByIndices() is faster than than setChannelState(), but
 *       it should only be used where the latter's performance overhead
 *       might be a problem.  For example, many channels in a single
 *       reporter and high-frequency state changes.
 *
 *       Drivers wishing to compute and report their own time in state
 *       should use incrementChannelState() or overrideChannelState().  It
 *       is not currently possible for a driver to synchronize with the
 *       automatic time-keeping enabled by setStateByIndices().  The
 *       4-argument version of setChannelState() is thus impossible to
 *       use correctly.  In the future, there may be a setChannelState()
 *       which accepts a last_intransition parameter and uses it to
 *       automatically calculate time in state (ERs -> IOReporting / X).
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setStateByIndices(int channel_index,
	    int new_state_index);

/*! @function   IOStateReporter::setStateByIndices
 *   @abstract   update a channel state without validating channel_id
 *
 *   @param  channel_index - 0..<nChannels>, available from getChannelIndex()
 *   @param  new_state_index - New state (by index) for the channel
 *   @param  last_intransition - deprecated: time of most recent entry
 *   @param  prev_state_residency - deprecated: time spent in previous state
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Similar to setState(), setStateByIndices() sets a channel's state
 *       without searching for the channel or state IDs.  It will perform
 *       bounds checking, but relies on the caller to properly indicate
 *       the indices of the channel and state.  Clients can rely on channels
 *       being added to IOStateReporter in order: the first channel will
 *       have index 0, the second index 1, etc.  Like ::setState(),
 *       "time in state" calculations are handled automatically.
 *
 *       setStateByIndices() is faster than than setChannelState(), but
 *       it should only be used where the latter's performance overhead
 *       might be a problem.  For example, many channels in a single
 *       reporter and high-frequency state changes.
 *
 *       Drivers wishing to compute and report their own time in state
 *       should use incrementChannelState() or overrideChannelState().  It
 *       is not currently possible for a driver to synchronize with the
 *       automatic time-keeping enabled by setStateByIndices().  The
 *       4-argument version of setChannelState() is thus impossible to
 *       use correctly.  In the future, there may be a setChannelState()
 *       which accepts a last_intransition parameter and uses it to
 *       automatically calculate time in state (ERs -> IOReporting / X).
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	IOReturn setStateByIndices(int channel_index,
	    int new_state_index,
	    uint64_t last_intransition,
	    uint64_t prev_state_residency) __deprecated;

/*! @function   IOStateReporter::getStateInTransitions
 *   @abstract   Accessor method for count of transitions into state
 *
 *   @param  channel_id - ID of the channel
 *   @param  state_id - State of the channel
 *   @result     Count of transitions into the requested state.
 *
 *   @discussion
 *       Some clients may need to consume internally the data aggregated by the
 *       reporter object. This method allows a client to retrieve the count of
 *       transitions into the requested state for the channel_id.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	uint64_t getStateInTransitions(uint64_t channel_id,
	    uint64_t state_id);

/*! @function   IOStateReporter::getStateResidencyTime
 *   @abstract   Accessor method for time spent in a given state
 *
 *   @param  channel_id - ID of the channel
 *   @param  state_id - State of the channel
 *   @result     Absolute time spent in specified state
 *
 *   @discussion
 *       Some clients may need to consume internally the data aggregated
 *       by the by the reporter object.  This method allows a client to
 *       retrieve the absolute time a particular channel recorded as spent
 *       in a specified state.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	uint64_t getStateResidencyTime(uint64_t channel_id,
	    uint64_t state_id);

/*! @function   IOStateReporter::getStateLastTransitionTime
 *   @abstract   Accessor method for last time a transition occured
 *
 *   @param  channel_id - ID of the channel
 *   @param  state_id - State of the channel
 *   @result     Absolute time for when the last transition occured
 *
 *   @discussion
 *       Some clients may need to consume internally the data aggregated
 *       by the by the reporter object.  This method allows a client to
 *       retrieve the absolute time stamp for when the last transition into
 *       a specific state was recorded.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	uint64_t getStateLastTransitionTime(uint64_t channel_id, uint64_t state_id);

/*! @function   [DEPRECATED] IOStateReporter::getStateLastChannelUpdateTime
 *   @abstract   Deprecated accessor for last time a channel was auto-updated
 *
 *   @param  channel_id - ID of the channel
 *   @result     Absolute time for last time the channel was updated
 *
 *   @discussion
 *       If a channel has had ::setState() called on it, calls such as
 *       getStateResidencyTime() or updateReport() will update time in the
 *       current state and update an internal "last channel update time."
 *       Because clients have no way to interlock with those methods, there
 *       is no sensible way to use this method and it will be removed in
 *       a future release.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	uint64_t getStateLastChannelUpdateTime(uint64_t channel_id) __deprecated;



};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOStateReporter IOReporters.iig:405-820 */


#define IOStateReporter_Methods \
\
public:\
\
    static OSPtr<IOStateReporter>\
    with(\
        IOService * reportingService,\
        IOReportCategories categories,\
        int nstates,\
        IOReportUnit unit = kIOReportUnitHWTicks);\
\
    bool\
    initWith(\
        IOService * reportingService,\
        IOReportCategories categories,\
        int nstates,\
        IOReportUnit unit = kIOReportUnitHWTicks);\
\
    IOReturn\
    setStateID(\
        uint64_t channel_id,\
        int state_index,\
        uint64_t state_id);\
\
    IOReturn\
    setChannelState(\
        uint64_t channel_id,\
        uint64_t new_state_id,\
        uint64_t last_intransition,\
        uint64_t prev_state_residency);\
\
    IOReturn\
    setChannelState(\
        uint64_t channel_id,\
        uint64_t new_state_id);\
\
    IOReturn\
    setState(\
        uint64_t new_state_id);\
\
    IOReturn\
    setState(\
        uint64_t new_state_id,\
        uint64_t last_intransition,\
        uint64_t prev_state_residency);\
\
    IOReturn\
    overrideChannelState(\
        uint64_t channel_id,\
        uint64_t state_id,\
        uint64_t time_in_state,\
        uint64_t intransitions,\
        uint64_t last_intransition = 0);\
\
    IOReturn\
    incrementChannelState(\
        uint64_t channel_id,\
        uint64_t state_id,\
        uint64_t time_in_state,\
        uint64_t intransitions,\
        uint64_t last_intransition = 0);\
\
    IOReturn\
    setStateByIndices(\
        int channel_index,\
        int new_state_index);\
\
    IOReturn\
    setStateByIndices(\
        int channel_index,\
        int new_state_index,\
        uint64_t last_intransition,\
        uint64_t prev_state_residency);\
\
    uint64_t\
    getStateInTransitions(\
        uint64_t channel_id,\
        uint64_t state_id);\
\
    uint64_t\
    getStateResidencyTime(\
        uint64_t channel_id,\
        uint64_t state_id);\
\
    uint64_t\
    getStateLastTransitionTime(\
        uint64_t channel_id,\
        uint64_t state_id);\
\
    uint64_t\
    getStateLastChannelUpdateTime(\
        uint64_t channel_id);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOStateReporter_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOStateReporter_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gIOStateReporterMetaClass;
extern const OSClassLoadInformation IOStateReporter_Class;

class IOStateReporterMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  IOStateReporterInterface : public OSInterface
{
public:
};

struct IOStateReporter_IVars;
struct IOStateReporter_LocalIVars;

class IOStateReporter : public IOReporter, public IOStateReporterInterface
{
#if !KERNEL
    friend class IOStateReporterMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOStateReporter_DECLARE_IVARS
IOStateReporter_DECLARE_IVARS
#else /* IOStateReporter_DECLARE_IVARS */
    union
    {
        IOStateReporter_IVars * ivars;
        IOStateReporter_LocalIVars * lvars;
    };
#endif /* IOStateReporter_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOStateReporterMetaClass; };
#endif /* KERNEL */

    using super = IOReporter;

#if !KERNEL
    IOStateReporter_Methods
    IOStateReporter_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOReporters.iig:822-823 */


/* source class IOHistogramReporter IOReporters.iig:824-918 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 *   @class      IOHistogramReporter
 *   @abstract   Report histograms of values
 *   @discussion
 *       Each IOHistogramReporter can report one histogram representing
 *       how a given value has changed over time.
 */
class LOCALONLY IOHistogramReporter : public IOReporter
{

public:
/*! @function   IOHistogramReporter::with
 *   @abstract   Initializes the IOHistogramReporter instance variables and data structures
 *
 *   @param  reportingService - The I/O Kit service for this reporter's channels
 *   @param  categories - The categories in which the report should be classified
 *   @param  channelID - uint64_t channel identifier
 *   @param  channelName - rich channel name as char*
 *   @param  unit - The unit for the quantity recorded by the reporter object
 *   @param  nSegments - Number of segments to be extracted from the config data structure
 *   @param  config - Histograms require the caller to pass a configuration by segments
 *   @result     an instance of the IOSimpleReporter object or NULL on error
 *
 *   @discussion
 *       Creates an instance of histogram reporter object.
 *
 *  FIXME: need more explanation of the config
 *
 *       IOHistogramReporter currently only supports a single channel.
 *
 *
 */
	static OSPtr<IOHistogramReporter> with(IOService *reportingService,
	    IOReportCategories categories,
	    uint64_t channelID,
	    const char *channelName,
	    IOReportUnit unit,
	    int nSegments,
	    IOHistogramSegmentConfig *config);

	bool initWith(IOService *reportingService,
	    IOReportCategories categories,
	    uint64_t channelID,
	    const char *channelName,
	    IOReportUnit unit,
	    int nSegments,
	    IOHistogramSegmentConfig *config);

/*! @function   IOHistogramReporter::addChannel
 *   @abstract   Override IOReporter::addChannel(*) to return an error
 *
 *   @result     kIOReturnUnsupported - doesn't support adding channels
 */
	IOReturn
	addChannel(uint64_t channelID, const char *channelName = NULL);


/*! @function   IOHistogramReporter::overrideBucketValues
 *   @abstract   Override values of a bucket at specified index
 *
 *   @param  index - index of bucket to override
 *   @param  bucket_hits - new bucket hits count
 *   @param  bucket_min - new bucket minimum value
 *   @param  bucket_max - new bucket maximum value
 *   @param  bucket_sum - new bucket sum
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Replaces data in the bucket at the specified index with the data pointed
 *       to by bucket. No sanity check is performed on the data. If the index
 *       is out of bounds, kIOReturnBadArgument is returned.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */

	IOReturn overrideBucketValues(unsigned int index,
	    uint64_t bucket_hits,
	    int64_t bucket_min,
	    int64_t bucket_max,
	    int64_t bucket_sum);

/*! @function   IOHistogramReporter::tallyValue
 *   @abstract   Add a new value to the histogram
 *
 *   @param  value - new value to add to the histogram
 *   @result     the index of the affected bucket, or -1 on error
 *
 *   @discussion
 *       The histogram reporter determines in which bucket the value
 *       falls and increments it.  The lowest and highest buckets
 *       extend to negative and positive infinity, respectively.
 *
 *   Locking: same-instance concurrency SAFE, WILL NOT BLOCK
 */
	int tallyValue(int64_t value);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOHistogramReporter IOReporters.iig:824-918 */


#define IOHistogramReporter_Methods \
\
public:\
\
    static OSPtr<IOHistogramReporter>\
    with(\
        IOService * reportingService,\
        IOReportCategories categories,\
        uint64_t channelID,\
        const char * channelName,\
        IOReportUnit unit,\
        int nSegments,\
        IOHistogramSegmentConfig * config);\
\
    bool\
    initWith(\
        IOService * reportingService,\
        IOReportCategories categories,\
        uint64_t channelID,\
        const char * channelName,\
        IOReportUnit unit,\
        int nSegments,\
        IOHistogramSegmentConfig * config);\
\
    IOReturn\
    addChannel(\
        uint64_t channelID,\
        const char * channelName = NULL);\
\
    IOReturn\
    overrideBucketValues(\
        unsigned int index,\
        uint64_t bucket_hits,\
        int64_t bucket_min,\
        int64_t bucket_max,\
        int64_t bucket_sum);\
\
    int\
    tallyValue(\
        int64_t value);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOHistogramReporter_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOHistogramReporter_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gIOHistogramReporterMetaClass;
extern const OSClassLoadInformation IOHistogramReporter_Class;

class IOHistogramReporterMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  IOHistogramReporterInterface : public OSInterface
{
public:
};

struct IOHistogramReporter_IVars;
struct IOHistogramReporter_LocalIVars;

class IOHistogramReporter : public IOReporter, public IOHistogramReporterInterface
{
#if !KERNEL
    friend class IOHistogramReporterMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOHistogramReporter_DECLARE_IVARS
IOHistogramReporter_DECLARE_IVARS
#else /* IOHistogramReporter_DECLARE_IVARS */
    union
    {
        IOHistogramReporter_IVars * ivars;
        IOHistogramReporter_LocalIVars * lvars;
    };
#endif /* IOHistogramReporter_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOHistogramReporterMetaClass; };
#endif /* KERNEL */

    using super = IOReporter;

#if !KERNEL
    IOHistogramReporter_Methods
    IOHistogramReporter_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOReporters.iig:920-925 */


/***********************************/
/***** 4. IOReportLegend Class *****/
/***********************************/

/* source class IOReportLegend IOReporters.iig:926-1075 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 *   @class      IOReportLegend
 *   @abstract   combine legend entries into a complete legend
 *   @discussion
 *       IOReportLegend adds metadata to legend entries and combines them
 *       into a single OSArray that can be published under the
 *       kIOReportLegendKey property in the I/O Kit registry.
 */
class LOCALONLY IOReportLegend : public OSObject
{

public:
/*! @function   IOReportLegend::with
 *   @abstract   Create an instance of IOReportLegend
 *
 *   @param  legend - OSArray of the legend possibly already present in registry
 *   @result     an instance of IOReportLegend, or NULL on failure
 *
 *   @discussion
 *       An IOReporting legend (an OSArray of legend entries) may be already
 *       present in the IORegistry.  Thus the recommended way to publish
 *       new entries is to append to any existing array as follows:
 *       1. call getProperty(kIOReportLegendKey) to get an existing legend.
 *
 *       2a. If it exists
 *       - OSDynamicCast to OSArray
 *       - and pass it to ::with()
 *       IOReportLegend *legendMaker = IOReportLegend::with(legend);
 *       The provided array is retained by IOReportLegend.
 *
 *       2b. If no legend already exists in the registry, pass NULL
 *       IOReportLegend *legend = IOReportLegend::with(NULL);
 *       This latter invocation will cause IOReportLegend to create a new
 *       array internally (also holding one reference).
 *
 *       At the cost of some registry churn, the static
 *       IOReportLegend::addReporterLegend() will handle the above, removing
 *       the need for any direct use of the IOReportLegend class.
 */
	static OSPtr<IOReportLegend> with(OSArray *legend);

/*! @function   IOReportLegend::addLegendEntry
 *   @abstract   Add a new legend entry
 *
 *   @param  legendEntry - entry to be added to the internal legend array
 *   @param  groupName - primary group name for this entry
 *   @param  subGroupName - secondary group name for this entry
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       The entry will be retained as an element of the internal array.
 *       Legend entries are available from reporter objects.  Entries
 *       represent some number of channels with similar properties (such
 *       as group and sub-group).  Multiple legend entries with the same
 *       group names will be aggregated in user space.
 *
 *       Drivers that instantiate their reporter objects in response to
 *       IOService::configureReport(kIOReportDisable) will need to create
 *       temporary reporter objects for the purpose of creating their
 *       legend entries.  User-space legends are tracked by 12836893.
 */
	IOReturn addLegendEntry(IOReportLegendEntry *legendEntry,
	    const char *groupName,
	    const char *subGroupName);

/*! @function   IOReportLegend::addReporterLegend
 *   @abstract   Add a legend entry from a reporter object
 *
 *   @param  reporter - IOReporter to use to extract and append the legend
 *   @param  groupName - primary group name for this entry
 *   @param  subGroupName - secondary group name for this entry
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       An IOReportLegendEntry will be created internally to this method from
 *       the IOReporter object passed in argument. The entry will be released
 *       internally after being appended to the IOReportLegend object.
 *       Legend entries are available from reporter objects.  Entries
 *       represent some number of channels with similar properties (such
 *       as group and sub-group).  Multiple legend entries with the same
 *       group names will be aggregated in user space.
 *
 *       Drivers that instantiate their reporter objects in response to
 *       IOService::configureReport(kIOReportDisable) will need to create
 *       temporary reporter objects for the purpose of creating their
 *       legend entries.  User-space legends are tracked by 12836893.
 *
 *       Locking: same-reportingService and same-IORLegend concurrency UNSAFE
 */
	IOReturn addReporterLegend(IOReporter *reporter,
	    const char *groupName,
	    const char *subGroupName);

/*! @function   IOReportLegend::addReporterLegend
 *   @abstract   Add a legend entry from a reporter object
 *
 *   @param  reportingService - IOService data provider into the reporter object
 *   @param  reporter - IOReporter to use to extract and append the legend
 *   @param  groupName - primary group name for this entry
 *   @param  subGroupName - secondary group name for this entry
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       An IOReportLegendEntry will be created internally to this method from
 *       the IOReporter object passed in argument. The entry will be released
 *       internally after being appended to the IOReportLegend object.
 *       Legend entries are available from reporter objects.  Entries
 *       represent some number of channels with similar properties (such
 *       as group and sub-group).  Multiple legend entries with the same
 *       group names will be aggregated in user space.
 *
 *       Drivers that instantiate their reporter objects in response to
 *       IOService::configureReport(kIOReportDisable) will need to create
 *       temporary reporter objects for the purpose of creating their
 *       legend entries.  User-space legends are tracked by 12836893.
 *
 *       The static version of addReporterLegend adds the reporter's legend
 *       directly to reportingService's kIOReportLegendKey.  It is not
 *       possible to safely update kIOReportLegendKey from multiple threads.
 *
 *       Locking: same-reportingService and same-IORLegend concurrency UNSAFE
 */
	static  IOReturn addReporterLegend(IOService *reportingService,
	    IOReporter *reporter,
	    const char *groupName,
	    const char *subGroupName);

/*! @function   IOReportLegend::getLegend
 *   @abstract   Accessor method to get the legend array
 *
 *   @result     Returns the OSObject holding the legend to be published by the driver
 *   @discussion
 *       This array will include all legend entries added to the object.
 */
	OSArray* getLegend(void);

/*! @function   IOReportLegend::free
 *   @abstract   Frees the IOReportLegend object
 *
 *   @discussion
 *       ::free() cleans up the reporter and anything it allocated.
 *
 *       ::free() releases the internal array (which was either passed
 *       to ::with() or created as a result of ::with(NULL)).  Assuming
 *       the caller extracted the array with getLegend() and published it
 *       in the I/O Kit registry, its ownership will now be with the
 *       registry.
 */
	void free(void) override;

};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOReportLegend IOReporters.iig:926-1075 */


#define IOReportLegend_Methods \
\
public:\
\
    static OSPtr<IOReportLegend>\
    with(\
        OSArray * legend);\
\
    IOReturn\
    addLegendEntry(\
        IOReportLegendEntry * legendEntry,\
        const char * groupName,\
        const char * subGroupName);\
\
    IOReturn\
    addReporterLegend(\
        IOReporter * reporter,\
        const char * groupName,\
        const char * subGroupName);\
\
    static IOReturn\
    addReporterLegend(\
        IOService * reportingService,\
        IOReporter * reporter,\
        const char * groupName,\
        const char * subGroupName);\
\
    OSArray *\
    getLegend(\
);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOReportLegend_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOReportLegend_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOReportLegendMetaClass;
extern const OSClassLoadInformation IOReportLegend_Class;

class IOReportLegendMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  IOReportLegendInterface : public OSInterface
{
public:
};

struct IOReportLegend_IVars;
struct IOReportLegend_LocalIVars;

class IOReportLegend : public OSObject, public IOReportLegendInterface
{
#if !KERNEL
    friend class IOReportLegendMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOReportLegend_DECLARE_IVARS
IOReportLegend_DECLARE_IVARS
#else /* IOReportLegend_DECLARE_IVARS */
    union
    {
        IOReportLegend_IVars * ivars;
        IOReportLegend_LocalIVars * lvars;
    };
#endif /* IOReportLegend_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOReportLegendMetaClass; };
#endif /* KERNEL */

    using super = OSObject;

#if !KERNEL
    IOReportLegend_Methods
    IOReportLegend_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOReporters.iig:1077- */

#endif  /* ! _IOKERNEL_REPORTERS_H_ */
