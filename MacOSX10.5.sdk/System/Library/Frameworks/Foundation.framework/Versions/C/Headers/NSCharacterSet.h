/*	NSCharacterSet.h
	Copyright (c) 1994-2007, Apple Inc. All rights reserved.
*/

#import <CoreFoundation/CFCharacterSet.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSString.h>

@class NSData;

enum {
    NSOpenStepUnicodeReservedBase = 0xF400
};

@interface NSCharacterSet : NSObject <NSCopying, NSMutableCopying, NSCoding>

+ (id)controlCharacterSet;
+ (id)whitespaceCharacterSet;
+ (id)whitespaceAndNewlineCharacterSet;
+ (id)decimalDigitCharacterSet;
+ (id)letterCharacterSet;
+ (id)lowercaseLetterCharacterSet;
+ (id)uppercaseLetterCharacterSet;
+ (id)nonBaseCharacterSet;
+ (id)alphanumericCharacterSet;
+ (id)decomposableCharacterSet;
+ (id)illegalCharacterSet;
+ (id)punctuationCharacterSet;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (id)capitalizedLetterCharacterSet;
#endif
#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (id)symbolCharacterSet;
#endif
#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (id)newlineCharacterSet;
#endif

+ (id)characterSetWithRange:(NSRange)aRange;
+ (id)characterSetWithCharactersInString:(NSString *)aString;
+ (id)characterSetWithBitmapRepresentation:(NSData *)data;
+ (id)characterSetWithContentsOfFile:(NSString *)fName;

- (BOOL)characterIsMember:(unichar)aCharacter;
- (NSData *)bitmapRepresentation;
- (NSCharacterSet *)invertedSet;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)longCharacterIsMember:(UTF32Char)theLongChar;

- (BOOL)isSupersetOfSet:(NSCharacterSet *)theOtherSet;
- (BOOL)hasMemberInPlane:(uint8_t)thePlane;
#endif
@end

@interface NSMutableCharacterSet : NSCharacterSet <NSCopying, NSMutableCopying>

- (void)addCharactersInRange:(NSRange)aRange;
- (void)removeCharactersInRange:(NSRange)aRange;
- (void)addCharactersInString:(NSString *)aString;
- (void)removeCharactersInString:(NSString *)aString;
- (void)formUnionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)formIntersectionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)invert;

@end

