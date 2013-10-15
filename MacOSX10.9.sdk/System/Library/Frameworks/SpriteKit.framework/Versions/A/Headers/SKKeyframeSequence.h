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

SK_EXPORT @interface SKKeyframeSequence : NSObject <NSCoding, NSCopying>

/* Designated initializer */
- (instancetype)initWithKeyframeValues:(NSArray*)values times:(NSArray*)times;

- (instancetype)initWithCapacity:(NSUInteger)numItems;

- (NSUInteger)count;

- (void)addKeyframeValue:(id)value time:(CGFloat)time;

- (void)removeLastKeyframe;
- (void)removeKeyframeAtIndex:(NSUInteger)index;

- (void)setKeyframeValue:(id)value forIndex:(NSUInteger)index;
- (void)setKeyframeTime:(CGFloat)time forIndex:(NSUInteger)index;

- (void)setKeyframeValue:(id)value time:(CGFloat)time forIndex:(NSUInteger)index;

- (id)getKeyframeValueForIndex:(NSUInteger)index;
- (CGFloat)getKeyframeTimeForIndex:(NSUInteger)index;

- (id)sampleAtTime:(CGFloat)time;

/* defaults to SKInterpolationModeLinear */
@property (SK_NONATOMIC_IOSONLY) SKInterpolationMode interpolationMode;

/* defaults to SKRepeatModeClamp */
@property (SK_NONATOMIC_IOSONLY) SKRepeatMode repeatMode;

@end
