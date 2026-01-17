//
//  MKMapItemRequest.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMapItemIdentifier.h>

NS_ASSUME_NONNULL_BEGIN

@class MKMapFeatureAnnotation;
@class MKMapItem;

API_AVAILABLE(ios(16.0), visionos(1.0), macos(15.0), tvos(18.0), watchos(11.0))
@interface MKMapItemRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithMapItemIdentifier:(MKMapItemIdentifier *)identifier NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));

- (instancetype)initWithMapFeatureAnnotation:(MKMapFeatureAnnotation *)mapFeatureAnnotation NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(16.0), visionos(1.0)) API_UNAVAILABLE(macos, tvos, watchos);

- (void)getMapItemWithCompletionHandler:(NS_SWIFT_UI_ACTOR void (^)(MKMapItem * _Nullable mapItem, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:mapItem());
- (void)cancel;

@property (nonatomic, nullable, readonly) MKMapItemIdentifier *mapItemIdentifier API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));

@property (nonatomic, nullable, readonly) MKMapFeatureAnnotation *mapFeatureAnnotation API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(macos, tvos, watchos);

@property (nonatomic, readonly) MKMapFeatureAnnotation *featureAnnotation API_DEPRECATED_WITH_REPLACEMENT("mapFeatureAnnotation", ios(16.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(macos, tvos, watchos);

@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end

NS_ASSUME_NONNULL_END
