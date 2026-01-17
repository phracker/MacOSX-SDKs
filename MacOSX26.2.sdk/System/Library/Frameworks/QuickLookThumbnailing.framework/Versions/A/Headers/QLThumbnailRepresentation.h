//
//  QLThumbnailRepresentation.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>

@class UIImage;
@class NSImage;

typedef NS_ENUM (NSInteger, QLThumbnailRepresentationType) {
    QLThumbnailRepresentationTypeIcon = 0,                      // Icon of the file type of the thumbnail request, provided by the system, that may not satisfy the parameters of the request.
    QLThumbnailRepresentationTypeLowQualityThumbnail = 1,       // A version of the thumbnail that was retrieved from a cache or low quality generation but not satisfying the parameters of the request.
    QLThumbnailRepresentationTypeThumbnail = 2,                 // Final version of the thumbnail for the given request, satisfying the parameters of the request.
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(QLThumbnailRepresentation.RepresentationType);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)
QLT_EXPORT @interface QLThumbnailRepresentation : NSObject

@property (nonatomic, readonly) QLThumbnailRepresentationType type;

/// Returns the CGImage representation of the thumbnail.
@property (nonatomic, readonly) CGImageRef CGImage;

/// Returns the UIImage representation of the thumbnail. You need to explicitly link against UIKit to use this property.
@property (nonatomic, readonly, strong) UIImage *UIImage API_UNAVAILABLE(macos);

/// Returns the NSImage representation of the thumbnail. You need to explicitly link against AppKit to use this property.
@property (nonatomic, readonly, strong) NSImage *NSImage API_UNAVAILABLE(ios,tvos,watchos);

/// Returns the the effective rect within the thumbnail image representing the content of the document. In icon mode, this is the part of the image without all the image decorations.
@property (nonatomic, readonly) CGRect contentRect API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
