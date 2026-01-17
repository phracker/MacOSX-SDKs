/*    NLTagScheme.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* An NLTagScheme is a type of tagging usable with NLTagger. A given tagger instance is created with an array of tag schemes, specifying which types of tagging it will provide. A specific tag scheme must be specified whenever tags are requested. Each tag scheme has its own set of tags. Clients using custom models may also define their own tag schemes and tags.
*/

typedef NSString *NLTagScheme NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT NLTagScheme const NLTagSchemeTokenType API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));               /* This tag scheme classifies tokens according to their broad general type:  word, punctuation, whitespace, etc. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeLexicalClass API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));            /* This tag scheme classifies tokens according to class:  part of speech for words, type of punctuation or whitespace, etc. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeNameType API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                /* This tag scheme classifies tokens as to whether they are part of named entities of various types or not. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeNameTypeOrLexicalClass API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));  /* This tag scheme follows NLTagSchemeNameType for names, NLTagSchemeLexicalClass for all other tokens. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeLemma API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                   /* This tag scheme supplies a stem form for each word token (if known). */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeLanguage API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                /* This tag scheme tags tokens according to their most likely language (if known). */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeScript API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                  /* This tag scheme tags tokens according to their script. */

/* An NLTag is a tag associated with a given tag scheme that can be returned by NLTagger. Each tag scheme has its own set of tags. For NLTagSchemeTokenType, NLTagSchemeLexicalClass, NLTagSchemeNameType, and NLTagSchemeNameTypeOrLexicalClass, tags will be taken from the lists below (clients may use == comparison). Tags for NLTagSchemeLemma are lemmas from the language. Tags for NLTagSchemeLanguage are standard language abbreviations. Tags for NLTagSchemeScript are standard script abbreviations
*/

typedef NSString *NLTag NS_TYPED_EXTENSIBLE_ENUM;

/* Tags for NLTagSchemeTokenType */
FOUNDATION_EXPORT NLTag const NLTagWord API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                          /* Tokens considered to be words or word-like linguistic items. */
FOUNDATION_EXPORT NLTag const NLTagPunctuation API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                   /* Tokens made up of punctuation. */
FOUNDATION_EXPORT NLTag const NLTagWhitespace API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                    /* Tokens made up of whitespace of all sorts. */
FOUNDATION_EXPORT NLTag const NLTagOther API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                         /* Other tokens, including non-linguistic items such as symbols. */

/* Tags for NLTagSchemeLexicalClass */
FOUNDATION_EXPORT NLTag const NLTagNoun API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagVerb API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagAdjective API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagAdverb API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagPronoun API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagDeterminer API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagParticle API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagPreposition API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagNumber API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagConjunction API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagInterjection API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagClassifier API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagIdiom API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOtherWord API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagSentenceTerminator API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOpenQuote API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagCloseQuote API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOpenParenthesis API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagCloseParenthesis API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagWordJoiner API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagDash API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOtherPunctuation API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagParagraphBreak API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOtherWhitespace API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Tags for NLTagSchemeNameType */
FOUNDATION_EXPORT NLTag const NLTagPersonalName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagPlaceName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOrganizationName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

