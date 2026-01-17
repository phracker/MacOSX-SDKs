//
//  ADBannerView.h
//  iAd
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang system_header

/*!
 * @const ADErrorDomain
 *
 * @discussion
 * Error domain for NSErrors passed to the following delegate methods:
 *
 *   • -[ADBannerViewDelegate bannerView:didFailToReceiveAdWithError:]
 *   • -[ADInterstitialAdDelegate interstitialAd:didFailWithError:]
 *
 */

NS_DEPRECATED(10_14, 10_14, 4_1, 13_0)
extern NSString * const ADErrorDomain;

/*!
 * @enum ADError
 *
 * @const ADErrorUnknown
 * General errors that aren't covered by one of the more specific error reasons.
 *
 * @const ADErrorServerFailure
 * Unable to request ads and their resources from the iAd service.
 *
 * @const ADErrorInventoryUnavailable
 * No ads are available at the moment. Note that this error is *always* returned
 * to iPhone apps running in compatibility mode on iPad, since ads are not
 * supported in that configuration.
 *
 * @const ADErrorConfigurationError
 * There are iAd configuration issues that need to be resolved before ads can be
 * served. Generally, this means visiting ADC <http://developer.apple.com/>.
 *
 * @const ADErrorBannerVisibleWithoutContent
 * The banner is visible but had no ad. Generally, this means a banner was made
 * visible before the -bannerViewDidLoadAd: delegate method was called, or
 * remained visible after the -bannerView:didFailToReceiveAdWithError: delegate
 * method was called.
 *
 * @const ADErrorAdUnloaded
 * The ad being displayed in the banner was unloaded. Some examples of when this
 * might happen is when an ad expires, or when an ad is moved from a non-visible
 * banner to a visible banner.
 *
 * @const ADErrorLoadingThrottled
 * Unused.
 *
 * @const ADErrorApplicationInactive
 * Unused.
 *
 * @discussion
 * Error codes for NSErrors passed to the delegate via the
 * bannerView:didFailToReceiveAdWithError: delegate method.
 */
typedef NS_ENUM(NSInteger, ADError) {
#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorUnknown = 0,
    ADErrorServerFailure = 1,
    ADErrorLoadingThrottled = 2,
    ADErrorInventoryUnavailable = 3,
#endif
#if __IPHONE_4_1 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorConfigurationError = 4,
    ADErrorBannerVisibleWithoutContent = 5,
#endif
#if __IPHONE_4_3 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorApplicationInactive = 6,
#endif
#if __IPHONE_6_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorAdUnloaded = 7,
#endif
#if __IPHONE_9_3 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorAssetLoadFailure = 8,
#endif
#if __IPHONE_10_3 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorAdResponseValidateFailure = 9,
    ADErrorAdAssetLoadPending = 10
#endif
} NS_ENUM_DEPRECATED(10_14, 10_14, 4_0, 10_0);

/*!
 * @enum ADAdType
 *
 * @const ADAdTypeBanner A device-width banner ad. The banner height varies with
 * device type and orientation:
 *
 *   • On iPhone; portrait = DEVICE_WIDTH × 50px, landscape = DEVICE_WIDTH × 32px
 *   • On iPad; both portrait & landscape = DEVICE_WIDTH × 66px
 *
 * @const ADAdTypeMediumRectangle An 320 × 250px ad, based on the International
 * Advertising Bureau's "Medium Rectangle" Interactive Marketing Unit.
 *
 * @discussion
 * Ad types that can be passed to -[ADBannerView -initWithAdType:].
 */
typedef NS_ENUM(NSInteger, ADAdType) {
    ADAdTypeBanner,
    ADAdTypeMediumRectangle
} NS_ENUM_DEPRECATED(10_14, 10_14, 6_0, 10_0);

@protocol ADBannerViewDelegate;

/*!
 * @class ADBannerView
 *
 * @discussion
 * Provides a view for displaying iAds in an application. iAds are automatically
 * loaded, presented, and refreshed. When a banner view is tapped, the iAd will
 * begin its action. In most cases, the action displays a fullscreen interactive
 * iAd.
 *
 * Note: ADBannerViews must be added to a view hierarchy managed by a
 * UIViewController. If view controller containment is being used, the controller
 * managing the banner view must be correctly configured to ensure banner action
 * presentation works correctly.
 */
