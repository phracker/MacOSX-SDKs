//
//  SHMediaItem.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NSString * SHMediaItemProperty NS_TYPED_EXTENSIBLE_ENUM;

/// The Shazam media ID
SH_EXPORT SHMediaItemProperty const SHMediaItemShazamID;

/// Title
SH_EXPORT SHMediaItemProperty const SHMediaItemTitle;

/// Subtitle
SH_EXPORT SHMediaItemProperty const SHMediaItemSubtitle;

/// Artist
SH_EXPORT SHMediaItemProperty const SHMediaItemArtist;

/// A web URL representing this result
SH_EXPORT SHMediaItemProperty const SHMediaItemWebURL;

/// The AppleMusic ID
SH_EXPORT SHMediaItemProperty const SHMediaItemAppleMusicID;

/// A link to this media on Apple Music
SH_EXPORT SHMediaItemProperty const SHMediaItemAppleMusicURL;

/// A URL to the artwork
SH_EXPORT SHMediaItemProperty const SHMediaItemArtworkURL;

/// A URL for a Video associated with the media
SH_EXPORT SHMediaItemProperty const SHMediaItemVideoURL;

/// Is this content explicit
SH_EXPORT SHMediaItemProperty const SHMediaItemExplicitContent;

/// An array of strings representing the genres of the media item
SH_EXPORT SHMediaItemProperty const SHMediaItemGenres;

/// The International Standard Recording Code
SH_EXPORT SHMediaItemProperty const SHMediaItemISRC;

/// @brief @c SHMediaItem represents metadata associated with a @c SHSignature
/// @discussion A @c SHMediaItem is used in two distinct ways
///        1. As the base class of a @c SHMatchedMedia item, and therefore as the result of a match
///     2. As a way of associating metadata with reference signatures in a @c SHCustomCatalog
///
/// A SHMediaItem contains no required fields and may be entirely blank, they can also contain custom data set with custom keys when making a @c SHCustomCatalog.
///
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMediaItem : NSObject <NSSecureCoding, NSCopying>

/// The Shazam Media ID
/// @note This may be fetched using the key @c SHMediaItemShazamID
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *shazamID;

/// The Title
/// @note This may be fetched using the key @c SHMediaItemTitle
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *title;

/// The Subtitle
/// @note This may be fetched using the key @c SHMediaItemSubtitle
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *subtitle;

/// The Artist
/// @note This may be fetched using the key @c SHMediaItemArtist
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *artist;

/// The Genre Names
/// @note This may be fetched using the key @c SHMediaItemGenres
/// @discussion An array of strings representing the genres of the media item. Will return an empty array if there are no genres.
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSArray<NSString *> *genres;

/// The Apple Music ID
/// @note This may be fetched using the key @c SHMediaItemAppleMusicID
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *appleMusicID;

/// The Apple Music URL
/// @note This may be fetched using the key @c SHMediaItemAppleMusicURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *appleMusicURL;

/// The Web URL
/// @discussion The URL will point to a page that displays the current object in its entirety
/// @note This may be fetched using the key @c SHMediaItemWebURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *webURL;

/// The Artwork URL
/// @note This may be fetched using the key @c SHMediaItemArtworkURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *artworkURL;

/// The VideoURL
/// @note This may be fetched using the key @c SHMediaItemVideoURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *videoURL;

/// @brief Whether this object represents explicit material
/// @note This may be fetched using the key @c SHMediaItemExplicitContent
@property (NS_NONATOMIC_IOSONLY, assign, readonly) BOOL explicitContent;

/// @brief The International Standard Recording Code
/// @note This may be fetched using the key @c SHMediaItemISRC
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *isrc;

/// Construct a new instance with the provided dictionary
/// @discussion You may add your own keys here to return custom data, custom data should conform to NSCoding
+ (instancetype)mediaItemWithProperties:(NSDictionary<SHMediaItemProperty, id> *)properties;

/// @brief Fetch a @c SHMediaItem by Shazam ID
/// @discussion The completionHandler will contain a @c SHMediaItem if the ShazamID is valid, otherwise nil and an error
+ (void)fetchMediaItemWithShazamID:(NSString *)shazamID completionHandler:(void (^)(SHMediaItem * __nullable mediaItem, NSError * __nullable error))completionHandler NS_SWIFT_NAME(fetch(shazamID:completionHandler:));

/// Retrieve a value using a known key
/// @param property The `SHMediaItemProperty` for a value
- (id)valueForProperty:(SHMediaItemProperty)property NS_SWIFT_UNAVAILABLE("Use subscripting in Swift");

/// Use subscripting to retrieve values
/// @param key The `SHMediaItemProperty` or custom key for a value
- (id)objectForKeyedSubscript:(SHMediaItemProperty)key;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
