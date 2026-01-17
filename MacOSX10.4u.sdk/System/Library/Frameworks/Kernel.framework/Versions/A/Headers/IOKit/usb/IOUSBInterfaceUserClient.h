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

//================================================================================================
//
//   Headers
//
//================================================================================================
//
#include <libkern/OSByteOrder.h>

#include <IOKit/IOUserClient.h>
#include <IOKit/assert.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOMessage.h>
#include <IOKit/usb/IOUSBUserClient.h>
#include <IOKit/usb/IOUSBControllerV2.h>
#include <IOKit/usb/IOUSBDevice.h>
#include <IOKit/usb/IOUSBInterface.h>
#include <IOKit/usb/IOUSBPipe.h>
#include <IOKit/usb/IOUSBLog.h>
#include <IOKit/IOCommandPool.h>
/*
#include <libkern/OSByteOrder.h>

#include <IOKit/assert.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/IOUserClient.h>
#include <IOKit/usb/IOUSBUserClient.h>
#include <IOKit/usb/IOUSBDevice.h>
#include <IOKit/usb/IOUSBInterface.h>
#include <IOKit/usb/IOUSBPipe.h>
#include <IOKit/usb/IOUSBLog.h>
#include <IOKit/IOCommandPool.h>
#include <IOKit/usb/IOUSBControllerV2.h>
*/

enum
{
    kSizeToIncrementLowLatencyCommandPool = 10
};


//================================================================================================
//
//   Structure declarations
//
//================================================================================================
//
typedef struct IOUSBInterfaceUserClientAsyncParamBlock IOUSBInterfaceUserClientAsyncParamBlock;

struct IOUSBInterfaceUserClientAsyncParamBlock {
    OSAsyncReference 		fAsyncRef;
    UInt32 			fMax;
    IOMemoryDescriptor 		*fMem;
    IOUSBDevRequestDesc		req;
};

typedef struct IOUSBInterfaceUserClientISOAsyncParamBlock IOUSBInterfaceUserClientISOAsyncParamBlock;
struct IOUSBInterfaceUserClientISOAsyncParamBlock {
    OSAsyncReference            fAsyncRef;
    int                         frameLen;	// In bytes
    void *                      frameBase;	// In user task
    IOMemoryDescriptor *        dataMem;
    IOMemoryDescriptor *        countMem;
	UInt32						numFrames;
    IOUSBIsocFrame              frames[0];
};

typedef struct IOUSBLowLatencyUserClientBufferInfo  IOUSBLowLatencyUserClientBufferInfo;

struct IOUSBLowLatencyUserClientBufferInfo
{
    UInt32									cookie;
    UInt32									bufferType;
    void *									bufferAddress;
    UInt32									bufferSize;
    IOMemoryDescriptor *					bufferDescriptor;
    IOMemoryDescriptor *					frameListDescriptor;
    IOMemoryMap *							frameListMap;
    IOVirtualAddress						frameListKernelAddress;
	IOBufferMemoryDescriptor *				writeDescritporForUHCI;
	IOMemoryMap *							writeMapForUHCI;
    IOUSBLowLatencyUserClientBufferInfo * 	nextBuffer;
};


//================================================================================================
//
//   Class Definition for IOUSBLowLatencyCommand
//
//================================================================================================
//
class IOUSBLowLatencyCommand : public IOCommand
{
    OSDeclareAbstractStructors(IOUSBLowLatencyCommand)

private:

    OSAsyncReference		fAsyncRef;
    IOByteCount			fFrameLength;	// In bytes
    void *			fFrameBase;	// In user task
    IOMemoryDescriptor *	fDataBufferDescriptor;

    struct IOUSBLowLatencyExpansionData 
    {
    };
    
    IOUSBLowLatencyExpansionData * fIOUSBLowLatencyExpansionData;
public:

    // static constructor
    //
    static IOUSBLowLatencyCommand *	NewCommand(void);

    // accessor methods
    //
    virtual void  			SetAsyncReference(OSAsyncReference  ref);
    void                                SetFrameLength(IOByteCount frameLength)     { fFrameLength = frameLength; }
    void                                SetFrameBase(void * frameBase)              { fFrameBase = frameBase; }
    void                                SetDataBuffer(IOMemoryDescriptor * dataMem) { fDataBufferDescriptor = dataMem; }

	void                                GetAsyncReference(OSAsyncReference *ref)    { bcopy (&fAsyncRef, ref, kOSAsyncRefCount * sizeof(natural_t)); }
    IOByteCount                         GetFrameLength(void)                        { return fFrameLength; }
    void *                              GetFrameBase(void)                          { return fFrameBase; }
    IOMemoryDescriptor *                GetDataBuffer(void)                         { return fDataBufferDescriptor; }
    IOUSBLowLatencyExpansionData  *     GetExpansionData(void)                      { return fIOUSBLowLatencyExpansionData; }

