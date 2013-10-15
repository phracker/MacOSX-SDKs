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
            Title  : musclecard.h
            Package: MuscleCard Framework
            Author : David Corcoran
            Date   : 11/28/01
            License: Copyright (C) 2001 David Corcoran
                     <corcoran@linuxnet.com>
            Purpose: This abstracts the MUSCLE Card Edge Inteface

	    You may not remove this header from this file
	    without prior permission from the author.
 
********************************************************************/

#ifndef __musclecard_h__
#define __musclecard_h__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef WIN32
#include "PCSC.h"
#endif

#ifndef __APPLE__
#include <mscdefines.h>
#else
#include <PCSC/mscdefines.h>
#endif

	/****************
     * Return codes *
     ****************/

	/** success */
#define MSC_SUCCESS                        0x9000

	/** There have been memory problems on the card */
#define MSC_NO_MEMORY_LEFT                 0x9C01
	/** Entered PIN is not correct */
#define MSC_AUTH_FAILED                    0x9C02
	/** Required operation is not allowed in actual circumstances */
#define MSC_OPERATION_NOT_ALLOWED          0x9C03
	/** Required operation is inconsistent with memory contents */
#define MSC_INCONSISTENT_STATUS            0x9C04
	/** Required feature is not (yet) supported */
#define MSC_UNSUPPORTED_FEATURE            0x9C05
	/** Required operation was not authorized because of a lack of privileges */
#define MSC_UNAUTHORIZED                   0x9C06
	/** Required object is missing */
#define MSC_OBJECT_NOT_FOUND               0x9C07
	/** New object ID already in use */
#define MSC_OBJECT_EXISTS                  0x9C08
	/** Algorithm specified is not correct */
#define MSC_INCORRECT_ALG                  0x9C09

	/** Verify operation detected an invalid signature */
#define MSC_SIGNATURE_INVALID              0x9C0B
	/** Operation has been blocked for security reason  */
#define MSC_IDENTITY_BLOCKED               0x9C0C
	/** Unspecified error */
#define MSC_UNSPECIFIED_ERROR              0x9C0D
	/** PCSC and driver transport errors */
#define MSC_TRANSPORT_ERROR                0x9C0E
	/** Invalid parameter given */
#define MSC_INVALID_PARAMETER              0x9C0F
	/** Incorrect P1 parameter */
#define MSC_INCORRECT_P1                   0x9C10
	/** Incorrect P2 parameter */
#define MSC_INCORRECT_P2                   0x9C11
	/** End of sequence */
#define MSC_SEQUENCE_END                   0x9C12
	/** For debugging purposes */
#define MSC_INTERNAL_ERROR                 0x9CFF

	/*******************************************************/
	/*
	 * These returns are beyond the protocol specification 
	 */
	/*
	 * and only exist here to provide return codes for the 
	 */
	/*
	 * additional functions provided by the MuscleCard API 
	 */
	/*
	 * beyond the protocol specification.  
	 */
	/*******************************************************/

	/** A blocking event has been cancelled */
#define MSC_CANCELLED                      0x9C50
	/*
	 * The buffer provided is too short 
	 */
#define MSC_INSUFFICIENT_BUFFER            0x9C51
	/*
	 * The selected token is not recognized 
	 */
#define MSC_UNRECOGNIZED_TOKEN             0x9C52
	/*
	 * The PC/SC services is not available 
	 */
#define MSC_SERVICE_UNRESPONSIVE           0x9C53
	/*
	 * The action has timed out 
	 */
#define MSC_TIMEOUT_OCCURRED               0x9C54
	/*
	 * The token has been removed 
	 */
#define MSC_TOKEN_REMOVED                  0x9C55
	/*
	 * The token has been reset 
	 */
#define MSC_TOKEN_RESET                    0x9C56
	/*
	 * The token has been inserted 
	 */
#define MSC_TOKEN_INSERTED                 0x9C57
	/*
	 * The token is unresponsive 
	 */
#define MSC_TOKEN_UNRESPONSIVE             0x9C58
	/*
	 * The handle is invalid 
	 */
#define MSC_INVALID_HANDLE                 0x9C59
	/*
	 * Invalid sharing 
	 */
#define MSC_SHARING_VIOLATION              0x9C60


#define MSC_BLOCKSTATUS_RESUME             0x0000
#define MSC_BLOCKSTATUS_BLOCKING           0x0001
#define MSC_BLOCKSTATUS_CANCELLING         0x0002

	/*
	 * Some boundary defines 
	 */
