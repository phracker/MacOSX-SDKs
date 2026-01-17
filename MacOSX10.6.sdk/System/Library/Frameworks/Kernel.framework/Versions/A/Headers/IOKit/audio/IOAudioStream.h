/*
 * Copyright (c) 1998-2010 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOKIT_IOAUDIOSTREAM_H
#define _IOKIT_IOAUDIOSTREAM_H

#include <IOKit/IOService.h>
#ifndef IOAUDIOFAMILY_SELF_BUILD
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/audio/IOAudioTypes.h>
#else
#include "IOAudioEngine.h"
#include "IOAudioTypes.h"
#endif

class OSSymbol;
class OSArray;
class OSDictionary;
class OSSet;

class IOCommandGate;
class IOAudioControl;

typedef struct IOAudioClientBuffer;
typedef struct IOAudioStreamFormatDesc;

/*!
 * @class IOAudioStream
 * @abstract This class wraps a single sample buffer in an audio driver.
 * @discussion An IOAudioStream represents one hardware sample buffer as well as the direction
 *  of that buffer, the mix buffer that multiple clients mix into as well as a list of
 *  all of the formats to which this buffer can be set.
 *
 *  When an IOAudioEngine is created during init time in the driver, an IOAudioStream must be
 *  created for each sample buffer in the device.  Typically, the sample buffer will be interleaved 
 *  (or single channel), as a non-interleaved buffer should be divided into multiple single-channel
 *  buffers (and multiple IOAudioStreams).
 *
 *  Additionally, when an IOAudioStream is created it must have all of the possible formats (and
 *  allowed sample rates for each format) set and must have the currently set format specified
 *  (addAvailableFormat() and setFormat()).
 */

class IOAudioStream : public IOService
{
    OSDeclareDefaultStructors(IOAudioStream)
    
    friend class IOAudioEngine;
    friend class IOAudioEngineUserClient;

public:

    typedef IOReturn (*AudioIOFunction)(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
    
    static const OSSymbol	*gDirectionKey;
    static const OSSymbol	*gNumChannelsKey;
    static const OSSymbol	*gSampleFormatKey;
    static const OSSymbol	*gNumericRepresentationKey;
    static const OSSymbol	*gBitDepthKey;
    static const OSSymbol	*gBitWidthKey;
    static const OSSymbol	*gAlignmentKey;
    static const OSSymbol	*gByteOrderKey;
    static const OSSymbol	*gIsMixableKey;
    static const OSSymbol	*gDriverTagKey;
    static const OSSymbol	*gMinimumSampleRateKey;
    static const OSSymbol	*gMaximumSampleRateKey;

    static void initKeys();

    static OSDictionary *createDictionaryFromFormat(const IOAudioStreamFormat *streamFormat, const IOAudioStreamFormatExtension *formatExtension, OSDictionary *formatDict = 0);
    static IOAudioStreamFormat *createFormatFromDictionary(const OSDictionary *formatDict, IOAudioStreamFormat *streamFormat = 0, IOAudioStreamFormatExtension *formatExtension = 0);

    IOAudioEngine 				*audioEngine;
    IOWorkLoop					*workLoop;
    IOCommandGate				*commandGate;
    IORecursiveLock				*streamIOLock;
    
    UInt32						numClients;

    IOAudioStreamDirection		direction;

    IOAudioStreamFormat			format;
    IOAudioStreamFormatDesc		*availableFormats;
    OSArray						*availableFormatDictionaries;
    UInt32						numAvailableFormats;
    
    UInt32						startingChannelID;
    UInt32						maxNumChannels;
    
    void						*sampleBuffer;
    UInt32						sampleBufferSize;

    void						*mixBuffer;
    UInt32						mixBufferSize;
    bool						streamAllocatedMixBuffer;
    
    AudioIOFunction				*audioIOFunctions;
    UInt32						numIOFunctions;
    
    bool						streamAvailable;
    
    OSSet						*defaultAudioControls;
    
    IOAudioEnginePosition		startingPosition;
    IOAudioEnginePosition		clippedPosition;
    
    IOAudioClientBuffer			*clientBufferListStart;
    IOAudioClientBuffer			*clientBufferListEnd;
    
    IOAudioClientBuffer			*userClientList;
	
protected:

    struct ExpansionData {
		IOAudioStreamFormatExtension	streamFormatExtension;
		UInt32							mSampleFramesReadByEngine;
		IOReturn						mClipOutputStatus;
	};
    
    ExpansionData *reserved;

public:
// New code added here:
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 0);
    virtual const IOAudioStreamFormatExtension *getFormatExtension();
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 1);
    virtual IOReturn setFormat(const IOAudioStreamFormat *streamFormat, const IOAudioStreamFormatExtension *formatExtension, bool callDriver = true);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 2);
    virtual IOReturn setFormat(const IOAudioStreamFormat *streamFormat, const IOAudioStreamFormatExtension *formatExtension, OSDictionary *formatDict, bool callDriver = true);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 3);
    virtual void addAvailableFormat(const IOAudioStreamFormat *streamFormat, const IOAudioStreamFormatExtension *formatExtension, const IOAudioSampleRate *minRate, const IOAudioSampleRate *maxRate, const AudioIOFunction *ioFunctionList = NULL, UInt32 numFunctions = 0);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 4);
    virtual void addAvailableFormat(const IOAudioStreamFormat *streamFormat, const IOAudioStreamFormatExtension *formatExtension, const IOAudioSampleRate *minRate, const IOAudioSampleRate *maxRate, AudioIOFunction ioFunction);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 5);
    virtual bool validateFormat(IOAudioStreamFormat *streamFormat, IOAudioStreamFormatExtension *formatExtension, IOAudioStreamFormatDesc *formatDesc);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 6);
	virtual void setTerminalType(const UInt32 terminalType);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 7);
	virtual IOReturn mixOutputSamples(const void *sourceBuf, void *mixBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 8);
	virtual void setSampleLatency(UInt32 numSamples);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 9);
	virtual bool validateFormat(IOAudioStreamFormat *streamFormat, IOAudioStreamFormatExtension *formatExtension, IOAudioStreamFormatDesc *formatDesc, const IOAudioSampleRate *sampleRate);
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 10);
	virtual UInt32 getNumSampleFramesRead();
	// OSMetaClassDeclareReservedUsed(IOAudioStream, 11);
	virtual void setDefaultNumSampleFramesRead(UInt32);

