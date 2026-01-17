//
//  SKPaymentTransaction.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKDownload;
@class SKPayment;

typedef NS_ENUM(NSInteger, SKPaymentTransactionState) {
    SKPaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    SKPaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    SKPaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    SKPaymentTransactionStateRestored,      // Transaction was restored from user's purchase history.  Client should complete the transaction.
    SKPaymentTransactionStateDeferred API_DEPRECATED("Use PurchaseResult.pending from Product.purchase(confirmIn:options:).", ios(8.0, 18.0), macos(10.10, 15.0), watchos(6.2, 11.0)),   // The transaction is in the queue, but its final status is pending external action.
} API_DEPRECATED("Use PurchaseResult from Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
API_DEPRECATED("Use PurchaseResult from Product.purchase(confirmIn:options:).",ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_SENDABLE
@interface SKPaymentTransaction : NSObject {
@private
    id _internal;
}

// Only set if state is SKPaymentTransactionFailed
@property(nonatomic, readonly, nullable) NSError *error;

// Only valid if state is SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) SKPaymentTransaction *originalTransaction;

@property(nonatomic, readonly) SKPayment *payment;

// Available downloads (SKDownload) for this transaction
@property(nonatomic, readonly) NSArray<SKDownload *> *downloads API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// The date when the transaction was added to the server queue.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSDate *transactionDate;

// The unique server-provided identifier.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSString *transactionIdentifier;

// Only valid if state is SKPaymentTransactionStatePurchased.
@property(nonatomic, readonly, nullable) NSData *transactionReceipt API_DEPRECATED_WITH_REPLACEMENT("-[NSBundle appStoreReceiptURL]", ios(3.0, 7.0), macCatalyst(13.0, 13.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, watchos);

@property(nonatomic, readonly) SKPaymentTransactionState transactionState;

@end

NS_ASSUME_NONNULL_END
