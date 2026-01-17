#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITimingCurveProvider.h>)
//
//  UITimingCurveProvider.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, UITimingCurveType) {
    UITimingCurveTypeBuiltin,
    UITimingCurveTypeCubic,
    UITimingCurveTypeSpring,
    UITimingCurveTypeComposed,        
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

@class UICubicTimingParameters, UISpringTimingParameters;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITimingCurveProvider <NSCoding, NSCopying>

@property(nonatomic, readonly) UITimingCurveType timingCurveType;
@property(nullable, nonatomic, readonly) UICubicTimingParameters *cubicTimingParameters;
@property(nullable, nonatomic, readonly) UISpringTimingParameters *springTimingParameters;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITimingCurveProvider.h>
#endif
