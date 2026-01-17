//
//  AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>

#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVMediaSelectionGroup.h>
#import <AVFoundation/AVMediaSelection.h>
#import <AVFoundation/AVMediaFormat.h>

NS_ASSUME_NONNULL_BEGIN

@class MPNowPlayingInfoLanguageOption, MPNowPlayingInfoLanguageOptionGroup;

/// Category for creating language options from AV types
@interface AVMediaSelectionOption (MPNowPlayingInfoLanguageOptionAdditions)

/// Will create a language option from the AVMediaSelectionOption
/// Returns nil if the AVMediaSelectionOption does not represent an Audible or Legible selection option.
- (nullable MPNowPlayingInfoLanguageOption *)makeNowPlayingInfoLanguageOption;

@end

// -----------------------------------------------------------------------------

@interface AVMediaSelectionGroup (MPNowPlayingInfoLanguageOptionAdditions)

/// Will create a language option group from the AVMediaSelectionGroup
/// Any AVMediaSelectionOptions in the AVMediaSelectionGroup not representing
/// Audible or Legible selection options will be ignored.
- (MPNowPlayingInfoLanguageOptionGroup *)makeNowPlayingInfoLanguageOptionGroup;

@end

NS_ASSUME_NONNULL_END
