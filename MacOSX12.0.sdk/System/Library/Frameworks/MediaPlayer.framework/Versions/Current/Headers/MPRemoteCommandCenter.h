//
//  MPRemoteCommandCenter.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPChangePlaybackPositionCommand;
@class MPChangePlaybackRateCommand;
@class MPChangeRepeatModeCommand;
@class MPChangeShuffleModeCommand;
@class MPFeedbackCommand;
@class MPRatingCommand;
@class MPRemoteCommand;
@class MPSkipIntervalCommand;

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRemoteCommandCenter : NSObject

// Playback Commands
@property (nonatomic, readonly) MPRemoteCommand *pauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *playCommand;
@property (nonatomic, readonly) MPRemoteCommand *stopCommand;
@property (nonatomic, readonly) MPRemoteCommand *togglePlayPauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *enableLanguageOptionCommand MP_API(ios(9.0), macos(10.12.2));
@property (nonatomic, readonly) MPRemoteCommand *disableLanguageOptionCommand MP_API(ios(9.0), macos(10.12.2));
@property (nonatomic, readonly) MPChangePlaybackRateCommand *changePlaybackRateCommand;
@property (nonatomic, readonly) MPChangeRepeatModeCommand *changeRepeatModeCommand;
@property (nonatomic, readonly) MPChangeShuffleModeCommand *changeShuffleModeCommand;

// Previous/Next Track Commands
@property (nonatomic, readonly) MPRemoteCommand *nextTrackCommand;
@property (nonatomic, readonly) MPRemoteCommand *previousTrackCommand;

// Skip Interval Commands
@property (nonatomic, readonly) MPSkipIntervalCommand *skipForwardCommand;
@property (nonatomic, readonly) MPSkipIntervalCommand *skipBackwardCommand;

// Seek Commands
@property (nonatomic, readonly) MPRemoteCommand *seekForwardCommand;
@property (nonatomic, readonly) MPRemoteCommand *seekBackwardCommand;
@property (nonatomic, readonly) MPChangePlaybackPositionCommand *changePlaybackPositionCommand MP_API(ios(9.1), macos(10.12.2));

// Rating Command
@property (nonatomic, readonly) MPRatingCommand *ratingCommand;

// Feedback Commands
// These are generalized to three distinct actions. Your application can provide
// additional context about these actions with the localizedTitle property in
// MPFeedbackCommand.
@property (nonatomic, readonly) MPFeedbackCommand *likeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *dislikeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *bookmarkCommand;

+ (MPRemoteCommandCenter *)sharedCommandCenter;

MP_INIT_UNAVAILABLE

@end

NS_ASSUME_NONNULL_END
