/*
        NSOpenGL.h
        Application Kit
        Copyright (c) 2000-2011, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <OpenGL/gltypes.h>

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

    /* Deprecated Global Option Values */
	NSOpenGLGOResetLibrary     = 504	/* Deprecated in Mac OS X 10.4.  Do a soft reset of the CGL library if true    */
} NSOpenGLGlobalOption;


/*
** Library global options.
*/
extern void NSOpenGLSetOption(NSOpenGLGlobalOption pname, GLint param);
extern void NSOpenGLGetOption(NSOpenGLGlobalOption pname, GLint *param);

/*
** Library version.
*/
extern void NSOpenGLGetVersion(GLint *major, GLint *minor);


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
	NSOpenGLPFAOffScreen          =  53,	/* choose an off-screen capable renderer        */
	NSOpenGLPFAFullScreen         =  54,	/* choose a full-screen capable renderer        */
	NSOpenGLPFASampleBuffers      =  55,	/* number of multi sample buffers               */
	NSOpenGLPFASamples            =  56,	/* number of samples per multi sample buffer    */
	NSOpenGLPFAAuxDepthStencil    =  57,	/* each aux buffer has its own depth stencil    */
	NSOpenGLPFAColorFloat         =  58,	/* color buffers store floating point pixels    */
	NSOpenGLPFAMultisample        =  59,    /* choose multisampling                         */
	NSOpenGLPFASupersample        =  60,    /* choose supersampling                         */
	NSOpenGLPFASampleAlpha        =  61,    /* request alpha filtering                      */
	NSOpenGLPFARendererID         =  70,	/* request renderer by ID                       */
	NSOpenGLPFASingleRenderer     =  71,	/* choose a single renderer for all screens     */
	NSOpenGLPFANoRecovery         =  72,	/* disable all failure recovery systems         */
	NSOpenGLPFAAccelerated        =  73,	/* choose a hardware accelerated renderer       */
	NSOpenGLPFAClosestPolicy      =  74,	/* choose the closest color buffer to request   */
	NSOpenGLPFABackingStore       =  76,	/* back buffer contents are valid after swap    */
	NSOpenGLPFAWindow             =  80,	/* can be used to render to an onscreen window  */
	NSOpenGLPFACompliant          =  83,	/* renderer is opengl compliant                 */
	NSOpenGLPFAScreenMask         =  84,	/* bit mask of supported physical screens       */
	NSOpenGLPFAPixelBuffer        =  90,	/* can be used to render to a pbuffer           */
	NSOpenGLPFARemotePixelBuffer  =  91,	/* can be used to render offline to a pbuffer   */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
	NSOpenGLPFAAllowOfflineRenderers = 96,  /* allow use of offline renderers               */
#endif
	NSOpenGLPFAAcceleratedCompute =  97,	/* choose a hardware accelerated compute device */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
	NSOpenGLPFAOpenGLProfile      =  99,	/* specify an OpenGL Profile to use             */
#endif
	NSOpenGLPFAVirtualScreenCount = 128,	/* number of virtual screens in this format     */

    /* NSOpenGLPFARobust, NSOpenGLPFAMPSafe, and NSOpenGLPFAMultiScreen are deprecated.  Applications that specify these attributes will continue to work, but they are deprecated for new development.
    */
	NSOpenGLPFARobust             =  75,	/* renderer does not need failure recovery      */
	NSOpenGLPFAMPSafe             =  78,	/* renderer is multi-processor safe             */
	NSOpenGLPFAMultiScreen        =  81 	/* single window can span multiple screens      */
};
typedef uint32_t NSOpenGLPixelFormatAttribute;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
/* NSOpenGLPFAOpenGLProfile values */
enum {
	NSOpenGLProfileVersionLegacy    = 0x1000,   /* choose a Legacy/Pre-OpenGL 3.0 Implementation */
	NSOpenGLProfileVersion3_2Core   = 0x3200    /* choose an OpenGL 3.2 Core Implementation      */
};
#endif

/*
** NSOpenGLPixelFormat interface.
*/
typedef struct _CGLPixelFormatObject NSOpenGLPixelFormatAuxiliary;

@interface NSOpenGLPixelFormat : NSObject <NSCoding>
{
@private
    NSOpenGLPixelFormatAuxiliary* _pixelFormatAuxiliary;
    NSData*                       _pixelAttributes;
    NSInteger                         _reserved1;
    NSInteger                         _reserved2;
    NSInteger                         _reserved3;
}

- (id)initWithAttributes:(const NSOpenGLPixelFormatAttribute *)attribs;
- (id)initWithData:(NSData*)attribs;
- (id)initWithCGLPixelFormatObj:(void *)format NS_AVAILABLE_MAC(10_6);

