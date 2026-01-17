#if !__has_include(<AVFCore/AVSampleBufferGenerator.h>)
/*
	File:  AVSampleBufferGenerator.h

	Framework:  AVFoundation
 
	Copyright 2014-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVSampleCursor.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMSync.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma pack(push)
#pragma pack()

/*!
	@class		AVSampleBufferGenerator

	@abstract	An AVSampleBufferGenerator creates CMSampleBuffers.
	@discussion
		Each request for CMSampleBuffer creation is described in an AVSampleBufferRequest object.
		CMSampleBuffers are returned synchronously.
		If requested, sample data may be loaded asynchronously (depending on file format support).
		Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
@class AVSampleBufferRequest;

@class AVSampleBufferGeneratorBatch;

@class AVSampleBufferGeneratorInternal;

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.10), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0))
@interface AVSampleBufferGenerator : NSObject {
@private
	AVSampleBufferGeneratorInternal	*_generator;
}
AV_INIT_UNAVAILABLE

/*!
  @method		initWithAsset: timebase:
  @abstract		Creates an instance of AVSampleBufferGenerator to generate sample buffers from the specified asset.
  @param 		asset
				The asset from which sample buffers will be created.
  @param 		timebase
				The generator timebase, which governs when sample data for sample buffers is loaded. If NULL, sample data is loaded synchronously.
  @result		An instance of AVSampleBufferGenerator.
  @discussion	If the specified asset is an HTTP Live Streaming asset, the generator cannot create sample buffers.
*/
- (instancetype)initWithAsset:(AVAsset *)asset timebase:(nullable CMTimebaseRef)timebase NS_DESIGNATED_INITIALIZER;

/*!
 @method		createSampleBufferForRequest: error:
 @abstract		Creates a sample buffer and if requested, attempts to load its data asynchronously. Attempt may fail based on generator configuration or file format.
				See [AVSampleBufferGenerator notifyOfDataReadyForSampleBuffer: completionHandler:] to get notified when the sample buffer data is available.
  @param		request
				An instance of AVSampleBufferRequest representing the CMSampleBuffer creation request.
  @param		outError
				A pointer to an NSError object that will be populated with failure information, if sample buffer creation fails.
  @result		A CMSampleBuffer object referencing the output sample buffer.
  @discussion	If the AVSampleBufferGenerator was created with a NULL timebase, any associated AVSampleBufferRequest will default to using AVSampleBufferRequestModeImmediate.
*/
- (nullable CMSampleBufferRef)createSampleBufferForRequest:(AVSampleBufferRequest *)request error:(NSError * _Nullable * _Nullable)outError CF_RETURNS_RETAINED API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0)) NS_SWIFT_NAME(makeSampleBuffer(for:)) NS_SWIFT_SENDING;

/* It is an error to use an AVSampleBufferRequest with mode set to AVSampleBufferRequestModeScheduled when the AVSampleBufferGenerator was created with a NULL timebase. */
- (nullable CMSampleBufferRef)createSampleBufferForRequest:(AVSampleBufferRequest *)request CF_RETURNS_RETAINED API_DEPRECATED("Use -createSampleBufferForRequest: error:, passing NULL for the error if not required", macos(10.10, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
  @method		makeBatch
  @abstract		Creates a batch to handle multiple sample buffers, allowing to asynchronously load sample data and optimize I/O when possible.
  @result		An instance of an AVSampleBufferGeneratorBatch that can be used in calls to createSampleBufferForRequest:addingToBatch:error: of the same AVSampleBufferGenerator instance.
*/
- (AVSampleBufferGeneratorBatch *) makeBatch API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @method		createSampleBufferForRequest: addingToBatch: error:
  @abstract		Creates a sample buffer and attempts to defer I/O for its data. Attempt may fail based on generator configuration or file format.
				The [AVSampleBufferGeneratorBatch makeDataReadyWithCompletionHandler:] should be called once to commence I/O and load sample data for all CMSampleBuffers within a batch.
				Any subsequent calls to createSampleBufferForRequest:addingToBatch:error: will throw an exception.
  @param		request
				An instance of AVSampleBufferRequest representing the CMSampleBuffer creation request
  @param		batch
				An instance of AVSampleBufferGeneratorBatch to contain the output sample buffer. If nil, an exception is thrown.
				Must be created by calling makeBatch on the same instance of AVSampleBufferGenerator. An exception will be thrown otherwise.
  @param		outError
				A pointer to an NSError object that will be populated with failure information, if sample buffer creation fails.
  @result		A CMSampleBuffer object referencing the output sample buffer. The generator may defer I/O to fetch sample data depending on the source of the sample data and
				the generator's timebase.
*/
- (nullable CMSampleBufferRef)createSampleBufferForRequest:(AVSampleBufferRequest *)request addingToBatch: (AVSampleBufferGeneratorBatch *)batch error:(NSError * _Nullable * _Nullable)outError CF_RETURNS_RETAINED API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0)) NS_SWIFT_NAME(makeSampleBuffer(for:addTo:));

