/*
 * Copyright (c) 2012-2013 Apple Computer, Inc.  All Rights Reserved.
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

#ifndef _IOEPORTERDEFS_H
#define _IOEPORTERDEFS_H

#include <DriverKit/OSSharedPtr.h>
#include <DriverKit/IOReporters.h>

//#include "IOReportHubCommon.h"

//#define IORDEBUG_IOLOG

#if defined(IORDEBUG_IOLOG)
#define IORLOG(fmt, args...)    \
do {                            \
    IOLog((fmt), ##args);         \
} while(0)

#else
#define IORLOG(fmt, args...)
#endif

#define IORERROR_LOG

#ifdef IORERROR_LOG
#define IORERROR(fmt, args...) IOLog(fmt, ##args);
#else
#define IORERROR(fmt, args...)
#endif

// overflow detection routines
#if (SIZE_T_MAX < INT_MAX)
#error "(SIZE_T_MAX < INT_MAX) -> PREFL_MEMOP_*()) unsafe for size_t"
#endif

//#define panic(...) ({IOLog(__VA_ARGS__); abort();})

#define PREFL_MEMOP_FAIL(__val, __type) do {  \
    if (__val <= 0) {  \
	IORERROR("%s - %s <= 0!\n", __func__, #__val);  \
	res = kIOReturnUnderrun;  \
	goto finish;  \
    }  else if (__val > INT_MAX / (int)sizeof(__type)) {  \
	IORERROR("%s - %s > INT_MAX / sizeof(%s)!\n",__func__,#__val,#__type);\
	res = kIOReturnOverrun;  \
	goto finish;  \
    }  \
} while(0)

#define PREFL_MEMOP_PANIC(__val, __type) do {  \
    if (__val <= 0) {  \
	panic("%s - %s <= 0!", __func__, #__val);  \
    }  else if (__val > INT_MAX / (int)sizeof(__type)) {  \
	panic("%s - %s > INT_MAX / sizeof(%s)!", __func__, #__val, #__type);  \
    }  \
} while(0)

//#include "IOReportHubCommon.h"//



#define IOREPORTER_DEBUG_ELEMENT(idx)                                   \
do {                                                                    \
IOLog("IOReporter::DrvID: %llx | Elt:[%3d] |ID: %llx |Ticks: %llu |",   \
ivars->elements[idx].provider_id,                                             \
idx,                                                                    \
ivars->elements[idx].channel_id,                                              \
ivars->elements[idx].timestamp);                                              \
IOLog("0: %llu | 1: %llu | 2: %llu | 3: %llu\n",                        \
ivars->elements[idx].values.v[0],                                             \
ivars->elements[idx].values.v[1],                                             \
ivars->elements[idx].values.v[2],                                             \
ivars->elements[idx].values.v[3]);                                            \
} while(0)



#if PRIVATE_WIFI_ONLY
#define HIDDEN
#else /* PRIVATE_WIFI_ONLY */
#define HIDDEN __attribute__((visibility("hidden")))
#endif /* !PRIVATE_WIFI_ONLY */

struct HIDDEN IOReporter_IVars  {

	IOReportChannelType channelType;
	uint64_t driver_id;     // driver reporting data

	// IOHistogramReporter accesses these; need to re-do its instantiation
	IOReportElement *elements;
	int *enableCounts;  // refcount kIOReportEnable/Disable
	uint16_t channelDimension;// Max channel size
	int nElements;
	int nChannels;     // Total Channels in this reporter
	OSArray *channelNames;

	// MUST be protected because check is a macro!
	bool reporterIsLocked;
	bool reporterConfigIsLocked;

	// Required for swapping inside addChannel
	IOReportElement *swapElements;
	int *swapEnableCounts;

	IOReportUnit unit;
	int enabled;// 'enabled' if _enabled > 0
	IOLock *configLock;
	IOLock *reporterLock;


