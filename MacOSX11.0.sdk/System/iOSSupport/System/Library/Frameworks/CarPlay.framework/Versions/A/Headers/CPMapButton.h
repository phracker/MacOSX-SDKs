//
//  CPMapButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMapButton : NSObject <NSSecureCoding>

/**
 Initializes a new map button.

 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.
 */
- (instancetype)initWithHandler:(void (^ _Nullable)(CPMapButton *mapButton))handler NS_DESIGNATED_INITIALIZER;

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 A Boolean value indicating whether the button is hidden.

 @discussion Setting the value of this property to @c YES hides the button and setting it to @c NO shows it. The default value is @c NO.
 */
@property (nonatomic, assign, getter=isHidden) BOOL hidden;

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 */
@property (nullable, nonatomic, strong) UIImage *image;

/**
 The image displayed on the button when focused.

 @discussion The button will automatically create a focused image using the alpha values from the source image.

 @note If unspecified, the button will use the default @c image
 */
@property (nullable, nonatomic, strong) UIImage *focusedImage;

@end

NS_ASSUME_NONNULL_END
