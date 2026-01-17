/*
    NSCollectionViewTransitionLayout.h
    Application Kit
    Copyright (c) 2015-2017, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSCollectionViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * NSCollectionViewTransitionLayoutAnimatedKey NS_EXTENSIBLE_STRING_ENUM;

NS_CLASS_AVAILABLE_MAC(10_11)
@interface NSCollectionViewTransitionLayout : NSCollectionViewLayout
#ifndef __OBJC2__
{
@private
    NSCollectionViewLayout *_fromLayout;
    NSCollectionViewLayout *_toLayout;
    
    CGRect _fromVisibleBounds;
    CGRect _toVisibleBounds;
    NSSize _contentSize;
    
    BOOL _haveValidInfos;
    CGFloat _transitionProgress;
    
    NSMutableDictionary *_transitionInformationsDict;
    NSMutableDictionary *_currentLayoutInfos;
    
    BOOL _layoutIsValid;
    
    NSMutableArray *_disappearingLayoutAttributes;
    NSMutableArray *_appearingLayoutAttributes;
    
    CGFloat _accuracy;
}
#endif

@property (assign) CGFloat transitionProgress;
@property (readonly) NSCollectionViewLayout *currentLayout;
@property (readonly) NSCollectionViewLayout *nextLayout;

// Designated initializer
- (instancetype)initWithCurrentLayout:(NSCollectionViewLayout *)currentLayout nextLayout:(NSCollectionViewLayout *)newLayout;

- (void)updateValue:(CGFloat)value forAnimatedKey:(NSCollectionViewTransitionLayoutAnimatedKey)key;
- (CGFloat)valueForAnimatedKey:(NSCollectionViewTransitionLayoutAnimatedKey)key;

@end

NS_ASSUME_NONNULL_END
