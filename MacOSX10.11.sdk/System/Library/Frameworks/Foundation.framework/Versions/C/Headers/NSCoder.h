/*	NSCoder.h
	Copyright (c) 1993-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData, NSSet<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

@interface NSCoder : NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
- (void)encodeDataObject:(NSData *)data;
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
- (nullable NSData *)decodeDataObject;
- (NSInteger)versionForClassName:(NSString *)className;

@end

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(nullable id)object;
- (void)encodeRootObject:(id)rootObject;
- (void)encodeBycopyObject:(nullable id)anObject;
- (void)encodeByrefObject:(nullable id)anObject;
- (void)encodeConditionalObject:(nullable id)object;
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
- (void)encodeArrayOfObjCType:(const char *)type count:(NSUInteger)count at:(const void *)array;
- (void)encodeBytes:(nullable const void *)byteaddr length:(NSUInteger)length;

- (nullable id)decodeObject;
- (nullable id)decodeTopLevelObjectAndReturnError:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeTopLevelObject() throws' instead");
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
- (void)decodeArrayOfObjCType:(const char *)itemType count:(NSUInteger)count at:(void *)array;
- (nullable void *)decodeBytesWithReturnedLength:(NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)encodePropertyList:(id)aPropertyList;
- (nullable id)decodePropertyList;
#endif

- (void)setObjectZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (nullable NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

@property (readonly) unsigned int systemVersion;

@property (readonly) BOOL allowsKeyedCoding;

- (void)encodeObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeConditionalObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeBool:(BOOL)boolv forKey:(NSString *)key;
- (void)encodeInt:(int)intv forKey:(NSString *)key;
- (void)encodeInt32:(int32_t)intv forKey:(NSString *)key;
- (void)encodeInt64:(int64_t)intv forKey:(NSString *)key;
- (void)encodeFloat:(float)realv forKey:(NSString *)key;
- (void)encodeDouble:(double)realv forKey:(NSString *)key;
- (void)encodeBytes:(nullable const uint8_t *)bytesp length:(NSUInteger)lenv forKey:(NSString *)key;

- (BOOL)containsValueForKey:(NSString *)key;
- (nullable id)decodeObjectForKey:(NSString *)key;
- (nullable id)decodeTopLevelObjectForKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeObjectForKey(_:) throws' instead");
- (BOOL)decodeBoolForKey:(NSString *)key;
- (int)decodeIntForKey:(NSString *)key;
- (int32_t)decodeInt32ForKey:(NSString *)key;
- (int64_t)decodeInt64ForKey:(NSString *)key;
- (float)decodeFloatForKey:(NSString *)key;
- (double)decodeDoubleForKey:(NSString *)key;
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(nullable NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;   // returned bytes immutable!

- (void)encodeInteger:(NSInteger)intv forKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);
- (NSInteger)decodeIntegerForKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);

// Returns YES if this coder requires secure coding. Secure coders check a list of allowed classes before decoding objects, and all objects must implement NSSecureCoding.
@property (readonly) BOOL requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

// Specify what the expected class of the allocated object is. If the coder responds YES to -requiresSecureCoding, then an exception will be thrown if the class to be decoded does not implement NSSecureCoding or is not isKindOfClass: of the argument. If the coder responds NO to -requiresSecureCoding, then the class argument is ignored and no check of the class of the decoded object is performed, exactly as if decodeObjectForKey: had been called.
- (nullable id)decodeObjectOfClass:(Class)aClass forKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);
- (nullable id)decodeTopLevelObjectOfClass:(Class)aClass forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeTopLevelObjectOfClass(_:,forKey:) throws instead");

// The class of the object may be any class in the provided NSSet, or a subclass of any class in the set. Otherwise, the behavior is the same as -decodeObjectOfClass:forKey:.
- (nullable id)decodeObjectOfClasses:(nullable NSSet<Class> *)classes forKey:(NSString *)key NS_AVAILABLE(10_8, 6_0) NS_REFINED_FOR_SWIFT;
- (nullable id)decodeTopLevelObjectOfClasses:(nullable NSSet<Class> *)classes forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeObjectOfClasses(_:,forKey:) throws' instead");

// Calls -decodeObjectOfClasses:forKey: with a set allowing only property list types.
- (nullable id)decodePropertyListForKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);

// Get the current set of allowed classes.
@property (nullable, readonly, copy) NSSet<Class> *allowedClasses NS_AVAILABLE(10_8, 6_0);

// Record that the entire decode has failed, in lieu of raising an exception
- (void)failWithError:(NSError *)error NS_AVAILABLE(10_11, 9_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
FOUNDATION_EXPORT NSObject * __nullable NXReadNSObjectFromCoder(NSCoder *decoder) NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
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
    
- (nullable id)decodeNXObject NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Reads an object previously written with -encodeNXObject:. No
   sharing is done across separate -decodeNXObject. Callers must
   have implemented an -initWithCoder:, which parallels the -read:
   methods, on all of their classes which may be touched by this
   operation. Object's -awakeAfterUsingCoder: compatibility method
   will take care of calling -awake and -finishUnarchiving. The
   returned object is autoreleased. */

@end
#endif

NS_ASSUME_NONNULL_END
