/*
     File:       OpenTransportProviders.r
 
     Contains:   This file contains provider-specific definitions for various built-in providers.
 
     Version:    OpenTransport-105~810
 
     Copyright:  © 1993-2006 by Apple Computer, Inc. and Mentat Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __OPENTRANSPORTPROVIDERS_R__
#define __OPENTRANSPORTPROVIDERS_R__

#ifndef __CONDITIONALMACROS_R__
#include <CarbonCore/ConditionalMacros.r>
#endif

/* Shared library prefixes*/

/* Module Names*/


#define kDNRName       "dnr"
#define kTCPName      "tcp"
#define kUDPName      "udp"
#define kRawIPName        "rawip"

/* XTI Options*/

/* Protocol levels*/

#define INET_IP 						0x00
#define INET_TCP 						0x06
#define INET_UDP 						0x11

/* TCP Level Options*/

#define TCP_NODELAY 					0x01
#define TCP_MAXSEG 						0x02
#define TCP_NOTIFY_THRESHOLD 			0x10				/* * not a real XTI option  */
#define TCP_ABORT_THRESHOLD 			0x11				/* * not a real XTI option  */
#define TCP_CONN_NOTIFY_THRESHOLD 		0x12				/* * not a real XTI option  */
#define TCP_CONN_ABORT_THRESHOLD 		0x13				/* * not a real XTI option  */
#define TCP_OOBINLINE 					0x14				/* * not a real XTI option  */
#define TCP_URGENT_PTR_TYPE 			0x15				/* * not a real XTI option  */
#define TCP_KEEPALIVE 					0x0008				/*  keepalive defined in OpenTransport.h  */

/*
   Mentat's code does an #ifdef on this symbol, so we have to #define
   it as well as declare it as an enum.  But only for Apple builds because
   we don't want internal weirdness to propagate to developers.
*/
#define T_GARBAGE 						2
/* UDP Level Options*/

#define UDP_CHECKSUM 					0x0600
#define UDP_RX_ICMP 					0x02

/*
   Mentat's code does an #ifdef on this symbol, so we have to #define
   it as well as declare it as an enum.  But only for Apple builds because
   we don't want internal weirdness to propagate to developers.
*/
/* IP Level Options*/
#define kIP_OPTIONS 					0x01
#define kIP_TOS 						0x02
#define kIP_TTL 						0x03
#define kIP_REUSEADDR 					0x04
#define kIP_DONTROUTE 					0x10
#define kIP_BROADCAST 					0x20
#define kIP_REUSEPORT 					0x0200
#define kIP_HDRINCL 					0x1002
#define kIP_RCVOPTS 					0x1005
#define kIP_RCVDSTADDR 					0x1007
#define kIP_MULTICAST_IF 				0x1010				/*  set/get IP multicast interface  */
#define kIP_MULTICAST_TTL 				0x1011				/*  set/get IP multicast timetolive     */
#define kIP_MULTICAST_LOOP 				0x1012				/*  set/get IP multicast loopback   */
#define kIP_ADD_MEMBERSHIP 				0x1013				/*  add an IP group membership      */
#define kIP_DROP_MEMBERSHIP 			0x1014				/*  drop an IP group membership        */
#define kIP_BROADCAST_IFNAME 			0x1015				/*  Set interface for broadcasts    */
#define kIP_RCVIFADDR 					0x1016				/*  Set interface for broadcasts    */

/*
   BSD's netinet/in.h uses different values for the same IP_ logical constants.
   If you are using OT and want those values, prefix your use with k
   e.g. change IP_TTL to kIP_TTL in your source code
*/
#define DVMRP_INIT 						100					/*  DVMRP-specific setsockopt commands, from ip_mroute.h */
#define DVMRP_DONE 						101
#define DVMRP_ADD_VIF 					102
#define DVMRP_DEL_VIF 					103
#define DVMRP_ADD_LGRP 					104
#define DVMRP_DEL_LGRP 					105
#define DVMRP_ADD_MRT 					106
#define DVMRP_DEL_MRT 					107


