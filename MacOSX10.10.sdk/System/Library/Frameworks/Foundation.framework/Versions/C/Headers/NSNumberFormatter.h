/*	NSNumberFormatter.h
	Copyright (c) 1996-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFNumberFormatter.h>

@class NSLocale, NSError, NSMutableDictionary, NSRecursiveLock;

typedef NS_ENUM(NSUInteger, NSNumberFormatterBehavior) {
    NSNumberFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSNumberFormatterBehavior10_0 = 1000,
#endif
    NSNumberFormatterBehavior10_4 = 1040,
};

@interface NSNumberFormatter : NSFormatter {
@private
    NSMutableDictionary	*_attributes;
    __strong CFNumberFormatterRef _formatter;
    NSUInteger _counter;
    NSNumberFormatterBehavior _behavior;
    NSRecursiveLock *_lock;
    unsigned long _stateBitMask; // this is for NSUnitFormatter
    void *_reserved[9];
}

@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id *)obj forString:(NSString *)string range:(inout NSRange *)rangep error:(out NSError **)error;

// Even though NSNumberFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromNumber:(NSNumber *)number;
- (NSNumber *)numberFromString:(NSString *)string;

typedef NS_ENUM(NSUInteger, NSNumberFormatterStyle) {
    NSNumberFormatterNoStyle = kCFNumberFormatterNoStyle,
    NSNumberFormatterDecimalStyle = kCFNumberFormatterDecimalStyle,
    NSNumberFormatterCurrencyStyle = kCFNumberFormatterCurrencyStyle,
    NSNumberFormatterPercentStyle = kCFNumberFormatterPercentStyle,
    NSNumberFormatterScientificStyle = kCFNumberFormatterScientificStyle,
    NSNumberFormatterSpellOutStyle = kCFNumberFormatterSpellOutStyle,
};

+ (NSString *)localizedStringFromNumber:(NSNumber *)num numberStyle:(NSNumberFormatterStyle)nstyle NS_AVAILABLE(10_6, 4_0);

// Attributes of an NSNumberFormatter

+ (NSNumberFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSNumberFormatterBehavior)behavior;

@property NSNumberFormatterStyle numberStyle;
@property (copy) NSLocale *locale;
@property BOOL generatesDecimalNumbers;
@property NSNumberFormatterBehavior formatterBehavior;

@property (copy) NSString *negativeFormat;
@property (copy) NSDictionary *textAttributesForNegativeValues;
@property (copy) NSString *positiveFormat;
@property (copy) NSDictionary *textAttributesForPositiveValues;
@property BOOL allowsFloats;
@property (copy) NSString *decimalSeparator;
@property BOOL alwaysShowsDecimalSeparator;
@property (copy) NSString *currencyDecimalSeparator;
@property BOOL usesGroupingSeparator;
@property (copy) NSString *groupingSeparator;

@property (copy) NSString *zeroSymbol;
@property (copy) NSDictionary *textAttributesForZero;
@property (copy) NSString *nilSymbol;
@property (copy) NSDictionary *textAttributesForNil;
@property (copy) NSString *notANumberSymbol;
@property (copy) NSDictionary *textAttributesForNotANumber;
@property (copy) NSString *positiveInfinitySymbol;
@property (copy) NSDictionary *textAttributesForPositiveInfinity;
@property (copy) NSString *negativeInfinitySymbol;
@property (copy) NSDictionary *textAttributesForNegativeInfinity;

@property (copy) NSString *positivePrefix;
@property (copy) NSString *positiveSuffix;
@property (copy) NSString *negativePrefix;
@property (copy) NSString *negativeSuffix;
@property (copy) NSString *currencyCode;
@property (copy) NSString *currencySymbol;
@property (copy) NSString *internationalCurrencySymbol;
@property (copy) NSString *percentSymbol;
@property (copy) NSString *perMillSymbol;
@property (copy) NSString *minusSign;
@property (copy) NSString *plusSign;
@property (copy) NSString *exponentSymbol;

@property NSUInteger groupingSize;
@property NSUInteger secondaryGroupingSize;
@property (copy) NSNumber *multiplier;
@property NSUInteger formatWidth;
@property (copy) NSString *paddingCharacter;


typedef NS_ENUM(NSUInteger, NSNumberFormatterPadPosition) {
    NSNumberFormatterPadBeforePrefix = kCFNumberFormatterPadBeforePrefix,
    NSNumberFormatterPadAfterPrefix = kCFNumberFormatterPadAfterPrefix,
    NSNumberFormatterPadBeforeSuffix = kCFNumberFormatterPadBeforeSuffix,
    NSNumberFormatterPadAfterSuffix = kCFNumberFormatterPadAfterSuffix
};

typedef NS_ENUM(NSUInteger, NSNumberFormatterRoundingMode) {
    NSNumberFormatterRoundCeiling = kCFNumberFormatterRoundCeiling,
    NSNumberFormatterRoundFloor = kCFNumberFormatterRoundFloor,
    NSNumberFormatterRoundDown = kCFNumberFormatterRoundDown,
    NSNumberFormatterRoundUp = kCFNumberFormatterRoundUp,
    NSNumberFormatterRoundHalfEven = kCFNumberFormatterRoundHalfEven,
    NSNumberFormatterRoundHalfDown = kCFNumberFormatterRoundHalfDown,
    NSNumberFormatterRoundHalfUp = kCFNumberFormatterRoundHalfUp
};

@property NSNumberFormatterPadPosition paddingPosition;
@property NSNumberFormatterRoundingMode roundingMode;
@property (copy) NSNumber *roundingIncrement;
@property NSUInteger minimumIntegerDigits;
@property NSUInteger maximumIntegerDigits;
@property NSUInteger minimumFractionDigits;
@property NSUInteger maximumFractionDigits;
@property (copy) NSNumber *minimum;
@property (copy) NSNumber *maximum;
@property (copy) NSString *currencyGroupingSeparator NS_AVAILABLE(10_5, 2_0);
@property (getter=isLenient) BOOL lenient NS_AVAILABLE(10_5, 2_0);
@property BOOL usesSignificantDigits NS_AVAILABLE(10_5, 2_0);
@property NSUInteger minimumSignificantDigits NS_AVAILABLE(10_5, 2_0);
@property NSUInteger maximumSignificantDigits NS_AVAILABLE(10_5, 2_0);
@property (getter=isPartialStringValidationEnabled) BOOL partialStringValidationEnabled NS_AVAILABLE(10_5, 2_0);

@end

@class NSDecimalNumberHandler;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSNumberFormatter (NSNumberFormatterCompatibility)

@property BOOL hasThousandSeparators;
@property (copy) NSString *thousandSeparator;

@property BOOL localizesFormat;

@property (copy) NSString *format;

@property (copy) NSAttributedString *attributedStringForZero;
@property (copy) NSAttributedString *attributedStringForNil;
@property (copy) NSAttributedString *attributedStringForNotANumber;

@property (copy) NSDecimalNumberHandler *roundingBehavior;

@end
#endif

