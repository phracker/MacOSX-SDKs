/**
 @header
 
 Node that holds an AVAudioEngine sound graph, including from a single sound source or URL.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKit.h>

#if __has_include(<AVFoundation/AVAudioEngine.h>)

@class AVAudioNode;

NS_ASSUME_NONNULL_BEGIN

/**
 * A SpriteKit scene graph audio node that provides a way to link audio graphs to a SpriteKit scene.
 * The currently presented scene is responsible for mixing the audio from nodes in the scene.
 *
 * Positional sounds will use their relative location and velocity to the scene's listener to apply distance
 * attenuation, doppler shift and pan.
 * 
 * @see AVAudio3DMixing
 * @see SKScene.listener
 */
SK_EXPORT API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11)) @interface SKAudioNode : SKNode <NSSecureCoding>

/**Creates a SpriteKit scene graph audio node from the given AVAudioNode.
 * @see AVAudioNode
 */
- (instancetype)initWithAVAudioNode:(nullable AVAudioNode *)node NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**Convenience initializer that creates an AVAudioNode from the named audio asset in the main bundle.
 * @see initWithAVAudioNode
 */
- (instancetype)initWithFileNamed:(NSString *)name;

/**Convenience initializer that creates an AVAudioNode from the URL that contain a audio asset.
 * @see initWithAVAudioNode
 */
- (instancetype)initWithURL:(NSURL *)url;

/**Sets or gets the current AVAudioNode used by this instance.
 */
@property (nonatomic, retain, nullable) AVAudioNode *avAudioNode;

/**Specifies whether the node is to automatically play sound when added to a scene.
 * If autoplaysLooped is NO, the node and its sound must be explicitly scheduled and played using
 * the scene's engine.
 *
 * If YES, the node will automatically play sound when added to a scene.
 *
 * Defaults to YES.
 * @see SKView.paused
 */
@property (nonatomic, assign) BOOL autoplayLooped;

/**Marks the audio source as positional so that the audio mix considers relative position and velocity
 * with regards to the scene's current listener node.
 *
 * @see AVAudio3DMixing
 * @see SKScene.listener
 */
@property (nonatomic, assign, getter=isPositional) BOOL positional;

@end

/**Actions that are to be used with audio nodes.
 */
@interface SKAction (SKAudioNode)

+ (SKAction *)stereoPanTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)stereoPanBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeReverbTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeReverbBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeObstructionTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeObstructionBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeOcclusionTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeOcclusionBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

@end

NS_ASSUME_NONNULL_END

#endif
