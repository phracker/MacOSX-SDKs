/*
    File:  AVUtilities.h
	
    Framework:  AVFoundation
	
    Copyright 2010-2015 Apple Inc. All rights reserved.
	
 */

#import <AVFoundation/AVBase.h>

#import <CoreGraphics/CGBase.h>
#import <CoreGraphics/CGGeometry.h>

/*!
 @function					AVMakeRectWithAspectRatioInsideRect
 @abstract					Returns a scaled CGRect that maintains the aspect ratio specified by a CGSize within a bounding CGRect.
 @discussion				This is useful when attempting to fit the presentationSize property of an AVPlayerItem within the bounds of another CALayer. 
							You would typically use the return value of this function as an AVPlayerLayer frame property value. For example:
							myPlayerLayer.frame = AVMakeRectWithAspectRatioInsideRect(myPlayerItem.presentationSize, mySuperLayer.bounds);
 @param aspectRatio			The width & height ratio, or aspect, you wish to maintain.
 @param	boundingRect		The bounding CGRect you wish to fit into. 
 */

AVF_EXPORT CGRect AVMakeRectWithAspectRatioInsideRect(CGSize aspectRatio, CGRect boundingRect) NS_AVAILABLE(10_7, 4_0);
