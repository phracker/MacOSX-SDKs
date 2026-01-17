/*	NSStream.h
        Copyright (c) 2003-2016, Apple Inc. All rights reserved
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>

@class NSData, NSDictionary, NSError, NSHost, NSInputStream, NSOutputStream, NSRunLoop, NSString, NSURL;
@protocol NSStreamDelegate;

typedef NSString * NSStreamPropertyKey NS_EXTENSIBLE_STRING_ENUM;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSStreamStatus) {
    NSStreamStatusNotOpen = 0,
    NSStreamStatusOpening = 1,
    NSStreamStatusOpen = 2,
    NSStreamStatusReading = 3,
    NSStreamStatusWriting = 4,
    NSStreamStatusAtEnd = 5,
    NSStreamStatusClosed = 6,
    NSStreamStatusError = 7
};

typedef NS_OPTIONS(NSUInteger, NSStreamEvent) {
    NSStreamEventNone = 0,
    NSStreamEventOpenCompleted = 1UL << 0,
    NSStreamEventHasBytesAvailable = 1UL << 1,
    NSStreamEventHasSpaceAvailable = 1UL << 2,
    NSStreamEventErrorOccurred = 1UL << 3,
    NSStreamEventEndEncountered = 1UL << 4
};

// NSStream is an abstract class encapsulating the common API to NSInputStream and NSOutputStream.
// Subclassers of NSInputStream and NSOutputStream must also implement these methods.
@interface NSStream : NSObject
- (void)open;
- (void)close;

@property (nullable, assign) id <NSStreamDelegate> delegate;
    // By default, a stream is its own delegate, and subclassers of NSInputStream and NSOutputStream must maintain this contract. [someStream setDelegate:nil] must restore this behavior. As usual, delegates are not retained.

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
- (nullable id)propertyForKey:(NSStreamPropertyKey)key;
- (BOOL)setProperty:(nullable id)property forKey:(NSStreamPropertyKey)key;
#else
- (nullable id)propertyForKey:(NSString *)key;
- (BOOL)setProperty:(nullable id)property forKey:(NSString *)key;
#endif

- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

@property (readonly) NSStreamStatus streamStatus;
@property (nullable, readonly, copy) NSError *streamError;
@end

// NSInputStream is an abstract class representing the base functionality of a read stream.
// Subclassers are required to implement these methods.
@interface NSInputStream : NSStream
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;
    // reads up to length bytes into the supplied buffer, which must be at least of size len. Returns the actual number of bytes read.

- (BOOL)getBuffer:(uint8_t * _Nullable * _Nonnull)buffer length:(NSUInteger *)len;
    // returns in O(1) a pointer to the buffer in 'buffer' and by reference in 'len' how many bytes are available. This buffer is only valid until the next stream operation. Subclassers may return NO for this if it is not appropriate for the stream type. This may return NO if the buffer is not available.

@property (readonly) BOOL hasBytesAvailable;
    // returns YES if the stream has bytes available or if it impossible to tell without actually doing the read.

- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;

@end

// NSOutputStream is an abstract class representing the base functionality of a write stream.
// Subclassers are required to implement these methods.
@interface NSOutputStream : NSStream
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;
    // writes the bytes from the specified buffer to the stream up to len bytes. Returns the number of bytes actually written.

@property (readonly) BOOL hasSpaceAvailable;
    // returns YES if the stream can be written to or if it is impossible to tell without actually doing the write.

- (instancetype)initToMemory NS_DESIGNATED_INITIALIZER;
- (instancetype)initToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;

@end


@interface NSStream (NSSocketStreamCreationExtensions)

+ (void)getStreamsToHostWithName:(NSString *)hostname port:(NSInteger)port inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream NS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
+ (void)getStreamsToHost:(NSHost *)host port:(NSInteger)port inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream NS_DEPRECATED_MAC(10_3, 10_10, "Please use getStreamsToHostWithName:port:inputStream:outputStream: instead");
#endif

@end

@interface NSStream (NSStreamBoundPairCreationExtensions)
+ (void)getBoundStreamsWithBufferSize:(NSUInteger)bufferSize inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream NS_AVAILABLE(10_10, 8_0);
@end

// The NSInputStreamExtensions category contains additional initializers and convenience routines for dealing with NSInputStreams.
@interface NSInputStream (NSInputStreamExtensions)
- (nullable instancetype)initWithFileAtPath:(NSString *)path;

+ (nullable instancetype)inputStreamWithData:(NSData *)data;
+ (nullable instancetype)inputStreamWithFileAtPath:(NSString *)path;
+ (nullable instancetype)inputStreamWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
@end

// The NSOutputStreamExtensions category contains additional initializers and convenience routines for dealing with NSOutputStreams.
@interface NSOutputStream (NSOutputStreamExtensions)
- (nullable instancetype)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;

+ (instancetype)outputStreamToMemory;
+ (instancetype)outputStreamToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity;
+ (instancetype)outputStreamToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
+ (nullable instancetype)outputStreamWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_AVAILABLE(10_6, 4_0);
@end

@protocol NSStreamDelegate <NSObject>
@optional
- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode;
@end

// NSString constants for the propertyForKey/setProperty:forKey: API
// String constants for the setting of the socket security level.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamSocketSecurityLevelKey		NS_AVAILABLE(10_3, 2_0);	// use this as the key for setting one of the following values for the security level of the target stream.

typedef NSString * NSStreamSocketSecurityLevel NS_STRING_ENUM;

FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelNone		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelSSLv2		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelSSLv3		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelTLSv1		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelNegotiatedSSL	NS_AVAILABLE(10_3, 2_0);

FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamSOCKSProxyConfigurationKey		NS_AVAILABLE(10_3, 2_0);	// Value is an NSDictionary containing the key/value pairs below. The dictionary returned from SystemConfiguration for SOCKS proxies will work without alteration.

typedef NSString * NSStreamSOCKSProxyConfiguration NS_STRING_ENUM;

FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyHostKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyPortKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSNumber
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyVersionKey		NS_AVAILABLE(10_3, 2_0);
    // Value is one of NSStreamSOCKSProxyVersion4 or NSStreamSOCKSProxyVersion5
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyUserKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyPasswordKey		NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString

typedef NSString * NSStreamSOCKSProxyVersion NS_STRING_ENUM;

FOUNDATION_EXPORT NSStreamSOCKSProxyVersion const NSStreamSOCKSProxyVersion4			NS_AVAILABLE(10_3, 2_0);
    // Value for NSStreamSOCKProxyVersionKey
FOUNDATION_EXPORT NSStreamSOCKSProxyVersion const NSStreamSOCKSProxyVersion5			NS_AVAILABLE(10_3, 2_0);
    // Value for NSStreamSOCKProxyVersionKey

FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamDataWrittenToMemoryStreamKey	NS_AVAILABLE(10_3, 2_0);
    // Key for obtaining the data written to a memory stream.

FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamFileCurrentOffsetKey		NS_AVAILABLE(10_3, 2_0);
    // Value is an NSNumber representing the current absolute offset of the stream.

// NSString constants for error domains.
FOUNDATION_EXPORT NSErrorDomain const NSStreamSocketSSLErrorDomain			NS_AVAILABLE(10_3, 2_0);
    // SSL errors are to be interpreted via <Security/SecureTransport.h>
FOUNDATION_EXPORT NSErrorDomain const NSStreamSOCKSErrorDomain			NS_AVAILABLE(10_3, 2_0);

// Property key to specify the type of service for the stream.  This
// allows the system to properly handle the request with respect to
// routing, suspension behavior and other networking related attributes
// appropriate for the given service type.  The service types supported
// are documented below.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamNetworkServiceType		    NS_AVAILABLE(10_7, 4_0);

typedef NSString * NSStreamNetworkServiceTypeValue NS_STRING_ENUM;

// Supported network service types:
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVoIP	    NS_AVAILABLE(10_7, 4_0);
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVideo	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeBackground	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVoice	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeCallSignaling    API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

NS_ASSUME_NONNULL_END
