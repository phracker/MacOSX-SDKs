/*    NLLanguageRecognizer.h
      Copyright (c) 2017-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>

NS_ASSUME_NONNULL_BEGIN

/* NLLanguageRecognizer is a class used to automatically identify the language of text. An instance of this class is created and passed one or more pieces of text, and clients can then obtain either a single most likely language or a set of language candidates with probabilities. It is also possible to constrain the identification by specifying either a list of hints about known prior probabilities for languages, or a list of constraint languages into which the predictions are constrained to fall, or both.
*/

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLLanguageRecognizer : NSObject

/* dominantLanguageForString: is a convenience method used to get the single most likely language for a specific piece of text, without having to create an NLLanguageRecognizer object.
*/
+ (nullable NLLanguage)dominantLanguageForString:(NSString *)string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* To use an NLLanguageRecognizer object, clients create it and then pass in one or more pieces of text via the process method. After this, identification of the text can be obtained from the object. The object can be restored to its initial state by calling reset, so that it can then be reused for a new analysis. Note that a given instance of NLLanguageRecognizer should not be used from more than one thread simultaneously.
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (void)processString:(NSString *)string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (void)reset API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* The identification obtained from an NLLanguageRecognizer object can be either a single most likely language, via dominantLanguage, or a set of language candidates with probabilities, via languageHypothesesWithMaximum:. The latter method returns a dictionary mapping languages to their estimated probabilities, up to a maximum number given by maxHypotheses.
*/
@property (nullable, readonly, copy, nonatomic) NLLanguage dominantLanguage API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (NSDictionary<NLLanguage, NSNumber *> *)languageHypothesesWithMaximum:(NSUInteger)maxHypotheses API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* Allows clients to specify known prior probabilities for languages as hints for the language identification process. This should be a dictionary mapping languages to their prior probabilities.
*/
@property (copy, nonatomic) NSDictionary<NLLanguage, NSNumber *> *languageHints API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/*  Allows clients to constrain the space of identified languages. For example, setting Spanish, French and English as constraints would yield identification only from these three languages. */
@property (copy, nonatomic) NSArray<NLLanguage> *languageConstraints API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END
