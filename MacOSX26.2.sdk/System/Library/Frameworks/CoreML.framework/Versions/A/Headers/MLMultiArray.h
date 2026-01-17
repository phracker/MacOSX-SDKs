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

/// The data type of scalars in the multi-array.
typedef NS_ENUM(NSInteger, MLMultiArrayDataType) {
    MLMultiArrayDataTypeDouble  = 0x10000 | 64,
    MLMultiArrayDataTypeFloat64 API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000 | 64,
    MLMultiArrayDataTypeFloat32 = 0x10000 | 32,
    MLMultiArrayDataTypeFloat16 API_AVAILABLE(macos(12.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x10000 | 16,
    MLMultiArrayDataTypeFloat   API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000 | 32,
    MLMultiArrayDataTypeInt32   = 0x20000 | 32,
    MLMultiArrayDataTypeInt8    API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0)) = 0x20000 | 8,
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Use `MLMultiArray` to store a multi-dimensional value.
///
/// Unlike `MLShapedArray` or `MLTensor`, `MLMultiArray` can be used in Obj-C code. Unlike `MLTensor`, `MLMultiArray` is
/// always backed by a concrete storage.
///
/// The object has properties to define the interpretation of the storage.
///
/// `.dataType` defines the interpretation of raw bytes into a numeric scalar value. For example,
/// `MLMultiArrayDataTypeFloat32` means the backing storage uses IEEE 754 Float32 encoding.
///
/// `.shape` defines the multi-dimensional space. For example, 30 x 20 image with three color components (Red, Green,
/// Blue) could be defined using the shape `[3, 20, 30]`.
///
/// `.strides` defines the offset addressing of the scalar for a given coordinates. For example, the image above might
/// use `[640, 32, 1]` as the `strides`. Then, the scalar at (1, 10, 15) is stored at `640 * 1 + 32 * 10 + 1 * 15`, or
/// 975th scalar in the storage. In general, the scalar offset for coordinates `index` and strides `strides` is:
///
/// ```
/// scalarOffset = sum_d index[d]*strides[d]
/// ```
///
/// The backing storage can be a heap allocated buffer or CVPixelBuffer. Though CVPixelBuffer backing supports limited
/// data types, `MLModel` could share the storage with backend hardware such as Apple Neural Engine without copy.
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLMultiArray : NSObject <NSSecureCoding>

/// Unsafe pointer to underlying buffer holding the data
@property (readonly, nonatomic) void *dataPointer NS_RETURNS_INNER_POINTER API_DEPRECATED("Use getBytesWithHandler or getMutableBytesWithHandler instead. For Swift, use withUnsafeBytes or withUnsafeMutableBytes.", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED));

/// Scalar's data type.
@property (readonly, nonatomic) MLMultiArrayDataType dataType;

/// Shape of the multi-dimensional space that this instance represents.
@property (readonly, nonatomic) NSArray<NSNumber *> *shape;

/// Strides.
///
/// It defines the offset of the scalar of a given coordinate index in the storage, which is:
/// ```
/// scalarOffset = sum_d index[d]*strides[d]
/// ```
@property (readonly, nonatomic) NSArray<NSNumber *> *strides;

/// Count of total number of addressable scalars.
///
/// The value is same as `product_d shape[d]`.
@property (readonly, nonatomic) NSInteger count;

/// Returns the backing pixel buffer if exists, otherwise nil.
@property (readonly, nullable, nonatomic) CVPixelBufferRef pixelBuffer API_AVAILABLE(macos(12.0), ios(16.0), watchos(9.0), tvos(16.0));

@end

@interface MLMultiArray (Creation)

/// Creates the object.
///
/// The contents of the object are left uninitialized; the client must initialize it.
///
/// The scalars will use the first-major contiguous layout.
///
/// - Parameters:
///   - shape: The shape
///   - dataType: The data type
///   - error: Filled with error information on error.
- (nullable instancetype)initWithShape:(NSArray<NSNumber *> *)shape
                              dataType:(MLMultiArrayDataType)dataType
                                 error:(NSError **)error;

