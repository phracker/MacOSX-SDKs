/*!
 @header MDLTransformStack.h
 @framework ModelIO
 @abstract Time sampled transformation of elements in 3d assets
 @copyright Copyright © 2017 Apple, Inc. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>
#import <ModelIO/MDLAnimatedValueTypes.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MDLTransformOpRotationOrder) {
    MDLTransformOpRotationOrderXYZ = 1,
    MDLTransformOpRotationOrderXZY,
    MDLTransformOpRotationOrderYXZ,
    MDLTransformOpRotationOrderYZX,
    MDLTransformOpRotationOrderZXY,
    MDLTransformOpRotationOrderZYX,
};

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@protocol MDLTransformOp
@property (nonatomic, readonly) NSString* name;
-(matrix_float4x4)float4x4AtTime:(NSTimeInterval)time;
-(matrix_double4x4)double4x4AtTime:(NSTimeInterval)time;
-(bool)IsInverseOp;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformRotateXOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedScalar* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformRotateYOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedScalar* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformRotateZOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedScalar* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformRotateOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedVector3* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformTranslateOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedVector3* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformScaleOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedVector3* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformMatrixOp : NSObject<MDLTransformOp>
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) MDLAnimatedMatrix4x4* animatedValue;
@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLTransformStack : NSObject<NSCopying, MDLTransformComponent>

- (id)init;

-(MDLTransformTranslateOp*) addTranslateOp:(NSString*)animatedValueName
                                   inverse:(bool)inverse;

-(MDLTransformRotateXOp*) addRotateXOp:(NSString*)animatedValueName
                               inverse:(bool)inverse;

-(MDLTransformRotateYOp*) addRotateYOp:(NSString*)animatedValueName
                               inverse:(bool)inverse;

-(MDLTransformRotateZOp*) addRotateZOp:(NSString*)animatedValueName
                               inverse:(bool)inverse;

-(MDLTransformRotateOp*) addRotateOp:(NSString*)animatedValueName
                               order:(MDLTransformOpRotationOrder)order
                             inverse:(bool)inverse;

-(MDLTransformScaleOp*) addScaleOp:(NSString*)animatedValueName
                           inverse:(bool)inverse;

-(MDLTransformMatrixOp*) addMatrixOp:(NSString*)animatedValueName
                             inverse:(bool)inverse;

-(MDLAnimatedValue*) animatedValueWithName:(NSString*) name;

-(matrix_float4x4)float4x4AtTime:(NSTimeInterval)time;
-(matrix_double4x4)double4x4AtTime:(NSTimeInterval)time;

-(NSUInteger)count;

@property (nonatomic, readonly, copy) NSArray<NSNumber*> *keyTimes;
@property (nonatomic, readonly, copy) NSArray<id<MDLTransformOp>> *transformOps;


@end


NS_ASSUME_NONNULL_END
