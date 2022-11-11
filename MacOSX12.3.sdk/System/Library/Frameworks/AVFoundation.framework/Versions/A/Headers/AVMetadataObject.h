#if !__has_include(<AVFCapture/AVMetadataObject.h>)
/*
    File:  AVMetadataObject.h
 
    Framework:  AVFoundation
 
    Copyright 2012-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group AVMetadataObjectType string constants
 
 @discussion
    Constants indicating the type of an AVMetadataObject.
 */
typedef NSString * AVMetadataObjectType NS_TYPED_ENUM API_AVAILABLE(macos(10.10), ios(6.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);


#pragma mark - AVMetadataObject

@class AVMetadataObjectInternal;

/*!
 @class AVMetadataObject
 @abstract
    AVMetadataObject is an abstract class that defines an interface for a metadata object used by AVFoundation.
 
 @discussion
    AVMetadataObject provides an abstract interface for metadata associated with a piece of media. One example is face metadata that might be detected in a picture. All metadata objects have a time, duration, bounds, and type.
 
    The concrete AVMetadataFaceObject is used by AVCaptureMetadataOutput for face detection.
 */
API_AVAILABLE(macos(10.10), ios(6.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMetadataObject : NSObject
{
@private
    AVMetadataObjectInternal *_objectInternal;
}

AV_INIT_UNAVAILABLE

/*!
 @property time
 @abstract
    The media time associated with this metadata object.
 
 @discussion
    The value of this property is a CMTime associated with the metadata object. For capture, it is the time at which this object was captured. If this metadata object originates from a CMSampleBuffer, its time matches the sample buffer's presentation time. This property may return kCMTimeInvalid.
 */
@property(readonly) CMTime time;

/*!
 @property duration
 @abstract
    The media duration associated with this metadata object.
 
 @discussion
    The value of this property is a CMTime representing the duration of the metadata object. If this metadata object originates from a CMSampleBuffer, its duration matches the sample buffer's duration. This property may return kCMTimeInvalid.
 */
@property(readonly) CMTime duration;

/*!
 @property bounds
 @abstract
    The bounding rectangle of the receiver.
 
 @discussion
    The value of this property is a CGRect representing the bounding rectangle of the object with respect to the picture in which it resides. The rectangle's origin is top left. If the metadata originates from video, bounds may be expressed as scalar values from 0. - 1. If the original video has been scaled down, the bounds of the metadata object still are meaningful. This property may return CGRectZero if the metadata has no bounds.
 */
@property(readonly) CGRect bounds;

/*!
 @property type
 @abstract
    An identifier for the metadata object.
 
 @discussion
    The value of this property is an AVMetadataObjectType representing the type of the metadata object. Clients inspecting a collection of metadata objects can use this property to filter objects with a matching type.
 */
@property(readonly) AVMetadataObjectType type;

@end


#pragma mark - AVMetadataBodyObject

/*!
 @class AVMetadataBodyObject
 @abstract
    AVMetadataBodyObject is an abstract class that defines an interface for a body metadata object used by AVFoundation.

 @discussion
    AVMetadataBodyObject represents a single detected body in a picture. It is the base object used to represent bodies, for example AVMetadataHumanBodyObject, AVMetadataCatBodyObject, AVMetadataDogBodyObject.

 */
API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface AVMetadataBodyObject : AVMetadataObject <NSCopying>

/*!
 @property bodyID
 @abstract
    A unique number associated with the receiver.

 @discussion
    The value of this property is an NSInteger indicating the unique identifier of this body type (Human, Dog, Cat) in the picture. When a new body enters the picture, it is assigned a new unique identifier. bodyIDs are not re-used as bodies leave the picture and new ones enter. Bodies that leave the picture then re-enter are assigned a new bodyID.
 */
@property(readonly) NSInteger bodyID;

@end


#pragma mark - AVMetadataHumanBodyObject

/*!
 @constant AVMetadataObjectTypeHumanBody
 @abstract
    An identifier for an instance of AVMetadataHumanBodyObject.

 @discussion
    AVMetadataHumanBodyObject objects return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeHumanBody API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @class AVMetadataHumanBodyObject
 @abstract
    AVMetadataHumanBodyObject is a concrete subclass of AVMetadataBodyObject defining a detected human body.

 @discussion
    AVMetadataHumanBodyObject represents a single detected human body in a picture. It is an immutable object describing the various features found in the body.

    On supported platforms, AVCaptureMetadataOutput outputs arrays of detected human body objects. See AVCaptureOutput.h.
 */
API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface AVMetadataHumanBodyObject : AVMetadataBodyObject <NSCopying>

@end


#pragma mark - AVMetadataCatBodyObject

/*!
 @constant AVMetadataObjectTypeCatBody
 @abstract
    An identifier for an instance of AVMetadataCatBodyObject.

 @discussion
    AVMetadataCatBodyObject objects return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeCatBody API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @class AVMetadataCatBodyObject
 @abstract
    AVMetadataCatBodyObject is a concrete subclass of AVMetadataBodyObject defining a detected cat body.

 @discussion
    AVMetadataCatBodyObject represents a single detected cat body in a picture. It is an immutable object describing the various features found in the body.

    On supported platforms, AVCaptureMetadataOutput outputs arrays of detected cat body objects. See AVCaptureOutput.h.
 */
API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface AVMetadataCatBodyObject : AVMetadataBodyObject <NSCopying>

@end


#pragma mark - AVMetadataDogBodyObject

/*!
 @constant AVMetadataObjectTypeDogBody
 @abstract
    An identifier for an instance of AVMetadataDogBodyObject.

 @discussion
    AVMetadataDogBodyObject objects return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeDogBody API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @class AVMetadataDogBodyObject
 @abstract
    AVMetadataDogBodyObject is a concrete subclass of AVMetadataBodyObject defining a detected dog body.

 @discussion
    AVMetadataDogBodyObject represents a single detected dog body in a picture. It is an immutable object describing the various features found in the body.

    On supported platforms, AVCaptureMetadataOutput outputs arrays of detected dog body objects. See AVCaptureOutput.h.
 */
API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface AVMetadataDogBodyObject : AVMetadataBodyObject <NSCopying>

@end


#pragma mark - AVMetadataSalientObject

/*!
 @constant AVMetadataObjectTypeSalientObject
 @abstract
    An identifier for an instance of AVMetadataSalientObject.

 @discussion
    AVMetadataSalientObject objects return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeSalientObject API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @class AVMetadataSalientObject
 @abstract
    AVMetadataSalientObject is a concrete subclass of AVMetadataObject defining the features of a salient object.

 @discussion
    AVMetadataSalientObject represents a single detected salient area in a picture. It is an immutable object describing the salient object.

    On supported platforms, AVCaptureMetadataOutput outputs arrays of detected salient objects. See AVCaptureOutput.h.
 */
API_AVAILABLE(macos(10.15), ios(13.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface AVMetadataSalientObject : AVMetadataObject <NSCopying>

/*!
 @property objectID
 @abstract
    A unique number associated with the receiver.

 @discussion
    The value of this property is an NSInteger indicating the unique identifier of this object in the picture. When a new object enters the picture, it is assigned a new unique identifier. objectIDs are not re-used as object leave the picture and new ones enter. Objects that leave the picture then re-enter are assigned a new objectID.
 */
@property(readonly) NSInteger objectID;

@end


/*!
 @constant AVMetadataObjectTypeFace
 @abstract
    An identifier for an instance of AVMetadataFaceObject.
 
 @discussion
    AVMetadataFaceObject objects return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeFace API_AVAILABLE(macos(10.10), ios(6.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);


#pragma mark - AVMetadataFaceObject

@class AVMetadataFaceObjectInternal;

/*!
 @class AVMetadataFaceObject
 @abstract
    AVMetadataFaceObject is a concrete subclass of AVMetadataObject defining the features of a detected face.
 
 @discussion
    AVMetadataFaceObject represents a single detected face in a picture. It is an immutable object describing the various features found in the face.
 
    On supported platforms, AVCaptureMetadataOutput outputs arrays of detected face objects. See AVCaptureOutput.h.
 */
API_AVAILABLE(macos(10.10), ios(6.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMetadataFaceObject : AVMetadataObject <NSCopying>
{
@private
    AVMetadataFaceObjectInternal *_internal;
}

/*!
 @property faceID
 @abstract
    A unique number associated with the receiver.
 
 @discussion
    The value of this property is an NSInteger indicating the unique identifier of this face in the picture. When a new face enters the picture, it is assigned a new unique identifier. faceIDs are not re-used as faces leave the picture and new ones enter. Faces that leave the picture then re-enter are assigned a new faceID.
 */
@property(readonly) NSInteger faceID;

/*!
 @property hasRollAngle
 @abstract
    A BOOL indicating whether the rollAngle property is valid for this receiver.
 */
@property(readonly) BOOL hasRollAngle;

/*!
 @property rollAngle
 @abstract
    The roll angle of the face in degrees.
 
 @discussion
    The value of this property is a CGFloat indicating the face's angle of roll (or tilt) in degrees. A value of 0.0 indicates that the face is level in the picture. If -hasRollAngle returns NO, then reading this property throws an NSGenericException.
 */
@property(readonly) CGFloat rollAngle;

/*!
 @property hasYawAngle
 @abstract
    A BOOL indicating whether the yawAngle property is valid for this receiver.
 */
@property(readonly) BOOL hasYawAngle;

/*!
 @property yawAngle
 @abstract
    The yaw angle of the face in degrees.
 
 @discussion
    The value of this property is a CGFloat indicating the face's angle of yaw (or turn) in degrees. A value of 0.0 indicates that the face is straight on in the picture. If -hasYawAngle returns NO, then reading this property throws an NSGenericException.
 */
@property(readonly) CGFloat yawAngle;

@end


/*!
 @constant AVMetadataObjectTypeUPCECode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeUPCECode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from UPC-E codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeUPCECode API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeCode39Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeCode39Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Code 39 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeCode39Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeCode39Mod43Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeCode39Mod43Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Code 39 mod 43 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeCode39Mod43Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeEAN13Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeEAN13Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from EAN-13 (including UPC-A) codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeEAN13Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeEAN8Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeEAN8Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from EAN-8 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeEAN8Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeCode93Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeCode93Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Code 93 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeCode93Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeCode128Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeCode128Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Code 128 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeCode128Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypePDF417Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypePDF417Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from PDF417 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypePDF417Code API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeQRCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeQRCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from QR codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeQRCode API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeAztecCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeAztecCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Aztec codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeAztecCode API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeInterleaved2of5Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeInterleaved2of5Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Interleaved 2 of 5 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeInterleaved2of5Code API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeITF14Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeITF14Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from ITF14 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeITF14Code API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeDataMatrixCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeDataMatrixCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from DataMatrix codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeDataMatrixCode API_AVAILABLE(macos(10.15), ios(8.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeCodabarCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeCodabarCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from Codabar codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeCodabarCode NS_SWIFT_NAME(codabar) API_AVAILABLE(macos(12.3), ios(15.4), macCatalyst(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeGS1DataBarCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeGS1DataBarCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from GS1DataBar codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeGS1DataBarCode NS_SWIFT_NAME(gs1DataBar) API_AVAILABLE(macos(12.3), ios(15.4), macCatalyst(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeGS1DataBarExpandedCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeGS1DataBarExpandedCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from GS1DataBarExpanded codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeGS1DataBarExpandedCode NS_SWIFT_NAME(gs1DataBarExpanded) API_AVAILABLE(macos(12.3), ios(15.4), macCatalyst(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeGS1DataBarLimitedCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeGS1DataBarLimitedCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from GS1DataBarLimited codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeGS1DataBarLimitedCode NS_SWIFT_NAME(gs1DataBarLimited) API_AVAILABLE(macos(12.3), ios(15.4), macCatalyst(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeMicroQRCode
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeMicroQRCode.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from MicroQR codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeMicroQRCode NS_SWIFT_NAME(microQR) API_AVAILABLE(macos(12.3), ios(15.4), macCatalyst(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMetadataObjectTypeMicroPDF417Code
 @abstract
    An identifier for an instance of AVMetadataMachineReadableCodeObject having a type AVMetadataObjectTypeMicroPDF417Code.
 
 @discussion
    AVMetadataMachineReadableCodeObject objects generated from MicroPDF417 codes return this constant as their type.
 */
AVF_EXPORT AVMetadataObjectType const AVMetadataObjectTypeMicroPDF417Code NS_SWIFT_NAME(microPDF417) API_AVAILABLE(macos(12.3), ios(15.4), macCatalyst(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);


#pragma mark - AVMetadataMachineReadableCodeObject

@class AVMetadataMachineReadableCodeObjectInternal;

/*!
 @class AVMetadataMachineReadableCodeObject
 @abstract
    AVMetadataMachineReadableCodeObject is a concrete subclass of AVMetadataObject defining the features of a detected one-dimensional or two-dimensional barcode.
 
 @discussion
    AVMetadataMachineReadableCodeObject represents a single detected machine readable code in a picture. It is an immutable object describing the features and payload of a barcode.
 
    On supported platforms, AVCaptureMetadataOutput outputs arrays of detected machine readable code objects. See AVCaptureMetadataOutput.h.
 */
API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMetadataMachineReadableCodeObject : AVMetadataObject
{
@private
    AVMetadataMachineReadableCodeObjectInternal *_internal;
}

/*!
 @property corners
 @abstract
    The points defining the (X,Y) locations of the corners of the machine-readable code.
 
 @discussion
    The value of this property is an NSArray of NSDictionaries, each of which has been created from a CGPoint using CGPointCreateDictionaryRepresentation(), representing the coordinates of the corners of the object with respect to the image in which it resides. If the metadata originates from video, the points may be expressed as scalar values from 0. - 1. The points in the corners differ from the bounds rectangle in that bounds is axis-aligned to orientation of the captured image, and the values of the corners reside within the bounds rectangle. The points are arranged in counter-clockwise order (clockwise if the code or image is mirrored), starting with the top-left of the code in its canonical orientation.
 */
@property(readonly) NSArray<NSDictionary *> *corners;

/*!
 @property stringValue
 @abstract
    Returns the receiver's errorCorrectedData decoded into a human-readable string.
 
 @discussion
    The value of this property is an NSString created by decoding the binary payload according to the format of the machine readable code. Returns nil if a string representation cannot be created from the payload.
 */
@property(readonly, nullable) NSString *stringValue;

@end


@class CIBarcodeDescriptor;

API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMetadataMachineReadableCodeObject (AVMetadataMachineReadableCodeDescriptor)

/*!
 @property descriptor
 @abstract
    An abstract representation of a machine readable code's symbol attributes.
 
 @discussion
    The value may be nil if an abstract representation of a machine readable code object is not defined for the code type or could not be detected.
 */
@property(readonly, nullable) CIBarcodeDescriptor *descriptor API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0), tvos(11.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVMetadataObject.h>
#endif
