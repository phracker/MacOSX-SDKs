/*
        NSOpenGLView.h
        Application Kit
        Copyright (c) 2000-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>

NS_ASSUME_NONNULL_BEGIN

@class NSOpenGLContext, NSOpenGLPixelFormat;

@interface NSOpenGLView : NSView {
  @private
    NSOpenGLContext*     _openGLContext;
    NSOpenGLPixelFormat* _pixelFormat;
    NSInteger                _reserved1;
    NSInteger                _reserved2;
    NSInteger                _reserved3;
}

+ (NSOpenGLPixelFormat*)defaultPixelFormat;

- (nullable instancetype)initWithFrame:(NSRect)frameRect pixelFormat:(nullable NSOpenGLPixelFormat*)format;

@property (nullable, strong) NSOpenGLContext *openGLContext;
- (void)clearGLContext;

- (void)update;		// moved or resized
- (void)reshape;	// scrolled, moved or resized

@property (nullable, strong) NSOpenGLPixelFormat *pixelFormat;

- (void)prepareOpenGL;
@end

@interface NSView (NSOpenGLSurfaceResolution)

/* Specifies whether a given view instance wants, and is capable of correctly handling, an OpenGL backing surface (framebuffer) with resolution greater than 1 pixel per point.  This property is relevant only for views to which an NSOpenGLContext is bound (including, but not limited to, NSOpenGLViews); its value does not affect the behavior of other views, including CALayer-backed views (which may choose to render at a higher surface resolution independent of this property's value.  For compatibility, wantsBestResolutionOpenGLSurface defaults to NO, providing a 1 pixel per point framebuffer regardless of the backing scale factor for the display the view occupies.  (When the backing scale factor is > 1.0, the rendered surface contents are scaled up to the appropriate apparent size.)  Setting this property to YES for a given view gives AppKit permission to allocate a higher-resolution framebuffer when appropriate for the backing scale factor and target display.  AppKit may vary the surface resolution when the display mode is changed or the view is moved to a different display, but with this property set to YES it is capable of allocating a surface of greater than 1 pixel per point for the view.

To function correctly with wantsBestResolutionOpenGLSurface set to YES, a view must take care to perform correct conversions between view units and pixel units when needed.  For example: The common practice of passing the width and height of [self bounds] to glViewport() will yield incorrect results (partial instead of complete coverage of the render surface) at backing scale factors other than 1.0, since the parameters to glViewport() must be expressed in pixels. When wantsBestResolutionOpenGLSurface is set to YES, glViewPort will automatically be called before update and reshape. If you wish to call it yourself (for backwards compatibility, or to draw to a subrect of the surface) use the dimensions of [self convertRectToBacking:[self bounds]], which are in appropriate (pixel) units.

This property is archived (keyed archiving required).

For testing purposes only, the effect of this property can be overridden globally for all views in a process, using the "NSSurfaceResolution" user default.  If NSSurfaceResolution is set to "Device", all views that have surfaces (including not only OpenGL surfaces, but layer tree render surfaces as well) will be opted into using the best resolution surface for the primary display the view is presented on.  This can be used to quickly assess whether an apps view's are ready for non-1x surfaces.  If NSSurfaceResolution is set to "1x", all views that have surfaces will be opted into using 1x (1 pixel per point) surfaces, independent of the display or backing scale factor.  If NSSurfaceResolution is set to any other value, or no value is present for it, then wantsBestResolutionOpenGLSurface will be consulted as described above for views that perform NSOpenGL rendering, and AppKit will separately determine the appropriate resolution for other surfaces, as also described above.
*/
@property BOOL wantsBestResolutionOpenGLSurface NS_AVAILABLE_MAC(10_7);

@end

@interface NSView (NSExtendedDynamicRange)

/* If any view on the screen has this enabled, the NSScreen which the OpenGL surface is on may have its maximumExtendedDynamicRangeColorComponentValue increased.  When composited by the Window Server, color values rendered by this OpenGL surface will be clamped to the NSScreen’s maximumExtendedDynamicRangeColorComponentValue rather than 1.0.
 */
@property BOOL wantsExtendedDynamicRangeOpenGLSurface NS_AVAILABLE_MAC(10_11);

@end


NS_ASSUME_NONNULL_END
