/*
        NSOpenGL.h
        Application Kit
        Copyright (c) 2000-2015, Apple Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <OpenGL/gltypes.h>

NS_ASSUME_NONNULL_BEGIN

@class NSData, NSView, NSScreen;

/*
** NSOpenGL current API version
*/
#define NSOPENGL_CURRENT_VERSION  1

/* Option names for NSOpenGLSetOption() and NSOpenGLGetOption() */
typedef enum {
	NSOpenGLGOFormatCacheSize  = 501,	/* Set the size of the pixel format cache        */
	NSOpenGLGOClearFormatCache = 502,	/* Reset the pixel format cache if true          */
	NSOpenGLGORetainRenderers  = 503,	/* Whether to retain loaded renderers in memory  */
	NSOpenGLGOUseBuildCache    = 506,	/* Enable the function compilation block cache.  Off by default.  Must be enabled at startup. */

	NSOpenGLGOResetLibrary NS_ENUM_DEPRECATED_MAC(10_0, 10_4) = 504
} NSOpenGLGlobalOption;


/*
** Library global options.
*/
extern void NSOpenGLSetOption(NSOpenGLGlobalOption pname, GLint param);
extern void NSOpenGLGetOption(NSOpenGLGlobalOption pname, GLint * param);

/*
** Library version.
*/
extern void NSOpenGLGetVersion(GLint * __nullable major, GLint * __nullable minor);


/*********************
** NSOpenGLPixelFormat
*********************/

/*
** Attribute names for [NSOpenGLPixelFormat initWithAttributes]
** and [NSOpenGLPixelFormat getValues:forAttribute:forVirtualScreen].
*/
enum {
	NSOpenGLPFAAllRenderers       =   1,	/* choose from all available renderers          */
	NSOpenGLPFATripleBuffer       =   3,	/* choose a triple buffered pixel format        */
	NSOpenGLPFADoubleBuffer       =   5,	/* choose a double buffered pixel format        */
	NSOpenGLPFAStereo             =   6,	/* stereo buffering supported                   */
	NSOpenGLPFAAuxBuffers         =   7,	/* number of aux buffers                        */
	NSOpenGLPFAColorSize          =   8,	/* number of color buffer bits                  */
	NSOpenGLPFAAlphaSize          =  11,	/* number of alpha component bits               */
	NSOpenGLPFADepthSize          =  12,	/* number of depth buffer bits                  */
	NSOpenGLPFAStencilSize        =  13,	/* number of stencil buffer bits                */
	NSOpenGLPFAAccumSize          =  14,	/* number of accum buffer bits                  */
	NSOpenGLPFAMinimumPolicy      =  51,	/* never choose smaller buffers than requested  */
	NSOpenGLPFAMaximumPolicy      =  52,	/* choose largest buffers of type requested     */
	NSOpenGLPFASampleBuffers      =  55,	/* number of multi sample buffers               */
	NSOpenGLPFASamples            =  56,	/* number of samples per multi sample buffer    */
	NSOpenGLPFAAuxDepthStencil    =  57,	/* each aux buffer has its own depth stencil    */
	NSOpenGLPFAColorFloat         =  58,	/* color buffers store floating point pixels    */
	NSOpenGLPFAMultisample        =  59,    /* choose multisampling                         */
	NSOpenGLPFASupersample        =  60,    /* choose supersampling                         */
	NSOpenGLPFASampleAlpha        =  61,    /* request alpha filtering                      */
	NSOpenGLPFARendererID         =  70,	/* request renderer by ID                       */
	NSOpenGLPFANoRecovery         =  72,	/* disable all failure recovery systems         */
	NSOpenGLPFAAccelerated        =  73,	/* choose a hardware accelerated renderer       */
	NSOpenGLPFAClosestPolicy      =  74,	/* choose the closest color buffer to request   */
	NSOpenGLPFABackingStore       =  76,	/* back buffer contents are valid after swap    */
	NSOpenGLPFAScreenMask         =  84,	/* bit mask of supported physical screens       */
	NSOpenGLPFAAllowOfflineRenderers NS_ENUM_AVAILABLE_MAC(10_5) = 96,  /* allow use of offline renderers               */
	NSOpenGLPFAAcceleratedCompute =  97,	/* choose a hardware accelerated compute device */
	NSOpenGLPFAVirtualScreenCount = 128,	/* number of virtual screens in this format     */
 	NSOpenGLPFAOpenGLProfile NS_ENUM_AVAILABLE_MAC(10_7)     =  99,	/* specify an OpenGL Profile to use             */
   
        /* The following attributes are deprecated. */
	NSOpenGLPFAOffScreen NS_ENUM_DEPRECATED_MAC(10_0, 10_7)        =  53,
	NSOpenGLPFAFullScreen NS_ENUM_DEPRECATED_MAC(10_0, 10_6)       =  54,
	NSOpenGLPFASingleRenderer  NS_ENUM_DEPRECATED_MAC(10_0, 10_9)  =  71,
	NSOpenGLPFAWindow NS_ENUM_DEPRECATED_MAC(10_0, 10_9)           =  80,
	NSOpenGLPFACompliant NS_ENUM_DEPRECATED_MAC(10_0, 10_9)        =  83,
	NSOpenGLPFAPixelBuffer NS_ENUM_DEPRECATED_MAC(10_3, 10_7)      =  90,
	NSOpenGLPFARemotePixelBuffer NS_ENUM_DEPRECATED_MAC(10_3, 10_7) =  91,

