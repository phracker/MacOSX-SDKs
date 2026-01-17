//
//  CKModifySubscriptionsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

#import <CloudKit/CKSubscription.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
@interface CKModifySubscriptionsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithSubscriptionsToSave:(nullable NSArray<CKSubscription *> *)subscriptionsToSave subscriptionIDsToDelete:(nullable NSArray<CKSubscriptionID> *)subscriptionIDsToDelete;

@property (nullable, copy, nonatomic) NSArray<CKSubscription *> *subscriptionsToSave;
@property (nullable, copy, nonatomic) NSArray<CKSubscriptionID> *subscriptionIDsToDelete;

/*! @abstract Called on success or failure of a subscription save
 *
 *  @discussion Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^perSubscriptionSaveBlock)(CKSubscriptionID subscriptionID, CKSubscription * _Nullable subscription, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/*! @abstract Called on success or failure of a subscription deletion
 *
 *  @discussion Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^perSubscriptionDeleteBlock)(CKSubscriptionID subscriptionID, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  If the error is @c CKErrorPartialFailure, the error's userInfo dictionary contains a dictionary of subscriptionIDs to errors keyed off of @c CKPartialErrorsByItemIDKey.
 *  @c savedSubscriptions, @c deletedSubscriptionIDs and any @c CKPartialErrorsByItemIDKey errors are repeats of the data sent back in previous @c perSubscriptionSaveBlock and @c perSubscriptionDeleteBlock invocations
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^modifySubscriptionsCompletionBlock)(NSArray<CKSubscription *> * _Nullable savedSubscriptions, NSArray<CKSubscriptionID> * _Nullable deletedSubscriptionIDs, NSError * _Nullable operationError);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
