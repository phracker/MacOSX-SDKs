//
//  PKInkingTool.h
//  PencilKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <PencilKit/PKTool.h>
#import <PencilKit/PKInkType.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

NS_ASSUME_NONNULL_BEGIN


@class PKInk;

/// A tool for drawing on a PKCanvasView.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(13.0), macos(10.15))
@interface PKInkingTool : PKTool

/// Create a new inking tool, specifying its type, color, and width.
///
/// @param type The type of ink.
/// @param color The color of the ink.
/// @param width The width of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color width:(CGFloat)width NS_DESIGNATED_INITIALIZER;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color width:(CGFloat)width NS_DESIGNATED_INITIALIZER;
#endif

/// Create a new inking tool, specifying its type and color, using a default width.
///
/// @param type The type of ink.
/// @param color The color of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color;
#endif

/// Create a new inking tool for the provided ink.
///
/// @param ink The ink to use.
/// @param width The width of stroke to create.
- (instancetype)initWithInk:(PKInk *)ink width:(CGFloat)width API_AVAILABLE(ios(14.0));

/// The default width for an ink of a type.
+ (CGFloat)defaultWidthForInkType:(PKInkType)inkType;

/// The minimum width for an ink of a type.
+ (CGFloat)minimumWidthForInkType:(PKInkType)inkType;

/// The maximum width for an ink of a type.
+ (CGFloat)maximumWidthForInkType:(PKInkType)inkType;

/// The type of ink, eg. pen, pencil...
@property (nonatomic, readonly) PKInkType inkType;

/// The base color of this ink.
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIColor *color;

/// Converts a color from one user interface style to another.
///
/// A dark color in a light user interface style is converted to a lighter color in a
/// dark user interface style. This conversion is not guaranteed to roundtrip losslessly, or to
/// be consistent between different OS versions.
///
/// @param color The color to convert
/// @param fromUserInterfaceStyle The user interface style to convert the color from.
/// @param toUserInterfaceStyle The user interface style to convert the color to.
+ (UIColor *)convertColor:(UIColor *)color fromUserInterfaceStyle:(UIUserInterfaceStyle)fromUserInterfaceStyle to:(UIUserInterfaceStyle)toUserInterfaceStyle;
#else
@property (nonatomic, readonly) NSColor *color;
#endif

/// The base width of the ink.
@property (nonatomic, readonly) CGFloat width;

/// The ink that this tool will create strokes with.
@property (nonatomic, readonly) PKInk *ink API_AVAILABLE(ios(14.0));

@end
NS_ASSUME_NONNULL_END
