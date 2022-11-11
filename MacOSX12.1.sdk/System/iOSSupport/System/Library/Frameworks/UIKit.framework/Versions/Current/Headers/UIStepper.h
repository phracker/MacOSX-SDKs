#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIStepper.h>)
//
//  UIStepper.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIControl.h>

NS_ASSUME_NONNULL_BEGIN

@class UIButton, UIImageView;

UIKIT_EXTERN API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIStepper : UIControl

@property(nonatomic,getter=isContinuous) BOOL continuous; // if YES, value change events are sent any time the value changes during interaction. default = YES
@property(nonatomic) BOOL autorepeat;                     // if YES, press & hold repeatedly alters value. default = YES
@property(nonatomic) BOOL wraps;                          // if YES, value wraps from min <-> max. default = NO

@property(nonatomic) double value;                        // default is 0. sends UIControlEventValueChanged. clamped to min/max
@property(nonatomic) double minimumValue;                 // default 0. must be less than maximumValue
@property(nonatomic) double maximumValue;                 // default 100. must be greater than minimumValue
@property(nonatomic) double stepValue;                    // default 1. must be greater than 0

// a background image which will be 3-way stretched over the whole of the control. Each half of the stepper will paint the image appropriate for its state
- (void)setBackgroundImage:(nullable UIImage*)image forState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage*)backgroundImageForState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

// an image which will be painted in between the two stepper segments. The image is selected depending both segments' state
- (void)setDividerImage:(nullable UIImage*)image forLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage*)dividerImageForLeftSegmentState:(UIControlState)state rightSegmentState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

// the glyph image for the plus/increase button
- (void)setIncrementImage:(nullable UIImage *)image forState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)incrementImageForState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

// the glyph image for the minus/decrease button
- (void)setDecrementImage:(nullable UIImage *)image forState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)decrementImageForState:(UIControlState)state API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIStepper.h>
#endif
