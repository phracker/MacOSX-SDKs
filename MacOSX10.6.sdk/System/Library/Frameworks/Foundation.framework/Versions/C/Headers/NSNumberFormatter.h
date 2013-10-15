/*	NSNumberFormatter.h
	Copyright (c) 1996-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFNumberFormatter.h>

@class NSLocale, NSError, NSMutableDictionary;

@interface NSNumberFormatter : NSFormatter {
@private
    NSMutableDictionary	*_attributes;
    __strong CFNumberFormatterRef _formatter;
    NSUInteger _counter;
    void *_reserved[12];
}

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id *)obj forString:(NSString *)string range:(inout NSRange *)rangep error:(out NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// Even though NSNumberFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromNumber:(NSNumber *)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSNumber *)numberFromString:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

enum {
    NSNumberFormatterNoStyle = kCFNumberFormatterNoStyle,
    NSNumberFormatterDecimalStyle = kCFNumberFormatterDecimalStyle,
    NSNumberFormatterCurrencyStyle = kCFNumberFormatterCurrencyStyle,
    NSNumberFormatterPercentStyle = kCFNumberFormatterPercentStyle,
    NSNumberFormatterScientificStyle = kCFNumberFormatterScientificStyle,
    NSNumberFormatterSpellOutStyle = kCFNumberFormatterSpellOutStyle
};
typedef NSUInteger NSNumberFormatterStyle;

enum {
    NSNumberFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSNumberFormatterBehavior10_0 = 1000,
#endif
    NSNumberFormatterBehavior10_4 = 1040,
};
typedef NSUInteger NSNumberFormatterBehavior;

#endif

+ (NSString *)localizedStringFromNumber:(NSNumber *)num numberStyle:(NSNumberFormatterStyle)nstyle AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Attributes of an NSNumberFormatter

- (NSNumberFormatterStyle)numberStyle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setNumberStyle:(NSNumberFormatterStyle)style AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSLocale *)locale AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setLocale:(NSLocale *)locale AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (BOOL)generatesDecimalNumbers AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setGeneratesDecimalNumbers:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSNumberFormatterBehavior)formatterBehavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setFormatterBehavior:(NSNumberFormatterBehavior)behavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

+ (NSNumberFormatterBehavior)defaultFormatterBehavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
+ (void)setDefaultFormatterBehavior:(NSNumberFormatterBehavior)behavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)negativeFormat;
- (void)setNegativeFormat:(NSString *)format;

- (NSDictionary *)textAttributesForNegativeValues;
- (void)setTextAttributesForNegativeValues:(NSDictionary *)newAttributes;

- (NSString *)positiveFormat;
- (void)setPositiveFormat:(NSString *)format;

- (NSDictionary *)textAttributesForPositiveValues;
- (void)setTextAttributesForPositiveValues:(NSDictionary *)newAttributes;

- (BOOL)allowsFloats;
- (void)setAllowsFloats:(BOOL)flag;

- (NSString *)decimalSeparator;
- (void)setDecimalSeparator:(NSString *)string;

- (BOOL)alwaysShowsDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setAlwaysShowsDecimalSeparator:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)currencyDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setCurrencyDecimalSeparator:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (BOOL)usesGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setUsesGroupingSeparator:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)groupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setGroupingSeparator:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


- (NSString *)zeroSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setZeroSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDictionary *)textAttributesForZero AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTextAttributesForZero:(NSDictionary *)newAttributes AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)nilSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setNilSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDictionary *)textAttributesForNil AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTextAttributesForNil:(NSDictionary *)newAttributes AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)notANumberSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setNotANumberSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDictionary *)textAttributesForNotANumber AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTextAttributesForNotANumber:(NSDictionary *)newAttributes AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)positiveInfinitySymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPositiveInfinitySymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDictionary *)textAttributesForPositiveInfinity AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTextAttributesForPositiveInfinity:(NSDictionary *)newAttributes AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)negativeInfinitySymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setNegativeInfinitySymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDictionary *)textAttributesForNegativeInfinity AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTextAttributesForNegativeInfinity:(NSDictionary *)newAttributes AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


- (NSString *)positivePrefix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPositivePrefix:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)positiveSuffix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPositiveSuffix:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)negativePrefix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setNegativePrefix:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)negativeSuffix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setNegativeSuffix:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)currencyCode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setCurrencyCode:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)currencySymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setCurrencySymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)internationalCurrencySymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setInternationalCurrencySymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)percentSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPercentSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)perMillSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPerMillSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)minusSign AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMinusSign:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)plusSign AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPlusSign:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)exponentSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setExponentSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


- (NSUInteger)groupingSize AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setGroupingSize:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSUInteger)secondaryGroupingSize AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setSecondaryGroupingSize:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSNumber *)multiplier AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMultiplier:(NSNumber *)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSUInteger)formatWidth AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setFormatWidth:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)paddingCharacter AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPaddingCharacter:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

enum {
    NSNumberFormatterPadBeforePrefix = kCFNumberFormatterPadBeforePrefix,
    NSNumberFormatterPadAfterPrefix = kCFNumberFormatterPadAfterPrefix,
    NSNumberFormatterPadBeforeSuffix = kCFNumberFormatterPadBeforeSuffix,
    NSNumberFormatterPadAfterSuffix = kCFNumberFormatterPadAfterSuffix
};
typedef NSUInteger NSNumberFormatterPadPosition;

enum {
    NSNumberFormatterRoundCeiling = kCFNumberFormatterRoundCeiling,
    NSNumberFormatterRoundFloor = kCFNumberFormatterRoundFloor,
    NSNumberFormatterRoundDown = kCFNumberFormatterRoundDown,
    NSNumberFormatterRoundUp = kCFNumberFormatterRoundUp,
    NSNumberFormatterRoundHalfEven = kCFNumberFormatterRoundHalfEven,
    NSNumberFormatterRoundHalfDown = kCFNumberFormatterRoundHalfDown,
    NSNumberFormatterRoundHalfUp = kCFNumberFormatterRoundHalfUp
};
typedef NSUInteger NSNumberFormatterRoundingMode;

#endif

- (NSNumberFormatterPadPosition)paddingPosition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPaddingPosition:(NSNumberFormatterPadPosition)position AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSNumberFormatterRoundingMode)roundingMode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setRoundingMode:(NSNumberFormatterRoundingMode)mode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSNumber *)roundingIncrement AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setRoundingIncrement:(NSNumber *)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSUInteger)minimumIntegerDigits AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMinimumIntegerDigits:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSUInteger)maximumIntegerDigits AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMaximumIntegerDigits:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSUInteger)minimumFractionDigits AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMinimumFractionDigits:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSUInteger)maximumFractionDigits AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMaximumFractionDigits:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (NSNumber *)minimum;
- (void)setMinimum:(NSNumber *)number;

- (NSNumber *)maximum;
- (void)setMaximum:(NSNumber *)number;

#endif

- (NSString *)currencyGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setCurrencyGroupingSeparator:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (BOOL)isLenient AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setLenient:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (BOOL)usesSignificantDigits AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setUsesSignificantDigits:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSUInteger)minimumSignificantDigits AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setMinimumSignificantDigits:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSUInteger)maximumSignificantDigits AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setMaximumSignificantDigits:(NSUInteger)number AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (BOOL)isPartialStringValidationEnabled AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setPartialStringValidationEnabled:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@class NSDecimalNumberHandler;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSNumberFormatter (NSNumberFormatterCompatibility)

- (BOOL)hasThousandSeparators;
- (void)setHasThousandSeparators:(BOOL)flag;
- (NSString *)thousandSeparator;
- (void)setThousandSeparator:(NSString *)newSeparator;

- (BOOL)localizesFormat;
- (void)setLocalizesFormat:(BOOL)flag;

- (NSString *)format;
- (void)setFormat:(NSString *)string;

- (NSAttributedString *)attributedStringForZero;
- (void)setAttributedStringForZero:(NSAttributedString *)newAttributedString;
- (NSAttributedString *)attributedStringForNil;
- (void)setAttributedStringForNil:(NSAttributedString *)newAttributedString;
- (NSAttributedString *)attributedStringForNotANumber;
- (void)setAttributedStringForNotANumber:(NSAttributedString *)newAttributedString;

- (NSDecimalNumberHandler *)roundingBehavior;
- (void)setRoundingBehavior:(NSDecimalNumberHandler *)newRoundingBehavior;

#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_3

- (NSDecimalNumber *)minimum;
- (void)setMinimum:(NSDecimalNumber *)aMinimum;
- (NSDecimalNumber *)maximum;
- (void)setMaximum:(NSDecimalNumber *)aMaximum;

#endif

@end
#endif

