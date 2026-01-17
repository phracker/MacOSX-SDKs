//
//  SHError.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

/// The error domain for specific errors for ShazamKit.
SH_EXPORT NSErrorDomain const SHErrorDomain API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// An error type that you create, or the system creates, to indicate problems with a catalog, match attempt, or signature, or when saving to a user's Shazam library.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NS_ERROR_ENUM(SHErrorDomain, SHErrorCode) {
    
    /// The error code to indicate an unsupported audio format.
    ///
    /// For the list of the supported audio formats, see ``SHSignatureGenerator/append(_:at:)``.
    SHErrorCodeInvalidAudioFormat = 100,
    
    /// The error code to indicate the use of noncontiguous audio to request a match.
    SHErrorCodeAudioDiscontinuity = 101,
    
    /// The error code to indicate that the system is unable to generate a signature from the audio.
    ///
    /// The most common cause of this error is silent audio input.
    SHErrorCodeSignatureInvalid = 200,
    
    /// The error code to indicate that the length of the generated signature is too long or too short to make a match in the catalog.
    ///
    /// This error occurs when the length of the generated signature is less than ``SHCatalog/minimumQuerySignatureDuration`` or greater than ``SHCatalog/maximumQuerySignatureDuration`` for the session ``SHSession/catalog``.
    SHErrorCodeSignatureDurationInvalid = 201,
    
    /// The error code to indicate when a Shazam Music catalog server issue prevents finding a match.
    SHErrorCodeMatchAttemptFailed = 202,
    
    /// The error code to indicate when the custom catalog fails to load due to an invalid format.
    SHErrorCodeCustomCatalogInvalid = 300,
    
    /// The error code to indicate that the format for the custom catalog URL is invalid.
    SHErrorCodeCustomCatalogInvalidURL = 301,
    
    /// The error code that indicates when the system fails to add media items to or remove items from the user's Shazam library.
    SHErrorCodeMediaLibrarySyncFailed = 400,
    
    /// The error code to indicate a generic framework error.
    SHErrorCodeInternalError API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) = 500,
    
    /// The error code to indicate when the system fails to fetch one or more media items.
    SHErrorCodeMediaItemFetchFailed API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) = 600
};
