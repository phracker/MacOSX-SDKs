//
//  SKArcadeService.h
//  StoreKit
//
//  Created by Ross LeBeau on 4/2/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS @interface SKArcadeService : NSObject

+ (void)registerArcadeAppWithRandomFromLib:(NSData *)randomFromLib
                   randomFromLibLength:(uint32_t)randomFromLibLength
                         resultHandler:(void (^)(NSData * _Nullable randomFromFP, uint32_t randomFromFPLength, NSData * _Nullable cmacOfAppPID, uint32_t cmacOfAppPIDLength, NSError * _Nullable error))resultHandler;

+ (void)arcadeSubscriptionStatusWithNonce:(uint64_t)nonce
                                resultHandler:(void (^)(NSData * _Nullable subscriptionStatus, uint32_t subscriptionStatusLength, NSData * _Nullable cmacOfNonce, uint32_t cmacOfNonceLength, NSError * _Nullable error))resultHandler;

+ (void)repairArcadeApp;

@end

NS_ASSUME_NONNULL_END
