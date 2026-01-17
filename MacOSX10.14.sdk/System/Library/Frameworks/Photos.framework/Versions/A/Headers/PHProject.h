//
//  PHProject.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Photos/PHCollection.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, NA)
@interface PHProject : PHAssetCollection

@property (nonatomic, readonly) NSData *projectExtensionData;

/**
 Property to determine if a project preview was previously set.
 Use -[PHProjectChangeRequest setProjectPreviewImage:] to set a project preview.
 */
@property (nonatomic, readonly) BOOL hasProjectPreview API_AVAILABLE(macos(10.14));

@end

NS_ASSUME_NONNULL_END
