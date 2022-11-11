//
//  MEMessageAction.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger,  MEMessageActionMessageColor) {
    MEMessageActionMessageColorNone,
    MEMessageActionMessageColorGreen,
    MEMessageActionMessageColorYellow,
    MEMessageActionMessageColorOrange,
    MEMessageActionMessageColorRed,
    MEMessageActionMessageColorPurple,
    MEMessageActionMessageColorBlue,
    MEMessageActionMessageColorGray,
} NS_SWIFT_NAME(MEMessageAction.MessageColor) API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst);

typedef NS_ENUM(NSInteger, MEMessageActionFlag) {
    MEMessageActionFlagNone,
    MEMessageActionFlagDefaultColor,
    MEMessageActionFlagRed,
    MEMessageActionFlagOrange,
    MEMessageActionFlagYellow,
    MEMessageActionFlagGreen,
    MEMessageActionFlagBlue,
    MEMessageActionFlagPurple,
    MEMessageActionFlagGray,
} NS_SWIFT_NAME(MEMessageAction.Flag) API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst);

/// @brief An action that can be performed on a mail message.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface MEMessageAction : NSObject <NSSecureCoding>

/// @brief Moves the mail message to the user's trash mailbox for the account.
@property (class, readonly) MEMessageAction *moveToTrashAction;

/// @brief Moves the mail message to the user's archive mailbox for the account.
@property (class, readonly) MEMessageAction *moveToArchiveAction;

/// @brief Moves the mail message to the user's junk mailbox for the account.
@property (class, readonly) MEMessageAction *moveToJunkAction;

/// @brief Marks the mail message as read.
@property (class, readonly) MEMessageAction *markAsReadAction;

/// @brief Marks the mail  message as unread.
@property (class, readonly) MEMessageAction *markAsUnreadAction;

/// @brief Marks the message as flagged with the provided color.
+ (instancetype)flagActionWithFlag:(MEMessageActionFlag)flag NS_SWIFT_NAME(flag(_:));

/// @brief Adds a color to the message when shown in the message list.
+ (instancetype)setBackgroundColorActionWithColor:(MEMessageActionMessageColor)color NS_SWIFT_NAME(setBackgroundColor(_:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
