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
#import <Vision/VNRequestRevisionProviding.h>


/*!
 @header VNObservation VNObservations describe the results of performing a VNRequest. The type of request determines the type of observations.
 */


NS_ASSUME_NONNULL_BEGIN


@class CIBarcodeDescriptor;
@class MLFeatureValue;
@class VNFaceLandmarks2D;



/*!
 @class VNObservation
 @brief VNObservation describes the results of performing a VNRequest. The result has a confidence score. The different types of requests will create different subclasses of VNObservation to return their results in properties of those subclasses.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNObservation : NSObject < NSCopying, NSSecureCoding, VNRequestRevisionProviding >

/*!
   @brief The unique identifier assigned to an observation.
 */
@property (readonly, nonatomic, strong) NSUUID *uuid;

/*!
 * @brief The level of confidence normalized to [0, 1] where 1 is most confident
 * @discussion Confidence can always be returned as 1.0 if confidence is not supported or has no meaning
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

+ (instancetype)observationWithRequestRevision:(NSUInteger)requestRevision boundingBox:(CGRect)boundingBox API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
    @brief The bounding box of the detected object. The coordinates are normalized to the dimensions of the processed image, with the origin at the image's lower-left corner.
 */
@property (readonly, nonatomic, assign) CGRect boundingBox;

@end


/*!
 @class VNFaceObservation
 @superclass VNObservation
 @brief VNFaceObservation is the result of a face detection request or derivatives like a face landmark request.
 @discussion The properties filled in this obervation depend on the request being performed. For instance if just a VNDetectFaceRectanglesRequest was performed the landmarks will not be populated. VNFaceObservation are also used as inputs to other request as defined by the VNFaceObservationAccepting protocol. An example would be the VNDetectFaceLandmarksRequest. This can be helpful for instance if the face rectangles in an image are not derived from a VNDetectFaceRectanglesRequest but instead come from other sources like EXIF or other face detectors. In that case the client of the API creates a VNFaceObservation with the boundingBox (in normalized coordinates) that were based on those detected faces.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceObservation: VNDetectedObjectObservation

/*!
 @brief create a new VNFaceObservation with a normalized bounding box, roll and yaw
 @discussion If you're creating your bounding box without using Vision, set the requestRevision to VNRequestRevisionUnspecified
 */
+ (instancetype)faceObservationWithRequestRevision:(NSUInteger)requestRevision boundingBox:(CGRect)boundingBox roll:(nullable NSNumber *)roll yaw:(nullable NSNumber *)yaw API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
 @brief The face landmarks populated by the VNDetectFaceLandmarksRequest. This is set to nil if only a VNDetectFaceRectanglesRequest was performed.
 */
@property (readonly, nonatomic, strong, nullable)  VNFaceLandmarks2D *landmarks;

/*!
 @brief The capture quality of the face as a normalized value between 0.0 and 1.0 that can be used to compare the quality of the face in terms of it capture attributes (lighting, blur, position). This score can be used to compare the capture quality of a face against other captures of the same face in a given set.
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *faceCaptureQuality API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/*!
 @brief Face roll angle populated by VNDetectFaceRectanglesRequest. The roll is reported in radians, positive angle corresponds to counterclockwise direction, range [-Pi, Pi). nil value indicates that the roll angle hasn't been computed
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *roll API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
 @brief Face yaw angle populated by VNDetectFaceRectanglesRequest. The yaw is reported in radians, positive angle corresponds to counterclockwise direction, range [-Pi/2, Pi/2). nil value indicates that the yaw angle hasn't been computed
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *yaw API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

@end

/*!
 @class VNClassificationObservation
 @superclass VNObservation
 @brief VNClassificationObservation returns the classifcation in form of a string.
 @discussion VNClassificationObservation is the observation returned by VNCoreMLRequests that using a model that is a classifier. A classifier produces an arrary (this can be a single entry) of classifications which are labels (identifiers) and confidence scores.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNClassificationObservation : VNObservation

/*!
 @brief The is the label or identifier of a classification request. An example classification could be a string like 'cat' or 'hotdog'. The string is defined in the model that was used for the classification. Usually these are technical labels that are not localized and not meant to be used directly to be presented to an end user in the UI.
 */
@property (readonly, nonatomic, copy) NSString *identifier;

@end