#define MSC_MAX_KEYS                       16
#define MSC_MAX_PINS                        8
#define MSC_SIZEOF_KEYPACKET              200
#define MSC_MAXSIZEOF_APDU_DATALEN        255
#define MSC_PERCENT_STEPSIZE             1000
#define MSC_SINGLE_READ_PACKET            255
#define MSC_MAXSIZE_TOKENARRAY            255

	/*
	 * KeyPair Generation algorithms 
	 */
#define MSC_GEN_ALG_RSA	        0x00
#define MSC_GEN_ALG_RSA_CRT	0x01
#define MSC_GEN_ALG_DSA	        0x02
#define MSC_GEN_ALG_DES	        0x03
#define MSC_GEN_ALG_3DES	0x04
#define MSC_GEN_ALG_3DES3	0x05

	/*
	 * Blob encodings in KeyBlob structure 
	 */
#define MSC_BLOB_ENC_PLAIN	0x00
#define MSC_BLOB_ENC_CRYPT	0x01

	/*
	 * Key Type in Key Blobs 
	 */
#define MSC_KEY_RSA_PUBLIC       0x01
#define MSC_KEY_RSA_PRIVATE      0x02
#define MSC_KEY_RSA_PRIVATE_CRT  0x03
#define MSC_KEY_DSA_PUBLIC       0x04
#define MSC_KEY_DSA_PRIVATE      0x05
#define MSC_KEY_DES              0x06
#define MSC_KEY_3DES             0x07
#define MSC_KEY_3DES3            0x08

	/*
	 * Key generation options TODO: add other 
	 */
#define MSC_OPT_DEFAULT		 0x00
#define MSC_OPT_RSA_PUB_EXP      0x01
#define MSC_OPT_DSA_GPQ          0x02

	/*
	 * Cipher operations in ComputeCrypt() 
	 */
#define MSC_CIPHER_INIT	        0x01
#define MSC_CIPHER_PROCESS	0x02
#define MSC_CIPHER_FINAL	0x03

	/*
	 * Cipher modes in ComputeCrypt() 
	 */
#define MSC_MODE_RSA_NOPAD	0x00
#define MSC_MODE_RSA_PAD_PKCS1	0x01
#define MSC_MODE_DSA_SHA	0x10
#define MSC_MODE_DES_CBC_NOPAD	0x20
#define MSC_MODE_DES_ECB_NOPAD	0x21

	/*
	 * Cipher directions 
	 */
#define MSC_DIR_SIGN		0x01
#define MSC_DIR_VERIFY		0x02
#define MSC_DIR_ENCRYPT		0x03
#define MSC_DIR_DECRYPT		0x04

	/*
	 * Sequence options in ListXXX() 
	 */
#define MSC_SEQUENCE_RESET	0x00
#define MSC_SEQUENCE_NEXT	0x01

	/*
	 * Zero flag in DeleteObject() 
	 */
#define MSC_ZF_DEFAULT	0x00
#define MSC_ZF_WRITE_ZERO	0x01

	/*
	 * Some defines for ID's Bitmask 
	 */
#define MSC_AUT_ALL       0x0000
#define MSC_AUT_NONE      0xFFFF

#define MSC_AUT_PIN_0     0x0001
#define MSC_AUT_PIN_1     0x0002
#define MSC_AUT_PIN_2     0x0004
#define MSC_AUT_PIN_3     0x0008
#define MSC_AUT_PIN_4     0x0010

#define MSC_AUT_KEY_0     0x0100
#define MSC_AUT_KEY_1     0x0200
#define MSC_AUT_KEY_2     0x0400
#define MSC_AUT_KEY_3     0x0800
#define MSC_AUT_KEY_4     0x1000
#define MSC_AUT_KEY_5     0x2000

#define MSC_AUT_USR_0     0x4000
#define MSC_AUT_USR_1     0x8000

	/*
	 * This structure allows you to customize your MuscleCard. It is used
	 * in MSCWriteFramework to specify attributes you may want to set in
	 * this 'personalization' routine and will be getting new values in
	 * future revisions of the API 
	 */

#define MSC_INIT_DEFAULT_KEY     0x00	/* Use card's default transport
										 * key */
