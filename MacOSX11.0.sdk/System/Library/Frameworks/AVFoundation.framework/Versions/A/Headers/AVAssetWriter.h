#if !__has_include(<AVFCore/AVAssetWriter.h>)
/*
	File:  AVAssetWriter.h

	Framework:  AVFoundation
 
	Copyright 2010-2020 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMediaSelectionGroup.h>
#import <AVFoundation/AVAssetSegmentReport.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMBase.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <UniformTypeIdentifiers/UTType.h>

@class AVAssetWriterInput;
@class AVMetadataItem;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum AVAssetWriterStatus
 @abstract
	These constants are returned by the AVAssetWriter status property to indicate whether it can successfully write samples to its output file.

 @constant	 AVAssetWriterStatusUnknown
	Indicates that the status of the asset writer is not currently known.
 @constant	 AVAssetWriterStatusWriting
	Indicates that the asset writer is successfully writing samples to its output file.
 @constant	 AVAssetWriterStatusCompleted
	Indicates that the asset writer has successfully written all samples following a call to finishWriting.
 @constant	 AVAssetWriterStatusFailed
	Indicates that the asset writer can no longer write samples to its output file because of an error. The error is described by the value of the asset writer's error property.
 @constant	 AVAssetWriterStatusCancelled
	Indicates that the asset writer can no longer write samples because writing was canceled with the cancelWriting method.
 */
typedef NS_ENUM(NSInteger, AVAssetWriterStatus) {
	AVAssetWriterStatusUnknown = 0,
	AVAssetWriterStatusWriting = 1,
	AVAssetWriterStatusCompleted = 2,
	AVAssetWriterStatusFailed = 3,
	AVAssetWriterStatusCancelled = 4
};

@class AVAssetWriterInternal;

/*!
 @class AVAssetWriter
 @abstract
	 AVAssetWriter provides services for writing media data to a new file,
 
 @discussion
	Instances of AVAssetWriter can write media to new files in formats such as the QuickTime movie file format or the MPEG-4 file format. AVAssetWriter has support for automatic interleaving of media data for multiple concurrent tracks. Source media data can be obtained from instances of AVAssetReader for one or more assets or from other sources outside of AVFoundation.

	Instances of AVAssetWriter can re-encode media samples as they are written. Instances of AVAssetWriter can also optionally write metadata collections to the output file.
 
	A single instance of AVAssetWriter can be used once to write to a single file. Clients that wish to write to files multiple times must use a new instance of AVAssetWriter each time.
 */
