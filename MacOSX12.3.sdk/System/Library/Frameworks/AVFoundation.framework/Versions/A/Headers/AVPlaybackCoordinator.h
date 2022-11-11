#if !__has_include(<AVFCore/AVPlaybackCoordinator.h>)
/*
	File: AVPlaybackCoordinator.h
	
	Framework: AVFoundation
	
	Copyright © 2020-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVPlayer.h>
#import <CoreMedia/CMTime.h>


NS_ASSUME_NONNULL_BEGIN

@class AVPlaybackCoordinator;
@class AVCoordinatedPlaybackParticipant;

#pragma mark AVPlaybackCoordinator

/**
	@typedef 	AVCoordinatedPlaybackSuspensionReason
	@abstract	Describes why an AVCoordinatedPlaybackParticipant is not currently available to participate in coordinated playback.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
typedef NSString *AVCoordinatedPlaybackSuspensionReason NS_TYPED_EXTENSIBLE_ENUM;

/**
	@constant	AVCoordinatedPlaybackSuspensionReasonAudioSessionInterrupted
	@abstract	The participant's audio session was interrupted.
 */
AVF_EXPORT AVCoordinatedPlaybackSuspensionReason const AVCoordinatedPlaybackSuspensionReasonAudioSessionInterrupted API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/**
	@constant	AVCoordinatedPlaybackSuspensionReasonStallRecovery
	@abstract	The player is buffering data after a stall.
 */
AVF_EXPORT AVCoordinatedPlaybackSuspensionReason const AVCoordinatedPlaybackSuspensionReasonStallRecovery API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/**
	@constant	AVCoordinatedPlaybackSuspensionReasonPlayingInterstitial
	@abstract	The participant is presented with interstitial content instead of the main player.
 */
AVF_EXPORT AVCoordinatedPlaybackSuspensionReason const AVCoordinatedPlaybackSuspensionReasonPlayingInterstitial API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/**
	@constant	AVCoordinatedPlaybackSuspensionReasonCoordinatedPlaybackNotPossible
	@abstract	The participant cannot participate in coordinated playback.
 */
AVF_EXPORT AVCoordinatedPlaybackSuspensionReason const AVCoordinatedPlaybackSuspensionReasonCoordinatedPlaybackNotPossible API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/**
	@constant	AVCoordinatedPlaybackSuspensionReasonUserActionRequired
	@abstract	The participant's playback object is in a state that requires manual intervention by the user to resume playback.
 */
AVF_EXPORT AVCoordinatedPlaybackSuspensionReason const AVCoordinatedPlaybackSuspensionReasonUserActionRequired API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/**
	@constant	AVCoordinatedPlaybackSuspensionReasonUserIsChangingCurrentTime
	@abstract	The participant is actively changing current time.
 */
AVF_EXPORT AVCoordinatedPlaybackSuspensionReason const AVCoordinatedPlaybackSuspensionReasonUserIsChangingCurrentTime API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/**
	@class		AVCoordinatedPlaybackSuspension
	@abstract	A representation of a temporary break in participation.
	@note		See AVPlaybackCoordinator's beginSuspensionForReason: method for details on use.
 */
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVCoordinatedPlaybackSuspension : NSObject

AV_INIT_UNAVAILABLE

/**
	@property	reason
	@abstract	The reason for the suspension. This will be communicated to other participants while coordination is suspended.
 */
@property (nonatomic, readonly) AVCoordinatedPlaybackSuspensionReason reason;

/**
	@property	beginDate
	@abstract	The begin time of the suspension.
 */
@property (nonatomic, readonly) NSDate *beginDate;

/**
	@method		end
	@abstract	Ends the suspension.
	@discussion If this is the last suspension, the coordinator will adjust timing of its playback object to match the group.
				Also see endProposingNewTime: for a way to end a suspension and simultaneously proposing a new time to the group.
*/
-(void)end;

/**
	@method		endProposingNewTime:
	@abstract	Ends the suspension and proposes a new time that everyone should seek to.
	@discussion If this is the last suspension, the coordinator will propose the new time to the group without changing the groups playback rate.
				If this is not the last suspension, the time will be ignored.
				If the time is not numeric, this will behave like a call to [suspension end].
*/
-(void)endProposingNewTime:(CMTime)time;

@end

