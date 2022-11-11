//
//  HMAccessorySetupManager.h
//  HomeKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessorySetupRequest;
@class HMAccessorySetupResult;
@class HMMatterTopology;

/*!
 *  @abstract   This class can be used to launch system UI that will allow the user to go through the process
 *              of adding one or more accessories to a particular home and follow up with additional setup.
 *              These APIs do not require that the current app has home data authorization
 */
HM_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macos, macCatalyst)
@interface HMAccessorySetupManager : NSObject

/*!
 *  @abstract   Launch system UI to perform the process of setting up accessories with the given request.
 *              During this process, each of the accessories is added to a home, assigned to a room and
 *              further configured based on its services
 *
 *  @param request A request object describing information about how to set up the accessory
 *  @param completion A block that is invoked once the setup process finishes. On failure, the result will be
 *                    nil and the error will provide additional information
 */
- (void)performAccessorySetupUsingRequest:(HMAccessorySetupRequest *)request completionHandler:(void(^)(HMAccessorySetupResult * _Nullable result, NSError * _Nullable error))completion API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, tvos);

/*!
 *  @abstract   Launch system UI to perform the process of setting up Matter accessories with a Matter Partner
 *              Ecosystem App. This flow is different from other accessory setup flows in that it primarily
 *              targets the ecosystem of the originating (i.e. non-HomeKit) app as the ecosystem to add
 *              accessories to. The option to add to Apple Home is presented as a final, optional step after
 *              the user has completed setup with the Matter Partner Ecosystem App
 *
 *  @param request A request object describing information about how to set up the accessory
 *  @param topology A configuration object representing the topology of the initiating ecosystem
 *  @param completion A block that is invoked once the setup process finishes. The provided error will be nil
 *                    on success or will provide additional information on failure
 */
- (void)performMatterEcosystemAccessorySetupUsingRequest:(HMAccessorySetupRequest *)request
                                                topology:(HMMatterTopology *)topology
                                       completionHandler:(HMErrorBlock)completion API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, tvos);
- (void)addAndSetUpAccessoriesForTopology:(HMMatterTopology *)topology completionHandler:(HMErrorBlock)completion API_DEPRECATED("Use -[HMAccessorySetupManager performAccessorySetupUsingRequest:topology:completionHandler:] instead", ios(15.0, 15.4));

@end

NS_ASSUME_NONNULL_END
