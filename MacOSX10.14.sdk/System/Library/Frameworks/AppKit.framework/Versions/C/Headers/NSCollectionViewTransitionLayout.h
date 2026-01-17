/*
    NSCollectionViewTransitionLayout.h
    Application Kit
    Copyright (c) 2015-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSCollectionViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * NSCollectionViewTransitionLayoutAnimatedKey NS_SWIFT_BRIDGED_TYPEDEF;

NS_CLASS_AVAILABLE_MAC(10_11)
@interface NSCollectionViewTransitionLayout : NSCollectionViewLayout
#ifndef __OBJC2__
{
@private
    NSCollectionViewLayout *_fromLayout APPKIT_IVAR;
    NSCollectionViewLayout *_toLayout APPKIT_IVAR;
    
    CGRect _fromVisibleBounds APPKIT_IVAR;
    CGRect _toVisibleBounds APPKIT_IVAR;
    NSSize _contentSize APPKIT_IVAR;
    
    BOOL _haveValidInfos APPKIT_IVAR;
    CGFloat _transitionProgress APPKIT_IVAR;
    
    NSMutableDictionary *_transitionInformationsDict APPKIT_IVAR;
    NSMutableDictionary *_currentLayoutInfos APPKIT_IVAR;
    
    BOOL _layoutIsValid APPKIT_IVAR;
    
    NSMutableArray *_disappearingLayoutAttributes APPKIT_IVAR;
    NSMutableArray *_appearingLayoutAttributes APPKIT_IVAR;
    
    CGFloat _accuracy APPKIT_IVAR;
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
