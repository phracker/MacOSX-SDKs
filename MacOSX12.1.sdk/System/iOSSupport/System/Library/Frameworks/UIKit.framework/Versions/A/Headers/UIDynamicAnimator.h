#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDynamicAnimator.h>)
//
//  UIDynamicAnimator.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UICollectionViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

@class UIDynamicBehavior;
@class UIDynamicAnimator;

NS_SWIFT_UI_ACTOR
@protocol UIDynamicAnimatorDelegate <NSObject>

@optional
- (void)dynamicAnimatorWillResume:(UIDynamicAnimator *)animator;
- (void)dynamicAnimatorDidPause:(UIDynamicAnimator *)animator;

@end

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UIDynamicAnimator: NSObject

// When you initialize a dynamic animator with this method, you should only associates views with your behaviors.
// the behaviors (and their dynamic items) that you add to the animator employ the reference view’s coordinate system.
- (instancetype)initWithReferenceView:(UIView *)view NS_DESIGNATED_INITIALIZER;

- (void)addBehavior:(UIDynamicBehavior *)behavior;
- (void)removeBehavior:(UIDynamicBehavior *)behavior;
- (void)removeAllBehaviors;

@property (nullable, nonatomic, readonly) UIView *referenceView;
@property (nonatomic, readonly, copy) NSArray<__kindof UIDynamicBehavior*> *behaviors;

// Returns the dynamic items associated with the animator’s behaviors that intersect a specified rectangle
- (NSArray<id<UIDynamicItem>> *)itemsInRect:(CGRect)rect;
// Update the item state in the animator if an external change was made to this item 
- (void)updateItemUsingCurrentState:(id <UIDynamicItem>)item;

@property (nonatomic, readonly, getter = isRunning) BOOL running;
@property (nonatomic, readonly) NSTimeInterval elapsedTime;

@property (nullable, nonatomic, weak) id <UIDynamicAnimatorDelegate> delegate;

@end

@interface UIDynamicAnimator (UICollectionViewAdditions)

// When you initialize a dynamic animator with this method, you should only associate collection view layout attributes with your behaviors.
// The animator will employ the collection view layout’s content size coordinate system.
- (instancetype)initWithCollectionViewLayout:(UICollectionViewLayout *)layout;

// The three convenience methods returning layout attributes (if associated to behaviors in the animator) if the animator was configured with collection view layout
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForCellAtIndexPath:(NSIndexPath *)indexPath;
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryViewOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForDecorationViewOfKind:(NSString *)decorationViewKind atIndexPath:(NSIndexPath *)indexPath;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDynamicAnimator.h>
#endif
