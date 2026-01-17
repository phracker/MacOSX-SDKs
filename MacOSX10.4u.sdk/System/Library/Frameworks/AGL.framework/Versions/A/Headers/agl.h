/*
    File:	    AGL/agl.h

    Contains:	Basic AGL data types, constants and function prototypes.

    Version:	Technology:	Mac OS X
                Release:	GM
 
     Copyright:  (c) 2000, 2001, 2002, 2003, 2004, 2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                 http://developer.apple.com/bugreporter/
 
*/

#ifndef _AGL_H
#define _AGL_H

#if defined (__MACH__)
	#include <AvailabilityMacros.h>
	#include <Carbon/Carbon.h>
	#include <OpenGL/gl.h>
#else
	#define AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER 
	#define AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER 
	#define AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER 
	#include <Carbon.h>
	#include <gl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
** AGL API version.
*/
#define AGL_VERSION_2_0  1

/*
** Macintosh device type.
*/
typedef GDHandle AGLDevice;

/*
** Macintosh drawable type.
*/
typedef CGrafPtr AGLDrawable;

/*
** AGL opaque data.
*/
typedef struct __AGLRendererInfoRec  *AGLRendererInfo;
typedef struct __AGLPixelFormatRec   *AGLPixelFormat;
typedef struct __AGLContextRec       *AGLContext;
typedef struct __AGLPBufferRec       *AGLPbuffer;

/************************************************************************/

/*
** Attribute names for aglChoosePixelFormat and aglDescribePixelFormat.
*/
#define AGL_NONE                   0
#define AGL_ALL_RENDERERS          1  /* choose from all available renderers          */
#define AGL_BUFFER_SIZE            2  /* depth of the index buffer                    */
#define AGL_LEVEL                  3  /* level in plane stacking                      */
#define AGL_RGBA                   4  /* choose an RGBA format                        */
#define AGL_DOUBLEBUFFER           5  /* double buffering supported                   */
#define AGL_STEREO                 6  /* stereo buffering supported                   */
#define AGL_AUX_BUFFERS            7  /* number of aux buffers                        */
#define AGL_RED_SIZE               8  /* number of red component bits                 */
#define AGL_GREEN_SIZE             9  /* number of green component bits               */
#define AGL_BLUE_SIZE             10  /* number of blue component bits                */
#define AGL_ALPHA_SIZE            11  /* number of alpha component bits               */
#define AGL_DEPTH_SIZE            12  /* number of depth bits                         */
#define AGL_STENCIL_SIZE          13  /* number of stencil bits                       */
#define AGL_ACCUM_RED_SIZE        14  /* number of red accum bits                     */
#define AGL_ACCUM_GREEN_SIZE      15  /* number of green accum bits                   */
#define AGL_ACCUM_BLUE_SIZE       16  /* number of blue accum bits                    */
#define AGL_ACCUM_ALPHA_SIZE      17  /* number of alpha accum bits                   */

/*
** Extended attributes
*/
#define AGL_PIXEL_SIZE            50  /* frame buffer bits per pixel                  */
#define AGL_MINIMUM_POLICY        51  /* never choose smaller buffers than requested  */
#define AGL_MAXIMUM_POLICY        52  /* choose largest buffers of type requested     */
#define AGL_OFFSCREEN             53  /* choose an off-screen capable renderer        */
#define AGL_FULLSCREEN            54  /* choose a full-screen capable renderer        */
#define AGL_SAMPLE_BUFFERS_ARB    55  /* number of multi sample buffers               */
#define AGL_SAMPLES_ARB	          56  /* number of samples per multi sample buffer    */
#define AGL_AUX_DEPTH_STENCIL	  57  /* independent depth and/or stencil buffers for the aux buffer */
#define AGL_COLOR_FLOAT     	  58  /* color buffers store floating point pixels    */
#define AGL_MULTISAMPLE     	  59  /* choose multisample                           */
#define AGL_SUPERSAMPLE     	  60  /* choose supersample                           */
#define AGL_SAMPLE_ALPHA     	  61  /* request alpha filtering                      */

