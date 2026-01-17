/*	NSOrthography.h
	Copyright (c) 2008-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSDictionary;

/* NSOrthography is a class used to describe the linguistic content of a piece of text, especially for the purposes of spelling and grammar checking.  It describes (a) which scripts the text contains, (b) a dominant language and possibly other languages for each of these scripts, and (c) a dominant script and language for the text as a whole.  Scripts are uniformly described by standard four-letter tags (Latn, Grek, Cyrl, etc.) with the supertags Jpan and Kore typically used for Japanese and Korean text, Hans and Hant for Chinese text; the tag Zyyy is used if a specific script cannot be identified.  Languages are uniformly described by BCP-47 tags, preferably in canonical form; the tag und is used if a specific language cannot be determined. */

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSOrthography : NSObject <NSCopying, NSCoding>

/* These are the primitive properties which a subclass must implement.  The dominantScript should be a script tag (such as Latn, Cyrl, and so forth) and the languageMap should be a dictionary whose keys are script tags and whose values are arrays of language tags (such as en, fr, de, and so forth). */
@property (readonly) NSString *dominantScript;
@property (readonly) NSDictionary *languageMap;

@end

@interface NSOrthography (NSOrthographyExtended)

/* languagesForScript: returns the list of languages for the specified script, and dominantLanguageForScript: returns the first item on that list. */
- (NSArray *)languagesForScript:(NSString *)script;
- (NSString *)dominantLanguageForScript:(NSString *)script;

/*  The dominantLanguage is the first in the list of languages for the dominant script, allScripts includes the dominant script and all others appearing as keys in the language map, and allLanguages includes all languages appearing in the values of the language map. */
@property (readonly) NSString *dominantLanguage;
@property (readonly) NSArray *allScripts;
@property (readonly) NSArray *allLanguages;

@end

@interface NSOrthography (NSOrthographyCreation)

+ (id)orthographyWithDominantScript:(NSString *)script languageMap:(NSDictionary *)map;
- (id)initWithDominantScript:(NSString *)script languageMap:(NSDictionary *)map;

@end

