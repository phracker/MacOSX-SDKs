//
//  INIntentIdentifiers.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

// Identifier for INStartAudioCallIntent class.
INTENTS_EXTERN NSString *const INStartAudioCallIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INStartVideoCallIntent class.
INTENTS_EXTERN NSString *const INStartVideoCallIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos);

// Identifier for INSearchCallHistoryIntent class.
INTENTS_EXTERN NSString *const INSearchCallHistoryIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INSetAudioSourceInCarIntent class.
INTENTS_EXTERN NSString *const INSetAudioSourceInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetClimateSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetClimateSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetDefrosterSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetDefrosterSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetSeatSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetSeatSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSetProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSaveProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSaveProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INStartWorkoutIntent class.
INTENTS_EXTERN NSString *const INStartWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INPauseWorkoutIntent class.
INTENTS_EXTERN NSString *const INPauseWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INEndWorkoutIntent class.
INTENTS_EXTERN NSString *const INEndWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INCancelWorkoutIntent class.
INTENTS_EXTERN NSString *const INCancelWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INResumeWorkoutIntent class.
INTENTS_EXTERN NSString *const INResumeWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INSetRadioStationIntent class.
INTENTS_EXTERN NSString *const INSetRadioStationIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSendMessageIntent class.
INTENTS_EXTERN NSString *const INSendMessageIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INSearchForMessagesIntent class.
INTENTS_EXTERN NSString *const INSearchForMessagesIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INSetMessageAttributeIntent class.
INTENTS_EXTERN NSString *const INSetMessageAttributeIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos);

// Identifier for INSendPaymentIntent class.
INTENTS_EXTERN NSString *const INSendPaymentIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INRequestPaymentIntent class.
INTENTS_EXTERN NSString *const INRequestPaymentIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INSearchForPhotosIntent class.
INTENTS_EXTERN NSString *const INSearchForPhotosIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INStartPhotoPlaybackIntent class.
INTENTS_EXTERN NSString *const INStartPhotoPlaybackIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INListRideOptionsIntent class.
INTENTS_EXTERN NSString *const INListRideOptionsIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INRequestRideIntent class.
INTENTS_EXTERN NSString *const INRequestRideIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INGetRideStatusIntent class.
INTENTS_EXTERN NSString *const INGetRideStatusIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);