/*
** Renderer management
*/
#define AGL_RENDERER_ID           70  /* request renderer by ID                       */
#define AGL_SINGLE_RENDERER       71  /* choose a single renderer for all screens     */
#define AGL_NO_RECOVERY           72  /* disable all failure recovery systems         */
#define AGL_ACCELERATED           73  /* choose a hardware accelerated renderer       */
#define AGL_CLOSEST_POLICY        74  /* choose the closest color buffer to request   */
#define AGL_ROBUST                75  /* renderer does not need failure recovery      */
#define AGL_BACKING_STORE         76  /* back buffer contents are valid after swap    */
#define AGL_MP_SAFE               78  /* renderer is multi-processor safe             */

#define AGL_WINDOW                80  /* can be used to render to a window            */
#define AGL_MULTISCREEN           81  /* single window can span multiple screens      */
#define AGL_VIRTUAL_SCREEN        82  /* virtual screen number                        */
#define AGL_COMPLIANT             83  /* renderer is opengl compliant                 */

#define AGL_PBUFFER               90  /* can be used to render to a pbuffer           */
#define AGL_REMOTE_PBUFFER        91  /* can be used to render offline to a pbuffer	  */

/*
** Property names for aglDescribeRenderer
*/
/* #define AGL_OFFSCREEN          53 */
/* #define AGL_FULLSCREEN         54 */
/* #define AGL_RENDERER_ID        70 */
/* #define AGL_ACCELERATED        73 */
/* #define AGL_ROBUST             75 */
/* #define AGL_BACKING_STORE      76 */
/* #define AGL_MP_SAFE            78 */
/* #define AGL_WINDOW             80 */
/* #define AGL_MULTISCREEN        81 */
/* #define AGL_COMPLIANT          83 */
/* #define AGL_PBUFFER            90 */
#define AGL_BUFFER_MODES         100
#define AGL_MIN_LEVEL            101
#define AGL_MAX_LEVEL            102
#define AGL_COLOR_MODES          103
#define AGL_ACCUM_MODES          104
#define AGL_DEPTH_MODES          105
#define AGL_STENCIL_MODES        106
#define AGL_MAX_AUX_BUFFERS      107
#define AGL_VIDEO_MEMORY         120
#define AGL_TEXTURE_MEMORY       121
#define AGL_RENDERER_COUNT       128

/*
** Integer parameter names
*/
#define AGL_SWAP_RECT	         200  /* Enable or set the swap rectangle              */
#define AGL_BUFFER_RECT          202  /* Enable or set the buffer rectangle            */
#define AGL_SWAP_LIMIT           203  /* Enable or disable the swap async limit        */
#define AGL_COLORMAP_TRACKING    210  /* Enable or disable colormap tracking           */
#define AGL_COLORMAP_ENTRY       212  /* Set a colormap entry to {index, r, g, b}      */
#define AGL_RASTERIZATION        220  /* Enable or disable all rasterization           */
#define AGL_SWAP_INTERVAL        222  /* 0 -> Don't sync, n -> Sync every n retrace    */
#define AGL_STATE_VALIDATION     230  /* Validate state for multi-screen functionality */
#define AGL_BUFFER_NAME          231  /* Set the buffer name. Allows for multi ctx to share a buffer */
#define AGL_ORDER_CONTEXT_TO_FRONT  232  /* Order the current context in front of all the other contexts. */
#define AGL_CONTEXT_SURFACE_ID   233  /* aglGetInteger only - returns the ID of the drawable surface for the context */
#define AGL_CONTEXT_DISPLAY_ID   234  /* aglGetInteger only - returns the display ID(s) of all displays touched by the context, up to a maximum of 32 displays */
#define AGL_SURFACE_ORDER        235  /* Position of OpenGL surface relative to window: 1 -> Above window, -1 -> Below Window */
#define AGL_SURFACE_OPACITY      236  /* Opacity of OpenGL surface: 1 -> Surface is opaque (default), 0 -> non-opaque */
#define AGL_CLIP_REGION          254  /* Enable or set the drawable clipping region */
#define AGL_FS_CAPTURE_SINGLE    255  /* Enable the capture of only a single display for aglFullScreen, normally disabled */
#define AGL_SURFACE_BACKING_SIZE 304  /* 2 params.   Width/height of surface backing size     */
#define AGL_ENABLE_SURFACE_BACKING_SIZE  305  /* Enable or disable surface backing size override */
#define AGL_SURFACE_VOLATILE     306  /* Flag surface to candidate for deletion */
/*
** Option names for aglConfigure.
*/
#define AGL_FORMAT_CACHE_SIZE    501  /* Set the size of the pixel format cache        */
#define AGL_CLEAR_FORMAT_CACHE   502  /* Reset the pixel format cache                  */
#define AGL_RETAIN_RENDERERS     503  /* Whether to retain loaded renderers in memory  */

