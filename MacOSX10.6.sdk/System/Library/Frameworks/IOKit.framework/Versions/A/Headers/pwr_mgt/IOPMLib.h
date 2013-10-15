/*
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#include <CoreFoundation/CFArray.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/pwr_mgt/IOPMLibDefs.h>
#include <IOKit/pwr_mgt/IOPMKeys.h>
#include <Availability.h>

#ifndef _IOKIT_PWRMGT_IOPMLIB_
#define _IOKIT_PWRMGT_IOPMLIB_

#ifdef __cplusplus
extern "C" {
#endif

/*!
@header IOPMLib.h
    IOPMLib provides access to common power management facilites, like initiating 
    system sleep, getting current idle timer values, registering for sleep/wake notifications, 
    and preventing system sleep.
*/

/*! @function IOPMFindPowerManagement
    @abstract Finds the Root Power Domain IOService.
    @param master_device_port  Just pass in MACH_PORT_NULL for master device port.
    @result Returns a io_connect_t handle on the root domain. Must be released with IOServiceClose() when done.
 */
io_connect_t IOPMFindPowerManagement( mach_port_t master_device_port )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
    
/*! @function IOPMSetAggressiveness
    @abstract Sets one of the aggressiveness factors in IOKit Power Management.
    @param fb  Representation of the Root Power Domain from IOPMFindPowerManagement.
    @param type Specifies which aggressiveness factor is being set.
    @param aggressiveness New value of the aggressiveness factor.
    @result Returns kIOReturnSuccess or an error condition if request failed.
*/
IOReturn IOPMSetAggressiveness (io_connect_t fb, unsigned long type, unsigned long aggressiveness )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
                            
/*! @function IOPMGetAggressiveness
    @abstract Retrieves the current value of one of the aggressiveness factors in IOKit Power Management.
    @param fb  Representation of the Root Power Domain from IOPMFindPowerManagement.
    @param type Specifies which aggressiveness factor is being retrieved.
    @param aggressiveness Points to where to store the retrieved value of the aggressiveness factor.
    @result Returns kIOReturnSuccess or an error condition if request failed. 
 */
IOReturn IOPMGetAggressiveness ( io_connect_t fb, unsigned long type, unsigned long * aggressiveness )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*! @function IOPMSleepEnabled
    @abstract Tells whether the system supports full sleep, or just doze
    @result Returns true if the system supports sleep, false if some hardware prevents full sleep.
 */
boolean_t IOPMSleepEnabled ( void ) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*! @function IOPMSleepSystem
    @abstract Request that the system initiate sleep.
    @discussion For security purposes, caller must be root or the console user.
    @param fb  Port used to communicate to the kernel,  from IOPMFindPowerManagement.
    @result Returns kIOReturnSuccess or an error condition if request failed.
 */
IOReturn IOPMSleepSystem ( io_connect_t fb ) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*! @function IOPMCopyBatteryInfo
    @abstract Request raw battery data from the system. 
    @discussion WARNING! IOPMCoyBatteryInfo is unsupported on ALL Intel CPU based systems. For PPC CPU based systems, it remains not recommended. For almost all purposes, developers should use the richer IOPowerSources API (with change notifications) instead of using IOPMCopyBatteryInfo. Keys to decipher IOPMCopyBatteryInfo's return CFArray exist in IOPM.h.
    @param masterPort The master port obtained from IOMasterPort(). Just pass MACH_PORT_NULL.
    @param info A CFArray of CFDictionaries containing raw battery data. 
    @result Returns kIOReturnSuccess or an error condition if request failed.
 */
IOReturn IOPMCopyBatteryInfo( mach_port_t masterPort, CFArrayRef * info )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*!
    @functiongroup Notifications
*/    


