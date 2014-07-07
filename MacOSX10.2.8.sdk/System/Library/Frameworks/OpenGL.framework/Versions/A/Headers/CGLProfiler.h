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

#ifdef __cplusplus
}
#endif

#endif /* _CGLPROFILER_H */