/* buffer_modes */
#define AGL_MONOSCOPIC_BIT       0x00000001
#define AGL_STEREOSCOPIC_BIT     0x00000002
#define AGL_SINGLEBUFFER_BIT     0x00000004
#define AGL_DOUBLEBUFFER_BIT     0x00000008

/* bit depths */
#define AGL_0_BIT                0x00000001
#define AGL_1_BIT                0x00000002
#define AGL_2_BIT                0x00000004
#define AGL_3_BIT                0x00000008
#define AGL_4_BIT                0x00000010
#define AGL_5_BIT                0x00000020
#define AGL_6_BIT                0x00000040
#define AGL_8_BIT                0x00000080
#define AGL_10_BIT               0x00000100
#define AGL_12_BIT               0x00000200
#define AGL_16_BIT               0x00000400
#define AGL_24_BIT               0x00000800
#define AGL_32_BIT               0x00001000
#define AGL_48_BIT               0x00002000
#define AGL_64_BIT               0x00004000
#define AGL_96_BIT               0x00008000
#define AGL_128_BIT              0x00010000

/* color modes */
#define AGL_RGB8_BIT             0x00000001  /* 8 rgb bit/pixel,     RGB=7:0, inverse colormap         */
#define AGL_RGB8_A8_BIT          0x00000002  /* 8-8 argb bit/pixel,  A=7:0, RGB=7:0, inverse colormap  */
#define AGL_BGR233_BIT           0x00000004  /* 8 rgb bit/pixel,     B=7:6, G=5:3, R=2:0               */
#define AGL_BGR233_A8_BIT        0x00000008  /* 8-8 argb bit/pixel,  A=7:0, B=7:6, G=5:3, R=2:0        */
#define AGL_RGB332_BIT           0x00000010  /* 8 rgb bit/pixel,     R=7:5, G=4:2, B=1:0               */
#define AGL_RGB332_A8_BIT        0x00000020  /* 8-8 argb bit/pixel,  A=7:0, R=7:5, G=4:2, B=1:0        */
#define AGL_RGB444_BIT           0x00000040  /* 16 rgb bit/pixel,    R=11:8, G=7:4, B=3:0              */
#define AGL_ARGB4444_BIT         0x00000080  /* 16 argb bit/pixel,   A=15:12, R=11:8, G=7:4, B=3:0     */
#define AGL_RGB444_A8_BIT        0x00000100  /* 8-16 argb bit/pixel, A=7:0, R=11:8, G=7:4, B=3:0       */
#define AGL_RGB555_BIT           0x00000200  /* 16 rgb bit/pixel,    R=14:10, G=9:5, B=4:0             */
#define AGL_ARGB1555_BIT         0x00000400  /* 16 argb bit/pixel,   A=15, R=14:10, G=9:5, B=4:0       */
#define AGL_RGB555_A8_BIT        0x00000800  /* 8-16 argb bit/pixel, A=7:0, R=14:10, G=9:5, B=4:0      */
#define AGL_RGB565_BIT           0x00001000  /* 16 rgb bit/pixel,    R=15:11, G=10:5, B=4:0            */
#define AGL_RGB565_A8_BIT        0x00002000  /* 8-16 argb bit/pixel, A=7:0, R=15:11, G=10:5, B=4:0     */
#define AGL_RGB888_BIT           0x00004000  /* 32 rgb bit/pixel,    R=23:16, G=15:8, B=7:0            */
#define AGL_ARGB8888_BIT         0x00008000  /* 32 argb bit/pixel,   A=31:24, R=23:16, G=15:8, B=7:0   */
#define AGL_RGB888_A8_BIT        0x00010000  /* 8-32 argb bit/pixel, A=7:0, R=23:16, G=15:8, B=7:0     */
#define AGL_RGB101010_BIT        0x00020000  /* 32 rgb bit/pixel,    R=29:20, G=19:10, B=9:0           */
#define AGL_ARGB2101010_BIT      0x00040000  /* 32 argb bit/pixel,   A=31:30  R=29:20, G=19:10, B=9:0  */
#define AGL_RGB101010_A8_BIT     0x00080000  /* 8-32 argb bit/pixel, A=7:0  R=29:20, G=19:10, B=9:0    */
#define AGL_RGB121212_BIT        0x00100000  /* 48 rgb bit/pixel,    R=35:24, G=23:12, B=11:0          */
#define AGL_ARGB12121212_BIT     0x00200000  /* 48 argb bit/pixel,   A=47:36, R=35:24, G=23:12, B=11:0 */
#define AGL_RGB161616_BIT        0x00400000  /* 64 rgb bit/pixel,    R=47:32, G=31:16, B=15:0          */
#define AGL_ARGB16161616_BIT     0x00800000  /* 64 argb bit/pixel,   A=63:48, R=47:32, G=31:16, B=15:0 */
#define AGL_INDEX8_BIT           0x20000000  /* 8 bit color look up table (deprecated)                 */
#define AGL_INDEX16_BIT          0x40000000  /* 16 bit color look up table (deprecated)				   */
#define AGL_RGBFLOAT64_BIT       0x01000000  /* 64 rgb bit/pixel,    half float                        */
#define AGL_RGBAFLOAT64_BIT      0x02000000  /* 64 argb bit/pixel,   half float                        */
#define AGL_RGBFLOAT128_BIT      0x04000000  /* 128 rgb bit/pixel,   ieee float                        */
#define AGL_RGBAFLOAT128_BIT     0x08000000  /* 128 argb bit/pixel,  ieee float                        */
#define AGL_RGBFLOAT256_BIT      0x10000000  /* 256 rgb bit/pixel,   ieee double                       */
#define AGL_RGBAFLOAT256_BIT     0x20000000  /* 256 argb bit/pixel,  ieee double                       */

