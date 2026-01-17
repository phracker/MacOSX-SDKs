/*	NSKeyedArchiver.h
	Copyright (c) 2001-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>
#import <Foundation/NSPropertyList.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <Foundation/NSGeometry.h>
#endif


@class NSArray<ObjectType>, NSMutableData, NSData, NSString;
@protocol NSKeyedArchiverDelegate, NSKeyedUnarchiverDelegate;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSInvalidArchiveOperationException;
FOUNDATION_EXPORT NSString * const NSInvalidUnarchiveOperationException;
// Archives created using the class method archivedRootDataWithObject used this key for the root object in the hierarchy of encoded objects. The NSKeyedUnarchiver class method unarchiveObjectWithData: will look for this root key as well. You can also use it as the key for the root object in your own archives.
FOUNDATION_EXPORT NSString * const NSKeyedArchiveRootObjectKey NS_AVAILABLE(10_9, 7_0);

@interface NSKeyedArchiver : NSCoder {
@private
    void *_stream;
    NSUInteger _flags;
    id _delegate;
    id _containers;
    id _objects;
    id _objRefMap;
    id _replacementMap;
    id _classNameMap;
    id _conditionals;
    id _classes;
    NSUInteger _genericKey;
    void *_cache;
    NSUInteger _cacheSize;
    NSUInteger _estimatedCount;
    void *_reserved2;
    id _visited;
    void *  __strong _reserved0;
}

+ (NSData *)archivedDataWithRootObject:(id)rootObject;
+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path;

- (instancetype)initForWritingWithMutableData:(NSMutableData *)data;

@property (nullable, assign) id <NSKeyedArchiverDelegate> delegate;

@property NSPropertyListFormat outputFormat;

- (void)finishEncoding;

+ (void)setClassName:(nullable NSString *)codedName forClass:(Class)cls;
- (void)setClassName:(nullable NSString *)codedName forClass:(Class)cls;
	// During encoding, the coder first checks with the coder's
	// own table, then if there was no mapping there, the class's.

+ (nullable NSString *)classNameForClass:(Class)cls;
- (nullable NSString *)classNameForClass:(Class)cls;

- (void)encodeObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeConditionalObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeBool:(BOOL)boolv forKey:(NSString *)key;
- (void)encodeInt:(int)intv forKey:(NSString *)key;	// native int
- (void)encodeInt32:(int32_t)intv forKey:(NSString *)key;
- (void)encodeInt64:(int64_t)intv forKey:(NSString *)key;
- (void)encodeFloat:(float)realv forKey:(NSString *)key;
- (void)encodeDouble:(double)realv forKey:(NSString *)key;
- (void)encodeBytes:(nullable const uint8_t *)bytesp length:(NSUInteger)lenv forKey:(NSString *)key;

// Enables secure coding support on this keyed archiver. You do not need to enable secure coding on the archiver to enable secure coding on the unarchiver. Enabling secure coding on the archiver is a way for you to be sure that all classes that are encoded conform with NSSecureCoding (it will throw an exception if a class which does not NSSecureCoding is archived). Note that the getter is on the superclass, NSCoder. See NSCoder for more information about secure coding.
@property (readwrite) BOOL requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

@end

@interface NSKeyedUnarchiver : NSCoder {
@private
    id _delegate;
    uint32_t _flags;
    id _objRefMap;
    id _replacementMap;
    id _nameClassMap;
    id _tmpRefObjMap;
    id _refObjMap;
    int32_t _genericKey;
    id _data;
    void *_offsetData;
    id _containers;
    id _objects;
    const uint8_t *_bytes;
    uint64_t _len;
    id _helper;
    void *  __strong _reserved0;
}

+ (nullable id)unarchiveObjectWithData:(NSData *)data;
+ (nullable id)unarchiveTopLevelObjectWithData:(NSData *)data error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'unarchiveTopLevelObjectWithData(_:) throws' instead");
+ (nullable id)unarchiveObjectWithFile:(NSString *)path;

- (instancetype)initForReadingWithData:(NSData *)data;

@property (nullable, assign) id <NSKeyedUnarchiverDelegate> delegate;

- (void)finishDecoding;

+ (void)setClass:(nullable Class)cls forClassName:(NSString *)codedName;
- (void)setClass:(nullable Class)cls forClassName:(NSString *)codedName;
	// During decoding, the coder first checks with the coder's
	// own table, then if there was no mapping there, the class's.

+ (nullable Class)classForClassName:(NSString *)codedName;
- (nullable Class)classForClassName:(NSString *)codedName;

- (BOOL)containsValueForKey:(NSString *)key;

- (nullable id)decodeObjectForKey:(NSString *)key;
- (BOOL)decodeBoolForKey:(NSString *)key;
- (int)decodeIntForKey:(NSString *)key;		// may raise a range exception
- (int32_t)decodeInt32ForKey:(NSString *)key;
- (int64_t)decodeInt64ForKey:(NSString *)key;
- (float)decodeFloatForKey:(NSString *)key;
- (double)decodeDoubleForKey:(NSString *)key;
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(nullable NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;	// returned bytes immutable, and they go away with the unarchiver, not the containing autorelease pool

// Enables secure coding support on this keyed unarchiver. When enabled, anarchiving a disallowed class throws an exception. Once enabled, attempting to set requiresSecureCoding to NO will throw an exception. This is to prevent classes from selectively turning secure coding off. This is designed to be set once at the top level and remain on. Note that the getter is on the superclass, NSCoder. See NSCoder for more information about secure coding.
@property (readwrite) BOOL requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

@end

@protocol NSKeyedArchiverDelegate <NSObject>
@optional

// substitution
- (nullable id)archiver:(NSKeyedArchiver *)archiver willEncodeObject:(id)object;
	// Informs the delegate that the object is about to be encoded.  The delegate
	// either returns this object or can return a different object to be encoded
	// instead.  The delegate can also fiddle with the coder state.  If the delegate
	// returns nil, nil is encoded.  This method is called after the original object
        // may have replaced itself with replacementObjectForKeyedArchiver:.
        // This method is not called for an object once a replacement mapping has been
        // setup for that object (either explicitly, or because the object has previously
        // been encoded).  This is also not called when nil is about to be encoded.
        // This method is called whether or not the object is being encoded conditionally.

- (void)archiver:(NSKeyedArchiver *)archiver didEncodeObject:(nullable id)object;
	// Informs the delegate that the given object has been encoded.  The delegate
	// might restore some state it had fiddled previously, or use this to keep
	// track of the objects which are encoded.  The object may be nil.  Not called
	// for conditional objects until they are really encoded (if ever).

// notification
- (void)archiver:(NSKeyedArchiver *)archiver willReplaceObject:(nullable id)object withObject:(nullable id)newObject;
	// Informs the delegate that the newObject is being substituted for the
	// object. This is also called when the delegate itself is doing/has done
	// the substitution. The delegate may use this method if it is keeping track
	// of the encoded or decoded objects.

- (void)archiverWillFinish:(NSKeyedArchiver *)archiver;
	// Notifies the delegate that encoding is about to finish.

- (void)archiverDidFinish:(NSKeyedArchiver *)archiver;
	// Notifies the delegate that encoding has finished.

@end

@protocol NSKeyedUnarchiverDelegate <NSObject>
@optional

// error handling
- (nullable Class)unarchiver:(NSKeyedUnarchiver *)unarchiver cannotDecodeObjectOfClassName:(NSString *)name originalClasses:(NSArray<NSString *> *)classNames;
	// Informs the delegate that the named class is not available during decoding.
	// The delegate may, for example, load some code to introduce the class to the
	// runtime and return it, or substitute a different class object.  If the
	// delegate returns nil, unarchiving aborts with an exception.  The first class
        // name string in the array is the class of the encoded object, the second is
        // the immediate superclass, and so on.

// substitution
- (nullable id)unarchiver:(NSKeyedUnarchiver *)unarchiver didDecodeObject:(nullable id) NS_RELEASES_ARGUMENT object NS_RETURNS_RETAINED;
	// Informs the delegate that the object has been decoded.  The delegate
	// either returns this object or can return a different object to replace
	// the decoded one.  The object may be nil.  If the delegate returns nil,
        // the decoded value will be unchanged (that is, the original object will be
        // decoded). The delegate may use this to keep track of the decoded objects.

// notification
- (void)unarchiver:(NSKeyedUnarchiver *)unarchiver willReplaceObject:(id)object withObject:(id)newObject;
	// Informs the delegate that the newObject is being substituted for the
	// object. This is also called when the delegate itself is doing/has done
	// the substitution. The delegate may use this method if it is keeping track
	// of the encoded or decoded objects.

- (void)unarchiverWillFinish:(NSKeyedUnarchiver *)unarchiver;
	// Notifies the delegate that decoding is about to finish.

- (void)unarchiverDidFinish:(NSKeyedUnarchiver *)unarchiver;
	// Notifies the delegate that decoding has finished.

@end

@interface NSObject (NSKeyedArchiverObjectSubstitution)

@property (nullable, readonly) Class classForKeyedArchiver;
	// Implemented by classes to substitute a new class for instances during
	// encoding.  The object will be encoded as if it were a member of the
	// returned class.  The results of this method are overridden by the archiver
        // class and instance name<->class encoding tables.  If nil is returned,
        // the result of this method is ignored.  This method returns the result of
	// [self classForArchiver] by default, NOT -classForCoder as might be
	// expected.  This is a concession to source compatibility.

- (nullable id)replacementObjectForKeyedArchiver:(NSKeyedArchiver *)archiver;
	// Implemented by classes to substitute new instances for the receiving
	// instance during encoding.  The returned object will be encoded instead
	// of the receiver (if different).  This method is called only if no
	// replacement mapping for the object has been set up in the archiver yet
        // (for example, due to a previous call of replacementObjectForKeyedArchiver:
        // to that object).  This method returns the result of
	// [self replacementObjectForArchiver:nil] by default, NOT
	// -replacementObjectForCoder: as might be expected.  This is a concession
	// to source compatibility.


+ (NSArray<NSString *> *)classFallbacksForKeyedArchiver;


@end

@interface NSObject (NSKeyedUnarchiverObjectSubstitution)

+ (Class)classForKeyedUnarchiver;
	// Implemented by classes to substitute a new class during decoding.
        // Objects of the class will be decoded as members of the returned
        // class.  This method overrides the results of the unarchiver's class and
        // instance name<->class encoding tables.  Returns self by default.

@end

NS_ASSUME_NONNULL_END