/// Creates the object with specified strides.
///
/// The contents of the object are left uninitialized; the client must initialize it.
///
/// ```swift
/// let shape = [2, 3];
/// let strides = [4, 1]
///
/// let multiArray = MLMultiArray(shape: shape, dataType: .float32, strides: strides)
/// XCTAssertEqual(multiArray.shape, shape as [NSNumber])
/// XCTAssertEqual(multiArray.strides, strides as [NSNumber])
/// ```
///
/// ```objc
/// NSArray<NSNumber *> *shape = @[@2, @3];
/// NSArray<NSNumber *> *strides = @[@4, @1];
///
/// MLMultiArray *multiArray = [[MLMultiArray alloc] initWithShape:shape
///                                                       dataType:MLMultiArrayDataTypeFloat32
///                                                        strides:strides];
/// XCTAssertEqualObjects(multiArray.shape, shape);
/// XCTAssertEqualObjects(multiArray.strides, strides);
/// ```
///
/// - Parameters:
///   - shape: The shape
///   - dataType: The data type
///   - strides: The strides.
- (instancetype)initWithShape:(NSArray<NSNumber *> *)shape
                     dataType:(MLMultiArrayDataType)dataType
                      strides:(NSArray<NSNumber *> *)strides NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Creates the object with existing data without copy.
///
/// Use this initializer to reference the existing buffer as the storage without copy.
///
/// ```objc
/// int32_t *buffer = malloc(sizeof(int32_t) * 2 * 3 * 4);
/// MLMultiArray *multiArray = [[MLMultiArray alloc] initWithDataPointer:buffer
///                                                                shape:@[@2, @3, @4]
///                                                             dataType:MLMultiArrayDataTypeInt32
///                                                              strides:@[@12, @4, @1]
///                                                          deallocator:^(void *bytes) { free(bytes); }
///                                                                error:NULL];
/// ```
///
/// - Parameters:
///   - dataPointer: The pointer to the buffer.
///   - shape: The shape
///   - dataType: The data type
///   - strides: The strides.
///   - deallocator: Block to be called on the deallocation of the instance.
///   - error: Filled with error information on error.
- (nullable instancetype)initWithDataPointer:(void *)dataPointer
                                       shape:(NSArray<NSNumber *> *)shape
                                    dataType:(MLMultiArrayDataType)dataType
                                     strides:(NSArray<NSNumber *> *)strides
                                 deallocator:(void (^_Nullable)(void *bytes))deallocator
                                       error:(NSError **)error;

/// Create by wrapping a pixel buffer.
///
/// Use this initializer to create an IOSurface backed MLMultiArray, which can reduce the inference latency by avoiding the buffer copy.
///
/// The instance will own the pixel buffer and release it on the deallocation.
///
/// The pixel buffer's pixel format type must be either `kCVPixelFormatType_OneComponent16Half` for `MLMultiArrayDataTypeFloat16` or
/// `kCVPixelFormatType_OneComponent8` for `MLMultiArrayDataTypeInt8`.
///
/// ```objc
/// CVPixelBufferRef pixelBuffer = NULL;
/// NSDictionary* pixelBufferAttributes = @{
///     (id)kCVPixelBufferIOSurfacePropertiesKey: @{}
/// };
///
/// // Since shape == [2, 3, 4], width is 4 (= shape[2]) and height is 6 (= shape[0] * shape[1]).
/// CVPixelBufferCreate(kCFAllocatorDefault, 4, 6, kCVPixelFormatType_OneComponent16Half, (__bridge CFDictionaryRef)pixelBufferAttributes, &pixelBuffer);
/// MLMultiArray *multiArray = [[MLMultiArray alloc] initWithPixelBuffer:pixelBuffer shape:@[@2, @3, @4]];
/// ```
///
/// - Parameters:
///   - pixelBuffer: The pixel buffer to be owned by the instance.
///   - shape: The shape of the MLMultiArray. The last dimension of `shape` must match the pixel buffer's width. The product of the rest of the dimensions must match the height.
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer
                              shape:(NSArray<NSNumber *> *)shape API_AVAILABLE(macos(12.0), ios(16.0), watchos(9.0), tvos(16.0));

@end

@interface MLMultiArray (ScopedBufferAccess)

/// Get the underlying buffer pointer to read.
///
/// The buffer pointer is valid only within the block.
///
/// ```objc
/// MLMultiArray * A = [[MLMultiArray alloc] initWithShape:@[@3, @2] dataType:MLMultiArrayDataTypeInt32 error:NULL];
/// A[@[@1, @2]] = @42;
/// [A getBytesWithHandler:^(const void *bytes, NSInteger size) {
///     const int32_t *scalarBuffer = (const int32_t *)bytes;
///     const int strideY = A.strides[0].intValue;
///     // Print 42
///     NSLog(@"Scalar at (1, 2): %d", scalarBuffer[1 * strideY + 2]);
/// }];
/// ```
/// - Parameters:
///   - handler: The block to receive the buffer pointer and its size in bytes.
- (void)getBytesWithHandler:(void (NS_NOESCAPE ^)(const void *bytes, NSInteger size))handler API_AVAILABLE(macos(12.3), ios(15.4), watchos(8.5), tvos(15.4)) NS_REFINED_FOR_SWIFT;

