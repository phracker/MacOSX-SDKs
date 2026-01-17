#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIConversationContext.h>)
//
//  UIConversationContext.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIConversationEntry.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A base class that represents a conversation between participants, such as in an email or messaging app.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst)
@interface UIConversationContext : NSObject

/// A string that uniquely identifies a conversation.
/// This identifier is persistent for the life of the conversation.
@property (copy, nonatomic, readwrite) NSString *threadIdentifier;

/// Array of messages in the conversation
@property (copy, nonatomic, readwrite) NSArray<UIConversationEntry *> *entries;

/// A set of strings that identifies the active person in the conversation on the current device.
@property (copy, nonatomic, readwrite) NSSet<NSString *> *selfIdentifiers;

/// A dictionary that relates participant identifiers to participant names.
@property (copy, nonatomic, readwrite) NSSet<NSString *> *responsePrimaryRecipientIdentifiers;

/// Map of participant identifiers to participant names
@property (copy, nonatomic, readwrite) NSDictionary<NSString *, NSPersonNameComponents *> *participantNameByIdentifier;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIConversationContext.h>
#endif