#define MSC_INIT_IGNORE_KEY      0x01	/* Don't verify any key at all */
#define MSC_INIT_USE_KEY         0x02	/* Use the key in this struct */

	typedef struct
	{
		MSCUChar8 transportKey[MAX_BUFFER_SIZE];
		MSCULong32 transportKeyLen;
		MSCUChar8  transportBehavior;
		MSCULong32 objectMemory;

		MSCUChar8  newTransportKey[MAX_BUFFER_SIZE];
		MSCULong32 newTransportKeyLen;

		MSCUChar8  defaultCHV[MAX_BUFFER_SIZE];
		MSCULong32 defaultCHVLen;
		MSCUChar8  defaultCHVTries;

		MSCUChar8  defaultCHVUnblock[MAX_BUFFER_SIZE];
		MSCULong32 defaultCHVUnblockSize;
		MSCUChar8  defaultCHVUnblockTries;

		MSCUShort16 createObjectACL;
		MSCUShort16 createKeysACL;
		MSCUShort16 createPINsACL;

		MSCUChar8   maxNumberKeys;
		MSCUChar8   maxNumberPINs;
		MSCUShort16 maxNumberObjects;

	}
	MSCInitTokenParams, *MSCLPInitTokenParams;

	/*
	 * Direction policy bitmasks for MSCKeyPolicy 
	 */
#define MSC_KEYPOLICY_MODE_RSA_NOPAD      0x0001
#define MSC_KEYPOLICY_MODE_RSA_PAD_PKCS1  0x0002
#define MSC_KEYPOLICY_MODE_DSA_SHA        0x0004
#define MSC_KEYPOLICY_MODE_DES_CBC_NOPAD  0x0008
#define MSC_KEYPOLICY_MODE_DES_ECB_NOPAD  0x0010

#define MSC_KEYPOLICY_DIR_SIGN            0x0100
#define MSC_KEYPOLICY_DIR_VERIFY          0x0200
#define MSC_KEYPOLICY_DIR_ENCRYPT         0x0400
#define MSC_KEYPOLICY_DIR_DECRYPT         0x0800

	typedef struct
	{
		MSCUShort16 cipherMode;
		MSCUShort16 cipherDirection;
	}
	MSCKeyPolicy, *MSCLPKeyPolicy;

	typedef struct
	{
		MSCUShort16 readPermission;
		MSCUShort16 writePermission;
		MSCUShort16 usePermission;
	}
	MSCKeyACL, *MSCLPKeyACL;

	typedef struct
	{
		MSCUShort16 readPermission;
		MSCUShort16 writePermission;
		MSCUShort16 deletePermission;
	}
	MSCObjectACL, *MSCLPObjectACL, MSCCertACL, *MSCLPCertACL;

	typedef struct
	{
		MSCUChar8 algoType;
		MSCUShort16 keySize;
		MSCKeyACL privateKeyACL;
		MSCKeyACL publicKeyACL;
		MSCKeyPolicy privateKeyPolicy;
		MSCKeyPolicy publicKeyPolicy;
		MSCUChar8 keyGenOptions;
		MSCPUChar8 pOptParams;
		MSCULong32 optParamsSize;
	}
	MSCGenKeyParams, *MSCLPGenKeyParams;

	typedef MSCPUChar8 MSCLPKeyBlob;

	typedef struct
	{
		MSCUChar8 keyNum;
		MSCUChar8 keyType;
		MSCUChar8 keyPartner;   /* Do not use (deprecated) */
	        MSCUChar8 keyMapping;   /* Do not use (deprecated) */
		MSCUShort16 keySize;
		MSCKeyPolicy keyPolicy;
		MSCKeyACL keyACL;
	}
	MSCKeyInfo, *MSCLPKeyInfo;

	typedef struct
	{
		MSCUChar8 keyNum;
		MSCUChar8 cipherMode;
		MSCUChar8 cipherDirection;
		MSCPUChar8 optParams;
		MSCUShort16 optParamsSize;
	}
	MSCCryptInit, *MSCLPCryptInit;

	/*
	 * Scope definitions for MSCListTokens 
	 */
#define MSC_LIST_KNOWN     1	/* Lists known tokens only */
#define MSC_LIST_SLOTS     2	/* Lists all slots, with or without tokens 
								 */
#define MSC_LIST_ALL       3	/* Lists all tokens, known or not */

#define MSC_TOKEN_EMPTY_STR    "Token Removed"
#define MSC_TOKEN_UNKNOWN_STR  "Token Unknown"

#define MSC_TOKEN_TYPE_REMOVED   1	/* Token was removed at one point */
#define MSC_TOKEN_TYPE_UNKNOWN   2	/* Token is unknown, state is fine */
#define MSC_TOKEN_TYPE_KNOWN     4	/* Token is known, state is fine */
#define MSC_TOKEN_TYPE_RESET     8	/* Token is known, was reset */

	/*
	 * endAction definitions for MSCReleaseConnection 
	 */