/**
	@constant	AVPlaybackCoordinatorOtherParticipantsDidChangeNotification
	@abstract	Posted by the playback coordinator when its otherParticipants property changes.
 */
AVF_EXPORT NSNotificationName const AVPlaybackCoordinatorOtherParticipantsDidChangeNotification API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))  API_UNAVAILABLE(watchos);

/**
	@constant	AVPlaybackCoordinatorSuspensionReasonsDidChangeNotification
	@abstract	Posted by the playback coordinator when its suspensionReasons property changes.
 */
AVF_EXPORT NSNotificationName const AVPlaybackCoordinatorSuspensionReasonsDidChangeNotification API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))  API_UNAVAILABLE(watchos);


/**
	@class		AVPlaybackCoordinator
	@abstract	The playback coordinator negotiates playback state between a player, such as AVPlayer or a custom playback object represented by an implementation of the AVPlaybackCoordinatorPlaybackControlDelegate protocol, and a group of other connected players.
	@discussion	AVPlaybackCoordinator will match rate and time of all connected players. This means that a local rate change or seek will be reflected in all connected players. Equally, a rate change or seek in any of the connected players will be reflected locally.
				AVPlaybackCoordinator does not manage the items in the play queue of the connected players, so it is up to player's owner to share and match the play queue across participants.
				The coordinator does, however, keep track of the identity of items enqueued in each player. This means that for one player's current time and rate to be applied on another player, both players must be playing the same item. If two players are playing different items, they each have independent playback states. When one of the two players transitions to the other's item later, it will match the time and rate of that other player.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVPlaybackCoordinator : NSObject

AV_INIT_UNAVAILABLE

/**
	@property	otherParticipants
	@abstract	The playback states of the other participants in the group.
	@discussion	Use this property to create UI informing the local user about the state of other participants in the group.
	@note		The coordinator posts AVPlaybackCoordinatorOtherParticipantsDidChangeNotification when the contents of the array changes.
*/
@property (nonatomic, readonly) NSArray<AVCoordinatedPlaybackParticipant*> *otherParticipants;

/**
	@property	suspensionReasons
	@abstract	Describes why the coordinator is currently not able to participate in group playback.
	@discussion	If the list of reasons is non-empty, the coordinator will not react to any changes of group playback state.
*/
@property (nonatomic, readonly) NSArray<AVCoordinatedPlaybackSuspensionReason> *suspensionReasons;

/**
	@method		beginSuspensionForReason:
	@abstract	Informs the coordinator that its playback object is detached from the group for some reason and should not receive any playback commands from the coordinator.
	@discussion	Use this to tell the coordinator that its player cannot, or should not, participate in coordinated playback temporarily.
				The coordinator will not respond to playback commands coming from the group and it will also not send any commands to the group.
				To resume in group playback, end a suspension by calling one of the suspension's end methods.
	@note		See the description of AVPlaybackCoordinator subclasses for suspensions automatically begun on behalf of their playback objects, if any.
	@param		suspensionReason
					Indicates the reason for the suspension that is shared with other participants. Can be a system-defined reason (see AVCoordinatedPlaybackSuspensionReason*) or a custom string.
*/
- (AVCoordinatedPlaybackSuspension *)beginSuspensionForReason:(AVCoordinatedPlaybackSuspensionReason)suspensionReason;

/**
	@method 	expectedItemTimeAtHostTime:
	@abstract 	Returns the item time (for the current item) that the coordinator expects to be playing at a given host clock time.
	@discussion This method is useful to decide if it is appropriate to end a suspension, e.g. a suspension with AVCoordinatedPlaybackSuspensionReasonStallRecovery, while other participants are continuing playback.
*/
- (CMTime)expectedItemTimeAtHostTime:(CMTime)hostClockTime;

@end

/**
	@class		AVCoordinatedPlaybackParticipant
	@abstract	A participant in a coordinated playback group connected through AVPlaybackCoordinator.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVCoordinatedPlaybackParticipant : NSObject

/**
	@property	suspensionReasons
	@abstract	The reason, if any, this participant is currently not participating in coordinated playback.
*/
@property (nonatomic, readonly) NSArray<AVCoordinatedPlaybackSuspensionReason> *suspensionReasons;

/**
	@property	readyToPlay
	@abstract 	YES if the participant is ready to play.
*/
@property (nonatomic, readonly, getter=isReadyToPlay) BOOL readyToPlay;

