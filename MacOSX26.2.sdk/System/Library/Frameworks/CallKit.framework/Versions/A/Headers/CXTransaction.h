//
//  CXTransaction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXAction;

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@interface CXTransaction : NSObject <NSCopying, NSSecureCoding>

/// Unique ID
@property (nonatomic, readonly, copy) NSUUID *UUID;

/// Whether all actions have been completed
@property (nonatomic, readonly, assign, getter=isComplete) BOOL complete;

/// The list of actions contained by the receiver
@property (nonatomic, readonly, copy) NSArray<__kindof CXAction *> *actions;

- (instancetype)initWithActions:(NSArray<CXAction *> *)actions NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAction:(CXAction *)action;

/// Add the provided action to the receiver's list of actions
- (void)addAction:(CXAction *)action;

@end

NS_ASSUME_NONNULL_END
