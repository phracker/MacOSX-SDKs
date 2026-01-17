//
//  MPMoviePlayerViewController.h
//  MediaPlayer
//
//  Copyright 2009-2015 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#if MP_HAS_UIVIEW
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>

@class MPMoviePlayerController;

MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0))
MP_PROHIBITED(tvos, watchos)
@interface MPMoviePlayerViewController : UIViewController

- (instancetype)initWithContentURL:(NSURL *)contentURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MPMoviePlayerController *moviePlayer;

@end

// -----------------------------------------------------------------------------
// UIViewController Additions
// Additions to present a fullscreen movie player as a modal view controller using the standard movie player transition.

@interface UIViewController (MPMoviePlayerViewController)

- (void)presentMoviePlayerViewControllerAnimated:(MPMoviePlayerViewController *)moviePlayerViewController MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
- (void)dismissMoviePlayerViewControllerAnimated MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

@end
#endif
