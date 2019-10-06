#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISwitch.h>)
//
//  UISwitch.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(tvos) @interface UISwitch : UIControl <NSCoding>

@property(nullable, nonatomic, strong) UIColor *onTintColor API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
@property(nullable, nonatomic, strong) UIColor *thumbTintColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

@property(nullable, nonatomic, strong) UIImage *onImage API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
@property(nullable, nonatomic, strong) UIImage *offImage API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

@property(nonatomic,getter=isOn) BOOL on;

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;      // This class enforces a size appropriate for the control, and so the frame size is ignored.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (void)setOn:(BOOL)on animated:(BOOL)animated; // does not send action

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISwitch.h>
#endif
