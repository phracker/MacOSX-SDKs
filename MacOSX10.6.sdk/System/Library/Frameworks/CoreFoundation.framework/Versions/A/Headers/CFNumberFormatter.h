/*	CFNumberFormatter.h
	Copyright (c) 2003-2009, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFNUMBERFORMATTER__)
#define __COREFOUNDATION_CFNUMBERFORMATTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFLocale.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

CF_EXTERN_C_BEGIN

typedef struct __CFNumberFormatter *CFNumberFormatterRef;

// CFNumberFormatters are not thread-safe.  Do not use one from multiple threads!

CF_EXPORT
CFTypeID CFNumberFormatterGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

enum {	// number format styles
	kCFNumberFormatterNoStyle = 0,
	kCFNumberFormatterDecimalStyle = 1,
	kCFNumberFormatterCurrencyStyle = 2,
	kCFNumberFormatterPercentStyle = 3,
	kCFNumberFormatterScientificStyle = 4,
	kCFNumberFormatterSpellOutStyle = 5
};
typedef CFIndex CFNumberFormatterStyle;


CF_EXPORT
CFNumberFormatterRef CFNumberFormatterCreate(CFAllocatorRef allocator, CFLocaleRef locale, CFNumberFormatterStyle style) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns a CFNumberFormatter, localized to the given locale, which
	// will format numbers to the given style.

CF_EXPORT
CFLocaleRef CFNumberFormatterGetLocale(CFNumberFormatterRef formatter) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CF_EXPORT
CFNumberFormatterStyle CFNumberFormatterGetStyle(CFNumberFormatterRef formatter) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Get the properties with which the number formatter was created.

CF_EXPORT
CFStringRef CFNumberFormatterGetFormat(CFNumberFormatterRef formatter) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CF_EXPORT
void CFNumberFormatterSetFormat(CFNumberFormatterRef formatter, CFStringRef formatString) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Set the format description string of the number formatter.  This
	// overrides the style settings.  The format of the format string
	// is as defined by the ICU library, and is similar to that found
	// in Microsoft Excel and NSNumberFormatter (and Java I believe).
	// The number formatter starts with a default format string defined
	// by the style argument with which it was created.


CF_EXPORT
CFStringRef CFNumberFormatterCreateStringWithNumber(CFAllocatorRef allocator, CFNumberFormatterRef formatter, CFNumberRef number) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CF_EXPORT
CFStringRef CFNumberFormatterCreateStringWithValue(CFAllocatorRef allocator, CFNumberFormatterRef formatter, CFNumberType numberType, const void *valuePtr) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Create a string representation of the given number or value
	// using the current state of the number formatter.


enum {
    kCFNumberFormatterParseIntegersOnly = 1	/* only parse integers */
};
typedef CFOptionFlags CFNumberFormatterOptionFlags;

CF_EXPORT
CFNumberRef CFNumberFormatterCreateNumberFromString(CFAllocatorRef allocator, CFNumberFormatterRef formatter, CFStringRef string, CFRange *rangep, CFOptionFlags options) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CF_EXPORT
Boolean CFNumberFormatterGetValueFromString(CFNumberFormatterRef formatter, CFStringRef string, CFRange *rangep, CFNumberType numberType, void *valuePtr) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Parse a string representation of a number using the current state
	// of the number formatter.  The range parameter specifies the range
	// of the string in which the parsing should occur in input, and on
	// output indicates the extent that was used; this parameter can
	// be NULL, in which case the whole string may be used.  The
	// return value indicates whether some number was computed and
	// (if valuePtr is not NULL) stored at the location specified by
	// valuePtr.  The numberType indicates the type of value pointed
	// to by valuePtr.


CF_EXPORT
void CFNumberFormatterSetProperty(CFNumberFormatterRef formatter, CFStringRef key, CFTypeRef value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CF_EXPORT
CFTypeRef CFNumberFormatterCopyProperty(CFNumberFormatterRef formatter, CFStringRef key) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Set and get various properties of the number formatter, the set of
	// which may be expanded in the future.

CF_EXPORT const CFStringRef kCFNumberFormatterCurrencyCode AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterCurrencyDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; // CFString
CF_EXPORT const CFStringRef kCFNumberFormatterAlwaysShowDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; // CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterUseGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterPercentSymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterZeroSymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterNaNSymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterInfinitySymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterMinusSign AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterPlusSign AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterCurrencySymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterExponentSymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterMinIntegerDigits AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMaxIntegerDigits AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMinFractionDigits AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMaxFractionDigits AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterGroupingSize AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterSecondaryGroupingSize AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterRoundingMode AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterRoundingIncrement AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterFormatWidth AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterPaddingPosition AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterPaddingCharacter AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterDefaultFormat AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterMultiplier AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterPositivePrefix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterPositiveSuffix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterNegativePrefix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterNegativeSuffix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterPerMillSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterInternationalCurrencySymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // CFString
CF_EXPORT const CFStringRef kCFNumberFormatterCurrencyGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // CFString
CF_EXPORT const CFStringRef kCFNumberFormatterIsLenient AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;		// CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterUseSignificantDigits AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterMinSignificantDigits AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMaxSignificantDigits AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// CFNumber

enum {
    kCFNumberFormatterRoundCeiling = 0,
    kCFNumberFormatterRoundFloor = 1,
    kCFNumberFormatterRoundDown = 2,
    kCFNumberFormatterRoundUp = 3,
    kCFNumberFormatterRoundHalfEven = 4,
    kCFNumberFormatterRoundHalfDown = 5,
    kCFNumberFormatterRoundHalfUp = 6
};
typedef CFIndex CFNumberFormatterRoundingMode;

enum {
    kCFNumberFormatterPadBeforePrefix = 0,
    kCFNumberFormatterPadAfterPrefix = 1,
    kCFNumberFormatterPadBeforeSuffix = 2,
    kCFNumberFormatterPadAfterSuffix = 3
};
typedef CFIndex CFNumberFormatterPadPosition;


CF_EXPORT
Boolean CFNumberFormatterGetDecimalInfoForCurrencyCode(CFStringRef currencyCode, int32_t *defaultFractionDigits, double *roundingIncrement) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns the number of fraction digits that should be displayed, and
	// the rounding increment (or 0.0 if no rounding is done by the currency)
	// for the given currency.  Returns false if the currency code is unknown
	// or the information is not available.
	// Not localized because these are properties of the currency.

CF_EXTERN_C_END

#endif

#endif /* ! __COREFOUNDATION_CFNUMBERFORMATTER__ */

