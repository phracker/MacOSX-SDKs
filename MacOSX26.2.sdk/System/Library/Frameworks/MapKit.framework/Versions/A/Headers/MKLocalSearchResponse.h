//
//  MKLocalSearchResponse.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

@class MKMapItem;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(6.1), tvos(9.2), watchos(1.0))
@interface MKLocalSearchResponse : NSObject

// An array of MKMapItems sorted by relevance in descending order
@property (nonatomic, readonly) NSArray<MKMapItem *> *mapItems;

@property (nonatomic, readonly) MKCoordinateRegion boundingRegion;

@end

NS_ASSUME_NONNULL_END
