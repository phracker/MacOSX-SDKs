/*	NSFileHandle.h
	Copyright (c) 1995-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>

@class NSString, NSData, NSError;

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
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSFileHandle (NSFileHandleCreation)

+ (NSFileHandle *)fileHandleWithStandardInput;
+ (NSFileHandle *)fileHandleWithStandardOutput;
+ (NSFileHandle *)fileHandleWithStandardError;
+ (NSFileHandle *)fileHandleWithNullDevice;

+ (instancetype)fileHandleForReadingAtPath:(NSString *)path;
+ (instancetype)fileHandleForWritingAtPath:(NSString *)path;
+ (instancetype)fileHandleForUpdatingAtPath:(NSString *)path;

+ (instancetype)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
+ (instancetype)fileHandleForWritingToURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
+ (instancetype)fileHandleForUpdatingURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

@end

FOUNDATION_EXPORT NSString * const NSFileHandleOperationException;

FOUNDATION_EXPORT NSString * const NSFileHandleReadCompletionNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleReadToEndOfFileCompletionNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleConnectionAcceptedNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleDataAvailableNotification;

FOUNDATION_EXPORT NSString * const NSFileHandleNotificationDataItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationFileHandleItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationMonitorModes NS_DEPRECATED(10_0, 10_7, 2_0, 5_0);

@interface NSFileHandle (NSFileHandleAsynchronousAccess)

- (void)readInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)readInBackgroundAndNotify;

- (void)readToEndOfFileInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)readToEndOfFileInBackgroundAndNotify;

- (void)acceptConnectionInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)acceptConnectionInBackgroundAndNotify;

- (void)waitForDataInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)waitForDataInBackgroundAndNotify;

#ifdef __BLOCKS__
@property (copy) void (^readabilityHandler)(NSFileHandle *)  NS_AVAILABLE(10_7, 5_0);
@property (copy) void (^writeabilityHandler)(NSFileHandle *) NS_AVAILABLE(10_7, 5_0);
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

