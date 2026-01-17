#if !__has_include(<PassKitUI/PKShareSecureElementPassViewController.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKShareSecureElementPassViewController.h
//    PassKit
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#ifndef __PKSHARESECUREELEMENTPASSVIEWCONTROLLER_H
#define __PKSHARESECUREELEMENTPASSVIEWCONTROLLER_H

#import <TargetConditionals.h>

#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

@class PKShareSecureElementPassViewController;
@class PKSecureElementPass;

NS_ASSUME_NONNULL_BEGIN

/// Share secure element pass result sent to delegate upon user completion.
///
/// @constant   PKShareSecureElementPassResultCanceled   User canceled the share.
/// @constant   PKShareSecureElementPassResultShared        User successfully shared the secure element pass.
/// @constant   PKShareSecureElementPassResultFailed          User's attempt to share was unsuccessful.
typedef NS_ENUM(NSInteger, PKShareSecureElementPassResult) {
    PKShareSecureElementPassResultCanceled,
    PKShareSecureElementPassResultShared,
    PKShareSecureElementPassResultFailed,
} API_AVAILABLE(ios(16.0));

API_AVAILABLE(ios(16.0))
@protocol PKShareSecureElementPassViewControllerDelegate <NSObject>

// Called once the share pass flow finishes.
//
// The delegate is responsible for dismissing the view controller in this method.
- (void)shareSecureElementPassViewController:(PKShareSecureElementPassViewController *)controller
                         didFinishWithResult:(PKShareSecureElementPassResult)result;

@optional

// This is called when using the `PKShareSecureElementPassViewControllerFlowDoNotPromptToShareURL` flow.
//
// Upon a successful share the share URL will be returned to be sent over an internal messaging channel.
// In an activation code was attached to the share it will also be returned. It it is up to the delegate
// to show the user the activationCode so that the recipient can successfully redeem the share.
- (void)shareSecureElementPassViewController:(PKShareSecureElementPassViewController *)controller
                           didCreateShareURL:(nullable NSURL *)universalShareURL
                              activationCode:(nullable NSString *)activationCode;

@end

API_AVAILABLE(ios(16.0))
@interface PKShareSecureElementPassViewController : UIViewController

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithSecureElementPass:(PKSecureElementPass *)pass delegate:(nullable id<PKShareSecureElementPassViewControllerDelegate>)delegate;

@property (nonatomic, weak, nullable) id<PKShareSecureElementPassViewControllerDelegate> delegate;

// This can be used to change the sharing flow a user will see.
// This must be configured before the view controller is presented.
// Defaults to YES
@property (nonatomic, assign) BOOL promptToShareURL;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IOS
#endif // __PKSHARESECUREELEMENTPASSVIEWCONTROLLER_H

#else
#if !TARGET_OS_OSX 
#import <TargetConditionals.h>
#import <PassKitUI/PKShareSecureElementPassViewController.h>
#endif
#endif