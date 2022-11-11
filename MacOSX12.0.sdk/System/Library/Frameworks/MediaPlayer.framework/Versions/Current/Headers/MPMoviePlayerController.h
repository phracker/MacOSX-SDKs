//
//  MPMoviePlayerController.h
//  MediaPlayer
//
//  Copyright 2008-2015 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>

#if MP_HAS_HEADER(UIKit, UIView.h)

#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaPlayback.h>
#import <UIKit/UIKit.h>

#ifndef MP_DEPRECATED_BEGIN
#define MP_DEPRECATED_BEGIN(...)
#define MP_DEPRECATED_END
#endif
MP_DEPRECATED_BEGIN("Use AVPlayerViewController in AVKit", ios(3.2, 9.0))
MP_UNAVAILABLE_BEGIN(watchos, macos)

@class MPMovieAccessLog, MPMovieErrorLog;

// -----------------------------------------------------------------------------
// Types

typedef NS_ENUM(NSInteger, MPMovieScalingMode) {
    MPMovieScalingModeNone,       // No scaling
    MPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    MPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    MPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
} MP_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, MPMoviePlaybackState) {
    MPMoviePlaybackStateStopped,
    MPMoviePlaybackStatePlaying,
    MPMoviePlaybackStatePaused,
    MPMoviePlaybackStateInterrupted,
    MPMoviePlaybackStateSeekingForward,
    MPMoviePlaybackStateSeekingBackward
} MP_UNAVAILABLE(tvos);

typedef NS_OPTIONS(NSUInteger, MPMovieLoadState) {
    MPMovieLoadStateUnknown        = 0,
    MPMovieLoadStatePlayable       = 1 << 0,
    MPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    MPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
} MP_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, MPMovieRepeatMode) {
    MPMovieRepeatModeNone,
    MPMovieRepeatModeOne
} MP_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, MPMovieControlStyle) {
    MPMovieControlStyleNone,       // No controls
    MPMovieControlStyleEmbedded,   // Controls for an embedded view
    MPMovieControlStyleFullscreen, // Controls for fullscreen playback
    
    MPMovieControlStyleDefault = MPMovieControlStyleEmbedded
} MP_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, MPMovieFinishReason) {
    MPMovieFinishReasonPlaybackEnded,
    MPMovieFinishReasonPlaybackError,
    MPMovieFinishReasonUserExited
} MP_UNAVAILABLE(tvos);

// -----------------------------------------------------------------------------
// Movie Property Types

typedef NS_OPTIONS(NSUInteger, MPMovieMediaTypeMask) {
    MPMovieMediaTypeMaskNone  = 0,
    MPMovieMediaTypeMaskVideo = 1 << 0,
    MPMovieMediaTypeMaskAudio = 1 << 1
} MP_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, MPMovieSourceType) {
    MPMovieSourceTypeUnknown,
    MPMovieSourceTypeFile,     // Local or progressively downloaded network content
    MPMovieSourceTypeStreaming // Live or on-demand streaming content
} MP_UNAVAILABLE(tvos);

// -----------------------------------------------------------------------------
// Movie Player
// 
// See MPMediaPlayback.h for the playback methods.

MP_UNAVAILABLE(tvos)
@interface MPMoviePlayerController : NSObject <MPMediaPlayback>

- (instancetype)initWithContentURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSURL *contentURL;

// The view in which the media and playback controls are displayed.
@property (nonatomic, readonly) UIView *view;

// A view for customization which is always displayed behind movie content.
@property (nonatomic, readonly) UIView *backgroundView;

// Returns the current playback state of the movie player.
@property (nonatomic, readonly) MPMoviePlaybackState playbackState;

// Returns the network load state of the movie player.
@property (nonatomic, readonly) MPMovieLoadState loadState;

// The style of the playback controls. Defaults to MPMovieControlStyleDefault.
@property (nonatomic) MPMovieControlStyle controlStyle;

// Determines how the movie player repeats when reaching the end of playback. Defaults to MPMovieRepeatModeNone.
@property (nonatomic) MPMovieRepeatMode repeatMode;

// Indicates if a movie should automatically start playback when it is likely to finish uninterrupted based on e.g. network conditions. Defaults to YES.
@property (nonatomic) BOOL shouldAutoplay;