/**
	@property	identifier
	@abstract	A unique id for the participant.
	@discussion	Use this identifier to distinguish participants.
*/
@property (nonatomic, readonly) NSUUID *identifier;

@end

/**
	@category	AVPlaybackCoordinator (AVCoordinatedPlaybackPolicies)
	@abstract	Policies used by AVPlaybackCoordinator to determine how to interact with the group.
*/
@interface AVPlaybackCoordinator (AVCoordinatedPlaybackPolicies)

/**
	@method		setParticipantLimit:forWaitingOutSuspensionsWithReason:
	@abstract	Sets the amount of participants that can join a group before the coordinator stops waiting for this particular suspension reason.
	@discussion	This allows additional configuration for suspension reasons in the suspensionReasonsThatTriggerWaiting array.
				When the coordinator decides whether one participant's suspensions should cause others to wait, it will also consider this limit of participants currently in the group.
*/
- (void)setParticipantLimit:(NSInteger)participantLimit forWaitingOutSuspensionsWithReason:(AVCoordinatedPlaybackSuspensionReason)reason;

/**
	@method		participantLimitForWaitingOutSuspensionsWithReason:
	@abstract	Returns the maximum number of participants that can be in a group before the coordinator stops waiting out this particular suspensions reason. Default value is NSIntegerMax.
*/
- (NSInteger)participantLimitForWaitingOutSuspensionsWithReason:(AVCoordinatedPlaybackSuspensionReason)reason;

/**
	@property	suspensionReasonsThatTriggerWaiting
	@abstract	If the coordinator decides to delay playback to wait for others, it will wait out these reasons, but not others.
*/
@property (nonatomic, copy) NSArray<AVCoordinatedPlaybackSuspensionReason> *suspensionReasonsThatTriggerWaiting;

/**
	@property	pauseSnapsToMediaTimeOfOriginator
	@abstract	Determines if participants should mirror the originator's stop time when pausing.
	@discussion	If YES, all participants will seek to the originator's stop time after they pause. Use this if it is desirable to counteract any network delay incurred by communicating the originator's pause to the other participants.
				If NO, it's acceptable for participants to stop at slightly different offsets and a pause will not cause other participants' time to jump back.
*/
@property (nonatomic, assign) BOOL pauseSnapsToMediaTimeOfOriginator;
 
@end

#pragma mark - AVPlayerPlaybackCoordinator

@protocol AVPlayerPlaybackCoordinatorDelegate;

/**
	@class		AVPlayerPlaybackCoordinator
	@abstract	An AVPlaybackCoordinator subclass for controlling an AVPlayer
	@discussion	While the coordinator is connected to other participants, it will intercept rate changes and seeks issued to the player to share these with other participants if appropriate.
				Clients of AVPlayer can thus use the AVPlayer interfaces to modify the playback state of connected participants. When appropriate, the coordinator will also impose rate changes and seeks from other participants on the player. If this occurs, the corresponding notifications will carry an originating participant in their payload.
				See AVPlayer's playbackCoordinator property for more details about player behavior changes.
				AVPlayerPlaybackCoordinator may begin suspensions on behalf of the player when the player's timeControlStatus changes from AVPlayerTimeControlStatusPlaying to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate or AVPlayerTimeControlStatusPaused. These suspensions will end when the player's timeControlStatus changes back to AVPlayerTimeControlStatusPlaying. This means that a suspension that begun because the player entered a waiting state, will end automatically when the player is done waiting. A suspension that begun because the player paused, will only end once the player's rate changes back to non-zero.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVPlayerPlaybackCoordinator : AVPlaybackCoordinator

AV_INIT_UNAVAILABLE

/**
	@property	player
	@abstract	The AVPlayer this coordinator is controlling.
*/
@property (nonatomic, readonly, weak) AVPlayer *player;

/**
	@property	delegate
	@abstract An object implementing the AVPlaybackCoordinatorDelegate protocol.
*/
@property (weak) id<AVPlayerPlaybackCoordinatorDelegate> delegate;

@end

/**
	@protocol	AVPlayerPlaybackCoordinatorDelegate
	@abstract	Delegate protocol for AVPlayerPlaybackCoordinator.
 */
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@protocol AVPlayerPlaybackCoordinatorDelegate <NSObject>

