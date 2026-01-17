/*
    File:       CMIOHardwareStream.h

    Contains:   API for communicating with CoreMediaIO hardware

    Copyright:  © 2005-2018 by Apple Inc., all rights reserved.
*/


#if !defined(__CMIOHardwareStream_h__)
#define __CMIOHardwareStream_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Overview
/*!
    @header CMIOHardwareStream
    A CMIOStream represents a single conduit of data for transferring across the user/kernel boundary. As such, CMIOStreams are the gatekeepers of format information. Each has it's own
    format and list of available formats. These formats are not constrained, and may include encoded formats and non-media formats.

    CMIOStreams can contain instances of the CMIOControl class or it's many subclasses.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Includes

#include <CoreMediaIO/CMIOHardwareObject.h>
#include <CoreMedia/CMTime.h>
#include <CoreMedia/CMSimpleQueue.h>
#include <CoreMedia/CMSampleBuffer.h>


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOStream Types

/*!
    @typedef        CMIOStreamID
    @abstract       CMIOStream is the base class for all objects that represent a stream of data on a CMIO device.
    @discussion     CMIOStream is a subclass of CMIOObject and can contain CMIOControls.
*/
typedef CMIOObjectID CMIOStreamID;

/*!
    @typedef        CMIODeviceStreamQueueAlteredProc
    @abstract       Clients register a CMIODeviceStreamQueueAlteredProc when invoking CMIOStreamCopyBufferQueue() to specify a routine for the stream to call when it alters its
                    buffer queue. Input streams invoke it following the insertion of a buffer into the queue, and output streams will invoke it upon removal.
    @param          streamID
                        The stream whose queue has been altered
    @param          token
                        The token which was inserted / removed
    @param          refCon
                        A pointer to client data established when the proc was registered via CMIOStreamCopyBufferQueue().
*/
typedef void (*CMIODeviceStreamQueueAlteredProc)(CMIOStreamID streamID, void* token, void* refCon);

/*!
    @struct         CMIOStreamDeck
    @abstract       This structure is returned in response to the kCMIOStreamPropertyDeck property queries. 
    @field          mStatus
                        The CMIO Deck Status constant that changed.
    @field          mState
                        If kCMIODeckStatusOpcode == mStatus, this can be used to determine more specific status. The values are CMIO Deck State constants.
    @field          mState2
                        if kCMIODeckStatusOpcode == mStatus, this can be used to determine more specific status. The values are device specific.
*/
struct CMIOStreamDeck
{
    UInt32  mStatus;
    UInt32  mState;
    UInt32  mState2;
} API_AVAILABLE(macos(10.7));
typedef struct CMIOStreamDeck CMIOStreamDeck;
    
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOStream Constants

/*!
    @enum           CMIOStream Class Constants
    @abstract       Various constants related to CMIOStreams.
    @discussion     
    @constant       kCMIOStreamClassID
                        The CMIOClassID that identifies the CMIOStream class.
    @constant       kCMIOStreamUnknown
                        The CMIOObjectID for a nonexistent CMIOObject.
*/
enum
{
    kCMIOStreamClassID  = 'astr',
    kCMIOStreamUnknown  = kCMIOObjectUnknown
};

/*!
    @enum           CMIO Deck Status Constants
    @abstract       These are the values that can be in the CMIOStreamDeck.mStatus field.
    @discussion     
    @constant       kCMIODeckStatusBusy
                        Deck is busy.
    @constant       kCMIODeckStatusLocal
                        Deck is in local.
    @constant       kCMIODeckStatusNotThreaded
                        Deck is not threaded.
    @constant       kCMIODeckStatusTapeInserted
                        Deck has new tape.
    @constant       kCMIODeckStatusOpcode
                        Use CMIOStreamDeck.mState & CMIOStreamDeck.mState2 to determine state.
    @constant       kCMIODeckStatusSearchingForDevice
                        Searching for device.
    @constant       kCMIODeckStatusNoDevice
                        No device.
*/
enum 
{
    kCMIODeckStatusBusy                 = 1UL,
    kCMIODeckStatusLocal                = 2UL,
    kCMIODeckStatusNotThreaded          = 3UL,
    kCMIODeckStatusTapeInserted         = 4UL,
    kCMIODeckStatusOpcode               = 5UL,
    kCMIODeckStatusSearchingForDevice   = 6UL,  
    kCMIODeckStatusNoDevice             = 7UL
};

