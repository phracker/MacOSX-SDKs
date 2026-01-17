//
//  SKPaymentTransaction.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKPayment;
@class SKDownload;

typedef NS_ENUM(NSInteger, SKPaymentTransactionState) {
    SKPaymentTransactionStatePurchasing,                                // Transaction is being added to the server queue.
    SKPaymentTransactionStatePurchased,                                 // Transaction is in queue, user has been charged.  Client should complete the transaction.
    SKPaymentTransactionStateFailed,                                    // Transaction was cancelled or failed before being added to the server queue.
    SKPaymentTransactionStateRestored,                                  // Transaction was restored from user's purchase history.  Client should complete the transaction.
    SKPaymentTransactionStateDeferred NS_ENUM_AVAILABLE_MAC(10_10),     // Transaction is neither purchased nor failed, yet.
} NS_AVAILABLE_MAC(10_7);

NS_ASSUME_NONNULL_BEGIN

// Model object representing a transaction with the server
SK_EXTERN_CLASS_AVAILABLE(10_7)
@interface SKPaymentTransaction : NSObject
{
@private
    id _internal;
}

// Only set if state is SKPaymentTransactionStateFailed
@property(nonatomic, readonly, nullable) NSError *error NS_AVAILABLE_MAC(10_7);

// Only valid if state is SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) SKPaymentTransaction *originalTransaction NS_AVAILABLE_MAC(10_7);

@property(nonatomic, readonly) SKPayment *payment NS_AVAILABLE_MAC(10_7);

// The date when the transaction was added to the server queue.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSDate *transactionDate NS_AVAILABLE_MAC(10_7);

// The unique server-provided identifier.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSString *transactionIdentifier NS_AVAILABLE_MAC(10_7);

// Array of SKDownload objects
// Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly) NSArray<SKDownload *> *downloads NS_AVAILABLE_MAC(10_8);

@property(nonatomic, readonly) SKPaymentTransactionState transactionState NS_AVAILABLE_MAC(10_7);

@end
NS_ASSUME_NONNULL_END
