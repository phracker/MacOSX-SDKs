/*
	File:  AVSampleBufferGenerator.h

	Framework:  AVFoundation
 
	Copyright 2014-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVSampleCursor.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMSync.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#if ! TARGET_OS_IPHONE

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

NS_CLASS_AVAILABLE_MAC(10_10)
@interface AVSampleBufferGenerator : NSObject {
@private
	AVSampleBufferGeneratorInternal	*_generator;
}
AV_INIT_UNAVAILABLE

/* If timebase is NULL, requests will be handled synchronously. */
- (instancetype)initWithAsset:(AVAsset *)asset timebase:(nullable CMTimebaseRef)timebase NS_DESIGNATED_INITIALIZER;

/* It is an error to use an AVSampleBufferRequest with mode set to AVSampleBufferRequestModeScheduled when the AVSampleBufferGenerator was created with a NULL timebase. */
- (CMSampleBufferRef)createSampleBufferForRequest:(AVSampleBufferRequest *)request CF_RETURNS_RETAINED;

/* completionHandler is called when data is ready or as soon as an error has occurred. */
+ (void)notifyOfDataReadyForSampleBuffer:(CMSampleBufferRef)sbuf completionHandler:(void (^)(BOOL dataReady, NSError *error))completionHandler;

@end

/*!
	@class		AVSampleBufferRequest

	@abstract	An AVSampleBufferRequest describes a CMSampleBuffer creation request.
*/
typedef NS_ENUM(NSInteger, AVSampleBufferRequestDirection) {
	AVSampleBufferRequestDirectionForward = +1,
	AVSampleBufferRequestDirectionNone = 0,
	AVSampleBufferRequestDirectionReverse = -1,
};

typedef NS_ENUM(NSInteger, AVSampleBufferRequestMode) {
	AVSampleBufferRequestModeImmediate,
	AVSampleBufferRequestModeScheduled,
};

@class AVSampleBufferRequestInternal;

NS_CLASS_AVAILABLE_MAC(10_10)
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

/* If AVSampleBufferRequestModeImmediate, sample data shall be loaded as soon as possible. 
   If AVSampleBufferRequestModeScheduled, sample data shall be scheduled with deadline equal to overrideTime if set, or based on DTS or PTS time of the CMSampleBuffer if overrideTime is not set.
   Default is AVSampleBufferRequestModeImmediate. */
@property (nonatomic, assign) AVSampleBufferRequestMode mode;

/* optional: indicates deadline for sample data and output PTS for CMSampleBuffer. */
@property (nonatomic, assign) CMTime overrideTime;

@end

#pragma pack(pop)

#endif // ! TARGET_OS_IPHONE

NS_ASSUME_NONNULL_END

