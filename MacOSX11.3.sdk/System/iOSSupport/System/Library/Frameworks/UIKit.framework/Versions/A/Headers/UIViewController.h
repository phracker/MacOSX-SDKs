#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewController.h>)
//
//  UIViewController.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSExtensionRequestHandling.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIStateRestoration.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIFocus.h>
#import <UIKit/UIPointerLockState.h>

/*
  UIViewController is a generic controller base class that manages a view.  It has methods that are called
  when a view appears or disappears.
 
  Subclasses can override -loadView to create their custom view hierarchy, or specify a nib name to be loaded
  automatically.  This class is also a good place for delegate & datasource methods, and other controller
  stuff.
*/

NS_ASSUME_NONNULL_BEGIN

@class UIView;
@class UINavigationItem, UIBarButtonItem, UITabBarItem;
@class UISearchDisplayController;
@class UIPopoverController;
@class UIStoryboard, UIStoryboardSegue, UIStoryboardUnwindSegueSource;
@class UIScrollView;
@protocol UIViewControllerTransitionCoordinator;

typedef NS_ENUM(NSInteger, UIModalTransitionStyle) {
    UIModalTransitionStyleCoverVertical = 0,
    UIModalTransitionStyleFlipHorizontal API_UNAVAILABLE(tvos),
    UIModalTransitionStyleCrossDissolve,
    UIModalTransitionStylePartialCurl API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos),
};

typedef NS_ENUM(NSInteger, UIModalPresentationStyle) {
    UIModalPresentationFullScreen = 0,
    UIModalPresentationPageSheet API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos),
    UIModalPresentationFormSheet API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos),
    UIModalPresentationCurrentContext API_AVAILABLE(ios(3.2)),
    UIModalPresentationCustom API_AVAILABLE(ios(7.0)),
    UIModalPresentationOverFullScreen API_AVAILABLE(ios(8.0)),
    UIModalPresentationOverCurrentContext API_AVAILABLE(ios(8.0)),
    UIModalPresentationPopover API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos),
    UIModalPresentationBlurOverFullScreen API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos),
    UIModalPresentationNone API_AVAILABLE(ios(7.0)) = -1,
    UIModalPresentationAutomatic API_AVAILABLE(ios(13.0)) = -2,
};

@protocol UIContentContainer <NSObject>

@property (nonatomic, readonly) CGSize preferredContentSize API_AVAILABLE(ios(8.0));
- (void)preferredContentSizeDidChangeForChildContentContainer:(id <UIContentContainer>)container API_AVAILABLE(ios(8.0));

/*
 Intended as a bridge for a view controller that does not use auto layout presenting a child that does use auto layout.
 
 If the child's view is using auto layout and the -systemLayoutSizeFittingSize: of the view
 changes, -systemLayoutFittingSizeDidChangeForChildContentContainer: will be sent to the view controller's parent.
 */
- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(id <UIContentContainer>)container API_AVAILABLE(ios(8.0));

/*
 When the content container forwards viewWillTransitionToSize:withTransitionCoordinator: to its children, it will call this method to determine what size to send them. 
 
 If the returned size is the same as the child container's current size, viewWillTransitionToSize:withTransitionCoordinator: will not be called.
 */
- (CGSize)sizeForChildContentContainer:(id <UIContentContainer>)container withParentContainerSize:(CGSize)parentSize API_AVAILABLE(ios(8.0));

/* 
 This method is called when the view controller's view's size is changed by its parent (i.e. for the root view controller when its window rotates or is resized). 
 
 If you override this method, you should either call super to propagate the change to children or manually forward the change to children.
 */
- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator API_AVAILABLE(ios(8.0));

/* 
 This method is called when the view controller's trait collection is changed by its parent.
 
 If you override this method, you should either call super to propagate the change to children or manually forward the change to children.
 */
- (void)willTransitionToTraitCollection:(UITraitCollection *)newCollection withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator API_AVAILABLE(ios(8.0));

@end

// Sometimes view controllers that are using showViewController:sender and showDetailViewController:sender: will need to know when the split view controller environment above it has changed. This notification will be posted when that happens (for example, when a split view controller is collapsing or expanding). The NSNotification's object will be the view controller that caused the change.
UIKIT_EXTERN NSNotificationName const UIViewControllerShowDetailTargetDidChangeNotification API_AVAILABLE(ios(8.0));

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIViewController : UIResponder <NSCoding, UIAppearanceContainer, UITraitEnvironment, UIContentContainer, UIFocusEnvironment>

/*
  The designated initializer. If you subclass UIViewController, you must call the super implementation of this
  method, even if you aren't using a NIB.  (As a convenience, the default init method will do this for you,
  and specify nil for both of this methods arguments.) In the specified NIB, the File's Owner proxy should
  have its class set to your view controller subclass, with the view outlet connected to the main view. If you
  invoke this method with a nil nib name, then this class' -loadView method will attempt to load a NIB whose
  name is the same as your view controller's class. If no such NIB in fact exists then you must either call
  -setView: before -view is invoked, or override the -loadView method to set up your views programatically.
*/
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property(null_resettable, nonatomic,strong) UIView *view; // The getter first invokes [self loadView] if the view hasn't been set yet. Subclasses must call super if they override the setter or getter.
- (void)loadView; // This is where subclasses should create their custom view hierarchy if they aren't using a nib. Should never be called directly.
- (void)loadViewIfNeeded API_AVAILABLE(ios(9.0)); // Loads the view controller's view if it has not already been set.
@property(nullable, nonatomic, readonly, strong) UIView *viewIfLoaded API_AVAILABLE(ios(9.0)); // Returns the view controller's view if loaded, nil if not.

