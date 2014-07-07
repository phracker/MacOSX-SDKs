/*
 *  dpsexcept.h      -- exception handling for the DPS client library
 *
 * (c) Copyright 1984-1994 Adobe Systems Incorporated.
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
/* $XFree86: xc/include/DPS/dpsexcept.h,v 1.3 2000/06/07 22:02:56 tsi Exp $ */

/*
Original version: Jeffrey Mogul, Stanford, 18 February 1983
*/

#ifndef DPSEXCEPT_H
#define DPSEXCEPT_H

/* If the macro setjmp_h is defined, it is the #include path to be used
   instead of <setjmp.h>
 */
#ifdef setjmp_h
#include setjmp_h
#else /* setjmp_h */
#ifdef VAXC
#include setjmp
#else /* VAXC */
#include <setjmp.h>
#endif /* VAXC */
#endif /* setjmp_h */

/* 
  This interface defines a machine-independent exception handling
  facility. It depends only on the availability of setjmp and longjmp.
  Note that we depend on native setjmp and longjmp facilities; it's
  not possible to interpose a veneer due to the way setjmp works.
  (In fact, in ANSI C, setjmp is a macro, not a procedure.)

  The exception handler is largely defined by a collection of macros
  that provide some additional "syntax". A stretch of code that needs
  to handle exceptions is written thus:

    DURING
      statement1;
      statement2;
      ...
    HANDLER
      statement3
      statement4;
      ...
    END_HANDLER

  The meaning of this is as follows. Normally, the statements between
  DURING and HANDLER are executed. If no exception occurs, the statements
  between HANDLER and END_HANDLER are bypassed; execution resumes at the
  statement after END_HANDLER.

  If an exception is raised while executing the statements between
  DURING and HANDLER (including any procedure called from those statements),
  execution of those statements is aborted and control passes to the
  statements between HANDLER and END_HANDLER. These statements
  comprise the "exception handler" for exceptions occurring between
  the DURING and the HANDLER.

  The exception handler has available to it two local variables,
  Exception.Code and Exception.Message, which are the values passed
  to the call to RAISE that generated the exception (see below).
  These variables have valid contents only between HANDLER and
  END_HANDLER.

  If the exception handler simply falls off the end (or returns, or
  whatever), propagation of the exception ceases. However, if the
  exception handler executes RERAISE, the exception is propagated to
  the next outer dynamically enclosing occurrence of DURING ... HANDLER.

  There are two usual reasons for wanting to handle exceptions:

  1. To clean up any local state (e.g., deallocate dynamically allocated
     storage), then allow the exception to propagate further. In this
     case, the handler should perform its cleanup, then execute RERAISE.

  2. To recover from certain exceptions that might occur, then continue
     normal execution. In this case, the handler should perform a
     "switch" on Exception.Code to determine whether the exception
     is one it is prepared to recover from. If so, it should perform
     the recovery and just fall through; if not, it should execute
     RERAISE to propagate the exception to a higher-level handler.

  It is ILLEGAL to execute a statement between DURING and HANDLER
  that would transfer control outside of those statements. In particular,
  "return" is illegal (an unspecified malfunction will occur).
  To perform a "return", execute E_RETURN_VOID; to perform a "return(x)",
  execute E_RETURN(x). This restriction does not apply to the statements
  between HANDLER and END_HANDLER.

  Note that in an environment with multiple contexts (i.e., multiple
  coroutines), each context has its own stack of nested exception
  handlers. An exception is raised within the currently executing
  context and transfers control to a handler in the same context; the
  exception does not propagate across context boundaries.
 */


/* Data structures */

typedef struct _Exc_buf_x {
	struct _Exc_buf_x *Prev;	/* exception chain back-pointer */
	jmp_buf Environ;		/* saved environment */
	char *Message;			/* Human-readable cause */
	int Code;			/* Exception code */
} _Exc_Buf;

extern _Exc_Buf *_Exc_Header;	/* global exception chain header */


/* Macros defining the exception handler "syntax":
     DURING statements HANDLER statements END_HANDLER
   (see the description above)
 */

#define	_E_RESTORE	_Exc_Header = Exception.Prev

#define	DURING {_Exc_Buf Exception;\
		 Exception.Prev=_Exc_Header;\
		 _Exc_Header= &Exception;\
		 if (! setjmp(Exception.Environ)) {

#define	HANDLER	_E_RESTORE;} else {

#define	END_HANDLER }}

#define	E_RETURN(x) {_E_RESTORE; return(x);}

#define	E_RTRN_VOID {_E_RESTORE; return;}


/* Exported Procedures */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void DPSRaise(int Code, char *Message);
/* Initiates an exception; always called via the RAISE macro.
   This procedure never returns; instead, the stack is unwound and
   control passes to the beginning of the exception handler statements
   for the innermost dynamically enclosing occurrence of
   DURING ... HANDLER. The Code and Message arguments are passed to
   that handler as described above.

   It is legal to call DPSRaise from within a "signal" handler for a
   synchronous event such as floating point overflow. It is not reasonable
   to do so from within a "signal" handler for an asynchronous event
   (e.g., interrupt), since the exception handler's data structures
   are not updated atomically with respect to asynchronous events.

   If there is no dynamically enclosing exception handler, DPSRaise
   writes an error message to os_stderr and aborts with DPSCantHappen.
 */

extern void DPSCantHappen(void);
/* Calls abort. This is used only to handle "impossible" errors;
   there is no recovery, and DPSCantHappen does not return.
 */


/* The following two operations are invoked only from the exception
   handler macros and from the DPSRaise procedure. Note that they are
   not actually declared here but in <setjmp.h> (or a substitute
   specified by the macro SETJMP, above).

   Note that the exception handler facility uses setjmp/longjmp in
   a stylized way that may not require the full generality of the
   standard setjmp/longjmp mechanism. In particular, setjmp is never
   called during execution of a signal handler; thus, the signal
   mask saved by setjmp can be constant rather than obtained from
   the operating system on each call. This can have considerable
   performance consequences.
 */

#if 0
extern int setjmp(jmp_buf buf);
/* Saves the caller's environment in the buffer (which is an array
   type and therefore passed by pointer), then returns the value zero.
   It may return again if longjmp is executed subsequently (see below).
 */

extern void longjmp(jmp_buf buf, int value);
/* Restores the environment saved by an earlier call to setjmp,
   unwinding the stack and causing setjmp to return again with
   value as its return value (which must be non-zero).
   The procedure that called setjmp must not have returned or
   otherwise terminated. The saved environment must be at an earlier
   place on the same stack as the call to longjmp (in other words,
   it must not be in a different coroutine). It is legal to call
   longjmp in a signal handler and to restore an environment
   outside the signal handler; longjmp must be able to unwind
   the signal cleanly in such a case.
 */
#endif /* 0 */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

/* In-line Procedures */

#define RAISE DPSRaise
/* See DPSRaise above; defined as a macro simply for consistency */

#define	RERAISE	RAISE(Exception.Code, Exception.Message)
/* Called from within an exception handler (between HANDLER and
   END_HANDLER), propagates the same exception to the next outer
   dynamically enclosing exception handler; does not return.
 */

/*
  Error code enumerations

  By convention, error codes are divided into blocks belonging to
  different components of the Display PostScript system.

  Negative error codes and the codes between 0 and 999 (inclusive) are
  reserved for use by the Display PostScript system.
 */

#define dps_err_base 1000

#endif /* DPSEXCEPT_H */
