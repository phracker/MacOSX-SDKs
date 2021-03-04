//
//  MLModel.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLModelDescription.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLPredictionOptions.h>
#import <CoreML/MLModelConfiguration.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModel
 *
 * Construct a model and evaluate on a specific set of input features.
 * Inputs and outputs are accessed via the MLFeatureProvider protocol.
 * Returns a model or nil if there is an error.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLModel : NSObject

/// A model holds a description of its required inputs and expected outputs.
@property (readonly, nonatomic) MLModelDescription *modelDescription;

/// The load-time parameters used to instantiate this MLModel object.
@property (readonly, nonatomic) MLModelConfiguration *configuration API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Construct a model with a default MLModelConfiguration object
+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url
                                          error:(NSError **)error;

/// Construct a model given the location of its on-disk representation. Returns nil on error.
+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url
                                  configuration:(MLModelConfiguration *)configuration
                                          error:(NSError * _Nullable __autoreleasing *)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*!
  Construct a model asynchronously given the location of its on-disk representation and configuration.

  Model loading may take time when the model content is not immediately available (e.g. encrypted model). Use this factory method especially when the caller is on the main thread.

  @param url the location of its on-disk representation (.mlmodelc directory).
  @param configuration The model configuration
  @param handler When the model load completes successfully or unsuccessfully, the completion handler is invoked with a valid MLModel instance or NSError object.
*/
+ (void)loadContentsOfURL:(NSURL *)url
            configuration:(MLModelConfiguration *)configuration
        completionHandler:(void (^)(MLModel * _Nullable model, NSError * _Nullable error))handler API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/// All models can predict on a specific set of input features.
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                   error:(NSError **)error;

/// Prediction with explicit options
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError **)error;

/// Batch prediction without explicit options
- (nullable id<MLBatchProvider>)predictionsFromBatch:(id<MLBatchProvider>)inputBatch
                                               error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Batch prediction with explicit options
- (nullable id<MLBatchProvider>)predictionsFromBatch:(id<MLBatchProvider>)inputBatch
                                             options:(MLPredictionOptions *)options
                                               error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Provides value for the given parameter. Returns nil on error.
- (nullable id)parameterValueForKey:(MLParameterKey *)key
                              error:(NSError * _Nullable __autoreleasing * _Nullable)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END
