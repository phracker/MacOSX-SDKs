//
//  PHProject.h
//  Photos
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PHCollection.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

API_UNAVAILABLE_BEGIN(ios, tvos, macCatalyst)


OS_EXPORT
NS_SWIFT_SENDABLE
@interface PHProject : PHAssetCollection

@property (nonatomic, readonly) NSData *projectExtensionData;

/**
 Property to determine if a project preview was previously set.
 Use -[PHProjectChangeRequest setProjectPreviewImage:] to set a project preview.
 */
@property (nonatomic, readonly) BOOL hasProjectPreview;

@end


API_UNAVAILABLE_END

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
