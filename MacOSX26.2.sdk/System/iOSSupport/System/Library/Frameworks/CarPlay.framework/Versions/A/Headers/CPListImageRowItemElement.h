//
//  CPListImageRowItemElement.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Abstract superclass for a a row item element object.
 */
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItemElement : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 The image associated with this element.
 */
@property (nonatomic, copy) UIImage *image;

/**
 The expected image size for the image in your @c CPListImageRowItemElement. Images provided
 will be resized to this size.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumImageSize;

/**
 A Boolean value indicating whether the list element is enabled.
 
 @discussion Set the value of this property to @c YES to enable the list element or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

@end

NS_ASSUME_NONNULL_END
