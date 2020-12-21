//
//  MKLocalSearchRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

@class MKPointOfInterestFilter;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, MKLocalSearchResultType) {
    MKLocalSearchResultTypeAddress = 1 << 0,
    MKLocalSearchResultTypePointOfInterest = 1 << 1
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

NS_CLASS_AVAILABLE(10_9, 6_1) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKLocalSearchRequest : NSObject <NSCopying>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNaturalLanguageQuery:(NSString *)naturalLanguageQuery NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos);
- (instancetype)initWithNaturalLanguageQuery:(NSString *)naturalLanguageQuery region:(MKCoordinateRegion)region NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos);

@property (nonatomic, copy, nullable) NSString *naturalLanguageQuery;
@property (nonatomic, assign) MKCoordinateRegion region;

@property (nonatomic, assign) MKLocalSearchResultType resultTypes API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
