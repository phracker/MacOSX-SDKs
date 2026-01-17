//
//  SFSpeechLanguageModel.h
//  Speech
//
//  Created by Ethan Peters on 8/1/22.
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object describing the location of a custom language model and specialized vocabulary.
 
 Pass this object to ``SFSpeechLanguageModel/prepareCustomLanguageModelForUrl:configuration:completion:`` to indicate where that method should create the custom language model file, and to ``SFSpeechRecognitionRequest/customizedLanguageModel`` or ``DictationTranscriber/ContentHint/customizedLanguage(modelConfiguration:)`` to indicate where the system should find that model to use.
 */
API_AVAILABLE(ios(17), macos(14), tvos(18))
NS_SWIFT_SENDABLE
NS_SWIFT_NAME(SFSpeechLanguageModel.Configuration)
@interface SFSpeechLanguageModelConfiguration : NSObject <NSCopying, NSSecureCoding>

/** The location of a compiled language model file. */
@property (nonatomic, readonly, copy) NSURL *languageModel;

/** The location of a compiled vocabulary file. */
@property (nonatomic, readonly, nullable, copy) NSURL *vocabulary;

/** The relative weight of the language model customization. Value must be between 0.0 and 1.0 inclusive. */
@property (nonatomic, readonly, nullable, copy) NSNumber *weight API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0));

/** Creates a configuration with the location of a language model file. */
- (instancetype)initWithLanguageModel:(NSURL *)languageModel;

/** Creates a configuration with the locations of language model and vocabulary files. */
- (instancetype)initWithLanguageModel:(NSURL *)languageModel vocabulary:(NSURL * __nullable)vocabulary;

/** Creates a configuration with the locations of language model and vocabulary files, and custom weight. */
- (instancetype)initWithLanguageModel:(NSURL *)languageModel vocabulary:(NSURL * __nullable)vocabulary weight:(NSNumber * __nullable)weight API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0));

@end

/**
 A language model built from custom training data.
 
 Create this object using ``SFSpeechLanguageModel/prepareCustomLanguageModelForUrl:configuration:completion:`` or ``SFSpeechLanguageModel/prepareCustomLanguageModelForUrl:configuration:ignoresCache:completion:``.
 */
API_AVAILABLE(ios(17), macos(14), tvos(18))
@interface SFSpeechLanguageModel : NSObject
  
+ (void)prepareCustomLanguageModelForUrl:(NSURL *)asset clientIdentifier:(NSString *)clientIdentifier configuration:(SFSpeechLanguageModelConfiguration *)configuration completion:(void(^)(NSError * __nullable error))completion
API_DEPRECATED_WITH_REPLACEMENT("+prepareCustomLanguageModelForUrl:configuration:completion:",
                                macos(14, 26.0), ios(17, 26.0), watchos(10, 26.0), tvos(18, 26.0));

+ (void)prepareCustomLanguageModelForUrl:(NSURL *)asset clientIdentifier:(NSString *)clientIdentifier configuration:(SFSpeechLanguageModelConfiguration *)configuration ignoresCache:(BOOL)ignoresCache completion:(void(^)(NSError * __nullable error))completion
API_DEPRECATED_WITH_REPLACEMENT("+prepareCustomLanguageModelForUrl:configuration:ignoresCache:completion:",
                                macos(14, 26.0), ios(17, 26.0), watchos(10, 26.0), tvos(18, 26.0));

/**
 Creates a language model from custom training data.
 
 - Parameters:
    - asset: The URL of a file containing custom training data. Create this file with ``SFCustomLanguageModelData/export(to:)``.
    - configuration: An object listing the URLs at which this method should create the language model and compiled vocabulary from the training data.
    - completion: Called when the language model has been created.
 */
+ (void)prepareCustomLanguageModelForUrl:(NSURL *)asset configuration:(SFSpeechLanguageModelConfiguration *)configuration completion:(void(^)(NSError * __nullable error))completion;

/**
 Creates a language model from custom training data.
 
 - Parameters:
    - asset: The URL of a file containing custom training data. Create this file with ``SFCustomLanguageModelData/export(to:)``.
    - configuration: An object listing the URLs at which this method should create the language model and compiled vocabulary from the training data.
    - ignoresCache: If `true`, the language model identified by the configuration will be recreated even if the `asset` file is unchanged.
    - completion: Called when the language model has been created.
 */
+ (void)prepareCustomLanguageModelForUrl:(NSURL *)asset configuration:(SFSpeechLanguageModelConfiguration *)configuration ignoresCache:(BOOL)ignoresCache completion:(void(^)(NSError * __nullable error))completion;

@end

NS_ASSUME_NONNULL_END
