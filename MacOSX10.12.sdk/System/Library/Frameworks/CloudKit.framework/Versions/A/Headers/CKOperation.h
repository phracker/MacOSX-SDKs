//
//  CKOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKContainer;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKOperation : NSOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/* If no container is set, [CKContainer defaultContainer] is used */
@property (nonatomic, strong, nullable) CKContainer *container;

/*
 CKOperations behave differently depending on how you set qualityOfService:

 NSQualityOfServiceUserInteractive
    Network requests are non-discretionary
 NSQualityOfServiceUserInitiated
    Network requests are non-discretionary
 NSQualityOfServiceUtility
    The system marks your network requests as discretionary when the user is not using your app
 NSQualityOfServiceBackground
    Network requests are discretionary

 CKOperations have a default qualityOfService of NSQualityOfServiceUtility.

 */

/* If set, network traffic will happen on a background NSURLSession.
 Defaults to (NSOperationQualityOfServiceBackground == self.qualityOfService) */
@property (nonatomic, assign) BOOL usesBackgroundSession NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Set qualityOfService to NSQualityOfServiceUtility or NSQualityOfServiceBackground");

/* Defaults to YES */
@property (nonatomic, assign) BOOL allowsCellularAccess;

@property (nonatomic, readonly, copy) NSString *operationID NS_AVAILABLE(10_12, 9_3);

/* 
   Long lived operations will continue running even if your process exits. If your process remains alive for the lifetime of the long lived operation its behavior is the same as a regular operation.

   Long lived operations can be fetched and replayed from the container via the fetchAllLongLivedOperations: and fetchLongLivedOperationsWithIDs: APIs.

   Long lived operations persist until their -[NSOperation completionBlock] returns or until the operation is cancelled. 
   Long lived operations may be garbage collected 24 hours after they finish running if no client has replayed them.
 
   The default value for longLived is NO. Changing the value of longLived on an already started operation or on an outstanding long lived operation fetched from CKContainer has no effect.
 */
@property (nonatomic, assign, getter=isLongLived) BOOL longLived NS_AVAILABLE(10_12, 9_3);

/* 
   If non-zero, overrides the timeout interval for any network requests issued by this operation.
   See NSURLSessionConfiguration.timeoutIntervalForRequest 
*/
@property (nonatomic, assign) NSTimeInterval timeoutIntervalForRequest NS_AVAILABLE(10_12, 10_0);

/*
 If non-zero, overrides the timeout interval for any network resources retrieved by this operation.
 See NSURLSessionConfiguration.timeoutIntervalForResource
 */
@property (nonatomic, assign) NSTimeInterval timeoutIntervalForResource NS_AVAILABLE(10_12, 10_0);

/*
   This callback is called after a long lived operation has begun running and is persisted. Once this callback is called the operation will continue running even if the current process exits.
 */
@property (nonatomic, strong, nullable) void (^longLivedOperationWasPersistedBlock)(void) NS_AVAILABLE(10_12, 9_3);

@end
NS_ASSUME_NONNULL_END
