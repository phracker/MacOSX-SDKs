//
//  PHPhotoLibrary+PhotosUISupport.h
//  PhotosUI
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Photos/Photos.h>

@class UIViewController;

API_AVAILABLE_BEGIN(ios(14))
API_UNAVAILABLE_BEGIN(macos, tvos, watchos)
NS_ASSUME_NONNULL_BEGIN

@interface PHPhotoLibrary (PhotosUISupport)

/**
 @abstract Prompt the user to update their limited library selection by presenting the limited library image picker when the user has opted into limited library access mode (see \c PHAuthorizationStatusLimited )
 @param controller The view controller that is used to present the limited library picker.
 @discussion Use this API when the user has enabled limited photo library access to present the limited library picker and give the user a way to update their selection. If the user has not enabled limited library access mode for this application, then this method will do nothing. This should be used when disabling the automatic limited library alert prompt (by adding \c PHPhotoLibraryPreventAutomaticLimitedAccessAlert = \c YES to the application's Info.plist).  
 
 Any changes applied to the limited library selection by the user will trigger a \c PHPhotoLibraryChangeObserver update that can be used to observe the changes to the selection.
 */
- (void)presentLimitedLibraryPickerFromViewController:(UIViewController *)controller;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END // (macos, tvos, watchos)
API_AVAILABLE_END // (ios(14))
