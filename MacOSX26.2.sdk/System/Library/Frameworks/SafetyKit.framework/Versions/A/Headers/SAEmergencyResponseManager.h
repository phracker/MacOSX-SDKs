
//
//  SAEmergencyResponseManager.h
//  SafetyKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafetyKit/SABase.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SAEmergencyResponseDelegate;

/**
 * @brief This enumeration defines the status of requested voice call
 * @sa SAEmergencyResponseManagerVoiceCallStatus
 */
typedef NS_ENUM(NSInteger, SAEmergencyResponseManagerVoiceCallStatus) {
    SAEmergencyResponseManagerVoiceCallStatusDialing, /// < the system is dialing the voice call
    SAEmergencyResponseManagerVoiceCallStatusActive, /// < the system dialed voice call is connected and active
    SAEmergencyResponseManagerVoiceCallStatusDisconnected, ///< the system dialed voice call is disconnected after being active
    SAEmergencyResponseManagerVoiceCallStatusFailed, ///< the system dialed voice call failed to connect
} NS_SWIFT_NAME(SAEmergencyResponseManager.VoiceCallStatus) API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos);


/**
 * SAEmergencyResponseManager

 *
 * @discussion
 * Use SAEmergencyResponseManager to request actions in response to an emergency event.
 * Set the delegate to monitor the progress of requested emergency response actions.
 * SAEmergencyResponseManager requires user authorization for at least one of the emergency event detections e.g. SACrashDetectionEvent
 *
 * SAEmergencyResponseManager requires an entitlement from Apple to at least one of the emergency event detections. To apply for the entitlement, see respective detection mechanisms
 */
SA_EXTERN API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos)
@interface SAEmergencyResponseManager : NSObject

/**
 * delegate
 *
 * @discussion
 * The delegate object to receive updates about requested emergency response action.
 */
@property (nonatomic, readwrite, weak) id<SAEmergencyResponseDelegate> delegate;

/**
 * @discussion
 * Requests the system to dial a voice call on behalf of the user.
 * Apps running in the background / foreground can request to dial a voice call without user confirmation. Emergency numbers are not allowed.
 * Requests are accepted only if user has authorized the app to receive and handle emergency detection events and only for a limited time after an emergency event is detected.
 *
 * @sa SAEmergencyResponseDelegate
 *
 * @param phoneNumber
 * Apps can request the system to dial a voice call by providing a phone number. Emergency numbers are not allowed.
 *
 * @param handler
 * Completion handler invoked with the status of the voice call request.
 * If requested is accepted, the handler is invoked with a nil error. Interpret the error returned using SAErrorDomain.
 * Requests will fail with SAErrorNotAuthorized if user has not authorized the app to receive and handle any emergency events.
 * Requests will fail with SAErrorNotAvailable if invoked outside of the limited time window after an emergency event is detected.
 * Use the SAEmergencyResponseDelegate to monitor the progress of the voice call.
 */
- (void)dialVoiceCallToPhoneNumber:(NSString *)phoneNumber
                 completionHandler:(void(^)(BOOL requestAccepted, NSError * _Nullable error))handler;

@end

/**
 * SAEmergencyResponseDelegate
 *
 * @brief
 * SAEmergencyResponseManager notifies its delegate about status of the requested emergency response action
 *
 * @sa SAEmergencyResponseManager
 */
SA_EXTERN API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos)
@protocol SAEmergencyResponseDelegate <NSObject>
@optional

/**
 * @discussion
 * Voice call can be requested when running in the foreground or background within a limited time window of a detected emergency event,
 * Use this delegate to monitor the status of the requested voice call.
 */
- (void)emergencyResponseManager:(SAEmergencyResponseManager *)emergencyResponseManager
        didUpdateVoiceCallStatus:(SAEmergencyResponseManagerVoiceCallStatus)voiceCallStatus NS_SWIFT_NAME(emergencyResponseManager(_:didUpdateVoiceCallStatus:));

@end

NS_ASSUME_NONNULL_END
