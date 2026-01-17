#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImagePickerController.h>)
//
//  UIImagePickerController.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UINavigationController.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage;
@protocol UIImagePickerControllerDelegate;

typedef NS_ENUM(NSInteger, UIImagePickerControllerSourceType) {
    UIImagePickerControllerSourceTypePhotoLibrary API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(2, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos),
    UIImagePickerControllerSourceTypeCamera API_UNAVAILABLE(visionos),
    UIImagePickerControllerSourceTypeSavedPhotosAlbum API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(2, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos),
} API_UNAVAILABLE(tvos, watchos);

typedef NS_ENUM(NSInteger, UIImagePickerControllerQualityType) {
    UIImagePickerControllerQualityTypeHigh = 0,       // highest quality
    UIImagePickerControllerQualityTypeMedium = 1,     // medium quality, suitable for transmission via Wi-Fi 
    UIImagePickerControllerQualityTypeLow = 2,         // lowest quality, suitable for transmission via cellular network
    UIImagePickerControllerQualityType640x480 API_AVAILABLE(ios(4.0)) = 3,    // VGA quality
    UIImagePickerControllerQualityTypeIFrame1280x720 API_AVAILABLE(ios(5.0)) = 4,
    UIImagePickerControllerQualityTypeIFrame960x540 API_AVAILABLE(ios(5.0)) = 5,
} API_UNAVAILABLE(tvos, visionos, watchos);

typedef NS_ENUM(NSInteger, UIImagePickerControllerCameraCaptureMode) {
    UIImagePickerControllerCameraCaptureModePhoto,
    UIImagePickerControllerCameraCaptureModeVideo
} API_UNAVAILABLE(tvos, visionos, watchos);

typedef NS_ENUM(NSInteger, UIImagePickerControllerCameraDevice) {
    UIImagePickerControllerCameraDeviceRear,
    UIImagePickerControllerCameraDeviceFront
} API_UNAVAILABLE(tvos, visionos, watchos);

typedef NS_ENUM(NSInteger, UIImagePickerControllerCameraFlashMode) {
    UIImagePickerControllerCameraFlashModeOff  = -1,
    UIImagePickerControllerCameraFlashModeAuto = 0,
    UIImagePickerControllerCameraFlashModeOn   = 1
} API_UNAVAILABLE(tvos, visionos, watchos);

typedef NS_ENUM(NSInteger, UIImagePickerControllerImageURLExportPreset) {
    UIImagePickerControllerImageURLExportPresetCompatible = 0,
    UIImagePickerControllerImageURLExportPresetCurrent
} API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(11, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(tvos, watchos);

typedef NSString * UIImagePickerControllerInfoKey NS_TYPED_ENUM API_UNAVAILABLE(watchos);

// info dictionary keys
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerMediaType API_UNAVAILABLE(tvos, watchos);      // an NSString (UTI, i.e. kUTTypeImage)
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerOriginalImage API_UNAVAILABLE(tvos, watchos);  // a UIImage
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerEditedImage API_UNAVAILABLE(tvos, watchos);    // a UIImage
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerCropRect API_UNAVAILABLE(tvos, watchos);       // an NSValue (CGRect)
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerMediaURL API_UNAVAILABLE(tvos, watchos);       // an NSURL
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerReferenceURL API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(4.1, 11.0)) API_UNAVAILABLE(visionos, tvos, watchos); // an NSURL that references an asset in the AssetsLibrary framework
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerMediaMetadata       API_AVAILABLE(ios(4.1)) API_UNAVAILABLE(tvos, watchos);  // an NSDictionary containing metadata from a captured photo
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerLivePhoto API_AVAILABLE(ios(9.1)) API_UNAVAILABLE(tvos, watchos);  // a PHLivePhoto
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerPHAsset API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(11.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(tvos, watchos); // a PHAsset
UIKIT_EXTERN UIImagePickerControllerInfoKey const UIImagePickerControllerImageURL API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);  // an NSURL

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIImagePickerController : UINavigationController <NSCoding>

+ (BOOL)isSourceTypeAvailable:(UIImagePickerControllerSourceType)sourceType;                 // returns YES if source is available (i.e. camera present)
+ (nullable NSArray<NSString *> *)availableMediaTypesForSourceType:(UIImagePickerControllerSourceType)sourceType; // returns array of available media types (i.e. kUTTypeImage)

+ (BOOL)isCameraDeviceAvailable:(UIImagePickerControllerCameraDevice)cameraDevice                   API_UNAVAILABLE(visionos) API_AVAILABLE(ios(4.0)); // returns YES if camera device is available
+ (BOOL)isFlashAvailableForCameraDevice:(UIImagePickerControllerCameraDevice)cameraDevice           API_UNAVAILABLE(visionos) API_AVAILABLE(ios(4.0)); // returns YES if camera device supports flash and torch.
+ (nullable NSArray<NSNumber *> *)availableCaptureModesForCameraDevice:(UIImagePickerControllerCameraDevice)cameraDevice API_UNAVAILABLE(visionos) API_AVAILABLE(ios(4.0)); // returns array of NSNumbers (UIImagePickerControllerCameraCaptureMode)

