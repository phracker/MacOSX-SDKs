/*	NSOperation.h
	Copyright (c) 2006-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <sys/qos.h>
#import <dispatch/dispatch.h>

@class NSArray, NSSet;


#define NSOperationQualityOfService NSQualityOfService
#define NSOperationQualityOfServiceUserInteractive NSQualityOfServiceUserInteractive
#define NSOperationQualityOfServiceUserInitiated NSQualityOfServiceUserInitiated
#define NSOperationQualityOfServiceUtility NSQualityOfServiceUtility
#define NSOperationQualityOfServiceBackground NSQualityOfServiceBackground


NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSOperation : NSObject {
@private
    id _private;
    int32_t _private1;
#if __LP64__
    int32_t _private1b;
#endif
}

- (void)start;
- (void)main;

@property (readonly, getter=isCancelled) BOOL cancelled;
- (void)cancel;

@property (readonly, getter=isExecuting) BOOL executing;
@property (readonly, getter=isFinished) BOOL finished;
@property (readonly, getter=isConcurrent) BOOL concurrent; // To be deprecated; use and override 'asynchronous' below
@property (readonly, getter=isAsynchronous) BOOL asynchronous NS_AVAILABLE(10_8, 7_0);
@property (readonly, getter=isReady) BOOL ready;

- (void)addDependency:(NSOperation *)op;
- (void)removeDependency:(NSOperation *)op;

@property (readonly, copy) NSArray *dependencies;

typedef NS_ENUM(NSInteger, NSOperationQueuePriority) {
	NSOperationQueuePriorityVeryLow = -8L,
	NSOperationQueuePriorityLow = -4L,
	NSOperationQueuePriorityNormal = 0,
	NSOperationQueuePriorityHigh = 4,
	NSOperationQueuePriorityVeryHigh = 8
};

@property NSOperationQueuePriority queuePriority;

@property (copy) void (^completionBlock)(void) NS_AVAILABLE(10_6, 4_0);

- (void)waitUntilFinished NS_AVAILABLE(10_6, 4_0);

@property double threadPriority NS_DEPRECATED(10_6, 10_10, 4_0, 8_0);

@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0);

@property (copy) NSString *name NS_AVAILABLE(10_10, 8_0);

@end



NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSBlockOperation : NSOperation {
@private
    id _private2;
    void *_reserved2;
}

+ (instancetype)blockOperationWithBlock:(void (^)(void))block;

- (void)addExecutionBlock:(void (^)(void))block;
@property (readonly, copy) NSArray *executionBlocks;

@end


NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSInvocationOperation : NSOperation {
@private
    id _inv;
    id _exception;
    void *_reserved2;
}

- (instancetype)initWithTarget:(id)target selector:(SEL)sel object:(id)arg;
- (instancetype)initWithInvocation:(NSInvocation *)inv NS_DESIGNATED_INITIALIZER;

@property (readonly, retain) NSInvocation *invocation;

@property (readonly, retain) id result;

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

- (void)addOperationWithBlock:(void (^)(void))block NS_AVAILABLE(10_6, 4_0);

@property (readonly, copy) NSArray *operations;
@property (readonly) NSUInteger operationCount NS_AVAILABLE(10_6, 4_0);

@property NSInteger maxConcurrentOperationCount;

enum {
    NSOperationQueueDefaultMaxConcurrentOperationCount = -1
};

@property (getter=isSuspended) BOOL suspended;

@property (copy) NSString *name NS_AVAILABLE(10_6, 4_0);

@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0);

@property (assign /* actually retain */) dispatch_queue_t underlyingQueue NS_AVAILABLE(10_10, 8_0);

- (void)cancelAllOperations;

- (void)waitUntilAllOperationsAreFinished;

+ (NSOperationQueue *)currentQueue NS_AVAILABLE(10_6, 4_0);
+ (NSOperationQueue *)mainQueue NS_AVAILABLE(10_6, 4_0);

@end


