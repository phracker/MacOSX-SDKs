//
//  CXCallObserver.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCall;
@class CXCallObserver;

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@protocol CXCallObserverDelegate <NSObject>

- (void)callObserver:(CXCallObserver *)callObserver callChanged:(CXCall *)call;

@end

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@interface CXCallObserver : NSObject

/// Retrieve the current call list, blocking on initial state retrieval if necessary
@property (nonatomic, readonly, copy) NSArray<CXCall *> *calls;

/// Set delegate and optional queue for delegate callbacks to be performed on.
/// A nil queue implies that delegate callbacks should happen on the main queue. The delegate is stored weakly
- (void)setDelegate:(nullable id<CXCallObserverDelegate>)delegate queue:(nullable dispatch_queue_t)queue;

@end

NS_ASSUME_NONNULL_END
