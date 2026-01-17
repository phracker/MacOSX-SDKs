//
//  SKTransformNode.h
//  SpriteKit
//
//

#import <SpriteKit/SpriteKit.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

#if !defined(__MAC_10_13) && !defined(__IPHONE_11_0) && !defined(__WATCHOS_4_0) && !defined(__TVOS_11_0)
typedef struct {  vector_float4 vector; } simd_quatf;
#endif

/**
 * An SKTransformNode can be applied a 3D rotation that will affect
 * the visual aspect of its children.
 * The physics and constraints of the children will behave as if none
 * of them were transformed.
 */
API_AVAILABLE(ios(11.0), tvos(11.0), watchos(4.0), macos(10.13)) SK_EXPORT @interface SKTransformNode : SKNode

@property (nonatomic) CGFloat xRotation;
@property (nonatomic) CGFloat yRotation;

/**
 * Rotation specific setter/getter
 */

- (void)setEulerAngles:(vector_float3)euler;
- (vector_float3)eulerAngles;

- (void)setRotationMatrix:(matrix_float3x3)rotationMatrix;
- (matrix_float3x3)rotationMatrix;

- (void)setQuaternion:(simd_quatf)quaternion;
- (simd_quatf)quaternion;

@end

NS_ASSUME_NONNULL_END
