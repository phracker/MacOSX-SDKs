//
//  PKToolPickerCustomItemConfiguration.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

@class PKToolPickerCustomItem;
@class UIColor;
@class UIImage;
@class UIViewController;

NS_ASSUME_NONNULL_BEGIN

/// Options for which controls to present.
API_AVAILABLE(ios(18.0), visionos(2.0))
typedef NS_OPTIONS(NSUInteger, PKToolPickerCustomItemControlOptions) {
    
    /// Present neither a width nor opacity control.
    PKToolPickerCustomItemControlNone    = 0,
    
    /// Present a width control if width adjustment is supported.
    PKToolPickerCustomItemControlWidth   = 1 << 0,
    
    /// Present an opacity control if color adjustment is supported.
    PKToolPickerCustomItemControlOpacity = 1 << 1
} NS_SWIFT_NAME(PKToolPickerCustomItem.ControlOptions);

/// A configuration that specifies the appearance and behavior of a item and its contents.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(18.0), visionos(2.0))
@interface PKToolPickerCustomItemConfiguration : NSObject <NSCopying>

/// Create a new eraser tool item with a width.
/// @param identifier The identifier for the tool item.
/// @param name The name for the tool item.
- (instancetype)initWithIdentifier:(NSString *)identifier name:(NSString *)name;

- (instancetype)init NS_UNAVAILABLE;

/// A string that identifies the item in the picker.
/// For example, com.example.myapp.toolpicker.pencil.
/// If multiple items with the same identifier are used to create the picker, only the first instance is used.
@property (nonatomic, copy) NSString *identifier;

/// A short string suitable for presentation to users as the name of the tool.
@property (nonatomic, copy) NSString *name;

/// A block to provide an image representing the given tool item.
/// Return an image at least 150 points tall to avoid the bottom of the item showing during animations.
/// By default, PencilKit uses `name` to label the tool item for accessibility.
/// To override this, set the `accessibilityLabel` of the image returned from this block.
@property (nonatomic, copy, nullable) UIImage *(^imageProvider)(PKToolPickerCustomItem *toolPickerItem);

/// A block to provide a view controller above the system controls in the tool attributes popover.
@property (nonatomic, copy, nullable) UIViewController *(^viewControllerProvider)(PKToolPickerCustomItem *toolPickerItem);

/// Default width for the tool.
/// Default value is 0.
@property (nonatomic, assign) CGFloat defaultWidth;

/// A dictionary representing the UI options for choosing width variants, with each element containing its width value paired with its corresponding image.
/// A dictionary with fewer than 2 elements means no selection UI is available for users to adjust the width value.
/// A dictionary with 2 or more elements means that users can adjust the width value using the selection UI.
/// Provide square images with a size of at least 32pts by 32pts.
@property (nonatomic, copy) NSDictionary<NSNumber *, UIImage *> *widthVariants;

/// Default color for the tool.
/// Default value is black.
@property (nonatomic, strong) UIColor *defaultColor;

/// Present color selection UI to the user.
/// Note that the custom item has a mutable version of this property. This property provides its initial value.
/// Default value is NO.
@property (nonatomic, assign) BOOL allowsColorSelection;

/// Defines which attribute controls are available to be presented in UI such as the tool attributes popover, or inline in the picker presented from a pencil squeeze.
/// Controls for properties which the tool item does not support will not be presented. Excluding a control here does not hide all UI for adjusting that value.
/// For example, excluding the opacity control here will not remove it from the color picker, if the color picker is otherwise available.
/// Defaults to all controls.
@property (nonatomic, assign) PKToolPickerCustomItemControlOptions toolAttributeControls;

@end

NS_ASSUME_NONNULL_END