#define MSC_LEAVE_TOKEN    SCARD_LEAVE_CARD
#define MSC_RESET_TOKEN    SCARD_RESET_CARD
#define MSC_EJECT_TOKEN    SCARD_EJECT_CARD

	/*
	 * sharingMode for MSCEstablishConnection 
	 */
#define MSC_SHARE_SHARED     SCARD_SHARE_SHARED
#define MSC_SHARE_EXCLUSIVE  SCARD_SHARE_EXCLUSIVE
#define MSC_SHARE_DIRECT     SCARD_SHARE_DIRECT

	/*
	 * tokenState for MSCWaitForTokenEvent 
	 */
#define MSC_STATE_UNAWARE      0x4000
#define MSC_STATE_CHANGED      SCARD_STATE_CHANGED
#define MSC_STATE_UNKNOWN      SCARD_STATE_UNKNOWN
#define MSC_STATE_UNAVAILABLE  SCARD_STATE_UNAVAILABLE
#define MSC_STATE_EMPTY        SCARD_STATE_EMPTY
#define MSC_STATE_PRESENT      SCARD_STATE_PRESENT
#define MSC_STATE_EXCLUSIVE    SCARD_STATE_EXCLUSIVE
#define MSC_STATE_INUSE        SCARD_STATE_INUSE
#define MSC_STATE_MUTE         SCARD_STATE_MUTE

#define MSC_NO_TIMEOUT         INFINITE

/********************** TAGS for GetStatus ********************************/

	/*
	 * high level tags 
	 */
#define MSC_TAG_SUPPORT_FUNCTIONS     101	/* Supported functions */
#define MSC_TAG_SUPPORT_CRYPTOALG     102	/* Supported crypto algorithms 
											 */

	/*
	 * crypto related tags 
	 */
#define MSC_TAG_CAPABLE_RSA           103	/* RSA capabilities */
#define MSC_TAG_CAPABLE_DSA           104	/* DSA capabilities */
#define MSC_TAG_CAPABLE_ECURVE        105	/* Eliptic Curve capabilities */
#define MSC_TAG_CAPABLE_ELGAMAL       106	/* El Gamal capabilities */

#define MSC_TAG_CAPABLE_KEY_AUTH      180	/* Key import/gen AUT needed */

#define MSC_TAG_CAPABLE_DES           201	/* DES capabilities */
#define MSC_TAG_CAPABLE_3DES          202	/* Triple DES capabilities */
#define MSC_TAG_CAPABLE_IDEA          203	/* IDEA capabilities */
#define MSC_TAG_CAPABLE_AES           204	/* AES capabilities */
#define MSC_TAG_CAPABLE_BLOWFISH      205	/* Blowfish capabilities */
#define MSC_TAG_CAPABLE_TWOFISH       206	/* Twofish capabilities */

#define MSC_TAG_CAPABLE_MD5           207	/* MD5 capabilities */
#define MSC_TAG_CAPABLE_SHA1          208	/* SHA1 capabilities */

	/*
	 * object related tags 
	 */
#define MSC_TAG_CAPABLE_OBJ_ATTR      301	/* returns general attributes */
#define MSC_TAG_CAPABLE_OBJ_IDSIZE    302	/* returns size of object id */
#define MSC_TAG_CAPABLE_OBJ_AUTH      303	/* return AUT needed for
											 * create */
#define MSC_TAG_CAPABLE_OBJ_MAXNUM    304	/* maximum number of objects */

	/*
	 * pin related tags 
	 */
#define MSC_TAG_CAPABLE_PIN_ATTR      401	/* returns general attributes */
#define MSC_TAG_CAPABLE_PIN_MAXNUM    402	/* returns max number of pins */
#define MSC_TAG_CAPABLE_PIN_MINSIZE   403	/* returns minimum pin size */
#define MSC_TAG_CAPABLE_PIN_MAXSIZE   404	/* returns maximum pin size */
#define MSC_TAG_CAPABLE_PIN_CHARSET   405	/* char set supported
											 * (bitmask) */
#define MSC_TAG_CAPABLE_PIN_POLICY    406	/* returns pin policy
											 * (bitmask) */
#define MSC_TAG_CAPABLE_PIN_AUTH      407	/* return AUT needed for
											 * create */

#define MSC_TAG_CAPABLE_ID_STATE      501	/* returns state capability */

#define MSC_TAG_CAPABLE_RANDOM        600	/* Random number capabilities */
#define MSC_TAG_CAPABLE_RANDOM_MAX    601	/* Maximum random number */
#define MSC_TAG_CAPABLE_RANDOM_MIN    602	/* Minimum random number */

