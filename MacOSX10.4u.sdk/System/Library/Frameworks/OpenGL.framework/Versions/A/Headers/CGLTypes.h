/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _CGLTYPES_H
#define _CGLTYPES_H

#ifdef __cplusplus
extern "C" {
#endif


/*
** CGL opaque data.
*/
typedef struct _CGLContextObject       *CGLContextObj;
typedef struct _CGLPixelFormatObject   *CGLPixelFormatObj;
typedef struct _CGLRendererInfoObject  *CGLRendererInfoObj;
typedef struct _CGLPBufferObject       *CGLPBufferObj;

/*
** Attribute names for CGLChoosePixelFormat and CGLDescribePixelFormat.
*/
typedef enum _CGLPixelFormatAttribute {
	kCGLPFAAllRenderers       =   1,	/* choose from all available renderers          */
	kCGLPFADoubleBuffer       =   5,	/* choose a double buffered pixel format        */
	kCGLPFAStereo             =   6,	/* stereo buffering supported                   */
	kCGLPFAAuxBuffers         =   7,	/* number of aux buffers                        */
	kCGLPFAColorSize          =   8,	/* number of color buffer bits                  */
	kCGLPFAAlphaSize          =  11,	/* number of alpha component bits               */
	kCGLPFADepthSize          =  12,	/* number of depth buffer bits                  */
	kCGLPFAStencilSize        =  13,	/* number of stencil buffer bits                */
	kCGLPFAAccumSize          =  14,	/* number of accum buffer bits                  */
	kCGLPFAMinimumPolicy      =  51,	/* never choose smaller buffers than requested  */
	kCGLPFAMaximumPolicy      =  52,	/* choose largest buffers of type requested     */
	kCGLPFAOffScreen          =  53,	/* choose an off-screen capable renderer        */
	kCGLPFAFullScreen         =  54,	/* choose a full-screen capable renderer        */
	kCGLPFASampleBuffers      =  55,	/* number of multi sample buffers               */
	kCGLPFASamples            =  56,	/* number of samples per multi sample buffer    */
	kCGLPFAAuxDepthStencil    =  57,	/* each aux buffer has its own depth stencil    */
	kCGLPFAColorFloat         =  58,	/* color buffers store floating point pixels    */
	kCGLPFAMultisample        =  59,	/* choose multisampling                         */
	kCGLPFASupersample        =  60,	/* choose supersampling                         */
	kCGLPFASampleAlpha        =  61,	/* request alpha filtering                      */

	kCGLPFARendererID         =  70,	/* request renderer by ID                       */
	kCGLPFASingleRenderer     =  71,	/* choose a single renderer for all screens     */
	kCGLPFANoRecovery         =  72,	/* disable all failure recovery systems         */
	kCGLPFAAccelerated        =  73,	/* choose a hardware accelerated renderer       */
	kCGLPFAClosestPolicy      =  74,	/* choose the closest color buffer to request   */
	kCGLPFARobust             =  75,	/* renderer does not need failure recovery      */
	kCGLPFABackingStore       =  76,	/* back buffer contents are valid after swap    */
	kCGLPFAMPSafe             =  78,	/* renderer is multi-processor safe             */
	kCGLPFAWindow             =  80,	/* can be used to render to an onscreen window  */
	kCGLPFAMultiScreen        =  81,	/* single window can span multiple screens      */
	kCGLPFACompliant          =  83,	/* renderer is opengl compliant                 */
	kCGLPFADisplayMask        =  84,	/* mask limiting supported displays             */
	kCGLPFAPBuffer            =  90,	/* can be used to render to a pbuffer           */
	kCGLPFARemotePBuffer      =  91,	/* can be used to render offline to a pbuffer   */
	kCGLPFAVirtualScreenCount = 128 	/* number of virtual screens in this format     */
} CGLPixelFormatAttribute;

/*
** Property names for CGLDescribeRenderer.
*/
typedef enum _CGLRendererProperty {
	kCGLRPOffScreen           =  53,
	kCGLRPFullScreen          =  54,
	kCGLRPRendererID          =  70,
	kCGLRPAccelerated         =  73,
	kCGLRPRobust              =  75,
	kCGLRPBackingStore        =  76,
	kCGLRPMPSafe              =  78,
	kCGLRPWindow              =  80,
	kCGLRPMultiScreen         =  81,
	kCGLRPCompliant           =  83,
	kCGLRPDisplayMask         =  84,
	kCGLRPBufferModes         = 100,	/* a bitfield of supported buffer modes          */
	kCGLRPColorModes          = 103,	/* a bitfield of supported color buffer formats  */
	kCGLRPAccumModes          = 104,	/* a bitfield of supported accum buffer formats  */
	kCGLRPDepthModes          = 105,	/* a bitfield of supported depth buffer depths   */
	kCGLRPStencilModes        = 106,	/* a bitfield of supported stencil buffer depths */
	kCGLRPMaxAuxBuffers       = 107,	/* maximum number of auxilliary buffers          */
	kCGLRPMaxSampleBuffers    = 108,	/* maximum number of sample buffers              */
	kCGLRPMaxSamples          = 109,	/* maximum number of samples                     */
	kCGLRPSampleModes         = 110,	/* a bitfield of supported sample modes          */
	kCGLRPSampleAlpha         = 111,	/* support for alpha sampling                    */
	kCGLRPVideoMemory         = 120,	/* total video memory                            */
	kCGLRPTextureMemory       = 121,	/* video memory useable for texture storage      */
	kCGLRPGPUVertProcCapable  = 122,	/* renderer capable of GPU vertex processing     */
	kCGLRPGPUFragProcCapable  = 123,	/* renderer capable of GPU fragment processing   */
	kCGLRPRendererCount       = 128 	/* the number of renderers in this renderer info */
} CGLRendererProperty;

/*
** Enable names for CGLEnable, CGLDisable, and CGLIsEnabled.
*/
typedef enum _CGLContextEnable {
	kCGLCESwapRectangle    = 201,	/* Enable or disable the swap rectangle          */
	kCGLCESwapLimit        = 203,	/* Enable or disable the swap async limit        */
	kCGLCERasterization    = 221,	/* Enable or disable all rasterization           */
	kCGLCEStateValidation  = 301,	/* Validate state for multi-screen functionality */
	kCGLCESurfaceBackingSize = 305, /* Enable or disable surface backing size override */
	kCGLCEDisplayListOptimization = 307,  /* Ability to turn off display list optimizer */
	kCGLCEMPEngine = 313            /* Enable or disable multi-threaded GL engine    */
} CGLContextEnable;

/*
** Parameter names for CGLSetParameter and CGLGetParameter.
*/
typedef enum _CGLContextParameter {
	kCGLCPSwapRectangle     = 200,  /* 4 params.  Set or get the swap rectangle {x, y, w, h}  */
	kCGLCPSwapInterval      = 222,  /* 1 param.   0 -> Don't sync, n -> Sync every n retrace  */
	kCGLCPDispatchTableSize = 224,  /* 1 param.   Get the dispatch table size                 */
	/* Note: kCGLCPClientStorage is always a pointer-sized parameter, even though the API claims GLint. */
	kCGLCPClientStorage     = 226,  /* 1 param.   Context specific generic storage            */
	kCGLCPSurfaceTexture    = 228,  /* 3 params.  SID, target, internal_format                */
/*  - Used by AGL - */
/*  AGL_STATE_VALIDATION     230    */
/*  AGL_BUFFER_NAME          231    */
/*  AGL_ORDER_CONTEXT_TO_FRONT  232 */
/*  AGL_CONTEXT_SURFACE_ID   233    */
/*  AGL_CONTEXT_DISPLAY_ID   234    */
	kCGLCPSurfaceOrder      = 235,  /* 1 param.   1 -> Above window, -1 -> Below Window       */
	kCGLCPSurfaceOpacity    = 236,  /* 1 param.   1 -> Surface is opaque (default), 0 -> non-opaque */
/*  - Used by AGL - */
/*  AGL_CLIP_REGION          254   */
/*  AGL_FS_CAPTURE_SINGLE    255   */
	kCGLCPSurfaceBackingSize = 304,  	/* 2 params.   Width/height of surface backing size     */
/* AGL_SURFACE_VOLATILE		 306	*/
	kCGLCPSurfaceSurfaceVolatile = 306,	/* 1 param.   Surface volatile state					*/
	kCGLCPReclaimResources		 = 308,	/* 0 params.  */
	kCGLCPCurrentRendererID      = 309,	/* 1 param.   Retrieves the current renderer ID         */
	kCGLCPGPUVertexProcessing	 = 310, /* 1 param.   Currently processing vertices with GPU (get) */
	kCGLCPGPUFragmentProcessing	 = 311, /* 1 param.   Currently processing fragments with GPU (get) */
} CGLContextParameter;

/*
** Option names for CGLSetOption and CGLGetOption.
*/
typedef enum _CGLGlobalOption {
	kCGLGOFormatCacheSize  = 501,	/* Set the size of the pixel format cache        */
	kCGLGOClearFormatCache = 502,	/* Reset the pixel format cache if true          */
	kCGLGORetainRenderers  = 503,	/* Whether to retain loaded renderers in memory  */
	kCGLGOResetLibrary     = 504,	/* *** DEPRECATED in MacOS X 10.4 ***            */
	                             	/* Do a soft reset of the CGL library if true    */
	kCGLGOUseErrorHandler  = 505,	/* Call the Core Graphics handler on CGL errors  */
} CGLGlobalOption;

/*
** Error return values from CGLGetError.
*/
typedef enum _CGLError {
	kCGLNoError            = 0,     /* no error */
	kCGLBadAttribute       = 10000,	/* invalid pixel format attribute  */
	kCGLBadProperty        = 10001,	/* invalid renderer property       */
	kCGLBadPixelFormat     = 10002,	/* invalid pixel format            */
	kCGLBadRendererInfo    = 10003,	/* invalid renderer info           */
	kCGLBadContext         = 10004,	/* invalid context                 */
	kCGLBadDrawable        = 10005,	/* invalid drawable                */
	kCGLBadDisplay         = 10006,	/* invalid graphics device         */
	kCGLBadState           = 10007,	/* invalid context state           */
	kCGLBadValue           = 10008,	/* invalid numerical value         */
	kCGLBadMatch           = 10009,	/* invalid share context           */
	kCGLBadEnumeration     = 10010,	/* invalid enumerant               */
	kCGLBadOffScreen       = 10011,	/* invalid offscreen drawable      */
	kCGLBadFullScreen      = 10012,	/* invalid offscreen drawable      */
	kCGLBadWindow          = 10013,	/* invalid window                  */
	kCGLBadAddress         = 10014,	/* invalid pointer                 */
	kCGLBadCodeModule      = 10015,	/* invalid code module             */
	kCGLBadAlloc           = 10016,	/* invalid memory allocation       */
	kCGLBadConnection      = 10017 	/* invalid CoreGraphics connection */
} CGLError;


/* 
** Buffer modes
*/
#define kCGLMonoscopicBit   0x00000001
#define kCGLStereoscopicBit 0x00000002
#define kCGLSingleBufferBit 0x00000004
#define kCGLDoubleBufferBit 0x00000008

/*
** Depth and stencil buffer depths
*/
#define kCGL0Bit            0x00000001
#define kCGL1Bit            0x00000002
#define kCGL2Bit            0x00000004
#define kCGL3Bit            0x00000008
#define kCGL4Bit            0x00000010
#define kCGL5Bit            0x00000020
#define kCGL6Bit            0x00000040
#define kCGL8Bit            0x00000080
#define kCGL10Bit           0x00000100
#define kCGL12Bit           0x00000200
#define kCGL16Bit           0x00000400
#define kCGL24Bit           0x00000800
#define kCGL32Bit           0x00001000
#define kCGL48Bit           0x00002000
#define kCGL64Bit           0x00004000
#define kCGL96Bit           0x00008000
#define kCGL128Bit          0x00010000

/*
** Color and accumulation buffer formats.
*/
#define kCGLRGB444Bit       0x00000040  /* 16 rgb bit/pixel,    R=11:8, G=7:4, B=3:0              */
#define kCGLARGB4444Bit     0x00000080  /* 16 argb bit/pixel,   A=15:12, R=11:8, G=7:4, B=3:0     */
#define kCGLRGB444A8Bit     0x00000100  /* 8-16 argb bit/pixel, A=7:0, R=11:8, G=7:4, B=3:0       */
#define kCGLRGB555Bit       0x00000200  /* 16 rgb bit/pixel,    R=14:10, G=9:5, B=4:0             */
#define kCGLARGB1555Bit     0x00000400  /* 16 argb bit/pixel,   A=15, R=14:10, G=9:5, B=4:0       */
#define kCGLRGB555A8Bit     0x00000800  /* 8-16 argb bit/pixel, A=7:0, R=14:10, G=9:5, B=4:0      */
#define kCGLRGB565Bit       0x00001000  /* 16 rgb bit/pixel,    R=15:11, G=10:5, B=4:0            */
#define kCGLRGB565A8Bit     0x00002000  /* 8-16 argb bit/pixel, A=7:0, R=15:11, G=10:5, B=4:0     */
#define kCGLRGB888Bit       0x00004000  /* 32 rgb bit/pixel,    R=23:16, G=15:8, B=7:0            */
#define kCGLARGB8888Bit     0x00008000  /* 32 argb bit/pixel,   A=31:24, R=23:16, G=15:8, B=7:0   */
#define kCGLRGB888A8Bit     0x00010000  /* 8-32 argb bit/pixel, A=7:0, R=23:16, G=15:8, B=7:0     */
#define kCGLRGB101010Bit    0x00020000  /* 32 rgb bit/pixel,    R=29:20, G=19:10, B=9:0           */
#define kCGLARGB2101010Bit  0x00040000  /* 32 argb bit/pixel,   A=31:30  R=29:20, G=19:10, B=9:0  */
#define kCGLRGB101010_A8Bit 0x00080000  /* 8-32 argb bit/pixel, A=7:0  R=29:20, G=19:10, B=9:0    */
#define kCGLRGB121212Bit    0x00100000  /* 48 rgb bit/pixel,    R=35:24, G=23:12, B=11:0          */
#define kCGLARGB12121212Bit 0x00200000  /* 48 argb bit/pixel,   A=47:36, R=35:24, G=23:12, B=11:0 */
#define kCGLRGB161616Bit    0x00400000  /* 64 rgb bit/pixel,    R=63:48, G=47:32, B=31:16         */
#define kCGLRGBA16161616Bit 0x00800000  /* 64 argb bit/pixel,   R=63:48, G=47:32, B=31:16, A=15:0 */
#define kCGLRGBFloat64Bit   0x01000000  /* 64 rgb bit/pixel,    half float                        */
#define kCGLRGBAFloat64Bit  0x02000000  /* 64 argb bit/pixel,   half float                        */
#define kCGLRGBFloat128Bit  0x04000000  /* 128 rgb bit/pixel,   ieee float                        */
#define kCGLRGBAFloat128Bit 0x08000000  /* 128 argb bit/pixel,  ieee float                        */
#define kCGLRGBFloat256Bit  0x10000000  /* 256 rgb bit/pixel,   ieee double                       */
#define kCGLRGBAFloat256Bit 0x20000000  /* 256 argb bit/pixel,  ieee double                       */

/*
** Sampling modes
*/
#define kCGLSupersampleBit 0x00000001
#define kCGLMultisampleBit 0x00000002

/* Obsolete */
#define kCGLARGB16161616Bit kCGLRGBA16161616Bit


#ifdef __cplusplus
}
#endif

#endif /* _CGLTYPES_H */
