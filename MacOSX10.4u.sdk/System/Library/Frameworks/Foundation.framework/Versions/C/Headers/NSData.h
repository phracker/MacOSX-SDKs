/*	NSData.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString, NSURL, NSError;


/****************	Read/Write Options	****************/

enum {	// Options for NSData reading methods
    NSMappedRead = 1,	    // Hint to map the file in if possible
    NSUncachedRead = 2	    // Hint to get the file not to be cached in the kernel
};

enum {	// Options for NSData writing methods
    NSAtomicWrite = 1	    // Hint to use auxiliary file when saving; equivalent to atomically:YES
};



/****************	Immutable Data		****************/

@interface NSData : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (unsigned)length;
- (const void *)bytes;

@end

@interface NSData (NSExtendedData)

- (NSString *)description;
- (void)getBytes:(void *)buffer;
- (void)getBytes:(void *)buffer length:(unsigned)length;
- (void)getBytes:(void *)buffer range:(NSRange)range;
- (BOOL)isEqualToData:(NSData *)other;
- (NSData *)subdataWithRange:(NSRange)range;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if the url is not of a type the supports atomic writes
#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)writeToFile:(NSString *)path options:(unsigned)writeOptionsMask error:(NSError **)errorPtr;
- (BOOL)writeToURL:(NSURL *)url options:(unsigned)writeOptionsMask error:(NSError **)errorPtr;
#endif

@end

@interface NSData (NSDataCreation)

+ (id)data;
+ (id)dataWithBytes:(const void *)bytes length:(unsigned)length;
+ (id)dataWithBytesNoCopy:(void *)bytes length:(unsigned)length;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (id)dataWithBytesNoCopy:(void *)bytes length:(unsigned)length freeWhenDone:(BOOL)b;
#endif
#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (id)dataWithContentsOfFile:(NSString *)path options:(unsigned)readOptionsMask error:(NSError **)errorPtr;
+ (id)dataWithContentsOfURL:(NSURL *)url options:(unsigned)readOptionsMask error:(NSError **)errorPtr;
#endif
+ (id)dataWithContentsOfFile:(NSString *)path;
+ (id)dataWithContentsOfURL:(NSURL *)url;
+ (id)dataWithContentsOfMappedFile:(NSString *)path;
- (id)initWithBytes:(const void *)bytes length:(unsigned)length;
- (id)initWithBytesNoCopy:(void *)bytes length:(unsigned)length;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (id)initWithBytesNoCopy:(void *)bytes length:(unsigned)length freeWhenDone:(BOOL)b;
#endif
#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (id)initWithContentsOfFile:(NSString *)path options:(unsigned)readOptionsMask error:(NSError **)errorPtr;
- (id)initWithContentsOfURL:(NSURL *)url options:(unsigned)readOptionsMask error:(NSError **)errorPtr;
#endif
- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithContentsOfURL:(NSURL *)url;
- (id)initWithContentsOfMappedFile:(NSString *)path;
- (id)initWithData:(NSData *)data;
+ (id)dataWithData:(NSData *)data;

@end

/****************	Mutable Data		****************/

@interface NSMutableData : NSData

- (void *)mutableBytes;
- (void)setLength:(unsigned)length;

@end

@interface NSMutableData (NSExtendedMutableData)

- (void)appendBytes:(const void *)bytes length:(unsigned)length;
- (void)appendData:(NSData *)other;
- (void)increaseLengthBy:(unsigned)extraLength;
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
- (void)resetBytesInRange:(NSRange)range;
- (void)setData:(NSData *)data;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)replacementBytes length:(unsigned)replacementLength;
#endif

@end

@interface NSMutableData (NSMutableDataCreation)

+ (id)dataWithCapacity:(unsigned)aNumItems;
+ (id)dataWithLength:(unsigned)length;
- (id)initWithCapacity:(unsigned)capacity;
- (id)initWithLength:(unsigned)length;

@end

