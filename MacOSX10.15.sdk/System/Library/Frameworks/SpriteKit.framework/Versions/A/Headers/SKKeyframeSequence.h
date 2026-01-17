//
//  SKKeyframeSequence.h
//  SpriteKit
//
//  Created by Tim Oriol on 2/25/13.
//
//

#import <SpriteKit/SpriteKitBase.h>

typedef NS_ENUM(NSInteger, SKInterpolationMode) {
    SKInterpolationModeLinear   = 1,
    SKInterpolationModeSpline   = 2,
    SKInterpolationModeStep     = 3,
};

typedef NS_ENUM(NSInteger, SKRepeatMode) {
    SKRepeatModeClamp   = 1,
    SKRepeatModeLoop    = 2,
};

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKKeyframeSequence : NSObject <NSSecureCoding, NSCopying>

/* Designated initializer */
- (instancetype)initWithKeyframeValues:(NSArray*)values times:(NSArray<NSNumber*> *)times NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCapacity:(NSUInteger)numItems;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (NSUInteger)count;

- (void)addKeyframeValue:(id)value time:(CGFloat)time;

- (void)removeLastKeyframe;
- (void)removeKeyframeAtIndex:(NSUInteger)index;

- (void)setKeyframeValue:(id)value forIndex:(NSUInteger)index;
- (void)setKeyframeTime:(CGFloat)time forIndex:(NSUInteger)index;

- (void)setKeyframeValue:(id)value time:(CGFloat)time forIndex:(NSUInteger)index;

- (id)getKeyframeValueForIndex:(NSUInteger)index;
- (CGFloat)getKeyframeTimeForIndex:(NSUInteger)index;

- (nullable id)sampleAtTime:(CGFloat)time;

/* defaults to SKInterpolationModeLinear */
@property (nonatomic) SKInterpolationMode interpolationMode;

/* defaults to SKRepeatModeClamp */
@property (nonatomic) SKRepeatMode repeatMode;

@end

NS_ASSUME_NONNULL_END
