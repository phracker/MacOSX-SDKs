#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImageAsset.h>)
//
//  UIImageAsset.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIImage.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UITraitCollection;
@protocol UIImageConfiguration;

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_SENDABLE
@interface UIImageAsset : NSObject <NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (UIImage *)imageWithConfiguration:(UIImageConfiguration *)configuration; // Images returned hold a strong reference to the asset that created them
- (void)registerImage:(UIImage *)image withConfiguration:(UIImageConfiguration *)configuration;
- (void)unregisterImageWithConfiguration:(UIImageConfiguration *)configuration; // removes only those images added with registerImage:withConfiguration:

- (UIImage *)imageWithTraitCollection:(UITraitCollection *)traitCollection; // Images returned hold a strong reference to the asset that created them
- (void)registerImage:(UIImage *)image withTraitCollection:(UITraitCollection *)traitCollection; // Adds a new variation to this image asset that is appropriate for the provided traits. Any traits not exposed by asset catalogs (such as forceTouchCapability) are ignored.
- (void)unregisterImageWithTraitCollection:(UITraitCollection *)traitCollection; // removes only those images added with registerImage:withTraitCollection:
@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIImageAsset.h>
#endif
