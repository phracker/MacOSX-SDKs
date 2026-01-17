/*	NSScanner.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSCharacterSet, NSDictionary;

@interface NSScanner : NSObject <NSCopying>

- (NSString *)string;
- (NSUInteger)scanLocation;
- (void)setScanLocation:(NSUInteger)pos;
- (void)setCharactersToBeSkipped:(NSCharacterSet *)set;
- (void)setCaseSensitive:(BOOL)flag;
- (void)setLocale:(id)locale;

@end

@interface NSScanner (NSExtendedScanner)

- (NSCharacterSet *)charactersToBeSkipped;
- (BOOL)caseSensitive;
- (id)locale;

- (BOOL)scanInt:(int *)value;
- (BOOL)scanInteger:(NSInteger *)value NS_AVAILABLE(10_5, 2_0);
- (BOOL)scanHexLongLong:(unsigned long long *)result NS_AVAILABLE(10_5, 2_0);
- (BOOL)scanHexFloat:(float *)result NS_AVAILABLE(10_5, 2_0);		// Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix. 
- (BOOL)scanHexDouble:(double *)result NS_AVAILABLE(10_5, 2_0);		// Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix. 
- (BOOL)scanHexInt:(unsigned *)value;		// Optionally prefixed with "0x" or "0X"
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

