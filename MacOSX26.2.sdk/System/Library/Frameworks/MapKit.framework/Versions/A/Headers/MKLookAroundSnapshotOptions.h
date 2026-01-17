//
//  MKLookAroundSnapshotOptions.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

#if TARGET_OS_IPHONE
#import <UIKit/UITraitCollection.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class MKPointOfInterestFilter;

API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos)
@interface MKLookAroundSnapshotOptions : NSObject

@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter;
// The size of the image to create. Defaults to 256x256
@property (nonatomic, assign) CGSize size;
#if TARGET_OS_IPHONE
// Set traitCollection.displayScale to specify the scale factor to use when creating the image
@property (nonatomic, copy) UITraitCollection *traitCollection;
#endif

@end

NS_ASSUME_NONNULL_END
