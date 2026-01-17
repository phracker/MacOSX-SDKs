
/*
 *  CLError.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

/*
 *  CLError
 *  
 *  Discussion:
 *    Error returned as code to NSError from CoreLocation.
 */
typedef enum {
    kCLErrorLocationUnknown  = 0,         // location is currently unknown, but CL will keep trying
    kCLErrorDenied,                       // CL access has been denied (eg, user declined location use)
    kCLErrorNetwork,                      // general, network-related error
    kCLErrorHeadingFailure,               // heading could not be determined
    kCLErrorRegionMonitoringDenied,       // Location region monitoring has been denied by the user
    kCLErrorRegionMonitoringFailure,      // A registered region cannot be monitored
    kCLErrorRegionMonitoringSetupDelayed, // CL could not immediately initialize region monitoring
    kCLErrorGeocodeFoundNoResult,         // A geocode request yielded no result
    kCLErrorGeocodeCanceled               // A geocode request was cancelled
} CLError;

