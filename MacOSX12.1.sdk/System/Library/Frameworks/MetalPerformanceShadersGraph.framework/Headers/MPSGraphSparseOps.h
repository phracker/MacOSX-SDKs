//
//  MPSGraphSparseOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/30/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphSparseOps_h
#define MPSGraphSparseOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @typedef    MPSGraphSparseStorageType
 *  @abstract   Sparse Storage options in graph
 *
 *  @constant   MPSGraphSparseStorageCOO                                  COO Storage
 *  @constant   MPSGraphSparseStorageCSC                                   CSC Storage
 *  @constant   MPSGraphSparseStorageCSR                                   CSR Storage
 */
typedef NS_ENUM(uint64_t, MPSGraphSparseStorageType) {
    MPSGraphSparseStorageCOO MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0)) MPS_SWIFT_NAME(COO) = 0,
    MPSGraphSparseStorageCSC MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0)) = 1L,
    MPSGraphSparseStorageCSR MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0)) = 2L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphCreateSparseOpDescriptor : NSObject <NSCopying>

@property(readwrite, nonatomic) MPSGraphSparseStorageType sparseStorageType;
@property(readwrite, nonatomic) MPSDataType dataType;

+ (nullable instancetype)descriptorWithStorageType:(MPSGraphSparseStorageType)sparseStorageType
                                          dataType:(MPSDataType)dataType
    MPS_SWIFT_NAME(sparseDescriptor(descriptorWithStorageType:dataType:));

@end

@interface MPSGraph (MPSGraphSparseOps)

/*!
 *  @abstract   Create sparseTensor op and return the result tensor
 *
 *
 *  @param      sparseStorageType       sparseStorageType
 *  @param      inputTensorArray         array of input tensors as [sparseVals, indexTensor0, indexTensor1]
 *  @param      shape                                  shape of sparse tensor
 *  @param      dataType                           dataType of sparse tensor
 *  @param      name                                    name for the operation
 *
 *  @discussion sparseVals corresponds to non zero values in matrix.
 *              indexTensor0 and indexTensor1 are indices used for indexing into sparse data structure
 *              For COO, indexTensor0 is x index and indexTensor1 is y index
 *              For CSC, indexTensor0 and indexTensor1 correspond to rowIndex and colStarts respectively.
 *              For CSR, indexTensor0 and indexTensor1 correspond to colIndex and rowStarts respectively.
 *  @return     A valid MPSGraphTensor object.
 */
- (MPSGraphTensor *)sparseTensorWithType:(MPSGraphSparseStorageType)sparseStorageType
                                 tensors:(NSArray<MPSGraphTensor *> *)inputTensorArray
                                   shape:(MPSShape *)shape
                                dataType:(MPSDataType)dataType
                                    name:(NSString *_Nullable)name
    MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
    MPS_SWIFT_NAME(sparseTensor(sparseTensorWithType:tensors:shape:dataType:name:));

/*!
 *  @abstract   Create sparseTensor op and return the result tensor
 *
 *
 *  @param      sparseDescriptor         sparseDescriptorType
 *  @param      inputTensorArray         array of input tensors as [sparseVals, indexTensor0, indexTensor1]
 *  @param      shape                                  shape of sparse tensor
 *  @param      name                                    name for the operation
 *
 *  @discussion sparseVals corresponds to non zero values in matrix.
 *              indexTensor0 and indexTensor1 are indices used for indexing into sparse data structure
 *              For COO, indexTensor0 is x index and indexTensor1 is y index
 *              For CSC, indexTensor0 and indexTensor1 correspond to rowIndex and colStarts respectively.
 *              For CSR, indexTensor0 and indexTensor1 correspond to colIndex and rowStarts respectively.
 *  @return     A valid MPSGraphTensor object.
 */
- (MPSGraphTensor *)sparseTensorWithDescriptor:(MPSGraphCreateSparseOpDescriptor *)sparseDescriptor
                                       tensors:(NSArray<MPSGraphTensor *> *)inputTensorArray
                                         shape:(MPSShape *)shape
                                          name:(NSString *_Nullable)name
    MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
    MPS_SWIFT_NAME(sparseTensor(sparseTensorWithDescriptor:tensors:shape:name:));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphSparseOps_h */
