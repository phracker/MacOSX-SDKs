//
//  PKToolPickerCustomItem.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <PencilKit/PKToolPickerItem.h>

#import <CoreGraphics/CoreGraphics.h>

@class PKToolPickerCustomItemConfiguration;
@class UIColor;

NS_ASSUME_NONNULL_BEGIN

/// A user interface for a custom tool item in PKToolPicker.
API_AVAILABLE(ios(18.0), visionos(2.0))
@interface PKToolPickerCustomItem : PKToolPickerItem

/// Create a new custom tool picker item.
/// @param configuration The configuration for the custom item.
- (instancetype)initWithConfiguration:(PKToolPickerCustomItemConfiguration *)configuration NS_REFINED_FOR_SWIFT;

/// The configuration of the custom tool item.
@property (nonatomic, readonly) PKToolPickerCustomItemConfiguration *configuration NS_REFINED_FOR_SWIFT;

/// The current color of the custom tool item.
@property (nonatomic, strong) UIColor *color;

/// Present color selection UI to the user.
/// Defaults to the value set in `configuration`.
@property (nonatomic, assign) BOOL allowsColorSelection;

/// The current width of the custom tool item.
@property (nonatomic, assign) CGFloat width;

/// Causes a new image for this tool item to be requested from `configuration`'s `imageProvider` block.
/// Call this method when the image for the tool item would be different from the one previously provided.
/// It is not necessary to call this method when attributes provided by PencilKit, like `color` or `width`, are changed;
/// the block will be called automatically when those are mutated.
- (void)reloadImage;

@end

NS_ASSUME_NONNULL_END
