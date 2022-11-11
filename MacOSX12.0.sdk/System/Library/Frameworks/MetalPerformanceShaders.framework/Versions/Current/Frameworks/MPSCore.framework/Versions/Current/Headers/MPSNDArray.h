//
//  MPSNDArray.h
//  MPSCore
//
//  Created on 11/16/18.
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef MPSNDArray_h
#define MPSNDArray_h

#include <MPSCore/MPSCoreTypes.h>
#import <Metal/MTLBuffer.h>
#include <simd/simd.h>

@class MPSMatrix;
@class MPSMatrixDescriptor;
@class MPSImage;
typedef NSArray<MPSImage*>  MPSImageBatch;

/*!
 *  @class      MPSNDArrayDescriptor
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSNDArrayDescriptor object describes a attributes of MPSNDArray and is used to
 *              create one (see MPSNDArray discussion below) */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayDescriptor : NSObject

/*! @abstract  Data Type of the MPSNDArray elements
 */
@property (readwrite, nonatomic)  MPSDataType dataType;

/*! @abstract   The number of dimensions in the NDArray.
 *  @discussion May not exceed 16. A 0-diumension MPSNDArray is a single scalar value.
 *              Undefined dimensions are implicitly length 1. */
@property (readwrite, nonatomic)  NSUInteger numberOfDimensions;

/*! @abstract   The number of elements of type dataType in the indicated dimension.
 *  @discussion If dimensionIndex >= numberOfDimensions, 1 will be returned.
 *  @param      dimensionIndex  dimension the MPSNDArray for which to return the length
 *  @return     The number of elements in that dimension. */
-(NSUInteger)  lengthOfDimension: (NSUInteger)dimensionIndex;

/*! @abstract      The slice dimensions for each dimension
 *  @discusion     A slice is a subregion of a dimension. It is
 *                 used to calve off a fraction of a larger NDArray.
 *  @param         dimensionIndex           The index of the dimension
 *  @return        Returns the slice range for the index. If the
 *                 dimensionIndex >= numberOfDimensions, {0,1} is returned. */
-(MPSDimensionSlice)   sliceRangeForDimension:  (NSUInteger) dimensionIndex;

/*! @abstract      The slice dimensions for each dimension
 *  @discusion     A slice is a subregion of a dimension. It is
 *                 used to calve off a fraction of a larger NDArray.
 *
 *                 Default:  NSRange(0, lengthOfDimension(i))
 *
 *  @param         subRange                 The region of the slice, start value is wrt dimensionLength of the NDArray.
 *  @param         dimensionIndex           The index of the dimension. Must be < numberOfDimensions */
-(void)      sliceDimension: (NSUInteger) dimensionIndex
               withSubrange: (MPSDimensionSlice) subRange;

/*! @abstract    transpose two dimensions
 *  @discusion   If the intention is to insert a length 1 dimension, increment the numberOfDimensions first.
 *  @param       dimensionIndex  The first dimension. Must be < numberOfDimensions
 *  @param       dimensionIndex2 The second dimension.  Must be < number of Dimensions. */
-(void)     transposeDimension: (NSUInteger) dimensionIndex
                 withDimension: (NSUInteger) dimensionIndex2;

/*! @abstract    The new ordering of dimensions
 *  @discussion  If a transpose is applied, it will change the order
 *               of dimensions in the MPSNDArray. The default ordering is
 *               {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}.  After a transpose
 *               of dimensions 0 and 1, it will be: {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15}     */
-(vector_uchar16)   dimensionOrder;

/*! @abstract   Create an MPSNDArrayDescriptor object for a given size of dimensions.
 *  @discussion Sample code:
 *   @code
 *                // Creates an NDArrayDescriptor of dimensions [32, 6, 5, 3]
 *                NSUInteger sizes[] = {3,5,6,32};
 *                [ MPSNDArray descriptorWithDataType: MPSDataTypeFloat32
 *                                     dimensionCount: 4
 *                                     dimensionSizes: sizes ];    // array of numberOfDimensions dimensions. Starts with dimension 0
 *   @endcode
 *  @param      dataType           MPSDataType of elements in the MPSNDArray
 *  @param      numberOfDimensions Number of dimensions in the NDArray. May not exceed 16.
 *  @param      dimensionSizes     An array of NSUIntegers where dimension lengths provided by the user goes from fastest
 *                                 moving to slowest moving dimension.
 *                                 The product of all dimension lengths must be less than 2**31.
 *                                 Additional system memory limits may apply
 *  @return     A valid MPSNDArrayDescriptor object or nil, if failure. */
