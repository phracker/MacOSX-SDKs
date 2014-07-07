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

/*!
 * @header IOAudioDevice
 */

#ifndef _IOKIT_IOAUDIOENGINE_H
#define _IOKIT_IOAUDIOENGINE_H

#include <IOKit/IOService.h>

#include <IOKit/audio/IOAudioTypes.h>

class OSDictionary;
class OSCollection;
class OSOrderedSet;
class IOAudioEngineUserClient;
class IOAudioDevice;
class IOAudioStream;
class IOAudioControl;
class IOCommandGate;

#define IOAUDIOENGINE_DEFAULT_NUM_ERASES_PER_BUFFER	4

/*!
 * @typedef IOAudioEnginePosition
 * @abstract Represents a position in an audio audio engine based on the sample frame within a 
 *  loop around the sample buffer, and the loop count which starts at 0 when the audio engine
 *  begins playback
 * @field fSampleFrame The sample frame within the buffer - starts at 0
 * @field fLoopCount The number of times the ring buffer has looped
 */
typedef struct {
    UInt32	fSampleFrame;
    UInt32	fLoopCount;
} IOAudioEnginePosition;

#define CMP_IOAUDIOENGINEPOSITION(p1, p2) \
    (((p1)->fLoopCount > (p2)->fLoopCount) ? 1 :	\
        ((p1)->fLoopCount == (p2)->fLoopCount) && ((p1)->fSampleFrame > (p2)->fSampleFrame) ? 1 :	\
            ((p1)->fLoopCount == (p2)->fLoopCount) && ((p1)->fSampleFrame == (p2)->fSampleFrame) ? 0 : -1)
            
#define IOAUDIOENGINEPOSITION_IS_ZERO(p1) (((p1)->fLoopCount == 0) && ((p1)->fSampleFrame == 0))

/*!
 * @class IOAudioEngine
 * @abstract Abstract base class for a single audio audio / I/O engine.
 * @discussion An IOAudioEngine is defined by a single I/O engine to transfer data to
 *  or from one ore more sample buffers.  Each sample buffer is represented by a single IOAudioStream
 *  instance.  A single IOAudioEngine must contain at least one IOAudioStream, but has no upper
 *  limit on the number of IOAudioStreams it may contain.  An IOAudioEngine instance may contain
 *  both input and output IOAudioStreams.
 *
 *  An audio driver must subclass IOAudioEngine in order to provide certain services.  An 
 *  IOAudioEngine subclass must start and stop the I/O engine when requested.  The I/O
 *  engine should be continuously running and loop around from end to beginning.  While the audio
 *  engine is running, it must take a timestamp as the sample buffer(s) wrap around and start at
 *  the beginning.  The CoreAudio.framework uses the timestamp to calculate the exact position of
 *  the audio engine.  An IOAudioEngine subclass must implement getCurrentSampleFrame() to provide
 *  a sample position on demand.  Finally, an IOAudioEngine subclass must provide clipping and
 *  format conversion routines to go to/from the CoreAudio.framework's native float format.
 *
 *  If multiple stream formats or sample rates are allowed, the IOAudioEngine
 *  subclass must provide support for changing the hardware when a format or sample rate is
 *  changed.
 *
 *  There are several attributes associated with a single IOAudioEngine: .
 *
 *  The IOAudioEngine superclass provides a shared status buffer that contains all of the dynamic pieces
 *  of information about the audio engine (type IOAudioEngineStatus).  It runs an erase process on
 *  all of the output streams.  The erase head is used to zero out the mix and sample buffers after
 *  the samples have been played.  Additionally, the IOAudioEngine superclass handles the 
 *  communication with the CoreAudio.framework and makes the decision to start and stop the
 *  audio engine when it detects it is in use.
 *
 *  In order for an audio device to play back or record sound, an IOAudioEngine subclass must be created.
 *  The subclass must initialize all of the necessary hardware resources to prepare for starting the
 *  audio I/O engine.  It typically will perform these tasks in the initHardware() method.  A subclass 
 *  may also implement a stop() method which is called as the driver is being torn down.  This is 
 *  typically called in preparation of removing the device from the system for removable devices.
 *
 *  In addition to initializing the necessary hardware, there are a number of other tasks an 
 *  IOAudioEngine must do during initHardware().  It must create the necessary IOAudioStream objects
 *  to match the device capabilities.  Each IOAudioStream must be added using addAudioStream().  It
 *  also should create the IOAudioControls needed to control the various attributes of the audio engine:
 *  output volume, mute, input gain, input selection, analog passthru.  To do that, addDefaultAudioControl()
 *  should be called with each IOAudioControl to be attached to the IOAudioEngine.  In order to provide
 *  for proper synchronization, the latency of the audio engine should be specified with setSampleLatency().
 *  This value represents the latency between the timestamp taken at the beginning of the buffer and 
 *  when the audio is actually played (or recorded) by the device.  If a device is block based or if
 *  there is a need to keep the CoreAudio.framework a certain number of samples ahead of (or behind for
 *  input) the I/O head, that value should be specified using setSampleOffset().  If this is not specified
 *  the CoreAudio.framework may attempt to get as close to the I/O head as possible.
 *
 *  The following fields in the shared IOAudioEngineStatus struct must be maintained by the subclass
 *  implementation:
 *  <pre>
 *  <t>  fCurrentLoopCount - the number of times the sample buffer has wrapped around to the beginning
 *  <t>  fLastLoopTime - timestamp of the most recent time that the I/O engine looped back to the 
 *  beginning of the sample buffer
 *  </pre>
 *  It is critically important that the fLastLoopTime field be as accurate as possible.  It is 
 *  the basis for the entire timer and synchronization mechanism used by the audio system.
 *
 *  At init time, the IOAudioEngine subclass must call setNumSampleFramesPerBuffer() to indicate how large
 *  each of the sample buffers are (measured in sample frames).  Within a single IOAudioEngine, all sample
 *  buffers must be the same size and be running at the same sample rate.  If different buffers/streams can
 *  be run at different rates, separate IOAudioEngines should be used.  The IOAudioEngine subclass must
 *  also call setSampleRate() at init time to indicate the starting sample rate of the device.
 *
 */

