/*	NSScanner.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSCharacterSet, NSDictionary;

@interface NSScanner : NSObject <NSCopying>

- (NSString *)string;
- (unsigned)scanLocation;
- (void)setScanLocation:(unsigned)pos;
- (void)setCharactersToBeSkipped:(NSCharacterSet *)set;
- (void)setCaseSensitive:(BOOL)flag;
- (void)setLocale:(NSDictionary *)dict;

@end

@interface NSScanner (NSExtendedScanner)

- (NSCharacterSet *)charactersToBeSkipped;
- (BOOL)caseSensitive;
- (NSDictionary *)locale;

- (BOOL)scanInt:(int *)value;
- (BOOL)scanHexInt:(unsigned *)value;		/* Optionally prefixed with "0x" or "0X" */
- (BOOL)scanLongLong:(long long *)value;
- (BOOL)scanFloat:(float *)value;
- (BOOL)scanDouble:(double *)value;
- (BOOL)scanString:(NSString *)string intoString:(NSString **)value;
- (BOOL)scanCharactersFromSet:(NSCharacterSet *)set intoString:(NSString **)value;

- (BOOL)scanUpToString:(NSString *)string intoString:(NSString **)value;
- (BOOL)scanUpToCharactersFromSet:(NSCharacterSet *)set intoString:(NSString **)value;

- (BOOL)isAtEnd;

- (id)initWithString:(NSString *)string;
+ (id)scannerWithString:(NSString *)string;
+ (id)localizedScannerWithString:(NSString *)string;

@end

