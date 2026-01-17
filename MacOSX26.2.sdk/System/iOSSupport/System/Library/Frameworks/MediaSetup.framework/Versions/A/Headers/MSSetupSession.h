//
//  MSSetupSession.h
//  MediaSetup
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSServiceAccount;

/// A window that presents a Media Setup configuration view.
typedef UIWindow * MSPresentationAnchor;

/// A protocol that provides media setup display information to the system.
@protocol MSAuthenticationPresentationContext <NSObject>

/// A window that presents the system’s HomePod configuration view to the user.
///
/// - Returns: The interface element in your app that the system uses to display
/// HomePod configuration information.
- (_Nullable MSPresentationAnchor) presentationAnchor;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macosx, watchos, tvos)
/// An object that manages the transfer of configuration information between
/// your app, the system, your media service, and HomePod speakers.
///
/// An `MSSetupSession` object guides the user through connecting HomePod
/// speakers in their home to your media service. When your iOS app calls
/// ``MSSetupSession/startWithError:``, the session displays a setup view in the
/// window you provide in
/// ``MSAuthenticationPresentationContext/presentationAnchor``. The session
/// embeds your app icon and the ``MSServiceAccount/serviceName`` you provide
/// into this setup view.
///
/// ![A wireframe showing the setup view Media Setup displays to the user, with
/// callouts indicating where your app’s icon and your media service’s name
/// appear.](mssetupsession-1)
///
/// After the user confirms the setup by tapping the “Use in Home” button, the
/// system requests an OAuth 2.0 token from your authentication service and shares
/// the token with HomePod speakers in the user’s home.
@interface MSSetupSession : NSObject

- (instancetype _Null_unspecified)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a new session.
///
/// - Parameters:
///     - serviceAccount: The streaming media service account to set up on a
/// HomePod.
///
/// - Returns:
///  Returns `true` if it successfully presents; otherwise, `false`.
///
/// This method presents user with options to add a service to the home.
- (instancetype)initWithServiceAccount:(MSServiceAccount *)serviceAccount;

/// Initiates the service configuration process.
///
/// This method sends the account details of the streaming media service to the user’s HomePod speakers.
- (BOOL) startWithError:(NSError * _Nullable * _Nullable)error;

/// A delegate that provides media setup display information to the system.
@property (nonatomic, weak) _Nullable id<MSAuthenticationPresentationContext> presentationContext;

/// The streaming media service account for the session to configure.
@property (nonatomic, strong, readonly) MSServiceAccount * account;

@end

NS_ASSUME_NONNULL_END
