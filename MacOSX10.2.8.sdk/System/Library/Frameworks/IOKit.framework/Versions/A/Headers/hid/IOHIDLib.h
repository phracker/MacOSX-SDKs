/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_HID_IOHIDLIB_H_
#define _IOKIT_HID_IOHIDLIB_H_

#include <sys/cdefs.h>

__BEGIN_DECLS
#include <CoreFoundation/CoreFoundation.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <IOKit/IOTypes.h>
#include <IOKit/IOReturn.h>

#include <IOKit/hid/IOHIDKeys.h>

struct IOHIDEventStruct
{
    IOHIDElementType	type;
    IOHIDElementCookie	elementCookie;
    SInt32		value;
    AbsoluteTime	timestamp;
    UInt32		longValueSize;
    void *		longValue;
};
typedef struct IOHIDEventStruct IOHIDEventStruct;

/* FA12FA38-6F1A-11D4-BA0C-0005028F18D5 */
#define kIOHIDDeviceUserClientTypeID CFUUIDGetConstantUUIDWithBytes(NULL, \
    0xFA, 0x12, 0xFA, 0x38, 0x6F, 0x1A, 0x11, 0xD4,			\
    0xBA, 0x0C, 0x00, 0x05, 0x02, 0x8F, 0x18, 0xD5)

/* 13AA9C44-6F1B-11D4-907C-0005028F18D5 */
#define kIOHIDDeviceFactoryID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x13, 0xAA, 0x9C, 0x44, 0x6F, 0x1B, 0x11, 0xD4,			\
    0x90, 0x7C, 0x00, 0x05, 0x02, 0x8F, 0x18, 0xD5)

/* 78BD420C-6F14-11D4-9474-0005028F18D5 */
/*! @defined kIOHIDDeviceInterfaceID
    @discussion Interface ID for the IOHIDDeviceInterface. Corresponds to an
                 available HID device. */
#define kIOHIDDeviceInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0x78, 0xBD, 0x42, 0x0C, 0x6F, 0x14, 0x11, 0xD4,			\
    0x94, 0x74, 0x00, 0x05, 0x02, 0x8F, 0x18, 0xD5)

/* 8138629E-6F14-11D4-970E-0005028F18D5 */
/*! @defined kIOHIDQueueInterfaceID
    @discussion Interface ID for the kIOHIDQueueInterfaceID. Corresponds to a
                queue for a specific HID device. */
#define kIOHIDQueueInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0x81, 0x38, 0x62, 0x9E, 0x6F, 0x14, 0x11, 0xD4,			\
    0x97, 0x0E, 0x00, 0x05, 0x02, 0x8F, 0x18, 0xD5)

/* 80CDCC00-755D-11D4-8E0F-0005028F18D5 */
/*! @defined kIOHIDOutputTransactionInterfaceID
    @discussion Interface ID for the kIOHIDOutputTransactionInterfaceID.
                Corresponds to a output transaction for one or more report IDs
                on a specific device. */
#define kIOHIDOutputTransactionInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL,\
    0x80, 0xCD, 0xCC, 0x00, 0x75, 0x5D, 0x11, 0xD4,			\
    0x80, 0xEF, 0x00, 0x05, 0x02, 0x8F, 0x18, 0xD5)

/*! @typedef IOHIDCallbackFunction
    @discussion Type and arguments of callout C function that is used when a
                completion routine is called, see
                IOHIDLib.h:setRemovalCallback().
    @param target void * pointer to your data, often a pointer to an object.
    @param result completion result of desired operation
    @param refcon void * pointer to more data.
    @param sender interface instance sending the completion routine.
*/
typedef void (*IOHIDCallbackFunction)
              (void * target, IOReturn result, void * refcon, void * sender);

/*! @typedef IOHIDElementCallbackFunction
    @discussion Type and arguments of callout C function that is used when a
                completion routine is called, see IOHIDLib.h:setElementValue().
    @param target void * pointer to your data, often a pointer to an object.
    @param result completion result of desired operation
    @param refcon void * pointer to more data.
    @param sender interface instance sending the completion routine.
    @param elementCookie element within interface instance sending completion.
*/
typedef void (*IOHIDElementCallbackFunction)
              (void *	 		target,
               IOReturn 		result,
               void * 			refcon,
               void * 			sender,
               IOHIDElementCookie 	elementCookie);

