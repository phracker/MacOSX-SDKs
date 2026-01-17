//
//  CPNowPlayingButton.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

extern CGSize const CPNowPlayingButtonMaximumImageSize;

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPNowPlayingButton : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initialize a now playing button with a handler. The handler will be called when the user
 selects this button.
 
 @note Your app should use this method in one of the six concrete subclasses of @c CPNowPlayingButton.
 Do not initialize this class directly.
 */
- (instancetype)initWithHandler:(void (^ _Nullable)(__kindof CPNowPlayingButton *))handler;

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 A Boolean value indicating whether the button is selected. When selected, the button draws with a selected appearance to
 indicate its selected state.
 
 @discussion Only custom image buttons may display a custom selected state. Other system-provided buttons, like repeat
 and shuffle, change their selected states depending on what your app reports for current repeat and shuffle states.
 */
@property (nonatomic, assign, getter=isSelected) BOOL selected;

@end

/**
 A now playing button that indicates the current shuffle mode for your app.
 */
@interface CPNowPlayingShuffleButton : CPNowPlayingButton
@end

/**
 A now playing button that can be used to allow the user to add the current
 playing item to a collection, like their library.
 */
@interface CPNowPlayingAddToLibraryButton : CPNowPlayingButton
@end

/**
 A now playing button that shows a callout-style action. For example,
 your app could present a @c CPActionSheetTemplate to show more actions
 when the user taps this button.
 */
@interface CPNowPlayingMoreButton : CPNowPlayingButton
@end

/**
 A now playing button that shows the current playback rate and allows
 the user to cycle between different playback rates provided by your app.
 */
@interface CPNowPlayingPlaybackRateButton : CPNowPlayingButton
@end

/**
 A now playing button that shows the current repeat state, like "once"
 or "all".
 */
@interface CPNowPlayingRepeatButton : CPNowPlayingButton
@end

/**
 A now playing button that shows a custom image provided by your app
 for any other custom actions on the now playing screen.
 */
@interface CPNowPlayingImageButton : CPNowPlayingButton

/**
 Initialize a button with a custom image.
 
 @param image A custom image for this button. The maximum image size is CPNowPlayingButtonMaximumImageSize; larger images will be scaled down.
 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.
 */
- (instancetype)initWithImage:(UIImage *)image
                      handler:(void (^ _Nullable)(__kindof CPNowPlayingButton *))handler;

/**
 The custom image, if any, displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 */
@property (nullable, nonatomic, readonly, strong) UIImage *image;

@end

NS_ASSUME_NONNULL_END
