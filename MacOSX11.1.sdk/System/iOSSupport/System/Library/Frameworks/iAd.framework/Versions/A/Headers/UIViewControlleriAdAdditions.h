//
//  UIViewControlleriAdAdditions.h
//  iAd
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang system_header

/*!
 * @enum ADInterstitialPresentationPolicy
 *
 * @constant ADInterstitialPresentationPolicyNone Default policy - this is effectively
 * the same as the Manual policy except that setting the Manual policy will trigger
 * the +prepareInterstitialAds logic if needed.
 *
 * @constant ADInterstitialPresentationPolicyAutomatic Automatic policy - the framework
 * determines when an interstitial will be presented.
 *
 * @constant ADInterstitialPresentationPolicyManual Manual policy - the application
 * determines when an interstitial should be presented and calls an API from the
 * iAdAdditions category.
 *
 * @discussion
 * Policy options governing how and when interstitial ads may be presented from
 * a given view controller.
 */
typedef NS_ENUM(NSInteger, ADInterstitialPresentationPolicy) {
    ADInterstitialPresentationPolicyNone = 0,
    ADInterstitialPresentationPolicyAutomatic,
    ADInterstitialPresentationPolicyManual
}  NS_ENUM_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @category UIViewController (iAdAdditions)
 *
 * @discussion
 * This category on UIViewController provides an interface for configuring the kind
 * of ads that should be shown with the view controller's content. Two types of
 * ads may be shown - banners and interstitials. Banner ads will be displayed below
 * the content which will be resized appropriately based on the size of the banner.
 * Interstitials can be displayed automatically or upon request. Automatic display
 * of interstitials will be tied to the appearance of the view, with the frequency
 * of presentation managed by the framework. On-request display of interstitials
 * is subject to similar internal constraints.
*/
@interface UIViewController (iAdAdditions)

/*!
 * @method prepareInterstitials
 *
 * @discussion
 * Ads involve network requests, so if an application needs to use interstitial
 * ads and wants to ensure early availability, this method can be called to trigger
 * a prefetch. If this method is not called, the first fetch will occur when a
 * view controller's interstitialPresentationPolicy is set to something other
 * than ADInterstitialPresentationPolicyNone.
 */
+ (void)prepareInterstitialAds NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @property interstitialPresentationPolicy
 *
 * @discussion
 * The presentation policy determines whether the timing of presentation is entirely
 * managed by the framework or should only take place when the application calls
 * -requestInterstitialAdPresentation. By default the policy is "None", so to be
 * able to present an interstitial it must be changed to either "Automatic" or "Manual".
 */
@property (nonatomic, assign) ADInterstitialPresentationPolicy interstitialPresentationPolicy NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @property canDisplayBannerAds
 *
 * @discussion
 * Set this to enable automatic management of banner ad display with the view controller.
 * It's important to note that this will modify the view hierarchy of the view controller
 * by inserting a new container view above the view controller's view. The impact
 * is that the view controller's view property will no longer return the originally
 * provided view, it will return the new container. To access the original view,
 * use the originalContentView property.
 *
 * @seealso originalContentView
 */
@property (nonatomic, assign) BOOL canDisplayBannerAds NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @property originalContentView
 *
 * @discussion
 * If banner ads have not been enabled, originalContentView will return the view
 * controller's view. If banner ads are enabled, originalContentView returns the
 * view that was previously the view controller's view. If banner ads are then subsequently
 * disabled, the view controller's content view will remain embedded - that operation
 * will not be reversed.
 */
@property (nullable, nonatomic, strong, readonly) UIView *originalContentView NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @property presentingFullScreenAd
 *
 * @discussion
 * Can be used to query the controller to determine if it is presenting a full screen
 * ad, which may be an interstitial or the iAd shown when the user taps a banner.
 */
@property (nonatomic, readonly, getter=isPresentingFullScreenAd) BOOL presentingFullScreenAd NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @property displayingBannerAd
 *
 * @discussion
 * Can be used to query the controller to determine if it is displaying a banner ad.
 */
@property (nonatomic, readonly, getter=isDisplayingBannerAd) BOOL displayingBannerAd NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @method requestInterstitialAdPresentation
 *
 * @return
 * Returns YES if an interstitial can be displayed, NO if not.
 *
 * @discussion
 * Call at any time to request that an interstitial ad be presented. This is appropriate
 * for view controllers that are on screen for long periods of time and internally
 * manage significant state changes, such as game levels. Returns YES if an interstitial
 * will be presented.
 */
- (BOOL)requestInterstitialAdPresentation NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

/*!
 * @method shouldPresentInterstitialAd
 *
 * @return
 * Should return YES to allow presentation to proceed, NO to prevent it. The default
 * implementation always returns YES.
 *
 * @discussion
 * Subclasses should override this method if they use ADInterstitialPresentationPolicyAutomatic
 * and require the ability to selectively prevent presentation based on application
 * state. The method will be invoked when the framework is about to present an interstitial
 * ad in the ADInterstitialPresentationPolicyAutomatic configuration.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL shouldPresentInterstitialAd NS_DEPRECATED(10_14, 10_14, 7_0, 10_0);

@end

NS_ASSUME_NONNULL_END

