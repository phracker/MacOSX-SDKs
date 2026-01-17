//
//  SCNAudioSource.h
//  SceneKit
//
//  Copyright © 2015-2021 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNNode.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioNode;

/*!
 @class SCNAudioSource
 @abstract The SCNAudioSource class represents an audio source that can be added to a SCNNode.
 */
SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNAudioSource : NSObject <NSCopying, NSSecureCoding>

/*!
 @method initWithFileNamed:
 @abstract Convenience initializer that creates an AVAudioNode from the named audio asset in the main bundle.
 */
- (nullable instancetype)initWithFileNamed:(NSString *)name;

/*!
 @method initWithURL:
 @abstract Convenience initializer that creates an AVAudioNode from the URL that contain a audio asset.
 */
- (nullable instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

/*!
 @method audioSourceNamed:
 @abstract Convenience class initializer that caches audioSources.
 */
+ (nullable instancetype)audioSourceNamed:(NSString *)fileName;

/*!
 @property positional
 @abstract Marks the audio source as positional so that the audio mix considers relative position and velocity with regards to the SCNSceneRenderer's current listener node. Defaults to YES.
 @discussion shouldStream must be set to false in order to get positional audio (see shouldStream).
 @see SCNSceneRenderer audioListener.
 */
@property(nonatomic, getter=isPositional) BOOL positional;

/*!
 @property volume
 @abstract The default volume for this audio buffer. Default is 1.0 (full volume).
 */
@property(nonatomic) float volume;

/*!
 @property rate
 @abstract The default rate for this audio buffer. Default is 1.0 (original rate of the audio source).
 */
@property(nonatomic) float rate;

/*!
 @property reverbBlend
 @abstract The default reverbBlend for this audio buffer. Default is 0.0 (no sound is sent to the reverb).
 */
@property(nonatomic) float reverbBlend;

/*!
 @property loops
 @abstract Specifies whether the audio source should loop or not. Defaults to NO.
 */
@property(nonatomic) BOOL loops;

/*!
 @property shouldStream
 @abstract Specifies whether the audio source should be streamed or not. Defaults to NO.
 */
@property(nonatomic) BOOL shouldStream;

/*!
 @method load
 @abstract Load and uncompress the audio source in memory. This method has no effect if "shouldStream" is set to YES or if the audio source is already loaded.
 @discussion This method let you preload your audio sources. If an audio source is not preloaded, it will be loaded anyway when playing it.
 */
- (void)load;

@end

SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNAudioPlayer : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property initWithSource:
 @abstract Init an audio player with a source. Most people should use audioPlayerWithSource as it permits to recycle previous players instead of creating new ones for each instance.
 */
- (instancetype)initWithSource:(SCNAudioSource *)source NS_DESIGNATED_INITIALIZER;

/*!
 @property initWithAVAudioNode:
 @abstract Init an audio player with an AVAudioNode. Most people should use audioPlayerWithAVAudioNode as it permits to recycle previous players instead of creating new ones for each instance.
 */
- (instancetype)initWithAVAudioNode:(AVAudioNode *)audioNode NS_DESIGNATED_INITIALIZER;

/*!
 @property audioPlayerWithSource:
 @abstract Create an audio player with a source.
 */
+ (instancetype)audioPlayerWithSource:(SCNAudioSource *)source;

/*!
 @property audioPlayerWithAVAudioNode:
 @abstract Create an audio player with a custom AVAudioNode instance.
 */
+ (instancetype)audioPlayerWithAVAudioNode:(AVAudioNode *)audioNode;

/*!
 @property playbackStarted
 @abstract This block is called when the playback starts in case a valid audio source is present.
 */
@property(nonatomic, copy, nullable) void (^willStartPlayback)(void);

/*!
 @property playbackFinished
 @abstract This block is called when the playback stops in case a valid audio source is present.
 */
@property(nonatomic, copy, nullable) void (^didFinishPlayback)(void);

/*!
 @property audioNode
 @abstract The audioNode. If this player was not initialised with a custom AVAudioNode this contains the internal audio player node used by scene kit internally.
 */
@property(nonatomic, readonly, nullable) AVAudioNode *audioNode;

/*!
 @property audioSource
 @abstract The audioSource if there is one.
 */
@property(nonatomic, readonly, nullable) SCNAudioSource *audioSource;

@end


@interface SCNNode (SCNAudioSupport)

/*!
 @method addAudioPlayer:
 @abstract Add an audio player to the node and starts playing it right away.
 */
- (void)addAudioPlayer:(SCNAudioPlayer *)player API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method removeAllAudioPlayers
 @abstract Remove all audio players from this node and stop playing them.
 */
- (void)removeAllAudioPlayers API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method removeAudioPlayer:
 @abstract Remove the given audio player from this node and stop playing it.
 */
- (void)removeAudioPlayer:(SCNAudioPlayer *)player API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property audioPlayers
 @abstract Get an array with all the audio players connected and playing on this node.
 */
@property(nonatomic, readonly) NSArray<SCNAudioPlayer *> *audioPlayers API_AVAILABLE(macos(10.11), ios(9.0));

@end

NS_ASSUME_NONNULL_END
