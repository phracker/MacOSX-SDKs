//
//  MKUserLocationView.h
//  MapKit
//
//  Copyright © 2019 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <MapKit/MKAnnotationView.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0)) API_UNAVAILABLE(watchos)
@interface MKUserLocationView : MKAnnotationView

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
