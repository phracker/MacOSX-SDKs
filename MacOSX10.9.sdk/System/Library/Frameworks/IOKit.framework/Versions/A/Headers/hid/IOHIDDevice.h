/*
 * Copyright (c) 1999-2008 Apple Computer, Inc.  All Rights Reserved.
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

#ifndef _IOKIT_HID_IOHIDDEVICE_USER_H
#define _IOKIT_HID_IOHIDDEVICE_USER_H

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDBase.h>

/*!
	@header IOHIDDevice
    IOHIDDevice defines a Human Interface Device (HID) object, which interacts 
    with an IOHIDDevicePlugIn object that typically maps to an object in the 
    kernel.  IOHIDDevice is used to communicate with a single HID device in 
    order to obtain or set device properties, element values, and reports.
    IOHIDDevice is also a CFType object and as such conforms to all the 
    conventions expected such object.
    <p>
    This documentation assumes that you have a basic understanding of the 
    material contained in <a href="http://developer.apple.com/documentation/DeviceDrivers/Conceptual/AccessingHardware/index.html"><i>Accessing Hardware From Applications</i></a>
    For definitions of I/O Kit terms used in this documentation, such as 
    matching dictionary, family, and driver, see the overview of I/O Kit terms 
    and concepts n the "Device Access and the I/O Kit" chapter of 
    <i>Accessing Hardware From Applications</i>.

    This documentation also assumes you have read <a href="http://developer.apple.com/documentation/DeviceDrivers/HumanInterfaceDeviceForceFeedback-date.html"><i>Human Interface Device & Force Feedback</i></a>.
    Please review documentation before using this reference.
    <p>
    All of the information described in this document is contained in the header 
    file <font face="Courier New,Courier,Monaco">IOHIDDevice.h</font> found at 
    <font face="Courier New,Courier,Monaco">/System/Library/Frameworks/IOKit.framework/Headers/hid/IOHIDDevice.h</font>.
*/

__BEGIN_DECLS

/*!
	@function   IOHIDDeviceGetTypeID
	@abstract   Returns the type identifier of all IOHIDDevice instances.
*/
CF_EXPORT
CFTypeID IOHIDDeviceGetTypeID(void)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@function   IOHIDDeviceCreate
	@abstract   Creates an element from an io_service_t.
    @discussion The io_service_t passed in this method must reference an object 
                in the kernel of type IOHIDDevice.
    @param      allocator Allocator to be used during creation.
    @param      io_service_t Reference to service object in the kernel.
    @result     Returns a new IOHIDDeviceRef.
*/
CF_EXPORT
IOHIDDeviceRef IOHIDDeviceCreate(
                                CFAllocatorRef                  allocator, 
                                io_service_t                    service)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   IOHIDDeviceGetService
    @abstract   Returns the io_service_t for an IOHIDDevice, if it has one.
    @discussion If the IOHIDDevice references an object in the kernel, this is
                used to get the io_service_t for that object.
    @param      device Reference to an IOHIDDevice.
    @result     Returns the io_service_t if the IOHIDDevice has one, or 
                MACH_PORT_NULL if it does not.
 */
CF_EXPORT
io_service_t IOHIDDeviceGetService(
                                 IOHIDDeviceRef                  device)
AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
	@function   IOHIDDeviceOpen
	@abstract   Opens a HID device for communication.
    @discussion Before the client can issue commands that change the state of 
                the device, it must have succeeded in opening the device. This 
                establishes a link between the client's task and the actual 
                device.  To establish an exclusive link use the 
                kIOHIDOptionsTypeSeizeDevice option. 
    @param      device Reference to an IOHIDDevice.
    @param      options Option bits to be sent down to the device.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceOpen(          
                                IOHIDDeviceRef                  device, 
                                IOOptionBits                    options)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@function   IOHIDDeviceClose
	@abstract   Closes communication with a HID device.
    @discussion This closes a link between the client's task and the actual 
                device.
    @param      device Reference to an IOHIDDevice.
    @param      options Option bits to be sent down to the device.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceClose(
                                IOHIDDeviceRef                  device, 
                                IOOptionBits                    options)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@function   IOHIDDeviceConformsTo
	@abstract   Convenience function that scans the Application Collection 
                elements to see if it conforms to the provided usagePage 
                and usage.
    @discussion Examples of Application Collection usages pairs are:
                <br>
                    usagePage = kHIDPage_GenericDesktop  <br>
                    usage = kHIDUsage_GD_Mouse
                <br>
                <b>or</b>
                <br>
                    usagePage = kHIDPage_GenericDesktop  <br>
                    usage = kHIDUsage_GD_Keyboard
    @param      device Reference to an IOHIDDevice.
    @param      usagePage Device usage page
    @param      usage Device usage
    @result     Returns TRUE if device conforms to provided usage.
