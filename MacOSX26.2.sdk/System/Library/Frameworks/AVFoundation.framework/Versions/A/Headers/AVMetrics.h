#if !__has_include(<AVFCore/AVMetrics.h>)
/*
 File: AVMetrics.h
 
 Copyright (c) 2024. Apple Inc. All rights reserved.
 */
#ifndef AVMETRICS_H
#define AVMETRICS_H

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVContentKeySession.h>
#import <AVFoundation/AVAssetVariant.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMetricEvent;

/// This protocol needs to be implemented by interfaces intending to publish metric events to the event stream.
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@protocol AVMetricEventStreamPublisher
@end

/// This protocol needs to be implemented by the subscriber delegate to receive subscribed metric events.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@protocol AVMetricEventStreamSubscriber

/// Delegate callback to receive metric events.
/// 
/// - Parameter event: The metric event.
/// - Parameter publisher: The publisher which generated the current event.
- (void)publisher:(id<AVMetricEventStreamPublisher>)publisher didReceiveEvent:(AVMetricEvent *)event;
@end

/// AVMetricEventStream allows clients to add publishers and then subscribe to specific metric event classes from those publishers. Publishers are AVFoundation instances implementing AVMetricEventStreamPublisher. The interface allows clients to receive metric events via a subscriber delegate which implements AVMetricEventStreamSubscriber.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricEventStream : NSObject 

AV_INIT_UNAVAILABLE

/// Returns an autoreleased instance.
+ (instancetype)eventStream;

/// The publisher should be an AVFoundation instance conforming to AVMetricEventStreamPublisher.
- (BOOL)addPublisher:(id<AVMetricEventStreamPublisher>)publisher;

/// Set a subscriber delegate.
/// 
/// - Parameter subscriber: A subscriber delegate object conforming to AVMetricEventStreamSubscriber.
/// - Parameter queue: Dispatch queue for the delegate callbacks.
- (BOOL)setSubscriber:(id<AVMetricEventStreamSubscriber>)subscriber queue:(nullable dispatch_queue_t)queue;

/// Subscribe to a specific metric event class.
/// 
/// - Parameter metricEventClass: Type of metric event class to subscribe to.
- (void)subscribeToMetricEvent:(Class)metricEventClass;

/// Subscribe to set of metric event classes.
/// 
/// - Parameter metricEventClasses: Set of metric event classes to subscribe to.
- (void)subscribeToMetricEvents:(NSArray<Class> *)metricEventClasses;

/// Subscribe to all metric event classes.
- (void)subscribeToAllMetricEvents;

@end

#pragma mark - Base class -

/// An abstract base class representing metric events.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricEvent : NSObject <NSSecureCoding>
AV_INIT_UNAVAILABLE

/// Returns the date when the event occurred.
@property (readonly) NSDate *date;

/// Returns the time in the media timeline when the event occured.
@property (readonly) CMTime mediaTime;

/// A GUID that identifies the media session. If not available, value is nil.
@property (readonly, nullable) NSString *sessionID;

@end

#pragma mark - Error Event -

/// Represents a metric event when an error occurred.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricErrorEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns whether the error was recoverable.
@property (readonly) BOOL didRecover;

/// Returns the error encountered.
@property (readonly) NSError *error;
@end

#pragma mark - Resource Request Event -

/// Represents a metric event associated with media resource requests.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricMediaResourceRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the URL of the resource request. If no value is available, returns nil.
@property (readonly, nullable) NSURL *url;

/// The IP address of the server. If not available, the value is nil.
@property (readonly, nullable) NSString *serverAddress;

/// Returns the start time of the resource request.
@property (readonly) NSDate *requestStartTime;

/// Returns the end time of the resource request.
@property (readonly) NSDate *requestEndTime;

/// Returns the start time of the resource request response.
@property (readonly) NSDate *responseStartTime;

/// Returns the end time of the resource request response.
@property (readonly) NSDate *responseEndTime;

/// Returns the byte range downloaded for the resource request. If not available, the range start and end will be 0.
@property (readonly) NSRange byteRange;

/// Returns true if the resource was read from the cache.
@property (readonly, getter=wasReadFromCache) BOOL readFromCache;

/// Returns the error event, if any, encountered during the resource request. If no value is present, returns nil.
@property (readonly, nullable) AVMetricErrorEvent *errorEvent;

/// Returns the NSURLSessionTaskMetrics associated with the resource request. If no value is present, returns nil
@property (readonly, nullable) NSURLSessionTaskMetrics *networkTransactionMetrics;
@end

/// Represents a metric event associated with a HLS playlist resource request.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricHLSPlaylistRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the URL of the playlist. If no value is available, returns nil.
@property (readonly, nullable) NSURL *url;

