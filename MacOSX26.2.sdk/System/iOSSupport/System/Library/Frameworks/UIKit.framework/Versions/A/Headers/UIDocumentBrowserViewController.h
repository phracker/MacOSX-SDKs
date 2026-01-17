#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<DocumentManager/UIDocumentBrowserViewController.h>)
//
//  UIDocumentBrowserViewController.h
//  UIKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIDocument.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitioning.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIDocumentBrowserViewControllerDelegate;
@class UIImage, UIColor, UIActivity, UTType, UIActivityViewController, UIDocumentBrowserAction, UIDocumentBrowserTransitionController;

extern NSErrorDomain const UIDocumentBrowserErrorDomain API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos);
typedef NS_ERROR_ENUM(UIDocumentBrowserErrorDomain, UIDocumentBrowserErrorCode) {
    UIDocumentBrowserErrorGeneric                                                                  = 1,
    UIDocumentBrowserErrorNoLocationAvailable API_AVAILABLE(ios(12.0)) = 2,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos);

typedef NS_ENUM(NSUInteger, UIDocumentBrowserImportMode) {
    UIDocumentBrowserImportModeNone,
    UIDocumentBrowserImportModeCopy,
    UIDocumentBrowserImportModeMove,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos) NS_SWIFT_NAME(UIDocumentBrowserViewController.ImportMode);

typedef NS_ENUM(NSUInteger, UIDocumentBrowserUserInterfaceStyle) {
    UIDocumentBrowserUserInterfaceStyleWhite = 0,
    UIDocumentBrowserUserInterfaceStyleLight,
    UIDocumentBrowserUserInterfaceStyleDark,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos) API_UNAVAILABLE(visionos) NS_SWIFT_NAME(UIDocumentBrowserViewController.BrowserUserInterfaceStyle);

#pragma mark -

/// UIDocumentBrowserViewController is a view controller to browse the files on the user's device or cloud services and open them directly in your application
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos)
@interface UIDocumentBrowserViewController : UIViewController <NSCoding>

/// @param allowedContentTypes  The document types that the user should be able to open. If nil, the types specified via the CFBundleDocumentTypes key in the application plist will be used instead.
- (instancetype)initForOpeningFilesWithContentTypes:(nullable NSArray <NSString *> *)allowedContentTypes NS_DESIGNATED_INITIALIZER API_DEPRECATED_WITH_REPLACEMENT("use initForOpeningContentTypes: instead", ios(11.0,14.0));

/// @param contentTypes  The content types that the user should be able to open. If nil, the types specified via the CFBundleDocumentTypes key in the application plist will be used instead.
- (instancetype)initForOpeningContentTypes:(nullable NSArray <UTType *> *)contentTypes NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(forOpening:)) API_AVAILABLE(ios(14.0));

/// Please use the designated initializers above instead.
- (instancetype)initWithNibName:(nullable NSString *)nibName bundle:(nullable NSBundle *)bundle NS_UNAVAILABLE;

@property (nullable, nonatomic, weak) id <UIDocumentBrowserViewControllerDelegate> delegate;


#pragma mark Behaviors

/// Defaults to YES
@property (assign, nonatomic) BOOL allowsDocumentCreation;

/// The active document creation intent.
@property (nonatomic, readonly, nullable) UIDocumentCreationIntent activeDocumentCreationIntent API_AVAILABLE(ios(18.0));

/// Defaults to NO
@property (assign, nonatomic) BOOL allowsPickingMultipleItems;

@property (readonly, copy, nonatomic) NSArray<NSString *> *allowedContentTypes API_DEPRECATED("allowedContentTypes is no longer supported", ios(11.0, 14.0));

/// Array of content types supported for Recents documents.
/// Default is same as allowedContentTypes.
/// Can be defined via the 'UIDocumentBrowserRecentDocumentContentTypes' key in the app Info.plist.
/// Note that the recentDocumentsContentTypes must be a subset conforming to the types declared in allowedContentTypes.
@property (readonly, copy, nonatomic) NSArray<NSString *> *recentDocumentsContentTypes API_DEPRECATED_WITH_REPLACEMENT("use contentTypesForRecentDocuments instead", ios(11.0,14.0));

