#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocumentViewController.h>)
//
//  UIDocumentViewController.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitCore.h>

@class UIDocumentViewControllerLaunchOptions;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos)
@interface UIDocumentViewController : UIViewController

- (instancetype)initWithDocument:(nullable UIDocument *)document;

@property (nonatomic, strong, nullable) UIDocument *document;

/// Properties to configure the view controller when no document is open.
@property (nonatomic, strong) UIDocumentViewControllerLaunchOptions *launchOptions API_AVAILABLE(ios(18.0));

/// When this view controller updates its navigation item, this method will be called, allowing subclasses to apply any kind of customization you might want.
- (void)navigationItemDidUpdate;

/// Opens the current document.
/// This method is optional. If the document is not opened by the time the view controller becomes visible, the view controller will take care of opening the document.
/// If the document is already opened, the completion handler will be called as if opening the document succeeded.
- (void)openDocumentWithCompletionHandler:(void(^)(BOOL success))completionHandler;

/// Notifies subclasses that the specified document was opened. This method will be called by the system after
/// opening the document initially or after the presented document was changed.
- (void)documentDidOpen;


/// MARK: Custom Navigation Items

@property (nonatomic, readonly) UIBarButtonItemGroup *undoRedoItemGroup;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIDocumentViewController.h>
#endif
