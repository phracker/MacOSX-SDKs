//
//  HMEventTriggerActivationState.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract This enumeration describes the current activation state of the event trigger.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMEventTriggerActivationState)
{
    /*!
     * Trigger is not active because it is disabled
     */
    HMEventTriggerActivationStateDisabled = 0,
    
    /*!
     * Trigger is not active because there is no HomeHub
     */
    HMEventTriggerActivationStateDisabledNoHomeHub = 1,
    
    /*!
     * Trigger is not active because there is no compatible HomeHub
     */
    HMEventTriggerActivationStateDisabledNoCompatibleHomeHub = 2,
    
    /*!
     * Trigger is not active because Location Authorization has been turned off by user
     */
    HMEventTriggerActivationStateDisabledNoLocationServicesAuthorization = 3,
    
    /*!
     * Trigger is currently active
     */
    HMEventTriggerActivationStateEnabled = 4,
};

NS_ASSUME_NONNULL_END


