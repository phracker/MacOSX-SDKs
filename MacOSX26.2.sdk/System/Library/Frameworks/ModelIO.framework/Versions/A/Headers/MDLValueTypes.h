/*!
 @header MDLValueTypes.h
 @framework ModelIO
 @abstract SIMD array value types
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import <ModelIO/MDLTypes.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
MDL_EXPORT
@interface MDLMatrix4x4Array : NSObject<NSCopying>

@property (nonatomic, readonly) NSUInteger elementCount;

@property (nonatomic, readonly) MDLDataPrecision precision;

-(void)clear;
-(instancetype)initWithElementCount:(NSUInteger)arrayElementCount;

-(void)setFloat4x4Array:(const matrix_float4x4 *)valuesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;
-(void)setDouble4x4Array:(const matrix_double4x4 *)valuesArray count:(NSUInteger)count NS_REFINED_FOR_SWIFT;

-(NSUInteger)getFloat4x4Array:(matrix_float4x4 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
-(NSUInteger)getDouble4x4Array:(matrix_double4x4 *)valuesArray maxCount:(NSUInteger)maxCount NS_REFINED_FOR_SWIFT;
@end

NS_ASSUME_NONNULL_END
