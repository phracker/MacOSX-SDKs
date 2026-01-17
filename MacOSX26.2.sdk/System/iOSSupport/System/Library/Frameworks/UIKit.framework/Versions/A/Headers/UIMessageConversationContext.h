#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMessageConversationContext.h>)
//
//  UIMessageConversationContext.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIConversationContext.h>
#import <UIKit/UIMessageConversationEntry.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class that represents a message conversation.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst)
@interface UIMessageConversationContext : UIConversationContext

/// A Boolean value that indicates whether the message thread is "junk", such as spam.
@property (nonatomic, readwrite, assign) BOOL isJunk;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMessageConversationContext.h>
#endif
