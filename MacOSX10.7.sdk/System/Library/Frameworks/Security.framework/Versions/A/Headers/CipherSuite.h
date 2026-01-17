/*
 * Copyright (c) 2000-2002 Apple Computer, Inc. All Rights Reserved.
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


/*
	File:		CipherSuite.h

	Contains:	SSL Cipher Suite definitions. 

	Copyright: (c) 1999 by Apple Computer, Inc., all rights reserved.

*/
#ifndef _SECURITY_CIPHERSUITE_H_
#define _SECURITY_CIPHERSUITE_H_

/* fetch Uint32 */
#include <CoreFoundation/CFBase.h>

/*
 * Defined as enum for debugging, but in the protocol
 * it is actually exactly two bytes
 */
typedef UInt32 SSLCipherSuite;

enum
{   SSL_NULL_WITH_NULL_NULL =                   0x0000,
    SSL_RSA_WITH_NULL_MD5 =                     0x0001,
    SSL_RSA_WITH_NULL_SHA =                     0x0002,
    SSL_RSA_EXPORT_WITH_RC4_40_MD5 =            0x0003,
    SSL_RSA_WITH_RC4_128_MD5 =                  0x0004,
    SSL_RSA_WITH_RC4_128_SHA =                  0x0005,
    SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5 =        0x0006,
    SSL_RSA_WITH_IDEA_CBC_SHA =                 0x0007,
    SSL_RSA_EXPORT_WITH_DES40_CBC_SHA =         0x0008,
    SSL_RSA_WITH_DES_CBC_SHA =                  0x0009,
    SSL_RSA_WITH_3DES_EDE_CBC_SHA =             0x000A,
    SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA =      0x000B,
    SSL_DH_DSS_WITH_DES_CBC_SHA =               0x000C,
    SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA =          0x000D,
    SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA =      0x000E,
    SSL_DH_RSA_WITH_DES_CBC_SHA =               0x000F,
    SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA =          0x0010,
    SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA =     0x0011,
    SSL_DHE_DSS_WITH_DES_CBC_SHA =              0x0012,
    SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA =         0x0013,
    SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA =     0x0014,
    SSL_DHE_RSA_WITH_DES_CBC_SHA =              0x0015,
    SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA =         0x0016,
    SSL_DH_anon_EXPORT_WITH_RC4_40_MD5 =        0x0017,
    SSL_DH_anon_WITH_RC4_128_MD5 =              0x0018,
    SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA =     0x0019,
    SSL_DH_anon_WITH_DES_CBC_SHA =              0x001A,
    SSL_DH_anon_WITH_3DES_EDE_CBC_SHA =         0x001B,
    SSL_FORTEZZA_DMS_WITH_NULL_SHA =            0x001C,
    SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA =    0x001D,
	
	/* TLS addenda using AES, per RFC 3268 */
	TLS_RSA_WITH_AES_128_CBC_SHA	  =			0x002F,
	TLS_DH_DSS_WITH_AES_128_CBC_SHA	  =			0x0030,
	TLS_DH_RSA_WITH_AES_128_CBC_SHA   =			0x0031,
	TLS_DHE_DSS_WITH_AES_128_CBC_SHA  =			0x0032,
	TLS_DHE_RSA_WITH_AES_128_CBC_SHA  =			0x0033,
	TLS_DH_anon_WITH_AES_128_CBC_SHA  =			0x0034,
	TLS_RSA_WITH_AES_256_CBC_SHA      =			0x0035,
	TLS_DH_DSS_WITH_AES_256_CBC_SHA   =			0x0036,
	TLS_DH_RSA_WITH_AES_256_CBC_SHA   =			0x0037,
	TLS_DHE_DSS_WITH_AES_256_CBC_SHA  =			0x0038,
	TLS_DHE_RSA_WITH_AES_256_CBC_SHA  =			0x0039,
	TLS_DH_anon_WITH_AES_256_CBC_SHA  =			0x003A,
	
	/* ECDSA addenda, RFC 4492 */
	TLS_ECDH_ECDSA_WITH_NULL_SHA           =	0xC001,
	TLS_ECDH_ECDSA_WITH_RC4_128_SHA        =	0xC002,
	TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA   =	0xC003,
	TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA    =	0xC004,
	TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA    =	0xC005,
	TLS_ECDHE_ECDSA_WITH_NULL_SHA          =	0xC006,
	TLS_ECDHE_ECDSA_WITH_RC4_128_SHA       =	0xC007,
	TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA  =	0xC008,
	TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA   =	0xC009,
	TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA   =	0xC00A,
	TLS_ECDH_RSA_WITH_NULL_SHA             =	0xC00B,
	TLS_ECDH_RSA_WITH_RC4_128_SHA          =	0xC00C,
	TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA     =	0xC00D,
	TLS_ECDH_RSA_WITH_AES_128_CBC_SHA      =	0xC00E,
	TLS_ECDH_RSA_WITH_AES_256_CBC_SHA      =	0xC00F,
	TLS_ECDHE_RSA_WITH_NULL_SHA            =	0xC010,
	TLS_ECDHE_RSA_WITH_RC4_128_SHA         =	0xC011,
	TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA    =	0xC012,
	TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA     =	0xC013,
	TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA     =	0xC014,
	TLS_ECDH_anon_WITH_NULL_SHA            =	0xC015,
	TLS_ECDH_anon_WITH_RC4_128_SHA         =	0xC016,
	TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA    =	0xC017,
	TLS_ECDH_anon_WITH_AES_128_CBC_SHA     =	0xC018,
	TLS_ECDH_anon_WITH_AES_256_CBC_SHA     =	0xC019,
	
	/*
	 * Tags for SSL 2 cipher kinds which are not specified 
	 * for SSL 3. 
	 */
    SSL_RSA_WITH_RC2_CBC_MD5 =                  0xFF80,     
    SSL_RSA_WITH_IDEA_CBC_MD5 =                 0xFF81,     
    SSL_RSA_WITH_DES_CBC_MD5 =                  0xFF82,     
    SSL_RSA_WITH_3DES_EDE_CBC_MD5 =             0xFF83,
    SSL_NO_SUCH_CIPHERSUITE =                   0xFFFF
};

#endif	/* !_SECURITY_CIPHERSUITE_H_ */
