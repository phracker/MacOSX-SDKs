#if !__has_include(<AVFCore/AVPlayerInterstitialEventController.h>)
/*
	File:  AVPlayerInterstitialEventController.h

	Framework:  AVFoundation
 
   Copyright:  2020 by Apple Inc., all rights reserved.

*/

#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerItem.h>

NS_ASSUME_NONNULL_BEGIN

/*!
  @enum         AVPlayerInterstitialEventRestrictions
  @abstract     These constants can be specified when creating AVPlayerInterstitialEvents in order to configure their behavior.
 
  @constant     AVPlayerInterstitialEventRestrictionNone
	Indicates that the user may freely employ playback controls, as available, both within the primary content and in the interstitial content specified for the event.
  @constant     AVPlayerInterstitialEventRestrictionConstrainsSeekingForwardInPrimaryContent
	Indicates that seeking within the primary content from a date prior to the date of the event to a date subsequent to the date of the event is not permitted.
  @constant     AVPlayerInterstitialEventRestrictionRequiresPlaybackAtPreferredRateForAdvancement
	Indicates that advancing the currentTime within an interstitial item, either by seeking ahead or by setting the playback rate to a value greater than the item's asset's preferredRate, is not permitted.
*/
typedef NS_OPTIONS(NSUInteger, AVPlayerInterstitialEventRestrictions) {
	AVPlayerInterstitialEventRestrictionNone = 0UL,
	AVPlayerInterstitialEventRestrictionConstrainsSeekingForwardInPrimaryContent = (1UL << 0),
	AVPlayerInterstitialEventRestrictionRequiresPlaybackAtPreferredRateForAdvancement = (1UL << 2),
	
	AVPlayerInterstitialEventRestrictionDefaultPolicy = AVPlayerInterstitialEventRestrictionNone
} NS_SWIFT_NAME(AVPlayerInterstitialEvent.Restrictions) API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));

/*!
  @class        AVPlayerInterstitialEvent

  @abstract
    An AVPlayerInterstitialEvent provides instructions for temporarily suspending the playback of primary content in order to play alternative interstitial content instead, resuming playback of the primary content when playback of the interstitial content is complete or is canceled.
    
  @discussion
    The primary content is specified as an instance of AVPlayerItem, designated as the primary item of the interstitial event.

    The timing of interstitial playback is specified as a date within the date range of the primary item. Interstitial events are currently possible only for items with an intrinsic mapping from their timeline to real-time dates.

    The alternative interstitial content is specified as an array of one or more AVPlayerItems that will be used as templates for the creation of items for interstitial playback. In other words, these template items are not the actual items that will be played during interstitial playback; instead they are used to generate the items that are to be played, with property values that match the configuration of your template items.

    If you wish to observe the scheduling and progress of interstitial events, use an AVPlayerInterstitialEventObserver. If you wish to specify your own schedule of interstitial events, use an AVPlayerInterstitialEventController.

*/
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5))
@interface AVPlayerInterstitialEvent : NSObject

AV_INIT_UNAVAILABLE
/*!
  @method       interstitialEventWithPrimaryItem:time:templateItems:restrictions:resumptionOffset:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in scheduling interstitial playback.
  @param        primaryItem
                An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
  @param        time
                The time within the duration of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @param        templateItems
                An array of AVPlayerItems with configurations that will be reproduced for the playback of interstitial content.
  @param        restrictions
                Indicates restrictions on the use of end user playback controls that are imposed by the event.
  @param        resumptionOffset
                Specifies the offset in time at which playback of the primary item should resume after interstitial playback has finished. Definite numeric values are supported. The value kCMTimeIndefinite can also be used, in order to specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback.
  @result       An instance of AVPlayerInterstitialEvent.
*/
+ (instancetype)interstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem time:(CMTime)time templateItems:(NSArray<AVPlayerItem *> *)templateItems restrictions:(AVPlayerInterstitialEventRestrictions)restrictions resumptionOffset:(CMTime)resumptionOffset;

+ (instancetype)playerInterstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem time:(CMTime)time interstitialTemplateItems:(NSArray<AVPlayerItem *> *)interstitialTemplateItems restrictions:(AVPlayerInterstitialEventRestrictions)restrictions resumptionOffset:(CMTime)resumptionOffset;// COMPATIBILITY SHIM - 72562501

