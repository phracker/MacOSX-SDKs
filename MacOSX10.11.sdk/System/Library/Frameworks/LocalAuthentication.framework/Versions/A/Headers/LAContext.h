//
//  LAContext.h
//  LocalAuthentication
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAPublicDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, LAPolicy)
{
    /// Device owner was authenticated using a biometric method (Touch ID).
    ///
    /// @discussion Touch ID authentication is required. If Touch ID is not available or not enrolled,
    ///             policy evaluation will fail. If Touch ID is locked out, passcode is required as
    ///             the first step to unlock the Touch ID.
    ///
    ///             Touch ID authentication dialog contains a cancel button and a fallback button with
    ///             default title "Enter Password" which can be customized using localizedFallbackTitle
    ///             property. Fallback button is initially hidden and shows up after first unsuccessful
    ///             Touch ID attempt. Tapping cancel button or fallback button causes evaluatePolicy call
    ///             to fail, returning a distinct error code.
    ///
    ///             Biometric authentication will get locked after 5 unsuccessful attempts. After that,
    ///             users have to unlock it by entering passcode.
    LAPolicyDeviceOwnerAuthenticationWithBiometrics NS_ENUM_AVAILABLE(NA, 8_0) = kLAPolicyDeviceOwnerAuthenticationWithBiometrics,

    /// Device owner was authenticated by Touch ID or device passcode.
    ///
    /// @discussion Touch ID or passcode authentication is required. If Touch ID is available, enrolled and
    ///             not locked out, user is asked for it first, otherwise they are asked to enter device
    ///             passcode. If passcode is not enabled, policy evaluation will fail.
    ///
    ///             Touch ID authentication dialog behaves similarly as the one used by
    ///             LAPolicyDeviceOwnerAuthenticationWithBiometrics. However, instead of "Enter Password"
    ///             button there is "Enter Passcode" button which, when tapped, switches the authentication
    ///             method and allows users to enter device passcode.
    ///
    ///             Passcode authentication will get locked after 6 unsuccessful attempts with progressively
    ///             increased backoff delay.
    LAPolicyDeviceOwnerAuthentication NS_ENUM_AVAILABLE(10_11, 9_0) = kLAPolicyDeviceOwnerAuthentication

} NS_ENUM_AVAILABLE(10_10, 8_0);

/// The maximum value for LAContext touchIDAuthenticationAllowableReuseDuration property.
extern const NSTimeInterval LATouchIDAuthenticationMaximumAllowableReuseDuration NS_AVAILABLE_IOS(9_0);

/// Class that represents an authentication context.
///
/// @discussion This context can be used for evaluating policies.
///
/// @see LAPolicy
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface LAContext : NSObject

/// Determines if a particular policy can be evaluated.
///
/// @discussion Policies can have certain requirements which, when not satisfied, would always cause
///             the policy evaluation to fail. Examples can be a passcode set or a fingerprint
///             enrolled with Touch ID. This method allows easy checking for such conditions.
///
///             Applications should consume the returned value immediately and avoid relying on it
///             for an extensive period of time. At least, it is guaranteed to stay valid until the
///             application enters background.
///
/// @warning    Do not call this method in the reply block of evaluatePolicy:reply: because it could
///             lead to a deadlock.
///
/// @param policy Policy for which the preflight check should be run.
///
/// @param error Optional output parameter which is set to nil if the policy can be evaluated, or it
///              contains error information if policy evaluation is not possible.
///
/// @return YES if the policy can be evaluated, NO otherwise.
- (BOOL)canEvaluatePolicy:(LAPolicy)policy error:(NSError * __autoreleasing *)error __attribute__((swift_error(none)));

