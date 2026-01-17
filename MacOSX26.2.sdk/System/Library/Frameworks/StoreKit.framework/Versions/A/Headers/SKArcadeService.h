//
//  SKArcadeService.h
//  StoreKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(13.0), macos(10.15), macCatalyst(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos) @interface SKArcadeService : NSObject

+ (void)registerArcadeAppWithRandomFromLib:(NSData *)randomFromLib
                   randomFromLibLength:(uint32_t)randomFromLibLength
                         resultHandler:(void (^)(NSData * _Nullable randomFromFP, uint32_t randomFromFPLength, NSData * _Nullable cmacOfAppPID, uint32_t cmacOfAppPIDLength, NSError * _Nullable error))resultHandler API_AVAILABLE(ios(13.0), macos(10.15), macCatalyst(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

+ (void)arcadeSubscriptionStatusWithNonce:(uint64_t)nonce
                                resultHandler:(void (^)(NSData * _Nullable subscriptionStatus, uint32_t subscriptionStatusLength, NSData * _Nullable cmacOfNonce, uint32_t cmacOfNonceLength, NSError * _Nullable error))resultHandler API_AVAILABLE(ios(13.0), macos(10.15), macCatalyst(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

+ (void)repairArcadeApp API_AVAILABLE(ios(13.0), macos(10.15), macCatalyst(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