@optional
/**
	@method		playbackCoordinator:identifierForPlayerItem:
	@abstract	Called by the coordinator to identify AVPlayerItems played by the coordinator's AVPlayer.
	@discussion	Implementing this method allows the coordinator to establish identity of two items created from different URLs, e.g., because one participant is using a local cache and the other a remote URL.
				If the method is not implemented, the coordinator will derive the identifier from the item's asset.
*/
-(NSString *)playbackCoordinator:(AVPlayerPlaybackCoordinator *)coordinator identifierForPlayerItem:(AVPlayerItem *)playerItem;

/**
	@method		playbackCoordinator:interstitialTimeRangesForPlayerItem:
	@abstract	Called by the coordinator to obtain time ranges in the AVPlayerItem that do not correspond to the primary content.
	@discussion	Implement this method to provide the coordinator a list of sample accurate time ranges that represent interstitials in the player item.
				The coordinator would use this along with the waiting policy for the playingInterstitial suspension to coordinate playback across the group.
				If the playingInterstitial suspension is part of AVPlaybackCoordinator.suspensionReasonsThatTriggerWaiting, then the coordinator would wait for other participants to complete the interstitial before proceeding with playback.
				And if the playingInterstitial suspension is not a part of AVPlaybackCoordinator.suspensionReasonsThatTriggerWaiting then the coordinator will not wait for the participant playing the interstitial.
				Instead, that participant would jump to catch up with the rest of the group when they finish playing the interstitial.
				This delegate method is expected to return an array of NSValues with each value containing a CMTimeRange that represents the interstitial.
				If the method is not implemented, the coordinator would assume that the entire item corresponds to the primary content.
*/
-(NSArray<NSValue *> *)playbackCoordinator:(AVPlayerPlaybackCoordinator *)coordinator interstitialTimeRangesForPlayerItem:(AVPlayerItem *)playerItem API_AVAILABLE(macos(12.3), ios(15.4), tvos(15.4)) API_UNAVAILABLE(watchos);

@end


#pragma mark - AVDelegatingPlaybackCoordinator

@protocol AVPlaybackCoordinatorPlaybackControlDelegate;

/**
	@enum		AVDelegatingPlaybackCoordinatorRateChangeOptions
	@abstract	Configuration for a call to [AVDelegatingPlaybackCoordinator coordinateRateChangeToRate:options:].
	
	@constant	AVDelegatingPlaybackCoordinatorRateChangeOptionPlayImmediately
					Requests that the coordinator begin playback as soon as possible and ignore other participant's readiness and suspensions.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
typedef NS_OPTIONS(NSUInteger, AVDelegatingPlaybackCoordinatorRateChangeOptions) {
	AVDelegatingPlaybackCoordinatorRateChangeOptionPlayImmediately = (1UL << 0),
};

/**
	@enum		AVDelegatingPlaybackCoordinatorSeekOptions
	@abstract	Configuration for a call to [AVDelegatingPlaybackCoordinator coordinateSeekToTime:options:].
	
	@constant	AVDelegatingPlaybackCoordinatorSeekOptionResumeImmediately
					Requests that the coordinator resume playback as soon as possible after the seek is complete and ignore other participant's readiness and suspensions.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
typedef NS_OPTIONS(NSUInteger, AVDelegatingPlaybackCoordinatorSeekOptions) {
	AVDelegatingPlaybackCoordinatorSeekOptionResumeImmediately = (1UL << 0),
};

/**
	@class		AVDelegatingPlaybackCoordinator
	@abstract	An AVPlaybackCoordinator subclass for controlling a custom playback object.
	@note		Use AVPlayer's playbackCoordinator property to get an AVPlaybackCoordinator for an AVPlayer.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVDelegatingPlaybackCoordinator : AVPlaybackCoordinator

/**
	@method		initWithPlaybackControlDelegate:
	@abstract	Creates an AVPlaybackCoordinator for a custom playback object.
	@discussion	Use this to create an AVPlaybackCoordinator when playback is not driven by an AVPlayer.
	@param		playbackControlDelegate
					An object conforming to the AVPlaybackCoordinatorPlaybackControlDelegate protocol representing a custom playback object.
					The coordinator will only hold a weak reference to its delegate.
	@note		See AVPlayer's playbackCoordinator property to get an AVPlaybackCoordinator for an AVPlayer.
*/
-(instancetype)initWithPlaybackControlDelegate:(id<AVPlaybackCoordinatorPlaybackControlDelegate>)playbackControlDelegate;

