//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that contains metadata about a URL.
///
/// Use ``LPLinkMetadata`` to store the metadata about a URL, including its
/// title, icon, images and video.
///
/// Fetch metadata using ``LPMetadataProvider``. For remote URLs, cache the
/// metadata locally to avoid the data and performance cost of fetching it from
/// the internet every time you present it. ``LPLinkMetadata`` is serializable
/// with
/// <doc://com.apple.documentation/documentation/foundation/nssecurecoding>.
///
/// For local file URLs, the
/// <doc://com.apple.documentation/documentation/quicklookthumbnailing> API
/// retrieves a representative thumbnail for the file, if possible.
///
/// ## Provide custom metadata
///
/// Say your app already has a database of links, with titles and images that
/// weren’t fetched by ``LPMetadataProvider``. You don’t have to fetch new
/// metadata from the internet in order to accelerate the share sheet or to
/// present a rich link. Instead, you can fill in the fields of
/// ``LPLinkMetadata`` yourself.
///
/// Create an ``LPLinkMetadata`` object, and fill in at least the
/// ``LPLinkMetadata/originalURL`` and ``LPLinkMetadata/URL`` fields, plus
/// whatever additional information you have.
///
/// ```swift
/// func activityViewControllerLinkMetadata(_: UIActivityViewController) -> LPLinkMetadata? {
///     let metadata = LPLinkMetadata()
///     metadata.originalURL = URL(string: "https://www.example.com/apple-pie")
///     metadata.url = metadata.originalURL
///     metadata.title = "The Greatest Apple Pie In The World"
///     metadata.imageProvider = NSItemProvider.init(contentsOf:
///         Bundle.main.url(forResource: "apple-pie", withExtension: "jpg"))
///     return metadata
/// }
/// ```
///
/// ## Accelerate the share sheet preview
///
/// For existing apps that share URLs, the share sheet automatically presents a
/// preview of the link. The preview first shows a placeholder link icon
/// alongside the base URL while fetching the link’s metadata over the network.
/// The preview updates once the link’s icon and title become available.
///
/// If you already have an ``LPLinkMetadata`` object for a URL, pass it to the
/// share sheet to present the preview instantly, without fetching data over the
/// network. In your implementation of
/// <doc://com.apple.documentation/documentation/uikit/uiactivityitemsource/3144571-activityviewcontrollerlinkmetada>,
/// return the metadata object.
///
/// ```swift
/// func activityViewControllerLinkMetadata(_:
/// UIActivityViewController) -> LPLinkMetadata? {
///     return self.metadata
/// }
/// ```
///
/// If the user chooses to share to Messages, the same metadata passes directly
/// through, providing a smooth and seamless experience with no unnecessary
/// loading.
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0))
@interface LPLinkMetadata : NSObject <NSCopying, NSSecureCoding>

/// The original URL of the metadata request.
@property (nonatomic, retain, nullable) NSURL *originalURL;

/// The URL that returned the metadata, taking server-side redirects into
/// account.
///
/// The URL that returns the metadata may differ from the
/// ``LPLinkMetadata/originalURL`` to which you sent the metadata request. This
/// can happen if the server redirects the request, for example, when a resource
/// has moved, or when the original URL is a domain alias.
@property (nonatomic, retain, nullable) NSURL *URL;

/// A representative title for the URL.
@property (nonatomic, copy, nullable) NSString *title;

/// An object that retrieves data corresponding to a representative icon for the
/// URL.
@property (nonatomic, retain, nullable) NSItemProvider *iconProvider;

/// An object that retrieves data corresponding to a representative image for
/// the URL.
@property (nonatomic, retain, nullable) NSItemProvider *imageProvider;

/// An object that retrieves data corresponding to a representative video for
/// the URL.
///
/// The item provider returns a video that
/// <doc://com.apple.documentation/documentation/avfoundation> can play.
@property (nonatomic, retain, nullable) NSItemProvider *videoProvider;

/// A remote URL corresponding to a representative video for the URL.
///
/// This may reference a remote video file that
/// <doc://com.apple.documentation/documentation/avfoundation> can stream,
/// or a YouTube video URL.
@property (nonatomic, retain, nullable) NSURL *remoteVideoURL;

@end

NS_ASSUME_NONNULL_END
