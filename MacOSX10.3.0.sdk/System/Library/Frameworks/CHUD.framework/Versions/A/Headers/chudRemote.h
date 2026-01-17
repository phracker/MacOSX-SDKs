/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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
int	chudRegisterAsRemotePerfMonitor( void );
int	chudCancelRemotePerfMonitor( void );
void 	chudRemotePerfMonitorReady( int ready );
char *	chudGetRemoteRunLabel(void); 


/* remote perf monitor "client" */
int 	chudAcquireRemoteAccess( void );
int 	chudReleaseRemoteAccess( void );
int 	chudStartRemotePerfMonitor( char *label );
int 	chudStopRemotePerfMonitor( void );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void 	chudRemoteProfilingCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 );
void	chudRemoteProfilingStatusCallback(chudCallbackFuncData uicf, unsigned long ha1, unsigned long ha2);

#ifdef __cplusplus
}
#endif

#endif /* CHUD_REMOTE_H */