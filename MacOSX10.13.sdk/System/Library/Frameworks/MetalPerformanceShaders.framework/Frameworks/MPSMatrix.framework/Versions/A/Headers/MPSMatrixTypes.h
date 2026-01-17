//
//  MPSMatrixTypes.h
//  MPS
//
//  Created by Ian Ollmann on 8/20/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSMatrixTypes_h
#define MPSMatrixTypes_h

#import <MPSCore/MPSKernel.h>
#import <MPSCore/MPSCoreTypes.h>

#ifdef __cplusplus
extern "C" {
#endif



    
/*!
*  @class      MPSMatrixDescriptor
*
*  @dependency This depends on Metal.framework
*
*  @discussion A MPSMatrixDescriptor describes the sizes, strides, and data type of a
*              an array of 2-dimensional matrices.  All storage is assumed to be in 
*              "matrix-major".  See the description for MPSMatrix for further details.
*/
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSMatrixDescriptor: NSObject

/*! @property   rows
 *  @discussion The number of rows in a matrix.
 */
@property (readwrite, nonatomic) NSUInteger rows;

/*! @property   columns
 *  @discussion The number of columns in a matrix.
 */
@property (readwrite, nonatomic) NSUInteger columns;

/*! @property   matrices
 *  @discussion The number of matrices.
 */
@property (readonly, nonatomic) NSUInteger matrices MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @property   dataType
 *  @discussion The type of the data which makes up the values of the matrix.
 */
@property (readwrite, nonatomic) MPSDataType dataType;

/*! @property   rowBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive rows.  Must be a multiple of the element size.
 */
@property (readwrite, nonatomic) NSUInteger rowBytes;

/*! @property   matrixBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive matrices.  Must be a multiple of rowBytes.
 */
@property (readonly, nonatomic) NSUInteger matrixBytes MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 *  @abstract   Create a MPSMatrixDescriptor with the specified dimensions and data type.
 *
 *  @param      rows                The number of rows of the matrix.
 *
 *  @param      columns             The number of columns of the matrix.
 *
 *  @param      rowBytes            The number of bytes between starting elements of consecutive
 *                                  rows.  Must be a multiple of the element size.
 *
 *  @param      dataType            The type of the data to be stored in the matrix.
 *
 *  @discussion For performance considerations the optimal row stride may not necessarily be equal
 *              to the number of columns in the matrix.  The MPSMatrix class provides a method which
 *              may be used to determine this value, see the rowBytesForColumns API in the MPSMatrix
 *              class.
 *              The number of matrices described is initialized to 1.
 */
+(__nonnull instancetype) matrixDescriptorWithDimensions: (NSUInteger)              rows
                                                 columns: (NSUInteger)              columns
                                                rowBytes: (NSUInteger)              rowBytes
                                                dataType: (MPSDataType)             dataType
MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Use matrixDescriptorWithRows:columns:rowBytes:dataType instead.",
                                      ios(10.0, 11.0), tvos(10.0, 11.0));

+(__nonnull instancetype) matrixDescriptorWithRows: (NSUInteger)              rows
                                           columns: (NSUInteger)              columns
                                          rowBytes: (NSUInteger)              rowBytes
                                          dataType: (MPSDataType)             dataType
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));
/*!
 *  @abstract   Create a MPSMatrixDescriptor with the specified dimensions and data type.
 *
 *  @param      rows                The number of rows of a single matrix.
 *
 *  @param      columns             The number of columns of a single matrix.
 *
 *  @param      matrices            The number of matrices in the MPSMatrix object.
 *
 *  @param      rowBytes            The number of bytes between starting elements of consecutive
 *                                  rows.  Must be a multiple of the element size.
 *
 *  @param      matrixBytes         The number of bytes between starting elements of consecutive
 *                                  matrices.  Must be a multiple of rowBytes.
 *
 *  @param      dataType            The type of the data to be stored in the matrix.
 *
 *  @discussion For performance considerations the optimal row stride may not necessarily be equal
 *              to the number of columns in the matrix.  The MPSMatrix class provides a method which
 *              may be used to determine this value, see the rowBytesForColumns API in the MPSMatrix
 *              class.
 */
