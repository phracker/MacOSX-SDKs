#pragma once

#ifdef __OBJC__

#import <xpc/xpc.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum ServiceManagement App Service Status
 *
 * @abstract The values returned by SMAppService:status
 *
 * @const SMAppServiceNotRegistered
 * A service has not been registered with ServiceManagement or that the service was unregistered
 * after it was already registered.
 *
 * @const SMAppServiceEnabled
 * A service has been successfully registered and is eligible to run
 *
 * @const SMAppServiceRequiresApproval
 * A service has been successfully registered, but the user needs to take action in System Settings
 * before the service is eligible to run. This status will be returned if the user revokes consent for the service
 * to run in System Settings
 *
 * @const SMAppServiceNotFound
 * An error occurred and no such service could be found
 */
typedef NS_ENUM(NSInteger, SMAppServiceStatus) {
	SMAppServiceStatusNotRegistered,
	SMAppServiceStatusEnabled,
	SMAppServiceStatusRequiresApproval,
	SMAppServiceStatusNotFound,
} NS_SWIFT_NAME(SMAppService.Status);

XPC_EXPORT
API_AVAILABLE(macos(15.0), macCatalyst(18.0)) API_UNAVAILABLE(ios, tvos, watchos)
NSString * const SMAppServiceErrorDomain;

/*!
 * @abstract
 * An SMAppService is used to control helper executables that live inside of an app's main bundle.
 *
 * @discussion
 * For SMAppServices initialized as LoginItems, the register and unregister APIs provide a replacement for
 * SMLoginItemSetEnabled.
 *
 * Apps that use SMAppService APIs must be code signed.
 *
 * For SMAppServices initialized as LaunchAgents, the register and unregister APIs provide a replacement
 * for installing plists in ~/Library/LaunchAgents or /Library/LaunchAgents.
 *
 * For SMAppServices initialized as LaunchDaemons, the register and unregister APIs provide a replacement
 * for installing plists in /Library/LaunchDaemons. Apps that contain LaunchDaemons must be notarized.
 *
 * Legacy LaunchDaemons installed in /Library/LaunchDaemons will continue to be bootstrapped without
 * explicit approval in System Settings since writing to /Library is protected  with filesystem permissions.
 *
 * If an app updates either the plist or the executable for a LaunchAgent or LaunchDaemon, the SMAppService
 * must be re-registered or it may not launch. It is recommended to also call unregister before
 * re-registering if the executable has been changed.
 */
XPC_EXPORT
API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos, watchos)
@interface SMAppService : NSObject

/*!
 * @method loginItemServiceWithIdentifier
 *
 * @abstract
 * Initializes a SMAppService for a LoginItem corresponding to the bundle with the specified identifier.
 *
 * @param identifier
 * The bundle identifier of the helper application
 *
 * @discussion
 * The identifier must correspond to the bundle identifier for a LoginItem that lives in the calling app's
 * Contents/Library/LoginItems directory
 */
+ (instancetype)loginItemServiceWithIdentifier:(NSString *)identifier NS_SWIFT_NAME(loginItem(identifier:)) API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @property mainAppService
 *
 * @abstract
 * A SMAppService corresponding to the main application as a LoginItem
 *
 * This SMAppService can be used to configure the main app to be launched at login
 */
@property (class, readonly) SMAppService *mainAppService NS_SWIFT_NAME(mainApp) API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @method agentServiceWithPlistName
 *
 * @abstract
 * Initializes a SMAppService with a LaunchAgent with the specified plist name.
 *
 * @param plistName
 * The name of the plist corresponding to the SMAppService.
 *
 * @discussion
 * The plistName must correspond to a plist in the calling app's Contents/Library/LaunchAgents directory
 *
 * In addition to the standard launchd.plist keys, plists registered with SMAppService may use the
 * BundleProgram launchd plist key to specify an app bundle relative path for the executable. This key allows
 * apps to support a user relocating the app bundle after installation.
 */
+ (instancetype)agentServiceWithPlistName:(NSString *)plistName NS_SWIFT_NAME(agent(plistName:)) API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @method daemonServiceWithPlistName
 *
 * @abstract
 * Initializes a SMAppService with a LaunchDaemon with the specified plist name.
 *
 * @param plistName
 * The name of the plist corresponding to the SMAppService.
 *
 * @discussion
 * The plistName must correspond to a plist in the calling app's Contents/Library/LaunchDaemons directory
 *
 * In addition to the standard launchd.plist keys, plists registered with SMAppService may use the
 * BundleProgram launchd plist key to specify an app bundle relative path for the executable. This key allows
 * apps to support a user relocating the app bundle after installation.
 *
 * For a LaunchDaemon to be bootstrapped during boot, the containing application must be accessible before
 * a user logs in. For applications that intend to register LaunchDaemons, it is recommended that the
 * application bundle live in /Applications
 */
