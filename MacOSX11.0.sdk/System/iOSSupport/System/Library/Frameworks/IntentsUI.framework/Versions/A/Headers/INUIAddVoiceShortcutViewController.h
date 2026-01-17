//
//  INUIAddVoiceShortcutViewController.h
//  IntentsUI
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class INShortcut;
@class INVoiceShortcut;
@protocol INUIAddVoiceShortcutViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A view controller that will take the user through the setup flow to add a shortcut to Siri.
 @discussion First create the @c INShortcut object that represents the shortcut the user wants to perform. Then create an @c INUIAddVoiceShortcutViewController object and set its delegate. Then, present the view controller modally from another view controller in your app. The delegate must dismiss the view controller when the user completes the set up.
 */
API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@interface INUIAddVoiceShortcutViewController : UIViewController

@property (nonatomic, nullable, weak) id<INUIAddVoiceShortcutViewControllerDelegate> delegate;

/*!
 @param shortcut The shortcut is what will be run when the resulting voice shortcut is invoked. It also provides the suggested invocation phrase, via the @c suggestedInvocationPhrase property on the intent or user activity.
 */
- (instancetype)initWithShortcut:(INShortcut *)shortcut;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@protocol INUIAddVoiceShortcutViewControllerDelegate <NSObject>

/*!
 @abstract Called after the user finishes the setup flow for the voice shortcut, with either the successfully-added voice shortcut, or an error.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)addVoiceShortcutViewController:(INUIAddVoiceShortcutViewController *)controller didFinishWithVoiceShortcut:(nullable INVoiceShortcut *)voiceShortcut error:(nullable NSError *)error;

/*!
 @abstract Called if the user cancels the setup flow; the voice shortcut was not added.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)addVoiceShortcutViewControllerDidCancel:(INUIAddVoiceShortcutViewController *)controller;

@end

NS_ASSUME_NONNULL_END