/**
	@property	playbackControlDelegate
	@abstract	The custom player implementation controlled by the coordinator.
*/
@property (nonatomic, readonly, weak) id<AVPlaybackCoordinatorPlaybackControlDelegate> playbackControlDelegate;


/**
	@method 	coordinateRateChangeToRate:options:
	@abstract 	Coordinaties a rate change across the group of connected participants, waiting for other participants to become ready if necessary.
	@discussion	The coordinator will request a coordinated rate change from all other connected participants.
				When changing the rate from zero to non-zero, it may also wait out other participant's suspensions as configured by the suspensionReasonsThatTriggerWaiting property.
				
				This method should not be called when the rate change should not affect the group, or the group should not have control over local playback temporarily, e.g. a pause because of an audio session interruption.
				In those cases, the coordinator should be informed by beginning a suspension with the appropriate reason instead. If other participants pause is dependent on the coordinator's configuration.
				The suspension will stop the coordinator from issuing further commands to its playbackControlDelegate. After beginning the suspension, the playback object can be reconfigured as necessary.
	@note		Calling this method while the coordinator is suspended affects only the local playback object. The group state will not be affected, even after the suspension ends.
	@param		rate
					The playback rate the group should be using.
	@param		options
					Additional configuration of the rate change. For details see AVDelegatingPlaybackCoordinatorRateChangeOptions.
*/
-(void)coordinateRateChangeToRate:(float)rate options:(AVDelegatingPlaybackCoordinatorRateChangeOptions)options;


/**
	@method 	coordinateSeekToTime:
	@abstract 	Triggers a seek to the requested time for all connected participants.
	@discussion	For behavior around resuming playback after the seek is complete and suspensions, see the discussion of coordinateRateChangeToRate:options.
	@note		Calling this method while the coordinator is suspended affects only the local playback object. The group state will not be affected, even after the suspension ends.
				To end a suspension and also affect the group timing see -[AVCoordinatedPlaybackSuspension endProposingNewTime:]
	@param		time
					The time the group should seek to when the command ends.
	@param		options
					Additional configuration of the seek. For details see AVDelegatingPlaybackCoordinatorSeekOptions.
*/
-(void)coordinateSeekToTime:(CMTime)time options:(AVDelegatingPlaybackCoordinatorSeekOptions)options;

/**
	@method 	transitionToItemWithIdentifier:proposingInitialTimingBasedOnTimebase:
	@abstract 	Informs the coordinator to transition to a new current item.
	@discussion	The coordinator will stop sending commands for any previous item identifier and begin sending commands for the new identifier.
				The proposed timing will either be used as the new referece timing for the group, or it will be compared to an already existing reference timing.
				If the proposed timing doesn't match such an existing reference timing, the coordinator will use the playbackControlDelegate to issue appropriate commands to match up the timing.
	@note 		This is not a way to affect the play queue of other participants. All other participants must do this independently, e.g. as a side-effect of an automatic item transition or an out-of-band communication requesting a similar item change.
	@param		itemIdentifier
					The identifier for the new current item. May be nil if nothing is playing.
	@param		snapshotTimebase
					A timebase used to communicate the initial playback state of the new item. If NULL, the coordinator will assume that playback is paused at kCMTimeZero.
					An appropriate timebase to pass to the completion handler may be retreived from AVFoundation playback objects such as AVSampleBufferRenderSynchronizer.
					It can also be created manually using CMTimebaseCreateWithSourceClock. The timebase will only be used to take a snapshot of its immediate timing. It will not be observed further.
*/
-(void)transitionToItemWithIdentifier:(NSString * __nullable)itemIdentifier proposingInitialTimingBasedOnTimebase:(CMTimebaseRef __nullable)snapshotTimebase;

/**
	@property	currentItemIdentifier
	@abstract	The item identifier of the current item. Previously set by a call to transitionToItemWithIdentifier:proposingInitialTimingBasedOnTimebase:
*/
@property (nonatomic, readonly, nullable) NSString *currentItemIdentifier;

/**
	@method 	reapplyCurrentItemStateToPlaybackControlDelegate
	@abstract 	Instructs the coordinator to re-issue commands to synchronize the current item back to the state of the other participants.
	@discussion Use this method when the playback object is in a state that doesn't match the group for some reason and should be re-synchronized.
*/
-(void)reapplyCurrentItemStateToPlaybackControlDelegate;

