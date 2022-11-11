#if !__has_include(<AVFCapture/AVSemanticSegmentationMatte.h>)
/*
    File:  AVSemanticSegmentationMatte.h
 
    Framework:  AVFoundation
 
    Copyright 2019-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBufferPool.h>
#import <ImageIO/CGImageProperties.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group AVSemanticSegmentationMatteType string constants
 
 @discussion
    AVSemanticSegmentationMatteType string constants describe specific types of semantic segmentation matting images that may be captured and stored along with a primary image and may be used to improve the rendering of various effects on that image.
 */
typedef NSString *AVSemanticSegmentationMatteType NS_TYPED_ENUM;

/*!
 @constant AVSemanticSegmentationMatteTypeSkin
    A matting image segmenting all skin from all persons in the visible field-of-view of an image.
 */
AVF_EXPORT AVSemanticSegmentationMatteType const AVSemanticSegmentationMatteTypeSkin API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVSemanticSegmentationMatteTypeHair
    A matting image segmenting all hair from all persons in the visible field-of-view of an image.
 */
AVF_EXPORT AVSemanticSegmentationMatteType const AVSemanticSegmentationMatteTypeHair API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVSemanticSegmentationMatteTypeTeeth
    A matting image segmenting all teeth from all persons in the visible field-of-view of an image.
 */
AVF_EXPORT AVSemanticSegmentationMatteType const AVSemanticSegmentationMatteTypeTeeth API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVSemanticSegmentationMatteTypeGlasses
 A matting image segmenting all glasses ( e.g. eyeglasses, sunglasses ) from all persons wearing glasses in the visible field-of-view of an image.
 */
AVF_EXPORT AVSemanticSegmentationMatteType const AVSemanticSegmentationMatteTypeGlasses API_AVAILABLE(macos(11.0), ios(14.1), macCatalyst(14.1), tvos(14.5), watchos(8.0));

/*!
 @class AVSemanticSegmentationMatte
 @abstract
    An object wrapping a matting image for a particular semantic segmentation.
 
 @discussion
    The pixel data in the matting image is represented in CVPixelBuffers as kCVPixelFormatType_OneComponent8 ('L008'). It is stored in image files as an auxiliary image, accessible using CGImageSourceCopyAuxiliaryDataInfoAtIndex using data types defined in <ImageIO/CGImageProperties.h>.
 */
API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0), tvos(13.0), watchos(6.0))
@interface AVSemanticSegmentationMatte : NSObject

AV_INIT_UNAVAILABLE

/*!
 @method semanticSegmentationMatteFromDictionaryRepresentation:error:
 @abstract
    Returns an AVSemanticSegmentationMatte instance from auxiliary image information in an image file.
 
 @param imageSourceAuxiliaryDataType
    The kCGImageAuxiliaryDataType constant corresponding to the semantic segmentation matte being created (see <ImageIO/CGImageProperties.h>.
 @param imageSourceAuxiliaryDataInfoDictionary
    A dictionary of primitive semantic segmentation matte related information obtained from CGImageSourceCopyAuxiliaryDataInfoAtIndex.
 @param outError
    On return, if the semantic segmentation matte cannot be created, points to an NSError describing the problem.
 @result
    An AVSemanticSegmentationMatte instance, or nil if the auxiliary data info dictionary was malformed.
 
 @discussion
    When using ImageIO framework's CGImageSource API to read from a HEIF or JPEG file containing a semantic segmentation matte, AVSemanticSegmentationMatte can be instantiated using the result of CGImageSourceCopyAuxiliaryDataInfoAtIndex, which returns a CFDictionary of primitive segmentation matte information.
 */
+ (nullable instancetype)semanticSegmentationMatteFromImageSourceAuxiliaryDataType:(CFStringRef)imageSourceAuxiliaryDataType dictionaryRepresentation:(NSDictionary *)imageSourceAuxiliaryDataInfoDictionary error:(NSError * _Nullable * _Nullable)outError;

/*!
 @property matteType
 @abstract
    Specifies the receiver's semantic segmentation matting image type.
 
 @discussion
    An AVSemanticSegmentationMatte's matteType is immutable for the life of the object.
 */
@property(readonly) AVSemanticSegmentationMatteType matteType;

/*!
 @method semanticSegmentationMatteByApplyingExifOrientation:
 @abstract
    Returns a derivative AVSemanticSegmentationMatte instance in which the specified Exif orientation has been applied.
 
 @param exifOrientation
    One of the 8 standard Exif orientation tags expressing how the matte should be rotated / mirrored.
 @result
    An AVSemanticSegmentationMatte's instance.
 
 @discussion
    When applying simple 90 degree rotation or mirroring edits to media containing a semantic segmentation matte, you may use this initializer to create a derivative copy of the matte in which the specified orientation is applied. This method throws an NSInvalidArgumentException if you pass an unrecognized exifOrientation.
 */
- (instancetype)semanticSegmentationMatteByApplyingExifOrientation:(CGImagePropertyOrientation)exifOrientation;

/*!
 @method semanticSegmentationMatteByReplacingSemanticSegmentationMatteWithPixelBuffer:error:
 @abstract
    Returns an AVSemanticSegmentationMatte instance wrapping the replacement pixel buffer.
 
 @param pixelBuffer
    A pixel buffer containing a semantic segmentation matting image, represented as kCVPixelFormatType_OneComponent8 with a kCVImageBufferTransferFunction_Linear transfer function.
 @param outError
    On return, if the AVSemanticSegmentationMatte cannot be created, points to an NSError describing the problem.
 @result
    An AVSemanticSegmentationMatte instance, or nil if the pixel buffer is malformed.
 
 @discussion
    When applying complex edits to media containing a semantic segmentation matte, you may create a derivative matte with arbitrary transforms applied to it, then use this initializer to create a new AVSemanticSegmentationMatte.
 */
- (nullable instancetype)semanticSegmentationMatteByReplacingSemanticSegmentationMatteWithPixelBuffer:(CVPixelBufferRef)pixelBuffer error:(NSError * _Nullable * _Nullable)outError;

/*!
 @method dictionaryRepresentationForAuxiliaryDataType:
 @abstract
    Returns a dictionary of primitive map information to be used when writing an image file with a semantic segmentation matte.
 
 @param outAuxDataType
    On output, the auxiliary data type to be used when calling CGImageDestinationAddAuxiliaryDataInfo. Currently supported auxiliary data types are enumerated in <ImageIO/CGImageProperties.h>
 @result
    A dictionary of CGImageDestination compatible semantic segmentation matte information, or nil if the auxDataType is unsupported.
 
 @discussion
    When using ImageIO framework's CGImageDestination API to write semantic segmentation matte information to a HEIF or JPEG file, you may use this method to generate a dictionary of primitive map information consumed by CGImageDestinationAddAuxiliaryDataInfo.
 */
- (nullable NSDictionary *)dictionaryRepresentationForAuxiliaryDataType:(NSString * _Nullable * _Nullable)outAuxDataType;

/*!
 @property pixelFormatType
 @abstract
    Specifies the pixel format type of this object's internal matting image.
 
 @discussion
    Currently the only supported CV pixel format type for the matting image is kCVPixelFormatType_OneComponent8.
 */
@property(readonly) OSType pixelFormatType;

/*!
 @property mattingImage
 @abstract
    Provides access to the semantic segmentation matte's internal image.
 
 @discussion
    The pixel format can be queried using the pixelFormatType property.
 */
@property(readonly) __attribute__((NSObject)) CVPixelBufferRef mattingImage NS_RETURNS_INNER_POINTER;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVSemanticSegmentationMatte.h>
#endif
