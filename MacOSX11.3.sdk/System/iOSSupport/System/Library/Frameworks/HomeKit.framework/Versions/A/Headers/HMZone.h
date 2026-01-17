//
//  HMZone.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMRoom;

/*!
 * @brief Used to describe a collection of HMRoom objects
 *
 * @discussion This class is used to group a collection of rooms.
 *             This allows for association of a set of rooms into a group.
 *             Eg. "Living Room" and "Kitchen" rooms can be grouped together
 *             in the "Downstairs" zone.
 */
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMZone : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the zone.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Array of HMRoom objects that correspond to the rooms contained in this zone.
 */
@property(readonly, copy, nonatomic) NSArray<HMRoom *> *rooms;

/*!
 * @brief A unique identifier for the zone.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the zone.
 *
 * @param name New name for the zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Adds a room to a zone.
 *
 * @discussion Both the room and the zone should be part of the home.  A room can be added to multiple
 *             zones, e.g., a room "Kitchen" can be added to "Downstairs" as well as "Outdoor" zones.
 *
 * @param room Room to add to this zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes a room from the zone.
 *
 * @param room Room to remove from this zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