/*!
  @method		notifyOfDataReadyForSampleBuffer: completionHandler:
  @abstract		Allows the client to get notified when the sample buffer data is ready, or as soon as an error has occured.
  @param		completionHandler
				The completionHandler will be called, when the sample buffer data is ready, or as soon as an error has occurred.
*/

+ (void)notifyOfDataReadyForSampleBuffer:(CMSampleBufferRef)sbuf completionHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL dataReady, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

@end


/*!
 @enum AVSampleBufferRequestDirection
 @abstract
	Indicates the direction in which the samples should be generated for the AVSampleBufferRequest.
 
 @constant	AVSampleBufferRequestDirectionNone
	Indicates only one sample will be loaded at [AVSampleBufferRequest startCursor], and the [AVSampleBufferRequest limitCursor], [AVSampleBufferRequest preferredMinSampleCount], and [AVSampleBufferRequest maxSampleCount] will be ignored.
 @constant	AVSampleBufferRequestDirectionForward
	Indicates zero or more following samples may be loaded from [AVSampleBufferRequest startCursor], subject to [AVSampleBufferRequest limitCursor], [AVSampleBufferRequest preferredMinSampleCount], and [AVSampleBufferRequest maxSampleCount]
 @constant	AVSampleBufferRequestDirectionReverse
	Indicates zero or more preceeding samples may be loaded from [AVSampleBufferRequest startCursor], subject to [AVSampleBufferRequest limitCursor], [AVSampleBufferRequest preferredMinSampleCount], and [AVSampleBufferRequest maxSampleCount]*/
typedef NS_ENUM(NSInteger, AVSampleBufferRequestDirection) {
	AVSampleBufferRequestDirectionForward = +1,
	AVSampleBufferRequestDirectionNone = 0,
	AVSampleBufferRequestDirectionReverse = -1,
};



/*!
 @enum AVSampleBufferRequestMode
 @abstract
	Defines the allowed values for AVSampleBufferRequest's mode property.
 
 @constant	AVSampleBufferRequestModeImmediate
	Sample data for requests with AVSampleBufferRequestModeImmediate will be loaded as soon as possible. The current time represented by AVSampleBufferGenerator's timebase has no influence on these requests.
 @constant	AVSampleBufferRequestModeScheduled
	AVSampleBufferRequestModeScheduled indicates that a request is needed by the time AVSampleBufferGenerator's timebase reaches the CMSampleBuffer's presentationTime or, if specificed, AVSampleBufferRequest's overrideTime. The AVSampleBufferGenerator will attempt to deliver sample data with sufficient leeway for downstream processing. It will also attempt to hold off on loading data until the CMSampleBuffer is needed. If AVSampleBufferGenerator's timebase has a rate of zero, this mode behaves like AVSampleBufferRequestModeImmediate.
 @constant	AVSampleBufferRequestModeOpportunistic
 	The AVSampleBufferGenerator will attempt to read data for opportunistic requests as soon as possible. However, in situations with multiple competing requests, the AVSampleBufferGenerator may defer an opportunistic request in favor of another immediate request or a scheduled requests with a presentation time close to the timebase time. Because a request with AVSampleBufferRequestModeOpportunistic may be postponed indefinitely, this mode should not be used for time-sensitive processing.
*/
typedef NS_ENUM(NSInteger, AVSampleBufferRequestMode) {
	AVSampleBufferRequestModeImmediate = 0,
	AVSampleBufferRequestModeScheduled = 1,
	AVSampleBufferRequestModeOpportunistic = 2,
};