@end

@class AVDelegatingPlaybackCoordinatorPlayCommand;
@class AVDelegatingPlaybackCoordinatorPauseCommand;
@class AVDelegatingPlaybackCoordinatorSeekCommand;
@class AVDelegatingPlaybackCoordinatorBufferingCommand;

/**
	@protocol	AVPlaybackCoordinatorPlaybackControlDelegate
	@abstract	A custom player implementation
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@protocol AVPlaybackCoordinatorPlaybackControlDelegate <NSObject>

/**
	@method		playbackCoordinator:didIssuePlayCommand:completionHandler:
	@abstract	Called by the coordinator to match the playback rate of the control delegate to the group, when the target rate is non-zero.
	@discussion	The coordinator issues this command when the desired playback timeline has changed. This may mean that the rate has changed, but it can also mean that the anchor time has changed.
				Play commands are only issued when the desired playback rate is non-zero.
	@param		coordinator
					The coordinator requesting a change in playback rate.
	@param 		playCommand
					A play command object. See AVDelegatingPlaybackCoordinatorPlayCommand.
					The receiver should verify that the command is still valid by inspecting the expectedCurrentItemIdentifier property before applying the command.
	@param		completionHandler
					The receiver must call the completion handler when done, either when the command has been handled succesfully or when the receiver has indicated its inability
					to handle the command by beginning a suspension with an appropriate reason.
*/
-(void)playbackCoordinator:(AVDelegatingPlaybackCoordinator *)coordinator
	   didIssuePlayCommand:(AVDelegatingPlaybackCoordinatorPlayCommand *)playCommand
		 completionHandler:(void (^)(void))completionHandler;

/**
	@method		playbackCoordinator:didIssuePauseCommand:completionHandler:
	@abstract	Called by the coordinator to pause playback.
	@param		coordinator
					The coordinator requesting playback to pause.
	@param 		pauseCommand
					A pause command object. See AVDelegatingPlaybackCoordinatorPauseCommand.
					The receiver should verify that the command is still valid by inspecting the expectedCurrentItemIdentifier property before applying the command.
	@param		completionHandler
					The receiver must call the completion handler when done, either when the command has been handled succesfully or when the receiver has indicated its inability
					to handle the command by beginning a suspension with an appropriate reason.
					If the command's shouldBufferInAnticipationOfPlayback is YES, the completion handler should also only be called once the playback object is ready to receive a subsequent play command.
*/
-(void)playbackCoordinator:(AVDelegatingPlaybackCoordinator *)coordinator
	  didIssuePauseCommand:(AVDelegatingPlaybackCoordinatorPauseCommand *)pauseCommand
		 completionHandler:(void (^)(void))completionHandler;


/**
	@method		playbackCoordinator:didIssueSeekCommand:completionHandler:
	@abstract	Called by the coordinator to seek to a new time.
	@discussion The coordinator issues this command when the playback object current time changes, potentially also pausing playback.
	@param		coordinator
					The coordinator requesting the seek.
	@param 		seekCommand
					A seek command object. See AVDelegatingPlaybackCoordinatorSeekCommand.
					The receiver should verify that the command is still valid by inspecting the expectedCurrentItemIdentifier property before applying the command.
	@param		completionHandler
					The receiver must call the completion handler when done, either when the command has been handled succesfully or when the receiver has indicated its inability
					to handle the command by beginning a suspension with an appropriate reason.
					If the command's shouldBufferInAnticipationOfPlayback is YES, the completion handler should also only be called once the playback object is ready to receive a subsequent play command.
*/
-(void)playbackCoordinator:(AVDelegatingPlaybackCoordinator *)coordinator
	   didIssueSeekCommand:(AVDelegatingPlaybackCoordinatorSeekCommand *)seekCommand
		 completionHandler:(void (^)(void))completionHandler;


