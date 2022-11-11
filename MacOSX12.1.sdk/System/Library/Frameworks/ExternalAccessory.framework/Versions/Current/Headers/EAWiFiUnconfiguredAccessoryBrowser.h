//
//  EAWiFiUnconfiguredAccessoryBrowser.h
//  ExternalAccessory
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

/*!
 * @brief Forward declaration of the EAWiFiUnconfiguredAccessory class.
 *
 */
@class EAWiFiUnconfiguredAccessory;

/*!
 * @brief Forward declaration of the UIViewController class.
 *
 */
@class UIViewController;

/*!
 * @brief Forward declaration of the EAWiFiUnconfiguredAccessoryBrowserDelegate protocol.
 *
 */
@protocol EAWiFiUnconfiguredAccessoryBrowserDelegate;

/*!
 *  @enum EAWiFiUnconfiguredAccessoryBrowserState
 *
 *  @discussion Represents the current state of a EAWiFiUnconfiguredAccessoryBrowser.
 *
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateWiFiUnavailable  Wi-Fi is unavailable due to the user placing the device in Airplane Mode or explicitly turning Wi-Fi off.
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateStopped          The browser is not actively searching for unconfigured accessories.
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateSearching        The browser is actively searching for unconfigured accessory.
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateConfiguring      The browser is actively configuring an accessory.
 *
 */
typedef NS_ENUM(NSInteger, EAWiFiUnconfiguredAccessoryBrowserState)
{
    EAWiFiUnconfiguredAccessoryBrowserStateWiFiUnavailable = 0,
    EAWiFiUnconfiguredAccessoryBrowserStateStopped,
    EAWiFiUnconfiguredAccessoryBrowserStateSearching,
    EAWiFiUnconfiguredAccessoryBrowserStateConfiguring,
};

/*!
 *  @enum EAWiFiUnconfiguredAccessoryConfigurationStatus
 *
 *  @discussion Represents the state of an EAWiFiUnconfiguredAccessory configuration process.
 *
 *  @constant EAWiFiUnconfiguredAccessoryConfigurationStatusSuccess                     The configuration of the accessory succeeded.
 *  @constant EAWiFiUnconfiguredAccessoryConfigurationStatusUserCancelledConfiguration  The user cancelled the configuration process.
 *  @constant EAWiFiUnconfiguredAccessoryConfigurationStatusFailed                      The configuration failed.
 *
 */
typedef NS_ENUM(NSInteger, EAWiFiUnconfiguredAccessoryConfigurationStatus)
{
    EAWiFiUnconfiguredAccessoryConfigurationStatusSuccess = 0,
    EAWiFiUnconfiguredAccessoryConfigurationStatusUserCancelledConfiguration,
    EAWiFiUnconfiguredAccessoryConfigurationStatusFailed,
};

/*!
 * @brief Interface for browsing unconfigured accessories
 *
 * @discussion This class brokers access to the MFi Wireless Accessory Configuration (WAC) process.
 *             This browser enables the application to scan for unconfigured accessories,
 *             connect them to the user's Wi-Fi infrastructure and configure attributes of
 *             the accessory.
 *
 */

NS_CLASS_AVAILABLE(NA, 8_0)
NS_ASSUME_NONNULL_BEGIN

@interface EAWiFiUnconfiguredAccessoryBrowser : NSObject

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive the browser events.
 *
 */
@property (weak, nonatomic, nullable) id<EAWiFiUnconfiguredAccessoryBrowserDelegate> delegate;

/*!
 * @property unconfiguredAccessories
 *
 * @discussion The set of discovered unconfigured accessories described by EAWiFiUnconfiguredAccessory objects.
 *             This snapshot will only include objects matching the filter predicate defined when starting the search.
 *
 */
@property (readonly, copy, atomic) NSSet<EAWiFiUnconfiguredAccessory *> *unconfiguredAccessories;

/*!
 * @brief Designated initializer.
 *
 * @discussion Initializes an instance of the EAWiFiUnconfiguredAccessoryBrowser class
 *             which can be further configured based on the application's interests.
 *
 * @param delegate The delegate that will receive the EAWiFiUnconfiguredAccessoryBrowserDelegate events.
 * @param queue    The dispatch queue the delegate would like to receive events on. If nil the events will be on the main queue.
 *
 * @return Instance object
 *
 */
