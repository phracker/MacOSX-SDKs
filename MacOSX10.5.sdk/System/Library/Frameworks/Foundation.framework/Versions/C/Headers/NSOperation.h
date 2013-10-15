/*	NSOperation.h
	Copyright (c) 2006-2007, Apple Inc. All rights reserved.
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

@end

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

- (NSArray *)operations;

- (NSInteger)maxConcurrentOperationCount;
- (void)setMaxConcurrentOperationCount:(NSInteger)cnt;

enum {
    NSOperationQueueDefaultMaxConcurrentOperationCount = -1
};

- (void)setSuspended:(BOOL)b;
- (BOOL)isSuspended;

- (void)cancelAllOperations;

- (void)waitUntilAllOperationsAreFinished;

@end

#endif

