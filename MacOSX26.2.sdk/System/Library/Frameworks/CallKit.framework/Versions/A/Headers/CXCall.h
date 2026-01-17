//
//  CXCall.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@interface CXCall : NSObject

@property (nonatomic, readonly, copy) NSUUID *UUID;

@property (nonatomic, readonly, assign, getter=isOutgoing) BOOL outgoing;
@property (nonatomic, readonly, assign, getter=isOnHold) BOOL onHold;
@property (nonatomic, readonly, assign) BOOL hasConnected;
@property (nonatomic, readonly, assign) BOOL hasEnded;

- (instancetype)init NS_UNAVAILABLE;

- (BOOL)isEqualToCall:(CXCall *)call;

@end

NS_ASSUME_NONNULL_END