+(__nonnull instancetype) matrixDescriptorWithRows: (NSUInteger)              rows
                                           columns: (NSUInteger)              columns
                                          matrices: (NSUInteger)              matrices
                                          rowBytes: (NSUInteger)              rowBytes
                                       matrixBytes: (NSUInteger)              matrixBytes
                                          dataType: (MPSDataType)             dataType
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));
/*!
 *  @abstract   Return the recommended row stride, in bytes, for a given number of
 *              columns.
 *
 *  @param      columns         The number of columns in the matrix for which the recommended
 *                              row stride, in bytes, is to be determined.
 *
 *  @param      dataType        The type of matrix data values.
 *
 *  @discussion To achieve best performance the optimal stride between rows of a matrix is not
 *              necessarily equivalent to the number of columns.  This method returns the row stride, in
 *              bytes, which gives best performance for a given number of columns.  Using this row stride
 *              to construct your array is recommended, but not required (provided that the stride
 *              used is still large enough to allocate a full row of data).
 */
+(size_t) rowBytesFromColumns: (NSUInteger) columns
                     dataType: (MPSDataType) dataType
MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Use rowBytesForColumns:dataType instead.",
                                      ios(10.0, 11.0), tvos(10.0, 11.0));

+(size_t) rowBytesForColumns:   (NSUInteger) columns
                    dataType:   (MPSDataType) dataType
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));
@end // MPSMatrixDescriptor
    
/*!
*  @class      MPSVectorDescriptor
*
*  @dependency This depends on Metal.framework
*
*  @discussion A MPSVectorDescriptor describes the length and data type of a
*              an array of 1-dimensional vectors.  All vectors are stored as
*              contiguous arrays of data.
*/
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSVectorDescriptor: NSObject

/*! @property   length
 *  @discussion The number of elements in the vector.
 */
@property (readwrite, nonatomic) NSUInteger length;

/*! @property   vectors
 *  @discussion The number of vectors.
 */
@property (readonly, nonatomic) NSUInteger vectors;

/*! @property   dataType
 *  @discussion The type of the data which makes up the values of the vector.
 */
@property (readwrite, nonatomic) MPSDataType dataType;

/*! @property   vectorBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive vectors.  Must be a multiple of the element size
 */
@property (readonly, nonatomic) NSUInteger vectorBytes;

/*!
 *  @abstract   Create a MPSVectorDescriptor with the specified length and data type.
 *
 *  @param      length              The number of elements in a single vector.
 *
 *  @param      dataType            The type of the data to be stored in the vector.
 *
 *  @discussion Use this function for creating a descriptor of a MPSVector object
 *              containing a single vector.
 */
+(__nonnull instancetype) vectorDescriptorWithLength: (NSUInteger)              length
                                            dataType: (MPSDataType)             dataType;

/*!
 *  @abstract   Create a MPSVectorDescriptor with the specified length and data type.
 *
 *  @param      length              The number of elements in a single vector.
 *
 *  @param      vectors             The number of vectors in the MPSVector object.
 *
 *  @param      vectorBytes         The number of bytes between starting elements of consecutive
 *                                  vectors.
 *
 *  @param      dataType            The type of the data to be stored in the vector.
 *
 *  @discussion For performance considerations the optimal stride between vectors may not necessarily be equal
 *              to the vector length.  The MPSVectorDescriptor class provides a method which
 *              may be used to determine this value, see the vectorBytesForLength API.
 */
+(__nonnull instancetype) vectorDescriptorWithLength: (NSUInteger)              length
                                             vectors: (NSUInteger)              vectors
                                         vectorBytes: (NSUInteger)              vectorBytes
                                            dataType: (MPSDataType)             dataType;

/*!
 *  @abstract   Return the recommended stride, in bytes, to be used for an array
 *              of vectors of a given length.
 *
 *  @param      length          The number of elements in a single vector.
 *
 *  @param      dataType        The type of vector data values.
 *
 *  @discussion To achieve best performance the optimal stride between vectors within an array of
 *              vectors is not necessarily equivalent to the number of elements per vector.  This method 
 *              returns the stride, in bytes, which gives best performance for a given vector length.  
 *              Using this stride to construct your array is recommended, but not required (provided that
 *              the stride used is still large enough to allocate a full vector of data).
 */
