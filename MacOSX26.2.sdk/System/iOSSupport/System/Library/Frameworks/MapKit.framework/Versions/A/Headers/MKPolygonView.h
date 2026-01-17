//
//  MKPolygonView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <MapKit/MKPolygon.h>
#import <MapKit/MKOverlayPathView.h>

// Prefer MKPolygonRenderer
API_DEPRECATED("Use MKPolygonRenderer", ios(4.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@interface MKPolygonView : MKOverlayPathView

- (instancetype)initWithPolygon:(MKPolygon *)polygon NS_DEPRECATED_IOS(4_0, 7_0);
@property (nonatomic, readonly) MKPolygon *polygon NS_DEPRECATED_IOS(4_0, 7_0);

@end

#endif // MK_SUPPORTS_VIEW_CLASSES
