//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An LPLinkMetadata object contains metadata about a URL.
 */
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0))
@interface LPLinkMetadata : NSObject <NSCopying, NSSecureCoding>

/** The original URL that metadata was requested from. */
@property (nonatomic, retain, nullable) NSURL *originalURL;

/**
 The URL that metadata was retrieved from.
 This takes server-side redirects into account.
 */
@property (nonatomic, retain, nullable) NSURL *URL;

/**
 A title for the URL.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 An item provider which will return data corresponding to a representative
 icon for the URL.
 */
@property (nonatomic, retain, nullable) NSItemProvider *iconProvider;

/**
 An item provider which will return data corresponding to a representative
 image for the URL.
 */
@property (nonatomic, retain, nullable) NSItemProvider *imageProvider;

/**
 An item provider which will return data corresponding to a representative
 video for the URL that AVFoundation can play.
 */
@property (nonatomic, retain, nullable) NSItemProvider *videoProvider;

/**
 A remote URL corresponding to a representative video for the URL.

 This may point to to a remote video file that AVFoundation can stream,
 or to a YouTube video URL.
 */
@property (nonatomic, retain, nullable) NSURL *remoteVideoURL;

@end

NS_ASSUME_NONNULL_END
