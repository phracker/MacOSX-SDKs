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

#ifndef _IOKIT_IOAUDIOENGINEUSERCLIENT_H
#define _IOKIT_IOAUDIOENGINEUSERCLIENT_H

#include <IOKit/IOUserClient.h>
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/audio/IOAudioTypes.h>
#include <IOKit/IOBufferMemoryDescriptor.h>

class IOAudioEngine;
class IOAudioStream;
class IOMemoryDescriptor;
class IOCommandGate;
class IOWorkLoop;

class IOAudioEngineUserClient;
class IOAudioClientBufferSet;
typedef struct IOAudioFormatNotification;

typedef struct IOAudioClientBuffer {
    IOAudioEngineUserClient		*userClient;
    IOAudioStream 				*audioStream;
    void						*sourceBuffer;
    IOMemoryDescriptor			*sourceBufferDescriptor;
    IOMemoryMap					*sourceBufferMap;
    void						*unmappedSourceBuffer;
    UInt32						numSampleFrames;
    UInt32						numChannels;
    IOAudioEnginePosition		mixedPosition;
    struct IOAudioClientBuffer	*next;
    struct IOAudioClientBuffer	*nextClip;
    struct IOAudioClientBuffer	*previousClip;
    struct IOAudioClientBuffer	*nextClient;
	IOAudioBufferDataDescriptor *bufferDataDescriptor;
} IOAudioClientBuffer;

typedef struct IOAudioClientBufferExtendedInfo {
	// Added stuff for registerClientParameterBuffer
	UInt32						bufferSetID;
	void						*paramBuffer;
	IOMemoryDescriptor			*paramBufferDescriptor;
	IOMemoryMap					*paramBufferMap;
	void						*unmappedParamBuffer;
	struct IOAudioClientBufferExtendedInfo	*next;
} IOAudioClientBufferExtendedInfo;

class IOAudioEngineUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(IOAudioEngineUserClient)

    friend class IOAudioEngine;
    friend class IOAudioClientBufferSet;
    friend class IOAudioStream;

protected:
    IOAudioEngine				*audioEngine;
    
    IOWorkLoop					*workLoop;
    IOCommandGate				*commandGate;

    IOExternalMethod			old_methods[5];		// It's size can't be changed for binary compatibility reasons, no longer used.
    IOExternalTrap				trap;

    task_t						clientTask;
    UInt32						numSampleFrames;		// Never used...
    
    IOAudioClientBufferSet		*clientBufferSetList;
    IORecursiveLock 			*clientBufferLock;
    
    IOAudioNotificationMessage	*notificationMessage;
    
    bool						online;
    
protected:
    struct ExpansionData {
		IOAudioClientBufferExtendedInfo		*extendedInfo;
		IOExternalMethod					methods[kIOAudioEngineNumCalls];		// This size can be changed, this is the new methods pointer
 		UInt32								classicMode;
//		void								*securityToken;
	};

    ExpansionData *reserved;

public:
	// New code added here...
	virtual IOReturn registerClientParameterBuffer (void *parameterBuffer, UInt32 bufferSetID);
	virtual IOAudioClientBufferExtendedInfo * findExtendedInfo(UInt32 bufferSetID);
	virtual IOReturn getNearestStartTime(IOAudioStream *audioStream, IOAudioTimeStamp *ioTimeStamp, UInt32 isInput);
	virtual IOReturn getClientNearestStartTime(IOAudioStream *audioStream, IOAudioTimeStamp *ioTimeStamp, UInt32 isInput);
	virtual IOReturn safeRegisterClientBuffer(UInt32 audioStreamIndex, void *sourceBuffer, UInt32 bufSizeInBytes, UInt32 bufferSetID);
#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
    // OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 5);	
    virtual bool initWithAudioEngine(IOAudioEngine *engine, task_t task, void *securityToken, UInt32 type, OSDictionary *properties);
#endif

private:
    OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 0);
    OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 1);
    OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 2);
    OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 3);
    OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 4);
#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
    OSMetaClassDeclareReservedUsed(IOAudioEngineUserClient, 5);
