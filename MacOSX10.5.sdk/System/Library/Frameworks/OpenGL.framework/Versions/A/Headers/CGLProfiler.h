/*
	Copyright:	(c) 2002 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _CGLPROFILER_H
#define _CGLPROFILER_H

#ifdef __cplusplus
extern "C" {
#endif


/* Profiler extensions for CGLContextParameter */

/* Use these parameter names as the argument to CGLSetParameter. */

#define kCGLCPComment ((CGLContextParameter)1232)
        /* param is a pointer to a NULL-terminated C-style string. */
        /* Inserts a context-specific comment into the function trace stream. */
	/* Availability: set only, get is ignored. */
	
#define kCGLCPDumpState ((CGLContextParameter)1233)
        /* param ignored.  Dumps all the gl state. */
	/* Availability: set only, get is ignored. */

#define kCGLCPEnableForceFlush ((CGLContextParameter)1234)
        /* param is GL_TRUE to enable "force flush" mode or GL_FALSE to disable. */
	/* Availability: set and get. */

/* Profiler extensions for CGLGlobalOption */

/* Use these as the parameter name for CGLSetOption to control global profiling
** features from within your application.  Using CGLSetOption()
** overrides the settings you have in OpenGL Profiler.  Example:
**    CGLSetOption(kCGLGOEnableFunctionTrace, GL_TRUE);
**    CGLSetOption(kCGLGOComment, "Start call trace");
*/

#define kCGLGOComment ((CGLGlobalOption)1506)
        /* param is a pointer to a NULL-terminated C-style string. */
	/* Inserts a comment in the trace steam that applies to all contexts. */
	/* Availability: set only, get is ignored. */
	
#define kCGLGOEnableFunctionTrace ((CGLGlobalOption)1507)
        /* param is GL_TRUE or GL_FALSE */
        /* Turns GL function call tracing on and off */
	/* Availability: set and get */
	
#define kCGLGOEnableFunctionStatistics ((CGLGlobalOption)1508)
        /* param is GL_TRUE or GL_FALSE */
        /* Turns GL function counter on and off */
	/* Availability: set and get */

#define kCGLGOResetFunctionTrace ((CGLGlobalOption)1509)
        /* param is ignored */
        /* Erases current function trace and starts a new one */
	/* Availability: set only, get is ignored. */

#define kCGLGOPageBreak ((CGLGlobalOption)1510)
        /* param is ignored */
        /* Inserts a page break into the function trace */
	/* Availability: set only, get is ignored. */

#define kCGLGOResetFunctionStatistics ((CGLGlobalOption)1511)
        /* param is ignored */
        /* Erases current function statistics, resets all counters to 0 and starts a new set */
	/* Availability: set only, get is ignored. */

#define kCGLGOEnableDebugAttach ((CGLGlobalOption)1512)
        /* param is GL_TRUE or GL_FALSE */
        /* Turns proflier attach feature on and off.  Off by default, you can
	   override this with the environment variable GL_ENABLE_DEBUG_ATTACH */
	/* Availability: set only, get is ignored. */

#define kCGLGOHideObjects ((CGLGlobalOption)1513)
        /* param is GL_TRUE to hide all resources from Profiler or GL_FALSE to expose resources to
		   Profiler.  Default is GL_FALSE (expose resources to Profiler). */
	/* Availability: set and get. */


#define kCGLProfBreakBefore  0x0001
#define kCGLProfBreakAfter   0x0002

#define kCGLGOEnableBreakpoint ((CGLGlobalOption)1514)
        /* param is an array of 3 GLints:
				param[0] is function ID (see CGLProfilerFunctionEnum.h)
				param[1] is the logical OR of kCGLProfBreakBefore or kCGLProfBreakAfter, indicating how
				         you want the breakpoint to stop: before entering OpenGL, on return from OpenGL, or both.
				param[2] is a boolean which turns the breakpoint on or off.
		*/
	/* Availability: set and get. */


/* Hardware accelerator controls
**
** Use these as the parameter name for CGLSetOption to control hardware
** accelerator debugging features from within your application.
**
** Sets debugging feature of hardware accelerator.  Unless otherwise noted, a
** non-0 param means turn the feature on, while a 0 param means turn it off.
**
** Availability: set and get
*/

/* Rendering Options */
#define kCGLGOForceSlowRenderingPath         ((CGLGlobalOption)1609)
#define kCGLGODisableImmediateRenderPath     ((CGLGlobalOption)1610)
#define kCGLGODisableCVARenderPath           ((CGLGlobalOption)1611)
#define kCGLGODisableVARRenderPath           ((CGLGlobalOption)1612)
#define kCGLGOForceWireframeRendering        ((CGLGlobalOption)1613)
#define kCGLGOSubmitOnImmediateRenderCommand ((CGLGlobalOption)1614)
#define kCGLGOSubmitOnCVARenderCommand       ((CGLGlobalOption)1615)
#define kCGLGOSubmitOnVAORenderCommand       ((CGLGlobalOption)1616)
#define kCGLGOSubmitOnClearCommand           ((CGLGlobalOption)1617)

/* HW Transform & Lighting Engine Options */
#define kCGLGOForceSoftwareTransformLighting ((CGLGlobalOption)1618)
#define kCGLGOForceSoftwareTexgen            ((CGLGlobalOption)1619)
#define kCGLGOForceSoftwareTRUFORM_ATI       ((CGLGlobalOption)1620)

/* Vertex & Fragment Shader Options */
#define kCGLGOForceSoftwareVertexShaders     ((CGLGlobalOption)1621)
#define kCGLGODisableFragmentShaders_ATI     ((CGLGlobalOption)1622)

/* Texturing Options */
#define kCGLGODisableTexturing               ((CGLGlobalOption)1623)
#define kCGLGOOutlineTexture                 ((CGLGlobalOption)1624)
#define kCGLGOOutlineTextureColor            ((CGLGlobalOption)1625)

/* glBitmap Options */
#define kCGLGOForceSlowBitmapPath            ((CGLGlobalOption)1626)
#define kCGLGODisableBitmap                  ((CGLGlobalOption)1627)

/* glReadPixels Options */
#define kCGLGOForceSlowReadPixelsPath        ((CGLGlobalOption)1630)
#define kCGLGODisableReadPixels              ((CGLGlobalOption)1631)
#define kCGLGOOutlineReadPixelsBuffer        ((CGLGlobalOption)1632)
#define kCGLGOOutlineReadPixelsBufferColor   ((CGLGlobalOption)1633)

/* glDrawPixels Options */
#define kCGLGOForceSlowDrawPixelsPath        ((CGLGlobalOption)1634)
#define kCGLGODisableDrawPixels              ((CGLGlobalOption)1635)
#define kCGLGOOutlineDrawPixelsBuffer        ((CGLGlobalOption)1636)
#define kCGLGOOutlineDrawPixelsBufferColor   ((CGLGlobalOption)1637)

/* glCopyPixels Options */
#define kCGLGOForceSlowCopyPixelsPath        ((CGLGlobalOption)1638)
#define kCGLGODisableCopyPixels              ((CGLGlobalOption)1639)
#define kCGLGOOutlineCopyPixelsBuffer        ((CGLGlobalOption)1640)
#define kCGLGOOutlineCopyPixelsBufferColor   ((CGLGlobalOption)1641)

/* GL Object & State Management Options */
#define kCGLGOMakeAllGLObjectsRequireUpdate  ((CGLGlobalOption)1642)
#define kCGLGOMakeAllGLStateRequireUpdate    ((CGLGlobalOption)1643)

#ifdef __cplusplus
}
#endif

#endif /* _CGLPROFILER_H */
