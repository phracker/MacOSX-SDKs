//
//  TCTouchControllerDescriptor.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>

#import <Metal/Metal.h>

@class MTKView;

NS_ASSUME_NONNULL_BEGIN

/// A descriptor for configuring a touch controller.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCTouchControllerDescriptor : NSObject

/// The Metal device to use for rendering.
@property (nonatomic, readwrite, strong) id<MTLDevice> device;

/// The size of the view the touch controller's drawable is embedded in, in points.
@property (nonatomic, readwrite, assign) CGSize size;

/// The size of the drawable to which the touch controller's contents be drawn, in native pixels.
@property (nonatomic, readwrite, assign) CGSize drawableSize;

/// The pixel format for the drawable texture.
@property (nonatomic, readwrite, assign) MTLPixelFormat colorPixelFormat;

/// The pixel format for the depth attachment.
@property (nonatomic, readwrite, assign) MTLPixelFormat depthAttachmentPixelFormat;

/// The pixel format for the stencil attachment.
@property (nonatomic, readwrite, assign) MTLPixelFormat stencilAttachmentPixelFormat;

/// The number of samples per pixel for multisampling.
@property (nonatomic, readwrite, assign) NSUInteger sampleCount;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithMTKView:(MTKView *)mtkView;

@end


NS_ASSUME_NONNULL_END
#endif
