//
//  MKLocalSearchRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKAddressFilter.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>

@class MKPointOfInterestFilter;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, MKLocalSearchResultType) {
    MKLocalSearchResultTypeAddress = 1 << 0,
    MKLocalSearchResultTypePointOfInterest = 1 << 1,
    MKLocalSearchResultTypePhysicalFeature API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0)) = 1 << 2
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

API_AVAILABLE(macos(10.9), ios(6.1), tvos(9.2), watchos(1.0))
@interface MKLocalSearchRequest : NSObject <NSCopying>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNaturalLanguageQuery:(NSString *)naturalLanguageQuery API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0));
- (instancetype)initWithNaturalLanguageQuery:(NSString *)naturalLanguageQuery region:(MKCoordinateRegion)region API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0));

@property (nonatomic, copy, nullable) NSString *naturalLanguageQuery;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKLocalSearchRegionPriority regionPriority API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));

@property (nonatomic, assign) MKLocalSearchResultType resultTypes API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
@property (nonatomic, copy, nullable) MKAddressFilter *addressFilter API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));

@end

NS_ASSUME_NONNULL_END
