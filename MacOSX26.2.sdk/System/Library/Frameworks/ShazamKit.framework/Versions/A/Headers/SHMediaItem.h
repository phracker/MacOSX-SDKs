//
//  SHMediaItem.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHRange.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants for the media item property names.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NSString * SHMediaItemProperty NS_TYPED_EXTENSIBLE_ENUM;

/// The Shazam media ID
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemShazamID;

/// Title
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemTitle;

/// Subtitle
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemSubtitle;

/// Artist
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemArtist;

/// A web URL representing this result
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemWebURL;

/// The AppleMusic ID
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemAppleMusicID;

/// A link to this media on Apple Music
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemAppleMusicURL;

/// A URL to the artwork
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemArtworkURL;

/// A URL for a Video associated with the media
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemVideoURL;

/// Is this content explicit
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemExplicitContent;

/// An array of strings representing the genres of the media item
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemGenres;

/// The International Standard Recording Code
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemISRC;

/// The key to access the time ranges property of a media item.
SH_EXPORT SHMediaItemProperty const SHMediaItemTimeRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// The key to access the frequency skew ranges property of a media item.
SH_EXPORT SHMediaItemProperty const SHMediaItemFrequencySkewRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// The date when the media item was created
SH_EXPORT SHMediaItemProperty const SHMediaItemCreationDate API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// An object that represents the metadata for a reference signature.
///
/// This class uses subscripting for the data elements of a custom media item that an existing property doesn't already represent.
///
/// Add a readable custom property by extending ``SHMediaItemProperty-struct``  with a key for that property, and by extending this class with a property that uses the key. The following code shows the extensions for an episode number:
///
/// ```swift
/// // Add an episode number to the list of properties.
/// extension SHMediaItemProperty {
///     static let episode = SHMediaItemProperty("Episode")
/// }
///
/// // Add a property for returning the episode number using a subscript.
/// extension SHMediaItem {
///     var episode: Int? {
///         return self[.episode] as? Int
///     }
/// }
/// ```
///
///
/// Add your custom property when you create the media item as the following code shows:
///
/// ```swift
/// // Create a new media item and set the title, subtitle, and episode properties.
/// let mediaItem = SHMediaItem(properties: [.episode: 42,
///                                          .title: "Question",
///                                          .subtitle: "The Answer"])
/// ```
///
///
/// > Note:
/// > The class of the object that represents a custom object must be one of: `Dictionary`, `Array`, `URL`, `Number`, `String`, `Date`, or `Data`.
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMediaItem : NSObject <NSSecureCoding, NSCopying>

/// The Shazam ID for the song.
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *shazamID;

/// A title for the media item.
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *title;

/// A subtitle for the media item.
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *subtitle;

/// The name of the artist for the media item, such as the performer of a song.
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *artist;

/// An array of genre names for the media item.
///
/// The array is empty if there are no media items.
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSArray<NSString *> *genres;

/// The Apple Music ID for the song.
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *appleMusicID;

/// A link to the Apple Music page that contains the full information for the song.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *appleMusicURL;

/// A link to the Shazam Music catalog page that contains the full information for the song.
///
/// This link opens the Shazam app or App Clip if it's available on the device.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *webURL;

/// The URL for artwork for the media item, such as an album cover.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *artworkURL;

/// The URL for a video for the media item, such as a music video.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *videoURL;

/// A Boolean value that indicates whether the media item contains explicit content.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) BOOL explicitContent;

/// The International Standard Recording Code (ISRC) for the media item.
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *isrc;

/// An array of ranges that indicate the offsets within the reference signature that this media item describes.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nonnull) NSArray<SHRange *> *timeRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// An array of ranges that indicate the frequency skews in the reference signature that this media item describes.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nonnull) NSArray<SHRange *> *frequencySkewRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// The date the media item was created.
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSDate *creationDate API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// Creates a media item object with a dictionary of properties and their associated values.
///
/// - Parameters:
///   - properties: A dictionary that contains the media item properties and their associated values.
+ (instancetype)mediaItemWithProperties:(NSDictionary<SHMediaItemProperty, id> *)properties NS_REFINED_FOR_SWIFT;

#if !0
/// Requests the media item for the song with the specified Shazam ID.
///
/// > Important:
/// > You can call this method from synchronous code using a completion handler, as shown on this page, or you can call it as an asynchronous method that has the following declaration:
/// >
/// > ```swift
/// > class func fetch(shazamID: String) async throws -> SHMediaItem
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// - Parameters:
///   - shazamID: The Shazam ID of the song.
///   - completionHandler: The completion handler that the system calls with the result of the request.
///
///     This block takes the following parameters:
///
///     - term `mediaItem`: A media item.
///     - term `error`: An error object if a problem occurs when fetching the media item; otherwise, `nil`.
///
+ (void)fetchMediaItemWithShazamID:(NSString *)shazamID completionHandler:(void (NS_SWIFT_SENDABLE ^)(SHMediaItem * __nullable mediaItem, NSError * __nullable error))completionHandler NS_SWIFT_NAME(fetch(shazamID:completionHandler:));
#endif

/// Accesses the property for the specified key for reading.
///
/// - Parameters:
///   - property: The key for the property.
///
/// - Returns: The value of the property; otherwise, `nil`.
- (id)valueForProperty:(SHMediaItemProperty)property NS_SWIFT_UNAVAILABLE("Use subscripting in Swift");

/// Accesses the property for the specified key for reading.
///
/// - Parameters:
///   - key: The key for the media item property.
///
/// - Returns: The value of the property; otherwise, `nil`.
- (id)objectForKeyedSubscript:(SHMediaItemProperty)key;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
