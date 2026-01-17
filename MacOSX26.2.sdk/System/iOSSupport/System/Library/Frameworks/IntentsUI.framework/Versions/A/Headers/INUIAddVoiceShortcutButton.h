//
//  INUIAddVoiceShortcutButton
//  IntentsUI
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, INUIAddVoiceShortcutButtonStyle) {
    INUIAddVoiceShortcutButtonStyleWhite = 0,
    INUIAddVoiceShortcutButtonStyleWhiteOutline,
    INUIAddVoiceShortcutButtonStyleBlack,
    INUIAddVoiceShortcutButtonStyleBlackOutline,
    INUIAddVoiceShortcutButtonStyleAutomatic API_AVAILABLE(ios(13.0)),
    INUIAddVoiceShortcutButtonStyleAutomaticOutline API_AVAILABLE(ios(13.0)),
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, macosx, tvos);

@class INShortcut, INUIAddVoiceShortcutButton, INUIAddVoiceShortcutViewController, INUIEditVoiceShortcutViewController;

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@protocol INUIAddVoiceShortcutButtonDelegate <NSObject>

- (void)presentAddVoiceShortcutViewController:(INUIAddVoiceShortcutViewController *)addVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;
- (void)presentEditVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)editVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
IB_DESIGNABLE @interface INUIAddVoiceShortcutButton : UIButton

- (instancetype)initWithStyle:(INUIAddVoiceShortcutButtonStyle)style NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;

@property (nonatomic, readonly) INUIAddVoiceShortcutButtonStyle style;

- (void)setStyle:(INUIAddVoiceShortcutButtonStyle)style API_AVAILABLE(ios(13.0));

@property (nonatomic, weak) id<INUIAddVoiceShortcutButtonDelegate> delegate;
@property (nonatomic, strong, nullable) INShortcut *shortcut;

/*!
 @abstract A custom corner radius for the @c INUIAddVoiceShortcutButton.
 @discussion If the provided corner radius is greater than half of the button’s height, it will be capped at half of the button’s height.
 */
@property (nonatomic, assign) IBInspectable CGFloat cornerRadius API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END
