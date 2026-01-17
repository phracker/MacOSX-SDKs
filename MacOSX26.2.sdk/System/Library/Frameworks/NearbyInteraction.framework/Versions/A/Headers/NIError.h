//
//  NIError.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT NSErrorDomain const NIErrorDomain;

/**
 Error codes for nearby interaction session failures.
 */
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
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

    /** ARSession Configuration provided is not compatible or the platform does not support camera assistance. */
    NIErrorCodeInvalidARConfiguration API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos, macos) = -5883 ,

    /** A Nearby Accessory session has been associated with a peer device (such as a Bluetooth peer) that is not available */
    NIErrorCodeAccessoryPeerDeviceUnavailable API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos, macos) = -5882,

    /**
     The NINearbyPeerConfiguration provided is not compatible with the capabilities of the peer device
     */
    NIErrorCodeIncompatiblePeerDevice API_AVAILABLE(ios(17.0), watchos(10.0), macos(14.0), tvos(17.0)) = -5881,

    /**
     The maximum number of active extended distance measurement sessions was exceeded
     */
    NIErrorCodeActiveExtendedDistanceSessionsLimitExceeded API_AVAILABLE(ios(17.0), watchos(10.0), macos(14.0), tvos(17.0)) = -5880,

};


NS_ASSUME_NONNULL_END
