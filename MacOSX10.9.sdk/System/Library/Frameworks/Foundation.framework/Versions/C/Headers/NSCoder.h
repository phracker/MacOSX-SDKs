/*	NSCoder.h
	Copyright (c) 1993-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData, NSSet;

@interface NSCoder : NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
- (void)encodeDataObject:(NSData *)data;
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
- (NSData *)decodeDataObject;
- (NSInteger)versionForClassName:(NSString *)className;

@end

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(id)object;
- (void)encodeRootObject:(id)rootObject;
- (void)encodeBycopyObject:(id)anObject;
- (void)encodeByrefObject:(id)anObject;
- (void)encodeConditionalObject:(id)object;
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
- (void)encodeArrayOfObjCType:(const char *)type count:(NSUInteger)count at:(const void *)array;
- (void)encodeBytes:(const void *)byteaddr length:(NSUInteger)length;

- (id)decodeObject;
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
- (void)decodeArrayOfObjCType:(const char *)itemType count:(NSUInteger)count at:(void *)array;
- (void *)decodeBytesWithReturnedLength:(NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)encodePropertyList:(id)aPropertyList;
- (id)decodePropertyList;
#endif

- (void)setObjectZone:(NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

- (unsigned)systemVersion;

- (BOOL)allowsKeyedCoding;

- (void)encodeObject:(id)objv forKey:(NSString *)key;
- (void)encodeConditionalObject:(id)objv forKey:(NSString *)key;
- (void)encodeBool:(BOOL)boolv forKey:(NSString *)key;
- (void)encodeInt:(int)intv forKey:(NSString *)key;
- (void)encodeInt32:(int32_t)intv forKey:(NSString *)key;
- (void)encodeInt64:(int64_t)intv forKey:(NSString *)key;
- (void)encodeFloat:(float)realv forKey:(NSString *)key;
- (void)encodeDouble:(double)realv forKey:(NSString *)key;
- (void)encodeBytes:(const uint8_t *)bytesp length:(NSUInteger)lenv forKey:(NSString *)key;

- (BOOL)containsValueForKey:(NSString *)key;
- (id)decodeObjectForKey:(NSString *)key;
- (BOOL)decodeBoolForKey:(NSString *)key;
- (int)decodeIntForKey:(NSString *)key;
- (int32_t)decodeInt32ForKey:(NSString *)key;
- (int64_t)decodeInt64ForKey:(NSString *)key;
- (float)decodeFloatForKey:(NSString *)key;
- (double)decodeDoubleForKey:(NSString *)key;
- (const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;   // returned bytes immutable!

- (void)encodeInteger:(NSInteger)intv forKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);
- (NSInteger)decodeIntegerForKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);

// Returns YES if this coder requires secure coding. Secure coders check a list of allowed classes before decoding objects, and all objects must implement NSSecureCoding.
- (BOOL)requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

// Specify what the expected class of the allocated object is. If the coder responds YES to -requiresSecureCoding, then an exception will be thrown if the class to be decoded does not implement NSSecureCoding or is not isKindOfClass: of the argument. If the coder responds NO to -requiresSecureCoding, then the class argument is ignored and no check of the class of the decoded object is performed, exactly as if decodeObjectForKey: had been called.
- (id)decodeObjectOfClass:(Class)aClass forKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);

// The class of the object may be any class in the provided NSSet, or a subclass of any class in the set. Otherwise, the behavior is the same as -decodeObjectOfClass:forKey:.
- (id)decodeObjectOfClasses:(NSSet *)classes forKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);

// Calls -decodeObjectOfClasses:forKey: with a set allowing only property list types.
- (id)decodePropertyListForKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);

// Get the current set of allowed classes.
- (NSSet *)allowedClasses NS_AVAILABLE(10_8, 6_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
FOUNDATION_EXPORT NSObject *NXReadNSObjectFromCoder(NSCoder *decoder) NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Given an NSCoder, returns an object previously written with
   NXWriteNSObject(). The returned object is autoreleased. */

@interface NSCoder (NSTypedstreamCompatibility)

- (void)encodeNXObject:(id)object NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Writes old-style object onto the coder. No sharing is done across
   separate -encodeNXObject:. Callers must have implemented an
   -encodeWithCoder:, which parallels the -write: methods, on all of
   their classes which may be touched by this operation. Object's
   -replacementObjectForCoder: compatibility method will take care
   of calling -startArchiving:. */
    
- (id)decodeNXObject NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Reads an object previously written with -encodeNXObject:. No
   sharing is done across separate -decodeNXObject. Callers must
   have implemented an -initWithCoder:, which parallels the -read:
   methods, on all of their classes which may be touched by this
   operation. Object's -awakeAfterUsingCoder: compatibility method
   will take care of calling -awake and -finishUnarchiving. The
   returned object is autoreleased. */

@end
#endif

