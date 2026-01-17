//
//  MTLStageInputOutputDescriptor.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>



NS_ASSUME_NONNULL_BEGIN

/*
 MTLAttributeFormat
*/
typedef NS_ENUM(NSUInteger, MTLAttributeFormat)
{
    MTLAttributeFormatInvalid = 0,
    
    MTLAttributeFormatUChar2 = 1,
    MTLAttributeFormatUChar3 = 2,
    MTLAttributeFormatUChar4 = 3,
    
    MTLAttributeFormatChar2 = 4,
    MTLAttributeFormatChar3 = 5,
    MTLAttributeFormatChar4 = 6,
    
    MTLAttributeFormatUChar2Normalized = 7,
    MTLAttributeFormatUChar3Normalized = 8,
    MTLAttributeFormatUChar4Normalized = 9,
    
    MTLAttributeFormatChar2Normalized = 10,
    MTLAttributeFormatChar3Normalized = 11,
    MTLAttributeFormatChar4Normalized = 12,
    
    MTLAttributeFormatUShort2 = 13,
    MTLAttributeFormatUShort3 = 14,
    MTLAttributeFormatUShort4 = 15,
    
    MTLAttributeFormatShort2 = 16,
    MTLAttributeFormatShort3 = 17,
    MTLAttributeFormatShort4 = 18,
    
    MTLAttributeFormatUShort2Normalized = 19,
    MTLAttributeFormatUShort3Normalized = 20,
    MTLAttributeFormatUShort4Normalized = 21,
    
    MTLAttributeFormatShort2Normalized = 22,
    MTLAttributeFormatShort3Normalized = 23,
    MTLAttributeFormatShort4Normalized = 24,
    
    MTLAttributeFormatHalf2 = 25,
    MTLAttributeFormatHalf3 = 26,
    MTLAttributeFormatHalf4 = 27,
    
    MTLAttributeFormatFloat = 28,
    MTLAttributeFormatFloat2 = 29,
    MTLAttributeFormatFloat3 = 30,
    MTLAttributeFormatFloat4 = 31,
    
    MTLAttributeFormatInt = 32,
    MTLAttributeFormatInt2 = 33,
    MTLAttributeFormatInt3 = 34,
    MTLAttributeFormatInt4 = 35,
    
    MTLAttributeFormatUInt = 36,
    MTLAttributeFormatUInt2 = 37,
    MTLAttributeFormatUInt3 = 38,
    MTLAttributeFormatUInt4 = 39,
    
    MTLAttributeFormatInt1010102Normalized = 40,
    MTLAttributeFormatUInt1010102Normalized = 41,
    
    MTLAttributeFormatUChar4Normalized_BGRA NS_ENUM_AVAILABLE(10_13, 11_0) = 42,
    
    MTLAttributeFormatUChar NS_ENUM_AVAILABLE(10_13, 11_0) = 45,
    MTLAttributeFormatChar NS_ENUM_AVAILABLE(10_13, 11_0) = 46,
    MTLAttributeFormatUCharNormalized NS_ENUM_AVAILABLE(10_13, 11_0) = 47,
    MTLAttributeFormatCharNormalized NS_ENUM_AVAILABLE(10_13, 11_0) = 48,
    
    MTLAttributeFormatUShort NS_ENUM_AVAILABLE(10_13, 11_0) = 49,
    MTLAttributeFormatShort NS_ENUM_AVAILABLE(10_13, 11_0) = 50,
    MTLAttributeFormatUShortNormalized NS_ENUM_AVAILABLE(10_13, 11_0) = 51,
    MTLAttributeFormatShortNormalized NS_ENUM_AVAILABLE(10_13, 11_0) = 52,
    
    MTLAttributeFormatHalf NS_ENUM_AVAILABLE(10_13, 11_0) = 53,
    
} NS_ENUM_AVAILABLE(10_12, 10_0);


typedef NS_ENUM(NSUInteger, MTLIndexType) {
    MTLIndexTypeUInt16 = 0,
    MTLIndexTypeUInt32 = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);


typedef NS_ENUM(NSUInteger, MTLStepFunction)
{
    MTLStepFunctionConstant = 0,

    // vertex functions only
    MTLStepFunctionPerVertex = 1,
    MTLStepFunctionPerInstance = 2,
    MTLStepFunctionPerPatch NS_ENUM_AVAILABLE(10_12, 10_0) = 3,
    MTLStepFunctionPerPatchControlPoint NS_ENUM_AVAILABLE(10_12, 10_0) = 4,

    // compute functions only
    MTLStepFunctionThreadPositionInGridX = 5,
    MTLStepFunctionThreadPositionInGridY = 6,
    MTLStepFunctionThreadPositionInGridXIndexed = 7,
    MTLStepFunctionThreadPositionInGridYIndexed = 8,
} NS_ENUM_AVAILABLE(10_12, 10_0);


NS_CLASS_AVAILABLE(10_12, 10_0)
@interface MTLBufferLayoutDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) NSUInteger stride;
@property (assign, nonatomic) MTLStepFunction stepFunction;
@property (assign, nonatomic) NSUInteger stepRate;
@end

NS_CLASS_AVAILABLE(10_12, 10_0)
@interface MTLBufferLayoutDescriptorArray : NSObject
- (MTLBufferLayoutDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLBufferLayoutDescriptor *)bufferDesc atIndexedSubscript:(NSUInteger)index;
@end

NS_CLASS_AVAILABLE(10_12, 10_0)
@interface MTLAttributeDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) MTLAttributeFormat format;
@property (assign, nonatomic) NSUInteger offset;
@property (assign, nonatomic) NSUInteger bufferIndex;
@end

NS_CLASS_AVAILABLE(10_12, 10_0)
@interface MTLAttributeDescriptorArray : NSObject
- (MTLAttributeDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLAttributeDescriptor *)attributeDesc atIndexedSubscript:(NSUInteger)index;
@end

/*
 MTLStageInputOutputDescriptor
 */
NS_CLASS_AVAILABLE(10_12, 10_0)
@interface MTLStageInputOutputDescriptor : NSObject <NSCopying>

+ (MTLStageInputOutputDescriptor *)stageInputOutputDescriptor;

@property (readonly) MTLBufferLayoutDescriptorArray *layouts;
@property (readonly) MTLAttributeDescriptorArray *attributes;

/* only used for compute with MTLStepFunction...Indexed */
@property (assign, nonatomic) MTLIndexType indexType;
@property (assign, nonatomic) NSUInteger indexBufferIndex;

- (void)reset;

@end
NS_ASSUME_NONNULL_END
