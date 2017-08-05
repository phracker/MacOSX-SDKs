/*	NSData.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString, NSURL, NSError;

NS_ASSUME_NONNULL_BEGIN

/****************	Read/Write Options	****************/

typedef NS_OPTIONS(NSUInteger, NSDataReadingOptions) {
    NSDataReadingMappedIfSafe =   1UL << 0,	// Hint to map the file in if possible and safe
    NSDataReadingUncached = 1UL << 1,	// Hint to get the file not to be cached in the kernel
    NSDataReadingMappedAlways NS_ENUM_AVAILABLE(10_7, 5_0) = 1UL << 3,	// Hint to map the file in if possible. This takes precedence over NSDataReadingMappedIfSafe if both are given.
    
    // Options with old names for NSData reading methods. Please stop using these old names.
    NSDataReadingMapped = NSDataReadingMappedIfSafe,	// Deprecated name for NSDataReadingMappedIfSafe
    NSMappedRead = NSDataReadingMapped,			// Deprecated name for NSDataReadingMapped
    NSUncachedRead = NSDataReadingUncached		// Deprecated name for NSDataReadingUncached
};

typedef NS_OPTIONS(NSUInteger, NSDataWritingOptions) {
    NSDataWritingAtomic = 1UL << 0,	// Hint to use auxiliary file when saving; equivalent to atomically:YES
    NSDataWritingWithoutOverwriting NS_ENUM_AVAILABLE(10_8, 6_0) = 1UL << 1, // Hint to  prevent overwriting an existing file. Cannot be combined with NSDataWritingAtomic.

    NSDataWritingFileProtectionNone NS_ENUM_AVAILABLE_IOS(4_0)                                  = 0x10000000,
    NSDataWritingFileProtectionComplete NS_ENUM_AVAILABLE_IOS(4_0)                              = 0x20000000,
    NSDataWritingFileProtectionCompleteUnlessOpen NS_ENUM_AVAILABLE_IOS(5_0)                    = 0x30000000,
    NSDataWritingFileProtectionCompleteUntilFirstUserAuthentication NS_ENUM_AVAILABLE_IOS(5_0)  = 0x40000000,
    NSDataWritingFileProtectionMask NS_ENUM_AVAILABLE_IOS(4_0)                                  = 0xf0000000,

    // Options with old names for NSData writing methods. Please stop using these old names.
    NSAtomicWrite = NSDataWritingAtomic	    // Deprecated name for NSDataWritingAtomic
};


/****************	Data Search Options	****************/

typedef NS_OPTIONS(NSUInteger, NSDataSearchOptions) {
    NSDataSearchBackwards = 1UL << 0,
    NSDataSearchAnchored = 1UL << 1
} NS_ENUM_AVAILABLE(10_6, 4_0);


/****************        Base 64 Options	****************/

typedef NS_OPTIONS(NSUInteger, NSDataBase64EncodingOptions) {
    // Use zero or one of the following to control the maximum line length after which a line ending is inserted. No line endings are inserted by default.
    NSDataBase64Encoding64CharacterLineLength = 1UL << 0,
    NSDataBase64Encoding76CharacterLineLength = 1UL << 1,

    // Use zero or more of the following to specify which kind of line ending is inserted. The default line ending is CR LF.
    NSDataBase64EncodingEndLineWithCarriageReturn = 1UL << 4,
    NSDataBase64EncodingEndLineWithLineFeed = 1UL << 5,

} NS_ENUM_AVAILABLE(10_9, 7_0);


typedef NS_OPTIONS(NSUInteger, NSDataBase64DecodingOptions) {
    // Use the following option to modify the decoding algorithm so that it ignores unknown non-Base64 bytes, including line ending characters.
    NSDataBase64DecodingIgnoreUnknownCharacters = 1UL << 0
} NS_ENUM_AVAILABLE(10_9, 7_0);


/****************	Immutable Data		****************/

@interface NSData : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

@property (readonly) NSUInteger length;
/*
 The -bytes method returns a pointer to a contiguous region of memory managed by the receiver.
 If the regions of memory represented by the receiver are already contiguous, it does so in O(1) time, otherwise it may take longer
 Using -enumerateByteRangesUsingBlock: will be efficient for both contiguous and discontiguous data.
 */
@property (readonly) const void *bytes NS_RETURNS_INNER_POINTER;

@end

@interface NSData (NSExtendedData)

