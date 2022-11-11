#if !__has_include(<AVFCore/AVSampleBufferGenerator.h>)
/*
	File:  AVSampleBufferGenerator.h

	Framework:  AVFoundation
 
	Copyright 2014-2018 Apple Inc. All rights reserved.

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
*/
@class AVSampleBufferRequest;

@class AVSampleBufferGeneratorInternal;

API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos)
@interface AVSampleBufferGenerator : NSObject {
@private
	AVSampleBufferGeneratorInternal	*_generator;
}
AV_INIT_UNAVAILABLE

/* If timebase is NULL, requests will be handled synchronously. */
- (instancetype)initWithAsset:(AVAsset *)asset timebase:(nullable CMTimebaseRef)timebase NS_DESIGNATED_INITIALIZER;

/* It is an error to use an AVSampleBufferRequest with mode set to AVSampleBufferRequestModeScheduled when the AVSampleBufferGenerator was created with a NULL timebase. */
- (nullable CMSampleBufferRef)createSampleBufferForRequest:(AVSampleBufferRequest *)request CF_RETURNS_RETAINED;

/* completionHandler is called when data is ready or as soon as an error has occurred. */
+ (void)notifyOfDataReadyForSampleBuffer:(CMSampleBufferRef)sbuf completionHandler:(void (^)(BOOL dataReady, NSError *error))completionHandler;

@end

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
API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos)
@interface AVSampleBufferRequest : NSObject {
@private
	AVSampleBufferRequestInternal	*_request;
}
AV_INIT_UNAVAILABLE

- (instancetype)initWithStartCursor:(AVSampleCursor *)startCursor NS_DESIGNATED_INITIALIZER;

/* mandatory: the created CMSampleBuffer must include the sample at this position */
@property (nonatomic, retain, readonly) AVSampleCursor *startCursor;

/* If AVSampleBufferRequestDirectionNone, only one sample will be loaded and limitCursor, preferredMinSampleCount, and maxSampleCount will be ignored.
   If AVSampleBufferRequestDirectionForward, zero or more following samples may be included, subject to limitCursor, preferredMinSampleCount, and maxSampleCount.
   If AVSampleBufferRequestDirectionReverse, zero or more preceeding samples may be included, subject to limitCursor, preferredMinSampleCount, and maxSampleCount.
   Default is AVSampleBufferRequestDirectionNone. */
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

#pragma pack(pop)

NS_ASSUME_NONNULL_END


#else
#import <AVFCore/AVSampleBufferGenerator.h>
#endif
