//
//  INPhotoAttributeOptions.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INPhotoAttributeOptions_h
#define INPhotoAttributeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INPhotoAttributeOptions) {
    INPhotoAttributeOptionPhoto = (1UL << 0),
    INPhotoAttributeOptionVideo = (1UL << 1),
    INPhotoAttributeOptionGIF = (1UL << 2),
    INPhotoAttributeOptionFlash = (1UL << 3),
    INPhotoAttributeOptionLandscapeOrientation = (1UL << 4),
    INPhotoAttributeOptionPortraitOrientation = (1UL << 5),
    INPhotoAttributeOptionFavorite = (1UL << 6),
    INPhotoAttributeOptionSelfie = (1UL << 7),
    INPhotoAttributeOptionFrontFacingCamera = (1UL << 8),
    INPhotoAttributeOptionScreenshot = (1UL << 9),
    INPhotoAttributeOptionBurstPhoto = (1UL << 10),
    INPhotoAttributeOptionHDRPhoto = (1UL << 11),
    INPhotoAttributeOptionSquarePhoto = (1UL << 12),
    INPhotoAttributeOptionPanoramaPhoto = (1UL << 13),
    INPhotoAttributeOptionTimeLapseVideo = (1UL << 14),
    INPhotoAttributeOptionSlowMotionVideo = (1UL << 15),
    INPhotoAttributeOptionNoirFilter = (1UL << 16),
    INPhotoAttributeOptionChromeFilter = (1UL << 17),
    INPhotoAttributeOptionInstantFilter = (1UL << 18),
    INPhotoAttributeOptionTonalFilter = (1UL << 19),
    INPhotoAttributeOptionTransferFilter = (1UL << 20),
    INPhotoAttributeOptionMonoFilter = (1UL << 21),
    INPhotoAttributeOptionFadeFilter = (1UL << 22),
    INPhotoAttributeOptionProcessFilter = (1UL << 23),
    INPhotoAttributeOptionPortraitPhoto API_AVAILABLE(ios(12.0), macos(10.14), watchos(5.0)) = (1UL << 24),
    INPhotoAttributeOptionLivePhoto API_AVAILABLE(ios(12.0), macos(10.14), watchos(5.0)) = (1UL << 25),
    INPhotoAttributeOptionLoopPhoto API_AVAILABLE(ios(12.0), macos(10.14), watchos(5.0)) = (1UL << 26),
    INPhotoAttributeOptionBouncePhoto API_AVAILABLE(ios(12.0), macos(10.14), watchos(5.0)) = (1UL << 27),
    INPhotoAttributeOptionLongExposurePhoto API_AVAILABLE(ios(12.0), macos(10.14), watchos(5.0)) = (1UL << 28),
} API_DEPRECATED("INPhotoAttributeOptions is deprecated. There is no replacement.", ios(10.0, 15.0), watchos(3.2, 8.0)) API_UNAVAILABLE(macos, tvos);

#endif // INPhotoAttributeOptions_h
