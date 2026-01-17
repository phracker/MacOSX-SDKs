//
//  MKLocalSearchRequest.h
//  MapKit
//
//  Copyright (c) 2012-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

MK_CLASS_AVAILABLE(10_9, 6_1)
@interface MKLocalSearchRequest : NSObject <NSCopying>

@property (nonatomic, copy) NSString *naturalLanguageQuery;
@property (nonatomic, assign) MKCoordinateRegion region;

@end