private:
    OSMetaClassDeclareReservedUsed(IOAudioStream, 0);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 1);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 2);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 3);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 4);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 5);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 6);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 7);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 8);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 9);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 10);
    OSMetaClassDeclareReservedUsed(IOAudioStream, 11);

    OSMetaClassDeclareReservedUnused(IOAudioStream, 12);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 13);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 14);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 15);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 16);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 17);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 18);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 19);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 20);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 21);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 22);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 23);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 24);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 25);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 26);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 27);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 28);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 29);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 30);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 31);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 32);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 33);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 34);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 35);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 36);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 37);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 38);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 39);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 40);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 41);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 42);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 43);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 44);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 45);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 46);
    OSMetaClassDeclareReservedUnused(IOAudioStream, 47);

public:
    virtual bool initWithAudioEngine(IOAudioEngine *engine, IOAudioStreamDirection dir, UInt32 startChannelID, const char *streamDescription = NULL, OSDictionary *properties = 0);
    virtual void free();
    
    virtual void stop(IOService *provider);
    
    virtual IOWorkLoop *getWorkLoop() const;

    virtual IOReturn setProperties(OSObject *properties);

    virtual IOAudioStreamDirection getDirection();

    virtual void setSampleBuffer(void *buffer, UInt32 size);
    virtual void *getSampleBuffer();
    virtual UInt32 getSampleBufferSize();
    
    virtual void setMixBuffer(void *buffer, UInt32 size);
    virtual void *getMixBuffer();
    virtual UInt32 getMixBufferSize();
    
    virtual void numSampleFramesPerBufferChanged();

    virtual void clearSampleBuffer();
    
    virtual void setIOFunction(AudioIOFunction ioFunction);
    virtual void setIOFunctionList(const AudioIOFunction *ioFunctionList, UInt32 numFunctions);

    virtual const IOAudioStreamFormat *getFormat();
    static IOReturn setFormatAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    virtual IOReturn setFormat(const IOAudioStreamFormat *streamFormat, bool callDriver = true);
    virtual IOReturn setFormat(OSDictionary *formatDict);
    virtual IOReturn setFormat(const IOAudioStreamFormat *streamFormat, OSDictionary *formatDict, bool callDriver = true);
    virtual IOReturn hardwareFormatChanged(const IOAudioStreamFormat *streamFormat);
    virtual void addAvailableFormat(const IOAudioStreamFormat *streamFormat, const IOAudioSampleRate *minRate, const IOAudioSampleRate *maxRate, const AudioIOFunction *ioFunctionList = NULL, UInt32 numFunctions = 0);
    virtual void addAvailableFormat(const IOAudioStreamFormat *streamFormat, const IOAudioSampleRate *minRate, const IOAudioSampleRate *maxRate, AudioIOFunction ioFunction);
    virtual void clearAvailableFormats();
    virtual bool validateFormat(IOAudioStreamFormat *streamFormat, IOAudioStreamFormatDesc *formatDesc);
    
    virtual UInt32 getStartingChannelID();
    virtual UInt32 getMaxNumChannels();
    
    virtual void setStreamAvailable(bool available);
    virtual bool getStreamAvailable();
    
    virtual IOReturn addDefaultAudioControl(IOAudioControl *defaultAudioControl);
    virtual void removeDefaultAudioControls();

protected:
    virtual void lockStreamForIO();
    virtual void unlockStreamForIO();
    
    virtual void updateNumClients();
    virtual IOReturn addClient(IOAudioClientBuffer *clientBuffer);
    virtual void removeClient(IOAudioClientBuffer *clientBuffer);
    virtual UInt32 getNumClients();
    
    virtual IOReturn processOutputSamples(IOAudioClientBuffer *clientBuffer, UInt32 firstSampleFrame, UInt32 loopCount, bool samplesAvailable);
    virtual IOReturn readInputSamples(IOAudioClientBuffer *clientBuffer, UInt32 firstSampleFrame);
    
    virtual void resetClipInfo();
    virtual void clipIfNecessary();
    virtual void clipOutputSamples(UInt32 startingSampleFrame, UInt32 numSampleFrames);
    
    virtual void setStartingChannelNumber(UInt32 channelNumber);

private:
    virtual void setDirection(IOAudioStreamDirection dir);

};

#endif /* _IOKIT_IOAUDIOSTREAM_H */