+(nonnull instancetype) descriptorWithDataType: (MPSDataType) dataType
                                dimensionCount: (NSUInteger) numberOfDimensions
                                dimensionSizes: (NSUInteger*__nonnull) dimensionSizes;

/*! @abstract   A convenience function to create an MPSNDArrayDescriptor object for a given size of dimensions.
 *  @discussion Sample code:
 *   @code
 *                // Creates an NDArrayDescriptor of dimensions [32, 6, 5, 3]
 *                NSArray<NSNumber *> sizes = {@32,@6,@5,@3};
 *                [ MPSNDArray descriptorWithDataType: MPSDataTypeFloat32
 *                                              shape: &sizes];
 *   @endcode
 *  @param      dataType           MPSDataType of elements in the MPSNDArray
 *  @param      shape              An array of NSUIntegers where dimension lengths provided by the user goes from slowest
 *                                 moving to fastest moving dimension. This is same order as MLMultiArray in coreML and most frameworks in Python
 *                                 The product of all dimension lengths must be less than 2**31.
 *                                 Additional system memory limits may apply
 *  @return     A valid MPSNDArrayDescriptor object or nil, if failure. */
+(nonnull instancetype) descriptorWithDataType: (MPSDataType) dataType
                                         shape: (NSArray<NSNumber *> * _Nonnull) shape;


/*! @abstract   Create an MPSNDArrayDescriptor object for a given size of dimensions.
 *  @discussion     Sample code:
 *   @code
 *                // Creates an NDArrayDescriptor of dimensions [32, 5, 6, 3]
 *                [ MPSNDArray descriptorWithDataType: MPSDataTypeFloat32
 *                                     dimensionSizes: 3, 6, 5, 32, 0 //<--list terminator! ]; // array of numberOfDimensions dimensions. Starts with dimension 0
 *   @endcode
 *  @param      dataType           MPSDataType of elements in the MPSNDArray
 *  @param      dimension0         The start of a 0-terminated variadric list of NSUIntegers where dimension lengths provided by the user goes from fastest
 *                                 moving to slowest moving dimension.
 *                                 The product of all dimension sizes must be less than 2**31.
 *                                 Additional system memory limits may apply
 *  @return     A valid MPSNDArrayDescriptor object or nil, if failure. */
+(nonnull instancetype) descriptorWithDataType: (MPSDataType) dataType
                                dimensionSizes: (NSUInteger) dimension0, ...;

/*! @abstract   Changes dimension sizes and number of dimensions on the current descriptor
 *  @param      numberOfDimensions Number of dimensions in the NDArray. May not exceed 16.
 *  @param      dimensionSizes     An array of NSUIntegers where dimension lengths provided by the user goes from fastest
 *                                 moving to slowest moving dimension.
 *                                 The product of all dimension lengths must be less than 2**31.
 *                                 Additional system memory limits may apply
 */
-(void) reshapeWithDimensionCount: (NSUInteger) numberOfDimensions
                   dimensionSizes: (NSUInteger*__nonnull) dimensionSizes;

/*! @abstract   Changes dimension sizes and number of dimensions on the current descriptor
 *  @param      shape              An array of NSUIntegers where dimension lengths provided by the user goes from slowest
 *                                 moving to fastest moving dimension. This is same order as MLMultiArray in coreML and most frameworks in Python
 *                                 The product of all dimension lengths must be less than 2**31.
 *                                 Additional system memory limits may apply
 */
-(void) reshapeWithShape: (NSArray<NSNumber *> * _Nonnull) shape;

/*! @abstract Use -descriptorWithDataType:... instead */
-(nonnull instancetype) init NS_UNAVAILABLE;
@end

@class MPSKernel;
@class MPSNDArray;

@protocol MPSNDArrayAllocator <NSObject, NSSecureCoding, NSCopying>
@required

/*! @abstract   Create a new MPSNDArray
 *  @discussion See class description for sample implementation
 *  @param          cmdBuf      The MTLCommandBuffer on which the array will be initialized.
 *                              cmdBuf.device encodes the MTLDevice.
 *  @param          descriptor  A MPSNDArrayDescriptor containing the array parameters to use.
 *                              This format is the result of your MPSPadding policy.
 *  @param          kernel      The kernel that will overwrite the array returned by the filter.
 *                              Note that the MPS implementations of this protocol don't need
 *                              this field. It is provided for your convenience.
 *
 *  @return         A valid MPSNDArray or MPSTemporaryNDArray. It will be automatically released when the command buffer completes.
 */
