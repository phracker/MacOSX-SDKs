//
//  SKRegion.h
//  SpriteKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import <CoreGraphics/CGPath.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKRegion : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, nullable) CGPathRef path;

/** A shared infinite region
  */
+ (instancetype)infiniteRegion;

/** Create a circular region with radius
 */
- (instancetype)initWithRadius:(float)radius;

/** Create a rectangular region of size
 */
- (instancetype)initWithSize:(CGSize)size;

/** Create a region bounded by a CGPath. Note that this option can be
    costly to evaluate.
 */
- (instancetype)initWithPath:(CGPathRef)path;

/** Create a new region that is the inverse of the current region.
    The inverse of the infiniteRegion is an empty region.
    Subclasses of SKRegion need to provide an implementation of inverseRegion.
 */
- (instancetype)inverseRegion;

/** Create a new region that is the original region plus the supplied region
 */
- (instancetype)regionByUnionWithRegion:(SKRegion *)region;

/** Create a new region that is the original region minus the supplied region
 */
- (instancetype)regionByDifferenceFromRegion:(SKRegion *)region;

/** Create a new region that is the region covered by the original region and the supplied region
 */
- (instancetype)regionByIntersectionWithRegion:(SKRegion *)region;

/** Test for containment
 */
- (BOOL)containsPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
