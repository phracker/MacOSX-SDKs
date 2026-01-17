//
//  SKPaymentTransaction.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKPayment;

enum {
    SKPaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    SKPaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    SKPaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    SKPaymentTransactionStateRestored,      // Transaction was restored from user's purchase history.  Client should complete the transaction.
    SKPaymentTransactionStateDeferred,		// Transaction is neither purchased nor failed, yet.
};
typedef NSInteger SKPaymentTransactionState;

// Model object representing a transaction with the server
NS_CLASS_AVAILABLE(10_7, NA)
NS_ASSUME_NONNULL_BEGIN
@interface SKPaymentTransaction : NSObject {
@private
    id _internal;
}

// Only set if state is SKPaymentTransactionFailed
@property(nullable, readonly) NSError *error;

// Only valid if state is SKPaymentTransactionStateRestored.
@property(nullable, readonly) SKPaymentTransaction *originalTransaction;

@property(readonly) SKPayment *payment;

// The date when the transaction was added to the server queue.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nullable, readonly) NSDate *transactionDate;

// The unique server-provided identifier.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nullable, readonly) NSString *transactionIdentifier;

// Array of SKDownload objects
// Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nullable, readonly) NSArray *downloads;

@property(readonly) SKPaymentTransactionState transactionState;

@end
NS_ASSUME_NONNULL_END
