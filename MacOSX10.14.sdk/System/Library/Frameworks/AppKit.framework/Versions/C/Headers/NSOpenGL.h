/*
        NSOpenGL.h
        Application Kit
        Copyright (c) 2000-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>
#import <OpenGL/gltypes.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef GL_SILENCE_DEPRECATION
#define NS_OPENGL_DEPRECATED(minVers, maxVers, ...) NS_DEPRECATED_MAC(minVers, maxVers, __VA_ARGS__)
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers, ...) NS_ENUM_DEPRECATED_MAC(minVers, maxVers, __VA_ARGS__)
#define NS_OPENGL_CLASS_DEPRECATED(minVers, maxVers, ...) NS_CLASS_DEPRECATED_MAC(minVers, maxVers, __VA_ARGS__)
#else
#define NS_OPENGL_DEPRECATED(minVers, maxVers, ...) NS_AVAILABLE_MAC(minVers)
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers, ...) NS_ENUM_AVAILABLE_MAC(minVers)
#define NS_OPENGL_CLASS_DEPRECATED(minVers, maxVers, ...) NS_CLASS_AVAILABLE_MAC(minVers)
#endif

@class NSData, NSView, NSScreen;

/* Option names for NSOpenGLSetOption() and NSOpenGLGetOption() */
typedef NS_ENUM(uint32_t, NSOpenGLGlobalOption) {
    NSOpenGLGOFormatCacheSize  NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 501,	/* Set the size of the pixel format cache        */
    NSOpenGLGOClearFormatCache NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 502,	/* Reset the pixel format cache if true          */
    NSOpenGLGORetainRenderers  NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 503,	/* Whether to retain loaded renderers in memory  */
    NSOpenGLGOUseBuildCache    NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 506,	/* Enable the function compilation block cache.  Off by default.  Must be enabled at startup. */
    
    NSOpenGLGOResetLibrary     NS_ENUM_DEPRECATED_MAC(10_0, 10_4) = 504
} NS_OPENGL_DEPRECATED(10_0, 10_14);


/*
 ** Library global options.
 */
APPKIT_EXTERN void NSOpenGLSetOption(NSOpenGLGlobalOption pname, GLint param)   NS_OPENGL_DEPRECATED(10_0, 10_14);
APPKIT_EXTERN void NSOpenGLGetOption(NSOpenGLGlobalOption pname, GLint * param) NS_OPENGL_DEPRECATED(10_0, 10_14);

/*
 ** Library version.
 */
APPKIT_EXTERN void NSOpenGLGetVersion(GLint * __nullable major, GLint * __nullable minor) NS_OPENGL_DEPRECATED(10_0, 10_14);


/*********************
 ** NSOpenGLPixelFormat
 *********************/

/*
 ** Attribute names for [NSOpenGLPixelFormat initWithAttributes]
 ** and [NSOpenGLPixelFormat getValues:forAttribute:forVirtualScreen].
 */
