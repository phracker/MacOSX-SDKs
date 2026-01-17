/*	NSNumberFormatter.h
	Copyright (c) 1996-2007, Apple Inc. All rights reserved.
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

- (id)init;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id *)obj forString:(NSString *)string range:(inout NSRange *)rangep error:(out NSError **)error;

// Even though NSNumberFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromNumber:(NSNumber *)number;
- (NSNumber *)numberFromString:(NSString *)string;

#endif

// Attributes of an NSNumberFormatter

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

- (NSNumberFormatterStyle)numberStyle;
- (void)setNumberStyle:(NSNumberFormatterStyle)style;

- (NSLocale *)locale;
- (void)setLocale:(NSLocale *)locale;

- (BOOL)generatesDecimalNumbers;
- (void)setGeneratesDecimalNumbers:(BOOL)b;

enum {
    NSNumberFormatterBehaviorDefault = 0,
    NSNumberFormatterBehavior10_0 = 1000,
    NSNumberFormatterBehavior10_4 = 1040,
};
typedef NSUInteger NSNumberFormatterBehavior;

- (NSNumberFormatterBehavior)formatterBehavior;
- (void)setFormatterBehavior:(NSNumberFormatterBehavior)behavior;

+ (NSNumberFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSNumberFormatterBehavior)behavior;

#endif

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

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (BOOL)alwaysShowsDecimalSeparator;
- (void)setAlwaysShowsDecimalSeparator:(BOOL)b;

- (NSString *)currencyDecimalSeparator;
- (void)setCurrencyDecimalSeparator:(NSString *)string;

- (BOOL)usesGroupingSeparator;
- (void)setUsesGroupingSeparator:(BOOL)b;

- (NSString *)groupingSeparator;
- (void)setGroupingSeparator:(NSString *)string;


- (NSString *)zeroSymbol;
- (void)setZeroSymbol:(NSString *)string;

- (NSDictionary *)textAttributesForZero;
- (void)setTextAttributesForZero:(NSDictionary *)newAttributes;

- (NSString *)nilSymbol;
- (void)setNilSymbol:(NSString *)string;

- (NSDictionary *)textAttributesForNil;
- (void)setTextAttributesForNil:(NSDictionary *)newAttributes;

- (NSString *)notANumberSymbol;
- (void)setNotANumberSymbol:(NSString *)string;

- (NSDictionary *)textAttributesForNotANumber;
- (void)setTextAttributesForNotANumber:(NSDictionary *)newAttributes;

- (NSString *)positiveInfinitySymbol;
- (void)setPositiveInfinitySymbol:(NSString *)string;

- (NSDictionary *)textAttributesForPositiveInfinity;
- (void)setTextAttributesForPositiveInfinity:(NSDictionary *)newAttributes;

- (NSString *)negativeInfinitySymbol;
- (void)setNegativeInfinitySymbol:(NSString *)string;

- (NSDictionary *)textAttributesForNegativeInfinity;
- (void)setTextAttributesForNegativeInfinity:(NSDictionary *)newAttributes;


- (NSString *)positivePrefix;
- (void)setPositivePrefix:(NSString *)string;

- (NSString *)positiveSuffix;
- (void)setPositiveSuffix:(NSString *)string;

- (NSString *)negativePrefix;
- (void)setNegativePrefix:(NSString *)string;

- (NSString *)negativeSuffix;
- (void)setNegativeSuffix:(NSString *)string;

- (NSString *)currencyCode;
- (void)setCurrencyCode:(NSString *)string;

- (NSString *)currencySymbol;
- (void)setCurrencySymbol:(NSString *)string;

- (NSString *)internationalCurrencySymbol;
- (void)setInternationalCurrencySymbol:(NSString *)string;

- (NSString *)percentSymbol;
- (void)setPercentSymbol:(NSString *)string;

- (NSString *)perMillSymbol;
- (void)setPerMillSymbol:(NSString *)string;

- (NSString *)minusSign;
- (void)setMinusSign:(NSString *)string;

- (NSString *)plusSign;
- (void)setPlusSign:(NSString *)string;

- (NSString *)exponentSymbol;
- (void)setExponentSymbol:(NSString *)string;


- (NSUInteger)groupingSize;
- (void)setGroupingSize:(NSUInteger)number;

- (NSUInteger)secondaryGroupingSize;
- (void)setSecondaryGroupingSize:(NSUInteger)number;

- (NSNumber *)multiplier;
- (void)setMultiplier:(NSNumber *)number;

- (NSUInteger)formatWidth;
- (void)setFormatWidth:(NSUInteger)number;

- (NSString *)paddingCharacter;
- (void)setPaddingCharacter:(NSString *)string;

enum {
    NSNumberFormatterPadBeforePrefix = kCFNumberFormatterPadBeforePrefix,
    NSNumberFormatterPadAfterPrefix = kCFNumberFormatterPadAfterPrefix,
    NSNumberFormatterPadBeforeSuffix = kCFNumberFormatterPadBeforeSuffix,
    NSNumberFormatterPadAfterSuffix = kCFNumberFormatterPadAfterSuffix
};
typedef NSUInteger NSNumberFormatterPadPosition;

- (NSNumberFormatterPadPosition)paddingPosition;
- (void)setPaddingPosition:(NSNumberFormatterPadPosition)position;

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

- (NSNumberFormatterRoundingMode)roundingMode;
- (void)setRoundingMode:(NSNumberFormatterRoundingMode)mode;

- (NSNumber *)roundingIncrement;
- (void)setRoundingIncrement:(NSNumber *)number;

- (NSUInteger)minimumIntegerDigits;
- (void)setMinimumIntegerDigits:(NSUInteger)number;

- (NSUInteger)maximumIntegerDigits;
- (void)setMaximumIntegerDigits:(NSUInteger)number;

- (NSUInteger)minimumFractionDigits;
- (void)setMinimumFractionDigits:(NSUInteger)number;

- (NSUInteger)maximumFractionDigits;
- (void)setMaximumFractionDigits:(NSUInteger)number;


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

#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_4

- (NSDecimalNumber *)minimum;
- (void)setMinimum:(NSDecimalNumber *)aMinimum;
- (NSDecimalNumber *)maximum;
- (void)setMaximum:(NSDecimalNumber *)aMaximum;

#endif

@end