/*! @typedef IOHIDReportCallbackFunction
    @discussion Type and arguments of callout C function that is used when a
                completion routine is called, see IOHIDLib.h:setReport().
    @param target void * pointer to your data, often a pointer to an object.
    @param result completion result of desired operation
    @param refcon void * pointer to more data.
    @param sender interface instance sending the completion routine.
    @param bufferSize size of the buffer received upon completion.
*/
typedef void (*IOHIDReportCallbackFunction)
              (void *	 		target,
               IOReturn 		result,
               void * 			refcon,
               void * 			sender,
               UInt32		 	bufferSize);

/* Forward declarations of the queue and output transaction interfaces */
struct IOHIDQueueInterface;
struct IOHIDOutputTransactionInterface;
typedef struct IOHIDQueueInterface IOHIDQueueInterface;
typedef struct IOHIDOutputTransactionInterface IOHIDOutputTransactionInterface;

/*! @typedef IOHIDDeviceInterface
    @discussion CFPlugin object subclass which privides the primary inteface to
                HID devices.
*/
struct IOHIDDeviceInterface
{
    IUNKNOWN_C_GUTS;

    /* Completion plumbing (must be set before any callbacks used) */
    /* Either createAsyncEventSource or createAsyncPort should be used */
    IOReturn (*createAsyncEventSource)(void * 			self,
                                       CFRunLoopSourceRef * 	source);
    CFRunLoopSourceRef (*getAsyncEventSource)(void * self);

    IOReturn (*createAsyncPort)(void * self, mach_port_t * port);
    mach_port_t (*getAsyncPort)(void * self);
    
    /* Basic IOHIDDevice interface */
    IOReturn (*open)(void * self, UInt32 flags);
    IOReturn (*close)(void * self);