/*!
  @method       interstitialEventWithPrimaryItem:date:templateItems:restrictions:resumptionOffset:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in scheduling interstitial playback.
  @param        primaryItem
                An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
  @param        date
                The date within the date range of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @param        templateItems
                An array of AVPlayerItems with configurations that will be reproduced for the playback of interstitial content.
  @param        restrictions
                Indicates restrictions on the use of end user playback controls that are imposed by the event.
  @param        resumptionOffset
                Specifies the offset in time at which playback of the primary item should resume after interstitial playback has finished. Definite numeric values are supported. The value kCMTimeIndefinite can also be used, in order to specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback.
  @result       An instance of AVPlayerInterstitialEvent.
*/
+ (instancetype)interstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem date:(NSDate *)date templateItems:(NSArray<AVPlayerItem *> *)templateItems restrictions:(AVPlayerInterstitialEventRestrictions)restrictions resumptionOffset:(CMTime)resumptionOffset;

+ (instancetype)playerInterstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem date:(NSDate *)date interstitialTemplateItems:(NSArray<AVPlayerItem *> *)interstitialTemplateItems restrictions:(AVPlayerInterstitialEventRestrictions)restrictions resumptionOffset:(CMTime)resumptionOffset;// COMPATIBILITY SHIM - 72562501

/*!
  @property     primaryItem
  @abstract     An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
*/
@property (nonatomic, readonly, weak) AVPlayerItem *primaryItem;

/*!
  @property     time
  @abstract     The time within the duration of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @discussion	Will have a value equal to kCMTimeInvalid if the event was initialized with a date instead of a time.
*/
@property (nonatomic, readonly) CMTime time;

/*!
  @property     date
  @abstract     The date within the date range of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @discussion	Will have a value of nil if the event was initialized with a time instead of a date.
*/
@property (nonatomic, readonly, nullable) NSDate *date;

/*!
  @property     templateItems
  @abstract     An array of AVPlayerItems with configurations that will be reproduced for the playback of interstitial content.
*/
@property (nonatomic, readonly) NSArray<AVPlayerItem *> *templateItems;
@property (nonatomic, readonly) NSArray<AVPlayerItem *> *interstitialTemplateItems;// COMPATIBILITY SHIM - 72562501

/*!
  @property     restrictions
  @abstract     Indicates restrictions on the use of end user playback controls that are imposed by the event.
*/
@property (nonatomic, readonly) AVPlayerInterstitialEventRestrictions restrictions;

/*!
  @property     resumptionOffset
  @abstract     Specifies the offset in time at which playback of the primary item should resume after interstitial playback has finished.
  @discussion
    Definite numeric values are supported. The value kCMTimeIndefinite can also be used, in order to specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback; this value is typically suitable for live broadcasts. The default value is kCMTimeZero.
*/
@property (nonatomic, readonly) CMTime resumptionOffset;

@end

/*!
  @class        AVPlayerInterstitialEventObserver

  @abstract
    An AVPlayerInterstitialEventObserver allows you to observe the scheduling and progress of interstitial events, specified either intrinsically within the content of primary items, such as via use of directives carried by HLS media playlists, or via use of an AVPlayerInterstitialEventController.
    
  @discussion
    The schedule of interstitial events is provided as an array of AVPlayerInterstitialEvents. For each AVPlayerInterstitialEvent, when the primary player's current item is the primary item of the interstitial event and its currentDate reaches the date of the event, playback of the primary item by the primary player is temporarily suspended, i.e. its timeControlStatus changes to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate and its reasonForWaitingToPlay will change to AVPlayerWaitingDuringInterstitialEventReason. During this suspension, playback of items that replicate the interstitial template items of the event are played by the interstitial player, which temporarily assumes the output configuration of the primary player; for example, its visual content will be routed to AVPlayerLayers that reference the primary player. Once the interstitial player has advanced through playback of the interstitial items specified by the event or its current item otherwise becomes nil, playback of the primary content will resume, at an offset from the time at which it was suspended as specified by the event.
  
*/
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5))
@interface AVPlayerInterstitialEventObserver : NSObject