/// Evaluates the specified policy.
///
/// @discussion Policy evaluation may involve prompting user for various kinds of interaction
///             or authentication. Actual behavior is dependent on evaluated policy, device type,
///             and can be affected by installed configuration profiles.
///
///             Be sure to keep a strong reference to the context while the evaluation is in progress.
///             Otherwise, an evaluation would be canceled when the context is being deallocated.
///
///             The method does not block. Instead, the caller must provide a reply block to be
///             called asynchronously when evaluation finishes. The block is executed on a private
///             queue internal to the framework in an unspecified threading context. Other than that,
///             no guarantee is made about which queue, thread, or run-loop the block is executed on.
///
///             Implications of successful policy evaluation are policy specific. In general, this
///             operation is not idempotent. Policy evaluation may fail for various reasons, including
///             user cancel, system cancel and others, see LAError codes.
///
/// @param policy Policy to be evaluated.
///
/// @param reply Reply block that is executed when policy evaluation finishes.
///
/// @param localizedReason Application reason for authentication. This string must be provided in correct
///                        localization and should be short and clear. It will be eventually displayed in
///                        the authentication dialog subtitle. A name of the calling application will be
///                        already displayed in title, so it should not be duplicated here.
///
/// @param success Reply parameter that is YES if the policy has been evaluated successfully or NO if
///                the evaluation failed.
///
/// @param error Reply parameter that is nil if the policy has been evaluated successfully, or it contains
///              error information about the evaluation failure.
///
/// @warning localizedReason parameter is mandatory and the call will throw NSInvalidArgumentException if
///          nil or empty string is specified.
///
/// @see LAError
///
/// Typical error codes returned by this call are:
/// @li          LAErrorUserFallback if user tapped the fallback button
/// @li          LAErrorUserCancel if user has tapped the Cancel button
/// @li          LAErrorSystemCancel if some system event interrupted the evaluation (e.g. Home button pressed).
- (void)evaluatePolicy:(LAPolicy)policy
       localizedReason:(NSString *)localizedReason
                 reply:(void(^)(BOOL success, NSError * __nullable error))reply;

/// Invalidates the context.
///
/// @discussion The context is invalidated automatically when it is (auto)released. This method
///             allows invalidating it manually while it is still in scope.
///
///             Invalidation terminates any existing policy evaluation and the respective call will
///             fail with LAErrorAppCancel. After the context has been invalidated, it can not be
///             used for policy evaluation and an attempt to do so will fail with LAErrorInvalidContext.
///
///             Invalidating a context that has been already invalidated has no effect.
- (void)invalidate NS_AVAILABLE(10_11, 9_0);

