//
//  UICoordinateSpace.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_SWIFT_UI_ACTOR
@protocol UICoordinateSpace <NSObject>

- (CGPoint)convertPoint:(CGPoint)point toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);
- (CGPoint)convertPoint:(CGPoint)point fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);
- (CGRect)convertRect:(CGRect)rect toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);
- (CGRect)convertRect:(CGRect)rect fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);

@property (readonly, nonatomic) CGRect bounds API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
