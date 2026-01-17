//
//  CKOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <os/activity.h>

@class CKContainer;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKOperation : NSOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (os_activity_t)activityStart;


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

 CKOperations have a default qualityOfService of NSQualityOfServiceBackground.

 */

/* If set, network traffic will happen on a background NSURLSession.
 Defaults to (NSOperationQualityOfServiceBackground == self.qualityOfService) */
@property (nonatomic, assign) BOOL usesBackgroundSession NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Set qualityOfService to NSQualityOfServiceUtility or NSQualityOfServiceBackground");

/* Defaults to YES */
@property (nonatomic, assign) BOOL allowsCellularAccess;

@end
NS_ASSUME_NONNULL_END
