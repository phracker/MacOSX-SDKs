#if (defined(USE_VISIONKIT_PUBLIC_HEADERS) && USE_VISIONKIT_PUBLIC_HEADERS) || !__has_include(<DocumentCamera/VNDocumentCameraViewController.h>)
//
//  VNDocumentCameraViewController.h
//  VisionKit
//
//  Copyright © 2017-2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class VNDocumentCameraScan;

@protocol VNDocumentCameraViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN


/// A view controller that shows what the document camera sees.
///
/// Present this view controller, as follows, and add it to your view controller
/// hierarchy to scan documents.
///
/// ```occ VNDocumentCameraViewController* documentCameraViewController =
/// [[VNDocumentCameraViewController alloc] init];
/// documentCameraViewController.delegate = self; [self
/// presentViewController:documentCameraViewController animated:YES
/// completion:nil]; ```
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface VNDocumentCameraViewController : UIViewController

// The delegate to be notified when the user saves or cancels

/// The delegate to be notified when the user saves or cancels the document
/// scanner.
///
/// The delegate receives one of the following three calls:
///
/// -
/// ``VisionKit/VNDocumentCameraViewControllerDelegate/documentCameraViewController(_:didFinishWith:)``
/// when the camera successfully completes a scan. -
/// ``VisionKit/VNDocumentCameraViewControllerDelegate/documentCameraViewControllerDidCancel(_:)``
/// when the user cancels out of the document camera interface. -
/// ``VisionKit/VNDocumentCameraViewControllerDelegate/documentCameraViewController(_:didFailWithError:)``
/// when the document scan fails or is unable to capture a photo.
///
/// Your app is responsible for dismissing the document camera in all delegate
/// callback methods.
@property (nonatomic, weak, nullable) id <VNDocumentCameraViewControllerDelegate>delegate;

/// A Boolean variable that indicates whether or not the current device supports document scanning.
///
/// This class method returns `false` for unsupported hardware.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

// Unavailable
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)

/// A delegate protocol through which the document camera returns its scanned
/// results.
///
/// Your app is responsible for dismissing the document camera in all delegate
/// callback methods.
@protocol VNDocumentCameraViewControllerDelegate<NSObject>
@optional
/// Tells the delegate that the user successfully saved a scanned document from the document camera.
///
/// - Parameter controller: The document camera view controller that captured the scan.
/// - Parameter scan: The scanned document that the camera detected.
- (void)documentCameraViewController:(VNDocumentCameraViewController *)controller didFinishWithScan:(VNDocumentCameraScan *)scan;

/// Tells the delegate that the user canceled out of the document scanner camera.
///
/// - Parameter controller: The document camera view controller in which the user canceled.
- (void)documentCameraViewControllerDidCancel:(VNDocumentCameraViewController *)controller;

/// Tells the delegate that document scanning failed while the camera view controller was active.
///
/// - Parameter controller: The document camera view controller that failed.
/// - Parameter error: The error containing the reason for failure.
- (void)documentCameraViewController:(VNDocumentCameraViewController *)controller didFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END

#else
#import <DocumentCamera/VNDocumentCameraViewController.h>
#endif
