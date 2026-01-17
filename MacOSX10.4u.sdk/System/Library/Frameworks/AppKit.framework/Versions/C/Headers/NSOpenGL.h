/*
        NSOpenGL.h
        Application Kit
        Copyright (c) 2000-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSData, NSView, NSScreen;

/*
** NSOpenGL current API version
*/
#define NSOPENGL_CURRENT_VERSION  1

/*
** Option names for NSOpenGLSetOption and NSOpenGLGetOption.
*/
typedef enum {
	NSOpenGLGOFormatCacheSize  = 501,	/* Set the size of the pixel format cache        */
	NSOpenGLGOClearFormatCache = 502,	/* Reset the pixel format cache if true          */
	NSOpenGLGORetainRenderers  = 503,	/* Whether to retain loaded renderers in memory  */
	NSOpenGLGOResetLibrary     = 504	/* Do a soft reset of the CGL library if true    */
} NSOpenGLGlobalOption;


/*
** Library global options.
*/
extern void NSOpenGLSetOption(NSOpenGLGlobalOption pname, long param);
extern void NSOpenGLGetOption(NSOpenGLGlobalOption pname, long *param);

/*
** Library version.
*/
extern void NSOpenGLGetVersion(long *major, long *minor);


/*********************
** NSOpenGLPixelFormat
*********************/

/*
** Attribute names for [NSOpenGLPixelFormat initWithAttributes]
** and [NSOpenGLPixelFormat getValues:forAttribute:forVirtualScreen].
*/
typedef enum {
	NSOpenGLPFAAllRenderers       =   1,	/* choose from all available renderers          */
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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
	NSOpenGLPFAMultisample        =  59,    /* choose multisampling                         */
	NSOpenGLPFASupersample        =  60,    /* choose supersampling                         */
	NSOpenGLPFASampleAlpha        =  61,    /* request alpha filtering                      */
#endif
	NSOpenGLPFARendererID         =  70,	/* request renderer by ID                       */
	NSOpenGLPFASingleRenderer     =  71,	/* choose a single renderer for all screens     */
	NSOpenGLPFANoRecovery         =  72,	/* disable all failure recovery systems         */
	NSOpenGLPFAAccelerated        =  73,	/* choose a hardware accelerated renderer       */
	NSOpenGLPFAClosestPolicy      =  74,	/* choose the closest color buffer to request   */
	NSOpenGLPFARobust             =  75,	/* renderer does not need failure recovery      */
	NSOpenGLPFABackingStore       =  76,	/* back buffer contents are valid after swap    */
	NSOpenGLPFAMPSafe             =  78,	/* renderer is multi-processor safe             */
	NSOpenGLPFAWindow             =  80,	/* can be used to render to an onscreen window  */
	NSOpenGLPFAMultiScreen        =  81,	/* single window can span multiple screens      */
	NSOpenGLPFACompliant          =  83,	/* renderer is opengl compliant                 */
	NSOpenGLPFAScreenMask         =  84,	/* bit mask of supported physical screens       */
	NSOpenGLPFAPixelBuffer        =  90,	/* can be used to render to a pbuffer           */
	NSOpenGLPFAVirtualScreenCount = 128	/* number of virtual screens in this format     */
} NSOpenGLPixelFormatAttribute;


/*
** NSOpenGLPixelFormat interface.
*/
typedef struct _CGLPixelFormatObject NSOpenGLPixelFormatAuxiliary;

@interface NSOpenGLPixelFormat : NSObject <NSCoding>
{
@private
    NSOpenGLPixelFormatAuxiliary* _pixelFormatAuxiliary;
    NSData*                       _pixelAttributes;
    unsigned long                 _reserved1;
    unsigned long                 _reserved2;
    unsigned long                 _reserved3;
}

- (id)initWithAttributes:(NSOpenGLPixelFormatAttribute*)attribs;
- (id)initWithData:(NSData*)attribs;

- (NSData*)attributes;
- (void)setAttributes:(NSData*)attribs;

- (void)getValues:(long*)vals forAttribute:(NSOpenGLPixelFormatAttribute)attrib forVirtualScreen:(int)screen;
- (int)numberOfVirtualScreens;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void *)CGLPixelFormatObj;
#endif

@end

