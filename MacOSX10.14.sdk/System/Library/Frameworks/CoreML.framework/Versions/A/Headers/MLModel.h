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

/// All models can predict on a specific set of input features.
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                   error:(NSError **)error;

/// Prediction with explict options
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError **)error;

/// Batch prediction with explict options
- (nullable id<MLBatchProvider>)predictionsFromBatch:(id<MLBatchProvider>)inputBatch
                                             options:(MLPredictionOptions *)options
                                               error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END
