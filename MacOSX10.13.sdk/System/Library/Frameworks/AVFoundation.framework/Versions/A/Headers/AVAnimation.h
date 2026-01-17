/*
    File:  AVAnimation.h
 
    Framework:  AVFoundation
 
	Copyright 2010-2017 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreFoundation/CFDate.h>

/*!
 @constant					AVCoreAnimationBeginTimeAtZero
 @discussion				Use this constant to set the CoreAnimation's animation beginTime property to be time 0.
							The constant is a small, non-zero, positive value which avoids CoreAnimation
							from replacing 0.0 with CACurrentMediaTime().
*/
AVF_EXPORT const CFTimeInterval AVCoreAnimationBeginTimeAtZero NS_AVAILABLE(10_7, 4_0);

typedef NSString * AVLayerVideoGravity NS_STRING_ENUM;

/*!
	@constant		AVLayerVideoGravityResizeAspect
	@abstract		Preserve aspect ratio; fit within layer bounds.
	@discussion		AVLayerVideoGravityResizeAspect may be used when setting the videoGravity
                    property of an AVPlayerLayer or AVCaptureVideoPreviewLayer instance.
 */
AVF_EXPORT AVLayerVideoGravity const AVLayerVideoGravityResizeAspect NS_AVAILABLE(10_7, 4_0);


/*!
	@constant		AVLayerVideoGravityResizeAspectFill
	@abstract		Preserve aspect ratio; fill layer bounds.
    @discussion     AVLayerVideoGravityResizeAspectFill may be used when setting the videoGravity
                    property of an AVPlayerLayer or AVCaptureVideoPreviewLayer instance.
 */
AVF_EXPORT AVLayerVideoGravity const AVLayerVideoGravityResizeAspectFill NS_AVAILABLE(10_7, 4_0);

/*!
	@constant		AVLayerVideoGravityResize
	@abstract		Stretch to fill layer bounds.
    @discussion     AVLayerVideoGravityResize may be used when setting the videoGravity
                    property of an AVPlayerLayer or AVCaptureVideoPreviewLayer instance.
 */
AVF_EXPORT AVLayerVideoGravity const AVLayerVideoGravityResize NS_AVAILABLE(10_7, 4_0);
