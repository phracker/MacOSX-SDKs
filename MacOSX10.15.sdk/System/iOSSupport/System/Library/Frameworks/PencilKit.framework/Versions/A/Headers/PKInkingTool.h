//
//  PKInkingTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <PencilKit/PencilKit.h>
#import <PencilKit/PKTool.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NSString * PKInkType NS_TYPED_ENUM API_AVAILABLE(ios(13.0)) NS_REFINED_FOR_SWIFT;
API_AVAILABLE(ios(13.0)) FOUNDATION_EXPORT PKInkType const PKInkTypePen;
API_AVAILABLE(ios(13.0)) FOUNDATION_EXPORT PKInkType const PKInkTypePencil;
API_AVAILABLE(ios(13.0)) FOUNDATION_EXPORT PKInkType const PKInkTypeMarker;


/// A tool for drawing on a PKCanvasView.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(13.0))
@interface PKInkingTool : PKTool

/// Create a new ink, specifying its type, color, and width.
///
/// @param type The type of ink.
/// @param color The color of the ink.
/// @param width The width of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color width:(CGFloat)width NS_DESIGNATED_INITIALIZER;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color width:(CGFloat)width NS_DESIGNATED_INITIALIZER;
#endif
/// Create a new ink, specifying its type and color, using a default width.
///
/// @param type The type of ink.
/// @param color The color of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color;
#endif

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

@end
NS_ASSUME_NONNULL_END
