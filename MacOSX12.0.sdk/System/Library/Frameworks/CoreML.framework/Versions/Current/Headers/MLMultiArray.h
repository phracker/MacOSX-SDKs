//
//  MLMultiArray.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>
#import <CoreVideo/CVPixelBuffer.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Allowed data types for multidimensional arrays
 */
typedef NS_ENUM(NSInteger, MLMultiArrayDataType) {
    MLMultiArrayDataTypeDouble  = 0x10000 | 64,
    MLMultiArrayDataTypeFloat64 API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000 | 64,
    MLMultiArrayDataTypeFloat32 = 0x10000 | 32,
    MLMultiArrayDataTypeFloat16 API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos) = 0x10000 | 16,
    MLMultiArrayDataTypeFloat   API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000 | 32,
    MLMultiArrayDataTypeInt32   = 0x20000 | 32,
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


/*!
 * Multidimensional Array
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLMultiArray : NSObject <NSSecureCoding>

/// Unsafe pointer to underlying buffer holding the data
@property (readonly, nonatomic) void *dataPointer NS_RETURNS_INNER_POINTER;

/// Type of element held
@property (readonly, nonatomic) MLMultiArrayDataType dataType;

/// An array containing the sizes of each dimension in the multiarray
@property (readonly, nonatomic) NSArray<NSNumber *> *shape;

/*!
 * An array containing the stride in memory for each dimension.
 * The element referred to by a multidimensional index is located at an offset equal to
 * sum_d index[d]*strides[d]. This offset is in the units of the specified dataType.
 */
@property (readonly, nonatomic) NSArray<NSNumber *> *strides;

/// Count of total number of elements
@property (readonly, nonatomic) NSInteger count;

/**
   Returns the backing pixel buffer if exists, otherwise nil.
 */
@property (readonly, nullable, nonatomic) CVPixelBufferRef pixelBuffer API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

@interface MLMultiArray (Creation)

/// Create by C-style contiguous array by allocating and managing the necessary memory
- (nullable instancetype)initWithShape:(NSArray<NSNumber *> *)shape
                              dataType:(MLMultiArrayDataType)dataType
                                 error:(NSError **)error;


/// Create by wrapping existing data
- (nullable instancetype)initWithDataPointer:(void *)dataPointer
                                       shape:(NSArray<NSNumber *> *)shape
                                    dataType:(MLMultiArrayDataType)dataType
                                     strides:(NSArray<NSNumber *> *)strides
                                 deallocator:(void (^_Nullable)(void *bytes))deallocator
                                       error:(NSError **)error;

/*!
 * Create by wrapping a pixel buffer.
 *
 * Use this initializer to create IOSurface backed MLMultiArray, which can reduce the inference latency by avoiding the buffer copy.
 *
 * The instance will own the pixel buffer and release it on the deallocation.
 *
 * The pixel buffer's pixel format type must be OneComponent16Half. As such, MLMultiArray's data type will be MLMultiArrayDataTypeFloat16.
 *
 * \code
 * CVPixelBufferRef pixelBuffer = NULL;
 * NSDictionary* pixelBufferAttributes = @{
 *     (id)kCVPixelBufferIOSurfacePropertiesKey: @{}
 * };
 *
 * // Since shape == [2, 3, 4], width is 4 (= shape[2]) and height is 6 (= shape[0] * shape[1]).
 * CVPixelBufferCreate(kCFAllocatorDefault, 4, 6, kCVPixelFormatType_OneComponent16Half, (__bridge CFDictionaryRef)pixelBufferAttributes, &pixelBuffer);
 * MLMultiArray *multiArray = [[MLMultiArray alloc] initWithPixelBuffer:pixelBuffer shape:@[@2, @3, @4]];
 * \endcode
 *
 * @param pixelBuffer The pixel buffer to be owned by the instance.
 *
 * @param shape The shape of the MLMultiArray. The last dimension of `shape` must match the pixel buffer's width. The product of the rest of the dimensions must match the height.
 */
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer
                              shape:(NSArray<NSNumber *> *)shape API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

@interface MLMultiArray (Concatenating)

/*!
 * Concatenate MLMultiArrays to form a new MLMultiArray.
 *
 * All the source MLMultiArrays must have a same shape except the specified axis. The resultant
 * MLMultiArray has the same shape as inputs except this axis, which dimension will be the sum of
 * all the input dimensions of the axis.
 *
 * For example,
 *
 * \code
 * // Swift
 * let A = try MLMultiArray(shape: [2, 3], dataType: .int32)
 * let B = try MLMultiArray(shape: [2, 2], dataType: .int32)
 * let C = MLMultiArray(concatenating: [A, B], axis: 1, dataType: .int32)
 * assert(C.shape == [2, 5])
 * \endcode
 *
 * \code
 * // Obj-C
 * MLMultiArray *A = [[MLMultiArray alloc] initWithShape:@[@2, @3] dataType:MLMultiArrayDataTypeInt32 error:NULL];
 * MLMultiArray *B = [[MLMultiArray alloc] initWithShape:@[@2, @2] dataType:MLMultiArrayDataTypeInt32 error:NULL];
 * MLMultiArray *C = [MLMultiArray multiArrayByConcatenatingMultiArrays:@[A, B] alongAxis:1 dataType:MLMultiArrayDataTypeInt32];
 * assert(C.shape == @[@2, @5])
 * \endcode
 *
 * Numeric data will be up or down casted as needed.
 *
 * The method raises NSInvalidArgumentException if the shapes of input multi arrays are not
 * compatible for concatenation.
 *
 * @param multiArrays Array of MLMultiArray instances to be concatenated.
 *
 * @param axis Axis index with which the concatenation will performed. The value is wrapped by the
 * dimension of the axis. For example, -1 is the last axis.
 *
 * @param dataType The data type of the resultant MLMultiArray
 */
+ (instancetype)multiArrayByConcatenatingMultiArrays:(NSArray<MLMultiArray *> *)multiArrays
                                           alongAxis:(NSInteger)axis
                                            dataType:(MLMultiArrayDataType)dataType API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));
@end

@interface MLMultiArray (NSNumberDataAccess)

/// Get a value by its linear index (assumes C-style index ordering)
- (NSNumber *)objectAtIndexedSubscript:(NSInteger)idx;

/// Get a value by its multidimensional index (NSArray<NSNumber *>)
- (NSNumber *)objectForKeyedSubscript:(NSArray<NSNumber *> *)key;

/// Set a value by its linear index (assumes C-style index ordering)
- (void)setObject:(NSNumber *)obj atIndexedSubscript:(NSInteger)idx;

/// Set a value by subindicies (NSArray<NSNumber *>)
- (void)setObject:(NSNumber *)obj forKeyedSubscript:(NSArray<NSNumber *> *)key;

@end

NS_ASSUME_NONNULL_END
