//  SystemExtensions.h
//  Copyright © 2019-2020 Apple Inc. All rights reserved.

#ifndef __SYSTEM_EXTENSIONS_H__
#define __SYSTEM_EXTENSIONS_H__

#import <Foundation/Foundation.h>

__BEGIN_DECLS
NS_ASSUME_NONNULL_BEGIN

@protocol OSSystemExtensionRequestDelegate;

OS_EXPORT API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NSErrorDomain const OSSystemExtensionErrorDomain;

/*!
 @brief A property of a Driver Extension bundle containing a message that tells
 the user why the app is requesting to install it.

 @discussion The 'OSBundleUsageDescription' key is required in your Driver
 Extension if your app uses APIs that install them.
 */
OS_EXPORT API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NSString* const OSBundleUsageDescriptionKey;

/*!
 @brief A property of a System Extension bundle containing a message that tells
 the user why the app is requesting to install it.

 @discussion The 'NSSystemExtensionUsageDescription' key is required in your
 System Extension if your app uses APIs that install them.
 */
OS_EXPORT API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NSString* const NSSystemExtensionUsageDescriptionKey;

typedef NS_ERROR_ENUM(OSSystemExtensionErrorDomain, OSSystemExtensionErrorCode) {
    OSSystemExtensionErrorUnknown = 1,
    OSSystemExtensionErrorMissingEntitlement = 2,
    OSSystemExtensionErrorUnsupportedParentBundleLocation = 3,
    OSSystemExtensionErrorExtensionNotFound = 4,
    OSSystemExtensionErrorExtensionMissingIdentifier = 5,
    OSSystemExtensionErrorDuplicateExtensionIdentifer = 6,
    OSSystemExtensionErrorUnknownExtensionCategory = 7,
    OSSystemExtensionErrorCodeSignatureInvalid = 8,
    OSSystemExtensionErrorValidationFailed = 9,
    OSSystemExtensionErrorForbiddenBySystemPolicy = 10,
    OSSystemExtensionErrorRequestCanceled = 11,
    OSSystemExtensionErrorRequestSuperseded = 12,
    OSSystemExtensionErrorAuthorizationRequired = 13,
} NS_ENUM_AVAILABLE_MAC(10.15);

typedef NS_ENUM(NSInteger, OSSystemExtensionReplacementAction) {
    /// Returned by the delegate when it determines that replacing an existing
    /// System Extension should not proceed.
    OSSystemExtensionReplacementActionCancel,

    /// Returned by the delegate when it determines that replacing an existing
    /// System Extension is desired.
    OSSystemExtensionReplacementActionReplace,
} NS_SWIFT_NAME(OSSystemExtensionRequest.ReplacementAction) NS_ENUM_AVAILABLE_MAC(10.15);

/// Describes additional result feedback after completion of a system extension request
typedef NS_ENUM(NSInteger, OSSystemExtensionRequestResult) {
    /// The request was successfully completed.
    OSSystemExtensionRequestCompleted,

    /// The request will be successfully completed after a reboot.
    OSSystemExtensionRequestWillCompleteAfterReboot,
} NS_SWIFT_NAME(OSSystemExtensionRequest.Result) NS_ENUM_AVAILABLE_MAC(10.15);

OS_EXPORT API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface OSSystemExtensionRequest : NSObject

/*!
 @brief Creates a request to activate a System Extension.

 @discussion This method creates a new request to activate a System Extension.
 Extensions are bundles discovered from the `Contents/Library/SystemExtensions`
 directory of the main application bundle.

 @param identifier The bundle identifier of the target extension.

 @param queue The dispatch queue to use when calling delegate methods.

 @return A new extension request.

 @note It is expected that an application create and submit an activation
 request whenever an extension should be active. Upon submitting an activation
 request for an inactive extension, user approval may be required and the
 request will not succeed until approval is given.

 If the extension is already active then the request will succeed in short
 order without significant delay or user interaction. Activating an new version
 of an already active extension will prompt the delegate to resolve the conflict
 before proceeding.

 An activation request can be successful but also indicate that a reboot is
 required in order for the extension to become active. This can occur when
 replacing an existing extension that required a reboot in order to deactivate.
 The most recently activated extension will then become active when the system
 is next rebooted.
 */
