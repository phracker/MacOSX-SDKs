//
//  CKFetchSubscriptionsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKDefines.h>

@class CKSubscription;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchSubscriptionsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

+ (instancetype)fetchAllSubscriptionsOperation;

- (instancetype)initWithSubscriptionIDs:(NSArray <NSString *> *)subscriptionIDs;

@property (nonatomic, copy, nullable) NSArray <NSString *> *subscriptionIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of subscriptionID to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^fetchSubscriptionCompletionBlock)(NSDictionary <NSString *, CKSubscription *> * __nullable subscriptionsBySubscriptionID, NSError * __nullable operationError);

@end
NS_ASSUME_NONNULL_END
