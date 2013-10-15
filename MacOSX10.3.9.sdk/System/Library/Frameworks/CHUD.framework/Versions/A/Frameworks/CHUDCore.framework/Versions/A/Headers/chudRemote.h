/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
  @header CHUD Remote Functions
  Use the CHUD Remote Functions to setup inter-process communication using mach messages
  between a performance monitor application (like MONster or Shark) and an application to 
  be profiled. The application to be profiled should add "chudRemote*" calls around critical
  sections that are to be measured. Check out the CHUD Example Code: "TowersOfHanoi" for a code sample illustrating how to instrument code for remote performance monitoring. A typical program needs ony to call the functions marked "[client routine]."
*/

#ifndef CHUD_REMOTE_H
#define CHUD_REMOTE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    REMOTE_STATUS_NO_SERVER			= 0,		// no server running
    REMOTE_STATUS_SERVER_BUSY			= 1,		// server not yet ready, no client request
    REMOTE_STATUS_CLIENT_REQUEST		= 2,		// remote client requesting start
    REMOTE_STATUS_SERVER_READY			= 3,		// server ready, waiting for remote client
    REMOTE_STATUS_CLIENT_ACTIVE			= 4		// remote client has started sampling
} chud_remote_client_status_t;

/* remote perf monitor "server" */
 /*!
 @function chudRegisterAsRemotePerfMonitor
 @discussion [server routine] set up a performance monitor program as an external PMC controller
 announce the profiler is ready to receive a start or stop command
 @param void
 @result chudSuccess
 */
int	chudRegisterAsRemotePerfMonitor( void );
 /*!
 @function chudCancelRemotePerfMonitor
 @discussion [server routine] shut down a performance monitor program as an external PMC controller
 announce the profiler is no longer recieving start or stop commands
 @param void
 @result chudSuccess
 */
int	chudCancelRemotePerfMonitor( void );
 /*!
 @function chudRemotePerfMonitorReady
 @discussion [server routine] alert the server side of the remote facility as to whether the 
 external Perf monitor is ready for another sample or not
 @param ready pass in a 1 or a 0 or TRUE FALSE
 @result chudSuccess
 */
void 	chudRemotePerfMonitorReady( int ready );
 /*!
 @function chudGetRemoteRunLabel
 @discussion [server routine] returns the current remote run label assigned in the chudStartRemotePerfMonitor function.
 @param void
 @result the current run label
 */
char *	chudGetRemoteRunLabel(void); 


/* remote perf monitor "client" */
 /*!
 @function chudAcquireRemoteAccess
 @discussion [client routine] client programs connect to the remote access facility provided by an 
 external performance monitor program. This routine must
 be called before calling chudStart/StopExternalPerfMoniitor
 @param void
 @result chudSuccess, or chudIOKitFailure
 */
int 	chudAcquireRemoteAccess( void );
 /*!
 @function chudReleaseRemoteAccess
 @discussion [client routine] client programs disconnect from an external performance monitor facility
 usually so that another remote client can use it
 @param void
 @result chudSuccess, or chudReleaseExternalFacilityFailure
 */
int 	chudReleaseRemoteAccess( void );
 /*!
 @function chudStartRemotePerfMonitor
 @discussion [client routine] called by remote client to start a CHUD-based remote profiler collecting samples
 pass in a descriptive label that will be used in the index column of MONster, or as part of a
 description in other performance profiling apps.
 @param char *label
 @result chudStatus:  chudSuccess
 */
int 	chudStartRemotePerfMonitor( char *label );
 /*!
 @function chudStopRemotePerfMonitor
 @discussion [client routine] Signal to stop a CHUD-based remote profiler from collecting samples.
 @param void
 @result chudStatus:  chudSuccess
 */
int 	chudStopRemotePerfMonitor( void );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /*!
 @function chudRemoteProfilingCallback
 @discussion [server routine] if a remote stop profiling message is detected, this function is called in the 
 server application to respond to the signal,  The two values representing input to the
 server-function:  the values are designed to make this calling function
 compatible with both ansi-C and objective-C
 @param uicf (chudCallback *) the server-function
 @param ha1 unsigned long
 @param ha2 unsigned long 
 @result void
 */
void 	chudRemoteProfilingCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 );
 /*!
 @function chudRemoteProfilingStatusCallback
 @discussion [server routine] calls back to the remote server whenever the status changes (e.g. remote client starts sampling)
 @param uicf (chudCallbackFuncData *) the server-function
 @param ha1 unsigned long
 @param ha2 unsigned long 
 @result void
 */
void	chudRemoteProfilingStatusCallback(chudCallbackFuncData uicf, unsigned long ha1, unsigned long ha2);

#ifdef __cplusplus
}
#endif

#endif /* CHUD_REMOTE_H */