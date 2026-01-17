#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDynamicBehavior.h>)
//
//  UIDynamicBehavior.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIDynamicAnimator;
@class UIBezierPath;

typedef NS_ENUM(NSUInteger, UIDynamicItemCollisionBoundsType) {
    UIDynamicItemCollisionBoundsTypeRectangle,
    UIDynamicItemCollisionBoundsTypeEllipse, // radii will be determined from the items bounds width, height
    UIDynamicItemCollisionBoundsTypePath
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos);

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIDynamicItem <NSObject>

@property (nonatomic, readwrite) CGPoint center;
@property (nonatomic, readonly) CGRect bounds;
@property (nonatomic, readwrite) CGAffineTransform transform;

@optional
/**
 The collision type represents how the dynamics system will evaluate collisions with 
 respect to the dynamic item. defaults to UIDynamicItemCollisionBoundsTypeRectangle
 */
@property (nonatomic, readonly) UIDynamicItemCollisionBoundsType collisionBoundsType API_AVAILABLE(ios(9.0));

/**
 The path must represent a convex polygon with counter clockwise winding and no self intersection. 
 The point (0,0) in the path corresponds to the dynamic item's center.
 */
@property (nonatomic, readonly) UIBezierPath *collisionBoundingPath API_AVAILABLE(ios(9.0));

@end

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIDynamicItemGroup : NSObject <UIDynamicItem>

- (instancetype)initWithItems:(NSArray<id <UIDynamicItem>> *)items;

@property (nonatomic, readonly, copy) NSArray<id <UIDynamicItem>> *items;

@end

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIDynamicBehavior : NSObject

- (void)addChildBehavior:(UIDynamicBehavior *)behavior;
- (void)removeChildBehavior:(UIDynamicBehavior *)behavior;

@property (nonatomic, readonly, copy) NSArray<__kindof UIDynamicBehavior *> *childBehaviors;

// When running, the dynamic animator calls the action block on every animation step.
@property (nullable, nonatomic,copy) void (^action)(void);

- (void)willMoveToAnimator:(nullable UIDynamicAnimator *)dynamicAnimator; // nil when being removed from an animator

@property (nullable, nonatomic, readonly) UIDynamicAnimator *dynamicAnimator;


@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIDynamicBehavior.h>
#endif
