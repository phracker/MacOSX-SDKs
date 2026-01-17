//
//  WCSessionDictionaryTransfer.h
//  WatchConnectivity
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** Used to track a user info dictionary being transferred.
 */
NS_CLASS_AVAILABLE_IOS(9.0)
@interface WCSessionUserInfoTransfer : NSObject <NSSecureCoding>
@property (nonatomic, readonly, getter=isCurrentComplicationInfo) BOOL currentComplicationInfo __WATCHOS_UNAVAILABLE;
@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *userInfo;
@property (nonatomic, readonly, getter=isTransferring) BOOL transferring;
- (void)cancel;
@end

NS_ASSUME_NONNULL_END
