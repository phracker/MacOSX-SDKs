/*	NSThread.h
	Copyright 1994-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMutableDictionary, NSDate;

@interface NSThread : NSObject  {
@private
    unsigned		seqNum;
    unsigned		reserved2;
    NSMutableDictionary	*threadDictionary;
    id			runLoop;
    void		*excHandlers;
    void		*autoreleasePool;
    id			doQueue;
    id			doConversation;
    unsigned		doConversationCount;
    id			doConversationRequest;
    void		*reserved1;
    void		*reserved;
}

+ (NSThread *)currentThread;

+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(id)argument;

+ (BOOL)isMultiThreaded;

- (NSMutableDictionary *)threadDictionary;

+ (void)sleepUntilDate:(NSDate *)date;

+ (void)exit;

@end

FOUNDATION_EXPORT NSString * const NSWillBecomeMultiThreadedNotification;
FOUNDATION_EXPORT NSString * const NSDidBecomeSingleThreadedNotification;
FOUNDATION_EXPORT NSString * const NSThreadWillExitNotification;

