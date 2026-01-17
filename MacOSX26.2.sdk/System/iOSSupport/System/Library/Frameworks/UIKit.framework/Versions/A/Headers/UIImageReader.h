#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImageReader.h>)
//
//  UIImageReader.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface UIImageReaderConfiguration : NSObject<NSCopying>

/// For image types that may decode as either SDR or HDR, prefer the HDR variant. Images that may only decode as either SDR or HDR are unaffected. Default depends on system capabilities.
@property (nonatomic, readwrite, assign) BOOL prefersHighDynamicRange;
/// If set, images vended by the loader are automatically prepared for display. Default is NO.
@property (nonatomic, readwrite, assign) BOOL preparesImagesForDisplay;
/// If set, images loaded will be thumbnails of approximately the given size. Default value is CGSizeZero, indicating that thumb-nailing is disabled. This size is always in pixels.
@property (nonatomic, readwrite, assign) CGSize preferredThumbnailSize;
/// If non-zero when generating images, image metadata information (if present) will be used to determine the scale to assign to the image. If zero all images will be assigned a scale of 1.0. Always assigns integral scales. Defaults to 0.
@property (nonatomic, readwrite, assign) CGFloat pixelsPerInch;

@end

@class UIImage;

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface UIImageReader : NSObject

/// Returns a reader that uses the default configuration options. This method is thread safe.
@property (class, readonly, strong) UIImageReader *defaultReader;

/// Returns a loader of the given configuration. Loaders are thread safe and sharable.
+ (instancetype)readerWithConfiguration:(UIImageReaderConfiguration *)configuration;

@property (nonatomic, readonly, copy) UIImageReaderConfiguration *configuration;

/// Synchronously generate an image from the given file URL. If an image could not be generated, returns nil.
- (UIImage *)imageWithContentsOfFileURL:(NSURL *)url;
/// Synchronously generate an image from the given data. If an image could not be generated, returns nil.
- (UIImage *)imageWithData:(NSData *)data;

/// Asynchronously generate an image from the given file URL. If an image could not be generated, the completion will be called with nil.
- (void)imageWithContentsOfFileURL:(NSURL *)url completion:(void (^)(UIImage *_Nullable))completion;
/// Asynchronously generate an image from the given data. If an image could not be generated, the completion will be called with nil.
- (void)imageWithData:(NSData *)data completion:(void (^)(UIImage *_Nullable))completion;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIImageReader.h>
#endif
