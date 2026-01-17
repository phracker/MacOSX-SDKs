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

/// The sparse storage options in the Metal Performance Shaders Graph framework.
typedef NS_ENUM(uint64_t, MPSGraphSparseStorageType) {
    /// COO Storage
    MPSGraphSparseStorageCOO MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0)) MPS_SWIFT_NAME(COO) = 0,
    /// CSC Storage
    MPSGraphSparseStorageCSC MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0)) = 1L,
    /// CSR Storage
    MPSGraphSparseStorageCSR MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0)) = 2L,
};

/// A class that describes the properties of a create sparse operation.
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphCreateSparseOpDescriptor : MPSGraphObject <NSCopying>

/// Defines the storage format of the sparse tensor.
@property(readwrite, nonatomic) MPSGraphSparseStorageType sparseStorageType;

/// Defines the datatype of the sparse tensor.
@property(readwrite, nonatomic) MPSDataType dataType;

/// Creates a descriptor for a sparse tensor.
///
/// - Parameters:
///   - sparseStorageType: A sparseStorageType.
///   - dataType: A dataType of the sparse tensor.
/// - Returns: The descriptor.
+ (nullable instancetype)descriptorWithStorageType:(MPSGraphSparseStorageType)sparseStorageType
                                          dataType:(MPSDataType)dataType
    MPS_SWIFT_NAME(sparseDescriptor(descriptorWithStorageType:dataType:));

@end

@interface MPSGraph (MPSGraphSparseOps)

/// Creates a sparse tensor representation.
///
/// sparseVals corresponds to non zero values in matrix. 
/// indexTensor0 and indexTensor1 are indices used for indexing into sparse data structure. 
/// For COO, indexTensor0 is x index and indexTensor1 is y index. 
/// For CSC, indexTensor0 and indexTensor1 correspond to rowIndex and colStarts respectively. 
/// For CSR, indexTensor0 and indexTensor1 correspond to colIndex and rowStarts respectively.
/// You must set input tensors appropriately for each sparse storage type.
///
/// - Parameters:
///   - sparseStorageType: A sparseStorageType.
///   - inputTensorArray: An array of input tensors as [sparseVals, indexTensor0, indexTensor1].
///   - shape: The shape of the sparse tensor.
///   - dataType: The dataType of the sparse tensor.
///   - name: A name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object.
- (MPSGraphTensor *)sparseTensorWithType:(MPSGraphSparseStorageType)sparseStorageType
                                 tensors:(NSArray<MPSGraphTensor *> *)inputTensorArray
                                   shape:(MPSShape *)shape
                                dataType:(MPSDataType)dataType
                                    name:(NSString *_Nullable)name
    MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
    MPS_SWIFT_NAME(sparseTensor(sparseTensorWithType:tensors:shape:dataType:name:));

/// Creates a sparse tensor representation.
///
/// sparseVals corresponds to non zero values in matrix. 
/// indexTensor0 and indexTensor1 are indices used for indexing into sparse data structure. 
/// For COO, indexTensor0 is x index and indexTensor1 is y index .
/// For CSC, indexTensor0 and indexTensor1 correspond to rowIndex and colStarts respectively. 
/// For CSR, indexTensor0 and indexTensor1 correspond to colIndex and rowStarts respectively.
/// You must set input tensors appropriately for each sparse storage type.
///
/// - Parameters:
///   - sparseDescriptor: A sparseDescriptor.
///   - inputTensorArray: An array of input tensors as [sparseVals, indexTensor0, indexTensor1].
///   - shape: The shape of the sparse tensor.
///   - name: A name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object
- (MPSGraphTensor *)sparseTensorWithDescriptor:(MPSGraphCreateSparseOpDescriptor *)sparseDescriptor
                                       tensors:(NSArray<MPSGraphTensor *> *)inputTensorArray
                                         shape:(MPSShape *)shape
                                          name:(NSString *_Nullable)name
    MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
    MPS_SWIFT_NAME(sparseTensor(sparseTensorWithDescriptor:tensors:shape:name:));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphSparseOps_h */
