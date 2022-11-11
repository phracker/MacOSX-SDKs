#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollisionBehavior.h>)
//
//  UICollisionBehavior.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIBezierPath.h>
#import <UIKit/UIDynamicBehavior.h>

NS_ASSUME_NONNULL_BEGIN

@class UICollisionBehavior;

typedef NS_OPTIONS(NSUInteger, UICollisionBehaviorMode) {
    UICollisionBehaviorModeItems        = 1 << 0,
    UICollisionBehaviorModeBoundaries   = 1 << 1,
    UICollisionBehaviorModeEverything   = NSUIntegerMax
} API_AVAILABLE(ios(7.0));

NS_SWIFT_UI_ACTOR
@protocol UICollisionBehaviorDelegate <NSObject>
@optional

- (void)collisionBehavior:(UICollisionBehavior *)behavior beganContactForItem:(id <UIDynamicItem>)item1 withItem:(id <UIDynamicItem>)item2 atPoint:(CGPoint)p;
- (void)collisionBehavior:(UICollisionBehavior *)behavior endedContactForItem:(id <UIDynamicItem>)item1 withItem:(id <UIDynamicItem>)item2;

// The identifier of a boundary created with translatesReferenceBoundsIntoBoundary or setTranslatesReferenceBoundsIntoBoundaryWithInsets is nil
- (void)collisionBehavior:(UICollisionBehavior*)behavior beganContactForItem:(id <UIDynamicItem>)item withBoundaryIdentifier:(nullable id <NSCopying>)identifier atPoint:(CGPoint)p;
- (void)collisionBehavior:(UICollisionBehavior*)behavior endedContactForItem:(id <UIDynamicItem>)item withBoundaryIdentifier:(nullable id <NSCopying>)identifier;

@end

    
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) NS_SWIFT_UI_ACTOR
@interface UICollisionBehavior : UIDynamicBehavior

- (instancetype)initWithItems:(NSArray<id <UIDynamicItem>> *)items NS_DESIGNATED_INITIALIZER;

- (void)addItem:(id <UIDynamicItem>)item;
- (void)removeItem:(id <UIDynamicItem>)item;

@property (nonatomic, readonly, copy) NSArray<id <UIDynamicItem>> *items;

@property (nonatomic, readwrite) UICollisionBehaviorMode collisionMode;

@property (nonatomic, readwrite) BOOL translatesReferenceBoundsIntoBoundary;
- (void)setTranslatesReferenceBoundsIntoBoundaryWithInsets:(UIEdgeInsets)insets;

- (void)addBoundaryWithIdentifier:(id <NSCopying>)identifier forPath:(UIBezierPath *)bezierPath;
- (void)addBoundaryWithIdentifier:(id <NSCopying>)identifier fromPoint:(CGPoint)p1 toPoint:(CGPoint)p2;
- (nullable UIBezierPath *)boundaryWithIdentifier:(id <NSCopying>)identifier;
- (void)removeBoundaryWithIdentifier:(id <NSCopying>)identifier;
@property (nullable, nonatomic, readonly, copy) NSArray<id <NSCopying>> *boundaryIdentifiers;
- (void)removeAllBoundaries;

@property (nullable, nonatomic, weak, readwrite) id <UICollisionBehaviorDelegate> collisionDelegate;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICollisionBehavior.h>
#endif
