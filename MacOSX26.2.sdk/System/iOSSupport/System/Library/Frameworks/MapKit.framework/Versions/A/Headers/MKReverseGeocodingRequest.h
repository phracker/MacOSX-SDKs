//
//  MKReverseGeocodingRequest.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMapItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0), visionos(26.0), macos(26.0), tvos(26.0), watchos(26.0))
@interface MKReverseGeocodingRequest : NSObject

@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@property (nonatomic, readonly, copy) CLLocation *location;
@property (nonatomic, nullable, strong) NSLocale *preferredLocale;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithLocation:(CLLocation *)location;

- (void)getMapItemsWithCompletionHandler:(NS_SWIFT_UI_ACTOR void (^)(NSArray<MKMapItem *> * _Nullable mapItems, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:mapItems());
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
