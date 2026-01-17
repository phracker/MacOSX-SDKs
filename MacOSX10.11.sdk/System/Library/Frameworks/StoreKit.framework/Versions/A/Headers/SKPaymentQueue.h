//
//  SKPaymentQueue.h
//  StoreKit
//
//  Copyright 2009-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>



@class SKPayment, SKPaymentTransaction, SKDownload;
@protocol SKPaymentTransactionObserver;

// SKPaymentQueue interacts with the server-side payment queue
NS_CLASS_AVAILABLE(10_7, NA)
NS_ASSUME_NONNULL_BEGIN
@interface SKPaymentQueue : NSObject
{
	@private
		id _internal;
}

+ (SKPaymentQueue *) defaultQueue;

// NO if this device is not able or allowed to make payments
+ (BOOL) canMakePayments;

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void) addPayment:(SKPayment *)payment;

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void) restoreCompletedTransactions;
- (void) restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username;

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void) finishTransaction:(SKPaymentTransaction *)transaction;

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void) addTransactionObserver:(id <SKPaymentTransactionObserver>)observer;
- (void) removeTransactionObserver:(id <SKPaymentTransactionObserver>)observer;

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nullable, readonly) NSArray<SKPaymentTransaction *> *transactions;

//
- (void) startDownloads:(NSArray <SKDownload *> *)downloads;
- (void) pauseDownloads:(NSArray <SKDownload *> *)downloads;
- (void) resumeDownloads:(NSArray <SKDownload *> *)downloads;
- (void) cancelDownloads:(NSArray <SKDownload *> *)downloads;

@end
NS_ASSUME_NONNULL_END


NS_ASSUME_NONNULL_BEGIN
@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray <SKPaymentTransaction *> *)transactions;

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void) paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray <SKPaymentTransaction *> *)transactions;

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void) paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error;

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue;

// Sent when the download state has changed.
- (void) paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray <SKDownload *> *)downloads;

@end
NS_ASSUME_NONNULL_END


