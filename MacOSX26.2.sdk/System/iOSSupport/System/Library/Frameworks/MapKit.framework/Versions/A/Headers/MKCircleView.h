//
//  MKCircleView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <MapKit/MKCircle.h>
#import <MapKit/MKOverlayPathView.h>

// Prefer MKCircleRenderer
API_DEPRECATED("Use MKCircleRenderer", ios(4.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@interface MKCircleView : MKOverlayPathView

- (instancetype)initWithCircle:(MKCircle *)circle NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) MKCircle *circle NS_DEPRECATED_IOS(4_0, 7_0);

@end

#endif // MK_SUPPORTS_VIEW_CLASSES
