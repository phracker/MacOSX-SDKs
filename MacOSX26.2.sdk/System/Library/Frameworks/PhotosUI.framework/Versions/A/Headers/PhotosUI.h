//
//  PhotosUI.h
//  PhotosUI
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#ifndef PhotosUI_PhotosUI_h
#define PhotosUI_PhotosUI_h

#import <TargetConditionals.h>

#if TARGET_OS_IOS || TARGET_OS_OSX || TARGET_OS_TV || TARGET_OS_VISION
#import <PhotosUI/PHLivePhotoView.h>
#endif

#if TARGET_OS_IOS || TARGET_OS_OSX || TARGET_OS_WATCH || TARGET_OS_VISION || TARGET_OS_TV
#import <PhotosUI/PHPicker.h>
#endif

#if TARGET_OS_IOS || TARGET_OS_OSX || TARGET_OS_VISION
#import <PhotosUI/PHContentEditingController.h>
#endif

#if TARGET_OS_IOS || TARGET_OS_VISION
#import <PhotosUI/PHPhotoLibrary+PhotosUISupport.h>
#endif

#if TARGET_OS_OSX
#import <PhotosUI/PhotosUITypes.h>
#import <PhotosUI/PHProjectExtensionContext.h>
#import <PhotosUI/PHProjectExtensionController.h>
#import <PhotosUI/PHProjectInfo.h>
#import <PhotosUI/PHProjectTypeDescription.h>
#import <PhotosUI/PHProjectTypeDescriptionDataSource.h>
#endif

#endif // PhotosUI_PhotosUI_h
