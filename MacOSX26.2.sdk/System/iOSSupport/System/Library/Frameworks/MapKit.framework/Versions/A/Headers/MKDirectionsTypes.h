//
//  MKDirectionsTypes.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

typedef NS_OPTIONS(NSUInteger, MKDirectionsTransportType) {
    MKDirectionsTransportTypeAutomobile = 1 << 0,
    MKDirectionsTransportTypeWalking = 1 << 1,
    MKDirectionsTransportTypeTransit NS_ENUM_AVAILABLE(10_11, 9_0) = 1 << 2, // Only supported for ETA calculations
    MKDirectionsTransportTypeCycling API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0), tvos(14.0), visionos(1.0)) = 1 << 3,
    MKDirectionsTransportTypeAny = 0x0FFFFFFF
} API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2), watchos(1.0));
