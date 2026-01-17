//
//  INUIEditVoiceShortcutViewController.h
//  IntentsUI
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class INVoiceShortcut;
@protocol INUIEditVoiceShortcutViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A view controller that shows the details of a voice shortcut, and lets the user edit the phrase.
 @discussion To have the user edit a voice shortcut, create an @c INUIEditVoiceShortcutViewController object with the @c INVoiceShortcut that they wish to edit, and set its delegate. Then, present the view controller modally from another view controller in your app. Your delegate must dismiss the view controller when the user finishes editing.
 */
API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@interface INUIEditVoiceShortcutViewController : UIViewController

@property (nonatomic, nullable, weak) id<INUIEditVoiceShortcutViewControllerDelegate> delegate;

/*!
 @param voiceShortcut The voice shortcut to be edited.
 */
- (instancetype)initWithVoiceShortcut:(INVoiceShortcut *)voiceShortcut;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@protocol INUIEditVoiceShortcutViewControllerDelegate <NSObject>

/*!
 @abstract Called if the user updates the voice shortcut, with either the successfully-updated voice shortcut, or an error.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)editVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)controller didUpdateVoiceShortcut:(nullable INVoiceShortcut *)voiceShortcut error:(nullable NSError *)error;

/*!
 @abstract Called if the user deletes the voice shortcut.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)editVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)controller didDeleteVoiceShortcutWithIdentifier:(NSUUID *)deletedVoiceShortcutIdentifier;

/*!
 @abstract Called if the user cancelled; no changes were made to the voice shortcut.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)editVoiceShortcutViewControllerDidCancel:(INUIEditVoiceShortcutViewController *)controller;

@end

NS_ASSUME_NONNULL_END
