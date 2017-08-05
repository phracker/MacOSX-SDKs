//
//  MTLComputePipeline.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLArgument.h>
#import <Metal/MTLStageInputOutputDescriptor.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLComputePipelineReflection : NSObject

@property (readonly) NSArray <MTLArgument *> *arguments;


@end

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTLComputePipelineDescriptor : NSObject <NSCopying>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, nonatomic) NSString *label;

/*!
 @property computeFunction
 @abstract The function to use with the MTLComputePipelineState
 */
@property (nullable, readwrite, nonatomic, strong) id <MTLFunction> computeFunction;

/*!
 @property threadGroupSizeIsMultipleOfThreadExecutionWidth
 @abstract An optimization flag, set if the thread group size will always be a multiple of thread execution width
 */
@property (readwrite, nonatomic) BOOL threadGroupSizeIsMultipleOfThreadExecutionWidth;


/*!
 @property computeDataDescriptor
 @abstract An MTLStageInputOutputDescriptor to fetch data from buffers
 */
@property (nullable, copy, nonatomic) MTLStageInputOutputDescriptor *stageInputDescriptor NS_AVAILABLE(10_12, 10_0);

/*!
 @method reset
 @abstract Restore all compute pipeline descriptor properties to their default values.
 */
- (void)reset;

@end

/*!
 @protocol MTLComputePipelineState
 @abstract A handle to compiled code for a compute function.
 @discussion MTLComputePipelineState is a single compute function.  It can only be used with the device that it was created against.
*/
NS_AVAILABLE(10_11, 8_0)
@protocol MTLComputePipelineState <NSObject>

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property maxTotalThreadsPerThreadgroup
 @abstract The maximum total number of threads that can be in a single compute threadgroup.
 */
@property (readonly) NSUInteger maxTotalThreadsPerThreadgroup;

/*!
 @property threadExecutionWidth
 @abstract For most efficient execution, the threadgroup size should be a multiple of this when executing the kernel.
 */
@property (readonly) NSUInteger threadExecutionWidth;

@end
NS_ASSUME_NONNULL_END
