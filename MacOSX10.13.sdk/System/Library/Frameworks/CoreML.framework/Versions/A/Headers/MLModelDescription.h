//
//  MLModelDescription.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreML/MLFeatureDescription.h>
#import <CoreML/MLModelMetadataKeys.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A description of a model containing input and output feature descriptions, optionally outputted features
 * with special meaning and metadata.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLModelDescription : NSObject

/// Description of the inputs to the model
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureDescription *> *inputDescriptionsByName;

/// Description of the outputs from the model
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureDescription *> *outputDescriptionsByName;

/// Name of the primary target / predicted output feature in the output descriptions
@property (readonly, nullable, nonatomic, copy) NSString *predictedFeatureName;

/// Key for all predicted probabilities stored as a MLFeatureTypeDictionary in the output descriptions
@property (readonly, nullable, nonatomic, copy) NSString *predictedProbabilitiesName;

/// Optional metadata describing the model
@property (readonly, nonatomic) NSDictionary<MLModelMetadataKey, id> *metadata;

@end

NS_ASSUME_NONNULL_END
