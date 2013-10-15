/*
 *  GKFriendRequestComposeViewController.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 */

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@protocol GKFriendRequestComposeViewControllerDelegate;

// Standard view controller for sending friend requests to other players. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 4_2)
@interface GKFriendRequestComposeViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, NA)
@interface GKFriendRequestComposeViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@end
#endif

@interface GKFriendRequestComposeViewController ()
// Get the maximum number of recipients permitted
+ (NSUInteger)maxNumberOfRecipients;

// Specify the message sent to the invitee. A default message will be used if you don't specify one.
- (void)setMessage:(NSString *)message;

// Add recipients to the request.
// If you don't specify at least one recipient before presenting the view, the recipients field will be made firstResponder, to encourage the user to add some.
// If you add more than maxNumberOfRecipients recipients, these methods will throw an exception.
- (void)addRecipientsWithPlayerIDs:(NSArray *)playerIDs;
- (void)addRecipientsWithEmailAddresses:(NSArray *)emailAddresses;

@property (assign, NS_NONATOMIC_IOSONLY) id<GKFriendRequestComposeViewControllerDelegate> composeViewDelegate;
@end

// Optional delegate
@protocol GKFriendRequestComposeViewControllerDelegate
// The compose view has finished
- (void)friendRequestComposeViewControllerDidFinish:(GKFriendRequestComposeViewController *)viewController;
@end
