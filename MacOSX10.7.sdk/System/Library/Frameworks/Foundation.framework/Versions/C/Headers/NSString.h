/*	NSString.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

typedef unsigned short unichar;

#import <limits.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <stdarg.h>

@class NSData, NSArray, NSDictionary, NSCharacterSet, NSURL, NSError, NSLocale;

FOUNDATION_EXPORT NSString * const NSParseErrorException; // raised by -propertyList

#define NSMaximumStringLength	(INT_MAX-1)

/* These options apply to the various search/find and comparison methods (except where noted).
*/
enum {
    NSCaseInsensitiveSearch = 1,
    NSLiteralSearch = 2,		/* Exact character-by-character equivalence */
    NSBackwardsSearch = 4,		/* Search from end of source string */
    NSAnchoredSearch = 8,		/* Search is limited to start (or end, if NSBackwardsSearch) of source string */
    NSNumericSearch = 64		/* Added in 10.2; Numbers within strings are compared using numeric value, that is, Foo2.txt < Foo7.txt < Foo25.txt; only applies to compare methods, not find */
#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ,
    NSDiacriticInsensitiveSearch = 128, /* If specified, ignores diacritics (o-umlaut == o) */
    NSWidthInsensitiveSearch = 256, /* If specified, ignores width differences ('a' == UFF41) */
    NSForcedOrderingSearch = 512 /* If specified, comparisons are forced to return either NSOrderedAscending or NSOrderedDescending if the strings are equivalent but not strictly equal, for stability when sorting (e.g. "aaa" > "AAA" with NSCaseInsensitiveSearch specified) */
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */
#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_3_2 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ,
    NSRegularExpressionSearch = 1024    /* Applies to rangeOfString:..., stringByReplacingOccurrencesOfString:..., and replaceOccurrencesOfString:... methods only; the search string is treated as an ICU-compatible regular expression; if set, no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch */
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7 || __IPHONE_3_2 <= __IPHONE_OS_VERSION_MAX_ALLOWED */
};
typedef NSUInteger NSStringCompareOptions;

/* Note that in addition to the values explicitly listed below, NSStringEncoding supports encodings provided by CFString.
See CFStringEncodingExt.h for a list of these encodings.
See CFString.h for functions which convert between NSStringEncoding and CFStringEncoding.
*/
enum {
    NSASCIIStringEncoding = 1,		/* 0..127 only */
    NSNEXTSTEPStringEncoding = 2,
    NSJapaneseEUCStringEncoding = 3,
    NSUTF8StringEncoding = 4,
    NSISOLatin1StringEncoding = 5,
    NSSymbolStringEncoding = 6,
    NSNonLossyASCIIStringEncoding = 7,
    NSShiftJISStringEncoding = 8,          /* kCFStringEncodingDOSJapanese */
    NSISOLatin2StringEncoding = 9,
    NSUnicodeStringEncoding = 10,
    NSWindowsCP1251StringEncoding = 11,    /* Cyrillic; same as AdobeStandardCyrillic */
    NSWindowsCP1252StringEncoding = 12,    /* WinLatin1 */
    NSWindowsCP1253StringEncoding = 13,    /* Greek */
    NSWindowsCP1254StringEncoding = 14,    /* Turkish */
    NSWindowsCP1250StringEncoding = 15,    /* WinLatin2 */
    NSISO2022JPStringEncoding = 21,        /* ISO 2022 Japanese encoding for e-mail */
    NSMacOSRomanStringEncoding = 30,

    NSUTF16StringEncoding = NSUnicodeStringEncoding,      /* An alias for NSUnicodeStringEncoding */

    NSUTF16BigEndianStringEncoding = 0x90000100,          /* NSUTF16StringEncoding encoding with explicit endianness specified */
    NSUTF16LittleEndianStringEncoding = 0x94000100,       /* NSUTF16StringEncoding encoding with explicit endianness specified */

    NSUTF32StringEncoding = 0x8c000100,                   
    NSUTF32BigEndianStringEncoding = 0x98000100,          /* NSUTF32StringEncoding encoding with explicit endianness specified */
    NSUTF32LittleEndianStringEncoding = 0x9c000100        /* NSUTF32StringEncoding encoding with explicit endianness specified */
};
typedef NSUInteger NSStringEncoding;