/*! @function IORegisterApp
    @abstract Connects the caller to an IOService for the purpose of receiving power state change notifications for the device controlled by the IOService.
    @discussion IORegisterApp requires that the IOService of interest implement an IOUserClient. In addition, that IOUserClient must implement the allowPowerChange and cancelPowerChange methods defined in IOPMLibDefs.h. If you're interested in receiving power state notifications from a device without an IOUserClient, try using IOServiceAddInterestNotification with interest type gIOGeneralInterest instead.
    @param refcon Data returned on power state change notifications and not used by the kernel.
    @param theDriver  Representation of the IOService, probably from IOServiceGetMatchingService.
    @param thePortRef Pointer to a port on which the caller will receive power state change notifications. The port is allocated by the calling application.
    @param callback  A c-function which is called during the notification.
    @param notifier  Pointer to a notifier which caller must keep and pass to subsequent call to IODeregisterApp.
    @result Returns a io_connect_t session for the IOService or MACH_PORT_NULL if request failed. Caller must close return value via IOServiceClose() after calling IODeregisterApp on the notifier argument.
*/
io_connect_t IORegisterApp( void * refcon,
                            io_service_t theDriver,
                            IONotificationPortRef * thePortRef,
                            IOServiceInterestCallback callback,
                            io_object_t * notifier )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*! @function IORegisterForSystemPower
    @abstract Connects the caller to the Root Power Domain IOService for the purpose of receiving sleep & wake notifications for the system.
				Does not provide system shutdown and restart notifications.
    @discussion Provides sleep/wake notifications to applications. Requires that applications acknowledge
        some, but not all notifications. Register for sleep/wake notifications will deliver these messages
        over the sleep/wake lifecycle:

            - kIOMessageSystemWillSleep is delivered at the point the system is initiating a 
                non-abortable sleep.
                Callers MUST acknowledge this event by calling @link IOAllowPowerChange @/link.
                If a caller does not acknowledge the sleep notification, the sleep will continue anyway after
                a 30 second timeout (resulting in bad user experience). 
                Delivered before any hardware is powered off.
            - kIOMessageSystemWillPowerOn is delivered at early wakeup time, before most hardware has been
                powered on. Be aware that any attempts to access disk, network, the display, etc. may result
                in errors or blocking your process until those resources become avaiable.
                Caller must NOT acknowledge kIOMessageSystemWillPowerOn; the caller must simply return from its handler.
            - kIOMessageSystemHasPoweredOn is delivered at wakeup completion time, after all device drivers and
                hardware have handled the wakeup event. Expect this event 1-5 or more seconds after initiating
                system awkeup.
                Caller must NOT acknowledge kIOMessageSystemHasPoweredOn; the caller must simply return from its handler.
            - kIOMessageCanSystemSleep indicates the system is pondering an idle sleep, but gives apps the
                chance to veto that sleep attempt. 
                Caller must acknowledge kIOMessageCanSystemSleep by calling @link IOAllowPowerChange @/link
                or @link IOCancelPowerChange @/link. Calling IOAllowPowerChange will not veto the sleep; any
                app that calls IOCancelPowerChange will veto the idle sleep. A kIOMessageCanSystemSleep 
                notification will be followed up to 30 seconds later by a kIOMessageSystemWillSleep message.
                or a kIOMessageSystemWillNotPowerOn message.
            - kIOMessageSystemWillNotPowerOn is delivered when some app client has vetoed an idle sleep
                request. kIOMessageSystemWillNotPowerOn may follow a kIOMessageCanSystemSleep notification,
                but will not otherwise be sent.
                Caller must NOT acknowledge kIOMessageSystemWiillNotPowerOn; the caller must simply return from its handler.
                
        To deregister for sleep/wake notifications, the caller must make two calls, in this order:
            - Call IODeregisterForSystemPower with the 'notifier' argument returned here.
            - Then call IONotificationPortDestroy passing the 'thePortRef' argument
                returned here.
  
  @param refcon Caller may provide data to receive s an argument to 'callback' on power state changes.
    @param thePortRef On return, thePortRef is a pointer to a port on which the caller will receive power state change notifications. The port is allocated by this function and must be later released by the caller (after IODeregisterForSystemPower). 
    @param callback  A c-function which is called during the notification.
    @param notifier  On success, returns a pointer to a unique notifier which caller must keep and pass to a subsequent call to IODeregisterForSystemPower.
    @result Returns a io_connect_t session for the IOPMrootDomain or MACH_PORT_NULL if request failed. Caller must close return value via IOServiceClose() after calling IODeregisterForSystemPower on the notifier argument.
 */
