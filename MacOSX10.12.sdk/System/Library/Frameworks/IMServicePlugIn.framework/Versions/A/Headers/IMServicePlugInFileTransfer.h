/*
    IMServicePlugInFileTransfer.h
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@class IMServicePlugInFileTransferSession;

typedef struct _IMServicePlugInFileTransferInternal IMServicePlugInFileTransferInternal;

@interface IMServicePlugInFileTransfer : NSObject {
    IMServicePlugInFileTransferInternal *_internal;
}

+ (id) fileTransferWithPath: (NSString *) path
                       type: (NSString *) type 
                 totalBytes: (uint64_t) totalBytes;
 
- (id) initWithPath: (NSString *) path
               type: (NSString *) type
         totalBytes: (uint64_t) totalBytes;

@property (readonly) NSString *guid;

@property (readonly) NSString *path;
@property (readonly) NSString *type;
@property (readonly) uint64_t transferredBytes;
@property (readonly) uint64_t totalBytes;

@property (readonly) IMServicePlugInFileTransferSession *session;

@end


@interface IMServicePlugInOutgoingFileTransfer : IMServicePlugInFileTransfer

- (void) resetInputStream;

@property (readonly) NSInputStream *inputStream;

@end


@interface IMServicePlugInIncomingFileTransfer : IMServicePlugInFileTransfer

- (void) resetOutputStream;

@property (readonly) NSOutputStream *outputStream;

@end
