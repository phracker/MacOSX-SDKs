//
//  CPPointOfInterest.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CarPlay/CPTextButton.h>

NS_ASSUME_NONNULL_BEGIN

@class MKMapItem;

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPointOfInterest : NSObject <NSSecureCoding>

/**
 Initializes a point of interest to be used with @c CPPointOfInterestTemplate .

 @param location Location indicator use by map annotations.
 @param title Primary title for this point of interest.
 @param subtitle Optional: Secondary title for this point of interest.
 @param summary Optional: Summary text for this point of interest.
 @param detailTitle Optional: Title to be used when POI detail card is visible.
 @param detailSubtitle Optional: Subtitle to be used when POI detail card is visible.
 @param detailSummary Optional: Summary text to be used when POI detail card is visible.
 @param pinImage Optional: a custom unselected map annotation image.
 @param selectedPinImage Optional: a custom selected map annotation image.
 
 @note When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.
 
 CPPointOfInterest instances appear on the Point of Interest map view as both selectable items in the table view overlay and as map annotations.
 
 @discussion To properly size your pin images, your app should size them to the display scale of the car screen. See -[CPInterfaceController carTraitCollection].
 */

- (instancetype)initWithLocation:(MKMapItem *)location
                           title:(NSString *)title
                        subtitle:(nullable NSString *)subtitle
                         summary:(nullable NSString *)summary
                     detailTitle:(nullable NSString *)detailTitle
                  detailSubtitle:(nullable NSString *)detailSubtitle
                   detailSummary:(nullable NSString *)detailSummary
                        pinImage:(nullable UIImage *)pinImage
                selectedPinImage:(nullable UIImage *)selectedPinImage NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);
/**
 Initializes a point of interest to be used with @c CPPointOfInterestTemplate.

 @param location Location indicator use by map annotations.
 @param title Primary title for this point of interest.
 @param subtitle Optional: Secondary title for this point of interest.
 @param summary Optional: Summary text for this point of interest.
 @param detailTitle Optional: Title to be used when POI detail card is visible.
 @param detailSubtitle Optional: Subtitle to be used when POI detail card is visible.
 @param detailSummary Optional: Summary text to be used when POI detail card is visible.
 @param pinImage Optional: a custom map annotation image.
 
 @note When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.
 
 CPPointOfInterest instances appear on the Point of Interest map view as both selectable items in the table view overlay and as map annotations.
 
 @discussion To properly size your pin images, your app should size them to the display scale of the car screen. See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithLocation:(MKMapItem *)location
                           title:(NSString *)title
                        subtitle:(nullable NSString *)subtitle
                         summary:(nullable NSString *)summary
                     detailTitle:(nullable NSString *)detailTitle
                  detailSubtitle:(nullable NSString *)detailSubtitle
                   detailSummary:(nullable NSString *)detailSummary
                        pinImage:(nullable UIImage *)pinImage;

/**
 If you provide a custom image for this point of interest, the unselected image must be this size. Any image larger than this size will be resized.
*/
@property (nonatomic, class, readonly) CGSize pinImageSize API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/**
  If you provide a custom image for this point of interest, the selected image must be this size. Any image larger than this size will be resized.
*/
@property (nonatomic, class, readonly) CGSize selectedPinImageSize API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/**
 Location associated with this point of interest.
 */
@property (nonatomic, strong) MKMapItem *location;

/**
 Primary title for this point of interest.
 */
@property (nonatomic, copy) NSString *title;

/**
 Subtitle for this point of interest.
 */
@property (nonatomic, copy, nullable) NSString *subtitle;

/**
 Summary text for this point of interest.
 */
@property (nonatomic, copy, nullable) NSString *summary;

/**
 Title to be used when POI detail card is visible.
 
 @note If not provided, the point of interest will fall back to displaying @c title.
 */
@property (nonatomic, copy, nullable) NSString *detailTitle;

/**
 Subtitle to be used when POI detail card is visible.
 
 @note If not provided, the point of interest will fall back to displaying @c subtitle.
 */
@property (nonatomic, copy, nullable) NSString *detailSubtitle;

/**
 Summary text to be used when POI detail card is visible.
 
 @note If not provided, the point of interest will fall back to displaying @c summary.
 */
@property (nonatomic, copy, nullable) NSString *detailSummary;

/**
 Image used for map view unselected annotations.
 
 @discussion To properly size your pin image, your app should size them to the display scale of the car screen. See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, strong, nullable) UIImage *pinImage;

/**
 Image used for map view selected annotation.
 
 @discussion To properly size your pin image, your app should size them to the display scale of the car screen. See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, strong, nullable) UIImage *selectedPinImage API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/**
Point of Interest detail card buttons.
*/
@property (nullable, nonatomic, strong) CPTextButton *primaryButton;
@property (nullable, nonatomic, strong) CPTextButton *secondaryButton;

/**
 Any custom data or an object associated with this Point of Interest.
 */
@property (nullable, nonatomic, strong) id userInfo;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
