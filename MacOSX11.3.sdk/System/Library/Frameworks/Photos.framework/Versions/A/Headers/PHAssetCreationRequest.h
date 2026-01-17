//
//  PHAssetCreationRequest.h
//  PhotoKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#import <Photos/PHAssetChangeRequest.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

OS_EXPORT
@interface PHAssetResourceCreationOptions : NSObject <NSCopying>

// The filename for the resource. If not specified, one will be inferred from a fileURL if available, or else generated.
@property (nonatomic, copy, nullable) NSString *originalFilename;

// The uniform type identifier for the resource. If not specified, one will be inferred from the PHAssetResourceType.
@property (nonatomic, copy, nullable) NSString *uniformTypeIdentifier;

// When enabled, the file passed to the creation request will be moved into the photo library without duplicating the file data (the original file is removed if the asset is created successfully), otherwise a copy of the file is created from the original. Defaults to NO.  Attempting to move a file that is open or hardlinked will fail.
@property (nonatomic, assign) BOOL shouldMoveFile;

@end


// PHAssetCreationRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHAssetCreationRequest : PHAssetChangeRequest

+ (instancetype)creationRequestForAsset;

// Whether we support a given combination of PHAssetResourceTypes.
// Note: Adding resources to a creation request always succeeds; validation of the request is performed later, and any errors are reported after the performChanges block.
+ (BOOL)supportsAssetResourceTypes:(NSArray<NSNumber *> *)types;

- (void)addResourceWithType:(PHAssetResourceType)type fileURL:(NSURL *)fileURL options:(nullable PHAssetResourceCreationOptions *)options;

- (void)addResourceWithType:(PHAssetResourceType)type data:(NSData *)data options:(nullable PHAssetResourceCreationOptions *)options;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