/// Array of content types supported for Recents documents.
/// Default is same as content types passed in the designated initializer or as CFBundleDocumentTypes  in the app Info.plist.
/// Can be defined via the 'UIDocumentBrowserRecentDocumentContentTypes' key in the app Info.plist.
/// Note that the contentTypesForRecentDocuments must be a subset conforming to the types passed in the initializer or Info.plist.
@property (readonly, copy, nonatomic) NSArray<UTType *> *contentTypesForRecentDocuments API_AVAILABLE(ios(14.0));

/// Force the display of file extensions (default: NO).
@property (assign, nonatomic) BOOL shouldShowFileExtensions API_AVAILABLE(ios(13.0));

#pragma mark Additional Navigation Bar Buttons

/// An array of buttons that will be added to the existing buttons in the UIDocumentBrowserViewController navigation bar
@property (strong, nonatomic) NSArray <UIBarButtonItem *> *additionalLeadingNavigationBarButtonItems;

/// An array of buttons that will be added to the existing buttons in the UIDocumentBrowserViewController navigation bar
@property (strong, nonatomic) NSArray <UIBarButtonItem *> *additionalTrailingNavigationBarButtonItems;


#pragma mark Reveal Items

/// Called to reveal a document at the URL.
/// Typically called from the application delegate method application:openURL:options:; to let the application present the document.
- (void)revealDocumentAtURL:(NSURL *)url importIfNeeded:(BOOL)importIfNeeded completion:(nullable void(^)(NSURL * _Nullable revealedDocumentURL,  NSError * _Nullable error))completion;


#pragma mark Document Import

/// Allow a document to be imported next to another document.
- (void)importDocumentAtURL:(NSURL *)documentURL nextToDocumentAtURL:(NSURL *)neighbourURL mode:(UIDocumentBrowserImportMode)importMode completionHandler:(void (^)(NSURL * _Nullable, NSError * _Nullable))completion;


#pragma mark Document Renaming

/// Rename a document.
/// If the proposed name is already taken, a different name may be used after confirming with the user.
/// The finalURL and error are available in the completion handler.
- (void)renameDocumentAtURL:(NSURL *)documentURL proposedName:(NSString *)proposedName completionHandler:(void(^)(NSURL *_Nullable finalURL, NSError *_Nullable error))completionHandler API_AVAILABLE(ios(16.0));


#pragma mark Item Presentation

/// A UIDocumentBrowserTransitionController object is used to display a loading indicator, while the application is spending time on time-consuming operations (e.g., loading, parsing, …) after having finished the file download, and before presenting it. To be used together with the UIViewControllerTransitioningDelegate protocol for custom view controller transitions.
- (UIDocumentBrowserTransitionController *)transitionControllerForDocumentAtURL:(NSURL *)documentURL API_AVAILABLE(ios(12.0)) NS_SWIFT_NAME(transitionController(forDocumentAt:));

- (UIDocumentBrowserTransitionController *)transitionControllerForDocumentURL:(NSURL *)documentURL API_DEPRECATED_WITH_REPLACEMENT("transitionControllerForDocumentAtURL:", ios(11.0,12.0)) API_UNAVAILABLE(visionos);


#pragma mark Custom actions

/// Allows clients to add custom actions in the menu and the navigation bar. These actions are contextual to the document items.
@property (copy, nonatomic) NSArray <UIDocumentBrowserAction *> *customActions;

#pragma mark UI Customization

/// Allows clients to customize the look of the browser. Default: UIDocumentBrowserUserInterfaceStyleWhite
@property (assign, nonatomic) UIDocumentBrowserUserInterfaceStyle browserUserInterfaceStyle API_UNAVAILABLE(visionos);

/// Title of the Create Document button (default: "Create Document”).
@property(copy, nonatomic) NSString * localizedCreateDocumentActionTitle API_AVAILABLE(ios(13.0));

