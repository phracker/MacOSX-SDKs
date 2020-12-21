//
//  ARVideoFormat.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVCaptureDevice.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3))
NS_SWIFT_NAME(ARConfiguration.VideoFormat)
@interface ARVideoFormat : NSObject <NSCopying>

/**
 Indicates the physical position of an AVCaptureDevice's hardware on the system.
 */
@property (nonatomic, readonly) AVCaptureDevicePosition captureDevicePosition API_AVAILABLE(ios(13.0));

/**
 Image resolution.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 Frame rate.
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
