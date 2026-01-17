//
//  ADBannerView_Deprecated.h
//  iAd
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//

#import <iAd/ADBannerView.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @category ADBannerView (Deprecated)
 *
 * @discussion
 * These banner view resizing APIs have been deprecated and should no longer be
 * used when targeting iOS 6.0 or later.
 *
 * To resize a banner view on iOS 6.0 or later, call -sizeThatFits: on the banner
 * view, specifying the bounds of the view that contains your banner, and use the
 * returned size to resize the banner view. Based on the size you provide, the
 * banner will be sized to the correct width and height for the current device
 * type and orientation, as per the ADAdTypeBanner documentation.
 *
 * A full example of this - including how to handle resizing on devices running
 * older versions of iOS - can be found in the 'iAdSuite' sample project on the
 * ADC website <http://developer.apple.com>.
 */
@interface ADBannerView (Deprecated)

@property (nullable, nonatomic, copy) NSSet *requiredContentSizeIdentifiers NS_DEPRECATED(10_14, 10_14, 4_0, 6_0);

@property (nullable, nonatomic, copy) NSString *currentContentSizeIdentifier NS_DEPRECATED(10_14, 10_14, 4_0, 6_0);

+ (CGSize)sizeFromBannerContentSizeIdentifier:(NSString *)contentSizeIdentifier NS_DEPRECATED(10_14, 10_14, 4_0, 6_0);

@end

extern NSString * const ADBannerContentSizeIdentifier320x50 NS_DEPRECATED(10_14, 10_14, 4_0, 4_2);
extern NSString * const ADBannerContentSizeIdentifier480x32 NS_DEPRECATED(10_14, 10_14, 4_0, 4_2);
extern NSString * const ADBannerContentSizeIdentifierPortrait NS_DEPRECATED(10_14, 10_14, 4_2, 6_0);
extern NSString * const ADBannerContentSizeIdentifierLandscape NS_DEPRECATED(10_14, 10_14, 4_2, 6_0);

NS_ASSUME_NONNULL_END
