/**
 @header
 
 Constraints are used to apply restrictions to Node attributes.
 They are evaluated each frame after actions and physics.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKNode.h>

NS_ASSUME_NONNULL_BEGIN

/**
 SKRange object used to define a range of allowable values 
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKRange : NSObject <NSCoding, NSCopying>

/* SKRange with a lower and upper limit. Designated initializer. */
- (instancetype)initWithLowerLimit:(CGFloat)lower upperLimit:(CGFloat)upper NS_DESIGNATED_INITIALIZER;



/* SKRange with a lower and upper limit */
+ (instancetype)rangeWithLowerLimit:(CGFloat)lower upperLimit:(CGFloat)upper;

/* SKRange with only a lower limit */
+ (instancetype)rangeWithLowerLimit:(CGFloat)lower;

/* SKRange with only a upper limit */
+ (instancetype)rangeWithUpperLimit:(CGFloat)upper;

/* SKRange representing a single value */
+ (instancetype)rangeWithConstantValue:(CGFloat)value;

/* SKRange representing a variance about a value */
+ (instancetype)rangeWithValue:(CGFloat)value variance:(CGFloat)variance;

/* SKRange with no upper or lower limit */
+ (instancetype)rangeWithNoLimits;



/* The lower limit, -1.0 * CGFLOAT_MAX means no limit */
@property CGFloat lowerLimit;

/* The upper limit, +1.0 * CGFLOAT_MAX means no limit */
@property CGFloat upperLimit;

@end




/**
 SKConstraints are evaluated each frame after actions and physics.
 The node's transform will be changed to staisfy the constarint
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKConstraint : NSObject <NSCoding, NSCopying>

/* Wether the constraint should apply. Defualts to YES */
@property BOOL enabled;

/* Reference node to transform the values to before apply the constraint limits. Defaults to nil (no transfrom). */
@property (retain, nonatomic, nullable) SKNode *referenceNode;

/**
 Constrain the node's position to a range
 */
+ (instancetype)positionX:(SKRange *)range;
+ (instancetype)positionY:(SKRange *)range;
+ (instancetype)positionX:(SKRange *)xRange Y:(SKRange *)yRange;

/**
 Constrain the node's position to be within a distance of a point or node
 */
+ (instancetype)distance:(SKRange *)range toNode:(SKNode *)node;
+ (instancetype)distance:(SKRange *)range toPoint:(CGPoint)point;
+ (instancetype)distance:(SKRange *)range toPoint:(CGPoint)point inNode:(SKNode *)node;

/**
 Constrain the node's rotation to a range
 */
+ (instancetype)zRotation:(SKRange *)zRange;

/**
 Constrain the node's rotation to orient to a point or node
 */
+ (instancetype)orientToNode:(SKNode *)node offset:(SKRange *)radians;
+ (instancetype)orientToPoint:(CGPoint)point offset:(SKRange *)radians;
+ (instancetype)orientToPoint:(CGPoint)point inNode:(SKNode *)node offset:(SKRange *)radians;

@end

NS_ASSUME_NONNULL_END
