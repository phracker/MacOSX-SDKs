//
//  MKLocalSearchResponse.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

MK_CLASS_AVAILABLE(10_9, 6_1)
@interface MKLocalSearchResponse : NSObject

// An array of MKMapItems sorted by relevance in descending order
@property (nonatomic, readonly) NSArray *mapItems;

@property (nonatomic, readonly) MKCoordinateRegion boundingRegion;

@end