enum {
    NSStringEncodingConversionAllowLossy = 1,
    NSStringEncodingConversionExternalRepresentation = 2
};
typedef NSUInteger NSStringEncodingConversionOptions;

FOUNDATION_EXPORT NSString * const NSCharacterConversionException;


@interface NSString : NSObject <NSCopying, NSMutableCopying, NSCoding>

/* NSString primitive (funnel) methods. A minimal subclass of NSString just needs to implement these, although we also recommend getCharacters:range:. See below for the other methods.
*/
- (NSUInteger)length;			
- (unichar)characterAtIndex:(NSUInteger)index;

@end

@interface NSString (NSStringExtensionMethods)

- (void)getCharacters:(unichar *)buffer range:(NSRange)aRange;

- (NSString *)substringFromIndex:(NSUInteger)from;
- (NSString *)substringToIndex:(NSUInteger)to;
- (NSString *)substringWithRange:(NSRange)range;    // Hint: Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up composed characters

- (NSComparisonResult)compare:(NSString *)string;
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask;
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)compareRange;
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)compareRange locale:(id)locale; // locale arg used to be a dictionary pre-Leopard. We now accepts NSLocale. Assumes the current locale if non-nil and non-NSLocale.
- (NSComparisonResult)caseInsensitiveCompare:(NSString *)string;
- (NSComparisonResult)localizedCompare:(NSString *)string;
- (NSComparisonResult)localizedCaseInsensitiveCompare:(NSString *)string;

/* localizedStandardCompare:, added in 10.6, should be used whenever file names or other strings are presented in lists and tables where Finder-like sorting is appropriate.  The exact behavior of this method may be tweaked in future releases, and will be different under different localizations, so clients should not depend on the exact sorting order of the strings.
*/
- (NSComparisonResult)localizedStandardCompare:(NSString *)string NS_AVAILABLE(10_6, 4_0);

- (BOOL)isEqualToString:(NSString *)aString;

- (BOOL)hasPrefix:(NSString *)aString;
- (BOOL)hasSuffix:(NSString *)aString;

