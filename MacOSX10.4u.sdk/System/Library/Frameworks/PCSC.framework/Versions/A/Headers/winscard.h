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
	    Title  : winscard.h
	    Package: pcsc lite
            Author : David Corcoran
            Date   : 7/27/99
 	    License: Copyright (C) 1999 David Corcoran
	             <corcoran@linuxnet.com>
            Purpose: This handles smartcard reader communications. 
	            

********************************************************************/

#ifndef __winscard_h__
#define __winscard_h__

#ifndef __APPLE__
#include <pcsclite.h>
#else
#include <PCSC/pcsclite.h>
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	int32_t SCardEstablishContext(uint32_t dwScope,
		const void *pvReserved1, const void *pvReserved2, LPSCARDCONTEXT phContext);

	int32_t SCardReleaseContext(int32_t hContext);

	int32_t SCardSetTimeout(int32_t hContext, uint32_t dwTimeout);

	int32_t SCardConnect(int32_t hContext,
		const char *szReader,
		uint32_t dwShareMode,
		uint32_t dwPreferredProtocols,
		int32_t *phCard, uint32_t *pdwActiveProtocol);

	int32_t SCardReconnect(int32_t hCard,
		uint32_t dwShareMode,
		uint32_t dwPreferredProtocols,
		uint32_t dwInitialization, uint32_t *pdwActiveProtocol);

	int32_t SCardDisconnect(int32_t hCard, uint32_t dwDisposition);

	int32_t SCardBeginTransaction(int32_t hCard);

	int32_t SCardEndTransaction(int32_t hCard, uint32_t dwDisposition);

	int32_t SCardCancelTransaction(int32_t hCard);

	int32_t SCardStatus(int32_t hCard,
		char *mszReaderNames,
		uint32_t *pcchReaderLen,
		uint32_t *pdwState,
		uint32_t *pdwProtocol,
		unsigned char *pbAtr, uint32_t *pcbAtrLen);

	int32_t SCardGetStatusChange(int32_t hContext,
		uint32_t dwTimeout,
		LPSCARD_READERSTATE_A rgReaderStates, uint32_t cReaders);

	int32_t SCardControl(int32_t hCard,
		const unsigned char *pbSendBuffer,
		uint32_t cbSendLength,
		unsigned char *pbRecvBuffer, uint32_t *pcbRecvLength);

	int32_t SCardTransmit(int32_t hCard,
		LPCSCARD_IO_REQUEST pioSendPci,
		const unsigned char *pbSendBuffer,
		uint32_t cbSendLength,
		LPSCARD_IO_REQUEST pioRecvPci,
		unsigned char *pbRecvBuffer, uint32_t *pcbRecvLength);

	int32_t SCardListReaderGroups(int32_t hContext,
		char *mszGroups, uint32_t *pcchGroups);

	int32_t SCardListReaders(int32_t hContext,
		const char *mszGroups,
		char *mszReaders, uint32_t *pcchReaders);

	int32_t SCardCancel(int32_t hContext);

#ifdef __cplusplus
}
#endif

#endif
