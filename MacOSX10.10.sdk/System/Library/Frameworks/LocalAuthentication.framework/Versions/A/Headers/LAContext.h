//
//  LAContext.h
//  LocalAuthentication
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAPublicDefines.h>

typedef NS_ENUM(NSInteger, LAPolicy)
{
    /// Device owner was authenticated using a biometric method.
    /// @discussion Biometrics (Touch ID) authentication is required. If Touch ID is not available or
    ///             not enabled, policy evaluation will fail.
    ///             Touch ID authentication dialog contains a cancel button and a fallback button with
    ///             default title "Enter Password" which can be customized using localizedFallbackTitle
    ///             property.
    LAPolicyDeviceOwnerAuthenticationWithBiometrics NS_ENUM_AVAILABLE(NA, 8_0) = kLAPolicyDeviceOwnerAuthenticationWithBiometrics 
}NS_ENUM_AVAILABLE(10_10, 8_0);

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
- (BOOL)canEvaluatePolicy:(LAPolicy)policy error:(NSError * __autoreleasing *)error;

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
                 reply:(void(^)(BOOL success, NSError *error))reply;

/// Fallback button title.
/// @discussion Allows fallback button title customization. A default title "Enter Password" is used when
///             this property is left nil. If set to empty string, the button will be hidden.
@property (nonatomic, copy) NSString *localizedFallbackTitle;

@end