-(MPSNDArray * __nonnull)  arrayForCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                 arrayDescriptor: (MPSNDArrayDescriptor * __nonnull) descriptor
                                          kernel: (MPSKernel * __nonnull) kernel;

@end


/*! @class      MPSNDArray
 *  @abstract   A MPSNDArray object is a MTLBuffer based storage container for multi-dimensional data.
 *  @discussion Operations on MPSNDArrays will commonly implicitly reshape the multidimensional
 *              structure into a 2-dimensional structure by reinterpreting higher dimensions as a single dimensional
 *              array of matrix rows. For example a [a, b, c, d] NDArray passed to a matrix multiplication may
 *              be implicitly reinterpreted as a [a*b*c, d] matrix and a 2D matrix multiplication performed.
 *              In practice, the major row (the dimension in which successive elements appear adjacent to one
 *              another in memory) is the 0th dimension (represented as 'd' in the above example).  It has both a
 *              dimension size indicating the number of elements and a storage size which may be slightly bigger
 *              to allow for performance improvement arising from better data alignment in memory.  In principle,
 *              the rowBytes may also be used to create a 0th-dimension slice out of a larger array stored in the
 *              underlying MTLBuffer.
 *
 *              MPS will automatically manage the storage size of the major row ("rowBytes") though you may
 *              set it in the descriptor if you have a need to do so. Generally, it should be at least a multiple
 *              of 16 bytes.   Dimensions after the 0th are a densely packed array of rows of size rowBytes.
 *              Thus, the 1st dimension is an array of rows. The 2nd dimension is an array of arrays of rows with
 *              identical size, and so forth.  When the reduction to 2 dimensions is done, no data is moved. MPS
 *              just reinterprets a higher order N-1 dimensions of matrix rows as a single large 1-dimensional
 *              array of rows.
 *
 *              It is a common desire to reorder the dimensions of NDArrays or define a subregion thereof. A transpose
 *              or slice operation is performed by making a MPSNDArray view of the original. The dimensions to transpose
 *              or slice are given by the descriptor for the new view. If both a transpose and slice operation are defined,
 *              then the slice is performed first and the result of the slice is transposed. Because many MPS kernels can
 *              operate on transposed data at speed, MPS will usually defer doing a physical transpose operation until later,
 *              when it becomes clear that one is actually required. For this reason, conversions to formats that do not
 *              support deferred transposes and slices such as MPSMatrix MPSVector view or using -exportWithCommandBuffer:
 *              toBuffer:offset:rowStrides, may cause substantial new computation to be done and new memory to be allocated.
 *              These should be avoided except when necessary.  As a general rule, transposes that do not involve the 0th
 *              dimension should be able to be handled by nearly everything natively. MPSNDArrayMatrixMultiplication and reductions
 *              can handle 0th dimension transposes. Other filters may insert a physical repacking operation. If you wish
 *              to force a physical repacking use MPSAliasingStrategyShallNotAlias. To avoid confusion with aliased NDArrays
 *              the parent property is provided.  MPSNDArrays that alias share a common ancestor.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArray : NSObject

/*!     Get a well known <MPSNDArrayAllocator> that makes standard MTLBuffers */
+(nonnull id <MPSNDArrayAllocator>) defaultAllocator;

/*! @abstract   A used specified string to help identify the array during debugging.
 *  @discussion May be externally visible to tools like Instruments */
@property (copy, atomic, nullable)  NSString *label;

/*! @abstract  The type of data stored by each element in the array */
@property (readonly, nonatomic)  MPSDataType dataType;

/*! @abstract  The size of one element in the MPSNDArray */
@property (readonly, nonatomic)  size_t dataTypeSize;

/*! @abstract  Number of dimensions in the NDArray */
@property (readonly, nonatomic)  NSUInteger numberOfDimensions;

/*! @abstract    The number of elements in the dimension at dimensionIndex
 *  @discussion     The dimension length is at least as large as the existing
 *                  slice length.  Views of this MPSNDArray may have differing
 *                  dimension lengths.
 */
-(NSUInteger)  lengthOfDimension: (NSUInteger)dimensionIndex;

/*! @property device
 *  @abstract The device on which the MSPNDArray may be used */
@property (readonly, retain, nonatomic, nonnull)  id <MTLDevice>  device;


