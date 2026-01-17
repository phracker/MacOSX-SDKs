//
//  PKToolPickerInkingItem.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <PencilKit/PKToolPickerItem.h>
#import <PencilKit/PKInkType.h>

#import <CoreGraphics/CoreGraphics.h>

@class PKInkingTool;
@class UIColor;

NS_ASSUME_NONNULL_BEGIN

/// A user interface for an inking tool item in PKToolPicker.
API_AVAILABLE(ios(18.0), visionos(2.0), macos(26.0))
@interface PKToolPickerInkingItem : PKToolPickerItem

/// Create a new tool picker item with a `PKInkType`.
/// @param inkType The ink type for the tool.
- (instancetype)initWithInkType:(PKInkType)inkType NS_REFINED_FOR_SWIFT;

/// Create a new tool picker item with a `PKInkType`.
/// @param inkType The ink type for the tool.
/// @param color The color for the tool.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)inkType color:(UIColor *)color NS_REFINED_FOR_SWIFT;
#else
- (instancetype)initWithInkType:(PKInkType)inkType color:(NSColor *)color NS_REFINED_FOR_SWIFT;
#endif

/// Create a new tool picker item with a `PKInkType`.
/// @param inkType The ink type for the tool.
/// @param width The width for the tool.
- (instancetype)initWithInkType:(PKInkType)inkType width:(CGFloat)width NS_REFINED_FOR_SWIFT;

/// Create a new tool picker item with a `PKInkType`.
/// @param inkType The ink type for the tool.
/// @param color The color for the tool.
/// @param width The width for the tool.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)inkType color:(UIColor *)color width:(CGFloat)width NS_REFINED_FOR_SWIFT;
#else
- (instancetype)initWithInkType:(PKInkType)inkType color:(NSColor *)color width:(CGFloat)width NS_REFINED_FOR_SWIFT;
#endif

/// Create a new tool picker item with a `PKInkType`.
/// @param inkType The ink type for the tool.
/// @param color The color for the tool.
/// @param width The width for the tool.
/// @param identifier The identifier for the tool item. Passing `nil` resolves to a default value based on the `PKInkType`.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)inkType color:(UIColor *)color width:(CGFloat)width identifier:(nullable NSString *)identifier NS_REFINED_FOR_SWIFT;
#else
- (instancetype)initWithInkType:(PKInkType)inkType color:(NSColor *)color width:(CGFloat)width identifier:(nullable NSString *)identifier NS_REFINED_FOR_SWIFT;
#endif

/// Create a new tool picker item with a `PKInkType`.
/// @param inkType The ink type for the tool.
/// @param color The color for the tool.
/// @param width The width for the tool.
/// @param azimuth The azimuth for the tool.
/// @param identifier The identifier for the tool item. Passing `nil` resolves to a default value based on the `PKInkType`.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)inkType color:(UIColor *)color width:(CGFloat)width azimuth:(CGFloat)azimuth identifier:(nullable NSString *)identifier API_AVAILABLE(ios(26.0), visionos(26.0)) NS_REFINED_FOR_SWIFT;
#else
- (instancetype)initWithInkType:(PKInkType)inkType color:(NSColor *)color width:(CGFloat)width azimuth:(CGFloat)azimuth identifier:(nullable NSString *)identifier NS_REFINED_FOR_SWIFT;
#endif

/// A tool for drawing on a `PKCanvasView`.
@property (nonatomic, readonly) PKInkingTool *inkingTool NS_REFINED_FOR_SWIFT;

/// Present color selection UI to the user.
/// Default value is YES.
@property (nonatomic, assign) BOOL allowsColorSelection;

@end

NS_ASSUME_NONNULL_END
