/**
 @header
 
 
 Node that can play a video file
 
 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

@class AVPlayer;

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

SK_EXPORT @interface SKVideoNode : SKNode

/**
 Create a video node from an AVPlayer. You can use the AVPlayer to control playback.
 */
+ (SKVideoNode *)videoNodeWithAVPlayer:(AVPlayer*)player;

/**
 Create a video node from a file.
 */
+ (SKVideoNode *)videoNodeWithVideoFileNamed:(NSString *)videoFile;

/**
 Create a video node from a URL.
 */
+ (SKVideoNode *)videoNodeWithVideoURL:(NSURL *)videoURL;


/**
 Designated Initializer.
 
 Initialize a video node from an AVPlayer. You can use the AVPlayer to control playback.
 */
- (instancetype)initWithAVPlayer:(AVPlayer*)player;

/**
 Initialize a video node from a file.
 */
- (instancetype)initWithVideoFileNamed:(NSString *)videoFile;

- (instancetype)initWithVideoURL:(NSURL *)url;

- (void)play;
- (void)pause;

/**
 The display size of the video (in parent's coordinate space)
 */
@property (SK_NONATOMIC_IOSONLY) CGSize size;

/**
 The location in the video that maps to its 'position' in the parent's coordinate space. (0.0-1.0)
 */
@property (SK_NONATOMIC_IOSONLY) CGPoint anchorPoint;

@end