/*!
 @discussion VNClassificationObservation mave have precision/recall curves which can be used to decide on an "optimal" operation point.
             Precision is a value in the range of [0..1] which represents the fraction of relevant instances among the retrieved instances.
             Recall is a value in the range of [0..1] which represents the fraction of relevant instances that have been retrieved over the total amount of relevant instances.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNClassificationObservation (PrecisionRecallAdditions)

/*!
	@brief	Determine whether or not precision/recall curves are available with the observation.
	@discussion	If this property is YES, then all other precision/recall related methods in this addition can be called.
*/
@property (readonly, nonatomic, assign) BOOL hasPrecisionRecallCurve;

/*!
	@brief	Determine whether or not the observation's operation point for a specific precision has a minimum recall value.
 
	@param minimumRecall	The minimum recall desired for an operation point.
 
	@param precision		The precision value used to select the operation point.
 
	@return YES if the recall value for the operation point specified by a precision value has the minimum value; otherwise, NO.
*/
- (BOOL) hasMinimumRecall:(float)minimumRecall forPrecision:(float)precision;

/*!
	@brief	Determine whether or not the observation's operation point for a specific recall has a minimum precision value.

	@param minimumPrecision	The minimum precision desired for an operation point.
 
	@param recall		The recall value used to select the operation point.
 
	@return YES if the precision value for the operation point specified by a recall value has the minimum value; otherwise, NO.
*/
- (BOOL) hasMinimumPrecision:(float)minimumPrecision forRecall:(float)recall;

@end



/*!
 @class VNRecognizedObjectObservation
 @superclass VNDetectedObjectObservation
 @brief VNRecognizedObjectObservation is a VNDetectedObjectObservation with an array of classifications that classify the recognized object. The confidence of the classifications sum up to 1.0. It is common practice to multiply the classification confidence with the confidence of this observation.
 */
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
@interface VNRecognizedObjectObservation : VNDetectedObjectObservation

@property (readonly, nonatomic, copy) NSArray<VNClassificationObservation *> *labels;

@end

/*!
 @class VNCoreMLFeatureValueObservation
 @superclass VNObservation
 @brief VNCoreMLFeatureValueObservation returns the prediction of a model as an MLFeatureValue.
 @discussion This is the returned observations for models that are not classifiers and that do not return an image as a prediction. The confidence for these observations is always 1.0.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNCoreMLFeatureValueObservation : VNObservation

/*!
 @brief The result VNCoreMLRequest where the model produces an MLFeatureValue that is neither a classification or image. Refer to the Core ML documentation and the model itself for the handling of the content of the featureValue.
 
 */
@property (readonly, nonatomic, copy) MLFeatureValue *featureValue;

/*!
 @brief The name used in the model description of the CoreML model that produced this observation allowing to correlate the observation back to the output of the model.
 
 */
@property (readonly, nonatomic, copy) NSString *featureName API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

/*!
 @class VNPixelBufferObservation
 @superclass VNObservation
 @brief VNPixelBufferObservation returns the prediction of a model as a CVPixelBufferRef.
 @discussion This is the returned observations for models that are not classifiers and return an image as a prediction. The confidence for these observations is always 1.0.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNPixelBufferObservation : VNObservation

/*!
 @brief The resulting image from a request like VNCoreMLRequest where the model produces an image as an output.
 
 */
@property (readonly, nonatomic) CVPixelBufferRef pixelBuffer;

/*!
 @brief The name used in the model description of the CoreML model that produced this observation allowing to correlate the observation back to the output of the model. This can be nil if the observation is not the result of a VNCoreMLRequest operation.
 
 */
@property (readonly, nonatomic, copy, nullable) NSString *featureName API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


/*!
 @class VNRectangleObservation
 @superclass VNObservation
 @brief VNRectangleObservation is the result of a rectangle detector
 @discussion The VNRectangleObservation has a bounding box that encompasses the rectangle found in the image. The rectangle itself is defined by the four corner point properties. The rectangle can be rotated in or even out of plane. A common use case is to use the CIPerspectiveTransform filter to correct a detected rectangle to its 'flat upright' representation. All coordinates are normalized and the coordinates can be outside the image.

 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNRectangleObservation : VNDetectedObjectObservation

+ (instancetype)rectangleObservationWithRequestRevision:(NSUInteger)requestRevision topLeft:(CGPoint)topLeft bottomLeft:(CGPoint)bottomLeft bottomRight:(CGPoint)bottomRight topRight:(CGPoint)topRight API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

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
@interface VNTextObservation : VNRectangleObservation

/*!
	@brief		Array of individual character bounding boxes found within the observation's boundingBox.
	@discussion	If the associated request indicated that it is interested in character boxes by setting the VNRequestOptionReportCharacterBoxes option to @YES, this property will be non-nil (but may still be empty, depending on the detection results).
*/
@property (readonly, nonatomic, copy, nullable) NSArray<VNRectangleObservation *> *characterBoxes;

