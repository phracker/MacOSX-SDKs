//
//  MKPointOfInterestFilter.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKPointOfInterestCategory.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKPointOfInterestFilter : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic, class, readonly) MKPointOfInterestFilter *filterIncludingAllCategories;
@property (nonatomic, class, readonly) MKPointOfInterestFilter *filterExcludingAllCategories;

- (instancetype)initIncludingCategories:(NSArray<MKPointOfInterestCategory> *)categories NS_DESIGNATED_INITIALIZER;
- (instancetype)initExcludingCategories:(NSArray<MKPointOfInterestCategory> *)categories NS_DESIGNATED_INITIALIZER;

- (BOOL)includesCategory:(MKPointOfInterestCategory)category;
- (BOOL)excludesCategory:(MKPointOfInterestCategory)category;

@end

NS_ASSUME_NONNULL_END
