/*	NSScanner.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSCharacterSet, NSDictionary;

NS_ASSUME_NONNULL_BEGIN

@interface NSScanner : NSObject <NSCopying>

@property (readonly, copy) NSString *string;
@property NSUInteger scanLocation;
@property (nullable, copy) NSCharacterSet *charactersToBeSkipped;
@property BOOL caseSensitive;
@property (nullable, retain) id locale;

- (instancetype)initWithString:(NSString *)string NS_DESIGNATED_INITIALIZER;

@end

@interface NSScanner (NSExtendedScanner)

// On overflow, the below methods will return success and clamp
- (BOOL)scanInt:(nullable int *)result;
- (BOOL)scanInteger:(nullable NSInteger *)result NS_AVAILABLE(10_5, 2_0);
- (BOOL)scanLongLong:(nullable long long *)result;
- (BOOL)scanUnsignedLongLong:(nullable unsigned long long *)result NS_AVAILABLE(10_9, 7_0);
- (BOOL)scanFloat:(nullable float *)result;
- (BOOL)scanDouble:(nullable double *)result;
- (BOOL)scanHexInt:(nullable unsigned *)result;                                          // Optionally prefixed with "0x" or "0X"
- (BOOL)scanHexLongLong:(nullable unsigned long long *)result NS_AVAILABLE(10_5, 2_0);   // Optionally prefixed with "0x" or "0X"
- (BOOL)scanHexFloat:(nullable float *)result NS_AVAILABLE(10_5, 2_0);                   // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.
- (BOOL)scanHexDouble:(nullable double *)result NS_AVAILABLE(10_5, 2_0);                 // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.

- (BOOL)scanString:(NSString *)string intoString:(NSString * __nullable * __nullable)result;
- (BOOL)scanCharactersFromSet:(NSCharacterSet *)set intoString:(NSString * __nullable * __nullable)result;

- (BOOL)scanUpToString:(NSString *)string intoString:(NSString * __nullable * __nullable)result;
- (BOOL)scanUpToCharactersFromSet:(NSCharacterSet *)set intoString:(NSString * __nullable * __nullable)result;

@property (getter=isAtEnd, readonly) BOOL atEnd;

+ (instancetype)scannerWithString:(NSString *)string;
+ (id)localizedScannerWithString:(NSString *)string;

@end

NS_ASSUME_NONNULL_END