    // padding methods
    //
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  0);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  1);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  2);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  3);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  4);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  5);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  6);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  7);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  8);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand,  9);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 10);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 11);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 12);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 13);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 14);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 15);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 16);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 17);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 18);
    OSMetaClassDeclareReservedUnused(IOUSBLowLatencyCommand, 19);
};


//================================================================================================
//
//   Class Definition for IOUSBInterfaceUserClient
//
//================================================================================================
//
class IOUSBInterfaceUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(IOUSBInterfaceUserClient)

private:
    IOUSBInterface *							fOwner;
    task_t										fTask;
    mach_port_t									fWakePort;
    const IOExternalMethod *                    fMethods;
    const IOExternalAsyncMethod *               fAsyncMethods;
    IOCommandGate *                             fGate;
    IOWorkLoop	*                               fWorkLoop;
    IOUSBLowLatencyUserClientBufferInfo *		fUserClientBufferInfoListHead;
    IOCommandPool *                             fFreeUSBLowLatencyCommandPool;
    UInt32										fNumMethods;
    UInt32										fNumAsyncMethods;
    UInt32										fOutstandingIO;
    bool                                        fDead;
    bool                                        fNeedToClose;
    UInt32                                      fCurrentSizeOfCommandPool;

    struct IOUSBInterfaceUserClientExpansionData 
    {
		bool									clientRunningUnderRosetta;				// True if our user space client is running PPC code under Rosetta
		bool									needContiguousMemoryForLowLatencyIsoch;
    };
    
    IOUSBInterfaceUserClientExpansionData *        fIOUSBInterfaceUserClientExpansionData;
    
protected:
    virtual void                                SetExternalMethodVectors(void);

public:
        
    // IOKit methods
    //
    virtual void                                stop(IOService * provider);
    virtual bool                                start( IOService * provider );
    virtual bool                                finalize(IOOptionBits options);
    virtual void                                free();
    virtual bool                                willTerminate( IOService * provider, IOOptionBits options );
    virtual bool                                didTerminate( IOService * provider, IOOptionBits options, bool * defer );
#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
    virtual IOReturn							message( UInt32 type, IOService * provider,  void * argument = 0 );
