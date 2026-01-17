//
//  MKLookAroundSnapshot.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/NSImage.h>
#endif

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos)
@interface MKLookAroundSnapshot : NSObject

#if TARGET_OS_OSX
@property (nonatomic, readonly) NSImage *image;
#else
@property (nonatomic, readonly) UIImage *image;
#endif

@end

NS_ASSUME_NONNULL_END