class IOAudioEngine : public IOService
{
    OSDeclareAbstractStructors(IOAudioEngine)
    
    friend class IOAudioEngineUserClient;
    friend class IOAudioDevice;
    friend class IOAudioStream;
    
public:
    /*! @var gSampleRateWholeNumberKey */
    static const OSSymbol	*gSampleRateWholeNumberKey;
    /*! @var gSampleRateFractionKey */
    static const OSSymbol	*gSampleRateFractionKey;
    
    /*! @var numSampleFramesPerBuffer */
    UInt32			numSampleFramesPerBuffer;
    
    /*! @var sampleRate The current sample rate of the audio engine in samples per second */
    IOAudioSampleRate			sampleRate;

    /*! @var numErasesPerBuffer The number of times the erase head get scheduled to run for each 
     *   cycle of the audio engine */
    UInt32			numErasesPerBuffer;
    /*! @var runEraseHead Set to true if the erase head is to run when the audio engine is running.  This is the
    *    case if there are any output streams. */
    bool			runEraseHead;
    
    /*! @var audioEngineStopPosition When all clients have disconnected, this is set to one buffer length past the
    *    current audio engine position at the time.  Then when the stop position is reached, the audio engine
    *    is stopped */
    IOAudioEnginePosition	audioEngineStopPosition;

    /*! @var isRegistered Internal state variable to keep track or whether registerService() has been called. */
    bool			isRegistered;
    /*! @var configurationChangeInProgress Set to true after beginConfigurationChange() and false upon a 
    *    subsequent call to completeConfigurationChange() or cancelConfigurationChange(). */
    bool			configurationChangeInProgress;
    
    /*! @var state The current state of the IOAudioEngine - running, stopped, paused */
    IOAudioEngineState		state;

    /*! @var status Status struct shared with the CoreAudio.framework */
    IOAudioEngineStatus *	status;

    /*! @var audioDevice The IOAudioDevice instance to which the IOAudioEngine belongs */
    IOAudioDevice *		audioDevice;
    