/*!
  @method       interstitialEventObserverWithPrimaryPlayer:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in observing and scheduling interstitial playback.
  @param        primaryPlayer
                The AVPlayer that will play the primaryItems of the receiver's interstitial events.
  @result       An instance of AVPlayerInterstitialEventObserver.
*/
+ (instancetype)interstitialEventObserverWithPrimaryPlayer:(AVPlayer *)primaryPlayer;
+ (instancetype)playerInterstitialEventObserverWithPrimaryPlayer:(AVPlayer *)primaryPlayer;// COMPATIBILITY SHIM - 72562501

- (instancetype)initWithPrimaryPlayer:(AVPlayer *)primaryPlayer  NS_DESIGNATED_INITIALIZER;

/*!
  @property     primaryPlayer
  @abstract     The AVPlayer that will play the primaryItems of the receiver's interstitial events.
*/
@property (nonatomic, readonly, weak) AVPlayer *primaryPlayer;

/*!
  @property     interstitialPlayer
  @abstract     The AVQueuePlayer that will play interstitial items during suspension of playback of primary items.
*/
@property (nonatomic, readonly, weak) AVQueuePlayer *interstitialPlayer;

/*!
  @property     events
  @abstract     Provides the current schedule of interstitial events, specified either intrinsically within the content of primary items, such as via use of directives carried by HLS media playlists, or via use of an AVPlayerInterstitialEventController.
  @discussion
    When interstitial events follow a schedule specified intrinsically within the content of primary items, the value of this property will typically change whenever the currentItem of the primaryPlayer changes. For HLS content that specifies interstitials via the use of DATERANGE tags, the value of this property may also change whenever the set of DATERANGE tags in the currentItem's media playlist changes.
    When interstitial events follow a schedule specified via use of an AVPlayerInterstitialEventController, the value of this property changes only when a new schedule is set on the AVPlayerInterstitialEventController.
*/
@property (readonly) NSArray<AVPlayerInterstitialEvent *> *events;
@property (readonly) NSArray<AVPlayerInterstitialEvent *> *interstitialEvents;// COMPATIBILITY SHIM - 72562501

/*!
  @property     currentEvent
  @abstract     The current interstitial event. Has a value of nil during playback of primary content by the primary player.
*/
@property (readonly, nullable) AVPlayerInterstitialEvent *currentEvent;

@end

/*!
  @constant     AVPlayerInterstitialEventObserverEventsDidChangeNotification
  @abstract     A notification that's posted whenever the value of events of an AVPlayerInterstitialEventObserver is changed.
*/
AVF_EXPORT NSNotificationName const AVPlayerInterstitialEventObserverEventsDidChangeNotification API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));

/*!
  @constant     AVPlayerInterstitialEventObserverCurrentEventDidChangeNotification
  @abstract     A notification that's posted whenever the currentEvent of an AVPlayerInterstitialEventObserver changes.
*/
AVF_EXPORT NSNotificationName const AVPlayerInterstitialEventObserverCurrentEventDidChangeNotification API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));



/*!
  @class        AVPlayerInterstitialEventController

  @abstract
    An AVPlayerInterstitialEventController allows you to specify a schedule of interstitial events for items played by a primary player.
    By creating an instance of AVPlayerInterstitialEventController and setting a schedule of interstitial events, you pre-empt directives the are intrinsic to the items played by the primary player, if any exist, causing them to be ignored.
    
  @discussion
    The schedule of interstitial events is specified as an array of AVPlayerInterstitialEvents. For each AVPlayerInterstitialEvent, when the primary player's current item is the primary item of the interstitial event and its currentDate reaches the date of the event, playback of the primary item by the primary player is temporarily suspended, i.e. its timeControlStatus changes to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate and its reasonForWaitingToPlay will change to AVPlayerWaitingDuringInterstitialEventReason. During this suspension, playback of items that replicate the interstitial template items of the event are played by the interstitial player, which temporarily assumes the output configuration of the primary player; for example, its visual content will be routed to AVPlayerLayers that reference the primary player. Once the interstitial player has advanced through playback of the interstitial items specified by the event or its current item otherwise becomes nil, playback of the primary content will resume, at an offset from the time at which it was suspended as specified by the event.

*/
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5))
@interface AVPlayerInterstitialEventController : AVPlayerInterstitialEventObserver