    bool valid() {
        return channelType.report_format != kIOReportInvalidFormat;
    }

/*! @function   IOReporter_IVars
 *  @abstract   constructor
 *
 *   @param  reportingService - IOService associated with all channels
 *   @param  channelType - type info for all channels (element_idx = 0)
 *   @param  unit - description applied for all channels
  *
 *   @discussion
 *       init() establishes the parameters of all channels for this reporter
 *       instance. Any channels added via addChannel() will be of this type
 *       and have this unit.
 *
 *       IOReporter clients should use the static <subclass>::with() methods
 *       below to obtain fully-initialized reporter instances.  ::free()
 *       expects ::init() to have completed successfully.  On failure, any
 *       allocations are cleaned up.
 *
 *   Locking: same-instance concurrency UNSAFE
 */
	IOReporter_IVars(IOService *reportingService,
	                 IOReportChannelType channelType,
		     IOReportUnit unit);


    virtual ~IOReporter_IVars();


/*! @function   IOReporter::lockReporterConfig
 *   @function   IOReporter::unlockReporterConfig
 *   @abstract   prevent concurrent reconfiguration of a reporter
 *
 *   @discussion
 *       lockReporterConfig() takes a mutex-based lock intended to prevent
 *       concurrent access to the reporter's configuration.  It is not
 *       intended to prevent updates to the reporter's data.  As long as
 *       all other requirements are met, it is safe to simultaneously hold
 *       both the configuration and data locks on a single reporter.
 *
 *       lockReporterConfig() is used by routines such as addChannel().
 *       See also lockReporter() and ::handle*Swap*() below.
 */
	void lockReporterConfig(void);
	void unlockReporterConfig(void);

/*! @function   IOReporter::lockReporter
 *   @function   IOReporter::unlockReporter
 *   @abstract   prevent concurrent access to a reporter's data
 *
 *   @discussion
 *       This method grabs a lock intended to control access the reporter's
 *       reporting data.  Sub-classes maninupating internal report values
 *       must make sure the reporter is locked (usually by the most generic
 *       public interface) before calling getElementValues(),
 *       copyElementValues(), or setElementValues().
 *
 *       Subclasses should ensure that this lock is taken exactly once
 *       before directly accessing reporter data.  For example,
 *       [virtual] IOFooReporter::handleSetFoo(.) {
 *           // assert(lock_held)
 *           getElementValues(1..)
 *           getElementValues(3..)
 *           getElementValues(5..)
 *           [calculate]
 *           setElementValues(6..)
 *       }
 *       IOFooReporter::setFoo(.) {      // not virtual
 *           lockReporter()
 *           handleSetFoo(.)
 *           unlockReporter()
 *       }
 *
 *       IOReporter::handle*() use lockReporter() similarly.  For example,
 *       the lock is taken by IOReporter::updateReport() and is already
 *       held by the time any ::updateChannelValues() methods are called.
 *
 *       Subclasses cannot call this routine if the lock is already held.
 *       That's why IOReporting generally only calls it from non-virtual
 *       public methods.  In particular, this method should not be called
 *       it from ::handle*() methods which exist to allow override after
 *       the lock is taken.
 *
 *       Because lockReporter() uses a spin lock, it is SAFE to use in the
 *       interrupt context.  For the same reason, however, it is UNSAFE
 *       to perform any blocking blocking operations (including memory
 *       allocations) while holding this lock.
 */
	void lockReporter(void);
	void unlockReporter(void);

/*!
 *   @discussion
 *       The ::handle*Swap* functions allow subclasses to safely reconfigure
 *       their internal state.  A non-virtual function handles locking
 *       and invokes the functions in order:
 *       - lockReporterConfig()  // protecting instance vars but not content
 *       - prepare / allocate buffers of the new size
 *       - if error, bail (unlocking, of course)
 *
 *       - lockReporter()        // protecting data / blocking updates
 *       - swap: preserve continuing data / install new buffers
 *       - unlockReporter()
 *
 *       - deallocate now-unused buffers
 *       - unlockReporterConfig()
 */


/*! @function   IOReporter::handleSwapPrepare
 *   @abstract   allocate memory in preparation for an instance variable swap
 *
 *   @param newNChannels   target number of channels
 *   @result     IOReturn code
 *
 *   @discussion
 *       ::handleSwapPrepare() is responsible for allocating appropriately-
 *       sized buffers (based on the new number of channels) and storing
 *       them in _swap* instance variables.  If returning and error, it
 *       must deallocate any buffers and set to NULL any _swap* variables.
 *
 *   Locking: The caller must ensure that the *config* lock is HELD but
 *            that the reporter (data) lock is *NOT HELD*.
 */
	virtual IOReturn handleSwapPrepare(int newNChannels);

/*! @function   IOReporter::handleAddChannelSwap
 *   @abstract   update primary instance variables with new buffers
 *
 *   @param channel_id   ID of channel being added
 *   @param symChannelName   optional channel name, in an allocated object
 *   @result     IOReturn code
 *
 *   @discussion
 *       handlAddChannelSwap() replaces the primary instance variables
 *       with buffers allocated in handlePrepareSwap().  It copies the the
 *       existing data into the appropriate portion of the new buffers.
 *       Because it is specific to adding one channel, it assumes that the
 *       target number of channels is one greater than the current value
 *       of _nChannels.
 *
 *       IOReporter::handleAddChannelSwap() increments _nElements and
 *       _nChannels.  To ensure that these variables describe the current
 *       buffers throughout ::handle*Swap(), subclasses overriding this
 *       method should call super::handleAddChannelSwap() after swapping
 *       their own instance variables.
 *
 *       If returning an error, all implementations should leave their
 *       instance variables as they found them (*unswapped*).  That ensures
 *       handleSwapCleanup() cleans up the unused buffers regardless of
 *       whether the swap was complete.
 *
 *       Pseudo-code incorporating these suggestions:
 *       res = <err>; swapComplete = false;
 *       if (<unexpected>)       goto finish
 *       tmpBuf = _primaryBuf; _primaryBuf = _swapBuf; _swapBuf = _primaryBuf;
 *       ...
 *       swapComplete = true;
 *       res = super::handle*Swap()
 *       ...
 *       finish:
 *       if (res && swapComplete)    // unswap
 *
 *   Locking: The caller must ensure that BOTH the configuration and
 *            reporter (data) locks are HELD.
 */
	virtual IOReturn handleAddChannelSwap(uint64_t channel_id,
	    const OSString *symChannelName);

/*! @function   IOReporter::handleSwapCleanup
 *   @abstract   release and forget unused buffers
 *
 *   @param swapNChannels   channel-relative size of the _swap buffers
 *
 *   @discussion
 *       ::handleSwapCleanup() is responsible for deallocating the buffers
 *       no longer used after a swap.  It must always be called if
 *       SwapPrepare() completes successfully.  Because bufers may be
 *       swapped in and out of existance, the _swap* variables may be
 *       NULL and should be set to NULL when complete.
 *
 *   Locking: The caller must ensure that the *config* lock is HELD but
 *            that the reporter (data) lock is *NOT HELD*.
 */
	virtual void handleSwapCleanup(int swapNChannels);

/*! @function   IOReporter::handleConfigureReport
 *   @abstract   override vector for IOReporter::configureReport()
 *               [parameters and result should exactly match]
 *
 *   @discussion
 *       The public base class method takes the reporter lock, calls this
 *       function, and then drops the lock.  Subclasses should not call
 *       this function directly.
 */
	virtual IOReturn handleConfigureReport(IOReportChannelList *channelList,
	    IOReportConfigureAction action,
		uint32_t &elementCount);

/*! @function   IOReporter::handleUpdateReport
 *   @abstract   override vector for IOReporter::updateReport()
 *               [parameters and result should exactly match]
 *
 *   @discussion
 *       The public base class method takes the reporter lock, calls this
 *       function, and then drops the lock.  Subclasses should not call
 *       this function directly.
 *
 *       This function may be overriden but the common case should be to
 *       simply update reporter's specific values by overriding
 *       IOReporter::updateChannelValues().
 */
	virtual IOReturn handleUpdateReport(IOReportChannelList *channelList,
	    IOReportConfigureAction action,
		uint32_t  &elementCount,
		uint8_t *&buffer,
		size_t &capacity);

/*  @function   IOReporter::handleCreateLegend
 *   @abstract   override vector for IOReporter::createLegend()
 *               [parameters and result should exactly match]
 *
 *   @discussion
 *       The public base class method takes the reporter lock, calls this
 *       function, and then drops the lock.  Subclasses should not call
 *       this function directly.
 */
	virtual OSSharedPtr<IOReportLegendEntry> handleCreateLegend(void);

/*! @function   IOReporter::updateChannelValues
 *   @abstract   update channel values for IOReporter::updateReport()
 *
 *   @param  channel_index - logical (internal) index of the channel
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       Internal reporter method to allow a subclass to update channel
 *       data when updateReport() is called.  This routine handles the
 *       common case of a subclass needing to refresh state in response
 *       to IOReporter::updateReport().  It saves the complexity of
 *       parsing the full parameters to IOReporter::updateReport().
 *
 *       The IOReporter base class implementation does not do anything
 *       except return success.
 *
 *   Locking: IOReporter::updateReport() takes the reporter lock,
 *            determines the indices involved, calls this function, and
 *            then proceeds to provide values to the caller.  If subclasses
 *            need to call this routine directly, they must ensure that
 *            the reporter (data) lock is held: see
 *            IOReporter::lockReporter().
 */
	virtual IOReturn updateChannelValues(int channel_index);


/*! @function   IOReporter::updateReportChannel
 *   @abstract   Internal method to extract channel data to a destination
 *
 *   @param  channel_index - offset into internal elements array
 *   @param  elementCount - incremented by the number of IOReportElements added
 *   @result     IOReturn code
 *
 *   @discussion
 *       updateReportChannel() is used to extract a single channel's
 *       data to the updateReport() destination.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	IOReturn updateReportChannel(int channel_index,
	    uint32_t &elementCount,
		uint8_t *&buffer,
		size_t &capacity);


/*! @function   IOReporter::setElementValues
 *   @abstract   Atomically update a specific member of _elements[].
 *
 *   @param  element_index - index of the _element in internal array
 *   @param  values - IORepoterElementValues to replace those at _elements[idx]
 *   @param  record_time - optional mach_absolute_time to be used for metadata
 *   @result     IOReturn code
 *
 *   @discussion
 *       element_index can be obtained from getFirstElementIndex().  If
 *       record_time is not provided, IOReporter::setElementValues() will
 *       fetch the current mach_absolute_time.  If the current time is
 *       already known, it is more efficient to pass it along.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	virtual IOReturn setElementValues(int element_index,
	    IOReportElementValues *values,
	    uint64_t record_time = 0);

/*! @function   IOReporter::getElementValues
 *   @abstract   Internal method to directly access the values of an element
 *
 *   @param  element_index - index of the _element in internal array
 *   @result     A pointer to the element values requested or NULL on failure
 *
 *   @discussion Locking: Caller must ensure that the reporter (data) lock is held.
 *   The returned pointer is only valid until unlockReporter() is called.
 */
	virtual const IOReportElementValues* getElementValues(int element_index);

/*! @function   IOReporter::getFirstElementIndex
 *   @abstract   Returns the first element index for a channel
 *
 *   @param  channel_id - ID of the channel
 *   @param  element_index - pointer to the returned element_index
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       For efficiently and thread-safely reading _elements
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	virtual IOReturn getFirstElementIndex(uint64_t channel_id,
	    int *element_index);

/*! @function   IOReporter::getChannelIndex
 *   @abstract   Returns the index of a channel from internal data structures
 *
 *   @param  channel_id - ID of the channel
 *   @param  channel_index - pointer to the returned element_index
 *   @result     appropriate IOReturn code
 *
 *   @discussion
 *       For efficiently and thread-safely reading channels
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	virtual IOReturn getChannelIndex(uint64_t channel_id,
	    int *channel_index);

/*! @function   IOReporter::getChannelIndices
 *   @abstract   Returns the index of a channel and its corresponding
 *               first element index from internal data structure
 *
 *    @param  channel_id - ID of the channel
 *    @param  channel_index - pointer to the returned channel_index
 *    @param  element_index - pointer to the returned element_index
 *    @result     appropriate IOReturn code
 *
 *    @discussion
 *       For efficiently and thread-safely reading channel elements.
 *       It is commonly useful to get access to both channel and element
 *       indices togther.  This convenience method allows sub-classes to
 *       get both indices simultaneously.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	virtual IOReturn getChannelIndices(uint64_t channel_id,
	    int *channel_index,
	    int *element_index);

/*! @function   IOReporter::copyElementValues
 *   @abstract   Copies the values of an internal element to *elementValues
 *
 *   @param  element_index - Index of the element to return values from
 *   @param  elementValues - For returning the content of element values
 *   @result     Returns the content of an element
 *
 *   @discussion
 *       For efficiently and thread-safely reading _elements.
 *       May need to find the index of the element first.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	virtual IOReturn copyElementValues(int element_index,
	    IOReportElementValues *elementValues);

/*! @function   IOReporter::copyChannelIDs
 *   @abstract   return an an OSArray of the reporter's
 *               channel IDs
 *
 *   @result     An OSArray of the repoter's channel ID's as OSNumbers
 *
 *   @discussion
 *       This method is an internal helper function used to prepare a
 *       legend entry.  It encapsulates the channel IDs in OSNumbers and
 *       aggregates them in an OSArray used when building the IOReportLegend
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	OSSharedPtr<OSArray> copyChannelIDs(void);

/*! @function   IOReporter_IVars::legendWith
 *   @abstract   Internal method to help create legend entries
 *
 *   @param  channelIDs - OSArray of OSNumber(uint64_t) channels IDs.
 *   @param  channelNames - parrallel OSArray of OSSymbol(rich names)
 *   @param  channelType - the type of all channels in this legend
 *   @param  unit - The unit for the quantity recorded by this reporter object
 *
 *   @result     An IOReportLegendEntry object or NULL on failure
 *
 *   @discussion
 *       This static method is the main legend creation function. It is called by
 *       IOReporter sub-classes and is responsible for building an
 *       IOReportLegendEntry corresponding to this reporter object.
 *       This legend entry may be extended by the sub-class of IOReporter if
 *       required.
 *
 *   Locking: SAFE to call concurrently (no static globals), MAY BLOCK
 */
	static OSSharedPtr<IOReportLegendEntry> legendWith(OSArray *channelIDs,
	    OSArray *channelNames,
	    IOReportChannelType channelType,
	    IOReportUnit unit);


};

