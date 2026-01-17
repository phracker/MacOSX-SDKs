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
SK_EXTERN_CLASS
API_DEPRECATED("No longer supported.", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_SENDABLE
@interface SKPaymentQueue : NSObject {
@private
    id _internal;
}

@property (NS_NONATOMIC_IOSONLY, weak, nullable) id<SKPaymentQueueDelegate> delegate API_DEPRECATED("No longer supported.", ios(13.0, 18.0), tvos(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property (NS_NONATOMIC_IOSONLY, readonly, nullable) SKStorefront *storefront API_DEPRECATED("Use Storefront.current.", ios(13.0, 18.0), tvos(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

+ (instancetype)defaultQueue;

// NO if this device is not able or allowed to make payments
+ (BOOL)canMakePayments API_DEPRECATED("Use AppStore.canMakePayments.", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void)addPayment:(SKPayment *)payment API_DEPRECATED("Use Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void)restoreCompletedTransactions API_DEPRECATED("Use AppStore.sync().", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));
- (void)restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username API_DEPRECATED("Use AppStore.sync().", ios(7.0, 18.0), tvos(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void)finishTransaction:(SKPaymentTransaction *)transaction API_DEPRECATED("Use Transaction.finish().", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Asynchronous.  Start the given downloads (SKDownload).
- (void)startDownloads:(NSArray<SKDownload *> *)downloads API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Asynchronous.  Pause/resume downloads (SKDownload).
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);
- (void)resumeDownloads:(NSArray<SKDownload *> *)downloads API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Asynchronous.  Cancel downloads (SKDownload)
- (void)cancelDownloads:(NSArray<SKDownload *> *)downloads API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void)addTransactionObserver:(id<SKPaymentTransactionObserver>)observer API_DEPRECATED("Use Transaction.updates or PurchaseResult from Product.purchase(confirmIn:options:).", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0)) NS_SWIFT_NAME(add(_:));
- (void)removeTransactionObserver:(id<SKPaymentTransactionObserver>)observer API_DEPRECATED("No longer supported.", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0)) NS_SWIFT_NAME(remove(_:));

// Array of transactionObservers that are available. Transaction observers are not retained.
@property(nonatomic, readonly) NSArray <id<SKPaymentTransactionObserver>> *transactionObservers API_DEPRECATED("Use Transaction.updates or PurchaseResult from Product.purchase(confirmIn:options:).", ios(14.0, 18.0), tvos(14.0, 18.0), macos(11.0, 15.0), watchos(7.0, 11.0), visionos(1.0, 2.0));

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nonatomic, readonly) NSArray<SKPaymentTransaction *> *transactions API_DEPRECATED("Use Transaction.unfinished.", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// If StoreKit has called your SKPaymentQueueDelegate's "paymentQueueShouldShowPriceConsent:" method and you returned NO, you can use this method to show the price consent UI at a later time that is more appropriate for your app. If there is no pending price consent, this method will do nothing.
- (void)showPriceConsentIfNeeded API_DEPRECATED("Use Message.messages and Message.display(in:).", ios(13.4, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(tvos, macos, watchos);

// Call this method to have StoreKit present a sheet enabling the user to redeem codes provided by your app.
- (void)presentCodeRedemptionSheet API_DEPRECATED("Use AppStore.presentOfferCodeRedeemSheet(in:).", ios(14.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(tvos, macos, watchos);

@end

API_DEPRECATED("No longer supported.", ios(13.0, 18.0), tvos(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
@protocol SKPaymentQueueDelegate <NSObject>
@optional
// Sent when the storefront changes while a payment is processing.
- (BOOL)paymentQueue:(SKPaymentQueue *)paymentQueue shouldContinueTransaction:(SKPaymentTransaction *)transaction inStorefront:(SKStorefront *)newStorefront API_DEPRECATED("Pass Product.PurchaseOption.onStorefrontChange(shouldContinuePurchase:) to product.purchase(options:).", ios(13.0, 18.0), tvos(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Sent if there is a pending price consent confirmation from the App Store for the current user. Return YES to immediately show the price consent UI. Return NO if you intend to show it at a later time. Defaults to YES.
// This may be called at any time that you have transaction observers on the payment queue, so make sure to set the delegate before adding any transaction observers if you intend to implement this method.
- (BOOL)paymentQueueShouldShowPriceConsent:(SKPaymentQueue *)paymentQueue API_DEPRECATED("Use Message.messages and Message.display(in:).", ios(13.4, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(tvos, macos, watchos);

@end


API_DEPRECATED("Use StoreKit 2 Transaction APIs.", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions;

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions;

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error API_DEPRECATED("Use AppStore.sync().", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue API_DEPRECATED("Use AppStore.sync().", ios(3.0, 18.0), tvos(9.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Sent when a user initiates an IAP buy from the App Store
- (BOOL)paymentQueue:(SKPaymentQueue *)queue shouldAddStorePayment:(SKPayment *)payment forProduct:(SKProduct *)product NS_SWIFT_NAME(paymentQueue(_:shouldAddStorePayment:for:)) API_DEPRECATED("Use PurchaseIntent.intents.", ios(11.0, 18.0), tvos(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos);

- (void)paymentQueueDidChangeStorefront:(SKPaymentQueue *)queue API_DEPRECATED("Use Storefront.updates.", ios(13.0, 18.0), tvos(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Sent when entitlements for a user have changed and access to the specified IAPs has been revoked.
- (void)paymentQueue:(SKPaymentQueue *)queue didRevokeEntitlementsForProductIdentifiers:(NSArray<NSString *> *)productIdentifiers NS_SWIFT_NAME(paymentQueue(_:didRevokeEntitlementsForProductIdentifiers:)) API_DEPRECATED("Use Transaction.updates.", ios(14.0, 18.0), macos(11.0, 15.0), tvos(14.0, 18.0), watchos(7.0, 11.0), visionos(1.0, 2.0));

@end

NS_ASSUME_NONNULL_END
