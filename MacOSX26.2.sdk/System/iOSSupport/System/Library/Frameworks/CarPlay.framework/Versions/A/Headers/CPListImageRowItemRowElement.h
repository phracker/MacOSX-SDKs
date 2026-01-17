//
//  CPListImageRowItemRowElement.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPListImageRowItemElement.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItemRowElement: CPListImageRowItemElement

/**
 Initialize an element that is constituted of an image, title and subtitle. Only image is required while the two others can be omitted.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.
 
 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @note The expected image size is given by +[CPListImageRowItemRowElement maximumImageSize]. Images provided will be resized to this size if necessary.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 
 @param image The image associated to the element.
 @param title The title of the element.
 @param subtitle The subtitle of the element.
 */
- (instancetype)initWithImage:(UIImage *)image
                        title:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle;

/**
 The title associated with this element.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 The subtitle associated with this element.
 */
@property (nonatomic, copy, nullable) NSString *subtitle;

@end

NS_ASSUME_NONNULL_END
