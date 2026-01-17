/*	NSOperation.h
	Copyright (c) 2006-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSArray, NSSet;

@interface NSOperation : NSObject {
@private
    id _private;
    void *_reserved;
}

- (id)init; // designated initializer

- (void)start;
- (void)main;

- (BOOL)isCancelled;
- (void)cancel;

- (BOOL)isExecuting;
- (BOOL)isFinished;

- (BOOL)isConcurrent;

- (BOOL)isReady;

- (void)addDependency:(NSOperation *)op;
- (void)removeDependency:(NSOperation *)op;

- (NSArray *)dependencies;

enum {
	NSOperationQueuePriorityVeryLow = -8,
	NSOperationQueuePriorityLow = -4,
	NSOperationQueuePriorityNormal = 0,
	NSOperationQueuePriorityHigh = 4,
	NSOperationQueuePriorityVeryHigh = 8
};
typedef NSInteger NSOperationQueuePriority;

- (NSOperationQueuePriority)queuePriority;
- (void)setQueuePriority:(NSOperationQueuePriority)p;

#if NS_BLOCKS_AVAILABLE
- (void (^)(void))completionBlock AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setCompletionBlock:(void (^)(void))block AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
#endif

- (void)waitUntilFinished AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (double)threadPriority AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setThreadPriority:(double)p AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end


#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
#if NS_BLOCKS_AVAILABLE

@interface NSBlockOperation : NSOperation {
@private
    id _private2;
    void *_reserved2;
}

+ (id)blockOperationWithBlock:(void (^)(void))block AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)addExecutionBlock:(void (^)(void))block AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSArray *)executionBlocks AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif
#endif


@interface NSInvocationOperation : NSOperation {
@private
    id _inv;
    id _exception;
    void *_reserved2;
}

- (id)initWithTarget:(id)target selector:(SEL)sel object:(id)arg;
- (id)initWithInvocation:(NSInvocation *)inv;		// designated initializer

- (NSInvocation *)invocation;

- (id)result;

@end

FOUNDATION_EXPORT NSString * const NSInvocationOperationVoidResultException;
FOUNDATION_EXPORT NSString * const NSInvocationOperationCancelledException;


@interface NSOperationQueue : NSObject {
@private
    id _private;
    void *_reserved;
}

- (void)addOperation:(NSOperation *)op;
- (void)addOperations:(NSArray *)ops waitUntilFinished:(BOOL)wait AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#if NS_BLOCKS_AVAILABLE
- (void)addOperationWithBlock:(void (^)(void))block AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
#endif

- (NSArray *)operations;
- (NSUInteger)operationCount AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSInteger)maxConcurrentOperationCount;
- (void)setMaxConcurrentOperationCount:(NSInteger)cnt;

enum {
    NSOperationQueueDefaultMaxConcurrentOperationCount = -1
};

- (void)setSuspended:(BOOL)b;
- (BOOL)isSuspended;

- (void)setName:(NSString *)n AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)cancelAllOperations;

- (void)waitUntilAllOperationsAreFinished;

+ (id)currentQueue AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (id)mainQueue AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif

