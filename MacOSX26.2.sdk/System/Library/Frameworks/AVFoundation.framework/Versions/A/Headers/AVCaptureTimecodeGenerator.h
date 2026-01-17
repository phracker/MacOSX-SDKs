#if !__has_include(<AVFCapture/AVCaptureTimecodeGenerator.h>)
/*
 File:  AVCaptureTimecodeGenerator.h

 Framework:  AVFoundation

 Copyright 2024-2025 Apple Inc. All rights reserved.
*/

#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMTime.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines possible sources for generating timecode in using a timecode generator.
typedef NS_ENUM(NSInteger, AVCaptureTimecodeSourceType) {
    /// No internal or external source is adopted. Timecodes are zero-based, sequentially generated frame counts.
    AVCaptureTimecodeSourceTypeFrameCount NS_SWIFT_NAME(frameCount)         = 0,
    /// Synchronizes timecode to the system clock for real-time applications. Useful for live events or scenarios requiring alignment with the actual time of day.
    AVCaptureTimecodeSourceTypeRealTimeClock NS_SWIFT_NAME(realTimeClock)   = 1,
    /// Synchronizes timecode to an external timecode data stream. Ideal for professional audio and video synchronization with external quarter-frame MIDI or HID timecode hardware.
    AVCaptureTimecodeSourceTypeExternal NS_SWIFT_NAME(external)             = 2,
} NS_SWIFT_NAME(AVCaptureTimecode.SourceType) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Constants defining the synchronization status of a timecode generator .
typedef NS_ENUM(NSInteger, AVCaptureTimecodeGeneratorSynchronizationStatus) {
    /// The initial state before a source is selected or during error conditions.
    AVCaptureTimecodeGeneratorSynchronizationStatusUnknown              = 0,
    /// A timecode source has been selected, but synchronization has not yet started.
    AVCaptureTimecodeGeneratorSynchronizationStatusSourceSelected       = 1,
    /// The timecode generator is actively synchronizing to the selected source.
    AVCaptureTimecodeGeneratorSynchronizationStatusSynchronizing        = 2,
    /// The timecode generator is successfully synchronized to the selected source, maintaining active timing alignment.
    AVCaptureTimecodeGeneratorSynchronizationStatusSynchronized         = 3,
    /// The synchronization has timed out.
    AVCaptureTimecodeGeneratorSynchronizationStatusTimedOut             = 4,
    /// The timecode generator has failed to establish a connection with a given source.
    AVCaptureTimecodeGeneratorSynchronizationStatusSourceUnavailable    = 5,
    /// The timecode generator is receiving data from the source in an unrecognized format.
    AVCaptureTimecodeGeneratorSynchronizationStatusSourceUnsupported    = 6,
    /// The timecode generator does not require active synchronization for a given source.
    AVCaptureTimecodeGeneratorSynchronizationStatusNotRequired          = 7
} NS_SWIFT_NAME(AVCaptureTimecodeGenerator.SynchronizationStatus) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Describes a timecode source that a timecode generator can synchronize to.
///
/// `AVCaptureTimecodeSource` provides information about a specific timecode source available for synchronization in `AVCaptureTimecodeGenerator`. It includes metadata such as the source’s name, type, and unique identifier.
NS_SWIFT_NAME(AVCaptureTimecode.Source)
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureTimecodeSource : NSObject <NSCopying>

/// The name of the timecode source.
///
/// This property provides a descriptive name of the timecode source, useful for display in user interfaces or logging.
@property (nonatomic, copy, readonly, nonnull) NSString *displayName;

/// The type of timecode source.
///
/// Indicates the type of timecode source, represented as a value from the ``AVCaptureTimecodeSynchronizationSourceType`` enum. This helps you identify the source for specific synchronization use cases, such as frame counter, real-time clock, MIDI, or HID.
@property (nonatomic, assign, readonly) AVCaptureTimecodeSourceType type;

/// A unique identifier for the timecode source.
///
/// The UUID uniquely identifies this timecode source. It is particularly useful when multiple sources of the same type are available, allowing your application to distinguish between them.
///
/// - Note: This value does not persist across application sessions.
@property (nonatomic, copy, readonly) NSUUID *uuid;

@end

