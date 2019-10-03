//
//  MPRemoteCommand.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPRemoteControlTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommandEvent;

typedef NS_ENUM(NSInteger, MPRemoteCommandHandlerStatus) {
    /// There was no error executing the requested command.
    MPRemoteCommandHandlerStatusSuccess = 0,
    
    /// The command could not be executed because the requested content does not
    /// exist in the current application state.
    MPRemoteCommandHandlerStatusNoSuchContent = 100,
    
    /// The command could not be executed because there is no now playing item
    /// available that is required for this command. As an example, an
    /// application would return this error code if an "enable language option"
    /// command is received, but nothing is currently playing.
    MPRemoteCommandHandlerStatusNoActionableNowPlayingItem MP_API(ios(9.1), macos(10.12.2)) = 110,
    
    /// The command could not be executed because a device required
    /// is not available. For instance, if headphones are required, or if a watch
    /// app realizes that it needs the companion to fulfull a request.
    MPRemoteCommandHandlerStatusDeviceNotFound MP_API(ios(11.0), macos(10.13)) = 120,
    
    /// The command could not be executed for another reason.
    MPRemoteCommandHandlerStatusCommandFailed = 200
} MP_API(ios(7.1), macos(10.12.2), watchos(5.0));

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRemoteCommand : NSObject

/// Whether a button (for example) should be enabled and tappable for this
/// particular command.
@property (nonatomic, assign, getter = isEnabled) BOOL enabled;

// Target-action style for adding handlers to commands.
// Actions receive an MPRemoteCommandEvent as the first parameter.
// Targets are not retained by addTarget:action:, and should be removed from the
// command when the target is deallocated.
//
// Your selector should return a MPRemoteCommandHandlerStatus value when
// possible. This allows the system to respond appropriately to commands that
// may not have been able to be executed in accordance with the application's
// current state.
- (void)addTarget:(id)target action:(SEL)action;
- (void)removeTarget:(id)target action:(nullable SEL)action;
- (void)removeTarget:(nullable id)target;

/// Returns an opaque object to act as the target.
- (id)addTargetWithHandler:(MPRemoteCommandHandlerStatus(^)(MPRemoteCommandEvent *event))handler;

/// Private constructor.
- (instancetype)init NS_UNAVAILABLE;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPSkipIntervalCommand : MPRemoteCommand

/// An array of NSNumbers (NSTimeIntervals) that contain preferred skip intervals.
@property (nonatomic, copy) NSArray<NSNumber *> *preferredIntervals;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPFeedbackCommand : MPRemoteCommand

/// Whether the feedback command is in an "active" state. An example of when a
/// feedback command would be active is if the user already "liked" a particular
/// content item.
@property (nonatomic, assign, getter = isActive) BOOL active;

/// A localized string briefly describing the context of the command.
@property (nonatomic, copy) NSString *localizedTitle;

/// An optional shorter version of the localized title for this feedback
/// command. MediaPlayer uses this property to display this command's title on
/// remote control interfaces with little screen space.
@property (nonatomic, copy) NSString *localizedShortTitle MP_API(ios(8.0));

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRatingCommand : MPRemoteCommand

/// Minimum rating for the command.
@property (nonatomic, assign) float minimumRating;

/// Maximum rating for the command.
@property (nonatomic, assign) float maximumRating;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPChangePlaybackRateCommand : MPRemoteCommand

/// An array of NSNumbers (floats) that contain supported playback rates that
/// the command can send.
@property (nonatomic, copy) NSArray<NSNumber *> *supportedPlaybackRates;

@end

/// Command for changing the current playback position in a now playing item.
/// Sends out MPChangePlaybackPositionCommandEvents.
MP_API(ios(9.0), tvos(9.0), macos(10.12.2), watchos(5.0))
@interface MPChangePlaybackPositionCommand : MPRemoteCommand

@end

/// Command for changing the current shuffle mode to use during playback. To
/// update the system's current representation of your app's shuffle mode, set
/// the currentShuffleType property on this command to the proper shuffle type
/// value.
MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangeShuffleModeCommand : MPRemoteCommand

/// The app's current shuffle type.
@property (nonatomic, assign) MPShuffleType currentShuffleType;

@end

/// Command for changing the current repeat mode to use during playback. To
/// update the system's current representation of your app's repeat mode, set
/// the currentRepeatType property on this command to the proper repeat type
/// value.
MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangeRepeatModeCommand : MPRemoteCommand

/// The app's current repeat mode.
@property (nonatomic, assign) MPRepeatType currentRepeatType;

@end

NS_ASSUME_NONNULL_END
