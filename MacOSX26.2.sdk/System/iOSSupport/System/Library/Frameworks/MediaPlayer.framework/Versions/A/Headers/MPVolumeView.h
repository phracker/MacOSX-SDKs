//
//  MPVolumeView.h
//  MediaPlayer
//
//  Copyright 2008-2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>

#if MP_HAS_HEADER(UIKit, UIView.h)

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

MP_UNAVAILABLE_BEGIN(watchos, macos)

MP_API(ios(2.0))
@interface MPVolumeView : UIView <NSCoding>

@property (nonatomic) BOOL showsVolumeSlider MP_API(ios(4.2)); // Default is YES.
@property (nonatomic) BOOL showsRouteButton MP_DEPRECATED("Use AVRoutePickerView instead.", ios(4.2, 13.0)) API_UNAVAILABLE(visionos);

// Returns YES if wireless routes (AirPlay, Bluetooth, etc) are available for user selection.
// Note that the view must be in present in a window hierarchy in order to discover some types of wireless routes.
@property (nonatomic, readonly, getter=areWirelessRoutesAvailable) BOOL wirelessRoutesAvailable MP_DEPRECATED("Use AVRouteDetector.multipleRoutesDetected instead.", ios(7.0, 13.0)) API_UNAVAILABLE(visionos);

// Returns YES if a wireless route is active.
@property (nonatomic, readonly, getter=isWirelessRouteActive) BOOL wirelessRouteActive MP_DEPRECATED("Use AVPlayer.externalPlaybackActive instead.", ios(7.0, 13.0)) API_UNAVAILABLE(visionos);

// Volume slider customization

- (void)setMinimumVolumeSliderImage:(nullable UIImage *)image forState:(UIControlState)state MP_API(ios(6.0));
- (void)setMaximumVolumeSliderImage:(nullable UIImage *)image forState:(UIControlState)state MP_API(ios(6.0));
- (void)setVolumeThumbImage:(nullable UIImage *)image forState:(UIControlState)state MP_API(ios(6.0));

- (nullable UIImage *)minimumVolumeSliderImageForState:(UIControlState)state MP_API(ios(6.0));
- (nullable UIImage *)maximumVolumeSliderImageForState:(UIControlState)state MP_API(ios(6.0));
- (nullable UIImage *)volumeThumbImageForState:(UIControlState)state MP_API(ios(6.0));

// Sets the image for the EU volume limit. When appropriate, this image will be displayed on top of the
// maximumVolumeSliderImage. It must be visually distinct from the maximumVolumeSliderImage, and use
// a color similar to the default, to convey a sense of warning to the user. The same image is used for
// all control states. For debugging purposes, switch on the "EU Volume Limit" setting in the Developer
// menu of the Settings application to always enable the volume limit.
@property (nonatomic, strong, nullable) UIImage *volumeWarningSliderImage MP_DEPRECATED("This is no longer supported", ios(7.0, 17.0))
    API_UNAVAILABLE(visionos);

- (CGRect)volumeSliderRectForBounds:(CGRect)bounds MP_API(ios(6.0));
- (CGRect)volumeThumbRectForBounds:(CGRect)bounds volumeSliderRect:(CGRect)rect value:(float)value MP_API(ios(6.0));

// Route button customization

- (void)setRouteButtonImage:(nullable UIImage *)image forState:(UIControlState)state
    MP_DEPRECATED("Use AVRoutePickerView.routePickerButtonStyle instead.", ios(6.0, 13.0))
    API_UNAVAILABLE(visionos);
- (nullable UIImage *)routeButtonImageForState:(UIControlState)state
    MP_DEPRECATED("See AVRoutePickerView for possible replacements.", ios(6.0, 13.0))
    API_UNAVAILABLE(visionos);

- (CGRect)routeButtonRectForBounds:(CGRect)bounds
    MP_DEPRECATED("See AVRoutePickerView for possible replacements.", ios(6.0, 13.0))
    API_UNAVAILABLE(visionos);

@end

// Posted when the wirelessRoutesAvailable property changes.
MP_EXTERN NSString * const MPVolumeViewWirelessRoutesAvailableDidChangeNotification
    MP_DEPRECATED("Use AVRouteDetectorMultipleRoutesDetectedDidChangeNotification instead.", ios(7.0, 13.0))
    API_UNAVAILABLE(visionos);

// Posted when the wirelessRouteActive property changes.
MP_EXTERN NSString * const MPVolumeViewWirelessRouteActiveDidChangeNotification
    MP_DEPRECATED("Use AVPlayer.externalPlaybackActive KVO instead.", ios(7.0, 13.0))
    API_UNAVAILABLE(visionos);

MP_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

#endif
