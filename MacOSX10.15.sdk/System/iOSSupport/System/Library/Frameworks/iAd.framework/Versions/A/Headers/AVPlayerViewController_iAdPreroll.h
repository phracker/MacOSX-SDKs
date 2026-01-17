//
//  AVPlayerViewController_iAdPreroll.h
//  iAd
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#import <AVKit/AVPlayerViewController.h>

NS_CLASS_DEPRECATED(10_14, 10_14, 8_0, 13_0) @interface AVPlayerViewController (iAdPreroll)

NS_ASSUME_NONNULL_BEGIN

/*!
 * @method +preparePrerollAds
 *
 * @discussion
 * Inform iAd that the application intends to use AVPlayerViewController's
 * -playPrerollAdWithCompletionHandler: API. Ad metadata will be fetched eagerly,
 * increasing the likelihood of an ad being available when first requested.
 */
+ (void)preparePrerollAds NS_AVAILABLE_IOS(8_0);

/*!
 * @method -playPrerollAdWithCompletionHandler:
 *
 * @discussion
 * Request playback of a pre-roll video iAd.
 *
 * If -[AVPlayerViewController player] begins playing during a pre-roll ad, the
 * video ad will stop immediately.
 *
 * The completion handler's error argument will be non-nil if the pre-roll ad
 * could not be played. Errors can occur for a number of reasons, such as lack
 * of ad inventory, exceeding the maximum pre-roll ad playback frequency, iAd
 * account configuration issues, and media playback issues. See ADError for an
 * exhaustive list of possible errors.
 *
 * Passing nil as the completion handler is an error and will throw an exception.
 */
- (void)playPrerollAdWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(8_0);

/*!
 * @method -cancelPreroll
 *
 * @discussion
 * Cancel pre-roll video ad playback.
 */
- (void)cancelPreroll NS_AVAILABLE_IOS(8_0);

@end

NS_ASSUME_NONNULL_END
#endif