enum {
    NSOpenGLPFAAllRenderers          NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =   1,	/* choose from all available renderers          */
    NSOpenGLPFATripleBuffer          NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =   3,	/* choose a triple buffered pixel format        */
    NSOpenGLPFADoubleBuffer          NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =   5,	/* choose a double buffered pixel format        */
    NSOpenGLPFAAuxBuffers            NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =   7,	/* number of aux buffers                        */
    NSOpenGLPFAColorSize             NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =   8,	/* number of color buffer bits                  */
    NSOpenGLPFAAlphaSize             NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  11,	/* number of alpha component bits               */
    NSOpenGLPFADepthSize             NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  12,	/* number of depth buffer bits                  */
    NSOpenGLPFAStencilSize           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  13,	/* number of stencil buffer bits                */
    NSOpenGLPFAAccumSize             NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  14,	/* number of accum buffer bits                  */
    NSOpenGLPFAMinimumPolicy         NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  51,	/* never choose smaller buffers than requested  */
    NSOpenGLPFAMaximumPolicy         NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  52,	/* choose largest buffers of type requested     */
    NSOpenGLPFASampleBuffers         NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  55,	/* number of multi sample buffers               */
    NSOpenGLPFASamples               NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  56,	/* number of samples per multi sample buffer    */
    NSOpenGLPFAAuxDepthStencil       NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  57,	/* each aux buffer has its own depth stencil    */
    NSOpenGLPFAColorFloat            NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  58,	/* color buffers store floating point pixels    */
    NSOpenGLPFAMultisample           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  59,    /* choose multisampling                         */
    NSOpenGLPFASupersample           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  60,    /* choose supersampling                         */
    NSOpenGLPFASampleAlpha           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  61,    /* request alpha filtering                      */
    NSOpenGLPFARendererID            NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  70,	/* request renderer by ID                       */
    NSOpenGLPFANoRecovery            NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  72,	/* disable all failure recovery systems         */
    NSOpenGLPFAAccelerated           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  73,	/* choose a hardware accelerated renderer       */
    NSOpenGLPFAClosestPolicy         NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  74,	/* choose the closest color buffer to request   */
    NSOpenGLPFABackingStore          NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  76,	/* back buffer contents are valid after swap    */
    NSOpenGLPFAScreenMask            NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  84,	/* bit mask of supported physical screens       */
    NSOpenGLPFAAllowOfflineRenderers NS_OPENGL_ENUM_DEPRECATED(10_5, 10_14)  =  96,  /* allow use of offline renderers               */
    NSOpenGLPFAAcceleratedCompute    NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  =  97,	/* choose a hardware accelerated compute device */
    NSOpenGLPFAOpenGLProfile         NS_OPENGL_ENUM_DEPRECATED(10_7, 10_14)  =  99,    /* specify an OpenGL Profile to use             */
    NSOpenGLPFAVirtualScreenCount    NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14)  = 128,	/* number of virtual screens in this format     */
    
    NSOpenGLPFAStereo                NS_ENUM_DEPRECATED_MAC(10_0, 10_12)     =   6,
    NSOpenGLPFAOffScreen             NS_ENUM_DEPRECATED_MAC(10_0, 10_7)      =  53,
    NSOpenGLPFAFullScreen            NS_ENUM_DEPRECATED_MAC(10_0, 10_6)      =  54,
    NSOpenGLPFASingleRenderer        NS_ENUM_DEPRECATED_MAC(10_0, 10_9)      =  71,
    NSOpenGLPFARobust                NS_ENUM_DEPRECATED_MAC(10_0, 10_5)      =  75,
    NSOpenGLPFAMPSafe                NS_ENUM_DEPRECATED_MAC(10_0, 10_5)      =  78,
    NSOpenGLPFAWindow                NS_ENUM_DEPRECATED_MAC(10_0, 10_9)      =  80,
    NSOpenGLPFAMultiScreen           NS_ENUM_DEPRECATED_MAC(10_0, 10_5)      =  81,
    NSOpenGLPFACompliant             NS_ENUM_DEPRECATED_MAC(10_0, 10_9)      =  83,
    NSOpenGLPFAPixelBuffer           NS_ENUM_DEPRECATED_MAC(10_3, 10_7)      =  90,
    NSOpenGLPFARemotePixelBuffer     NS_ENUM_DEPRECATED_MAC(10_3, 10_7)      =  91,
};
typedef uint32_t NSOpenGLPixelFormatAttribute NS_OPENGL_DEPRECATED(10_0, 10_14);

/* NSOpenGLPFAOpenGLProfile values */
enum {
    NSOpenGLProfileVersionLegacy     NS_OPENGL_ENUM_DEPRECATED(10_7, 10_14)  = 0x1000,   /* choose a Legacy/Pre-OpenGL 3.0 Implementation */
    NSOpenGLProfileVersion3_2Core    NS_OPENGL_ENUM_DEPRECATED(10_7, 10_14)  = 0x3200,   /* choose an OpenGL 3.2 Core Implementation      */
    NSOpenGLProfileVersion4_1Core    NS_OPENGL_ENUM_DEPRECATED(10_10, 10_14) = 0x4100    /* choose an OpenGL 4.1 Core Implementation      */
};

/*
 ** NSOpenGLPixelFormat interface.
 */

NS_OPENGL_CLASS_DEPRECATED(10_0, 10_14, "Please use Metal or MetalKit.")
@interface NSOpenGLPixelFormat : NSObject <NSCoding>
{
@private
    struct _CGLPixelFormatObject *_CGLPixelFormat APPKIT_IVAR;
    void *_reserved1 __unused APPKIT_IVAR;
    void *_reserved2 __unused APPKIT_IVAR;
    void *_reserved3 __unused APPKIT_IVAR;
    void *_reserved4 __unused APPKIT_IVAR;
}

- (nullable NSOpenGLPixelFormat *)initWithCGLPixelFormatObj:(struct _CGLPixelFormatObject *)format NS_AVAILABLE_MAC(10_6) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithAttributes:(const NSOpenGLPixelFormatAttribute *)attribs;
- (nullable id)initWithData:(null_unspecified NSData*)attribs NS_DEPRECATED_MAC(10_0, 10_6, "Use -initWithAttributes: instead");