NS_CLASS_DEPRECATED(10_14, 10_14, 4_0, 10_0)
@interface ADBannerView : UIView

/*!
 * @method initWithAdType:
 *
 * @discussion
 * Initialize the view with a specific ad type. The ad type cannot be changed
 * after initialization.
 */
- (nullable instancetype)initWithAdType:(ADAdType)type NS_AVAILABLE_IOS(6_0);

/*!
 * @property adType
 *
 * @return
 * The banner view's ad type.
 */
@property (nonatomic, readonly) ADAdType adType NS_AVAILABLE_IOS(6_0);

/*!
 * @property delegate
 *
 * @discussion
 * The banner view delegate is notified when events related to the banner view
 * and current ad occur, such as when a new ad is loaded, when errors occur
 * while fetching ads, or when banner actions begin and end.
 *
 * On iOS 5 and later, this property is a weak reference and cannot be used with
 * objects that modify the behavior of release or retain.
 */
@property (nullable, nonatomic, weak) id<ADBannerViewDelegate> delegate;

/*!
 * @property bannerLoaded
 *
 * @return
 * YES if an ad is currently loaded, NO otherwise.
 */
@property (nonatomic, readonly, getter=isBannerLoaded) BOOL bannerLoaded;

/*!
 * @property bannerViewActionInProgress
 *
 * @return
 * YES if the user is currently engaged with a fullscreen interactive ad.
 */
@property (nonatomic, readonly, getter=isBannerViewActionInProgress) BOOL bannerViewActionInProgress;

/*!
 * @method cancelBannerViewAction
 *
 * @discussion
 * Cancels the current in-progress banner view action. This should only be used
 * in cases where the user's attention is required immediately.
 */
- (void)cancelBannerViewAction;

/*!
 * @property advertisingSection
 *
 * @discussion
 * Reserved for future use.
 */
@property (nullable, nonatomic, copy) NSString *advertisingSection;

@end

/*!
 * @protocol ADBannerViewDelegate
 */
NS_DEPRECATED(10_14, 10_14, 4_1, 13_0)
@protocol ADBannerViewDelegate <NSObject>
@optional

/*!
 * @method bannerViewWillLoadAd:
 *
 * @discussion
 * Called when a banner has confirmation that an ad will be presented, but
 * before the resources necessary for presentation have loaded.
 */
- (void)bannerViewWillLoadAd:(ADBannerView *)banner  NS_AVAILABLE_IOS(5_0);

/*!
 * @method bannerViewDidLoadAd:
 *
 * @discussion
 * Called each time a banner loads a new ad. Once a banner has loaded an ad, it
 * will display it until another ad is available.
 *
 * It's generally recommended to show the banner view when this method is called,
 * and hide it again when bannerView:didFailToReceiveAdWithError: is called.
 */
- (void)bannerViewDidLoadAd:(ADBannerView *)banner;

/*!
 * @method bannerView:didFailToReceiveAdWithError:
 *
 * @discussion
 * Called when an error has occurred while attempting to get ad content. If the
 * banner is being displayed when an error occurs, it should be hidden
 * to prevent display of a banner view with no ad content.
 *
 * @see ADError for a list of possible error codes.
 */
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error;

/*!
 * @method bannerViewActionShouldBegin:willLeaveApplication:
 *
 * Called when the user taps on the banner and some action is to be taken.
 * Actions either display full screen content modally, or take the user to a
 * different application.
 *
 * The delegate may return NO to block the action from taking place, but this
 * should be avoided if possible because most ads pay significantly more when
 * the action takes place and, over the longer term, repeatedly blocking actions
 * will decrease the ad inventory available to the application.
 *
 * Applications should reduce their own activity while the advertisement's action
 * executes.
 */
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave;

/*!
 * @method bannerViewActionDidFinish:
 *
 * Called when a modal action has completed and control is returned to the
 * application. Games, media playback, and other activities that were paused in
 * bannerViewActionShouldBegin:willLeaveApplication: should resume at this point.
 */
- (void)bannerViewActionDidFinish:(ADBannerView *)banner;

@end

NS_DEPRECATED(10_14, 10_14, 12_0, 13_0)
CGSize ADClampedBannerSize(CGSize size);

NS_ASSUME_NONNULL_END
