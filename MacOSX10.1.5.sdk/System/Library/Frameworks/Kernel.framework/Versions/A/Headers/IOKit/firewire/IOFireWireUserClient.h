/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved. 
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOFIREWIREUSERCLIENT_H
#define _IOKIT_IOFIREWIREUSERCLIENT_H

#include <IOKit/IOUserClient.h>
#include <IOKit/firewire/IOFWIsoch.h>
#include <IOKit/firewire/IOLocalConfigDirectory.h>
#include <IOKit/firewire/IOFWAddressSpace.h>
#include <IOKit/firewire/IOFireWireNub.h>
#include <IOKit/firewire/IOFireWireFamilyCommon.h>
#include <IOKit/firewire/IOFireWireBus.h>

#ifndef Byte
typedef unsigned char Byte ;
#endif

#if IOFIREWIREUSERCLIENTDEBUG
	#define IOFireWireUserClientLog_(x) IOLog x
	#define IOFireWireUserClientLogIfNil_(x, y) \
	{ if ((void*)(x) == NULL) { IOFireWireUserClientLog_(y); } }
	#define IOFireWireUserClientLogIfErr_(x, y) \
	{ if ((x) != 0) { IOFireWireUserClientLog_(y); } }
	#define IOFireWireUserClientLogIfFalse_(x, y) \
	{ if (!(x)) { IOFireWireUserClientLog_(y); } }
#else
	#define IOFireWireUserClientLog_(x)
	#define IOFireWireUserClientLogIfNil_(x, y)
	#define IOFireWireUserClientLogIfErr_(x, y)
	#define IOFireWireUserClientLogIfFalse_(x, y)
#endif

typedef struct AsyncRefHolder_t
{
	OSAsyncReference	asyncRef ;
	void*				userRefCon ;
} AsyncRefHolder ;


class IOFireWireDevice;

class IOFireWireUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(IOFireWireUserClient)

//	friend class IOFWUserClientPseudoAddrSpace ;	// zzz - does this violate IOKit convention?
//	friend class IOFWUserClientPhysicalAddressSpace ;
//	friend class IOFWUserIsochPort ;
//	friend class IOFWUserCommand ;
//	friend class IOFWUserReadQuadletCommand ;

private:
    IOFireWireNub *			fOwner;
    task_t					fTask;
    IOExternalMethod		fMethods[ kNumFireWireMethods ];
    IOExternalAsyncMethod 	fAsyncMethods[ kNumFireWireAsyncMethods ];

	IOLock*					fSetLock ;

	OSSet*					fUserPseudoAddrSpaces ;	// all user allocated pseudo address spaces
	OSSet*					fUserPhysicalAddrSpaces ;
	OSSet*					fUserUnitDirectories ;
	OSSet*					fUserIsochChannels ;
	OSSet*					fUserIsochPorts ;
	OSSet*					fUserCommandObjects ;
	
	mach_port_t				fNotificationPort ;
	UInt32					fNotificationRefCon ;
	OSAsyncReference		fBusResetAsyncNotificationRef ;
	OSAsyncReference		fBusResetDoneAsyncNotificationRef ;
	IONotifier*				fNotifier ;
	IOService*				fOpenClient ;

    static void 					kernPongProc(
											void*					refcon,
											void* 					userProc,
											void* 					dclCommand);

