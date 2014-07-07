/*
        NSOpenGL.h
        Application Kit
        Copyright (c) 2000-2001, Apple Computer, Inc.
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
	NSOpenGLPFAAllRenderers    =   1,	/* choose from all available renderers          */
	NSOpenGLPFADoubleBuffer    =   5,	/* choose a double buffered pixel format        */
	NSOpenGLPFAStereo          =   6,	/* stereo buffering supported                   */
	NSOpenGLPFAAuxBuffers      =   7,	/* number of aux buffers                        */
	NSOpenGLPFAColorSize       =   8,	/* number of color buffer bits                  */
	NSOpenGLPFAAlphaSize       =  11,	/* number of alpha component bits               */
	NSOpenGLPFADepthSize       =  12,	/* number of depth buffer bits                  */
	NSOpenGLPFAStencilSize     =  13,	/* number of stencil buffer bits                */
	NSOpenGLPFAAccumSize       =  14,	/* number of accum buffer bits                  */
	NSOpenGLPFAMinimumPolicy   =  51,	/* never choose smaller buffers than requested  */
	NSOpenGLPFAMaximumPolicy   =  52,	/* choose largest buffers of type requested     */
	NSOpenGLPFAOffScreen       =  53,	/* choose an off-screen capable renderer        */
	NSOpenGLPFAFullScreen      =  54,	/* choose a full-screen capable renderer        */
	NSOpenGLPFARendererID      =  70,	/* request renderer by ID                       */
	NSOpenGLPFASingleRenderer  =  71,	/* choose a single renderer for all screens     */
	NSOpenGLPFANoRecovery      =  72,	/* disable all failure recovery systems         */
	NSOpenGLPFAAccelerated     =  73,	/* choose a hardware accelerated renderer       */
	NSOpenGLPFAClosestPolicy   =  74,	/* choose the closest color buffer to request   */
	NSOpenGLPFARobust          =  75,	/* renderer does not need failure recovery      */
	NSOpenGLPFABackingStore    =  76,	/* back buffer contents are valid after swap    */
	NSOpenGLPFAMPSafe          =  78,	/* renderer is multi-processor safe             */
	NSOpenGLPFAWindow          =  80,	/* can be used to render to an onscreen window  */
	NSOpenGLPFAMultiScreen     =  81,	/* single window can span multiple screens      */
	NSOpenGLPFACompliant       =  83,	/* renderer is opengl compliant                 */
	NSOpenGLPFAScreenMask      =  84	/* bit mask of supported physical screens       */
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

@end


/*****************
** NSOpenGLContext
*****************/

/*
** Parameter names for [NSOpenGLContext setParameter] and [NSOpenGLContext getParameter].
*/
typedef enum {
	NSOpenGLCPSwapRectangle       = 200,	/* Set or get the swap rectangle {x, y, w, h}    */
	NSOpenGLCPSwapRectangleEnable = 201,	/* Enable or disable the swap rectangle          */
	NSOpenGLCPRasterizationEnable = 221,	/* Enable or disable all rasterization           */
	NSOpenGLCPSwapInterval        = 222,	/* 0 -> Don't sync, n -> Sync every n retrace    */
	NSOpenGLCPStateValidation     = 301	/* Validate state for multi-screen functionality */
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

@end