/// This structure represents a timecode, adhering to SMPTE standards, which define precise time information and associated timestamps for video or audio synchronization.
///
/// This structure corresponds to the SMPTE 12M-1 Linear Timecode (LTC) format, widely used for professional video and audio synchronization.
typedef struct {
    /// Time component representing the current timecode in hours.
    uint8_t hours;
    /// Time component representing the current timecode in minutes.
    uint8_t minutes;
    /// Time component representing the current timecode in seconds.
    uint8_t seconds;
    /// Frame component of the timecode, indicating the frame count within the second.
    uint8_t frames;
    /// A 32-bit field carrying SMPTE user bits, which are not strictly standardized. User bits are often used for additional metadata such as scene-take information, reel numbers, or dates, but their exact usage is application-dependent.
    uint32_t userBits;
    /// Frame duration of the timecode. If unknown, the value is `kCMTimeInvalid`.
    CMTime frameDuration;
    /// Source type of the timecode, indicating the emitter, carriage, or transport mechanism.
    AVCaptureTimecodeSourceType sourceType API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);
} AVCaptureTimecode API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Creates a sample buffer containing Timecode Media Description metadata for integration with a video track.
///
/// - Parameter timecode: The ``AVCaptureTimecode`` instance providing the timecode details to encode.
/// - Parameter presentationTimeStamp: The presentation time stamp that determines the exact moment in the media timeline where the metadata should be applied. It is embedded in the sample timing info (``CMSampleTimingInfo``) and ensures that the packaged metadata synchronizes accurately with the corresponding video frame.
/// - Returns: A ``CMSampleBufferRef`` with the encoded Timecode Media Description metadata for video synchronization, or `nil` if sample buffer creation fails.
CMSampleBufferRef _Nullable AVCaptureTimecodeCreateMetadataSampleBufferAssociatedWithPresentationTimeStamp(AVCaptureTimecode timecode, CMTime presentationTimeStamp) NS_SWIFT_NAME(AVCaptureTimecode.createMetadataSampleBuffer(from:associatedWithPresentationTimeStamp:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Creates a sample buffer containing Timecode Media Description metadata for a specified duration.
///
/// - Parameter timecode: The ``AVCaptureTimecode`` instance providing the timecode details for the metadata sample.
/// - Parameter duration: The duration that the metadata sample buffer should represent.
/// - Returns: A ``CMSampleBufferRef`` with encoded Timecode Media Description metadata for the given duration, or `nil` if sample buffer creation fails.
///
/// Use this function for scenarios where timecode metadata needs to span a custom interval (not just a single frame), such as non-frame-accurate workflows or for describing a segment of media with a consistent timecode.
CMSampleBufferRef _Nullable AVCaptureTimecodeCreateMetadataSampleBufferForDuration(AVCaptureTimecode timecode, CMTime duration) NS_SWIFT_NAME(AVCaptureTimecode.createMetadataSampleBuffer(from:forDuration:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Generates a new timecode by adding a specified number of frames to the given timecode, handling overflow for seconds, minutes, and hours.
///
/// - Parameter timecode: The original ``AVCaptureTimecode`` to be incremented.
/// - Parameter framesToAdd: The number of frames to add to the timecode.
/// - Returns: A new ``AVCaptureTimecode`` struct with the updated time values after adding the specified frames.
AVCaptureTimecode AVCaptureTimecodeAdvancedByFrames(AVCaptureTimecode timecode, int64_t framesToAdd) NS_SWIFT_NAME(AVCaptureTimecode.advanced(_:by:)) API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@class AVCaptureTimecodeGenerator;

/// A protocol for receiving real-time timecode updates and error notifications from a timecode generator.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@protocol AVCaptureTimecodeGeneratorDelegate <NSObject>

@required

/// Notifies the delegate when new, unaligned timecodes are parsed from the specified source.
///
/// - Parameter generator: The timecode generator providing the update.
/// - Parameter timecode: The updated timecode data.
/// - Parameter source: The source from which the timecode was received.
- (void)timecodeGenerator:(AVCaptureTimecodeGenerator *)generator didReceiveUpdate:(AVCaptureTimecode)timecode fromSource:(AVCaptureTimecodeSource *)source;

/// Notifies the delegate when the synchronization status of a timecode source changes.
///
/// - Parameter generator: The ``AVCaptureTimecodeGenerator`` instance providing the status update.
/// - Parameter synchronizationStatus: The updated synchronization state.
/// - Parameter source: The internal or external source to which the generator synchronizes.
- (void)timecodeGenerator:(AVCaptureTimecodeGenerator *)generator transitionedToSynchronizationStatus:(AVCaptureTimecodeGeneratorSynchronizationStatus)synchronizationStatus forSource:(AVCaptureTimecodeSource *)source;

/// Notifies the delegate when the list of available timecode synchronization sources is updated.
///
/// - Parameter generator: The ``AVCaptureTimecodeGenerator`` instance providing the source list update.
/// - Parameter availableSources: An array of ``AVCaptureTimecodeSource`` objects representing the available timecode synchronization sources.
- (void)timecodeGenerator:(AVCaptureTimecodeGenerator *)generator didUpdateAvailableSources:(NSArray<AVCaptureTimecodeSource *> *)availableSources;

@end

/// Generates and synchronizes timecode data from various sources for precise video and audio synchronization.
///
/// The ``AVCaptureTimecodeGenerator`` class supports multiple timecode sources, including frame counting, system clock synchronization, and MIDI timecode input (MTC). Suitable for playback, recording, or other time-sensitive operations where precise timecode metadata is required.
///
/// Use the ``startSynchronizationWithTimecodeSource:`` method to set up the desired timecode source.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureTimecodeGenerator : NSObject

/// An array of available timecode synchronization sources that can be used by the timecode generator.
///
/// This property provides a list of ``AVCaptureTimecodeSource`` objects representing the available timecode sources with which the generator can synchronize. The sources may include built-in options such as the frame counter and real-time clock, as well as dynamically detected sources such as connected MIDI or HID devices.
///
/// This array is key-value observable, allowing you to monitor changes in real-time. For example, when a new MIDI device is connected, the array is updated to include the corresponding timecode source.
///
/// - Returns: A read-only array of ``AVCaptureTimecodeSource`` objects representing the available timecode synchronization sources.
@property(atomic, copy, readonly) NSArray<AVCaptureTimecodeSource *> *availableSources;

/// The active timecode source used by ``AVCaptureTimecodeGenerator`` to maintain clock synchronization for accurate timecode generation.
///
/// Indicates the active timecode source, as defined in the ``AVCaptureTimecodeSynchronizationSourceType`` enum. If an ``AVCaptureTimecodeGenerator`` becomes disconnected from its source, it continues generating timecodes using historical data from its ring buffer. This approach allows the generator to maintain synchronization during brief disruptions, as is common in cinema workflows where timecode signals may experience discontinuities.
@property(nonatomic, readonly) AVCaptureTimecodeSource *currentSource;

/// The delegate that receives timecode updates from the timecode generator.
///
/// You can use your ``delegate`` to receive real-time timecode updates. Implement the ``timecodeGenerator:didReceiveUpdate:`` method in your delegate to handle updates.
@property(nonatomic, readonly, nullable) id<AVCaptureTimecodeGeneratorDelegate> delegate;

/// The dispatch queue on which delegate callbacks are invoked.
///
/// Provides the queue set in ``setDelegate:queue:``. If no delegate is assigned, this property is `nil`.
@property(nonatomic, readonly, nullable) dispatch_queue_t delegateCallbackQueue;

/// Assigns a delegate to receive real-time timecode updates and specifies a queue for callbacks.
///
/// - Parameter delegate: An object conforming to the ``AVCaptureTimecodeGeneratorDelegate`` protocol.
/// - Parameter callbackQueue: The dispatch queue on which the delegate methods are invoked. The `callbackQueue` parameter may not be `nil`, except when setting the ``AVCaptureTimecodeGeneratorDelegate`` to `nil`, otherwise ``setDelegate:queue:`` throws an `NSInvalidArgumentException`.
///
/// Use this method to configure a delegate that handles timecode updates. The specified `queue` ensures thread-safe invocation of delegate methods.
- (void)setDelegate:(nullable id<AVCaptureTimecodeGeneratorDelegate>)delegate queue:(nullable dispatch_queue_t)callbackQueue;

/// The maximum time interval allowed for source synchronization attempts before timing out.
///
/// This property specifies the duration, in seconds, that the ``AVCaptureTimecodeGenerator`` will attempt to synchronize with a timecode source before timing out if synchronization cannot be achieved. If this threshold is exceeded, the synchronization status updates to reflect a timeout, and your ``AVCaptureTimecodeGeneratorDelegate/timecodeGenerator:transitionedToSynchronizationStatus:forSource:`` delegate method fires, informing you of the event. The default value is 15 seconds.
@property(nonatomic) NSTimeInterval synchronizationTimeout;

/// The time offset, in seconds, applied to the generated timecode.
///
/// This offset allows fine-tuning of time alignment for synchronization with external sources or to accommodate any intentional delay. The default value is 0 seconds.
@property(nonatomic) NSTimeInterval timecodeAlignmentOffset;

/// The frame duration that the generator will use to generate timecodes.
@property(nonatomic) CMTime timecodeFrameDuration;

/// Synchronizes the generator with the specified timecode source.
///
/// - Parameter source: The timecode source for synchronization.
- (void)startSynchronizationWithTimecodeSource:(AVCaptureTimecodeSource *)source NS_SWIFT_NAME(startSynchronization(source:));

/// Generates an initial timecode intended to be the first in a sequence.
///
/// - Returns: A populated ``AVCaptureTimecode`` structure.
- (AVCaptureTimecode)generateInitialTimecode;

/// A frame counter timecode source that operates independently of any internal or external synchronization.
///
/// This class property represents a standalone timecode source that advances based purely on frame count, independent of any real-time or external synchronization. It is ideal for scenarios where a simple, self-contained timing reference is sufficient, without requiring alignment to system clocks or external devices.
@property(class, nonatomic, readonly) AVCaptureTimecodeSource *frameCountSource;

/// A predefined timecode source synchronized to the real-time system clock.
///
/// This class property provides a default timecode source based on the real-time system clock, requiring no external device. It is ideal for live events or scenarios where alignment with the current time of day is necessary.
@property(class, nonatomic, readonly) AVCaptureTimecodeSource *realTimeClockSource;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureTimecodeGenerator.h>
#endif
