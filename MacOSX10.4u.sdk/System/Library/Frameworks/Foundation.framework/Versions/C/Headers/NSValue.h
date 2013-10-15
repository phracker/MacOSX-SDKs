/*	NSValue.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary;

@interface NSValue : NSObject <NSCopying, NSCoding>

- (void)getValue:(void *)value;
- (const char *)objCType;

@end

@interface NSValue (NSValueCreation)

- (id)initWithBytes:(const void *)value objCType:(const char *)type;
+ (NSValue *)valueWithBytes:(const void *)value objCType:(const char *)type;
+ (NSValue *)value:(const void *)value withObjCType:(const char *)type;

@end

@interface NSValue (NSValueExtensionMethods)

+ (NSValue *)valueWithNonretainedObject:(id)anObject;
- (id)nonretainedObjectValue;

+ (NSValue *)valueWithPointer:(const void *)pointer;
- (void *)pointerValue;

- (BOOL)isEqualToValue:(NSValue *)value;

@end

@interface NSNumber : NSValue

- (char)charValue;
- (unsigned char)unsignedCharValue;
- (short)shortValue;
- (unsigned short)unsignedShortValue;
- (int)intValue;
- (unsigned int)unsignedIntValue;
- (long)longValue;
- (unsigned long)unsignedLongValue;
- (long long)longLongValue;
- (unsigned long long)unsignedLongLongValue;
- (float)floatValue;
- (double)doubleValue;
- (BOOL)boolValue;
- (NSString *)stringValue;

- (NSComparisonResult)compare:(NSNumber *)otherNumber;

- (BOOL)isEqualToNumber:(NSNumber *)number;

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;

@end

@interface NSNumber (NSNumberCreation)

- (id)initWithChar:(char)value;
- (id)initWithUnsignedChar:(unsigned char)value;
- (id)initWithShort:(short)value;
- (id)initWithUnsignedShort:(unsigned short)value;
- (id)initWithInt:(int)value;
- (id)initWithUnsignedInt:(unsigned int)value;
- (id)initWithLong:(long)value;
- (id)initWithUnsignedLong:(unsigned long)value;
- (id)initWithLongLong:(long long)value;
- (id)initWithUnsignedLongLong:(unsigned long long)value;
- (id)initWithFloat:(float)value;
- (id)initWithDouble:(double)value;
- (id)initWithBool:(BOOL)value;

+ (NSNumber *)numberWithChar:(char)value;
+ (NSNumber *)numberWithUnsignedChar:(unsigned char)value;
+ (NSNumber *)numberWithShort:(short)value;
+ (NSNumber *)numberWithUnsignedShort:(unsigned short)value;
+ (NSNumber *)numberWithInt:(int)value;
+ (NSNumber *)numberWithUnsignedInt:(unsigned int)value;
+ (NSNumber *)numberWithLong:(long)value;
+ (NSNumber *)numberWithUnsignedLong:(unsigned long)value;
+ (NSNumber *)numberWithLongLong:(long long)value;
+ (NSNumber *)numberWithUnsignedLongLong:(unsigned long long)value;
+ (NSNumber *)numberWithFloat:(float)value;
+ (NSNumber *)numberWithDouble:(double)value;
+ (NSNumber *)numberWithBool:(BOOL)value;

@end