// Determines if the movie is presented in the entire screen (obscuring all other application content). Default is NO.
// Setting this property to YES before the movie player's view is visible will have no effect.
@property (nonatomic, getter=isFullscreen) BOOL fullscreen;
- (void)setFullscreen:(BOOL)fullscreen animated:(BOOL)animated;

// Determines how the content scales to fit the view. Defaults to MPMovieScalingModeAspectFit.
@property (nonatomic) MPMovieScalingMode scalingMode;

// Returns YES if the first video frame has been made ready for display for the current item.
// Will remain NO for items that do not have video tracks associated.
@property (nonatomic, readonly) BOOL readyForDisplay MP_API(ios(6.0));

// The types of media in the movie, or MPMovieMediaTypeNone if not known.
@property (nonatomic, readonly) MPMovieMediaTypeMask movieMediaTypes;

// The playback type of the movie. Defaults to MPMovieSourceTypeUnknown.
// Specifying a playback type before playing the movie can result in faster load times.
@property (nonatomic) MPMovieSourceType movieSourceType;

// The duration of the movie, or 0.0 if not known.
@property (nonatomic, readonly) NSTimeInterval duration;

// The currently playable duration of the movie, for progressively downloaded network content.
@property (nonatomic, readonly) NSTimeInterval playableDuration;

// The natural size of the movie, or CGSizeZero if not known/applicable.
@property (nonatomic, readonly) CGSize naturalSize;

// The start time of movie playback. Defaults to NaN, indicating the natural start time of the movie.
@property (nonatomic) NSTimeInterval initialPlaybackTime;

// The end time of movie playback. Defaults to NaN, which indicates natural end time of the movie.
@property (nonatomic) NSTimeInterval endPlaybackTime;

// Indicates whether the movie player allows AirPlay video playback. Defaults to YES on iOS 5.0 and later.
@property (nonatomic) BOOL allowsAirPlay;

// Indicates whether the movie player is currently playing video via AirPlay.
@property (nonatomic, readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive;

@end

// -----------------------------------------------------------------------------
// Movie Player Notifications

// Posted when the scaling mode changes.
MP_EXTERN NSString * const MPMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
MP_EXTERN NSString * const MPMoviePlayerPlaybackDidFinishNotification;

MP_EXTERN NSString * const MPMoviePlayerPlaybackDidFinishReasonUserInfoKey; // NSNumber (MPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN NSString * const MPMoviePlayerPlaybackStateDidChangeNotification;

// Posted when the network load state changes.
MP_EXTERN NSString * const MPMoviePlayerLoadStateDidChangeNotification;

// Posted when the currently playing movie changes.
MP_EXTERN NSString * const MPMoviePlayerNowPlayingMovieDidChangeNotification;

// Posted when the movie player enters or exits fullscreen mode.
MP_EXTERN NSString * const MPMoviePlayerWillEnterFullscreenNotification;
MP_EXTERN NSString * const MPMoviePlayerDidEnterFullscreenNotification;
MP_EXTERN NSString * const MPMoviePlayerWillExitFullscreenNotification;
MP_EXTERN NSString * const MPMoviePlayerDidExitFullscreenNotification;
MP_EXTERN NSString * const MPMoviePlayerFullscreenAnimationDurationUserInfoKey; // NSNumber of double (NSTimeInterval)
MP_EXTERN NSString * const MPMoviePlayerFullscreenAnimationCurveUserInfoKey;     // NSNumber of NSUInteger (UIViewAnimationCurve)

// Posted when the movie player begins or ends playing video via AirPlay.
MP_EXTERN NSString * const MPMoviePlayerIsAirPlayVideoActiveDidChangeNotification;

// Posted when the ready for display state changes.
MP_EXTERN NSString * const MPMoviePlayerReadyForDisplayDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(6.0, 9.0));

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
MP_EXTERN NSString * const MPMovieMediaTypesAvailableNotification;
MP_EXTERN NSString * const MPMovieSourceTypeAvailableNotification; // Posted if the movieSourceType is MPMovieSourceTypeUnknown when preparing for playback.
MP_EXTERN NSString * const MPMovieDurationAvailableNotification;
MP_EXTERN NSString * const MPMovieNaturalSizeAvailableNotification;

