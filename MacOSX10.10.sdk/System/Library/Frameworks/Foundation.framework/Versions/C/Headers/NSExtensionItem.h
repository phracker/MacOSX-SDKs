/*	NSExtensionItem.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <Foundation/NSItemProvider.h>

#if __OBJC2__
// A NSExtensionItem is an immutable collection of values representing different aspects of an item for the extension to act upon.
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSExtensionItem : NSObject<NSCopying, NSSecureCoding>

// (optional) title for the item
@property(copy, NS_NONATOMIC_IOSONLY) NSAttributedString *attributedTitle;

// (optional) content text
@property(copy, NS_NONATOMIC_IOSONLY) NSAttributedString *attributedContentText;

// (optional) Contains images, videos, URLs, etc. This is not meant to be an array of alternate data formats/types, but instead a collection to include in a social media post for example. These items are always typed NSItemProvider.
@property(copy, NS_NONATOMIC_IOSONLY) NSArray *attachments;

// (optional) dictionary of key-value data. The key/value pairs accepted by the service are expected to be specified in the extension's Info.plist. The values of NSExtensionItem's properties will be reflected into the dictionary.
@property(copy, NS_NONATOMIC_IOSONLY) NSDictionary *userInfo;

@end

// Keys corresponding to properties exposed on the NSExtensionItem interface
FOUNDATION_EXTERN NSString * const NSExtensionItemAttributedTitleKey NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXTERN NSString * const NSExtensionItemAttributedContentTextKey NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXTERN NSString * const NSExtensionItemAttachmentsKey NS_AVAILABLE(10_10, 8_0);
#endif
