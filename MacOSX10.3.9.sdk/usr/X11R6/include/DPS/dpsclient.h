/*
 * dpsclient.h - Application interface to the Display PostScript Library.
 *
 * (c) Copyright 1988-1994 Adobe Systems Incorporated.
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
/* $XFree86: xc/include/DPS/dpsclient.h,v 1.4 2001/08/01 00:44:34 tsi Exp $ */

#ifndef DPSCLIENT_H
#define DPSCLIENT_H

#include <DPS/dpsfriends.h>

/*=== TYPES ===*/

typedef int DPSErrorCode;

/* Standard error codes (type DPSErrorCode)
 * These are intended to be used with dpsexcept.h
 * System-specific extensions can be made. Codes 1000 through 1099 are
 * reserved for use by Adobe.
 */

#define dps_err_ps 1000
#define dps_err_nameTooLong 1001
#define dps_err_resultTagCheck 1002
#define dps_err_resultTypeCheck 1003
#define dps_err_invalidContext 1004
#define dps_err_invalidAccess 1005

  /* The above definitions specify the error codes passed to a DPSErrorProc:

       dps_err_ps identifies standard PostScript language interpreter
       errors. The arg1 argument to the errorProc is the address of the
       binary object sequence sent by the handleerror (or resynchandleerror)
       operator to report the error. The sequence has 1 object, which is an
       array of 4 objects. See the language extensions document for details
       on the contents of this sequence. arg2 is the number of bytes in the
       entire binary object sequence.

       dps_err_nameTooLong flags user names that are too long. 128 chars
       is the maximum length for PostScript language names. The name and its
       length are passed as arg1 and arg2 to the error proc.

       dps_err_resultTagCheck flags erroneous result tags, most likely
       due to erroneous explicit use of the printobject operator. The
       pointer to the binary object sequence and its length are passed
       as arg1 and arg2 to the error proc. There is one object in the
       sequence.

       dps_err_resultTypeCheck flags incompatible result types. A pointer
       to the offending binary object is passed as arg1; arg2 is unused.

       dps_err_invalidContext flags an invalid DPSContext argument. An
       attempt to send PostScript language code to a context that has
       terminated is the most likely cause of this error. arg1 to the
       DPSErrorProc is the context id (see the fork operator); arg2 is
       unused.

       dps_err_invalidAccess flags an attempt to access a context in
       a way that it does not support.  An example is waiting for return
       values on a text context.
  */

typedef void (*DPSTextProc)(
			    struct _t_DPSContextRec *ctxt, char *buf,
			    long unsigned int count
);

  /* Call-back procedure to handle text from the PostScript interpreter.
     'buf' contains 'count' bytes of ASCII text. */

typedef void (*DPSErrorProc)(
			     struct _t_DPSContextRec *ctxt,
			     DPSErrorCode errorCode,
			     long unsigned int arg1, long unsigned int arg2
);
  
  /* Call-back procedure to report errors from the PostScript interpreter.
     The meaning of arg1 and arg2 depend on 'errorCode', as described above.
     See DPSDefaultErrorProc, below.
   */

typedef struct {
    int systemNameIndex;
    char *operatorName;
    char *abbrev;
} DPSAbbrevRec;

  /* Abbreviation table for standard context abbreviations.  See 
     DPSFetchAbbrevList, below.
   */

typedef enum {dps_context_execution, dps_context_text} DPSContextType;

  /* See DPSGetContextType below */

/*=== PROCEDURES ===*/

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void DPSversion(DPSContext ctxt, int bufsize, char buf[]);

extern void DPSDefaultErrorProc(DPSContext ctxt, DPSErrorCode errorCode,
				long unsigned int arg1,
				long unsigned int arg2);
  
  /* A sample DPSErrorProc for handling errors from the PostScript interpreter.
     The meaning of arg1 and arg2 depend on 'errorCode'. See DPSErrorCode,
     above.

     DPSDefaultErrorProc formulates a text message and passes it to the
     text backstop proc (see DPSSetTextBackstop).
     
     If errorCode == dps_err_ps AND the application had previously caused
     resyncstart to be executed by ctxt, DPSDefaultErrorProc calls
     RAISE(dps_err_ps, ctxt) after invoking the text backstop proc.
     DPSDefaultErrorProc is the only procedure in the Display PostScript
     library that calls RAISE, and it calls RAISE only in the case outlined
     above.
     
     When DPSDefaultErrorProc is used as a context's errorProc, the exception
     to report dps_err_ps can be raised by any of the procedures in the Display
     PostScript library, even ones invoked to deal with other contexts. Note
     therefore that wraps might raise this exception. Applications that use
     resyncstart must be prepared to handle exceptions. 
     
     See DPSResetContext for details on what to do when an exception to
     report dps_err_ps is raised.

     See dpsexcept.h for general information on RAISE and exception handling */

