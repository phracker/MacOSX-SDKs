//
//  MKMapFeatureAnnotation.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <MapKit/MKAnnotation.h>
#import <MapKit/MKIconStyle.h>
#import <MapKit/MKPointOfInterestCategory.h>

typedef NS_ENUM(NSInteger, MKMapFeatureType) {
    MKMapFeatureTypePointOfInterest = 0,
    MKMapFeatureTypeTerritory,
    MKMapFeatureTypePhysicalFeature,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MKMapFeatureAnnotation : NSObject <MKAnnotation>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) MKMapFeatureType featureType;
@property (nonatomic, readonly, nullable) MKIconStyle *iconStyle;
@property (nonatomic, readonly, nullable) MKPointOfInterestCategory pointOfInterestCategory;

@end

NS_ASSUME_NONNULL_END