// -----------------------------------------------------------------------------
// Thumbnails

typedef NS_ENUM(NSInteger, MPMovieTimeOption) {
    MPMovieTimeOptionNearestKeyFrame,
    MPMovieTimeOptionExact
} MP_UNAVAILABLE(tvos);

MP_UNAVAILABLE(tvos)
@interface MPMoviePlayerController (MPMoviePlayerThumbnailGeneration)

// Returns a thumbnail at the given time.
// Deprecated.  Use -requestThumbnailImagesAtTimes:timeOption: / MPMoviePlayerThumbnailImageRequestDidFinishNotification instead.
- (UIImage *)thumbnailImageAtTime:(NSTimeInterval)playbackTime timeOption:(MPMovieTimeOption)option;

// Asynchronously request thumbnails for one or more times, provided as an array of NSNumbers (double).
// Posts MPMoviePlayerThumbnailImageRequestDidFinishNotification on completion.
- (void)requestThumbnailImagesAtTimes:(NSArray *)playbackTimes timeOption:(MPMovieTimeOption)option;

// Cancels all pending asynchronous thumbnail requests.
- (void)cancelAllThumbnailImageRequests;

@end

// Posted when each thumbnail image request is completed.
MP_EXTERN NSString * const MPMoviePlayerThumbnailImageRequestDidFinishNotification;
MP_EXTERN NSString * const MPMoviePlayerThumbnailImageKey; // UIImage, may be nil if an error occurred.
MP_EXTERN NSString * const MPMoviePlayerThumbnailTimeKey; // NSNumber (double)
MP_EXTERN NSString * const MPMoviePlayerThumbnailErrorKey; // NSError

// -----------------------------------------------------------------------------
// Timed Metadata

MP_UNAVAILABLE(tvos)
@interface MPMoviePlayerController (MPMoviePlayerTimedMetadataAdditions)

// Returns an array of the most recent MPTimedMetadata objects provided by the media stream.
@property (nonatomic, readonly) NSArray *timedMetadata MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(4.0, 9.0));

@end

MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0))
MP_UNAVAILABLE(tvos)
@interface MPTimedMetadata : NSObject

// A key which identifies a piece of timed metadata.
@property (nonatomic, readonly) NSString *key;

// The namespace of the identifying key.
@property (nonatomic, readonly) NSString *keyspace;

// The object value of the metadata.
@property (nonatomic, readonly) id value;

// The timestamp of the metadata, in the timebase of the media stream.
@property (nonatomic, readonly) NSTimeInterval timestamp;

// A dictionary containing all metadata information associated with this object, which may hold additional key-specific data (see below).
@property (nonatomic, readonly) NSDictionary *allMetadata;

@end

// Posted when new timed metadata arrives.
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataUpdatedNotification MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataUserInfoKey MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));       // NSDictionary of the most recent MPTimedMetadata objects.

// Additional dictionary keys for use with the 'allMetadata' property. All keys are optional.
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyName MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));           // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyInfo MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));           // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyMIMEType MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));       // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyDataType MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));       // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyLanguageCode MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0));   // NSString (ISO 639-2)

// -----------------------------------------------------------------------------

MP_UNAVAILABLE(tvos)
@interface MPMoviePlayerController (MPMovieLogging)

// Returns an object that represents a snapshot of the network access log. Can be nil.
@property (nonatomic, readonly) MPMovieAccessLog *accessLog MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0));

// Returns an object that represents a snapshot of the error log. Can be nil.
@property (nonatomic, readonly) MPMovieErrorLog *errorLog MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0));

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLog accumulates key metrics about network playback and presents them as a collection of MPMovieAccessLogEvent instances.
// Each MPMovieAccessLogEvent instance collates the data that relates to each uninterrupted period of playback.

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_UNAVAILABLE(tvos)
@interface MPMovieAccessLog : NSObject <NSCopying>

// Returns the webserver access log into a textual format that conforms to the W3C Extended Log File Format for web server log files.
// For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
@property (nonatomic, readonly) NSData *extendedLogData;

// Returns the string encoding of the extendedLogData property.
@property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

// An ordered collection of MPMovieAccessLogEvent instances that represent the chronological sequence of events contained in the access log.
@property (nonatomic, readonly) NSArray *events;