- (void)viewWillUnload API_DEPRECATED("", ios(5.0, 6.0)) API_UNAVAILABLE(tvos);
- (void)viewDidUnload API_DEPRECATED("", ios(3.0, 6.0)) API_UNAVAILABLE(tvos); // Called after the view controller's view is released and set to nil. For example, a memory warning which causes the view to be purged. Not invoked as a result of -dealloc.

- (void)viewDidLoad; // Called after the view has been loaded. For view controllers created in code, this is after -loadView. For view controllers unarchived from a nib, this is after the view is set.
@property(nonatomic, readonly, getter=isViewLoaded) BOOL viewLoaded API_AVAILABLE(ios(3.0));

@property(nullable, nonatomic, readonly, copy) NSString *nibName;     // The name of the nib to be loaded to instantiate the view.
@property(nullable, nonatomic, readonly, strong) NSBundle *nibBundle; // The bundle from which to load the nib.
@property(nullable, nonatomic, readonly, strong) UIStoryboard *storyboard API_AVAILABLE(ios(5.0));

- (void)performSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender API_AVAILABLE(ios(5.0));
- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender API_AVAILABLE(ios(6.0)); // Invoked immediately prior to initiating a segue. Return NO to prevent the segue from firing. The default implementation returns YES. This method is not invoked when -performSegueWithIdentifier:sender: is used.
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(nullable id)sender API_AVAILABLE(ios(5.0));

// View controllers will receive this message during segue unwinding. The default implementation returns the result of -respondsToSelector: - controllers can override this to perform any ancillary checks, if necessary.
- (BOOL)canPerformUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController sender:(nullable id)sender API_AVAILABLE(ios(13.0), tvos(13.0));
- (BOOL)canPerformUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController withSender:(id)sender API_DEPRECATED_WITH_REPLACEMENT("canPerformUnwindSegueAction:fromViewController:sender:", ios(6.0, 13.0), tvos(9.0, 13.0));

// Returns a subset of the receiver's childViewControllers in the order they should be searched for an unwind destination.
// The default implementation first sends itself -childViewControllerContainingSegueSource:, then returns a copy of its childViewControllers array excluding that object. A custom container view controller can override this method to affect the order in which its children are searched, or to modify the result of the default implementation.
// For compatibility, if a view controller overrides the deprecated -viewControllerForUnwindSegueAction:fromViewController:sender: method, but does not override this method, it will receive the deprecated method instead of this method.
// To affect this view controller's eligibility as an unwind destination, override -canPerformUnwindSegueAction:fromViewController:sender: instead.
- (NSArray<UIViewController *> *)allowedChildViewControllersForUnwindingFromSource:(UIStoryboardUnwindSegueSource *)source API_AVAILABLE(ios(9.0));

// Returns the child view controller that contains the provided segue source.
// Custom container view controllers should call this method from their implementation of -allowedChildViewControllersForUnwindingFromSource: to exclude the result from the returned array, as well as to determine the order of the returned array's contents.
// Do not try to re-implement or override this method; it takes special care to handle situations such as unwinding from a modally-presented view controller.
- (nullable UIViewController *)childViewControllerContainingSegueSource:(UIStoryboardUnwindSegueSource *)source API_AVAILABLE(ios(9.0));

// Deprecated. Returns a direct child of the receiver that responds YES to -canPerformUnwindSegueAction:fromViewController:sender:, or self if no children respond YES but the receiver itself does. If this method has been overridden, UIViewController's implementation does not consult child view controllers at all, and skips straight to sending -canPerformUnwindSegueAction:... to self.
// Applications targeting iOS 9 or later should not override this method. Applications can instead override -allowedChildViewControllersForUnwindingFromSource: to guide UIKit’s search for a descendant view controller that returns YES from -canPerformUnwindSegueAction:fromViewController:sender:.
- (nullable UIViewController *)viewControllerForUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController withSender:(nullable id)sender API_DEPRECATED("", ios(6.0, 9.0));

// Custom container view controllers should override this method to modify themselves as part of an ongoing unwind segue. The subsequentVC is the parent, child, or presented view controller closest to the receiver in the direction of the segue's destinationViewController. For example, UINavigationController's implementation of this method will pop any necessary view controllers to reveal the subsequentVC.
- (void)unwindForSegue:(UIStoryboardSegue *)unwindSegue towardsViewController:(UIViewController *)subsequentVC API_AVAILABLE(ios(9.0));

