/*	NSCoder.h
	Copyright 1993-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData;

@interface NSCoder : NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
- (void)encodeDataObject:(NSData *)data;
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
- (NSData *)decodeDataObject;
- (unsigned)versionForClassName:(NSString *)className;

@end

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(id)object;
- (void)encodePropertyList:(id)aPropertyList;
- (void)encodeRootObject:(id)rootObject;
- (void)encodeBycopyObject:(id)anObject;
- (void)encodeByrefObject:(id)anObject;
- (void)encodeConditionalObject:(id)object;
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
- (void)encodeArrayOfObjCType:(const char *)type count:(unsigned)count at:(const void *)array;
- (void)encodeBytes:(const void *)byteaddr length:(unsigned)length;

- (id)decodeObject;
- (id)decodePropertyList;
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
- (void)decodeArrayOfObjCType:(const char *)itemType count:(unsigned)count at:(void *)array;
- (void *)decodeBytesWithReturnedLength:(unsigned *)lengthp;

- (void)setObjectZone:(NSZone *)zone;
- (NSZone *)objectZone;

- (unsigned)systemVersion;

@end

FOUNDATION_EXPORT NSObject *NXReadNSObjectFromCoder(NSCoder *decoder);
/* Given an NSCoder, returns an object previously written with
   NXWriteNSObject(). The returned object is autoreleased. */

@interface NSCoder (NSTypedstreamCompatibility)

- (void)encodeNXObject:(id)object;
/* Writes old-style object onto the coder. No sharing is done across
   separate -encodeNXObject:. Callers must have implemented an
   -encodeWithCoder:, which parallels the -write: methods, on all of
   their classes which may be touched by this operation. Object's
   -replacementObjectForCoder: compatibility method will take care
   of calling -startArchiving:. */
    
- (id)decodeNXObject;
/* Reads an object previously written with -encodeNXObject:. No
   sharing is done across separate -decodeNXObject. Callers must
   have implemented an -initWithCoder:, which parallels the -read:
   methods, on all of their classes which may be touched by this
   operation. Object's -awakeAfterUsingCoder: compatibility method
   will take care of calling -awake and -finishUnarchiving. The
   returned object is autoreleased. */

@end

