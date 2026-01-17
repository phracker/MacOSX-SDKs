//
//  PKEraserTool.h
//  PencilKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <PencilKit/PKTool.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) typedef NS_ENUM(NSInteger, PKEraserType) {
    PKEraserTypeVector,
    PKEraserTypeBitmap,
    PKEraserTypeFixedWidthBitmap API_AVAILABLE(ios(16.4), macos(13.3))
} NS_REFINED_FOR_SWIFT;

/// An eraser tool for erasing parts of a drawing.
API_AVAILABLE(ios(13.0), macos(10.15))
NS_SWIFT_SENDABLE
@interface PKEraserTool : PKTool

/// The eraser type.
@property (nonatomic, readonly) PKEraserType eraserType;

- (instancetype)initWithEraserType:(PKEraserType)eraserType NS_DESIGNATED_INITIALIZER;

/// Create a new eraser tool with a width.
/// @param eraserType The type of eraser.
/// @param width The width of the eraser.
- (instancetype)initWithEraserType:(PKEraserType)eraserType width:(CGFloat)width NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(16.4), macos(13.3));

/// The width of the eraser.
@property (nonatomic, readonly) CGFloat width API_AVAILABLE(ios(16.4), macos(13.3));

/// The default width for an eraser type.
+ (CGFloat)defaultWidthForEraserType:(PKEraserType)eraserType API_AVAILABLE(ios(16.4), macos(13.3));

/// The minimum width for an eraser type.
+ (CGFloat)minimumWidthForEraserType:(PKEraserType)eraserType API_AVAILABLE(ios(16.4), macos(13.3));

/// The maximum width for an eraser type.
+ (CGFloat)maximumWidthForEraserType:(PKEraserType)eraserType API_AVAILABLE(ios(16.4), macos(13.3));

@end

NS_ASSUME_NONNULL_END