/*!
  @method       interstitialEventControllerWithPrimaryPlayer
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in observing and scheduling interstitial playback.
  @param        primaryPlayer
                The AVPlayer that will play the primaryItems of the receiver's interstitial events.
  @result       An instance of AVPlayerInterstitialEventController.
*/
+ (instancetype)interstitialEventControllerWithPrimaryPlayer:(AVPlayer *)primaryPlayer;
+ (instancetype)playerInterstitialEventControllerWithPrimaryPlayer:(AVPlayer *)primaryPlayer;// COMPATIBILITY SHIM - 72562501

- (instancetype)initWithPrimaryPlayer:(AVPlayer *)primaryPlayer;

/*!
  @property     events
  @abstract     Specifies the current schedule of interstitial events.
  @discussion
    Setting this property to a non-nil value cancels and overrides all previously scheduled future interstitial events, including those that are intrinsically specified by the content of primary items, such as directives carried by HLS media playlists. Setting it to nil causes its value to be reset in accordance with the content of the current primary item.

    If you change the value of events during an interstitial event and the current event is not included in the new value of events, the current event is nevertheless allowed to continue until completion. If you wish to cancel the current event, use -cancelCurrentEventWithResumptionOffset:.

    If interstitial events are scheduled with dates that coincide either with the date of another scheduled interstitial event or with the date range of the primary content that's omitted according to the resumption offset of another scheduled interstitial event, the primary content will remain suspended until all coinciding interstitial events have been completed. The effective resumption offset will be the sum of the resumption offsets of the coinciding interstitial events. (Note that the sum of a numeric CMTime and kCMTimeIndefinite is kCMTimeIndefinite.)

    If interstitial events are scheduled for the same date, they are ordered according to their position in the events array.
*/
@property (copy, null_resettable) NSArray<AVPlayerInterstitialEvent *> *events;
@property (copy, null_resettable) NSArray<AVPlayerInterstitialEvent *> *interstitialEvents;// COMPATIBILITY SHIM - 72562501

/*!
  @method       cancelCurrentEventWithResumptionOffset:
  @abstract     Causes the playback of any and all interstitial content currently in progress to be abandoned and the playback of primary content to be resumed.
  @param        resumptionOffset
                Specifies the offset in time at which playback of the primary player's current item should resume after interstitial playback has finished. To specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback, pass a value of kCMTimeIndefinite.
  @discussion
    If invoked during the handling of coinciding interstitial events, they will all be canceled.           
    When you cancel interstitial events via the use of this method, the value of resumptionOffset that you pass overrides the events' resumptionOffset.
    Has no effect while currentEvent is nil.
*/
- (void)cancelCurrentEventWithResumptionOffset:(CMTime)resumptionOffset;

@end

@interface AVPlayer (AVPlayerInterstitialSupport)

/*!
 @constant AVPlayerWaitingDuringInterstitialEventReason
 @abstract Indicates that the player is waiting for the completion of an interstitial event.
 @discussion
    The player is waiting for playback because an interstitial event is currently in progress. Interstitial events can be monitored via use of an AVPlayerInterstitialEventObserver.
 */
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingDuringInterstitialEventReason API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));

@end

@interface AVPlayerItem (AVPlayerInterstitialSupport)

/*!
  @property     automaticallyHandlesInterstitialEvents
  @abstract     Allows interstitials to be played according to a schedule that's specified by server-side directives. The default value is YES. A value of NO prevents automatic scheduling of future server-side interstitial events. Events specified by an AVPlayerInterstitialEventController override server-side events, regardless of the value of this property.
*/
@property (nonatomic) BOOL automaticallyHandlesInterstitialEvents API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));

/*!
  @property     templatePlayerItem
  @abstract     If the item was created automatically according to a template item for looping, for interstitial playback, or for other purposes, indicates the AVPlayerItem that was used as the template.
*/
@property (nonatomic, readonly, nullable) AVPlayerItem *templatePlayerItem API_AVAILABLE(macos(11.4), ios(14.5), tvos(14.5));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerInterstitialEventController.h>
#endif
