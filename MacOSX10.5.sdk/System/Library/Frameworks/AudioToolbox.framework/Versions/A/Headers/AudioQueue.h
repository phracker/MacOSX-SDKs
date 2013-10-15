/*
    File:       AudioQueue.h

    Contains:   AudioQueue Interfaces for the AudioToolbox

    Version:    Mac OS X

    Copyright:  © 2006-2007 by Apple Inc., all rights reserved.

    Bugs?:      For bug reports, consult the following page on
                the World Wide Web:

                    http://developer.apple.com/bugreporter/
*/

#ifndef __AudioQueue_h__
#define __AudioQueue_h__

/*!
    @header AudioQueue.h
    @abstract   Audio Queue Services
    @discussion
    
    This document describes Audio Queue Services, a 64-bit C programming interface in Core
    Audio's Audio Toolbox framework.

    Audio queues are software objects you use for recording or playing audio in Mac OS X. Audio
    queues perform the following tasks in your application:
    
    <ul>
    <li>Connect to audio hardware</li>
    <li>Manage audio data buffers</li>
    <li>Employ codecs, as necessary, for compressed audio formats</li>
    <li>Mediate playback or recording</li>
    </ul>
    
    Beginning with Mac OS X v10.5, "Leopard," Apple recommends that you use the Audio Queue Services
    technology for adding basic recording or playback to your Mac OS X application. It provides a
    straightforward, low overhead way for your application to record and play audio in Mac OS X
    without knowing the details of the hardware interface.
    
    Audio Queue Services enables you to record and play audio in linear PCM, in compressed formats
    (such as Apple Lossless, AAc, and MP3), and in other formats for which users have installed
    codecs.
    
    Audio Queue Services also provides high-level support for the use of hardware recording and
    playback devices in your application. Furthermore, it lets you use sophisticated codecs without
    knowledge of how they work.
    
    Additional advanced features support scheduled playback and synchronization of multiple audio
    queues and synchronization of audio with video.
    
    Note: Audio Queue Services provides features similar to those previously offered by the Sound
    Manager, and adds additional features such as synchronization. The Sound Manager is deprecated
    in Mac OS X v10.5 and does not work with 64-bit applications. Audio Queue Services is
    recommended for all new development, and as a replacement for the Sound Manager in existing
    applications. Audio Queue Services is a pure C interface that you can use in Cocoa and Carbon
    applications as well as Mac OS X command-line tools. This document describes Audio Queue
    Services for Mac OS X v10.5.
*/

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #include <CoreAudio/CoreAudioTypes.h>
    #include <CoreFoundation/CoreFoundation.h>
#else
    #include <CoreAudioTypes.h>
    #include <CoreFoundation.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark -
#pragma mark Constants
//==================================================================================================
//  CONSTANTS
//==================================================================================================
/*!
    @enum Result Codes
    @abstract   The OSStatus result codes returned by Audio Queue functions.
    @discussion
    @constant   kAudioQueueErr_InvalidBuffer        The specified buffer does not belong to the
                                                    audio queue.
    @constant   kAudioQueueErr_BufferEmpty          The buffer is empty (that is, the
                                                    mAudioDataByteSize field = 0).
    @constant   kAudioQueueErr_DisposalPending      The function cannot act on the audio queue
                                                    because it is being asynchronously disposed of.
    @constant   kAudioQueueErr_InvalidProperty      The specified property ID is invalid.
    @constant   kAudioQueueErr_InvalidPropertySize  The size of the specified property is invalid.
    @constant   kAudioQueueErr_InvalidParameter     The specified parameter ID is invalid.
    @constant   kAudioQueueErr_CannotStart          The audio queue has encountered a problem and
                                                    cannot start.
    @constant   kAudioQueueErr_BufferInQueue        The buffer cannot be disposed of when it is
                                                    enqueued.
    @constant   kAudioQueueErr_InvalidRunState      The queue is running but the function can
                                                    only operate on the queue when it is stopped,
                                                    or vice versa.
    @constant   kAudioQueueErr_InvalidQueueType     The queue is an input queue but the function can
                                                    only operate on an output queue, or vice versa.
*/
enum {
    kAudioQueueErr_InvalidBuffer        = -66687,
    kAudioQueueErr_BufferEmpty          = -66686,
    kAudioQueueErr_DisposalPending      = -66685,
    kAudioQueueErr_InvalidProperty      = -66684,
    kAudioQueueErr_InvalidPropertySize  = -66683,
    kAudioQueueErr_InvalidParameter     = -66682,
    kAudioQueueErr_CannotStart          = -66681,
    kAudioQueueErr_InvalidDevice        = -66680,
    kAudioQueueErr_BufferInQueue        = -66679,
    kAudioQueueErr_InvalidRunState      = -66678,
    kAudioQueueErr_InvalidQueueType     = -66677
};