@end

// -----------------------------------------------------------------------------
// An MPMovieErrorLog provides data to identify if, and when, network resource playback failures occured.

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_UNAVAILABLE(tvos)
@interface MPMovieErrorLog : NSObject <NSCopying>

// Returns the webserver error log into a textual format that conforms to the W3C Extended Log File Format for web server log files.
// For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
@property (nonatomic, readonly) NSData *extendedLogData;

// Returns the string encoding of the extendedLogData property.
@property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

// An ordered collection of MPMovieErrorLogEvent instances that represent the chronological sequence of events contained in the error log.
@property (nonatomic, readonly) NSArray *events;

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLogEvent repesents a single access log entry.

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_UNAVAILABLE(tvos)
@interface MPMovieAccessLogEvent : NSObject <NSCopying>

// A count of media segments downloaded from the server to this client.
@property (nonatomic, readonly) NSUInteger numberOfSegmentsDownloaded;

// The date/time at which playback began for this event.
@property (nonatomic, readonly) NSDate *playbackStartDate;

// The URI of the playback item.
@property (nonatomic, readonly) NSString *URI;

// The IP address of the server that was the source of the last delivered media segment. Can be either an IPv4 or IPv6 address.
@property (nonatomic, readonly) NSString *serverAddress;

// A count of changes to the serverAddress property over the last uninterrupted period of playback.
@property (nonatomic, readonly) NSUInteger numberOfServerAddressChanges;

// A GUID that identifies the playback session. This value is used in HTTP requests.
@property (nonatomic, readonly) NSString *playbackSessionID;

// An offset into the playlist where the last uninterrupted period of playback began, in seconds. The value is negative if unknown.
@property (nonatomic, readonly) NSTimeInterval playbackStartOffset;

// The accumulated duration of the media downloaded, in seconds. The value is negative if unknown.
@property (nonatomic, readonly) NSTimeInterval segmentsDownloadedDuration;

// The accumulated duration of the media played, in seconds.
@property (nonatomic, readonly) NSTimeInterval durationWatched;

// The total number of playback stalls encountered. The value is negative if unknown.
@property (nonatomic, readonly) NSInteger numberOfStalls;

// The accumulated number of bytes transferred. The value is negative if unknown.
@property (nonatomic, readonly) int64_t numberOfBytesTransferred;

// The empirical throughput across all media downloaded, in bits per second.
@property (nonatomic, readonly) double observedBitrate;

// The throughput required to play the stream, as advertised by the server, in bits per second.
@property (nonatomic, readonly) double indicatedBitrate;

// The total number of dropped video frames.
@property (nonatomic, readonly) NSInteger numberOfDroppedVideoFrames;

@end

// -----------------------------------------------------------------------------
// An MPMovieErrorLogEvent repesents a single error log entry.

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_UNAVAILABLE(tvos)
@interface MPMovieErrorLogEvent : NSObject <NSCopying>

// The date and time when the error occured.
@property (nonatomic, readonly) NSDate *date;

// The URI of the playback item.
@property (nonatomic, readonly) NSString *URI;

// The IP address of the server that was the source of the error.
@property (nonatomic, readonly) NSString *serverAddress;

// A GUID that identifies the playback session. This value is used in HTTP requests.
@property (nonatomic, readonly) NSString *playbackSessionID;

// A unique error code identifier. The value is negative if unknown.
@property (nonatomic, readonly) NSInteger errorStatusCode;

// The domain of the error.
@property (nonatomic, readonly) NSString *errorDomain;

// A description of the error encountered.
@property (nonatomic, readonly) NSString *errorComment;

@end

// -----------------------------------------------------------------------------
// Deprecated methods and properties
// These will be removed in a future release of iOS
MP_UNAVAILABLE(tvos)
@interface MPMoviePlayerController (MPMoviePlayerDeprecated)

// Indicates if the movie player should inherit the application's audio session instead of creating a new session (which would interrupt the application's session).
// Defaults to YES. Setting this property during playback will not take effect until playback is stopped and started again.
@property (nonatomic) BOOL useApplicationAudioSession MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(6.0, 9.0));

@end

MP_DEPRECATED_END
MP_UNAVAILABLE_END

#endif
