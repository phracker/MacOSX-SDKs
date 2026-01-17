//
//  HMLocationEvent.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;

/*!
 * @brief This class represents an event that is evaluated based on entry to and/or
 *        exit from a Region
 */
HM_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMLocationEvent : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new location event object
 *
 * @param region - Region with at least one property of notifyOnEntry or notifyOnExit set to TRUE.
 *
 * @return Instance object representing the location event.
 */
- (instancetype)initWithRegion:(CLRegion *)region API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Region on which events are triggered based on the properties notifyOnEntry and notifyOnExit.
 *        This property will be nil when an application is not authorized for location services.
 */
@property(readonly, strong, nonatomic, nullable) CLRegion *region;

/*!
 * @brief Updates the region
 *
 * @param region - New region with at least one property of notifyOnEntry or notifyOnExit set to TRUE.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateRegion:(CLRegion *)region completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("No longer supported.", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

@end


/*!
 * @brief This class represents an event that is evaluated based on entry to and/or
 *        exit from a Region
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableLocationEvent : HMLocationEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Region on which events are triggered based on the properties notifyOnEntry and notifyOnExit.
 *        This property will be nil when an application is not authorized for location services.
 */
@property(readwrite, strong, nonatomic, nullable) CLRegion *region;

@end

NS_ASSUME_NONNULL_END