/*!
    @enum           CMIO Deck State Constants
    @abstract       These are the values that can be in the CMIOStreamDeck.mState field.
    @discussion     
    @constant       kCMIODeckStateStop
                        The deck is stopped. 
    @constant       kCMIODeckStatePlay
                        The deck is playing. 
    @constant       kCMIODeckStatePause
                        The deck is paused. 
    @constant       kCMIODeckStatePlaySlow
                        The deck is playing slow. 
    @constant       kCMIODeckStateReverseSlow
                        The deck is reversing slow. 
    @constant       kCMIODeckStatePlayReverse
                        The deck is playing in reverse. 
    @constant       kCMIODeckStateFastForward
                        The deck is fast forwarding. 
    @constant       kCMIODeckStateFastRewind
                        The deck is rewinding. 
*/
enum
{
    kCMIODeckStateStop          = 0UL,
    kCMIODeckStatePlay          = 1UL,
    kCMIODeckStatePause         = 2UL,
    kCMIODeckStatePlaySlow      = 3UL,
    kCMIODeckStateReverseSlow   = 4UL,
    kCMIODeckStatePlayReverse   = 5UL,
    kCMIODeckStateFastForward   = 6UL,
    kCMIODeckStateFastRewind    = 7UL
};

/*!
    @enum           CMIO Deck Shuttle Speed Constants
    @abstract       These are the speed constants for the CMIOStreamDeckJog() function.
    @discussion     
    @constant       kCMIODeckShuttleReverseHighSpeed
                        Reverse high speed.
    @constant       kCMIODeckShuttleReverseFastest
                        Reverse fastest.
    @constant       kCMIODeckShuttleReverseFaster
                        Reverse faster.
    @constant       kCMIODeckShuttleReverseFast
                        Reverse fast.
    @constant       kCMIODeckShuttleReverse1x
                        Reverse 1x.
    @constant       kCMIODeckShuttleReverseSlow3
                        Reverse slow 3.
    @constant       kCMIODeckShuttleReverseSlow2
                        Reverse slow 2.
    @constant       kCMIODeckShuttleReverseSlow1
                        Reverse slow 1.
    @constant       kCMIODeckShuttleReverseSlowest
                        Reverse slowest.
    @constant       kCMIODeckShuttlePlayPreviousFrame
                        Reverse previous frame.
    @constant       kCMIODeckShuttlePause
                        Pause.
    @constant       kCMIODeckShuttlePlayNextFrame
                        Play next frame.
    @constant       kCMIODeckShuttlePlaySlowest
                        Play slowest.
    @constant       kCMIODeckShuttlePlaySlow1
                        Play slow 1.
    @constant       kCMIODeckShuttlePlaySlow2
                        Play slow 2.
    @constant       kCMIODeckShuttlePlaySlow3
                        Play slow 3.
    @constant       kCMIODeckShuttlePlay1x
                        Play 1x.
    @constant       kCMIODeckShuttlePlayFast
                        Play fast.
    @constant       kCMIODeckShuttlePlayFaster
                        Play faster.
    @constant       kCMIODeckShuttlePlayFastest
                        Play fastest.
    @constant       kCMIODeckShuttlePlayHighSpeed
                        Play high speed.
 */ 