/* These methods return length==0 if the target string is not found. So, to check for containment: ([str rangeOfString:@"target"].length > 0).  Note that the length of the range returned by these methods might be different than the length of the target string, due composed characters and such.
*/
- (NSRange)rangeOfString:(NSString *)aString;
- (NSRange)rangeOfString:(NSString *)aString options:(NSStringCompareOptions)mask;
- (NSRange)rangeOfString:(NSString *)aString options:(NSStringCompareOptions)mask range:(NSRange)searchRange;
- (NSRange)rangeOfString:(NSString *)aString options:(NSStringCompareOptions)mask range:(NSRange)searchRange locale:(NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

/* These return the range of the first character from the set in the string, not the range of a sequence of characters. 
*/
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet options:(NSStringCompareOptions)mask;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet options:(NSStringCompareOptions)mask range:(NSRange)searchRange;

- (NSRange)rangeOfComposedCharacterSequenceAtIndex:(NSUInteger)index;
- (NSRange)rangeOfComposedCharacterSequencesForRange:(NSRange)range NS_AVAILABLE(10_5, 2_0);

- (NSString *)stringByAppendingString:(NSString *)aString;
- (NSString *)stringByAppendingFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

/* The following convenience methods all skip initial space characters (whitespaceSet) and ignore trailing characters. NSScanner can be used for more "exact" parsing of numbers.
*/
- (double)doubleValue;
- (float)floatValue;
- (int)intValue;
- (NSInteger)integerValue NS_AVAILABLE(10_5, 2_0);
- (long long)longLongValue NS_AVAILABLE(10_5, 2_0);
- (BOOL)boolValue NS_AVAILABLE(10_5, 2_0);  // Skips initial space characters (whitespaceSet), or optional -/+ sign followed by zeroes. Returns YES on encountering one of "Y", "y", "T", "t", or a digit 1-9. It ignores any trailing characters.

- (NSArray *)componentsSeparatedByString:(NSString *)separator;
- (NSArray *)componentsSeparatedByCharactersInSet:(NSCharacterSet *)separator NS_AVAILABLE(10_5, 2_0);

- (NSString *)commonPrefixWithString:(NSString *)aString options:(NSStringCompareOptions)mask;

- (NSString *)uppercaseString;
- (NSString *)lowercaseString;
- (NSString *)capitalizedString;

- (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;
- (NSString *)stringByPaddingToLength:(NSUInteger)newLength withString:(NSString *)padString startingAtIndex:(NSUInteger)padIndex;

- (void)getLineStart:(NSUInteger *)startPtr end:(NSUInteger *)lineEndPtr contentsEnd:(NSUInteger *)contentsEndPtr forRange:(NSRange)range;
- (NSRange)lineRangeForRange:(NSRange)range;

- (void)getParagraphStart:(NSUInteger *)startPtr end:(NSUInteger *)parEndPtr contentsEnd:(NSUInteger *)contentsEndPtr forRange:(NSRange)range;
- (NSRange)paragraphRangeForRange:(NSRange)range;

#if NS_BLOCKS_AVAILABLE
enum {
	// Pass in one of the "By" options:
	NSStringEnumerationByLines = 0,                       // Equivalent to lineRangeForRange:
        NSStringEnumerationByParagraphs = 1,                  // Equivalent to paragraphRangeForRange:
	NSStringEnumerationByComposedCharacterSequences = 2,  // Equivalent to rangeOfComposedCharacterSequencesForRange:
	NSStringEnumerationByWords = 3,
        NSStringEnumerationBySentences = 4,
	// ...and combine any of the desired additional options:
	NSStringEnumerationReverse = 1UL << 8,
	NSStringEnumerationSubstringNotRequired = 1UL << 9,
	NSStringEnumerationLocalized = 1UL << 10              // User's default locale
};
typedef NSUInteger NSStringEnumerationOptions;

- (void)enumerateSubstringsInRange:(NSRange)range options:(NSStringEnumerationOptions)opts usingBlock:(void (^)(NSString *substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateLinesUsingBlock:(void (^)(NSString *line, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
#endif

- (NSString *)description;

- (NSUInteger)hash;

/*** Encoding methods ***/

- (NSStringEncoding)fastestEncoding;    	// Result in O(1) time; a rough estimate
- (NSStringEncoding)smallestEncoding;   	// Result in O(n) time; the encoding in which the string is most compact

- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;   // External representation
- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding;                                    // External representation

- (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;

/* Methods to convert NSString to a NULL-terminated cString using the specified encoding. Note, these are the "new" cString methods, and are not deprecated like the older cString methods which do not take encoding arguments.
*/
- (__strong const char *)cStringUsingEncoding:(NSStringEncoding)encoding;	// "Autoreleased"; NULL return if encoding conversion not possible; for performance reasons, lifetime of this should not be considered longer than the lifetime of the receiving string (if the receiver string is freed, this might go invalid then, before the end of the autorelease scope)
- (BOOL)getCString:(char *)buffer maxLength:(NSUInteger)maxBufferCount encoding:(NSStringEncoding)encoding;	// NO return if conversion not possible due to encoding errors or too small of a buffer. The buffer should include room for maxBufferCount bytes; this number should accomodate the expected size of the return value plus the NULL termination character, which this method adds. (So note that the maxLength passed to this method is one more than the one you would have passed to the deprecated getCString:maxLength:.)

/* Use this to convert string section at a time into a fixed-size buffer, without any allocations.  Does not NULL-terminate. 
    buffer is the buffer to write to; if NULL, this method can be used to computed size of needed buffer.
    maxBufferCount is the length of the buffer in bytes. It's a good idea to make sure this is at least enough to hold one character's worth of conversion. 
    usedBufferCount is the length of the buffer used up by the current conversion. Can be NULL.
    encoding is the encoding to convert to.
    options specifies the options to apply.
    range is the range to convert.
    leftOver is the remaining range. Can be NULL.
    YES return indicates some characters were converted. Conversion might usually stop when the buffer fills, 
      but it might also stop when the conversion isn't possible due to the chosen encoding. 
*/
- (BOOL)getBytes:(void *)buffer maxLength:(NSUInteger)maxBufferCount usedLength:(NSUInteger *)usedBufferCount encoding:(NSStringEncoding)encoding options:(NSStringEncodingConversionOptions)options range:(NSRange)range remainingRange:(NSRangePointer)leftover;

/* These return the maximum and exact number of bytes needed to store the receiver in the specified encoding in non-external representation. The first one is O(1), while the second one is O(n). These do not include space for a terminating null.
*/
- (NSUInteger)maximumLengthOfBytesUsingEncoding:(NSStringEncoding)enc;	// Result in O(1) time; the estimate may be way over what's needed. Returns 0 on error (overflow)
- (NSUInteger)lengthOfBytesUsingEncoding:(NSStringEncoding)enc;		// Result in O(n) time; the result is exact. Returns 0 on error (cannot convert to specified encoding, or overflow)

- (NSString *)decomposedStringWithCanonicalMapping;
- (NSString *)precomposedStringWithCanonicalMapping;
- (NSString *)decomposedStringWithCompatibilityMapping;
- (NSString *)precomposedStringWithCompatibilityMapping;

/* Returns a string with the character folding options applied. theOptions is a mask of compare flags with *InsensitiveSearch suffix.
*/
- (NSString *)stringByFoldingWithOptions:(NSStringCompareOptions)options locale:(NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

/* Replace all occurrences of the target string in the specified range with replacement. Specified compare options are used for matching target. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
*/
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange NS_AVAILABLE(10_5, 2_0);

/* Replace all occurrences of the target string with replacement. Invokes the above method with 0 options and range of the whole string.
*/
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement NS_AVAILABLE(10_5, 2_0);

/* Replace characters in range with the specified string, returning new string.
*/
- (NSString *)stringByReplacingCharactersInRange:(NSRange)range withString:(NSString *)replacement NS_AVAILABLE(10_5, 2_0);

- (__strong const char *)UTF8String;	// Convenience to return null-terminated UTF8 representation

/* User-dependent encoding who value is derived from user's default language and potentially other factors. The use of this encoding might sometimes be needed when interpreting user documents with unknown encodings, in the absence of other hints.  This encoding should be used rarely, if at all. Note that some potential values here might result in unexpected encoding conversions of even fairly straightforward NSString content --- for instance, punctuation characters with a bidirectional encoding.
*/
+ (NSStringEncoding)defaultCStringEncoding;	// Should be rarely used

+ (const NSStringEncoding *)availableStringEncodings;
+ (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;

/*** Creation methods ***/

/* In general creation methods in NSString do not apply to subclassers, as subclassers are assumed to provide their own init methods which create the string in the way the subclass wishes.  Designated initializers of NSString are thus init and initWithCoder:.
*/
- (id)init;
- (id)initWithCharactersNoCopy:(unichar *)characters length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
- (id)initWithCharacters:(const unichar *)characters length:(NSUInteger)length;
- (id)initWithUTF8String:(const char *)nullTerminatedCString;
- (id)initWithString:(NSString *)aString;
- (id)initWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
- (id)initWithFormat:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
- (id)initWithFormat:(NSString *)format locale:(id)locale, ... NS_FORMAT_FUNCTION(1,3);
- (id)initWithFormat:(NSString *)format locale:(id)locale arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
- (id)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;
- (id)initWithBytes:(const void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding;
- (id)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */

+ (id)string;
+ (id)stringWithString:(NSString *)string;
+ (id)stringWithCharacters:(const unichar *)characters length:(NSUInteger)length;
+ (id)stringWithUTF8String:(const char *)nullTerminatedCString;
+ (id)stringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
+ (id)localizedStringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

- (id)initWithCString:(const char *)nullTerminatedCString encoding:(NSStringEncoding)encoding;
+ (id)stringWithCString:(const char *)cString encoding:(NSStringEncoding)enc;

/* These use the specified encoding.  If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
*/
- (id)initWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
- (id)initWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;
+ (id)stringWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
+ (id)stringWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;

/* These try to determine the encoding, and return the encoding which was used.  Note that these methods might get "smarter" in subsequent releases of the system, and use additional techniques for recognizing encodings. If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
*/
- (id)initWithContentsOfURL:(NSURL *)url usedEncoding:(NSStringEncoding *)enc error:(NSError **)error;
- (id)initWithContentsOfFile:(NSString *)path usedEncoding:(NSStringEncoding *)enc error:(NSError **)error;
+ (id)stringWithContentsOfURL:(NSURL *)url usedEncoding:(NSStringEncoding *)enc error:(NSError **)error;
+ (id)stringWithContentsOfFile:(NSString *)path usedEncoding:(NSStringEncoding *)enc error:(NSError **)error;

/* Write to specified url or path using the specified encoding.  The optional error return is to indicate file system or encoding errors.
*/
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

@end


@interface NSMutableString : NSString

/* NSMutableString primitive (funnel) method. See below for the other mutation methods.
*/
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

@end

@interface NSMutableString (NSMutableStringExtensionMethods)

- (void)insertString:(NSString *)aString atIndex:(NSUInteger)loc;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)appendString:(NSString *)aString;
- (void)appendFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
- (void)setString:(NSString *)aString;

/* In addition to these two, NSMutableString responds properly to all NSString creation methods.
*/
- (id)initWithCapacity:(NSUInteger)capacity;
+ (id)stringWithCapacity:(NSUInteger)capacity;

/* This method replaces all occurrences of the target string with the replacement string, in the specified range of the receiver string, and returns the number of replacements. NSBackwardsSearch means the search is done from the end of the range (the results could be different); NSAnchoredSearch means only anchored (but potentially multiple) instances will be replaced. NSLiteralSearch and NSCaseInsensitiveSearch also apply. NSNumericSearch is ignored. Use NSMakeRange(0, [receiver length]) to process whole string. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
*/
- (NSUInteger)replaceOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange;

@end



@interface NSString (NSExtendedStringPropertyListParsing)

/* These methods are no longer recommended since they do not work with property lists and strings files in binary plist format. Please use the APIs in NSPropertyList.h instead.
*/
- (id)propertyList;
- (NSDictionary *)propertyListFromStringsFileFormat;

@end



@interface NSString (NSStringDeprecated)

/* The following methods are deprecated and will be removed from this header file in the near future. These methods use [NSString defaultCStringEncoding] as the encoding to convert to, which means the results depend on the user's language and potentially other settings. This might be appropriate in some cases, but often these methods are misused, resulting in issues when running in languages other then English. UTF8String in general is a much better choice when converting arbitrary NSStrings into 8-bit representations. Additional potential replacement methods are being introduced in NSString as appropriate.
*/
- (const char *)cString NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (const char *)lossyCString NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (NSUInteger)cStringLength NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);	
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength range:(NSRange)aRange remainingRange:(NSRangePointer)leftoverRange NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (id)initWithContentsOfFile:(NSString *)path NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (id)initWithContentsOfURL:(NSURL *)url NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (id)stringWithContentsOfFile:(NSString *)path NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (id)stringWithContentsOfURL:(NSURL *)url NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (id)initWithCStringNoCopy:(char *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (id)initWithCString:(const char *)bytes length:(NSUInteger)length NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (id)initWithCString:(const char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);	
+ (id)stringWithCString:(const char *)bytes length:(NSUInteger)length NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (id)stringWithCString:(const char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getCharacters:range: instead.
*/
- (void)getCharacters:(unichar *)buffer;

@end

enum {
    NSProprietaryStringEncoding = 65536    /* Installation-specific encoding */
};



/* The rest of this file is bookkeeping stuff that has to be here. Don't use this stuff, don't refer to it.
*/
#if !defined(_OBJC_UNICHAR_H_)
#define _OBJC_UNICHAR_H_
#endif
#define NS_UNICHAR_IS_EIGHT_BIT 0

@interface NSSimpleCString : NSString {
@package
    char *bytes;
    int numBytes;
#if __LP64__
    int _unused;
#endif
}
@end

@interface NSConstantString : NSSimpleCString
@end

#if __LP64__
#else
extern void *_NSConstantStringClassReference;
#endif

