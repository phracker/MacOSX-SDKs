//
//  ARVideoFormat.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVCaptureDevice.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCapturePhotoSettings;

API_AVAILABLE(ios(11.3))
NS_SWIFT_NAME(ARConfiguration.VideoFormat)
@interface ARVideoFormat : NSObject <NSCopying>

/**
 Indicates the physical position of an AVCaptureDevice's hardware on the system.
 */
@property (nonatomic, readonly) AVCaptureDevicePosition captureDevicePosition
        API_AVAILABLE(ios(13.0));

/**
 Indicates the type of AVCaptureDevice.
 */
@property (nonatomic, readonly) AVCaptureDeviceType captureDeviceType
        API_AVAILABLE(ios(14.5));

/**
 Image resolution.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 Frame rate.
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/**
 Indicates if the video format is recommended for capturing high resolution frames.
 */
@property (nonatomic, readonly) BOOL isRecommendedForHighResolutionFrameCapturing API_AVAILABLE(ios(16.0));

/**
 Indicates if the video format supports high dynamic range (HDR) streaming.
 */
@property (nonatomic, readonly, getter=isVideoHDRSupported) BOOL videoHDRSupported API_AVAILABLE(ios(16.0));

/**
 The color space ARKit uses to configure the capture session when this video format is selected.
 */
@property (nonatomic, readonly) AVCaptureColorSpace defaultColorSpace API_AVAILABLE(ios(26.0));

/**
 The default AVCapturePhotoSettings object that ARKit uses when capturing a high resolution frame using this video format.
 @discussion Calling this getter will return a new instance that may be mutated to customize settings. Pass that instance to
 `captureHighResolutionFrameUsingPhotoSettings:completion:` to capture a high resolution frame with custom settings.
 @see [ARSession captureHighResolutionFrameUsingPhotoSettings:completion:]
 @return An AVCapturePhotoSettings object.
 */
@property (nonatomic, readonly) AVCapturePhotoSettings *defaultPhotoSettings API_AVAILABLE(ios(26.0));

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
