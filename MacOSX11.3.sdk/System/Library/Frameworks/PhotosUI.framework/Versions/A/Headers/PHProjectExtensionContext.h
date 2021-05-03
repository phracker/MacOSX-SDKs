//
//  PHProjectExtensionContext.h
//  PhotosUI
//
//  Copyright © 2017 Apple. All rights reserved.
//


#import <Foundation/NSExtensionContext.h>

@class PHAsset;
@class PHPhotoLibrary;
@class PHProject;
@class PHProjectInfo;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

/**
 When a Photos project extension is initialized, it is handed a PHProjectExtensionContext object.
 This object provides the extension access to the underlying project as well as the photo library from which assets can be fetched.
 */
OS_EXPORT
@interface PHProjectExtensionContext : NSExtensionContext

@property (nonatomic, readonly) PHPhotoLibrary *photoLibrary;
@property (nonatomic, readonly) PHProject *project;

/**
 Invokes the Photos Editor for the given asset.
 @param asset The asset to edit.
 @note The extension should observe library changes to get notified when assets are changed/edited.
 @see PHPhotoLibraryChangeObserver
 */
- (void)showEditorForAsset:(PHAsset *)asset API_AVAILABLE(macos(10.14));


/**
 Creates an updated PHProjectInfo from the given projectInfo and the current assets in the PHProject.
 If the existingProjectInfo is not nil the extension sections will be update to reflect any deletions from the
 photo library and a new section is appended for any assets in the project which weren't referenced in existingProjectInfo.
 @param existingProjectInfo PHProjectInfo to update.
                            If existingProjectInfo is nil a new PHProjectInfo will be created from all assets in the PHProject.
 @param completion          Completion block that is called with the update result.
                            updatedProjectInfo is the updated project info, if the update was cancelled it might be nil.
 @return NSProgress which can be observed, if it's canceled the original project info is returned.
 */
- (NSProgress *)updatedProjectInfoFromProjectInfo:(nullable PHProjectInfo *)existingProjectInfo
                                       completion:(void(^)(PHProjectInfo * _Nullable updatedProjectInfo))completion API_AVAILABLE(macos(10.14));

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
