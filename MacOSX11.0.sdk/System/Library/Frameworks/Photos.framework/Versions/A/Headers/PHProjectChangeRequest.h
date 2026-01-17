//
//  PHProjectChangeRequest.h
//  Photos
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>

#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
@class UIImage;
#else
@class NSImage;
#endif
@class PHAsset;
@class PHProject;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

API_UNAVAILABLE_BEGIN(ios, tvos, macCatalyst)


// PHProjectChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHProjectChangeRequest : PHChangeRequest

- (instancetype)initWithProject:(PHProject *)project;

@property (nonatomic, copy, readwrite) NSString *title;

/**
 The projectExtensionData property is intended for storage of compressed, project specific data
 only. Do not include things like rasterized images that can be locally cached in this data. The
 total size of stored data is limited to 1 MB. Attempting to store more data than allowed will result
 in an error.
 */
@property (nonatomic, copy, readwrite) NSData *projectExtensionData;

/**
 Sets the key asset representing the project.
 Deprecated in macOS 10.14, please use -[PHProjectChangeRequest setProjectPreviewImage:] to provide a rendered preview instead.
 */
- (void)setKeyAsset:(nullable PHAsset *)keyAsset API_DEPRECATED_WITH_REPLACEMENT("-setProjectPreviewImage:", macos(10.13, 10.14)) API_UNAVAILABLE(ios, macCatalyst, tvos);

/**
 Use this method to update the project preview visible in Photos.
 Extensions are expected to set a project preview:
 - In or after -[id<PHProjectExtensionController> beginProjectWithExtensionContext:projectInfo:].
 - In or after -[id<PHProjectExtensionController> resumeProjectWithExtensionContext:projectInfo:]
 if -[PHProject hasProjectPreview] returns NO.
 - Whenever the project changes in a way that a new preview is needed.
 @param previewImage A rendered project preview, expected dimensions are 1024x1024.
 */
#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
- (void)setProjectPreviewImage:(UIImage *)previewImage;
#else
- (void)setProjectPreviewImage:(NSImage *)previewImage API_AVAILABLE(macos(10.14));
#endif

/**
 Removes the specified assets from the project.
 @param assets A collection of PHAsset objects to be removed from the project.
 */
- (void)removeAssets:(id<NSFastEnumeration>)assets API_AVAILABLE(macos(10.14)) NS_REFINED_FOR_SWIFT;

@end


API_UNAVAILABLE_END

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
