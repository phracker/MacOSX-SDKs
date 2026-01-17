//
//  MKLookAroundSceneRequest.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <CoreLocation/CLLocation.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKLookAroundScene;
@class MKMapItem;

API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos)
@interface MKLookAroundSceneRequest : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithMapItem:(MKMapItem *)mapItem NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
@property (nonatomic, readonly, nullable) MKMapItem *mapItem;

@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

- (void)getSceneWithCompletionHandler:(NS_SWIFT_UI_ACTOR void (^)(MKLookAroundScene * _Nullable_result scene, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:scene());
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
