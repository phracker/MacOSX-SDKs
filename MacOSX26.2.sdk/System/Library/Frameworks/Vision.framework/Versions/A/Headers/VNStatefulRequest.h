//
//  VNStatefulRequest.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNRequestHandler.h>



NS_ASSUME_NONNULL_BEGIN

/*!
 @brief A request that builds evidence over time by being reused on multiple images.
 @discussion The request requires the use of CMSampleBuffers with timestamps as input; otherwise, a VNErrorTimeStampNotFound error will be returned. VNStatefulRequest is used as a base class of other requests, so no objects of this class should be created directly.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNStatefulRequest : VNImageBasedRequest

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;

/*!
 @brief Create a new video-based stateful request.
    
 @param frameAnalysisSpacing The reciprocal of maximum rate at which buffers will be processed. The request will not process buffers that fall within the frameAnalysisSpacing after it has performed the analysis. The analysis is not done by wall time but by analysis of of the time stamps of the samplebuffers being processed.
 @param completionHandler The block to be invoked after the request has completed its processing. The completion handler gets executed on the same dispatch queue as the request being executed.
*/
- (instancetype) initWithFrameAnalysisSpacing:(CMTime)frameAnalysisSpacing completionHandler:(nullable VNRequestCompletionHandler)completionHandler;

/*!
 @brief The minimum number of frames that the request has to process on before reporting back any observation. This information is provided by the request once initialized with its required paramters.
 @discussion Video based request often need a minimum number of frames before they can report back any observation. An example would be that a movement detection requires at least 5 frames to be detected. The minimumLatencyFrameCount for that request would report 5 and only after 5 frames have been processed an observation would be returned in the results. This latency is indicative of how responsive a request is in respect to the incoming data.
*/
@property (readonly) NSInteger minimumLatencyFrameCount;

/*!
 @brief The reciprocal of maximum rate at which buffers will be processed.
 @discussion The request will not process buffers that fall within the `frameAnalysisSpacing` after it has performed the analysis. The analysis is not done by wall time but by analysis of of the time stamps of the samplebuffers being processed.
 */
@property (readonly) CMTime frameAnalysisSpacing;

@end


NS_ASSUME_NONNULL_END
