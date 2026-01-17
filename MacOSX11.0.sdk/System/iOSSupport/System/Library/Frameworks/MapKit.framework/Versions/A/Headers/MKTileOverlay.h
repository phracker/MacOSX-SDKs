//
//  MKTileOverlay.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlay.h>

NS_ASSUME_NONNULL_BEGIN

// MKTileOverlay represents a data source for raster image tiles in the spherical mercator projection (EPSG:3857).
NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKTileOverlay : NSObject <MKOverlay>

- (instancetype)initWithURLTemplate:(nullable NSString *)URLTemplate NS_DESIGNATED_INITIALIZER; // URL template is a string where the substrings "{x}", "{y}", "{z}", and "{scale}" are replaced with values from a tile path to create a URL to load. For example: http://server/path?x={x}&y={y}&z={z}&scale={scale}.

@property (atomic) CGSize tileSize; // default is 256x256

@property (atomic, getter=isGeometryFlipped) BOOL geometryFlipped; // Default is NO. If NO, a tile at x=0, y=0 is the upper left, otherwise it is in the lower left.

// The minimum/maximum zoom level at which tile data is available for this overlay. A tile at level 0 covers the entire world, at level 1 it covers 1/4th of the world, at level 2 it covers 1/16th of the world, and so on.
@property (atomic) NSInteger minimumZ;
@property (atomic) NSInteger maximumZ;

@property (atomic, readonly, nullable) NSString *URLTemplate;

@property (nonatomic) BOOL canReplaceMapContent;

@end

typedef struct {
    NSInteger x;
    NSInteger y;
    NSInteger z;
    CGFloat contentScaleFactor; // The screen scale that the tile will be shown on. Either 1.0 or 2.0.
} MKTileOverlayPath;

// Subclassers may override these methods to customize the loading behavior of MKTileOverlay
@interface MKTileOverlay (CustomLoading)

- (NSURL *)URLForTilePath:(MKTileOverlayPath)path; // default implementation fills out the URLTemplate

// Load the requested tile and call the callback block with the tile data or with an error if the tile could not be loaded. The default implementation first uses -URLForTilePath to get a URL and then it loads it asynchronously.
- (void)loadTileAtPath:(MKTileOverlayPath)path result:(void (^)(NSData * __nullable tileData, NSError * __nullable error))result;

@end

NS_ASSUME_NONNULL_END

