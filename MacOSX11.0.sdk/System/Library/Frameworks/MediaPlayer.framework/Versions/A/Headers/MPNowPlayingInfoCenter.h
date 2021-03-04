//
//  MPNowPlayingInfoCenter.h
//  MediaPlayer
//
//  Copyright 2011 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// -----------------------------------------------------------------------------
// MPNowPlayingInfoCenter provides an interface for setting the current now 
// playing information for the application. This information will be displayed 
// wherever now playing information typically appears, such as the lock screen
// and app switcher. The now playing info dictionary contains a group of 
// metadata properties for a now playing item. The list of property constants
// is available in <MediaPlayer/MPMediaItem.h>. The properties which are 
// currently supported include:
// 
// MPMediaItemPropertyAlbumTitle
// MPMediaItemPropertyAlbumTrackCount
// MPMediaItemPropertyAlbumTrackNumber
// MPMediaItemPropertyArtist
// MPMediaItemPropertyArtwork
// MPMediaItemPropertyComposer
// MPMediaItemPropertyDiscCount
// MPMediaItemPropertyDiscNumber
// MPMediaItemPropertyGenre
// MPMediaItemPropertyPersistentID
// MPMediaItemPropertyPlaybackDuration
// MPMediaItemPropertyTitle
//
// In addition, metadata properties specific to the current playback session
// may also be specified -- see "Additional metadata properties" below.

typedef NS_ENUM(NSUInteger, MPNowPlayingInfoMediaType) {
    MPNowPlayingInfoMediaTypeNone = 0,
    MPNowPlayingInfoMediaTypeAudio,
    MPNowPlayingInfoMediaTypeVideo,
} MP_API(ios(10.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSUInteger, MPNowPlayingPlaybackState) {
    MPNowPlayingPlaybackStateUnknown = 0,
    MPNowPlayingPlaybackStatePlaying,
    MPNowPlayingPlaybackStatePaused,
    MPNowPlayingPlaybackStateStopped,
    MPNowPlayingPlaybackStateInterrupted
} MP_API(ios(11.0), tvos(11.0), macos(10.12.2), watchos(5.0));

MP_API(ios(5.0), tvos(5.0), macos(10.12.2), watchos(5.0))
@interface MPNowPlayingInfoCenter : NSObject

/// Returns the default now playing info center.
/// The default center holds now playing info about the current application.
+ (MPNowPlayingInfoCenter *)defaultCenter;

MP_INIT_UNAVAILABLE

/// The current now playing info for the center.
/// Setting the info to nil will clear it.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *nowPlayingInfo;

/// The current playback state of the app.
/// This only applies on macOS, where playback state cannot be determined by
/// the application's audio session. This property must be set every time
/// the app begins or halts playback, otherwise remote control functionality may
/// not work as expected.
@property (nonatomic) MPNowPlayingPlaybackState playbackState MP_API(macos(10.12.2), ios(13.0), macCatalyst(13.0));

@end

// -----------------------------------------------------------------------------
// Additional metadata properties

// The elapsed time of the now playing item, in seconds.
// Note the elapsed time will be automatically extrapolated from the previously 
// provided elapsed time and playback rate, so updating this property frequently
// is not required (or recommended.)
MP_EXTERN NSString * const MPNowPlayingInfoPropertyElapsedPlaybackTime MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (double)

// The playback rate of the now playing item, with 1.0 representing normal 
// playback. For example, 2.0 would represent playback at twice the normal rate.
// If not specified, assumed to be 1.0.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackRate MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (double)

// The "default" playback rate of the now playing item. You should set this
// property if your app is playing a media item at a rate other than 1.0 in a
// default playback state. e.g., if you are playing back content at a rate of
// 2.0 and your playback state is not fast-forwarding, then the default
// playback rate should also be 2.0. Conversely, if you are playing back content
// at a normal rate (1.0) but the user is fast-forwarding your content at a rate
// greater than 1.0, then the default playback rate should be set to 1.0.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyDefaultPlaybackRate MP_API(ios(8.0), macos(10.12.2), watchos(5.0)); // NSNumber (double)

// The index of the now playing item in the application's playback queue.
// Note that the queue uses zero-based indexing, so the index of the first item 
// would be 0 if the item should be displayed as "item 1 of 10".
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackQueueIndex MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// The total number of items in the application's playback queue.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackQueueCount MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// The chapter currently being played. Note that this is zero-based.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyChapterNumber MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// The total number of chapters in the now playing item.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyChapterCount MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// A boolean denoting whether the now playing item is a live stream.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyIsLiveStream MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSNumber (BOOL)

// A list of available language option groups in the now playing item
// Only one language option in a given group can be played at once.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyAvailableLanguageOptions MP_API(ios(9.0), macos(10.12.2), watchos(5.0)); // NSArrayRef of MPNowPlayingInfoLanguageOptionGroup

// A list of currently active language options in the now playing item.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyCurrentLanguageOptions MP_API(ios(9.0), macos(10.12.2), watchos(5.0)); // NSArray of MPNowPlayingInfoLanguageOption

// An identifier that represents the collection to which the now playing item belongs.
// This can refer to an artist, album, playlist, etc.
// This can be used to ask the now playing app to resume playback of the collection.
MP_EXTERN NSString * const MPNowPlayingInfoCollectionIdentifier MP_API(ios(9.3), macos(10.12.2), watchos(5.0)); // NSString

// An opaque identifier that uniquely represents the now playing item,
// even across app relaunches. This can be in any format and is only used to
// reference this item back to the now playing app.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyExternalContentIdentifier MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSString

// An optional opaque identifier that uniquely represents the profile that the
// now playing item is being played from, even across app relauches.
// This can be in any format and is only used to reference this profile back to
// the now playing app.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyExternalUserProfileIdentifier MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSString

// A unique string that identifies a service provider. If the now playing item
// belongs to a channel or subscription service, this key can be used to
// coordinate various types of now playing content from a particular service
// provider.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyServiceIdentifier MP_API(ios(11.0), macos(10.13), watchos(5.0)); // NSString

// Represents the current playback progress of the now playing item.
// 0.0 = not watched/listened/viewed, 1.0 = fully watched/listened/viewed
// This value is different that ElapsedPlaybackTime and does not need to be exact
// as it is used as a high level indicator as to how far along the user is.
// For example, a movie may wish to set the now playing item as fully watched
// when the credits begin to roll.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackProgress MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSNumber (float)

// Indicates the media type of the now playing item
// This can be used to determine what kind of user interface the system displays.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyMediaType MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSNumber (MPNowPlayingInfoMediaType)

// A URL pointing to the now playing item's underlying audio/video asset. This
// property is used by system UI when video thumbnails or audio waveform
// visualizations are applicable.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyAssetURL MP_API(ios(10.3), macos(10.12.3), watchos(5.0)); // NSURL

// Represents the real-time date associated with the current elapsed playback time.
// The value of an AVPlayerItem’s currentDate property can be used to populate this property (see AVFoundation framework.)
// Note the current playback date will be automatically extrapolated from the previously
// provided current playback date, so updating this property frequently is not required (nor recommended.)
// For example, a sports broadcast can map an elapsed playback time (i.e 12 minutes and 30 seconds) to a real-time date (i.e "10:30:00 9/14/2017")
MP_EXTERN NSString * const MPNowPlayingInfoPropertyCurrentPlaybackDate MP_API(ios(11.1), macos(10.13.1), watchos(5.0)); // NSDate

NS_ASSUME_NONNULL_END
