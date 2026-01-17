/*    NLTagger.h
      Copyright (c) 2017-2020, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>
#import <NaturalLanguage/NLGazetteer.h>
#import <NaturalLanguage/NLTagScheme.h>
#import <NaturalLanguage/NLTokenizer.h>

@class NLModel;

NS_ASSUME_NONNULL_BEGIN

/* NLTagger is a class used to automatically tag portions of natural language text with information such as parts of speech, named entities, lemmas, language, and script. An instance of this class is assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme and unit. Predefined tag schemes and tags are defined in NLTagScheme.h.  Options arguments of type NLTaggerOptions may include the following flags, which allow clients interested only in certain general types of tokens to specify that tokens of other types should be omitted from the returned results.
*/

typedef NS_OPTIONS(NSUInteger, NLTaggerOptions) {   /* Any combination of options from the enumeration. */
    NLTaggerOmitWords         = 1 << 0,       /* Omit tokens of type NLTagWord. */
    NLTaggerOmitPunctuation   = 1 << 1,       /* Omit tokens of type NLTagPunctuation. */
    NLTaggerOmitWhitespace    = 1 << 2,       /* Omit tokens of type NLTagWhitespace. */
    NLTaggerOmitOther         = 1 << 3,       /* Omit tokens of type NLTagOther. */
    NLTaggerJoinNames         = 1 << 4,       /* Join tokens of tag scheme NLTagSchemeNameType. */
    NLTaggerJoinContractions  = 1 << 5        /* Join contractions such as it's, can't, etc. */
} NS_SWIFT_NAME(NLTagger.Options);

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLTagger : NSObject

/* An instance of NLTagger is created with an array of tag schemes. The tagger will be able to supply tags corresponding to any of the schemes in this array.
*/
- (instancetype)initWithTagSchemes:(NSArray<NLTagScheme> *)tagSchemes NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@property (readonly, copy, nonatomic) NSArray<NLTagScheme> *tagSchemes API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* An NLTagger instance must be assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme and unit.
*/
@property (nullable, retain, nonatomic) NSString *string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Not all combinations of scheme and unit are supported, and not all combinations of scheme and language are supported. Clients can use +availableTagSchemesForUnit:language: to determine which ones are supported on the current device.
*/
+ (NSArray<NLTagScheme> *)availableTagSchemesForUnit:(NLTokenUnit)unit language:(NLLanguage)language API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Returns the range corresponding to the token for the given unit that contains the given character index.
*/
- (NSRange)tokenRangeAtIndex:(NSUInteger)characterIndex unit:(NLTokenUnit)unit API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* Returns the smallest range covering all tokens for the given unit intersecting the given range.  If range.length == 0, this is equivalent to tokenRangeAtIndex:unit:.
*/
- (NSRange)tokenRangeForRange:(NSRange)range unit:(NLTokenUnit)unit API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/* Returns the top identified language (if any) for the entire string. Convenience for tagAtIndex: with NLTagSchemeLanguage and NLTaggerUnitDocument.
*/
@property (nullable, readonly, copy, nonatomic) NLLanguage dominantLanguage API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* The tagger will segment the string as needed into tokens for the given unit, and return those ranges along with a tag for any scheme in its array of tag schemes. The fundamental tagging method on NLTagger is a block iterator, that iterates over all tokens intersecting a given range, supplying tags and ranges. There are additional convenience methods for obtaining information about a single token, or for obtaining information about all tokens intersecting a given range at once. In each case, the index or range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception. Note that a given instance of NLTagger should not be used from more than one thread simultaneously.
*/
- (void)enumerateTagsInRange:(NSRange)range unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme options:(NLTaggerOptions)options usingBlock:(void (NS_NOESCAPE ^)(NLTag _Nullable tag, NSRange tokenRange, BOOL *stop))block API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;
- (nullable NLTag)tagAtIndex:(NSUInteger)characterIndex unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme tokenRange:(nullable NSRangePointer)tokenRange API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;
- (NSArray<NLTag> *)tagsInRange:(NSRange)range unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme options:(NLTaggerOptions)options tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* In addition, it is possible to obtain multiple hypotheses for a given tag with associated probability scores.  Not all tag schemes will produce more than one hypothesis. */

- (NSDictionary<NLTag, NSNumber *> *)tagHypothesesAtIndex:(NSUInteger)characterIndex unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme maximumCount:(NSUInteger)maximumCount tokenRange:(nullable NSRangePointer)tokenRange API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/* If clients know the language or orthography for a given portion of the string, they may supply it to the tagger (after setting the string itself via 'string' @property). Otherwise, the tagger will infer the language from the contents of the text. In each case, the range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception. When a new string is set, it resets any language or orthography settings.
*/
- (void)setLanguage:(NLLanguage)language range:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;
- (void)setOrthography:(NSOrthography *)orthography range:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* In addition to the built-in models for predefined tag schemes, clients can set custom models that they have trained, either for existing tag schemes or for custom tag schemes. If multiple models are specified, they will be matched to text based on the language that they specify.
*/
- (void)setModels:(NSArray <NLModel *> *)models forTagScheme:(NLTagScheme)tagScheme API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (NSArray <NLModel *> *)modelsForTagScheme:(NLTagScheme)tagScheme API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* In addition to the model for a given tag scheme, clients can add a custom gazetteer that will override the tags for that scheme, for terms that are included in the gazetteer. If multiple gazetteers are specified, they will be matched to text based on the language that they specify.
*/
- (void)setGazetteers:(NSArray <NLGazetteer *> *)gazetteers forTagScheme:(NLTagScheme)tagScheme API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(setGazetteers(_:for:));
- (NSArray <NLGazetteer *> *)gazetteersForTagScheme:(NLTagScheme)tagScheme API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(gazetteers(for:));

/* If a given tag scheme is not available for a particular language on the current device, it may be because necessary assets have not been loaded onto this device. In those cases, clients may put in a request for those assets. If they are available for loading, then they will be requested and at some point will be loaded and made available on the device, and the completion handler will be called on an arbitrary queue. The completion handler may be called immediately if the state of the assets is already known or if an error occurs.
*/

typedef NS_ENUM(NSInteger, NLTaggerAssetsResult) {
    NLTaggerAssetsResultAvailable,
    NLTaggerAssetsResultNotAvailable,
    NLTaggerAssetsResultError
} NS_SWIFT_NAME(NLTagger.AssetsResult);

+ (void)requestAssetsForLanguage:(NLLanguage)language tagScheme:(NLTagScheme)tagScheme completionHandler:(void (^)(NLTaggerAssetsResult result, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) NS_SWIFT_NAME(requestAssets(for:tagScheme:completionHandler:));

@end

NS_ASSUME_NONNULL_END