    /* removalCallback is called if the device is removed. */
    /* removeTarget and removalRefcon are passed to the callback. */
    IOReturn (*setRemovalCallback)(void * 			self,
                                   IOHIDCallbackFunction	removalCallback,
                                   void *			removalTarget,
                                   void *			removalRefcon);


/*! @function getElementValue
    @abstract Called to obtain the most recent value of an element
    @discussion This call is most useful for interrupt driven elements,
        such as input type elements.  Since feature type element values 
        need to be polled from the device, it is recommended to use the 
        queryElementValue method to obtain the current value.  The  
        timestamp field in the event details the last time the element 
        value was altered.
    @param elementCookie The element of interest. 
    @param valueEvent The event that will be filled.   If a long value is 
        present, it is up to the caller to deallocate it. */
    IOReturn (*getElementValue)(void * 			self,
                                IOHIDElementCookie	elementCookie,
                                IOHIDEventStruct *	valueEvent);


/*! @function setElementValue
    @abstract Called to set an element value on the device
    @discussion This call is most useful for feature type elements.  It is
        recommended to use IOOutputTransaction for output type elements
    @param elementCookie The element of interest. 
    @param valueEvent The event that will be filled.  If a long value is
        present, it will be copied.

    *** THIS METHOD IS SYNCHRONOUS ***
    *** THE FOLLOWING PARAMS ARE UNSUPPORTED ***
    @param timeoutMS
    @param callback 
    @param callbackTarget
    @param callbackRefcon */
    IOReturn (*setElementValue)(void *	 			self,
                                IOHIDElementCookie		elementCookie,
                                IOHIDEventStruct *		valueEvent,
                                UInt32 				timeoutMS,
                                IOHIDElementCallbackFunction	callback,
                                void * 				callbackTarget,
                                void *				callbackRefcon);


/*! @function queryElementValue
    @abstract Called to obtain the current value of an element
    @discussion This call is most useful for feature type elements.  This
        method will poll the device for the current element value.
    @param elementCookie The element of interest. 
    @param valueEvent The event that will be filled.  If a long value is 
        present, it is up to the caller to deallocate it.

    *** THIS METHOD IS SYNCHRONOUS ***
    *** THE FOLLOWING PARAMS ARE UNSUPPORTED ***
    @param timeoutMS
    @param callback 
    @param callbackTarget
    @param callbackRefcon */
    IOReturn (*queryElementValue)(void * 			self,
                                IOHIDElementCookie		elementCookie,
                                IOHIDEventStruct *		valueEvent,
                                UInt32 				timeoutMS,
                                IOHIDElementCallbackFunction	callback,
                                void * 				callbackTarget,
                                void *				callbackRefcon);

/*! @function startAllQueues
    @abstract Start data delivery on all queue for a this device */
    IOReturn (*startAllQueues)(void * self);
    
/*! @function stopAllQueues
    @abstract Stop data delivery on all queue for a this device */
    IOReturn (*stopAllQueues)(void * self);

/*! @function allocQueue
    @abstract Wrapper to return instances of the IOHIDQueueInterface */
    IOHIDQueueInterface ** (*allocQueue) (void *self);
    
/*! @function allocOutputTransaction
    @abstract Wrapper to return instances of the IOHIDOutputTransactionInterface */
    IOHIDOutputTransactionInterface ** (*allocOutputTransaction) (void *self);
    
    
/*! @function setReport
    @abstract Called to send a report to the device
    @discussion
    @param reportType The report type.
    @param reportID The report id.
    @param reportBuffer Pointer to a preallocated buffer.
    @param reportBufferSize Size of the reportBuffer in bytes.
    @param timeoutMS
    @param callback If null, this method will behave synchronously.
    @param callbackTarget The callback target passed to the callback.
    @param callbackRefcon The callback refcon passed to the callback. */
    IOReturn (*setReport)	(void * 			self,
                                IOHIDReportType			reportType,
                                UInt32				reportID,
                                void *				reportBuffer,
                                UInt32				reportBufferSize,
                                UInt32 				timeoutMS,
                                IOHIDReportCallbackFunction	callback,
                                void * 				callbackTarget,
                                void *				callbackRefcon);


/*! @function getReport
    @abstract Called to obtain a report from the device
    @discussion
    @param reportType The report type.
    @param reportID The report id.
    @param reportBuffer Pointer to a preallocated buffer.
    @param reportBufferSize Size of the reportBuffer in bytes.  
        When finished, will contain the actual size of the report.
    @param timeoutMS
    @param callback If null, this method will behave synchronously.
    @param callbackTarget The callback target passed to the callback.
    @param callbackRefcon The callback refcon passed to the callback. */
    IOReturn (*getReport)	(void * 			self,
                                IOHIDReportType			reportType,
                                UInt32				reportID,
                                void *				reportBuffer,
                                UInt32 *			reportBufferSize,
                                UInt32 				timeoutMS,
                                IOHIDReportCallbackFunction	callback,
                                void * 				callbackTarget,
                                void *				callbackRefcon);
};
typedef struct IOHIDDeviceInterface IOHIDDeviceInterface;