/********************************** END OF TAGS ***************************/

	/*
	 * Bitmask for TAG MSC_TAG_SUPPORT_FUNCTIONS 
	 */
#define MSC_SUPPORT_GENKEYS           0x00000001
#define MSC_SUPPORT_IMPORTKEY         0x00000002
#define MSC_SUPPORT_EXPORTKEY         0x00000004
#define MSC_SUPPORT_COMPUTECRYPT      0x00000008
#define MSC_SUPPORT_EXTAUTH           0x00000010
#define MSC_SUPPORT_LISTKEYS          0x00000020
#define MSC_SUPPORT_CREATEPIN         0x00000040
#define MSC_SUPPORT_VERIFYPIN         0x00000080
#define MSC_SUPPORT_CHANGEPIN         0x00000100
#define MSC_SUPPORT_UNBLOCKPIN        0x00000200
#define MSC_SUPPORT_LISTPINS          0x00000400
#define MSC_SUPPORT_CREATEOBJECT      0x00000800
#define MSC_SUPPORT_DELETEOBJECT      0x00001000
#define MSC_SUPPORT_WRITEOBJECT       0x00002000
#define MSC_SUPPORT_READOBJECT        0x00004000
#define MSC_SUPPORT_LISTOBJECTS       0x00008000
#define MSC_SUPPORT_LOGOUTALL         0x00010000
#define MSC_SUPPORT_GETCHALLENGE      0x00020000

	/*
	 * Bitmask for MSC_TAG_SUPPORT_CRYPTOALG 
	 */
#define MSC_SUPPORT_RSA           0x00000001	/* Supports RSA */
#define MSC_SUPPORT_DSA           0x00000002	/* Supports DSA */
#define MSC_SUPPORT_ECURVE        0x00000004	/* Supports Eliptic Curve */
#define MSC_SUPPORT_ELGAMAL       0x00000008	/* Supports El Gamal */

#define MSC_SUPPORT_DES           0x00000010	/* Supports DES */
#define MSC_SUPPORT_3DES          0x00000020	/* Supports Triple DES */
#define MSC_SUPPORT_IDEA          0x00000040	/* Supports IDEA */
#define MSC_SUPPORT_AES           0x00000080	/* Supports AES */
#define MSC_SUPPORT_BLOWFISH      0x00000100	/* Supports Blowfish */
#define MSC_SUPPORT_TWOFISH       0x00000200	/* Supports Twofish */
#define MSC_SUPPORT_SHA1          0x00000400	/* Supports SHA1 */
#define MSC_SUPPORT_MD5           0x00000800	/* Supports MD5 */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_RSA 
	 */
#define MSC_CAPABLE_RSA_512       0x00000001	/* Supports 512 bit RSA */
#define MSC_CAPABLE_RSA_768       0x00000002	/* Supports 768 bit RSA */
#define MSC_CAPABLE_RSA_1024      0x00000004	/* Supports 1024 bit RSA */
#define MSC_CAPABLE_RSA_2048      0x00000008	/* Supports 2048 bit RSA */
#define MSC_CAPABLE_RSA_4096      0x00000010	/* Supports 4096 bit RSA */

#define MSC_CAPABLE_RSA_KEYGEN    0x00001000	/* Support RSA key-gen */
#define MSC_CAPABLE_RSA_NOPAD     0x00002000	/* Supports RSA NO PAD */
#define MSC_CAPABLE_RSA_PKCS1     0x00004000	/* Supports PKCS padding */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_DSA 
	 */
#define MSC_CAPABLE_DSA_512       0x00000001	/* Supports 512 bit DSA */
#define MSC_CAPABLE_DSA_768       0x00000002	/* Supports 768 bit DSA */
#define MSC_CAPABLE_DSA_1024      0x00000004	/* Supports 1024 bit DSA */
#define MSC_CAPABLE_DSA_2048      0x00000008	/* Supports 2048 bit DSA */
#define MSC_CAPABLE_DSA_4096      0x00000010	/* Supports 4096 bit DSA */
#define MSC_CAPABLE_DSA_KEYGEN    0x00001000	/* Supports DSA key-gen */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_DES 
	 */
#define MSC_CAPABLE_DES_KEYGEN    0x00001000	/* Supports DES key-gen */
#define MSC_CAPABLE_DES_CBC       0x00002000	/* Supports DES CBC mode */
#define MSC_CAPABLE_DES_EBC       0x00004000	/* Supports DES EBC mode */
#define MSC_CAPABLE_DES_ECB       0x00008000	/* Supports DES ECB mode */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_3DES 
	 */
