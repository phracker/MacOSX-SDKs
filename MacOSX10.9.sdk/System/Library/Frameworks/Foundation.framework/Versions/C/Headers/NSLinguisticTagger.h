/*	NSLinguisticTagger.h
	Copyright (c) 2009-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

@class NSArray, NSOrthography;

/* NSLinguisticTagger is a class used to automatically segment natural-language text and tag the tokens with information such as language, script, lemma, and part of speech.  An instance of this class is assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme.
*/

/* Tag schemes */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeTokenType NS_AVAILABLE(10_7, 5_0);               /* This tag scheme classifies tokens according to their broad general type:  word, punctuation, whitespace, etc. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeLexicalClass NS_AVAILABLE(10_7, 5_0);            /* This tag scheme classifies tokens according to class:  part of speech for words, type of punctuation or whitespace, etc. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeNameType NS_AVAILABLE(10_7, 5_0);                /* This tag scheme classifies tokens as to whether they are part of named entities of various types or not. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeNameTypeOrLexicalClass NS_AVAILABLE(10_7, 5_0);  /* This tag scheme follows NSLinguisticTagSchemeNameType for names, NSLinguisticTagSchemeLexicalClass for all other tokens. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeLemma NS_AVAILABLE(10_7, 5_0);                   /* This tag scheme supplies a stem form for each word token (if known). */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeLanguage NS_AVAILABLE(10_7, 5_0);                /* This tag scheme tags tokens according to their most likely language (if known). */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeScript NS_AVAILABLE(10_7, 5_0);                  /* This tag scheme tags tokens according to their script. */

/* Tags for NSLinguisticTagSchemeTokenType */
FOUNDATION_EXPORT NSString *const NSLinguisticTagWord NS_AVAILABLE(10_7, 5_0);                          /* Tokens considered to be words or word-like linguistic items. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagPunctuation NS_AVAILABLE(10_7, 5_0);                   /* Tokens made up of punctuation. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagWhitespace NS_AVAILABLE(10_7, 5_0);                    /* Tokens made up of whitespace of all sorts. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagOther NS_AVAILABLE(10_7, 5_0);                         /* Other tokens, including non-linguistic items such as symbols. */

/* Tags for NSLinguisticTagSchemeLexicalClass */
FOUNDATION_EXPORT NSString *const NSLinguisticTagNoun NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagVerb NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagAdjective NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagAdverb NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagPronoun NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagDeterminer NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagParticle NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagPreposition NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagNumber NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagConjunction NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagInterjection NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagClassifier NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagIdiom NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOtherWord NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagSentenceTerminator NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOpenQuote NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagCloseQuote NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOpenParenthesis NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagCloseParenthesis NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagWordJoiner NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagDash NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOtherPunctuation NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagParagraphBreak NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOtherWhitespace NS_AVAILABLE(10_7, 5_0);

/* Tags for NSLinguisticTagSchemeNameType */
FOUNDATION_EXPORT NSString *const NSLinguisticTagPersonalName NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagPlaceName NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOrganizationName NS_AVAILABLE(10_7, 5_0);

/* For NSLinguisticTagSchemeTokenType, NSLinguisticTagSchemeLexicalClass, NSLinguisticTagSchemeNameType, and NSLinguisticTagSchemeNameTypeOrLexicalClass, tags will be taken from the lists above (clients may use == comparison).  Tags for NSLinguisticTagSchemeLemma are lemmas from the language.  Tags for NSLinguisticTagSchemeLanguage are standard language abbreviations.  Tags for NSLinguisticTagSchemeScript are standard script abbreviations.
*/

/* Options arguments of type NSLinguisticTaggerOptions may include the following flags, which allow clients interested only in certain general types of tokens to specify that tokens of other types should be omitted from the returned results. */
typedef NS_OPTIONS(NSUInteger, NSLinguisticTaggerOptions) {   /* Any combination of options from the enumeration. */
    NSLinguisticTaggerOmitWords         = 1 << 0,       /* Omit tokens of type NSLinguisticTagWord. */
    NSLinguisticTaggerOmitPunctuation   = 1 << 1,       /* Omit tokens of type NSLinguisticTagPunctuation. */
    NSLinguisticTaggerOmitWhitespace    = 1 << 2,       /* Omit tokens of type NSLinguisticTagWhitespace. */
    NSLinguisticTaggerOmitOther         = 1 << 3,       /* Omit tokens of type NSLinguisticTagOther. */
    NSLinguisticTaggerJoinNames         = 1 << 4        /* Join tokens of tag scheme NSLinguisticTagSchemeNameType. */
};   

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSLinguisticTagger : NSObject {
@private
    NSArray *_schemes;
    NSUInteger _options;
    NSString *_string;
    id _orthographyArray;
    id _tokenArray;
    id _reserved;
}

