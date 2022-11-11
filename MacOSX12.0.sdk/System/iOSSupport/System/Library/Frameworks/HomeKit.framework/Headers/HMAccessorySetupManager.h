//
//  HMAccessorySetupManager.h
//  HomeKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCHIPServiceTopology;

HM_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macos, macCatalyst)
@interface HMAccessorySetupManager : NSObject

/*!
 * @abstract Add and set up CHIP accessories with a CHIP Partner Ecosystem App. This flow is unique among the
 *           "Add Accessory" flows in that it primarily targets the originating (i.e. non-HomeKit) ecosystem
 *           to add accessories to. "Add to Apple Home?" is presented as a final, optional step after the user
 *           has completed pairing and configuration with the Partner Ecosystem App
 *
 * @param topology  A configuration object representing the topology of the initiating ecosystem
 */
- (void)addAndSetUpAccessoriesForTopology:(HMCHIPServiceTopology *)topology completionHandler:(HMErrorBlock)completion;

@end

NS_ASSUME_NONNULL_END