API_AVAILABLE(macos(10.7), ios(4.1), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAssetWriter : NSObject
{
@private
	AVAssetWriterInternal	*_internal;
}
AV_INIT_UNAVAILABLE

/*!
 @method assetWriterWithURL:fileType:error:
 @abstract
	Returns an instance of AVAssetWriter configured to write to a file in a specified container format.
 
 @param URL
	The location of the file to be written. The URL must be a file URL.
 @param fileType
	A UTI indicating the format of the file to be written.
 @param outError
	On return, if initialization of the AVAssetWriter fails, points to an NSError describing the nature of the failure.
 @result
	An instance of AVAssetWriter.
 
 @discussion
	Writing will fail if a file already exists at the specified URL.
	
	UTIs for container formats that can be written are declared in AVMediaFormat.h.
 */
+ (nullable instancetype)assetWriterWithURL:(NSURL *)outputURL fileType:(AVFileType)outputFileType error:(NSError * _Nullable * _Nullable)outError;

/*!
 @method initWithURL:fileType:error:
 @abstract
	Creates an instance of AVAssetWriter configured to write to a file in a specified container format.
 
 @param URL
	The location of the file to be written. The URL must be a file URL.
 @param fileType
	A UTI indicating the format of the file to be written.
 @param outError
	On return, if initialization of the AVAssetWriter fails, points to an NSError describing the nature of the failure.
 @result
	An instance of AVAssetWriter.
 
 @discussion
	Writing will fail if a file already exists at the specified URL.
	
	UTIs for container formats that can be written are declared in AVMediaFormat.h.
 */
- (nullable instancetype)initWithURL:(NSURL *)outputURL fileType:(AVFileType)outputFileType error:(NSError * _Nullable * _Nullable)outError NS_DESIGNATED_INITIALIZER;

/*!
 @method initWithContentType:
 @abstract
	Creates an instance of AVAssetWriter configured to output segment data in a specified container format.

 @param outputContentType
	A UTType indicating the format of the segment data to be output.
 @result
	An instance of AVAssetWriter.

 @discussion
	Clients that want to receive segment data through the -assetWriter:didOutputSegmentData:segmentType:segmentReport: or -assetWriter:didOutputSegmentData:segmentType: delegate method should use this initializer instead of -initWithURL:fileType:error:.

	Clients may use +typeWithIdentifier: with a UTI to create an instance of UTType. See <UniformTypeIdentifiers/UTType.h>.

	UTIs for container formats that can be output are declared in AVMediaFormat.h.
 */
- (instancetype)initWithContentType:(UTType *)outputContentType NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property outputURL
 @abstract
	The location of the file for which the instance of AVAssetWriter was initialized for writing.
 @discussion
	You may use UTTypeCopyPreferredTagWithClass(outputFileType, kUTTagClassFilenameExtension) to obtain an appropriate path extension for the outputFileType you have specified. For more information about UTTypeCopyPreferredTagWithClass and kUTTagClassFilenameExtension, on iOS see <CoreServices/UTType.h> and on Mac OS X see <LaunchServices/UTType.h>.
 */
@property (nonatomic, copy, readonly) NSURL *outputURL;

/*!
 @property outputFileType
 @abstract
	The UTI of the file format of the file for which the instance of AVAssetWriter was initialized for writing.
 */
@property (nonatomic, copy, readonly) AVFileType outputFileType;

/*!
 @property availableMediaTypes
 @abstract
	The media types for which inputs can be added to the receiver.

 @discussion
	Some media types may not be accepted within the file format with which an AVAssetWriter was initialized.
 */
@property (nonatomic, readonly) NSArray<AVMediaType> *availableMediaTypes;

/*!
 @property status
 @abstract
	The status of writing samples to the receiver's output file.

 @discussion
	The value of this property is an AVAssetWriterStatus that indicates whether writing is in progress, has completed successfully, has been canceled, or has failed. Clients of AVAssetWriterInput objects should check the value of this property after appending samples fails to determine why no more samples could be written. This property is thread safe.
 */
@property (readonly) AVAssetWriterStatus status;

/*!
 @property error
 @abstract
	If the receiver's status is AVAssetWriterStatusFailed, this describes the error that caused the failure.

 @discussion
	The value of this property is an NSError that describes what caused the receiver to no longer be able to write to its output file. If the receiver's status is not AVAssetWriterStatusFailed, the value of this property is nil. This property is thread safe.
 */
@property (readonly, nullable) NSError *error;

/*!
 @property metadata
 @abstract
	A collection of metadata to be written to the receiver's output file.

 @discussion
	The value of this property is an array of AVMetadataItem objects representing the collection of top-level metadata to be written in the output file.
	
	This property cannot be set after writing has started.
 */
@property (nonatomic, copy) NSArray<AVMetadataItem *> *metadata;

/*!
 @property shouldOptimizeForNetworkUse
 @abstract
	Specifies whether the output file should be written in way that makes it more suitable for playback over a network
 
 @discussion
	When the value of this property is YES, the output file will be written in such a way that playback can start after only a small amount of the file is downloaded.
	
	This property cannot be set after writing has started.
 */
@property (nonatomic) BOOL shouldOptimizeForNetworkUse;

/*!
 @property directoryForTemporaryFiles
 @abstract 
	Specifies a directory that is suitable for containing temporary files generated during the process of writing an asset.
 
 @discussion
	AVAssetWriter may need to write temporary files when configured in certain ways, such as when performsMultiPassEncodingIfSupported is set to YES on one or more of its inputs.  This property can be used to control where in the filesystem those temporary files are created.  All temporary files will be deleted when asset writing is completed, is canceled, or fails.
 
	When the value of this property is nil, the asset writer will choose a suitable location when writing temporary files.  The default value is nil.
	
	This property cannot be set after writing has started.  The asset writer will fail if a file cannot be created in this directory (for example, due to insufficient permissions).
 */
@property (nonatomic, copy, nullable) NSURL *directoryForTemporaryFiles API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property inputs
 @abstract
	The inputs from which the asset writer receives media data.
 @discussion
	The value of this property is an NSArray containing concrete instances of AVAssetWriterInput. Inputs can be added to the receiver using the addInput: method.
 */
@property (nonatomic, readonly) NSArray<AVAssetWriterInput *> *inputs;

/*!
 @method canApplyOutputSettings:forMediaType:
 @abstract
	Tests whether output settings for a specific media type are supported by the receiver's file format.

 @param outputSettings
	The output settings that are to be tested.
 @param mediaType
	The media type for which the output settings are to be tested. Media types are defined in AVMediaFormat.h.
 @result
	A BOOL indicating whether the given output settings can be used for the given media type.
 
 @discussion
	This method determines whether the output settings for the specified media type can be used with the receiver's file format. For example, video compression settings that specify H.264 compression are not compatible with file formats that cannot contain H.264-compressed video.
 
	Attempting to add an input with output settings and a media type for which this method returns NO will cause an exception to be thrown.
*/
- (BOOL)canApplyOutputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings forMediaType:(AVMediaType)mediaType;

/*!
 @method canAddInput:
 @abstract
	Tests whether an input can be added to the receiver.

 @param input
	The AVAssetWriterInput object to be tested.
 @result
	A BOOL indicating whether the input can be added to the receiver.

 @discussion
	An input that accepts media data of a type that is not compatible with the receiver, or with output settings that are not compatible with the receiver, cannot be added.
 */
- (BOOL)canAddInput:(AVAssetWriterInput *)input;

/*!
 @method addInput:
 @abstract
	Adds an input to the receiver.

 @param input
	The AVAssetWriterInput object to be added.

 @discussion
	Inputs are created with a media type and output settings. These both must be compatible with the receiver.
	
	Inputs cannot be added after writing has started.
 */
- (void)addInput:(AVAssetWriterInput *)input;

/*!
 @method startWriting
 @abstract
	Prepares the receiver for accepting input and for writing its output to its output file.

 @result
	A BOOL indicating whether writing successfully started.
 
 @discussion
	This method must be called after all inputs have been added and other configuration properties have been set in order to tell the receiver to prepare for writing. After this method is called, clients can start writing sessions using startSessionAtSourceTime: and can write media samples using the methods provided by each of the receiver's inputs.
 
	If writing cannot be started, this method returns NO. Clients can check the values of the status and error properties for more information on why writing could not be started.
 
	On iOS, if the status of an AVAssetWriter is AVAssetWriterStatusWriting when the client app goes into the background, its status will change to AVAssetWriterStatusFailed and appending to any of its inputs will fail.  You may want to use -[UIApplication beginBackgroundTaskWithExpirationHandler:] to avoid being interrupted in the middle of a writing session and to finish writing the data that has already been appended.  For more information about executing code in the background, see the iOS Application Programming Guide.
 */
- (BOOL)startWriting;

/*!
 @method startSessionAtSourceTime:
 @abstract
	Initiates a sample-writing session for the receiver.
 
 @param startTime
	The starting asset time for the sample-writing session, in the timeline of the source samples.

 @discussion
	Sequences of sample data appended to the asset writer inputs are considered to fall within "sample-writing sessions", initiated with this method. Accordingly, this method must be called after writing has started (using -startWriting) but before any sample data is appended to the receiver's inputs.
	
	Each writing session has a start time which, where allowed by the file format being written, defines the mapping from the timeline of source samples to the timeline of the written file. In the case of the QuickTime movie file format, the first session begins at movie time 0, so a sample appended with timestamp T will be played at movie time (T-startTime).  Samples with timestamps earlier than startTime will still be added to the output file but will be edited out (i.e. not presented during playback). If the earliest appended sample for an input has a timestamp later than than startTime, an empty edit will be inserted to preserve synchronization between tracks of the output asset.
	
	To end the session started by use of this method, use -endSessionAtSourceTime: or -finishWritingWithCompletionHandler:.  It is an error to invoke -startSessionAtSourceTime: twice in a row without invoking -endSessionAtSourceTime: in between.
 
	NOTE: Multiple sample-writing sessions are currently not supported. It is an error to call -startSessionAtSourceTime: a second time after calling -endSessionAtSourceTime:.
 */
- (void)startSessionAtSourceTime:(CMTime)startTime;

/*!
 @method endSessionAtSourceTime:
 @abstract
	Concludes a sample-writing session.

 @param endTime
	The ending asset time for the sample-writing session, in the timeline of the source samples.

 @discussion
	Call this method to complete a session started with -startSessionAtSourceTime:.
 
	The endTime defines the moment on the timeline of source samples at which the session ends. In the case of the QuickTime movie file format, each sample-writing session's startTime...endTime pair corresponds to a period of movie time into which the session's samples are inserted. Samples with timestamps that are later than the session end time will still be added to the written file but will be edited out (i.e. not presented during playback). So if the first session has duration D1 = endTime - startTime, it will be inserted into the written file at time 0 through D1; the second session would be inserted into the written file at time D1 through D1+D2, etc. It is legal to have a session with no samples; this will cause creation of an empty edit of the prescribed duration.
	
	It is not mandatory to call -endSessionAtSourceTime:; if -finishWritingWithCompletionHandler: is called without first invoking -endSessionAtSourceTime:, the session's effective end time will be the latest end timestamp of the session's appended samples (i.e. no samples will be edited out at the end).
 
	It is an error to append samples outside of a sample-writing session.  To append more samples after invoking -endSessionAtSourceTime:, you must first start a new session using -startSessionAtSourceTime:.
	
	NOTE: Multiple sample-writing sessions are currently not supported. It is an error to call -startSessionAtSourceTime: a second time after calling -endSessionAtSourceTime:.
 */
- (void)endSessionAtSourceTime:(CMTime)endTime;

/*!
 @method cancelWriting
 @abstract
	Cancels the creation of the output file.
 
 @discussion
	If the status of the receiver is "failed" or "completed," -cancelWriting is a no-op.  Otherwise, this method will block until writing is canceled.
 
	If an output file was created by the receiver during the writing process, -cancelWriting will delete the file.
	
	This method should not be called concurrently with -[AVAssetWriterInput appendSampleBuffer:] or -[AVAssetWriterInputPixelBufferAdaptor appendPixelBuffer:withPresentationTime:].
*/
- (void)cancelWriting;

/*!
 @method finishWriting
 @abstract
	Completes the writing of the output file.
 
 @result
	A BOOL indicating whether writing successfully finished.
 
 @discussion
	This method is deprecated.  Use finishWritingWithCompletionHandler: instead.

	This method will block until writing is finished. When this method returns successfully, the file being written by the receiver is complete and ready to use.

	Because this method is blocking and can take a long time to execute (especially with shouldOptimizeForNetworkUse set to YES), it should not be called from the main thread.  Doing so can cause the finishWriting operation to fail.

	If writing cannot be finished, this method returns NO. Clients can check the values of the status and error properties for more information on why writing could not be finished.
	
	This method should not be called concurrently with -[AVAssetWriterInput appendSampleBuffer:] or -[AVAssetWriterInputPixelBufferAdaptor appendPixelBuffer:withPresentationTime:].
*/
- (BOOL)finishWriting API_DEPRECATED("No longer supported", macos(10.7, 10.9), ios(4.1, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
 @method finishWritingWithCompletionHandler:
 @abstract
	Marks all unfinished inputs as finished and completes the writing of the output file.

 @discussion
	This method returns immediately and causes its work to be performed asynchronously.
	
	When the writing of the output file is finished, or if a failure or a cancellation occurs in the meantime, the specified handler will be invoked to indicate completion of the operation. To determine whether the operation succeeded, your handler can check the value of AVAssetWriter.status. If the status is AVAssetWriterStatusFailed, AVAsset.error will contain an instance of NSError that describes the failure.
	
	To guarantee that all sample buffers are successfully written, ensure all calls to -[AVAssetWriterInput appendSampleBuffer:] or -[AVAssetWriterInputPixelBufferAdaptor appendPixelBuffer:withPresentationTime:] have returned before invoking this method.
*/
- (void)finishWritingWithCompletionHandler:(void (^)(void))handler API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end


@interface AVAssetWriter (AVAssetWriterFileTypeSpecificProperties)

/*!
 @property movieFragmentInterval
 @abstract
	For file types that support movie fragments, specifies the frequency at which movie fragments should be written.
 
 @discussion
	When movie fragments are used, a partially written asset whose writing is unexpectedly interrupted can be successfully opened and played up to multiples of the specified time interval. The default value of this property is kCMTimeInvalid, which indicates that movie fragments should not be used.

	This property cannot be set after writing has started.
 */
@property (nonatomic) CMTime movieFragmentInterval;

/*!
 @property initialMovieFragmentSequenceNumber
 @abstract
	For file types that support movie fragments, specifies the initial movie fragment sequence number.

 @discussion
	The value must be equal to or greater than 1.

	The default value is 1.

	Note that if you combine movie fragments produced by an instance of AVAssetWriter with additional movie fragments, produced either by a different instance of AVAssetWriter or by some other means, it is necessary to ensure that movie fragment sequence numbers increase monotonically across the entire combined collection, in temporal order.

	This property cannot be set after writing has started.
 */
@property (nonatomic) NSInteger initialMovieFragmentSequenceNumber API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property producesCombinableFragments
 @abstract
	For file types that support fragmented MPEG-4, specifies whether the movie fragments should be produced in way that makes them suitable for combining with movie fragments produced by one or more other instances of AVAssetWriter into a single fragment stream of uniform encoding.

 @discussion
	The default value is NO.

	When multiple instances of AVAssetWriter are used to produce distinct streams that complement each other, for example to create HLS encoding or bitrate variants, it’s not necessary to set this property to YES.

	This property cannot be set after writing has started.
 */
@property (nonatomic) BOOL producesCombinableFragments API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property overallDurationHint
 @abstract
	For file types that support movie fragments, provides a hint of the final duration of the file to be written
 
 @discussion
	The value of this property must be a nonnegative, numeric CMTime.  Alternatively, if the value of this property is an invalid CMTime (e.g. kCMTimeInvalid), no overall duration hint will be written to the file.  The default value is kCMTimeInvalid.
 
	This property is currently ignored if movie fragments are not being written.  Use the movieFragmentInterval property to enable movie fragments.
 
	This property cannot be set after writing has started.
 */
@property (nonatomic) CMTime overallDurationHint;

/*!
 @property movieTimeScale
 @abstract
	For file types that contain a 'moov' atom, such as QuickTime Movie files, specifies the asset-level time scale to be used. 

 @discussion
	The default value is 0, which indicates that the receiver should choose a convenient value, if applicable.
 
	This property cannot be set after writing has started.
 */
@property (nonatomic) CMTimeScale movieTimeScale API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0)) API_UNAVAILABLE(watchos);

@end


@class AVAssetWriterInputGroup;

@interface AVAssetWriter (AVAssetWriterInputGroups)

/*!
 @method canAddInputGroup:
 @abstract
	Tests whether an input group can be added to the receiver.

 @param inputGroup
	The AVAssetWriterInputGroup object to be tested.
 @result
	A BOOL indicating whether the input group can be added to the receiver.

 @discussion
	If outputFileType specifies a container format that does not support mutually exclusive relationships among tracks, or if the specified instance of AVAssetWriterInputGroup contains inputs with media types that cannot be related, the group cannot be added to the AVAssetWriter.
 */
- (BOOL)canAddInputGroup:(AVAssetWriterInputGroup *)inputGroup API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*
 @method addInputGroup:
 @abstract
	Adds an instance of AVAssetWriterInputGroup to the AVAssetWriter.  The AVAssetWriter will mark the tracks associated with grouped inputs as mutually exclusive to each other for playback or other processing, if the output container format supports mutually exlusive relationships among tracks.

 @param inputGroup
	The collection of AVAssetWriterInputs to be grouped together.
 
 @discussion
	When an input group is added to an AVAssetWriter, the value of marksOutputTrackAsEnabled will automatically be set to YES for the default input and set to NO for all of the other inputs in the group.

	Input groups cannot be added after writing has started.
 */
- (void)addInputGroup:(AVAssetWriterInputGroup *)inputGroup API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property inputGroups
 @abstract
	The instances of AVAssetWriterInputGroup that have been added to the AVAssetWriter.
 
 @discussion
	The value of this property is an NSArray containing concrete instances of AVAssetWriterInputGroup.  Input groups can be added to the receiver using the addInputGroup: method.
 */
@property (nonatomic, readonly) NSArray<AVAssetWriterInputGroup *> *inputGroups API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end


@class AVAssetWriterInputGroupInternal;

/*
 @class AVAssetWriterInputGroup
 @abstract Associates tracks corresponding to inputs with each other in a mutually exclusive relationship.

 @discussion
	This class is used to associate tracks corresponding to multiple AVAssetWriterInputs as mutually exclusive to each other for playback or other processing.  For example, if you are creating an asset with multiple audio tracks using different spoken languages, only one of which should be played at a time, group the inputs corresponding to those tracks into a single instance of AVAssetWriterInputGroup and add the group to the AVAssetWriter via -[AVAssetWriter addInputGroup:].  If the output format supports mutually exlusive relationships among tracks, the AVAssetWriter will mark the tracks as mutually exclusive to each other.
 
	Note that because AVAssetWriterInputGroup is a subclass of AVMediaSelectionGroup, clients can examine the media selection options that will be available on the output asset before the asset is written.  Best results for examining the options of the AVAssetWriterInputGroup will be obtained after associating the AVAssetWriterInputs of the AVAsset as appropriate via -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:] and by initializing each AVAssetWriterInput with a source format hint, where appropriate.
 */

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAssetWriterInputGroup : AVMediaSelectionGroup
{
@private
    AVAssetWriterInputGroupInternal	*_internal;
}
AV_INIT_UNAVAILABLE

/*
 @method assetWriterInputGroupWithInputs:defaultInput:
 @abstract
	Creates an instance of AVAssetWriterInputGroup, for use with -[AVAssetWriter addInputGroup:].

 @param inputs
	The collection of AVAssetWriterInputs to be grouped together.
 @param defaultInput
	The instance of AVAssetWriterInput in the group to designate as the default.  When the input group is added to an AVAssetWriter via -addInputGroup:, the value of marksOutputTrackAsEnabled will automatically be set to YES for the default input and set to NO for all of the other inputs in the group.
 @result
	An instance of AVAssetWriterInputGroup, for use with -[AVAssetWriter addInputGroup:].
 */
+ (instancetype)assetWriterInputGroupWithInputs:(NSArray<AVAssetWriterInput *> *)inputs defaultInput:(nullable AVAssetWriterInput *)defaultInput;

/*
 @method initWithInputs:defaultInput:
 @abstract
	Creates an instance of AVAssetWriterInputGroup, for use with -[AVAssetWriter addInputGroup:].

 @param inputs
	The collection of AVAssetWriterInputs to be grouped together.
 @param defaultInput
	The instance of AVAssetWriterInput in the group to designate as the default.  When the input group is added to an AVAssetWriter via -addInputGroup:, the value of marksOutputTrackAsEnabled will automatically be set to YES for the default input and set to NO for all of the other inputs in the group.
 @result
	An instance of AVAssetWriterInputGroup, for use with -[AVAssetWriter addInputGroup:].
 */
- (instancetype)initWithInputs:(NSArray<AVAssetWriterInput *> *)inputs defaultInput:(nullable AVAssetWriterInput *)defaultInput NS_DESIGNATED_INITIALIZER;

/*!
 @property inputs
 @abstract
	The inputs grouped together by the receiver.
 
 @discussion
	The value of this property is an NSArray containing concrete instances of AVAssetWriterInput.
 */
@property (nonatomic, readonly) NSArray<AVAssetWriterInput *> *inputs;

/*!
 @property defaultInput
 @abstract
	The input designated at the defaultInput of the receiver.
 
 @discussion
	The value of this property is a concrete instance of AVAssetWriterInput.
 */
@property (nonatomic, readonly, nullable) AVAssetWriterInput *defaultInput;

@end


@protocol AVAssetWriterDelegate;

@interface AVAssetWriter (AVAssetWriterSegmentation)

/*!
 @property preferredOutputSegmentInterval
 @abstract
	Specifies preferred segment interval.

 @discussion
	The default value is kCMTimeInvalid, which means that the receiver will choose an appropriate default value. The value can be set to positive numeric or kCMTimeIndefinite.
	If the value is kCMTimeIndefinite, every time a client calls -flushSegment the receiver outputs a segment data.

	This property cannot be set after writing has started.
 */
@property (nonatomic) CMTime preferredOutputSegmentInterval API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property initialSegmentStartTime
 @abstract
	Specifies start time of initial segment.

 @discussion
	A numeric time must be set if the value of preferredOutputSegmentInterval property is positive numeric. If not, this property is irrelevant.

	This property cannot be set after writing has started.
 */
@property (nonatomic) CMTime initialSegmentStartTime API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property outputFileTypeProfile
 @abstract
	Specifies a file type profile for the specified file type.

 @discussion
	The default value is nil, which means that the receiver will choose an appropriate default profile based on the specified file type.

	Clients that want to receive segment data that is suitable for streaming through the -assetWriter:didOutputSegmentData:segmentType:segmentReport: or -assetWriter:didOutputSegmentData:segmentType: delegate method should set AVFileTypeProfileMPEG4AppleHLS, or AVFileTypeProfileMPEG4CMAFCompliant to require output that is specifically compliant with CMAF format, with AVFileTypeMPEG4 file type.

	File type profiles are declared in AVMediaFormat.h.

	This property cannot be set after writing has started.
 */

@property (nonatomic, copy, nullable) AVFileTypeProfile outputFileTypeProfile API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property delegate
 @abstract
	An object that implements one or more of the methods in the AVAssetWriterDelegate protocol.

 @discussion
	This property cannot be set after writing has started.
 */
@property (weak, nullable) id <AVAssetWriterDelegate> delegate API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @method flushSegment
 @abstract
	Closes the current segment and outputs it to the -assetWriter:didOutputSegmentData:segmentType:segmentReport: or -assetWriter:didOutputSegmentData:segmentType: delegate method.

 @discussion
	Use this method only when the value of preferredOutputSegmentInterval property is set to kCMTimeIndefinite.
 */
- (void)flushSegment API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos)
@protocol AVAssetWriterDelegate <NSObject>
@optional

