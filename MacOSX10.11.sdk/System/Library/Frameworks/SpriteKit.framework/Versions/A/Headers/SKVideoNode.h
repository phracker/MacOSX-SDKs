/**
 @header
 
 
 Node that can play a video file
 
 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

@class AVPlayer;

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKVideoNode : SKNode

/**
 Create a video node from an AVPlayer. You can use the AVPlayer to control playback.
 */
+ (SKVideoNode *)videoNodeWithAVPlayer:(AVPlayer*)player;

/**
 Create a video node from a file.
 */
+ (SKVideoNode *)videoNodeWithVideoFileNamed:(NSString *)videoFile NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);
+ (SKVideoNode *)videoNodeWithFileNamed:(NSString *)videoFile NS_AVAILABLE(10_10, 8_0);

/**
 Create a video node from a URL.
 */
+ (SKVideoNode *)videoNodeWithVideoURL:(NSURL *)videoURL NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);
+ (SKVideoNode *)videoNodeWithURL:(NSURL *)videoURL NS_AVAILABLE(10_10, 8_0);

/**
 Designated Initializer.
 
 Initialize a video node from an AVPlayer. You can use the AVPlayer to control playback.
 */
- (instancetype)initWithAVPlayer:(AVPlayer*)player NS_DESIGNATED_INITIALIZER;

/**
 Initialize a video node from a file.
 */
- (instancetype)initWithVideoFileNamed:(NSString *)videoFile NS_DESIGNATED_INITIALIZER NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);
- (instancetype)initWithFileNamed:(NSString *)videoFile NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_10, 8_0);

- (instancetype)initWithVideoURL:(NSURL *)url NS_DESIGNATED_INITIALIZER NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);
- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_10, 8_0);

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (void)play;
- (void)pause;

/**
 The display size of the video (in parent's coordinate space)
 */
@property (nonatomic) CGSize size;

/**
 The location in the video that maps to its 'position' in the parent's coordinate space. (0.0-1.0)
 */
@property (nonatomic) CGPoint anchorPoint;

@end

NS_ASSUME_NONNULL_END
