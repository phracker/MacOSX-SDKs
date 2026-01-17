//
//  NIError.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
NI_EXPORT NSErrorDomain const NIErrorDomain;

/**
 Error codes for nearby interaction session failures.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ERROR_ENUM(NIErrorDomain, NIErrorCode) {
    /** The platform does not support this operation */
    NIErrorCodeUnsupportedPlatform = -5889,
    
    /** Configuration is unsupported */
    NIErrorCodeInvalidConfiguration = -5888,

    /** The session has failed and cannot be restarted */
    NIErrorCodeSessionFailed = -5887,
    
    /** The session has been active for over the allowed period */
    NIErrorCodeResourceUsageTimeout = -5886,
    
    /** The maximum number of active sessions was exceeded */
    NIErrorCodeActiveSessionsLimitExceeded = -5885,
    
    /** The user did not authorize the session */
    NIErrorCodeUserDidNotAllow = -5884,
};


NS_ASSUME_NONNULL_END