struct HIDDEN IOHistogramReporter_IVars : public IOReporter_IVars {
	int                         segmentCount;
	int64_t                    *bucketBounds;
	int                         bucketCount;
	IOHistogramSegmentConfig   *histogramSegmentsConfig;


    HIDDEN IOHistogramReporter_IVars(
        IOService *reportingService,
        IOReportChannelType channelType,
        IOReportUnit unit,
        const OSString *channelName,
        IOReportCategories categories,
        uint64_t channelID,
        int nSegments,
        IOHistogramSegmentConfig *config) ;

	HIDDEN virtual OSSharedPtr<IOReportLegendEntry> handleCreateLegend(void) override;

    HIDDEN virtual ~IOHistogramReporter_IVars() override;
};

struct HIDDEN IOSimpleReporter_IVars : public IOReporter_IVars {

	IOSimpleReporter_IVars(IOService *reportingService,
	                       IOReportChannelType channelType,
		                   IOReportUnit unit) : IOReporter_IVars(reportingService, channelType, unit)
    {}

};

struct HIDDEN IOStateReporter_IVars : public IOReporter_IVars {

	int            *currentStates;     // current states (per chonnel)
	uint64_t       *lastUpdateTimes;   // most recent auto-update

    // Required for swapping inside addChannel
	int            *swapCurrentStates;
	uint64_t       *swapLastUpdateTimes;

