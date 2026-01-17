//
//  UIGeometry.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_OPTIONS(NSUInteger, UIRectEdge) {
    UIRectEdgeNone   = 0,
    UIRectEdgeTop    = 1 << 0,
    UIRectEdgeLeft   = 1 << 1,
    UIRectEdgeBottom = 1 << 2,
    UIRectEdgeRight  = 1 << 3,
    UIRectEdgeAll    = UIRectEdgeTop | UIRectEdgeLeft | UIRectEdgeBottom | UIRectEdgeRight
} API_AVAILABLE(ios(7.0), watchos(2.0));

typedef NS_OPTIONS(NSUInteger, UIAxis) {
    UIAxisNeither    = 0,
    UIAxisHorizontal = 1 << 0,
    UIAxisVertical   = 1 << 1,
    UIAxisBoth       = (UIAxisHorizontal | UIAxisVertical),
} API_AVAILABLE(ios(13.4), tvos(13.4), watchos(6.2));

NS_HEADER_AUDIT_END(nullability, sendability)
