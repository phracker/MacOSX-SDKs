/*
 *  CMFallDetectionManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>
#import "CMFallDetectionEvent.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CMFallDetectionDelegate;

/**
 *  CMFallDetectionManager
 *
 *  @discussion
 *  Use CMFallDetectionManager to receive information about Fall Detection events. Not all watch models support Fall Detection, check for availability before creating an instance of CMFallDetectionManager.
 *  CMFallDetectionManager requires an entitlement from Apple. To apply for the entitlement, see Fall Detection Entitlement Request.
 *
 * Set the delegate immediately after creating an instance of CMFallDetectionManager. Creating multiple instances of CMFallDetectionManager is not supported and should be avoided.
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(7.2)) API_UNAVAILABLE(macos, ios, tvos)
@interface CMFallDetectionManager : NSObject

/**
 * available
 * @discussion
 * Returns a  value indicating whether the current device supports Fall Detection.
 */
@property (class, nonatomic, readonly, getter=isAvailable) BOOL available;

/**
 * authorizationStatus
 * @discussion
 * Returns a value indicating whether the user has authorized the app to receive Fall Detection updates
 */
@property (nonatomic, readonly) CMAuthorizationStatus authorizationStatus;

/**
 * delegate
 *  @discussion
 *    The delegate object to receive Fall Detection events.
 */
@property (nonatomic, weak) id<CMFallDetectionDelegate> delegate;


/**
 * @discussion
 * Requests the user’s permission to access Fall Detection information.
 */
- (void)requestAuthorizationWithHandler:(void(^)(CMAuthorizationStatus status))handler;

@end

/**
 *  CMFallDetectionDelegate
 *
 * @brief CMFallDetectionManager notifies its delegate about Fall Detection related information using this protocol
 * @sa CMFallDetectionManager
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(7.2)) API_UNAVAILABLE(macos, ios, tvos)
@protocol CMFallDetectionDelegate <NSObject>

@optional

/**
 * @brief
 * Update the delegate with a new Fall Detection event
 *
 *  @param handler
 *  Apps running in the background have a finite amount of time to process Fall Detection events. Call this handler to indicate that the app has finished handling the event. The system may suspend or terminate the app before calling this block.
 *
 * @discussion
 * Fall Detection events may occur when the app is not running.
 * Following a Fall Detection event, the system will launch the watchOS app in the background giving it small amount of background execution time. This time should be used for critical tasks related to the Fall Event. For example: placing a network request or scheduling a local notification.
 * In order to receive Fall Detection events, create a new CMFallDetectionManager instance and set its delegate early in the watchOS app lifecycle (applicationDidFinishLaunching for example). Note that instances of WKInterfaceController may not be created when launched in the background.
 *
 *
 * If multiple Fall Detection events are generated while the app is not running, only the most recent event will be reported on the next app launch.
 *
 * The same event may be reported across different app launches, always check the date of the event before processing it.
 *
 * Fall Detection events can be simulated with the watchOS simulator. Use it to test the background functionality of your app.
 *
 */
- (void)fallDetectionManager:(CMFallDetectionManager *)fallDetectionManager didDetectEvent:(CMFallDetectionEvent *)event completionHandler:(void(^ __nonnull)(void))handler;

/**
 * @discussion
 * Update the delegate when the app's Fall Detection authorization status changes
 */
 - (void)fallDetectionManagerDidChangeAuthorization:(CMFallDetectionManager *)fallDetectionManager;

@end

NS_ASSUME_NONNULL_END
