//
//  MKDirectionsTypes.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

typedef NS_OPTIONS(NSUInteger, MKDirectionsTransportType) {
    MKDirectionsTransportTypeAutomobile     = 1 << 0,
    MKDirectionsTransportTypeWalking        = 1 << 1,
    MKDirectionsTransportTypeAny            = 0x0FFFFFFF
} NS_ENUM_AVAILABLE(10_9, 7_0);
