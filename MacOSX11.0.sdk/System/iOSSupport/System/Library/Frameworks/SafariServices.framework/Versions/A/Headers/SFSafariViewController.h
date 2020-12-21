//
//  SFSafariViewController.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSafariViewControllerConfiguration;
@protocol SFSafariViewControllerDelegate;

typedef NS_ENUM(NSInteger, SFSafariViewControllerDismissButtonStyle) {
    SFSafariViewControllerDismissButtonStyleDone,
    SFSafariViewControllerDismissButtonStyleClose,
    SFSafariViewControllerDismissButtonStyleCancel,
} API_AVAILABLE(ios(11.0)) NS_SWIFT_NAME(SFSafariViewController.DismissButtonStyle);

/*!
 @class SFSafariViewController
 A view controller for displaying web content in a Safari-like interface with some of Safari’s features.
 */
SF_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos)
@interface SFSafariViewController : UIViewController

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

/*! @abstract Returns a view controller that loads a URL.
    @param URL the initial URL to navigate to. Only supports initial URLs with http:// or https:// schemes.
    @param configuration the configuration for the new view controller.
    @discussion This is a designated initializer. You can use
    @link -initWithURL: @/link to initialize an instance with the default configuration. Mutating the configuration after invoking the initializer has no effect on the view controller.
*/
- (instancetype)initWithURL:(NSURL *)URL configuration:(SFSafariViewControllerConfiguration *)configuration NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0));

/*! @abstract Returns a view controller that loads a URL.
    @param URL the initial URL to navigate to. Only supports initial URLs with http:// or https:// schemes.
    @param entersReaderIfAvailable indicates if the Safari Reader version of content should be shown automatically
    when Safari Reader is available on a web page.
 */
- (instancetype)initWithURL:(NSURL *)URL entersReaderIfAvailable:(BOOL)entersReaderIfAvailable NS_DESIGNATED_INITIALIZER API_DEPRECATED_WITH_REPLACEMENT("-initWithURL:configuration:", ios(9.0, 11.0));

/*! @abstract Returns a view controller that loads a URL.
    @param URL the initial URL to navigate to. Only supports initial URLs with http:// or https:// schemes.
 */
- (instancetype)initWithURL:(NSURL *)URL;

/*! @abstract The view controller's delegate. */
@property (nonatomic, weak, nullable) id <SFSafariViewControllerDelegate> delegate;

/*! @abstract A copy of the configuration with which the view controller was
        initialized. */
@property (nonatomic, readonly, copy) SFSafariViewControllerConfiguration *configuration API_AVAILABLE(ios(11.0));

/*! @abstract The preferred color to tint the background of the navigation bar and toolbar. If SFSafariViewController is in Private
    Browsing mode or is displaying an anti-phishing warning page, this color will be ignored. Changes made after the view controller
    has been presented will not be reflected.
 */
@property (nonatomic, nullable) UIColor *preferredBarTintColor API_AVAILABLE(ios(10.0));

/*! @abstract The preferred color to tint the control buttons on the navigation bar and toolbar. If SFSafariViewController is in Private
    Browsing mode or is displaying an anti-phishing warning page, this color will be ignored. Changes made after the view controller
    has been presented will not be reflected.
 */
@property (nonatomic, nullable) UIColor *preferredControlTintColor API_AVAILABLE(ios(10.0));

/*! @abstract The style of dismiss button to use in the navigation bar to close SFSafariViewController.
    The default value is SFSafariViewControllerDismissButtonStyleDone, which makes the button title the localized
    string "Done". You can use other values such as "Close" to provide consistency with your app. "Cancel" is
    ideal when using SFSafariViewController to log in to an external service. All values will show a string localized
    to the user's locale. Changing this property after SFSafariViewController is presented will animate the change.
 */
@property (nonatomic) SFSafariViewControllerDismissButtonStyle dismissButtonStyle API_AVAILABLE(ios(11.0));

@end

API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos)
@protocol SFSafariViewControllerDelegate <NSObject>
@optional

/*! @abstract Called when the view controller is about to show UIActivityViewController after the user taps the action button.
    @param URL the URL of the web page.
    @param title the title of the web page.
    @result Returns an array of UIActivity instances that will be appended to UIActivityViewController.
 */
- (NSArray<UIActivity *> *)safariViewController:(SFSafariViewController *)controller activityItemsForURL:(NSURL *)URL title:(nullable NSString *)title;

/*! @abstract Allows you to exclude certain UIActivityTypes from the UIActivityViewController presented when the user taps the action button.
    @discussion Called when the view controller is about to show a UIActivityViewController after the user taps the action button.
    @param URL the URL of the current web page.
    @param title the title of the current web page.
    @result Returns an array of any UIActivityType that you want to be excluded from the UIActivityViewController.
 */
- (NSArray<UIActivityType> *)safariViewController:(SFSafariViewController *)controller excludedActivityTypesForURL:(NSURL *)URL title:(nullable NSString *)title API_AVAILABLE(ios(11.0));

/*! @abstract Delegate callback called when the user taps the Done button. Upon this call, the view controller is dismissed modally. */
- (void)safariViewControllerDidFinish:(SFSafariViewController *)controller;

/*! @abstract Invoked when the initial URL load is complete.
    @param didLoadSuccessfully YES if loading completed successfully, NO if loading failed.
    @discussion This method is invoked when SFSafariViewController completes the loading of the URL that you pass
    to its initializer. It is not invoked for any subsequent page loads in the same SFSafariViewController instance.
 */
- (void)safariViewController:(SFSafariViewController *)controller didCompleteInitialLoad:(BOOL)didLoadSuccessfully;

/*! @abstract Called when the browser is redirected to another URL while loading the initial page.
    @param URL The new URL to which the browser was redirected.
    @discussion This method may be called even after -safariViewController:didCompleteInitialLoad: if
    the web page performs additional redirects without user interaction.
 */
- (void)safariViewController:(SFSafariViewController *)controller initialLoadDidRedirectToURL:(NSURL *)URL API_AVAILABLE(ios(11.0));

/*! @abstract Called when the user opens the current page in the default browser by tapping the toolbar button.
 */
- (void)safariViewControllerWillOpenInBrowser:(SFSafariViewController *)controller NS_SWIFT_NAME(safariViewControllerWillOpenInBrowser(_:)) API_AVAILABLE(ios(14.0));

@end

NS_ASSUME_NONNULL_END
