//
//  EXHostViewController.h
//  ExtensionKit
//

#import <ExtensionFoundation/ExtensionFoundation.h>
#import <Foundation/Foundation.h>


#if TARGET_OS_OSX || __has_include(<UIKit/UIKit.h>)

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol EXHostViewControllerDelegate;

API_AVAILABLE(macos(13.0), ios(26.0))
API_UNAVAILABLE(watchos, tvos, visionos)
EXTENSIONKIT_EXPORT
#if TARGET_OS_OSX
/// A view controller that hosts remote views provided by an app extension.
///
/// Present this view controller from your app’s interface to display the content for
/// an associated app extension. Configure the view controller with the app extension
/// identity and the specific scene you want to display. Use the associated delegate
/// object to receive notifications when the app extension becomes active or inactive.
///
/// For more information about presenting this view controller and using it to display
/// an app extension’s UI, see
/// <doc://com.apple.documentation/documentation/extensionkit/including-extension-based-ui-in-your-interface>.
@interface EXHostViewController : NSViewController
#else
/// A view controller that hosts remote views provided by an app extension.
///
/// Present this view controller from your app’s interface to display the content for
/// an associated app extension. Configure the view controller with the app extension
/// identity and the specific scene you want to display. Use the associated delegate
/// object to receive notifications when the app extension becomes active or inactive.
///
/// For more information about presenting this view controller and using it to display
/// an app extension’s UI, see
/// <doc://com.apple.documentation/documentation/extensionkit/including-extension-based-ui-in-your-interface>.
@interface EXHostViewController : UIViewController
#endif

/// A custom delegate object you use to receive notifications about the activation
/// and deactivation of the app extension.
@property (weak, nonatomic, nullable) id<EXHostViewControllerDelegate> delegate;

#if TARGET_OS_OSX
/// The view to display when the view controller has no app extension content to display.
@property (strong, nonatomic) NSView* placeholderView;
#else
/// The view to display when the view controller has no app extension content to display.
@property (strong, nonatomic) UIView* placeholderView;
#endif

/// Initiates an XPC connection to the app extension’s scene.
///
/// Call this method from your delegate's ``EXHostViewControllerDelegate/hostViewControllerDidActivate:``
/// method to initiate a scene-specific connection to the app extension. 
///
/// - Returns: An object representing the connection.
-(nullable NSXPCConnection*)makeXPCConnectionWithError:(NSError* __nullable*)error;

@end

API_AVAILABLE(macos(13.0), ios(26.0))
API_UNAVAILABLE(watchos, tvos, visionos)
/// The delegate for a hosted view controller.
@protocol EXHostViewControllerDelegate <NSObject>
@optional

/// Tells the host that the app extension is active and ready to accept an XPC connection.
///
/// The host view controller calls this method after it launches an app extension and
/// connects to its remote scene. Use this method to establish an XPC connection to
/// the newly created UI instance.
///
/// - Parameters:
///    - viewController: The host view controller that initiated the connection.
-(void)hostViewControllerDidActivate:(EXHostViewController*)viewController NS_SWIFT_UI_ACTOR;

/// Tells the host that the app extension disconnected and is no longer available.
///
/// The host view controller calls this method when the app extension exits or when
/// you change the view controller’s ``EXHostViewController/configuration`` property.
/// Use this method to close out the previous connection to the app extension.
///
/// - Parameters:
///    - viewController: The host view controller that initiated the connection.
///    - error: An error object indicating why the app extension disconnected, or `nil`
///    if the extension exited without issues.
-(void)hostViewControllerWillDeactivate:(EXHostViewController*)viewController error:(nullable NSError *)error NS_SWIFT_UI_ACTOR;

@end

NS_ASSUME_NONNULL_END

#endif