/*! @abstract  Create a MPSNDArrayDescriptor that describes this MPSNDArray
 *  @discussion The descriptor will describe the shape of the MPSNDArray
 *              after all deferred slicing and transposes have completed.
 *              A new descriptor is created each time to allow for
 *              further customization of the descriptor by the application.
 *  @return     A new autoreleased MPSNDArrayDescriptor that matches the
 *              shape of the MPSNDArray, suitable for introduction of slice,
 *              cast and transpose operations. */
-(MPSNDArrayDescriptor * __nonnull) descriptor;


/* @abstract Please use -initWithDevice:descriptor: instead */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*! @abstract   Initialize an MPSNDArrayDescriptor object on a device
 *              for given dimension sizes in descriptor.
 *
 *   @param      device          The device on which the data type will be created.
 *
 *   @param      descriptor      The MPSNDArrayDescriptor used for initializing the the NDArray
 *
 *   @return     A valid MPSNDArray object or nil, if failure. */
-(nonnull instancetype) initWithDevice:(id<MTLDevice> _Nonnull) device
                            descriptor:(MPSNDArrayDescriptor * _Nonnull) descriptor NS_DESIGNATED_INITIALIZER;

/*! @abstract   Create a 1-Dimensional length=1 NDArray to hold a scalar    */
-(nonnull instancetype) initWithDevice:(id<MTLDevice> _Nonnull) device
                                scalar:(double) value;

/*! @abstract       Get the number of bytes used to allocate underyling MTLResources
 *  @discussion     This is the size of the backing store of underlying MTLResources.
 *                  It does not include all storage used by the object, for example
 *                  the storage used to hold the MPSNDArray instantiation and MTLBuffer
 *                  is not included. It only measures the size of the allocation used
 *                  to hold the MPSNDArray data in the MTLBuffer. This value is subject to
 *                  change between different devices and operating systems.
 *
 *                  Except when -initWithBuffer:descriptor: is used, most MPSNDArrays are allocated
 *                  initiallly without a backing store. The backing store is allocated lazily when
 *                  it is needed, typically when the MPSNDArray is written to the first time.
 *                  Consequently, in most cases, it should be inexpensive to make
 *                  a MPSImage to see how much memory it will need, and release it
 *                  if it is too large.
 */
-(NSUInteger)  resourceSize;

/*! @abstract   Make a new representation of a MPSNDArray with a slice, transpose or other change in property
 *  @discussion If possible, the views will merely record the slice or transpose without performing the
 *              operation. Many MPSKernels are able to operate on subregions of a MPSNDArray or operate on transposed
 *              data, so making a new copy of the data for these operations would be wasteful.  A copy may be forced by
 *              a change in dataType, rowBytes, or when using a view with a MPSKernel that does not support
 *              the deferred operation. To force an operation to occur immediately, use MPSAliasingStrategyShallNotAlias
 *              Otherwise, it is likely that the new MPSNDArray will share a MTLBuffer with the parent and alias
 *              its memory.
 *  @param      cmdBuf      The command buffer on which to perform physical copies if any are required
 *  @param      descriptor  A MPSNDArrayDescriptor describing the shape of the new view of the data
 *  @param      aliasing    A aliasing strategy to direct MPS how to respond to cases when aliasing can or can not
 *                          be performed.
 *  @return     A new MPSNDArray, if it is possible to make one. Otherwise nil is returned. The MPSNDArray is autoreleased. */
-(MPSNDArray * __nullable)     arrayViewWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                               descriptor: (MPSNDArrayDescriptor * _Nonnull) descriptor
                                                 aliasing: (MPSAliasingStrategy) aliasing;

/*! @abstract   The parent MPSNDArray that this object aliases
 *  @discussion If the MPSNDArray was createrd as a array view of another MPSNDArray object, and aliases content
 *              in the same MTLBuffer, the original MPSNDArray will be retained as the parent here. Two MPSNDArrays
 *              alias if they share a common ancestor. Note that the parent may itself have a parent, and so forth. */
@property (readonly, retain, nonatomic, nullable)  MPSNDArray *  parent;


/*! @abstract   Do a GPU side copy of the contents of a MPSNDArray to a MTLBuffer
 *  @discussion To do a transpose or slice as part of the operation, make a MPSNDArray view first that encodes that operation.
 *  @param      cmdBuf      The command buffer on which to encode the operation
 *  @param      buffer      The destination to overwrite
 *  @param      destinationDataType The destination data type.
 *  @param      offset      The byte offset to where the {0,0,0...}th element will be written
 *  @param      rowStrides  An optional array of (numberOfDimensions-1) byte counts which describe
 *                          the byte offset from position 0 of the respective dimension to position 1.  */