typedef NS_ENUM(NSInteger, LACredentialType)
{
    /// Password provided by application
    ///
    /// @discussion If not set, LocalAuthentication will ask for the password when necessary. It will use
    ///             its own user interface depending on the evaluated policy or ACL.
    ///             Applications can provide the password using the setCredential method. In such case,
    ///             LocalAuthentication will not show password entry user interface.
    ///             When entered from the LocalAuthentication user interface, the password is stored as
    ///             UTF-8 encoded string.
    LACredentialTypeApplicationPassword = 0,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/// Sets a credential to this context.
///
/// @discussion Some policies allow to bind application-provided credential with them.
///             This method allows credential to be passed to the right context.
///
/// @param credential Credential to be used with subsequent calls. Setting this parameter to nil will remove
///                   any existing credential of the specified type.
///
/// @param type Type of the provided credential.
///
/// @return YES if the credential was set successfully, NO otherwise.
///
- (BOOL)setCredential:(nullable NSData *)credential
                type:(LACredentialType)type NS_AVAILABLE(10_11, 9_0);

/// Reveals if credential was set with this context.
///
/// @param type Type of credential we are asking for.
///
/// @return YES on success, NO otherwise.
///
- (BOOL)isCredentialSet:(LACredentialType)type NS_AVAILABLE(10_11, 9_0);

typedef NS_ENUM(NSInteger, LAAccessControlOperation)
{
    /// Access control will be used for item creation.
    LAAccessControlOperationCreateItem,

    /// Access control will be used for accessing existing item.
    LAAccessControlOperationUseItem,

    /// Access control will be used for key creation.
    LAAccessControlOperationCreateKey,

    /// Access control will be used for accessing existing key.
    LAAccessControlOperationUseKeySign
} NS_ENUM_AVAILABLE(10_11, 9_0);

/// Evaluates access control object for the specified operation.
///
/// @discussion Access control evaluation may involve prompting user for various kinds of interaction
///             or authentication. Actual behavior is dependent on evaluated access control, device type,
///             and can be affected by installed configuration profiles.
///
///             Be sure to keep a strong reference to the context while the evaluation is in progress.
///             Otherwise, an evaluation would be canceled when the context is being deallocated.
///
///             The method does not block. Instead, the caller must provide a reply block to be
///             called asynchronously when evaluation finishes. The block is executed on a private
///             queue internal to the framework in an unspecified threading context. Other than that,
///             no guarantee is made about which queue, thread, or run-loop the block is executed on.
///
///             After successful access control evaluation, the LAContext can be used with keychain operations,
///             so that they do not require user to authenticate.
///
///             Access control evaluation may fail for various reasons, including user cancel, system cancel
///             and others, see LAError codes.
///
/// @param accessControl Access control object that is typically created by SecAccessControlCreateWithFlags.
///
/// @param operation Type of operation the access control will be used with.
///
/// @param localizedReason Application reason for authentication. This string must be provided in correct
///                        localization and should be short and clear. It will be eventually displayed in
///                        the authentication dialog subtitle. A name of the calling application will be
///                        already displayed in title, so it should not be duplicated here.
///
/// @param reply Reply block that is executed when access control evaluation finishes.
///
/// @param success Reply parameter that is YES if the access control has been evaluated successfully or NO
///                if the evaluation failed.
///
/// @param error Reply parameter that is nil if the access control has been evaluated successfully, or it
///              contains error information about the evaluation failure.
///
/// @warning localizedReason parameter is mandatory and the call will throw NSInvalidArgumentException if
///          nil or empty string is specified.
- (void)evaluateAccessControl:(SecAccessControlRef)accessControl
                    operation:(LAAccessControlOperation)operation
              localizedReason:(NSString *)localizedReason
                        reply:(void(^)(BOOL success, NSError * __nullable error))reply
                        NS_AVAILABLE(10_11, 9_0);

/// Fallback button title.
/// @discussion Allows fallback button title customization. A default title "Enter Password" is used when
///             this property is left nil. If set to empty string, the button will be hidden.
@property (nonatomic, nullable, copy) NSString *localizedFallbackTitle;

/// Allows setting the limit for the number of failures during biometric authentication.
///
/// @discussion When the specified limit is exceeded, evaluation of LAPolicyDeviceOwnerAuthenticationWithBiometrics
///             evaluation will fail with LAErrorAuthenticationFailed. By default this property is nil and
///             the biometric authentication fails after 3 wrong attempts.
///
/// @warning Please note that setting this property with high values does not prevent biometry lockout after 5
///          wrong attempts.
@property (nonatomic, nullable) NSNumber *maxBiometryFailures NS_DEPRECATED_IOS(8_3, 9_0);

/// Contains policy domain state.
///
/// @discussion  This property is set only when evaluatePolicy is called and succesful Touch ID authentication
///              was performed, or when canEvaluatePolicy succeeds for a biometric policy.
///              It stays nil for all other cases.
///              If finger database was modified (fingers were removed or added), evaluatedPolicyDomainState
///              data will change. Nature of such database changes cannot be determined
///              but comparing data of evaluatedPolicyDomainState after different evaluatePolicy
///              will reveal the fact database was changed between calls.
@property (nonatomic, nullable, readonly) NSData *evaluatedPolicyDomainState NS_AVAILABLE(10_11, 9_0);

/// Time interval for accepting a successful Touch ID unlock from the past.
///
/// @discussion This property can be set with a time interval in seconds. If the device was successfully unlocked by
///             Touch ID within this time interval, then Touch ID authentication on this context will succeed
///             automatically and the reply block will be called without prompting user for Touch ID.
///
///             The default value is 0, meaning that no previous TouchID authentication can be reused.
///
///             The maximum supported interval is 5 minutes and setting the value beyond 5 minutes does not increase
///             the accepted interval.
///
/// @see LATouchIDAuthenticationMaximumAllowableReuseDuration
@property (nonatomic) NSTimeInterval touchIDAuthenticationAllowableReuseDuration NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