- (instancetype)initWithDelegate:(nullable id<EAWiFiUnconfiguredAccessoryBrowserDelegate>)delegate queue:(nullable dispatch_queue_t)queue __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

/*!
 * @brief Start the search for unconfigured accessories
 *
 * @discussion Starts a Wi-Fi scan for unconfigured accessories. This power and resource intensive process and must
 *             only be used when actively searching for accessories. Scans should be stopped immediately when the
 *             desired accessories have been located.
 *
 * @param predicate The desired filter for unconfigured accessory results conforming to the EAWiFiUnconfiguredAccessory protocol.
 *
 */
- (void)startSearchingForUnconfiguredAccessoriesMatchingPredicate:(nullable NSPredicate *)predicate __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

/*!
 * @brief Stop the search for unconfigured MFi Wireless Accessory Configuration accessories
 *
 */
- (void)stopSearchingForUnconfiguredAccessories __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

/*!
 * @brief Begin the configuration process for the chosen accessory
 *
 * @discussion Stop the search for unconfigured accessories and begins the configuration process of the specified EAWiFiUnconfiguredAccessory.
 *             The user is guided through the configuration process via Apple UI. This process can take up to a few minutes to complete.
 *             The host application delegate will receive the didFinishConfiguringAccessory callback with an error that should be
 *             checked upon completion.
 *
 * @param accessory      The accessory the application wishes to configure
 * @param viewController The UIViewController that will host the Apple guided setup UI in the host application.
 *
 */
- (void)configureAccessory:(EAWiFiUnconfiguredAccessory *)accessory withConfigurationUIOnViewController:(UIViewController *)viewController __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

@end


#pragma mark - EAWiFiUnconfiguredAccessoryBrowserDelegate Methods

/*!
 *  @protocol EAWiFiUnconfiguredAccessoryBrowserDelegate
 *
 *  @discussion The delegate of a EAWiFiUnconfiguredAccessoryBrowser object must adopt the
 *              EAWiFiUnconfiguredAccessoryBrowserDelegate protocol. The required
 *              callbacks keep the delegate informed of the state of the search and configuration processes.
 *
 */
@protocol EAWiFiUnconfiguredAccessoryBrowserDelegate <NSObject>

/*!
 *  @method accessoryBrowser:didUpdateState:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser's state has changed.
 *
 *  @param browser The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param state   The current state of the EAWiFiUnconfiguredAccessoryBrowser.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didUpdateState:(EAWiFiUnconfiguredAccessoryBrowserState)state __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

/*!
 *  @method accessoryBrowser:didFindUnconfiguredAccessories:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser has found new unconfigured accessories that match
 *              the filter predicate defined when starting the search.
 *
 *  @param browser     The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param accessories The set of EAWiFiUnconfiguredAccessory objects that have been found since the last update.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didFindUnconfiguredAccessories:(NSSet<EAWiFiUnconfiguredAccessory *> *)accessories __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

/*!
 *  @method accessoryBrowser:didRemoveUnconfiguredAccessories:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser has removed unconfigured accessories from the scan results
 *              that match the filter predicate defined when starting the search.
 *
 *  @param browser     The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param accessories The set of EAWiFiUnconfiguredAccessory objects that have been removed from the scan results since the last update.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didRemoveUnconfiguredAccessories:(NSSet<EAWiFiUnconfiguredAccessory *> *)accessories __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

/*!
 *  @method accessoryBrowser:didFinishConfiguringAccessory:withStatus:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser has completed configuring the selected EAWiFiUnconfiguredAccessory.
 *
 *  @param browser   The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param accessory The EAWiFiUnconfiguredAccessory whose configuration process has completed.
 *  @param status    The status of the configuration process that has completed.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didFinishConfiguringAccessory:(EAWiFiUnconfiguredAccessory *)accessory withStatus:(EAWiFiUnconfiguredAccessoryConfigurationStatus)status __IOS_AVAILABLE(8.0) __OSX_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
