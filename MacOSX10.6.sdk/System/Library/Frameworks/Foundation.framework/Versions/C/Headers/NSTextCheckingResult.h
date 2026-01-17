/*	NSTextCheckingResult.h
	Copyright (c) 2008-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray, NSDictionary, NSDate, NSTimeZone, NSOrthography, NSURL;

/* NSTextCheckingResult is a class used to describe items located by text checking.  Each of these objects represents something that has been found during checking--a misspelled word, a sentence with grammatical issues, a detected URL, a straight quote to be replaced with curly quotes, and so forth. */

enum {
    NSTextCheckingTypeOrthography   = 1ULL << 0,            // language identification
    NSTextCheckingTypeSpelling      = 1ULL << 1,            // spell checking
    NSTextCheckingTypeGrammar       = 1ULL << 2,            // grammar checking
    NSTextCheckingTypeDate          = 1ULL << 3,            // date/time detection
    NSTextCheckingTypeAddress       = 1ULL << 4,            // address detection
    NSTextCheckingTypeLink          = 1ULL << 5,            // link detection
    NSTextCheckingTypeQuote         = 1ULL << 6,            // smart quotes
    NSTextCheckingTypeDash          = 1ULL << 7,            // smart dashes
    NSTextCheckingTypeReplacement   = 1ULL << 8,            // fixed replacements, such as copyright symbol for (c)
    NSTextCheckingTypeCorrection    = 1ULL << 9             // autocorrection
};
typedef uint64_t NSTextCheckingType;    // a single type

enum {
    NSTextCheckingAllSystemTypes    = 0xffffffffULL,        // the first 32 types are reserved
    NSTextCheckingAllCustomTypes    = 0xffffffffULL << 32,  // clients may use the remainder for their own purposes
    NSTextCheckingAllTypes          = (NSTextCheckingAllSystemTypes | NSTextCheckingAllCustomTypes)
};
typedef uint64_t NSTextCheckingTypes;   // a combination of types

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSTextCheckingResult : NSObject <NSCopying, NSCoding>

/* Mandatory properties, used with all types of results. */
@property (readonly) NSTextCheckingType resultType;
@property (readonly) NSRange range;

@end

@interface NSTextCheckingResult (NSTextCheckingResultOptional)

/* Optional properties, used with certain types of results. */
@property (readonly) NSOrthography *orthography;
@property (readonly) NSArray *grammarDetails;
@property (readonly) NSDate *date;
@property (readonly) NSTimeZone *timeZone;
@property (readonly) NSTimeInterval duration;
@property (readonly) NSDictionary *addressComponents;
@property (readonly) NSURL *URL;
@property (readonly) NSString *replacementString;

@end

/* Keys for address components. */
FOUNDATION_EXPORT NSString * const NSTextCheckingNameKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingJobTitleKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingOrganizationKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingStreetKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingCityKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingStateKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingZIPKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingCountryKey;
FOUNDATION_EXPORT NSString * const NSTextCheckingPhoneKey;


@interface NSTextCheckingResult (NSTextCheckingResultCreation)

/* Methods for creating instances of the various types of results. */
+ (NSTextCheckingResult *)orthographyCheckingResultWithRange:(NSRange)range orthography:(NSOrthography *)orthography;
+ (NSTextCheckingResult *)spellCheckingResultWithRange:(NSRange)range;
+ (NSTextCheckingResult *)grammarCheckingResultWithRange:(NSRange)range details:(NSArray *)details;
+ (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date;
+ (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date timeZone:(NSTimeZone *)timeZone duration:(NSTimeInterval)duration;
+ (NSTextCheckingResult *)addressCheckingResultWithRange:(NSRange)range components:(NSDictionary *)components;
+ (NSTextCheckingResult *)linkCheckingResultWithRange:(NSRange)range URL:(NSURL *)url;
+ (NSTextCheckingResult *)quoteCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)dashCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)replacementCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;

@end

#endif
