#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingViewControllerFormattingStyle.h>)
//
//  UITextFormattingViewControllerFormattingStyle.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - UITextFormattingViewControllerFormattingStyle

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT
/// Type that defines formatting style presented in text formatting view.
@interface UITextFormattingViewControllerFormattingStyle : NSObject <NSCopying, NSSecureCoding>

/// Formatting style key.
@property (nonatomic, nonnull, readonly, copy) NSString *styleKey;

/// Style title displayed in UI.
@property (nonatomic, nonnull, readonly, copy) NSString *title;

/// Attributes corresponding to this formatting style.
///
/// Alongside `title`, these may be used to create a preview for this formatting style.
@property (nonatomic, nonnull, readonly, copy) NSDictionary<NSAttributedStringKey, id> *attributes;

- (instancetype)initWithStyleKey:(NSString *)styleKey title:(NSString *)string attributes:(NSDictionary<NSAttributedStringKey, id> *)attributes;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextFormattingViewControllerFormattingStyle.h>
#endif
