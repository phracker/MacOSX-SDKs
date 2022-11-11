#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDynamicItemBehavior.h>)
//
//  UIDynamicItemBehavior.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) NS_SWIFT_UI_ACTOR
@interface UIDynamicItemBehavior : UIDynamicBehavior

- (instancetype)initWithItems:(NSArray<id <UIDynamicItem>> *)items NS_DESIGNATED_INITIALIZER;

- (void)addItem:(id <UIDynamicItem>)item;
- (void)removeItem:(id <UIDynamicItem>)item;
@property (nonatomic, readonly, copy) NSArray<id <UIDynamicItem>> *items;

@property (readwrite, nonatomic) CGFloat elasticity; // Usually between 0 (inelastic) and 1 (collide elastically) 
@property (readwrite, nonatomic) CGFloat friction; // 0 being no friction between objects slide along each other
@property (readwrite, nonatomic) CGFloat density; // 1 by default
@property (readwrite, nonatomic) CGFloat resistance; // 0: no velocity damping
@property (readwrite, nonatomic) CGFloat angularResistance; // 0: no angular velocity damping

/*!
 Specifies the charge associated with the item behavior. Charge determines the degree to which a dynamic item is affected by
 electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
 set charge and field strength appropriately. Defaults to 0.0
 */
@property (readwrite, nonatomic) CGFloat charge API_AVAILABLE(ios(9.0));

/*!
 If an item is anchored, it can participate in collisions, but will not exhibit
 any dynamic response. i.e. The item will behave more like a collision boundary.
 The default is NO
 */
@property (nonatomic, getter = isAnchored) BOOL anchored API_AVAILABLE(ios(9.0));

@property (readwrite, nonatomic) BOOL allowsRotation; // force an item to never rotate

// The linear velocity, expressed in points per second, that you want to add to the specified dynamic item
// If called before being associated to an animator, the behavior will accumulate values until being associated to an animator
- (void)addLinearVelocity:(CGPoint)velocity forItem:(id <UIDynamicItem>)item;
- (CGPoint)linearVelocityForItem:(id <UIDynamicItem>)item;

// The angular velocity, expressed in radians per second, that you want to add to the specified dynamic item
// If called before being associated to an animator, the behavior will accumulate values until being associated to an animator
- (void)addAngularVelocity:(CGFloat)velocity forItem:(id <UIDynamicItem>)item;
- (CGFloat)angularVelocityForItem:(id <UIDynamicItem>)item;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDynamicItemBehavior.h>
#endif
