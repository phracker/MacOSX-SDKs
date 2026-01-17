//
//  GKGameSessionSharingViewController.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_TV

#import <UIKit/UIViewController.h> // UIViewController

@class GKGameSession;
@protocol GKGameSessionSharingViewControllerDelegate;


NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("For real-time matches, use GKMatchmakerViewController. For turn-based matches, use GKTurnBasedMatchmakerViewController.", tvos(10.0, 12.0))
@interface GKGameSessionSharingViewController : UIViewController
@property (nonatomic, readonly, strong) GKGameSession *session;
@property (nonatomic, weak, nullable) id<GKGameSessionSharingViewControllerDelegate> delegate;

- (instancetype)initWithSession:(GKGameSession *)session;

@end

API_DEPRECATED("For real-time matches, use GKMatchmakerViewControllerDelegate to receive notifications from the GKMatchmakerViewController. For turn-based matches, use GKTurnBasedMatchmakerViewControllerDelegate and GKLocalPlayerListener to receive notifications from the GKTurnBasedMatchmakerViewController.", tvos(10.0, 12.0))
@protocol GKGameSessionSharingViewControllerDelegate <NSObject>
- (void)sharingViewController:(GKGameSessionSharingViewController *)viewController didFinishWithError:(NSError * __nullable)error;
@end

NS_ASSUME_NONNULL_END


#endif
