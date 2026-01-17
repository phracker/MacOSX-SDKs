//
//  HMAccessorySetupManager.h
//  HomeKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class HMAccessorySetupRequest;
@class HMAccessorySetupResult;

/*!
 *  @abstract   This class can be used to launch system UI that will allow the user to go through the process
 *              of adding one or more accessories to a particular home and follow up with additional setup.
 *              These APIs do not require that the current app has home data authorization
 */
HM_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(15.0))
API_UNAVAILABLE(watchos, tvos, visionos)
API_UNAVAILABLE(macos, macCatalyst)
@interface HMAccessorySetupManager : NSObject

- (instancetype)init;

/*!
 *  @abstract   Launch system UI to perform the process of setting up accessories with the given request.
 *              During this process, each of the accessories is added to a home, assigned to a room and
 *              further configured based on its services
 *
 *  @param request A request object describing information about how to set up the accessory
 *  @param completion A block that is invoked once the setup process finishes. On failure, the result will be
 *                    nil and the error will provide additional information
 */
- (void)performAccessorySetupUsingRequest:(HMAccessorySetupRequest *)request completionHandler:(void (^)(HMAccessorySetupResult *_Nullable result, NSError *_Nullable error))completion API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
