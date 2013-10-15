/*
 * dpsNXargs.h  -- constant values for XDPSNXSetClientArg()
 *
 * (c) Copyright 1993-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */

#ifndef DPSNXARGS_H
#define DPSNXARGS_H

/*    XDPSNXSetClientArg arg values    */

#define XDPSNX_AGENT 0		/* val := (char *), default := NULL
				 * val is a string in the form:
				 *   transport/host:[:]port
				 * specifying the agent to establish a
				 * connection with.
				 */
#define XDPSNX_EXEC_FILE 1	/* val := (char *), default := (see docs)
				 * val is a string giving the name of the
				 * agent executable to launch if
				 * XDPSNX_AUTO_LAUNCH is set to true.  The
				 * caller may explicity give the full path to
				 * the agent in val or just the name - which
				 * will cause the user's search path to
				 * searched for the named program file.
				 */
#define XDPSNX_EXEC_ARGS 2	/* val := (char **), default := NULL
				 * val is expected to be a pointer to an array
				 * of pointers to the arguments to be given to
				 * the program specified by
				 * XDPSNX_EXEC_FILE.
				 * Last array member must be (char *) NULL.
				 */
#define XDPSNX_AUTO_LAUNCH 3	/* val := Bool, default := False
				 * val specifies if library cannot find a
				 * suitable agent to connect to then it should
				 * try to start the one defined by
				 * XDPSNX_EXEC_FILE with XDPSNX_EXEC_ARGS as
				 * arguments.
				 */
#define XDPSNX_LAUNCHED_AGENT_TRANS 4
                                /* val := int, default := XDPSNX_USE_BEST
				 * val specifies the transport a new, auto-
				 * launched agent is to use.  See values
				 * below.
				 */
#define XDPSNX_LAUNCHED_AGENT_PORT 5
                                /* val := int, default := XDPSNX_USE_BEST
				 * val specifies the port that a new, auto-
				 * launched agent is to use for advertising in
				 * the transport protocol specified by
				 * XDPSNX_LAUNCHED_AGENT_TRANS. The default
				 * port of XDPXNX_USE_BEST specifies that
				 * the agent is to use its default
				 * "well-known" port.
				 */
#define XDPSNX_REQUEST_XSYNC 6
				/* val := (Display *), default := NULL
				 * val specifies a Display handle whose DPS
				 * request handling mode should be changed.
				 * When ANY DPS request is called, 
				 * an unconditional XSync is done on the
				 * Display before sending the DPS request.
				 * This guarantees that any buffered X requests
				 * are processed by the server before the
				 * DPS request is sent to the agent.
				 * The DPS request itself is flushed to the
				 * agent.  This mode is primarily useful
				 * for debugging.
				 */
#define XDPSNX_REQUEST_RECONCILE 7
				/* val := (Display *), default := NULL
				 * val specifies a Display handle whose DPS
				 * request handling mode should be changed.
				 * When ANY DPS request is called, 
				 * the logical equivalent of the routine
				 * XDPSReconcileRequests is done on the
				 * Display before sending the DPS request.
				 * This guarantees that any buffered X requests
				 * will be processed by the server before the
				 * DPS request is processed by the agent.
				 * Connections to the server and agent are
				 * flushed.  This is the default mode.
				 */
#define XDPSNX_REQUEST_BUFFER 8
				/* val := (Display *), default := NULL
				 * val specifies a display handle whose DPS
				 * request handling mode should be changed.
				 * When ANY DPS request is called,
				 * the DPS request is simply buffered as
				 * usual.  This is equivalent to what happens
				 * when the Client Library drives a DPS/X
				 * server extension.  This mode should
				 * only be used when the app has adequate
				 * synchronization through explicit calls
				 * to XDPSReconcileRequests.
				 */
/* DPS NX 2.0 */
#define XDPSNX_GC_UPDATES_SLOW	9
				/* val := (Display *), default := NULL
				 * val specifies a Display handle whose GC
				 * update handling mode should be changed.
				 * The library automatically tracks changes
				 * to the GCs used by the application.
				 * When ANY GC is changed by any component
				 * of the application (widget, toolkit, etc.), 
				 * a notification of the change is sent
				 * to the agent.  This guarantees that
				 * the agent tracks all GC changes that
				 * it cares about correctly, at the cost
				 * of sending unnecessary updates for GC's
				 * that the agent doesn't care about.
				 * Connections to the server and agent are
				 * are both syncronized.
				 * This is the default mode.
				 */
#define XDPSNX_GC_UPDATES_FAST	10
				/* val := (Display *), default := NULL
				 * val specifies a Display handle whose GC
				 * update handling mode should be changed.
				 * No automatic tracking of GC changes is
				 * done.  The library depends upon the
				 * application to do explicit notification
				 * of relevant GC changes by using the
				 * XDPSFlushGC() function.  Setting this
				 * mode means that the application commits
				 * to all updates, including components
				 * linked in (widgets, toolkits), with the
				 * benefit of substantial performance
				 * enhancement in certain situations.  Do
				 * not use this mode unless you are sure
				 * that all components of your application
				 * use XDPSFlushGC() properly, or else
				 * inaccurate display renderings will occur.
				 * No additional synchronization occurs.
				 */
#define XDPSNX_SEND_BUF_SIZE 11
                                /* val := int, default := XDPSNX_USE_BEST
				 * val specifies the size in bytes that
				 * the library should use for low-level
				 * output buffering on the agent connection.
				 * Sizes less than 4096 or greater than
				 * 65536 are ignored. 
				 */

#define XDPSNXLASTARG XDPSNX_SEND_BUF_SIZE

/* ---Special Values--- */

#define XDPSNX_USE_BEST	      -1

/* ---Transport Values--- */

#define XDPSNX_TRANS_UNIX     0
#define XDPSNX_TRANS_TCP      1
#define XDPSNX_TRANS_DECNET   2


/*    XDPSNXSetAgentArg arg values    */

#define AGENT_ARG_SMALLFONTS	-1
				/* val := (AGENT_SMALLFONTS_*, see below),
				 * default := AGENT_SMALLFONTS_ACCURATE.
				 * The value of this argument tells the
				 * agent whether fonts with small sizes
				 * (6-24 points) should be shown with
				 * accurate spacing but slowly, or as
				 * fast as possible with potentially
				 * inaccurate spacing.   This argument
				 * is a hint: the agent may not be able
				 * to satisfy the request for fast showing
				 * if matching screen fonts cannot be found. 
				 */

#define AGENT_ARG_PIXMEM	-2
				/* val := (AGENT_PIXMEM_*, see below),
				 * default := AGENT_PIXMEM_LIMITED.
				 * The value of this argument is a hint
				 * to the agent about the availability
				 * of pixmap storage on the X server.
				 * If there is ample pixmap memory, the
				 * agent can use various caching techniques
				 * to improve performance.   If memory
				 * is limited, the agent will minimize its
				 * use of pixmaps.  This argument is
				 * a hint: the agent may not be able to
				 * do anything about the specified value.
				 */

#define AGENTLASTARG AGENT_ARG_PIXMEM

/* ---AGENT_ARG_SMALLFONTS Values--- */
#define AGENT_SMALLFONTS_ACCURATE	0
#define AGENT_SMALLFONTS_FAST		1

/* ---AGENT_ARG_PIXMEM--- */
#define AGENT_PIXMEM_LIMITED		0
#define AGENT_PIXMEM_MODERATE		1
#define AGENT_PIXMEM_UNLIMITED		2

#endif /* DPSNXARGS_H */