- (NSData*)attributes;
- (void)setAttributes:(NSData*)attribs;

- (void)getValues:(GLint *)vals forAttribute:(NSOpenGLPixelFormatAttribute)attrib forVirtualScreen:(GLint)screen;
- (GLint)numberOfVirtualScreens;

- (void *)CGLPixelFormatObj;

@end

/*********************
** NSOpenGLPixelBuffer
*********************/

/* NOTE: PBuffers should be considered deprecated as of 10.7.  Use GL_EXT_framebuffer_object instead.
*/
@interface NSOpenGLPixelBuffer : NSObject
{
@private
    struct _CGLPBufferObject	*_pixelBufferAuxiliary;
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
- (id)initWithTextureTarget:(GLenum)target textureInternalFormat:(GLenum)format textureMaxMipMapLevel:(GLint)maxLevel pixelsWide:(GLsizei)pixelsWide pixelsHigh:(GLsizei)pixelsHigh;
- (id)initWithCGLPBufferObj:(void *)pbuffer NS_AVAILABLE_MAC(10_6);
- (void *)CGLPBufferObj NS_AVAILABLE_MAC(10_6);
- (GLsizei)pixelsWide;
- (GLsizei)pixelsHigh;
- (GLenum)textureTarget;
- (GLenum)textureInternalFormat;
- (GLint)textureMaxMipMapLevel;
@end


/*****************
** NSOpenGLContext
*****************/

/* Parameter names for NSOpenGLContext -setValues:forParameter: and -getValues:forParameter: */
typedef enum {
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
    NSOpenGLCPSurfaceSurfaceVolatile = 306  /* 1 param.   Surface volatile state                            */
} NSOpenGLContextParameter;


/*
** NSOpenGLContext interface.
*/
typedef struct _CGLContextObject NSOpenGLContextAuxiliary;

@interface NSOpenGLContext : NSObject
{
@private
	__weak NSView            *_view;
	NSOpenGLContextAuxiliary *_contextAuxiliary;
}

/* Context creation */
- (id)initWithFormat:(NSOpenGLPixelFormat *)format shareContext:(NSOpenGLContext *)share;
- (id)initWithCGLContextObj:(void *)context NS_AVAILABLE_MAC(10_6);

/* Drawable management */
- (void)setView:(NSView *)view;
- (NSView *)view;
- (void)setFullScreen;

/* Deprecated in 10.7.  The -setOffScreen:width:height:rowbytes: API forces use of the software rasterizer, which is much slower than GPU rendering.  It is generally much better nowadays to use a normal pixel format with either an off-screen window or an FBO (GL_EXT_framebuffer_object), and then call glReadPixels() to read the rendered result back to CPU memory (if that's where it is needed).
*/
- (void)setOffScreen:(void *)baseaddr width:(GLsizei)width height:(GLsizei)height rowbytes:(GLint)rowbytes;

- (void)clearDrawable;
- (void)update;

/* Flush draw buffer */
- (void)flushBuffer;

/* Current context control */
- (void)makeCurrentContext;
+ (void)clearCurrentContext;
+ (NSOpenGLContext *)currentContext;

/* Copy attributes from another context */
- (void)copyAttributesFromContext:(NSOpenGLContext *)context withMask:(GLbitfield)mask;

/* Context Parameter handling */
- (void)setValues:(const GLint *)vals forParameter:(NSOpenGLContextParameter)param;
- (void)getValues:(GLint *)vals forParameter:(NSOpenGLContextParameter)param;


/* virtual screens */
- (void)setCurrentVirtualScreen:(GLint)screen;
- (GLint)currentVirtualScreen;

/* creating textures */
- (void)createTexture:(GLenum)target fromView:(NSView *)view internalFormat:(GLenum)format;


- (void *)CGLContextObj;

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
- (void)setPixelBuffer:(NSOpenGLPixelBuffer *)pixelBuffer cubeMapFace:(GLenum)face mipMapLevel:(GLint)level currentVirtualScreen:(GLint)screen;
- (NSOpenGLPixelBuffer *)pixelBuffer;
- (GLenum)pixelBufferCubeMapFace;
- (GLint)pixelBufferMipMapLevel;

/*
** NOTE: PBuffers have been Deprecated as of 10.7.  Use GL_EXT_framebuffer_object instead.
**
** This call is a mirror of CGLTexImagePBuffer.  This essentially "binds" the given pixel buffer's image data
** to the currently bound texture object.   Source specifies which of the PBuffer's color buffers should be used,
** and should be one of GL_FRONT, GL_BACK, GL_AUX0, etc.
*/
- (void)setTextureImageToPixelBuffer:(NSOpenGLPixelBuffer *)pixelBuffer colorBuffer:(GLenum)source;

@end