    /*! @var workLoop The IOWorkLoop for the audio driver - shared with the IOAudioDevice */
    IOWorkLoop 			*workLoop;
    /*! @var commandGate The IOCommandGate for this audio engine - attached to the driver's IOWorkLoop */
    IOCommandGate		*commandGate;

    /*! @var inputStreams An OSSet of all of the input IOAudioStreams attached to this IOAudioEngine */
    OSOrderedSet 	*inputStreams;
    UInt32			maxNumInputChannels;
    /*! @var outputStreams An OSSet of all of the output IOAudioStreams attached to this IOAudioEngine */
    OSOrderedSet	*outputStreams;
    UInt32			maxNumOutputChannels;
    /*! @var userClients An OSSet of all of the currently connected user clients */
    OSSet			*userClients;
    /*! @var defaultAudioControls All of the IOAudioControls that affect this audio engine */
    OSSet			*defaultAudioControls;
    
    /*! @var numActiveUserClients A total of the active user clients - those that are currently playing or 
    *    recording audio */
    UInt32			numActiveUserClients;
    UInt32			sampleOffset;
    
    UInt32			index;
    bool			duringStartup;

protected:

    /*!
     * @var deviceStartedAudioEngine Used by the IOAudioDevice to determine responsibility for shutting
     *  the audio engine down when it is no longer needed.
     */
    bool			deviceStartedAudioEngine;
    
protected:
    struct ExpansionData { };
    
    ExpansionData *reserved;

public:
// This takes the 0th reserved slot:
    virtual IOReturn performFormatChange(IOAudioStream *audioStream, const IOAudioStreamFormat *newFormat, const IOAudioStreamFormatExtension *formatExtension, const IOAudioSampleRate *newSampleRate);

private:
    OSMetaClassDeclareReservedUsed(IOAudioEngine, 0);

    OSMetaClassDeclareReservedUnused(IOAudioEngine, 1);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 2);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 3);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 4);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 5);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 6);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 7);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 8);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 9);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 10);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 11);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 12);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 13);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 14);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 15);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 16);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 17);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 18);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 19);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 20);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 21);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 22);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 23);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 24);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 25);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 26);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 27);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 28);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 29);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 30);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 31);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 32);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 33);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 34);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 35);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 36);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 37);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 38);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 39);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 40);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 41);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 42);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 43);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 44);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 45);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 46);
    OSMetaClassDeclareReservedUnused(IOAudioEngine, 47);

