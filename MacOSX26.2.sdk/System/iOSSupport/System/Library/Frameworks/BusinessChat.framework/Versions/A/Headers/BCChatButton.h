//
//  BCChatButton.h
//  BusinessChat
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#import <TargetConditionals.h>
#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 BCChatButtonStyle is used to define the visual style of the button.
 */
typedef NS_ENUM(NSInteger, BCChatButtonStyle) { BCChatButtonStyleLight = 0, BCChatButtonStyleDark } NS_SWIFT_NAME(BCChatButton.Style) API_DEPRECATED("", macos(10.13.4, 13.0), ios(11.3, 16.1));

/**
 BCChatButton is a button allowing users to initiate a conversation with a business.
 */
API_DEPRECATED("", macos(10.13.4, 13.0), ios(11.3, 16.1))
#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
@interface BCChatButton : NSControl
#else
@interface BCChatButton : UIControl
#endif

/**
 Creates and returns a BCChatButton configured for a given style.

 @param style The visual style of the button.

 @return BCChatButton instance.
 */
- (instancetype)initWithStyle:(BCChatButtonStyle)style NS_DESIGNATED_INITIALIZER API_DEPRECATED("", macos(10.13.4, 13.0), ios(11.3, 16.1));

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER API_DEPRECATED("", macos(10.13.4, 13.0), ios(11.3, 16.1));

@end

NS_ASSUME_NONNULL_END
