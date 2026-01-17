//
//  VNGenerateOpticalFlowRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNTargetedImageRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief The level of optical flow computational accuracy.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(NSUInteger, VNGenerateOpticalFlowRequestComputationAccuracy)
{
    VNGenerateOpticalFlowRequestComputationAccuracyLow = 0,
    VNGenerateOpticalFlowRequestComputationAccuracyMedium,
    VNGenerateOpticalFlowRequestComputationAccuracyHigh,
    VNGenerateOpticalFlowRequestComputationAccuracyVeryHigh
} NS_SWIFT_NAME(VNGenerateOpticalFlowRequest.ComputationAccuracy);


/*!
 @brief VNGenerateOpticalFlowRequest will determine directional change vectors for each pixel in the targeted image to transform it into the image processed
        by the request handler, reporting this result with a single VNPixelBufferObservation.

 @discussion	Because this request works at the pixel level, both images must have the same dimensions in order for the request to be successfully performed.
				Setting a region of interest will isolate where the change determination is performed; however, the resultant observation will still be reported
				with a full resolution VNPixelBufferObservation.
				
                Optical flow requests are very resource intensive, so it is recommended that only one request at a time be created and that the handler
                where the request was issued be released immediately after generating optical flows.

				Example usage:

					- (nullable VNPixelBufferObservation*) opticalFlowFromImage:(CVPixelBufferRef)fromImage toImage:(CVPixelBuffer)toImage error:(NSError**)error
					{
						VNImageRequestHandler* imageRequestHandler = [[VNImageRequestHandler alloc] initWithCVPixelBuffer:fromImage options:@{}];
						VNGenerateOpticalFlowRequest* request = [[VNGenerateOpticalFlowRequest alloc] initWithTargetedCVPixelBuffer:toImage options:@{}];
						if (![imageRequestHandler performRequests:@[ request ] error:error])
						{
							return nil;
						}

						return [[request results] firstObject];
					}
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNGenerateOpticalFlowRequest : VNTargetedImageRequest

/*!
 @brief The level of accuracy used to compute the optical flow. Default is VNGenerateOpticalFlowRequestComputationAccuracyMedium.
 @discussion The computational time typically trends with the accuracy level.  This parameter allows for selective tuning by the client application.
 */
@property (readwrite, nonatomic, assign) VNGenerateOpticalFlowRequestComputationAccuracy computationAccuracy;

/*!
 @brief Pixel format type of the output buffer. Valid values are kCVPixelFormatType_TwoComponent32Float and kCVPixelFormatType_TwoComponent16Half.
        Default is kCVPixelFormatType_TwoComponent32Float.
 */
@property (readwrite, nonatomic, assign) OSType outputPixelFormat;

/*!
 @brief Setting this to YES will keep the raw pixel buffer coming from the the ML network. The default is NO.
 @discussion When set to YES, the outputPixelFormat is ignored. Setting this for revision 1 is a no-op as it is not ML-based.
 */
@property (readwrite, nonatomic, assign) BOOL keepNetworkOutput API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0));

/*!
	@discussion VNPixelBufferObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNPixelBufferObservation*>* results;

@end


API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
static const NSUInteger VNGenerateOpticalFlowRequestRevision1 = 1;

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
static const NSUInteger VNGenerateOpticalFlowRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
