/*
 * Copyright (c) 2000-2001 Apple Computer, Inc. All Rights Reserved.
 * 
 * The contents of this file constitute Original Code as defined in and are
 * subject to the Apple Public Source License Version 1.2 (the 'License').
 * You may not use this file except in compliance with the License. Please obtain
 * a copy of the License at http://www.apple.com/publicsource and read it before
 * using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see the License for the
 * specific language governing rights and limitations under the License.
 */


/******************************************************************

	MUSCLE SmartCard Development ( http://www.linuxnet.com )
	    Title  : debuglog.h
	    Package: pcsc lite
            Author : David Corcoran
            Date   : 7/27/99
	    License: Copyright (C) 1999 David Corcoran
	             <corcoran@linuxnet.com>
            Purpose: This handles debugging. 

********************************************************************/

#ifndef __debuglog_h__
#define __debuglog_h__

#ifdef __cplusplus
extern "C" {
#endif     

#define DEBUGLOG_LOG_ENTRIES    1
#define DEBUGLOG_IGNORE_ENTRIES 2

void DebugLogA( LPCSTR, LPCSTR, LONG );

void DebugLogB( LPCSTR, LONG, LPCSTR, LONG );

void DebugLogC( LPCSTR, LPCSTR, LPCSTR, LONG );

void DebugLogD( LPCSTR, PUCHAR, LONG, LPCSTR, LONG );

void DebugLogSuppress( LONG );

LPSTR pcsc_stringify_error ( LONG );

#ifdef __cplusplus
}
#endif     

#endif /* __debuglog_h__ */
