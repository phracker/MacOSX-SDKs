//
//  CPNavigationAlert.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPImageSet.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Reasons why your navigation alert was dismissed.
 */
typedef NS_ENUM(NSUInteger, CPNavigationAlertDismissalContext) {
    CPNavigationAlertDismissalContextTimeout = 0,    // The banner was visible long enough to reach its timeout.
    CPNavigationAlertDismissalContextUserDismissed,  // The banner was dismissed in response to a user button press.
    CPNavigationAlertDismissalContextSystemDismissed // The banner was dismissed because of a request by the app.
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Your @c CPNavigationAlert may specify a duration for which the alert will be visible onscreen,
 or 0 for an alert that is visible indefinitely.

 For non-indefinite alerts, this is the minimum duration the alert will be visible.
 */
static NSTimeInterval const CPNavigationAlertMinimumDuration = 5;

/**
 @c CPNavigationAlert is a banner alert that can display map or navigation-related information to the user.
*/
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPNavigationAlert : NSObject <NSSecureCoding>

/**
 Fully specify a @c CPNavigationAlert with a title, image, primary and secondary action,
 and duration.

 @param titleVariants An array of titles. The system will select a title that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param subtitleVariants An array of subtitles. The system will select a subtitle that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param imageSet An optional @c CPImageSet to display in this navigation alert. Animated images are not supported.
 If an animated image is provided, only the first image from each image set will be used.

 @param primaryAction The alert must include at least one action button.

 @param secondaryAction An optional secondary button to display on the trailing edge of this alert.

 @param duration The duration for which this alert should be visible. Specify 0 for an alert
 that displays indefinitely.

 @return an initialized @c CPNavigationAlert.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(nullable NSArray <NSString *> *)subtitleVariants
                             imageSet:(nullable CPImageSet *)imageSet
                        primaryAction:(CPAlertAction *)primaryAction
                      secondaryAction:(nullable CPAlertAction *)secondaryAction
                             duration:(NSTimeInterval)duration API_DEPRECATED_WITH_REPLACEMENT("initWithTitleVariants:subtitleVariants:image:primaryAction:secondaryAction:duration", ios(12.0, 13.0)) API_UNAVAILABLE(macos, watchos, tvos);

- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(nullable NSArray <NSString *> *)subtitleVariants
                                image:(nullable UIImage *)image
                        primaryAction:(CPAlertAction *)primaryAction
                      secondaryAction:(nullable CPAlertAction *)secondaryAction
                             duration:(NSTimeInterval)duration;

/**
 The navigation alert may be updated with new title and subtitle variants, either
 after it has already been displayed on screen, or before its initial presentation on screen.

 Updating an alert that has been already been dismissed has no effect.

 @param newTitleVariants an updated array of title variants
 @param newSubtitleVariants an updated array of subtitle variants
 */
- (void)updateTitleVariants:(NSArray <NSString *> *)newTitleVariants
           subtitleVariants:(NSArray <NSString *> *)newSubtitleVariants;

@property (nonatomic, readonly, copy) NSArray <NSString *> *titleVariants;
@property (nonatomic, readonly, copy) NSArray <NSString *> *subtitleVariants;
@property (nullable, nonatomic, readonly, copy) CPImageSet *imageSet;
@property (nullable, nonatomic, readonly, copy) UIImage *image;
@property (nonatomic, readonly, strong) CPAlertAction *primaryAction;
@property (nullable, nonatomic, readonly, strong) CPAlertAction *secondaryAction;
@property (nonatomic, readonly) NSTimeInterval duration;

@end

NS_ASSUME_NONNULL_END
