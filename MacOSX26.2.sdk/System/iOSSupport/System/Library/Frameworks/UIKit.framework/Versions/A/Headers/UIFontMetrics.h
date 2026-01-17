#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFontMetrics.h>)
//
//  UIFontMetrics.h
//  UIKit
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIFont.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0)) NS_SWIFT_SENDABLE
@interface UIFontMetrics : NSObject

@property (class, readonly, strong) UIFontMetrics *defaultMetrics;

+ (instancetype)metricsForTextStyle:(UIFontTextStyle)textStyle;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initForTextStyle:(UIFontTextStyle)textStyle NS_DESIGNATED_INITIALIZER;

- (UIFont *)scaledFontForFont:(UIFont *)font;
- (UIFont *)scaledFontForFont:(UIFont *)font maximumPointSize:(CGFloat)maximumPointSize;
- (UIFont *)scaledFontForFont:(UIFont *)font compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_UNAVAILABLE(watchos);
- (UIFont *)scaledFontForFont:(UIFont *)font maximumPointSize:(CGFloat)maximumPointSize compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_UNAVAILABLE(watchos);

- (CGFloat)scaledValueForValue:(CGFloat)value;
- (CGFloat)scaledValueForValue:(CGFloat)value compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFontMetrics.h>
#endif