/// Returns true if the playlist request is for a multivariant playlist.
@property (readonly) BOOL isMultivariantPlaylist;

/// Returns the media type. If the value cannot be determined, returns AVMediaTypeMuxed.
@property (readonly) AVMediaType mediaType;

/// Returns the media resource request event which was used to satisfy the playlist.
@property (readonly, nullable) AVMetricMediaResourceRequestEvent *mediaResourceRequestEvent;
@end

/// Represents a metric event associated with a HLS media segment resource request.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricHLSMediaSegmentRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the URL of the media segment. If no value is available, returns nil.
@property (readonly, nullable) NSURL *url;

/// Returns true if the media segment request is for a map segment.
@property (readonly) BOOL isMapSegment;

/// Returns the media type. If the value cannot be determined, returns AVMediaTypeMuxed.
@property (readonly) AVMediaType mediaType;

/// Returns the byte range for the media segment. If not available, the range start and end will be 0.
@property (readonly) NSRange byteRange;

/// Returns the URL of the index file in which this segment was declared. If not available, returns nil.
@property (readonly) NSURL *indexFileURL;

/// Returns the duration of segment in seconds.
@property (readonly) NSTimeInterval segmentDuration;

/// Returns the media resource request event which was used to satisfy the media segment.
@property (readonly, nullable) AVMetricMediaResourceRequestEvent *mediaResourceRequestEvent;
@end

/// Represents a metric event associated with a HLS content key resource request.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricContentKeyRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the content key specifier for the request.
@property (readonly) AVContentKeySpecifier *contentKeySpecifier;

/// Returns the media type. If the value cannot be determined, returns AVMediaTypeMuxed.
@property (readonly) AVMediaType mediaType;

/// Returns whether the content key resource request was initiated by the client.
@property (readonly) BOOL isClientInitiated;

/// Returns the media resource request event which was used to satisfy the content key.
@property (readonly, nullable) AVMetricMediaResourceRequestEvent *mediaResourceRequestEvent;
@end

#pragma mark - Likely To Keep Up Events -

/// Represents a metric event when playback was likely to play through without stalling.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemLikelyToKeepUpEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the variant selected at the time likely to keep up is achieved. If no value is present, returns nil.
@property (readonly, nullable) AVAssetVariant *variant;

/// Returns the total time taken to reach likely to keep up.
@property (readonly) NSTimeInterval timeTaken;

/// This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
/// 
/// Returns an NSArray of NSValues containing CMTimeRanges.
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;

@end

/// Represents a metric event when playback was first likely to play through without stalling.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemInitialLikelyToKeepUpEvent : AVMetricPlayerItemLikelyToKeepUpEvent
AV_INIT_UNAVAILABLE

/// Returns the playlist request events required to reach likely to keep up.
@property (readonly) NSArray <AVMetricHLSPlaylistRequestEvent *> *playlistRequestEvents;

/// Returns the media segment request events required to reach likely to keep up.
@property (readonly) NSArray <AVMetricHLSMediaSegmentRequestEvent *> *mediaSegmentRequestEvents;

/// Returns the content key request required to reach likely to keep up.
@property (readonly) NSArray <AVMetricContentKeyRequestEvent *> *contentKeyRequestEvents;

@end

#pragma mark - Rate Change Events -

/// Represents a metric event when playback rate change occurred.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemRateChangeEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the playback rate after the rate change event.
@property (readonly) double rate;

/// Returns the playback rate before the rate change event.
@property (readonly) double previousRate;

/// Returns the variant being played at the time of rate change. If no value is present, returns nil.
@property (readonly, nullable) AVAssetVariant *variant;

@end

/// Represents a metric event when playback stalled.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemStallEvent : AVMetricPlayerItemRateChangeEvent
AV_INIT_UNAVAILABLE

@end

/// Represents a metric event when playback seeked.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemSeekEvent : AVMetricPlayerItemRateChangeEvent
AV_INIT_UNAVAILABLE

@end

/// Represents a metric event when playback seek completed.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemSeekDidCompleteEvent : AVMetricPlayerItemRateChangeEvent
AV_INIT_UNAVAILABLE

/// Returns whether the seek was performed within the available buffer.
@property (readonly) BOOL didSeekInBuffer;

@end

#pragma mark - Variant Change Event -

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AVMetricMediaRendition : NSObject <NSSecureCoding>
AV_INIT_UNAVAILABLE

/*!
 @property stableID
 @abstract Provides ID corresponding to the rendition. This is equivalent to the
				STABLE-RENDITION-ID in the HLS playlist. If not available, value is nil.
 */
@property (readonly, nullable) NSString *stableID;

