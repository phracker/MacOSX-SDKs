//
//  MKGeoJSONSerialization.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MapKit.h>

#import <MapKit/MKPointAnnotation.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKMultiPolyline.h>
#import <MapKit/MKMultiPolygon.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@protocol MKGeoJSONObject <NSObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKGeoJSONDecoder : NSObject

- (NSArray<id<MKGeoJSONObject>> * _Nullable)geoJSONObjectsWithData:(NSData *)data error:(NSError ** _Nullable)errorPtr NS_SWIFT_NAME(decode(_:));

@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKGeoJSONFeature : NSObject <MKGeoJSONObject>

// If set, will be either a string or a number, depending on the original source data
@property (nonatomic, readonly, nullable) NSString *identifier;

// Serialized JSON
@property (nonatomic, readonly, nullable) NSData *properties;

@property (nonatomic, readonly) NSArray<__kindof MKShape<MKGeoJSONObject> *> *geometry;

@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKPointAnnotation (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKMultiPoint (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKMultiPolyline (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKMultiPolygon (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKPolyline (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface MKPolygon (MKGeoJSONSerialization) <MKGeoJSONObject>
@end

NS_ASSUME_NONNULL_END