/**
	@method		playbackCoordinator:didIssueBufferingCommand:completionHandler:
	@abstract	Called by the coordinator to indicate that playback is expected to begin soon and the playback object should begin buffering.
	@discussion	The coordinator issues this command when playback is currently paused and the coordinator is expecting playback to start soon.
 				In response to this command, it is appropriate to update playback UI to indicate playback in a waiting state.
				The expected start can be cancelled by calling -[AVDelegatingPlaybackCoordinator coordinateRateChangeTo:0].
	@param		coordinator
					The coordinator requesting buffering to begin.
	@param 		bufferingCommand
					A buffering command object. See AVDelegatingPlaybackCoordinatorBufferingCommand.
					The receiver should verify that the command is still valid by inspecting the expectedCurrentItemIdentifier property before applying the command.
	@param		completionHandler
					The receiver must call the completion handler when done, either when the command has been handled succesfully or when the receiver has indicated its inability
					to handle the command by beginning a suspension with an appropriate reason.
					For buffering commands, the command should only be considered complete once the playback object is ready to receive a subsequent play command.
*/
-(void)playbackCoordinator:(AVDelegatingPlaybackCoordinator *)coordinator
  didIssueBufferingCommand:(AVDelegatingPlaybackCoordinatorBufferingCommand *)bufferingCommand
		 completionHandler:(void (^)(void))completionHandler;

@end

/**
	@class		AVDelegatingPlaybackCoordinatorPlaybackControlCommand
	@abstract	Abstract superclass for playback commands
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVDelegatingPlaybackCoordinatorPlaybackControlCommand : NSObject

AV_INIT_UNAVAILABLE

/**
	@property	originator
	@abstract	The participant causing this command to be issued.
	@discussion	Only commands issued on behalf of another participant will contain an originator.
				Commands caused by local requests, e.g., requests to coordinate a rate change, will not contain an originator.
				Similarly, re-application of older commands, e.g., in response to a call to [AVDelegatingPlaybackCoordinator reapplyCurrentItemStateToPlaybackControlDelegate], will not contain an originator.
				If the originator is non-nil, it may be appropriate to show UI indicating someone else's action.
*/
@property (nonatomic, readonly, nullable) AVCoordinatedPlaybackParticipant *originator;

/**
	@property	expectedCurrentItemIdentifier
	@abstract	Indicates the item this command was issued for.
	@discussion	Commands are always meant for the current item. A command handler should verify that the identifier of its current item matches this identifier.
				If it doesn't this command is obsolete and should be ignored. Note that any completion handler of the delegate method issuing the command must still be invoked.
*/
@property (nonatomic, readonly) NSString *expectedCurrentItemIdentifier;

@end

/**
	@class		AVDelegatingPlaybackCoordinatorPlayCommand
	@abstract	A playback command requesting playback with specific timing.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVDelegatingPlaybackCoordinatorPlayCommand : AVDelegatingPlaybackCoordinatorPlaybackControlCommand

AV_INIT_UNAVAILABLE

/**
	@property	rate
	@abstract	Playback rate. Will always be non-zero.
*/
@property (nonatomic, readonly) float rate;

/**
	@property	itemTime
	@abstract	The itemTime that playback should begin at.
	@discussion	The receiver of this command should verify that data is loaded for the requested time and potentially begin loading it before beginning playback.
				It is not important to load data for time exactly. If data "similar" to time is already loaded, it is acceptable to start playback with the loaded data. Playback should still start with the requested timing.
				Should the receiver be unable to start with the exact requested timing, playback will be out of sync with the group.
				If data for the requested time cannot be loaded, or playback stalls later, the command handler may want to indicate this to the coordinator by beginning a suspension with AVCoordinatedPlaybackSuspensionReasonStallRecovery.
*/
@property (nonatomic, readonly) CMTime itemTime;

/**
	@property	hostClockTime
	@abstract	This is the host clock time (see CMClockGetHostTimeClock()) defining when playback should start (or should have started) at the given itemTime.
*/
@property (nonatomic, readonly) CMTime hostClockTime;

@end


/**
	@class		AVDelegatingPlaybackCoordinatorBufferingCommand
	@abstract	A playback command requesting buffering in anticipation of playback.
	@discussion Receiving this command should be reflected to the user as playback in a buffering state.
				To cancel the group intent to begin playback and move back into a paused state, call [AVDelegatingPlaybackCoordinator coordinateRateChangeToRate:0 options: 0]
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVDelegatingPlaybackCoordinatorBufferingCommand : AVDelegatingPlaybackCoordinatorPlaybackControlCommand

AV_INIT_UNAVAILABLE

/**
	@property	anticipatedPlaybackRate
	@abstract	The rate to prepare playback for.
	@discussion The command should only be considered complete once the player is ready to receive an AVDelegatingPlaybackCoordinatorPlayCommand with the indicated rate.
*/
@property (nonatomic, readonly) float anticipatedPlaybackRate;

