#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISnapBehavior.h>)
//
//  UISnapBehavior.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDynamicBehavior.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UISnapBehavior : UIDynamicBehavior

// The point argument is expressed in the reference coordinate system
- (instancetype)initWithItem:(id <UIDynamicItem>)item snapToPoint:(CGPoint)point NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign) CGPoint snapPoint API_AVAILABLE(ios(9.0));
@property (nonatomic, assign) CGFloat damping; // damping value from 0.0 to 1.0. 1.0 is the least oscillation.

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISnapBehavior.h>
#endif
