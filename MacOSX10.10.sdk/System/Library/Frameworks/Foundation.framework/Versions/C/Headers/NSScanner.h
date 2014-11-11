/*	NSScanner.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSCharacterSet, NSDictionary;

@interface NSScanner : NSObject <NSCopying>

@property (readonly, copy) NSString *string;
@property NSUInteger scanLocation;
@property (copy) NSCharacterSet *charactersToBeSkipped;
@property BOOL caseSensitive;
@property (retain) id locale;

- (instancetype)initWithString:(NSString *)string NS_DESIGNATED_INITIALIZER;

@end

@interface NSScanner (NSExtendedScanner)

// On overflow, the below methods will return success and clamp
- (BOOL)scanInt:(int *)result;
- (BOOL)scanInteger:(NSInteger *)result NS_AVAILABLE(10_5, 2_0);
- (BOOL)scanLongLong:(long long *)result;
- (BOOL)scanUnsignedLongLong:(unsigned long long *)result NS_AVAILABLE(10_9, 7_0);
- (BOOL)scanFloat:(float *)result;
- (BOOL)scanDouble:(double *)result;
- (BOOL)scanHexInt:(unsigned *)result;                                          // Optionally prefixed with "0x" or "0X"
- (BOOL)scanHexLongLong:(unsigned long long *)result NS_AVAILABLE(10_5, 2_0);   // Optionally prefixed with "0x" or "0X"
- (BOOL)scanHexFloat:(float *)result NS_AVAILABLE(10_5, 2_0);                   // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.
- (BOOL)scanHexDouble:(double *)result NS_AVAILABLE(10_5, 2_0);                 // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.

- (BOOL)scanString:(NSString *)string intoString:(NSString **)result;
- (BOOL)scanCharactersFromSet:(NSCharacterSet *)set intoString:(NSString **)result;

- (BOOL)scanUpToString:(NSString *)string intoString:(NSString **)result;
- (BOOL)scanUpToCharactersFromSet:(NSCharacterSet *)set intoString:(NSString **)result;

@property (getter=isAtEnd, readonly) BOOL atEnd;

+ (instancetype)scannerWithString:(NSString *)string;
+ (id)localizedScannerWithString:(NSString *)string;

@end