+ (instancetype)daemonServiceWithPlistName:(NSString *)plistName NS_SWIFT_NAME(daemon(plistName:)) API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @method registerAndReturnError
 *
 * @abstract
 * Registers the service such that it may begin launching subject to user consent
 *
 * @param error
 * Upon unsuccessful return, a new NSError object describing the error. Upon successful return, this
 * argument is set to NULL. This argument may be NULL.
 *
 * @result
 * YES if the service was successfully registered, otherwise NO.
 *
 * @discussion
 * If the service corresponds to a LoginItem bundle, the helper will be started immediately and on subsequent
 * logins. If the helper crashes or exits non-zero it will be relaunched.
 *
 * If the service corresponds to the main application, the application will be launched on subsequent logins.
 *
 * If the service corresponds to a LaunchAgent, the LaunchAgent is immediately bootstrapped and may
 * begin running. In addition LaunchAgents registered with this API will be bootstrapped on each subsequent
 * login.
 *
 * If an app desires to register a LaunchAgent for multiple users, the API must be called once per user while
 * the desired user is running the app. LaunchAgents cannot be registered from outside a user context
 * using this API.
 *
 * If the service corresponds to a LaunchDaemon, the LaunchDaemon will not be bootstrapped until an
 * admin approves the LaunchDaemon in System Settings. LaunchDaemons registered with this API
 * and approved by an admin will be bootstrapped on each subsequent boot.
 *
 * If the service is already registered, this API will return error kSMErrorAlreadyRegistered
 *
 * If the service is not approved by the user, this API will return error kSMErrorLaunchDeniedByUser
 *
 * If the app bundle is not properly code signed, this API will return error kSMErrorInvalidSignature 
 *
 * @see SMAppService:unregisterAndReturnError
 */
- (BOOL)registerAndReturnError:(NSError * _Nullable __autoreleasing * _Nullable)error API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @method unregisterAndReturnError
 *
 * @abstract
 * Unregisters the service such that it will no longer be launched by the system.
 *
 * @param error
 * Upon unsuccessful return, a new NSError object describing the error. Upon successful return, this
 * argument is set to NULL. This argument may be NULL.
 *
 * @result
 * YES if the service was successfully unregistered, otherwise NO.
 *
 * @discussion
 * If the service corresponds to a LoginItem, LaunchAgent, or LaunchDaemon and the service is currently
 * running it will be killed. The unregister call will not wait for the service to be reaped.
 *
 * If the service corresponds to the main application, it will continue running, but will still be unregistered to
 * prevent future launches at login.
 *
 * This is the opposite operation of SMAppService:register
 *
 * If the service is already unregistered, this API will return error kSMErrorJobNotFound
 *
 * @see SMAppService:registerAndReturnError
 *
 */
- (BOOL)unregisterAndReturnError:(NSError * _Nullable __autoreleasing * _Nullable)error API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @method unregisterWithCompletionHandler
 *
 * @abstract
 * Unregisters the service such that it will no longer be launched by the system.
 *
 * @param handler
 * The completion handler block to be invoked with the result of the unregister operation. This handler
 * will be invoked on libdispatch's default target queue
 *
 * @discussion
 * If the service corresponds to a LoginItem, LaunchAgent, or LaunchDaemon and the service is currently
 * running it will be killed. The unregister call will not wait for the service to be killed and will return promptly.
 * The completion handler will be invoked after the running process has been killed if successful or will be
 * invoked whenever an error occurs. After the completion handler has been invoked it is safe to re-register the
 * service.
 *
 * If the service corresponds to the main application, it will continue running, but will still be unregistered to
 * prevent future launches at login.
 *
 * This is the opposite operation of SMAppService:register
 *
 * This is the asynchronous variant of SMAppService:unregisterAndReturnError
 *
 * If the service is already unregistered, this API will return error kSMErrorJobNotFound
 *
 * @see SMAppService:unregisterAndReturnError
 *
 */
- (void)unregisterWithCompletionHandler:(void (^)(NSError * _Nullable error))handler API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @property status
 *
 * @abstract
 * Returns the status for the service
 *
 * @discussion
 * The status API can be used to check what selection a user has made regarding allowing the service
 * to launch.
 *
 * If the user has denied execution, the return value will be SMAppServiceRequiresApproval.
 *
 * If the service has been unregistered, the return value will be SMAppServiceNotRegistered
 */
@property (readonly) SMAppServiceStatus status API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*
 * @method statusForLegacyURL
 *
 * @abstract
 * Returns the status for a legacy service
 *
 * @param url
 * A URL pointing to a legacy service plist
 *
 * @discussion
 * Valid URLs have the prefix /Library/LaunchDaemons /Library/LaunchAgents or
 * /Users/$USER/Library/LaunchAgents
 *
 * This API is intended for apps that are unable to adopt the new daemon and agent packaging guidelines
 * but still want to know when a user disables its legacy daemons or agents.
 *
 * As a best practice, apps can check the status of their helpers when they are launched and should
 * also check the status of their helpers when handling XPC connection errors to help determine if the
 * cause of the error is because a user disabled a helper.
 */
+ (SMAppServiceStatus)statusForLegacyURL:(NSURL *)url NS_SWIFT_NAME(statusForLegacyPlist(at:)) API_AVAILABLE(macos(13.0), macCatalyst(16.0));

/*!
 * @method openSystemSettingsLoginItems
 *
 * @abstract
 * Opens System Settings to the Login Items panel
 *
 * @discussion
 * This API is intended for apps to call whenever they present a prompt to the user and the user
 * confirms that they want to enable the app's helpers again. The app can call this API to help
 * the user navigate to the appropriate panel in System Settings.
 */
+ (void)openSystemSettingsLoginItems API_AVAILABLE(macos(13.0), macCatalyst(16.0));

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
