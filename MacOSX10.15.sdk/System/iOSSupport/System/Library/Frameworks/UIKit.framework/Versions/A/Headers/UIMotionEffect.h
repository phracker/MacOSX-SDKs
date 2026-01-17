#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMotionEffect.h>)
//
//  UIMotionEffect.h
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

/*! UIMotionEffect is an abstract superclass which declaratively represents a rendering
    effect that depends on the motion of the device. Given some device pose, subclassers
    provide relative values which are to be applied to the keypaths of the target's view.
 
    Subclasses must implement conformance for NSCopying and NSCoding. */
NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UIMotionEffect : NSObject <NSCopying, NSCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/*! Abstract method. Given the `viewerOffset`, this method should compute a set of key paths
    and relative values pairs which will represent the effect of the device's motion on
    the target view. The return value is a dictionary whose keys and values are these
    key paths (as NSStrings) and relative values, respectively.

    The `viewerOffset` is an estimate of the viewer's position relative to direction the
    screen's facing. Values in each dimension range from -1 to 1. Facing straight at the
    viewer is (0, 0). Tilting the phone to the right produces a more positive horizontal
    value; tilting the phone down produces a more positive vertical value.

    `keyPaths` should be expressed relative to the effect's target view. Only key paths
    which would animate if set in an animation block may be targeted by motion effects.

    Example return value: `@{ @"center": [NSValue 
 valueFromCGPoint:CGPointMake(3.4, 1.2)],
                              @"layer.shadowOffset.x": @(-1.1) }` */
- (nullable NSDictionary<NSString *, id> *)keyPathsAndRelativeValuesForViewerOffset:(UIOffset)viewerOffset;

@end

//---------------------------------------------------------------------

typedef NS_ENUM(NSInteger, UIInterpolatingMotionEffectType) {
    /*! Tracks the device being tilted left/right relative to the viewer. The minimum
        relative values maps to the device being tilted all the way to the left, the
        maximum to the right. */
    UIInterpolatingMotionEffectTypeTiltAlongHorizontalAxis,
    
    /*! Tracks the device being tilted up/down relative to the viewer. The minimum
        relative values maps to the device being tilted all the way down, the maximum
        all the way up. */
    UIInterpolatingMotionEffectTypeTiltAlongVerticalAxis
};

/*! This motion effect maps movement of a particular type (e.g. left/right tilt) to an
    interpolated output between two relative values provided by the client. Uses Core
    Animation's implementation of interpolation for all the standard types.
 
    `keyPath` should be expressed relative to the effect's target view. */
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UIInterpolatingMotionEffect : UIMotionEffect

- (instancetype)initWithKeyPath:(NSString *)keyPath type:(UIInterpolatingMotionEffectType)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
@property (readonly, nonatomic) NSString *keyPath;
@property (readonly, nonatomic) UIInterpolatingMotionEffectType type;

@property (nullable, strong, nonatomic) id minimumRelativeValue;
@property (nullable, strong, nonatomic) id maximumRelativeValue;

@end

//---------------------------------------------------------------------

/*! Behaves like CAAnimationGroup. Merges key/value pairs of constituent
    using Core Animation's implementations of addition for all the standard types. */
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UIMotionEffectGroup : UIMotionEffect
@property (nullable, copy, nonatomic) NSArray<__kindof UIMotionEffect *> *motionEffects;
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIMotionEffect.h>
#endif
