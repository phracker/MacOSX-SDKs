//
//  VSAccountManager.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSDictionary<KeyType, ValueType>;
@class NSString;
@class NSError;
@class UIViewController;
@class VSAccountManagerResult;
@class VSAccountMetadata;
@class VSAccountMetadataRequest;

@protocol VSAccountManagerDelegate;

/// Represents the current state of the application's access to the user's subscription information.
typedef NS_ENUM(NSInteger, VSAccountAccessStatus)
{
    VSAccountAccessStatusNotDetermined = 0, // The user has not yet made a choice about whether to allow this access to the app.
    VSAccountAccessStatusRestricted = 1, // Restrictions, e.g. parental controls, prohibit the user from allowing access to the app.
    VSAccountAccessStatusDenied = 2, // The user has explicitly decided to not allow the app to access subscription information.
    VSAccountAccessStatusGranted = 3, // The user has currently decided to allow the app to access subscription information.
}
API_AVAILABLE(ios(10.0), tvos(10.0));

/// Options that may be provided when checking access status.
typedef NSString * VSCheckAccessOption NS_STRING_ENUM
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A boolean indicating whether the user may be prompted to grant access.
VS_EXTERN VSCheckAccessOption const VSCheckAccessOptionPrompt
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A VSAccountManager instance coordinates access to a subscriber's account.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0))
@interface VSAccountManager : NSObject

/// An object that can help the account manager by presenting and dismissing view controllers when needed, and deciding whether to allow authentication with the selected provider.
/// Some requests may fail if a delegate is not provided.  For example, an account metadata request may require a delegate if it allows interruption.
@property (nonatomic, weak) id<VSAccountManagerDelegate> delegate;

/// Determine the state of the application's access to the user's subscription information.
/// @param options The only currently supported option key is VSCheckAccessOptionPrompt.
/// @param completionHandler A block to be called when the request finishes.  It will always be called exactly once.  It may be called before the method call returns.  It may be called on any queue.
/// @param accessStatus The current state the application's access to the user's subscription information.
/// @param error If the user did not grant access to the app, this will contain an error describing the result of the operation.
- (void)checkAccessStatusWithOptions:(NSDictionary<VSCheckAccessOption, id> *)options completionHandler:(void (^)(VSAccountAccessStatus accessStatus, NSError * _Nullable error))completionHandler  API_UNAVAILABLE(macos);

/// Begins requesting information about the subscriber's account.
/// @param request This identifies what specific information the app wants to know.
/// @param completionHandler A block to be called when the request finishes.  It will always be called exactly once.  It may be called before the method call returns.  It may be called on any queue.
/// @param metadata If the request finished successfully, this will contain information about the subscriber's account.
/// @param error If the request did not finish successfully, this will contain an error describing the result of the operation.
/// @returns A result object that may be used to cancel the in-flight request.  Cancellation is advisory, and does not guarantee that the request will finish immediately.
- (VSAccountManagerResult *)enqueueAccountMetadataRequest:(VSAccountMetadataRequest *)request completionHandler:(void (^)(VSAccountMetadata * _Nullable metadata, NSError * _Nullable error))completionHandler  API_UNAVAILABLE(macos);

@end


/// A VSAccountManager instance coordinates access to a subscriber's account.
API_AVAILABLE(ios(10.0), tvos(10.0))
@protocol VSAccountManagerDelegate <NSObject>

@required

/// Called when the account manager needs user interaction to complete a request.
/// @param accountManager The account manager instance that needs to show the view controller.
/// @param viewController A view controller that needs to be presented to the user.  You must use -presentViewController:animated:completion: to begin presenting this view controller before returning from this method.
- (void)accountManager:(VSAccountManager *)accountManager presentViewController:(UIViewController *)viewController;

/// Called when the account manager is finished using the presented view controller.
/// @param accountManager The account manager instance that previously asked to show the view controller.
/// @param viewController The view controller that is being presented to the user.  You must use -dismissViewControllerAnimated:completion: to begin dismissing the view controller before returning from this method.
- (void)accountManager:(VSAccountManager *)accountManager dismissViewController:(UIViewController *)viewController;

@optional

/// This method can be used to temporarily refrain from authenticating with an
/// otherwise-supported provider during a transient outage.
/// This method will be called when the user chooses a supported provider from
/// the list of providers.
/// If you do not implement this method, the user will be able to authenticate
/// with all supported providers.
/// @param accountManager The account manager instance that received a metadata request.
/// @param accountProviderIdentifier Identifies the otherwise-supported account provider.
/// @returns Returning NO will cause the request will fail with an unsupported provider error.
- (BOOL)accountManager:(VSAccountManager *)accountManager shouldAuthenticateAccountProviderWithIdentifier:(NSString *)accountProviderIdentifier;

@end

NS_ASSUME_NONNULL_END
