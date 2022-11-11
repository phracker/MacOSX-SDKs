#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIVideoEditorController.h>)
//
//  UIVideoEditorController.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc.. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UINavigationController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIImagePickerController.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIVideoEditorControllerDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(3.1)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIVideoEditorController : UINavigationController

+ (BOOL)canEditVideoAtPath:(NSString *)videoPath API_AVAILABLE(ios(3.1));

@property(nullable, nonatomic,assign)    id <UINavigationControllerDelegate, UIVideoEditorControllerDelegate> delegate;

@property(nonatomic, copy)     NSString                              *videoPath;
@property(nonatomic)           NSTimeInterval                        videoMaximumDuration; // default value is 10 minutes. set to 0 to specify no maximum duration.
@property(nonatomic)           UIImagePickerControllerQualityType    videoQuality;         // default value is UIImagePickerControllerQualityTypeMedium

@end

API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@protocol UIVideoEditorControllerDelegate<NSObject>
@optional
// The editor does not dismiss itself; the client dismisses it in these callbacks.
// The delegate will receive exactly one of the following callbacks, depending whether the user
// confirms or cancels or if the operation fails.
- (void)videoEditorController:(UIVideoEditorController *)editor didSaveEditedVideoToPath:(NSString *)editedVideoPath; // edited video is saved to a path in app's temporary directory
- (void)videoEditorController:(UIVideoEditorController *)editor didFailWithError:(NSError *)error;
- (void)videoEditorControllerDidCancel:(UIVideoEditorController *)editor;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIVideoEditorController.h>
#endif