#else
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 5);
#endif

    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 6);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 7);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 8);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 9);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 10);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 11);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 12);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 13);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 14);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 15);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 16);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 17);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 18);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 19);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 20);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 21);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 22);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 23);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 24);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 25);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 26);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 27);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 28);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 29);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 30);
    OSMetaClassDeclareReservedUnused(IOAudioEngineUserClient, 31);

protected:
    virtual IOReturn clientClose();
    virtual IOReturn clientDied();
    
    static IOReturn closeClientAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    virtual IOReturn closeClient();

    virtual IOReturn clientMemoryForType(UInt32 type, UInt32 *flags, IOMemoryDescriptor **memory);
    virtual IOExternalMethod *getExternalMethodForIndex(UInt32 index);
    virtual IOExternalTrap *getExternalTrapForIndex(UInt32 index);
    virtual IOReturn registerNotificationPort(mach_port_t port, UInt32 type, UInt32 refCon);
    
    static IOReturn registerNotificationAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    virtual IOReturn registerNotification(mach_port_t port, UInt32 refCon);
    
    virtual void setOnline(bool newOnline);
    
	virtual IOReturn performClientOutput(UInt32 firstSampleFrame, UInt32 loopCount, IOAudioClientBufferSet *bufferSet, UInt32 sampleIntervalHi, UInt32 sampleIntervalLo);
    virtual IOReturn performClientInput(UInt32 firstSampleFrame, IOAudioClientBufferSet *bufferSet);
    virtual void performWatchdogOutput(IOAudioClientBufferSet *clientBufferSet, UInt32 generationCount);
    
    virtual void lockBuffers();
    virtual void unlockBuffers();

public:

    static IOAudioEngineUserClient *withAudioEngine(IOAudioEngine *engine, task_t clientTask, void *securityToken, UInt32 type);
    static IOAudioEngineUserClient *withAudioEngine(IOAudioEngine *engine, task_t clientTask, void *securityToken, UInt32 type, OSDictionary *properties);

    virtual bool initWithAudioEngine(IOAudioEngine *engine, task_t task, void *securityToken, UInt32 type);

    virtual void free();
    virtual void freeClientBufferSetList();
    virtual void freeClientBuffer(IOAudioClientBuffer *clientBuffer);
    
    virtual void stop(IOService *provider);
    
    virtual bool isOnline();
    
    virtual IOReturn registerBuffer(IOAudioStream *audioStream, void *sourceBuffer, UInt32 bufSizeInBytes, UInt32 bufferSetID);
    virtual IOReturn unregisterBuffer(void *sourceBuffer, UInt32 bufferSetID);
    
    static IOReturn registerBufferAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    static IOReturn unregisterBufferAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);

    virtual IOReturn registerClientBuffer(IOAudioStream *audioStream, void *sourceBuffer, UInt32 bufSizeInBytes, UInt32 bufferSetID);
    virtual IOReturn unregisterClientBuffer(void *sourceBuffer, UInt32 bufferSetID);
    
    static IOReturn getNearestStartTimeAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);

    virtual IOAudioClientBufferSet *findBufferSet(UInt32 bufferSetID);
    virtual void removeBufferSet(IOAudioClientBufferSet *bufferSet);
    
    virtual IOReturn getConnectionID(UInt32 *connectionID);
    
    virtual IOReturn clientStart();
    virtual IOReturn clientStop();
    
    static IOReturn startClientAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    static IOReturn stopClientAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);

    virtual IOReturn startClient();
    virtual IOReturn stopClient();
    
    virtual IOReturn performClientIO(UInt32 firstSampleFrame, UInt32 loopCount, bool inputIO, UInt32 bufferSetID, UInt32 sampleIntervalHi, UInt32 sampleIntervalLo);
    
    virtual void sendFormatChangeNotification(IOAudioStream *audioStream);
    virtual IOReturn sendNotification(UInt32 notificationType);
    
};

#endif /* _IOKIT_IOAUDIOENGINEUSERCLIENT_H */
