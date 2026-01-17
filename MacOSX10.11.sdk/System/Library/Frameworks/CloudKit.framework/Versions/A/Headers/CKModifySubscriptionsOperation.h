//
//  CKModifySubscriptionOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKSubscription;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifySubscriptionsOperation : CKDatabaseOperation

- (instancetype)initWithSubscriptionsToSave:(nullable NSArray <CKSubscription *> *)subscriptionsToSave subscriptionIDsToDelete:(nullable NSArray <NSString *> *)subscriptionIDsToDelete NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) NSArray <CKSubscription *> *subscriptionsToSave;
@property (nonatomic, copy, nullable) NSArray <NSString *> *subscriptionIDsToDelete;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of subscriptionIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^modifySubscriptionsCompletionBlock)(NSArray <CKSubscription *> * __nullable savedSubscriptions, NSArray <NSString *> * __nullable deletedSubscriptionIDs, NSError * __nullable operationError);

@end
NS_ASSUME_NONNULL_END
