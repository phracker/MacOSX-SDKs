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
} API_AVAILABLE(ios(10.0));

@class UICubicTimingParameters, UISpringTimingParameters;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_UI_ACTOR
@protocol UITimingCurveProvider <NSCoding, NSCopying>

@property(nonatomic, readonly) UITimingCurveType timingCurveType;
@property(nullable, nonatomic, readonly) UICubicTimingParameters *cubicTimingParameters;
@property(nullable, nonatomic, readonly) UISpringTimingParameters *springTimingParameters;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITimingCurveProvider.h>
#endif
