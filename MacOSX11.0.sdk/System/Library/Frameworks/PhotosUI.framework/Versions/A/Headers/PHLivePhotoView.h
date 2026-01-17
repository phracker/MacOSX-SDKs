//
//  PHLivePhotoView.h
//  PhotosUI
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#import <AppKit/AppKit.h>
#import <Photos/PHLivePhoto.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.12))

@protocol PHLivePhotoViewDelegate;


typedef NS_ENUM(NSInteger, PHLivePhotoViewPlaybackStyle) {
    PHLivePhotoViewPlaybackStyleUndefined = 0,
    PHLivePhotoViewPlaybackStyleFull,
    PHLivePhotoViewPlaybackStyleHint,
};

typedef NS_ENUM(NSInteger, PHLivePhotoViewContentMode) {
    PHLivePhotoViewContentModeAspectFit,
    PHLivePhotoViewContentModeAspectFill,
};

OS_EXPORT
@interface PHLivePhotoView : NSView


@property (readwrite, nonatomic, weak, nullable) id<PHLivePhotoViewDelegate> delegate;

/// Live photo displayed in the receiver.
@property (readwrite, nonatomic, strong, nullable) PHLivePhoto *livePhoto;

/// The mode in which the receiver will display its content. Defaults to PHLivePhotoViewContentModeAspectFit.
@property (readwrite, nonatomic, assign) PHLivePhotoViewContentMode contentMode;

/// The audio volume during playback
@property (readwrite, nonatomic, assign) float audioVolume;

/// Indicates whether the audio of the Live Photo is muted.
@property (readwrite, nonatomic, assign, getter=isMuted) BOOL muted;


/// The following methods allow the client to manually trigger playback. If the live photo is changed during playback, it will be immediately interrupted.
- (void)startPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;
- (void)stopPlayback;

/// Stops live photo playback. If animated is NO, the photo is immediately displayed.
- (void)stopPlaybackAnimated:(BOOL)animated;

/// Directly access the livePhotoBadge in cases where it should be added to a different place in the view hierachy and not the live photo view. This can be useful when the live photo view is added to a scroll view.
@property (readonly, nonatomic, strong, nullable) NSView *livePhotoBadgeView;
@end


OS_EXPORT
@protocol PHLivePhotoViewDelegate <NSObject>
@optional

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView willBeginPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView didEndPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
