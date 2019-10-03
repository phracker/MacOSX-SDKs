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

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface VNDocumentCameraViewController : UIViewController

// The delegate to be notified when the user saves or cancels
@property (nonatomic, weak, nullable) id <VNDocumentCameraViewControllerDelegate>delegate;

// Returns false for unsupported hardware
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

// Unavailable
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@protocol VNDocumentCameraViewControllerDelegate<NSObject>
@optional
// The client is responsible for dismissing the document camera in these callbacks.
// The delegate will receive one of the following calls, depending whether the user saves or cancels, or if the session fails.
- (void)documentCameraViewController:(VNDocumentCameraViewController *)controller didFinishWithScan:(VNDocumentCameraScan *)scan;

// The delegate will receive this call when the user cancels.
- (void)documentCameraViewControllerDidCancel:(VNDocumentCameraViewController *)controller;

// The delegate will receive this call when the user is unable to scan, with the following error.
- (void)documentCameraViewController:(VNDocumentCameraViewController *)controller didFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
