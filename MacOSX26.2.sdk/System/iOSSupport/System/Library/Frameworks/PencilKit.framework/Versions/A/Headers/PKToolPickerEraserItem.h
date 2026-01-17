//
//  PKToolPickerEraserItem.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <PencilKit/PKToolPickerItem.h>
#import <PencilKit/PKEraserTool.h>

#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/// A user interface for an eraser tool item in PKToolPicker.
API_AVAILABLE(ios(18.0), visionos(2.0), macos(26.0))
@interface PKToolPickerEraserItem : PKToolPickerItem

/// Create a new eraser tool item.
- (instancetype)initWithEraserType:(PKEraserType)eraserType NS_REFINED_FOR_SWIFT;

/// Create a new eraser tool item with a width.
/// @param eraserType The type of eraser.
/// @param width The width of the eraser.
- (instancetype)initWithEraserType:(PKEraserType)eraserType width:(CGFloat)width NS_REFINED_FOR_SWIFT;

/// An eraser tool for erasing parts of a drawing.
@property (nonatomic, readonly) PKEraserTool *eraserTool NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
