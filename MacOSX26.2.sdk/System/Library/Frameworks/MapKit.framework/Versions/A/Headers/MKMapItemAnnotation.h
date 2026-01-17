//
//  MKMapItemAnnotation.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#import <MapKit/MKAnnotation.h>
#import <MapKit/MKMapItem.h>

NS_ASSUME_NONNULL_BEGIN

// An annotation that represents a map item
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0), tvos(18.0))
API_UNAVAILABLE(watchos)
@interface MKMapItemAnnotation : NSObject <MKAnnotation>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// Creates a map item annotation
//
// If `mapItem` does not have valid `coordinate` data, the result will be `nil`.
//
// - Parameters:
//   - mapItem: the map item this annotation will represent
- (nullable instancetype)initWithMapItem:(MKMapItem *)mapItem NS_DESIGNATED_INITIALIZER;

// The map item represented by this annotation
@property (nonatomic, readonly, strong) MKMapItem *mapItem;
@end

NS_ASSUME_NONNULL_END