io_connect_t IORegisterForSystemPower ( void * refcon,
                                        IONotificationPortRef * thePortRef,
                                        IOServiceInterestCallback callback,
                                        io_object_t * notifier )
                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;                                        
/* @function IODeregisterApp
    @abstract Disconnects the caller from an IOService after receiving power state change notifications from the IOService. (Caller must also release IORegisterApp's return io_connect_t and returned IONotificationPortRef for complete clean-up).
    @param notifier  An object from IORegisterApp.
    @result Returns kIOReturnSuccess or an error condition if request failed.
 */
IOReturn IODeregisterApp ( io_object_t * notifier ) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*! @function IODeregisterForSystemPower
    @abstract Disconnects the caller from the Root Power Domain IOService after receiving system power state change notifications. (Caller must also destroy the IONotificationPortRef returned from IORegisterForSystemPower.)
    @param notifier  The object returned from IORegisterForSystemPower.
    @result Returns kIOReturnSuccess or an error condition if request failed.
*/
IOReturn IODeregisterForSystemPower ( io_object_t * notifier )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
                            
/*! @function IOAllowPowerChange
    @abstract The caller acknowledges notification of a power state change on a device it has registered for notifications for via IORegisterForSystemPower or IORegisterApp.
    @discussion Must be used when handling kIOMessageCanSystemSleep and kIOMessageSystemWillSleep messages from IOPMrootDomain system power. The caller should not call IOAllowPowerChange in response to any messages 
    except for these two.
    @param kernelPort  Port used to communicate to the kernel,  from IORegisterApp or IORegisterForSystemPower.
    @param notificationID A copy of the notification ID which came as part of the power state change notification being acknowledged.
    @result Returns kIOReturnSuccess or an error condition if request failed.
*/
IOReturn IOAllowPowerChange ( io_connect_t kernelPort, long notificationID )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*! @function IOCancelPowerChange
    @abstract The caller denies an idle system sleep power state change.
    @discussion Should only called in response to kIOMessageCanSystemSleep messages from IOPMrootDomain. IOCancelPowerChange has no meaning for responding to kIOMessageSystemWillSleep (which is non-abortable) or any other messages. 
    
    When an app responds to a kIOMessageCanSystemSleep message by calling IOCancelPowerChange, the app
    vetos the idle sleep request. The system will stay awake. 
    The idle timer will elapse again after a period of inactivity, and the system will
    send out the same kIOMessageCanSystemSleep message, and interested applications will respond gain.
 
    @param kernelPort  Port used to communicate to the kernel,  from IORegisterApp or IORegisterForSystemPower.
    @param notificationID A copy of the notification ID which came as part of the power state change notification being acknowledged.
    @result Returns kIOReturnSuccess or an error condition if request failed.
 */
IOReturn IOCancelPowerChange ( io_connect_t kernelPort, long notificationID )
                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*!
    @functiongroup ScheduledEvents
*/    

/*! @function IOPMSchedulePowerEvent
    @abstract Schedule the machine to wake from sleep, power on, go to sleep, or shutdown. 
    @discussion This event will be added to the system's queue of power events and stored persistently on disk. The sleep and shutdown events present a graphical warning and allow a console user to cancel the event. Must be called as root.
    @param time_to_wake Date and time that the system will power on/off.
    @param my_id A CFStringRef identifying the calling app by CFBundleIdentifier. May be NULL.
    @param type The type of power on you desire, either wake from sleep or power on. Choose from:
                CFSTR(kIOPMAutoWake) == wake machine, 
                CFSTR(kIOPMAutoPowerOn) == power on machine, 
                CFSTR(kIOPMAutoWakeOrPowerOn) == wake or power on,
                CFSTR(kIOPMAutoSleep) == sleep machine, 
                CFSTR(kIOPMAutoShutdown) == power off machine,
                CFSTR(kIOPMAutoRestart) == restart the machine.
    @result kIOReturnSuccess on success, otherwise on failure
*/
IOReturn IOPMSchedulePowerEvent(CFDateRef time_to_wake, CFStringRef my_id, CFStringRef type);

