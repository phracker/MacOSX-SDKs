//
//  EXAppExtensionBrowserViewController.h
//  ExtensionKit
//

#import <ExtensionFoundation/ExtensionFoundation.h>
#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif // TARGET_OS_OSX

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(18))
API_UNAVAILABLE(watchos)
API_UNAVAILABLE(tvos)
API_UNAVAILABLE(visionos)
EXTENSIONKIT_EXPORT
#if TARGET_OS_OSX
/// A view controller that displays an interface to enable or disable the host
/// app’s extensions.
///
/// When your host app supports app extensions, use this view controller to give
/// people a way to enable or disable those extensions. When you present this view
/// controller, the system displays an out-of-process UI with a list of all app
/// extensions that support your app’s extension points. Someone using your app
/// can use the presented interface to enable or disable extensions selectively.
/// App extensions you include inside your host app’s bundle are enabled by default,
/// but extensions that ship in separate apps are disabled by default.
///
/// Present this view controller modally from your app, or embed the view controller
/// as a child in one of your existing view controller interfaces. For example, you
/// might choose to embed the view controller in a tab of your app’s preferences interface.
@interface EXAppExtensionBrowserViewController : NSViewController
@end
#else
/// A view controller that displays an interface to enable or disable the host
/// app’s extensions.
///
/// When your host app supports app extensions, use this view controller to give
/// people a way to enable or disable those extensions. When you present this view
/// controller, the system displays an out-of-process UI with a list of all app
/// extensions that support your app’s extension points. Someone using your app
/// can use the presented interface to enable or disable extensions selectively.
/// App extensions you include inside your host app’s bundle are enabled by default,
/// but extensions that ship in separate apps are disabled by default.
///
/// Present this view controller modally from your app, or embed the view controller
/// as a child in one of your existing view controller interfaces. For example, you
/// might choose to embed the view controller in a tab of your app’s preferences interface.
@interface EXAppExtensionBrowserViewController : UIViewController
@end
#endif // TARGET_OS_OSX

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_WATCH
