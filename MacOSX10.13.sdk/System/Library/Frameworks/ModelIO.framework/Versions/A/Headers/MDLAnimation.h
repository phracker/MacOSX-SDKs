/*!
 @header MDLAnimation.h
 @framework ModelIO
 @abstract Support for time sampled animation of skeletal meshes
 @copyright Copyright © 2016 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ModelIO/MDLValueTypes.h>
#import <ModelIO/MDLAnimatedValueTypes.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLSkeleton : MDLObject<NSCopying>

@property (nonatomic, readonly) NSArray<NSString *> *jointPaths;
@property (nonatomic, readonly) MDLMatrix4x4Array *jointBindTransforms;

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
@interface MDLAnimationBindComponent : NSObject<MDLNamed, NSCopying, MDLComponent>

@property (nonatomic, nullable, retain) MDLSkeleton* skeleton;
@property (nonatomic, nullable, retain) id<MDLJointAnimation> jointAnimation;

@property (nonatomic) matrix_float4x4 geometryBindTransform;

-(instancetype) initWithName:(NSString *)name
                    skeleton:(MDLSkeleton *)skeleton
              jointAnimation:(id<MDLJointAnimation>)jointAnimation
       geometryBindTransform:(matrix_float4x4)geometryBindTransform;
@end


NS_ASSUME_NONNULL_END
