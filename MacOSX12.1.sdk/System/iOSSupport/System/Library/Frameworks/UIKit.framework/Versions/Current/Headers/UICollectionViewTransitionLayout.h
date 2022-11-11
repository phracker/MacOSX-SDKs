#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionViewTransitionLayout.h>)
//
//  UICollectionView.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UICollectionViewLayout.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewTransitionLayout : UICollectionViewLayout

@property (assign, nonatomic) CGFloat transitionProgress;
@property (readonly, nonatomic) UICollectionViewLayout *currentLayout;
@property (readonly, nonatomic) UICollectionViewLayout *nextLayout;

- (instancetype)initWithCurrentLayout:(UICollectionViewLayout *)currentLayout nextLayout:(UICollectionViewLayout *)newLayout NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

- (void)updateValue:(CGFloat)value forAnimatedKey:(NSString *)key;
- (CGFloat)valueForAnimatedKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END





#else
#import <UIKitCore/UICollectionViewTransitionLayout.h>
#endif
