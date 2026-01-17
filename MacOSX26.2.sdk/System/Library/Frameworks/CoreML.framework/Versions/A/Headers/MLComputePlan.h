//
//  MLComputePlan.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLComputePlanCost;
@class MLComputePlanDeviceUsage;
@class MLModelAsset;
@class MLModelConfiguration;
@class MLModelStructure;
@class MLModelStructureNeuralNetworkLayer;
@class MLModelStructureProgramOperation;

NS_ASSUME_NONNULL_BEGIN

/// A class describing the plan for executing a model.
///
/// The application can use the plan to estimate the necessary cost and
/// resources of the model before running the predictions.
///
///```
/// // Load the compute plan of an ML Program model.
/// [MLComputePlan loadContentsOfURL:modelURL configuration:configuration completionHandler:^(MLComputePlan * _Nullable computePlan, NSError * _Nullable error) {
///    if (!computePlan) {
///        // Handle error.
///        return;
///    }
///    MLModelStructureProgram *program = computePlan.modelStructure.program;
///    if (!program) {
///        [NSException raise:NSInternalInconsistencyException format:@"Unexpected model type."];
///    }
///
///    MLModelStructureFunction *mainFunction = program.functions["main"];
///    if (!mainFunction) {
///        [NSException raise:NSInternalInconsistencyException format:@"Missing main function."];
///    }
///
///    NSArray<MLModelStructureProgramOperation *> *operations = mainFunction.block.operations;
///    for (MLModelStructureProgramOperation *operation in operations) {
///        // Get the compute device usage for the operation.
///        MLComputeDeviceUsage *computeDeviceUsage = [computePlan computeDeviceUsageForMLProgramOperation:operation];
///        // Get the estimated cost of executing the operation.
///        MLComputePlanCost *estimatedCost = [computePlan estimatedCostOfMLProgramOperation:operation];
///
///    }
/// }];
///```
///
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLComputePlan : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;


/// Construct the compute plan of a model asynchronously given the location of its on-disk representation.
///
/// @param url The location of its on-disk representation (.mlmodelc directory).
/// @param configuration The model configuration.
/// @param handler When the compute plan is constructed successfully or unsuccessfully, the completion handler is invoked with a valid MLComputePlan instance or NSError object.
+ (void)loadContentsOfURL:(NSURL *)url
            configuration:(MLModelConfiguration *)configuration
        completionHandler:(void (^)(MLComputePlan * _Nullable computePlan, NSError * _Nullable error))handler NS_SWIFT_ASYNC_NAME(load(contentsOf:configuration:));

/// Construct the compute plan of a model asynchronously given the model asset.
///
/// @param asset The model asset.
/// @param configuration The model configuration.
/// @param handler When the compute plan is constructed successfully or unsuccessfully, the completion handler is invoked with a valid MLComputePlan instance or NSError object.
+ (void)loadModelAsset:(MLModelAsset *)asset
         configuration:(MLModelConfiguration *)configuration
     completionHandler:(void (^)(MLComputePlan * _Nullable computePlan, NSError * _Nullable error))handler NS_SWIFT_ASYNC_NAME(load(asset:configuration:));

/// Returns the estimated cost of executing an ML Program operation.
///
/// @param operation An ML Program operation.
/// @returns The estimated cost of executing the operation or nil if the cost couldn't be estimated.
- (nullable MLComputePlanCost *)estimatedCostOfMLProgramOperation:(MLModelStructureProgramOperation *)operation NS_SWIFT_NAME(cost(of:));

/// Returns the anticipated compute devices that would be used for executing a NeuralNetwork layer.
///
/// @param layer A NeuralNetwork layer.
/// @returns The anticipated compute devices that would be used for executing the layer or `nil` if the usage couldn't be determined.
- (nullable MLComputePlanDeviceUsage *)computeDeviceUsageForNeuralNetworkLayer:(MLModelStructureNeuralNetworkLayer *)layer NS_SWIFT_NAME(computeDeviceUsage(for:));

/// Returns The anticipated compute devices that would be used for executing an ML Program operation.
///
/// @param operation  An ML Program operation.
/// @returns The anticipated compute devices that would be used for executing the operation or `nil`if the usage couldn't be determined.
- (nullable MLComputePlanDeviceUsage *)computeDeviceUsageForMLProgramOperation:(MLModelStructureProgramOperation *)operation NS_SWIFT_NAME(computeDeviceUsage(for:));

/// The model structure.
@property (readonly, strong, nonatomic) MLModelStructure *modelStructure;

@end

NS_ASSUME_NONNULL_END
