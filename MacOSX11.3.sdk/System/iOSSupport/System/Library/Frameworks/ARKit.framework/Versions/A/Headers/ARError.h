//
//  ARError.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN NSString *const ARErrorDomain;

API_AVAILABLE(ios(11.0))
typedef NS_ERROR_ENUM(ARErrorDomain, ARErrorCode) {
    /** Unsupported configuration. */
    ARErrorCodeUnsupportedConfiguration                               = 100,
    
    /** A sensor required to run the session is not available. */
    ARErrorCodeSensorUnavailable                                      = 101,
    
    /** A sensor failed to provide the required input. */
    ARErrorCodeSensorFailed                                           = 102,
    
    /** App does not have permission to use the camera. The user may change this in settings. */
    ARErrorCodeCameraUnauthorized                                     = 103,
    
    /** App does not have permission to use the microphone. The user may change this in settings. */
    ARErrorCodeMicrophoneUnauthorized                                 = 104,
    
    /** App does not have permission to use the location data of the device. The user may change this in settings. */
    ARErrorCodeLocationUnauthorized          API_AVAILABLE(ios(14.0)) = 105,
    
    /** World tracking has encountered a fatal error. */
    ARErrorCodeWorldTrackingFailed                                    = 200,

    /** Geo tracking is not available at this location. */
    ARErrorCodeGeoTrackingNotAvailableAtLocation  API_AVAILABLE(ios(14.0)) = 201,

    /** Geo tracking has encountered a runtime error. */
    ARErrorCodeGeoTrackingFailed             API_AVAILABLE(ios(14.0)) = 202,


    /** Invalid reference image */
    ARErrorCodeInvalidReferenceImage         API_AVAILABLE(ios(11.3)) = 300,

    /** Invalid reference object. */
    ARErrorCodeInvalidReferenceObject        API_AVAILABLE(ios(12.0)) = 301,
    
    /** Invalid world map. */
    ARErrorCodeInvalidWorldMap               API_AVAILABLE(ios(12.0)) = 302,
    
    /** Invalid configuration. */
    ARErrorCodeInvalidConfiguration          API_AVAILABLE(ios(12.0)) = 303,
    
    /** Collaboration data is not available. */
    ARErrorCodeCollaborationDataUnavailable  API_DEPRECATED_WITH_REPLACEMENT("ARErrorCodeInvalidCollaborationData", ios(13.0, 13.2)) = 304,

    /** Invalid collaboration data.*/
    ARErrorCodeInvalidCollaborationData      API_AVAILABLE(ios(13.2)) = 304,
    
    /** Insufficient features. */
    ARErrorCodeInsufficientFeatures          API_AVAILABLE(ios(12.0)) = 400,
    
    /** Object merge failed. */
    ARErrorCodeObjectMergeFailed             API_AVAILABLE(ios(12.0)) = 401,
    
    /** Unable to read or write to file. */
    ARErrorCodeFileIOFailed                  API_AVAILABLE(ios(12.0)) = 500,

    /** Generic request failure. */
    ARErrorCodeRequestFailed                 API_AVAILABLE(ios(14.0)) = 501,
};

NS_ASSUME_NONNULL_END
