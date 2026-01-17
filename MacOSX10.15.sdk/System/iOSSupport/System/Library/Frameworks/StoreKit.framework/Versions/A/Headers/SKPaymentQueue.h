//
//  SKPaymentQueue.h
//  StoreKit
//
//  Copyright 2009-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKDownload;
@class SKPayment;
@class SKPaymentTransaction;
@class SKProduct;
@class SKStorefront;
@protocol SKPaymentQueueDelegate;
@protocol SKPaymentTransactionObserver;

NS_ASSUME_NONNULL_BEGIN

// SKPaymentQueue interacts with the server-side payment queue
SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKPaymentQueue : NSObject {
@private
    id _internal;
}

@property (NS_NONATOMIC_IOSONLY, weak, nullable) id<SKPaymentQueueDelegate> delegate API_AVAILABLE(ios(13.0), macos(10.15));;

@property (NS_NONATOMIC_IOSONLY, readonly, nullable) SKStorefront *storefront API_AVAILABLE(ios(13.0), macos(10.15));

+ (instancetype)defaultQueue API_AVAILABLE(ios(3.0), macos(10.7));

// NO if this device is not able or allowed to make payments
+ (BOOL)canMakePayments API_AVAILABLE(ios(3.0), macos(10.7));

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void)addPayment:(SKPayment *)payment API_AVAILABLE(ios(3.0), macos(10.7));

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void)restoreCompletedTransactions API_AVAILABLE(ios(3.0), macos(10.7));
- (void)restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username API_AVAILABLE(ios(7.0), macos(10.9));

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void)finishTransaction:(SKPaymentTransaction *)transaction API_AVAILABLE(ios(3.0), macos(10.7));

// Asynchronous.  Start the given downloads (SKDownload).
- (void)startDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Asynchronous.  Pause/resume downloads (SKDownload).
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));
- (void)resumeDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Asynchronous.  Cancel downloads (SKDownload)
- (void)cancelDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void)addTransactionObserver:(id <SKPaymentTransactionObserver>)observer API_AVAILABLE(ios(3.0), macos(10.7));
- (void)removeTransactionObserver:(id <SKPaymentTransactionObserver>)observer API_AVAILABLE(ios(3.0), macos(10.7));

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nonatomic, readonly) NSArray<SKPaymentTransaction *> *transactions API_AVAILABLE(ios(3.0), macos(10.7));

@end

@protocol SKPaymentQueueDelegate <NSObject>
@optional
- (BOOL)paymentQueue:(SKPaymentQueue *)paymentQueue shouldContinueTransaction:(SKPaymentTransaction *)transaction inStorefront:(SKStorefront *)newStorefront API_AVAILABLE(ios(13.0), macos(10.15));
@end


@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions API_AVAILABLE(ios(3.0), macos(10.7));

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions API_AVAILABLE(ios(3.0), macos(10.7));

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error API_AVAILABLE(ios(3.0), macos(10.7));

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue API_AVAILABLE(ios(3.0), macos(10.7));

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Sent when a user initiates an IAP buy from the App Store
- (BOOL)paymentQueue:(SKPaymentQueue *)queue shouldAddStorePayment:(SKPayment *)payment forProduct:(SKProduct *)product NS_SWIFT_NAME(paymentQueue(_:shouldAddStorePayment:for:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst);

- (void)paymentQueueDidChangeStorefront:(SKPaymentQueue *)queue API_AVAILABLE(ios(13.0), macos(10.15));

@end

NS_ASSUME_NONNULL_END
