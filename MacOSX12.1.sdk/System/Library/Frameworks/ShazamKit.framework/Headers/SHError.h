//
//  SHError.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

SH_EXPORT NSErrorDomain const SHErrorDomain API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// Error codes returned when generating and matching signatures
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NS_ERROR_ENUM(SHErrorDomain, SHErrorCode) {
    
    /// The @c AVAudioFormat is not supported
    /// @discussion ShazamKit only accepts certain audio formats
    /// @see -[SHSignatureGenerator appendBuffer:atTime:error] for valid formats
    SHErrorCodeInvalidAudioFormat = 100,
    
    /// The audio provided was not contiguous
    /// @discussion Shazam requires audio to be contiguous in order
    /// to match.
    SHErrorCodeAudioDiscontinuity = 101,
    
    /// Failed to create a signature from the provided audio
    /// @discussion Validate the audio you are supplying, it may be silence.
    SHErrorCodeSignatureInvalid = 200,
    
    /// The signature duration is outside the valid range
    /// @discussion The signature is valid but is too long/short for
    /// the service attempting to match it
    SHErrorCodeSignatureDurationInvalid = 201,
    
    /// The request to match the signature failed
    /// @discussion The attempt failed and was not matched, trying again may result in success
    /// @note This code does not indicate a 'No Match'
    SHErrorCodeMatchAttemptFailed = 202,
    
    /// Failed to load the Custom Catalog
    /// @discussion Validate the structure of the Catalog file
    SHErrorCodeCustomCatalogInvalid = 300,
    
    /// The Custom Catalog URL was invalid
    /// @discussion The URL must be a filePath URL that contains a valid Catalog
    SHErrorCodeCustomCatalogInvalidURL = 301,
    
    /// Failed to sync some content to the user's library
    /// @discussion Failed to add some items to the user's library, trying again may result in success
    /// Underlying error may contain more details about the failure
    SHErrorCodeMediaLibrarySyncFailed = 400
       
};
