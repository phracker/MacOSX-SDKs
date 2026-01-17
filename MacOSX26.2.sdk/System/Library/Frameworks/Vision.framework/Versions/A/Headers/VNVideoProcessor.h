//
//  VNVideoProcessor.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Vision/VNDefines.h>
#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>
#import <CoreMedia/CoreMedia.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief An object that defines the cadence at which the video stream is processed.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
NS_SWIFT_NAME(VNVideoProcessor.Cadence)
@interface VNVideoProcessorCadence : NSObject < NSCopying >
@end


/*!
	@brief An object that defines a frame-based cadence for processing the video stream.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
NS_SWIFT_NAME(VNVideoProcessor.FrameRateCadence)
@interface VNVideoProcessorFrameRateCadence : VNVideoProcessorCadence
- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithFrameRate:(NSInteger)frameRate NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(_:));
@property (readonly) NSInteger frameRate;
@end


/*!
	@brief An object that defines a time-based cadence for processing the video stream.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
NS_SWIFT_NAME(VNVideoProcessor.TimeIntervalCadence)
@interface VNVideoProcessorTimeIntervalCadence : VNVideoProcessorCadence
- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithTimeInterval:(CFTimeInterval)timeInterval NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(_:));
@property (readonly) CFTimeInterval timeInterval;
@end



/*!
	@abstract Options applied to a request's processing of the video.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
NS_SWIFT_NAME(VNVideoProcessor.RequestProcessingOptions)
@interface VNVideoProcessorRequestProcessingOptions : NSObject < NSCopying >

/*!
	@brief The cadence at which the request should be performed.
	@discussion If this property is not defined, then every frame will be processed.
*/
@property (readwrite, copy, nullable) VNVideoProcessorCadence* cadence;

@end




/*!
	@abstract	A controller object that is used to perform one or more requests on a video stream.
	@discussion	VNVideoProcessor handles the video decoding and buffer management, feeding the buffers to the associated requests at the best desired frame rate.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNVideoProcessor : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief Creates a VNVideoProcessor to be used for performing requests against a video asset specified by it's URL.

 @param videoURL A URL pointing at a video asset on which the requests will be performed. The video format has to be supported by AVFoundation.
*/
- (instancetype)initWithURL:(NSURL *)videoURL;


/*!
 @brief Add a VNRequest with the specified processing options to be performed on the video.
 @details This method can be called either before calling -analyzeTimeRange:error: or from within one of the already associated request's completion handlers.

 @param request The VNRequest to be added to the processing pipeline. If added from within a completionHandler, it will be processed on the same frame that is currently being processed.
 @param processingOptions The options applied to the request's processing of the video.
 @param error Returns an error that happened during scheduling of the requests. Check individual requests results and errors for their respective success and failures. This parameter is optional.
 @return Returns true if the request added to the processing pipeline.
 @note   The VNRequest must have completion handler set otherwise no results can be returned.
 */
- (BOOL)addRequest:(VNRequest *)request processingOptions:(VNVideoProcessorRequestProcessingOptions *)processingOptions error:(NSError **)error NS_SWIFT_NAME(addRequest(_:processingOptions:));
- (BOOL)addRequest:(VNRequest *)request withProcessingOptions:(NSDictionary<VNVideoProcessingOption, id>*)processingOptions error:(NSError **)error  API_DEPRECATED_WITH_REPLACEMENT("-addRequest:processingOptions:error:", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


/*!
 @brief Remove a VNRequest from the video processor, which means it won't be performed anymore.
 @details This method can be called either before calling -analyzeTimeRange:error: or from within one of the already associated request's completion handlers.
 
 @param request The VNRequest to be removed from the processing pipeline.
 @param error Returns an error that happened during processing of the request, such as if the request was not found in the processing queue. This parameter is optional.
 @return Returns true if the request was found and removed from the processing pipeline.
*/
- (BOOL)removeRequest:(VNRequest *)request error:(NSError **)error NS_SWIFT_NAME(removeRequest(_:));


/*!
 @brief Processes the video over the specified time range.
 @details This call is synchronous and only returns after the video is processed through its duration or an error prevented the processing.
 
 @param timeRange  Start and duration of the timerange within video to process. If the duration is longer than the video (e.g., kCMTimeIndefinite) the processing stops at the end of the video.
 @param error Returns an error that happened during the starting of the processing queue (for instance if the time range is not valid for the video asset). This parameter is optional.
 @return Returns true if all requests were scheduled and performed. Check individual requests results and errors for their respective success and failures.
 @note   The intersection of the CMTimeRangeMake(start, duration) and CMTimeRangeMake(kCMTimeZero, asset.duration) will determine the timerange of the video to process
 */
- (BOOL)analyzeTimeRange:(CMTimeRange)timeRange error:(NSError **)error;
- (BOOL)analyzeWithTimeRange:(CMTimeRange)timeRange error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("-analyzeTimeRange:error:", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


/*!
 @brief Cancel the processing of the video. This can return before the last request has completed.
 */
- (void)cancel;

@end


NS_ASSUME_NONNULL_END
