#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMailConversationEntry.h>)
//
//  UIMailConversationEntry.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIConversationEntry.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A set of categories for an email.
typedef NS_ENUM(NSInteger, UIMailConversationEntryKind) {
    /// The email does not fit in a specific category.
    UIMailConversationEntryKindNone = 0,
    /// The email is personal correspondence.
    UIMailConversationEntryKindPersonal = 1,
    /// The email contains a promotional offer.
    UIMailConversationEntryKindPromotion = 2,
    /// The email is related to social media.
    UIMailConversationEntryKindSocial = 3,
    /// The email is related to a purchase or transaction.
    UIMailConversationEntryKindTransaction = 4,
    /// The email is related to news or current events.
    UIMailConversationEntryKindNews = 5,
} API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst) NS_SWIFT_NAME(UIMailConversationEntry.Kind);

/// A class that represents a specific email in an email thread.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst) NS_SWIFT_NAME(UIMailConversationContext.MailEntry)
@interface UIMailConversationEntry : UIConversationEntry

/// An item that reflects the category that describes an email.
@property (nonatomic, assign, readwrite) UIMailConversationEntryKind kind;

/// A set of strings that identifies the secondary recipients of the message, such as those in CC or BCC messages.
@property (copy, nonatomic, readwrite) NSSet<NSString *> *responseSecondaryRecipientIdentifiers;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMailConversationEntry.h>
#endif