*/
CF_EXPORT
Boolean IOHIDDeviceConformsTo(          
                                IOHIDDeviceRef                  device, 
                                uint32_t                        usagePage,
                                uint32_t                        usage)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function   IOHIDDeviceGetProperty
	@abstract   Obtains a property from an IOHIDDevice.
    @discussion Property keys are prefixed by kIOHIDDevice and declared in 
                <IOKit/hid/IOHIDKeys.h>.
    @param      device Reference to an IOHIDDevice.
    @param      key CFStringRef containing key to be used when querying the 
                device.
    @result     Returns CFTypeRef containing the property.
*/
CF_EXPORT
CFTypeRef IOHIDDeviceGetProperty(
                                IOHIDDeviceRef                  device, 
                                CFStringRef                     key)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
                                
/*!
	@function   IOHIDDeviceSetProperty
	@abstract   Sets a property for an IOHIDDevice.
    @discussion Property keys are prefixed by kIOHIDDevice and declared in 
                <IOKit/hid/IOHIDKeys.h>.
    @param      device Reference to an IOHIDDevice.
    @param      key CFStringRef containing key to be used when modifiying the 
                device property.
    @param      property CFTypeRef containg the property to be set.
    @result     Returns TRUE if successful.
*/
CF_EXPORT
Boolean IOHIDDeviceSetProperty(
                                IOHIDDeviceRef                  device,
                                CFStringRef                     key,
                                CFTypeRef                       property)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@function   IOHIDDeviceCopyMatchingElements
    @abstract   Obtains HID elements that match the criteria contained in the 
                matching dictionary.
    @discussion Matching keys are prefixed by kIOHIDElement and declared in 
                <IOKit/hid/IOHIDKeys.h>.  Passing a NULL dictionary will result
                in all device elements being returned.
    @param      device Reference to an IOHIDDevice.
    @param      matching CFDictionaryRef containg element matching criteria.
    @param      options Reserved for future use.
    @result     Returns CFArrayRef containing multiple IOHIDElement object.
*/
CF_EXPORT 
CFArrayRef IOHIDDeviceCopyMatchingElements(
                                IOHIDDeviceRef                  device, 
                                CFDictionaryRef                 matching, 
                                IOOptionBits                    options)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceScheduleWithRunLoop
    @abstract   Schedules HID device with run loop.
    @discussion Formally associates device with client's run loop. Scheduling
                this device with the run loop is necessary before making use of
                any asynchronous APIs.
    @param      device Reference to an IOHIDDevice.
    @param      runLoop RunLoop to be used when scheduling any asynchronous 
                activity.
    @param      runLoopMode Run loop mode to be used when scheduling any 
                asynchronous activity.
*/
CF_EXPORT
void IOHIDDeviceScheduleWithRunLoop(
                                IOHIDDeviceRef                  device, 
                                CFRunLoopRef                    runLoop, 
                                CFStringRef                     runLoopMode)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceUnscheduleFromRunLoop
    @abstract   Unschedules HID device with run loop.
    @discussion Formally disassociates device with client's run loop.
    @param      device Reference to an IOHIDDevice.
    @param      runLoop RunLoop to be used when unscheduling any asynchronous 
                activity.
    @param      runLoopMode Run loop mode to be used when unscheduling any 
                asynchronous activity.
*/
CF_EXPORT
void IOHIDDeviceUnscheduleFromRunLoop(  
                                IOHIDDeviceRef                  device, 
                                CFRunLoopRef                    runLoop, 
                                CFStringRef                     runLoopMode)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceRegisterRemovalCallback
    @abstract   Registers a callback to be used when a IOHIDDevice is removed.
    @discussion In most cases this occurs when a device is unplugged.
    @param      device Reference to an IOHIDDevice.
    @param      callback Pointer to a callback method of type IOHIDCallback.
    @param      context Pointer to data to be passed to the callback.
