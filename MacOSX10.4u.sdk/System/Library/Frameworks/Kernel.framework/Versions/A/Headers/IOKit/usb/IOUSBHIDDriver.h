/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
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

#ifndef IOUSBHIDDRIVER_H
#define IOUSBHIDDRIVER_H

#include <IOKit/IOBufferMemoryDescriptor.h>

#include <IOKit/hid/IOHIDDevice.h>

#include <IOKit/usb/IOUSBBus.h>
#include <IOKit/usb/IOUSBInterface.h>
#include <IOKit/usb/USB.h>


#define ENABLE_HIDREPORT_LOGGING	0

// Report types from low level USB:
//	from USBSpec.h:
//    enum {
//        kHIDRtInputReport		= 1,
//        kHIDRtOutputReport		= 2,
//        kHIDRtFeatureReport		= 3
//    };
//    
//	from IOHIDDescriptorParser.h:
//    // types of HID reports (input, output, feature)
//    enum
//    {
//        kHIDInputReport			= 	1,
//        kHIDOutputReport,
//        kHIDFeatureReport,
//        kHIDUnknownReport		=	255
//    };
//    
// Report types from high level HID Manager:
//	from IOHIDKeys.h:
//    enum IOHIDReportType
//    {
//        kIOHIDReportTypeInput = 0,
//        kIOHIDReportTypeOutput,
//        kIOHIDReportTypeFeature,
//        kIOHIDReportTypeCount
//    };
//
#define HIDMGR2USBREPORTTYPE(x) (x + 1)
#define USB2HIDMGRREPORTTYPE(x) (x - 1)


// Note: In other Neptune files, kMaxHIDReportSize was defined as 64. But Ferg & Keithen were unable to
// find that value in the USB HID 1.1 specs. Brent had previously changed it to 256 in the OS 9 HID Driver
// to  allow for reports spanning multiple packets. 256 may be no more a hard and fast limit, but it's 
// working for now in OS 9.
#define kMaxHIDReportSize 256			// Max packet size = 8 for low speed & 64 for high speed.
#define kHIDDriverRetryCount	3
#define	kUSBHIDReportLoggingLevel	"USB HID Report Logging Level"


class IOUSBHIDDriver : public IOHIDDevice
{
    OSDeclareDefaultStructors(IOUSBHIDDriver)

    IOUSBInterface *			_interface;
    IOUSBDevice	*				_device;
    IOUSBPipe *					_interruptPipe;
    UInt32						_maxReportSize;
    IOBufferMemoryDescriptor *	_buffer;
    IOUSBCompletion				_completion;
    UInt32						_retryCount;
    thread_call_t				_deviceDeadCheckThread;
    thread_call_t				_clearFeatureEndpointHaltThread;
    bool						_deviceDeadThreadActive;
    bool						_deviceIsDead;                          // Should really be called "abort expected"
    bool						_deviceHasBeenDisconnected;
    bool						_needToClose;
    UInt32						_outstandingIO;
    IOCommandGate *				_gate;
    IOUSBPipe *					_interruptOutPipe;
    UInt32						_locationID; 	
    IOBufferMemoryDescriptor *	_outBuffer;								// Obsolete
    UInt32						_deviceUsage;							// Obsolete
    UInt32						_deviceUsagePage;						// Obsolete

    struct IOUSBHIDDriverExpansionData 
    {
        IOWorkLoop	*					_workLoop;
        thread_call_t					_handleReportThread;
        IOService *						_rootDomain;
        AbsoluteTime					_wakeUpTime;
        IOUSBCompletionWithTimeStamp	_completionWithTimeStamp;
        bool							_checkForTimeStamp;
        UInt32							_msToIgnoreTransactionsAfterWake;
        IOTimerEventSource	*			_suspendPortTimer;
		bool							_portSuspended;
		UInt32							_suspendTimeoutInMS;
		UInt8							_interfaceNumber;
		bool							_logHIDReports;
		UInt8							_hidLoggingLevel;
		AbsoluteTime					_interruptTimeStamp;
    };
    IOUSBHIDDriverExpansionData *_usbHIDExpansionData;
    
    static void 		InterruptReadHandlerEntry(OSObject *target, void *param, IOReturn status, UInt32 bufferSizeRemaining);
    static void 		InterruptReadHandlerWithTimeStampEntry(OSObject *target, void *param, IOReturn status, UInt32 bufferSizeRemaining, AbsoluteTime timeStamp);
    void				InterruptReadHandler(IOReturn status, UInt32 bufferSizeRemaining, AbsoluteTime timeStamp);

    static void 		CheckForDeadDeviceEntry(OSObject *target);
    void				CheckForDeadDevice();

    static void			ClearFeatureEndpointHaltEntry(OSObject *target);
    void				ClearFeatureEndpointHalt(void);
    
    static void			HandleReportEntry(OSObject *target, thread_call_param_t timeStamp);
    void				HandleReport(AbsoluteTime timeStamp);
    
    virtual void 		processPacket(void *data, UInt32 size);		// Obsolete

    static IOReturn		ChangeOutstandingIO(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);