/**
	@property	completionDueDate
	@abstract	Communicates when the coordinator expects the command's completion handler at the latest.
	@discussion	A receiver of a buffering command should fire the completion handler by this date at the latest. This is useful in buffering situations where the receiver
				has not yet buffered enough data to be considered ready to play by the due date. The receiver should then decide to either complete the command as is
				to try and keep up with the group, or alternatively begin a stall recovery suspension to communicate the situation to the other participants.
				Completing the command after this date means that the coordinator will likely send a play command for a later time than the receiver buffered for.
*/
@property (nonatomic, readonly, nullable) NSDate *completionDueDate;

@end

/**
	@class		AVDelegatingPlaybackCoordinatorPauseCommand
	@abstract	A playback command requesting a pause
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVDelegatingPlaybackCoordinatorPauseCommand : AVDelegatingPlaybackCoordinatorPlaybackControlCommand

AV_INIT_UNAVAILABLE

/**
	@property	shouldBufferInAnticipationOfPlayback
	@abstract	Indicates that playback is anticipated and the player should begin buffering if necessary.
	@discussion	When shouldBufferInAnticipationOfPlayback is YES, some participant wants to resume playback at the rate indicated by the anticipatedPlaybackRate property.
				This should be treated similar to receiving a separate AVDelegatingPlaybackCoordinatorBufferingCommand.
				If YES, the command should only be considered complete once the player is ready to receive an AVDelegatingPlaybackCoordinatorPlayCommand with the indicated rate.
*/
@property (nonatomic, readonly) BOOL shouldBufferInAnticipationOfPlayback;

/**
	@property	anticipatedPlaybackRate
	@abstract	The rate to prepare for if shouldBufferInAnticipationOfPlayback is YES.
*/
@property (nonatomic, readonly) float anticipatedPlaybackRate;

@end


/**
	@class		AVDelegatingPlaybackCoordinatorSeekCommand
	@abstract	A playback command requesting a seek.
	@discussion	If the current playback rate is non-zero, playback should not automatically resume after the seek. Instead the delegate should pause and wait for the coordinator to issue another PlayCommand.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVDelegatingPlaybackCoordinatorSeekCommand : AVDelegatingPlaybackCoordinatorPlaybackControlCommand

AV_INIT_UNAVAILABLE

/**
	@property	itemTime
	@abstract	The time to seek the currentItem to.
	@discussion	Playback should never automatically resume after seeking to this time. The coordinator will issue a new PlayCommand when everyone else is ready to resume.
*/
@property (nonatomic, readonly) CMTime itemTime;

/**
	@property	shouldBufferInAnticipationOfPlayback
	@abstract	Indicates that playback is anticipated and the player should begin buffering if necessary.
	@discussion	When shouldBufferInAnticipationOfPlayback, playback is expected to eventually resume at the rate indicated by the anticipatedPlaybackRate property.
				This should be treated similar to receiving a separate AVDelegatingPlaybackCoordinatorBufferingCommand.
				If YES, the command should only be considered complete once the player is ready to receive an AVDelegatingPlaybackCoordinatorPlayCommand with the indicated rate.
*/
@property (nonatomic, readonly) BOOL shouldBufferInAnticipationOfPlayback;

/**
	@property	anticipatedPlaybackRate
	@abstract	The rate to prepare for if shouldBufferInAnticipationOfPlayback is YES.
*/
@property (nonatomic, readonly) float anticipatedPlaybackRate;

/**
	@property	completionDueDate
	@abstract	Communicates when the coordinator expects the command's completion handler at the latest.
	@discussion	A seek command expecting buffering in anticipation of playback does expect the receiver to fire the completion handler by this date at the latest.
				This is useful in buffering situations where the receiver has not yet buffered enough data to be considered ready to play by the due date.
				The receiver should then decide to either complete the command as is to try and keep up with the group, or alternatively begin a stall recovery
				suspension to communicate the situation to the other participants.
				Completing the command after this date means that the coordinator will likely send a play command for a later time than the receiver buffered for.
*/
@property (nonatomic, readonly, nullable) NSDate *completionDueDate;

@end

NS_ASSUME_NONNULL_END


#else
#import <AVFCore/AVPlaybackCoordinator.h>
#endif