*/
CF_EXPORT
void IOHIDDeviceRegisterRemovalCallback( 
                                IOHIDDeviceRef                  device, 
                                IOHIDCallback                   callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceRegisterInputValueCallback
    @abstract   Registers a callback to be used when an input value is issued by 
                the device.
    @discussion An input element refers to any element of type 
                kIOHIDElementTypeInput and is usually issued by interrupt driven
                reports.  If more specific element values are desired, you can 
                specify matching criteria via IOHIDDeviceSetInputValueMatching
                and IOHIDDeviceSetInputValueMatchingMultiple.
    @param      device Reference to an IOHIDDevice.
    @param      callback Pointer to a callback method of type IOHIDValueCallback.
    @param      context Pointer to data to be passed to the callback.
*/
CF_EXPORT
void IOHIDDeviceRegisterInputValueCallback(
                                IOHIDDeviceRef                  device, 
                                IOHIDValueCallback              callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceRegisterInputReportCallback
    @abstract   Registers a callback to be used when an input report is issued 
                by the device.
    @discussion An input report is an interrupt driver report issued by the 
                device.
    @param      device Reference to an IOHIDDevice.
    @param      report Pointer to preallocated buffer in which to copy inbound
                report data.
    @param      reportLength Length of preallocated buffer.
    @param      callback Pointer to a callback method of type 
                IOHIDReportCallback.
    @param      context Pointer to data to be passed to the callback.
*/
CF_EXPORT
void IOHIDDeviceRegisterInputReportCallback( 
                                IOHIDDeviceRef                  device, 
                                uint8_t *                       report, 
                                CFIndex                         reportLength,
                                IOHIDReportCallback             callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceSetInputValueMatching
    @abstract   Sets matching criteria for input values received via 
                IOHIDDeviceRegisterInputValueCallback.
    @discussion Matching keys are prefixed by kIOHIDElement and declared in 
                <IOKit/hid/IOHIDKeys.h>.  Passing a NULL dictionary will result
                in all devices being enumerated. Any subsequent calls will cause
                the hid manager to release previously matched input elements and 
                restart the matching process using the revised criteria.  If 
                interested in multiple, specific device elements, please defer to
                using IOHIDDeviceSetInputValueMatchingMultiple.
    @param      manager Reference to an IOHIDDevice.
    @param      matching CFDictionaryRef containg device matching criteria.
*/
CF_EXPORT
void IOHIDDeviceSetInputValueMatching(
                                IOHIDDeviceRef                  device, 
                                CFDictionaryRef                 matching)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
                                
/*! @function   IOHIDDeviceSetInputValueMatchingMultiple
    @abstract   Sets multiple matching criteria for input values received via 
                IOHIDDeviceRegisterInputValueCallback.
    @discussion Matching keys are prefixed by kIOHIDElement and declared in 
                <IOKit/hid/IOHIDKeys.h>.  This method is useful if interested 
                in multiple, specific elements .
    @param      manager Reference to an IOHIDDevice.
    @param      multiple CFArrayRef containing multiple CFDictionaryRef objects
                containg input element matching criteria.
*/
CF_EXPORT
void IOHIDDeviceSetInputValueMatchingMultiple(
                                IOHIDDeviceRef                  device, 
                                CFArrayRef                      multiple)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
                                
/*! @function   IOHIDDeviceSetValue
    @abstract   Sets a value for an element.
    @discussion This method behaves synchronously and will block until the
                report has been issued to the device.  It is only relevent for 
                either output or feature type elements.  If setting values for 
                multiple elements you may want to consider using 
                IOHIDDeviceSetValueMultiple or IOHIDTransaction.
    @param      device Reference to an IOHIDDevice.
    @param      element IOHIDElementRef whose value is to be modified.
    @param      value IOHIDValueRef containing value to be set.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceSetValue(
                                IOHIDDeviceRef                  device, 
                                IOHIDElementRef                 element, 
                                IOHIDValueRef                   value)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceSetValueMultiple
    @abstract   Sets multiple values for multiple elements.
    @discussion This method behaves synchronously and will block until the
                report has been issued to the device.  It is only relevent for 
                either output or feature type elements.
    @param      device Reference to an IOHIDDevice.
    @param      muliple CFDictionaryRef where key is IOHIDElementRef and
                value is IOHIDValueRef.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceSetValueMultiple(
                                IOHIDDeviceRef                  device, 
                                CFDictionaryRef                 multiple)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceSetValueWithCallback
    @abstract   Sets a value for an element and returns status via a completion
                callback.
    @discussion This method behaves asynchronously and will invoke the callback
                once the report has been issued to the device.  It is only 
                relevent for either output or feature type elements.  
                If setting values for multiple elements you may want to 
                consider using IOHIDDeviceSetValueWithCallback or 
                IOHIDTransaction.
    @param      device Reference to an IOHIDDevice.
    @param      element IOHIDElementRef whose value is to be modified.
    @param      value IOHIDValueRef containing value to be set.
    @param      timeout CFTimeInterval containing the timeout.
    @param      callback Pointer to a callback method of type 
                IOHIDValueCallback.
    @param      context Pointer to data to be passed to the callback.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceSetValueWithCallback(
                                IOHIDDeviceRef                  device, 
                                IOHIDElementRef                 element, 
                                IOHIDValueRef                   value, 
                                CFTimeInterval                  timeout,
                                IOHIDValueCallback              callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceSetValueMultipleWithCallback
    @abstract   Sets multiple values for multiple elements and returns status 
                via a completion callback.
    @discussion This method behaves asynchronously and will invoke the callback
                once the report has been issued to the device.  It is only 
                relevent for either output or feature type elements.  
    @param      device Reference to an IOHIDDevice.
    @param      muliple CFDictionaryRef where key is IOHIDElementRef and
                value is IOHIDValueRef.
    @param      timeout CFTimeInterval containing the timeout.
    @param      callback Pointer to a callback method of type 
                IOHIDValueMultipleCallback.
    @param      context Pointer to data to be passed to the callback.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceSetValueMultipleWithCallback(
                                IOHIDDeviceRef                  device, 
                                CFDictionaryRef                 multiple,
                                CFTimeInterval                  timeout,
                                IOHIDValueMultipleCallback      callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceGetValue
    @abstract   Gets a value for an element.
    @discussion This method behaves synchronously and return back immediately
                for input type element.  If requesting a value for a feature
                element, this will block until the report has been issued to the
                device.  If obtaining values for multiple elements you may want 
                to consider using IOHIDDeviceCopyValueMultiple or IOHIDTransaction.
    @param      device Reference to an IOHIDDevice.
    @param      element IOHIDElementRef whose value is to be obtained.
    @param      pValue Pointer to IOHIDValueRef to be obtained.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceGetValue(
                                IOHIDDeviceRef                  device, 
                                IOHIDElementRef                 element, 
                                IOHIDValueRef *                 pValue)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceCopyValueMultiple
    @abstract   Copies a values for multiple elements.
    @discussion This method behaves synchronously and return back immediately
                for input type element.  If requesting a value for a feature
                element, this will block until the report has been issued to the
                device.
    @param      device Reference to an IOHIDDevice.
    @param      elements CFArrayRef containing multiple IOHIDElementRefs whose 
                values are to be obtained.
    @param      pMultiple Pointer to CFDictionaryRef where the keys are the 
                provided elements and the values are the requested values.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceCopyValueMultiple(
                                IOHIDDeviceRef                  device, 
                                CFArrayRef                      elements, 
                                CFDictionaryRef *               pMultiple)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceGetValueWithCallback
    @abstract   Gets a value for an element and returns status via a completion
                callback.
    @discussion This method behaves asynchronusly and is only relevent for 
                either output or feature type elements. If obtaining values for 
                multiple elements you may want to consider using 
                IOHIDDeviceCopyValueMultipleWithCallback or IOHIDTransaction.
    @param      device Reference to an IOHIDDevice.
    @param      element IOHIDElementRef whose value is to be obtained.
    @param      pValue Pointer to IOHIDValueRef to be passedback.
    @param      timeout CFTimeInterval containing the timeout.
    @param      callback Pointer to a callback method of type 
                IOHIDValueCallback.
    @param      context Pointer to data to be passed to the callback.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceGetValueWithCallback(
                                IOHIDDeviceRef                  device, 
                                IOHIDElementRef                 element, 
                                IOHIDValueRef *                 pValue,
                                CFTimeInterval                  timeout,
                                IOHIDValueCallback              callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*! @function   IOHIDDeviceCopyValueMultipleWithCallback
    @abstract   Copies a values for multiple elements and returns status via a 
                completion callback.
    @discussion This method behaves asynchronusly and is only relevent for 
                either output or feature type elements.
    @param      device Reference to an IOHIDDevice.
    @param      elements CFArrayRef containing multiple IOHIDElementRefs whose 
                values are to be obtained.
    @param      pMultiple Pointer to CFDictionaryRef where the keys are the 
                provided elements and the values are the requested values.
    @param      timeout CFTimeInterval containing the timeout.
    @param      callback Pointer to a callback method of type 
                IOHIDValueMultipleCallback.
    @param      context Pointer to data to be passed to the callback.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceCopyValueMultipleWithCallback(
                                IOHIDDeviceRef                  device, 
                                CFArrayRef                      elements, 
                                CFDictionaryRef *               pMultiple,
                                CFTimeInterval                  timeout,
                                IOHIDValueMultipleCallback      callback, 
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
                                
/*! @function   IOHIDDeviceSetReport
    @abstract   Sends a report to the device.
    @discussion This method behaves synchronously and will block until the
                report has been issued to the device.  It is only relevent for 
                either output or feature type reports.
    @param      device Reference to an IOHIDDevice.
    @param      reportType Type of report being sent.
    @param      reportID ID of the report being sent.  If the device supports
                multiple reports, this should also be set in the first byte of
                the report.
    @param      report The report bytes to be sent to the device.
    @param      reportLength The length of the report to be sent to the device.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceSetReport(
                                IOHIDDeviceRef                  device,
                                IOHIDReportType                 reportType,
                                CFIndex                         reportID,
                                const uint8_t *                 report,
                                CFIndex                         reportLength)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
                                
/*! @function   IOHIDDeviceSetReportWithCallback
    @abstract   Sends a report to the device.
    @discussion This method behaves asynchronously and will block until the
                report has been issued to the device.  It is only relevent for 
                either output or feature type reports.
    @param      device Reference to an IOHIDDevice.
    @param      reportType Type of report being sent.
    @param      reportID ID of the report being sent.  If the device supports
                multiple reports, this should also be set in the first byte of
                the report.
    @param      report The report bytes to be sent to the device.
    @param      reportLength The length of the report to be sent to the device.
    @param      timeout CFTimeInterval containing the timeout.
    @param      callback Pointer to a callback method of type 
                IOHIDReportCallback.
    @param      context Pointer to data to be passed to the callback.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceSetReportWithCallback(
                                IOHIDDeviceRef                  device,
                                IOHIDReportType                 reportType,
                                CFIndex                         reportID,
                                const uint8_t *                 report,
                                CFIndex                         reportLength,
                                CFTimeInterval                  timeout,
                                IOHIDReportCallback             callback,
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceGetReport
    @abstract   Obtains a report from the device.
    @discussion This method behaves synchronously and will block until the
                report has been received from the device.  This is only intended 
                for feature reports because of sporadic devicesupport for 
                polling input reports.  Please defer to using 
                IOHIDDeviceRegisterInputReportCallback for obtaining input 
                reports.
    @param      device Reference to an IOHIDDevice.
    @param      reportType Type of report being requested.
    @param      reportID ID of the report being requested.
    @param      report Pointer to preallocated buffer in which to copy inbound
                report data.
    @param      pReportLength Pointer to length of preallocated buffer.  This
                value will be modified to refect the length of the returned 
                report.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceGetReport(
                                IOHIDDeviceRef                  device,
                                IOHIDReportType                 reportType,
                                CFIndex                         reportID,
                                uint8_t *                       report,
                                CFIndex *                       pReportLength)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! @function   IOHIDDeviceGetReportWithCallback
    @abstract   Obtains a report from the device.
    @discussion This method behaves asynchronously and will block until the
                report has been received from the device.  This is only intended 
                for feature reports because of sporadic devicesupport for 
                polling input reports.  Please defer to using 
                IOHIDDeviceRegisterInputReportCallback for obtaining input 
                reports.
    @param      device Reference to an IOHIDDevice.
    @param      reportType Type of report being requested.
    @param      reportID ID of the report being requested.
    @param      report Pointer to preallocated buffer in which to copy inbound
                report data.
    @param      pReportLength Pointer to length of preallocated buffer.
    @param      pReportLength Pointer to length of preallocated buffer.  This
                value will be modified to refect the length of the returned 
                report.
    @param      callback Pointer to a callback method of type 
                IOHIDReportCallback.
    @param      context Pointer to data to be passed to the callback.
    @result     Returns kIOReturnSuccess if successful.
*/
CF_EXPORT
IOReturn IOHIDDeviceGetReportWithCallback(
                                IOHIDDeviceRef                  device,
                                IOHIDReportType                 reportType,
                                CFIndex                         reportID,
                                uint8_t *                       report,
                                CFIndex *                       pReportLength,
                                CFTimeInterval                  timeout,
                                IOHIDReportCallback             callback,
                                void *                          context)
AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
                                
__END_DECLS

#endif /* _IOKIT_HID_IOHIDDEVICE_USER_H */
