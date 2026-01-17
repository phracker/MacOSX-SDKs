//
//  CPGridButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPGridButton : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initialize a button with a title and image.

 @param titleVariants An array of title variants for this button, arranged from most to least preferred. You must provide at least one title.
 @param image The image displayed on the button. It must be non-nil for the button to be displayed.
 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.

 The image must be non-nil and the title must be a non-zero length string for the button to be displayed.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants image:(UIImage *)image handler:(void (^ _Nullable)(CPGridButton *barButton))handler NS_DESIGNATED_INITIALIZER;

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, readonly) UIImage *image;

/**
 An array of title variants for this button, arranged from most to least preferred.
 The system will select a title from your list of provided variants that fits the available space.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, readonly) NSArray <NSString *> *titleVariants;

@end

NS_ASSUME_NONNULL_END
