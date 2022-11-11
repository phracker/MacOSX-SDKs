//
//  SFSafariViewControllerActivityButton.h
//  SafariServices Framework
//
//  Created by Louie Livon-Bemel on 12/8/17.
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSafariViewController;

/*!
 @class SFSafariViewControllerActivityButton
 A custom button to show in SFSafariViewController's toolbar. When tapped, it will invoke a Share or Action Extension bundled with your app.
 @discussion The default VoiceOver description of this button is the `CFBundleDisplayName` set in the extension's Info.plist.
 To set a different description for VoiceOver to read, set this object's `accessibilityLabel` property.
 */
SF_EXTERN API_AVAILABLE(ios(15.0))
NS_SWIFT_NAME(SFSafariViewController.ActivityButton)
@interface SFSafariViewControllerActivityButton : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! @abstract Initializes an SFSafariViewControllerActivityButton with the given image, accessibility label, and extension bundle identifier.
    @param templateImage the image to show in SFSafariViewController's toolbar. This is a template image that will get the same color as all
        other buttons, defined by @link -[SFSafariViewController preferredControlTintColor] @/link. This image should look similar to the
        other buttons in SFSafariViewController, and should be close to a 1:1 aspect ratio.
    @param extensionIdentifier the bundle identifier of the Action or Sharing Extension to run when the button is tapped. The extension can run
        JavaScript and present a view controller, as if it were selected from the UIActivityViewController in Safari or SFSafariViewController.
        This extension must be part of your app or another app with the same Team ID.
 */
- (instancetype)initWithTemplateImage:(UIImage *)templateImage extensionIdentifier:(NSString *)extensionIdentifier NS_DESIGNATED_INITIALIZER;

/*! @abstract A template image to use for the toolbar button. This button should look similar to the rest of SFSafariViewController's buttons,
    and be close to a 1:1 aspect ratio. The button will inherit the tint color set by @link -[SFSafariViewController preferredControlTintColor] @/link.
 */
@property (nonatomic, nullable, readonly, copy) UIImage *templateImage;

/*! @abstract The Bundle Identifier of the extension that should be ran when the button is tapped. This extension can run JavaScript
    and present a UIViewController, just as if it was selected from the UIActivityViewController in Safari or SFSafariViewController.
    This extension must be part of your app or another app with the same Team ID.
 */
@property (nonatomic, nullable, readonly, copy) NSString *extensionIdentifier;

@end

NS_ASSUME_NONNULL_END

