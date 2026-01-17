// Copyright © 2023 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A helper class to provide static utility methods for quick access to settings related to credential providers.
API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASSettingsHelper : NSObject

/// Calling this method will open the Settings app and navigate directly to the AutoFill provider settings.
+ (void)openCredentialProviderAppSettingsWithCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(openCredentialProviderAppSettings());

/// Calling this method will open the Settings app and navigate directly to the Verification Code provider settings.
+ (void)openVerificationCodeAppSettingsWithCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(openVerificationCodeAppSettings());

/// Call this method from your containing app to request to turn on a contained Credential Provider Extension.
/// If the extension is not currently enabled, a prompt will be shown to allow it to be turned on.
/// The completion handler is called with YES or NO depending on whether the credential provider is enabled.
/// You need to wait 10 seconds in order to make additional request to this API.
+ (void)requestToTurnOnCredentialProviderExtensionWithCompletionHandler:(void (^)(BOOL appWasEnabledForAutoFill))completionHandler API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
