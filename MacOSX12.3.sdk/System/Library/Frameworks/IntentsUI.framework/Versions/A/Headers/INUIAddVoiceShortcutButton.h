//
//  INUIAddVoiceShortcutButton
//  IntentsUI
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, INUIAddVoiceShortcutButtonStyle) {
    INUIAddVoiceShortcutButtonStyleWhite = 0,
    INUIAddVoiceShortcutButtonStyleWhiteOutline,
    INUIAddVoiceShortcutButtonStyleBlack,
    INUIAddVoiceShortcutButtonStyleBlackOutline,
    INUIAddVoiceShortcutButtonStyleAutomatic,
    INUIAddVoiceShortcutButtonStyleAutomaticOutline,
} API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos);

@class INShortcut, INUIAddVoiceShortcutButton, INUIAddVoiceShortcutViewController, INUIEditVoiceShortcutViewController;

API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios, watchos, tvos)
@protocol INUIAddVoiceShortcutButtonDelegate <NSObject>

- (void)presentAddVoiceShortcutViewController:(INUIAddVoiceShortcutViewController *)addVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;
- (void)presentEditVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)editVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;

@end

API_AVAILABLE(macos(12.0))
IB_DESIGNABLE @interface INUIAddVoiceShortcutButton : NSButton

- (instancetype)initWithStyle:(INUIAddVoiceShortcutButtonStyle)style NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;

@property (nonatomic) INUIAddVoiceShortcutButtonStyle style;
@property (nonatomic, weak) id<INUIAddVoiceShortcutButtonDelegate> delegate;
@property (nonatomic, strong, nullable) INShortcut *shortcut;

/*!
 @abstract A custom corner radius for the @c INUIAddVoiceShortcutButton.
 @discussion If the provided corner radius is greater than half of the button’s height, it will be capped at half of the button’s height.
 */
@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;

@end

NS_ASSUME_NONNULL_END
