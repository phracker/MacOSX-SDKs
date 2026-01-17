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

NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInFileTransferSession : NSObject {
    IMServicePlugInFileTransferSessionInternal *_internal;
}

@property (readonly) NSString *guid NS_DEPRECATED_MAC(10_7, 10_13);
@property (readonly) NSString *containerName NS_DEPRECATED_MAC(10_7, 10_13);;

@end


NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInOutgoingFileTransferSession : IMServicePlugInFileTransferSession

@property (readonly) NSArray *outgoingFileTransfers NS_DEPRECATED_MAC(10_7, 10_13);;
- (IMServicePlugInOutgoingFileTransfer *) outgoingFileTransferForPath:(NSString *)path NS_DEPRECATED_MAC(10_7, 10_13);;

@end


NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInIncomingFileTransferSession : IMServicePlugInFileTransferSession

- (void) setContainerName:(NSString *)containerName NS_DEPRECATED_MAC(10_7, 10_13);;
- (void) addIncomingFileTransfer:(IMServicePlugInIncomingFileTransfer *)fileTransfer NS_DEPRECATED_MAC(10_7, 10_13);;

- (NSArray *) incomingFileTransfers NS_DEPRECATED_MAC(10_7, 10_13);;
- (IMServicePlugInIncomingFileTransfer *) incomingFileTransferForPath:(NSString *)path NS_DEPRECATED_MAC(10_7, 10_13);;

@end
