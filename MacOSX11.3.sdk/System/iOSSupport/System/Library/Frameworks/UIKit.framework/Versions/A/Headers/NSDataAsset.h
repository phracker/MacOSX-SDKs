#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSDataAsset.h>)
//
//  NSDataAsset.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

#if !__NSDATAASSET_SHARED_SECTION__
#define __NSDATAASSET_SHARED_SECTION__ 1

typedef NSString * NSDataAssetName NS_SWIFT_BRIDGED_TYPEDEF API_AVAILABLE(ios(9.0), macos(10.11), tvos(9.0), watchos(2.0));

/// NSDataAsset represents the contents of data entries in your asset catalog.
/// Data assets are not in the same class of stored content as images, so you cannot use a data asset to get image data for an image.
UIKIT_EXTERN API_AVAILABLE(ios(9.0), macos(10.11), tvos(9.0), watchos(2.0)) @interface NSDataAsset : NSObject<NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/// Equivalent to -initWithName:name bundle:[NSBundle mainBundle];
- (nullable instancetype)initWithName:(NSDataAssetName)name;
/// Create a data asset with the given name from the given bundle. Returns nil if the asset was not found.
- (nullable instancetype)initWithName:(NSDataAssetName)name bundle:(NSBundle *)bundle NS_DESIGNATED_INITIALIZER;

/// The name used to reference the data asset
@property (nonatomic, readonly, copy) NSDataAssetName name;
/// The data for this asset, as stored in the asset catalog
@property (nonatomic, readonly, copy) NSData *data;
/// The Uniform Type Identifier for this data object.
@property (nonatomic, readonly, copy) NSString *typeIdentifier;

@end

#endif // __NSDATAASSET_SHARED_SECTION__

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/NSDataAsset.h>
#endif
