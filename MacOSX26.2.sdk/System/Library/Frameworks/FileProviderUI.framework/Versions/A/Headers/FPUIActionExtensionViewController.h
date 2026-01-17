//
//  FPUIActionExtensionViewController.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <FileProviderUI/FPUIBase.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#if __has_include(<FileProvider/FileProvider.h>)
#import <FileProvider/FileProvider.h>
#else
typedef NSString *NSFileProviderItemIdentifier NS_EXTENSIBLE_STRING_ENUM;
#endif

#import <FileProviderUI/FPUIActionExtensionContext.h>

NS_ASSUME_NONNULL_BEGIN

FPUI_AVAILABLE(ios(11.0), macos(10.15))
API_UNAVAILABLE(macCatalyst)
#if TARGET_OS_OSX

/// The custom user interface used to perform a selected action.
///
/// Subclass this view controller to provide the user interface for your
/// actions.
///
/// No matter how many actions you define, your File Provider UI extension has
/// only one ``FPUIActionExtensionViewController`` subclass. When the user
/// selects one of your actions, the system instantiates a copy of your
/// subclass, calls its
/// ``FPUIActionExtensionViewController/prepareForActionWithIdentifier:itemIdentifiers:``
/// method, and presents it to the user.
///
/// Your subclass must do the following:
///
/// - Override the
/// ``FPUIActionExtensionViewController/prepareForActionWithIdentifier:itemIdentifiers:``
/// method to check the action identifiers and present an appropriate user
/// interface for the selected actions.
/// - Provide some sort of feedback, even if
/// the action doesn't require interaction with the user. For example, present a
/// view that quickly fades out and automatically completes the action.
/// - Call the ``FPUIActionExtensionViewController/extensionContext`` object's
/// ``FPUIActionExtensionContext/cancelRequestWithError:`` or
/// ``FPUIActionExtensionContext/completeRequest`` method when the action is
/// finished to complete the action.
@interface FPUIActionExtensionViewController : NSViewController
#else
@interface FPUIActionExtensionViewController : UIViewController
#endif

/// The extension context provided by the host app.
@property (nonatomic, readonly, strong) FPUIActionExtensionContext *extensionContext;

// To be overridden by the subclass

/// Performs any necessary setup or configuration when an authentication error
/// occurs.
///
/// While your file provider is enumerating its content, the system calls this
/// method whenever your file provider returns an
/// <doc://com.apple.documentation/documentation/fileprovider/nsfileprovidererrordomain>
/// error with a
/// <doc://com.apple.documentation/documentation/fileprovider/nsfileprovidererrorcode/nsfileprovidererrornotauthenticated>
/// code. Use this method to present an interface to authenticate the user.
///
/// - Parameters:
///   - error: An object representing the authentication error. Your File Provider
///   extension can pass additional information in the error's
///   <doc://com.apple.documentation/documentation/foundation/nserror/1411580-userinfo>
///   property.
- (void)prepareForError:(NSError *)error NS_SWIFT_NAME( prepare(forError:) );

// To be overridden by the subclass

/// Performs any necessary setup or configuration for the specified action.
///
/// Use this method to prepare a user interface for handling the action. At a
/// minimum, you should display feedback about the action.
///
/// For more information, see <doc:adding-actions-to-the-context-menu>.
///
/// - Parameters:
///   - actionIdentifier: The identifier for the action performed by the user.
///
///   - itemIdentifiers: The identifiers of the items affected by the action.
- (void)prepareForActionWithIdentifier:(NSString *)actionIdentifier itemIdentifiers:(NSArray <NSFileProviderItemIdentifier> *)itemIdentifiers NS_SWIFT_NAME( prepare(forAction:itemIdentifiers:) );
    
@end

NS_ASSUME_NONNULL_END
