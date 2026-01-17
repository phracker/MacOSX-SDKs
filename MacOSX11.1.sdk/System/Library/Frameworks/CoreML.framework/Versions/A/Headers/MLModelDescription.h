//
//  MLModelDescription.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureDescription.h>
#import <CoreML/MLModelMetadataKeys.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

@class MLParameterKey;
@class MLParameterDescription;

/*!
 * A description of a model containing input and output feature descriptions, optionally outputted features
 * with special meaning and metadata.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLModelDescription : NSObject <NSSecureCoding>

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

/*!
  Array to map a class index to the corresponding label, which is either Number or String.

  The property is populated from the classLabels entry specified in the model's protobuf message. When the model is a pipeline, which contains one or more sub models, the property value is calculated as follows.

  1. If the pipeline model's proto message specifies predictedFeatureName parameter, use classLabels property value of the sub model with the output feature with the name.

  2. Otherwise, if the pipeline model has only one sub model with non-nil classLabels property, use the property value.

  3. Otherwise, the property is nil.
*/
@property (readonly, nullable, nonatomic, copy) NSArray<id> *classLabels API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

@end

/*!
 * Additions to model descriptions related to model update API.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
@interface MLModelDescription (MLUpdateAdditions)

// Indicates if the model has to been configured for updation using model update API.
@property (readonly, nonatomic) BOOL isUpdatable;

// Allows for access of each training input as a feature description.
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureDescription *> *trainingInputDescriptionsByName;

@end

/*!
 * Additions to model descriptions related to model parameters
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
@interface MLModelDescription (MLParameters)

// Allows for access of each parameter as parameter description.
@property (readonly, nonatomic) NSDictionary<MLParameterKey *, MLParameterDescription *> *parameterDescriptionsByKey;

@end


NS_ASSUME_NONNULL_END
