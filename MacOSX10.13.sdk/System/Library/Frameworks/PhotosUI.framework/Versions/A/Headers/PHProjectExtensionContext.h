//
//  PHProjectExtensionContext.h
//  PhotosUI
//
//  Copyright © 2017 Apple. All rights reserved.
//


#import <Foundation/NSExtensionContext.h>

@class PHPhotoLibrary;
@class PHProject;
@class PHFetchOptions;

NS_ASSUME_NONNULL_BEGIN

/**
 When a Photos project extension is initialized, it is handed a PHProjectExtensionContext object.
 This object provides the extension access to the underlying project as well as the photo library from which assets can be fetched.
 */
NS_CLASS_AVAILABLE_MAC(10_13)
@interface PHProjectExtensionContext : NSExtensionContext

@property (nonatomic, readonly) PHPhotoLibrary *photoLibrary;
@property (nonatomic, readonly) PHProject *project;

@end

NS_ASSUME_NONNULL_END