/*! @typedef IOHIDQueueInterface
    @discussion CFPlugin object subclass which privides interface for input
                queues from HID devices. Created by a IOHIDDeviceInterface
                object.
*/
struct IOHIDQueueInterface
{
    IUNKNOWN_C_GUTS;
    
/*! @function createAsyncEventSource
    @abstract Called to create an async event source
    @discussion This will be used with setEventCallout.
    @param source The newly created event source */
    IOReturn (*createAsyncEventSource)(void * 			self, 
                                        CFRunLoopSourceRef * 	source);

/*! @function getAsyncEventSource
    @abstract Called to obtain the current event source */
    CFRunLoopSourceRef (*getAsyncEventSource)(void * self);

/*! @function createAsyncPort
    @abstract Called to create an async port
    @discussion This will be used with createAsyncEventSource.
    @param port The newly created async port */
    IOReturn (*createAsyncPort)(void * self, mach_port_t * port);
    
/*! @function getAsyncPort
    @abstract Called to obtain the current async port */
    mach_port_t (*getAsyncPort)(void * self);
    
/*! @function create
    @abstract Create the current queue. 
    @param flags
    @param depth The maximum number of elements in the queue 
        before the oldest elements in the queue begin to be lost. */
    IOReturn (*create)(void * 			self, 
                        UInt32 			flags,
                        UInt32			depth);

/*! @function create
    @abstract Dispose of the current queue. */
    IOReturn (*dispose)(void * self);
    
/*! @function addElement
    @abstract Called to add an element to the queue
    @discussion If the element has already been added to queue,
        an error will be returned.
    @param elementCookie The element of interest. 
    @flags */
    IOReturn (*addElement)(void * self,
                           IOHIDElementCookie elementCookie,
                           UInt32 flags);

/*! @function removeElement
    @abstract Called to remove an element to the queue
    @discussion If the element has not been added to queue,
        an error will be returned.
    @param elementCookie The element of interest. */
    IOReturn (*removeElement)(void * self, IOHIDElementCookie elementCookie);
    
/*! @function hasElement
    @abstract Called to check whether an element has been added to 
        the queue.
    @discussion Will return true if present, otherwise will return fales.
    @param elementCookie The element of interest. */
    Boolean (*hasElement)(void * self, IOHIDElementCookie elementCookie);

/*! @function start
    @abstract Called to start event delivery to the queue. */
    IOReturn (*start)(void * self);
    
/*! @function stop
    @abstract Called to stop event delivery to the queue. */
    IOReturn (*stop)(void * self);

/*! @function getNextEvent
    @abstract Called to read next event from the queue
    @discussion
    @param event The event that will be filled.  If a long value is
        present, it is up to the caller to deallocate it.
        
    *** THE FOLLOWING PARAMETERS ARE UNSUPPORTED ***
    @param maxtime If non-zero, limits read events to those that occured
        on or before maxTime
    @param timoutMS The timeout in milliseconds, a zero timeout will 
        cause this call to be non-blocking (returning queue empty) if 
        there is a NULL callback, and blocking forever until the queue
        is non-empty if their is a valid callback */

    IOReturn (*getNextEvent)(void * 			self,
                            IOHIDEventStruct *		event,
                            AbsoluteTime		maxTime,
                            UInt32 			timeoutMS);

/*! @function setEventCallout
    @abstract Set the event callout to be called when the queue 
        transitions to non-empty.
    @discussion In order for this to work correctly, you must call
        createAsyncPort and createAsyncEventSource.
    @param callback if non-NULL is a callback to be called when data 
        is  inserted to the queue
    @param callbackTarget The callback target passed to the callback
    @param callbackRefcon The callback refcon passed to the callback */
    IOReturn (*setEventCallout)(void * 			self,
                                IOHIDCallbackFunction   callback,
                                void * 			callbackTarget,
                                void *			callbackRefcon);

/*! @function getEventCallout
    @abstract Get the event callout.
    @discussion This callback will be called the queue transitions
        to non-empty.
    @param callback if non-NULL is a callback to be called when data 
        is  inserted to the queue
    @param callbackTarget The callback target passed to the callback
    @param callbackRefcon The callback refcon passed to the callback */
    IOReturn (*getEventCallout)(void * 			self,
                                IOHIDCallbackFunction * outCallback,
                                void ** 		outCallbackTarget,
                                void **			outCallbackRefcon);
};

/*! @typedef IOHIDOutputTransactionInterface
    @discussion CFPlugin object subclass which privides interface for output
                transactions to HID devices. Created by a IOHIDDeviceInterface
                object.
*/
struct IOHIDOutputTransactionInterface
{
    IUNKNOWN_C_GUTS;
    
    /* Completion plumbing (overrides that set in IOHIDDevice) */
    IOReturn (*createAsyncEventSource)(void * 			self,
                                       CFRunLoopSourceRef *	source);
    CFRunLoopSourceRef (*getAsyncEventSource)(void * self);

