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
	Title  : pcsclite.h
	Package: pcsc lite
	Author : David Corcoran
	Date   : 7/27/99
	License: Copyright (C) 1999 David Corcoran
			<corcoran@linuxnet.com>
	Purpose: This keeps a list of defines for pcsc lite.            

********************************************************************/

#ifndef __pcsclite_h__
#define __pcsclite_h__

#include <stdint.h>

#ifndef __APPLE__
#include <wintypes.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef int32_t SCARDCONTEXT;
	typedef SCARDCONTEXT *PSCARDCONTEXT;
	typedef SCARDCONTEXT *LPSCARDCONTEXT;
	typedef int32_t SCARDHANDLE;
	typedef SCARDHANDLE *PSCARDHANDLE;
	typedef SCARDHANDLE *LPSCARDHANDLE;

	typedef struct
	{
		const char *szReader;
		void *pvUserData;
		uint32_t dwCurrentState;
		uint32_t dwEventState;
		uint32_t cbAtr;
		unsigned char rgbAtr[33];
	}
	SCARD_READERSTATE_A;

	typedef SCARD_READERSTATE_A SCARD_READERSTATE, *PSCARD_READERSTATE_A,
		*LPSCARD_READERSTATE_A;

	typedef struct _SCARD_IO_REQUEST
	{
		uint32_t dwProtocol;	/* Protocol identifier */
		uint32_t cbPciLength;	/* Protocol Control Inf Length */
	}
	SCARD_IO_REQUEST, *PSCARD_IO_REQUEST, *LPSCARD_IO_REQUEST;

	typedef const SCARD_IO_REQUEST *LPCSCARD_IO_REQUEST;

	extern SCARD_IO_REQUEST g_rgSCardT0Pci, g_rgSCardT1Pci,
		g_rgSCardRawPci;

#define SCARD_PCI_T0  (&g_rgSCardT0Pci)
#define SCARD_PCI_T1  (&g_rgSCardT1Pci)
#define SCARD_PCI_RAW (&g_rgSCardRawPci)

	/*
	 * Gets a stringified error response 
	 */
	char *pcsc_stringify_error(int32_t err);

#define SCARD_S_SUCCESS                 0x00000000
#define SCARD_E_CANCELLED               0x80100002
#define SCARD_E_CANT_DISPOSE            0x8010000E
#define SCARD_E_INSUFFICIENT_BUFFER     0x80100008
#define SCARD_E_INVALID_ATR             0x80100015
#define SCARD_E_INVALID_HANDLE          0x80100003
#define SCARD_E_INVALID_PARAMETER       0x80100004
#define SCARD_E_INVALID_TARGET          0x80100005
#define SCARD_E_INVALID_VALUE           0x80100011
#define SCARD_E_NO_MEMORY               0x80100006
#define SCARD_F_COMM_ERROR              0x80100013
#define SCARD_F_INTERNAL_ERROR          0x80100001
#define SCARD_F_UNKNOWN_ERROR           0x80100014
#define SCARD_F_WAITED_TOO_LONG         0x80100007
#define SCARD_E_UNKNOWN_READER          0x80100009
#define SCARD_E_TIMEOUT                 0x8010000A
#define SCARD_E_SHARING_VIOLATION       0x8010000B
#define SCARD_E_NO_SMARTCARD            0x8010000C
#define SCARD_E_UNKNOWN_CARD            0x8010000D
#define SCARD_E_PROTO_MISMATCH          0x8010000F
#define SCARD_E_NOT_READY               0x80100010
#define SCARD_E_SYSTEM_CANCELLED        0x80100012
#define SCARD_E_NOT_TRANSACTED          0x80100016
#define SCARD_E_READER_UNAVAILABLE      0x80100017

#define SCARD_W_UNSUPPORTED_CARD        0x80100065
#define SCARD_W_UNRESPONSIVE_CARD       0x80100066
#define SCARD_W_UNPOWERED_CARD          0x80100067
#define SCARD_W_RESET_CARD              0x80100068
#define SCARD_W_REMOVED_CARD            0x80100069
#define SCARD_W_INSERTED_CARD           0x8010006A

#define SCARD_E_UNSUPPORTED_FEATURE     0x8010001F
#define SCARD_E_PCI_TOO_SMALL           0x80100019
#define SCARD_E_READER_UNSUPPORTED      0x8010001A
#define SCARD_E_DUPLICATE_READER        0x8010001B
#define SCARD_E_CARD_UNSUPPORTED        0x8010001C
#define SCARD_E_NO_SERVICE              0x8010001D
#define SCARD_E_SERVICE_STOPPED         0x8010001E

#define SCARD_SCOPE_USER                0x0000	/* Scope in user space */
#define SCARD_SCOPE_TERMINAL            0x0001	/* Scope in terminal */
#define SCARD_SCOPE_SYSTEM              0x0002	/* Scope in system */
#define SCARD_SCOPE_GLOBAL              0x0003	/* Scope is global */

#define SCARD_PROTOCOL_T0               0x0001	/* T=0 active protocol. */
#define SCARD_PROTOCOL_T1               0x0002	/* T=1 active protocol. */
#define SCARD_PROTOCOL_RAW              0x0004	/* Raw active protocol. */
#define SCARD_PROTOCOL_ANY              0x1000	/* IFD determines prot. */

#define SCARD_SHARE_EXCLUSIVE           0x0001	/* Exclusive mode only */
#define SCARD_SHARE_SHARED              0x0002	/* Shared mode only */
#define SCARD_SHARE_DIRECT              0x0003	/* Raw mode only */

