//
//  CPInstrumentClusterController.h
//  CarPlay
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CPInstrumentClusterControllerDelegate;

typedef NS_ENUM(NSUInteger, CPInstrumentClusterSetting) {
    CPInstrumentClusterSettingUnspecified,
    CPInstrumentClusterSettingEnabled,
    CPInstrumentClusterSettingDisabled,
    CPInstrumentClusterSettingUserPreference,
} API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos, watchos, tvos);

API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPInstrumentClusterController : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, weak) id<CPInstrumentClusterControllerDelegate> delegate;

/**
   The UIWindow created for this CPInstrumentClusterController
*/
@property (nullable, nonatomic, strong, readonly) UIWindow *instrumentClusterWindow;

@property (nonatomic, readonly) CPInstrumentClusterSetting speedLimitSetting;
@property (nonatomic, readonly) CPInstrumentClusterSetting compassSetting;

/**
 inactiveDescriptionVariants is an array of @c NSString to be displayed when the user is not actively navigating,
 arranged from most to least preferred.
 */
@property (nonatomic, copy) NSArray <NSString *> *inactiveDescriptionVariants;

/**
 attributedInactiveDescriptionVariants is an array of @c NSAttributedString to be displayed when the user is not actively navigating,
 arranged from most to least preferred.
 
 @c attributedInactiveDescriptionVariants will be preferred over inactiveDescriptionVariants.
 
 Only one attribute is presently supported: text attachments. You may annotate the string with an image
 by including a text attachment. The maximum text attachment image size is 64x16 points.

 @warning All attributes other than text attachment attributes will be removed from your attributed string.

 @see +[NSAttributedString attributedStringWithAttachment:], -[NSTextAttachment image]
 */
@property (nonatomic, copy) NSArray <NSAttributedString *> *attributedInactiveDescriptionVariants;

@end

API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPInstrumentClusterControllerDelegate <NSObject>

- (void)instrumentClusterControllerDidConnectWindow:(UIWindow *)instrumentClusterWindow;
- (void)instrumentClusterControllerDidDisconnectWindow:(UIWindow *)instrumentClusterWindow;

@optional

- (void)instrumentClusterControllerDidZoomIn:(CPInstrumentClusterController *)instrumentClusterController;
- (void)instrumentClusterControllerDidZoomOut:(CPInstrumentClusterController *)instrumentClusterController;

- (void)instrumentClusterController:(CPInstrumentClusterController *)instrumentClusterController didChangeCompassSetting:(CPInstrumentClusterSetting)compassSetting;
- (void)instrumentClusterController:(CPInstrumentClusterController *)instrumentClusterController didChangeSpeedLimitSetting:(CPInstrumentClusterSetting)speedLimitSetting;

@end

NS_ASSUME_NONNULL_END
