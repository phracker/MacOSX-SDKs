//
//  Intents.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for Intents.
FOUNDATION_EXPORT double IntentsVersionNumber;

//! Project version string for Intents.
FOUNDATION_EXPORT const unsigned char IntentsVersionString[];

#ifndef __INTENTS_INDIRECT__
#define __INTENTS_INDIRECT__
#endif

// Base
#import <Intents/INIntent.h>
#import <Intents/INIntentErrors.h>
#import <Intents/INIntentHandlerProviding.h>
#import <Intents/INIntentIdentifiers.h>
#import <Intents/INIntentResponse.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INIntentResolutionResult+Custom.h>
#import <Intents/INDomainHandling.h>
#import <Intents/INInteraction.h>
#import <Intents/INSpeakable.h>
#import <Intents/INParameter.h>
#import <Intents/INObjectSection.h>
#import <Intents/INObjectCollection.h>

// Intents & Intent Responses
#import <Intents/INIntents.h>
#import <Intents/INIntentResponses.h>

// Generated
#import <Intents/Intents_Generated.h>

// Donation Metadata
#import <Intents/INIntentDonationMetadata.h>
#import <Intents/INSendMessageIntentDonationMetadata.h>

// Extension
#import <Intents/INExtension.h>

// Common Types
#import <Intents/INPersonHandle.h>
#import <Intents/INCurrencyAmount.h>
#import <Intents/INDateComponentsRange.h>
#import <Intents/INImage.h>
#import <Intents/INObject.h>
#import <Intents/INPerson.h>
#import <Intents/INRecurrenceRule.h>
#import <Intents/INSpeakableString.h>
#import <Intents/INFile.h>

// Common Resolution Results
#import <Intents/INBooleanResolutionResult.h>
#import <Intents/INDateComponentsRangeResolutionResult.h>
#import <Intents/INDoubleResolutionResult.h>
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INPersonResolutionResult.h>
#import <Intents/INPlacemarkResolutionResult.h>
#import <Intents/INSpeakableStringResolutionResult.h>
#import <Intents/INStringResolutionResult.h>
#import <Intents/INTemperatureResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>
#import <Intents/INRestaurantResolutionResult.h>
#import <Intents/INRestaurantGuestResolutionResult.h>
#import <Intents/INURLResolutionResult.h>
#import <Intents/INLengthResolutionResult.h>
#import <Intents/INMassResolutionResult.h>
#import <Intents/INVolumeResolutionResult.h>
#import <Intents/INSpeedResolutionResult.h>
#import <Intents/INEnergyResolutionResult.h>
#import <Intents/INEnumResolutionResult.h>
#import <Intents/INObjectResolutionResult.h>
#import <Intents/INTimeIntervalResolutionResult.h>

// Messages Domain
#import <Intents/INMessage.h>
#import <Intents/INSendMessageAttachment.h>

// Payments Domain
#import <Intents/INBalanceAmount.h>

// Ridesharing Domain
#import <Intents/INPriceRange.h>
#import <Intents/INRideOption.h>
#import <Intents/INRideStatus.h>
#import <Intents/INRideDriver.h>
#import <Intents/INRideVehicle.h>
#import <Intents/INRideFareLineItem.h>
#import <Intents/INRidePartySizeOption.h>
#import <Intents/INRideCompletionStatus.h>

// Reservation Common
#import <Intents/INReservation.h>
#import <Intents/INReservationAction.h>

// Reservations
#import <Intents/INFlightReservation.h>
#import <Intents/INLodgingReservation.h>
#import <Intents/INRentalCarReservation.h>
#import <Intents/INRestaurantReservation.h>
#import <Intents/INTicketedEventReservation.h>
#import <Intents/INTrainReservation.h>
#import <Intents/INBusReservation.h>
#import <Intents/INBoatReservation.h>

// Restaurant Booking
#import <Intents/INIntentRestaurantReservation.h>

// User Vocabulary
#import <Intents/INVocabulary.h>

#import <Intents/INUpcomingMediaManager.h>

// Utilities
#import <Intents/CLPlacemark+IntentsAdditions.h>
#import <Intents/INPerson+SiriAdditions.h>
#import <Intents/INPreferences.h>
#import <Intents/INSiriAuthorizationStatus.h>
#import <Intents/INFocusStatusCenter.h>
#import <Intents/NSExtensionContext+ShareExtension.h>
#import <Intents/NSString+Intents.h>
#import <Intents/NSUserActivity+IntentsAdditions.h>

// User Context
#import <Intents/INUserContext.h>
#import <Intents/INMediaUserContext.h>

// Notes
#import <Intents/INNoteContent.h>
#import <Intents/INTextNoteContent.h>
#import <Intents/INImageNoteContent.h>

// Shortcuts
#import <Intents/INRelevantShortcut.h>
#import <Intents/INRelevantShortcutStore.h>
#import <Intents/INShortcut.h>
#import <Intents/INVoiceShortcut.h>
#import <Intents/INVoiceShortcutCenter.h>

// Media
#import <Intents/INMediaItem.h>

// User Notifications
#import <Intents/INSendMessageIntent+UserNotifications.h>
#import <Intents/INStartCallIntent+UserNotifications.h>

// Deprecated
#import <Intents/INPerson_Deprecated.h>
#import <Intents/INRequestRideIntent_Deprecated.h>
#import <Intents/INRideDriver_Deprecated.h>
#import <Intents/INSaveProfileInCarIntent_Deprecated.h>
#import <Intents/INSearchCallHistoryIntent_Deprecated.h>
#import <Intents/INStartAudioCallIntent_Deprecated.h>
#import <Intents/INStartCallIntent_Deprecated.h>
#import <Intents/INSearchForMessagesIntent_Deprecated.h>
#import <Intents/INSendMessageIntent_Deprecated.h>
#import <Intents/INSetProfileInCarIntent_Deprecated.h>
#import <Intents/INSetClimateSettingsInCarIntent_Deprecated.h>
#import <Intents/INSetDefrosterSettingsInCarIntent_Deprecated.h>
#import <Intents/INSetSeatSettingsInCarIntent_Deprecated.h>
#import <Intents/INSearchForNotebookItemsIntent_Deprecated.h>
#import <Intents/INPlayMediaIntent_Deprecated.h>
#import <Intents/INSetTaskAttributeIntent_Deprecated.h>
#import <Intents/INAddTasksIntent_Deprecated.h>
#import <Intents/INMediaSearch_Deprecated.h>
#import <Intents/INCallRecord_Deprecated.h>
#import <Intents/INSendMessageIntentResponse_Deprecated.h>
