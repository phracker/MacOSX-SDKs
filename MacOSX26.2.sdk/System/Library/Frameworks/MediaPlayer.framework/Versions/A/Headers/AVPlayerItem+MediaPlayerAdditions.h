//
//  AVPlayerItem+MPAdditions.h
//  MediaPlayer
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <AVFoundation/AVPlayerItem.h>

NS_ASSUME_NONNULL_BEGIN

MP_UNAVAILABLE_BEGIN(watchos, macos)

@interface AVPlayerItem (MPAdditions)

/// The current now playing info for the player item.
/// Setting the info to nil will clear it.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *nowPlayingInfo MP_API(ios(16.0), tvos(16.0));

@end

MP_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

