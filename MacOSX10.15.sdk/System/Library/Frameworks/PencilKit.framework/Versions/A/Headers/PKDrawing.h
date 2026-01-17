//
//  PKDrawing.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif


NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif
/// The UTType for storing drawing data.
extern const CFStringRef PKAppleDrawingTypeIdentifier API_AVAILABLE(ios(13.0), macos(10.15));
#ifdef __cplusplus
}
#endif

/// The data model object for storing drawing data created from PKCanvasView.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(13.0), macos(10.15))
@interface PKDrawing : NSObject <NSCopying, NSSecureCoding>

/// Initializes and returns a blank drawing.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Initializes and returns the drawing with the specified data.
///
/// @param data The data containing the drawing data.
/// @param error If an error occurs, upon return the NSError object describes the error.
///   Set to NULL to ignore errors.
/// @return On success, an initialized PKDrawing object. If nil, the outError parameter
///   contains an NSError instance describing the problem.
- (nullable instancetype)initWithData:(NSData *)data error:(NSError * _Nullable *)error NS_DESIGNATED_INITIALIZER;

/// Generate a data representation of the drawing.
///
/// @return A NSData object containing a representation of the drawing.
- (NSData *)dataRepresentation;

/// The bounds of the drawing's contents, taking into account the rendered width of all content.
/// If these bounds are used to render an image with `imageFromRect:scale:`, no contents will be cropped.
@property (nonatomic, readonly) CGRect bounds;

/// Renders the drawing to an image.
///
/// @param rect The rect in the drawing to render.
/// @param scale The scale of image to render. If you specify a value of 0.0, the scale factor is set to the
/// scale factor of the device’s main screen.
/// @return A non-opaque image of this drawing with pixel dimensions `rect.size * scale`.
#if TARGET_OS_IPHONE
- (UIImage *)imageFromRect:(CGRect)rect scale:(CGFloat)scale;
#else
- (NSImage *)imageFromRect:(CGRect)rect scale:(CGFloat)scale;
#endif

/// Returns a new drawing with `transform` applied.
///
/// @param transform The transform to apply to this drawing.
/// @return A new copy of this drawing with `transform` applied.
- (PKDrawing *)drawingByApplyingTransform:(CGAffineTransform)transform;

/// Returns a new drawing by appending the contents of `drawing` on top of the receiver’s contents.
///
/// @param drawing The drawing to append.
/// @return A new copy of this drawing with `drawing` appended onto it.
- (PKDrawing *)drawingByAppendingDrawing:(PKDrawing *)drawing;

@end

NS_ASSUME_NONNULL_END
