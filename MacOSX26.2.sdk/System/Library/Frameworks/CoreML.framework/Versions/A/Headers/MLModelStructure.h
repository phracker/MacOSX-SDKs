//
//  MLModelStructure.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

@class MLModelAsset;
@class MLModelStructureNeuralNetwork;
@class MLModelStructureProgram;
@class MLModelStructurePipeline;

NS_ASSUME_NONNULL_BEGIN

/// A class representing the structure of a model.
///
/// ```
/// // Load the model structure.
/// [MLModelStructure loadContentsOfURL:modelURL completionHandler:^(MLModelStructure * _Nullable modelStructure, NSError * _Nullable error) {
///    if (!modelStructure) {
///        // Handle error.
///        return;
///    }
///    if (modelStructure.neuralNetwork) {
///        // Examine Neural network model.
///    } else if (modelStructure.program) {
///        // Examine ML Program model.
///    } else if (modelStructure.pipeline) {
///        // Examine Pipeline model.
///    } else {
///        // The model type is something else.
///    }
/// }];
/// ```
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructure : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// Construct the model structure asynchronously given the location of its on-disk representation.
///
/// @param url The location of its on-disk representation (.mlmodelc directory).
/// @param handler When the model structure is constructed successfully or unsuccessfully, the completion handler is invoked with a valid MLModelStructure instance or NSError object.
+ (void)loadContentsOfURL:(NSURL *)url
        completionHandler:(void (^)(MLModelStructure * _Nullable modelStructure, NSError * _Nullable error))handler NS_SWIFT_ASYNC_NAME(load(contentsOf:));

/// Construct the model structure asynchronously  given the model asset.
///
/// @param asset The model asset.
/// @param handler When the model structure is constructed successfully or unsuccessfully, the completion handler is invoked with a valid MLModelStructure instance or NSError object.
+ (void)loadModelAsset:(MLModelAsset *)asset
     completionHandler:(void (^)(MLModelStructure * _Nullable modelStructure, NSError * _Nullable error))handler NS_SWIFT_ASYNC_NAME(load(asset:));

/// If the model is of NeuralNetwork type then it is the structure of the NeuralNetwork otherwise `nil`.
@property (readonly, strong, nonatomic, nullable) MLModelStructureNeuralNetwork *neuralNetwork;
/// If the model is of ML Program type then it is the structure of the ML Program otherwise `nil`.
@property (readonly, strong, nonatomic, nullable) MLModelStructureProgram *program;
/// If the model is of Pipeline type then it is the structure of the Pipeline otherwise `nil`.
@property (readonly, strong, nonatomic, nullable) MLModelStructurePipeline *pipeline;

@end

NS_ASSUME_NONNULL_END