@end

/*!
 @class VNRecognizedText
 @brief VNRecognizedText A block of recognized text. There can be multiple VNRecognizedText objects returned in a VNRecognizedTextObservation - one for each candidate.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizedText : NSObject < NSCopying, NSSecureCoding >

/*!
 @brief        Field that contains recognized text.
 @discussion   This is the top candidate of the recognized text.
 */
@property (readonly, nonatomic, copy) NSString *string;

/*!
 * @brief The level of confidence normalized to [0.0, 1.0] where 1.0 is most confident
 */
@property (readonly, nonatomic, assign) VNConfidence confidence;

/*!
 * @brief Calculate the bounding box around the characters in the range of the string.
 * @discussion The bounding boxes are not guaranteed to be an exact fit around the characters and are purely meant for UI purposes and not for image processing.
 */
- (nullable VNRectangleObservation *)boundingBoxForRange:(NSRange)range error:(NSError**)error;

@end

/*!
 @class VNRecognizedTextObservation
 @superclass VNDetectedObjectObservation
 @brief VNRecognizedTextObservation Describes a text area detected and recognized by the VNRecognizeTextRequest request.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizedTextObservation : VNRectangleObservation


/*!
 * @brief Returns the top N candidates sorted by decreasing confidence score
 * @discussion This will return no more than N but can be less than N candidates. The maximum number of candidates returned cannot exceed 10 candidates.
 */
- (NSArray<VNRecognizedText*>*) topCandidates:(NSUInteger)maxCandidateCount;


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


/*!
	@brief The string representation of the barcode's payload.  Depending on the symbology of the barcode and/or the payload data itself, a string representation of the payload may not be available.
*/
@property (readonly, nonatomic, copy, nullable) NSString* payloadStringValue;

@end



/*!
 @class VNHorizonObservation
 @superclass VNObservation
 @brief VNHorizonObservation is the result of a VNDetectHorizonRequest
 @discussion Use the transform or angle to upright the image and make the detected horizon level.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNHorizonObservation : VNObservation

@property (readonly, nonatomic, assign) CGAffineTransform transform;
@property (readonly, nonatomic, assign) CGFloat angle;

@end



/*!
 @class VNImageAlignmentObservation
 @superclass VNObservation
 @brief VNImageAlignmentObservation is generated from an image registration. This is an abstract base class. The type of registration request used defines which subclass describes the result.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageAlignmentObservation : VNObservation
@end


/*!
 @class VNImageTranslationAlignmentObservation
 @superclass VNImageAlignmentObservation
 @brief An observation describing the results of performing a translational image alignment.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageTranslationAlignmentObservation : VNImageAlignmentObservation
@property (readwrite, nonatomic, assign) CGAffineTransform alignmentTransform;
@end


/*!
 @class VNImageHomographicAlignmentObservation
 @superclass VNImageAlignmentObservation
 @brief An observation describing the results of performing a homographic image alignment.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageHomographicAlignmentObservation : VNImageAlignmentObservation
@property (readwrite, nonatomic, assign) matrix_float3x3 warpTransform;
@end

/*!
 @class VNSaliencyImageObservation
 @superclass VNPixelBufferObservation
 @brief VNSaliencyImageObservation provides a grayscale "heat" map of important areas of an image.
 @discussion In the revision1, the "heat" map is a OneComponent32Float pixel format CVPixelBuffer.
 
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNSaliencyImageObservation : VNPixelBufferObservation

/*!
 @brief An array of bounds of salient objects within the image. Each box represents a distinct mode of the heat map.
*/
@property (readonly, nonatomic, nullable) NSArray<VNRectangleObservation*>* salientObjects;

@end


/*!
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNFeaturePrintObservation : VNObservation

/*!
	@brief The type of each element in the data.
*/
@property (readonly, atomic, assign) VNElementType elementType;

/*!
	@brief The total number of elements in the data.
*/
@property (readonly, atomic, assign) NSUInteger elementCount;

/*!
	@brief The feature print data.
*/
@property (readonly, atomic, strong) NSData* data;

/*!
 @brief Computes the distance between two observations.
 @discussion The larger the distance the more dissimlar the feature prints are. In case of an error this method returns false with an error describing the error condition, for instance comparing two non-comparable feature prints.
 */
- (BOOL)computeDistance:(float *)outDistance toFeaturePrintObservation:(VNFeaturePrintObservation *)featurePrint error:(NSError **)error;

@end


NS_ASSUME_NONNULL_END
