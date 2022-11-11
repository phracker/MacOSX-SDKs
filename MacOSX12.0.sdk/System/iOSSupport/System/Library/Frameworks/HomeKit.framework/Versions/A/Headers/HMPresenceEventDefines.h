//
//  HMPresenceEventDefines.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @abstract This enumeration describes the different types of presence events.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMPresenceEventType)
{
    /*!
     * This corresponds to trigger an event for every user entering a home.
     * This cannot be added as predicate.
     */
    HMPresenceEventTypeEveryEntry = 1,
    
    /*!
     * This corresponds to trigger an event for every user exiting a home.
     * This cannot be added as predicate.
     */
    HMPresenceEventTypeEveryExit = 2,
    
    /*!
     * This corresponds to trigger an event for the first user entering a home.
     */
    HMPresenceEventTypeFirstEntry = 3,
    
    /*!
     * This corresponds to trigger an event for the last user exiting a home.
     */
    HMPresenceEventTypeLastExit = 4,
    
    /*!
     * Convenience value for First Entry to use in predicate of HMEventTrigger.
     */
    HMPresenceEventTypeAtHome = HMPresenceEventTypeFirstEntry,
    
    /*!
     * Convenience value for Last Exit to use in predicate of HMEventTrigger.
     */
    HMPresenceEventTypeNotAtHome = HMPresenceEventTypeLastExit,
};

/*!
 * @abstract This enumeration describes the different types of user sets in presence events.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMPresenceEventUserType)
{
    /*!
     * Only current user's presence is used.
     */
    HMPresenceEventUserTypeCurrentUser = 1,
    
    /*!
     * Presence of all home users is used.
     */
    HMPresenceEventUserTypeHomeUsers = 2,
    
    /*!
     * Presence of custom set of home users is used.
     */
    HMPresenceEventUserTypeCustomUsers = 3,
};
