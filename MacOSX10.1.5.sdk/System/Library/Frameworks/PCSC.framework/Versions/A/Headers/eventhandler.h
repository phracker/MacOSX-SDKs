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

            Title  : eventhandler.h
            Package: PC/SC Lite
            Author : David Corcoran
            Date   : 10/06/99
	    License: Copyright (C) 1999 David Corcoran
	             <corcoran@linuxnet.com>
            Purpose: This handles card insertion/removal events, 
                     updates ATR, protocol, and status information.

********************************************************************/

#ifndef __eventhandler_h__
#define __eventhandler_h__

#ifdef __cplusplus
extern "C" {
#endif

  /* Define an exported public reader state
     structure so each application gets instant
     notification of changes in state.
  */

  typedef struct pubReaderStatesList {
    LONG  readerID;
    char  readerName[MAX_READERNAME];    
    DWORD readerState;
    LONG  readerSharing;
    DWORD lockState;
    
    UCHAR cardAtr[MAX_ATR_SIZE];
    DWORD cardAtrLength;
    DWORD cardProtocol;
  } READER_STATES, *PREADER_STATES;
  
  LONG EHInitializeEventStructures( );
  LONG EHSpawnEventHandler( PREADER_CONTEXT );
  LONG EHDestroyEventHandler( PREADER_CONTEXT );
  void EHSetSharingEvent( PREADER_CONTEXT, DWORD );
  
#ifdef __cplusplus
}
#endif

#endif /* __eventhandler_h__ */