public:
    /*!
     * @function createDictionaryFromSampleRate
     * @abstract Internal routine used to generate a dictionary matching the given sample rate.
     * @discussion Used to generate a sample rate dictionary for the IORegistry - used by the 
     *  CoreAudio.framework.
     * @result Returns the newly create OSDictionary
     */
    static OSDictionary *createDictionaryFromSampleRate(const IOAudioSampleRate *sampleRate, OSDictionary *rateDict = 0);
    
    /*!
     * @function createSampleRateFromDictionary
     * @abstract Internal routine used to generate a sample rate from an OSDictionary.
     * @discussion Used to generate a sample rate give a new OSDictionary from the IORegistry - coming
     *  from the CoreAudio.framework.
     * @result Returns the sample rate
     */
    static IOAudioSampleRate *createSampleRateFromDictionary(const OSDictionary *rateDict, IOAudioSampleRate *sampleRate = 0);

    /*!
     * @function init
     * @abstract Performs initialization of a newly allocated IOAudioEngine.
     * @discussion This function is responsible for initialization of all of the general attributes of
     *  a new IOAudioEngine.  It initializes instance variables to their default
     *  values and allocates the shared status buffer.  Subclasses will likely want to override this method
     *  and do all of their common initialization in their implementation.  They do need to be sure to call
     *  IOAudioEngine's implementation of init and pay attention to the return value.
     * @param properties The default properties for the IOAudioEngine
     * @result Returns true if initialization was successful
     */
    virtual bool init(OSDictionary *properties);

    /*!
     * @function free
     * @abstract Frees all of the resources allocated by the IOAudioEngine.
     * @discussion Do not call this directly.  This is called automatically by the system when the instance's
     *  refcount goes to 0.  To decrement the refcount, call release() on the object.
     */
    virtual void free();

    /*!
     * @function getWorkLoop
     * @abstract Returns the IOWorkLoop for the driver
     */
    virtual IOWorkLoop *getWorkLoop() const;
    
    /*!
     * @function getCommandGate
     * @abstract Returns the IOCommandGate for this IOAudioEngine
     */
    virtual IOCommandGate *getCommandGate() const;
    
    /*!
     * @function start
     * @abstract A simple cover function for start(IOService *, IOAudioDevice *) that assumes the provider
     *  is the IOAudioDevice.
     * @discussion Subclasses will want to override start(IOService *, IOAudioDevice *) rather than this
     *  one.
     * @param provider The service provider for the IOAudioEngine (the IOAudioDevice in this case)
     * @result Returns true if the IOAudioEngine was successfully started.
     */
    virtual bool start(IOService *provider);

    /*!
     * @function start
     * @abstract Standard IOKit start() routine called to start an IOService
     * @discussion This function is called in order to prepare the IOAudioEngine for use.  It does NOT
     *  mean that the audio I/O engine itself should be started.  This implementation gets the IOWorkLoop
     *  from the IOAudioDevice and allocates an IOCommandGate.  Finally it calls initHardware() in which
     *  all of the subclass-specific device initialization should be done.  Upon return from initHardware()
     *  all IOAudioStreams should be created and added to the audio engine.  Also, all IOAudioControls
     *  for this IOAudioEngine should be created and attached.
     * @param provider The service provider for the IOAudioEngine
     * @param device The IOAudioDevice to which this IOAudioEngine belongs
     * @result Returns true if the service was successfully started
     */
    virtual bool start(IOService *provider, IOAudioDevice *device);
    
    /*!
     * @function initHardware
     * @abstract This function is called by start() to provide a convenient place for the subclass to
     *  perform its hardware initialization.
     * @discussion Upon return from this function, all IOAudioStreams and IOAudioControls should be created
     *  and the audio engine should be ready to be started when a client requests that playback begin.
     * @function provider The service provider numb for this audio engine - typically the IOAudioDevice.
     * @result Returns true if the hardware was successfully initialized
     */
    virtual bool initHardware(IOService *provider);

    /*!
     * @function stop
     * @abstract Called to stop the service and prepare for the driver to be terminated.
     * @discussion This function is called before the driver is terminated and usually means that the device
     *  has been removed from the system.
     * @param provider The service provider for the IOAudioEngine
     */
    virtual void stop(IOService *provider);

    /*!
     * @function registerService
     * @abstract Called when this audio engine is ready to begin vending services
     * @discussion This function is called by IOAudioDevice::activateAudioEngine() once the audio engine
     *  has been fully initialized and is ready to begin audio playback.
     * @var options
     */
    virtual void registerService(IOOptionBits options = 0);
    
    virtual void setAudioDevice(IOAudioDevice *device);
    virtual void setIndex(UInt32 index);
    
    virtual void setDescription(const char *description);

    /*!
     * @function newUserClient
     * @abstract Called to request a new user client object for this service
     * @discussion This function is called automatically by IOKit when a user process attempts
     *  to connect to this service.  It allocates a new IOAudioEngineUserClient object and increments
     *  the number of connections for this audio engine.  If this is the first user client for this IOAudioEngine,
     *  it calls startAudioEngine().  There is no need to call this function directly.
     * @param task The task requesting the new user client
     * @param securityID Optional security paramater passed in by the client - ignored
     * @param type Optional user client type passed in by the client - ignored
     * @param handler The new IOUserClient * must be stored in this param on a successful completion
     * @result Returns kIOReturnSuccess on success.  May also result kIOReturnError or kIOReturnNoMemory.
     */
    virtual IOReturn newUserClient(task_t task, void *securityID, UInt32 type, IOUserClient **handler);

    /*!
     * @function addAudioStream
     * @abstract Called by the driver to add an IOAudioStream to the audio engine
     * @discussion This must be called at least once to make sure the audio engine has at least one IOAudioStream.
     * @param stream The IOAudioStream to be added
     * @result Returns kIOReturnSuccess if the stream was successfully added
     */
    virtual IOReturn addAudioStream(IOAudioStream *stream);
    
    virtual IOAudioStream *getAudioStream(IOAudioStreamDirection direction, UInt32 channelID);
    
    virtual void lockAllStreams();
    virtual void unlockAllStreams();
    
    virtual void updateChannelNumbers();

    /*!
     * @function resetStatusBuffer
     * @abstract Resets the status buffer to its default values
     * @discussion This is called during startAudioEngine() and resumeAudioEngine() to clear out the status buffer
     *  in preparation of starting up the I/O engine.  There is no need to call this directly.
     */
    virtual void resetStatusBuffer();
    
    /*!
     * @function clearAllSampleBuffers
     * @abstract Zeros out all of the sample and mix buffers associated with the IOAudioEngine
     * @discussion This is called during resumeAudioEngine() since the audio engine gets started back at the
     *  beginning of the sample buffer.
     */
    virtual void clearAllSampleBuffers();
    
    /*!
     * @function getCurrentSampleFrame
     * @abstract Called to get the current sample frame from the IOAudioEngine subclass
     * @discussion
     * @result
     */
    virtual UInt32 getCurrentSampleFrame() = 0;

    /*!
     * @function startAudioEngine
     * @abstract Called to start the audio I/O engine
     * @discussion This method is called automatically when the audio engine is placed into use the first time.
     *  This must be overridden by the subclass.  No call to the superclass' implementation is
     *  necessary.  The subclass' implementation must start up the audio I/O engine.  This includes any audio
     *  engine that needs to be started as well as any interrupts that need to be enabled.  Upon successfully
     *  starting the engine, the subclass' implementation must call _setState(kAudioEngineRunning).  If
     *  it has also checked the state using getState() earlier in the implementation, the stateLock must be
     *  acquired for the entire initialization process (using IORecursiveLockLock(stateLock) and
     *  IORecursiveLockUnlock(stateLock)) to ensure that the state remains consistent.  See the general class
     *  comments for an example.
     * @result Must return kIOReturnSuccess on a successful start of the engine.
     */
    virtual IOReturn startAudioEngine();

    /*!
     * @function stopAudioEngine
     * @abstract Called to stop the audio I/O engine
     * @discussion This method is called automatically when the last client disconnects from this audio engine.
     *  It must be overridden by the subclass.  No call to the superclass' implementation is necessary.
     *  The subclass' implementation must stop the audio I/O engine.  The audio engine (if it exists) should
     *  be stopped and any interrupts disabled.  Upon successfully stopping the engine, the subclass must call
     *  _setState(kAudioEngineStopped).  If it has also checked the state using getState() earlier in the
     *  implementation, the stateLock must be acquired for the entire initialization process (using
     *  IORecursiveLockLock(stateLock) and IORecursiveLockUnlock(stateLock)) to ensure that the state remains
     *  consistent.
     * @result Must return kIOReturnSuccess on a successful stop of the engine.
     */
    virtual IOReturn stopAudioEngine();
    virtual IOReturn pauseAudioEngine();
    virtual IOReturn resumeAudioEngine();
    
    virtual IOReturn performAudioEngineStart();
    virtual IOReturn performAudioEngineStop();

    /*! 
     * @function getState
     * @abstract Returns the current state of the IOAudioEngine
     * @discussion If this method is called in preparation for calling _setState(), the stateLock must
     *  be acquired before the first call to getState() and held until after the last call to _setState().
     *  Be careful not to return from the code acquiring the lock while the lock is being held.  That
     *  will cause a deadlock situation.
     * @result The current state of the IOAudioEngine: kAudioEngineRunning, kAudioEngineStopped
     */
    virtual IOAudioEngineState getState();

    /*!
     * @function getSampleRate Returns the sample rate of the IOAudioEngine in samples per second
     */
    virtual const IOAudioSampleRate *getSampleRate();
    
    virtual IOReturn hardwareSampleRateChanged(const IOAudioSampleRate *sampleRate);

    /*!
     * @function getErases Returns true if the audio engine will run the erase head when the audio engine is running.
     */
    virtual bool getRunEraseHead();

    /*!
     * @function getStatus Returns a pointer to the shared status buffer
     */
    virtual const IOAudioEngineStatus *getStatus();

    /*!
     * @function timerCallback
     * @abstract A static method used as a callback for the IOAudioDevice timer services
     * @discussion This method implements the IOAudioDevice::TimerEvent type.
     * @param arg1 The IOAudioEngine that is the target of the event
     * @param device The IOAudioDevice that sent the timer event
     */
    static void timerCallback(OSObject *arg1, IOAudioDevice *device);

    /*!
     * @function timerFired
     * @abstract Called by timerCallback to indicate the timer has fired
     * @discussion This method calls performErase() and performFlush() to do erase head processing and
     *  audio engine flushing each time the timer event fires.
     */
    virtual void timerFired();

    /*!
     * @function getTimerInterval
     * @abstract Called to get the timer interval for use by the timer event
     * @discussion This method is called each timer the timer event is enabled through addTimer().  The default
     *  implementation is set to return a value such that the timer event runs n times each cycle of the audio
     *  engine through the sample buffer.  The value n is stored as the instance variable: numErasesPerBuffer.
     *  The default value of numErasesPerBuffer is set to IOAUDIOENGINE_DEFAULT_NUM_ERASES_PER_BUFFER which is 4.
     *  A subclass may change the value of numErasesPerBuffer or override getTimerInterval.  If it is overridden,
     *  the subclass should call the superclass' implementation, compare its interval with the superclass' and
     *  return the smaller of the two.
     * @result Returns the interval for the timer event
     */
    virtual AbsoluteTime getTimerInterval();

    /*!
     * @function performErase
     * @abstract Called to perform erase head processing
     * @discussion This method is called automatically each time the timer event fires and erases the sample
     *  buffer and mix buffer from the previous location up to the current location of the audio engine.
     */
    virtual void performErase();

    /*!
     * @function performFlush
     * @abstract Called to perform the flush operation
     * @discussion This method is called automatically each time the timer event fires.  It stops the audio engine
     *  if there are no more clients and the audio engine is passed the latest flush ending position.
     */
    virtual void performFlush();
    
    virtual void stopEngineAtPosition(IOAudioEnginePosition *endingPosition);

    virtual IOReturn mixOutputSamples(const void *sourceBuf, void *mixBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
    virtual IOReturn clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
    virtual void resetClipPosition(IOAudioStream *audioStream, UInt32 clipSampleFrame);
    virtual IOReturn convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
    
    virtual void takeTimeStamp(bool incrementLoopCount = true, AbsoluteTime *timestamp = NULL);
    virtual IOReturn getLoopCountAndTimeStamp(UInt32 *loopCount, AbsoluteTime *timestamp);

    virtual IOReturn calculateSampleTimeout(AbsoluteTime *sampleInterval, UInt32 numSampleFrames, IOAudioEnginePosition *startingPosition, AbsoluteTime *wakeupTime);
    
    virtual IOReturn performFormatChange(IOAudioStream *audioStream, const IOAudioStreamFormat *newFormat, const IOAudioSampleRate *newSampleRate);
    
    virtual void beginConfigurationChange();
    virtual void completeConfigurationChange();
    virtual void cancelConfigurationChange();

    virtual IOReturn addDefaultAudioControl(IOAudioControl *defaultAudioControl);
    virtual IOReturn removeDefaultAudioControl(IOAudioControl *defaultAudioControl);
    virtual void removeAllDefaultAudioControls();
    
    virtual OSString *getGlobalUniqueID();
    virtual OSString *getLocalUniqueID();

protected:

    /*!
     * @function initKeys
     * @abstract Internal initialization routine which generates the OSSymbols with the keys.
     * @discussion Do not call this directly.
     */ 
    static void initKeys();
    
    virtual void setNumSampleFramesPerBuffer(UInt32 numSampleFrames);
    virtual UInt32 getNumSampleFramesPerBuffer();

    /*!
     * @function _setState
     * @abstract Used to indicate that the audio engine is in the specified state
     * @discussion This method simply sets the internal state of the audio engine to the specified state.  It does not
     *  affect a change to the state.  It does however keep other internal state-related attributes consistent.
     *  For example, it enables or disables the timer as needed when the state changes to running or stopped.
     * @param newState The state the audio engine is in
     * @result Returns the old state
     */
    virtual IOAudioEngineState setState(IOAudioEngineState newState);

    /*!
     * @function setSampleRate
     * @abstract Records the sample rate of the audio engine
     * @discussion  This method must be called during initialization of a new audio engine to record the audio engine's
     *  initial sample rate.  It also is intended to be used to record changes to the sample rate during use.
     *  Currently changing sample rates after the audio engine has been started is not supported.
     *  It may require that the sample buffers be re-sized.  This will be available in an upcoming release.
     * @param newSampleRate The sample rate of the audio engine in samples per second
     */
    virtual void setSampleRate(const IOAudioSampleRate *newSampleRate);

    /*!
     * @function _setSampleLatency
     * @abstract Sets the sample latency for the audio engine
     * @discussion The sample latency represents the number of samples ahead of the playback head
     *  that it is safe to write into the sample buffer.  The audio device API will never write
     *  closer to the playback head than the number of samples specified.  For input audio engines
     *  the number of samples is behind the record head.
     */
    virtual void setSampleLatency(UInt32 numSamples);
    virtual void setOutputSampleLatency(UInt32 numSamples);
    virtual void setInputSampleLatency(UInt32 numSamples);
    virtual void setSampleOffset(UInt32 numSamples);

    /*!
     * @function _setErases
     * @abstract Tells the audio engine whether or not to run the erase head
     * @discussion By default, output audio engines run the erase head and input audio engines do not.  This method can
     *  be called after _setDirection() is called in order to change the default behavior.
     * @param runEraseHead The audio engine will run the erase head if this value is true
     */
    virtual void setRunEraseHead(bool runEraseHead);

    /*!
     * @function clientClosed
     * @abstract Called automatically when a user client closes its connection to the audio engine
     * @discussion This method decrements the number of connections to the audio engine and if they reach
     *  zero, the audio engine is called with a call to stopAudioEngine().  This method should not be called directly.
     * @param client The user client that has disconnected.
     */
    virtual void clientClosed(IOAudioEngineUserClient *client);

    /*!
     * @function addTimer
     * @abstract Enables the timer event for the audio engine
     * @discussion There is a timer event needed by the IOAudioEngine for processing the erase head
     *  and performing flushing operations. When the timer fires, the method timerFired() is ultimately
     *  called which in turn calls performErase() and performFlush().  This is called automatically
     *  to enable the timer event for this audio engine.  It is called by _setState() when the audio engine state
     *  is set to kAudioEngineRunning.  When the timer is no longer needed, removeTimer() is called.
     *  There is no need to call this directly.  
     */
    virtual void addTimer();

    /*!
     * @function removeTimer
     * @abstract Disables the timer event for the audio engine
     * @discussion  This method is called automatically to disable the timer event for this audio engine.
     *  There is need to call it directly.  This method is called by _setState() when the audio engine state
     *  is changed from kAudioEngineRunning to one of the stopped states.
     */
    virtual void removeTimer();

    virtual void sendFormatChangeNotification(IOAudioStream *audioStream);
    virtual void sendNotification(UInt32 notificationType);
    
    virtual IOReturn createUserClient(task_t task, void *securityID, UInt32 type, IOAudioEngineUserClient **newUserClient);

    static IOReturn addUserClientAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    static IOReturn removeUserClientAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    static IOReturn detachUserClientsAction(OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4);
    
    virtual IOReturn addUserClient(IOAudioEngineUserClient *newUserClient);
    virtual IOReturn removeUserClient(IOAudioEngineUserClient *userClient);
    virtual IOReturn detachUserClients();
    
    virtual IOReturn startClient(IOAudioEngineUserClient *userClient);
    virtual IOReturn stopClient(IOAudioEngineUserClient *userClient);
    
    virtual IOReturn incrementActiveUserClients();
    virtual IOReturn decrementActiveUserClients();
    
    virtual void detachAudioStreams();
	void setWorkLoopOnAllAudioControls(IOWorkLoop *wl);
};

#endif /* _IOKIT_IOAUDIOENGINE_H */