/*! @function IOPMCancelScheduledPowerEvent
    @abstract Cancel a previously scheduled power event.
    @discussion Arguments mirror those to IOPMSchedulePowerEvent. All arguments must match the original arguments from when the power on was scheduled. Must be called as root.
    @param time_to_wake Cancel entry with this date and time.
    @param my_id Cancel entry with this name.
    @param type Type to cancel
    @result kIOReturnSuccess on success, otherwise on failure
*/
IOReturn IOPMCancelScheduledPowerEvent(CFDateRef time_to_wake, CFStringRef my_id, CFStringRef type);

/*! @function IOPMCopyScheduledPowerEvents
    @abstract List all scheduled system power events
    @discussion Returns a CFArray of CFDictionaries of power events. Each CFDictionary  contains keys for CFSTR(kIOPMPowerEventTimeKey), CFSTR(kIOPMPowerEventAppNameKey), and CFSTR(kIOPMPowerEventTypeKey).
    @result A CFArray of CFDictionaries of power events. The CFArray must be released by the caller. NULL if there are no scheduled events.
*/
CFArrayRef IOPMCopyScheduledPowerEvents(void); 



/*!
    @functiongroup Assertions
*/    

    /*
@constant kIOPMAssertionTypeNoIdleSleep
@abstract Use as AssertionType argument to IOPMAssertionCreate. The system will not sleep when enabled (display may sleep).
    */
#define kIOPMAssertionTypeNoIdleSleep                 CFSTR("NoIdleSleepAssertion")

    /*
@constant kIOPMAssertionTypeNoDisplaySleep
@abstract Use as AssertionType argument to IOPMAssertionCreate. The display will not sleep when enabled (consequently the system will not sleep).
    */
#define kIOPMAssertionTypeNoDisplaySleep              CFSTR("NoDisplaySleepAssertion")

    /*
@typedef IOPMAssertionID
@abstract Type for AssertionID arguments to IOPMAssertionCreate and IOPMAssertionRelease
    */
typedef uint32_t IOPMAssertionID;

    /*
@constant kIOPMNullAssertionID
@abstract This value represents a non-initialized assertion ID
    */
enum {
    kIOPMNullAssertionID = 0
};

    /*
@typedef IOPMAssertionLevel
@abstract Type for AssertionLevel argument to IOPMAssertionCreate
    */
typedef uint32_t IOPMAssertionLevel;

    /*
@enum Assertion Levels
    */
enum {
    /*
    @constant kIOPMAssertionLevelOff
    @abstract Level for a disabled assertion, passed as an argument to IOPMAssertionCreate
    */
    kIOPMAssertionLevelOff = 0,

    /*
    @constant kIOPMAssertionLevelOn
    @abstract Level for an enabled assertion, passed as an argument to IOPMAssertionCreate
    */
    kIOPMAssertionLevelOn  = 255
 };

// Use these keys to examine assertion dictionaries returned
// in IOPMCopyAssertionsByProcess() return value.
    /*
@constant kIOPMAssertionTypeKey
@abstract The CFDictionary key for assertion type in dictionaries returned by IOPMCopyAssertionsByProcess.
    */
#define kIOPMAssertionTypeKey       CFSTR("AssertType")

    /*
@constant kIOPMAssertionLevelKey
@abstract The CFDictionary key for assertion level in dictionaries returned by IOPMCopyAssertionsByProcess.
    */
#define kIOPMAssertionLevelKey      CFSTR("AssertLevel")

    /*
 @constant kIOPMAssertionNameKey
 @abstract The CFDictionary key for assertion name in dictionaries returned by IOPMCopyAssertionsByProcess.
 @discussion Name is specified by the assertion creator, and reflects the calling process and 
    the activity being handled by the assertion.
    */
 #define kIOPMAssertionNameKey      CFSTR("AssertName")


    /*!
@function IOPMAssertionCreate
@abstract Dynamically requests a system behavior from the power management system.
@discussion IOPMAssertionCreate is deprecated in favor of IOPMAssertionCreateWithName. Please
        use the named portion of this API instead for greater accountability.
        No special privileges necessary to make this call - any process may
        activate a power assertion.
@param AssertionType The CFString assertion type to request from the PM system.
@param AssertionLevel Pass kIOPMAssertionLevelOn or kIOPMAssertionLevelOff.
@param AssertionID On success, a unique id will be returned in this parameter.
@result Returns kIOReturnSuccess on success, any other return indicates
        PM could not successfully activate the specified assertion.
     */
