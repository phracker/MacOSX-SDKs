//
//  CXCallController.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXAction;
@class CXCallObserver;
@class CXTransaction;

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@interface CXCallController : NSObject

/// Initialize call controller with a private, serial queue.
- (instancetype)init;

/// Initialize call controller with specified queue, which is used for calling completion blocks.
- (instancetype)initWithQueue:(dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) CXCallObserver *callObserver;

/// Request a transaction to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed to the CXProvider's -provider:executeTransaction: delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransaction:(CXTransaction *)transaction completion:(void (^)(NSError *_Nullable error))completion;

/// Request a transaction containing the specified actions to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed to the CXProvider's -provider:executeTransaction: delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransactionWithActions:(NSArray<CXAction *> *)actions completion:(void (^)(NSError *_Nullable error))completion API_AVAILABLE(ios(11.0), macCatalyst(13.0), watchos(9.0));

/// Request a transaction containing the specified action to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed to the CXProvider's -provider:executeTransaction: delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransactionWithAction:(CXAction *)action completion:(void (^)(NSError *_Nullable error))completion API_AVAILABLE(ios(11.0), macCatalyst(13.0), watchos(9.0));

@end

NS_ASSUME_NONNULL_END