/*!
 @property URL
 @abstract Provides URL corresponding to the rendition's HLS playlist. If not available,
				value is nil.
 */
@property (readonly, nullable) NSURL *URL;
@end

/// Represents a metric event when variant switch was completed.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemVariantSwitchEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the variant before the switch. If no value is available, returns nil
@property (readonly, nullable) AVAssetVariant *fromVariant;

/// Returns the variant after the switch.
@property (readonly) AVAssetVariant *toVariant;

/// This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
/// 
/// Returns an NSArray of NSValues containing CMTimeRanges.
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;

/// Represents the currently selected video rendition's identifiers.
///
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
@property (readonly) AVMetricMediaRendition *videoRendition API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Represents the currently selected video rendition's identifiers.
///
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
@property (readonly) AVMetricMediaRendition *audioRendition API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Represents the currently selected audio rendition's identifiers.
///
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
@property (readonly) AVMetricMediaRendition *subtitleRendition API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Returns if the switch did succeed.
@property (readonly) BOOL didSucceed;
@end

#pragma mark - Variant Switch Start Event -

/// Represents a metric event when variant switch was attempted.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemVariantSwitchStartEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the variant from which the switch is attempted. If no value is available, returns nil
@property (readonly, nullable) AVAssetVariant *fromVariant;

/// Returns the variant to which the switch is attempted.
@property (readonly) AVAssetVariant *toVariant;

/// This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
/// 
/// Returns an NSArray of NSValues containing CMTimeRanges.
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;

/*!
 @property videoRendition
 @abstract Contains information corresponding to the currently selected video rendition.
 */
@property (readonly) AVMetricMediaRendition *videoRendition API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/*!
 @property audioRendition
 @abstract Contains information corresponding to the currently selected audio rendition.
 */
@property (readonly) AVMetricMediaRendition *audioRendition API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/*!
 @property subtitleRendition
 @abstract Contains information corresponding to the currently selected subtitle rendition.
 */
@property (readonly) AVMetricMediaRendition *subtitleRendition API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
@end

#pragma mark - Playback Summary Event -

/// Represents a summary metric event with aggregated metrics for the entire playback session.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemPlaybackSummaryEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the error event if any. If no value is available, returns nil.
@property (readonly, nullable) AVMetricErrorEvent *errorEvent;

/// Returns the total count of recoverable errors encountered during playback. If no errors were encountered, returns 0.
@property (readonly) NSInteger recoverableErrorCount;

/// Returns the total count of stalls encountered during playback. If no stalls were encountered, returns 0.
@property (readonly) NSInteger stallCount;

/// Returns the total count of variant switch encountered during playback.
@property (readonly) NSInteger variantSwitchCount;

/// Returns the total duration of playback in seconds.
@property (readonly) NSInteger playbackDuration;

/// Returns the total number of media requests performed by the player. This includes playlist requests, media segment requests, and content key requests.
@property (readonly) NSInteger mediaResourceRequestCount;

/// Returns the total time spent recovering from a stall event.
@property (readonly) NSTimeInterval timeSpentRecoveringFromStall;

/// Returns the total time spent in initial startup of playback.
@property (readonly) NSTimeInterval timeSpentInInitialStartup;

/// Returns the playtime weighted average bitrate played in bits / second.
@property (readonly) NSInteger timeWeightedAverageBitrate;

/// Returns the playtime weighted peak bitrate played in bits / second.
@property (readonly) NSInteger timeWeightedPeakBitrate;

@end

#pragma mark - Download Summary Event -

/// Represents a summary metric event with aggregated metrics for the entire download task.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricDownloadSummaryEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/// Returns the error event if any. If no value is available, returns nil.
@property (readonly, nullable) AVMetricErrorEvent *errorEvent;

/// Returns the total count of recoverable errors encountered during the download. If no errors were encountered, returns 0.
/// 
/// Error counts may not be consistent across OS versions. Comparisons should be made within a given OS version, as error reporting is subject to change with OS updates.
@property (readonly) NSInteger recoverableErrorCount;

/// Returns the total number of media requests performed by the download task. This includes playlist requests, media segment requests, and content key requests.
@property (readonly) NSInteger mediaResourceRequestCount;

/// Returns the total number of bytes downloaded by the download task.
@property (readonly) NSInteger bytesDownloadedCount;

/// Returns the total duration of the download in seconds.
@property (readonly) NSTimeInterval downloadDuration;

/// Returns the variants that were downloaded.
@property (readonly) NSArray<AVAssetVariant *> *variants;

@end

NS_ASSUME_NONNULL_END

#endif /* AVMETRICS_H */

#else
#import <AVFCore/AVMetrics.h>
#endif
