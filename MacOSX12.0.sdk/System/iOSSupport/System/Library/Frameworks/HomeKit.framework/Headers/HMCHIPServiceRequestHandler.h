//
//  HMCHIPServiceRequestHandler.h
//  HomeKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMCHIPServiceHome;
@class HMCHIPServiceRoom;

NS_ASSUME_NONNULL_BEGIN

HM_EXTERN API_AVAILABLE(ios(15.0))
@interface HMCHIPServiceRequestHandler : NSObject <NSExtensionRequestHandling>

/**
 * @abstract Use this method to vend the rooms that correspond to a given home to accessory setup. iOS will issue this request before presenting the "Select Room" card.
 * @param home The home for which iOS is requesting rooms.
 * @param completion Invoke the completion block with the requested rooms or an optional error.
 */
- (void)fetchRoomsInHome:(HMCHIPServiceHome *)home completion:(void (^)(NSArray<HMCHIPServiceRoom *> * _Nullable, NSError * _Nullable))completion NS_SWIFT_ASYNC_NAME(rooms(in:));

/*!
 * @abstract When this method is invoked, pair with the given accessory payload.
 * @param onboardingPayload The onboarding payload your CHIP stack will use to pair with the accessory.
 * @param completion Invoke the completion handler with an optional error after pairing.
 */
- (void)pairAccessoryInHome:(HMCHIPServiceHome *)home onboardingPayload:(NSString *)onboardingPayload completion:(void(^)( NSError * _Nullable ))completion;

/*!
 * @abstract When this method is invoked, configure the accessory with user selected attributes.
 * @param accessoryName The user given name for the accessory.
 * @param accessoryRoom The user selected room for the accessory.
 * @param completion Invoke the completion handler with an optional error after configuration.
 */
- (void)configureAccessoryWithName:(NSString *)accessoryName room:(HMCHIPServiceRoom *)accessoryRoom completion:(void(^)( NSError * _Nullable ))completion NS_SWIFT_NAME(configureAccessory(named:room:completion:));

@end

NS_ASSUME_NONNULL_END
