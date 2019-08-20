/*!
 @header MDLAnimatedValueTypes.h
 @framework ModelIO
 @abstract Time sampled animated value types
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import <ModelIO/MDLTypes.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MDLAnimatedValueInterpolation) {
    MDLAnimatedValueInterpolationConstant,
    MDLAnimatedValueInterpolationLinear
};

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedValue : NSObject<NSCopying>
-(BOOL)isAnimated;
@property (nonatomic, readonly) MDLDataPrecision precision;
@property (nonatomic, readonly) NSUInteger timeSampleCount;
@property (nonatomic, readonly) NSTimeInterval minimumTime;
@property (nonatomic, readonly) NSTimeInterval maximumTime;
@property (nonatomic) MDLAnimatedValueInterpolation interpolation;

@property (nonatomic, readonly) NSArray<NSNumber *> *keyTimes;

-(void)clear;
-(NSUInteger)getTimes:(NSTimeInterval *)timesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
@end


/// AUTO-GENERATED FROM CodeGenArray.h


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedScalarArray : MDLAnimatedValue

@property (nonatomic, readonly) NSUInteger elementCount;

-(id)initWithElementCount:(NSUInteger)arrayElementCount;

-(void)setFloatArray:(const float *)array count:(NSUInteger)count atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;
-(void)setDoubleArray:(const double *)array count:(NSUInteger)count atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloatArray:(float *)array maxCount:(NSUInteger)maxCount atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDoubleArray:(double *)array maxCount:(NSUInteger)maxCount atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;

-(void)resetWithFloatArray:(const float *)valuesArray count:(NSUInteger)valuesCount atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)timesCount NS_REFINED_FOR_SWIFT;
-(void)resetWithDoubleArray:(const double *)valuesArray count:(NSUInteger)valuesCount atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)timesCount NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloatArray:(float *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDoubleArray:(double *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedVector3Array : MDLAnimatedValue

@property (nonatomic, readonly) NSUInteger elementCount;

-(id)initWithElementCount:(NSUInteger)arrayElementCount;

-(void)setFloat3Array:(const vector_float3 *)array count:(NSUInteger)count atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;
-(void)setDouble3Array:(const vector_double3 *)array count:(NSUInteger)count atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat3Array:(vector_float3 *)array maxCount:(NSUInteger)maxCount atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble3Array:(vector_double3 *)array maxCount:(NSUInteger)maxCount atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;

-(void)resetWithFloat3Array:(const vector_float3 *)valuesArray count:(NSUInteger)valuesCount atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)timesCount NS_REFINED_FOR_SWIFT;
-(void)resetWithDouble3Array:(const vector_double3 *)valuesArray count:(NSUInteger)valuesCount atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)timesCount NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat3Array:(vector_float3 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble3Array:(vector_double3 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedQuaternionArray : MDLAnimatedValue

@property (nonatomic, readonly) NSUInteger elementCount;

-(id)initWithElementCount:(NSUInteger)arrayElementCount;

-(void)setFloatQuaternionArray:(const simd_quatf *)array count:(NSUInteger)count atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;
-(void)setDoubleQuaternionArray:(const simd_quatd *)array count:(NSUInteger)count atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloatQuaternionArray:(simd_quatf *)array maxCount:(NSUInteger)maxCount atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDoubleQuaternionArray:(simd_quatd *)array maxCount:(NSUInteger)maxCount atTime:(NSTimeInterval)time NS_REFINED_FOR_SWIFT;

-(void)resetWithFloatQuaternionArray:(const simd_quatf *)valuesArray count:(NSUInteger)valuesCount atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)timesCount NS_REFINED_FOR_SWIFT;
-(void)resetWithDoubleQuaternionArray:(const simd_quatd *)valuesArray count:(NSUInteger)valuesCount atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)timesCount NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloatQuaternionArray:(simd_quatf *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDoubleQuaternionArray:(simd_quatd *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


/// AUTO-GENERATED FROM CodeGen.h


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedScalar : MDLAnimatedValue

-(void)setFloat:(float)value atTime:(NSTimeInterval)time;
-(void)setDouble:(double)value atTime:(NSTimeInterval)time;

-(float)floatAtTime:(NSTimeInterval)time;
-(double)doubleAtTime:(NSTimeInterval)time;

-(void)resetWithFloatArray:(const float *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;
-(void)resetWithDoubleArray:(const double *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloatArray:(float *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDoubleArray:(double *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedVector2 : MDLAnimatedValue

-(void)setFloat2:(vector_float2)value atTime:(NSTimeInterval)time;
-(void)setDouble2:(vector_double2)value atTime:(NSTimeInterval)time;

-(vector_float2)float2AtTime:(NSTimeInterval)time;
-(vector_double2)double2AtTime:(NSTimeInterval)time;

-(void)resetWithFloat2Array:(const vector_float2 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;
-(void)resetWithDouble2Array:(const vector_double2 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat2Array:(vector_float2 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble2Array:(vector_double2 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedVector3 : MDLAnimatedValue

-(void)setFloat3:(vector_float3)value atTime:(NSTimeInterval)time;
-(void)setDouble3:(vector_double3)value atTime:(NSTimeInterval)time;

-(vector_float3)float3AtTime:(NSTimeInterval)time;
-(vector_double3)double3AtTime:(NSTimeInterval)time;

-(void)resetWithFloat3Array:(const vector_float3 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;
-(void)resetWithDouble3Array:(const vector_double3 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat3Array:(vector_float3 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble3Array:(vector_double3 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedVector4 : MDLAnimatedValue

-(void)setFloat4:(vector_float4)value atTime:(NSTimeInterval)time;
-(void)setDouble4:(vector_double4)value atTime:(NSTimeInterval)time;

-(vector_float4)float4AtTime:(NSTimeInterval)time;
-(vector_double4)double4AtTime:(NSTimeInterval)time;

-(void)resetWithFloat4Array:(const vector_float4 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;
-(void)resetWithDouble4Array:(const vector_double4 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat4Array:(vector_float4 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble4Array:(vector_double4 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLAnimatedMatrix4x4 : MDLAnimatedValue

-(void)setFloat4x4:(matrix_float4x4)value atTime:(NSTimeInterval)time;
-(void)setDouble4x4:(matrix_double4x4)value atTime:(NSTimeInterval)time;

-(matrix_float4x4)float4x4AtTime:(NSTimeInterval)time;
-(matrix_double4x4)double4x4AtTime:(NSTimeInterval)time;

-(void)resetWithFloat4x4Array:(const matrix_float4x4 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;
-(void)resetWithDouble4x4Array:(const matrix_double4x4 *)valuesArray atTimes:(const NSTimeInterval *)timesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat4x4Array:(matrix_float4x4 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble4x4Array:(matrix_double4x4 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
