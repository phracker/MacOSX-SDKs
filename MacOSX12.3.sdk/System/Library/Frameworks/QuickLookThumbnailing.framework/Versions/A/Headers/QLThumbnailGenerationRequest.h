//
//  QLThumbnailGenerationRequest.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

@class QLThumbnailRepresentation;

typedef NS_OPTIONS (NSUInteger, QLThumbnailGenerationRequestRepresentationTypes) {
    QLThumbnailGenerationRequestRepresentationTypeIcon                      = 1 << 0,       // Request an icon, that is an image that represents the file type of the request. The size of an icon may not satisfy the parameters of the request (can be larger or smaller).
    QLThumbnailGenerationRequestRepresentationTypeLowQualityThumbnail       = 1 << 1,       // Request a thumbnail representing the file that may come from a previously generated and cached copy or faster lower quality generation, not satisfying the parameters of the request (can be larger or smaller).
    QLThumbnailGenerationRequestRepresentationTypeThumbnail                 = 1 << 2,       // Request a thumbnail representing the file, satisfying the parameters of the request (either retrieved from the cache, or generated).
    QLThumbnailGenerationRequestRepresentationTypeAll                       = NSUIntegerMax // Request all thumbnail representation types.
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(QLThumbnailGenerationRequest.RepresentationTypes);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos,tvos)
QLT_EXPORT NS_SWIFT_NAME(QLThumbnailGenerator.Request) @interface QLThumbnailGenerationRequest : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 @param url The url of the file on disk for which a thumbnail is requested.
 @param size The desired size of the thumbnails that should be generated.
 @param scale The desired scale of the thumbnails that should be generated. This will usually be the scale of the screen.
 You can for instance pass a scale different from the one of the screen if you would like to save generated thumbnails to a server to later download them on devices with a different screen scale.
 @param representationTypes The desired successive representations of the thumbnail that should be generated when possible.
 */
- (instancetype)initWithFileAtURL:(NSURL *)url
                             size:(CGSize)size
                            scale:(CGFloat)scale
              representationTypes:(QLThumbnailGenerationRequestRepresentationTypes)representationTypes;

/**
The content type of the file being thumbnailed is used to determine the provider of the thumbnail and the icon styles applied if iconMode is requested. By default the content type is derived from the file extension. Setting this property will override the derived content type. This is useful for files that don't have meaningful extensions but for which you may already know the content type. 
 */
@property (nonatomic, copy, null_resettable) UTType *contentType API_AVAILABLE(ios(14.0), macos(11.0));

/**
 Defaults to 0. If set, the thumbnail will have a width and height greater or equal to minimumDimension * scale.
 If set and it is not possible to generate thumbnails of minimumDimension for any of the requested QLThumbnailGenerationRequestRepresentationTypes, no thumbnail will be provided.
 */
@property (nonatomic, assign) CGFloat minimumDimension;

/**
 If set to YES, this will generate something appropriate for display as a file icon,
 meaning that the thumbnail might be embedded in a frame, show a curled corner, draw a background
 and/or a drop shadow, as appropriate for the platform.
 If set to NO, this will generate a raw undecorated thumbnail.
 Defaults to NO.
 */
@property (nonatomic, assign) BOOL iconMode;

@property (nonatomic, readonly) CGSize size;
@property (nonatomic, readonly) CGFloat scale;
@property (nonatomic, readonly) QLThumbnailGenerationRequestRepresentationTypes representationTypes;

@end

NS_ASSUME_NONNULL_END
