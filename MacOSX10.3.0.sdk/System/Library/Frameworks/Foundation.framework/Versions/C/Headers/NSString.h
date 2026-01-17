/*	NSString.h
	Copyright (c) 1994-2003, Apple, Inc. All rights reserved.
*/

typedef unsigned short unichar;

#import <limits.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <stdarg.h>

@class NSData, NSArray, NSDictionary, NSCharacterSet, NSData, NSURL;

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
};

/* Note that in addition to the values explicitly listed below, NSStringEncoding supports encodings provided by CFString.
See CFStringEncodingExt.h for a list of these encodings.
See CFString.h for functions which convert between NSStringEncoding and CFStringEncoding.
*/
typedef unsigned NSStringEncoding;

enum {
    NSASCIIStringEncoding = 1,		/* 0..127 only */
    NSNEXTSTEPStringEncoding = 2,
    NSJapaneseEUCStringEncoding = 3,
    NSUTF8StringEncoding = 4,
    NSISOLatin1StringEncoding = 5,
    NSSymbolStringEncoding = 6,
    NSNonLossyASCIIStringEncoding = 7,
    NSShiftJISStringEncoding = 8,
    NSISOLatin2StringEncoding = 9,
    NSUnicodeStringEncoding = 10,
    NSWindowsCP1251StringEncoding = 11,    /* Cyrillic; same as AdobeStandardCyrillic */
    NSWindowsCP1252StringEncoding = 12,    /* WinLatin1 */
    NSWindowsCP1253StringEncoding = 13,    /* Greek */
    NSWindowsCP1254StringEncoding = 14,    /* Turkish */
    NSWindowsCP1250StringEncoding = 15,    /* WinLatin2 */
    NSISO2022JPStringEncoding = 21,         /* ISO 2022 Japanese encoding for e-mail */
    NSMacOSRomanStringEncoding = 30,

    NSProprietaryStringEncoding = 65536    /* Installation-specific encoding */
};

FOUNDATION_EXPORT NSString * const NSCharacterConversionException;

@interface NSString : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (unsigned int)length;			
- (unichar)characterAtIndex:(unsigned)index;

@end

@interface NSString (NSStringExtensionMethods)

- (void)getCharacters:(unichar *)buffer;
- (void)getCharacters:(unichar *)buffer range:(NSRange)aRange;

- (NSString *)substringFromIndex:(unsigned)from;
- (NSString *)substringToIndex:(unsigned)to;
- (NSString *)substringWithRange:(NSRange)range;

- (NSComparisonResult)compare:(NSString *)string;
- (NSComparisonResult)compare:(NSString *)string options:(unsigned)mask;
- (NSComparisonResult)compare:(NSString *)string options:(unsigned)mask range:(NSRange)compareRange;
- (NSComparisonResult)compare:(NSString *)string options:(unsigned)mask range:(NSRange)compareRange locale:(NSDictionary *)dict;
- (NSComparisonResult)caseInsensitiveCompare:(NSString *)string;
- (NSComparisonResult)localizedCompare:(NSString *)string;
- (NSComparisonResult)localizedCaseInsensitiveCompare:(NSString *)string;

- (BOOL)isEqualToString:(NSString *)aString;

- (BOOL)hasPrefix:(NSString *)aString;
- (BOOL)hasSuffix:(NSString *)aString;
- (NSRange)rangeOfString:(NSString *)aString;
- (NSRange)rangeOfString:(NSString *)aString options:(unsigned)mask;
- (NSRange)rangeOfString:(NSString *)aString options:(unsigned)mask range:(NSRange)searchRange;

- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet options:(unsigned int)mask;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet options:(unsigned int)mask range:(NSRange)searchRange;

- (NSRange)rangeOfComposedCharacterSequenceAtIndex:(unsigned)index;

- (NSString *)stringByAppendingString:(NSString *)aString;
- (NSString *)stringByAppendingFormat:(NSString *)format, ...;

- (double)doubleValue;
- (float)floatValue;
- (int)intValue;

- (NSArray *)componentsSeparatedByString:(NSString *)separator;

- (NSString *)commonPrefixWithString:(NSString *)aString options:(unsigned)mask;

- (NSString *)uppercaseString;
- (NSString *)lowercaseString;
- (NSString *)capitalizedString;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;
- (NSString *)stringByPaddingToLength:(unsigned)newLength withString:(NSString *)padString startingAtIndex:(unsigned)padIndex;
#endif

- (void)getLineStart:(unsigned *)startPtr end:(unsigned *)lineEndPtr contentsEnd:(unsigned *)contentsEndPtr forRange:(NSRange)range;
- (NSRange)lineRangeForRange:(NSRange)range;

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)getParagraphStart:(unsigned *)startPtr end:(unsigned *)parEndPtr contentsEnd:(unsigned *)contentsEndPtr forRange:(NSRange)range;
- (NSRange)paragraphRangeForRange:(NSRange)range;
#endif

- (NSString *)description;

- (unsigned)hash;

- (NSStringEncoding)fastestEncoding;
- (NSStringEncoding)smallestEncoding;

- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;
- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding;

- (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)decomposedStringWithCanonicalMapping;
- (NSString *)precomposedStringWithCanonicalMapping;
- (NSString *)decomposedStringWithCompatibilityMapping;
- (NSString *)precomposedStringWithCompatibilityMapping;
#endif