/*********************
** NSOpenGLPixelBuffer
*********************/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

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
- (id)initWithTextureTarget:(unsigned long/*GLenum*/)target textureInternalFormat:(unsigned long/*GLenum*/)format textureMaxMipMapLevel:(long/*GLenum*/)maxLevel pixelsWide:(int)pixelsWide pixelsHigh:(int)pixelsHigh;
- (int)pixelsWide;
- (int)pixelsHigh;
- (unsigned long/*GLenum*/)textureTarget;
- (unsigned long/*GLenum*/)textureInternalFormat;
- (long/*GLint*/)textureMaxMipMapLevel;
@end
#endif


/*****************
** NSOpenGLContext
*****************/

/*
** Parameter names for [NSOpenGLContext setParameter] and [NSOpenGLContext getParameter].
*/
typedef enum {
	NSOpenGLCPSwapRectangle       = 200,	/* Set or get the swap rectangle {x, y, w, h}       */
	NSOpenGLCPSwapRectangleEnable = 201,	/* Enable or disable the swap rectangle             */
	NSOpenGLCPRasterizationEnable = 221,	/* Enable or disable all rasterization              */
	NSOpenGLCPSwapInterval        = 222,	/* 0 -> Don't sync, n -> Sync every n retrace       */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
	NSOpenGLCPSurfaceOrder        = 235,	/* 1 -> Above Window (default), -1 -> Below Window  */
	NSOpenGLCPSurfaceOpacity      = 236,	/* 1-> Surface is opaque (default), 0 -> non-opaque */
#endif
	NSOpenGLCPStateValidation     = 301	/* Validate state for multi-screen functionality    */
} NSOpenGLContextParameter;


/*
** NSOpenGLContext interface.
*/
typedef struct _CGLContextObject NSOpenGLContextAuxiliary;

@interface NSOpenGLContext : NSObject
{
@private
	NSView                   *_view;
	NSOpenGLContextAuxiliary *_contextAuxiliary;
}

/* Context creation */
- (id)initWithFormat:(NSOpenGLPixelFormat *)format shareContext:(NSOpenGLContext *)share;

/* Drawable management */
- (void)setView:(NSView *)view;
- (NSView *)view;
- (void)setFullScreen;
- (void)setOffScreen:(void *)baseaddr width:(long)width height:(long)height rowbytes:(long)rowbytes;
- (void)clearDrawable;
- (void)update;

/* Flush draw buffer */
- (void)flushBuffer;

/* Current context control */
- (void)makeCurrentContext;
+ (void)clearCurrentContext;
+ (NSOpenGLContext *)currentContext;

/* Copy attributes from another context */
- (void)copyAttributesFromContext:(NSOpenGLContext *)context withMask:(unsigned long)mask;

/* Context Parameter handling */
- (void)setValues:(const long *)vals forParameter:(NSOpenGLContextParameter)param;
- (void)getValues:(long *)vals forParameter:(NSOpenGLContextParameter)param;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

/* virtual screens */
- (void)setCurrentVirtualScreen:(int)screen;
- (int)currentVirtualScreen;

/* creating textures */
- (void)createTexture:(unsigned long/*GLenum*/)target fromView:(NSView*)view internalFormat:(unsigned long/*GLenum*/)format;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void *)CGLContextObj;

/*
** Attach context to an NSOpenGLPixelBuffer instance.
** For GL_CUBE_MAP target pixel buffers, face should be one of GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
** GL_TEXTURE_CUBE_MAP_POSITIVE_Y, etc.  Otherwise it should be 0.
** Level specifies the desired mipmap level you want to render to.  It must less than or equal to the maxLevel
** parameter of the pixel buffer.
** If applicable, the virtual screen should be set to the same value as the current virtual screen you are using
** to render on-screen with.
*/
- (void)setPixelBuffer:(NSOpenGLPixelBuffer *)pixelBuffer cubeMapFace:(unsigned long/*GLenum*/)face mipMapLevel:(long/*GLint*/)level currentVirtualScreen:(int)screen;
- (NSOpenGLPixelBuffer *)pixelBuffer;
- (unsigned long/*GLenum*/)pixelBufferCubeMapFace;
- (long/*GLint*/)pixelBufferMipMapLevel;
/*
** This call is a mirror of CGLTexImagePBuffer.  This essentially "binds" the given pixel buffer's image data
** to the currently bound texture object.   Source specifies which of the PBuffer's color buffers should be used,
** and should be one of GL_FRONT, GL_BACK, GL_AUX0, etc.
*/
- (void)setTextureImageToPixelBuffer:(NSOpenGLPixelBuffer *)pixelBuffer colorBuffer:(unsigned long/*GLenum*/)source;
#endif

@end

