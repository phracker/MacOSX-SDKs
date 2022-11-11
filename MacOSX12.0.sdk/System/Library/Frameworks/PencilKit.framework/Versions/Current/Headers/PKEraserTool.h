//
//  PKEraserTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <PencilKit/PencilKit.h>
#import <PencilKit/PKTool.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) typedef NS_ENUM(NSInteger, PKEraserType) {
    PKEraserTypeVector,
    PKEraserTypeBitmap
} NS_REFINED_FOR_SWIFT;

/// An eraser tool for erasing parts of a drawing.
API_AVAILABLE(ios(13.0), macos(10.15))
@interface PKEraserTool : PKTool

/// The eraser type.
@property (nonatomic, readonly) PKEraserType eraserType;

- (instancetype)initWithEraserType:(PKEraserType)eraserType NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