-(void) exportDataWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                           toBuffer: (__nonnull id <MTLBuffer>) buffer
                destinationDataType: (MPSDataType) destinationDataType
                             offset: (NSUInteger) offset
                         rowStrides: (NSInteger * __nullable) rowStrides;

/*! @abstract   Do a GPU side copy of the contents of a MTLBuffer into a MPSNDArray
 *  @discussion Copy data from provided buffer to the NDArray. Implicit transposes and slicing shall be honored.
 *  @param      cmdBuf      The command buffer on which to encode the operation
 *  @param      buffer      The destination to read from
 *  @param      sourceDataType  The source data type.
 *  @param      offset      The byte offset in the buffer from where the {0,0,0...}th element is to be read.
 *  @param      rowStrides  An optional array of (numberOfDimensions-1) byte counts which describe
 *                          the byte offset from position 0 of the respective dimension to position 1.  */
-(void) importDataWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                         fromBuffer: (__nonnull id <MTLBuffer>) buffer
                     sourceDataType: (MPSDataType) sourceDataType
                             offset: (NSUInteger) offset
                         rowStrides: (NSInteger * __nullable) rowStrides;



/*! @abstract   Do a GPU side copy of the contents of a MPSNDArray to a MPSImageBatch.
 *  @discussion To do a transpose or slice as part of the operation, make a MPSNDArray view first that encodes that operation.
 *              The shape of the array must be [ C, W, H, N, 1, 1, ... ], where C is dimension 0 (normally the fastest running index)
 *              and is mapped to feature channels in the destination image, W and H are mapped to x and y coordinates in the destination
 *              image and N is mapped to the image batch index. You can use arrayViewWithCommandBuffer: to transpose, slice and reshape
 *              the source array to layout the data in the desired way for the image(s).
 *
 *  @param      cmdBuf      The command buffer on which to encode the operation/
 *  @param      images      The destination images. NOTE: you can use [images subarrayWithRange:...] to get a sub-batch of images.
 *  @param      offset      The offset to the image where to write - the size of the operation is defined by the source array.
 *                          Note: offset.featureChannel must be multiple of four, otherwise results are undefined.
 */

-(void) exportDataWithCommandBuffer: (id <MTLCommandBuffer> _Nonnull) cmdBuf
                           toImages: (MPSImageBatch * _Nonnull) images
                             offset: (MPSImageCoordinate) offset;

/*! @abstract   Do a GPU side copy of the contents of a MPSImageBatch into a MPSNDArray.
 *  @discussion This reverses exportDataWithCommandBuffer:toImages: function.
 *  @param      cmdBuf      The command buffer on which to encode the operation.
 *  @param      images      The source images. NOTE: you can use [images subarrayWithRange:...] to get a sub-batch of images.
 *  @param      offset      The offset to the image where to read - the size of the operation is defined by the destination array.
 */
-(void) importDataWithCommandBuffer: (id <MTLCommandBuffer> _Nonnull) cmdBuf
                         fromImages: (MPSImageBatch * _Nonnull) images
                             offset: (MPSImageCoordinate) offset;



/*! @abstract       Copy bytes from MPSNDArray into buffer
 *  @discussion     The dimensionality and size of the copy region is given by the size of the MPSNDArray
 *                  For subregions, use a MPSNDArray view.
 *  @param          buffer                  A pointer to memory where to write the data
 *  @param          strideBytesPerDimension An optional array of numberOfDimensions sizes, which gives the distance
 *                                          in bytes from one element to the next in that dimension in buffer. The first value
 *                                          is typically dataTypeSize. The next is a row bytes. The next is 2d matrix bytes,
 *                                          and so forth.  If the value is nil, these are calculated for you assuming that the
 *                                          data is packed without additional space in between elements, rows, etc.
 *                                          0 and negative values are permitted. */
-(void) readBytes: (void*__nonnull) buffer
      strideBytes: (NSInteger*__nullable) strideBytesPerDimension;


