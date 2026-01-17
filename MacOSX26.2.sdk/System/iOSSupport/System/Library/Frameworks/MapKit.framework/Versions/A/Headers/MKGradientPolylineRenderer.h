//
//  MKMultiPolylineRenderer.h
//  MapKit
//
//  Copyright (c) 2020, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKPolylineRenderer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0)) API_UNAVAILABLE(watchos)
@interface MKGradientPolylineRenderer : MKPolylineRenderer

@property (nonatomic, copy, readonly) NSArray<NSNumber *> *locations NS_REFINED_FOR_SWIFT;

#if TARGET_OS_IPHONE
@property (nonatomic, copy, readonly) NSArray<UIColor *> *colors;
- (void)setColors:(NSArray<UIColor *> *)colors atLocations:(NSArray<NSNumber *> *)locations NS_REFINED_FOR_SWIFT;
#else
@property (nonatomic, copy, readonly) NSArray<NSColor *> *colors;
- (void)setColors:(NSArray<NSColor *> *)colors atLocations:(NSArray<NSNumber *> *)locations NS_REFINED_FOR_SWIFT;
#endif

@end

NS_ASSUME_NONNULL_END
