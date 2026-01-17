/*	NSNumberFormatter.h
	Copyright (c) 1996-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFNumberFormatter.h>

@class NSLocale, NSError, NSMutableDictionary, NSRecursiveLock, NSString, NSCache;

NS_ASSUME_NONNULL_BEGIN

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
    NSInteger _cacheGeneration;
    void *_reserved[8];
}

@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

// Even though NSNumberFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (nullable NSString *)stringFromNumber:(NSNumber *)number;
- (nullable NSNumber *)numberFromString:(NSString *)string;

typedef NS_ENUM(NSUInteger, NSNumberFormatterStyle) {
    NSNumberFormatterNoStyle = kCFNumberFormatterNoStyle,
    NSNumberFormatterDecimalStyle = kCFNumberFormatterDecimalStyle,
    NSNumberFormatterCurrencyStyle = kCFNumberFormatterCurrencyStyle,
    NSNumberFormatterPercentStyle = kCFNumberFormatterPercentStyle,
    NSNumberFormatterScientificStyle = kCFNumberFormatterScientificStyle,
    NSNumberFormatterSpellOutStyle = kCFNumberFormatterSpellOutStyle,
    NSNumberFormatterOrdinalStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterOrdinalStyle,
    NSNumberFormatterCurrencyISOCodeStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterCurrencyISOCodeStyle,
    NSNumberFormatterCurrencyPluralStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterCurrencyPluralStyle,
    NSNumberFormatterCurrencyAccountingStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterCurrencyAccountingStyle,
};

+ (NSString *)localizedStringFromNumber:(NSNumber *)num numberStyle:(NSNumberFormatterStyle)nstyle NS_AVAILABLE(10_6, 4_0);

// Attributes of an NSNumberFormatter

+ (NSNumberFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSNumberFormatterBehavior)behavior;

@property NSNumberFormatterStyle numberStyle;
@property (null_resettable, copy) NSLocale *locale;
@property BOOL generatesDecimalNumbers;
@property NSNumberFormatterBehavior formatterBehavior;

@property (null_resettable, copy) NSString *negativeFormat;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNegativeValues;
@property (null_resettable, copy) NSString *positiveFormat;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForPositiveValues;
@property BOOL allowsFloats;
@property (null_resettable, copy) NSString *decimalSeparator;
@property BOOL alwaysShowsDecimalSeparator;
@property (null_resettable, copy) NSString *currencyDecimalSeparator;
@property BOOL usesGroupingSeparator;
@property (null_resettable, copy) NSString *groupingSeparator;

@property (nullable, copy) NSString *zeroSymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForZero;
@property (copy) NSString *nilSymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNil;
@property (null_resettable, copy) NSString *notANumberSymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNotANumber;
@property (copy) NSString *positiveInfinitySymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForPositiveInfinity;
@property (copy) NSString *negativeInfinitySymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNegativeInfinity;

@property (null_resettable, copy) NSString *positivePrefix;
@property (null_resettable, copy) NSString *positiveSuffix;
@property (null_resettable, copy) NSString *negativePrefix;
@property (null_resettable, copy) NSString *negativeSuffix;
@property (null_resettable, copy) NSString *currencyCode;
@property (null_resettable, copy) NSString *currencySymbol;
@property (null_resettable, copy) NSString *internationalCurrencySymbol;
@property (null_resettable, copy) NSString *percentSymbol;
@property (null_resettable, copy) NSString *perMillSymbol;
@property (null_resettable, copy) NSString *minusSign;
@property (null_resettable, copy) NSString *plusSign;
@property (null_resettable, copy) NSString *exponentSymbol;

@property NSUInteger groupingSize;
@property NSUInteger secondaryGroupingSize;
@property (nullable, copy) NSNumber *multiplier;
@property NSUInteger formatWidth;
@property (null_resettable, copy) NSString *paddingCharacter;


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
@property (null_resettable, copy) NSNumber *roundingIncrement;
@property NSUInteger minimumIntegerDigits;
@property NSUInteger maximumIntegerDigits;
@property NSUInteger minimumFractionDigits;
@property NSUInteger maximumFractionDigits;
@property (nullable, copy) NSNumber *minimum;
@property (nullable, copy) NSNumber *maximum;
@property (null_resettable, copy) NSString *currencyGroupingSeparator NS_AVAILABLE(10_5, 2_0);
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
@property (null_resettable, copy) NSString *thousandSeparator;

@property BOOL localizesFormat;

@property (copy) NSString *format;

@property (copy) NSAttributedString *attributedStringForZero;
@property (copy) NSAttributedString *attributedStringForNil;
@property (copy) NSAttributedString *attributedStringForNotANumber;

@property (copy) NSDecimalNumberHandler *roundingBehavior;

@end
#endif

NS_ASSUME_NONNULL_END