#endif

    // pseudo IOKit methods - these methods are NOT the IOService:: methods, since both IOService::open
    // and IOService::close require an IOService* as the first parameter
    //
    virtual IOReturn                            open(bool seize);
    virtual IOReturn                            close(void);

    // IOUserClient methods
    //
    virtual bool								initWithTask(task_t owningTask, void *security_id, UInt32 type, OSDictionary *properties);
    virtual IOExternalMethod *                  getTargetAndMethodForIndex(IOService **target, UInt32 index);
    virtual IOExternalAsyncMethod *             getAsyncTargetAndMethodForIndex(IOService **target, UInt32 index);
    virtual IOReturn                            clientClose( void );
    virtual IOReturn                            clientDied( void );

    // misc methods
    //
    virtual IOUSBPipe *                         GetPipeObj(UInt8 pipeNo);

    // worker method for Isoch stuff
    //
    virtual IOReturn                            DoIsochPipeAsync(OSAsyncReference asyncRef, IOUSBIsocStruct *stuff, IODirection direction);
    virtual IOReturn                            DoLowLatencyIsochPipeAsync(OSAsyncReference asyncRef, IOUSBLowLatencyIsocStruct *stuff, IODirection direction);

    // IOUSBInterface methods
    //
    virtual IOReturn                            GetDevice(io_service_t *device);
    virtual IOReturn                            SetAlternateInterface(UInt8 altInterface);
    virtual IOReturn                            GetFrameNumber(IOUSBGetFrameStruct *data, UInt32 *size);
    virtual IOReturn                            GetMicroFrameNumber(IOUSBGetFrameStruct *data, UInt32 *size);
    virtual IOReturn                            GetBandwidthAvailable(UInt32 *bandwidth);
    virtual IOReturn                            GetFrameListTime(UInt32 *microsecondsInFrame);
    virtual IOReturn                            GetEndpointProperties(UInt8 alternateSetting, UInt8 endpointNumber, UInt8 direction, UInt32 *transferType, UInt32 *maxPacketSize, UInt32 *interval);
    
    // working with pipes
    //
    virtual IOReturn                            GetPipeProperties(UInt8 pipeRef, UInt32 *direction, UInt32 *number, UInt32 *transferType, UInt32 *maxPacketSize, UInt32 *interval);
    virtual IOReturn                            ReadPipe(UInt8 pipeRef, UInt32 noDataTimeout, UInt32 completionTimeout, void *buf, UInt32 *size);
    virtual IOReturn                            ReadPipeOOL(IOUSBBulkPipeReq *reqIn, UInt32 *sizeOut, IOByteCount inCount, IOByteCount *outCount);
    virtual IOReturn                            WritePipe(UInt8 pipeRef, UInt32 noDataTimeout, UInt32 completionTimeout, void *buf, UInt32 size);
    virtual IOReturn                            WritePipeOOL(IOUSBBulkPipeReq *req, IOByteCount inCount);
    virtual IOReturn                            GetPipeStatus(UInt8 pipeRef);
    virtual IOReturn                            AbortPipe(UInt8 pipeRef);
    virtual IOReturn                            ResetPipe(UInt8 pipeRef);
    virtual IOReturn                            SetPipeIdle(UInt8 pipeRef);
    virtual IOReturn                            SetPipeActive(UInt8 pipeRef);
    virtual IOReturn                            ClearPipeStall(UInt8 pipeRef, bool bothEnds);
    virtual IOReturn                            SetPipePolicy(UInt8 pipeRef, UInt16 maxPacketSize, UInt8 maxInterval);
    virtual IOReturn                            ControlRequestIn(UInt32 param1, UInt32 param2, UInt32 noDataTimeout, UInt32 completionTimeout, void *buf, UInt32 *size);
    virtual IOReturn                            ControlRequestOut(UInt32 param1, UInt32 param2, UInt32 noDataTimeout, UInt32 completionTimeout, void *buf, UInt32 size);
    virtual IOReturn                            ControlRequestInOOL(IOUSBDevReqOOLTO *req, UInt32 *sizeOut, IOByteCount inCount, IOByteCount *outCount);
    virtual IOReturn                            ControlRequestOutOOL(IOUSBDevReqOOLTO *req, IOByteCount inCount);

    // async methods
    //
    virtual IOReturn                            SetAsyncPort(OSAsyncReference asyncRef);

    virtual IOReturn                            ControlAsyncRequestOut(OSAsyncReference asyncRef, IOUSBDevReqOOLTO *reqIn, IOByteCount inCount);
    virtual IOReturn                            ControlAsyncRequestIn(OSAsyncReference asyncRef, IOUSBDevReqOOLTO *reqIn, IOByteCount inCount);

    virtual IOReturn                            AsyncReadPipe(OSAsyncReference asyncRef, UInt32 pipe, void *buf, UInt32 size, UInt32 noDataTimeout, UInt32 completionTimeout);
    virtual IOReturn                            AsyncWritePipe(OSAsyncReference asyncRef, UInt32 pipe, void *buf, UInt32 size, UInt32 noDataTimeout, UInt32 completionTimeout);

    virtual IOReturn                            ReadIsochPipe(OSAsyncReference asyncRef, IOUSBIsocStruct *stuff, UInt32 sizeIn);
    virtual IOReturn                            WriteIsochPipe(OSAsyncReference asyncRef, IOUSBIsocStruct *stuff, UInt32 sizeIn);
    virtual IOReturn                            LowLatencyReadIsochPipe(OSAsyncReference asyncRef, IOUSBLowLatencyIsocStruct *stuff, UInt32 sizeIn);
    virtual IOReturn                            LowLatencyWriteIsochPipe(OSAsyncReference asyncRef, IOUSBLowLatencyIsocStruct *stuff, UInt32 sizeIn);

    // bookkeeping methods
    //
    virtual void                                DecrementOutstandingIO(void);
    virtual void                                IncrementOutstandingIO(void);
    virtual UInt32                              GetOutstandingIO(void);
    virtual void                                IncreaseCommandPool();

    // Low Latency Buffer methods
    //
    virtual IOReturn                            LowLatencyPrepareBuffer(LowLatencyUserBufferInfoV2 *bufferData, UInt32 * addrOut, IOByteCount inCount, IOByteCount *outCount);
    virtual IOReturn                            LowLatencyReleaseBuffer(LowLatencyUserBufferInfoV2 *dataBuffer);
    virtual void                                AddDataBufferToList( IOUSBLowLatencyUserClientBufferInfo * insertBuffer );
    virtual IOUSBLowLatencyUserClientBufferInfo *	FindBufferCookieInList( UInt32 cookie);
    virtual bool                                RemoveDataBufferFromList( IOUSBLowLatencyUserClientBufferInfo *removeBuffer);
    virtual void                                ReleasePreparedDescriptors();
    
    
    // static methods
    //
    static const IOExternalMethod               sMethods[kNumUSBInterfaceMethods];
    static const IOExternalAsyncMethod          sAsyncMethods[kNumUSBInterfaceAsyncMethods];
    static void                                 ReqComplete(void *obj, void *param, IOReturn status, UInt32 remaining);
    static void                                 IsoReqComplete(void *obj, void *param, IOReturn res, IOUSBIsocFrame *pFrames);
    static void                                 LowLatencyIsoReqComplete(void *obj, void *param, IOReturn res, IOUSBLowLatencyIsocFrame *pFrames);
    static IOReturn                             ChangeOutstandingIO(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);
    static IOReturn                             GetGatedOutstandingIO(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);

    // padding methods
    //
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  0);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  1);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  2);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  3);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  4);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  5);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  6);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  7);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  8);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient,  9);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 10);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 11);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 12);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 13);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 14);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 15);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 16);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 17);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 18);
    OSMetaClassDeclareReservedUnused(IOUSBInterfaceUserClient, 19);
};

