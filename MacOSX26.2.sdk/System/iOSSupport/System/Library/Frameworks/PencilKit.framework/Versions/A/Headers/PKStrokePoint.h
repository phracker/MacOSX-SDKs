//
//  PKStrokePoint.h
//  PencilKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A point value stores all the attributes of a PKStroke at a specific point.
/// `PKStrokePoint` stores its properties compressed, the value read for a property may not
/// exactly equal the value set for a property.
API_AVAILABLE(ios(14.0), macos(11.0))
NS_SWIFT_SENDABLE
@interface PKStrokePoint : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/// Create a new point with the provided properties.
- (instancetype)initWithLocation:(CGPoint)location timeOffset:(NSTimeInterval)timeOffset size:(CGSize)size opacity:(CGFloat)opacity force:(CGFloat)force azimuth:(CGFloat)azimuth altitude:(CGFloat)altitude NS_DESIGNATED_INITIALIZER;

/// Create a new point with the provided properties.
- (instancetype)initWithLocation:(CGPoint)location timeOffset:(NSTimeInterval)timeOffset size:(CGSize)size opacity:(CGFloat)opacity force:(CGFloat)force azimuth:(CGFloat)azimuth altitude:(CGFloat)altitude secondaryScale:(CGFloat)secondaryScale NS_DESIGNATED_INITIALIZER;

/// Create a new point with the provided properties.
- (instancetype)initWithLocation:(CGPoint)location timeOffset:(NSTimeInterval)timeOffset size:(CGSize)size opacity:(CGFloat)opacity force:(CGFloat)force azimuth:(CGFloat)azimuth altitude:(CGFloat)altitude secondaryScale:(CGFloat)secondaryScale threshold:(CGFloat)threshold NS_DESIGNATED_INITIALIZER;

/// Location of the point.
@property (nonatomic, readonly) CGPoint location;
/// Time offset since the start of the stroke path in seconds.
@property (nonatomic, readonly) NSTimeInterval timeOffset;
/// Size of the point.
@property (nonatomic, readonly) CGSize size;
/// Opacity of the point 0-2.
@property (nonatomic, readonly) CGFloat opacity;
/// Azimuth of the point in radians, 0.0-2π radians
@property (nonatomic, readonly) CGFloat azimuth;

/// Force used to create this point.
@property (nonatomic, readonly) CGFloat force;
/// Altitude used to create this point in radians, 0.0-π/2 radians
@property (nonatomic, readonly) CGFloat altitude;

/// The scaling of the point for secondary effects.
///
/// For example the scaling of the pigment in the watercolor ink.
@property (nonatomic, readonly) CGFloat secondaryScale API_AVAILABLE(ios(17.0), macos(14.0));

/// The threshold for clipping the stroke rendering.
///
/// When rendering only pixels with an alpha greater than the threshold are drawn. A threshold of 0 has no affect on rendering,
/// a threshold of 1 does not draw anything. Thresholds are only used for some inks, eg. `PKInkIdentifierReed`.
@property (nonatomic, readonly) CGFloat threshold API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0));

@end

NS_ASSUME_NONNULL_END