/*!
    @enum Audio Queue Property IDs
    @abstract   Constants that identify properties for audio queues.
    @discussion
    @constant   kAudioQueueProperty_IsRunning
        A read-only property whose value is a UInt32 that indicates whether or not the queue is
        running. A notification is sent when the audio device starts or stops, which is not
        necessarily when the start or stop function is called.
    @constant   kAudioQueueProperty_Device_SampleRate
        A read-only property whose value is a Float64 that indicates the sampling rate of the
        associated audio device.
    @constant   kAudioQueueProperty_Device_NumberChannels
        A read-only property whose value is a UInt32 that indicates the number of channels in
        the associated audio device.
    @constant   kAudioQueueProperty_CurrentDevice
        A read/write property whose value is a CFStringRef that contains the unique identifier
        (UID) of the associated audio device.
    @constant   kAudioQueueProperty_MagicCookie
        A read/write property whose value is an audio format magic cookie. If the audio format
        requires a magic cookie, you must set this property before enqueuing any buffers.
    @constant   kAudioQueueProperty_ChannelLayout
        A read/write property whose value is an audio channel layout structure that describes
        the audio queue's channel layout. The number of channels must match the format of the
        queue. If more than two channels (for instance, a five-channel surround sound) exist in
        the queue, there may be a need to specify a channel layout. This layout indicates the
        specific order in which the channels do appear, such as left, then center, then right.
    @constant   kAudioQueueProperty_EnableLevelMetering
        A read-write property whose value is a UInt32 that indicates whether metering of
        audio levels is enabled for the audio queue. (0=off, 1=on).
    @constant   kAudioQueueProperty_CurrentLevelMeter
        A read-only property whose value is an array of AudioQueueLevelMeter structures, one
        array element per audio channel. The values in the AudioQueueLevelMeters are in the
        range 0-1.
    @constant   kAudioQueueProperty_CurrentLevelMeterDB
        A read-only property whose value is an array of AudioQueueLevelMeter structures, one
        array element per audio channel. The values in the AudioQueueLevelMeters are in
        decibels.
*/
enum { // typedef UInt32 AudioQueuePropertyID
    kAudioQueueProperty_IsRunning               = 'aqrn',       // value is UInt32

    kAudioQueueDeviceProperty_SampleRate        = 'aqsr',       // value is Float64
    kAudioQueueDeviceProperty_NumberChannels    = 'aqdc',       // value is UInt32
    kAudioQueueProperty_CurrentDevice           = 'aqcd',       // value is CFStringRef
    
    kAudioQueueProperty_MagicCookie             = 'aqmc',       // value is void*
        
    kAudioQueueProperty_ChannelLayout           = 'aqcl',       // value is AudioChannelLayout
    kAudioQueueProperty_EnableLevelMetering     = 'aqme',       // value is UInt32
    kAudioQueueProperty_CurrentLevelMeter       = 'aqmv',       // value is array of AudioQueueLevelMeterState, 1 per channel
    kAudioQueueProperty_CurrentLevelMeterDB     = 'aqmd',       // value is array of AudioQueueLevelMeterState, 1 per channel
};


/*!
    @enum       AudioQueueParameterID
    @abstract   Constants that identify the parameters for audio queues.
    @discussion
        In Mac OS X v10.5, audio queues have one parameter available: kAudioQueueParam_Volume.
        You can set a parameter in one of two ways:
        
        <ul>
        <li>    Assign a parameter value to an audio queue to take effect immediately using
                AudioQueueSetParameter.</li>
        <li>    Schedule a parameter to take effect when a buffer is enqueued. You supply the
                parameter when you queue a buffer, and the new value of the parameter is applied
                when that buffer is rendered.
        </ul>
        
        AudioQueueGetParameter always returns the current value of the parameter

    @constant   kAudioQueueParam_Volume
        A value from 0.0 to 1.0 indicating the linearly scaled gain for the queue. A value of
        1.0 (the default) indicates unity gain. A value of 0.0 indicates zero gain, or silence.
*/
enum    // typedef UInt32 AudioQueueParameterID;
{
    kAudioQueueParam_Volume     = 1

};



#pragma mark -
#pragma mark Types
//==================================================================================================
//  TYPES
//==================================================================================================

/*!
    @typedef    AudioQueuePropertyID
    @abstract   A value that uniquely identifies an audio queue property.
*/
typedef UInt32      AudioQueuePropertyID;

/*!
    @typedef    AudioQueueParameterID
    @abstract   A value that uniquely identifies an audio queue parameter.
*/
typedef UInt32      AudioQueueParameterID;

/*!
    @typedef    AudioQueueParameterID
    @abstract   A value for an audio queue parameter.
*/
typedef Float32     AudioQueueParameterValue;

/*!
    @typedef    AudioQueueRef
    @abstract   Defines an opaque data type that represents an audio queue.
*/
typedef struct OpaqueAudioQueue *   AudioQueueRef;

