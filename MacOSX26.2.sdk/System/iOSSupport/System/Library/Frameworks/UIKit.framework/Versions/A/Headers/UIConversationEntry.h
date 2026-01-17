#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIConversationEntry.h>)
//
//  UIConversationEntry.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class TIMutableInputContextEntry;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A base class that represents a message in a conversation.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst) NS_SWIFT_NAME(UIConversationContext.Entry)
@interface UIConversationEntry : NSObject

/// A string that contains the message’s text.
@property (nonatomic, copy, readwrite) NSString *text;

/// A string that identifies the message’s sender.
@property (nonatomic, copy, readwrite) NSString *senderIdentifier;

/// A date that notes when the sender added the message to the conversation.
@property (nonatomic, copy, readwrite) NSDate *sentDate;

/// A string that uniquely identifies this specific entry in the conversation.
@property (nonatomic, copy, readwrite) NSString *entryIdentifier;

/// An optional string that identifies another message in a conversation, when this entry is a reply to that message.
///
/// When an entry is a reply to another conversation entry, this contains the identifier of the conversation entry that the person replied to.
@property (nonatomic, copy, readwrite, nullable) NSString *replyThreadIdentifier;

/// A set of strings that identifies the primary recipients of the message.
@property (nonatomic, copy, readwrite) NSSet<NSString *> *primaryRecipientIdentifiers;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIConversationEntry.h>
#endif