/// Get the underlying buffer pointer to mutate.
///
/// The buffer pointer is valid only within the block.
///
/// Use `strides` parameter passed in the block because the method may switch to a new backing buffer with different strides.
///
/// ```objc
/// MLMultiArray * A = [[MLMultiArray alloc] initWithShape:@[@3, @2] dataType:MLMultiArrayDataTypeInt32 error:NULL];
/// [A getMutableBytesWithHandler:^(void *bytes, NSInteger __unused size, NSArray<NSNumber *> *strides) {
///     int32_t *scalarBuffer = (int32_t *)bytes;
///     const int strideY = strides[0].intValue;
///     scalarBuffer[1 * strideY + 2] = 42;  // Set 42 at A[1, 2]
/// }];
/// ```
///
/// - Parameters:
///   - handler: The block to receive the buffer pointer, size in bytes, and strides.
- (void)getMutableBytesWithHandler:(void (NS_NOESCAPE ^)(void *mutableBytes, NSInteger size, NSArray<NSNumber *> *strides))handler API_AVAILABLE(macos(12.3), ios(15.4), watchos(8.5), tvos(15.4)) NS_REFINED_FOR_SWIFT;

@end

@interface MLMultiArray (Concatenating)

/// Concatenate MLMultiArrays to form a new MLMultiArray.
///
/// All the source MLMultiArrays must have a same shape except the specified axis. The resultant
/// MLMultiArray has the same shape as inputs except this axis, which dimension will be the sum of
/// all the input dimensions of the axis.
///
/// For example,
///
/// ```swift
/// // Swift
/// let A = try MLMultiArray(shape: [2, 3], dataType: .int32)
/// let B = try MLMultiArray(shape: [2, 2], dataType: .int32)
/// let C = MLMultiArray(concatenating: [A, B], axis: 1, dataType: .int32)
/// assert(C.shape == [2, 5])
/// ```
///
/// ```objc
/// // Obj-C
/// MLMultiArray *A = [[MLMultiArray alloc] initWithShape:@[@2, @3] dataType:MLMultiArrayDataTypeInt32 error:NULL];
/// MLMultiArray *B = [[MLMultiArray alloc] initWithShape:@[@2, @2] dataType:MLMultiArrayDataTypeInt32 error:NULL];
/// MLMultiArray *C = [MLMultiArray multiArrayByConcatenatingMultiArrays:@[A, B] alongAxis:1 dataType:MLMultiArrayDataTypeInt32];
/// assert(C.shape == @[@2, @5])
/// ```
///
/// Numeric data will be up or down casted as needed.
///
/// The method raises NSInvalidArgumentException if the shapes of input multi arrays are not
/// compatible for concatenation.
///
/// - Parameters:
///   - multiArrays: Array of MLMultiArray instances to be concatenated.
///   - axis: Axis index with which the concatenation will performed. The value is wrapped by the dimension of the axis. For example, -1 is the last axis.
///   - dataType: The data type of the resultant MLMultiArray.
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

@interface MLMultiArray (Transferring)

/// Transfer the contents to the destination multi-array.
///
/// Numeric data will be up or down casted as needed. It can transfer to a multi-array with different layout (strides).
///
/// ```swift
/// let sourceMultiArray: MLMultiArray = ... // shape is [2, 3] and data type is Float64
///
/// let newStrides = [4, 1]
/// let destinationMultiArray = MLMultiArray(shape: [2, 3], 
///                                          dataType: .float32, 
///                                          strides: newStrides)
/// sourceMultiArray.transfer(to: destinationMultiArray)
/// ```
///
/// ```objc
/// NSArray<NSNumber *> *shape = @[@2, @3];
/// NSArray<NSNumber *> *sourceStrides = @[@3, @1];
/// NSArray<NSNumber *> *destinationStrides = @[@4, @1];
/// MLMultiArray *source = [[MLMultiArray alloc] initWithShape:shape
///                                                   dataType:MLMultiArrayDataTypeDouble
///                                                    strides:sourceStrides];
/// // Initialize source...
///
/// MLMultiArray *destination = [[MLMultiArray alloc] initWithShape:shape
///                                                        dataType:MLMultiArrayDataTypeFloat32
///                                                         strides:destinationStrides];
/// [source transferToMultiArray:destination];
/// ```
///
/// - Parameters:
///   - destinationMultiArray: The transfer destination.
- (void)transferToMultiArray:(MLMultiArray *)destinationMultiArray API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));
@end

NS_ASSUME_NONNULL_END
