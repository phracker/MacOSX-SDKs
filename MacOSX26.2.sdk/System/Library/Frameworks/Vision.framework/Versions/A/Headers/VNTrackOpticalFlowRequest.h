//
//  VNTrackOpticalFlowRequest.h
//  Vision
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Vision/VNStatefulRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief The level of optical flow computational accuracy.
 */
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
typedef NS_ENUM(NSUInteger, VNTrackOpticalFlowRequestComputationAccuracy)
{
    VNTrackOpticalFlowRequestComputationAccuracyLow = 0,
    VNTrackOpticalFlowRequestComputationAccuracyMedium,
    VNTrackOpticalFlowRequestComputationAccuracyHigh,
    VNTrackOpticalFlowRequestComputationAccuracyVeryHigh

} NS_SWIFT_NAME(VNTrackOpticalFlowRequest.ComputationAccuracy);


/*!
	@brief `VNTrackOpticalFlowRequest` will determine directional change vectors for each pixel from a previous to current image, reporting this result with a single `VNPixelBufferObservation`.

	@discussion	Because this request works at the pixel level, both images must have the same dimensions in order for the request to be successfully performed.
				Setting a region of interest will isolate where the change determination is performed; however, the resultant observation will still be reported
				with a full resolution `VNPixelBufferObservation.
				
				Being a stateful request, at least two images must me processed in order to produce an observation.
				
                Optical flow requests are very resource intensive, so it is recommended that only one request at a time be created and that the handler
                where the request was issued be released immediately after generating optical flows.

				Example usage:

					- (nullable VNPixelBufferObservation*) opticalFlowFromImage:(CVPixelBufferRef)fromImage toImage:(CVPixelBuffer)toImage error:(NSError**)error
					{
						VNTrackOpticalFlowRequest* request = [[VNTrackOpticalFlowRequest alloc] init];

						VNImageRequestHandler* imageRequestHandler = [[VNImageRequestHandler alloc] initWithCVPixelBuffer:fromImage options:@{}];
						if (![imageRequestHandler performRequests:@[ request ] error:error])
						{
							return nil;
						}
						
						imageRequestHandler = [[VNImageRequestHandler alloc] initWithCVPixelBuffer:toImage options:@{}];
						if (![imageRequestHandler performRequests:@[ request ] error:error])
						{
							return nil;
						}

						return [[request results] firstObject];
					}
*/
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface VNTrackOpticalFlowRequest : VNStatefulRequest

/*!
	@brief Create a new request that can statefully track the optical from from one image to another.
	@discussion This is a convenience initializer for a frame analysis spacing of kCMTimeZero and a nil completion handler.
*/
- (instancetype) init;

/*!
	@brief Create a new request that can statefully track the optical from from one image to another.
	@discussion This is a convenience initializer for a frame analysis spacing of kCMTimeZero.
*/
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler;

/*!
 @brief The level of accuracy used to compute the optical flow. Default is VNTrackOpticalFlowRequestComputationAccuracyMedium.
 @discussion The computational time typically trends with the accuracy level.  This parameter allows for selective tuning by the client application.
 */
@property (readwrite, nonatomic, assign) VNTrackOpticalFlowRequestComputationAccuracy computationAccuracy;

/*!
	@brief Pixel format type of the output buffer. Valid values are `kCVPixelFormatType_TwoComponent32Float` and `kCVPixelFormatType_TwoComponent16Half`.  Default is `kCVPixelFormatType_TwoComponent32Float`.
*/
@property (readwrite, nonatomic, assign) OSType outputPixelFormat;

/*!
	@brief Setting this to `YES` will keep the raw pixel buffer coming from the the ML network. The default is `NO`.
	@discussion When set to `YES`, the outputPixelFormat is ignored.
*/
@property (readwrite, nonatomic, assign) BOOL keepNetworkOutput;

/*!
	@discussion VNPixelBufferObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNPixelBufferObservation*>* results;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNTrackOpticalFlowRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