enum
{
    kCMIODeckShuttleReverseHighSpeed    = -10,
    kCMIODeckShuttleReverseFastest      = -9,
    kCMIODeckShuttleReverseFaster       = -8,
    kCMIODeckShuttleReverseFast         = -7,
    kCMIODeckShuttleReverse1x           = -6,
    kCMIODeckShuttleReverseSlow3        = -5,
    kCMIODeckShuttleReverseSlow2        = -4,
    kCMIODeckShuttleReverseSlow1        = -3,
    kCMIODeckShuttleReverseSlowest      = -2,
    kCMIODeckShuttlePlayPreviousFrame   = -1,
    kCMIODeckShuttlePause               = 0,
    kCMIODeckShuttlePlayNextFrame       = 1,
    kCMIODeckShuttlePlaySlowest         = 2,
    kCMIODeckShuttlePlaySlow1           = 3,
    kCMIODeckShuttlePlaySlow2           = 4,
    kCMIODeckShuttlePlaySlow3           = 5,
    kCMIODeckShuttlePlay1x              = 6,
    kCMIODeckShuttlePlayFast            = 7,
    kCMIODeckShuttlePlayFaster          = 8,
    kCMIODeckShuttlePlayFastest         = 9,
    kCMIODeckShuttlePlayHighSpeed       = 10
};
    
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOStream Properties

