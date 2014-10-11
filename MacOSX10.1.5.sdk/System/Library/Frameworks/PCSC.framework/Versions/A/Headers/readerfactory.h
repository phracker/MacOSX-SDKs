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
	    Title  : readerfactory.h
	    Package: pcsc lite
            Author : David Corcoran
            Date   : 7/27/99
	    License: Copyright (C) 1999 David Corcoran
	             <corcoran@linuxnet.com>
            Purpose: This keeps track of a list of currently 
	             available reader structures.

********************************************************************/

#ifndef __readerfactory_h__
#define __readerfactory_h__

#include <thread_generic.h>

#ifdef __cplusplus
extern "C" {
#endif  

  struct FctMap {
    LPVOID pvfCreateChannel;
    LPVOID pvfCloseChannel;
    LPVOID pvfGetCapabilities;
    LPVOID pvfSetCapabilities;
    LPVOID pvfSetProtocol;
    LPVOID pvfPowerICC;
    LPVOID pvfSwallowICC;        /* Deprecated in 2.0 */
    LPVOID pvfEjectICC;          /* Deprecated in 2.0 */
    LPVOID pvfConfiscateICC;     /* Deprecated in 2.0 */
    LPVOID pvfTransmitICC;
    LPVOID pvfICCPresent;
    LPVOID pvfICCAbsent;         /* Deprecated in 2.0 */
    LPVOID pvfControl;           /* MUSCLE IFD 2.0 Compliance */
  };

  typedef struct FctMap FCT_MAP, *PFCT_MAP;

  /* The following is not currently used but in place if needed */

  struct RdrCapabilities {
    DWORD dwAsynch_Supported;       /* Asynchronous Support */
    DWORD dwDefault_Clock;          /* Default Clock Rate   */
    DWORD dwMax_Clock;              /* Max Clock Rate       */
    DWORD dwDefault_Data_Rate;      /* Default Data Rate    */
    DWORD dwMax_Data_Rate;          /* Max Data Rate        */
    DWORD dwMax_IFSD;               /* Maximum IFSD Size    */
    DWORD dwSynch_Supported;        /* Synchronous Support  */
    DWORD dwPower_Mgmt;             /* Power Mgmt Features  */
    DWORD dwCard_Auth_Devices;      /* Card Auth Devices    */
    DWORD dwUser_Auth_Device;       /* User Auth Devices    */
    DWORD dwMechanics_Supported;    /* Machanics Supported  */
    DWORD dwVendor_Features;        /* User Defined.        */
  };

  typedef struct RdrCapabilities RDR_CAPABILITIES, *PRDR_CAPABILITIES;

  struct ProtOptions {
    DWORD dwProtocol_Type;          /* Protocol Type        */
    DWORD dwCurrent_Clock;          /* Current Clock        */
    DWORD dwCurrent_F;              /* Current F            */
    DWORD dwCurrent_D;              /* Current D            */
    DWORD dwCurrent_N;              /* Current N            */
    DWORD dwCurrent_W;              /* Current W            */
    DWORD dwCurrent_IFSC;           /* Current IFSC         */
    DWORD dwCurrent_IFSD;           /* Current IFSD         */
    DWORD dwCurrent_BWT;            /* Current BWT          */
    DWORD dwCurrent_CWT;            /* Current CWT          */
    DWORD dwCurrent_EBC;            /* Current EBC          */
  };

  typedef struct ProtOptions PROT_OPTIONS, *PPROT_OPTIONS;

  struct RdrCliHandles {
    SCARDHANDLE hCard;                 /* hCard for this connection        */
    DWORD dwEventStatus;               /* Recent event that must be sent   */
  };
  
  typedef struct RdrCliHandles RDR_CLIHANDLES, *PRDR_CLIHANDLES;

  struct ReaderContext {
    char  lpcReader[MAX_READERNAME];   /* Reader Name                      */
    char  lpcLibrary[MAX_LIBNAME];     /* Library Path                     */
    PCSCLITE_THREAD_T pthThread;       /* Event polling thread             */
    PCSCLITE_MUTEX_T mMutex;           /* Mutex for this connection        */
    RDR_CAPABILITIES psCapabilites;    /* Structure of reader capabilities */
    PROT_OPTIONS psProtOptions;        /* Structure of protocol options    */
    RDR_CLIHANDLES psHandles[16];      /* Structure of connected handles   */
    FCT_MAP psFunctions;               /* Structure of function pointers   */
    UCHAR ucAtr[MAX_ATR_SIZE];         /* Atr for inserted card            */
    DWORD dwAtrLen;                    /* Size of the ATR                  */
    LPVOID vHandle;                    /* Dlopen handle                    */
    DWORD dwVersion;                   /* IFD Handler version number       */
    DWORD dwPort;                      /* Port ID                          */
    DWORD dwProtocol;                  /* Currently used protocol          */
    DWORD dwSlot;                      /* Current Reader Slot              */
    DWORD dwBlockStatus;               /* Current blocking status          */
    DWORD dwStatus;                    /* Current Status Mask              */
    DWORD dwLockId;                    /* Lock Id                          */
    DWORD dwIdentity;                  /* Shared ID High Nibble            */
    DWORD dwContexts;                  /* Number of open contexts          */
    DWORD dwPublicID;                  /* Public id of public state struct */
    PDWORD dwFeeds;                    /* Number of shared client to lib   */
  };

  typedef struct ReaderContext READER_CONTEXT, *PREADER_CONTEXT;

  LONG RVAllocateReaderSpace( DWORD );
  LONG RFAddReader( LPSTR, DWORD, LPSTR );
  LONG RFRemoveReader( LPSTR, DWORD );
  LONG RFSetReaderName( PREADER_CONTEXT, LPSTR, LPSTR, DWORD, DWORD );
  LONG RFListReaders( LPSTR, LPDWORD );
  LONG RFReaderInfo( LPSTR, struct ReaderContext** );
  LONG RFReaderInfoNamePort( DWORD, LPSTR, struct ReaderContext** );
  LONG RFReaderInfoById( DWORD, struct ReaderContext** );
  LONG RFCheckSharing( DWORD );
  LONG RFLockSharing( DWORD );
  LONG RFUnlockSharing( DWORD );
  LONG RFUnblockReader( PREADER_CONTEXT );
  LONG RFUnblockContext( SCARDCONTEXT );
  LONG RFLoadReader( PREADER_CONTEXT );
  LONG RFBindFunctions( PREADER_CONTEXT );
  LONG RFUnBindFunctions( PREADER_CONTEXT );
  LONG RFUnloadReader( PREADER_CONTEXT );
  LONG RFInitializeReader( PREADER_CONTEXT );
  LONG RFUnInitializeReader( PREADER_CONTEXT );
  SCARDHANDLE RFCreateReaderHandle( PREADER_CONTEXT );
  LONG RFDestroyReaderHandle( SCARDHANDLE hCard );
  LONG RFAddReaderHandle( PREADER_CONTEXT, SCARDHANDLE );
  LONG RFFindReaderHandle( SCARDHANDLE );
  LONG RFRemoveReaderHandle( PREADER_CONTEXT, SCARDHANDLE );
  LONG RFSetReaderEventState( PREADER_CONTEXT, DWORD );
  LONG RFCheckReaderEventState( PREADER_CONTEXT, SCARDHANDLE );
  LONG RFClearReaderEventState( PREADER_CONTEXT, SCARDHANDLE );

#ifdef __cplusplus
}
#endif 
  
#endif
