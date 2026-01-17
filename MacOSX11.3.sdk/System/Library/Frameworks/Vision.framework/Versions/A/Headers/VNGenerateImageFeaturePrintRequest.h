//
//  VNGenerateImageFeaturePrintRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Vision/VNTypes.h>
#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request for generating a feature print of an image.

	@discussion This request will produce a VNFeaturePrintObservation object.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNGenerateImageFeaturePrintRequest : VNImageBasedRequest

/*!
	@brief Determine what type of croping and scaling action should be applied to the image before generating the feature print.
 
	@discussion The default value for this property is VNImageCropAndScaleOptionScaleFill.
*/
@property (nonatomic, readwrite, assign) VNImageCropAndScaleOption imageCropAndScaleOption;

@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNGenerateImageFeaturePrintRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
