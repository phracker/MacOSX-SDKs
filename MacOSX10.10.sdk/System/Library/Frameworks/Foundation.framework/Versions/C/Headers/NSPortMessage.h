/*	NSPortMessage.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSPort, NSDate, NSArray, NSMutableArray;

@interface NSPortMessage : NSObject {
    @private
    NSPort 		*localPort;
    NSPort 		*remotePort;
    NSMutableArray 	*components;
    uint32_t		msgid;
    void		*reserved2;
    void		*reserved;
}

- (instancetype)initWithSendPort:(NSPort *)sendPort receivePort:(NSPort *)replyPort components:(NSArray *)components NS_DESIGNATED_INITIALIZER;

@property (readonly, copy) NSArray *components;
@property (readonly, retain) NSPort *receivePort;
@property (readonly, retain) NSPort *sendPort;
- (BOOL)sendBeforeDate:(NSDate *)date;

@property uint32_t msgid;

@end

