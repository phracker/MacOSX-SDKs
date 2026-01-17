#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocumentPickerExtensionViewController.h>)
//
//  UIDocumentPickerExtensionViewController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDocumentPickerViewController.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(8.0))  API_UNAVAILABLE(tvos) @interface UIDocumentPickerExtensionViewController : UIViewController

// The preconditions for the URL passed to dismissGrantingAccessToURL: vary depending on the document picker mode.
// In Import mode, any URL that the extension has access to is valid.
// In Open mode, the URL needs to be on a level below the documentStorageURL returned by the corresponding non-UI extension.
// In Export mode, the URL needs to be below the documentStorageURL and should point to a duplicate of the object at originalURL.
- (void)dismissGrantingAccessToURL:(nullable NSURL *)url;

- (void)prepareForPresentationInMode:(UIDocumentPickerMode)mode;

// only valid after prepareForDocumentSelectionInMode: has been called
@property (nonatomic, readonly, assign) UIDocumentPickerMode documentPickerMode;

// Contains the URL to duplicate if in mode UIDocumentPickerModeExportToService. nil otherwise.
@property (nullable, nonatomic, readonly, copy) NSURL *originalURL;

// Contains the list of valid types if in mode UIDocumentPickerModeImport or UIDocumentPickerModeOpen. nil otherwise.
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *validTypes;

// if a corresponding non-UI picker component is found, these return the values returned by the corresponding methods
// in the non-UI component. Otherwise, they will return the values corresponding to the default implementation of a non-UI picker.
@property (nonatomic, readonly, copy) NSString *providerIdentifier;
@property (nullable, nonatomic, readonly, copy) NSURL *documentStorageURL;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDocumentPickerExtensionViewController.h>
#endif
