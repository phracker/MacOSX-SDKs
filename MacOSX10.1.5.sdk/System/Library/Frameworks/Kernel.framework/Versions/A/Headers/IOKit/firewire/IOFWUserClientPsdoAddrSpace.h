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
*  IOFWUserClientPsdoAddrSpace.h
 *  IOFireWireFamily
 *
 *  Created by NWG on Fri Dec 08 2000.
 *  Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __IOFWUserClientPsduAddrSpace_H__
#define __IOFWUserClientPsduAddrSpace_H__

#include <IOKit/OSMessageNotification.h>
#include <IOKit/firewire/IOFireWireFamilyCommon.h>
#include <IOKit/firewire/IOFireWireUserClient.h>

typedef union IOFWPacketHeader_t
{
    typedef enum QueueTag_t
    {
        kFree = 0,
        kStopPacket     = 'stop',
        kBadPacket	   = ' bad',
        kIncomingPacket = 'pckt',
        kSkippedPacket = 'skip',
		kReadPacket	= 'read'
    } QueueTag ;

    struct CommonHeader_t
    {
        QueueTag_t 					type ;
        IOFWPacketHeader_t*			next ;
        OSAsyncReference*			whichAsyncRef ;
        UInt32						argCount ;
        
        UInt32						args[8] ;
    } CommonHeader ;

    struct IncomingPacket_t
    {
        // -----------------------------------------------
        QueueTag_t 					type ;
        IOFWPacketHeader_t*			next ;
        OSAsyncReference*			whichAsyncRef ;
        UInt32						argCount ;
        // -----------------------------------------------
        
        UInt32						commandID ;			//	0
        UInt32						packetSize ;		//	1
        UInt32						packetOffset ;		//	2
        UInt32						nodeID ;
        UInt32						speed ;
        UInt32						addrHi ;
        UInt32						addrLo ;
        UInt32						lockWrite ;

    } IncomingPacket ;

    struct SkippedPacket_t
    {
        // -----------------------------------------------
        QueueTag_t 					type ;
        IOFWPacketHeader_t*			next ;
        OSAsyncReference*			whichAsyncRef ;
        UInt32						argCount ;
        // -----------------------------------------------

        UInt32						commandID ;			//	0
        UInt32						skippedPacketCount ;
    } SkippedPacket ;

	struct ReadPacket_t
	{
	    // -----------------------------------------------
	    QueueTag_t 					type ;
		IOFWPacketHeader_t*			next ;
		OSAsyncReference*			whichAsyncRef ;
		UInt32						argCount ;
		// -----------------------------------------------

        UInt32						commandID ;			//	0
        UInt32						packetSize ;		//	1
        UInt32						packetOffset ;		//	2
        UInt32						nodeID ;
        UInt32						speed ;
        UInt32						addrHi ;
        UInt32						addrLo ;
		
	} ReadPacket ;

public:
    IOFWPacketHeader_t() ;
    
} IOFWPacketHeader ;

inline IOByteCount& IOFWPacketHeaderGetSize(IOFWPacketHeader_t* hdr) ;
inline IOByteCount& IOFWPacketHeaderGetOffset(IOFWPacketHeader_t* hdr) ;
inline void InitIncomingPacketHeader(IOFWPacketHeader* header,
	const union IOFWPacketHeader_t* next,
	const IOByteCount				len,
	const IOByteCount				offset,
	OSAsyncReference				ref,
	void*							refCon,
	UInt16							nodeID,
	const IOFWSpeed&  				speed,
	const FWAddress&				addr,
	const Boolean					lockWrite) ;
inline void InitSkippedPacketHeader(
	IOFWPacketHeader*				header,
	const union IOFWPacketHeader_t* next,
	const IOByteCount				offset,
	OSAsyncReference*				ref,
	void*							refCon) ;
inline void InitReadPacketHeader(
	IOFWPacketHeader*				header,
	IOFWPacketHeader*				next,
	UInt32							len,
	UInt32							offset,
	OSAsyncReference*				ref,
	void*							refCon,
	UInt16							nodeID,
	IOFWSpeed&						speed,
	FWAddress						addr,
	IOFWRequestRefCon				reqrefcon) ;
inline Boolean IsSkippedPacketHeader(const union IOFWPacketHeader_t* header) ;
inline Boolean IsFreePacketHeader(const union IOFWPacketHeader_t* header) ;
inline Boolean IsReadPacketHeader(const union IOFWPacketHeader_t* header) ;


// To support mapping the memory descriptor within
// a pseudo address space to user space, we need to add
// accessors to IOFWPseudoAddressSpace. This class
// implements the additional functionality.
class IOFWUserClientPseudoAddrSpace: public IOFWPseudoAddressSpace
{
	OSDeclareDefaultStructors(IOFWUserClientPseudoAddrSpace)

public:
	virtual bool					initAll(
											IOFireWireUserClient*		me,
                                            IOMemoryDescriptor*			inPacketQueueBuffer,
											IOMemoryDescriptor*			inBackingStore,
											UInt32						inRefCon,
											IOFireWireController*		control,
                							FWAddress*					addr,
											UInt32 						len, 
											FWReadCallback 				reader,
											FWWriteCallback 			writer,
											void*						refcon);

	// override deactivate so we can delete any notification related structures...
	virtual void					free() ;
	virtual void					deactivate() ;
	
	// === getters ==========
    const FWAddress& 				getBase() { return fBase;}
	const UInt32					getLength() { return fLen; }
	const UInt32					getUserRefCon() { return fUserRefCon ;}
	const IOFireWireUserClient&		getUserClient() { return *fUserClient ;}

    static UInt32					pseudoAddrSpaceReader(
                                            void*					refCon,
                                            UInt16					nodeID,
                                            IOFWSpeed& 				speed,
                                            FWAddress 				addr,
                                            UInt32		 			len,
                                            IOMemoryDescriptor**	buf,
                                            IOByteCount* 			offset,
                                            IOFWRequestRefCon		reqrefcon) ;
    static UInt32					pseudoAddrSpaceWriter(
                                            void*					refCon,
                                            UInt16					nodeID,
                                            IOFWSpeed&				speed,
                                            FWAddress				addr,
                                            UInt32					len,
                                            const void*				buf,
                                            IOFWRequestRefCon		reqrefcon) ;
	virtual void					setAsyncRef_Packet(
											OSAsyncReference		inAsyncRef) ;
	virtual void					setAsyncRef_SkippedPacket(
											OSAsyncReference		inAsyncRef) ;
	virtual void					setAsyncRef_Read(
											OSAsyncReference		inAsyncRef) ;
	virtual void					clientCommandIsComplete(
											FWClientCommandID		inCommandID) ;
	void							sendPacketNotification(
											IOFWPacketHeader*		inPacketHeader) ;
private:
    IOMemoryDescriptor*		fPacketQueueBuffer ;
	IOMemoryDescriptor*		fBackingStore ;
	
	UInt32					fUserRefCon ;
	IOFireWireUserClient*	fUserClient ;
	IOFWPacketHeader*		fLastWrittenHeader ;
	IOFWPacketHeader*		fLastReadHeader ;
	UInt32					fBufferAvailable ;
	IOLock*					fLock ;
	FWAddress				fAddress ;

	OSAsyncReference		fSkippedPacketAsyncNotificationRef ;
	OSAsyncReference		fPacketAsyncNotificationRef ;
	OSAsyncReference		fReadAsyncNotificationRef ;
	bool					fWaitingForUserCompletion ;
} ;

#endif //__IOFWUserClientPsduAddrSpace_H__