+(size_t) vectorBytesForLength:   (NSUInteger) length
                      dataType:   (MPSDataType) dataType;
@end // MPSVectorDescriptor
    
/*!
*  @class      MPSMatrix
*
*  @dependency This depends on Metal.framework
*
*  @discussion A MPSMatrix object describes a set of 2-dimensional arrays of data and provides storage
*              for its values.  MPSMatrix objects serve as inputs and outputs of MPSMatrixKernel
*              objects.
*
*              Implementation note:
*              A MPSMatrix object maintains its internal storage using a MTLBuffer object and thus
*              the same rules for maintaining coherency of a MTLBuffer's data between CPU memory and GPU
*              memory apply to a MPSMatrix.  An MPSMatrix object's data refers to an array of matrices.
*              Data is assumed to be ordered by matrix first, followed by row, followed by column.
*
*              For example, index [i,j] of the k'th matrix of an MPSMatrix is located at byte offset:
*                       k * matrixBytes + i * rowBytes + j * sizeof(dataType)
*               
*               Where matrixBytes is a multiple of rowBytes at least equal to rows * rowBytes.
*/
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSMatrix: NSObject

/*! @property   device
 *  @discussion The device on which the MPSMatrix will be used.
 */
@property (readonly, retain, nonatomic, nonnull) id<MTLDevice> device;

/*! @property   rows
 *  @discussion The number of rows in a matrix in the MPSMatrix.
 */
@property (readonly, nonatomic) NSUInteger rows;

/*! @property   columns
 *  @discussion The number of columns in a matrix in the MPSMatrix.
 */
@property (readonly, nonatomic) NSUInteger columns;

/*! @property   matrices
 *  @discussion The number of matrices in the MPSMatrix.
 */
@property (readonly, nonatomic) NSUInteger matrices MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @property   dataType
 *  @discussion The type of the MPSMatrix data.
 */
@property (readonly, nonatomic) MPSDataType dataType;

/*! @property   rowBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive rows.
 */
@property (readonly, nonatomic) NSUInteger rowBytes;

/*! @property   matrixBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive matrices.
 */
@property (readonly, nonatomic) NSUInteger matrixBytes MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @property   data
 *  @discussion An MTLBuffer to store the data.
 */
@property (readonly, nonnull, nonatomic) id<MTLBuffer> data;

/*!
 *  @abstract   Initialize a MPSMatrix object with a MTLBuffer.
 *
 *  @param      buffer          The MTLBuffer object which contains the data to use for the
 *                              MPSMatrix. May not be NULL.
 *
 *  @param      descriptor      The MPSMatrixDescriptor. May not be NULL.
 *
 *  @return     A valid MPSMatrix object or nil, if failure.
 *
 *  @discussion This function returns a MPSMatrix object which uses the supplied MTLBuffer.  The
 *              dimensions and stride of the matrix are specified by the MPSMatrixDescriptor object.
 *
 *              The provided MTLBuffer must have enough storage to hold
 *
 *                  (descriptor.matrices-1) * descriptor.matrixBytes +
 *                  (descriptor.rows-1) * descriptor.rowBytes +
 *                   descriptor.columns * (element size) bytes.
 *
 */
-(nonnull instancetype) initWithBuffer: (nonnull id<MTLBuffer>) buffer
                            descriptor: (nonnull MPSMatrixDescriptor*) descriptor;

/*
 * Use one of the above initialization methods instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

@end // MPSMatrix
    
/*!
*  @class      MPSVector
*
*  @dependency This depends on Metal.framework
*
*  @discussion A MPSVector object describes a 1-dimensional array of data and provides storage
*              for its values.  Some MPSMatrixKernel objects operate on MPSVector objects
*              for convenience.
*/
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSVector: NSObject

/*! @property   device
 *  @discussion The device on which the MPSVector will be used.
 */
