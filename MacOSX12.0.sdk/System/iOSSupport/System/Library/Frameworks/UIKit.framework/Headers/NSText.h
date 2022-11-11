#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSText.h>)
//
//  NSText.h
//  UIKit
//
//  Copyright (c) 2011-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#if __has_include(<CoreText/CTParagraphStyle.h>)
#import <CoreText/CTParagraphStyle.h>
#endif
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

#if !__NSTEXT_SHARED_SECTION__
#define __NSTEXT_SHARED_SECTION__ 1
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
    NSTextAlignmentNatural   = 4     // Indicates the default alignment for script
} API_AVAILABLE(macos(10.0), ios(6.0), watchos(2.0), tvos(9.0));

/* Values for NSWritingDirection */
typedef NS_ENUM(NSInteger, NSWritingDirection) {
    NSWritingDirectionNatural       = -1,   // Determines direction using the Unicode Bidi Algorithm rules P2 and P3
    NSWritingDirectionLeftToRight   = 0,    // Left to right writing direction
    NSWritingDirectionRightToLeft   = 1     // Right to left writing direction
} API_AVAILABLE(macos(10.0), ios(6.0), watchos(2.0), tvos(9.0));
#endif // !__NSTEXT_SHARED_SECTION__

#if __has_include(<CoreText/CTParagraphStyle.h>)
UIKIT_SWIFT_FORWARD_DECLARE(typedef CF_ENUM(uint8_t, CTTextAlignment))
UIKIT_EXTERN CTTextAlignment NSTextAlignmentToCTTextAlignment(NSTextAlignment nsTextAlignment) API_AVAILABLE(ios(6.0));
UIKIT_EXTERN NSTextAlignment NSTextAlignmentFromCTTextAlignment(CTTextAlignment ctTextAlignment) API_AVAILABLE(ios(6.0));
#endif

NS_ASSUME_NONNULL_END
#elif TARGET_OS_OSX
#import <AppKit/NSText.h>
#endif

#else
#import <UIKitCore/NSText.h>
#endif
