//
//  Intents.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
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
#import <Intents/INIntentResponse.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INInteraction.h>
#import <Intents/INSpeakable.h>

// Intents & Intent Responses
#import <Intents/INIntents.h>
#import <Intents/INIntentResponses.h>

// Common Types
#import <Intents/INPersonHandle.h>
#import <Intents/INDateComponentsRange.h>
#import <Intents/INImage.h>
#import <Intents/INPerson.h>
#import <Intents/INRecurrenceRule.h>
#import <Intents/INSpeakableString.h>
#import <Intents/INPersonHandleLabel.h>
#import <Intents/INPersonRelationship.h>

// Common Resolution Results
#import <Intents/INDateComponentsRangeResolutionResult.h>
#import <Intents/INPersonResolutionResult.h>
#import <Intents/INPlacemarkResolutionResult.h>
#import <Intents/INSpeakableStringResolutionResult.h>
#import <Intents/INStringResolutionResult.h>

// Calls Domain
#import <Intents/INCallRecord.h>
#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeResolutionResult.h>
#import <Intents/INCallDestinationType.h>
#import <Intents/INCallDestinationTypeResolutionResult.h>
#import <Intents/INCallCapability.h>
#import <Intents/INCallCapabilityOptions.h>
#import <Intents/INCallRecordTypeOptionsResolutionResult.h>

// Messages Domain
#import <Intents/INSendMessageRecipientResolutionResult.h>

#import <Intents/INMessage.h>
#import <Intents/INMessageAttributeOptions.h>
#import <Intents/INMessageAttributeOptionsResolutionResult.h>

// Utilities
#import <Intents/CLPlacemark+IntentsAdditions.h>
#import <Intents/NSUserActivity+IntentsAdditions.h>

// Deprecated
#import <Intents/INPerson_Deprecated.h>
#import <Intents/INSearchCallHistoryIntent_Deprecated.h>
#import <Intents/INStartAudioCallIntent_Deprecated.h>
#import <Intents/INSearchForMessagesIntent_Deprecated.h>
#import <Intents/INSendMessageIntent_Deprecated.h>
