//
//  HMAccessoryBrowser.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;
@class HMAccessory;

@protocol HMAccessoryBrowserDelegate;

/*! 
 * @brief This class is used to discover new accessories in the home
 *        that have never been paired with and therefore not part of the home.
 */
HM_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst)
@interface HMAccessoryBrowser : NSObject

/*!
 * @brief Delegate that receives updates on the state of the accessories discovered.
 */
@property(weak, nonatomic, nullable) id<HMAccessoryBrowserDelegate> delegate;

/*!
 * @brief This is the array of HMAccessory objects that represents new
 *        accessories that were discovered as part of a search session.
 *        This array is not updated when a search session is not in progress.
 */
@property(readonly, copy, nonatomic) NSArray<HMAccessory *> *discoveredAccessories;

/*!
 * @brief Starts searching for accessories that are not associated to any home.
 *
 * @discussion If any accessories are discovered, updates are sent to the delegate.
 *             This will scan for the following types of accessories:
 *                 Accessories supporting HomeKit Wireless Accessory Configuration profile
 *                 Accessories supporting HomeKit Accessory Protocol and are already on
 *                     the same infrastructure IP network
 *                 Accessories supporting HomeKit Accessory Protocol on Bluetooth LE transport
 *             The array of discovered accessories will be updated when this method
 *             is called, so applications should clear and reload any stored copies
 *             of that array or previous new accessory objects.
 *
 */
- (void)startSearchingForNewAccessories;

/*!
 * @brief Stops searching for new accessories.
 *
 * @discussion After this method is called, updates will not be sent to the delegate
 *             if new accessories are found or removed. Scanning may continue for system
 *             reasons or if other delegates are still in active searching sessions.
 *             The contents of the array of discovered accessories will not be updated until 
 *             startSearchingForNewAccessories is called.
 */
- (void)stopSearchingForNewAccessories;

@end

/*!
 * @brief This delegate receives updates about new accessories in the home.
 */
HM_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst) 
@protocol HMAccessoryBrowserDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate about new accessories discovered in the home.
 *
 * @param browser Sender of the message.
 *
 * @param accessory New accessory that was discovered.
 */
- (void)accessoryBrowser:(HMAccessoryBrowser *)browser didFindNewAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate about new accessories removed from the home.
 *
 * @param browser Sender of the message.
 *
 * @param accessory Accessory that was previously discovered but are no longer reachable.
 * 	            This method is also invoked when an accessory is added to a home.
 */
- (void)accessoryBrowser:(HMAccessoryBrowser *)browser didRemoveNewAccessory:(HMAccessory *)accessory;

@end

NS_ASSUME_NONNULL_END
