//
//  HMHome.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHomeManager;
@class HMAccessory;
@class HMRoom;
@class HMZone;
@class HMService;
@class HMServiceGroup;
@class HMActionSet;
@class HMTrigger;
@class HMUser;
@class HMHomeAccessControl;
@class HMAccessorySetupPayload;

@protocol HMHomeDelegate;

/*!
 @enum      HMHomeHubState

 @constant  HMHomeHubStateNotAvailable      No home hub is present.
 @constant  HMHomeHubStateConnected         Home hub is connected.
 @constant  HMHomeHubStateDisconnected      No home hub is connected.
 */
typedef NS_ENUM(NSUInteger, HMHomeHubState)
{
    HMHomeHubStateNotAvailable = 0,
    HMHomeHubStateConnected,
    HMHomeHubStateDisconnected
} API_AVAILABLE(ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Represents a home.
 *
 * @discussion This class represents a home and is the entry point to communicate and
 *             configure different accessories in the home. This is also used to manage
 *             all the rooms, zones, service groups, users, triggers, and action sets in
 *             the home.
 */
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMHome : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Delegate that receives updates on the state of the home.
 */
@property(weak, nonatomic, nullable) id<HMHomeDelegate> delegate;

/*!
 * @brief The name of the home.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Specifies whether this home is the primary home.
 */
@property(readonly, getter=isPrimary, nonatomic) BOOL primary;

/*!
 * @brief Specifies the state of the home hub.
 */
@property(readonly, nonatomic) HMHomeHubState homeHubState API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief A unique identifier for the home.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the home.
 *
 * @param name New name for the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end


@interface HMHome(HMAccessory)

/*!
 * @brief Array of HMAccessory objects that represents all accessories added to the home. 
 */
@property(readonly, copy, nonatomic) NSArray<HMAccessory *> *accessories;

/*!
 * @brief Adds a new accessory to the home.
 *
 * @param accessory Accessory to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an accessory from the home.
 *
 * @param accessory Accessory to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Assigns a new room for the accessory.
 *
 * @discussion When an accessory is added to a home, it is automatically assigned the room corresponding to
 *             + [HMHome roomForEntireHome]. This method is used to change the room assigned to an accessory.
 *
 * @param accessory Accessory whose rooms needs to modified
 *
 * @param room New room for the accessory.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)assignAccessory:(HMAccessory *)accessory toRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Queries all services that match the specified types.
 *
 * @param serviceTypes Array of NSString objects that specifies the service types to match.
 *
 * @return Array of HMService objects that match the specified service types, 
 *         nil if no matching services were found.
 */
- (nullable NSArray<HMService *> *)servicesWithTypes:(NSArray<NSString *> *)serviceTypes;

/*!
 * @brief unblock a blocked accessory.
 *
 * @discussion A misbehaving accessory will automatically be blocked.  After that all requests to
 *              the accessory will fail.  This API must be used to explicitly unblock the accessory
 *
 * @param accessory accessory to be unblocked
 *
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)unblockAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Find nearby accessories and add them to the home. During this process, each of the accessories added
 *        to the home is assigned to a room and its services are configured.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAndSetupAccessoriesWithCompletionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addAndSetUpAccessories());

/*!
 * @brief Add accessory with the given setup payload to the home.
 * @note  This SPI requires entitlement: com.apple.developer.homekit.allow-setup-payload
 *
 * @param completion Block that is invoked once the request is processed.
 *                   Accessories provides the list of added accessories.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAndSetupAccessoriesWithPayload:(HMAccessorySetupPayload *)payload completionHandler:(void (^)(NSArray<HMAccessory *>* __nullable accessories, NSError * __nullable error))completion API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addAndSetUpAccessories(payload:));

/*!
 * @brief True if this home supports all of the requirements for adding a network router.
 */
@property (readonly, assign, nonatomic) BOOL supportsAddingNetworkRouter API_AVAILABLE(ios(13.2), watchos(6.1), tvos(13.2)) API_UNAVAILABLE(macCatalyst, macos);

@end


@interface HMHome(HMUser)

/*!
 * @brief HMUser object representing the current user of the home.
 */
@property(readonly, strong, nonatomic) HMUser *currentUser API_AVAILABLE(ios(9.0), macCatalyst(14.0));

/*!
 * @brief Array of HMUser objects that represent all users associated with the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMUser *> *users API_DEPRECATED("No longer supported.", ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos, macCatalyst);

/*!
 * @brief Presents a view controller to manage users of the home.
 *
 * @discussion This API is available only for users that have administrator access to the home.
 *
 * @param completion Block that is invoked once user management is completed.
 *                   The completion block is fired to allow clients to know when the user has dismissed the view.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. If the user does not have administrator privileges the error code will be set to
 *                   HMErrorCodeInsufficientPrivileges.
 */
- (void)manageUsersWithCompletionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(9.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Adds a user to the home.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The HMUser object provides a reference to the user that was added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. The userInfo dictionary will contain the HMUserFailedAccessoriesKey which provides
 *                   more details on the accessories that failed to add the user.
 */
- (void)addUserWithCompletionHandler:(void (^)(HMUser * __nullable user, NSError * __nullable error))completion API_DEPRECATED_WITH_REPLACEMENT("-manageUsersWithCompletionHandler:", ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos, macos, macCatalyst);

/*!
 * @brief Removes a user from the home.
 *
 * @param user HMUser whose access is being revoked.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. The userInfo dictionary will contain the HMUserFailedAccessoriesKey which provides
 *                   more details on the accessories that failed to remove the user.
 */
- (void)removeUser:(HMUser *)user completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED_WITH_REPLACEMENT("-manageUsersWithCompletionHandler:", ios(8.0, 9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @brief Retrieve the access level of the user associated with the home.
 */
- (HMHomeAccessControl *)homeAccessControlForUser:(HMUser *)user API_AVAILABLE(ios(9.0), macCatalyst(14.0));

@end


@interface HMHome(HMRoom)

/*!
 * @brief Array of HMRoom objects that represents all rooms in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMRoom *> *rooms;

/*!
 * @brief Adds a room to the home.
 *
 * @param roomName Name of the room to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMRoom is the new room added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addRoomWithName:(NSString *)roomName completionHandler:(void (^)(HMRoom * __nullable room, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addRoom(named:));

/*!
 * @brief Removes a room from the home. 
 * @discussion Any references to this room will be removed from all properties
 *             of the home. For example, the room will be removed from the zone.
 *             Any accessories associated contained by this room will be moved to
 *             the room provided by - [HMHome roomForEntireHome].
 *
 * @param room Room to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method returns a room that represents the entire home. This can be used to assign a room
 *        to a service that is not necessarily located in one particular room.
 *
 * @return HMRoom that represents the home.
 */
- (HMRoom *)roomForEntireHome;

@end


@interface HMHome(HMZone)

/*!
 * @brief Array of HMZone objects that represents all the zones in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMZone *> *zones;

/*!
 * @brief Adds a zone to the home.
 *
 * @param zoneName Name of the zone to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMZone is the new zone added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addZoneWithName:(NSString *)zoneName completionHandler:(void (^)(HMZone * __nullable zone, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addZone(named:));

/*!
 * @brief Removes a zone from the home.
 *
 * @param zone Zone to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeZone:(HMZone *)zone completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end


@interface HMHome(HMServiceGroup)

/*!
 * @brief Array of HMServiceGroup objects that represents all service groups in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMServiceGroup *> *serviceGroups;

/*!
 * @brief Adds a service group to the home.
 *
 * @param serviceGroupName Name of the service group to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMServiceGroup is the new service group added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addServiceGroupWithName:(NSString *)serviceGroupName completionHandler:(void (^)(HMServiceGroup * __nullable group, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addServiceGroup(named:));

/*!
 * @brief Removes a service group from the home.
 *
 * @param group Service group to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeServiceGroup:(HMServiceGroup *)group completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end


@interface HMHome(HMActionSet)

/*!
 * @brief Array of HMActionSet objects that represents all the action sets in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMActionSet *> *actionSets;

/*!
 * @brief Adds a new action set to the home.
 *
 * @param actionSetName Name of the action set to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMActionSet parameter is the new action set added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addActionSetWithName:(NSString *)actionSetName completionHandler:(void (^)(HMActionSet * __nullable actionSet, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addActionSet(named:));

/*!
 * @brief Removes an existing action set from the home.
 *
 * @param actionSet Action set to remove from the home. A builtin action set cannot be removed.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Executes all the actions within an action set.
 *
 * @param actionSet Action set to execute.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)executeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Retrieve a built-in action set for the home.
 *
 * @param actionSetType Type of the builtin action set. Supported action set types are HMActionSetTypeWakeUp,
 *                      HMActionSetTypeSleep, HMActionSetTypeHomeDeparture and HMActionSetTypeHomeArrival.
 *
 * @return Reference to the built-in action set corresponding to type argument,
 *         nil if no matching action set is found.
 */
- (nullable HMActionSet *)builtinActionSetOfType:(NSString *)actionSetType API_AVAILABLE(ios(9.0));

@end


@interface HMHome(HMTrigger)

/*!
 * @brief Array of HMTrigger objects that represents all the triggers in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMTrigger *> *triggers;

/*!
 * @brief Adds a trigger to the home. Unless the trigger object is added to the home, it cannot be 
 *        activated.
 *
 * @discussion  Triggers are specific to an iOS device and are not synced across multiple devices to
 *              ensure that the action sets are executed only once.
 *
 * @param trigger Trigger to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMTrigger parameter is the new trigger added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addTrigger:(HMTrigger *)trigger completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes a trigger from the home. If the trigger is active, they are automatically deactivated.
 *
 * @param trigger Trigger to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeTrigger:(HMTrigger *)trigger completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end


/*!
 * @brief This delegate receives update on the various accessories, action sets, groups and triggers 
 *        managed in the home.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@protocol HMHomeDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate of a change in the name of a home.
 *
 * @param home Sender of this message.
 */
- (void)homeDidUpdateName:(HMHome *)home;

/*!
 * @brief Informs the delegate when the access control for current user has been updated.
 *
 * @param home Sender of the message.
 */
- (void)homeDidUpdateAccessControlForCurrentUser:(HMHome *)home API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Informs the delegate of addition of an accessory to the home.
 *
 * @param home Sender of the message.
 *
 * @param accessory Accessory that was added to the home.
 */
- (void)home:(HMHome *)home didAddAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of removal of an accessory from the home.
 *
 * @param home Sender of the message.
 *
 * @param accessory Accessory that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate that a user was added to the home.
 *
 * @param home Sender of this message.
 *
 * @param user User who was granted access to the home.
 */
- (void)home:(HMHome *)home didAddUser:(HMUser *)user;

/*!
 * @brief Informs the delegate that a user was removed from the home.
 *
 * @param home Sender of this message.
 *
 * @param user User whose access was revoked from the home.
 */
- (void)home:(HMHome *)home didRemoveUser:(HMUser *)user;

/*!
 * @brief Informs the delegate when a new room is assigned to an accessory
 *
 * @param home Sender of the message.
 *
 * @param room New room for the accessory.
 *
 * @param accessory Accessory that was assigned a new room.
 */
- (void)home:(HMHome *)home didUpdateRoom:(HMRoom *)room forAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of addition of a room to the home.
 *
 * @param home Sender of the message.
 *
 * @param room Room that was added to the home.
 */
- (void)home:(HMHome *)home didAddRoom:(HMRoom *)room;

/*!
 * @brief Informs the delegate of removal of a room from the home.
 *
 * @param home Sender of the message.
 *
 * @param room Room that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveRoom:(HMRoom *)room;

/*!
 * @brief Informs the delegate that the name of a room was modified
 *
 * @param home Sender of this message.
 *
 * @param room Room that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForRoom:(HMRoom *)room;

/*!
 * @brief Informs the delegate of addition of a zone to the home.
 *
 * @param home Sender of the message.
 *
 * @param zone Zone that was added to the home.
 */
- (void)home:(HMHome *)home didAddZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate of removal of a zone from the home.
 *
 * @param home Sender of the message.
 *
 * @param zone Zone that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that the name of a zone was modified.
 *
 * @param home Sender of this message.
 *
 * @param zone Zone that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that the room was added to a zone.
 *
 * @param home Sender of this message.
 *
 * @param room Room that was added to the zone.
 *
 * @param zone Zone that was modified.
 */
- (void)home:(HMHome *)home didAddRoom:(HMRoom *)room toZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that the room was removed from a zone.
 *
 * @param home Sender of this message.
 *
 * @param room Room that was removed from the zone.
 *
 * @param zone Zone that was modified.
 */
- (void)home:(HMHome *)home didRemoveRoom:(HMRoom *)room fromZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that a service group was added to the home.
 *
 * @param home Sender of the message.
 *
 * @param group Service group that was added to the home.
 */
- (void)home:(HMHome *)home didAddServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that a service group was removed from the home.
 *
 * @param home Sender of the message.
 *
 * @param group Service group that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that the name of a service group was modified.
 *
 * @param home Sender of this message.
 *
 * @param group The service group that was modfied.
 */
- (void)home:(HMHome *)home didUpdateNameForServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that a service was added to a service group.
 *
 * @param home Sender of this message.
 *
 * @param service Service that was added to the service group.
 *
 * @param group Service group that was modified.
 */
- (void)home:(HMHome *)home didAddService:(HMService *)service toServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that a service was removed from a service group.
 *
 * @param home Sender of this message.
 *
 * @param service Service that was removed from the service group.
 *
 * @param group Service group that was modified.
 */
- (void)home:(HMHome *)home didRemoveService:(HMService *)service fromServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that an action set was added to the home.
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was added to the home.
 */
- (void)home:(HMHome *)home didAddActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate that an action set was removed from the home.
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate that the name of an action set was modified.
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate that the actions of an action set was modified.
 * This indicates that an action was added/removed or modified (value replaced)
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was modified.
 */
- (void)home:(HMHome *)home didUpdateActionsForActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate of the addition of a trigger to the home.
 *
 * @param home Sender of the message.
 *
 * @param trigger Trigger that was added to the home.
 */
- (void)home:(HMHome *)home didAddTrigger:(HMTrigger *)trigger;

/*!
 * @brief Informs the delegate of removal of a trigger from the home.
 *
 * @param home Sender of the message.
 *
 * @param trigger Trigger that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveTrigger:(HMTrigger *)trigger;

/*!
 * @brief Informs the delegate that the name of the trigger was modified.
 *
 * @param home Sender of this message.
 *
 * @param trigger Trigger that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForTrigger:(HMTrigger *)trigger;

/*!
 * @brief Informs the delegate whenever a trigger is updated. For example, this method may be
 *        invoked when a trigger is activated, when a trigger fires, or when the action sets 
 *        associated with a trigger are modified.
 *
 * @param home Sender of this message.
 *
 * @param trigger The trigger that was updated.
 */
- (void)home:(HMHome *)home didUpdateTrigger:(HMTrigger *)trigger;


/*!
 * @brief Informs the delegate that an accessory has been unblocked
 *
 * @param home Sender of this message.
 *
 * @param accessory Accessory that was unblocked
 */
- (void)home:(HMHome *)home didUnblockAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate that a configured accessory encountered an error. The 
 *        delegate should check the blocked state of the accessory
 *
 * @param home Sender of this message.
 *
 * @param error Error encountered by accessory.
 *
 * @param accessory Accessory that encountered the error
 */

- (void)home:(HMHome *)home didEncounterError:(NSError*)error forAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate when state of the home hub changes.
 *
 * @param home Sender of the message.
 *
 * @param homeHubState The new home hub state.
 */
- (void)home:(HMHome *)home didUpdateHomeHubState:(HMHomeHubState)homeHubState API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Informs the delegate when the supported features of this home changes.
 *
 * The supported features covered by this are currently:
 *   - supportsAddingNetworkRouter
 *
 * @param home Sender of the message.
 */
- (void)homeDidUpdateSupportedFeatures:(HMHome *)home API_AVAILABLE(ios(13.2), watchos(6.1), tvos(13.2)) API_UNAVAILABLE(macos);

@end

/*!
 * @brief Key that provides more details on the accessories that failed during an 
 *        addUser:completionHandler: or removeUser:completionHandler: call. 
 *
 * @discussion The value associated with this key is an NSArray of NSDictionary objects. Each dictionary
 *             contains the UUID of the accessory that failed to the added/removed and the value
 *             corresponding to the dictionary key is an NSError that provides more details on the
 *             underlying error for that accessory.
 */
HM_EXTERN NSString * const HMUserFailedAccessoriesKey API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
