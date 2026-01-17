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
    INIntentErrorNoAppAvailable = 2005,
    
    // Requests
    INIntentErrorRequestTimedOut = 3001,
    INIntentErrorMissingInformation = 3002,
    
    // User Vocabulary Sync
    INIntentErrorInvalidUserVocabularyFileLocation = 4000,
    
    // Extension connection
    INIntentErrorExtensionLaunchingTimeout = 5000,
    INIntentErrorExtensionBringUpFailed = 5001,
    
    // Image loading, storage, and retrieval
    INIntentErrorImageGeneric = 6000,
    INIntentErrorImageNoServiceAvailable = 6001,
    INIntentErrorImageStorageFailed = 6002,
    INIntentErrorImageLoadingFailed = 6003,
    INIntentErrorImageRetrievalFailed = 6004,
    INIntentErrorImageProxyLoop = 6005,
    INIntentErrorImageProxyInvalid = 6006,
    INIntentErrorImageProxyTimeout = 6007,
    INIntentErrorImageServiceFailure = 6008,
    INIntentErrorImageScalingFailed = 6009,
    INIntentErrorPermissionDenied = 6010,

    // Voice Shortcuts
    INIntentErrorVoiceShortcutCreationFailed = 7000,
    INIntentErrorVoiceShortcutGetFailed = 7001,
    INIntentErrorVoiceShortcutDeleteFailed = 7002,
    
    // Encoding
    INIntentErrorEncodingGeneric = 8000,
    INIntentErrorEncodingFailed = 8001,
    
    // Decoding
    INIntentErrorDecodingGeneric = 9000,
    
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));
