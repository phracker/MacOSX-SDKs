//
//  INPlayMediaIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INPlayMediaIntent.h>
#import <Intents/INPlaybackRepeatMode.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPlayMediaIntent (Deprecated)

- (instancetype)initWithMediaItems:(nullable NSArray<INMediaItem *> *)mediaItems
                    mediaContainer:(nullable INMediaItem *)mediaContainer
                      playShuffled:(nullable NSNumber *)playShuffled
                playbackRepeatMode:(INPlaybackRepeatMode)playbackRepeatMode
                    resumePlayback:(nullable NSNumber *)resumePlayback NS_REFINED_FOR_SWIFT API_DEPRECATED("Use the designated initializer instead", ios(12.0, 13.0), watchos(5.0, 6.0));

@end

NS_ASSUME_NONNULL_END