#define MSC_CAPABLE_3DES_KEYGEN   0x00001000	/* Supports 3DES key-gen */
#define MSC_CAPABLE_3DES_3KEY     0x00002000	/* Support 3 key 3DES */
#define MSC_CAPABLE_3DES_CBC      0x00004000	/* Supports 3DES CBC mode */
#define MSC_CAPABLE_3DES_EBC      0x00008000	/* Supports 3DES EBC mode */
#define MSC_CAPABLE_3DES_ECB      0x00010000	/* Supports 3DES ECB mode */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_IDEA 
	 */
#define MSC_CAPABLE_IDEA_KEYGEN   0x00001000	/* Supports IDEA key-gen */
#define MSC_CAPABLE_IDEA_CBC      0x00002000	/* Supports IDEA CBC mode */
#define MSC_CAPABLE_IDEA_ECB      0x00008000	/* Supports IDEA ECB mode */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_AES 
	 */
#define MSC_CAPABLE_AES_KEYGEN    0x00001000	/* Supports AES key-gen */
#define MSC_CAPABLE_AES_CBC       0x00002000	/* Supports AES CBC mode */
#define MSC_CAPABLE_AES_ECB       0x00008000	/* Supports AES ECB mode */

	/***********************************
     Bitmasks for other crypto algorithms 
     will come in future releases 
    ************************************/

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_OBJ_ATTR 
	 */
#define MSC_CAPABLE_OBJ_ZERO      0x00010000	/* Supports zero on DEL */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_PIN_ATTR 
	 */
#define MSC_CAPABLE_PIN_RESET     0x00000100	/* Unblock reset's pin */
#define MSC_CAPABLE_PIN_LEAVE     0x00000200	/* Unblock leaves pin */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_PIN_CHARSET 
	 */
#define MSC_CAPABLE_PIN_A_Z       0x00000001	/* Supports uppercase A-Z */
#define MSC_CAPABLE_PIN_a_z       0x00000002	/* Supports lowercase a-z */
#define MSC_CAPABLE_PIN_0_9       0x00000004	/* Supports numbers 0-9 */
#define MSC_CAPABLE_PIN_SPACE     0x00000008	/* Supports spaces */
#define MSC_CAPABLE_PIN_CALC      0x00000010	/* Supports + - / * % .= */
#define MSC_CAPABLE_PIN_NONALPHA  0x00000020	/* Supports all other
												 * chars */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_PIN_POLICY 
	 */
#define MSC_CAPABLE_PIN_A_Z       0x00000001	/* Requires uppercase A-Z */
#define MSC_CAPABLE_PIN_a_z       0x00000002	/* Requires lowercase a-z */
#define MSC_CAPABLE_PIN_0_9       0x00000004	/* Requires numbers 0-9 */
#define MSC_CAPABLE_PIN_NONALPHA  0x00000020	/* Requires
												 * non-alphanumeric */
#define MSC_CAPABLE_PIN_HISTORY   0x00001000	/* Checks pin history */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_ID_STATE 
	 */
#define MSC_CAPABLE_ID_STATE      0x00000001	/* maintains logged id
												 * state */

	/*
	 * Bitmask for TAG MSC_TAG_CAPABLE_RANDOM 
	 */
#define MSC_CAPABLE_RANDOM_SEED   0x00000001	/* Uses supplied seed */

	/*
	 * Structure used in MSCGetStatus to return status and capability
	 * information about the inserted token 
	 */

	typedef struct
	{
		MSCUShort16 appVersion;	/* Applet version number */
		MSCUShort16 swVersion;	/* Software version number */
		MSCULong32 freeMemory;	/* Free memory for objects */
		MSCULong32 totalMemory;	/* Total amount of memory */
		MSCUChar8 usedPINs;		/* Number of pins used */
		MSCUChar8 usedKeys;		/* Number of keys used */
		MSCUShort16 loggedID;	/* Bitmask of ID's verified */
	}
	MSCStatusInfo, *MSCLPStatusInfo;

	typedef struct
	{
		MSCChar8 objectID[MSC_MAXSIZE_OBJID];
		MSCULong32 objectSize;
		MSCObjectACL objectACL;
	}
	MSCObjectInfo, *MSCLPObjectInfo;

	/*******************************************************************/
	/*
	 * Connection oriented functions 
	 */
	/*
	 * These functions do not coorespond to internal library funcions 
	 */
	/*
	 * but serve to connect to tokens.  You can still use the internal 
	 */
	/*
	 * PC/SC calls to do this.  These provide an abstract means.  
	 */
	/*******************************************************************/

	/*
	 * Lists all known tokens on the system 
	 */
