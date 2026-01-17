//
//  Intents.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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

// Common Types
#import <Intents/INPersonHandle.h>
#import <Intents/INDateComponentsRange.h>
#import <Intents/INImage.h>
#import <Intents/INPerson.h>
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
#import <Intents/INStartAudioCallIntent.h>
#import <Intents/INStartAudioCallIntentResponse.h>
#import <Intents/INStartVideoCallIntent.h>
#import <Intents/INStartVideoCallIntentResponse.h>
#import <Intents/INSearchCallHistoryIntent.h>
#import <Intents/INSearchCallHistoryIntentResponse.h>

#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeResolutionResult.h>
#import <Intents/INCallCapabilityOptions.h>

// Messages Domain
#import <Intents/INSendMessageIntent.h>
#import <Intents/INSendMessageIntentResponse.h>
#import <Intents/INSearchForMessagesIntent.h>
#import <Intents/INSearchForMessagesIntentResponse.h>

#import <Intents/INMessage.h>
#import <Intents/INMessageAttributeOptions.h>
#import <Intents/INMessageAttributeOptionsResolutionResult.h>

// Utilities
#import <Intents/CLPlacemark+IntentsAdditions.h>
#import <Intents/NSUserActivity+IntentsAdditions.h>

// Deprecated
#import <Intents/INPerson_Deprecated.h>
