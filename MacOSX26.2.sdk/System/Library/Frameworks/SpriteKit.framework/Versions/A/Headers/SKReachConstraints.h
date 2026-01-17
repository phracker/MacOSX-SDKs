/**
 @header
 
 Reach contraints are used to control the degree of freedom when solving using inverse kinematics actions.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKReachConstraints : NSObject <NSSecureCoding>

/**
 Lower angle limit in radians
 */
@property (nonatomic, assign) CGFloat lowerAngleLimit;

/**
 Upper angle limit in radians
 */
@property (nonatomic, assign) CGFloat upperAngleLimit;

- (instancetype)initWithLowerAngleLimit:(CGFloat)lowerAngleLimit upperAngleLimit:(CGFloat)upperAngleLimit NS_DESIGNATED_INITIALIZER;

@end
