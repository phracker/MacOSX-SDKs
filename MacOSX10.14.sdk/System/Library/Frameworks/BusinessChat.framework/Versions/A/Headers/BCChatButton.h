//
//  BCChatButton.h
//  BusinessChat
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#import <TargetConditionals.h>
#if TARGET_OS_OSX
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 BCChatButtonStyle is used to define the visual style of the button.
 */
typedef NS_ENUM(NSInteger, BCChatButtonStyle) { BCChatButtonStyleLight = 0, BCChatButtonStyleDark } NS_SWIFT_NAME(BCChatButton.Style) API_AVAILABLE(macos(10.13.4), ios(11.3));

/**
 BCChatButton is a button allowing users to initiate a conversation with a business.
 */
API_AVAILABLE(macos(10.13.4), ios(11.3))
#if TARGET_OS_OSX
@interface BCChatButton : NSControl
#else
@interface BCChatButton : UIControl
#endif

/**
 Creates and returns a BCChatButton configured for a given style.

 @param style The visual style of the button.

 @return BCChatButton instance.
 */
- (instancetype)initWithStyle:(BCChatButtonStyle)style API_AVAILABLE(macos(10.13.4), ios(11.3))NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
