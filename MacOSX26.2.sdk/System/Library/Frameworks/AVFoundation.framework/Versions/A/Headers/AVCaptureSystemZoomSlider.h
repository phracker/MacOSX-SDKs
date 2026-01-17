#if !__has_include(<AVFCapture/AVCaptureSystemZoomSlider.h>)
/*
    File:  AVCaptureSystemZoomSlider.h
 
    Framework:  AVFoundation
 
    Copyright 2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureControl.h>
#import <AVFoundation/AVCaptureDevice.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVCaptureSystemZoomSlider
 @abstract
    The system's recommended continuous zoom control for `-[AVCaptureDevice videoZoomFactor]`.
 
 @discussion
    `AVCaptureSystemZoomSlider` uses the range specified by the `systemRecommendedVideoZoomRange` on the `activeFormat` from the `AVCaptureDevice` specified during initialization. As the device's `activeFormat` changes, the slider updates its range with the new format's `systemRecommendedVideoZoomRange`.
 
    Controls may be added to an `AVCaptureSession` using `-[AVCaptureSession addControl:]`.
 */
API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureSystemZoomSlider : AVCaptureControl

/*!
 @method initWithDevice:
 @abstract
    Initializes an `AVCaptureSystemZoomSlider` for controlling `device`.
 
 @param device
    The device to control.
 
 @discussion
    `AVCaptureSystemZoomSlider` may only be initialized with `AVCaptureDevice` instances that support setting `videoZoomFactor`, otherwise an `NSInvalidArgumentException` is thrown.
 */
- (instancetype)initWithDevice:(AVCaptureDevice *)device;

/*!
 @method initWithDevice:action
 @abstract
    Initializes an `AVCaptureSystemZoomSlider` for controlling `device` with a `@MainActor` `action` for handling `videoZoomFactor` changes.
 
 @param device
    The device to control.
 @param action
    An action called on `@MainActor` to handle `videoZoomFactor` changes by `AVCaptureSystemZoomSlider`.
 
 @discussion
    `action` is **only** called when `videoZoomFactor` is changed by this control. Clients should not change `videoZoomFactor` on the device when `action` is called.
 
    If you need to react to other sources of `videoZoomFactor` changes like `rampToVideoZoomFactor:withRate:` you will still need to use key-value observation.
 
    `AVCaptureSystemZoomSlider` may only be initialized with `AVCaptureDevice` instances that support setting `videoZoomFactor`, otherwise an `NSInvalidArgumentException` is thrown.
 */
- (instancetype)initWithDevice:(AVCaptureDevice *)device action:(NS_SWIFT_UI_ACTOR void (^)(CGFloat videoZoomFactor))action;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureSystemZoomSlider.h>
#endif