// Deprecated. This method is only used for unwind segues whose destination view controller has been returned by an override of the deprecated method -viewControllerForUnwindSegueAction:fromViewController:withSender:. In that case, UIKit will choose a view controller to act as the “executor” of the unwind. If the destination view controller is being modally presented, the destination view controller itself is the executor. Otherwise, the destination view controller’s parent view controller is the executor. If the executor overrides this method, UIKit will ignore the Custom Class specified in Interface Builder and instead call this method on the executor to obtain a segue that can perform the unwind.
// The returned segue object must be able to perform all steps necessary to unwind, including dismissing any intermediate modal presentations or popping any necessary navigation items.
// Applications targeting iOS 9 or later should not override this method. Custom container view controllers should instead override -unwindForSegue:towardsViewController: to modify their local state as part of a UIKit-generated incremental unwind segue.
- (nullable UIStoryboardSegue *)segueForUnwindingToViewController:(UIViewController *)toViewController fromViewController:(UIViewController *)fromViewController identifier:(nullable NSString *)identifier API_DEPRECATED("", ios(6.0, 9.0));

- (void)viewWillAppear:(BOOL)animated;    // Called when the view is about to made visible. Default does nothing
- (void)viewDidAppear:(BOOL)animated;     // Called when the view has been fully transitioned onto the screen. Default does nothing
- (void)viewWillDisappear:(BOOL)animated; // Called when the view is dismissed, covered or otherwise hidden. Default does nothing
- (void)viewDidDisappear:(BOOL)animated;  // Called after the view was dismissed, covered or otherwise hidden. Default does nothing

// Called just before the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a no-op.
- (void)viewWillLayoutSubviews API_AVAILABLE(ios(5.0));
// Called just after the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a no-op.
- (void)viewDidLayoutSubviews API_AVAILABLE(ios(5.0));

@property(nullable, nonatomic,copy) NSString *title;  // Localized title for use by a parent controller.

- (void)didReceiveMemoryWarning; // Called when the parent application receives a memory warning. On iOS 6.0 it will no longer clear the view by default.

/*
  If this view controller is a child of a containing view controller (e.g. a navigation controller or tab bar
  controller,) this is the containing view controller.  Note that as of 5.0 this no longer will return the
  presenting view controller.
*/
@property(nullable,nonatomic,weak,readonly) UIViewController *parentViewController;

// This property has been replaced by presentedViewController.
@property(nullable, nonatomic,readonly) UIViewController *modalViewController API_DEPRECATED("", ios(2.0, 6.0)) API_UNAVAILABLE(tvos);

// The view controller that was presented by this view controller or its nearest ancestor.
@property(nullable, nonatomic,readonly) UIViewController *presentedViewController  API_AVAILABLE(ios(5.0));

// The view controller that presented this view controller (or its farthest ancestor.)
@property(nullable, nonatomic,readonly) UIViewController *presentingViewController API_AVAILABLE(ios(5.0));

/*
  Determines which parent view controller's view should be presented over for presentations of type
  UIModalPresentationCurrentContext.  If no ancestor view controller has this flag set, then the presenter
  will be the root view controller.
*/
@property(nonatomic,assign) BOOL definesPresentationContext API_AVAILABLE(ios(5.0));

// A controller that defines the presentation context can also specify the modal transition style if this property is true.
@property(nonatomic,assign) BOOL providesPresentationContextTransitionStyle API_AVAILABLE(ios(5.0));

// If YES, when this view controller becomes visible and focusable, focus will be automatically restored to the item that was last focused. For example, when an item in this view controller is focused, and then another view controller is presented and dismissed, the original item will become focused again. Defaults to YES.
@property (nonatomic) BOOL restoresFocusAfterTransition API_AVAILABLE(ios(10.0));

/*
  These four methods can be used in a view controller's appearance callbacks to determine if it is being
  presented, dismissed, or added or removed as a child view controller. For example, a view controller can
  check if it is disappearing because it was dismissed or popped by asking itself in its viewWillDisappear:
  method by checking the expression ([self isBeingDismissed] || [self isMovingFromParentViewController]).
*/

@property(nonatomic, readonly, getter=isBeingPresented) BOOL beingPresented API_AVAILABLE(ios(5.0));
@property(nonatomic, readonly, getter=isBeingDismissed) BOOL beingDismissed API_AVAILABLE(ios(5.0));

@property(nonatomic, readonly, getter=isMovingToParentViewController) BOOL movingToParentViewController API_AVAILABLE(ios(5.0));
@property(nonatomic, readonly, getter=isMovingFromParentViewController) BOOL movingFromParentViewController API_AVAILABLE(ios(5.0));

/*
  The next two methods are replacements for presentModalViewController:animated and
  dismissModalViewControllerAnimated: The completion handler, if provided, will be invoked after the presented
  controllers viewDidAppear: callback is invoked.
*/
- (void)presentViewController:(UIViewController *)viewControllerToPresent animated: (BOOL)flag completion:(void (^ __nullable)(void))completion API_AVAILABLE(ios(5.0));
// The completion handler, if provided, will be invoked after the dismissed controller's viewDidDisappear: callback is invoked.
- (void)dismissViewControllerAnimated: (BOOL)flag completion: (void (^ __nullable)(void))completion API_AVAILABLE(ios(5.0));

// Display another view controller as a modal child. Uses a vertical sheet transition if animated.This method has been replaced by presentViewController:animated:completion:
- (void)presentModalViewController:(UIViewController *)modalViewController animated:(BOOL)animated API_DEPRECATED("", ios(2.0, 6.0)) API_UNAVAILABLE(tvos);

// Dismiss the current modal child. Uses a vertical sheet transition if animated. This method has been replaced by dismissViewControllerAnimated:completion:
- (void)dismissModalViewControllerAnimated:(BOOL)animated API_DEPRECATED("", ios(2.0, 6.0)) API_UNAVAILABLE(tvos);

/*
  Defines the transition style that will be used for this view controller when it is presented modally. Set
  this property on the view controller to be presented, not the presenter.  Defaults to
  UIModalTransitionStyleCoverVertical.
*/
@property(nonatomic,assign) UIModalTransitionStyle modalTransitionStyle API_AVAILABLE(ios(3.0));

/*
 Defines the presentation style that will be used for this view controller when it is presented modally. Set this property on the view controller to be presented, not the presenter.
 If this property has been set to UIModalPresentationAutomatic, reading it will always return a concrete presentation style. By default UIViewController resolves UIModalPresentationAutomatic to UIModalPresentationPageSheet, but system-provided subclasses may resolve UIModalPresentationAutomatic to other concrete presentation styles. Participation in the resolution of UIModalPresentationAutomatic is reserved for system-provided view controllers.
 Defaults to UIModalPresentationAutomatic on iOS starting in iOS 13.0, and UIModalPresentationFullScreen on previous versions. Defaults to UIModalPresentationFullScreen on all other platforms.
 */
@property(nonatomic,assign) UIModalPresentationStyle modalPresentationStyle API_AVAILABLE(ios(3.2));

// This controls whether this view controller takes over control of the status bar's appearance when presented non-full screen on another view controller. Defaults to NO.
@property(nonatomic,assign) BOOL modalPresentationCapturesStatusBarAppearance API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);

// Presentation modes may keep the keyboard visible when not required. Default implementation affects UIModalPresentationFormSheet visibility.
@property(nonatomic, readonly) BOOL disablesAutomaticKeyboardDismissal API_AVAILABLE(ios(4.3));

@property(nonatomic,assign) BOOL wantsFullScreenLayout API_DEPRECATED("", ios(3.0, 7.0)) API_UNAVAILABLE(tvos); // Deprecated in 7_0, Replaced by the following:

@property(nonatomic,assign) UIRectEdge edgesForExtendedLayout API_AVAILABLE(ios(7.0)); // Defaults to UIRectEdgeAll
@property(nonatomic,assign) BOOL extendedLayoutIncludesOpaqueBars API_AVAILABLE(ios(7.0)); // Defaults to NO, but bars are translucent by default on 7_0.  
@property(nonatomic,assign) BOOL automaticallyAdjustsScrollViewInsets API_DEPRECATED("Use UIScrollView's contentInsetAdjustmentBehavior instead", ios(7.0,11.0),tvos(7.0,11.0)); // Defaults to YES

/* The preferredContentSize is used for any container laying out a child view controller.
 */
@property (nonatomic) CGSize preferredContentSize API_AVAILABLE(ios(7.0));

// These methods control the attributes of the status bar when this view controller is shown. They can be overridden in view controller subclasses to return the desired status bar attributes.
@property(nonatomic, readonly) UIStatusBarStyle preferredStatusBarStyle API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos); // Defaults to UIStatusBarStyleDefault
@property(nonatomic, readonly) BOOL prefersStatusBarHidden API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos); // Defaults to NO
// Override to return the type of animation that should be used for status bar changes for this view controller. This currently only affects changes to prefersStatusBarHidden.
@property(nonatomic, readonly) UIStatusBarAnimation preferredStatusBarUpdateAnimation API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos); // Defaults to UIStatusBarAnimationFade

// This should be called whenever the return values for the view controller's status bar attributes have changed. If it is called from within an animation block, the changes will be animated along with the rest of the animation block.
- (void)setNeedsStatusBarAppearanceUpdate API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);

/* This method returns either itself or the nearest ancestor that can perform the given action and, if applicable, has overridden UIViewController's default implementation of the action method. View controllers can return NO from canPerformAction:withSender: to opt out of being a target for a given action. */
- (nullable UIViewController *)targetViewControllerForAction:(SEL)action sender:(nullable id)sender API_AVAILABLE(ios(8.0));

/* This method will show a view controller appropriately for the current size-class environment. It's implementation calls
 `[self targetViewControllerForAction:sender:]` first and redirects accordingly if the return value is not `self`, otherwise it will present the vc. */
- (void)showViewController:(UIViewController *)vc sender:(nullable id)sender API_AVAILABLE(ios(8.0));

/* This method will show a view controller within the semantic "detail" UI associated with the current size-class environment. It's implementation calls  `[self targetViewControllerForAction:sender:]` first and redirects accordingly if the return value is not `self`, otherwise it will present the vc.  */
- (void)showDetailViewController:(UIViewController *)vc sender:(nullable id)sender API_AVAILABLE(ios(8.0));

/* Override `preferredUserInterfaceStyle` in a subclass to make the application enter a specific
 * `UIUserInterfaceStyle` when this view controller becomes active (as determined by a parent's
 * `childViewControllerForUserInterfaceStyle`).
 * If the value changes, call `setNeedsUserInterfaceAppearanceUpdate` to apply the change.
 */
@property (nonatomic, readonly) UIUserInterfaceStyle preferredUserInterfaceStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos); // Defaults to UIUserInterfaceStyleUnspecified

- (void)setNeedsUserInterfaceAppearanceUpdate API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos);

/* Set `overrideUserInterfaceStyle` to cause this view controller and its children to have a
 * specific `UIUserInterfaceStyle`. This does not affect the application or any parent view controllers.
 */
@property (nonatomic) UIUserInterfaceStyle overrideUserInterfaceStyle API_AVAILABLE(tvos(13.0), ios(13.0)) API_UNAVAILABLE(watchos); // Defaults to UIUserInterfaceStyleUnspecified

@end

// To make it more convenient for applications to adopt rotation, a view controller may implement the below methods. Your UIWindow's frame should use [UIScreen mainScreen].bounds as its frame.
@interface UIViewController (UIViewControllerRotation)

// call this method when your return value from shouldAutorotateToInterfaceOrientation: changes
// if the current interface orientation does not match the current device orientation, a rotation may occur provided all relevant view controllers now return YES from shouldAutorotateToInterfaceOrientation:
+ (void)attemptRotationToDeviceOrientation API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

// Applications should use supportedInterfaceOrientations and/or shouldAutorotate.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation API_DEPRECATED("", ios(2.0, 6.0)) API_UNAVAILABLE(tvos);

// New Autorotation support.
@property(nonatomic, readonly) BOOL shouldAutorotate API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos);
@property(nonatomic, readonly) UIInterfaceOrientationMask supportedInterfaceOrientations API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos);
// Returns interface orientation masks.
@property(nonatomic, readonly) UIInterfaceOrientation preferredInterfaceOrientationForPresentation API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos);

// The rotating header and footer views will slide out during the rotation and back in once it has completed.
- (nullable UIView *)rotatingHeaderView API_DEPRECATED("Header views are animated along with the rest of the view hierarchy", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);     // Must be in the view hierarchy. Default returns nil.
- (nullable UIView *)rotatingFooterView API_DEPRECATED("Footer views are animated along with the rest of the view hierarchy", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);     // Must be in the view hierarchy. Default returns nil.

@property(nonatomic,readonly) UIInterfaceOrientation interfaceOrientation API_DEPRECATED("", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);

// Notifies when rotation begins, reaches halfway point and ends.
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration API_DEPRECATED("Implement viewWillTransitionToSize:withTransitionCoordinator: instead", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation API_DEPRECATED("", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration API_DEPRECATED("Implement viewWillTransitionToSize:withTransitionCoordinator: instead", ios(3.0, 8.0)) API_UNAVAILABLE(tvos);

- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration API_DEPRECATED("", ios(2.0, 5.0)) API_UNAVAILABLE(tvos);
- (void)didAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation API_DEPRECATED("", ios(2.0, 5.0)) API_UNAVAILABLE(tvos); // The rotating header and footer views are offscreen.
- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration API_DEPRECATED("", ios(2.0, 5.0)) API_UNAVAILABLE(tvos); // A this point, our view orientation is set to the new orientation.

@end

// Many view controllers have a view that may be in an editing state or not- for example, a UITableView.  These view
// controllers can track the editing state, and generate an Edit|Done button to be used in a navigation bar.
@interface UIViewController (UIViewControllerEditing)

@property(nonatomic,getter=isEditing) BOOL editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated; // Updates the appearance of the Edit|Done button item as necessary. Clients who override it must call super first.

@property(nonatomic, readonly) UIBarButtonItem *editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.

@end

@interface UIViewController (UISearchDisplayControllerSupport)

@property(nullable, nonatomic, readonly, strong) UISearchDisplayController *searchDisplayController API_DEPRECATED("", ios(3.0, 8.0)) API_UNAVAILABLE(tvos);

@end


/*
  This exception is raised when a child view controller's view is added into the view hierarchy and the first
  superview of the child view controller's view that has a view controller is NOT the child view controller's
  parent.
*/
UIKIT_EXTERN NSExceptionName const UIViewControllerHierarchyInconsistencyException API_AVAILABLE(ios(5.0));

/*
  The methods in the UIContainerViewControllerProtectedMethods and the UIContainerViewControllerCallbacks
  categories typically should only be called by subclasses which are implementing new container view
  controllers. They may be overridden but must call super.
*/
@interface UIViewController (UIContainerViewControllerProtectedMethods)

// An array of children view controllers. This array does not include any presented view controllers.
@property(nonatomic,readonly) NSArray<__kindof UIViewController *> *childViewControllers API_AVAILABLE(ios(5.0));

/*
  If the child controller has a different parent controller, it will first be removed from its current parent
  by calling removeFromParentViewController. If this method is overridden then the super implementation must
  be called.
*/
- (void)addChildViewController:(UIViewController *)childController API_AVAILABLE(ios(5.0));

/*
  Removes the the receiver from its parent's children controllers array. If this method is overridden then
  the super implementation must be called.
*/
- (void)removeFromParentViewController API_AVAILABLE(ios(5.0));

/*
  This method can be used to transition between sibling child view controllers. The receiver of this method is
  their common parent view controller. (Use [UIViewController addChildViewController:] to create the
  parent/child relationship.) This method will add the toViewController's view to the superview of the
  fromViewController's view and the fromViewController's view will be removed from its superview after the
  transition completes. It is important to allow this method to add and remove the views. The arguments to
  this method are the same as those defined by UIView's block animation API. This method will fail with an
  NSInvalidArgumentException if the parent view controllers are not the same as the receiver, or if the
  receiver explicitly forwards its appearance and rotation callbacks to its children. Finally, the receiver
  should not be a subclass of an iOS container view controller. Note also that it is possible to use the
  UIView APIs directly. If they are used it is important to ensure that the toViewController's view is added
  to the visible view hierarchy while the fromViewController's view is removed.
*/
- (void)transitionFromViewController:(UIViewController *)fromViewController toViewController:(UIViewController *)toViewController duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))animations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(5.0));

// If a custom container controller manually forwards its appearance callbacks, then rather than calling
// viewWillAppear:, viewDidAppear: viewWillDisappear:, or viewDidDisappear: on the children these methods
// should be used instead. This will ensure that descendent child controllers appearance methods will be
// invoked. It also enables more complex custom transitions to be implemented since the appearance callbacks are
// now tied to the final matching invocation of endAppearanceTransition.
- (void)beginAppearanceTransition:(BOOL)isAppearing animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)endAppearanceTransition __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Override to return a child view controller or nil. If non-nil, that view controller's status bar appearance attributes will be used. If nil, self is used. Whenever the return values from these methods change, -setNeedsStatusBarAppearanceUpdate should be called.
@property(nonatomic, readonly, nullable) UIViewController *childViewControllerForStatusBarStyle API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);
@property(nonatomic, readonly, nullable) UIViewController *childViewControllerForStatusBarHidden API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);

// Call to modify the trait collection for child view controllers.
- (void)setOverrideTraitCollection:(nullable UITraitCollection *)collection forChildViewController:(UIViewController *)childViewController API_AVAILABLE(ios(8.0));
- (nullable UITraitCollection *)overrideTraitCollectionForChildViewController:(UIViewController *)childViewController API_AVAILABLE(ios(8.0));

// Override to return a child view controller or nil. If non-nil, that view controller's preferred user interface style will be used. If nil, self is used. Whenever the preferredUserInterfaceStyle for a view controller has changed setNeedsUserInterfaceAppearanceUpdate should be called.
@property (nonatomic, readonly, nullable) UIViewController *childViewControllerForUserInterfaceStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

@end

@interface UIViewController (UIContainerViewControllerCallbacks)

/*
  This method is consulted to determine if a view controller manually forwards its containment callbacks to
  any children view controllers. Subclasses of UIViewController that implement containment logic may override
  this method. The default implementation returns YES. If it is overridden and returns NO, then the subclass is
  responsible for forwarding the following methods as appropriate - viewWillAppear: viewDidAppear: viewWillDisappear:
  viewDidDisappear: willRotateToInterfaceOrientation:duration:
  willAnimateRotationToInterfaceOrientation:duration: didRotateFromInterfaceOrientation:
*/

- (BOOL)automaticallyForwardAppearanceAndRotationMethodsToChildViewControllers API_DEPRECATED("", ios(5.0, 6.0)) API_UNAVAILABLE(tvos);
- (BOOL)shouldAutomaticallyForwardRotationMethods API_DEPRECATED("Manually forward viewWillTransitionToSize:withTransitionCoordinator: if necessary", ios(6.0, 8.0)) API_UNAVAILABLE(tvos);

@property(nonatomic, readonly) BOOL shouldAutomaticallyForwardAppearanceMethods API_AVAILABLE(ios(6.0));


/*
  These two methods are public for container subclasses to call when transitioning between child
  controllers. If they are overridden, the overrides should ensure to call the super. The parent argument in
  both of these methods is nil when a child is being removed from its parent; otherwise it is equal to the new
  parent view controller.

  addChildViewController: will call [child willMoveToParentViewController:self] before adding the
  child. However, it will not call didMoveToParentViewController:. It is expected that a container view
  controller subclass will make this call after a transition to the new child has completed or, in the
  case of no transition, immediately after the call to addChildViewController:. Similarly,
  removeFromParentViewController does not call [self willMoveToParentViewController:nil] before removing the
  child. This is also the responsibility of the container subclass. Container subclasses will typically define
  a method that transitions to a new child by first calling addChildViewController:, then executing a
  transition which will add the new child's view into the view hierarchy of its parent, and finally will call
  didMoveToParentViewController:. Similarly, subclasses will typically define a method that removes a child in
  the reverse manner by first calling [child willMoveToParentViewController:nil].
*/
- (void)willMoveToParentViewController:(nullable UIViewController *)parent API_AVAILABLE(ios(5.0));
- (void)didMoveToParentViewController:(nullable UIViewController *)parent API_AVAILABLE(ios(5.0));

@end

@interface UIViewController (UIStateRestoration) <UIStateRestoring>
@property (nullable, nonatomic, copy) NSString *restorationIdentifier API_AVAILABLE(ios(6.0));
@property (nullable, nonatomic, readwrite, assign) Class<UIViewControllerRestoration> restorationClass API_AVAILABLE(ios(6.0));
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder API_AVAILABLE(ios(6.0));
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder API_AVAILABLE(ios(6.0));
- (void) applicationFinishedRestoringState API_AVAILABLE(ios(7.0));
@end

@interface UIViewController (UIConstraintBasedLayoutCoreMethods)
/* Base implementation sends -updateConstraints to the view.
    When a view has a view controller, this message is sent to the view controller during 
     the Auto Layout updateConstraints pass in lieu of sending updateConstraints directly
     to the view.
    You may override this method in a UIViewController subclass for updating custom 
     constraints instead of subclassing your view and overriding -[UIView updateConstraints].
    Overrides must call super or send -updateConstraints to the view.
 */
- (void)updateViewConstraints API_AVAILABLE(ios(6.0));
@end

@protocol UIViewControllerTransitioningDelegate;

@interface UIViewController(UIViewControllerTransitioning)

@property (nullable, nonatomic, weak) id <UIViewControllerTransitioningDelegate> transitioningDelegate API_AVAILABLE(ios(7.0));

@end

@interface UIViewController (UILayoutSupport)
// These objects may be used as layout items in the NSLayoutConstraint API
@property(nonatomic,readonly,strong) id<UILayoutSupport> topLayoutGuide API_DEPRECATED("Use view.safeAreaLayoutGuide.topAnchor instead of topLayoutGuide.bottomAnchor", ios(7.0,11.0), tvos(7.0,11.0));
@property(nonatomic,readonly,strong) id<UILayoutSupport> bottomLayoutGuide API_DEPRECATED("Use view.safeAreaLayoutGuide.bottomAnchor instead of bottomLayoutGuide.topAnchor", ios(7.0,11.0), tvos(7.0,11.0));

/* Custom container UIViewController subclasses can use this property to add to the overlay
 that UIViewController calculates for the safeAreaInsets for contained view controllers.
 */
@property(nonatomic) UIEdgeInsets additionalSafeAreaInsets API_AVAILABLE(ios(11.0), tvos(11.0));

/* Minimum layoutMargins for the view determined by the view controller from context and hardware information.
 The view controller's view will respect these minimums unless viewRespectsSystemMinimumLayoutMargins
 (which defaults to YES) is set to NO.
 */
@property(nonatomic,readonly) NSDirectionalEdgeInsets systemMinimumLayoutMargins API_AVAILABLE(ios(11.0), tvos(11.0));

/* Default YES. The return value of the view's layoutMargins and directionalLayoutMargins properties will have
 values no smaller than the systemMinimumLayoutMargins. Set to NO for full customizability of the view's
 layoutMargins.
 */
@property(nonatomic) BOOL viewRespectsSystemMinimumLayoutMargins API_AVAILABLE(ios(11.0), tvos(11.0));

- (void)viewLayoutMarginsDidChange NS_REQUIRES_SUPER API_AVAILABLE(ios(11.0), tvos(11.0));
- (void)viewSafeAreaInsetsDidChange NS_REQUIRES_SUPER API_AVAILABLE(ios(11.0), tvos(11.0));

@end

@interface UIViewController (UIKeyCommand)

- (void)addKeyCommand:(UIKeyCommand *)keyCommand API_AVAILABLE(ios(9.0));
- (void)removeKeyCommand:(UIKeyCommand *)keyCommand API_AVAILABLE(ios(9.0));

@end

@interface UIViewController (UIPerformsActions)

/// Determines whether the receiver continues to respond to actions while it is presenting a view controller modally.
///
/// Defaults to YES. You can change the default return value by providing a value for UIViewControllerPerformsActionsWhilePresentingModally in your Info.plist file.
@property (nonatomic, readonly) BOOL performsActionsWhilePresentingModally API_AVAILABLE(ios(13.0), tvos(13.0));

@end

@class NSExtensionContext;

@interface UIViewController(NSExtensionAdditions) <NSExtensionRequestHandling>

// Returns the extension context. Also acts as a convenience method for a view controller to check if it participating in an extension request.
@property (nullable, nonatomic,readonly,strong) NSExtensionContext *extensionContext API_AVAILABLE(ios(8.0));

@end

@class UIPresentationController, UIPopoverPresentationController;

@interface UIViewController (UIPresentationController)

@property (nullable, nonatomic,readonly) UIPresentationController *presentationController API_AVAILABLE(ios(8.0));
@property (nullable, nonatomic,readonly) UIPopoverPresentationController *popoverPresentationController API_AVAILABLE(ios(8.0));

// modalInPresentation is set on the view controller when you wish to force the presentation hosting the view controller into modal behavior. When this is active, the presentation will prevent interactive dismiss and ignore events outside of the presented view controller's bounds until this is set to NO.
@property (nonatomic, getter=isModalInPresentation) BOOL modalInPresentation API_AVAILABLE(ios(13.0));

@end


@protocol UIViewControllerPreviewingDelegate;

@protocol UIViewControllerPreviewing <NSObject>

// This gesture can be used to cause the previewing presentation to wait until one of your gestures fails or to allow simultaneous recognition during the initial phase of the preview presentation.
@property (nonatomic, readonly) UIGestureRecognizer *previewingGestureRecognizerForFailureRelationship API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));

@property (nonatomic, readonly) id<UIViewControllerPreviewingDelegate> delegate API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));
@property (nonatomic, readonly) UIView *sourceView API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));