/*!
    @typedef    AudioQueueTimelineRef
    @abstract   Defines an opaque data type that represents an audio queue timeline.
    @discussion
        You can use this object to observe any overloads in the audio device associated with the
        audio queue. A timeline object receives notifications of discontinuities in the audio
        hardware's sample timeline—for instance, a period of silence when sound was expected.
        Causes of discontinuities include changes in the device state or processing overloads.
        See Technical Q & A: QA 1467 for a discussion of Core Audio overload warnings. These
        warnings indicate you are taking too long to process audio data and the system has cut
        you off. You query a timeline object by passing it as a parameter to
        AudioQueueGetCurrentTime, which means a discontinuity has occurred.
*/
typedef struct OpaqueAudioQueueTimeline *   AudioQueueTimelineRef;

/*!
    @struct     AudioQueueBuffer
    @abstract   Defines a buffer of audio data to be managed by an audio queue.
    @discussion 
        Each audio queue has an associated set of audio queue buffers. You can request that a
        queue allocate buffers using the AudioQueueAllocateBuffer function and dispose of them
        using the AudioQueueFreeBuffer function.
        
    @field      mAudioDataBytesCapacity
        The size of the buffer, in bytes. This size is set when the buffer is allocated and
        cannot be changed.
    @field      mAudioData
       A pointer to the audio data in the buffer. Although you can write data to this buffer,
       you cannot make it point to another address.
    @field      mAudioDataByteSize
        The number of bytes of valid audio data in the buffer. You set this value when providing
        data for playback; the audio queue sets this value when recording data from a recording
        queue.
    @field      mUserData
        A value you may specify to identify the buffer when it is passed back in recording or
        playback callback functions.
*/

typedef struct AudioQueueBuffer {
    const UInt32                    mAudioDataBytesCapacity;
    void * const                    mAudioData;
    UInt32                          mAudioDataByteSize;
    void *                          mUserData;
} AudioQueueBuffer;

/*!
    @typedef    AudioQueueBufferRef
    @abstract   An pointer to an AudioQueueBuffer.
*/
typedef AudioQueueBuffer *AudioQueueBufferRef;

/*!
    @struct     AudioQueueParameterEvent
    @abstract   Specifies a value for an audio queue parameter.
    @discussion
        Two ways are available to supply an audio queue with parameters:
        
        <ul>
        <li>    Provide one or more parameters by calling the
                AudioQueueEnqueueBufferWithParameters function. In this case, the parameters are
                applied to the specified buffer when it is played.</li>
        <li>    Assign a parameter value immediately to an audio queue by calling the
                AudioQueueSetParameter function.</li>
        </ul>
        
        Note that the AudioQueueGetParameter function always returns the actual value of the
        parameter.

        In Mac OS X v10.5, audio queues have one parameter available: kAudioQueueParam_Volume,
        which controls the queue's playback volume.
        
    @field      mID
        The parameter.
    @field      mValue
        The value of the specified parameter.
*/
struct AudioQueueParameterEvent {
    AudioQueueParameterID           mID;
    AudioQueueParameterValue        mValue;
};
typedef struct AudioQueueParameterEvent AudioQueueParameterEvent;


/*!
    @struct     AudioQueueLevelMeterState
    @abstract   Specifies the current level metering information for one channel of an audio queue.
    @discussion
    @field      mAveragePower
        The audio channel's average RMS power.
    @field      mPeakPower
        The audio channel's peak RMS power
*/
typedef struct AudioQueueLevelMeterState {
    Float32     mAveragePower;
    Float32     mPeakPower;
} AudioQueueLevelMeterState;


#pragma mark -
#pragma mark Callbacks
//==================================================================================================
//  CALLBACKS
//==================================================================================================

/*!
    @typedef    AudioQueueOutputCallback
    @abstract   Defines a pointer to a callback function that is called when a playback audio
                queue has finished taking data from a buffer.

    @discussion
        A playback buffer callback is invoked when the audio queue has finished with the data to
        be played and the buffer is available to your application for reuse. Your application
        might want to immediately refill and re-enqueue the completed buffer at this time.
    @param      inUserData
        The value specified by the inUserData parameter of the AudioQueueNewOutput function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        The audio queue buffer made available by the audio queue.
*/
typedef void (*AudioQueueOutputCallback)(
                                    void *                  inUserData,
                                    AudioQueueRef           inAQ,
                                    AudioQueueBufferRef     inBuffer);

/*!
    @typedef    AudioQueueInputCallback
    @abstract   Defines a pointer to a callback function that is called when a recording audio
                queue has finished filling a buffer.
    @discussion
        You specify a recording buffer callback when calling AudioQueueNewInput. Your callback
        is invoked each time the recording audio queue has filled a buffer with input data.
        Typically, your callback should write the audio queue buffer's data to a file or other
        buffer, and then re-queue the audio queue buffer to receive more data.
        
    @param      inUserData
        The value you've specified in the inUserData parameter of the AudioQueueNewInput
        function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        An audio queue buffer, newly filled by the audio queue, containing the new audio data
        your callback needs to write.
    @param      inStartTime
        A pointer to an audio time stamp structure corresponding to the first sample contained
        in the buffer. This contains the sample time of the first sample in the buffer. This
        parameter is not used in basic recording.
    @param      inNumberPacketDescriptions
        The number of audio packets contained in the data provided to the callback
    @param      inPacketDescs
        For compressed formats which require packet descriptions, the packet descriptions
        produced by the encoder for the incoming buffer.
*/
typedef void (*AudioQueueInputCallback)(
                                    void *                          inUserData,
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer,
                                    const AudioTimeStamp *          inStartTime,
                                    UInt32                          inNumberPacketDescriptions,
                                    const AudioStreamPacketDescription *inPacketDescs);