@property (readonly, retain, nonatomic, nonnull) id<MTLDevice> device;

/*! @property   length
 *  @discussion The number of elements in the vector.
 */
@property (readonly, nonatomic) NSUInteger length;

/*! @property   vectors
 *  @discussion The number of vectors in the MPSVector.
 */
@property (readonly, nonatomic) NSUInteger vectors;

/*! @property   dataType
 *  @discussion The type of the MPSVector data.
 */
@property (readonly, nonatomic) MPSDataType dataType;

/*! @property   vectorBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive vectors.
 */
@property (readonly, nonatomic) NSUInteger vectorBytes;

/*! @property   data
 *  @discussion An MTLBuffer to store the data.
 */
@property (readonly, nonnull, nonatomic) id<MTLBuffer> data;

/*!
 *  @abstract   Initialize a MPSVector object with a MTLBuffer.
 *
 *  @param      buffer          The MTLBuffer object which contains the data to use for the
 *                              MPSVector. May not be NULL.
 *
 *  @param      descriptor      The MPSVectorDescriptor. May not be NULL.
 *
 *  @return     A valid MPSVector object or nil, if failure.
 *
 *  @discussion This function returns a MPSVector object which uses the supplied MTLBuffer.  The
 *              length, number of vectors, and stride between vectors are specified by the
 *              MPSVectorDescriptor object.
 *
 *              The provided MTLBuffer must have enough storage to hold
 *
 *                  (descriptor.vectors-1) * descriptor.vectorBytes +
 *                   descriptor.length * (element size) bytes.
 *
 */
-(nonnull instancetype) initWithBuffer: (nonnull id<MTLBuffer>) buffer
                            descriptor: (nonnull MPSVectorDescriptor*) descriptor;

/*
 * Use the above initialization methods instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

@end // MPSVector
    
/*! @abstract A MPSMatrix allocated on GPU private memory. 
 *  @discussion It may alias one or more other MPSTemporaryMatrices. Undesired data destruction
 *              due to aliasing is avoided using the readCount property.
 */    
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSTemporaryMatrix : MPSMatrix

/*!
 *  @abstract   Initialize a MPSTemporaryMatrix for use on a MTLCommandBuffer
 *  @param      commandBuffer       The MTLCommandBuffer on which the MPSTemporaryMatrix will be exclusively used
 *  @param      matrixDescriptor    A valid MPSMatrixDescriptor describing the MPSMatrix format to create
 *  @return     A valid MPSTemporaryMatrix.  The object is not managed by a NSAutoreleasePool. The object will be 
 *              released when the command buffer is committed. The underlying buffer will become invalid before 
 *              this time due to the action of the readCount property.  Please read and understand the use of 
 *              the readCount property before using this object.
 */
+(nonnull instancetype) temporaryMatrixWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                        matrixDescriptor: (nonnull MPSMatrixDescriptor*) matrixDescriptor;

/*!
 *  @abstract       Help MPS decide which allocations to make ahead of time
 *  @discussion     The buffer cache that underlies the MPSTemporaryMatrix can automatically allocate new storage as
 *                  needed as you create new temporary matrices.  However, sometimes a more global view of what you
 *                  plan to make is useful for maximizing memory reuse to get the most efficient operation.
 *                  This class method hints to the cache what the list of matrices will be.
 *
 *                  It is never necessary to call this method. It is purely a performance and memory optimization.
 *
 *  @param commandBuffer        The command buffer on which the MPSTemporaryMatrix will be used
 *  @param descriptorList       A NSArray of MPSMatrixDescriptor, indicating matrices that will be created
 */
+(void) prefetchStorageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                    matrixDescriptorList: (NSArray <MPSMatrixDescriptor*> * __nonnull) descriptorList;

/* MPS can not make a temporary matrix with a outside buffer. Please use the above methods. */
/*! @abstract *** unavailable */
-(nonnull instancetype) initWithBuffer: (nonnull id<MTLBuffer>) buffer
                            descriptor: (nonnull MPSMatrixDescriptor*) descriptor NS_UNAVAILABLE;

