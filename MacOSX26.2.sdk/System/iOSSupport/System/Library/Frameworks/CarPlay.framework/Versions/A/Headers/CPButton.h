//
//  CPButton.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPButton : NSObject

extern CGSize const CPButtonMaximumImageSize;

/**
 Initialize a button for the Contact, POI, or Information templates with a custom image and a handler, called when
 the user taps this button.
 
 @param image An image to be displayed in this button. The maximum image size is given by @c CPButtonMaximumImageSize.
 @param handler A block that will be called when the user taps this button.
 
 @note This class is only available in templates that support buttons with custom images, like the Contact template.
 
 @discussion When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 */
- (instancetype)initWithImage:(UIImage *)image
                      handler:(void (^ _Nullable)(__kindof CPButton *button))handler NS_DESIGNATED_INITIALIZER;

/**
 An optional image, displayed only in templates that support custom images, like the Contact template.
 
 @discussion When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 */
@property (nonatomic, copy, nullable, readonly) UIImage *image;

/**
 A custom title to display for this button, displayed only in templates that allow for custom titles.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 A Boolean value indicating whether the button is enabled.
 
 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
