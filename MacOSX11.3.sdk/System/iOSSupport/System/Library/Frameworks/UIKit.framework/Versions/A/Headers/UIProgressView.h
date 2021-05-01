#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIProgressView.h>)
//
//  UIProgressView.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImageView, CAGradientLayer;

typedef NS_ENUM(NSInteger, UIProgressViewStyle) {
    UIProgressViewStyleDefault,     // normal progress bar
    UIProgressViewStyleBar API_UNAVAILABLE(tvos),     // for use in a toolbar
};

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIProgressView : UIView <NSCoding>

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithProgressViewStyle:(UIProgressViewStyle)style; // sets the view height according to the style

@property(nonatomic) UIProgressViewStyle progressViewStyle; // default is UIProgressViewStyleDefault
@property(nonatomic) float progress;                        // 0.0 .. 1.0, default is 0.0. values outside are pinned.
@property(nonatomic, strong, nullable) UIColor* progressTintColor  API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
@property(nonatomic, strong, nullable) UIColor* trackTintColor     API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
@property(nonatomic, strong, nullable) UIImage* progressImage      API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
@property(nonatomic, strong, nullable) UIImage* trackImage         API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

- (void)setProgress:(float)progress animated:(BOOL)animated API_AVAILABLE(ios(5.0));

@property(nonatomic, strong, nullable) NSProgress *observedProgress API_AVAILABLE(ios(9.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIProgressView.h>
#endif