/*!
    @enum           CMIOStream Properties
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOStreams.
    @discussion     CMIOStream is a subclass of CMIOObject and has only the single scope, kCMIOObjectPropertyScopeGlobal. They have a master element and an element for each channel
                    in the stream numbered upward from 1. Note that CMIOStream objects share CMIOControl objects with their owning CMIODevice. Consequently, all the standard
                    CMIOControl related property selectors implemented by CMIODevices are also implemented by CMIOStreams. The same constants are to be used for such properties.
    @constant       kCMIOStreamPropertyDirection
                        A UInt32 where a value of 0 means that this CMIOStream is an output stream and a value of 1 means that it is an input stream.
    @constant       kCMIOStreamPropertyTerminalType
                        A UInt32 whose value describes the general kind of functionality attached to the CMIOStream. Constants that describe some of the values of this property are defined
                        in <IOKit/audio/IOAudioTypes.h>
    @constant       kCMIOStreamPropertyStartingChannel
                        A UInt32 that specifies the first element in the owning device that corresponds to element one of this stream.
    @constant       kCMIOStreamPropertyLatency
                        A UInt32 containing the number of frames of latency in the CMIOStream. Note that the owning CMIODevice may have additional latency so it should be queried as
                        well. If both the device and the stream say they have latency, then the total latency for the stream is the device latency summed with the stream latency.
    @constant       kCMIOStreamPropertyFormatDescription
                        A CMFormatDescriptionRef that describes the current format for the CMIOStream. When getting this property, the client must release the CMFormatDescriptionRef
                        when done with it. If settable, either one of the CMFormatDescriptionRefs obtained by getting the kCMIOStreamPropertyFormatDescriptions property can be
                        used, or a new CMFormatDescriptionRef can be provided. In the event of the latter, the CMFormatDescriptionEquals() routine will be used to see if the
                        stream can support the provided CMFormatDescriptionRef.
    @constant       kCMIOStreamPropertyFormatDescriptions
                        An CFArray of CMFormatDescriptionRefs that describe the available data formats for the CMIOStream. The client must release the CFArray when done with it.
                        This property is never settable, and is not present for streams whose kCMIOStreamPropertyFormatDescription property is not settable.
    @constant       kCMIOStreamPropertyStillImage
                        A CMSampleBufferRef which holds a still image that is generated as soon as possible when getting this property. The client must release the CMSampleBufferRef when
                        done with it. The qualifier contains the desired CMFormatDescriptionRef of the still. The description can be one of those obtained by getting the
                        kCMIOStreamPropertyStillImageFormatDescriptions property, or a new CMFormatDescriptionRef can be provided. In the event of the latter, the
                        CMFormatDescriptionEquals() routine will be used to see if the stream can support the provided CMFormatDescriptionRef. Getting this property might inject a
                        discontinuity into the stream if it currently running, depending on the underlying hardware. The returned image might not have the same CMFormatDescriptionRef that
                        was requested.
                        This property is never settable, and is not present for streams which are unable to produce still images.
    @constant       kCMIOStreamPropertyStillImageFormatDescriptions
                        A CFArray of CMFormatDescriptionRefs that describe the available still image data formats for the CMIOStream. The client must release the CFArray when done with
                        it. This property is never settable, and is not present for streams which are unable to produce still images.
    @constant       kCMIOStreamPropertyFrameRate
                        A Float64 that indicates the current video frame rate of the CMIOStream. The frame rate might fall below this, but it will not exceed it. This property is only present
                        for muxed or video streams which can determine their rate. 
     @constant       kCMIOStreamPropertyMinimumFrameRate
                        A Float64 that indicates the minumum video frame rate of the CMIOStream. This property is only present for muxed or video streams which can determine their rate and 
                        guarantee a minimum rate.
   @constant       kCMIOStreamPropertyFrameRates
                        An array of Float64s that indicates the valid values for the video frame rate of the CMIOStream. This property is only present for muxed or video streams which can
                        determine their rate. Moreover, it is limited to the rates that correspond to a single CMFormatDescriptionRef, as opposed to the super set of rates that would be
                        associated with the full set of available CMFormatDescriptionRefs.
                        If no qualifier is used, the rates of the current format (as reported via kCMIOStreamPropertyFormatDescription) will be returned.
                        If a qualifier is present, it contains the CMFormatDescriptionRef whose frame rates are desired. The description can be one of those obtained by getting the
                        kCMIOStreamPropertyFormatDescriptions property, or a new CMFormatDescriptionRef can be provided. In the event of the latter, the CMFormatDescriptionEquals()
                        routine will be used to see if the stream can support the provided CMFormatDescriptionRef. 
    @constant       kCMIOStreamPropertyFrameRateRanges
                        An array of AudioValueRanges that contains the minimum and maximum ranges for the video frame rate of the CMIOStream.
                        If no qualifier is used, the frame rate ranges of the current format (as reported via kCMIOStreamPropertyFormatDescription) will be returned.
                        If a qualifier is present, it contains the CMFormatDescriptionRef whose frame rate ranges are desired. The description can be one of those obtained by getting the
                        kCMIOStreamPropertyFormatDescriptions property, or a new CMFormatDescriptionRef can be provided. In the event of the latter, the CMFormatDescriptionEquals()
                        routine will be used to see if the stream can support the provided CMFormatDescriptionRef. 
    @constant       kCMIOStreamPropertyNoDataTimeoutInMSec
                        A UInt32 that allows a client to specify how much time (in milliseconds) that a device should allow to go by without seeing data before it determines that it is
                        experiencing a period of "no data." The default value is device dependent.
    @constant       kCMIOStreamPropertyDeviceSyncTimeoutInMSec
                        A UInt32 that allows a client to specify how much time (in milliseconds) that a device should allow to go by without seeing data before it determines that there is a
                        serious problem, and will never see data. A value of 0 means to ignore checking for the condition. When non-zero, the value takes precedence over
                        kCMIOStreamPropertyNoDataTimeoutInMSec. This property is set by a client when it starts a device and knows by apriori means that data is present; once the client
                        starts seeing data, this value should be reset to 0 by the client. When setting the value, the client should use a value that is long enough to take into account the
                        amount of time the device may need to start up (including, if it has one, starting a transport). A time of 10000ms (10 seconds) is reasonable.
    @constant       kCMIOStreamPropertyNoDataEventCount
                        A UInt32 that is incremented every time a period of no data is determined (via the previous two properties). A client can listen to this property to get
                        notifications that no-data events have occured.
    @constant       kCMIOStreamPropertyOutputBufferUnderrunCount
                        A UInt32 that is incremented every time a stream's buffers are not being serviced fast enough (such as a DCL overrun when transmitting to a FireWire device).
    @constant       kCMIOStreamPropertyOutputBufferRepeatCount
                        A UInt32 indicating how many times the last output buffer is re-presented to the device when no fresh output buffers are available.
    @constant       kCMIOStreamPropertyOutputBufferQueueSize
                        A UInt32 property that allows a client to control how large a queue to hold buffers that are to be sent to the stream; the larger the queue, the more latency until a
                        buffer reaches the stream, but the less likelyhood that data will have to be repeated (or that the stream will run dry). Default value depends on the stream.
    @constant       kCMIOStreamPropertyOutputBuffersRequiredForStartup
                        A UInt32 that allows a client to control how many buffers should be accumulated before actually starting to pass them onto the stream. Default value is to use
                        1/2 of the kCMIOStreamPropertyOutputBufferQueueSize.
    @constant       kCMIOStreamPropertyOutputBuffersNeededForThrottledPlayback
                        A UInt32 indicating the minimum number of buffers required for the stream to maintain throttled playback without dropping frames. Interested clients can use this to throttle
                        the number of buffers in flight to avoid sending out more frames than necessary, thus helping with memory usage and responsiveness.
    @constant       kCMIOStreamPropertyFirstOutputPresentationTimeStamp
                        A CMTime that specifies the presentation timestamp for the first buffer sent to a device; used for startup sync. This property is never settable.
    @constant       kCMIOStreamPropertyEndOfData
                        A UInt32 where a value of 1 means that the stream has reached the end of its data and a value of 0 means that more data is available.
    @constant       kCMIOStreamPropertyClock
                        A CFTypeRef that encapsulates a clock abstraction for a device's stream. The clock can be created with CMIOStreamClockCreate.
    @constant       kCMIOStreamPropertyCanProcessDeckCommand
                        A Boolean that indicates whether or not the stream can process deck commands. This property is never settable.
    @constant       kCMIOStreamPropertyDeck
                        A CMIOStreamDeck that represents the current status of a deck associated with a CMIO stream. The definitions of the values in the structure are defined by the deck
                        being controlled. This property is never settable.
    @constant       kCMIOStreamPropertyDeckFrameNumber
                        A UInt64 that represents the current frame number read from a deck associated with a stream.
    @constant       kCMIOStreamPropertyDeckDropness
                        A UInt32 value that represents the current drop frame state of the deck being controlled. 1 is dropframe, 0 is non-dropframe. This property is never settable.
    @constant       kCMIOStreamPropertyDeckThreaded
                        A UInt32 value that represents the deck being controlled's current tape threaded state. 1 deck is threaded, 0 deck is not threaded. This property is never settable.
    @constant       kCMIOStreamPropertyDeckLocal
                        A UInt32 value that indicates whether the deck is being controlled locally or remotely. 1 indicates local mode, 0 indicates remote mode. This property is never settable.
    @constant       kCMIOStreamPropertyDeckCueing
                        A SInt32 value that represents the current cueing status of the deck being controlled. 0 = cueing, 1 = cue complete, -1 = cue failed. This property is never settable.
    @constant       kCMIOStreamPropertyInitialPresentationTimeStampForLinkedAndSyncedAudio
                        A presentation timestamp to be used for a given AudioTimeStamp that was received for audio from the linked and synced CoreAudio audio device that is specified
                        by kCMIOStreamPropertyLinkedAndSyncedCoreAudioDeviceUID. The AudioTimeStamp is passed as the qualifier data. If the DAL device isn't yet read to return a
                        valid time, it should return kCMTimeInvalid. (CMTime)
    @constant       kCMIOStreamPropertyScheduledOutputNotificationProc
                        A procedure to be called when the stream determines when a buffer was output. The procedure and a reference constant are specified by
                        a CMIOStreamScheduledOutputNotificationProcAndRefCon structure.
    @constant       kCMIOStreamPropertyPreferredFormatDescription
                        A CMFormatDescriptionRef that describes the preferred format for the CMIOStream. When getting this property, the client must release the CMFormatDescriptionRef when
                        done with it. Either one of the CMFormatDescriptionRefs obtained by getting the kCMIOStreamPropertyFormatDescriptions property can be used, or a new CMFormatDescriptionRef.
                        CMFormatDescriptionRef can be provided. In the event of the latter, the FigFormatDescriptionEquals() routine will be used to see if the stream can support the provided
                        Setting this property is not a guarantee that the CMIOStream will provide data in this format;  when possible, the CMIOStream will examine all of the values specified by
                        the various clients sharing it, and select the most appropriate configuration. Typically, the value set for this property will only have an effect when the stream is
                        active (unlike kCMIOStreamPropertyFormatDescription, which takes place immediately). Note that if the client is the device master (set using kCMIODevicePropertyDeviceMaster),
                        setting the value of this property *will* directly affect the device, as if kCMIOStreamPropertyFormatDescription were used.
    @constant       kCMIOStreamPropertyPreferredFrameRate
                        A Float64 that indicates the current preferred video frame rate of the CMIOStream. Setting this property is not a guarantee that the CMIOStream will operate at that
                        framerate;  when possible, the CMIOStream will examine all of the values specified by the various clients sharing it, and select the most appropriate configuration.
                        Typically, the value set for this property will only have an effect when the stream is active (unlike kCMIOStreamPropertyFormatDescription, which takes place immediately).
                        Note that if the client is the device master (set using kCMIODevicePropertyDeviceMaster), setting the value of this property will directly affect the device, as if
                        kCMIOStreamPropertyFormatDescription were used.
*/
enum
{
    kCMIOStreamPropertyDirection                                            = 'sdir',
    kCMIOStreamPropertyTerminalType                                         = 'term',
    kCMIOStreamPropertyStartingChannel                                      = 'schn',
    kCMIOStreamPropertyLatency                                              = 'ltnc',
    kCMIOStreamPropertyFormatDescription                                    = 'pft ',
    kCMIOStreamPropertyFormatDescriptions                                   = 'pfta',
    kCMIOStreamPropertyStillImage                                           = 'stmg',
    kCMIOStreamPropertyStillImageFormatDescriptions                         = 'stft',
    kCMIOStreamPropertyFrameRate                                            = 'nfrt',
    kCMIOStreamPropertyMinimumFrameRate                                     = 'mfrt',
    kCMIOStreamPropertyFrameRates                                           = 'nfr#',
    kCMIOStreamPropertyFrameRateRanges                                      = 'frrg',
    kCMIOStreamPropertyNoDataTimeoutInMSec                                  = 'pmn1',
    kCMIOStreamPropertyDeviceSyncTimeoutInMSec                              = 'pmn2',
    kCMIOStreamPropertyNoDataEventCount                                     = 'pmn3',
    kCMIOStreamPropertyOutputBufferUnderrunCount                            = 'pmou',
    kCMIOStreamPropertyOutputBufferRepeatCount                              = 'pmor',
    kCMIOStreamPropertyOutputBufferQueueSize                                = 'pmoq',
    kCMIOStreamPropertyOutputBuffersRequiredForStartup                      = 'pmos',
    kCMIOStreamPropertyOutputBuffersNeededForThrottledPlayback               = 'miff',
    kCMIOStreamPropertyFirstOutputPresentationTimeStamp                     = 'popt',
    kCMIOStreamPropertyEndOfData                                            = 'pmed',
    kCMIOStreamPropertyClock                                                = 'pmcl',
    kCMIOStreamPropertyCanProcessDeckCommand                                = 'pdcd',
    kCMIOStreamPropertyDeck                                                 = 'deck',
    kCMIOStreamPropertyDeckFrameNumber                                      = 'tcod',
    kCMIOStreamPropertyDeckDropness                                         = 'drop',
    kCMIOStreamPropertyDeckThreaded                                         = 'thrd',
    kCMIOStreamPropertyDeckLocal                                            = 'locl',
    kCMIOStreamPropertyDeckCueing                                           = 'cuec',
    kCMIOStreamPropertyInitialPresentationTimeStampForLinkedAndSyncedAudio  = 'ipls',
    kCMIOStreamPropertyScheduledOutputNotificationProc                      = 'sonp',
    kCMIOStreamPropertyPreferredFormatDescription                           = 'prfd',
    kCMIOStreamPropertyPreferredFrameRate                                   = 'prfr'
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOStream Functions

/*!
    @functiongroup  CMIOStream
*/

/*!
    @function       CMIOStreamCopyBufferQueue
    @abstract       Gets the CMSimpleQueue of the specified CMIOStream and registers a 'queue altered' callback function to be invoked when the stream alters the queue.
                    The stream will only invoke the most recent callback function registered. To unregister the existing callback function, pass NULL as the queueAlteredProc.
    @param          streamID
                        The CMIOStream to create the CMSimpleQueue.
    @param          queueAlteredProc
                        Routine to be invoked when the stream alters the queue for insertions (input streams) and removals (output streams).
                        Set this value to NULL to unregister any existing callbacks.
    @param          queueAlteredRefCon
                        The client refCon to pass back when the queue altered proc is invoked.
    @param          queue
                        The CMSimpleQueue to fill (for input streams) or to drain (for output streams).
                        If the return value is non-NULL, the client will need to release the queue when done with it.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamCopyBufferQueue(  CMIOStreamID                        streamID,
                            CMIODeviceStreamQueueAlteredProc    queueAlteredProc,
                            void*                               queueAlteredRefCon,
                            CMSimpleQueueRef*                   queue) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIOStreamDeckPlay
    @abstract       Sends a generic deck play command to the specified CMIOStream, instructing its associated deck to play.
    @param          streamID
                        The CMIOStream whose deck controls are being manipulated.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamDeckPlay(CMIOStreamID streamID) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIOStreamDeckStop
    @abstract       Sends a generic deck stop command to the specified CMIOStream, instructing the associated deck to stop.
    @param          streamID
                        The CMIOStream whose deck controls are being manipulated.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamDeckStop(CMIOStreamID streamID) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIOStreamDeckJog
    @abstract       Sends a generic deck jog command to the specified CMIOStream, instructing the associated deck to wind at the specified speed.
    @param          streamID
                        The CMIOStream whose deck controls are being manipulated.
    @param          speed
                        One of the CMIO Deck Shuttle Speed constants to specify the speed of movement of the associated deck.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamDeckJog(  CMIOStreamID    streamID,
                    SInt32          speed) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIOStreamDeckCueTo
    @abstract       Sends a generic deck cue-to command to the specified CMIOStream, instructing the associated deck to seek to a specific point.
    @param          streamID
                        The CMIOStream whose deck controls are being manipulated.
    @param          frameNumber
                        The desired frame number that the deck should cue to.
    @param          playOnCue
                        An indicator that the deck should start playing when the cue-to point is reached.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamDeckCueTo(    CMIOStreamID    streamID,
                        UInt64          frameNumber,
                        Boolean         playOnCue) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIOStreamClockCreate
    @abstract       Creates a clock object that can be vended by kCMIOStreamPropertyClock, and driven
                    by CMIOStreamClockPostTimingEvent.
    @param          allocator
                        Used to allocate the memory for the clock.
    @param          sourceIdentifier
                        An opaque reference to the entity that is driving the clock. This value is used internally to determine if two CMIO Device Clocks have the same hardware source, and
                        thus determine whether or not they will drift relative to one another. This parameter is used in the following way: if a device supports multiple active streams that
                        are internally clocked by a common source, then instead of sharing one clock between each stream, a clock per stream can be created with the sourceIdentifier for each
                        clock set to be the same value.
    @param          getTimeCallMinimumInterval
                        If the clock is queried for its current time more often than this interval, an interpolated value will be returned.
    @param          numberOfEventsForRateSmoothing
                        The number of events to use for rate smoothing; must be > 0.
    @param          numberOfAveragesForRateSmoothing
                        The number of averages used for rate smoothing; if 0, the CA HAL smoothing algorithm is used.
    @param          clock
                        Receives the created clock. When the clock is no longer needed, CMIOStreamClockInvalidate should be called, followed by CFRelease.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamClockCreate(  CFAllocatorRef  allocator,
                        CFStringRef     clockName,
                        const void*     sourceIdentifier,
                        CMTime          getTimeCallMinimumInterval,
                        UInt32          numberOfEventsForRateSmoothing,
                        UInt32          numberOfAveragesForRateSmoothing,
                        CFTypeRef*      clock) API_AVAILABLE(macos(10.7));


/*!
    @function       CMIOStreamClockPostTimingEvent
    @abstract       Used to drive a clock created by CMIOStreamClockCreate.
    @discussion     A CMIO Stream Clock is driven by events that occur on the stream. These events have a "stream time" value, and a host time value. For example, a camera might be set to
                    capture images at a rate of 29.97 frames per second. This rate is determined by the camera's clocking circuitry, which is not synchronized to the computer's host clock.
                    Every time a frame comes in, the CMIO device driver increments the event time by 1/29.97, and calls this routine with the host time for when that frame was captured. 
    @param          eventTime
                        Time when the event occurred, on the stream's timeline.
    @param          hostTime
                        The host time at which the event occurred.
    @param          resynchronize
                        If true, indicates that a device has experienced a disruption in its data stream, and a new anchor point for measuring time is created.
    @param          clock
                        The CMIO Device Clock returned by CMIOStreamClockCreate.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamClockPostTimingEvent( CMTime      eventTime,
                                UInt64      hostTime,
                                Boolean     resynchronize,
                                CFTypeRef   clock) API_AVAILABLE(macos(10.7));


/*!
    @function       CMIOStreamClockInvalidate
    @abstract       Indicates that a clock is no longer valid.
    @discussion     Since a CMIO Stream Clock is a reference counted object, it may be retained by clients for longer than its valid (for example, the device is stopped). When a device is no
                    longer going to be posting events for a clock, it needs to call this routine, followed by CFRelease. After this point, any clients that query the clock for the current
                    time will get kCMTimeInvalid.
    @param          clock
                        The CMIO Stream Clock returned by CMIOStreamClockCreate.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOStreamClockInvalidate(CFTypeRef clock) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIOStreamClockConvertHostTimeToDeviceTime
    @abstract       Converts a host time value to the equivalent time on a device's clock.
    @param          hostTime
                        The host time value to convert.
    @param          clock
                        The device clock object returned by CMIOStreamClockCreate.
    @result         The time on clock that is equivalent to the given hosttime.
*/
extern CMTime
CMIOStreamClockConvertHostTimeToDeviceTime( UInt64      hostTime,
                                            CFTypeRef   clock) API_AVAILABLE(macos(10.7));


/*!
    @typedef    CMIOStreamScheduledOutputNotificationProc
    @discussion Callback used to notify a client when a buffer was output.
*/
/*!
    @typedef        CMIOStreamScheduledOutputNotificationProc
    @abstract       Clients register a CMIOStreamScheduledOutputNotificationProc using kCMIOStreamPropertyScheduledOutputNotificationProc.
                    The procedure is called when the stream determines when a particular buffer was output.
    @param          sequenceNumberOfBufferThatWasOutput
                        The sequence number of the buffer that was output
    @param          outputHostTime
                        The host time that buffer was output
    @param          scheduledOutputNotificationRefCon
                        A pointer to client data, established when the proc was registered using kCMIOStreamPropertyScheduledOutputNotificationProc
*/
typedef void (*CMIOStreamScheduledOutputNotificationProc)(UInt64 sequenceNumberOfBufferThatWasOutput, UInt64 outputHostTime, void* scheduledOutputNotificationRefCon);


/*!
    @struct     CMIOStreamScheduledOutputNotificationProcAndRefCon
    @discussion The payload for kCMIOStreamPropertyScheduledOutputNotificationProc.
    @field      scheduledOutputNotificationProc
                    The procedure to call when a buffer was output
    @field      scheduledOutputNotificationRefCon
                    A pointer to client data that will be passed to the scheduledOutputNotificationProc
*/
struct CMIOStreamScheduledOutputNotificationProcAndRefCon {
    CMIOStreamScheduledOutputNotificationProc   scheduledOutputNotificationProc;
    void*                                       scheduledOutputNotificationRefCon;
} API_AVAILABLE(macos(10.8));
typedef struct CMIOStreamScheduledOutputNotificationProcAndRefCon CMIOStreamScheduledOutputNotificationProcAndRefCon;

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif
