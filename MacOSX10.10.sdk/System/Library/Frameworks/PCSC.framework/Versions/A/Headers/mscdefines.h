/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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

/******************************************************************

        MUSCLE SmartCard Development ( http://www.linuxnet.com )
            Title  : mscdefines.h
            Package: MuscleCard Framework
            Author : David Corcoran
            Date   : 10/02/01
            License: Copyright (C) 2001-2002 David Corcoran
                     <corcoran@linuxnet.com>
            Purpose: This provides high level definitions for
                     data types, structures.

	    You may not remove this header from this file
	    without prior permission from the author.
   
********************************************************************/

#ifndef __mscdefines_h__
#define __mscdefines_h__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef WIN32
#include "../win32/win32_pcsclite.h"
#else
#include "pcsclite.h"
#endif

#ifndef __APPLE__
#include <winscard.h>
#else
#include <PCSC/winscard.h>
#endif

#include <stdint.h>

#ifdef MSC_ARCH_WIN32
#define MAX_BUFFER_SIZE		265
#endif

	/*
	 * Some type defines used in MuscleCard 
	 */

	typedef uint32_t MSC_RV;
	typedef char MSCChar8;
	typedef uint8_t *MSCPUChar8;
	typedef const uint8_t *MSCPCUChar8;
	typedef uint8_t MSCUChar8;
	typedef uint16_t *MSCPUShort16;
	typedef uint16_t MSCUShort16;
	typedef int16_t *MSCPShort16;
	typedef int16_t MSCShort16;
	typedef uint32_t *MSCPULong32;
	typedef uint32_t MSCULong32;
	typedef int32_t *MSCPLong32;
	typedef int32_t MSCLong32;
	typedef const void *MSCPCVoid32;
	typedef void *MSCPVoid32;
	typedef const char *MSCCString;
	typedef char *MSCString;

	typedef struct
	{
		MSCPVoid32 pvfWriteFramework;
		MSCPVoid32 pvfInitializePlugin;
		MSCPVoid32 pvfIdentifyToken;
		MSCPVoid32 pvfFinalizePlugin;
		MSCPVoid32 pvfGetStatus;
		MSCPVoid32 pvfGetCapabilities;
		MSCPVoid32 pvfExtendedFeature;
		MSCPVoid32 pvfGenerateKeys;
		MSCPVoid32 pvfImportKey;
		MSCPVoid32 pvfExportKey;
		MSCPVoid32 pvfComputeCrypt;
		MSCPVoid32 pvfExtAuthenticate;
		MSCPVoid32 pvfListKeys;
		MSCPVoid32 pvfCreatePIN;
		MSCPVoid32 pvfVerifyPIN;
		MSCPVoid32 pvfChangePIN;
		MSCPVoid32 pvfUnblockPIN;
		MSCPVoid32 pvfListPINs;
		MSCPVoid32 pvfCreateObject;
		MSCPVoid32 pvfDeleteObject;
		MSCPVoid32 pvfWriteObject;
		MSCPVoid32 pvfReadObject;
		MSCPVoid32 pvfListObjects;
		MSCPVoid32 pvfLogoutAll;
		MSCPVoid32 pvfGetChallenge;

	}
	CFDyLibPointers, *LPCFDyLibPointers;

#define MSC_MAXSIZE_TOKENAME      150
#define MSC_MAXSIZE_SVCPROV       200
#define MSC_MAXSIZE_OBJID          16
#define MSC_MAXSIZE_AID            64
#define MSC_MAXSIZE_MAC           128
#define MSC_MAXSIZE_LABEL          32
#define MSC_MAXSIZE_CERT_ISSUER    512
#define MSC_MAXSIZE_CERT_SUBJECT   512
#define MSC_MAXSIZE_CERT_SERIAL    512
#define MSC_MAXSIZE_BUFFER     MAX_BUFFER_SIZE

	typedef struct
	{
	        MSCChar8 tokenName[MSC_MAXSIZE_TOKENAME]; /* Token name */ 
                MSCChar8 slotName[MAX_READERNAME];	/* Slot/reader name */
		MSCChar8 svProvider[MSC_MAXSIZE_SVCPROV]; /* Library */
		MSCUChar8 tokenId[MAX_ATR_SIZE];     /* Token ID (ATR) */
		MSCUChar8 tokenApp[MSC_MAXSIZE_AID]; /* Default app ID */
		MSCULong32 tokenAppLen;	  /* Default AID Length */
		MSCULong32 tokenIdLength; /* ID Length (ATR Length) */
		MSCULong32 tokenState;	  /* State (dwEventState) */
		MSCULong32 tokenType;	  /* Type - RFU */
		MSCPVoid32 addParams;	  /* Additional Data */
		MSCULong32 addParamsSize; /* Size of additional data */
	}
	MSCTokenInfo, *MSCLPTokenInfo;

	/*
	 * Callback function definitions 
	 */

	typedef MSCULong32(*MSCCallBack) (MSCLPTokenInfo, MSCULong32,
					  MSCPVoid32);

	typedef struct
	{
		MSCULong32 arraySize;
		MSCLPTokenInfo tokenArray;
		MSCPVoid32 appData;
		MSCCallBack callBack;
	}
	MSCEventWaitInfo, *MSCLPEventWaitInfo;

	typedef MSC_RV(*LPRWEventCallback) (MSCPVoid32, int);

	typedef struct
	{
		MSCLong32 hContext;	      /* Handle to resource manager */
		MSCLong32 hCard;	      /* Handle to the connection */
		LPSCARD_IO_REQUEST ioType;    /* Type of protocol */
		MSCUChar8 pMac[MSC_MAXSIZE_MAC];  /* MAC code */
		MSCULong32 macSize;	      /* Size of the MAC code */
		MSCPVoid32 tokenLibHandle;    /* Handle to token library */
		CFDyLibPointers libPointers;  /* Function pointers */
		MSCTokenInfo tokenInfo;	/* token information */
		MSCUChar8 loggedIDs;	/* Verification bit mask */
		MSCULong32 shareMode;	/* Sharing mode for this */
		LPRWEventCallback rwCallback;	/* Registered callback */
	}
	MSCTokenConnection, *MSCLPTokenConnection;

#define MSC_OK MSC_SUCCESS

#ifdef __cplusplus
}
#endif

#endif							/* __mscdefines_h__ */
