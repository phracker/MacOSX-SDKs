//
//  PHProjectChangeRequest.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PHProject;
@class PHAsset;
@class NSImage;
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, NA)
@interface PHProjectChangeRequest : NSObject

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
- (void)setKeyAsset:(PHAsset * _Nullable)keyAsset API_DEPRECATED_WITH_REPLACEMENT("-setProjectPreviewImage:", macos(10.13, 10.14));

/**
 Use this method to update the project preview visible in Photos.
 Extensions are expected to set a project preview:
    - In or after -[id<PHProjectExtensionController> beginProjectWithExtensionContext:projectInfo:].
    - In or after -[id<PHProjectExtensionController> resumeProjectWithExtensionContext:projectInfo:]
      if -[PHProject hasProjectPreview] returns NO.
    - Whenever the project changes in a way that a new preview is needed.
 @param previewImage A rendered project preview, expected dimensions are 1024x1024.
 */
- (void)setProjectPreviewImage:(NSImage *)previewImage API_AVAILABLE(macos(10.14));

/**
 Removes the specified assets from the project.
 @param assets A collection of PHAsset objects to be removed from the project.
 */
- (void)removeAssets:(id<NSFastEnumeration>)assets API_AVAILABLE(macos(10.14)) NS_REFINED_FOR_SWIFT;
@end

NS_ASSUME_NONNULL_END