extern void DPSSetTextBackstop(DPSTextProc textProc);

  /* Call this to establish textProc as the handler for text output from
     DPSDefaultErrorProc or from contexts created by the 'fork' operator but
     not made known to the dps client library. NULL will be passed as the ctxt
     argument to textProc in the latter case. */

extern DPSTextProc DPSGetCurrentTextBackstop(void);

  /* Returns the textProc passed most recently to DPSSetTextBackstop, or NULL
     if none */

extern void DPSSetErrorBackstop(DPSErrorProc errorProc);

  /* Call this to establish errorProc as the handler for PostScript interpreter
     errors from contexts created by the 'fork' operator but not made
     known to the dps client library. NULL will be passed as the ctxt
     argument to errorProc. */

extern DPSErrorProc DPSGetCurrentErrorBackstop(void);

  /* Returns the errorProc passed most recently to DPSSetErrorBackstop, or NULL
     if none */

extern DPSContext DPSGetCurrentContext(void);

  /* Get the default context. Used in conjunction with psops.h and with
     wraps that are defined without an explicit DPSContext argument. 
     Initially NULL. */

extern void DPSSetContext(DPSContext ctxt);

  /* Set the default context. Used in conjunction with psops.h and with
     wraps that are defined without an explicit DPSContext argument. */

extern void DPSWritePostScript(DPSContext ctxt, char *buf,
			       unsigned int count);

  /* Send as input to 'ctxt' 'count' bytes of PostScript language contained
     in 'buf'. The code may be in either of the 3 encodings for PostScript
     language programs: plain text, encoded tokens, or binary object sequence.
     If the form is encoded tokens or binary object sequence, an entire
     one of these must be sent (perhaps in a series of calls on
     DPSWritePostScript) before PostScript language in a different encoding
     can be sent.
     
     DPSWritePostScript may transform the PostScript language to a different
     encoding, depending on the characteristics established for 'ctxt' when
     it was created. For example, a context created to store its PostScript
     in an ASCII file would convert binary object sequences to ASCII.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc.
     
     If 'ctxt' is incapable of accepting more PostScript language, for example
     because it is backlogged with code that was sent earlier to be executed,
     this will block until transmission of 'count' bytes can be completed. */

extern void DPSPrintf(DPSContext ctxt, char *fmt, ...);

  /* Write string 'fmt' to ctxt with the optional arguments converted,
     formatted and logically inserted into the string in a manner
     identical to the C library routine printf.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc.
     
     If 'ctxt' is incapable of accepting more PostScript language, for example
     because it is backlogged with code that was sent earlier to be executed,
     this will block until transmission of the string can be completed. */

extern void DPSWriteData(DPSContext ctxt, char *buf, unsigned int count);
  
  /* Write 'count' bytes of data from 'buf' to 'ctxt'. This will not
     change the data.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc.
     
     If 'ctxt' is incapable of accepting more PostScript language, for example
     because it is backlogged with code that was sent earlier to be executed,
     this will block until transmission of 'count' bytes can be completed. */
  
extern void DPSFlushContext(DPSContext ctxt);
  
  /* Force any buffered data to be sent to ctxt.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc.
     
     If 'ctxt' is incapable of accepting more PostScript language, for example
     because it is backlogged with code that was sent earlier to be executed,
     this will block until transmission of all buffered bytes can be completed.
     */
  
extern int DPSChainContext(DPSContext parent, DPSContext child);

  /* This links child and all of child's children onto parent's 'chainChild'
     list. The 'chainChild' list threads those contexts that automatically
     receive copies of any PostScript code sent to parent. A context may
     appear on only one such list.
     
     Normally, DPSChainContext returns 0. It returns -1 if child already
     appears on some other context's 'chainChild' list. */