    HIDDEN IOStateReporter_IVars(
            IOService *reportingService,
            IOReportChannelType channelType,
            IOReportUnit unit,
            IOReportCategories categories,
            int64_t nstates);

	HIDDEN uint64_t _getStateValue(uint64_t channel_id,
	    uint64_t state_id,
	    enum IOStateReporter_valueSelector value);

	HIDDEN IOReturn _getStateIndices(uint64_t channel_id,
	    uint64_t state_id,
	    int *channel_index,
	    int *state_index);

    HIDDEN virtual ~IOStateReporter_IVars() override;
    HIDDEN virtual IOReturn handleSwapPrepare(int newNChannels) override;
    HIDDEN virtual IOReturn handleAddChannelSwap(uint64_t channelID,
                       const OSString *symChannelName) override;
    HIDDEN virtual void handleSwapCleanup(int swapNChannels) override;
    HIDDEN virtual IOReturn updateChannelValues(int channel_index) override;


/*! @function   IOStateReporter::setStateByIndices
 *   @abstract   update a channel state without validating channel_id
 *
 *   @param  channel_index - 0..<nChannels>, available from getChannelIndex()
 *   @param  new_state_index - New state for the channel
 *   @param  last_intransition - to remove: time of most recent entry
 *   @param  prev_state_residency - to remove: time spent in previous state
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Locked version of IOReporter::setStateByIndices().  This method may be
 *       overriden by sub-classes.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	HIDDEN  virtual IOReturn handleSetStateByIndices(int channel_index,
	    int new_state_index,
	    uint64_t last_intransition,
	    uint64_t prev_state_residency);

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
 *       Locked version of IOReporter::setStateID(). This method may be
 *       overriden by sub-classes
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	HIDDEN virtual IOReturn handleSetStateID(uint64_t channel_id,
	    int state_index,
	    uint64_t state_id);

/*! @function   IOStateReporter::handleOverrideChannelStateByIndices
 *   @abstract   Overrides state data for a channel with passed arguments
 *
 *   @param  channel_index - index of the channel which state is to be updated
 *   @param  state_index - index of the state id for the channel
 *   @param  time_in_state - time used as new total time in state
 *   @param  intransitions - total number of transitions into state
 *   @param  last_intransition - mach_absolute_time of most recent entry (opt)
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Locked version of IOReporter::overrideChannelState().  This method
 *       may be overriden by sub-classes.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	HIDDEN virtual IOReturn handleOverrideChannelStateByIndices(int channel_index,
	    int state_index,
	    uint64_t time_in_state,
	    uint64_t intransitions,
	    uint64_t last_intransition = 0);

/*! @function   IOStateReporter::handleIncrementChannelStateByIndices
 *   @abstract   Updates state data for a channel with passed arguments
 *
 *   @param  channel_index - index of the channel which state is to be updated
 *   @param  state_index - index of the state id for the channel
 *   @param  time_in_state - time used as new total time in state
 *   @param  intransitions - total number of transitions into state
 *   @param  last_intransition - mach_absolute_time of most recent entry (opt)
 *   @result     Appropriate IOReturn code
 *
 *   @discussion
 *       Locked version of IOReporter::incrementChannelState(). This method
 *       may be overriden by sub-classes.
 *
 *   Locking: Caller must ensure that the reporter (data) lock is held.
 */
	HIDDEN virtual IOReturn handleIncrementChannelStateByIndices(int channel_index,
	    int state_index,
	    uint64_t time_in_state,
	    uint64_t intransitions,
	    uint64_t last_intransition = 0);
};