/*! @abstract       Copy bytes from a buffer into the MPSNDArray
 *  @discussion     The dimensionality and size of the copy region is given by the size of the MPSNDArray
 *                  For subregions, use a MPSNDArray view.
 *  @param          buffer                  A pointer to memory where to read the data
 *  @param          strideBytesPerDimension An optional array of numberOfDimensions sizes, which gives the distance
 *                                          in bytes from one element to the next in that dimension in buffer. The first value
 *                                          is typically dataTypeSize. The next is a row bytes. The next is 2d matrix bytes,
 *                                          and so forth.  If strideBytesPerDimension is nil, these are calculated for you assuming that the
 *                                          data is packed without additional space in between elements, rows, etc.
 *                                          0 and negative values are permitted. */
-(void) writeBytes: (void*__nonnull) buffer
       strideBytes: (NSInteger*__nullable) strideBytesPerDimension;


/*! @abstract   Use a blit encoder if a discrete device to update CPU contents of underlying buffer with latest GPU value
 *  @param      commandBuffer     The commandBuffer on which we transfer the contents. */
-(void) synchronizeOnCommandBuffer:(id<MTLCommandBuffer> _Nonnull) commandBuffer;

@end

/*! @class MPSTemporaryNDArray
 *  @abstract   A MPSNDArray that uses command buffer specific memory to store the array data
 *  @discussion Temporary memory is command buffer specific memory, and is useful for MPSNDArray allocations
 *              with limited lifetime within a single command buffer. Typically, most MPSNDArrays that
 *              are not read or written to by the CPU or needed in other command buffers should be
 *              MPSTemporaryNDArray. This will greatly reduce time spent allocating new memory, reduce memory usage
 *              and help improve memory locality. */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSTemporaryNDArray : MPSNDArray

/*!     Get a well known <MPSNDArrayAllocator> that makes temporary MTLBuffers */
+(nonnull id <MPSNDArrayAllocator>) defaultAllocator;

/*!
 *  @abstract   Initialize a MPSTemporaryNDArray for use on a MTLCommandBuffer
 *  @param      commandBuffer       The MTLCommandBuffer on which the MPSTemporaryNDArray will be exclusively used
 *  @param      descriptor          A valid MPSNDArrayDescriptor describing the MPSNDArray format to create
 *  @return     A valid MPSTemporaryNDArray.  The object is not managed by a NSAutoreleasePool. The object will be
 *              released when the command buffer is committed. The underlying buffer will become invalid before
 *              this time due to the action of the readCount property.  Please read and understand the use of
 *              the readCount property before using this object. */
+(nonnull instancetype) temporaryNDArrayWithCommandBuffer: (id <MTLCommandBuffer> _Nonnull) commandBuffer
                                               descriptor: (MPSNDArrayDescriptor* _Nonnull) descriptor;


/*! @abstract  Please use temporaryNDArrayWithCommandBuffer:descriptor: instead */
-(nonnull instancetype) initWithDevice:(id<MTLDevice> _Nonnull) device
                            descriptor:(MPSNDArrayDescriptor * _Nonnull) descriptor NS_UNAVAILABLE;


/*!
 *  @abstract       The number of times a temporary MPSNDArray may be read by a MPSNDArray... kernel
 *                  before its contents become undefined.
 *
 *  @discussion     MPSTemporaryNDArrays must release their underlying buffers for reuse
 *                  immediately after last use. So as to facilitate *prompt* convenient
 *                  memory recycling, each time a MPSTemporaryNDArray is read by a
 *                  MPSNDArray... -encode... method, its readCount is automatically
 *                  decremented. When the readCount reaches 0, the underlying buffer is
 *                  automatically made available for reuse to MPS for its own needs and for
 *                  other MPSTemporaryNDArrays prior to return from the -encode.. function.
 *                  The contents of the buffer become undefined at this time.
 *
 *                  By default, the readCount is initialized to 1, indicating a MPSNDArray that
 *                  may be overwritten any number of times, but read only once.
 *
 *                  You may change the readCount as desired to allow MPSNDArrayKernels to read
 *                  the MPSTemporaryNDArray additional times. However, it is an error to change
 *                  the readCount once it is zero. It is an error to read or write to a
 *                  MPSTemporaryNDArray with a zero readCount. You may set the readCount to 0
 *                  yourself to cause the underlying buffer to be returned to MPS. Writing
 *                  to a MPSTemporaryNDArray does not adjust the readCount.
 *
 *                  The Metal API Validation layer will assert if a MPSTemporaryNDArray is
 *                  deallocated with non-zero readCount to help identify cases when resources
 *                  are not returned promptly.
 */
@property (readwrite, nonatomic)  NSUInteger  readCount;

@end

#endif /* MPSNDArray_h */
