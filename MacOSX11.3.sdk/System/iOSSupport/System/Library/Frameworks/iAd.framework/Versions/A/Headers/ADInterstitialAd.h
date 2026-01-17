//
//  ADInterstitialAd.h
//  iAd
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <iAd/ADBannerView.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang system_header

NS_CLASS_DEPRECATED(10_14, 10_14, 4_3, 10_0)
@protocol ADInterstitialAdDelegate;

/*!
 * ADInterstitialAd is a full screen advertisement, available on iPad since
 * iOS 4.3, and on iPhone since iOS 7.0.
 *
 * There are three ways to display an ADInterstitialAd:
 *
 *   • By providing a container view and calling -presentInView:
 *   • By providing a view controller and calling -presentFromViewController:
 *   • Indirectly, by setting the interstitial presentation policy on a view
 *     controller to Automatic or Manual (via -[UIViewController setInterstitialPresentationPolicy:]),
 *     and letting the framework manage presentation.
 *
 * An ADInterstitialAd should not be presented until it has loaded content. This
 * is indicated via the -interstitialAdDidLoad: delegate method, and can also be
 * queried via the loaded property. If the interstitial ad is presented when
 * loaded=NO, an exception will be thrown.
 *
 * Note that using interstitial ads on iPhones running iOS < 7.0 will cause an
 * exception to be thrown.
 */

NS_CLASS_DEPRECATED(10_14, 10_14, 4_3, 10_0)
@interface ADInterstitialAd : NSObject

/*!
 * @property delegate
 *
 * @discussion
 * The interstitial ad delegate is notified when it has loaded, when errors
 * occur in getting ads, when actions begin and end, and when it has unloaded.
 *
 * On iOS 5 and later, this property is a weak reference and cannot be used with
 * objects that modify the behavior of release or retain.
 */
@property (nullable, nonatomic, weak) id<ADInterstitialAdDelegate> delegate;

/*!
 * @property loaded
 *
 * @return
 * YES if an ad is loaded, NO otherwise. This property should always be checked
 * before the interstitial ad is presented.
 */
@property (nonatomic, readonly, getter=isLoaded) BOOL loaded;

/*!
 * @property actionInProgress
 *
 * @discussion
 * Actions display full screen content in a modal session. Use this property to
 * determine if such an action is currently in progress.
 */
@property (nonatomic, readonly, getter=isActionInProgress) BOOL actionInProgress;

/*!
 * @property cancelAction
 *
 * @discussion
 * Cancels the current in-progress action. This should only be used in cases
 * where the user's attention is required immediately. If this method is called,
 * -interstitialAdActionDidFinish: will not be called.
 */
- (void)cancelAction;

/*
 * @method presentInView:
 *
 * @discussion
 * This method should be used to display the interstitial in a view hierarchy.
 * The view hierarchy must be managed by a view controller and the size of the
 * container view must fit the following constraints:
 *
 *   • Width must be DEVICE_WIDTH for the current orientation.
 *   • Height must be at least (DEVICE_HEIGHT - STATUS_BAR_HEIGHT - NAVIGATION_BAR_HEIGHT - TAB_BAR_HEIGHT).
 *   • Height must not exceed DEVICE_HEIGHT
 *
 * @throws NSInternalInconsistencyException
 * If the container view is not already in a view controller's managed hierarchy,
 * an exception will be thrown.
 *
 * @throws NSInternalInconsistencyException
 * If the interstitial has not loaded at the time this method is invoked, an
 * exception will be thrown.
 *
 * @return
 * YES if the interstitial could be presented, NO otherwise.
 */
- (BOOL)presentInView:(UIView *)containerView;

/*!
 * @method presentFromViewController:
 *
 * @discussion
 * As of iOS 7.0, the interstitial ad presentation APIs on UIViewController
 * should be used instead of managing your own ADInterstitialAd and presenting
 * it via the presentFromViewController: API.
 *
 * On iOS < 7.0, this method should be used to present the interstitial ad in a
 * non-paging UI, such as a transition or at the end of a game level. When this
 * API is used, the framework will manage how the interstitial is displayed and
 * what happens when the user dismisses it.
 *
 * User dismissal of either the interstitial or the ad unit to which it is
 * linked will restore control to the application immediately.
 */
- (void)presentFromViewController:(UIViewController *)viewController;

@end

/*!
 * @protocol ADInterstitialAdDelegate
 */

NS_CLASS_DEPRECATED(10_14, 10_14, 4_3, 10_0)
@protocol ADInterstitialAdDelegate <NSObject>

/*!
 * @method interstitialAdDidUnload:
 *
 * @discussion
 * When this method is invoked, if the application is using -presentInView:, the
 * content will be unloaded from the container shortly after this method is
 * called and no new content will be loaded. This may occur either as a result
 * of user actions or if the ad content has expired.
 *
 * In the case of an interstitial presented via -presentInView:, the layout of
 * the app should be updated to reflect that an ad is no longer visible. e.g.
 * by removing the view used for presentation and replacing it with another view.
 */
- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd;

/*!
 * @method interstitialAd:didFailWithError:
 *
 * @discussion
 * Called when an error has occurred attempting to get ad content.
 *
 * @see ADError for a list of possible error codes.
 */
- (void)interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error;

@optional

/*!
 * @method interstitialAdWillLoad:
 *
 * @discussion
 * Called when the interstitial has confirmation that an ad will be presented,
 * but before the ad has loaded resources necessary for presentation.
 */
- (void)interstitialAdWillLoad:(ADInterstitialAd *)interstitialAd NS_AVAILABLE_IOS(5_0);

/*!
 * @method interstitialAdDidLoad:
 *
 * @discussion
 * Called when the interstitial ad has finished loading ad content. The delegate
 * should implement this method so it knows when the interstitial ad is ready to
 * be presented.
 */
- (void)interstitialAdDidLoad:(ADInterstitialAd *)interstitialAd;

/*!
 * @method interstitialAdActionShouldBegin:willLeaveApplication:
 *
 * @discussion
 * Called when the user chooses to interact with the interstitial ad.
 *
 * The delegate may return NO to block the action from taking place, but this
 * should be avoided if possible because most ads pay significantly more when
 * the action takes place and, over the longer term, repeatedly blocking actions
 * will decrease the ad inventory available to the application.
 *
 * Applications should reduce their own activity while the advertisement's action
 * executes.
 */
- (BOOL)interstitialAdActionShouldBegin:(ADInterstitialAd *)interstitialAd willLeaveApplication:(BOOL)willLeave;

/*!
 * @method interstitialAdActionDidFinish:
 * This message is sent when the action has completed and control is returned to
 * the application. Games, media playback, and other activities that were paused
 * in response to the beginning of the action should resume at this point.
 */
- (void)interstitialAdActionDidFinish:(ADInterstitialAd *)interstitialAd;

@end

NS_CLASS_DEPRECATED(10_14, 10_14, 12_0, 13_0)
@interface ADInterstitialAdPresentationViewController : UIViewController

- (id)initForInterstitialAd:(ADInterstitialAd *)interstitialAd;
- (BOOL)shouldTestVisibilityAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END

