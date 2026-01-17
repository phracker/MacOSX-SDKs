//
//  CPAlertAction.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, CPAlertActionStyle) {
    CPAlertActionStyleDefault = 0, // A style that indicates a default action.
    CPAlertActionStyleCancel,      // A style that indicates the action will cancel and leave data unchanged.
    CPAlertActionStyleDestructive, // A style that indicates the button might change or delete data.
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

/**
 @c CPAlertAction represents a single action that appears inside of a @c CPActionSheetTemplate or @c CPAlertTemplate.

 The style of the parent template and the style of the @c CPAlertAction will together
 determine the action's appearance.

 The action has a customizable title, style, and a block callback
 that is invoked when the user taps this button.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPAlertAction : NSObject <NSSecureCoding>

typedef void (^CPAlertActionHandler) (CPAlertAction *);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Create an alert action with a title, display style, and a callback handler that is invoked
 when the user taps this action.
 */
- (instancetype)initWithTitle:(NSString *)title
                        style:(CPAlertActionStyle)style
                      handler:(CPAlertActionHandler)handler;

/**
 Create an alert action with a title, a custom action color, and a callback handler that is invoked
 when the user taps this action.
 
 The system will automatically determine if the provided color meets contrast requirements.
 If the provided color does not meet contrast requirements, the system default will be used.
 Font color will automatically be adjusted by the system to correspond with this color.
 Alpha values will be ignored.
 */
- (instancetype)initWithTitle:(NSString *)title
                        color:(UIColor *)color
                      handler:(CPAlertActionHandler)handler API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

@property (nonatomic, copy, readonly) NSString *title;
@property (nonatomic, assign, readonly) CPAlertActionStyle style;
@property (nonatomic, copy, readonly) CPAlertActionHandler handler;
@property (nonatomic, copy, readonly, nullable) UIColor *color API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

@end

NS_ASSUME_NONNULL_END