#define SCARD_LEAVE_CARD                0x0000	/* Do nothing on close */
#define SCARD_RESET_CARD                0x0001	/* Reset on close */
#define SCARD_UNPOWER_CARD              0x0002	/* Power down on close */
#define SCARD_EJECT_CARD                0x0003	/* Eject on close */

#define SCARD_UNKNOWN                   0x0001	/* Unknown state */
#define SCARD_ABSENT                    0x0002	/* Card is absent */
#define SCARD_PRESENT                   0x0004	/* Card is present */
#define SCARD_SWALLOWED                 0x0008	/* Card not powered */
#define SCARD_POWERED                   0x0010	/* Card is powered */
#define SCARD_NEGOTIABLE                0x0020	/* Ready for PTS */
#define SCARD_SPECIFIC                  0x0040	/* PTS has been set */

#define SCARD_STATE_UNAWARE		0x0000	/* App wants status */
#define SCARD_STATE_IGNORE              0x0001	/* Ignore this reader */
#define SCARD_STATE_CHANGED             0x0002	/* State has changed */
#define SCARD_STATE_UNKNOWN		0x0004	/* Reader unknown */
#define SCARD_STATE_UNAVAILABLE         0x0008	/* Status unavailable */
#define SCARD_STATE_EMPTY	        0x0010	/* Card removed */
#define SCARD_STATE_PRESENT		0x0020	/* Card inserted */
#define SCARD_STATE_ATRMATCH         	0x0040	/* ATR matches card */
#define SCARD_STATE_EXCLUSIVE      	0x0080	/* Exclusive Mode */
#define SCARD_STATE_INUSE               0x0100	/* Shared Mode */
#define SCARD_STATE_MUTE                0x0200	/* Unresponsive card */

#define SCARD_RESET                     0x0001	/* Card was reset */
#define SCARD_INSERTED                  0x0002	/* Card was inserted */
#define SCARD_REMOVED                   0x0004	/* Card was removed */

#define BLOCK_STATUS_RESUME             0x00FF	/* Normal resume */
#define BLOCK_STATUS_BLOCKING           0x00FA	/* Function is blocking */

#ifndef USE_READER_CONF
#define PCSCLITE_CONFIG_DIR		"/etc"
#else
#define PCSCLITE_CONFIG_DIR		USE_READER_CONF
#endif
#define PCSCLITE_READER_CONFIG		PCSCLITE_CONFIG_DIR "/reader.conf"
#define PCSCLITE_IPC_DIR		"/var/run/pcscd"
#define PCSCLITE_PUBSHM_FILE            PCSCLITE_IPC_DIR "/.pcscpub"
#define PCSCLITE_CSOCK_NAME             PCSCLITE_IPC_DIR "/.pcscomm"

#define PCSCLITE_SVC_IDENTITY	     0x01030000	/* Service ID */

#define INFINITE                     0xFFFFFFFF	/* Infinite timeout */
#define PCSCLITE_INFINITE_TIMEOUT    4320000	/* 50 day infinite t/o */

#define PCSCLITE_VERSION_NUMBER		"1.1.2"	/* Current version */
#define PCSCLITE_CLIENT_ATTEMPTS        120	/* Attempts to reach sv */
#define PCSCLITE_MCLIENT_ATTEMPTS       20	/* Attempts to reach sv */
#define PCSCLITE_STATUS_POLL_RATE       400000	/* Status polling rate */
#define PCSCLITE_MSG_KEY_LEN            16	/* App ID key length */
#define PCSCLITE_RW_ATTEMPTS            100	/* Attempts to rd/wrt */
#define PCSCLITE_MAX_CHANNELS           16	/* Maximum channels */
#define PCSCLITE_MAX_APPLICATIONS       16	/* Maximum applications */
#define PCSCLITE_MAX_CONTEXTS           16	/* Maximum readers */
#define PCSCLITE_MAX_THREADS            16	/* Stat change threads */
#define PCSCLITE_MAX_COMSIZE            64	/* Maximum arg size */
#define PCSCLITE_STATUS_WAIT		200000	/* Status Change Sleep */
#define PCSCLITE_TRANSACTION_TIMEOUT    40	/* Transaction timeout */
#define MAX_ATR_SIZE                    33	/* Maximum ATR size */
#define MAX_READERNAME			50	/* 50 char Reader Name */
#define MAX_LIBNAME			100	/* 100 char Lib Name */

#define SCARD_ATR_LENGTH           MAX_ATR_SIZE	/* Maximum ATR size */

/*
 * Enhanced messaging has been added to accomodate newer devices which have
 * more advanced capabilites, such as dedicated secure co-processors which
 * can stream and encrypt data over USB.  In order to used enhanced messaging
 * you must define PCSCLITE_ENHANCED_MESSAGING in the framework(library), 
 * the daemon, and your application
 */
#ifndef PCSCLITE_ENHANCED_MESSAGING
#define PCSCLITE_MAX_MESSAGE_SIZE        2048    /* Transport msg len */
#define MAX_BUFFER_SIZE                  264     /* Maximum Tx/Rx Buffer */
#define PCSCLITE_SERVER_ATTEMPTS         5       /* Attempts to reach cl */
#else
	/* Note: The message and buffer sizes must be multiples of 16 */
	/* Note2: The max message size must be at least large enough
	 * to accomodate the transmit_struct */
#define PCSCLITE_MAX_MESSAGE_SIZE       (1<<17)  /* enhanced (128K) msg len */
#define MAX_BUFFER_SIZE                 (1<<15)  /* enhanced (32K) Tx/Rx Buffer */
#define PCSCLITE_SERVER_ATTEMPTS         200     /* To allow larger data reads/writes */
#endif

#ifdef __cplusplus
}
#endif

#endif

