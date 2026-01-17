/*
 NSSliderTouchBarItem.h
 Application Kit
 Copyright (c) 2016-2018, Apple Inc.
 All rights reserved.
 */

#import <AppKit/NSUserInterfaceCompression.h>
#import <AppKit/NSTouchBarItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSliderAccessory, NSSlider;

typedef CGFloat NSSliderAccessoryWidth NS_TYPED_EXTENSIBLE_ENUM NS_AVAILABLE_MAC(10_12_2);
/// The default width for slider accessories.
APPKIT_EXTERN const NSSliderAccessoryWidth NSSliderAccessoryWidthDefault NS_AVAILABLE_MAC(10_12_2);
/// The standard "wide" width for slider accessories.
APPKIT_EXTERN const NSSliderAccessoryWidth NSSliderAccessoryWidthWide NS_AVAILABLE_MAC(10_12_2);

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSSliderTouchBarItem : NSTouchBarItem {
@private
    __kindof NSView *_view APPKIT_IVAR;
    id _autounbinder APPKIT_IVAR;
    __weak id _target APPKIT_IVAR;
    SEL _action APPKIT_IVAR;
    NSString *_customizationLabel APPKIT_IVAR;

#if !__OBJC2__
    void *_sliderTouchBarItemReserved[4] __unused APPKIT_IVAR;
#endif /* !__OBJC2__ */
}

@property (readonly, nonnull) NSView<NSUserInterfaceCompression> *view;

/// The slider displayed by the bar item. It is automatically created, but can be set to a custom subclass. doubleValue, minValue, maxValue, etc can all be read and set through the slider.
@property (strong) NSSlider *slider;

/// The text label displayed along with the slider. If set to nil, the label will not have space reserved in the item.
@property (nullable, copy) NSString *label;

/// The accessory that appears on the end of the slider with the minimum value
@property (strong, nullable) NSSliderAccessory *minimumValueAccessory;
/// The accessory that appears on the end of the slider with the maximum value
@property (strong, nullable) NSSliderAccessory *maximumValueAccessory;
/// The width of the value accessories. Defaults to `.default`, but can be set to `.wide` or a custom value.
@property NSSliderAccessoryWidth valueAccessoryWidth;

/// The target of the item, notified when the slider or accessories receive user interaction.
@property (weak, nullable) id target;
/// The action of the item, called when the slider or accessories receive user interaction.
@property (nullable) SEL action;

/// The localized string labelling this item during user customization. The default value is empty string.
@property (readwrite, copy, null_resettable) NSString *customizationLabel;

@end

NS_ASSUME_NONNULL_END