	NSOpenGLPFARobust NS_ENUM_DEPRECATED_MAC(10_0, 10_5)           =  75,
	NSOpenGLPFAMPSafe NS_ENUM_DEPRECATED_MAC(10_0, 10_5)           =  78,
	NSOpenGLPFAMultiScreen NS_ENUM_DEPRECATED_MAC(10_0, 10_5)      =  81,
};
typedef uint32_t NSOpenGLPixelFormatAttribute;

/* NSOpenGLPFAOpenGLProfile values */
enum {
	NSOpenGLProfileVersionLegacy    NS_ENUM_AVAILABLE_MAC(10_7)     = 0x1000,   /* choose a Legacy/Pre-OpenGL 3.0 Implementation */
	NSOpenGLProfileVersion3_2Core   NS_ENUM_AVAILABLE_MAC(10_7)     = 0x3200,   /* choose an OpenGL 3.2 Core Implementation      */
        NSOpenGLProfileVersion4_1Core   NS_ENUM_AVAILABLE_MAC(10_10)    = 0x4100    /* choose an OpenGL 4.1 Core Implementation      */
};

/*
** NSOpenGLPixelFormat interface.
*/

@interface NSOpenGLPixelFormat : NSObject <NSCoding>
{
@private
    struct _CGLPixelFormatObject *_CGLPixelFormat;
    void *_reserved1;
    void *_reserved2;
    void *_reserved3;
    void *_reserved4;
}

- (nullable instancetype)initWithAttributes:(const NSOpenGLPixelFormatAttribute *)attribs;
- (nullable id)initWithData:(null_unspecified NSData*)attribs NS_DEPRECATED_MAC(10_0, 10_6, "Use -initWithAttributes: instead");
- (nullable NSOpenGLPixelFormat *)initWithCGLPixelFormatObj:(struct _CGLPixelFormatObject *)format NS_AVAILABLE_MAC(10_6);

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
    struct _CGLPBufferObject *_CGLPBuffer;
    void			*_reserved1;
    void			*_reserved2;
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
    NSOpenGLCPSwapInterval           = 222, /* 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace     */
    NSOpenGLCPSurfaceOrder           = 235, /* 1 param.  1 -> Above Window (default), -1 -> Below Window    */
    NSOpenGLCPSurfaceOpacity         = 236, /* 1 param.  1-> Surface is opaque (default), 0 -> non-opaque   */
    NSOpenGLCPSurfaceBackingSize     = 304, /* 2 params.  Width/height of surface backing size              */
    NSOpenGLCPReclaimResources       = 308, /* 0 params.                                                    */
    NSOpenGLCPCurrentRendererID      = 309, /* 1 param.   Retrieves the current renderer ID                 */
    NSOpenGLCPGPUVertexProcessing    = 310, /* 1 param.   Currently processing vertices with GPU (get)      */
    NSOpenGLCPGPUFragmentProcessing  = 311, /* 1 param.   Currently processing fragments with GPU (get)     */
    NSOpenGLCPHasDrawable            = 314, /* 1 param.   Boolean returned if drawable is attached          */
    NSOpenGLCPMPSwapsInFlight        = 315, /* 1 param.   Max number of swaps queued by the MP GL engine    */

    /* The following parameters are obsolete and deprecated for new development. */
    NSOpenGLCPSwapRectangle          = 200, /* 4 params.  Set or get the swap rectangle {x, y, w, h}        */
    NSOpenGLCPSwapRectangleEnable    = 201, /* Enable or disable the swap rectangle                         */
    NSOpenGLCPRasterizationEnable    = 221, /* Enable or disable all rasterization                          */
    NSOpenGLCPStateValidation        = 301, /* Validate state for multi-screen functionality                */
    NSOpenGLCPSurfaceSurfaceVolatile = 306, /* 1 param.   Surface volatile state                            */
} ;


/*
** NSOpenGLContext interface.
*/
typedef struct _CGLContextObject NSOpenGLContextAuxiliary;

@interface NSOpenGLContext : NSObject <NSLocking>
{
@private
	__weak NSView            *_view;
    struct _CGLContextObject *_CGLContext;
}

/* Context creation */
- (nullable instancetype)initWithFormat:(NSOpenGLPixelFormat *)format shareContext:(nullable NSOpenGLContext *)share;
- (nullable NSOpenGLContext *)initWithCGLContextObj:(struct _CGLContextObject *)context NS_AVAILABLE_MAC(10_6);

@property (readonly, strong) NSOpenGLPixelFormat *pixelFormat NS_AVAILABLE_MAC(10_10);

/* Drawable management */
@property (nullable, assign) NSView *view;
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
+ (nullable NSOpenGLContext *)currentContext;

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

NS_ASSUME_NONNULL_END
