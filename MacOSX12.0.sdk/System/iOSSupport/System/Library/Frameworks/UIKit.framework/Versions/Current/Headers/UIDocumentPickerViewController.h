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

@class UIDocumentPickerViewController, UIDocumentMenuViewController, UTType;

API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@protocol UIDocumentPickerDelegate <NSObject>

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
} API_DEPRECATED("Use appropriate initializers instead",ios(8.0,14.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIDocumentPickerViewController : UIViewController

// Initializes the picker instance for selecting a document in a remote location. The valid modes are Import and Open.
- (instancetype)initWithDocumentTypes:(NSArray <NSString *>*)allowedUTIs inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER API_DEPRECATED_WITH_REPLACEMENT("use initForOpeningContentTypes:asCopy: or initForOpeningContentTypes: instead", ios(8.0, 14.0)) API_UNAVAILABLE(tvos);

/// Initializes the picker instance for selecting a document in a remote location.
/// @param asCopy if true, the picker will give you access to a local copy of the document, otherwise you will have access to the original document
- (instancetype)initForOpeningContentTypes:(NSArray <UTType *>*)contentTypes asCopy:(BOOL)asCopy NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos);

/// Initializes the picker instance for selecting a document in a remote location, giving you access to the original document.
- (instancetype)initForOpeningContentTypes:(NSArray <UTType *>*)contentTypes API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos);
              
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
             
// Initializes the picker for exporting a local file to an external location. The valid modes are Export and Move. The new location will be returned using `didPickDocumentAtURL:`.
- (instancetype)initWithURL:(NSURL *)url inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER API_DEPRECATED_WITH_REPLACEMENT("use initForExportingURLs:asCopy: or initForExportingURLs: instead", ios(8.0, 14.0)) API_UNAVAILABLE(tvos);

// Initializes the picker for exporting local files to an external location. The valid modes are Export and Move. The new locations will be returned using `didPickDocumentAtURLs:`.
- (instancetype)initWithURLs:(NSArray <NSURL *> *)urls inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER API_DEPRECATED_WITH_REPLACEMENT("use initForExportingURLs:asCopy: or initForExportingURLs: instead", ios(11.0, 14.0)) API_UNAVAILABLE(tvos);
   
/// Initializes the picker for exporting local documents to an external location. The new locations will be returned using `didPickDocumentAtURLs:`.
/// @param asCopy if true, a copy will be exported to the destination, otherwise the original document will be moved to the destination. For performance reasons and to avoid copies, we recommend you set `asCopy` to false.
- (instancetype)initForExportingURLs:(NSArray <NSURL *> *)urls asCopy:(BOOL)asCopy NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos);

/// Initializes the picker for exporting local documents to an external location. The new locations will be returned using `didPickDocumentAtURLs:`. The original document will be moved to the destination.
- (instancetype)initForExportingURLs:(NSArray <NSURL *> *)urls API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos);
                     
@property (nullable, nonatomic, weak) id<UIDocumentPickerDelegate> delegate;
@property (nonatomic, assign, readonly) UIDocumentPickerMode documentPickerMode API_DEPRECATED("Use appropriate initializers instead",ios(8.0,14.0));
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
