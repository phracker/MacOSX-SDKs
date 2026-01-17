#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextItem.h>)
//
//  UITextItem.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UITextView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The attribute name for adding a text item with a specified custom tag. The value of the attribute must be an `NSString`.
UIKIT_EXTERN NSAttributedStringKey const UITextItemTagAttributeName API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos);

#pragma mark - UITextItem

typedef NS_ENUM(NSInteger, UITextItemContentType) {
    /// The text item represents a link.
    UITextItemContentTypeLink = 0,
    /// The text item represents a text attachment.
    UITextItemContentTypeTextAttachment = 1,
    /// The text item represents a custom tag.
    UITextItemContentTypeTag = 2,
} API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UITextItem : NSObject

/// The content type of the text item.
@property (nonatomic, assign, readonly) UITextItemContentType contentType;

/// The range of the text item.
@property (nonatomic, assign, readonly) NSRange range;

/// The link represented by the text item. This value is `nil` if the `contentType != UITextItemContentTypeLink`
@property (nonatomic, strong, nullable, readonly) NSURL *link;

/// The text attachment represented by the text item. This value is `nil` if the `contentType != UITextItemContentTypeTextAttachment`
@property (nonatomic, strong, nullable, readonly) NSTextAttachment *textAttachment;

/// The custom tag identifier represented by the text item. This value is `nil` if the `contentType != UITextItemContentTypeTag`
@property (nonatomic, strong, nullable, readonly) NSString *tagIdentifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UITextItemMenuPreview

/// An object representing the preview for a text item.
UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UITextItemMenuPreview : NSObject

/// Show the default system preview for the given text item.
+ (instancetype)defaultPreview;

/// Show the specified preview view for the given text item.
- (instancetype)initWithView:(UIView *)view;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UITextItemMenuConfiguration

@class UIMenu;

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UITextItemMenuConfiguration : NSObject

/**
 *  Creates a menu configuration with the specified menu and a default preview.
 *
 *  @param menu The menu to be presented.
 */
+ (instancetype)configurationWithMenu:(UIMenu *)menu;

/**
 *  Creates a menu configuration with the specified menu and custom preview.
 *
 *  @param menu The menu to be presented.
 *  @param preview The preview associated with the menu. Specify @c nil for no preview.
 */
+ (instancetype)configurationWithPreview:(nullable UITextItemMenuPreview *)preview menu:(UIMenu *)menu;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextItem.h>
#endif
