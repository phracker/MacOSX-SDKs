#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityContentSizeCategoryImageAdjusting.h>)
//
//  UIAccessibilityContentSizeCategoryImageAdjusting.h
//  UIKit
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIImageView.h>
#import <UIKit/UIButton.h>
#if __has_include(<UIFoundation/NSTextAttachment.h>)
#import <UIFoundation/NSTextAttachment.h>
#else
#import <UIKit/NSTextAttachment.h>
#endif

// These should be used in conjunction with the "Preserve vector data" checkbox for an asset catalog asset, to allow smooth scaling of symbolic glyphs.

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos)
@protocol UIAccessibilityContentSizeCategoryImageAdjusting <NSObject>

// When this is equal to YES, the receiver's intrinsic size will increase for users who prefer an accessibility content size category.
@property (nonatomic) BOOL adjustsImageSizeForAccessibilityContentSizeCategory NS_SWIFT_UI_ACTOR;

@end

// If the contentMode of the UIImageView is set to a mode that scales the image (e.g. the default one), the image will be scaled for an accessibility content size category. If not, the behavior is undefined.
UIKIT_EXTERN API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos)
@interface UIImageView (UIAccessibilityContentSizeCategoryImageAdjusting) <UIAccessibilityContentSizeCategoryImageAdjusting>

@end

// If applicable, the image (not the background image) will be scaled for an accessibility content size category. Image edge insets are left unchanged.
UIKIT_EXTERN API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos)
@interface UIButton (UIAccessibilityContentSizeCategoryImageAdjusting) <UIAccessibilityContentSizeCategoryImageAdjusting>

@end

// If an image is set, the attachment bounds' size will increase for users who prefer an accessibility content size category.
// This should be used in a UIContentSizeCategoryAdjusting view that responds YES to adjustsFontForContentSizeCategory and has a font that can be adjusted. If not, the behavior is undefined.
UIKIT_EXTERN API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos)
@interface NSTextAttachment (UIAccessibilityContentSizeCategoryImageAdjusting) <UIAccessibilityContentSizeCategoryImageAdjusting>

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIAccessibilityContentSizeCategoryImageAdjusting.h>
#endif
