//
//  MKHybridMapConfiguration.h
//  MapKit
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <MapKit/MKMapConfiguration.h>
#import <MapKit/MKPointOfInterestFilter.h>

NS_ASSUME_NONNULL_BEGIN

MK_EXTERN
API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface MKHybridMapConfiguration : MKMapConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithElevationStyle:(MKMapElevationStyle)elevationStyle;

@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter;
@property (nonatomic) BOOL showsTraffic;

@end

NS_ASSUME_NONNULL_END
