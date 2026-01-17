/*	NSCharacterSet.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <CoreFoundation/CFCharacterSet.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSString.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

enum {
    NSOpenStepUnicodeReservedBase = 0xF400
};

@interface NSCharacterSet : NSObject <NSCopying, NSMutableCopying, NSCoding>

+ (NSCharacterSet *)controlCharacterSet;
+ (NSCharacterSet *)whitespaceCharacterSet;
+ (NSCharacterSet *)whitespaceAndNewlineCharacterSet;
+ (NSCharacterSet *)decimalDigitCharacterSet;
+ (NSCharacterSet *)letterCharacterSet;
+ (NSCharacterSet *)lowercaseLetterCharacterSet;
+ (NSCharacterSet *)uppercaseLetterCharacterSet;
+ (NSCharacterSet *)nonBaseCharacterSet;
+ (NSCharacterSet *)alphanumericCharacterSet;
+ (NSCharacterSet *)decomposableCharacterSet;
+ (NSCharacterSet *)illegalCharacterSet;
+ (NSCharacterSet *)punctuationCharacterSet;
+ (NSCharacterSet *)capitalizedLetterCharacterSet;
+ (NSCharacterSet *)symbolCharacterSet;
+ (NSCharacterSet *)newlineCharacterSet NS_AVAILABLE(10_5, 2_0);

+ (NSCharacterSet *)characterSetWithRange:(NSRange)aRange;
+ (NSCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;
+ (NSCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;
+ (nullable NSCharacterSet *)characterSetWithContentsOfFile:(NSString *)fName;

- (instancetype) initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (BOOL)characterIsMember:(unichar)aCharacter;
@property (readonly, copy) NSData *bitmapRepresentation;
@property (readonly, copy) NSCharacterSet *invertedSet;


- (BOOL)longCharacterIsMember:(UTF32Char)theLongChar;

- (BOOL)isSupersetOfSet:(NSCharacterSet *)theOtherSet;
- (BOOL)hasMemberInPlane:(uint8_t)thePlane;
@end

@interface NSMutableCharacterSet : NSCharacterSet <NSCopying, NSMutableCopying>

- (void)addCharactersInRange:(NSRange)aRange;
- (void)removeCharactersInRange:(NSRange)aRange;
- (void)addCharactersInString:(NSString *)aString;
- (void)removeCharactersInString:(NSString *)aString;
- (void)formUnionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)formIntersectionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)invert;

+ (NSMutableCharacterSet *)controlCharacterSet;
+ (NSMutableCharacterSet *)whitespaceCharacterSet;
+ (NSMutableCharacterSet *)whitespaceAndNewlineCharacterSet;
+ (NSMutableCharacterSet *)decimalDigitCharacterSet;
+ (NSMutableCharacterSet *)letterCharacterSet;
+ (NSMutableCharacterSet *)lowercaseLetterCharacterSet;
+ (NSMutableCharacterSet *)uppercaseLetterCharacterSet;
+ (NSMutableCharacterSet *)nonBaseCharacterSet;
+ (NSMutableCharacterSet *)alphanumericCharacterSet;
+ (NSMutableCharacterSet *)decomposableCharacterSet;
+ (NSMutableCharacterSet *)illegalCharacterSet;
+ (NSMutableCharacterSet *)punctuationCharacterSet;
+ (NSMutableCharacterSet *)capitalizedLetterCharacterSet;
+ (NSMutableCharacterSet *)symbolCharacterSet;
+ (NSMutableCharacterSet *)newlineCharacterSet NS_AVAILABLE(10_5, 2_0);

+ (NSMutableCharacterSet *)characterSetWithRange:(NSRange)aRange;
+ (NSMutableCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;
+ (NSMutableCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;
+ (nullable NSMutableCharacterSet *)characterSetWithContentsOfFile:(NSString *)fName;

@end

NS_ASSUME_NONNULL_END
