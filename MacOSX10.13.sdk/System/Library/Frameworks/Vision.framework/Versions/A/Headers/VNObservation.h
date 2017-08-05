//
//  VNObservation.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreML/CoreML.h>
#import <simd/simd.h>

#import <Vision/VNTypes.h>


/*!
 @header VNObservation VNObservations describe the results of performing a VNRequest. The type of request determines the type of observations.
 */


@class CIBarcodeDescriptor;
@class MLFeatureValue;
@class VNFaceLandmarks2D;


NS_ASSUME_NONNULL_BEGIN

/*!
 @class VNObservation
 @brief VNObservation describes the results of performing a VNRequest. The result has a confidence score. The different types of requests will create different subclasses of VNObservation to return their results in properties of those subclasses.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNObservation : NSObject < NSCopying, NSSecureCoding >

/*!
 * @brief The unique identifier assigned to an observation.
 */
@property (readonly, nonatomic, strong) NSUUID *uuid;

/*!
 * @brief the level of confidence normalized in [0, 1] where 1 is most confident
 * @discussion this can be constant == 1.0 if confidence is not supported or has no meaning
 * @note the confidence values are not plumbed in.  These values are unreliable at this time.
 */
@property (readonly, nonatomic, assign) VNConfidence confidence;

@end


/*!
    @class VNDetectedObjectObservation
    @superclass VNObservation
    @brief VNDetectedObjectObservation is VNObservation in an image that has a location and/or dimension. Further attributes depend on the specific detected object.
    @discussion All result objects (faces, scene objects, shapes etc) must extend from this class.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectedObjectObservation : VNObservation

/*!
 @brief create a new VNDetectedObjectObservation with a normalized bounding box and a confidence of 1.0.
 */
+ (instancetype)observationWithBoundingBox:(CGRect)boundingBox;

/*!
    @brief The bounding box of detected object. The coordinates are normalized to the dimensions of the processed image, with the origin at the image's lower-left corner.
 */
@property (readonly, nonatomic, assign) CGRect boundingBox;

@end


/*!
 @class VNFaceObservation
 @superclass VNObservation
 @brief VNFaceObservation is the result of a face detection request.
 @discussion TBD.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceObservation: VNDetectedObjectObservation

@property (readonly, nonatomic, strong, nullable)  VNFaceLandmarks2D *landmarks;

@end

/*!
 @class VNClassificationObservation
 @superclass VNObservation
 @brief VNClassificationObservation returns the classifcation in form of a string.
 @discussion TBD
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNClassificationObservation : VNObservation

@property (readonly, nonatomic, copy) NSString *identifier;

@end

/*!
 @class VNCoreMLFeatureValueObservation
 @superclass VNObservation
 @brief VNCoreMLFeatureValueObservation returns the prediction of a model as an MLFeatureValue.
 @discussion This is the returned observations for models that are not classifiers and that do not return an image as a prediction. Also the confidence for these observations is always 1.0.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNCoreMLFeatureValueObservation : VNObservation

@property (readonly, nonatomic, copy) MLFeatureValue *featureValue;

@end

/*!
 @class VNPixelBufferObservation
 @superclass VNObservation
 @brief VNPixelBufferObservation returns the prediction of a model as a CVPixelBufferRef.
 @discussion This is the returned observations for models that are not classifiers and return an image as a prediction. Also the confidence for these observations is always 1.0.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNPixelBufferObservation : VNObservation

@property (readonly, nonatomic) CVPixelBufferRef pixelBuffer;

@end


/*!
 @class VNRectangleObservation
 @superclass VNObservation
 @brief VNRectangleObservation is the result of a rectangle detector
 @discussion TBD

 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNRectangleObservation : VNDetectedObjectObservation

@property (readonly, nonatomic, assign) CGPoint topLeft;
@property (readonly, nonatomic, assign) CGPoint topRight;
@property (readonly, nonatomic, assign) CGPoint bottomLeft;
@property (readonly, nonatomic, assign) CGPoint bottomRight;

@end


/*!
 @class VNTextObservation
 @superclass VNDetectedObjectObservation
 @brief VNTextObservation Describes a text area detected by the VNRequestNameDetectTextRectangles request.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTextObservation : VNDetectedObjectObservation

/*!
	@brief		Array of individual character bounding boxes found within the observation's boundingBox.
	@discussion	If the associated request indicated that it is interested in character boxes by setting the VNRequestOptionReportCharacterBoxes option to @YES, this property will be non-nil (but may still be empty, depending on the detection results).
*/
@property (readonly, nonatomic, copy, nullable) NSArray<VNRectangleObservation *> *characterBoxes;

@end


/*!
 @class VNBarcodeObservation
 @superclass VNRectangleObservation
 @brief VNBarcodeObservation Describes an area containing a barcode detected by the VNRequestNameDetectBarcodes request.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNBarcodeObservation : VNRectangleObservation

/*!
	@brief The symbology of the detected barcode.
*/
@property (readonly, nonatomic, copy) VNBarcodeSymbology symbology;


/*!
	@brief An object that provides symbology-specific data for the barcode.
*/
@property (readonly, nonatomic, strong, nullable) CIBarcodeDescriptor* barcodeDescriptor;

@end



/*!
 @class VNHorizonObservation
 @superclass VNObservation
 @brief VNHorizonObservation is the result of a VNDetectHorizonRequest
 @discussion TBD
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNHorizonObservation : VNObservation

@property (readonly, nonatomic, assign) CGAffineTransform transform;
@property (readonly, nonatomic, assign) CGFloat angle;

@end



/*!
 @brief VNImageAlignmentObservation is generated from an image registration.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageAlignmentObservation : VNObservation
@end


/*!
	@brief An observation describing the results of performing a translational image alignment.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageTranslationAlignmentObservation : VNImageAlignmentObservation
@property (readwrite, nonatomic, assign) CGAffineTransform alignmentTransform;
@end


/*!
	@brief An observation describing the results of performing a homorgraphic image alignment.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageHomographicAlignmentObservation : VNImageAlignmentObservation
@property (readwrite, nonatomic, assign) matrix_float3x3 warpTransform;
@end




NS_ASSUME_NONNULL_END
