//
//  VNGeneratePersonSegmentationRequest.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Vision/VNObservation.h>
#import <Vision/VNStatefulRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief     Person segmentation level options to favor speed over recognition accuracy.
            VNPersonSegmentationRequestLevelAccurate is the default option.
 @details   fast - generates a low accuracy segmentation mask that can be used in streaming scenarios on devices that have a neural engine
            balanced - generates a high accuracy segmentation mask
            accurate - generates a mask based on the balanced output that includes matting refinement
            The request may hold on to previous masks to improve temporal stability.
 */
typedef NS_ENUM(NSUInteger, VNGeneratePersonSegmentationRequestQualityLevel)
{
    VNGeneratePersonSegmentationRequestQualityLevelAccurate = 0,
    VNGeneratePersonSegmentationRequestQualityLevelBalanced,
    VNGeneratePersonSegmentationRequestQualityLevelFast,
}  NS_SWIFT_NAME(VNGeneratePersonSegmentationRequest.QualityLevel);

/*!
 @brief Performs person segmentationin an image.
 */
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
@interface VNGeneratePersonSegmentationRequest : VNStatefulRequest

+ (instancetype) new NS_SWIFT_UNAVAILABLE("");
- (instancetype) init;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler;
- (instancetype) initWithFrameAnalysisSpacing:(CMTime)frameAnalysisSpacing
                            completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;

/*!
 @brief The quality level selects which techniques will be used during the person segmentation. There are trade-offs between performance and accuracy.
 */
@property (readwrite, nonatomic, assign) VNGeneratePersonSegmentationRequestQualityLevel qualityLevel;

/*!
 @brief Pixel format type of the output buffer. Valid values are kCVPixelFormatType_OneComponent32Float, kCVPixelFormatType_OneComponent16Half, and kCVPixelFormatType_OneComponent8. Default is kCVPixelFormatType_OneComponent8.
 */
@property (readwrite, nonatomic) OSType outputPixelFormat;

@property (readonly, copy, nullable) NSArray<VNPixelBufferObservation *> * results;

@end


API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
static const NSUInteger VNGeneratePersonSegmentationRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
