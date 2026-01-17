// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@protocol GKFriendRequestComposeViewControllerDelegate;
@class GKPlayer;


#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
NS_ASSUME_NONNULL_BEGIN

/// Standard view controller for sending friend requests to other players. Present modally from the top view controller.
API_DEPRECATED("No longer supported.", ios(4.2,10.0), macos(10.8,10.12), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos)
@interface GKFriendRequestComposeViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
/// Standard view controller for sending friend requests to other players. Present modally from the top view controller.
API_DEPRECATED("No longer supported.", ios(4.2,10.0), macos(10.8,10.12), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos)
@interface GKFriendRequestComposeViewController : NSViewController <GKViewController>
@end
#endif

API_DEPRECATED("No longer supported.", ios(4.2,10.0), macos(10.8,10.12), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos)
@interface GKFriendRequestComposeViewController ()
/// Get the maximum number of recipients permitted
+ (NSUInteger)maxNumberOfRecipients;

/// Specify the message sent to the invitee. A default message will be used if you don't specify one.
- (void)setMessage:(nullable NSString *)message;

/// Add recipients to the request.
/// If you don't specify at least one recipient before presenting the view, the recipients field will be made firstResponder, to encourage the user to add some.
/// If you add more than maxNumberOfRecipients recipients, these methods will throw an exception.
- (void)addRecipientPlayers:(NSArray<GKPlayer *> *)players API_AVAILABLE(ios(8.0), macos(10.10), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
- (void)addRecipientsWithPlayerIDs:(NSArray<NSString *> *)playerIDs API_DEPRECATED_WITH_REPLACEMENT("Use ``GKFriendRequestComposeViewController/addRecipientPlayers(_:)`` instead.", ios(4.2,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);
- (void)addRecipientsWithEmailAddresses:(NSArray<NSString *> *)emailAddresses;

@property (nonatomic, weak, nullable) id<GKFriendRequestComposeViewControllerDelegate> composeViewDelegate API_DEPRECATED("No longer supported.", ios(4.2,10.0), macos(10.8,10.12), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
@end

/// Optional delegate
API_DEPRECATED("No longer supported.", ios(4.2,10.0), macos(10.8,10.12), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos)
@protocol GKFriendRequestComposeViewControllerDelegate
/// The compose view has finished
- (void)friendRequestComposeViewControllerDidFinish:(GKFriendRequestComposeViewController *)viewController API_DEPRECATED("No longer supported.", ios(4.2,10.0), macos(10.8,10.12), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
@end

NS_ASSUME_NONNULL_END

#endif