IOReturn IOPMAssertionCreate(CFStringRef        AssertionType, 
                           IOPMAssertionLevel   AssertionLevel,
                           IOPMAssertionID      *AssertionID)
                            __OSX_AVAILABLE_BUT_DEPRECATED
                            (__MAC_10_5,__MAC_10_6,__IPHONE_2_0, __IPHONE_2_1);

    /*!
@function IOPMAssertionCreateWithName
@abstract Dynamically requests a system behavior from the power management system.
@discussion No special privileges necessary to make this call - any process may
        activate a power assertion. Caller must specify an AssertionName - NULL is not
        a valid input.
@param AssertionType The CFString assertion type to request from the PM system.
@param AssertionLevel Pass kIOPMAssertionLevelOn or kIOPMAssertionLevelOff.
@param AssertionName A string that describes the name of the caller and the activity being
        handled by this assertion (e.g. "Mail Compacting Mailboxes"). Name may be no longer 
        than 128 characters.
@param AssertionID On success, a unique id will be returned in this parameter.
@result Returns kIOReturnSuccess on success, any other return indicates
        PM could not successfully activate the specified assertion.
     */
IOReturn IOPMAssertionCreateWithName(
                        CFStringRef          AssertionType, 
                        IOPMAssertionLevel   AssertionLevel,
                        CFStringRef          AssertionName,
                        IOPMAssertionID      *AssertionID)
                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;                           
                           
    /*!
@function IOPMAssertionRelease
@abstract Releases the behavior requested in IOPMAssertionCreate
@discussion All calls to IOPMAssertionCreate must be paired with calls to IOPMAssertionRelease.
@param AssertionID The assertion_id, returned from IOPMAssertionCreate, to cancel.
@result Returns kIOReturnSuccess on success
     */
IOReturn IOPMAssertionRelease(IOPMAssertionID AssertionID)
                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

    /*!
@function IOPMCopyAssertionsByProcess
@abstract Returns a dictionary mapping processes to the assertions they are holding active.
@discussion Notes: One process may have multiple assertions. Several processes may
            have asserted the same assertion to different levels.
@param AssertionsByPID On success, this returns a dictionary of assertions per process.
        At the top level, keys to the CFDictionary are pids stored as CFNumbers (kCFNumberIntType).
        The value associated with each CFNumber pid is a CFArray of active assertions.
        Each entry in the CFArray is an assertion represented as a CFDictionary. See the keys
        kIOPMAssertionTypeKey and kIOPMAssertionLevelKey. 
        Caller must CFRelease() this dictionary when done.
@result Returns kIOReturnSuccess on success.
     */
IOReturn IOPMCopyAssertionsByProcess(CFDictionaryRef *AssertionsByPID)
                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

    /*!
@function IOPMCopyAssertionsStatus
@abstract Returns a list of available assertions and their system-wide level.
@discussion Notes: One process may have multiple assertions. Several processes may
            have asserted the same assertion to different levels. The system-wide level is the
            maximum of these assertions' levels.
@param AssertionsStatus On success, this returns a CFDictionary of all assertions currently available.
       The keys in the dictionary are the assertion types, and the value of each is a CFNumber that
       represents the aggregate level for that assertion.  Caller must CFRelease() this dictionary when done.
@result Returns kIOReturnSuccess on success.
     */
IOReturn IOPMCopyAssertionsStatus(CFDictionaryRef *AssertionsStatus)
                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 * @functiongroup IOSystemLoadAdvisory
 */

/*! @constant kIOSystemLoadAdvisoryNotifyName
   @abstract The notifcation by this name fires when system "SystemLoadAdvisory" status changes.
   @discussion Pass this string as an argument to register via notify(3).
            You can query SystemLoadAdvisory state via notify_get_state() when this notification
            fires - this is more efficient than calling IOGetSystemLoadAdvisory(), and returns
            an identical combined SystemLoadAdvisory value.
 */
#define kIOSystemLoadAdvisoryNotifyName   "com.apple.system.powermanagement.SystemLoadAdvisory"

