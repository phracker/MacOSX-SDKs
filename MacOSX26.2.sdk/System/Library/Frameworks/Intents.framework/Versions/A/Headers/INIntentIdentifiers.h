//
//  INIntentIdentifiers.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

// Identifier for INStartAudioCallIntent class.
INTENTS_EXTERN NSString *const INStartAudioCallIntentIdentifier API_DEPRECATED("INStartAudioCallIntentIdentifier is deprecated. Please adopt INStartCallIntentIdentifier instead", ios(10.0, 13.0), watchos(3.2, 6.0)) API_UNAVAILABLE(macos, tvos);

// Identifier for INStartVideoCallIntent class.
INTENTS_EXTERN NSString *const INStartVideoCallIntentIdentifier API_DEPRECATED("INStartVideoCallIntentIdentifier is deprecated. Please adopt INStartCallIntentIdentifier instead", ios(10.0, 13.0), watchos(3.2, 6.0)) API_UNAVAILABLE(macos, tvos);

// Identifier for INSearchCallHistoryIntent class.
INTENTS_EXTERN NSString *const INSearchCallHistoryIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INStartCallIntent class.
INTENTS_EXTERN NSString *const INStartCallIntentIdentifier API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

// Identifier for INAnswerCallIntent class.
INTENTS_EXTERN NSString *const INAnswerCallIntentIdentifier API_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2), tvos(16.2));

// Identifier for INHangUpCallIntent class.
INTENTS_EXTERN NSString *const INHangUpCallIntentIdentifier API_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2), tvos(16.2));

// Identifier for INSetAudioSourceInCarIntent class.
INTENTS_EXTERN NSString *const INSetAudioSourceInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INSetClimateSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetClimateSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INSetDefrosterSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetDefrosterSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INSetSeatSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetSeatSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INSetProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSetProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INSaveProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSaveProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INStartWorkoutIntent class.
INTENTS_EXTERN NSString *const INStartWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INPauseWorkoutIntent class.
INTENTS_EXTERN NSString *const INPauseWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INEndWorkoutIntent class.
INTENTS_EXTERN NSString *const INEndWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INCancelWorkoutIntent class.
INTENTS_EXTERN NSString *const INCancelWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INResumeWorkoutIntent class.
INTENTS_EXTERN NSString *const INResumeWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INSetRadioStationIntent class.
INTENTS_EXTERN NSString *const INSetRadioStationIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos, tvos);

// Identifier for INSendMessageIntent class.
INTENTS_EXTERN NSString *const INSendMessageIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INSearchForMessagesIntent class.
INTENTS_EXTERN NSString *const INSearchForMessagesIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INSetMessageAttributeIntent class.
INTENTS_EXTERN NSString *const INSetMessageAttributeIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, watchos);

// Identifier for INSendPaymentIntent class.
INTENTS_EXTERN NSString *const INSendPaymentIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INRequestPaymentIntent class.
INTENTS_EXTERN NSString *const INRequestPaymentIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INSearchForPhotosIntent class.
INTENTS_EXTERN NSString *const INSearchForPhotosIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INStartPhotoPlaybackIntent class.
INTENTS_EXTERN NSString *const INStartPhotoPlaybackIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INListRideOptionsIntent class.
INTENTS_EXTERN NSString *const INListRideOptionsIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INRequestRideIntent class.
INTENTS_EXTERN NSString *const INRequestRideIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

// Identifier for INGetRideStatusIntent class.
INTENTS_EXTERN NSString *const INGetRideStatusIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
