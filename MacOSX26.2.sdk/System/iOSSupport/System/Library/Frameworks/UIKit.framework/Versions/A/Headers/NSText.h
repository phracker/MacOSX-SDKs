#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSText.h>)
#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSText.h>)
#import <UIKit/UIKitDefines.h>
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS && !TARGET_OS_OSX
#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

//
//  NSText.h
//  UIKit
//
//  Copyright (c) 2011-2025, Apple Inc. All rights reserved.
//

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if !__NSWRITING_DIRECTION_SHARED_SECTION__
#define __NSWRITING_DIRECTION_SHARED_SECTION__ 1
#pragma mark NSWritingDirection
typedef NS_ENUM(NSInteger, NSWritingDirection) {
    NSWritingDirectionNatural       = -1,   // Determines direction using the Unicode Bidi Algorithm rules P2 and P3
    NSWritingDirectionLeftToRight   = 0,    // Left to right writing direction
    NSWritingDirectionRightToLeft   = 1     // Right to left writing direction
} API_AVAILABLE(macos(10.0), ios(6.0), watchos(2.0), tvos(9.0), visionos(1.0));
#endif // !__NSWRITING_DIRECTION_SHARED_SECTION__

NS_HEADER_AUDIT_END(nullability, sendability)
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS && !TARGET_OS_OSX
#else
#import <UIFoundation/NSText.h>
#endif

#if __has_include(<CoreText/CTParagraphStyle.h>)
#import <CoreText/CTParagraphStyle.h>
#endif
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if !__NSTEXT_ALIGNMENT_SHARED_SECTION__
#define __NSTEXT_ALIGNMENT_SHARED_SECTION__ 1
/* Values for NSTextAlignment */
typedef NS_ENUM(NSInteger, NSTextAlignment) {
    NSTextAlignmentLeft      = 0,    // Visually left aligned
#if TARGET_ABI_USES_IOS_VALUES
    NSTextAlignmentCenter    = 1,    // Visually centered
    NSTextAlignmentRight     = 2,    // Visually right aligned
#else /* !TARGET_ABI_USES_IOS_VALUES */
    NSTextAlignmentRight     = 1,    // Visually right aligned
    NSTextAlignmentCenter    = 2,    // Visually centered
#endif
    NSTextAlignmentJustified = 3,    // Fully-justified. The last line in a paragraph is natural-aligned.

    /// Resolved to either ``left`` or ``right`` based on the natural alignment resolution type active in the associated component.
    ///
    /// There are two types of natural alignment resolution behavior. The natural alignment is resolved based on either the UI language or the base writing direction.
    /// The behavior is selected by the ``resolvesNaturalAlignmentWithBaseWritingDirection`` property for ``NSTextLayoutManager``.
    /// ``NSStringDrawingOptions.resolvesNaturalAlignmentWithBaseWritingDirection`` specifies the base writing direction based resolution for ``NSStringDrawing``.
    NSTextAlignmentNatural   = 4
} API_AVAILABLE(macos(10.0), ios(6.0), watchos(2.0), tvos(9.0), visionos(1.0));
#endif // !__NSTEXT_ALIGNMENT_SHARED_SECTION__

#if __has_include(<CoreText/CTParagraphStyle.h>)
UIKIT_SWIFT_FORWARD_DECLARE(typedef CF_ENUM(uint8_t, CTTextAlignment))
UIKIT_EXTERN CTTextAlignment NSTextAlignmentToCTTextAlignment(NSTextAlignment nsTextAlignment) API_AVAILABLE(ios(6.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextAlignment NSTextAlignmentFromCTTextAlignment(CTTextAlignment ctTextAlignment) API_AVAILABLE(ios(6.0), tvos(9.0), watchos(2.0), visionos(1.0));
#endif

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/NSText.h>
#endif