    static void			SuspendPortTimer(OSObject *target, IOTimerEventSource *sender);

public:
        
    // IOService methods
    //
    virtual bool		init(OSDictionary *properties);
    virtual bool		start(IOService * provider);
    virtual bool		didTerminate( IOService * provider, IOOptionBits options, bool * defer );
    virtual bool		willTerminate( IOService * provider, IOOptionBits options );
    virtual void		stop(IOService *  provider);
#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
    virtual void		free();
#endif
    virtual IOReturn 	message( UInt32 type, IOService * provider,  void * argument = 0 );
    

    // IOHIDDevice methods
    //
    virtual bool		handleStart(IOService * provider);
    virtual void		handleStop(IOService *  provider);

    virtual IOReturn 	newReportDescriptor( IOMemoryDescriptor ** descriptor ) const;
                        
    virtual OSString * 	newTransportString() const;

    virtual OSNumber * 	newVendorIDNumber() const;

    virtual OSNumber * 	newProductIDNumber() const;

    virtual OSNumber * 	newVersionNumber() const;

    virtual OSString * 	newManufacturerString() const;

    virtual OSString * 	newProductString() const;

    virtual OSString * 	newSerialNumberString() const;

    virtual OSNumber * 	newLocationIDNumber() const;

    virtual OSNumber * 	newCountryCodeNumber() const;

    virtual IOReturn	getReport( IOMemoryDescriptor * report,
                                IOHIDReportType      reportType,
                                IOOptionBits         options = 0 );
                                
    virtual IOReturn 	setReport( IOMemoryDescriptor * report,
                                IOHIDReportType      reportType,
                                IOOptionBits         options = 0 );
			
    // HID driver methods
    //
    virtual OSString * 	newIndexedString(UInt8 index) const;

    virtual UInt32		getMaxReportSize();
	
    virtual void		DecrementOutstandingIO(void);
    virtual void		IncrementOutstandingIO(void);
    virtual IOReturn	StartFinalProcessing();
    virtual IOReturn	SetIdleMillisecs(UInt16 msecs);
    
private:

	IOReturn			GetHIDDescriptor(UInt8 inDescriptorType, UInt8 inDescriptorIndex, UInt8 *vOutBuf, UInt32 *vOutSize);
	IOReturn			GetReport(UInt8 inReportType, UInt8 inReportID, UInt8 *vInBuf, UInt32 *vInSize);
	IOReturn			SetReport(UInt8 outReportType, UInt8 outReportID, UInt8 *vOutBuf, UInt32 vOutSize);
	IOReturn			GetIndexedString(UInt8 index, UInt8 *vOutBuf, UInt32 *vOutSize, UInt16 lang = 0x409) const;
	IOReturn			SetProtocol(UInt32 protocolType);
	char				GetHexChar(char hexChar);
	IOReturn			AbortAndSuspend( bool suspend );
	
        

#if ENABLE_HIDREPORT_LOGGING
    void LogBufferReport(char *report, UInt32 len);
    void LogMemReport(IOMemoryDescriptor * reportBuffer);
    char GetHexChar(char hexChar);
#endif

public:
    OSMetaClassDeclareReservedUsed(IOUSBHIDDriver,  0);
    virtual IOReturn    RearmInterruptRead();
    
#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
    /*!
		@function SuspendPort
	 @abstract Suspends the port for this device or optionally sets a timeout to suspend after a period of inactivity.
	 @discussion  This call can be used to immediately suspend/resume a port or to enable the suspension of the port after a period of inactivity.  If called with suspendPort = true (no timeout parameter), the HID driver
	 will immediately suspend the port, after aborting any outstanding reads on the interrupt pipe.  If called with suspendPort = true and timeout != 0, it will suspend the port after the timeout number of ms have
	 passed without any read completions.  If called with suspendPort = false, the port will be immediately resumed and the reads will be re-issued.  If a timeout was enabled, it will be cancelled.
	 @param suspendPort Boolean value. true = suspend the port, false = resume the port.
	 @param timeoutMS	Value in milliseconds If value is non-zero, the port will be suspended after the timeout milliseconds have passed without any read completions.
	 @result The IOReturn value from the IOUSBDevice::Suspend() call. 
	*/
    OSMetaClassDeclareReservedUsed(IOUSBHIDDriver,  1);
	virtual IOReturn	SuspendPort(bool suspendPort, UInt32 timeoutMS = 0);
	
    OSMetaClassDeclareReservedUsed(IOUSBHIDDriver,  2);
	virtual bool		IsPortSuspended();
	
    OSMetaClassDeclareReservedUsed(IOUSBHIDDriver,  3);
    virtual void		LogMemReport(UInt8 level, IOMemoryDescriptor * reportBuffer, IOByteCount size);
#else
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  1);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  2);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  3);
#endif

    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  4);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  5);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  6);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  7);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  8);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver,  9);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 10);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 11);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 12);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 13);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 14);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 15);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 16);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 17);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 18);
    OSMetaClassDeclareReservedUnused(IOUSBHIDDriver, 19);
};

#endif	// IOUSBHIDDRIVER_H
