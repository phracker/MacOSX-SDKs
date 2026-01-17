//
//  CPDashboardButton.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPDashboardButton : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initialize a button with title variants, optional subtitle variants, and image.

 @param titleVariants An array of title variants for this button, arranged from longest to shortest. You must provide at least one title.
 @param subtitleVariants An array of subtitle variants for this button, arranged from longest to shortest.
 @param image The image displayed on the button. It must be non-nil for the button to be displayed.
 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.
 The image must be non-nil and the title must be a non-zero length string for the button to be displayed.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants subtitleVariants:(NSArray <NSString *> *)subtitleVariants image:(UIImage *)image handler:(void (^ _Nullable)(CPDashboardButton *barButton))handler NS_DESIGNATED_INITIALIZER;

/**
 The image displayed on the button. Maximum supported size is 30x30 points.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 */
@property (nonatomic, readonly) UIImage *image;

/**
 An array of title variants for this button, arranged from most to least preferred.
 The system will select a title from your list of provided variants that fits the available space.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, readonly) NSArray <NSString *> *titleVariants;

/**
An array of subtitle variants for this button, arranged from most to least preferred.
The system will select a title from your list of provided variants that fits the available space.
The variant strings should be provided as localized, displayable content.
*/
@property (nonatomic, readonly) NSArray <NSString *> *subtitleVariants;

@end

NS_ASSUME_NONNULL_END
