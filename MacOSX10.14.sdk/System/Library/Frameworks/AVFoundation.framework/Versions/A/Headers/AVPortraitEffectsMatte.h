/*
    File:  AVPortraitMatte.h
 
    Framework:  AVFoundation
 
    Copyright 2018 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBufferPool.h>
#import <ImageIO/CGImageProperties.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPortraitEffectsMatteInternal;

/*!
 @class AVPortraitEffectsMatte
 @abstract
    An object wrapping a matting image used for high quality rendering of portrait style effects onto an image (i.e. shallow depth of field, stage lighting, etc).
 
 @discussion
    The pixel data in the matting image is represented in CVPixelBuffers as kCVPixelFormatType_OneComponent8 ('L008'). It's stored in image files as an auxiliary image, accessible using CGImageSourceCopyAuxiliaryDataInfoAtIndex with the data type kCGImageAuxiliaryDataTypePortraitEffectsMatte (see <ImageIO/CGImageProperties.h>).
 */
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0))
@interface AVPortraitEffectsMatte : NSObject
{
@private
    AVPortraitEffectsMatteInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @method portraitEffectsMatteFromDictionaryRepresentation:error:
 @abstract
    Returns an AVPortraitEffectsMatte instance from auxiliary image information in an image file.
 
 @param imageSourceAuxDataInfoDictionary
    A dictionary of primitive portrait effects matte related information obtained from CGImageSourceCopyAuxiliaryDataInfoAtIndex.
 @param outError
    On return, if the portrait effects matte cannot be created, points to an NSError describing the problem.
 @result
    An AVPortraitEffectsMatte instance, or nil if the auxiliary data info dictionary was malformed.
 
 @discussion
    When using ImageIO framework's CGImageSource API to read from a HEIF or JPEG file containing a portrait effects matte, AVPortraitEffectsMatte can be instantiated using the result of CGImageSourceCopyAuxiliaryDataInfoAtIndex, which returns a CFDictionary of primitive map information.
 */
+ (nullable instancetype)portraitEffectsMatteFromDictionaryRepresentation:(NSDictionary *)imageSourceAuxDataInfoDictionary error:(NSError * _Nullable * _Nullable)outError;

/*!
 @method portraitEffectsMatteByApplyingExifOrientation:
 @abstract
    Returns a derivative AVPortraitEffectsMatte instance in which the specified Exif orientation has been applied.
 
 @param exifOrientation
    One of the 8 standard Exif orientation tags expressing how the portrait effects matte should be rotated / mirrored.
 @result
    An AVPortraitEffectsMatte instance.
 
 @discussion
    When applying simple 90 degree rotation or mirroring edits to media containing a portrait effects matte, you may use this initializer to create a derivative copy of the portrait effects matte in which the specified orientation is applied. This method throws an NSInvalidArgumentException if you pass an unrecognized exifOrientation.
 */
- (instancetype)portraitEffectsMatteByApplyingExifOrientation:(CGImagePropertyOrientation)exifOrientation;

/*!
 @method portraitEffectsMatteByReplacingPortraitEffectsMatteWithPixelBuffer:error:
 @abstract
    Returns an AVPortraitEffectsMatte instance wrapping the replacement pixel buffer.
 
 @param pixelBuffer
    A pixel buffer containing a portrait effects matting image, represented as kCVPixelFormatType_OneComponent8 with kCVImageBufferColorPrimaries_ITU_R_709_2 color primaries and a kCVImageBufferTransferFunction_Linear transfer function.
 @param outError
    On return, if the AVPortraitEffectsMatte cannot be created, points to an NSError describing the problem.
 @result
    An AVPortraitEffectsMatte instance, or nil if the pixel buffer is malformed.
 
 @discussion
    When applying complex edits to media containing a portrait effects matte, you may create a derivative matte with arbitrary transforms applied to it, then use this initializer to create a new AVPortraitEffectsMatte.
 */
- (nullable instancetype)portraitEffectsMatteByReplacingPortraitEffectsMatteWithPixelBuffer:(CVPixelBufferRef)pixelBuffer error:(NSError * _Nullable * _Nullable)outError;

/*!
 @method dictionaryRepresentationForAuxiliaryDataType:
 @abstract
    Returns a dictionary of primitive map information to be used when writing an image file with a portrait effects matte.
 
 @param outAuxDataType
    On output, the auxiliary data type to be used when calling CGImageDestinationAddAuxiliaryDataInfo. Currently the only supported auxiliary data type is kCGImageAuxiliaryDataTypePortraitEffectsMatte.
 @result
    A dictionary of CGImageDestination compatible portrait effects matte information, or nil if the auxDataType is unsupported.
 
 @discussion
    When using ImageIO framework's CGImageDestination API to write portrait effects matte information to a HEIF or JPEG file, you may use this method to generate a dictionary of primitive map information consumed by CGImageDestinationAddAuxiliaryDataInfo.
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
    Provides access to the portrait effects matte's internal image.
 
 @discussion
    The pixel format can be queried using the pixelFormatType property.
 */
@property(readonly) __attribute__((NSObject)) CVPixelBufferRef mattingImage NS_RETURNS_INNER_POINTER;

@end

NS_ASSUME_NONNULL_END
