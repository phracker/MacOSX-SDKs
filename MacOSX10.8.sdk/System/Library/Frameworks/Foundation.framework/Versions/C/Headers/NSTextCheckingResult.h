/*	NSTextCheckingResult.h
	Copyright (c) 2008-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray, NSDictionary, NSDate, NSTimeZone, NSOrthography, NSURL, NSRegularExpression;

/* NSTextCheckingResult is a class used to describe items located by text checking.  Each of these objects represents something that has been found during checking--a misspelled word, a sentence with grammatical issues, a detected URL, a straight quote to be replaced with curly quotes, and so forth. */

typedef NS_OPTIONS(uint64_t, NSTextCheckingType) {    // a single type
    NSTextCheckingTypeOrthography           = 1ULL << 0,            // language identification
    NSTextCheckingTypeSpelling              = 1ULL << 1,            // spell checking
    NSTextCheckingTypeGrammar               = 1ULL << 2,            // grammar checking
    NSTextCheckingTypeDate                  = 1ULL << 3,            // date/time detection
    NSTextCheckingTypeAddress               = 1ULL << 4,            // address detection
    NSTextCheckingTypeLink                  = 1ULL << 5,            // link detection
    NSTextCheckingTypeQuote                 = 1ULL << 6,            // smart quotes
    NSTextCheckingTypeDash                  = 1ULL << 7,            // smart dashes
    NSTextCheckingTypeReplacement           = 1ULL << 8,            // fixed replacements, such as copyright symbol for (c)
    NSTextCheckingTypeCorrection            = 1ULL << 9,            // autocorrection
    NSTextCheckingTypeRegularExpression NS_ENUM_AVAILABLE(10_7, 4_0)  = 1ULL << 10,           // regular expression matches
    NSTextCheckingTypePhoneNumber NS_ENUM_AVAILABLE(10_7, 4_0)        = 1ULL << 11,           // phone number detection
    NSTextCheckingTypeTransitInformation NS_ENUM_AVAILABLE(10_7, 4_0) = 1ULL << 12            // transit (e.g. flight) info detection
};

typedef NS_OPTIONS(uint64_t, NSTextCheckingTypes) {   // a combination of types
    NSTextCheckingAllSystemTypes    = 0xffffffffULL,        // the first 32 types are reserved
    NSTextCheckingAllCustomTypes    = 0xffffffffULL << 32,  // clients may use the remainder for their own purposes
    NSTextCheckingAllTypes          = (NSTextCheckingAllSystemTypes | NSTextCheckingAllCustomTypes)
};

NS_CLASS_AVAILABLE(10_6, 4_0)
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
@property (readonly) NSDictionary *components NS_AVAILABLE(10_7, 4_0);
@property (readonly) NSURL *URL;
@property (readonly) NSString *replacementString;
@property (readonly) NSRegularExpression *regularExpression NS_AVAILABLE(10_7, 4_0);
@property (readonly) NSString *phoneNumber NS_AVAILABLE(10_7, 4_0);

@property (readonly) NSDictionary *addressComponents;

/* A result must have at least one range, but may optionally have more (for example, to represent regular expression capture groups).  The range at index 0 always matches the range property.  Additional ranges, if any, will have indexes from 1 to numberOfRanges-1. */
@property (readonly) NSUInteger numberOfRanges NS_AVAILABLE(10_7, 4_0);
- (NSRange)rangeAtIndex:(NSUInteger)idx NS_AVAILABLE(10_7, 4_0);
- (NSTextCheckingResult *)resultByAdjustingRangesWithOffset:(NSInteger)offset NS_AVAILABLE(10_7, 5_0);

@end



/* Keys for address components. */
FOUNDATION_EXPORT NSString * const NSTextCheckingNameKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingJobTitleKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingOrganizationKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingStreetKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingCityKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingStateKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingZIPKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingCountryKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingPhoneKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingAirlineKey NS_AVAILABLE(10_7, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingFlightKey NS_AVAILABLE(10_7, 4_0);


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
+ (NSTextCheckingResult *)regularExpressionCheckingResultWithRanges:(NSRangePointer)ranges count:(NSUInteger)count regularExpression:(NSRegularExpression *)regularExpression   NS_AVAILABLE(10_7, 4_0);
+ (NSTextCheckingResult *)phoneNumberCheckingResultWithRange:(NSRange)range phoneNumber:(NSString *)phoneNumber             NS_AVAILABLE(10_7, 4_0);
+ (NSTextCheckingResult *)transitInformationCheckingResultWithRange:(NSRange)range components:(NSDictionary *)components    NS_AVAILABLE(10_7, 4_0);

@end