- (null_unspecified NSData*)attributes NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setAttributes:(null_unspecified NSData*)attribs NS_DEPRECATED_MAC(10_0, 10_6);

- (void)getValues:(GLint *)vals forAttribute:(NSOpenGLPixelFormatAttribute)attrib forVirtualScreen:(GLint)screen;
@property (readonly) GLint numberOfVirtualScreens;

@property (nullable, readonly) struct _CGLPixelFormatObject *CGLPixelFormatObj NS_RETURNS_INNER_POINTER;

@end

/*********************
 ** NSOpenGLPixelBuffer
 *********************/

/* NOTE: PBuffers should be considered deprecated as of 10.7.  Use GL_EXT_framebuffer_object instead.
 */
NS_CLASS_DEPRECATED_MAC(10_2, 10_7, "Use GL_EXT_framebuffer_object instead")
@interface NSOpenGLPixelBuffer : NSObject
{
@private
    struct _CGLPBufferObject *_CGLPBuffer APPKIT_IVAR;
    void			*_reserved1 __unused APPKIT_IVAR;
    void			*_reserved2 __unused APPKIT_IVAR;
}

/*
 ** size width and height must be powers of two for 1D or 2D or CUBE_MAP targets
 ** size width and height must also be equal for CUBE_MAP target
 ** target should be one of GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP or GL_TEXTURE_RECTANGLE_EXT
 ** internalFormat should be GL_RGB, GL_RGBA or GL_DEPTH_COMPONENT
 ** maxLevel specifies the desired maximum mipmap level, starting with 0.  Must be 0 for
 ** TEXTURE_RECTANGLE targets.
 */
