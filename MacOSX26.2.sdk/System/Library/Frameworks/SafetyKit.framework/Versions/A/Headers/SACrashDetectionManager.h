//
//  SACrashDetectionManager.h
//  SafetyKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <SafetyKit/SAAuthorizationStatus.h>
#import <SafetyKit/SACrashDetectionEvent.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SACrashDetectionDelegate;

/**
 * SACrashDetectionManager
 *
 * @discussion
 * Use SACrashDetectionManager to receive information about Vehicular Crash Detection events.
 * Not all phone models support Crash Detection, check for availability before creating an instance of SACrashDetectionManager.
 * Set the delegate immediately after creating an instance of SACrashDetectionManager. Creating multiple instances of SACrashDetectionManager is not supported and should be avoided.
 *
 * SACrashDetectionManager requires an entitlement from Apple. To apply for the entitlement, see Crash Detection Entitlement Request.
 */
SA_EXTERN API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos)
@interface SACrashDetectionManager : NSObject

/**
 * available
 *
 * @discussion
 * Returns a  value indicating whether the current device supports Crash Detection.
 */
@property (class, nonatomic, readonly, getter=isAvailable) BOOL available;

/**
 * authorizationStatus
 *
 * @discussion
 * Returns a value indicating whether the user has authorized the app to receive Crash Detection updates
 */
@property (nonatomic, readonly) SAAuthorizationStatus authorizationStatus;

/**
 * delegate
 *
 * @discussion
 * The delegate object to receive Crash Detection events.
 */
@property (nonatomic, readwrite, weak) id<SACrashDetectionDelegate> delegate;

/**
 * @discussion
 * Requests the user’s permission to access Crash Detection information.
 *
 * @param handler
 * Completion handler invoked with the status of the authorization request.
 */
- (void)requestAuthorizationWithCompletionHandler:(void(^)(SAAuthorizationStatus status, NSError * _Nullable error))handler;

@end

/**
 *  SACrashDetectionDelegate
 *
 *  @brief SACrashDetectionManager notifies its delegate about Crash Detection related information using this protocol.
 *
 *  @sa SACrashDetectionManager
 */
SA_EXTERN API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos)
@protocol SACrashDetectionDelegate <NSObject>
@optional

/**
 * @brief
 * Update the delegate with a new Crash Detection event
 *
 * @discussion
 * Crash Detection events may occur when the app is not running.
 * Following a Crash Detection event, the system will launch the iOS app in the background giving it small amount of background execution time. This time should be used for critical tasks related to the Crash Event. For example: placing a network request or scheduling a local notification.
 * In order to receive Crash Detection events, create a new SACrashDetectionManager instance and set its delegate early in the iOS app lifecycle (applicationDidFinishLaunching for example).
 *
 * If multiple Crash Detection events are generated while the app is not running, only the most recent event will be reported on the next app launch.
 *
 * The same event may be reported across different app launches, always check the date of the event before processing it.
 *
 * Crash Detection events can be simulated with the iOS simulator. Use it to test the background functionality of your app.
 */
- (void)crashDetectionManager:(SACrashDetectionManager *)crashDetectionManager
               didDetectEvent:(SACrashDetectionEvent *)event;

 @end

NS_ASSUME_NONNULL_END
