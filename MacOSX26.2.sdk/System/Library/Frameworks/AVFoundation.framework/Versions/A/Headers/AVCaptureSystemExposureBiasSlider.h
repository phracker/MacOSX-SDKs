#if !__has_include(<AVFCapture/AVCaptureSystemExposureBiasSlider.h>)
/*
    File:  AVCaptureSystemExposureBiasSlider.h
 
    Framework:  AVFoundation
 
    Copyright 2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureControl.h>
#import <AVFoundation/AVCaptureDevice.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVCaptureSystemExposureBiasSlider
 @abstract
    The system's recommended continuous exposure bias control for `-[AVCaptureDevice exposureTargetBias]`.
 
 @discussion
    `AVCaptureSystemExposureBiasSlider` uses the range specified by `systemRecommendedExposureBiasRange` on the `activeFormat` from the `AVCaptureDevice` specified during initialization. As the device's `activeFormat` changes, the slider updates its range with the new format's `systemRecommendedExposureBiasRange`.
    
    Controls may be added to an `AVCaptureSession` using `-[AVCaptureSession addControl:]`.
 */
API_AVAILABLE(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureSystemExposureBiasSlider : AVCaptureControl

/*!
 @method initWithDevice:
 @abstract
    Initializes an `AVCaptureSystemExposureBiasSlider` for controlling `device`.
 
 @param device
    The device to control.
 
 @discussion
    `AVCaptureSystemExposureBiasSlider` may only be initialized with `AVCaptureDevice` instances that support setting `exposureTargetBias`, otherwise an `NSInvalidArgumentException` is thrown.
 */
- (instancetype)initWithDevice:(AVCaptureDevice *)device;

/*!
 @method initWithDevice:action
 @abstract
    Initializes an `AVCaptureSystemExposureBiasSlider` for controlling `device` with a `@MainActor` `action` for handling `exposureTargetBias` changes.
 
 @param device
    The device to control.
 @param action
    An action called on `@MainActor` to handle `exposureTargetBias` changes by `AVCaptureSystemExposureBiasSlider`.
 
 @discussion
    `action` is **only** called when `exposureTargetBias` is changed by this control. Clients should not change `exposureTargetBias` on the device when `action` is called.
 
    If you need to react to other sources of `exposureTargetBias` changes, you will still need to use key-value observation.
 
    `AVCaptureSystemExposureBiasSlider` may only be initialized with `AVCaptureDevice` instances that support setting `exposureTargetBias`, otherwise an `NSInvalidArgumentException` is thrown.
 */
- (instancetype)initWithDevice:(AVCaptureDevice *)device action:(NS_SWIFT_UI_ACTOR void (^)(float exposureTargetBias))action;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureSystemExposureBiasSlider.h>
#endif