/*!
    @typedef    AudioQueuePropertyListenerProc
    @abstract   Defines a pointer to a callback function that is called when a specified
                property changes value.
    @discussion
        You assign a property listener callback when calling AudioQueueAddPropertyListener.
        
    @param      inUserData
        A pointer to the data specified by the inUserData parameter of the
        AudioQueueAddPropertyListener function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inID
        The ID of the property that invoked the callback.
*/
typedef void (*AudioQueuePropertyListenerProc)(  
                                    void *                  inUserData,
                                    AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID);


//==================================================================================================
//  FUNCTIONS
//==================================================================================================

#pragma mark -
#pragma mark Creating/destroying queues
//=============================================================================
//  Creating/destroying queues
//=============================================================================

/*!
    @function   AudioQueueNewOutput
    @abstract   Creates a new audio queue for playing audio data.
    @discussion
        To create an playback audio queue, you allocate buffers, then queue buffers (using
        AudioQueueEnqueueBuffer). The callback receives buffers and typically queues them again.
        To schedule a buffer for playback, providing parameter and start time information, call
        AudioQueueEnqueueBufferWithParameters.
       
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be played. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inCallbackProc
        A pointer to a callback function to be called when the audio queue has finished playing
        a buffer.
    @param      inUserData
        A value or pointer to data that you specify to be passed to the callback function.
    @param      inCallbackRunLoop
        The event loop on which inCallbackProc is to be called. If you specify NULL, the
        callback is called on one of the audio queue's internal threads.
    @param      inCallbackRunLoopMode
        The run loop mode in which to call the callback. Typically, you pass
        kCFRunLoopCommonModes. Other possibilities are implementation specific. You can choose
        to create your own thread with your own run loops. For more information on run loops,
        see Run Loops or CFRunLoop Reference.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      outAQ
        On return, this variable contains a pointer to the newly created playback audio queue
        object.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewOutput(                const AudioStreamBasicDescription *inFormat,
                                    AudioQueueOutputCallback        inCallbackProc,
                                    void *                          inUserData,
                                    CFRunLoopRef                    inCallbackRunLoop,
                                    CFStringRef                     inCallbackRunLoopMode,
                                    UInt32                          inFlags,
                                    AudioQueueRef *                 outAQ)          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
    @function   AudioQueueNewInput
    @abstract   Creates a new audio queue for recording audio data.
    @discussion
        
        Outline of how to use the queue for input:
        
        - create input queue
        - allocate buffers
        - enqueue buffers (AudioQueueEnqueueBuffer, not with parameters, no packet descriptions)
        - the callback receives buffers and re-enqueues them
        
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be recorded. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inCallbackProc
        A pointer to a callback function to be called when the audio queue has finished filling
        a buffer.
    @param      inUserData
        A value or pointer to data that you specify to be passed to the callback function.
    @param      inCallbackRunLoop
        The event loop on which inCallbackProc is to be called. If you specify NULL, the
        callback is called on one of the audio queue's internal threads.
    @param      inCallbackRunLoopMode
        The run loop mode in which to call the callback. Typically, you pass
        kCFRunLoopCommonModes. Other possibilities are implementation specific. You can choose
        to create your own thread with your own run loops. For more information on run loops,
        see Run Loops or CFRunLoop Reference.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      outAQ
        On return, this variable contains a pointer to the newly created recording audio queue
        object.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewInput(                 const AudioStreamBasicDescription *inFormat,
                                    AudioQueueInputCallback         inCallbackProc,
                                    void *                          inUserData,
                                    CFRunLoopRef                    inCallbackRunLoop,
                                    CFStringRef                     inCallbackRunLoopMode,
                                    UInt32                          inFlags,
                                    AudioQueueRef *                 outAQ)          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueDispose
    @abstract   Disposes an existing audio queue.
    @discussion
        Disposing of the audio queue also disposes of all its resources, including its buffers.
    @param      inAQ
        The audio queue you want to dispose of
    @param      inImmediate
        If you pass true, the audio queue is disposed of immediately (that is, synchronously).
        If you pass false, disposal does not take place until all enqueued buffers are
        processed. Whether you call AudioQueueDispose synchronously or asynchronously, you can
        no longer interact with the queue, and the queue no longer invokes any callbacks to your
        application after the function returns.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueDispose(                  AudioQueueRef           inAQ, 
                                    Boolean                 inImmediate)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#pragma mark -
#pragma mark Buffer Management
//=============================================================================
//  Buffer Management
//=============================================================================

/*!
    @function   AudioQueueAllocateBuffer
    @abstract   Asks an audio queue to allocate a buffer.
    @discussion
        Once allocated, the pointer to the buffer and the buffer's size are fixed and cannot be
        changed. The mAudioDataByteSize field in the audio queue buffer structure,
        AudioQueueBuffer, is initially set to 0.
        
    @param      inAQ
        The audio queue you want to allocate a buffer.
    @param      inBufferByteSize
        The desired size of the new buffer, in bytes. An appropriate buffer size depends on the
        processing you will perform on the data as well as on the audio data format.
    @param      outBuffer
        On return, points to the newly created audio buffer. The mAudioDataByteSize field in the
        audio queue buffer structure, AudioQueueBuffer, is initially set to 0.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueAllocateBuffer(           AudioQueueRef           inAQ,
                                    UInt32                  inBufferByteSize,
                                    AudioQueueBufferRef *   outBuffer)              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueFreeBuffer
    @abstract   Disposes of an audio queue buffer.
    @discussion
        This function disposes of the buffer allocated by AudioQueueAllocateBuffer. Disposing of
        an audio queue also automatically disposes of any associated buffers and timeline
        objects. Call this function only if you want to dispose of a particular buffer while
        continuing to use an audio queue. You can dispose of buffers only when the associated
        queue is stopped (that is, not processing audio data).
    @param      inAQ
        The queue from which the buffer was allocated.
    @param      inBuffer
        The buffer to be disposed.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueFreeBuffer(               AudioQueueRef           inAQ,
                                    AudioQueueBufferRef     inBuffer)   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



/*!
    @function   AudioQueueEnqueueBuffer
    @abstract   Assigns a buffer to an audio queue for recording or playback.
    @discussion

    @param      inAQ
        The audio queue you are assigning the buffer to.
    @param      inBuffer
        The buffer to queue (that is, to be recorded into or played from).
    @param      inNumPacketDescs
        The number of packet descriptions pointed to by the inPacketDescs pointer. Applicable
        only for output queues and required only for variable-bit-rate (VBR) audio formats. Pass
        0 for input queues (no packet descriptions are required).
    @param      inPacketDescs
        An array of packet descriptions. Applicable only for output queues and required only for
        variable-bit-rate (VBR) audio formats. Pass NULL for input queues (no packet
        descriptions are required).
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueEnqueueBuffer(            AudioQueueRef                       inAQ,
                                    AudioQueueBufferRef                 inBuffer,
                                    UInt32                              inNumPacketDescs,
                                    const AudioStreamPacketDescription *inPacketDescs)      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueEnqueueBufferWithParameters
    @abstract   Assigns a buffer to an audio queue for playback, providing parameters
                and start time information.
    @discussion
        You can exert some control of the buffer queue by using this function. You can assign
        audio queue settings that are in effect carried by an audio queue buffer as you enqueue
        it. Hence, these changes only take effect when an audio queue buffer begins playing.
        
        This function queues a buffer for playback only, not for recording. Audio queues for
        recording have no parameters, do not support variable-bit-rate (VBR) formats (which
        might require trimming), and have a different way to handle timing. When queued for
        playback, the buffer must contain the audio data to be played back. See
        AudioQueueEnqueueBuffer for details on queuing a buffer for recording.
    @param      inAQ
        The audio queue associated with the buffer.
    @param      inBuffer
        The buffer to be played from.
    @param      inNumPacketDescs
        The number of packet descriptions pointed to by the inPacketDescs parameter. Required
        only for variable-bit-rate (VBR) audio formats. Pass 0 if no packet descriptions are
        required.
    @param      inPacketDescs
        A pointer to an array of audio stream packet descriptions. Required only for VBR audio
        formats. Pass NULL if no packet descriptions are required.
    @param      inTrimFramesAtStart
        The number of priming frames to skip at the start of the buffer.
    @param      inTrimFramesAtEnd
        The number of frames to skip at the end of the buffer.
    @param      inNumParamValues
        The number of parameter values pointed to by the inParamValues parameter.
    @param      inParamValues
        An array of parameter values(In Mac OS X v10.5, there is only one parameter,
        kAudioQueueParam_Volume.) These values are set before buffer playback and cannot be
        changed while the buffer is playing. How accurately changes in parameters can be
        scheduled depends on the size of the buffer. If there are no parameters to set
        (inNumParamValues = 0), pass NULL.
    @param      inStartTime
        A pointer to a structure containing the desired start time for playing the buffer. If
        you specify the time using the mSampleTime field of the AudioTimeStamp structure, the
        sample time is relative to the time the queue started. If you pass NULL for the start
        time, the buffer starts immediately after the previously queued buffer, or as soon as
        possible if no buffers are queued ahead of it. Buffers are played in the order they are
        queued. If multiple buffers are queued, their times must be in ascending order or NULL;
        otherwise, an error occurs. The start time indicates when the actual audio data in the
        buffer is to be played (that is, the trim frames are not counted).
    @param      outActualStartTime
        On return, points to an AudioTimeStamp structure indicating when the buffer will
        actually play.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueEnqueueBufferWithParameters(
                                    AudioQueueRef                           inAQ,
                                    AudioQueueBufferRef                     inBuffer,
                                    UInt32                                  inNumPacketDescs,
                                    const AudioStreamPacketDescription *    inPacketDescs,
                                    UInt32                                  inTrimFramesAtStart,
                                    UInt32                                  inTrimFramesAtEnd,
                                    UInt32                                  inNumParamValues,
                                    const AudioQueueParameterEvent *        inParamValues,
                                    const AudioTimeStamp *                  inStartTime,
                                    AudioTimeStamp *                        outActualStartTime)     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#pragma mark -
#pragma mark Queue Control
//=============================================================================
//  Queue Control
//=============================================================================

/*!
    @function   AudioQueueStart
    @abstract   Begins playing or recording audio.
    @discussion
        If the audio hardware is not already running, this function starts it.
    @param      inAQ
        The audio queue to start.
    @param      inStartTime
        A pointer to the time at which the audio queue should start. If you specify the time
        using the mSampleTime field of the AudioTimeStamp structure, the sample time is
        referenced to the sample frame timeline of the associated audio device. May be NULL.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueStart(                    AudioQueueRef                   inAQ,
                                    const AudioTimeStamp *          inStartTime)        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueuePrime
    @abstract   Begins decoding buffers in preparation for playback.
    @discussion
        This function begins decoding buffers in preparation for playback. It returns when at
        least the number of audio sample frames are decoded and ready to play or when all
        encoded buffers have been completely decoded. To ensure that a buffer has been decoded
        and is completely ready for playback, before playback:
            1.  Call AudioQueueEnqueueBuffer.
            2.  Call AudioQueuePrime, which waits if you pass 0 to have a default number of
                frames decoded.
            3.  Call AudioQueueStart.
    @param      inAQ
        The audio queue to be primed.
    @param      inNumberOfFramesToPrepare
        The number of frames to decode before returning. Pass 0 to decode all enqueued buffers.
    @param      outNumberOfFramesPrepared
        If not NULL, on return, a pointer to the number of frames actually decoded and prepared
        for playback.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueuePrime(                    AudioQueueRef           inAQ,
                                    UInt32                  inNumberOfFramesToPrepare,
                                    UInt32 *                outNumberOfFramesPrepared)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueStop
    @abstract   Stops playing or recording audio.
    @discussion
        This function resets the audio queue and stops the audio hardware associated with the
        queue if it is not in use by other audio services. Synchronous stops occur immediately,
        regardless of previously buffered audio data. Asynchronous stops occur after all queued
        buffers have been played or recorded.
    @param      inAQ
        The audio queue to stop.
    @param      inImmediate
        If you pass true, the stop request occurs immediately (that is, synchronously), and the
        function returns when the audio queue has stopped. Buffer callbacks are invoked during
        the stopping. If you pass false, the function returns immediately, but the queue does
        not stop until all its queued buffers are played or filled (that is, the stop occurs
        asynchronously). Buffer callbacks are invoked as necessary until the queue actually
        stops. Also, a playback audio queue callback calls this function when there is no more
        audio to play.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueStop(                     AudioQueueRef           inAQ,
                                    Boolean                 inImmediate)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueuePause
    @abstract   Pauses audio playback or recording.
    @discussion
        Pausing the queue does not affect buffers or reset the audio queue. To resume playback
        or recording using the audio queue, call AudioQueueStart.
    @param      inAQ
        The queue to be paused.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueuePause(                    AudioQueueRef           inAQ)       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueFlush
    @abstract   Resets the audio queue's decoder state.
    @discussion
        After all queued buffers have been played, the function cleans up all decoder state
        information. You must call this function following a sequence of buffers of encoded
        audio; otherwise, some of the audio might not play in the next set of queued buffers.
        Also, you might wish to call this function before calling AudioQueueStop depending on
        whether you want to stop immediately regardless of what has played or whether you want
        to ensure that all buffered data and all data that is in the middle of processing gets
        recorded or played before stopping.
        
    @param      inAQ
        The audio queue to be flushed.
        
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueFlush(                    AudioQueueRef           inAQ)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueReset
    @abstract   Resets an audio queue.
    @discussion
        This function immediately resets an audio queue, flushes any queued buffer, removes all
        buffers from previously scheduled use, and resets any decoder and digital signal
        processing (DSP) state information. It also invokes callbacks for any flushed buffers.
        If you queue any buffers after calling this function, processing does not occur until
        the decoder and DSP state information is reset. Hence, a discontinuity (that is, a
        "glitch") might occur.

    @param      inAQ
        The audio queue to reset.

    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueReset(                    AudioQueueRef           inAQ)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#pragma mark -
#pragma mark Parameter Management
//=============================================================================
//  Parameter Management
//=============================================================================

/*!
    @function   AudioQueueGetParameter
    @abstract   Obtains an audio queue parameter value.
    @discussion
        You can access the current parameter values for an audio queue at any time with this
        function.
    @param      inAQ
        The audio queue whose parameter value you want to obtain.
    @param      inParamID
        The ID of the parameter you want to obtain. In Mac OS X v10.5, audio queues have one
        parameter available: kAudioQueueParam_Volume, which controls the queue's playback
        volume.
    @param      outValue
        On return, points to the current value of the specified parameter.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetParameter(             AudioQueueRef               inAQ,
                                    AudioQueueParameterID       inParamID,
                                    AudioQueueParameterValue *  outValue)       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueSetParameter
    @abstract   Sets an audio queue parameter value.
    @discussion
    @param      inAQ
        The audio queue whose parameter value you want to set.
    @param      inParamID
        The ID of the parameter you want to set.
    @param      inValue
        The parameter value to set.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetParameter(             AudioQueueRef               inAQ,
                                    AudioQueueParameterID       inParamID,
                                    AudioQueueParameterValue    inValue)        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

                                                                        
#pragma mark -
#pragma mark Property Management
//=============================================================================
//  Property Management
//=============================================================================

/*!
    @function   AudioQueueGetProperty
    @abstract   Obtains an audio queue property value.
    @discussion 
    @param      inAQ
        The audio queue whose property value you want to obtain.
    @param      inID
        The ID of the property you want to obtain. See "Audio Queue Property IDs."
    @param      outData
        On return, points to the desired property value.
    @param      ioDataSize
        A pointer to the size of the property data. On input, points to the maximum bytes of
        space the caller expects to receive. On return, points to the actual data size.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetProperty(              AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    void *                  outData,
                                    UInt32 *                ioDataSize)             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueSetProperty
    @abstract   Sets an audio queue property value.
    @discussion 
    @param      inAQ
        The audio queue whose property value you want to set.
    @param      inID
        The ID of the property you want to set. See "Audio Queue Property IDs" for the various
        audio queue properties.
    @param      inData
        A pointer to the property value to set.
    @param      inDataSize
        The size of the property data.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetProperty(              AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    const void *            inData,
                                    UInt32                  inDataSize)             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
    @function   AudioQueueGetPropertySize
    @abstract   Obtains the size of an audio queue property.
    @discussion 
    @param      inAQ
        The audio queue containing the property value whose size you want to obtain.
    @param      inID
        The ID of the property value whose size you want to obtain. See "Audio Queue Property
        IDs" for possible values.
    @param      outDataSize
        On return, points to the size of the specified property value.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetPropertySize(          AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    UInt32 *                outDataSize)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueAddPropertyListener
    @abstract   Adds a listener callback for a property.
    @discussion 
        This callback is used to act upon a change in an audio queue property such as
        kAudioQueueProperty_IsRunning. For instance, if your application has a user interface
        with a Play/Stop button, and kAudioQueueProperty_IsRunning changes, you need to update
        your button.
    @param      inAQ
        The audio queue that owns the property you want to assign the listener callback to.
    @param      inID
        The ID of the property to which you want to assign a listener callback. See "Audio Queue Property IDs".
    @param      inProc
        The listener callback to be called when the property value changes.
    @param      inUserData
        A value to be passed to the listener callback when it is called.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueAddPropertyListener(      AudioQueueRef                   inAQ,
                                    AudioQueuePropertyID            inID,
                                    AudioQueuePropertyListenerProc  inProc,
                                    void *                          inUserData)     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueRemovePropertyListener
    @abstract   Removes a listener callback for a property.
    @discussion 
    @param      inAQ
        The audio queue that owns the property from which you want to remove a listener.
    @param      inID
        The ID of the property from which you want to remove a listener.
    @param      inProc
        The listener being removed.
    @param      inUserData
        The same inUserData value that was previously passed to AudioQueueAddPropertyListener.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueRemovePropertyListener(   AudioQueueRef                   inAQ,
                                    AudioQueuePropertyID            inID,
                                    AudioQueuePropertyListenerProc  inProc,
                                    void *                          inUserData)     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

                                    

#pragma mark -
#pragma mark Handling Timing
//=============================================================================
//  Handling Timing
//=============================================================================

/*!
    @function   AudioQueueCreateTimeline
    @abstract   Creates a timeline object.
    @discussion
        You need to instantiate a timeline object if you want to know about any timeline
        discontinuities. See AudioQueueGetCurrentTime for more details.
    @param      inAQ
        The audio queue to associate with the new timeline object.
    @param      outTimeline
        On return, points to the newly created timeline object.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueCreateTimeline(           AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef * outTimeline)            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueDisposeTimeline
    @abstract   Disposes of a timeline object.
    @discussion
        Disposing of an audio queue automatically disposes of any associated timeline objects.
        Call this function only if you want to dispose of a timeline object and not the audio
        queue associated with it.
    @param      inAQ
        The audio queue associated with the timeline object you want to dispose of.
    @param      inTimeline
        The timeline object to dispose of.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDisposeTimeline(          AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef   inTimeline)             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueGetCurrentTime
    @abstract   Obtains the current audio queue time.
    @discussion
        You must specify a timeline object if you want to be notified about any timeline
        discontinuities in the outTimelineDiscontinuity parameter. If you don't care about
        discontinuities, pass NULL in the inTimeLine and outTimelineDiscontinuity parameters.
    @param      inAQ
        The audio queue whose current time you want to obtain.
    @param      inTimeline
        The audio queue timeline object to which any timeline discontinuities are reported. May
        be NULL.
    @param      outTimeStamp
        On return, points to an audio timestamp structure containing the current audio queue
        time. The mSampleTime field is in terms of the audio queue's sample rate, and relative
        to the time at which the queue has started or will start.
    @param      outTimelineDiscontinuity
        On return, might be NULL. Only set to true or false if the inTimeLine parameter is not
        NULL. Set to true if a discontinuity has occurred in the sample timeline of the audio
        queue. For instance, the device's sample rate changed and a gap occurred in playback or
        recording, or the audio queue was unable to prepare and playback in time because it was
        late.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetCurrentTime(           AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef   inTimeline,
                                    AudioTimeStamp *        outTimeStamp,
                                    Boolean *               outTimelineDiscontinuity)       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueDeviceGetCurrentTime
    @abstract   Obtains the current time of the audio device associated with an audio queue.
    @discussion
        If the audio device associated with the audio queue is not running, the only valid field
        in the audio timestamp structure is mHostTime. This result differentiates the action of
        this function from that of the AudioDeviceGetCurrentTime function, (declared in
        AudioHardware.h) which returns an error if the audio device is not running.
    @param      inAQ
        The audio queue whose audio device is to be queried.
    @param      outTimeStamp
        A pointer to a structure that, on return, contains the current time of the audio device
        associated with the audio queue.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceGetCurrentTime(     AudioQueueRef           inAQ,
                                    AudioTimeStamp          *outTimeStamp)      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueDeviceTranslateTime
    @abstract   Converts the time in the time base of the associated audio device from one
                representation to another.
    @discussion
        This function converts from one time representation to another (for example, from sample
        time to host time or vice versa):
        
        <ul>
        <li>    Sample time is the absolute sample frame time.
        Sample numbers are the count of the samples on the audio device.</li>
        <li>    Host time is the
        time base of the host machine such as the time of the bus clock on the CPU.</li>
        </ul>

        The mSampleTime field in the AudioTimestamp structure (described in Core Audio Data
        Types Reference) is always in device time, not in audio queue time. Audio queue time is
        relative to the audio queue's start time. The associated audio device has to be running
        for the AudioQueueDeviceTranslateTime function to provide a result.
    @param      inAQ
        The queue whose audio device is to perform the requested time translation.
    @param      inTime
        A pointer to a structure containing the time to be translated.
    @param      outTime
        A pointer to the the translated time.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceTranslateTime(      AudioQueueRef           inAQ,
                                    const AudioTimeStamp *  inTime,
                                    AudioTimeStamp *        outTime)        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   AudioQueueDeviceGetNearestStartTime
    @abstract   Obtains an audio device's start time that is closest to a requested start time.
    @discussion
    @param      inAQ
        The audio queue whose device's nearest start time you want to obtain.
    @param      ioRequestedStartTime
        On entry, points to the requested start time. On return, points to the actual start time.
    @param      inFlags
        Reserved for future use. Pass 0.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceGetNearestStartTime(AudioQueueRef           inAQ,
                                    AudioTimeStamp *        ioRequestedStartTime,
                                    UInt32                  inFlags)        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#pragma mark -
#pragma mark Offline Rendering
//=============================================================================
//  Offline Rendering
//=============================================================================

/*!
    @function   AudioQueueSetOfflineRenderFormat
    @abstract   Specify an audio format to which the queue will perform subsequent offline rendering,
                or disable offline rendering.
    @discussion
                An output queue's audio playback can be redirected for capture to an audio file,
                to support an export function, for example. AudioQueueSetOfflineRenderFormat switches
                a queue between normal and offline rendering modes.
    @param      inAQ
        The output queue whose offline rendering mode is to be changed.
    @param      inFormat
        The desired format for offline rendering. Pass NULL to disable offline rendering and return the
        queue to normal output to an audio device. This format must be linear PCM and (if not mono)
        interleaved.
    @param      inLayout
        The desired channel layout for offline rendering; also NULL when disabling offline rendering.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetOfflineRenderFormat(   AudioQueueRef           inAQ,
                                    const AudioStreamBasicDescription *inFormat,
                                    const AudioChannelLayout *inLayout);

/*!
    @function   AudioQueueOfflineRender
    @abstract   Obtain a buffer of audio output from a queue in offline rendering mode.
    @discussion
    @param      inAQ
        The output queue from which to obtain output.
    @param      inTimestamp
        The point in time corresponding to the beginning of the output buffer. Only mSampleTime
        is used.
    @param      ioBuffer
        The buffer into which the queue will render.
    @param      inNumberFrames
        The number of frames of audio to render.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueOfflineRender(            AudioQueueRef           inAQ,
                                    const AudioTimeStamp *  inTimestamp,
                                    AudioQueueBufferRef     ioBuffer,
                                    UInt32                  inNumberFrames);

#ifdef __cplusplus
}
#endif

#endif // __AudioQueue_h__

