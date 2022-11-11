//
//  MKGeoJSONSerialization.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MapKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@protocol MKGeoJSONObject <NSObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKGeoJSONDecoder : NSObject

- (NSArray<id<MKGeoJSONObject>> * _Nullable)geoJSONObjectsWithData:(NSData *)data error:(NSError ** _Nullable)errorPtr NS_SWIFT_NAME(decode(_:));

@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKGeoJSONFeature : NSObject <MKGeoJSONObject>

// If set, will be either a string or a number, depending on the original source data
@property (nonatomic, readonly, nullable) NSString *identifier;

// Serialized JSON
@property (nonatomic, readonly, nullable) NSData *properties;

@property (nonatomic, readonly) NSArray<__kindof MKShape<MKGeoJSONObject> *> *geometry;

@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKPointAnnotation (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPoint (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPolyline (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPolygon (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKPolyline (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKPolygon (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

NS_ASSUME_NONNULL_END
