/*    NLTokenizer.h
      Copyright (c) 2017-2020, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>

NS_ASSUME_NONNULL_BEGIN

/* NLTokenizer is a class used to automatically segment natural-language text. An instance of this class is created with a specific unit and assigned a string to tokenize, and clients can then obtain ranges for tokens in that string appropriate to the given unit. Units are defined by NLTokenUnit, which specifies the size of the units in a string to which tokenization or tagging applies, whether word, sentence, paragraph, or document.
*/

typedef NS_ENUM(NSInteger, NLTokenUnit) {
    NLTokenUnitWord,         /* Token units are at word or equivalent level */
    NLTokenUnitSentence,     /* Token units are at sentence level */
    NLTokenUnitParagraph,    /* Token units are at paragraph level */
    NLTokenUnitDocument      /* Token unit is the entire string */
};

/* The tokenizer also conveys some basic information about the content of the token via NLTokenizerAttributes.
*/
typedef NS_OPTIONS(NSUInteger, NLTokenizerAttributes) {
    NLTokenizerAttributeNumeric    = 1 << 0,
    NLTokenizerAttributeSymbolic   = 1 << 1,
    NLTokenizerAttributeEmoji      = 1 << 2
} NS_SWIFT_NAME(NLTokenizer.Attributes);

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLTokenizer : NSObject

- (instancetype)initWithUnit:(NLTokenUnit)unit NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@property (readonly, nonatomic) NLTokenUnit unit API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* An NLTokenizer instance must be assigned a string to tokenize, and clients can then obtain ranges for tokens in that string appropriate to the tokenizer's unit.
*/
@property (nullable, retain, nonatomic) NSString *string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Clients may specify the language of the string, if it is known; otherwise it will be determined from the text.
*/
- (void)setLanguage:(NLLanguage)language API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Returns the range corresponding to the token for the tokenizer's unit that contains the given character index. The index must not extend beyond the end of the tokenizer's string, or the method will raise an exception.
*/
- (NSRange)tokenRangeAtIndex:(NSUInteger)characterIndex API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* Returns the smallest range covering all tokens for the tokenizer's unit intersecting the given range.  If range.length == 0, this is equivalent to tokenRangeAtIndex:.
*/
- (NSRange)tokenRangeForRange:(NSRange)range API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/* Returns the ranges corresponding to the tokens for the tokenizer's unit that intersect the given range.
*/
- (NSArray <NSValue *> *)tokensForRange:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* The tokenizer will segment the string as needed into tokens for the given unit, and return those ranges via a block iterator, that iterates over all tokens intersecting a given range, supplying token ranges and flags. The range passed in must not extend beyond the end of the tokenizer's string, or the method will raise an exception. Note that a given instance of NLTokenizer should not be used from more than one thread simultaneously.
*/
- (void)enumerateTokensInRange:(NSRange)range usingBlock:(void (NS_NOESCAPE ^)(NSRange tokenRange, NLTokenizerAttributes flags, BOOL *stop))block API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