+ (instancetype)activationRequestForExtension:(NSString *)identifier queue:(dispatch_queue_t)queue NS_SWIFT_NAME(activationRequest(forExtensionWithIdentifier:queue:)) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief Creates a request to deactivate a System Extension.

 @discussion This method creates a new request to deactivate a System Extension.
 Extensions are discovered from the `Contents/Library/SystemExtensions`
 directory of the main application bundle.

 @param identifier The bundle identifier of the target extension.

 @param queue The dispatch queue to use when calling delegate methods.

 @note It is possible for an extension to require a reboot before it is fully
 deactivated. If a request succeeds and indicates a reboot is required, the
 extension may still appear to be operational until that time.
 */
+ (instancetype)deactivationRequestForExtension:(NSString *)identifier queue:(dispatch_queue_t)queue NS_SWIFT_NAME(deactivationRequest(forExtensionWithIdentifier:queue:)) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief A delegate to receive updates about the progress of a request
 */
@property (weak, nonatomic) id<OSSystemExtensionRequestDelegate> delegate API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief The bundle identifier of the target extension
 */
@property (readonly, nonatomic) NSString *identifier API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

OS_EXPORT API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface OSSystemExtensionProperties : NSObject
/*!
 @brief The file URL locating an indicating the extension bundle these properties
 were retreived from.
 */
@property (strong, readonly) NSURL *URL API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief The bundle identifier of the extension (CFBundleIdentifier)
 */
@property (strong, readonly) NSString *bundleIdentifier API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief The bundle version of the extension (CFBundleVersion)
 */
@property (strong, readonly) NSString *bundleVersion API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief The bundle short version string of the extension (CFBundleShortVersionString)
 */
@property (strong, readonly) NSString *bundleShortVersion API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);
@end

API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@protocol OSSystemExtensionRequestDelegate <NSObject>
@required
/*!
 @brief Called when the target extension bundle identifier is already activated.

 @discussion The delegate will receive this callback when an activation request
 encounters an existing extension with the same team and bundle identifiers but
 with different version identifiers. The delegate must make a decision on
 whether or not to replace the existing extension.

 @param request The request that encountered the conflict

 @param existing The NSBundle of the existing extension

 @param ext The NSBundle of the extension matching the bundle identifier of the request

 @return A replacement action indicating the desired outcome of the conflict

 @note This method is invoked if the `CFBundleVersion` or `CFBundleShortVersionString`
 identifiers of the target and existing extension differ.

 If the local system has System Extension developer mode enabled, this callback
 will always fire when an existing extension is found, regardless of version
 identifiers.

 Returning OSSystemExtensionReplacementActionAbortRequest will trigger a callback
 to `request:didFailWithError:` with the OSSystemExtensionErrorRequestCanceled
 error code.
 */
- (OSSystemExtensionReplacementAction)request:(OSSystemExtensionRequest *)request actionForReplacingExtension:(OSSystemExtensionProperties *)existing withExtension:(OSSystemExtensionProperties *)ext API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief Called when the target extension requires user approval to be activated.

 @discussion Activating an extension may require explicit user approval in order
 to proceed. For example, this can occur when the user has never previously
 approved this extension. If approval is necessary, this callback will be
 triggered and the activation request will remain pending until user approves,
 or until the application exits.
 */
- (void)requestNeedsUserApproval:(OSSystemExtensionRequest *)request API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @brief Called when the target extension request has completed.

 @discussion Successful results can come with additional information regarding
 the manner in which they were completed. See the OSSystemExtensionRequestResult
 documentation for more information.

 @param result Additional result information from the completed request.

 @note If the request completes with the `OSSystemExtensionRequestWillCompleteAfterReboot`
 result, then the extension will not be active until after the next reboot. Upon
 reboot, a given extension will be in the state dictated by the most recently
 processed request.
 */
- (void)request:(OSSystemExtensionRequest *)request didFinishWithResult:(OSSystemExtensionRequestResult)result NS_SWIFT_NAME(request(_:didFinishWithResult:)) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Called when the target extension request failed.
 */
- (void)request:(OSSystemExtensionRequest *)request didFailWithError:(NSError *)error API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);
@end

OS_EXPORT API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface OSSystemExtensionManager : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

@property (class, readonly) OSSystemExtensionManager *sharedManager API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Submits a System Extension request to the manager.

 @param request The request to process.
 */
- (void)submitRequest:(OSSystemExtensionRequest *)request API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
__END_DECLS

#endif // __SYSTEM_EXTENSIONS_H__