- (const char *)UTF8String;	// Convenience to return null-terminated UTF8 representation

/* The "cString" methods are discouraged and will be deprecated in the near future. These methods use [NSString defaultCStringEncoding] as the encoding to convert to, which means the results depend on the user's language and potentially other settings. This might be appropriate in some cases, but often these methods are misused, resulting in issues when running in languages other then English. UTF8String in general is a much better choice when converting arbitrary NSStrings into 8-bit representations.
*/
- (const char *)cString;		// Will raise if NSString cannot be converted to [NSString defaultCStringEncoding]
- (const char *)lossyCString;
- (unsigned)cStringLength;		// Will raise if NSString cannot be converted to [NSString defaultCStringEncoding]
- (void)getCString:(char *)bytes;	// Will raise if NSString cannot be converted to [NSString defaultCStringEncoding]
- (void)getCString:(char *)bytes maxLength:(unsigned)maxLength;		// Will raise if NSString cannot be converted to [NSString defaultCStringEncoding]
- (void)getCString:(char *)bytes maxLength:(unsigned)maxLength range:(NSRange)aRange remainingRange:(NSRangePointer)leftoverRange;	// Will raise if NSString cannot be converted to [NSString defaultCStringEncoding]
+ (NSStringEncoding)defaultCStringEncoding;	

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if url is not of a type that can be accessed atomically

+ (const NSStringEncoding *)availableStringEncodings;
+ (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;

/* In general creation methods in NSString do not apply to subclassers, as subclassers are assumed to provide their own init methods which create the string in the way the subclass wishes.  Designated initializers of NSString are thus init and initWithCoder:.
*/
+ (id)string;
+ (id)stringWithString:(NSString *)string;
+ (id)stringWithCharacters:(const unichar *)characters length:(unsigned)length;
+ (id)stringWithCString:(const char *)bytes length:(unsigned)length;
+ (id)stringWithCString:(const char *)bytes;
+ (id)stringWithUTF8String:(const char *)bytes;
+ (id)stringWithFormat:(NSString *)format, ...;
+ (id)stringWithContentsOfFile:(NSString *)path;
+ (id)stringWithContentsOfURL:(NSURL *)url;
+ (id)localizedStringWithFormat:(NSString *)format, ...;

- (id)init;
- (id)initWithCharactersNoCopy:(unichar *)characters length:(unsigned)length freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
- (id)initWithCharacters:(const unichar *)characters length:(unsigned)length;
- (id)initWithBytes:(const void *)bytes length:(unsigned)len encoding:(NSStringEncoding)encoding;
#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (id)initWithBytesNoCopy:(void *)bytes length:(unsigned)len encoding:(NSStringEncoding)encoding freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
#endif
- (id)initWithUTF8String:(const char *)bytes;
- (id)initWithString:(NSString *)aString;
- (id)initWithFormat:(NSString *)format, ...;
- (id)initWithFormat:(NSString *)format arguments:(va_list)argList;
- (id)initWithFormat:(NSString *)format locale:(NSDictionary *)dict, ...;
- (id)initWithFormat:(NSString *)format locale:(NSDictionary *)dict arguments:(va_list)argList;
- (id)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;
- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithContentsOfURL:(NSURL *)url;

- (id)initWithCStringNoCopy:(char *)bytes length:(unsigned)length freeWhenDone:(BOOL)freeBuffer;	/* Best to avoid this, will be removed */
- (id)initWithCString:(const char *)bytes length:(unsigned)length;	/* Best to avoid this, will be removed */
- (id)initWithCString:(const char *)bytes;				/* Best to avoid this, will be removed */

@end

@interface NSMutableString : NSString

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

@end

@interface NSMutableString (NSMutableStringExtensionMethods)

- (void)insertString:(NSString *)aString atIndex:(unsigned)loc;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)appendString:(NSString *)aString;
- (void)appendFormat:(NSString *)format, ...;
- (void)setString:(NSString *)aString;

+ (id)stringWithCapacity:(unsigned)capacity;
- (id)initWithCapacity:(unsigned)capacity;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
/* This method replaces all occurrences of the target string with the replacement string, in the specified range of the receiver string, and returns the number of replacements. NSBackwardsSearch means the search is done from the end of the range (the results could be different); NSAnchoredSearch means only anchored (but potentially multiple) instances will be replaced. NSLiteralSearch and NSCaseInsensitiveSearch also apply. NSNumericSearch is ignored. Use NSMakeRange(0, [receiver length]) to process whole string. 
*/
- (unsigned int)replaceOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(unsigned)opts range:(NSRange)searchRange;
#endif

@end

@interface NSString (NSExtendedStringPropertyListParsing)
    
- (id)propertyList;
- (NSDictionary *)propertyListFromStringsFileFormat;

@end


/* ***	The rest of this file is bookkeeping stuff that has to
   ***	be here (for now). Don't use this stuff, don't refer to it.
*/
#if !defined(_OBJC_UNICHAR_H_)
#define _OBJC_UNICHAR_H_
#endif
#define NS_UNICHAR_IS_EIGHT_BIT 0

@interface NSSimpleCString : NSString {
@protected
    char *bytes;
    unsigned int numBytes;
}
@end

@interface NSConstantString : NSSimpleCString
@end

extern void *_NSConstantStringClassReference;

