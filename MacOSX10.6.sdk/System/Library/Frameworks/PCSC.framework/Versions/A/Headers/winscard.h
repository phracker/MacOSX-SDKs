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

/*
 * MUSCLE SmartCard Development ( http://www.linuxnet.com )
 *
 * Copyright (C) 1999-2003
 *  David Corcoran <corcoran@linuxnet.com>
 *  Ludovic Rousseau <ludovic.rousseau@free.fr>
 *
 * $Id: winscard.h 2072 2006-06-06 09:31:07Z rousseau $
 */

/**
 * @file
 * @brief This handles smartcard reader communications.
 */

#ifndef __winscard_h__
#define __winscard_h__

#include <PCSC/pcsclite.h>
#include <stdint.h>
//#include "pcscexport.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PCSC_API
#define PCSC_API
#endif

	PCSC_API int32_t SCardEstablishContext(uint32_t dwScope,
		const void *pvReserved1, const void *pvReserved2, LPSCARDCONTEXT phContext);

	PCSC_API int32_t SCardReleaseContext(SCARDCONTEXT hContext);

	PCSC_API int32_t SCardIsValidContext(SCARDCONTEXT hContext);
	
	PCSC_API int32_t SCardSetTimeout(SCARDCONTEXT hContext, uint32_t dwTimeout);

	PCSC_API int32_t SCardConnect(SCARDCONTEXT hContext,
		const char *szReader,
		uint32_t dwShareMode,
		uint32_t dwPreferredProtocols,
		LPSCARDHANDLE phCard, uint32_t *pdwActiveProtocol);

	PCSC_API int32_t SCardReconnect(SCARDHANDLE hCard,
		uint32_t dwShareMode,
		uint32_t dwPreferredProtocols,
		uint32_t dwInitialization, uint32_t *pdwActiveProtocol);

	PCSC_API int32_t SCardDisconnect(SCARDHANDLE hCard, uint32_t dwDisposition);

	PCSC_API int32_t SCardBeginTransaction(SCARDHANDLE hCard);

	PCSC_API int32_t SCardEndTransaction(SCARDHANDLE hCard, uint32_t dwDisposition);

	PCSC_API int32_t SCardCancelTransaction(SCARDHANDLE hCard);

	PCSC_API int32_t SCardStatus(SCARDHANDLE hCard,
		char *mszReaderNames, uint32_t *pcchReaderLen,
		uint32_t *pdwState,
		uint32_t *pdwProtocol,
		unsigned char *pbAtr, uint32_t *pcbAtrLen);

	PCSC_API int32_t SCardGetStatusChange(SCARDCONTEXT hContext,
		uint32_t dwTimeout,
		LPSCARD_READERSTATE_A rgReaderStates, uint32_t cReaders);

	PCSC_API int32_t SCardControl(SCARDHANDLE hCard,
		const void *pbSendBuffer, uint32_t cbSendLength,
		void *pbRecvBuffer, uint32_t *pcbRecvLength);

	PCSC_API int32_t SCardControl132(SCARDHANDLE hCard, uint32_t dwControlCode,
		const void *pbSendBuffer, uint32_t cbSendLength,
		void *pbRecvBuffer, uint32_t cbRecvLength, uint32_t *lpBytesReturned);

	PCSC_API int32_t SCardTransmit(SCARDHANDLE hCard,
		LPCSCARD_IO_REQUEST pioSendPci,
		const unsigned char *pbSendBuffer, uint32_t cbSendLength,
		LPSCARD_IO_REQUEST pioRecvPci,
		unsigned char *pbRecvBuffer, uint32_t *pcbRecvLength);

	PCSC_API int32_t SCardListReaderGroups(SCARDCONTEXT hContext,
		char *mszGroups, uint32_t *pcchGroups);

	PCSC_API int32_t SCardListReaders(SCARDCONTEXT hContext,
		const char *mszGroups,
		char *mszReaders, uint32_t *pcchReaders);

	PCSC_API int32_t SCardCancel(SCARDCONTEXT hContext);

	PCSC_API int32_t SCardGetAttrib(SCARDHANDLE hCard, uint32_t dwAttrId,
		uint8_t *pbAttr, uint32_t *pcbAttrLen);

	PCSC_API int32_t SCardSetAttrib(SCARDHANDLE hCard, uint32_t dwAttrId,
		const uint8_t *pbAttr, uint32_t cbAttrLen);

	void SCardUnload(void);

#ifdef __cplusplus
}
#endif

/*
	To support the newer version of SCardControl, we define it
	as follows. The old version number was 1.1.2, the new call
	appears in 1.3.2 of pcsc-lite (or perhaps earlier).
*/

#if !defined(USE_SCARD_CONTROL_112)
#define SCardControl SCardControl132
#endif /* USE_SCARD_CONTROL_112 */

#endif

