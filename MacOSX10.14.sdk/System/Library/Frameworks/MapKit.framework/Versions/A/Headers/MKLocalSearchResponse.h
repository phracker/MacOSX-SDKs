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

NS_CLASS_AVAILABLE(10_9, 6_1) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKLocalSearchResponse : NSObject

// An array of MKMapItems sorted by relevance in descending order
@property (nonatomic, readonly) NSArray<MKMapItem *> *mapItems;

@property (nonatomic, readonly) MKCoordinateRegion boundingRegion;

@end

NS_ASSUME_NONNULL_END