    IOReturn (*createAsyncPort)(void * self, mach_port_t * port);
    mach_port_t (*getAsyncPort)(void * self);
    
/*! @function create
    @abstract Create the current transaction.
    @discussion This method will free any memory that has been
        allocated for this transaction. */
    IOReturn (*create)(void * self);
    
/*! @function dispose
    @abstract Dispose of the current transaction.
    @discussion The transaction will have to be recreated, in order
        to perform any operations on the transaction.*/
    IOReturn (*dispose)(void * self);
    
/*! @function addElement
    @abstract Called to add an element to the transaction
    @discussion If the element has already been added to transaction,
        an error will be returned.
    @param elementCookie The element of interest. */
    IOReturn (*addElement)	(void * self, IOHIDElementCookie elementCookie);
    
/*! @function removeElement
    @abstract Called to removed an element from the transaction
    @discussion If the element has not been added to transaction,
        an error will be returned.
    @param elementCookie The element of interest. */
    IOReturn (*removeElement)	(void * self, IOHIDElementCookie elementCookie);
    
/*! @function hasElement
    @abstract Called to check whether an element has been added to 
        the transaction.
    @discussion Will return true if present, otherwise will return fales.
    @param elementCookie The element of interest. */
    Boolean  (*hasElement)	(void * self, IOHIDElementCookie elementCookie);
    
/*! @function setElementDefault
    @abstract Called to set the default value of an element in a 
        transaction.
    @discussion An error will be returned if the element has not been
        added to the transaction.
    @param elementCookie The element of interest. 
    @param valueEvent The event that will be filled.  If a long value is
        present, it will be copied.*/
    IOReturn (*setElementDefault)(void *	 	self,
                                  IOHIDElementCookie	elementCookie,
                                  IOHIDEventStruct *	valueEvent);

/*! @function getElementDefault
    @abstract Called to obtain the default value of an element in a 
        transaction.
    @discussion An error will be returned if the element has not been 
        added to the transaction.
    @param elementCookie The element of interest. 
    @param outValueEvent The event that will be filled.  If a long value is 
        present, it is up to the caller to deallocate it. */
    IOReturn (*getElementDefault)(void *	 	self,
                                  IOHIDElementCookie	elementCookie,
                                  IOHIDEventStruct *	outValueEvent);

/*! @function setElementValue
    @abstract Called to set the value of an element in a transaction.
    @discussion An error will be returned if the element has not been
        added to the transaction.
    @param elementCookie The element of interest. 
    @param valueEvent The event that will be filled.  If a long value is
        present, it will be copied. */
    IOReturn (*setElementValue)(void *	 		self,
                                IOHIDElementCookie	elementCookie,
                                IOHIDEventStruct *	valueEvent);

/*! @function getElementValue
    @abstract Called to obtain the value of an element in a transaction.
    @discussion An error will be returned if the element has not been 
        added to the transaction.
    @param elementCookie The element of interest. 
    @param outValueEvent The event that will be filled.  If a long value is 
        present, it is up to the caller to deallocate it. */
    IOReturn (*getElementValue)(void *	 		self,
                                IOHIDElementCookie	elementCookie,
                                IOHIDEventStruct *	outValueEvent);

/*! @function commit
    @abstract Commit the transaction
    @discussion Transaction element values, if set, will be sent to the 
        device.  Otherwise, the default element value will be used.  If
        neither are set, that element will be omitted from the commit.
        After a transaction is committed, transaction element values 
        will be cleared.  Default values will be preserved.
        
    *** THIS METHOD IS SYNCHRONOUS ***
    *** THE FOLLOWING PARAMS ARE UNSUPPORTED ***
    @param timeoutMS
    @param callback 
    @param callbackTarget
    @param callbackRefcon */
   IOReturn (*commit)(void * 			self,
                        UInt32 			timeoutMS,
                        IOHIDCallbackFunction   callback,
                        void * 			callbackTarget,
                        void *			callbackRefcon);
    
/*! @function clear
    @abstract Clear the transaction
    @discussion Transaction element values will cleared.   Default 
        values will be preserved. */
    IOReturn (*clear)(void * self);
    
};

__END_DECLS

#endif /* !_IOKIT_HID_IOHIDLIB_H_ */
