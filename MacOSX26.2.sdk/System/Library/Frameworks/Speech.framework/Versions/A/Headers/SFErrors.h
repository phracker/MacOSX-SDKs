//
//  SFErrors.h
//  SpeechRecognition
//
//  Created by Donovan Voss on 10/25/22.
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const SFSpeechErrorDomain
API_AVAILABLE(macos(14), ios(17), tvos(18));

/**
 Error codes that can be thrown under the Speech framework's error domain.
 */
typedef NS_ERROR_ENUM (SFSpeechErrorDomain, SFSpeechErrorCode) {
    /// There was an internal error.
    SFSpeechErrorCodeInternalServiceError = 1,

    /// The audio file could not be read.
    SFSpeechErrorCodeAudioReadFailed = 2,

    // MARK: CustomLM data related errors
    
    /// The custom language model templates were malformed.
    SFSpeechErrorCodeUndefinedTemplateClassName = 7,
    
    /// The custom language model file was malformed.
    SFSpeechErrorCodeMalformedSupplementalModel = 8,
    
    /// The operation timed out.
    SFSpeechErrorCodeTimeout = 12,

    /// A required parameter is missing/nil.
    SFSpeechErrorCodeMissingParameter = 13,
} API_AVAILABLE(macos(14), ios(17), tvos(18));

NS_ASSUME_NONNULL_END
