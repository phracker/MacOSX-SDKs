/*
 *  GKChallengesViewController.h
 *  GameKit
 *
 *  Copyright 2010-2013 Apple Inc. All rights reserved.
 */

#if !TARGET_OS_IPHONE

#import <GameKit/GKGameCenterViewController.h>

@protocol GKChallengesViewControllerDelegate;

// View controller that provides the standard user interface for challenges. Present modally from the top view controller.
#import <GameKit/GKDialogController.h>
NS_DEPRECATED_MAC(10_8, 10_10)
@interface GKChallengesViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@property (weak, NS_NONATOMIC_IOSONLY) id<GKChallengesViewControllerDelegate> challengeDelegate;
@end

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

// Optional delegate
@protocol GKChallengesViewControllerDelegate
@required
// The challenge view has finished
- (void)challengesViewControllerDidFinish:(GKChallengesViewController *)viewController;
@end
#pragma clang diagnostic pop

#endif

