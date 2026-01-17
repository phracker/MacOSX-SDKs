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
	    Title  : winscard_msg.h
	    Package: pcsc lite
            Author : David Corcoran
            Date   : 03/30/01
	    License: Copyright (C) 2001 David Corcoran
	             <corcoran@linuxnet.com>
            Purpose: This defines some structures and defines to
	             be used over the transport layer.

********************************************************************/

#ifndef __winscard_msg_h__
#define __winscard_msg_h__

#ifdef __cplusplus
extern "C" {
#endif
  
typedef struct rxSharedSegment {
  unsigned int   mtype;
  unsigned int   user_id;
  unsigned int   group_id;
  unsigned int   command;
  unsigned int   request_id;
  time_t         date;
  unsigned char  data[PCSCLITE_MAX_MESSAGE_SIZE];
} sharedSegmentMsg, *psharedSegmentMsg;


  enum pcsc_msg_commands {
    
    CMD_FAILED		            = -1,
    CMD_SERVER_DIED                 = -2,
    CMD_CLIENT_DIED                 = -3,
    CMD_READER_EVENT                = -4,
    
    SCARD_ESTABLISH_CONTEXT	    = 0x01,
    SCARD_RELEASE_CONTEXT	    = 0x02,
    SCARD_LIST_READERS		    = 0x03,
    SCARD_CONNECT                   = 0x04,
    SCARD_RECONNECT                 = 0x05,
    SCARD_DISCONNECT                = 0x06,
    SCARD_BEGIN_TRANSACTION         = 0x07,
    SCARD_END_TRANSACTION           = 0x08,
    SCARD_TRANSMIT                  = 0x09,
    SCARD_CONTROL                   = 0x0A,
    SCARD_STATUS                    = 0x0B,
    SCARD_GET_STATUS_CHANGE         = 0x0C,
    SCARD_CANCEL                    = 0x0D,
    SCARD_CANCEL_TRANSACTION        = 0x0E
    
  };
  
  struct client_struct {
    SCARDCONTEXT hContext;
  };
  typedef struct client_struct client_struct;
  
  struct establish_struct {
    DWORD dwScope;
    SCARDCONTEXT phContext;
    LONG rv;
  };
  typedef struct establish_struct establish_struct;
  
  struct release_struct {
    SCARDCONTEXT hContext;
    LONG rv;
  };
  typedef struct release_struct release_struct;
  
  struct connect_struct {
    SCARDCONTEXT hContext;
    char szReader[MAX_READERNAME];
    DWORD dwShareMode;
    DWORD dwPreferredProtocols;
    SCARDHANDLE phCard;
    DWORD pdwActiveProtocol;
    LONG rv;
  };
  typedef struct connect_struct connect_struct;
  
  struct reconnect_struct {
    SCARDHANDLE hCard;
    DWORD dwShareMode;
    DWORD dwPreferredProtocols;
    DWORD dwInitialization;
    DWORD pdwActiveProtocol;
    LONG rv;
  };
  typedef struct reconnect_struct reconnect_struct;
  
  struct disconnect_struct {
    SCARDHANDLE hCard;
    DWORD dwDisposition;
    LONG rv;
  };
  typedef struct disconnect_struct disconnect_struct;
  
  struct begin_struct {
    SCARDHANDLE hCard;
    LONG rv;
  };
  typedef struct begin_struct begin_struct;
  
  struct end_struct {
    SCARDHANDLE hCard;
    DWORD dwDisposition;
    LONG rv;
  };
  typedef struct end_struct end_struct;
  
  struct cancel_struct {
    SCARDHANDLE hCard;
    LONG rv;
  };
  typedef struct cancel_struct cancel_struct;
  
  
  struct transmit_struct {
    SCARDHANDLE hCard;
    SCARD_IO_REQUEST pioSendPci;
    UCHAR pbSendBuffer[MAX_BUFFER_SIZE];
    DWORD cbSendLength;
    SCARD_IO_REQUEST pioRecvPci;
    BYTE pbRecvBuffer[MAX_BUFFER_SIZE];
    DWORD pcbRecvLength;
    LONG rv;
  };
  typedef struct transmit_struct transmit_struct;

  /* Now some function definitions */

  int SHMInitializeSharedSegment();
  int SHMClientSetupLocks();
  int SHMClientLock();
  int SHMClientUnlock();
  int SHMClientWrite( psharedSegmentMsg, int );
  int SHMClientRead( psharedSegmentMsg, int );
  int SHMServerWrite( psharedSegmentMsg, int );
  int SHMServerRead( psharedSegmentMsg, int );
  int SHMMessageToRX( psharedSegmentMsg, int );
  int SHMMessageFromRX( psharedSegmentMsg, int );
  int SHMMessageToTX( psharedSegmentMsg, int );
  int SHMMessageFromTX( psharedSegmentMsg, int );
  int WrapSHMWrite( unsigned int, unsigned int, unsigned int, 
                    unsigned int, void *);

#ifdef __cplusplus
}
#endif         

#endif
