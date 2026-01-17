#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMessageConversationEntry.h>)
//
//  UIMessageConversationEntry.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIConversationEntry.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A list of options that represent the kinds of data a message can contain.
typedef NS_ENUM(NSInteger, UIMessageConversationEntryDataKind) {
    /// The message contains text.
    UIMessageConversationEntryDataKindText = 0,
    /// The message contains an attachment, such as an image or file.
    UIMessageConversationEntryDataKindAttachment = 1,
    /// The message contains other data, such as data that represents a sticker or a payment.
    UIMessageConversationEntryDataKindOther = 2,
} API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst) NS_SWIFT_NAME(UIMessageConversationEntry.DataKind);

/// A class that represents a message in a message conversation.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst) NS_SWIFT_NAME(UIMessageConversationContext.MessageEntry)
@interface UIMessageConversationEntry : UIConversationEntry

/// Indicates the data format of the entry
@property (nonatomic, assign, readwrite) UIMessageConversationEntryDataKind dataKind;

/// A Boolean value that indicates whether the current user sent the message.
@property (nonatomic, assign, readwrite) BOOL wasSentBySelf;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIMessageConversationEntry.h>
#endif
