/*	NSOperation.h
	Copyright (c) 2006-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>


@class NSArray, NSSet;

NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSOperation : NSObject {
@private
    id _private;
    int32_t _private1;
#if __LP64__
    int32_t _private1b;
#endif
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

typedef NS_ENUM(NSInteger, NSOperationQueuePriority) {
	NSOperationQueuePriorityVeryLow = -8L,
	NSOperationQueuePriorityLow = -4L,
	NSOperationQueuePriorityNormal = 0,
	NSOperationQueuePriorityHigh = 4,
	NSOperationQueuePriorityVeryHigh = 8
};

- (NSOperationQueuePriority)queuePriority;
- (void)setQueuePriority:(NSOperationQueuePriority)p;

#if NS_BLOCKS_AVAILABLE
- (void (^)(void))completionBlock NS_AVAILABLE(10_6, 4_0);
- (void)setCompletionBlock:(void (^)(void))block NS_AVAILABLE(10_6, 4_0);
#endif

- (void)waitUntilFinished NS_AVAILABLE(10_6, 4_0);

- (double)threadPriority NS_AVAILABLE(10_6, 4_0);
- (void)setThreadPriority:(double)p NS_AVAILABLE(10_6, 4_0);

@end



NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSBlockOperation : NSOperation {
@private
    id _private2;
    void *_reserved2;
}

#if NS_BLOCKS_AVAILABLE
+ (id)blockOperationWithBlock:(void (^)(void))block;

- (void)addExecutionBlock:(void (^)(void))block;
- (NSArray *)executionBlocks;
#endif

@end


NS_CLASS_AVAILABLE(10_5, 2_0)
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

FOUNDATION_EXPORT NSString * const NSInvocationOperationVoidResultException NS_AVAILABLE(10_5, 2_0);
FOUNDATION_EXPORT NSString * const NSInvocationOperationCancelledException NS_AVAILABLE(10_5, 2_0);

NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSOperationQueue : NSObject {
@private
    id _private;
    void *_reserved;
}

- (void)addOperation:(NSOperation *)op;
- (void)addOperations:(NSArray *)ops waitUntilFinished:(BOOL)wait NS_AVAILABLE(10_6, 4_0);

#if NS_BLOCKS_AVAILABLE
- (void)addOperationWithBlock:(void (^)(void))block NS_AVAILABLE(10_6, 4_0);
#endif

- (NSArray *)operations;
- (NSUInteger)operationCount NS_AVAILABLE(10_6, 4_0);

- (NSInteger)maxConcurrentOperationCount;
- (void)setMaxConcurrentOperationCount:(NSInteger)cnt;

enum {
    NSOperationQueueDefaultMaxConcurrentOperationCount = -1
};

- (void)setSuspended:(BOOL)b;
- (BOOL)isSuspended;

- (void)setName:(NSString *)n NS_AVAILABLE(10_6, 4_0);
- (NSString *)name NS_AVAILABLE(10_6, 4_0);

- (void)cancelAllOperations;

- (void)waitUntilAllOperationsAreFinished;

+ (id)currentQueue NS_AVAILABLE(10_6, 4_0);
+ (id)mainQueue NS_AVAILABLE(10_6, 4_0);

@end


