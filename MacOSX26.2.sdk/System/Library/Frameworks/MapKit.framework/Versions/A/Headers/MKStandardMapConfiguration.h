//
//  MKStandardMapConfiguration.h
//  MapKit
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <MapKit/MKMapConfiguration.h>
#import <MapKit/MKPointOfInterestFilter.h>

API_AVAILABLE(ios(16.0), tvos(16.0), macos(13.0), watchos(9.0))
typedef NS_ENUM(NSInteger, MKStandardMapEmphasisStyle) {
    MKStandardMapEmphasisStyleDefault = 0,
    MKStandardMapEmphasisStyleMuted,
};

NS_ASSUME_NONNULL_BEGIN

MK_EXTERN
API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0), watchos(9.0))
@interface MKStandardMapConfiguration : MKMapConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithElevationStyle:(MKMapElevationStyle)elevationStyle;
- (instancetype)initWithElevationStyle:(MKMapElevationStyle)elevationStyle emphasisStyle:(MKStandardMapEmphasisStyle)emphasisStyle;
- (instancetype)initWithEmphasisStyle:(MKStandardMapEmphasisStyle)emphasisStyle;

@property (nonatomic) MKStandardMapEmphasisStyle emphasisStyle;
@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter;
@property (nonatomic) BOOL showsTraffic;

@end

NS_ASSUME_NONNULL_END


