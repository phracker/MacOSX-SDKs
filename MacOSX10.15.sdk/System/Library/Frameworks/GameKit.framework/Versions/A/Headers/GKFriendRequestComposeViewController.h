//
//  GKFriendRequestComposeViewController.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@protocol GKFriendRequestComposeViewControllerDelegate;
@class GKPlayer;


// Standard view controller for sending friend requests to other players. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0) 
@interface GKFriendRequestComposeViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0)
@interface GKFriendRequestComposeViewController : NSViewController <GKViewController> {
    id _remoteViewController;
    id<GKFriendRequestComposeViewControllerDelegate> _composeViewDelegateWeak;
    id _initialState;
    BOOL _internalFlag;
}
@end
#endif

@interface GKFriendRequestComposeViewController ()
// Get the maximum number of recipients permitted
+ (NSUInteger)maxNumberOfRecipients;

// Specify the message sent to the invitee. A default message will be used if you don't specify one.
- (void)setMessage:(nullable NSString *)message;

// Add recipients to the request.
// If you don't specify at least one recipient before presenting the view, the recipients field will be made firstResponder, to encourage the user to add some.
// If you add more than maxNumberOfRecipients recipients, these methods will throw an exception.
- (void)addRecipientPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);
- (void)addRecipientsWithPlayerIDs:(NSArray<NSString *> *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_2, 8_0, "use addRecipientPlayers:") ;
- (void)addRecipientsWithEmailAddresses:(NSArray<NSString *> *)emailAddresses;

@property (nonatomic, assign, nullable) id<GKFriendRequestComposeViewControllerDelegate> composeViewDelegate NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) ;
@end

// Optional delegate
NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) 
@protocol GKFriendRequestComposeViewControllerDelegate
// The compose view has finished
- (void)friendRequestComposeViewControllerDidFinish:(GKFriendRequestComposeViewController *)viewController NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) ;
@end
NS_ASSUME_NONNULL_END