#ifdef WIN32
	PCSC_API
#endif
	 MSC_RV MSCListTokens(MSCULong32 listScope,	/* defines the scope to
												 * return */
		MSCLPTokenInfo tokenArray,	/* token struct array */
		MSCPULong32 arrayLength	/* Length of array */
		);

	/*
	 * Establishes a connection to the specified token 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCEstablishConnection(MSCLPTokenInfo tokenStruct,	/* The
																 * struct
																 * of
																 * token */
		MSCULong32 sharingMode,	/* Mode of sharing */
		MSCPUChar8 applicationName,	/* The applet ID/Name */
		MSCULong32 nameSize,	/* The ID/Name Size */
		MSCLPTokenConnection pConnection	/* Returned connection */
		);

	/*
	 * Releases a connection to the specified token 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCReleaseConnection(MSCLPTokenConnection pConnection,	/* Connection 
																	 * handle 
																	 */
		MSCULong32 endAction	/* Action to perform */
		);

	/*
	 * Blocks for an event to occur on a token 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCWaitForTokenEvent(MSCLPTokenInfo tokenArray,	/* Array of
															 * token
															 * structs */
		MSCULong32 arraySize,	/* Size of the array */
		MSCULong32 timeoutValue	/* Timeout */
		);

	/*
	 * Cancels a pending MSCWaitForTokenEvent 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCCancelEventWait(void	/* No parameters */
		);

	/*
	 * Registers a callback function for event change 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCCallbackForTokenEvent(MSCLPTokenInfo tokenArray,	/* Array
																 * of
																 * token
																 * structs 
																 */
		MSCULong32 arraySize,	/* Size of the array */
		MSCCallBack callBack,	/* Callback function */
		MSCPVoid32 appData		/* Application data */
		);

	/*
	 * Cancels all callback registrations 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCCallbackCancelEvent();

	/*
	 * Locks a transaction to the token 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCBeginTransaction(MSCLPTokenConnection pConnection	/* Connection 
																 * handle */
		);

	/*
	 * Releases a locked transaction to the token 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCEndTransaction(MSCLPTokenConnection pConnection,	/* Connection 
																 * handle */
		MSCULong32 endAction	/* Action to perform on token */
		);

	/*
	 * Selects applet - Not to be used by applications 
	 */
	MSC_RV MSCSelectAID(MSCLPTokenConnection pConnection,
		MSCPUChar8 aidValue, MSCULong32 aidSize);

	/*
	 * Pre-personalization function 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCWriteFramework(MSCLPTokenConnection pConnection,
		MSCLPInitTokenParams pInitParams);

	/*****************************************************************/
	/*
	 * Core Musclecard functions 
	 */
	/*
	 * These functions coorespond directly to internal library 
	 */
	/*
	 * functions.  
	 */
	/*****************************************************************/

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCGetStatus(MSCLPTokenConnection pConnection,
		MSCLPStatusInfo pStatusInfo);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCGetCapabilities(MSCLPTokenConnection pConnection,
		MSCULong32 Tag, MSCPUChar8 Value, MSCPULong32 Length);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCExtendedFeature(MSCLPTokenConnection pConnection,
		MSCULong32 extFeature,
		MSCPUChar8 outData,
		MSCULong32 outLength, MSCPUChar8 inData, MSCPULong32 inLength);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCGenerateKeys(MSCLPTokenConnection pConnection,
		MSCUChar8 prvKeyNum,
		MSCUChar8 pubKeyNum, MSCLPGenKeyParams pParams);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCImportKey(MSCLPTokenConnection pConnection,
		MSCUChar8 keyNum,
		MSCLPKeyACL pKeyACL,
		MSCPUChar8 pKeyBlob,
		MSCULong32 keyBlobSize,
		MSCLPKeyPolicy keyPolicy,
		MSCPVoid32 pAddParams, MSCUChar8 addParamsSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCExportKey(MSCLPTokenConnection pConnection,
		MSCUChar8 keyNum,
		MSCPUChar8 pKeyBlob,
		MSCPULong32 keyBlobSize,
		MSCPVoid32 pAddParams, MSCUChar8 addParamsSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCComputeCrypt(MSCLPTokenConnection pConnection,
		MSCLPCryptInit cryptInit,
		MSCPUChar8 pInputData,
		MSCULong32 inputDataSize,
		MSCPUChar8 pOutputData, MSCPULong32 outputDataSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCExtAuthenticate(MSCLPTokenConnection pConnection,
				  MSCUChar8 keyNum,
				  MSCUChar8 cipherMode,
				  MSCUChar8 cipherDirection, 
				  MSCPUChar8 pData, 
				  MSCULong32 dataSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCListKeys(MSCLPTokenConnection pConnection,
			   MSCUChar8 seqOption, 
			   MSCLPKeyInfo pKeyInfo);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCCreatePIN(MSCLPTokenConnection pConnection,
			    MSCUChar8 pinNum,
			    MSCUChar8 pinAttempts,
			    MSCPUChar8 pPinCode,
			    MSCULong32 pinCodeSize,
			    MSCPUChar8 pUnblockCode, 
			    MSCUChar8 unblockCodeSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCVerifyPIN(MSCLPTokenConnection pConnection,
			    MSCUChar8 pinNum, 
			    MSCPUChar8 pPinCode, 
			    MSCULong32 pinCodeSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCChangePIN(MSCLPTokenConnection pConnection,
		MSCUChar8 pinNum,
		MSCPUChar8 pOldPinCode,
		MSCUChar8 oldPinCodeSize,
		MSCPUChar8 pNewPinCode, MSCUChar8 newPinCodeSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCUnblockPIN(MSCLPTokenConnection pConnection,
		MSCUChar8 pinNum,
		MSCPUChar8 pUnblockCode, MSCULong32 unblockCodeSize);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCListPINs(MSCLPTokenConnection pConnection,
		MSCPUShort16 pPinBitMask);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCCreateObject(MSCLPTokenConnection pConnection,
		MSCString objectID,
		MSCULong32 objectSize, MSCLPObjectACL pObjectACL);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCDeleteObject(MSCLPTokenConnection pConnection,
		MSCString objectID, MSCUChar8 zeroFlag);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCWriteObject(MSCLPTokenConnection pConnection,
		MSCString objectID, MSCULong32 offset, 
		MSCPUChar8 pInputData, MSCULong32 dataSize,
		LPRWEventCallback rwCallback, MSCPVoid32 addParams);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCReadObject(MSCLPTokenConnection pConnection,
		MSCString objectID, MSCULong32 offset, 
                MSCPUChar8 pOutputData, MSCULong32 dataSize,
		LPRWEventCallback rwCallback, MSCPVoid32 addParams);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCReadAllocateObject(MSCLPTokenConnection pConnection,
		MSCString objectID, MSCPUChar8 *pOutputData, 
                MSCPULong32 dataSize,
                LPRWEventCallback rwCallback, MSCPVoid32 addParams);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCListObjects(MSCLPTokenConnection pConnection,
		MSCUChar8 seqOption, MSCLPObjectInfo pObjectInfo);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCLogoutAll(MSCLPTokenConnection pConnection);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCGetChallenge(MSCLPTokenConnection pConnection,
		MSCPUChar8 pSeed,
		MSCUShort16 seedSize,
		MSCPUChar8 pRandomData, MSCUShort16 randomDataSize);

	/*****************************************************************/
	/*
	 * Extended Musclecard functions 
	 */
	/*
	 * These functions do not coorespond to internal library funcions 
	 */
	/*
	 * but rather use them to provide some extended functionality.  
	 */
	/*****************************************************************/

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCGetKeyAttributes(MSCLPTokenConnection pConnection,
				   MSCUChar8 keyNumber, 
				   MSCLPKeyInfo pKeyInfo);

#ifdef WIN32
	PCSC_API
#endif
	MSC_RV MSCGetObjectAttributes(MSCLPTokenConnection pConnection,
				      MSCString objectID, 
				      MSCLPObjectInfo pObjectInfo);

#ifdef WIN32
	PCSC_API
#endif
	char *msc_error(unsigned long int errorCode);

	/*
	 * Was the token reset ? 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSCUChar8 MSCIsTokenReset(MSCLPTokenConnection pConnection);

	/*
	 * Clear the Reset state 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSCUChar8 MSCClearReset(MSCLPTokenConnection pConnection);

	/*
	 * Was the token moved (removed, removed/inserted) ? 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSCUChar8 MSCIsTokenMoved(MSCLPTokenConnection pConnection);

	/*
	 * Did any state change with the token ? 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSCUChar8 MSCIsTokenChanged(MSCLPTokenConnection pConnection);

	/*
	 * Is the token recognized ? 
	 */
#ifdef WIN32
	PCSC_API
#endif
	MSCUChar8 MSCIsTokenKnown(MSCLPTokenConnection pConnection);

#ifdef __cplusplus
}
#endif

#endif							/* __musclecard_h__ */
