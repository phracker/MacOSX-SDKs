/*!
 @header MDLAnimation.h
 @framework ModelIO
 @abstract Support for time sampled animation of skeletal meshes
 @copyright Copyright © 2016 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ModelIO/MDLValueTypes.h>
#import <ModelIO/MDLAnimatedValueTypes.h>
#import <ModelIO/MDLObject.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLSkeleton : MDLObject<NSCopying>

@property (nonatomic, readonly) NSArray<NSString *> *jointPaths;

 // world space bind transforms
@property (nonatomic, readonly) MDLMatrix4x4Array *jointBindTransforms;

 // local space default transforms, used for joints not animated in a MDLPackedJointAnimation
@property (nonatomic, readonly) MDLMatrix4x4Array *jointRestTransforms;

-(instancetype) initWithName:(NSString *)name
                  jointPaths:(NSArray<NSString *> *)jointPaths;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@protocol MDLJointAnimation
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLPackedJointAnimation : MDLObject<NSCopying, MDLJointAnimation>
@property (nonatomic, readonly) NSArray<NSString *> *jointPaths;

@property (nonatomic, readonly) MDLAnimatedVector3Array *translations;
@property (nonatomic, readonly) MDLAnimatedQuaternionArray *rotations;
@property (nonatomic, readonly) MDLAnimatedVector3Array *scales;

-(instancetype) initWithName:(NSString *)name
                  jointPaths:(NSArray<NSString *> *)jointPaths;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimationBindComponent : NSObject<NSCopying, MDLComponent>

@property (nonatomic, nullable, retain) MDLSkeleton* skeleton;
@property (nonatomic, nullable, retain) id<MDLJointAnimation> jointAnimation;

 // optional. If set, jointIndices vertex buffers index into this list of joints.
@property (nonatomic, nullable, retain) NSArray<NSString *> *jointPaths;

@property (nonatomic) matrix_double4x4 geometryBindTransform;
@end


NS_ASSUME_NONNULL_END