/*
** Error return values from aglGetError.
*/
#define AGL_NO_ERROR                 0 /* no error                        */

#define AGL_BAD_ATTRIBUTE        10000 /* invalid pixel format attribute  */
#define AGL_BAD_PROPERTY         10001 /* invalid renderer property       */
#define AGL_BAD_PIXELFMT         10002 /* invalid pixel format            */
#define AGL_BAD_RENDINFO         10003 /* invalid renderer info           */
#define AGL_BAD_CONTEXT          10004 /* invalid context                 */
#define AGL_BAD_DRAWABLE         10005 /* invalid drawable                */
#define AGL_BAD_GDEV             10006 /* invalid graphics device         */
#define AGL_BAD_STATE            10007 /* invalid context state           */
#define AGL_BAD_VALUE            10008 /* invalid numerical value         */
#define AGL_BAD_MATCH            10009 /* invalid share context           */
#define AGL_BAD_ENUM             10010 /* invalid enumerant               */
#define AGL_BAD_OFFSCREEN        10011 /* invalid offscreen drawable      */
#define AGL_BAD_FULLSCREEN       10012 /* invalid offscreen drawable      */
#define AGL_BAD_WINDOW           10013 /* invalid window                  */
#define AGL_BAD_POINTER          10014 /* invalid pointer                 */
#define AGL_BAD_MODULE           10015 /* invalid code module             */
#define AGL_BAD_ALLOC            10016 /* memory allocation failure       */
#define AGL_BAD_CONNECTION       10017 /* invalid CoreGraphics connection */

/************************************************************************/

/*
** Pixel format functions
*/
extern AGLPixelFormat aglChoosePixelFormat(const AGLDevice *gdevs, GLint ndev, const GLint *attribs);
extern void aglDestroyPixelFormat(AGLPixelFormat pix);
extern AGLPixelFormat aglNextPixelFormat(AGLPixelFormat pix);
extern GLboolean aglDescribePixelFormat(AGLPixelFormat pix, GLint attrib, GLint *value);
extern AGLDevice *aglDevicesOfPixelFormat(AGLPixelFormat pix, GLint *ndevs);

