//
//  CKModifySubscriptionOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifySubscriptionsOperation : CKDatabaseOperation

- (instancetype)initWithSubscriptionsToSave:(NSArray /* CKSubscription */ *)subscriptionsToSave subscriptionIDsToDelete:(NSArray /* NSString */ *)subscriptionIDsToDelete NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray /* CKSubscription */ *subscriptionsToSave;
@property (nonatomic, copy) NSArray /* NSString */ *subscriptionIDsToDelete;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of subscriptionIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy) void (^modifySubscriptionsCompletionBlock)(NSArray /* CKSubscription */ *savedSubscriptions, NSArray /* NSString */ *deletedSubscriptionIDs, NSError *operationError);

@end
