//
//  SLComposeServiceViewController.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Social/SocialDefines.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif



#if TARGET_OS_IPHONE
SOCIAL_CLASS_AVAILABLE_IOS(8_0)
@interface SLComposeServiceViewController : UIViewController <UITextViewDelegate>
#else
SOCIAL_CLASS_AVAILABLE_MAC(10_10)
@interface SLComposeServiceViewController : NSViewController <NSTextViewDelegate>
#endif

/*
 Setup
 */

// Called when the sheet presentation animation is finished.
// Subclasses should implement this to begin performing any expensive work (e.g., messaging a server), instead of during initialization, -viewWillAppear, or -viewDidAppear.
- (void)presentationAnimationDidFinish;


/*
 Sheet Content
 
 NOTE: Attachments (e.g., links, images, videos) and initial text are accessible via the view controller's extensionContext.
 */

// The textView displaying the (editable) text content on the sheet. When it's time to post, grab self.textView.text.
// SLComposeServiceViewController creates textView in -loadView and sets itself to be the textView's delegate.
#if TARGET_OS_IPHONE
@property (readonly, nonatomic) UITextView *textView;
#else
@property (readonly) NSTextView *textView;
#endif

// Convenience. This returns the current text from the textView.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *contentText;

// When textView is empty, this string is displayed instead.
// NOTE: This uses the iOS naming convention: "placeholder" vs. "placeholderString" on OS X.
@property (copy, NS_NONATOMIC_IOSONLY) NSString *placeholder;


/*
 Posting & Canceling
 */

// Called after the post animation has finished (in response to the user selecting the Post button).
// The default implementation calls the extensionContext's -completeRequestReturningItems:completionHandler: method with nil.
// Subclasses must override this in order to peform the post, based on contentText and any attachments.
// Subclasses may call super in order to leverage the default completion behavior; if a subclass does not call super, it must call extensionContext's completion method manually.
- (void)didSelectPost;

// Called after the cancel animation has finished (in response to the user selecting the Cancel button, or someone calling -cancel).
// The default implementation calls the extensionContext's -cancelRequestWithError: method with an NSError/NSUserCancelledError.
// Subclasses may override this in order to customize the extensionContext completion.
- (void)didSelectCancel;

// Triggers an animated dismissal of the sheet, and then calls -didSelectCancel.
// Subclasses do not typically need to call this manually, but may choose to in response to a catastrophic failure during the user's interaction with the sheet.
// Subclasses should not need to override this.
- (void)cancel;


/*
 Sheet Content Validation
 */

// Called automatically after each text change to help determine the enable state of the Post button, and to give the subclass a chance to update charactersRemaining.
// Defaults to YES.
// Subclasses should override this, and return whether contentText and attachments are currently valid for posting.
- (BOOL)isContentValid;

// Calls -isContentValid immediately, performs other internal validation, then updates the enable state of the Post button appropriately.
// Subclasses should call this whenever they change data used as part of validity checking in their implementation of -isContentValid.
- (void)validateContent;

// Set/change this to something non-nil to cause the character count view to appear/redraw. This is useful for services that have a character count limit on their posts. Defaults to nil.
@property (strong, NS_NONATOMIC_IOSONLY) NSNumber *charactersRemaining;



#if TARGET_OS_IPHONE
/*
 Configuration Item Support (account pickers, privacy selection, location, etc.)
 */

// Subclasses should implement this, and return an array of SLComposeSheetConfigurationItem instances, if if needs to display configuration items in the sheet. Defaults to nil.
- (NSArray *)configurationItems;

// Forces a reload of the configuration items table.
// This is typically only necessary for subclasses that determine their configuration items in a deferred manner (for example, in -presentationAnimationDidFinish).
// You do not need to call this after changing a configuration item property; the base class detects and reacts to that automatically.
- (void)reloadConfigurationItems;

// Presents a configuration view controller. Typically called from a configuration item's tapHandler. Only one configuration view controller is allowed at a time.
// The pushed view controller should set preferredContentSize appropriately. SLComposeServiceViewController observes changes to that property and animates sheet size changes as necessary.
- (void)pushConfigurationViewController:(UIViewController *)viewController;

// Dismisses the current configuration view controller.
- (void)popConfigurationViewController;
#endif


#if TARGET_OS_IPHONE
/*
 Custom Preview
 */

// Called when it's time to create a view suitable for previewing the attachments on the extensionContext.
// Defaults to returning a UIView instance appropriate to the set of attachments in the extensionContext, or nil if a preview is unneccessary for the extensionContext.
// Subclasses can override this to supply a preview view of their own choosing for the set of attachments on the extensionContext.
- (UIView *)loadPreviewView;
#endif


#if TARGET_OS_IPHONE
/*
 Text Auto Completion (mentions)
 */

// A view controller whose view replaces the configuration item table, sitting just below the text view. Defaults to nil.
// Set this to a non-nil view controller to implement a mentions picker or something similar. The view controller should set preferredContentSize appropriately. SLComposeServiceViewController observes changes to that property and animates sheet size changes as necessary.
// Set it to nil to remove your view controller, thus restoring the configuration item table.
// SLComposeServiceViewController animates the addition/removal of the view controller's view, as appropriate.
@property (strong, NS_NONATOMIC_IOSONLY) UIViewController *autoCompletionViewController;
#endif


@end


