//
//  INBookRestaurantReservationIntent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantOffer.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantResolutionResult.h>
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INRestaurantGuestResolutionResult.h>
#import <Intents/INStringResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INBookRestaurantReservationIntent : INIntent <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant
             bookingDateComponents:(NSDateComponents *)bookingDateComponents
                         partySize:(NSUInteger)partySize
                 bookingIdentifier:(nullable NSString *)bookingIdentifier
                             guest:(nullable INRestaurantGuest *)guest
                     selectedOffer:(nullable INRestaurantOffer *)selectedOffer
   guestProvidedSpecialRequestText:(nullable NSString *)guestProvidedSpecialRequestText API_AVAILABLE(ios(11.0));

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (copy, NS_NONATOMIC_IOSONLY) NSDateComponents *bookingDateComponents;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *bookingIdentifier; // unique identifier supplied by vendor to this booking
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest; // model object containing contact information
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantOffer *selectedOffer; // offer selected by user, if one exists
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *guestProvidedSpecialRequestText; // text captured in UI from user for special requests

@end

@class INBookRestaurantReservationIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macos, watchos, tvos)
@protocol INBookRestaurantReservationIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INBookRestaurantReservationIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INBookRestaurantReservationIntentResponse
 
 */

- (void)handleBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent completion:(void (^)(INBookRestaurantReservationIntentResponse *response))completion  NS_SWIFT_NAME(handle(bookRestaurantReservation:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INBookRestaurantReservationIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INEndWorkoutIntentResponse
 
 */

- (void)confirmBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent completion:(void (^)(INBookRestaurantReservationIntentResponse *response))completion  NS_SWIFT_NAME(confirm(bookRestaurantReservation:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INIntentResolutionResult
 
 */

- (void)resolveRestaurantForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));
- (void)resolveBookingDateComponentsForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INDateComponentsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBookingDateComponents(for:completion:));
- (void)resolvePartySizeForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(for:completion:));
- (void)resolveGuestForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INRestaurantGuestResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGuest(for:completion:));
- (void)resolveGuestProvidedSpecialRequestTextForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGuestProvidedSpecialRequestText(for:completion:));

@end
NS_ASSUME_NONNULL_END
