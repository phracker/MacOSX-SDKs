//
//  CoreSpotlight.h
//  CoreSpotlight
//
//  Copyright © 2014–2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for CoreSpotlight.
FOUNDATION_EXPORT double CoreSpotlightVersionNumber;

//! Project version string for CoreSpotlight.
FOUNDATION_EXPORT const unsigned char CoreSpotlightVersionString[];

#define  CoreSpotlightAPIVersion 40

#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CSImportExtension.h>
#import <CoreSpotlight/CSIndexExtensionRequestHandler.h>
#import <CoreSpotlight/CSPerson.h>
#import <CoreSpotlight/CSSearchQuery.h>
#import <CoreSpotlight/CSSearchableIndex.h>
#import <CoreSpotlight/CSSearchableItem.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Categories.h>
#import <CoreSpotlight/CSSuggestion.h>
#import <CoreSpotlight/CSUserQuery.h>
