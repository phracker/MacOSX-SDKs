//
//  PHLivePhotoView.h
//  PhotosUI
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <Photos/Photos.h>
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#import <Photos/PHLivePhoto.h>
#endif

NS_ASSUME_NONNULL_BEGIN
#if TARGET_OS_IPHONE
API_AVAILABLE_BEGIN(ios(9.1), tvos(10))
#elif TARGET_OS_OSX
API_AVAILABLE_BEGIN(macos(10.12))
#endif

@protocol PHLivePhotoViewDelegate;

#if TARGET_OS_IPHONE
typedef NS_OPTIONS(NSUInteger, PHLivePhotoBadgeOptions) {
    PHLivePhotoBadgeOptionsOverContent  = 1 << 0,               ///< Include treatments so this image can be shown directly over the content of the Live Photo
    PHLivePhotoBadgeOptionsLiveOff      = 1 << 1,               ///< To indicate that the Live Photo aspect is turned off and it will be treated as a still (e.g. for sharing)
} NS_SWIFT_SENDABLE;
#endif

typedef NS_ENUM(NSInteger, PHLivePhotoViewPlaybackStyle) {
    PHLivePhotoViewPlaybackStyleUndefined = 0,
    PHLivePhotoViewPlaybackStyleFull,
    PHLivePhotoViewPlaybackStyleHint,
} NS_SWIFT_SENDABLE;

#if TARGET_OS_OSX
typedef NS_ENUM(NSInteger, PHLivePhotoViewContentMode) {
    PHLivePhotoViewContentModeAspectFit,
    PHLivePhotoViewContentModeAspectFill,
} NS_SWIFT_SENDABLE;
#endif

OS_EXPORT
#if TARGET_OS_IPHONE
@interface PHLivePhotoView : UIView
#elif TARGET_OS_OSX
@interface PHLivePhotoView : NSView
#endif

#if TARGET_OS_IPHONE
/// System badge images representing Live Photo content
+ (UIImage *)livePhotoBadgeImageWithOptions:(PHLivePhotoBadgeOptions)badgeOptions;
#endif

@property (readwrite, nonatomic, weak, nullable) id<PHLivePhotoViewDelegate> delegate;

/// Live photo displayed in the receiver.
@property (readwrite, nonatomic, strong, nullable) PHLivePhoto *livePhoto;

#if TARGET_OS_OSX
/// The mode in which the receiver will display its content. Defaults to PHLivePhotoViewContentModeAspectFit.
@property (readwrite, nonatomic, assign) PHLivePhotoViewContentMode contentMode;
#endif

/// The rectangle, in the unit coordinate space, that defines the portion of the Live Photo contents that should be displayed. In this coordinate system, the point `{0.0,0.0}` refers to the upper left corner of the Live Photo, and `{1.0,1.0}` refers to the bottom right corner.
@property (nonatomic) CGRect contentsRect API_AVAILABLE(macos(14), ios(17), tvos(17));

#if TARGET_OS_OSX
/// The audio volume during playback
@property (readwrite, nonatomic, assign) float audioVolume;
#endif

/// Indicates whether the audio of the Live Photo is muted.
@property (readwrite, nonatomic, assign, getter=isMuted) BOOL muted;

#if TARGET_OS_IPHONE
/// Gesture used to trigger playback. By default, added to the receiver. Can be moved to a different view.
@property (readonly, nonatomic, strong) UIGestureRecognizer *playbackGestureRecognizer;
#endif

/// The following methods allow the client to manually trigger playback. If the live photo is changed during playback, it will be immediately interrupted.
- (void)startPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;
- (void)stopPlayback;

#if TARGET_OS_OSX
/// Stops live photo playback. If animated is NO, the photo is immediately displayed.
- (void)stopPlaybackAnimated:(BOOL)animated;

/// Directly access the livePhotoBadge in cases where it should be added to a different place in the view hierarchy and not the live photo view. This can be useful when the live photo view is added to a scroll view.
@property (readonly, nonatomic, strong, nullable) NSView *livePhotoBadgeView;
#endif
@end


OS_EXPORT
NS_SWIFT_UI_ACTOR
@protocol PHLivePhotoViewDelegate <NSObject>
@optional

- (BOOL)livePhotoView:(PHLivePhotoView *)livePhotoView canBeginPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView willBeginPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView didEndPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

#if TARGET_OS_IPHONE // {
// This will be called before gestureRecognizer get touch info (point location), so we need to provide the touch to delegate to decide.
- (NSTimeInterval)livePhotoView:(PHLivePhotoView *)livePhotoView extraMinimumTouchDurationForTouch:(UITouch *)touch withStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;
#endif // }
@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
