/*
    IMServicePlugInFileTransfer.h
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@class IMServicePlugInFileTransferSession;

typedef struct _IMServicePlugInFileTransferInternal IMServicePlugInFileTransferInternal;

NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInFileTransfer : NSObject {
    IMServicePlugInFileTransferInternal *_internal;
}

+ (id) fileTransferWithPath: (NSString *) path
                       type: (NSString *) type 
                 totalBytes: (uint64_t) totalBytes NS_DEPRECATED_MAC(10_7, 10_13);
 
- (id) initWithPath: (NSString *) path
               type: (NSString *) type
         totalBytes: (uint64_t) totalBytes NS_DEPRECATED_MAC(10_7, 10_13);

@property (readonly) NSString *guid NS_DEPRECATED_MAC(10_7, 10_13);

@property (readonly) NSString *path NS_DEPRECATED_MAC(10_7, 10_13);
@property (readonly) NSString *type NS_DEPRECATED_MAC(10_7, 10_13);
@property (readonly) uint64_t transferredBytes NS_DEPRECATED_MAC(10_7, 10_13);
@property (readonly) uint64_t totalBytes NS_DEPRECATED_MAC(10_7, 10_13);

@property (readonly) IMServicePlugInFileTransferSession *session NS_DEPRECATED_MAC(10_7, 10_13);

@end


NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInOutgoingFileTransfer : IMServicePlugInFileTransfer

- (void) resetInputStream NS_DEPRECATED_MAC(10_7, 10_13);

@property (readonly) NSInputStream *inputStream NS_DEPRECATED_MAC(10_7, 10_13);

@end


NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInIncomingFileTransfer : IMServicePlugInFileTransfer

- (void) resetOutputStream NS_DEPRECATED_MAC(10_7, 10_13);

@property (readonly) NSOutputStream *outputStream NS_DEPRECATED_MAC(10_7, 10_13);

@end
