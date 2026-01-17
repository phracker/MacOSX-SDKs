//
//  INIntentErrors.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

INTENTS_EXTERN NSString * const INIntentErrorDomain API_AVAILABLE(macosx(10.12), ios(10.0));

typedef NS_ENUM(NSInteger, INIntentErrorCode) {
    // Interactions
    INIntentErrorInteractionOperationNotSupported = 1900,
    INIntentErrorDonatingInteraction = 1901,
    INIntentErrorDeletingAllInteractions = 1902,
    INIntentErrorDeletingInteractionWithIdentifiers = 1903,
    INIntentErrorDeletingInteractionWithGroupIdentifier = 1904,
    
    // Extension discovery / info plist validation
    INIntentErrorIntentSupportedByMultipleExtension = 2001,
    INIntentErrorRestrictedIntentsNotSupportedByExtension = 2002,
    INIntentErrorNoHandlerProvidedForIntent = 2003,
    INIntentErrorInvalidIntentName = 2004,
    
    // Requests
    INIntentErrorRequestTimedOut = 3001,
    
    // User Vocabulary Sync
    INIntentErrorInvalidUserVocabularyFileLocation = 4000,
} API_AVAILABLE(macosx(10.12), ios(10.0));