struct IVarsInvalidator {
    IOReporter_IVars *ivars;
    IVarsInvalidator(IOReporter_IVars &ivars) : ivars(&ivars) {}
    ~IVarsInvalidator() {
        if (ivars) {
            ivars->channelType = {};
        }
    }
    void disarm() {
        ivars = nullptr;
    }
};


static inline IOReporter_IVars *get_IOReporter_IVars(IOReporter *p) {
	return p->IOReporter::ivars;
}

static inline IOReporter_IVars *get_IOReporter_IVars(IOReporter_IVars *p) {
	return p;
}

static inline IOHistogramReporter_IVars *get_IOHistogramReporter_IVars(IOHistogramReporter *p) {
	return p->IOHistogramReporter::ivars;
}

static inline IOHistogramReporter_IVars *get_IOHistogramReporter_IVars(IOHistogramReporter_IVars *p) {
	return p;
}

static inline IOStateReporter_IVars *get_IOStateReporter_IVars(IOStateReporter *p) {
	return p->IOStateReporter::ivars;
}

static inline IOStateReporter_IVars *get_IOStateReporter_IVars(IOStateReporter_IVars *p) {
	return p;
}




#define IOREPORTER_CHECK_LOCK()                                         \
do {                                                                    \
    if (!get_IOReporter_IVars(this)->reporterIsLocked) {                 \
	panic("%s was called out of locked context!", __PRETTY_FUNCTION__); \
    }                                                                   \
} while(0)                                                              \

#define IOREPORTER_CHECK_CONFIG_LOCK()                                  \
do {                                                                    \
    if (!get_IOReporter_IVars(this)->reporterConfigIsLocked) {           \
	panic("%s was called out of config locked context!", __PRETTY_FUNCTION__); \
    }                                                                   \
} while(0)                                                              \



#endif /* ! _IOEPORTERDEFS_H */
