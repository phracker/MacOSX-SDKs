#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentSizeCategoryAdjusting.h>)
//
//  UIContentSizeCategoryAdjusting.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIContentSizeCategoryAdjusting <NSObject>

/*
 Indicates whether the corresponding element should automatically update its font when the device’s UIContentSizeCategory is changed.
 For this property to take effect, the element’s font must be one of the following:
 - a font vended using +preferredFontForTextStyle: or +preferredFontForTextStyle:compatibleWithTraitCollection: with a valid UIFontTextStyle
 - a font vended using - [UIFontMetrics scaledFontForFont:] or one of its variants
 */
@property (nonatomic) BOOL adjustsFontForContentSizeCategory;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentSizeCategoryAdjusting.h>
#endif
