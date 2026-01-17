#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewLayoutRegion.h>)
//
//  UIViewLayoutRegion.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSUInteger, UIViewLayoutRegionAdaptivityAxis) {
    UIViewLayoutRegionAdaptivityAxisNone,
    UIViewLayoutRegionAdaptivityAxisHorizontal,
    UIViewLayoutRegionAdaptivityAxisVertical,
} API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

UIKIT_EXTERN API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT
@interface UIViewLayoutRegion: NSObject

+ (UIViewLayoutRegion *)safeAreaLayoutRegionWithCornerAdaptation:(UIViewLayoutRegionAdaptivityAxis)adaptivityAxis;
+ (UIViewLayoutRegion *)marginsLayoutRegionWithCornerAdaptation:(UIViewLayoutRegionAdaptivityAxis)adaptivityAxis;
+ (UIViewLayoutRegion *)readableContentLayoutRegionWithCornerAdaptation:(UIViewLayoutRegionAdaptivityAxis)adaptivityAxis;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIViewLayoutRegion.h>
#endif