public:
    inline static IOReturn 			sendAsyncResult(
											OSAsyncReference 		reference,
											IOReturn 				result, 
											void*					args[], 
											UInt32 					numArgs)
											{ return IOUserClient::sendAsyncResult(reference, result, args, numArgs) ; }
									
    static IOFireWireUserClient*	withTask(
											task_t 					owningTask);
    virtual IOReturn 				clientClose( void );
    virtual IOReturn 				clientDied( void );
	virtual IOExternalMethod*		getTargetAndMethodForIndex(IOService **target, UInt32 index) ;
	virtual IOExternalAsyncMethod*	getAsyncTargetAndMethodForIndex(IOService **target, UInt32 index) ;
	virtual const task_t			getOwningTask() const {return fTask;}
	virtual IOFireWireNub*			getOwner() const { return fOwner; }
    virtual IOReturn				registerNotificationPort(
                                            mach_port_t 			port,
                                            UInt32					/* type */,
                                            UInt32					refCon) ;
	virtual bool 					start(
											IOService * provider );

	// --- utils ----------
    inline static void 				setAsyncReference(
											OSAsyncReference 		asyncRef,
											mach_port_t 			wakePort,
											void*					callback, 
											void*					refcon)
											{ IOUserClient::setAsyncReference(asyncRef, wakePort, callback, refcon) ; }
	virtual IOReturn				addObjectToSet(
											OSObject* 				object, 
											OSSet* 					set) ;
	virtual void					removeObjectFromSet(
											OSObject* 				object, 
											OSSet* 					set) ;
	virtual void					initMethodTable() ;
	virtual void					initIsochMethodTable() ;
	virtual void					initAsyncMethodTable() ;
	virtual void					initIsochAsyncMethodTable() ;
	
	static IOReturn 				interestHandler(
											void*					target,
											void* 					refCon,
											UInt32					messageType,
											IOService*				provider,
											void*					messageArgument,
											vm_size_t				argSize );
											
	// --- open/close ----------
	virtual IOReturn				userOpen() ;
	virtual IOReturn				userOpenWithSessionRef(IOService*	session) ;
	virtual IOReturn				userClose() ;
	
	// --- read ----------------
	virtual IOReturn				readQuad(
											UInt64					addr,
											UInt32					failOnReset,
											UInt32					generation,
											UInt32*					val) ;
	virtual IOReturn				readQuadAbsolute(
											UInt64					addr,
											UInt32					failOnReset,
											UInt32					generation,
											UInt32*					val) ;
    virtual IOReturn 				read(
											FWReadWriteParams*		inParams,
											UInt32*					outSize) ;
    virtual IOReturn 				readAbsolute(
											FWReadWriteParams* 		inParams,
											UInt32*					outSize) ;
	// --- write ----------
    virtual IOReturn 				writeQuad(
											UInt64					addr,
											UInt32					val,
											UInt32					failOnReset,
											UInt32					generation) ;
    virtual IOReturn 				writeQuadAbsolute(
											UInt64					addr,
											UInt32					val,
											UInt32					failOnReset,
											UInt32					generation) ;
    virtual IOReturn 				write(
											FWReadWriteParams* 		inParams,
											UInt32*					outSize) ;
/*											FWAddress				addr,
											void*					buf,
											UInt32 					size,
											UInt32					failOnReset,
											UInt32					generation); */
    virtual IOReturn 				writeAbsolute(
											FWReadWriteParams* 		inParams,
											UInt32*					outSize) ;
/*											FWAddress				addr,
											void*					buf,
											UInt32 					size,
											UInt32					failOnReset,
											UInt32					generation); */
	// --- compare/swap ----------
    virtual IOReturn 				compareSwap(
											UInt64					addr,
											UInt32 					cmpVal,
											UInt32 					newVal,
											UInt32					failOnReset,
											UInt32					generation);
    virtual IOReturn 				compareSwapAbsolute(
											UInt64					addr,
											UInt32 					cmpVal,
											UInt32 					newVal,
											UInt32					failOnReset,
											UInt32					generation);

	// --- other -----------------
    virtual IOReturn 				busReset();
	virtual IOReturn				getGenerationAndNodeID(
											UInt32*					outGeneration,
											UInt16*					outNodeID) const ;
	virtual IOReturn				getLocalNodeID(
											UInt16*					outLocalNodeID) const ;
	virtual IOReturn				getResetTime(
											AbsoluteTime*			outResetTime) const ;
    virtual IOReturn 				message(
											UInt32 					type,
											IOService* 				provider,
											void* 					argument );
    virtual IOReturn 				Test();

    // --- DCL Methods ----------
	
