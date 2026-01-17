/* CoreImage - CIFeature.h
 
 Copyright (c) 2010 Apple Computer, Inc.
 All rights reserved. */

#import <Foundation/Foundation.h>

#import <CoreImage/CoreImageDefines.h>

/** Generic feature found by a CIDetector. */
CORE_IMAGE_CLASS_EXPORT
@interface CIFeature : NSObject {}

/** The type of the feature. */
@property (readonly, retain) NSString *type;
/** The bounds of the feature in the image it was detected in. */
@property (readonly, assign) CGRect bounds;

@end


/** Specifies the type of a feature that is a face. */
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeFace;
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeRectangle;

/** A face feature found by a CIDetector.
 All positions are relative to the original image. */
CORE_IMAGE_CLASS_EXPORT
@interface CIFaceFeature : CIFeature
{
	CGRect bounds;
	BOOL hasLeftEyePosition;
	CGPoint leftEyePosition;
	BOOL hasRightEyePosition;
	CGPoint rightEyePosition;
	BOOL hasMouthPosition;
	CGPoint mouthPosition;
	

	BOOL hasTrackingID;
	int trackingID;
	BOOL hasTrackingFrameCount;
	int trackingFrameCount;
	
	BOOL hasFaceAngle;
	float faceAngle;
	
	BOOL hasSmile;
	BOOL leftEyeClosed;
	BOOL rightEyeClosed;
	
}

@property (readonly, assign) CGRect bounds;
@property (readonly, assign) BOOL hasLeftEyePosition;
@property (readonly, assign) CGPoint leftEyePosition;
@property (readonly, assign) BOOL hasRightEyePosition;
@property (readonly, assign) CGPoint rightEyePosition;
@property (readonly, assign) BOOL hasMouthPosition;
@property (readonly, assign) CGPoint mouthPosition;

@property (readonly, assign) BOOL hasTrackingID;
@property (readonly, assign) int trackingID;
@property (readonly, assign) BOOL hasTrackingFrameCount;
@property (readonly, assign) int trackingFrameCount;

@property (readonly, assign) BOOL hasFaceAngle;
@property (readonly, assign) float faceAngle;

@property (readonly, assign) BOOL hasSmile;
@property (readonly, assign) BOOL leftEyeClosed;
@property (readonly, assign) BOOL rightEyeClosed;

@end


/** A rectangle feature found by a CIDetector.
 All positions are relative to the original image. */
CORE_IMAGE_CLASS_EXPORT
@interface CIRectangleFeature : CIFeature
{
	CGRect bounds;
	CGPoint topLeft;
	CGPoint topRight;
	CGPoint bottomLeft;
	CGPoint bottomRight;
	
}

@property (readonly, assign) CGRect bounds;
@property (readonly, assign) CGPoint topLeft;
@property (readonly, assign) CGPoint topRight;
@property (readonly, assign) CGPoint bottomLeft;
@property (readonly, assign) CGPoint bottomRight;

@end

/** A barcode feature found by a CIDetector
 All positions are relative to the original image. */

CORE_IMAGE_CLASS_EXPORT
@interface CIQRCodeFeature : CIFeature
{
    CGRect bounds;
	CGPoint topLeft;
	CGPoint topRight;
	CGPoint bottomLeft;
	CGPoint bottomRight;
    NSString* messageString;
}

@property (readonly, assign) CGRect bounds;
@property (readonly, assign) CGPoint topLeft;
@property (readonly, assign) CGPoint topRight;
@property (readonly, assign) CGPoint bottomLeft;
@property (readonly, assign) CGPoint bottomRight;
@property (readonly, copy) NSString* messageString;


@end

