/*	NSStream.h
        Copyright (c) 2003-2005, Apple, Inc. All rights reserved
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSData, NSDictionary, NSError, NSHost, NSInputStream, NSRunLoop, NSString, NSOutputStream;

typedef enum {
    NSStreamStatusNotOpen = 0,
    NSStreamStatusOpening = 1,
    NSStreamStatusOpen = 2,
    NSStreamStatusReading = 3,
    NSStreamStatusWriting = 4,
    NSStreamStatusAtEnd = 5,
    NSStreamStatusClosed = 6,
    NSStreamStatusError = 7
} NSStreamStatus;

typedef enum {
    NSStreamEventNone = 0,
    NSStreamEventOpenCompleted = 1 << 0,
    NSStreamEventHasBytesAvailable = 1 << 1,
    NSStreamEventHasSpaceAvailable = 1 << 2,
    NSStreamEventErrorOccurred = 1 << 3,
    NSStreamEventEndEncountered = 1 << 4
} NSStreamEvent;

// NSStream is an abstract class encapsulating the common API to NSInputStream and NSOutputStream.
// Subclassers of NSInputStream and NSOutputStream must also implement these methods.
@interface NSStream : NSObject
- (void)open;
- (void)close;

- (id)delegate;
- (void)setDelegate:(id)delegate;
    // By default, a stream is its own delegate, and subclassers of NSInputStream and NSOutputStream must maintain this contract. [someStream setDelegate:nil] must restore this behavior. As usual, delegates are not retained.

- (id)propertyForKey:(NSString *)key;
- (BOOL)setProperty:(id)property forKey:(NSString *)key;

- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

- (NSStreamStatus)streamStatus;
- (NSError *)streamError;
@end

// NSInputStream is an abstract class representing the base functionality of a read stream.
// Subclassers are required to implement these methods.
@interface NSInputStream : NSStream
- (int)read:(uint8_t *)buffer maxLength:(unsigned int)len;
    // reads up to length bytes into the supplied buffer, which must be at least of size len. Returns the actual number of bytes read.

- (BOOL)getBuffer:(uint8_t **)buffer length:(unsigned int *)len;
    // returns in O(1) a pointer to the buffer in 'buffer' and by reference in 'len' how many bytes are available. This buffer is only valid until the next stream operation. Subclassers may return NO for this if it is not appropriate for the stream type. This may return NO if the buffer is not available.

- (BOOL)hasBytesAvailable;
    // returns YES if the stream has bytes available or if it impossible to tell without actually doing the read.
@end

// NSOutputStream is an abstract class representing the base functionality of a write stream.
// Subclassers are required to implement these methods.
@interface NSOutputStream : NSStream
- (int)write:(const uint8_t *)buffer maxLength:(unsigned int)len;
    // writes the bytes from the specified buffer to the stream up to len bytes. Returns the number of bytes actually written.

- (BOOL)hasSpaceAvailable;
    // returns YES if the stream can be written to or if it is impossible to tell without actually doing the write.
@end

@interface NSStream (NSSocketStreamCreationExtensions)
+ (void)getStreamsToHost:(NSHost *)host port:(int)port inputStream:(NSInputStream **)inputStream outputStream:(NSOutputStream **)outputStream;
@end

// The NSInputStreamExtensions category contains additional initializers and convenience routines for dealing with NSInputStreams.
@interface NSInputStream (NSInputStreamExtensions)
- (id)initWithData:(NSData *)data;
- (id)initWithFileAtPath:(NSString *)path;

+ (id)inputStreamWithData:(NSData *)data;
+ (id)inputStreamWithFileAtPath:(NSString *)path;
@end

// The NSOutputStreamExtensions category contains additiona initializers and convenience routines for dealing with NSOutputStreams.
@interface NSOutputStream (NSOutputStreamExtensions)
- (id)initToMemory;
- (id)initToBuffer:(uint8_t *)buffer capacity:(unsigned int)capacity;
- (id)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;

+ (id)outputStreamToMemory;
+ (id)outputStreamToBuffer:(uint8_t *)buffer capacity:(unsigned int)capacity;
+ (id)outputStreamToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
@end

@interface NSObject (NSStreamDelegateEventExtensions)
- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode;
@end

// NSString constants for the propertyForKey/setProperty:forKey: API
// String constants for the setting of the socket security level.
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// use this as the key for setting one of the following values for the security level of the target stream.

FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelNone		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelSSLv2		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelSSLv3		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelTLSv1		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelNegotiatedSSL	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyConfigurationKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// Value is an NSDictionary containing the key/value pairs below. The dictionary returned from SystemConfiguration for SOCKS proxies will work without alteration.

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyHostKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value is an NSString
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyPortKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value is an NSNumber
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersionKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value is one of NSStreamSOCKSProxyVersion4 or NSStreamSOCKSProxyVersion5
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyUserKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value is an NSString
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyPasswordKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value is an NSString

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersion4			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value for NSStreamSOCKProxyVersionKey
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersion5			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value for NSStreamSOCKProxyVersionKey

FOUNDATION_EXPORT NSString * const NSStreamDataWrittenToMemoryStreamKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Key for obtaining the data written to a memory stream.

FOUNDATION_EXPORT NSString * const NSStreamFileCurrentOffsetKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Value is an NSNumber representing the current absolute offset of the stream.

// NSString constants for error domains.
FOUNDATION_EXPORT NSString * const NSStreamSocketSSLErrorDomain			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // SSL errors are to be interpreted via <Security/SecureTransport.h>
FOUNDATION_EXPORT NSString * const NSStreamSOCKSErrorDomain			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#endif		// Availability guard
