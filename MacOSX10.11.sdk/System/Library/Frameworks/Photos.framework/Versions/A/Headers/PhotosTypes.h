//
//  PhotosTypes.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

typedef NS_ENUM(NSInteger, PHAssetMediaType) {
	PHAssetMediaTypeUnknown = 0,
	PHAssetMediaTypeImage,
	PHAssetMediaTypeVideo,
	PHAssetMediaTypeAudio,
} NS_ENUM_AVAILABLE_MAC(10_11);

typedef NS_OPTIONS(NSUInteger, PHAssetMediaSubtype) {
    PHAssetMediaSubtypeNone               = 0,
    
    // Photo subtypes
    PHAssetMediaSubtypePhotoPanorama      = (1UL << 0),
    PHAssetMediaSubtypePhotoHDR           = (1UL << 1),
	PHAssetMediaSubtypePhotoScreenshot    = (1UL << 2),
    
    // Video subtypes
    PHAssetMediaSubtypeVideoStreamed      = (1UL << 16),
    PHAssetMediaSubtypeVideoHighFrameRate = (1UL << 17),
    PHAssetMediaSubtypeVideoTimelapse     = (1UL << 18),
} NS_ENUM_AVAILABLE_MAC(10_11);