- (nullable instancetype)initWithTextureTarget:(GLenum)target textureInternalFormat:(GLenum)format textureMaxMipMapLevel:(GLint)maxLevel pixelsWide:(GLsizei)pixelsWide pixelsHigh:(GLsizei)pixelsHigh NS_DEPRECATED_MAC(10_2, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (nullable NSOpenGLPixelBuffer *)initWithCGLPBufferObj:(null_unspecified struct _CGLPBufferObject *)pbuffer NS_DEPRECATED_MAC(10_6, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (nullable struct _CGLPBufferObject *)CGLPBufferObj NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_6) NS_DEPRECATED_MAC(10_6, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLsizei)pixelsWide NS_DEPRECATED_MAC(10_2, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLsizei)pixelsHigh NS_DEPRECATED_MAC(10_2, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLenum)textureTarget NS_DEPRECATED_MAC(10_2, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLenum)textureInternalFormat NS_DEPRECATED_MAC(10_2, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLint)textureMaxMipMapLevel NS_DEPRECATED_MAC(10_2, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
@end


/*****************
 ** NSOpenGLContext
 *****************/

/* Parameter names for NSOpenGLContext -setValues:forParameter: and -getValues:forParameter: */
typedef NS_ENUM(NSInteger, NSOpenGLContextParameter) {
    NSOpenGLContextParameterSwapInterval           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 222, /* 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace     */
    NSOpenGLContextParameterSurfaceOrder           NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 235, /* 1 param.  1 -> Above Window (default), -1 -> Below Window    */
    NSOpenGLContextParameterSurfaceOpacity         NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 236, /* 1 param.  1-> Surface is opaque (default), 0 -> non-opaque   */
    NSOpenGLContextParameterSurfaceBackingSize     NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 304, /* 2 params.  Width/height of surface backing size              */
    NSOpenGLContextParameterReclaimResources       NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 308, /* 0 params.                                                    */
    NSOpenGLContextParameterCurrentRendererID      NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 309, /* 1 param.   Retrieves the current renderer ID                 */
    NSOpenGLContextParameterGPUVertexProcessing    NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 310, /* 1 param.   Currently processing vertices with GPU (get)      */
    NSOpenGLContextParameterGPUFragmentProcessing  NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 311, /* 1 param.   Currently processing fragments with GPU (get)     */
    NSOpenGLContextParameterHasDrawable            NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 314, /* 1 param.   Boolean returned if drawable is attached          */
    NSOpenGLContextParameterMPSwapsInFlight        NS_OPENGL_ENUM_DEPRECATED(10_0, 10_14) = 315, /* 1 param.   Max number of swaps queued by the MP GL engine    */
    
    NSOpenGLContextParameterSwapRectangle NS_ENUM_DEPRECATED_MAC(10_0, 10_14) = 200, /* 4 params.  Set or get the swap rectangle {x, y, w, h} */
    NSOpenGLContextParameterSwapRectangleEnable NS_ENUM_DEPRECATED_MAC(10_0, 10_14) = 201, /* Enable or disable the swap rectangle */
    NSOpenGLContextParameterRasterizationEnable NS_ENUM_DEPRECATED_MAC(10_0, 10_14) = 221, /* Enable or disable all rasterization */
    NSOpenGLContextParameterStateValidation NS_ENUM_DEPRECATED_MAC(10_0, 10_14) = 301, /* Validate state for multi-screen functionality */
    NSOpenGLContextParameterSurfaceSurfaceVolatile NS_ENUM_DEPRECATED_MAC(10_0, 10_14)  = 306, /* 1 param.   Surface volatile state */
} NS_OPENGL_DEPRECATED(10_0, 10_14);


/*
 ** NSOpenGLContext interface.
 */
typedef struct _CGLContextObject NSOpenGLContextAuxiliary;

NS_OPENGL_CLASS_DEPRECATED(10_0, 10_14, "Please use Metal or MetalKit.")
@interface NSOpenGLContext : NSObject <NSLocking>
{
@private
    __weak NSView *_view APPKIT_IVAR;
    struct _CGLContextObject *_CGLContext APPKIT_IVAR;
}

/* Context creation */
- (nullable instancetype)initWithFormat:(NSOpenGLPixelFormat *)format shareContext:(nullable NSOpenGLContext *)share;
- (nullable NSOpenGLContext *)initWithCGLContextObj:(struct _CGLContextObject *)context NS_AVAILABLE_MAC(10_6);

@property (readonly, strong) NSOpenGLPixelFormat *pixelFormat NS_AVAILABLE_MAC(10_10);

/* Drawable management */
@property (nullable, weak) NSView *view;
- (void)setView:(nullable NSView *)view NS_DEPRECATED_MAC(10_0, 10_14, "Use NSOpenGLView to provide OpenGL content in a Cocoa app.");
- (void)setFullScreen NS_DEPRECATED_MAC(10_0, 10_7, "Use a fullscreen NSOpenGLView instead");

/* Deprecated in 10.7.  The -setOffScreen:width:height:rowbytes: API forces use of the software rasterizer, which is much slower than GPU rendering.  It is generally much better nowadays to use a normal pixel format with either an off-screen window or an FBO (GL_EXT_framebuffer_object), and then call glReadPixels() to read the rendered result back to CPU memory (if that's where it is needed).
 */
- (void)setOffScreen:(void *)baseaddr width:(GLsizei)width height:(GLsizei)height rowbytes:(GLint)rowbytes NS_DEPRECATED_MAC(10_0, 10_7);

- (void)clearDrawable;
- (void)update;

/* Flush draw buffer */
- (void)flushBuffer;

/* Current context control */
- (void)makeCurrentContext;
+ (void)clearCurrentContext;
@property (class, readonly, nullable, strong) NSOpenGLContext *currentContext;

/* Copy attributes from another context */
- (void)copyAttributesFromContext:(NSOpenGLContext *)context withMask:(GLbitfield)mask NS_DEPRECATED_MAC(10_0, 10_8);

/* Context Parameter handling */
- (void)setValues:(const GLint *)vals forParameter:(NSOpenGLContextParameter)param;
- (void)getValues:(GLint *)vals forParameter:(NSOpenGLContextParameter)param;


/* virtual screens */
@property GLint currentVirtualScreen;

/* creating textures */
- (void)createTexture:(GLenum)target fromView:(NSView *)view internalFormat:(GLenum)format NS_DEPRECATED_MAC(10_2, 10_8);

@property (nullable, readonly) struct _CGLContextObject *CGLContextObj NS_RETURNS_INNER_POINTER;

@end

@interface NSOpenGLContext (NSOpenGLPixelBufer)
/*
 ** NOTE: PBuffers have been Deprecated as of 10.7.  Use GL_EXT_framebuffer_object instead.
 **
 ** Attach context to an NSOpenGLPixelBuffer instance.
 ** For GL_CUBE_MAP target pixel buffers, face should be one of GL_TEXTURE_CUBE_MAP_POSITIVE_X,
 ** GL_TEXTURE_CUBE_MAP_POSITIVE_Y, etc.  Otherwise it should be 0.
 ** Level specifies the desired mipmap level you want to render to.  It must less than or equal to the maxLevel
 ** parameter of the pixel buffer.
 ** If applicable, the virtual screen should be set to the same value as the current virtual screen you are using
 ** to render on-screen with.
 */
- (void)setPixelBuffer:(NSOpenGLPixelBuffer *)pixelBuffer cubeMapFace:(GLenum)face mipMapLevel:(GLint)level currentVirtualScreen:(GLint)screen NS_DEPRECATED_MAC(10_3, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (nullable NSOpenGLPixelBuffer *)pixelBuffer NS_DEPRECATED_MAC(10_3, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLenum)pixelBufferCubeMapFace NS_DEPRECATED_MAC(10_3, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
- (GLint)pixelBufferMipMapLevel NS_DEPRECATED_MAC(10_3, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */

/*
 ** NOTE: PBuffers have been Deprecated as of 10.7.  Use GL_EXT_framebuffer_object instead.
 **
 ** This call is a mirror of CGLTexImagePBuffer.  This essentially "binds" the given pixel buffer's image data
 ** to the currently bound texture object.   Source specifies which of the PBuffer's color buffers should be used,
 ** and should be one of GL_FRONT, GL_BACK, GL_AUX0, etc.
 */
- (void)setTextureImageToPixelBuffer:(NSOpenGLPixelBuffer *)pixelBuffer colorBuffer:(GLenum)source NS_DEPRECATED_MAC(10_3, 10_7); /* Use IOSurface instead of NSOpenGLPixelBuffer on Mac OS 10.7 and newer. */
@end


static const NSOpenGLContextParameter NSOpenGLCPSwapInterval NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSwapInterval", 10_5, 10_14) = NSOpenGLContextParameterSwapInterval;
static const NSOpenGLContextParameter NSOpenGLCPSurfaceOrder NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSurfaceOrder", 10_0, 10_14) = NSOpenGLContextParameterSurfaceOrder;
static const NSOpenGLContextParameter NSOpenGLCPSurfaceOpacity NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSurfaceOpacity", 10_0, 10_14) = NSOpenGLContextParameterSurfaceOpacity;
static const NSOpenGLContextParameter NSOpenGLCPSurfaceBackingSize NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSurfaceBackingSize", 10_0, 10_14) = NSOpenGLContextParameterSurfaceBackingSize;
static const NSOpenGLContextParameter NSOpenGLCPReclaimResources NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterReclaimResources", 10_0, 10_14) = NSOpenGLContextParameterReclaimResources;
static const NSOpenGLContextParameter NSOpenGLCPCurrentRendererID NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterCurrentRendererID", 10_0, 10_14) = NSOpenGLContextParameterCurrentRendererID;
static const NSOpenGLContextParameter NSOpenGLCPGPUVertexProcessing NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterGPUVertexProcessing", 10_0, 10_14) = NSOpenGLContextParameterGPUVertexProcessing;
static const NSOpenGLContextParameter NSOpenGLCPGPUFragmentProcessing NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterGPUFragmentProcessing", 10_0, 10_14) = NSOpenGLContextParameterGPUFragmentProcessing;
static const NSOpenGLContextParameter NSOpenGLCPHasDrawable NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterHasDrawable", 10_0, 10_14) = NSOpenGLContextParameterHasDrawable;
static const NSOpenGLContextParameter NSOpenGLCPMPSwapsInFlight NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterMPSwapsInFlight", 10_0, 10_14) = NSOpenGLContextParameterMPSwapsInFlight;

static const NSOpenGLContextParameter NSOpenGLCPSwapRectangle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSwapRectangle", 10_0, 10_14) = NSOpenGLContextParameterSwapRectangle;
static const NSOpenGLContextParameter NSOpenGLCPSwapRectangleEnable NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSwapRectangleEnable", 10_0, 10_14) = NSOpenGLContextParameterSwapRectangleEnable;
static const NSOpenGLContextParameter NSOpenGLCPRasterizationEnable NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterRasterizationEnable", 10_0, 10_14) = NSOpenGLContextParameterRasterizationEnable;
static const NSOpenGLContextParameter NSOpenGLCPStateValidation NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterStateValidation", 10_0, 10_14) = NSOpenGLContextParameterStateValidation;
static const NSOpenGLContextParameter NSOpenGLCPSurfaceSurfaceVolatile NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSOpenGLContextParameterSurfaceSurfaceVolatile", 10_0, 10_14) = NSOpenGLContextParameterSurfaceSurfaceVolatile;

NS_ASSUME_NONNULL_END