/* An instance of NSLinguisticTagger is created with an array of tag schemes.  The tagger will be able to supply tags corresponding to any of the schemes in this array.
*/
- (id)initWithTagSchemes:(NSArray *)tagSchemes options:(NSUInteger)opts NS_AVAILABLE(10_7, 5_0);
- (NSArray *)tagSchemes NS_AVAILABLE(10_7, 5_0);
- (void)setString:(NSString *)string NS_AVAILABLE(10_7, 5_0);
- (NSString *)string NS_AVAILABLE(10_7, 5_0);

/* Clients wishing to know the tag schemes supported in NSLinguisticTagger for a particular language may query them with this method.  The language should be specified using a standard abbreviation as with NSOrthography.
*/
+ (NSArray *)availableTagSchemesForLanguage:(NSString *)language NS_AVAILABLE(10_7, 5_0);

/* If clients know the orthography for a given portion of the string, they may supply it to the tagger.  Otherwise, the tagger will infer the language from the contents of the text.  In each case, the charIndex or range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception.
*/
- (void)setOrthography:(NSOrthography *)orthography range:(NSRange)range NS_AVAILABLE(10_7, 5_0);
- (NSOrthography *)orthographyAtIndex:(NSUInteger)charIndex effectiveRange:(NSRangePointer)effectiveRange NS_AVAILABLE(10_7, 5_0);

/* If the string attached to the tagger is mutable, this method must be called to inform the tagger whenever the string changes.  The newRange is the range in the final string which was explicitly edited, and delta is the change in length from the previous version to the current version of the string.  Alternatively, the client may call setString: again to reset all information about the string, but this has the disadvantage of not preserving information about portions of the string that have not changed.
*/
- (void)stringEditedInRange:(NSRange)newRange changeInLength:(NSInteger)delta NS_AVAILABLE(10_7, 5_0);

/* The tagger will segment the string as needed into sentences and tokens, and return those ranges along with a tag for any scheme in its array of tag schemes.  The fundamental tagging method on NSLinguisticTagger is a block iterator, that iterates over all tokens intersecting a given range, supplying tags and ranges.  There are several additional convenience methods, for obtaining a sentence range, information about a single token, or for obtaining information about all tokens intersecting a given range at once, in arrays.  In each case, the charIndex or range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception.  Note that a given instance of NSLinguisticTagger should not be used from more than one thread simultaneously.
*/
#if NS_BLOCKS_AVAILABLE
- (void)enumerateTagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts usingBlock:(void (^)(NSString *tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);
#endif /* NS_BLOCKS_AVAILABLE */

- (NSRange)sentenceRangeForRange:(NSRange)range NS_AVAILABLE(10_7, 5_0);
- (NSString *)tagAtIndex:(NSUInteger)charIndex scheme:(NSString *)tagScheme tokenRange:(NSRangePointer)tokenRange sentenceRange:(NSRangePointer)sentenceRange NS_AVAILABLE(10_7, 5_0);
- (NSArray *)tagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts tokenRanges:(NSArray **)tokenRanges NS_AVAILABLE(10_7, 5_0);
- (NSArray *)possibleTagsAtIndex:(NSUInteger)charIndex scheme:(NSString *)tagScheme tokenRange:(NSRangePointer)tokenRange sentenceRange:(NSRangePointer)sentenceRange scores:(NSArray **)scores NS_AVAILABLE(10_7, 5_0);

@end

@interface NSString (NSLinguisticAnalysis)

/* Clients wishing to analyze a given string once may use these NSString APIs without having to create an instance of NSLinguisticTagger.  If more than one tagging operation is needed on a given string, it is more efficient to use an explicit NSLinguisticTagger instance.
*/
- (NSArray *)linguisticTagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts orthography:(NSOrthography *)orthography tokenRanges:(NSArray **)tokenRanges NS_AVAILABLE(10_7, 5_0);
#if NS_BLOCKS_AVAILABLE
- (void)enumerateLinguisticTagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts orthography:(NSOrthography *)orthography usingBlock:(void (^)(NSString *tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);
#endif /* NS_BLOCKS_AVAILABLE */

@end