/*!
 *  @abstract       The number of times a temporary matrix may be read by a MPSMatrix... kernel
 *                  before its contents become undefined.
 *
 *  @discussion     MPSTemporaryMatrices must release their underlying buffers for reuse
 *                  immediately after last use. So as to facilitate *prompt* convenient
 *                  memory recycling, each time a MPSTemporaryMatrix is read by a
 *                  MPSMatrix... -encode... method, its readCount is automatically
 *                  decremented. When the readCount reaches 0, the underlying buffer is
 *                  automatically made available for reuse to MPS for its own needs and for
 *                  other MPSTemporaryMatrices prior to return from the -encode.. function.
 *                  The contents of the buffer become undefined at this time.
 *
 *                  By default, the readCount is initialized to 1, indicating a matrix that
 *                  may be overwritten any number of times, but read only once.
 *
 *                  You may change the readCount as desired to allow MPSMatrixKernels to read
 *                  the MPSTemporaryMatrix additional times. However, it is an error to change
 *                  the readCount once it is zero. It is an error to read or write to a
 *                  MPSTemporaryMatrix with a zero readCount. You may set the readCount to 0
 *                  yourself to cause the underlying buffer to be returned to MPS. Writing
 *                  to a MPSTemporaryMatrix does not adjust the readCount.
 *
 *                  The Metal API Validation layer will assert if a MPSTemporaryMatrix is
 *                  deallocated with non-zero readCount to help identify cases when resources
 *                  are not returned promptly.
 */
@property (readwrite, nonatomic)  NSUInteger  readCount;

@end 

/*!
 *  @class      MPSMatrixUnaryKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSMatrixUnaryKernel consumes one MPSMatrix and produces one MPSMatrix.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixUnaryKernel : MPSKernel

/*! @property   sourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the source matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin sourceMatrixOrigin;

/*! @property   resultMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the result matrix, at which to
 *              start writing results.  This property is modifiable and defaults
 *              to [0, 0] at initialization time.  If a different origin is desired
 *              then this should be modified prior to encoding the kernel.  The z
 *              value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin resultMatrixOrigin;

/*! @property   batchStart
 *
 *  @discussion The index of the first matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.  If
 *              batch processing should begin at a different matrix this value
 *              should be modified prior to encoding the kernel.
 */
@property (readwrite, nonatomic) NSUInteger batchStart;

/*! @property   batchSize
 *
 *  @discussion The number of matrices in the batch to process.  This property
 *              is modifiable and by default allows all matrices available at
 *              encoding time to be processed.  If a single matrix should be
 *              processed set this value to 1.
 */
@property (readwrite, nonatomic) NSUInteger batchSize;

@end // MPSMatrixUnaryKernel

/*!
 *  @class      MPSMatrixBinaryKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSMatrixBinaryKernel consumes two MPSMatrix objects and produces
 *              one MPSMatrix object.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixBinaryKernel : MPSKernel
/*! @property   primarySourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the primary source matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin primarySourceMatrixOrigin;

/*! @property   secondarySourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the secondary source matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin secondarySourceMatrixOrigin;

/*! @property   resultMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the result matrix, at which to
 *              start writing results.  This property is modifiable and defaults
 *              to [0, 0] at initialization time.  If a different origin is desired
 *              then this should be modified prior to encoding the kernel.  The z
 *              value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin resultMatrixOrigin;

/*! @property   batchStart
 *
 *  @discussion The index of the first matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.  If
 *              batch processing should begin at a different matrix this value
 *              should be modified prior to encoding the kernel.
 */
@property (readwrite, nonatomic) NSUInteger batchStart;

/*! @property   batchSize
 *
 *  @discussion The number of matrices in the batch to process.  This property
 *              is modifiable and by default allows all matrices available at
 *              encoding time to be processed.  If a single matrix should be
 *              processed set this value to 1.
 */
@property (readwrite, nonatomic) NSUInteger batchSize;
@end // MPSMatrixBinaryKernel

#ifdef __cplusplus
}   // extern "C"
#endif

#endif /* MPSMatrixTypes_h */