@property (readonly, copy) NSString *description;
- (void)getBytes:(void *)buffer length:(NSUInteger)length;
- (void)getBytes:(void *)buffer range:(NSRange)range;
- (BOOL)isEqualToData:(NSData *)other;
- (NSData *)subdataWithRange:(NSRange)range;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if the url is not of a type the supports atomic writes
- (BOOL)writeToFile:(NSString *)path options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
- (BOOL)writeToURL:(NSURL *)url options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
- (NSRange)rangeOfData:(NSData *)dataToFind options:(NSDataSearchOptions)mask range:(NSRange)searchRange NS_AVAILABLE(10_6, 4_0);

/*
 'block' is called once for each contiguous region of memory in the receiver (once total for contiguous NSDatas), until either all bytes have been enumerated, or the 'stop' parameter is set to YES.
 */
- (void) enumerateByteRangesUsingBlock:(void (NS_NOESCAPE ^)(const void *bytes, NSRange byteRange, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);

@end

@interface NSData (NSDataCreation)

+ (instancetype)data;
+ (instancetype)dataWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path;
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url;
- (instancetype)initWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length deallocator:(nullable void (^)(void *bytes, NSUInteger length))deallocator NS_AVAILABLE(10_9, 7_0);
- (nullable instancetype)initWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
- (nullable instancetype)initWithContentsOfFile:(NSString *)path;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
- (instancetype)initWithData:(NSData *)data;
+ (instancetype)dataWithData:(NSData *)data;

@end

@interface NSData (NSDataBase64Encoding)

/* Create an NSData from a Base-64 encoded NSString using the given options. By default, returns nil when the input is not recognized as valid Base-64.
*/
- (nullable instancetype)initWithBase64EncodedString:(NSString *)base64String options:(NSDataBase64DecodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create a Base-64 encoded NSString from the receiver's contents using the given options.
*/
- (NSString *)base64EncodedStringWithOptions:(NSDataBase64EncodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create an NSData from a Base-64, UTF-8 encoded NSData. By default, returns nil when the input is not recognized as valid Base-64.
*/
- (nullable instancetype)initWithBase64EncodedData:(NSData *)base64Data options:(NSDataBase64DecodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create a Base-64, UTF-8 encoded NSData from the receiver's contents using the given options.
*/
- (NSData *)base64EncodedDataWithOptions:(NSDataBase64EncodingOptions)options NS_AVAILABLE(10_9, 7_0);

@end


@interface NSData (NSDeprecated)

- (void)getBytes:(void *)buffer NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "This method is unsafe because it could potentially cause buffer overruns. Use -getBytes:length: instead.");
+ (nullable id)dataWithContentsOfMappedFile:(NSString *)path NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use +dataWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.");
- (nullable id)initWithContentsOfMappedFile:(NSString *)path  NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use -initWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.");

/* These methods first appeared in NSData.h on OS X 10.9 and iOS 7.0. They are deprecated in the same releases in favor of the methods in the NSDataBase64Encoding category. However, these methods have existed for several releases, so they may be used for applications targeting releases prior to OS X 10.9 and iOS 7.0.
*/
- (nullable id)initWithBase64Encoding:(NSString *)base64String NS_DEPRECATED(10_6, 10_9, 4_0, 7_0);
- (NSString *)base64Encoding NS_DEPRECATED(10_6, 10_9, 4_0, 7_0);

@end

/****************	Mutable Data		****************/

@interface NSMutableData : NSData

@property (readonly) void *mutableBytes NS_RETURNS_INNER_POINTER;
@property NSUInteger length;

@end

@interface NSMutableData (NSExtendedMutableData)

- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;
- (void)appendData:(NSData *)other;
- (void)increaseLengthBy:(NSUInteger)extraLength;
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
- (void)resetBytesInRange:(NSRange)range;
- (void)setData:(NSData *)data;
- (void)replaceBytesInRange:(NSRange)range withBytes:(nullable const void *)replacementBytes length:(NSUInteger)replacementLength;

@end

@interface NSMutableData (NSMutableDataCreation)

+ (nullable instancetype)dataWithCapacity:(NSUInteger)aNumItems;
+ (nullable instancetype)dataWithLength:(NSUInteger)length;
- (nullable instancetype)initWithCapacity:(NSUInteger)capacity;
- (nullable instancetype)initWithLength:(NSUInteger)length;

@end

/****************	    Purgeable Data	****************/

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSPurgeableData : NSMutableData <NSDiscardableContent> {
@private
    NSUInteger _length;
    int32_t _accessCount;
    uint8_t _private[32];
    void *_reserved;
}

@end

NS_ASSUME_NONNULL_END
