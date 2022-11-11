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
SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2)) @interface SKPaymentQueue : NSObject {
@private
    id _internal;
}

@property (NS_NONATOMIC_IOSONLY, weak, nullable) id<SKPaymentQueueDelegate> delegate API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2));;

@property (NS_NONATOMIC_IOSONLY, readonly, nullable) SKStorefront *storefront API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2));

+ (instancetype)defaultQueue API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// NO if this device is not able or allowed to make payments
+ (BOOL)canMakePayments API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void)addPayment:(SKPayment *)payment API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void)restoreCompletedTransactions API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));
- (void)restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2));

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void)finishTransaction:(SKPaymentTransaction *)transaction API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Asynchronous.  Start the given downloads (SKDownload).
- (void)startDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8), watchos(6.2));

// Asynchronous.  Pause/resume downloads (SKDownload).
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8), watchos(6.2));
- (void)resumeDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8), watchos(6.2));

// Asynchronous.  Cancel downloads (SKDownload)
- (void)cancelDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8), watchos(6.2));

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void)addTransactionObserver:(id <SKPaymentTransactionObserver>)observer API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2)) NS_SWIFT_NAME(add(_:));
- (void)removeTransactionObserver:(id <SKPaymentTransactionObserver>)observer API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2)) NS_SWIFT_NAME(remove(_:));

// Array of transactionObservers that are available. Transaction observers are not retained.
@property(nonatomic, readonly) NSArray <id <SKPaymentTransactionObserver>> *transactionObservers API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nonatomic, readonly) NSArray<SKPaymentTransaction *> *transactions API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// If StoreKit has called your SKPaymentQueueDelegate's "paymentQueueShouldShowPriceConsent:" method and you returned NO, you can use this method to show the price consent UI at a later time that is more appropriate for your app. If there is no pending price consent, this method will do nothing.
- (void)showPriceConsentIfNeeded API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, macos, watchos);

// Call this method to have StoreKit present a sheet enabling the user to redeem codes provided by your app.
- (void)presentCodeRedemptionSheet API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, macos, watchos);

@end

@protocol SKPaymentQueueDelegate <NSObject>
@optional
// Sent when the storefront changes while a payment is processing.
- (BOOL)paymentQueue:(SKPaymentQueue *)paymentQueue shouldContinueTransaction:(SKPaymentTransaction *)transaction inStorefront:(SKStorefront *)newStorefront API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2));

// Sent if there is a pending price consent confirmation from the App Store for the current user. Return YES to immediately show the price consent UI. Return NO if you intend to show it at a later time. Defaults to YES.
// This may be called at any time that you have transaction observers on the payment queue, so make sure to set the delegate before adding any transaction observers if you intend to implement this method.
- (BOOL)paymentQueueShouldShowPriceConsent:(SKPaymentQueue *)paymentQueue API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, macos, watchos);

@end


@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8), watchos(6.2));

// Sent when a user initiates an IAP buy from the App Store
- (BOOL)paymentQueue:(SKPaymentQueue *)queue shouldAddStorePayment:(SKPayment *)payment forProduct:(SKProduct *)product NS_SWIFT_NAME(paymentQueue(_:shouldAddStorePayment:for:)) API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);

- (void)paymentQueueDidChangeStorefront:(SKPaymentQueue *)queue API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2));

// Sent when entitlements for a user have changed and access to the specified IAPs has been revoked.
- (void)paymentQueue:(SKPaymentQueue *)queue didRevokeEntitlementsForProductIdentifiers:(NSArray<NSString *> *)productIdentifiers NS_SWIFT_NAME(paymentQueue(_:didRevokeEntitlementsForProductIdentifiers:)) API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

@end

NS_ASSUME_NONNULL_END
