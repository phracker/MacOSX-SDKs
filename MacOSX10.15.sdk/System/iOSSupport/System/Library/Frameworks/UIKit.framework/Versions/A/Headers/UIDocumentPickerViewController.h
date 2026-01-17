#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocumentPickerViewController.h>)
//
//  UIDocumentPickerViewController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
	
NS_ASSUME_NONNULL_BEGIN

@class UIDocumentPickerViewController, UIDocumentMenuViewController;

API_UNAVAILABLE(tvos) @protocol UIDocumentPickerDelegate <NSObject>

@optional

- (void)documentPicker:(UIDocumentPickerViewController *)controller didPickDocumentsAtURLs:(NSArray <NSURL *>*)urls API_AVAILABLE(ios(11.0));

// called if the user dismisses the document picker without selecting a document (using the Cancel button)
- (void)documentPickerWasCancelled:(UIDocumentPickerViewController *)controller;

- (void)documentPicker:(UIDocumentPickerViewController *)controller didPickDocumentAtURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("documentPicker:didPickDocumentsAtURLs:", ios(8.0, 11.0));
@end

typedef NS_ENUM(NSUInteger, UIDocumentPickerMode) {
    UIDocumentPickerModeImport,
    UIDocumentPickerModeOpen,
    UIDocumentPickerModeExportToService,
    UIDocumentPickerModeMoveToService
} API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos) @interface UIDocumentPickerViewController : UIViewController

// Initializes the picker instance for selecting a document in a remote location. The valid modes are Import and Open.
- (instancetype)initWithDocumentTypes:(NSArray <NSString *>*)allowedUTIs inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Initializes the picker for exporting a local file to an external location. The valid modes are Export and Move. The new location will be returned using didPickDocumentAtURL:
- (instancetype)initWithURL:(NSURL *)url inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER; // This method will be deprecated in a future release and should be avoided. Instead, use initWithURLs:inMode:.

// Initializes the picker for exporting local files to an external location. The valid modes are Export and Move. The new locations will be returned using didPickDocumentAtURLs:
- (instancetype)initWithURLs:(NSArray <NSURL *> *)urls inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0));

@property (nullable, nonatomic, weak) id<UIDocumentPickerDelegate> delegate;
@property (nonatomic, assign, readonly) UIDocumentPickerMode documentPickerMode;
@property (nonatomic, assign) BOOL allowsMultipleSelection API_AVAILABLE(ios(11.0));

/// Force the display of supported file extensions (default: NO).
@property (assign, nonatomic) BOOL shouldShowFileExtensions API_AVAILABLE(ios(13.0));

/// Picker will try to display this URL when presented
@property (nullable, nonatomic, copy) NSURL *directoryURL API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDocumentPickerViewController.h>
#endif
