//
//  CPListImageRowItemGridElement.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPListImageRowItemElement.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItemGridElement: CPListImageRowItemElement

/**
 Initialize an element that is constituted of an image.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.
 
 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @note The expected image size is given by +[CPListImageRowItemGridElement maximumImageSize]. Images provided will be resized to this size if necessary.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 
 @param image The image associated to the element.
 */

- (instancetype)initWithImage:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