/*
** Renderer information functions
*/
extern AGLRendererInfo aglQueryRendererInfo(const AGLDevice *gdevs, GLint ndev);
extern void aglDestroyRendererInfo(AGLRendererInfo rend);
extern AGLRendererInfo aglNextRendererInfo(AGLRendererInfo rend);
extern GLboolean aglDescribeRenderer(AGLRendererInfo rend, GLint prop, GLint *value);

/*
** Context functions
*/
extern AGLContext aglCreateContext(AGLPixelFormat pix, AGLContext share);
extern GLboolean aglDestroyContext(AGLContext ctx);
extern GLboolean aglCopyContext(AGLContext src, AGLContext dst, GLuint mask);
extern GLboolean aglUpdateContext(AGLContext ctx);

/*
** Current state functions
*/
extern GLboolean aglSetCurrentContext(AGLContext ctx);
extern AGLContext aglGetCurrentContext(void);

/*
** Drawable Functions
*/
extern GLboolean aglSetDrawable(AGLContext ctx, AGLDrawable draw);
extern GLboolean aglSetOffScreen(AGLContext ctx, GLsizei width, GLsizei height, GLsizei rowbytes, GLvoid *baseaddr);
extern GLboolean aglSetFullScreen(AGLContext ctx, GLsizei width, GLsizei height, GLsizei freq, GLint device);
extern AGLDrawable aglGetDrawable(AGLContext ctx);

/*
** Virtual screen functions
*/
extern GLboolean aglSetVirtualScreen(AGLContext ctx, GLint screen);
extern GLint aglGetVirtualScreen(AGLContext ctx);

/*
** Obtain version numbers
*/
extern void aglGetVersion(GLint *major, GLint *minor);

/*
** Global library options
*/
extern GLboolean aglConfigure(GLenum pname, GLuint param);

/*
** Swap functions
*/
extern void aglSwapBuffers(AGLContext ctx);

/*
** Per context options
*/
extern GLboolean aglEnable(AGLContext ctx, GLenum pname);
extern GLboolean aglDisable(AGLContext ctx, GLenum pname);
extern GLboolean aglIsEnabled(AGLContext ctx, GLenum pname);
extern GLboolean aglSetInteger(AGLContext ctx, GLenum pname, const GLint *params);
extern GLboolean aglGetInteger(AGLContext ctx, GLenum pname, GLint *params);

/*
** Font function
*/
extern GLboolean aglUseFont(AGLContext ctx, GLint fontID, Style face, GLint size, GLint first, GLint count, GLint base);

/*
** Error functions
*/
extern GLenum aglGetError(void);
extern const GLubyte *aglErrorString(GLenum code);

/*
** Soft reset function
*/
extern void aglResetLibrary(void);

/*
** Surface texture function
*/
extern void aglSurfaceTexture (AGLContext context, GLenum target, GLenum internalformat, AGLContext surfacecontext)    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
** PBuffer functions
*/
extern GLboolean aglCreatePBuffer (GLint width, GLint height, GLenum target, GLenum internalFormat, long max_level, AGLPbuffer *pbuffer)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern GLboolean aglDestroyPBuffer (AGLPbuffer pbuffer)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern GLboolean aglDescribePBuffer (AGLPbuffer pbuffer, GLint *width, GLint *height, GLenum *target, GLenum *internalFormat, GLint *max_level)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern GLboolean aglTexImagePBuffer (AGLContext ctx, AGLPbuffer pbuffer, GLint source)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
** Pbuffer Drawable Functions
*/
extern GLboolean aglSetPBuffer (AGLContext ctx, AGLPbuffer pbuffer, GLint face, GLint level, GLint screen)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern GLboolean aglGetPBuffer (AGLContext ctx, AGLPbuffer *pbuffer, GLint *face, GLint *level, GLint *screen)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
** CGL functions
*/
extern GLboolean aglGetCGLContext(AGLContext ctx, void **cgl_ctx) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern GLboolean aglGetCGLPixelFormat(AGLPixelFormat pix, void **cgl_pix) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* _AGL_H */