//	virtual IOReturn 				compileDCL(
//											UInt32 					dclStart,
//											UInt32 					dclBase,
//											UInt32 					dclSize,
//											UInt32 					dataBase,
//											UInt32 					dataSize,
//											UInt32*					program);
//	virtual IOReturn 				runDCL(
//											OSAsyncReference 		asyncRef,
//											UInt32 					program);
//	virtual IOReturn 				stopDCL(
//											UInt32 					program);

	// --- my conversion helpers -------
	virtual IOReturn				getOSStringData(
											FWKernOSStringRef		inStringRef,
											UInt32					inStringLen,
											char*					inStringBuffer,
											UInt32*					outStringLen) ;
	virtual IOReturn				getOSDataData(
											FWKernOSDataRef			inDataRef,
											IOByteCount				inDataLen,
											char*					inDataBuffer,
											IOByteCount*			outDataLen) ;
	
	//
    // --- CSR ROM Methods ----------
	//
	virtual IOReturn				unitDirCreate(
											IOLocalConfigDirectory**	outDir) ;
	virtual IOReturn				unitDirRelease(
											IOLocalConfigDirectory*	dir) ;
	virtual IOReturn				addEntry_Buffer(
											IOLocalConfigDirectory*	dir, 
											int 					key,
											char*					buffer,
											UInt32					kr_size ) ;
	virtual IOReturn				addEntry_UInt32(
											IOLocalConfigDirectory*	inDir,
											int						key,
											UInt32					value) ;
	virtual IOReturn				addEntry_FWAddr(
											IOLocalConfigDirectory*	dir, 
											int 					key,
											FWAddress				value ) ;
	virtual IOReturn				addEntry_UnitDir(
											IOLocalConfigDirectory*	dir,
											int						key,
											IOLocalConfigDirectory*	value) ;
	virtual IOReturn				publish(
											IOLocalConfigDirectory*	inDir ) ;
	virtual IOReturn				unpublish(
											IOLocalConfigDirectory*	inDir) ;

	//
    // --- Address Spaces Methods ----------
	//
	virtual IOReturn				allocateAddressSpace(
											FWAddrSpaceCreateParams*	inParams,
											FWKernAddrSpaceRef* 		outKernAddrSpaceRef) ;
	virtual IOReturn				releaseAddressSpace(
											IOFWUserClientPseudoAddrSpace*	inAddrSpace) ;
	virtual IOReturn				getPseudoAddressSpaceInfo(
											IOFWUserClientPseudoAddrSpace*	inAddrSpaceRef,
											UInt32*					outNodeID,
											UInt32*					outAddressHi,
											UInt32*					outAddressLo) ;
	virtual IOReturn				setAsyncRef_Packet(
											OSAsyncReference		asyncRef,
											FWKernAddrSpaceRef		inAddrSpaceRef,
											void*					inCallback,
											void*					inUserRefCon,
											void*,
											void*,
											void*) ;
	virtual IOReturn				setAsyncRef_SkippedPacket(
											OSAsyncReference		asyncRef,
											FWKernAddrSpaceRef		inAddrSpaceRef,
											void*					inCallback,
											void*					inUserRefCon,
											void*,
											void*,
											void*) ;
	virtual IOReturn				setAsyncRef_Read(
											OSAsyncReference		asyncRef,
											FWKernAddrSpaceRef		inAddrSpaceRef,
											void*					inCallback,
											void*					inUserRefCon,
											void*,
											void*,
											void*) ;
	virtual IOReturn				setAsyncRef_BusReset(
											OSAsyncReference		asyncRef,
											void*					inCallback,
											void*					inUserRefCon,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				setAsyncRef_BusResetDone(
											OSAsyncReference		asyncRef,
											void*					inCallback,
											void*					inUserRefCon,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				clientCommandIsComplete(
											FWKernAddrSpaceRef		inAddrSpaceRef,
											FWClientCommandID		inCommandID) ;											

	//
	//	--- physical address space stuff ----------
	//
	virtual IOReturn				allocatePhysicalAddressSpace(
											FWPhysicalAddrSpaceCreateParams* inParams,
											FWKernPhysicalAddrSpaceRef* outKernAddrSpaceRef) ;
	virtual IOReturn				releasePhysicalAddressSpace(
											IOFWUserClientPhysicalAddressSpace*	inAddrSpace) ;
	virtual IOReturn				getPhysicalAddressSpaceSegmentCount(
											IOFWUserClientPhysicalAddressSpace*	inAddrSpace,
											UInt32*								outSegmentCount) ;
	virtual IOReturn				getPhysicalAddressSpaceSegments(
											IOFWUserClientPhysicalAddressSpace*	inAddrSpace,
											UInt32								inSegmentCount,
											UInt32*								outSegmentCount,
											IOPhysicalAddress					segments[],
											IOByteCount							segmentLengths[]) ;
	
	//
	//	--- async commands ----------
	//
/*	virtual IOReturn				readQuadAsync(
											OSAsyncReference			asyncRef,
											FWReadWriteQuadAsyncParams*	inParams,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				readQuadAbsoluteAsync(
											OSAsyncReference			asyncRef,
											FWReadWriteQuadAsyncParams*	inParams,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				readAsync(
											OSAsyncReference		asyncRef,
											FWReadWriteAsyncParams*	inParams,
											mach_msg_type_number_t*	outSize,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				readAbsoluteAsync(
											OSAsyncReference		asyncRef,
											FWReadWriteAsyncParams*	inParams,
											mach_msg_type_number_t*	outSize,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				writeQuadAsync(
											OSAsyncReference		asyncRef,
											FWReadWriteQuadAsyncParams*	inParams,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				writeQuadAbsoluteAsync(
											OSAsyncReference		asyncRef,
											FWReadWriteQuadAsyncParams*	inParams,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				writeAsync(
											OSAsyncReference		asyncRef,
											FWReadWriteAsyncParams*	inParams,
											mach_msg_type_number_t*	outSize,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				writeAbsoluteAsync(
											OSAsyncReference		asyncRef,
											FWReadWriteAsyncParams*	inParams,
											mach_msg_type_number_t*	outSize,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				compareSwapAsync(
											OSAsyncReference		asyncRef,
											FWCompareSwapAsyncParams* inParams,
											void*,
											void*,
											void*,
											void*,
											void*) ;
	virtual IOReturn				compareSwapAbsoluteAsync(
											OSAsyncReference		asyncRef,
											FWCompareSwapAsyncParams* inParams,
											void*,
											void*,
											void*,
											void*,
											void*) ;*/
	virtual IOReturn				userAsyncCommand_Submit(
											OSAsyncReference			asyncRef,
											FWUserCommandSubmitParams*	inParams,
											FWUserCommandSubmitResult*	outResult,
											UInt32						inParamsSize,
											UInt32*						outResultSize) ;
	virtual IOReturn				userAsyncCommand_SubmitAbsolute(
											OSAsyncReference			asyncRef,
											FWUserCommandSubmitParams*	inParams,
											FWUserCommandSubmitResult*	outResult) ;

	static void						asyncReadWriteCommandCompletion(
											void *					refcon, 
											IOReturn 				status, 
											IOFireWireNub *			device, 
											IOFWCommand *			fwCmd);
	
	//
	//	--- config directory functions ----------
	//
	virtual IOReturn configDirectoryCreate(
							FWKernConfigDirectoryRef*	outDirRef) ;
	virtual IOReturn configDirectoryRelease(
							FWKernConfigDirectoryRef	dirRef) ;
	virtual IOReturn configDirectoryUpdate(
							FWKernConfigDirectoryRef 	dirRef, 
							UInt32 						offset, 
							const UInt32*&				romBase) ;
    virtual IOReturn configDirectoryGetKeyType(
							FWKernConfigDirectoryRef 	dirRef, 
							int 						key, 
							IOConfigKeyType* 			type);
    virtual IOReturn configDirectoryGetKeyValue_UInt32(
							FWKernConfigDirectoryRef	inDirRef,
							int							key,
							UInt32*						outValue,
							FWKernOSStringRef*			outString,
							UInt32*						outStringLen);
    virtual IOReturn configDirectoryGetKeyValue_Data(
							FWKernConfigDirectoryRef	inDirRef,
							int							key,
							FWKernOSDataRef*			outValue,
							IOByteCount*				outDataSize,
							FWKernOSStringRef*			outString,
							UInt32*						outStringLen);
    virtual IOReturn configDirectoryGetKeyValue_ConfigDirectory(
							FWKernConfigDirectoryRef	inDirRef,
							int							key,
							FWKernConfigDirectoryRef*	outValue,
							FWKernOSStringRef*			outString,
							UInt32*						outStringLen);
    virtual IOReturn configDirectoryGetKeyOffset_FWAddress(
							FWKernConfigDirectoryRef	inDirRef,
							int							key,
							UInt32*						addressHi,
							UInt32*						addressLo,
							FWKernOSStringRef*			outString,
							UInt32*						outStringLen);
    virtual IOReturn configDirectoryGetIndexType(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							IOConfigKeyType*			outType);
    virtual IOReturn configDirectoryGetIndexKey(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							int*						outKey);
    virtual IOReturn configDirectoryGetIndexValue_UInt32(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							UInt32*						outKey);
    virtual IOReturn configDirectoryGetIndexValue_Data(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							FWKernOSDataRef*			outDataRef,
							IOByteCount*				outDataLen);
    virtual IOReturn configDirectoryGetIndexValue_String(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							FWKernOSStringRef*			outString,
							UInt32*						outStringLen);
    virtual IOReturn configDirectoryGetIndexValue_ConfigDirectory(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							FWKernConfigDirectoryRef*	outDirRef);
    virtual IOReturn configDirectoryGetIndexOffset_FWAddress(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							UInt32*						addressHi,
							UInt32*						addressLo);
    virtual IOReturn configDirectoryGetIndexOffset_UInt32(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							UInt32*						outValue);
    virtual IOReturn configDirectoryGetIndexEntry(
							FWKernConfigDirectoryRef	inDirRef,
							int							index,
							UInt32*						outValue);
    virtual IOReturn configDirectoryGetSubdirectories(
							FWKernConfigDirectoryRef	inDirRef,
							OSIterator**				outIterator);
	virtual IOReturn configDirectoryGetKeySubdirectories(
							FWKernConfigDirectoryRef	inDirRef,
							int							key,
							OSIterator**				outIterator);
	virtual IOReturn configDirectoryGetType(
							FWKernConfigDirectoryRef dirRef, int *outType) ;
	virtual IOReturn configDirectoryGetNumEntries(
							FWKernConfigDirectoryRef dirRef, int *outNumEntries) ;
							
	//
	// --- isoch port -------------
	//
	virtual IOReturn	isochPortAllocate(
								FWIsochPortAllocateParams*	inParams,
								FWKernIsochPortRef*			outPortRef) ;
	virtual IOReturn	isochPortRelease(
								FWKernIsochPortRef		inPortRef) ;
	virtual IOReturn	isochPortGetSupported(
								FWKernIsochPortRef		inPortRef,
								IOFWSpeed*				outMaxSpeed,
								UInt32*					outChanSupportedHi,
								UInt32*					outChanSupportedLo) ;
	virtual IOReturn	isochPortAllocatePort(
								FWKernIsochPortRef		inPortRef,
								IOFWSpeed				inSpeed,
								UInt32					inChannel) ;
	virtual IOReturn	isochPortReleasePort(
								FWKernIsochPortRef		inPortRef) ;
	virtual IOReturn	isochPortStart(
								FWKernIsochPortRef		inPortRef) ;
	virtual IOReturn	isochPortStop(
								FWKernIsochPortRef		inPortRef) ;

	//
	// local isoch port
	//
	virtual IOReturn	localIsochPortAllocate(
								FWLocalIsochPortAllocateParams*	inParams,
								FWKernIsochPortRef*		outPortRef) ;
	virtual IOReturn	localIsochPortModifyJumpDCL(
								FWKernIsochPortRef		inPortRef,
								UInt32					inJumpDCLCompilerData,
								UInt32					inLabelDCLCompilerData) ;
	virtual IOReturn	setAsyncRef_DCLCallProc(
								OSAsyncReference		asyncRef,
								FWKernIsochPortRef		inPortRef,
								DCLCallCommandProcPtr	inProc) ;
	
	//
	// --- isoch channel ----------
	//
	static IOReturn		isochChannelForceStopHandler(
								void*					refCon,
								IOFWIsochChannel*		isochChannelID,
								UInt32					stopCondition) ;
	virtual IOReturn	isochChannelAllocate(
								bool					inDoIRM,
								UInt32					inPacketSize,
								IOFWSpeed				inPrefSpeed,
								FWKernIsochChannelRef*	outIsochChannelRef) ;
	virtual IOReturn	isochChannelRelease(
								FWKernIsochChannelRef	inChannelRef) ;
/*	virtual IOReturn	isochChannelSetTalker(
								FWKernIsochChannelRef	inChannelRef,
								FWKernIsochPortRef		inTalkerRef) ;
	virtual IOReturn	isochChannelAddListener(
								FWKernIsochChannelRef	inChannelRef,
								FWKernIsochPortRef		inListenerRef) ;
	virtual IOReturn	isochChannelAllocateChannel(
								FWKernIsochChannelRef	inChannelRef) ;
	virtual IOReturn	isochChannelReleaseChannel(
								FWKernIsochChannelRef	inChannelRef) ;
	virtual IOReturn	isochChannelStart(
								FWKernIsochChannelRef	inChannelRef) ;
	virtual IOReturn	isochChannelStop(
								FWKernIsochChannelRef	inChannelRef) ;*/
	virtual IOReturn	isochChannelUserAllocateChannelBegin(
								FWKernIsochChannelRef	inChannelRef,
								IOFWSpeed				inSpeed,
//								UInt32					inAllowedChansHi,
//								UInt32					inAllowedChansLo,
								UInt64					inAllowedChans,
								IOFWSpeed*				outSpeed,
								UInt32*					outChannel) ;
	virtual IOReturn	isochChannelUserReleaseChannelComplete(
								FWKernIsochChannelRef	inChannelRef) ;
	virtual IOReturn	setAsyncRef_IsochChannelForceStop(
								OSAsyncReference		asyncRef,
								void*					inCallback,
								void*					inUserRefCon,
								void*,
								void*,
								void*,
								void*) ;

	//
	// --- firewire command objects ----------------------
	//
	virtual IOReturn	userAsyncCommand_Release(
								FWKernCommandRef		inCommandRef) ;
	virtual IOReturn	userAsyncCommand_Cancel(
								FWKernCommandRef		inCommandRef,
								IOReturn				reason) { return kIOReturnUnsupported; }
};

#endif /* ! _IOKIT_IOFIREWIREUSERCLIENT_H */

