//
//  MEComposeContext.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MEMessage;

NS_ASSUME_NONNULL_BEGIN

/// @brief An enumeration corresponding to the action user took to start a new mail compose window.
typedef NS_ENUM(NSInteger, MEComposeUserAction) {
  /// Compose a new message.
  MEComposeUserActionNewMessage = 1,
  /// Reply to the sender of an original email.
  MEComposeUserActionReply = 2,
  /// Reply to the sender and all the recipeients of original email.
  MEComposeUserActionReplyAll = 3,
  /// Forward an original message.
  MEComposeUserActionForward = 4,
} API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos);

/// @brief An object encapsulating additional information about the message being composed.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEComposeContext : NSObject

//+ (instancetype)new NS_UNAVAILABLE;
//- (instancetype)init NS_UNAVAILABLE;

/// @brief A unique identifier for the compose context.
@property (nonatomic, readonly, strong) NSUUID *contextID;

/// @brief The original email message on which user performed an action
/// It is @c nil for @c MEComposeUserActionNewMessage actions.
@property (nonatomic, nullable, readonly, strong) MEMessage *originalMessage;

/// Indicates the action performed by the user that created this compose context.
@property (nonatomic, readonly) MEComposeUserAction action;

/// Boolean that indicates the message is encrypted by a Message Security extension.
@property (nonatomic, readonly, assign) BOOL isEncrypted;

/// Boolean that indicates if the user wants to encrypt the message.
@property (nonatomic, readonly, assign) BOOL shouldEncrypt;

/// Boolean that indicates the message is signed by a Message Security extension.
@property (nonatomic, readonly, assign) BOOL isSigned;

/// A Boolean that indicates if the user wants to sign the message.
@property (nonatomic, readonly, assign) BOOL shouldSign;

@end

NS_ASSUME_NONNULL_END
