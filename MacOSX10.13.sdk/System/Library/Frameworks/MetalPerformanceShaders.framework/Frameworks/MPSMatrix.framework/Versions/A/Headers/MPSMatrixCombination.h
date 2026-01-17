//
//  MPSMatrixCombination.h
//  MPSMatrix
//
//  Created by Ian Ollmann on 6/5/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSMatrixCombination_h
#define MPSMatrixCombination_h


#ifndef __METAL_VERSION__
#   include <stdint.h>
#endif

/*!
 *  @struct     MPSMatrixCopyOffsets
 *  @memberof   MPSMatrixCopy
 *  @abstract   A description of each copy operations
 */

typedef struct
{
    uint32_t    sourceRowOffset;        /**< offset to start of source region to read in rows */
    uint32_t    sourceColumnOffset;     /**< offset to start of source region to read in columns */
    uint32_t    destinationRowOffset;   /**< offset to start of destination region to read in rows */
    uint32_t    destinationColumnOffset;/**< offset to start of destination region to read in columns */
} MPSMatrixCopyOffsets;

// Hide the rest of the header from metal shading language
#ifndef __METAL_VERSION__

#import <MPSMatrix/MPSMatrixTypes.h>

#ifdef __cplusplus
extern "C" {
#endif


/*! @abstract   A list of copy operations
 *  @discussion The MPSMatrixCopy filter can do multiple copy operations.  For RNN filters, these
 *              copies are often small, and are more efficient when grouped together.
 *              The MPSMatriceCopyDescriptor provides a container to list the operations.
 *              The operations occur in any order, and may not alias.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSMatrixCopyDescriptor : NSObject
/*! @abstract   convenience allocator for single copies */
+(nonnull instancetype) descriptorWithSourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
                                 destinationMatrix: (MPSMatrix * __nonnull) destinationMatrix
                                           offsets: (MPSMatrixCopyOffsets) offsets
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );

/*! @abstract       initialize a MPSMatrixCopyDescriptor with default values.
 *  @discussion     Use -setCopyOperationAtIndex:sourceMatrix:destinationMatrix:copyOffsets
 *                  to initialize. All indices must be initialized before use.
 *  @param          device    The device on which the copy will be performed
 *  @param          count     The number of copy operations the object will encode
 *  @return     A MPSMatrixCopyDescriptor. It still needs to be initialized with
 *              -setCopyOperationAtIndex:sourceMatrix:destinationMatrix:copyOffsets */
-(nonnull instancetype)     initWithDevice: (nonnull id <MTLDevice>) device
                                     count: (NSUInteger) count
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );

/*! @abstract    Initialize a MPSMatrixCopyDescriptor using offsets generated on the CPU
 *  @discussion  This is for one at a time intialization of the copy operations
 *  @param  index               The index of the copy operation
 *  @param  sourceMatrix        The source matrix for this copy operation
 *  @param  destinationMatrix   The destination matrix for this copy operation
 *  @param  offsets             The offsets to use for the copy operation */
-(void) setCopyOperationAtIndex: (NSUInteger) index
                   sourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
              destinationMatrix: (MPSMatrix * __nonnull) destinationMatrix
                        offsets: (MPSMatrixCopyOffsets) offsets
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );


/*! @abstract       Initialize a MPSMatrixCopyDescriptor using offsets generated on the GPU
 *  @discussion     Use this method when the offsets needed are coming from GPU based computation.
 *  @param          sourceMatrices      A list of matrices from which the matrix data is read
 *  @param          destinationMatrices A list of matrices to which to write the data. The count
 *                                      must match the number of source matrices.
 *  @param          offsets         A MPSVector of type MPSDataTypeUInt32 containing the list of
 *                                  offsets, stored as a packed array of MPSMatrixCopyOffsets.
 *  @param          byteOffset      A byte offset into the offsets vector where the data starts.
 *                                  This value must be a multiple of 16.
 *  @result         A valid MPSMatrixCopyDescriptor to represent the list of copy operations
 */
-(nonnull instancetype) initWithSourceMatrices: (NSArray<MPSMatrix*>*__nonnull) sourceMatrices
                           destinationMatrices: (NSArray<MPSMatrix*>*__nonnull) destinationMatrices
                                  offsetVector: (MPSVector * __nullable) offsets
                                        offset: (NSUInteger) byteOffset
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );


-(nonnull instancetype) init    NS_UNAVAILABLE;

@end

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixCopy : MPSKernel

/*
 * Use initWithDevice:rnnDescriptor instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract   Initialize a copy operator
 *  @param      copyRows        The number of rows to copy for each copy operation
 *  @param      copyColumns     The number of matrix columns to copy in each copy operation
 *  @param      sourcesAreTransposed       If YES, the sources are in row major storage order
 *  @param      destinationsAreTransposed  If YES, the destinations are in row major storage order
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                              copyRows: (NSUInteger) copyRows
                           copyColumns: (NSUInteger) copyColumns
                  sourcesAreTransposed: (BOOL) sourcesAreTransposed
             destinationsAreTransposed: (BOOL) destinationsAreTransposed
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );

/*! @abstract   The number of rows to copy for each copy operation */
@property (nonatomic, readonly) NSUInteger copyRows;

/*! @abstract   The number of columns to copy for each copy operation */
@property (nonatomic, readonly) NSUInteger copyColumns;

/*! @abstract   If YES, the sources are in row major storage order */
@property (nonatomic, readonly) BOOL sourcesAreTransposed;

/*! @abstract   If YES, the destinations are in row major storage order */
@property (nonatomic, readonly) BOOL destinationsAreTransposed;

/*! @abstract   Encode the copy operations to the command buffer */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) cmdBuf
               copyDescriptor: (MPSMatrixCopyDescriptor*__nonnull) copyDescriptor
MPS_SWIFT_NAME( encode(commandBuffer:copyDescriptor:));

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixLookUpAndCopy
 *  @param      device      The MTLDevice on which to make the MPSMatrixLookUpAndCopy
 *  @return     A new MPSMatrixLookUpAndCopy object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

@end


#ifdef __cplusplus
}
#endif

#endif // __METAL_VERSION__

#endif /* MPSMatrixCombination_h */
