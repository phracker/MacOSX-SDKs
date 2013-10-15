/*	NSPortMessage.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSPort, NSDate, NSArray, NSMutableArray;

@interface NSPortMessage : NSObject {
    @private
    NSPort 		*localPort;
    NSPort 		*remotePort;
    NSMutableArray 	*components;
    unsigned		msgid;
    void		*reserved2;
    void		*reserved;
}

- (id)initWithSendPort:(NSPort *)sendPort receivePort:(NSPort *)replyPort components:(NSArray *)components;

- (NSArray *)components;
- (NSPort *)receivePort;
- (NSPort *)sendPort;
- (BOOL)sendBeforeDate:(NSDate *)date;

- (unsigned)msgid;
- (void)setMsgid:(unsigned)msgid;
@end