/*!
 @method assetWriter:didOutputSegmentData:segmentType:segmentReport:
 @abstract
	A method invoked when a segment data is output.

 @param writer
	An AVAssetWriter instance.
 @param segmentData
	An instance of NSData containing a segment data.
 @param segmentType
	A segment type of the segment data. Segment types are declared in AVAssetSegmentReport.h.
 @param segmentReport
	An AVAssetSegmentReport instance.

 @discussion
	If this method is implemented, normal file writing will be suppressed. The instance of AVAssetWriter must be initialized by -initWithContentType: initializer.
	Then, clients append media data to AVAssetWriterInputs added to the receiver, call -markAsFinished for each input to mark the input as finished and call -finishWritingWithCompletionHandler: to finish writing as is the case in normal file writing.

	Do not use the movieFragmentInterval or shouldOptimizeForNetworkUse properties, as these properties are ignored in this mode of operation.

	Clients that need to reference the NSData outside of the scope of this method must retain or copy it and then release it when they are finished with it.

	The segmentReport provides information on the segment data. If there is no information available to report, the segmentReport may be nil.
	Clients that do not need information on consecutive segment data should implement the -assetWriter:didOutputSegmentData:segmentType: method instead of this one for greater efficiency, as this will signal the receiver to skip the preparation of segment reports.
	See more detailed description of AVAssetSegmentReport in AVAssetSegmentReport.h.

	If the file type is AVFileTypeMPEG4 and the outputFileTypeProfile is AVFileTypeProfileMPEG4AppleHLS or AVFileTypeProfileMPEG4CMAFCompliant, when the segmentType is AVAssetSegmentTypeInitialization, the segment contains a 'moov' atom that does not contain any sample tables other than the sample descriptions, and is suitable for use as an initialization segment for the following segment data sequences.
	When the segmentType is AVAssetSegmentTypeSeparable, the segment contains a 'moof' atom  that contains one 'moof' atom followed by one 'mdat' atom.

	1. If the value of preferredOutputSegmentInterval property is positive numeric, when (a sample's output PTS - InitialSegmentStartTime) >= (interval * N) (N = 1, 2, 3...), the receiver waits for next sync sample and outputs a segment data that includes all samples appended since the previous interval to the delegate method when the sync sample appears, so that the next segment can start with the sync sample.
	In this configuration, passthrough (by passing nil to output settings for AVAssetWriterInputs) and compression are available. The media type of input can be AVMediaTypeVideo or AVMediaTypeAudio.
	Only one input of each media type can be added for compression and when (a sample's PTS - InitialSegmentStartTime) >= (interval * N) (N = 1, 2, 3...), the sample will be forced to be encoded as sync sample so that the current segment will be closed immediately.
	For passthrough, only one input can be added.

	2. If the value of preferredOutputSegmentInterval property is kCMTimeIndefinite, every time a client calls -flushSegment the receiver outputs a segment data that includes all samples appended since the previous call to the delegate method.
	The delegate method may be called asynchronously, on a different thread from the one that calls -flushSegment.
	In this configuration, only passthrough is available. The media type of input can be AVMediaTypeVideo or AVMediaTypeAudio.
	Only one input of each media type can be added.
	The client should call -flushSegment prior to a sync sample so that the next segment can start with the sync sample. Otherwise, it is an error.
 */
- (void)assetWriter:(AVAssetWriter *)writer didOutputSegmentData:(NSData *)segmentData segmentType:(AVAssetSegmentType)segmentType segmentReport:(nullable AVAssetSegmentReport *)segmentReport;

/*!
 @method assetWriter:didOutputSegmentData:segmentType:
 @abstract
	A method invoked when a segment data is output.

 @param writer
	An AVAssetWriter instance.
 @param segmentData
	An instance of NSData containing a segment data.
 @param segmentType
	A segment type of the segment data. Segment types are declared in AVAssetSegmentReport.h.

 @discussion
	The usage of this method is same as -assetWriter:didOutputSegmentData:segmentType:segmentReport: except that this method does not deliver AVAssetSegmentReport.

	If clients implement the -assetWriter:didOutputSegmentData:segmentType:segmentReport: method, that method is called instead of this one.
 */
- (void)assetWriter:(AVAssetWriter *)writer didOutputSegmentData:(NSData *)segmentData segmentType:(AVAssetSegmentType)segmentType;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetWriter.h>
#endif
