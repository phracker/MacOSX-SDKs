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


/*
   File:      cssmapple.h

   Contains:  CSSM features specific to Apple's Implementation

   Copyright: (c) 1999-2000 Apple Computer, Inc., all rights reserved.
*/

#ifndef _CSSMAPPLE_H_
#define _CSSMAPPLE_H_  1

#include <Security/cssmerr.h>
#include <Security/cssmtype.h>
#include <sys/types.h>	/* for the BSD *_t types */

#ifdef __cplusplus
extern "C" {
#endif

/* Guids for standard Apple addin modules. */

/* {87191ca0-0fc9-11d4-849a-000502b52122} */
extern const CSSM_GUID gGuidCssm;

/* {87191ca1-0fc9-11d4-849a-000502b52122} */
extern const CSSM_GUID gGuidAppleFileDL;

/* {87191ca2-0fc9-11d4-849a-000502b52122} */
extern const CSSM_GUID gGuidAppleCSP;

/* {87191ca3-0fc9-11d4-849a-000502b52122} */
extern const CSSM_GUID gGuidAppleCSPDL;

/* {87191ca4-0fc9-11d4-849a-000502b52122} */
extern const CSSM_GUID gGuidAppleX509CL;

/* {87191ca5-0fc9-11d4-849a-000502b52122} */
extern const CSSM_GUID gGuidAppleX509TP;


/* Apple defined WORDID values */
enum
{
	CSSM_WORDID_KEYCHAIN_PROMPT = CSSM_WORDID_VENDOR_START,
    CSSM_WORDID_KEYCHAIN_LOCK,
    CSSM_WORDID_KEYCHAIN_CHANGE_LOCK,
	CSSM_WORDID_PROCESS,
	CSSM_WORDID__FIRST_UNUSED
};

/* Apple defined ACL subject and credential types */
enum
{
	CSSM_ACL_SUBJECT_TYPE_KEYCHAIN_PROMPT = CSSM_WORDID_KEYCHAIN_PROMPT,
	CSSM_ACL_SUBJECT_TYPE_PROCESS = CSSM_WORDID_PROCESS,
	CSSM_ACL_SUBJECT_TYPE_CODE_SIGNATURE = CSSM_WORDID_SIGNATURE,
	CSSM_ACL_SUBJECT_TYPE_COMMENT = CSSM_WORDID_COMMENT
};

enum
{
	CSSM_SAMPLE_TYPE_KEYCHAIN_PROMPT = CSSM_WORDID_KEYCHAIN_PROMPT,
    CSSM_SAMPLE_TYPE_KEYCHAIN_LOCK = CSSM_WORDID_KEYCHAIN_LOCK,
    CSSM_SAMPLE_TYPE_KEYCHAIN_CHANGE_LOCK = CSSM_WORDID_KEYCHAIN_CHANGE_LOCK,
	CSSM_SAMPLE_TYPE_PROCESS = CSSM_WORDID_PROCESS,
	CSSM_SAMPLE_TYPE_COMMENT = CSSM_WORDID_COMMENT,
	CSSM_SAMPLE_TYPE_RETRY_ID = CSSM_WORDID_PROPAGATE
};


/* Apple-defined ACL authorization tags */
enum {
	CSSM_ACL_AUTHORIZATION_CHANGE_ACL = CSSM_ACL_AUTHORIZATION_TAG_VENDOR_DEFINED_START,
	CSSM_ACL_AUTHORIZATION_CHANGE_OWNER
};


/* Parameters and structures for Apple-defined ACL subjects and samples */

enum {	/* types of code signatures - item 1 of CSSM_ACL_SUBJECT_TYPE_CODE_SIGNATURE subjects */
    CSSM_ACL_CODE_SIGNATURE_INVALID = 0, /* standard OS X code signature */
    CSSM_ACL_CODE_SIGNATURE_OSX = 1		/* standard OS X code signature */
};


enum {	/* PROCESS_SUBJECT mask fields */
    CSSM_ACL_MATCH_UID = 0x01,			/* match userid against uid field */
    CSSM_ACL_MATCH_GID = 0x02,			/* match groupid against gid field */
    CSSM_ACL_MATCH_HONOR_ROOT = 0x100,	/* let root (uid 0) match any userid */
    CSSM_ACL_MATCH_BITS = CSSM_ACL_MATCH_UID | CSSM_ACL_MATCH_GID
};

enum {	/* PROCESS_SUBJECT structure version field */
    CSSM_ACL_PROCESS_SELECTOR_CURRENT_VERSION = 0x101
};

typedef struct cssm_acl_process_subject_selector {	/* PROCESS_SUBJECT selector */
    uint16 version;			/* version of this selector */
    uint16 mask;			/* active fields mask */
    uid_t uid;				/* effective user id match */
    gid_t gid;				/* effective group id match */
} CSSM_ACL_PROCESS_SUBJECT_SELECTOR;


/* Apple defined algorithm IDs */
enum
{
    CSSM_ALGID_APPLE_YARROW = CSSM_ALGID_VENDOR_DEFINED,
	CSSM_ALGID_AES,				/* RijnDael */
	CSSM_ALGID_FEE,				/* FEE Key Generation */ 
	CSSM_ALGID_FEE_MD5,			/* FEE/ElGamal signature w/ MD5 hash */
	CSSM_ALGID_FEE_SHA1,		/* FEE/ElGamal signature w/ SHA1 hash */
	CSSM_ALGID_FEED,			/* 1:1 FEE asymmetric encryption */
	CSSM_ALGID_FEEDEXP,			/* 2:1 FEE asymmetric encryption */
	CSSM_ALGID_ASC,				/* Apple Secure Compression */
	CSSM_ALGID_SHA1HMAC_LEGACY,	/* HMAC/SHA1, legacy compatible */
    CSSM_ALGID__FIRST_UNUSED
};


/* Apple adds some "common" error codes. CDSA does not define an official start value for this. */
enum
{
    CSSM_CUSTOM_COMMON_ERROR_EXTENT = 0x00e0,
    
    CSSM_ERRCODE_NO_USER_INTERACTION =				0x00e0,
    CSSM_ERRCODE_USER_CANCELED =					0x00e1,
	CSSM_ERRCODE_SERVICE_NOT_AVAILABLE =			0x00e2
};

enum {
	CSSMERR_CSSM_NO_USER_INTERACTION = CSSM_CSSM_BASE_ERROR + CSSM_ERRCODE_NO_USER_INTERACTION,
	CSSMERR_AC_NO_USER_INTERACTION = CSSM_AC_BASE_ERROR + CSSM_ERRCODE_NO_USER_INTERACTION,
	CSSMERR_CSP_NO_USER_INTERACTION = CSSM_CSP_BASE_ERROR + CSSM_ERRCODE_NO_USER_INTERACTION,
	CSSMERR_CL_NO_USER_INTERACTION = CSSM_CL_BASE_ERROR + CSSM_ERRCODE_NO_USER_INTERACTION,
	CSSMERR_DL_NO_USER_INTERACTION = CSSM_DL_BASE_ERROR + CSSM_ERRCODE_NO_USER_INTERACTION,
	CSSMERR_TP_NO_USER_INTERACTION = CSSM_TP_BASE_ERROR + CSSM_ERRCODE_NO_USER_INTERACTION,
	
	CSSMERR_CSSM_USER_CANCELED = CSSM_CSSM_BASE_ERROR + CSSM_ERRCODE_USER_CANCELED,
	CSSMERR_AC_USER_CANCELED = CSSM_AC_BASE_ERROR + CSSM_ERRCODE_USER_CANCELED,
	CSSMERR_CSP_USER_CANCELED = CSSM_CSP_BASE_ERROR + CSSM_ERRCODE_USER_CANCELED,
	CSSMERR_CL_USER_CANCELED = CSSM_CL_BASE_ERROR + CSSM_ERRCODE_USER_CANCELED,
	CSSMERR_DL_USER_CANCELED = CSSM_DL_BASE_ERROR + CSSM_ERRCODE_USER_CANCELED,
	CSSMERR_TP_USER_CANCELED = CSSM_TP_BASE_ERROR + CSSM_ERRCODE_USER_CANCELED,

	CSSMERR_CSSM_SERVICE_NOT_AVAILABLE = CSSM_CSSM_BASE_ERROR + CSSM_ERRCODE_SERVICE_NOT_AVAILABLE,
	CSSMERR_AC_SERVICE_NOT_AVAILABLE = CSSM_AC_BASE_ERROR + CSSM_ERRCODE_SERVICE_NOT_AVAILABLE,
	CSSMERR_CSP_SERVICE_NOT_AVAILABLE = CSSM_CSP_BASE_ERROR + CSSM_ERRCODE_SERVICE_NOT_AVAILABLE,
	CSSMERR_CL_SERVICE_NOT_AVAILABLE = CSSM_CL_BASE_ERROR + CSSM_ERRCODE_SERVICE_NOT_AVAILABLE,
	CSSMERR_DL_SERVICE_NOT_AVAILABLE = CSSM_DL_BASE_ERROR + CSSM_ERRCODE_SERVICE_NOT_AVAILABLE,
	CSSMERR_TP_SERVICE_NOT_AVAILABLE = CSSM_TP_BASE_ERROR + CSSM_ERRCODE_SERVICE_NOT_AVAILABLE
};

/* AppleCSPDL private error codes. */
enum {
	CSSMERR_CSP_APPLE_ADD_APPLICATION_ACL_SUBJECT = CSSM_CSP_PRIVATE_ERROR + 0
};


/* AppleFileDL record types. */
enum
{
    CSSM_DL_DB_RECORD_GENERIC_PASSWORD = CSSM_DB_RECORDTYPE_APP_DEFINED_START + 0,
    CSSM_DL_DB_RECORD_INTERNET_PASSWORD = CSSM_DB_RECORDTYPE_APP_DEFINED_START + 1,
    CSSM_DL_DB_RECORD_APPLESHARE_PASSWORD = CSSM_DB_RECORDTYPE_APP_DEFINED_START + 2
};

/* AppleFileDL extentions: passthrough ids */
enum {
	// Toggle whether or not to autocommit after modifying the database.
	// The input parameter is a CSSM_BOOL, where TRUE turns autocommit on
	// and FALSE turns it off.
	CSSM_APPLEFILEDL_TOGGLE_AUTOCOMMIT,
	
	// Commit any pending changes to the database.
	CSSM_APPLEFILEDL_COMMIT,
	
	// Rollback and discard any pending changes to the database.
	CSSM_APPLEFILEDL_ROLLBACK
};

/* Apple DL private error codes. */
enum
{
	/* The OpenParameters argument passed to CSSM_DL_DbCreate or CSSM_DL_DbOpen
	   was neither NULL nor a pointer to a valid CSSM_APPLEDL_OPEN_PARAMETERS
	   structure. */
	CSSMERR_APPLEDL_INVALID_OPEN_PARAMETERS =		CSSM_DL_PRIVATE_ERROR + 0,
	
	/* an operation failed because the disk was full */
	CSSMERR_APPLEDL_DISK_FULL = 					CSSM_DL_PRIVATE_ERROR + 1,
	
	/* an operation failed because a disk quote was exceeded */
	CSSMERR_APPLEDL_QUOTA_EXCEEDED =				CSSM_DL_PRIVATE_ERROR + 2,
	
	/* an operation failed because a file was too large */
	CSSMERR_APPLEDL_FILE_TOO_BIG = 					CSSM_DL_PRIVATE_ERROR + 3,
    
    /* a keychain database's internal information ("blob") is invalid */
    CSSMERR_APPLEDL_INVALID_DATABASE_BLOB =			CSSM_DL_PRIVATE_ERROR + 4,
    CSSMERR_APPLEDL_INVALID_KEY_BLOB =				CSSM_DL_PRIVATE_ERROR + 5,
    
    /* the internal data format version for a database's internal information ("blob") is invalid */
    CSSMERR_APPLEDL_INCOMPATIBLE_DATABASE_BLOB =	CSSM_DL_PRIVATE_ERROR + 6,
    CSSMERR_APPLEDL_INCOMPATIBLE_KEY_BLOB =			CSSM_DL_PRIVATE_ERROR + 7,    
};

enum
{
	CSSM_APPLEDL_OPEN_PARAMETERS_VERSION =			0
};

/* Pass a CSSM_APPLEDL_OPEN_PARAMETERS_PTR as the OpenParameters argument to
   CSSM_DL_DbCreate or CSSM_DL_DbOpen. */
typedef struct cssm_appledl_open_parameters
{
	uint32 length;	/* Should be sizeof(CSSM_APPLEDL_OPEN_PARAMETERS). */
	uint32 version;	/* Should be CSSM_APPLEDL_OPEN_PARAMETERS_VERSION. */

	/* If no OpenParameters are specified autoCommit is on (!CSSM_FALSE) by default.
	   When autoCommit is on (!CSSM_FALSE) changes made to the Db are written to disk
	   before returning from each function.
	   When autoCommit is off (CSSM_FALSE) changes made to the database are not guaranteed
	   to be written to disk until the Db is closed.  This is useful for bulk writes.
	   Beware that if autoCommit is off changes made in previous calls to the DL might
	   get rolled back if a new modification operation fails. */
	CSSM_BOOL autoCommit;
} CSSM_APPLEDL_OPEN_PARAMETERS, *CSSM_APPLEDL_OPEN_PARAMETERS_PTR;


/* AppleCSPDL passthough ids */
enum
{
	/* Tell the SecurityServer to lock the database specified by the DLDBHandle argument.
	   The InputParams and OutputParams arguments are ignored. */
	CSSM_APPLECSPDL_DB_LOCK =			0,

	/* Tell the SecurityServer to unlock the database specified by the DLDBHandle argument.
	   The InputParameters argument is a CSSM_DATA_PTR containing the password. Or NULL if
	   the SecurityServer should prompt for the password.
	   The OutputParams argument is ignored.
	   The SecurityServer will put up UI (though the SecurityAgent) when this function is called
	   iff InputParameters is NULL.  */
	CSSM_APPLECSPDL_DB_UNLOCK =			1,

	/* Ask the SecurityServer to get the db settings specified for the database
	   specified by the DLDBHandle argument.  The settings are returned in the OutputParameters argument.
	   The OutputParameters argument is a pointer to a CSSM_APPLECSPDL_DB_SETTINGS_PARAMETERS_PTR.
	   Upon successful completion the AppleCSPDL will have allocated a
	   CSSM_APPLECSPDL_DB_SETTINGS_PARAMETERS structure using the application specified
	   allocators for the DL attachment specified by the DLDBHandle argument.  The structure will contain
	   the current database settings for the specified database.  The client should free the
	   CSSM_APPLECSPDL_DB_SETTINGS_PARAMETERS_PTR after it has finished using it.
	   The InputParameters argument is ignored.
	   The SecurityServer might put up UI (though the SecurityAgent) when this function is called.  */
	CSSM_APPLECSPDL_DB_GET_SETTINGS =	2,

	/* Tell the SecurityServer to set the db settings specified in InputParameters on the database
	   specified by the DLDBHandle argument.
	   The InputParameters argument is a const CSSM_APPLECSPDL_DB_SETTINGS_PARAMETERS * containing
	   the new settings for the specified database.
	   The OutputParams argument is ignored.
	   The SecurityServer might put up UI (though the SecurityAgent) when this function is called.  */
	CSSM_APPLECSPDL_DB_SET_SETTINGS =	3,

	/* Ask the SecurityServer whether the database specified by the DLDBHandle argument is locked.
	   The InputParameters argument is ignored.
	   The OutputParameters argument is a pointer to a CSSM_APPLECSPDL_DB_IS_LOCKED_PARAMETERS_PTR.
	   Upon successful completion the AppleCSPDL will have allocated a
	   CSSM_APPLECSPDL_DB_IS_LOCKED_PARAMETERS structure using the application specified
	   allocators for the DL attachment specified by the DLDBHandle argument.  The structure will contain
	   the current lock status for the specified database.  The client should free the
	   CSSM_APPLECSPDL_DB_IS_LOCKED_PARAMETERS_PTR after it has finished using it.
	   The SecurityServer will put up UI (though the SecurityAgent) when this function is called. */
	CSSM_APPLECSPDL_DB_IS_LOCKED =		4,

	/* Tell the SecurityServer to change the password for the database specified by
	   the DLDBHandle.

	   The InputParameters argument is a const CSSM_APPLECSPDL_DB_CHANGE_PASSWORD_PARAMETERS * containing
	   a CSSM_ACCESS_CREDENTIALS * which determines how the password will be changed.  If the
	   accessCredentials are NULL the SecurityAgent will prompt for the old and the new password for the
	   specified database.  If credentials are specified there should be 2 entries.  First a 3 element
	   list containing:
	   CSSM_WORDID_KEYCHAIN_LOCK, CSSM_SAMPLE_TYPE_PASSWORD, and the old password.
	   Second a 3 element list containing:
	   CSSM_WORDID_KEYCHAIN_CHANGE_LOCK, CSSM_SAMPLE_TYPE_PASSWORD, and the new password.

	   The OutputParams argument is ignored.
	   The SecurityServer might put up UI (though the SecurityAgent) when this function is called.  */
	CSSM_APPLECSPDL_DB_CHANGE_PASSWORD =5,

	
	/* Given a CSSM_KEY_PTR in any format, obtain the SSHA-1 hash of the 
	 * associated key blob. 
	 * Key is specified in CSSM_CSP_CreatePassThroughContext.
	 * Hash is allocated bythe CSP, in the App's memory, and returned
	 * in *outData. */
	CSSM_APPLECSP_KEYDIGEST = 			0x100	
};

/* AppleCSPDL passthough parameters */
typedef struct cssm_applecspdl_db_settings_parameters
{
	uint32 idleTimeout;				// seconds idle timeout lock
	uint8 lockOnSleep;				// lock database when system sleeps
} CSSM_APPLECSPDL_DB_SETTINGS_PARAMETERS, *CSSM_APPLECSPDL_DB_SETTINGS_PARAMETERS_PTR;

/* AppleCSPDL passthough parameters */
typedef struct cssm_applecspdl_db_is_locked_parameters
{
	uint8 isLocked;				// True iff the database is locked
} CSSM_APPLECSPDL_DB_IS_LOCKED_PARAMETERS, *CSSM_APPLECSPDL_DB_IS_LOCKED_PARAMETERS_PTR;

/* AppleCSPDL passthough parameters */
typedef struct cssm_applecspdl_db_change_password_parameters
{
	CSSM_ACCESS_CREDENTIALS *accessCredentials;
} CSSM_APPLECSPDL_DB_CHANGE_PASSWORD_PARAMETERS, *CSSM_APPLECSPDL_DB_CHANGE_PASSWORD_PARAMETERS_PTR;

/* Custom wrapped key format */
enum {
	CSSM_KEYBLOB_WRAPPED_FORMAT_APPLE_CUSTOM = 100
};

/* 
 * Optional argument for X509TP's CertGroupVerify. Instructs TP to
 * ignore "certificate expired" error conditions. Expressed in 
 * CSSM_TP_CALLERAUTH_CONTEXT.Policy.PolicyControl. 
 */
#define CSSM_TP_ALLOW_EXPIRE	((void *)0x55)

/*
 * Structure containing parameters for the MDS DbOpen() function.
 */
 
#define MDS_APPLE_OPEN_LOCAL_DB    ((uint32) (1 << 0))
#define MDS_APPLE_CREATE_LOCAL_DB  ((uint32) (1 << 1))

typedef struct mds_apple_open_parameters
{
	uint32 version;
	uint32 openFlags;
} MDS_APPLE_OPEN_PARAMETERS, *MDS_APPLE_OPEN_PARAMETERS_PTR;

/*
 * Custom context attributes for AppleCSP.
 */
enum {
	CSSM_ATTRIBUTE_VENDOR_DEFINED	= 0x800000
};

enum {
	/* 
	 * Public Key attribute for use with CSSM_ALGID_FEED.
	 */
    CSSM_ATTRIBUTE_PUBLIC_KEY =		
			(CSSM_ATTRIBUTE_DATA_KEY | (CSSM_ATTRIBUTE_VENDOR_DEFINED + 0)),
			
	/*
	 * FEE key attributes.
	 * See CSSM_FEE_PRIME_TYPE_xxx, CSSM_FEE_CURVE_TYPE_xxx enumsm below.
	 */
	CSSM_ATTRIBUTE_FEE_PRIME_TYPE = 
			(CSSM_ATTRIBUTE_DATA_UINT32 | (CSSM_ATTRIBUTE_VENDOR_DEFINED + 1)),
	CSSM_ATTRIBUTE_FEE_CURVE_TYPE = 
			(CSSM_ATTRIBUTE_DATA_UINT32 | (CSSM_ATTRIBUTE_VENDOR_DEFINED + 2)),
};

/*
 * FEE key pair prime modulus types.
 */
enum {
	CSSM_FEE_PRIME_TYPE_DEFAULT,		/* default per key size */
	CSSM_FEE_PRIME_TYPE_MERSENNE,		/* (2 ** q) - 1Ê*/
	CSSM_FEE_PRIME_TYPE_FEE,			/* (2 ** q) - k */
	CSSM_FEE_PRIME_TYPE_GENERAL			/* random prime */
};

/*
 * FEE curve types. Comments refer to equation
 *
 *    y**2 = x**3 + c(x**2) + ax + b
 */
enum {
	CSSM_FEE_CURVE_TYPE_DEFAULT,		/* default per key size */
	CSSM_FEE_CURVE_TYPE_MONTGOMERY,		/* a==1, b==0 */
	CSSM_FEE_CURVE_TYPE_WEIERSTRASS		/* c==0. IEEE P1363 compliant. */
};

#ifdef __cplusplus
}
#endif

#endif /* _CSSMAPPLE_H_ */
