#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMailConversationContext.h>)
//
//  UIMailConversationContext.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIConversationContext.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class that represents an email conversation.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst)
@interface UIMailConversationContext : UIConversationContext

/// A string that contains the subject line of an intended response.
@property (copy, nonatomic, readwrite) NSString *responseSubject;

/// A Boolean value that indicates whether the intended response contains a custom signature.
@property (nonatomic, assign, readwrite) BOOL responseHasCustomSignature;

/// A set of strings that identifies the secondary recipients of the message, such as those in CC or BCC messages.
@property (copy, nonatomic, readwrite) NSSet<NSString *> *responseSecondaryRecipientIdentifiers;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMailConversationContext.h>
#endif
