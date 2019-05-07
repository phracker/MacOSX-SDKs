//
//  MKLocalSearchRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 6_1) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKLocalSearchRequest : NSObject <NSCopying>

@property (nonatomic, copy, nullable) NSString *naturalLanguageQuery;
@property (nonatomic, assign) MKCoordinateRegion region;

@end

NS_ASSUME_NONNULL_END
