//
//  IMServicePlugInFileTransferSession.h
//  IMServicePlugIn
//
//  Created by Ricci Adams on 2010-07-14.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@class IMServicePlugInIncomingFileTransfer, IMServicePlugInOutgoingFileTransfer;

typedef struct _IMServicePlugInFileTransferSessionInternal IMServicePlugInFileTransferSessionInternal;

@interface IMServicePlugInFileTransferSession : NSObject {
    IMServicePlugInFileTransferSessionInternal *_internal;
}

@property (readonly) NSString *guid;
@property (readonly) NSString *containerName;

@end


@interface IMServicePlugInOutgoingFileTransferSession : IMServicePlugInFileTransferSession

@property (readonly) NSArray *outgoingFileTransfers;
- (IMServicePlugInOutgoingFileTransfer *) outgoingFileTransferForPath:(NSString *)path;

@end


@interface IMServicePlugInIncomingFileTransferSession : IMServicePlugInFileTransferSession

- (void) setContainerName:(NSString *)containerName;
- (void) addIncomingFileTransfer:(IMServicePlugInIncomingFileTransfer *)fileTransfer;

- (NSArray *) incomingFileTransfers;
- (IMServicePlugInIncomingFileTransfer *) incomingFileTransferForPath:(NSString *)path;

@end
