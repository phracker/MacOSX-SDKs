//
//  HMServiceGroup.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMService;

/*!
 * @abstract Used to describe a collection of HMService objects
 *
 * @discussion This class is used to group a collection of HMService objects.
 *             This allows for association of a set of accessory services into a group.
 *             Eg. A collection of lights can be grouped as the "Desk Lamps" service group.
 */
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMServiceGroup : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the service group.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Array of HMService objects that correspond to the services contained in this group.
 */
@property(readonly, copy, nonatomic) NSArray<HMService *> *services;

/*!
 * @brief A unique identifier for the service group.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the service group.
 *
 * @param name New name for the service group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Adds an service to this service group. The service and the group must be part of the same
 *        home. A service can be added to multiple service groups, e.g., a light can be added
 *        to "Desk Lamps" as well as "Dimmable Lamps" service groups.
 *
 * @param service Service to add to this group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addService:(HMService *)service completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an service from this service group.
 *
 * @param service Service to remove from this group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeService:(HMService *)service completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
