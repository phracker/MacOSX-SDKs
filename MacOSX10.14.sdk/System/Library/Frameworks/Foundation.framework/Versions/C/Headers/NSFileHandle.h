/*	NSFileHandle.h
	Copyright (c) 1995-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSException.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSRunLoop.h>

@class NSString, NSData, NSError;

NS_ASSUME_NONNULL_BEGIN

@interface NSFileHandle : NSObject <NSSecureCoding>

@property (readonly, copy) NSData *availableData;

- (NSData *)readDataToEndOfFile;
- (NSData *)readDataOfLength:(NSUInteger)length;

- (void)writeData:(NSData *)data;

@property (readonly) unsigned long long offsetInFile;
- (unsigned long long)seekToEndOfFile;
- (void)seekToFileOffset:(unsigned long long)offset;

- (void)truncateFileAtOffset:(unsigned long long)offset;
- (void)synchronizeFile;
- (void)closeFile;

- (instancetype)initWithFileDescriptor:(int)fd closeOnDealloc:(BOOL)closeopt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSFileHandle (NSFileHandleCreation)

@property (class, readonly, strong) NSFileHandle *fileHandleWithStandardInput;
@property (class, readonly, strong) NSFileHandle *fileHandleWithStandardOutput;
@property (class, readonly, strong) NSFileHandle *fileHandleWithStandardError;
@property (class, readonly, strong) NSFileHandle *fileHandleWithNullDevice;

+ (nullable instancetype)fileHandleForReadingAtPath:(NSString *)path;
+ (nullable instancetype)fileHandleForWritingAtPath:(NSString *)path;
+ (nullable instancetype)fileHandleForUpdatingAtPath:(NSString *)path;

+ (nullable instancetype)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
+ (nullable instancetype)fileHandleForWritingToURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
+ (nullable instancetype)fileHandleForUpdatingURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

FOUNDATION_EXPORT NSExceptionName const NSFileHandleOperationException;

FOUNDATION_EXPORT NSNotificationName const NSFileHandleReadCompletionNotification;
FOUNDATION_EXPORT NSNotificationName const NSFileHandleReadToEndOfFileCompletionNotification;
FOUNDATION_EXPORT NSNotificationName const NSFileHandleConnectionAcceptedNotification;
FOUNDATION_EXPORT NSNotificationName const NSFileHandleDataAvailableNotification;

FOUNDATION_EXPORT NSString * const NSFileHandleNotificationDataItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationFileHandleItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationMonitorModes API_DEPRECATED("Not supported", macos(10.0,10.7), ios(2.0,5.0), watchos(2.0,2.0), tvos(9.0,9.0));

@interface NSFileHandle (NSFileHandleAsynchronousAccess)

- (void)readInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
- (void)readInBackgroundAndNotify;

- (void)readToEndOfFileInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
- (void)readToEndOfFileInBackgroundAndNotify;

- (void)acceptConnectionInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
- (void)acceptConnectionInBackgroundAndNotify;

- (void)waitForDataInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
- (void)waitForDataInBackgroundAndNotify;

#ifdef __BLOCKS__
@property (nullable, copy) void (^readabilityHandler)(NSFileHandle *)  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
@property (nullable, copy) void (^writeabilityHandler)(NSFileHandle *) API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
#endif

@end

@interface NSFileHandle (NSFileHandlePlatformSpecific)

- (instancetype)initWithFileDescriptor:(int)fd;

@property (readonly) int fileDescriptor;

@end

@interface NSPipe : NSObject

@property (readonly, retain) NSFileHandle *fileHandleForReading;
@property (readonly, retain) NSFileHandle *fileHandleForWriting;

+ (NSPipe *)pipe;

@end

NS_ASSUME_NONNULL_END
