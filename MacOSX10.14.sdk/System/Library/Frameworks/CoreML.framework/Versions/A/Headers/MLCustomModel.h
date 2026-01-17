//
//  MLCustomLayer.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLModelDescription.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLPredictionOptions.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * Protocol for specifying a custom model implementation.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
@protocol MLCustomModel

/*
 * Initialize the custom model implementation. The model description describes the input
 * and output feature types and metadata in the Model specificaiton.
 * The parameter dictionary contains the contents of the 'parameters' map from the CustomModel specification.
 * This function is called once on model load.
 * We expect the implementation to return 'nil' and set an error in the event of failure
 * initializing the object.
 */
- (nullable instancetype)initWithModelDescription:(MLModelDescription *)modelDescription
                              parameterDictionary:(NSDictionary<NSString *, id> *)parameters
                                            error:(NSError **)error;


/*
 * Required implemenationat of a single sample input prediction.
 */
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError **)error;


@optional

/// Batch prediction with explict options, if not implemented the single input predictionFromFeatures:options:error will be used
- (nullable id<MLBatchProvider>)predictionsFromBatch:(id<MLBatchProvider>)inputBatch
                                             options:(MLPredictionOptions *)options
                                               error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END