// This rect will be set to the bounds of sourceView before each call to
// -previewingContext:viewControllerForLocation:

@property (nonatomic) CGRect sourceRect API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));

@end


UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @protocol UIViewControllerPreviewingDelegate <NSObject>

// If you return nil, a preview presentation will not be performed
- (nullable UIViewController *)previewingContext:(id <UIViewControllerPreviewing>)previewingContext viewControllerForLocation:(CGPoint)location API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));
- (void)previewingContext:(id <UIViewControllerPreviewing>)previewingContext commitViewController:(UIViewController *)viewControllerToCommit API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));

@end

@interface UIViewController (UIViewControllerPreviewingRegistration)

// Registers a view controller to participate with 3D Touch preview (peek) and commit (pop).
- (id <UIViewControllerPreviewing>)registerForPreviewingWithDelegate:(id<UIViewControllerPreviewingDelegate>)delegate sourceView:(UIView *)sourceView API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));
- (void)unregisterForPreviewingWithContext:(id <UIViewControllerPreviewing>)previewing API_DEPRECATED_WITH_REPLACEMENT("UIContextMenuInteraction", ios(9.0, 13.0));

@end

@interface UIViewController (UIScreenEdgesDeferringSystemGestures)

// Override to return a child view controller or nil. If non-nil, that view controller's screen edges deferring system gestures will be used. If nil, self is used. Whenever the return value changes, -setNeedsScreenEdgesDeferringSystemGesturesUpdate should be called.
@property (nonatomic, readonly, nullable) UIViewController *childViewControllerForScreenEdgesDeferringSystemGestures API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// Controls the application's preferred screen edges deferring system gestures when this view controller is shown. Default is UIRectEdgeNone.
@property (nonatomic, readonly) UIRectEdge preferredScreenEdgesDeferringSystemGestures API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// This should be called whenever the return values for the view controller's screen edges deferring system gestures have changed.
- (void)setNeedsUpdateOfScreenEdgesDeferringSystemGestures API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end


@interface UIViewController (UIHomeIndicatorAutoHidden)

// Override to return a child view controller or nil. If non-nil, that view controller's home indicator auto-hiding will be used. If nil, self is used. Whenever the return value changes, -setNeedsHomeIndicatorAutoHiddenUpdate should be called.
@property (nonatomic, readonly, nullable) UIViewController *childViewControllerForHomeIndicatorAutoHidden API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// Controls the application's preferred home indicator auto-hiding when this view controller is shown.
@property (nonatomic, readonly) BOOL prefersHomeIndicatorAutoHidden API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// This should be called whenever the return values for the view controller's home indicator auto-hiding have changed.
- (void)setNeedsUpdateOfHomeIndicatorAutoHidden API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end


@interface UIViewController (UIPointerLockSupport)

// Override to return a child view controller or nil. If non-nil, that view controller's preferred pointer lock value will be used. If nil, self is used. Whenever the return value changes, setNeedsUpdateOfPrefersPointerLocked() should be called.
@property (nonatomic, readonly, nullable) UIViewController *childViewControllerForPointerLock API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

// Whether the pointer should be locked to a given scene when this view controller is shown.
// The default is NO. This preference may or may not be honored.
// See UIPointerLockState.locked for the current pointer lock state as determined by the system.
@property (nonatomic, readonly) BOOL prefersPointerLocked API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

// This should be called whenever the view controller's preferred pointer lock value has changed.
- (void)setNeedsUpdateOfPrefersPointerLocked API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

@end

@protocol UIPreviewActionItem;

@interface UIViewController ()

@property(nonatomic, readonly) NSArray <id <UIPreviewActionItem>> *previewActionItems API_DEPRECATED("UIViewControllerPreviewing is deprecated. Please use UIContextMenuInteraction.", ios(9.0, 13.0));

@end


UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @protocol UIPreviewActionItem <NSObject>
@property(nonatomic, copy, readonly) NSString *title;
@end

typedef NS_ENUM(NSInteger,UIPreviewActionStyle) {
    UIPreviewActionStyleDefault=0,
    UIPreviewActionStyleSelected,
    UIPreviewActionStyleDestructive,
} API_AVAILABLE(ios(9.0));

NS_CLASS_DEPRECATED_IOS(9_0, 13_0, "UIViewControllerPreviewing is deprecated. Please use UIContextMenuInteraction.")
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UIPreviewAction : NSObject <NSCopying,UIPreviewActionItem>

@property(nonatomic, copy, readonly) void (^handler)(id<UIPreviewActionItem> action, UIViewController *previewViewController);

+ (instancetype)actionWithTitle:(NSString *)title style:(UIPreviewActionStyle)style handler:(void (^)(UIPreviewAction *action, UIViewController *previewViewController))handler;

@end

NS_CLASS_DEPRECATED_IOS(9_0, 13_0, "UIViewControllerPreviewing is deprecated. Please use UIContextMenuInteraction.")
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UIPreviewActionGroup : NSObject <NSCopying,UIPreviewActionItem>
+ (instancetype)actionGroupWithTitle:(NSString *)title style:(UIPreviewActionStyle)style actions:(NSArray<UIPreviewAction *> *)actions;
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIViewController.h>
#endif
