#if !__has_include(<AVFCore/AVGeometry.h>)
/*
	File:  AVGeometry.h
	
	Framework:  AVFoundation
	
	Copyright 2022 Apple Inc. All rights reserved.
	
 */

#import <AVFoundation/AVBase.h>

#import <Foundation/Foundation.h>

#import <CoreGraphics/CGBase.h>
#import <CoreGraphics/CGGeometry.h>
#import <CoreMedia/CMFormatDescription.h>

/*!
 @function					AVMakeRectWithAspectRatioInsideRect
 @abstract					Returns a scaled CGRect that maintains the aspect ratio specified by a CGSize within a bounding CGRect.
 @discussion				This is useful when attempting to fit the presentationSize property of an AVPlayerItem within the bounds of another CALayer. 
							You would typically use the return value of this function as an AVPlayerLayer frame property value. For example:
							myPlayerLayer.frame = AVMakeRectWithAspectRatioInsideRect(myPlayerItem.presentationSize, mySuperLayer.bounds);
 @param aspectRatio			The width & height ratio, or aspect, you wish to maintain.
 @param	boundingRect		The bounding CGRect you wish to fit into. 
 */

AVF_EXPORT CGRect AVMakeRectWithAspectRatioInsideRect(CGSize aspectRatio, CGRect boundingRect) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);


/*
	Utilities for packing and unpacking CMVideoDimension structs in NSValue objects
 */
@interface NSValue (NSValueCMVideoDimensionsExtensions)

/*!
 @method valueWithCMVideoDimensions
 @abstract
	Creates a NSValue object encoding a CMVideoDimensions struct value.
 
 @param dimensions
	The CMVideoDimensions struct to encode.
 @result
	An NSValue object encoding the provided dimensions.
 
 @discussion
	This extension simplifies converting CMVideoDimensions struct values into NSValue objects.
 */
+ (NSValue *)valueWithCMVideoDimensions:(CMVideoDimensions)dimensions API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
 @property CMVideoDimensionsValue
 @abstract
	Returns the CMVideoDimensions struct encoded by this object.
 
 @discussion
	This property simplifies accessing the contents of AVCaptureDeviceFormat.supportedMaxPhotoDimensions which are CMVideoDimension struct values encoded in NSValue objects.
 */
@property (readonly) CMVideoDimensions CMVideoDimensionsValue API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

@end

#else
#import <AVFCore/AVGeometry.h>
#endif