/* Shared library prefixes*/


#define kATalkVersion  "1.1"
#define kATalkPrefix  "ot:atlk$"
#define kATBinderID      "ot:atbd$"

/*******************************************************************************
** Module definitions
********************************************************************************/
/* XTI Levels*/

#define ATK_DDP 						'DDP '
#define ATK_AARP 						'AARP'
#define ATK_ATP 						'ATP '
#define ATK_ADSP 						'ADSP'
#define ATK_ASP 						'ASP '
#define ATK_PAP 						'PAP '
#define ATK_NBP 						'NBP '
#define ATK_ZIP 						'ZIP '

/* Module Names*/


#define kDDPName       "ddp"
#define   kATPName        "atp"
#define kADSPName     "adsp"
#define  kASPName        "asp"
#define kPAPName      "pap"
#define kNBPName      "nbp"
#define kZIPName      "zip"
#define kLTalkName        "ltlk"
#define kLTalkAName      "ltlkA"
#define kLTalkBName     "ltlkB"

/*
   Protocol-specific Options
   NOTE:
   All Protocols support OPT_CHECKSUM (Value is (unsigned long)T_YES/T_NO)
   ATP supports OPT_RETRYCNT (# Retries, 0 = try once) and
                OPT_INTERVAL (# Milliseconds to wait)
*/

#define DDP_OPT_HOPCOUNT 				0x2100				/*  DDP UnitDataReq Only - set hop count, Value is (unsigned long)  hop count    */
#define DDP_OPT_CHECKSUM 				0x0600
#define DDP_OPT_SRCADDR 				0x2101				/*  DDP UnitDataReq Only - set src address, Value is DDPAddress  */
#define ATP_OPT_REPLYCNT 				0x2110				/*  AppleTalk - ATP Resp Pkt Ct Type, Value is (unsigned long)  pkt count  */
#define ATP_OPT_DATALEN 				0x2111				/*  AppleTalk - ATP Pkt Data Len Type, Value is (unsigned long) length  */
#define ATP_OPT_RELTIMER 				0x2112				/*  AppleTalk - ATP Release Timer Type, Value is (unsigned long) timer, (See Inside AppleTalk, second edition  */
#define ATP_OPT_TRANID 					0x2113				/*  Value is (unsigned long) Boolean, Used to request Transaction ID, Returned with Transaction ID on requests  */
#define PAP_OPT_OPENRETRY 				0x2120				/*  AppleTalk - PAP OpenConn Retry count, Value is (unsigned long) T_YES/T_NO  */

/* XTI Level*/
#define COM_SERIAL 						'SERL'

#define kSerialABVersion   "1.1.1"


#define kSerialABName      "serialAB"
#define kSerialName          "serial"
#define kSerialPortAName   "serialA"
#define kSerialPortBName  "serialB"

/* Option Management for Serial Drivers*/

/*
   These options are all 4-byte values.
   BaudRate is the baud rate.
   DataBits is the number of data bits.
   StopBits is the number of stop bits times 10.
   Parity is an enum
*/

#define SERIAL_OPT_BAUDRATE 			0x0100				/*  UInt32  */
#define SERIAL_OPT_DATABITS 			0x0101				/*  UInt32  */
#define SERIAL_OPT_STOPBITS 			0x0102				/*  UInt32 10, 15 or 20 for 1, 1.5 or 2     */
#define SERIAL_OPT_PARITY 				0x0103				/*  UInt32  */
#define SERIAL_OPT_STATUS 				0x0104				/*  UInt32  */
															/*  The "Status" option is a 4-byte value option that is ReadOnly */
															/*  It returns a bitmap of the current serial status */
#define SERIAL_OPT_HANDSHAKE 			0x0105				/*  UInt32  */
															/*  The "Handshake" option defines what kind of handshaking the serial port */
															/*  will do for line flow control.  The value is a 32-bit value defined by */
															/*  the function or macro SerialHandshakeData below. */
															/*  For no handshake, or CTS handshake, the onChar and offChar parameters */
															/*  are ignored. */
