/*    NLModel.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>
#import <CoreML/MLModel.h>

@class NLModelConfiguration;

NS_ASSUME_NONNULL_BEGIN

/* NLModel is a class representing a custom model that has been trained for tagging. Currently supported models follow one of two types. Classifier models, of type NLModelTypeClassifier, tag text at the sentence or higher level. Sequence models, of type NLModelTypeSequence, tag text at the token level. Currently NLModel objects can be created only from model files on disk or from MLModel objects. Each NLModel object has an associated NLModelConfiguration, which contains all the metadata about the model, including specifying whether it is a sequence or classifier model.
*/

typedef NS_ENUM(NSInteger, NLModelType) {
    NLModelTypeClassifier,
    NLModelTypeSequence
} NS_SWIFT_NAME(NLModel.ModelType);

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLModel : NSObject

+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
+ (nullable instancetype)modelWithMLModel:(MLModel *)mlModel error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@property (readonly, copy) NLModelConfiguration *configuration API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* For inference purposes, a model will usually be attached to an NLTagger via -setModels:forTagScheme:, and the tagger will then take care of calling the model to produce tags as appropriate. However, it is also possible to use a model to make an individual prediction, either of the label for a given pieces of text (for a classifier model), or of the labels for a given sequence of tokens (for a sequence model).
*/

- (nullable NSString *)predictedLabelForString:(NSString *)string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

- (NSArray<NSString *> *)predictedLabelsForTokens:(NSArray<NSString *> *)tokens API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

/* NLModelConfiguration is a class representing the metadata about a model, including specifying whether it is a sequence or classifier model, what language it is intended to support, and what revision of the model training was used to produce the model.
*/

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLModelConfiguration : NSObject <NSCopying, NSSecureCoding>

@property (readonly) NLModelType type API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Most models will be trained to support tagging for a specific language, specified using a standard language abbreviation.
*/
@property (nullable, readonly, copy) NLLanguage language API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Each update to model training is specified by a particular revision number, and each model is labeled with the revision of the model training that was used to produce it. Each system version has a current revision for each model type, corresponding to the most recent revision of model training available, and a larger set of supported revisions for backward compatibility. A given revision will be supported for a number of system versions, but not indefinitely, and the set of supported revisions can be used to determine whether a given revision is still supported. Attempting to use a model from a revision that is no longer supported will fail with a suitable error.
*/

@property (readonly) NSUInteger revision API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

+ (NSIndexSet *)supportedRevisionsForType:(NLModelType)type API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
+ (NSUInteger)currentRevisionForType:(NLModelType)type API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END
