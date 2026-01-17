//
//  CPListImageRowItemCardElement.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <CarPlay/CPListImageRowItemElement.h>
#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItemCardElement: CPListImageRowItemElement

/**
 Initialize an element that is constituted of an image, boolean to entirely cover the element with the image, title, subtitle and a tint color.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.
 
 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @note The expected image size is given by +[CPListImageRowItemCardElement maximumImageSize] or by +[CPListImageRowItemCardElement maximumFullHeightImageSize] if @c showsImageFullHeight is true. Images provided will be resized to this size if necessary.

 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 
 @param image The image associated to the element.
 @param showsImageFullHeight Determines if the image should entirely cover the card
 @param title The title of the element.
 @param subtitle The subtitle of the element.
 @param tintColor The color used as background if @c showsImageFullHeight is true, part of the gradient color at the bottom of the card otherwise.
 */

- (instancetype)initWithImage:(UIImage *)image
          showsImageFullHeight:(BOOL)showsImageFullHeight
                        title:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
                    tintColor:(nullable UIColor *)tintColor;

/**
 The title associated with this element.
 */
@property (nonatomic, copy) NSString *title;

/**
 The subtitle associated with this element.
 */
@property (nonatomic, copy, nullable) NSString *subtitle;

/**
 A Boolean value indicating whether the element should be fill with the image.
 
 @discussion Set the value of this property to @c YES to fill the element with the image or @c NO to use a rounded square image that does not fill the card.
 */
@property (nonatomic, assign, readonly) BOOL showsImageFullHeight;

/**
 A UIColor used to tint the element. When @c showsImageFullHeight is true, the tint color is applied behind the labels at the bottom of the card. Otherwise, this color is part of the gradient color at the bottom of the card.

 If this value is nil, iOS will use secondarySystemBackground color.
 */
@property (nonatomic, copy, nullable) UIColor *tintColor;

/**
 The expected image size for the image in your @c CPListImageRowItemCardElement when @c showsImageFullHeight is false. Images provided
 will be resized to this size.

 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumImageSize;

/**
 The expected image size for the image in your @c CPListImageRowItemCardElement when @c showsImageFullHeight is  true. Images provided
 will be resized to this size.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumFullHeightImageSize;

@end

NS_ASSUME_NONNULL_END