@class AVSampleBufferRequestInternal;

/*!
	@class		AVSampleBufferRequest
 
	@abstract	An AVSampleBufferRequest describes a CMSampleBuffer creation request.
 */
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.10), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0))
@interface AVSampleBufferRequest : NSObject {
@private
	AVSampleBufferRequestInternal	*_request;
}
AV_INIT_UNAVAILABLE

- (instancetype)initWithStartCursor:(AVSampleCursor *)startCursor NS_DESIGNATED_INITIALIZER;

/* mandatory: the created CMSampleBuffer must include the sample at this position */
@property (nonatomic, retain, readonly) AVSampleCursor *startCursor;

/* Default is AVSampleBufferRequestDirectionNone. */
@property (nonatomic, assign) AVSampleBufferRequestDirection direction;

/* optional: if not nil, the sequence of samples to be loaded may include the sample at this position, but no further. */
@property (nonatomic, retain,  nullable) AVSampleCursor *limitCursor;

/* optional: if not zero, indicates the preferred number of samples to load. Fewer samples may be loaded if there is a change of format description. */
@property (nonatomic, assign) NSInteger preferredMinSampleCount;

/* optional: if not zero, indicates the maximum number of samples to load. */
@property (nonatomic, assign) NSInteger maxSampleCount;

/* One of AVSampleBufferRequestMode*. This property is ignored when scheduling the request on an AVSampleBufferGenerator created with a NULL timebase. */
@property (nonatomic, assign) AVSampleBufferRequestMode mode;

/* optional: indicates deadline for sample data and output PTS for CMSampleBuffer. */
@property (nonatomic, assign) CMTime overrideTime;

@end

/*!
	@class		AVSampleBufferGeneratorBatch
 
	@abstract	An AVSampleBufferGeneratorBatch provides an optimized way to load sample data asynchronously for multiple CMSampleBuffers in an asset.
	@discussion
		The AVSampleBufferGeneratorBatch loads sample data asynchronously, by aggregating adjacent I/O requests and overlapping them when possible for all CMSampleBuffers within a batch.
		An AVSampleBufferGeneratorBatch is associated with an AVSampleBufferGenerator. See -[AVSampleBufferGenerator makeBatch] to create an AVSampleBufferGeneratorBatch.
		See -[AVSampleBufferGeneratorBatch createSampleBufferForRequest: addingToBatch: error:] to create a CMSampleBuffer, defer I/O for its data, and build up a batch.
		Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0))
@interface AVSampleBufferGeneratorBatch : NSObject

AV_INIT_UNAVAILABLE

/*!
  @method		makeDataReadyWithCompletionHandler:
  @abstract		Loads sample data asynchronously for all CMSampleBuffers within a batch.
				This can only be called once on a batch, an exception will be thrown otherwise.
  @param		completionHandler
				The completionHandler is called once, when all CMSampleBuffers in the batch are data-ready, or as soon as an error has occurred.
*/
- (void) makeDataReadyWithCompletionHandler: (void (^ NS_SWIFT_SENDABLE)(NSError * _Nullable error))completionHandler;

/*!
  @method		cancel
  @abstract		Attempt to cancel any I/O for this batch. The associated sample buffers will have their data ready handler invoked with an error.
*/
- (void) cancel;

@end

#pragma pack(pop)

NS_ASSUME_NONNULL_END


#else
#import <AVFCore/AVSampleBufferGenerator.h>
#endif
