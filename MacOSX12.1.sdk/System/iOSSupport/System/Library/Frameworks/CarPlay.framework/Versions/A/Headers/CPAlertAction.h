//
//  CPAlertAction.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, CPAlertActionStyle) {
    CPAlertActionStyleDefault = 0, // A style that indicates a default action.
    CPAlertActionStyleCancel,     // A style that indicates the action will cancel and leave data unchanged.
    CPAlertActionStyleDestructive // A style that indicates the button might change or delete data.
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 @c CPAlertAction represents a single action that appears inside of a @c CPActionSheetTemplate or @c CPAlertTemplate.

 The style of the parent template and the style of the @c CPAlertAction will together
 determine the action's appearance.

 The action has a customizable title, style, and a block callback
 that is invoked when the user taps this button.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
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

@property (nonatomic, copy, readonly) NSString *title;
@property (nonatomic, assign, readonly) CPAlertActionStyle style;
@property (nonatomic, copy, readonly) CPAlertActionHandler handler;

@end

NS_ASSUME_NONNULL_END
