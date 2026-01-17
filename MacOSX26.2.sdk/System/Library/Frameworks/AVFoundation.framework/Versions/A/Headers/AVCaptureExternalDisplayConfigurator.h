#if !__has_include(<AVFCapture/AVCaptureExternalDisplayConfigurator.h>)
/*
    File:  AVCaptureExternalDisplayConfigurator.h
 
    Framework:  AVFoundation
 
    Copyright 2025 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>

#if __has_include(<QuartzCore/QuartzCore.h>)
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVCaptureDevice.h>
#import <CoreMedia/CMFormatDescription.h>

NS_ASSUME_NONNULL_BEGIN

/// A class you use to specify a configuration to your external display configurator.
///
/// Using an ``AVCaptureExternalDisplayConfiguration``, you direct your ``AVCaptureExternalDisplayConfigurator`` how to configure an external display to match your device's active video format.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureExternalDisplayConfiguration : NSObject

/// A property indicating whether the frame rate of the external display should be configured to match the camera's frame rate.
///
/// If you want to configure your ``AVCaptureVideoPreviewLayer`` to match its source ``AVCaptureDevice/activeVideoMinFrameDuration``, set ``shouldMatchFrameRate`` to `true`. The default value is `false`.
@property(nonatomic, assign) BOOL shouldMatchFrameRate;

/// A property indicating whether the color space of the configurator's preview layer should be preserved on the output display by avoiding color space conversions.
///
/// Set ``bypassColorSpaceConversion`` to `true` if you would like the configurator's  ``AVCaptureVideoPreviewLayer`` color space preserved on the output display. This is accomplished by setting the working color space to match the color space of the external display. The color properties of the ``CALayer`` remain untouched. The default value is `false`.
@property(nonatomic, assign) BOOL bypassColorSpaceConversion;

/// Your preferred external display resolution.
///
/// Use ``preferredResolution`` to set your desired resolution of the external display. When left at the default value of { 0, 0 },  the native resolution of the external display is used.
@property(nonatomic, assign) CMVideoDimensions preferredResolution;

@end

/// A configurator class allowing you to configure properties of an external display to match the camera's active video format.
///
/// An ``AVCaptureExternalDisplayConfigurator`` allows you to configure a connected external display to output a clean feed using a ``CALayer``. Using the configurator, you can opt into automatic adjustment of the external display’s color space and / or frame rate to match your device’s capture configuration. These adjustments are only applied to the external display, not to the device.
///
/// - Note: Not all displays support the same configuration options as the device’s capture formats. Your adjustments to the external display are applied with utmost effort to accurately represent the capture device. When your capture device's ``AVCaptureDevice/activeFormat`` is unavailable on the external display, the configurator automatically chooses the closest available format.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureExternalDisplayConfigurator : NSObject

AV_INIT_UNAVAILABLE

/// An external display configurator instance that attempts to synchronize the preview layer configuration with the device capture configuration.
///
/// - Parameter device: The device for which to monitor the configuration.
/// - Parameter previewLayer: The layer that is being used on an external display for displaying the camera preview.
/// - Parameter configuration: A configuration specifying which aspects of the camera's active format to monitor and configure on the external display.
/// - Returns: an ``AVCaptureExternalDisplayConfigurator`` instance.
///
/// An ``AVCaptureExternalDisplayConfigurator`` is only applicable to external displays. It determines which properties to configure on the external display based on your provided configuration (see ``AVCaptureExternalDisplayConfiguration``). The configurator observes changes to your camera''s configuration, and when changes are observed, it modifies the external display's properties to match.
///
/// If multiple configurators are linked to the same external display ,the last one created becomes the active configurator for the external display (see ``active``).
///
/// - Important: An `NSInvalidArgumentException` is thrown if any of the ``AVCaptureExternalDisplayConfiguration`` options are not supported.
- (instancetype)initWithDevice:(AVCaptureDevice *)device previewLayer:(CALayer *)previewLayer configuration:(AVCaptureExternalDisplayConfiguration *)configuration;

/// The device for which the coordinator configures the preview layer.
///
/// The value of this property is the ``AVCaptureDevice`` instance you provided when instantiating the configurator. ``AVCaptureExternalDisplayConfigurator`` holds a weak reference to the device. If the device is released, this property returns `nil`.
@property(nonatomic, readonly, nullable, weak) AVCaptureDevice *device;

/// The layer for which the configurator adjusts display properties to match the device's state.
///
/// The value of this property is the ``CALayer`` instance that you provided when instantiating the configurator. You may specify either an ``AVCaptureVideoPreviewLayer`` or another ``CALayer`` instance that displays a camera's video preview. ``AVCaptureExternalDisplayConfigurator``holds a weak reference to the layer. If the layer is released, this property returns `nil`.
@property(nonatomic, readonly, nullable, weak) CALayer *previewLayer;

/// This property tells you whether the configurator is actively configuring the external display.
///
/// When this property returns `true`, the external display is successfully configured to match the device. If it returns`false`, the configurator is not making any configuration changes to the external display. If another ``AVCaptureExternalDisplayConfigurator`` instance takes over the configuration of the external display, this property returns `false`.
@property(nonatomic, readonly, getter=isActive) BOOL active;

/// Forces the external display configurator to asynchronously stop configuring the external display.
///
/// Call ``stop`` to force the ``AVCaptureExternalDisplayConfigurator`` to asynchronously stop configuring the external display. Once stopped, the ``active`` property changes to `false` and the ``activeExternalDisplayFrameRate`` becomes 0.
- (void)stop;

/// The currently configured frame rate on the external display that's displaying the preview layer.
///
/// Observe this property to determine if the configured frame rate matches the max frame rate (``AVCaptureDevice/activeVideoMinFrameDuration``) of the device. When the ``active`` property becomes `false`, this property changes to 0.
@property(nonatomic, readonly) double activeExternalDisplayFrameRate;

/// Whether the external display supports matching frame rate to a capture device.
///
/// If `true`, you may instantiate a configurator with a configuration specifying ``AVCaptureExternalDisplayConfiguration/shouldMatchFrameRate`` set to `true`.
@property(class, readonly, getter=isMatchingFrameRateSupported) BOOL shouldMatchFrameRateSupported;

/// Whether the external display supports bypassing color space conversion.
///
/// If `true`, you may instantiate a configurator with a configuration specifying ``AVCaptureExternalDisplayConfiguration/bypassColorSpaceConversion`` set to `true`.
@property(class, readonly, getter=isBypassingColorSpaceConversionSupported) BOOL supportsBypassingColorSpaceConversion;

/// Whether the external display supports configuration to your preferred resolution.
///
/// If `true`, you may instantiate a configurator with a configuration specifying ``AVCaptureExternalDisplayConfiguration/preferredResolution`` set to `true`.
@property(class, readonly, getter=isPreferredResolutionSupported) BOOL supportsPreferredResolution;

@end

NS_ASSUME_NONNULL_END

#endif  // __has_include(<QuartzCore/QuartzCore.h>)

#else
#import <AVFCapture/AVCaptureExternalDisplayConfigurator.h>
#endif
