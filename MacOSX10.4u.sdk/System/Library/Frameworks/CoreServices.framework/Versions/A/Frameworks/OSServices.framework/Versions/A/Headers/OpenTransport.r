/*
     File:       OpenTransport.r
 
     Contains:   Open Transport client interface file.
 
     Version:    OpenTransport-105~810
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __OPENTRANSPORT_R__
#define __OPENTRANSPORT_R__

#ifndef __CONDITIONALMACROS_R__
#include <CarbonCore/ConditionalMacros.r>
#endif

#ifndef OTKERNEL
#define OTKERNEL 0
#endif  /* !defined(OTKERNEL) */

#ifndef OTUNIXERRORS
#define OTUNIXERRORS 0
#endif  /* !defined(OTUNIXERRORS) */

#ifdef qDebug
#ifndef OTDEBUG
#define OTDebug qDebug
#endif  /* !defined(OTDEBUG) */

#endif  /* defined(qDebug) */

#ifndef OTDEBUG
#define OTDEBUG 0
#endif  /* !defined(OTDEBUG) */

#ifndef BuildingOTForKernel
#define BuildingOTForKernel 0
#endif  /* !defined(BuildingOTForKernel) */

#ifndef OTCARBONAPPLICATION
#define OTCARBONAPPLICATION 0
#endif  /* !defined(OTCARBONAPPLICATION) */

/* ***** Shared Library Prefixes ******/

#define kOTLibraryVersion      "1.1"

#define kOTLibraryPrefix         "OTLib$"
#define kOTModulePrefix            "OTModl$"
#define kOTClientPrefix           "OTClnt$"
#define kOTKernelPrefix           "OTKrnl$"

#define kOTCFMClass 					'otan'
/* ***** Option Management Definitions ******/
/* The XTI Level number of a protocol.*/
#define XTI_GENERIC 					0xFFFF				/*  level for XTI options  */
/* XTI names for options used with XTI_GENERIC above*/
#define XTI_DEBUG 						0x0001
#define XTI_LINGER 						0x0080
#define XTI_RCVBUF 						0x1002
#define XTI_RCVLOWAT 					0x1004
#define XTI_SNDBUF 						0x1001
#define XTI_SNDLOWAT 					0x1003
#define XTI_PROTOTYPE 					0x1005
#define OPT_CHECKSUM 					0x0600				/*  Set checksumming = UInt32 - 0 or 1) */
#define OPT_RETRYCNT 					0x0601				/*  Set a retry counter = UInt32 (0 = infinite) */
#define OPT_INTERVAL 					0x0602				/*  Set a retry interval = UInt32 milliseconds */
#define OPT_ENABLEEOM 					0x0603				/*  Enable the EOM indication = UInt8 (0 or 1) */
#define OPT_SELFSEND 					0x0604				/*  Enable Self-sending on broadcasts = UInt32 (0 or 1) */
#define OPT_SERVERSTATUS 				0x0605				/*  Set Server Status (format is proto dependent) */
#define OPT_ALERTENABLE 				0x0606				/*  Enable/Disable protocol alerts */
#define OPT_KEEPALIVE 					0x0008				/*  See t_keepalive structure */


#endif /* __OPENTRANSPORT_R__ */

