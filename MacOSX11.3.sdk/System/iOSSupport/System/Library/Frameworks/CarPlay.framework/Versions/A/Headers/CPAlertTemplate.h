//
//  CPAlertTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPTemplate.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPAlertTemplate represents a modal alert that must be dismissed with a button press
 before the user may return to using the app.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPAlertTemplate : CPTemplate

/**
 Initialize a @c CPAlertTemplate by specifying a list of title variants and at least one action.

 @param titleVariants An array of strings, ordered longest to shortest. The template will display
 the longest string that fits in the available space on the current size of the car screen,
 dropping down to shorter strings as necessary.
 
 @param actions An array of alert actions to display in this alert template. You must specify at
 least one action.
 */
- (instancetype)initWithTitleVariants:(NSArray<NSString *> *)titleVariants
                              actions:(NSArray <CPAlertAction *> *)actions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, readonly) NSArray<NSString *> *titleVariants;

#pragma mark - Actions

/**
 Maximum number of action buttons that may appear in any @c CPAlertTemplate.
 If you add more than this number of buttons, only the most recently-added buttons
 (up to this count) will be kept.
*/
@property (nonatomic, class, readonly) NSUInteger maximumActionCount API_AVAILABLE(ios(14.0));

@property (nonatomic, strong, readonly) NSArray <CPAlertAction *> *actions;

@end

NS_ASSUME_NONNULL_END