#define SERIAL_OPT_RCVTIMEOUT 			0x0106				/*  The "RcvTimeout" option defines how long the receiver should wait before delivering */
															/*  less than the RcvLoWat number of characters.  If RcvLoWat is 0, then the RcvTimeout */
															/*  is how long a gap to wait for before delivering characters.  This parameter is advisory, */
															/*  and serial drivers are free to deliver data whenever they deem it convenient.  For instance, */
															/*  many serial drivers will deliver data whenever 64 bytes have been received, since 64 bytes */
															/*  is the smallest STREAMS buffer size. Keep in mind that timeouts are quantized, so be sure to */
															/*  look at the return value of the option to determine what it was negotiated to. */
#define SERIAL_OPT_ERRORCHARACTER 		0x0107				/*  This option defines how characters with parity errors are handled. */
															/*  A 0 value will disable all replacement.  A single character value in the low */
															/*  byte designates the replacement character.  When characters are received with a  */
															/*  parity error, they are replaced by this specified character.  If a valid incoming */
															/*  character matches the replacement character, then the received character's msb is */
															/*  cleared. For this situation, the alternate character is used, if specified in bits */
															/*  8 through 15 of the option long, with 0xff being place in bits 16 through 23. */
															/*  Whenever a valid character is received that matches the first replacement character, */
															/*  it is replaced with this alternate character. */
#define SERIAL_OPT_EXTCLOCK 			0x0108				/*  The "ExtClock" requests an external clock.  A 0-value turns off external clocking. */
															/*  Any other value is a requested divisor for the external clock.  Be aware that */
															/*  not all serial implementations support an external clock, and that not all */
															/*  requested divisors will be supported if it does support an external clock. */
#define SERIAL_OPT_BURSTMODE 			0x0109				/*  The "BurstMode" option informs the serial driver that it should continue looping, */
															/*  reading incoming characters, rather than waiting for an interrupt for each character. */
															/*  This option may not be supported by all Serial driver */
#define SERIAL_OPT_DUMMY 				0x010A				/*  placeholder */

/* XTI Level*/
#define COM_ISDN 						'ISDN'
#define kISDNName       "isdn"
/* Option management calls for ISDN*/
#define ISDN_OPT_COMMTYPE 				0x0200
#define ISDN_OPT_FRAMINGTYPE 			0x0201
#define ISDN_OPT_56KADAPTATION 			0x0202

/*******************************************************************************
*   Constants for Open Transport-based Remote Access/PPP API
********************************************************************************/

/* OTCreateConfiguration name for PPP control endpoint*/

#define kPPPControlName     "ppp"

/* XTI Level*/

#define COM_PPP 						'PPPC'
/* Option names*/

#define IPCP_OPT_GETREMOTEPROTOADDR 	0x00007000
#define IPCP_OPT_GETLOCALPROTOADDR 		0x00007001
#define IPCP_OPT_TCPHDRCOMPRESSION 		0x00007002
#define LCP_OPT_PPPCOMPRESSION 			0x00007003
#define LCP_OPT_MRU 					0x00007004
#define LCP_OPT_RCACCMAP 				0x00007005
#define LCP_OPT_TXACCMAP 				0x00007006
#define SEC_OPT_OUTAUTHENTICATION 		0x00007007
#define SEC_OPT_ID 						0x00007008
#define SEC_OPT_PASSWORD 				0x00007009
#define CC_OPT_REMINDERTIMER 			0x00007010
#define CC_OPT_IPIDLETIMER 				0x00007011
#define CC_OPT_DTEADDRESSTYPE 			0x00007012
#define CC_OPT_DTEADDRESS 				0x00007013
#define CC_OPT_CALLINFO 				0x00007014
#define CC_OPT_GETMISCINFO 				0x00007015
#define PPP_OPT_GETCURRENTSTATE 		0x00007016
#define LCP_OPT_ECHO 					0x00007017			/*  Available on Mac OS X only  */
#define CC_OPT_SERIALPORTNAME 			0x00007200


#endif /* __OPENTRANSPORTPROVIDERS_R__ */

