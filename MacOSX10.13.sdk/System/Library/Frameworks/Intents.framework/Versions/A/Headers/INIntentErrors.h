//
//  INIntentErrors.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

INTENTS_EXTERN NSString * const INIntentErrorDomain API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

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
    
    // Extension connection
    INIntentErrorExtensionLaunchingTimeout = 5000,
    INIntentErrorExtensionBringUpFailed = 5001,
    
    
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));