extern void DPSUnchainContext(DPSContext ctxt);

  /* This unlinks ctxt from the chain that it is on, if any. It leaves
	ctxt->chainParent == ctxt->chainChild == NULL
   */

extern void DPSResetContext(DPSContext ctxt);
  
  /* This should be called by the application in its HANDLER clauses
     when Exception.Code == dps_err_ps. See the discussion above about
     DPSDefaultErrorProc. Also see the discussion of error handling in
     the client library documentation.
     
     DPSResetContext closes the input stream to the server for the context
     and discards any pending bytes on the output stream from the server for
     the context. It then waits for this output stream to close, then reopens
     both streams. DPSResetContext is designed to work with resyncstart to
     leave the context ready to read and execute more input after handling
     a PostScript error.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc. */
  
extern void DPSInterruptContext(DPSContext ctxt);

  /* Sends a request to the server to interrupt execution of the context.
     This causes a PostScript language 'interrupt' error in the context.
     
     DPSInterruptContext returns immediately after sending the request.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc. */

extern void DPSDestroyContext(DPSContext ctxt);

  /* This calls DPSUnchainContext, then (for an interpreter context) sends a
     request to the interpreter to terminate ctxt, then frees the storage
     referenced by ctxt. The termination request is ignored by the
     server if the context is invalid, for example if it has already
     terminated. */
  
extern void DPSDestroySpace(DPSSpace spc);

  /* Calls DPSDestroyContext for each of the contexts in the space, then
     sends a request to the server to terminate the space, then frees the
     storage referenced by spc. */

extern void DPSSetNumStringConversion(DPSContext ctxt, int flag);

  /* Sets the numstring conversion flag, which tells the client library
     to convert numstrings to simple arrays */

extern void DPSSetWrapSynchronization(DPSContext ctxt, int flag);

  /* Sets the wrap synchronization flag, which makes all wraps synchronize
     with the server */

extern void DPSSuppressBinaryConversion(DPSContext ctxt, int flag);

  /* Sets the no binary convert flag, which makes the client library not
     convert binary object sequences and binary tokens into ASCII */

extern void DPSSetAbbrevMode(DPSContext ctxt, int flag);

  /* Sets the abbrev mode flag, which controls whether the client library
     uses abbreviated operator names when converting from binary to ascii */

extern void DPSFetchAbbrevList(DPSAbbrevRec **list, int *count);

  /* Returns the list of abbreviations used for binary to ascii conversion.
     The returned list is sorted both by systemNameIndex and by operatorName.
   */

extern char *DPSGetSysnameAbbrev(int n);

  /* Returns the abbreviation for the operator with system name n, or
     NULL if there is no such abbreviation */

extern char *DPSGetOperatorAbbrev(char *op);

  /* Returns the abbreviation for the operator, or NULL if there is no
     such abbreviation */

extern DPSContextType DPSGetContextType(DPSContext ctxt);

  /* Returns whether a context is a text context or an execution context */

  /* generated functions used in dpstk */
extern void DPSrectfill(DPSContext ctxt, double x, double y, double w, double h);
extern void DPSsetcmykcolor(DPSContext ctxt, double c, double m, double y, double k);
extern void DPSsetgray(DPSContext ctxt, double gray);
extern void DPSsethsbcolor(DPSContext ctxt, double h, double s, double b);
extern void DPSsetrgbcolor(DPSContext ctxt, double r, double g, double b);
extern void DPSsetXoffset(DPSContext ctxt, int x, int y);
extern void DPSinitviewclip(DPSContext ctxt);
extern void DPSinitgraphics(DPSContext ctxt);
extern void DPSscale(DPSContext ctxt, double x, double y);
extern void DPSinitclip(DPSContext ctxt);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define DPSSetTextProc(ctxt, tp) ((ctxt)->textProc = (tp))

  /* Change ctxt's textProc. */
  
#define DPSSetErrorProc(ctxt, ep) ((ctxt)->errorProc = (ep))

  /* Change ctxt's errorProc. */
  
#define DPSSpaceFromContext(ctxt) ((ctxt)->space)

  /* Extract space handle from context. */

#endif /* DPSCLIENT_H */