/// Aspect ratio of the Create Document button defined as width / height (default: 2/3).
@property(assign, nonatomic) CGFloat defaultDocumentAspectRatio API_AVAILABLE(ios(13.0));

@end


#pragma mark -
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos)
@protocol UIDocumentBrowserViewControllerDelegate <NSObject>

@optional

/// Called when the user validates a selection of items to open or pick.
/// If you have created this document manager to open files, you should then open the document, potentially using a @c UIDocumentBrowserTransitionController for the transition.
- (void)documentBrowser:(UIDocumentBrowserViewController *)controller didPickDocumentURLs:(NSArray <NSURL *> *)documentURLs API_DEPRECATED_WITH_REPLACEMENT("documentBrowser:didPickDocumentsAtURLs:", ios(11.0, 12.0)) API_UNAVAILABLE(visionos);

- (void)documentBrowser:(UIDocumentBrowserViewController *)controller didPickDocumentsAtURLs:(NSArray <NSURL *> *)documentURLs API_AVAILABLE(ios(12.0));


#pragma mark Document Creation Support

/// When the user requests the creation of a new document, this method will be called. The application can then, optionally, present UI
/// it deems appropriate to let the user configure the new document (for example, it could show a list of templates).
/// When done, create an empty document or a copy of your template to a temporary location.
/// Then use the importHandler to pass the document URL to be imported.
/// If the user cancels the document creation, it's still expetected to call importHandler(nil, UIDocumentBrowserImportModeNone).
/// The Document Browser will asynchronously move the document to its final destination and call back one of the following delegate methods:
/// -documentBrowser:didImportDocumentURL:toDestinationURL:
/// -documentBrowser:failedToImportDocumentAtURL:error:
/// The app should wait for the delegate callbacks before presenting the imported document at the destination URL. Usage of UIDocument is recommended.
/// If you do not implement this method, document creation will not be available.
- (void)documentBrowser:(UIDocumentBrowserViewController *)controller didRequestDocumentCreationWithHandler:(void(^)(NSURL *_Nullable urlToImport, UIDocumentBrowserImportMode importMode))importHandler;
- (void)documentBrowser:(UIDocumentBrowserViewController *)controller didImportDocumentAtURL:(NSURL *)sourceURL toDestinationURL:(NSURL *)destinationURL;
- (void)documentBrowser:(UIDocumentBrowserViewController *)controller failedToImportDocumentAtURL:(NSURL *)documentURL error:(NSError * _Nullable)error;

#pragma mark Activities

/// Allows clients to add application specific UIActivity instances
- (NSArray<__kindof UIActivity *> *)documentBrowser:(UIDocumentBrowserViewController *)controller applicationActivitiesForDocumentURLs:(NSArray <NSURL *> *)documentURLs;

/// Implement this to customize the UIActivityViewController before it's presented.
- (void)documentBrowser:(UIDocumentBrowserViewController *)controller willPresentActivityViewController:(UIActivityViewController *)activityViewController;

@end


#pragma mark -

/// Class to handle the loading and animation transition when opening or closing a document.
/// @discussion You can use this object to display a loading indicator if you need time to perform time-consuming operations (loading, parsing, …) after the document download and before presenting it. You can also get a transition controller to pass to UIKit when pushing or presenting your document view
/// in response to @c documentBrowser:didPickItem:, or when popping or dismissing it.
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos)
@interface UIDocumentBrowserTransitionController : NSObject <UIViewControllerAnimatedTransitioning>

- (instancetype)init NS_UNAVAILABLE;

/// An optional progress can be displayed on the document thumbnail while the document is loading (during opening).
@property (strong, nonatomic, nullable) NSProgress *loadingProgress;


/// This view will be used for the zoom transition from/to the document collection view.
/// If UIDocumentBrowserViewController is being dismissed, this view should be a subview of the presented view controller's view
/// If UIDocumentBrowserViewController is being presented, this view should be a subview of the presenting view controller's view
@property (weak, nullable, nonatomic) UIView *targetView;

@end


NS_ASSUME_NONNULL_END

#else
#import <DocumentManager/UIDocumentBrowserViewController.h>
#endif