@property(nullable,nonatomic,weak)      id <UINavigationControllerDelegate, UIImagePickerControllerDelegate> delegate;

@property(nonatomic)           UIImagePickerControllerSourceType     sourceType;                                                        // default value is UIImagePickerControllerSourceTypePhotoLibrary.
@property(nonatomic,copy)      NSArray<NSString *>                   *mediaTypes;
    // default value is an array containing kUTTypeImage.
@property(nonatomic)           BOOL                                  allowsEditing API_AVAILABLE(ios(3.1));     // replacement for -allowsImageEditing; default value is NO.
@property(nonatomic)           BOOL                                  allowsImageEditing API_DEPRECATED("", ios(2.0, 3.1)) API_UNAVAILABLE(visionos, watchos);
@property(nonatomic)           UIImagePickerControllerImageURLExportPreset imageExportPreset API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(11.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);  // default value is UIImagePickerControllerImageExportPresetCompatible.

// video properties apply only if mediaTypes includes kUTTypeMovie
@property(nonatomic)           NSTimeInterval                        videoMaximumDuration API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(visionos); // default value is 10 minutes.
@property(nonatomic)           UIImagePickerControllerQualityType    videoQuality API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(visionos);         // default value is UIImagePickerControllerQualityTypeMedium. If the cameraDevice does not support the videoQuality, it will use the default value.
@property(nonatomic, copy)     NSString                              *videoExportPreset API_DEPRECATED("Will be removed in a future release, use PHPicker.", ios(11.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);  // videoExportPreset can be used to specify the transcoding quality for videos (via a AVAssetExportPreset* string). If the value is nil (the default) then the transcodeQuality is determined by videoQuality instead. Not valid if the source type is UIImagePickerControllerSourceTypeCamera


// camera additions available only if sourceType is UIImagePickerControllerSourceTypeCamera.
@property(nonatomic)           BOOL                                  showsCameraControls API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(visionos);   // set to NO to hide all standard camera UI. default is YES
@property(nullable, nonatomic,strong) __kindof UIView                *cameraOverlayView  API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(visionos);   // set a view to overlay the preview view.
@property(nonatomic)           CGAffineTransform                     cameraViewTransform API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(visionos);   // set the transform of the preview view.

- (void)takePicture API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(visionos);
// programmatically initiates still image capture. ignored if image capture is in-flight.
// clients can initiate additional captures after receiving -imagePickerController:didFinishPickingMediaWithInfo: delegate callback

- (BOOL)startVideoCapture API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(visionos);
- (void)stopVideoCapture  API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(visionos);

@property(nonatomic) UIImagePickerControllerCameraCaptureMode cameraCaptureMode API_UNAVAILABLE(visionos) API_AVAILABLE(ios(4.0)); // default is UIImagePickerControllerCameraCaptureModePhoto
@property(nonatomic) UIImagePickerControllerCameraDevice      cameraDevice      API_UNAVAILABLE(visionos) API_AVAILABLE(ios(4.0)); // default is UIImagePickerControllerCameraDeviceRear
@property(nonatomic) UIImagePickerControllerCameraFlashMode   cameraFlashMode   API_UNAVAILABLE(visionos) API_AVAILABLE(ios(4.0)); // default is UIImagePickerControllerCameraFlashModeAuto.
// cameraFlashMode controls the still-image flash when cameraCaptureMode is Photo. cameraFlashMode controls the video torch when cameraCaptureMode is Video.

@end

API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UIImagePickerControllerDelegate<NSObject>
@optional
// The picker does not dismiss itself; the client dismisses it in these callbacks.
// The delegate will receive one or the other, but not both, depending whether the user
// confirms or cancels.
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(nullable NSDictionary<UIImagePickerControllerInfoKey, id> *)editingInfo API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(visionos, watchos);
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey, id> *)info;
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker;

@end


// Adds a photo to the saved photos album.  The optional completionSelector should have the form:
//  - (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo;
UIKIT_EXTERN void UIImageWriteToSavedPhotosAlbum(UIImage *image, __nullable id completionTarget, __nullable SEL completionSelector, void * __nullable contextInfo) API_UNAVAILABLE(tvos, watchos);

// Is a specific video eligible to be saved to the saved photos album? 
UIKIT_EXTERN BOOL UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(NSString *videoPath) API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(tvos, watchos);

// Adds a video to the saved photos album. The optional completionSelector should have the form:
//  - (void)video:(NSString *)videoPath didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo;
UIKIT_EXTERN void UISaveVideoAtPathToSavedPhotosAlbum(NSString *videoPath, __nullable id completionTarget, __nullable SEL completionSelector, void * __nullable contextInfo) API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(tvos, watchos);

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIImagePickerController.h>
#endif
