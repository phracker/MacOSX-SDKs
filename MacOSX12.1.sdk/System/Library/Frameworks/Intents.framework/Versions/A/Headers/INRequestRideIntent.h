//
//  INRequestRideIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INIntegerResolutionResult;
@class INPaymentMethod;
@class INPlacemarkResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INRequestRideIntent : INIntent

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation
                        rideOptionName:(nullable INSpeakableString *)rideOptionName
                             partySize:(nullable NSNumber *)partySize
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod
                   scheduledPickupTime:(nullable INDateComponentsRange *)scheduledPickupTime NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(10.3), watchos(3.2));

// Specifies the location to to begin the ride.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;

// Specifies where the ride should end.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *rideOptionName;

// Defines the number of people in the party requesting the ride.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *partySize NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentMethod *paymentMethod;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *scheduledPickupTime API_AVAILABLE(ios(10.3));

@end

@class INRequestRideIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INRequestRideIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INRequestRideIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INRequestRideIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INRequestRideIntentResponse containing the details of the result of having executed the intent

 @see  INRequestRideIntentResponse
 */

- (void)handleRequestRide:(INRequestRideIntent *)intent
               completion:(void (^)(INRequestRideIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INRequestRideIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INRequestRideIntentResponse
 */

- (void)confirmRequestRide:(INRequestRideIntent *)intent
                completion:(void (^)(INRequestRideIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolvePickupLocationForRequestRide:(INRequestRideIntent *)intent
                             withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePickupLocation(for:with:));

- (void)resolveDropOffLocationForRequestRide:(INRequestRideIntent *)intent
                              withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDropOffLocation(for:with:));

- (void)resolveRideOptionNameForRequestRide:(INRequestRideIntent *)intent
                             withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRideOptionName(for:with:));

- (void)resolvePartySizeForRequestRide:(INRequestRideIntent *)intent
                        withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(for:with:));

- (void)resolveScheduledPickupTimeForRequestRide:(INRequestRideIntent *)intent
                                  withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveScheduledPickupTime(for:with:)) API_AVAILABLE(ios(10.3));

@end

NS_ASSUME_NONNULL_END