/*! @typedef IOSystemLoadAdvisoryLevel
   @abstract Return type for IOGetSystemLoadAdvisory
   @discussion Value is one of kIOSystemLoadAdvisoryLevelGreat, kIOSystemLoadAdvisoryLevelOK,
       or kIOSystemLoadAdvisoryLevelBad.
 */
typedef int IOSystemLoadAdvisoryLevel;

enum {
    kIOSystemLoadAdvisoryLevelBad       = 1,
    kIOSystemLoadAdvisoryLevelOK        = 2,
    kIOSystemLoadAdvisoryLevelGreat     = 3
};

/*! @constant kIOSystemLoadAdvisoryUserLevelKey
   @abstract Key for dictionary returned by IOCopySystemLoadAdvisoryDetailed
   @discussion Indicates user activity constraints on the current SystemLoadAdvisory level.
 */
#define kIOSystemLoadAdvisoryUserLevelKey             CFSTR("UserLevel")

/*! @constant kIOSystemLoadAdvisoryBatteryLevelKey
   @abstract Key for dictionary returned by IOCopySystemLoadAdvisoryDetailed
   @discussion Indicates battery constraints on the current SystemLoadAdvisory level.
 */
#define kIOSystemLoadAdvisoryBatteryLevelKey          CFSTR("BatteryLevel")

/*! @constant kIOSystemLoadAdvisoryThermalLevelKey
   @abstract Key for dictionary returned by IOCopySystemLoadAdvisoryDetailed
   @discussion Indicates thermal constraints on the current SystemLoadAdvisory level.
 */
#define kIOSystemLoadAdvisoryThermalLevelKey          CFSTR("ThermalLevel")

/*! @constant kIOSystemLoadAdvisoryCombinedLevelKey
   @abstract Key for dictionary returned by IOCopySystemLoadAdvisoryDetailed
   @discussion Provides a combined level based on UserLevel, BatteryLevel,
        and ThermalLevels; the combined level is the minimum of these levels. 
        In the future, this combined level may represent new levels as well.
        The combined level is identical to the value returned by IOGetSystemLoadAdvisory().
 */
#define kIOSystemLoadAdvisoryCombinedLevelKey         CFSTR("CombinedLevel")

/*! @function IOGetSystemLoadAdvisory
   @abstract Returns a hint about whether now would be a good time to perform time-insensitive 
        work.
   @discussion Based on user and system load, IOGetSystemLoadAdvisory determines "better" and "worse"
   times to run optional or time-insensitive CPU or disk work.
    
   Applications may use this result to avoid degrading the user experience. If it is a 
   "Bad" or "OK" time to perform work, applications should slow down and perform work
   less aggressively.
   
   There is no guarantee that the system will ever be in "Great" condition to perform work -
   all essential work must still be performed even in "Bad", or "OK" times. 
   Completely optional work, such as updating caches, may be postponed indefinitely.
   
   Note: You may more efficiently read the SystemLoadAdvisory level using notify_get_state() instead
        of IOGetSystemLoadAdvisory. The results are identical. notify_get_state() requires that you
        pass the token argument received by registering for SystemLoadAdvisory notifications.
   
   @return IOSystemLoadAdvisoryLevel - one of:
        kIOSystemLoadAdvisoryLevelGreat - A Good time to perform time-insensitive work.
        kIOSystemLoadAdvisoryLevelOK - An OK time to perform time-insensitive work.
        kIOSystemLoadAdvisoryLevelBad - A Bad time to perform time-insensitive work.
 */
   
IOSystemLoadAdvisoryLevel IOGetSystemLoadAdvisory( void );

/*! @function IOCopySystemLoadAdvisoryDetailed
   @abstract Indicates how user activity, battery level, and thermal level each 
        contribute to the overall "SystemLoadAdvisory" level. In the future, 
        this combined level may represent new levels as well.
   @discussion See dictionary keys defined above.
   @return Returns a CFDictionaryRef, or NULL on error. Caller must release the
        returned dictionary.
 */
CFDictionaryRef IOCopySystemLoadAdvisoryDetailed(void);



#ifdef __cplusplus
}
#endif

#endif
