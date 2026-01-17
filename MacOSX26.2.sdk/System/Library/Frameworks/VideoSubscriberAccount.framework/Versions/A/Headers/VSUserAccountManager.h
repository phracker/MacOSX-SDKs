//
//  VSUserAccountManager.h
//  VideoSubscriberAccountFramework
//
//  Created by Nik Harris on 1/30/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

#import <Foundation/Foundation.h>

@class VSAutoSignInToken;
#if ((TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION) || TARGET_OS_TV)
@class VSAutoSignInTokenUpdateContext;
#endif // ((TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION) || TARGET_OS_TV)
@class VSUserAccount;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSInteger, VSUserAccountQueryOptions) {
    VSUserAccountQueryNone = 0,  // default
    VSUserAccountQueryAllDevices // return VSUserAccounts also registered on other devices in the users iCloud account
} NS_SWIFT_NAME(VSUserAccountManager.QueryOptions) API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst);

VS_EXPORT API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst)
@interface VSUserAccountManager : NSObject

@property (nonatomic, readonly, class) VSUserAccountManager *sharedUserAccountManager;

// Register a new VSUserAccount.
- (void)updateUserAccount:(VSUserAccount *)account completion:(void (^ _Nullable)(NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT;

// Query the registered VSUserAccounts for your application.
// By default, this will return VSUserAccounts registered by your application on the current
// device only. To query the VSUserAccounts registered on all of the devices signed into the
// users iCloud account, use the query flag VSUserAccountQueryAllDevices.
- (void)queryUserAccountsWithOptions:(VSUserAccountQueryOptions)options completion:(void (^)(NSArray<VSUserAccount *> * _Nullable accounts, NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT;


// MARK: Auto Sign In

/// Query the auto sign in token and authorization state.
- (void)queryAutoSignInTokenWithCompletionHandler:(void(^)(VSAutoSignInToken *_Nullable token, NSError *_Nullable error))completion NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), tvos(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, macCatalyst);

#if (TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION) || TARGET_OS_TV

/// Request user authorization to store and use an auto sign in token. An UI prompt will be shown to the user to confirm this action.
/// Make sure to only call this method after your app is signed in:
/// - If the app is already authenticated, check the authorization status by calling `queryAutoSignInTokenWithCompletionHandler:` and only request
/// authorization if the authorization value is `VSAutoSignInAuthorizationNotDetermined`.
/// - If the user is signing in for the first time, or after going through the manual sign in flow again, you should always request authorization.
///
/// @return A `VSAutoSignInTokenUpdateContext` that you pass to `updateAutoSignInToken:updateContext:completionHandler:`.
- (void)requestAutoSignInAuthorizationWithCompletionHandler:(void(^)(VSAutoSignInTokenUpdateContext *_Nullable updateContext, NSError *_Nullable error))completion NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(macos, watchos, macCatalyst, visionos);

/// Sets the auto sign in token.
/// You're in full control of your token, it doesn't have any implied expiration dates. Use
/// `-[VSUserAccountManager deleteAutoSignInTokenWithCompletionHandler:]` if you need to remove an old token.
///
/// Before calling this method you have to obtain an update context object using
/// `-[VSUserAccountManager requestAutoSignInAuthorizationWithCompletionHandler:]`. Updating the token will fail if the user hasn't
/// granted authorization.
- (void)updateAutoSignInToken:(NSString *)autoSignInToken updateContext:(VSAutoSignInTokenUpdateContext *)context completionHandler:(void(^)(NSError *_Nullable error))completion NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(macos, watchos, macCatalyst, visionos);

#endif // (TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION) || TARGET_OS_TV

/// Deletes the auto sign in token.
- (void)deleteAutoSignInTokenWithCompletionHandler:(void(^)(NSError *_Nullable error))completion NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0), tvos(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, macCatalyst);


@end

NS_ASSUME_NONNULL_END
