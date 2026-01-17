//
//  MPMoviePlayerViewController.h
//  MediaPlayer
//
//  Copyright 2009-2015 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>

#if MP_HAS_HEADER(UIKit, UIViewController.h)

#import <UIKit/UIViewController.h>

@class MPMoviePlayerController;

MP_DEPRECATED_BEGIN("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0))
MP_UNAVAILABLE_BEGIN(tvos, watchos, macos)

API_UNAVAILABLE(visionos)
@interface MPMoviePlayerViewController : UIViewController

- (instancetype)initWithContentURL:(NSURL *)contentURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MPMoviePlayerController *moviePlayer;

@end

// -----------------------------------------------------------------------------
// UIViewController Additions
// Additions to present a fullscreen movie player as a modal view controller using the standard movie player transition.

API_UNAVAILABLE(visionos)
@interface UIViewController (MPMoviePlayerViewController)

- (void)presentMoviePlayerViewControllerAnimated:(MPMoviePlayerViewController *)moviePlayerViewController MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0));
- (void)dismissMoviePlayerViewControllerAnimated MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0));

@end

MP_UNAVAILABLE_END
MP_DEPRECATED_END

#endif
