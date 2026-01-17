/* $OpenLDAP: pkg/ldap/include/ldap.h,v 1.168.2.16 2003/03/05 23:48:31 kurt Exp $ */
/*
 * Copyright 1998-2003 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.  A copy of this license is available at
 * http://www.OpenLDAP.org/license.html or in file LICENSE in the
 * top-level directory of the distribution.
 */
/* Portions
 * Copyright (c) 1990 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 */

#ifndef _LDAP_H
#define _LDAP_H

/* pull in lber */
#include <lber.h>

/* include version and API feature defines */
#include <ldap_features.h>

LDAP_BEGIN_DECL

#define LDAP_VERSION1	1
#define LDAP_VERSION2	2
#define LDAP_VERSION3	3

#define LDAP_VERSION_MIN	LDAP_VERSION2
#define	LDAP_VERSION		LDAP_VERSION2
#define LDAP_VERSION_MAX	LDAP_VERSION3

/*
 * We'll use 2000+draft revision for our API version number
 * As such, the number will be above the old RFC but below
 * whatever number does finally get assigned
 */
#define LDAP_API_VERSION	2004
#define LDAP_VENDOR_NAME	"OpenLDAP"

/* OpenLDAP API Features */
#define LDAP_API_FEATURE_X_OPENLDAP LDAP_VENDOR_VERSION

#if defined( LDAP_API_FEATURE_X_OPENLDAP_REENTRANT ) || \
	( defined( LDAP_THREAD_SAFE ) && \
		defined( LDAP_API_FEATURE_X_OPENLDAP_THREAD_SAFE ) )
	/* -lldap may or may not be thread safe */
	/* -lldap_r, if available, is always thread safe */
#	define	LDAP_API_FEATURE_THREAD_SAFE 1
#endif
#if defined( LDAP_THREAD_SAFE ) && \
	defined( LDAP_API_FEATURE_X_OPENLDAP_THREAD_SAFE )
/* #define LDAP_API_FEATURE_SESSION_SAFE	1	*/
/* #define LDAP_API_OPERATION_SESSION_SAFE	1	*/
#endif

#define LDAP_PORT		389		/* ldap:///		default LDAP port */
#define LDAPS_PORT		636		/* ldaps:///	default LDAP over TLS port */

#define LDAP_ROOT_DSE				""
#define LDAP_NO_ATTRS				"1.1"
#define LDAP_ALL_USER_ATTRIBUTES	"*"
#define LDAP_ALL_OPERATIONAL_ATTRIBUTES	"+" /* OpenLDAP extension */

/*
 * LDAP_OPTions defined by draft-ldapext-ldap-c-api-02
 * 0x0000 - 0x0fff reserved for api options
 * 0x1000 - 0x3fff reserved for api extended options
 * 0x4000 - 0x7fff reserved for private and experimental options
 */
#define LDAP_OPT_API_INFO			0x0000
#define LDAP_OPT_DESC				0x0001 /* deprecated */
#define LDAP_OPT_DEREF				0x0002
#define LDAP_OPT_SIZELIMIT			0x0003
#define LDAP_OPT_TIMELIMIT			0x0004
/* 0x05 - 0x07 not defined by current draft */
#define LDAP_OPT_REFERRALS			0x0008
#define LDAP_OPT_RESTART			0x0009
/* 0x0a - 0x10 not defined by current draft */
#define LDAP_OPT_PROTOCOL_VERSION	0x0011
#define LDAP_OPT_SERVER_CONTROLS	0x0012
#define LDAP_OPT_CLIENT_CONTROLS	0x0013
/* 0x14 not defined by current draft */
#define LDAP_OPT_API_FEATURE_INFO	0x0015

/* 0x16 - 0x2f not defined by current draft */
#define LDAP_OPT_HOST_NAME			0x0030
#define	LDAP_OPT_ERROR_NUMBER		0x0031
#define LDAP_OPT_ERROR_STRING		0x0032
#define LDAP_OPT_MATCHED_DN			0x0033

/* 0x34 - 0x0fff not defined by current draft */

#define LDAP_OPT_PRIVATE_EXTENSION_BASE 0x4000  /* to 0x7FFF inclusive */

/* private and experimental options */
/* OpenLDAP specific options */
#define LDAP_OPT_DEBUG_LEVEL		0x5001	/* debug level */
#define LDAP_OPT_TIMEOUT			0x5002	/* default timeout */
#define LDAP_OPT_REFHOPLIMIT		0x5003	/* ref hop limit */
#define LDAP_OPT_NETWORK_TIMEOUT	0x5005	/* socket level timeout */
#define LDAP_OPT_URI				0x5006
#define LDAP_OPT_REFERRAL_URLS      0x5007  /* Referral URLs */

/* OpenLDAP TLS options */
#define LDAP_OPT_X_TLS				0x6000
#define LDAP_OPT_X_TLS_CTX			0x6001	/* SSL CTX */
#define LDAP_OPT_X_TLS_CACERTFILE	0x6002
#define LDAP_OPT_X_TLS_CACERTDIR	0x6003
#define LDAP_OPT_X_TLS_CERTFILE		0x6004
#define LDAP_OPT_X_TLS_KEYFILE		0x6005
#define LDAP_OPT_X_TLS_REQUIRE_CERT	0x6006
/* #define LDAP_OPT_X_TLS_PROTOCOL		0x6007 */
#define LDAP_OPT_X_TLS_CIPHER_SUITE	0x6008
#define LDAP_OPT_X_TLS_RANDOM_FILE	0x6009
#define LDAP_OPT_X_TLS_SSL_CTX		0x600a

#define LDAP_OPT_X_TLS_NEVER		0
#define LDAP_OPT_X_TLS_HARD		1
#define LDAP_OPT_X_TLS_DEMAND		2
#define LDAP_OPT_X_TLS_ALLOW		3
#define LDAP_OPT_X_TLS_TRY		4

/* OpenLDAP SASL options */
#define LDAP_OPT_X_SASL_MECH			0x6100
#define LDAP_OPT_X_SASL_REALM			0x6101
#define LDAP_OPT_X_SASL_AUTHCID			0x6102
#define LDAP_OPT_X_SASL_AUTHZID			0x6103
#define LDAP_OPT_X_SASL_SSF				0x6104 /* read-only */
#define LDAP_OPT_X_SASL_SSF_EXTERNAL	0x6105 /* write-only */
#define LDAP_OPT_X_SASL_SECPROPS		0x6106 /* write-only */
#define LDAP_OPT_X_SASL_SSF_MIN			0x6107
#define LDAP_OPT_X_SASL_SSF_MAX			0x6108
#define	LDAP_OPT_X_SASL_MAXBUFSIZE		0x6109

/* on/off values */
#define LDAP_OPT_ON		((void *) 1)
#define LDAP_OPT_OFF	((void *) 0)

/*
 * ldap_get_option() and ldap_set_option() return values.
 * As later versions may return other values indicating
 * failure, current applications should only compare returned
 * value against LDAP_OPT_SUCCESS.
 */
#define LDAP_OPT_SUCCESS	0
#define	LDAP_OPT_ERROR		(-1)

#define LDAP_API_INFO_VERSION	(1)
typedef struct ldapapiinfo {
	int		ldapai_info_version;		/* version of LDAPAPIInfo (1) */
	int		ldapai_api_version;			/* revision of API supported */
	int		ldapai_protocol_version;	/* highest LDAP version supported */
	char	**ldapai_extensions;		/* names of API extensions */
	char	*ldapai_vendor_name;		/* name of supplier */
	int		ldapai_vendor_version;		/* supplier-specific version * 100 */
} LDAPAPIInfo;

#define LDAP_FEATURE_INFO_VERSION (1) /* version of api feature structure */
typedef struct ldap_apifeature_info {
	int		ldapaif_info_version; /* version of this struct (1) */
	char*	ldapaif_name;    /* matches LDAP_API_FEATURE_... less the prefix */
	int		ldapaif_version; /* matches the value LDAP_API_FEATURE_... */
} LDAPAPIFeatureInfo;

typedef struct ldapcontrol {
	char *			ldctl_oid;
	struct berval	ldctl_value;
	char			ldctl_iscritical;
} LDAPControl;


/* LDAP Controls */
#define LDAP_CONTROL_VALUESRETURNFILTER "1.2.826.0.1.334810.2.3"
#define LDAP_CONTROL_SUBENTRIES		"1.3.6.1.4.1.4203.1.10.1"
#define LDAP_CONTROL_NOOP			"1.3.6.1.4.1.4203.1.10.2"
#define LDAP_CONTROL_MANAGEDSAIT	"2.16.840.1.113730.3.4.2"
#define LDAP_CONTROL_PROXY_AUTHZ	"2.16.840.1.113730.3.4.18"

#define LDAP_CONTROL_SORTREQUEST    "1.2.840.113556.1.4.473"
#define LDAP_CONTROL_SORTRESPONSE	"1.2.840.113556.1.4.474"
#define LDAP_CONTROL_VLVREQUEST    	"2.16.840.1.113730.3.4.9"
#define LDAP_CONTROL_VLVRESPONSE    "2.16.840.1.113730.3.4.10"


/* LDAP Unsolicited Notifications */
#define	LDAP_NOTICE_OF_DISCONNECTION	"1.3.6.1.4.1.1466.20036"
#define LDAP_NOTICE_DISCONNECT LDAP_NOTICE_OF_DISCONNECTION


/* LDAP Extended Operations */
#define LDAP_EXOP_START_TLS	"1.3.6.1.4.1.1466.20037"

#define LDAP_EXOP_MODIFY_PASSWD	"1.3.6.1.4.1.4203.1.11.1"
#define LDAP_TAG_EXOP_MODIFY_PASSWD_ID	((ber_tag_t) 0x80U)
#define LDAP_TAG_EXOP_MODIFY_PASSWD_OLD	((ber_tag_t) 0x81U)
#define LDAP_TAG_EXOP_MODIFY_PASSWD_NEW	((ber_tag_t) 0x82U)
#define LDAP_TAG_EXOP_MODIFY_PASSWD_GEN	((ber_tag_t) 0x80U)

#define LDAP_EXOP_X_WHO_AM_I	"1.3.6.1.4.1.4203.1.11.3"


/* LDAP Features */
#define LDAP_FEATURE_ALL_OPERATIONAL_ATTRS "1.3.6.1.4.1.4203.1.5.1"  /* + */
#define LDAP_FEATURE_OBJECTCLASS_ATTRS "1.3.6.1.4.1.4203.1.5.2"
#define LDAP_FEATURE_ABSOLUTE_FILTERS "1.3.6.1.4.1.4203.1.5.3"  /* (&) (|) */
#define LDAP_FEATURE_LANGUAGE_TAG_OPTIONS "1.3.6.1.4.1.4203.1.5.4"
#define LDAP_FEATURE_LANGUAGE_RANGE_OPTIONS "1.3.6.1.4.1.4203.1.5.5"

/*
 * specific LDAP instantiations of BER types we know about
 */

/* Overview of LBER tag construction
 *
 *	Bits
 *	______
 *	8 7 | CLASS
 *	0 0 = UNIVERSAL
 *	0 1 = APPLICATION
 *	1 0 = CONTEXT-SPECIFIC
 *	1 1 = PRIVATE
 *		_____
 *		| 6 | DATA-TYPE
 *		  0 = PRIMITIVE
 *		  1 = CONSTRUCTED
 *			___________
 *			| 5 ... 1 | TAG-NUMBER
 */

/* general stuff */
#define LDAP_TAG_MESSAGE	((ber_tag_t) 0x30U)	/* constructed + 16 */
#define LDAP_TAG_MSGID		((ber_tag_t) 0x02U)	/* integer */

#define LDAP_TAG_LDAPDN		((ber_tag_t) 0x04U)	/* octet string */
#define LDAP_TAG_LDAPCRED	((ber_tag_t) 0x04U)	/* octet string */

#define LDAP_TAG_CONTROLS	((ber_tag_t) 0xa0U)	/* context specific + constructed + 0 */
#define LDAP_TAG_REFERRAL	((ber_tag_t) 0xa3U)	/* context specific + constructed + 3 */

#define LDAP_TAG_NEWSUPERIOR	((ber_tag_t) 0x80U)	/* context-specific + primitive + 0 */

#define LDAP_TAG_EXOP_REQ_OID   ((ber_tag_t) 0x80U)	/* context specific + primitive */
#define LDAP_TAG_EXOP_REQ_VALUE ((ber_tag_t) 0x81U)	/* context specific + primitive */
#define LDAP_TAG_EXOP_RES_OID   ((ber_tag_t) 0x8aU)	/* context specific + primitive */
#define LDAP_TAG_EXOP_RES_VALUE ((ber_tag_t) 0x8bU)	/* context specific + primitive */

#define LDAP_TAG_SASL_RES_CREDS	((ber_tag_t) 0x87U)	/* context specific + primitive */


/* possible operations a client can invoke */
#define LDAP_REQ_BIND		((ber_tag_t) 0x60U)	/* application + constructed */
#define LDAP_REQ_UNBIND		((ber_tag_t) 0x42U)	/* application + primitive   */
#define LDAP_REQ_SEARCH		((ber_tag_t) 0x63U)	/* application + constructed */
#define LDAP_REQ_MODIFY		((ber_tag_t) 0x66U)	/* application + constructed */
#define LDAP_REQ_ADD		((ber_tag_t) 0x68U)	/* application + constructed */
#define LDAP_REQ_DELETE		((ber_tag_t) 0x4aU)	/* application + primitive   */
#define LDAP_REQ_MODDN		((ber_tag_t) 0x6cU)	/* application + constructed */
#define LDAP_REQ_MODRDN		LDAP_REQ_MODDN
#define LDAP_REQ_RENAME		LDAP_REQ_MODDN
#define LDAP_REQ_COMPARE	((ber_tag_t) 0x6eU)	/* application + constructed */
#define LDAP_REQ_ABANDON	((ber_tag_t) 0x50U)	/* application + primitive   */
#define LDAP_REQ_EXTENDED	((ber_tag_t) 0x77U)	/* application + constructed */

/* possible result types a server can return */
#define LDAP_RES_BIND		((ber_tag_t) 0x61U)	/* application + constructed */
#define LDAP_RES_SEARCH_ENTRY	((ber_tag_t) 0x64U)	/* application + constructed */
#define LDAP_RES_SEARCH_REFERENCE	((ber_tag_t) 0x73U)	/* V3: application + constructed */
#define LDAP_RES_SEARCH_RESULT	((ber_tag_t) 0x65U)	/* application + constructed */
#define LDAP_RES_MODIFY		((ber_tag_t) 0x67U)	/* application + constructed */
#define LDAP_RES_ADD		((ber_tag_t) 0x69U)	/* application + constructed */
#define LDAP_RES_DELETE		((ber_tag_t) 0x6bU)	/* application + constructed */
#define LDAP_RES_MODDN		((ber_tag_t) 0x6dU)	/* application + constructed */
#define LDAP_RES_MODRDN		LDAP_RES_MODDN	/* application + constructed */
#define LDAP_RES_RENAME		LDAP_RES_MODDN	/* application + constructed */
#define LDAP_RES_COMPARE	((ber_tag_t) 0x6fU)	/* application + constructed */
#define LDAP_RES_EXTENDED	((ber_tag_t) 0x78U)	/* V3: application + constructed */
#define LDAP_RES_EXTENDED_PARTIAL	((ber_tag_t) 0x79U)	/* V3+: application + constructed */

#define LDAP_RES_ANY			(-1)
#define LDAP_RES_UNSOLICITED	(0)


/* sasl methods */
#define LDAP_SASL_SIMPLE	((char*)0)
#define LDAP_SASL_NULL		("")


/* authentication methods available */
#define LDAP_AUTH_NONE	((ber_tag_t) 0x00U)	/* no authentication		  */
#define LDAP_AUTH_SIMPLE	((ber_tag_t) 0x80U)	/* context specific + primitive */
#define LDAP_AUTH_SASL	((ber_tag_t) 0xa3U)	/* context specific + constructed */
#define LDAP_AUTH_KRBV4	((ber_tag_t) 0xffU)	/* means do both of the following */
#define LDAP_AUTH_KRBV41	((ber_tag_t) 0x81U)	/* context specific + primitive */
#define LDAP_AUTH_KRBV42	((ber_tag_t) 0x82U)	/* context specific + primitive */


/* filter types */
#define LDAP_FILTER_AND	((ber_tag_t) 0xa0U)	/* context specific + constructed */
#define LDAP_FILTER_OR	((ber_tag_t) 0xa1U)	/* context specific + constructed */
#define LDAP_FILTER_NOT	((ber_tag_t) 0xa2U)	/* context specific + constructed */
#define LDAP_FILTER_EQUALITY	((ber_tag_t) 0xa3U)	/* context specific + constructed */
#define LDAP_FILTER_SUBSTRINGS	((ber_tag_t) 0xa4U)	/* context specific + constructed */
#define LDAP_FILTER_GE	((ber_tag_t) 0xa5U)	/* context specific + constructed */
#define LDAP_FILTER_LE	((ber_tag_t) 0xa6U)	/* context specific + constructed */
#define LDAP_FILTER_PRESENT	((ber_tag_t) 0x87U)	/* context specific + primitive   */
#define LDAP_FILTER_APPROX	((ber_tag_t) 0xa8U)	/* context specific + constructed */
#define LDAP_FILTER_EXT	((ber_tag_t) 0xa9U)	/* context specific + constructed */

/* extended filter component types */
#define LDAP_FILTER_EXT_OID		((ber_tag_t) 0x81U)	/* context specific */
#define LDAP_FILTER_EXT_TYPE	((ber_tag_t) 0x82U)	/* context specific */
#define LDAP_FILTER_EXT_VALUE	((ber_tag_t) 0x83U)	/* context specific */
#define LDAP_FILTER_EXT_DNATTRS	((ber_tag_t) 0x84U)	/* context specific */

/* substring filter component types */
#define LDAP_SUBSTRING_INITIAL	((ber_tag_t) 0x80U)	/* context specific */
#define LDAP_SUBSTRING_ANY		((ber_tag_t) 0x81U)	/* context specific */
#define LDAP_SUBSTRING_FINAL	((ber_tag_t) 0x82U)	/* context specific */

/* search scopes */
#define LDAP_SCOPE_DEFAULT	((ber_int_t) -1)
#define LDAP_SCOPE_BASE		((ber_int_t) 0x0000)
#define LDAP_SCOPE_ONELEVEL	((ber_int_t) 0x0001)
#define LDAP_SCOPE_SUBTREE	((ber_int_t) 0x0002)

/* substring filter component types */
#define LDAP_SUBSTRING_INITIAL	((ber_tag_t) 0x80U)	/* context specific */
#define LDAP_SUBSTRING_ANY		((ber_tag_t) 0x81U)	/* context specific */
#define LDAP_SUBSTRING_FINAL	((ber_tag_t) 0x82U)	/* context specific */

/*
 * possible error codes we can return
 */

#define LDAP_RANGE(n,x,y)	(((x) <= (n)) && ((n) <= (y)))

#define LDAP_SUCCESS				0x00
#define LDAP_OPERATIONS_ERROR		0x01
#define LDAP_PROTOCOL_ERROR			0x02
#define LDAP_TIMELIMIT_EXCEEDED		0x03
#define LDAP_SIZELIMIT_EXCEEDED		0x04
#define LDAP_COMPARE_FALSE			0x05
#define LDAP_COMPARE_TRUE			0x06
#define LDAP_AUTH_METHOD_NOT_SUPPORTED	0x07
#define LDAP_STRONG_AUTH_NOT_SUPPORTED	LDAP_AUTH_METHOD_NOT_SUPPORTED
#define LDAP_STRONG_AUTH_REQUIRED	0x08
#define LDAP_PARTIAL_RESULTS		0x09	/* LDAPv2+ (not LDAPv3) */

#define	LDAP_REFERRAL				0x0a /* LDAPv3 */
#define LDAP_ADMINLIMIT_EXCEEDED	0x0b /* LDAPv3 */
#define	LDAP_UNAVAILABLE_CRITICAL_EXTENSION	0x0c /* LDAPv3 */
#define LDAP_CONFIDENTIALITY_REQUIRED	0x0d /* LDAPv3 */
#define	LDAP_SASL_BIND_IN_PROGRESS	0x0e /* LDAPv3 */

#define LDAP_ATTR_ERROR(n)	LDAP_RANGE((n),0x10,0x15) /* 16-21 */

#define LDAP_NO_SUCH_ATTRIBUTE		0x10
#define LDAP_UNDEFINED_TYPE			0x11
#define LDAP_INAPPROPRIATE_MATCHING	0x12
#define LDAP_CONSTRAINT_VIOLATION	0x13
#define LDAP_TYPE_OR_VALUE_EXISTS	0x14
#define LDAP_INVALID_SYNTAX			0x15

#define LDAP_NAME_ERROR(n)	LDAP_RANGE((n),0x20,0x24) /* 32-34,36 */

#define LDAP_NO_SUCH_OBJECT			0x20
#define LDAP_ALIAS_PROBLEM			0x21
#define LDAP_INVALID_DN_SYNTAX		0x22
#define LDAP_IS_LEAF				0x23 /* not LDAPv3 */
#define LDAP_ALIAS_DEREF_PROBLEM	0x24

#define LDAP_SECURITY_ERROR(n)	LDAP_RANGE((n),0x2F,0x32) /* 47-50 */

#define LDAP_PROXY_AUTHZ_FAILURE	0x2F /* LDAPv3 proxy authorization */
#define LDAP_INAPPROPRIATE_AUTH		0x30
#define LDAP_INVALID_CREDENTIALS	0x31
#define LDAP_INSUFFICIENT_ACCESS	0x32

#define LDAP_SERVICE_ERROR(n)	LDAP_RANGE((n),0x33,0x36) /* 51-54 */

#define LDAP_BUSY					0x33
#define LDAP_UNAVAILABLE			0x34
#define LDAP_UNWILLING_TO_PERFORM	0x35
#define LDAP_LOOP_DETECT			0x36

#define LDAP_UPDATE_ERROR(n)	LDAP_RANGE((n),0x40,0x47) /* 64-69,71 */

#define LDAP_NAMING_VIOLATION		0x40
#define LDAP_OBJECT_CLASS_VIOLATION	0x41
#define LDAP_NOT_ALLOWED_ON_NONLEAF	0x42
#define LDAP_NOT_ALLOWED_ON_RDN		0x43
#define LDAP_ALREADY_EXISTS			0x44
#define LDAP_NO_OBJECT_CLASS_MODS	0x45
#define LDAP_RESULTS_TOO_LARGE		0x46 /* CLDAP */
#define LDAP_AFFECTS_MULTIPLE_DSAS	0x47 /* LDAPv3 */

#define LDAP_OTHER				0x50

#define LDAP_API_ERROR(n)		LDAP_RANGE((n),0x51,0x61) /* 81-97 */
#define LDAP_API_RESULT(n)		(((n) == LDAP_SUCCESS) || \
								LDAP_RANGE((n),0x51,0x61)) /* 0,81-97 */

/* reserved for APIs */
#define LDAP_SERVER_DOWN		0x51
#define LDAP_LOCAL_ERROR		0x52
#define LDAP_ENCODING_ERROR		0x53
#define LDAP_DECODING_ERROR		0x54
#define LDAP_TIMEOUT			0x55
#define LDAP_AUTH_UNKNOWN		0x56
#define LDAP_FILTER_ERROR		0x57
#define LDAP_USER_CANCELLED		0x58
#define LDAP_PARAM_ERROR		0x59
#define LDAP_NO_MEMORY			0x5a

/* used but not reserved for APIs */
#define LDAP_CONNECT_ERROR				0x5b	/* draft-ietf-ldap-c-api-xx */
#define LDAP_NOT_SUPPORTED				0x5c	/* draft-ietf-ldap-c-api-xx */
#define LDAP_CONTROL_NOT_FOUND			0x5d	/* draft-ietf-ldap-c-api-xx */
#define LDAP_NO_RESULTS_RETURNED		0x5e	/* draft-ietf-ldap-c-api-xx */
#define LDAP_MORE_RESULTS_TO_RETURN		0x5f	/* draft-ietf-ldap-c-api-xx */
#define LDAP_CLIENT_LOOP				0x60	/* draft-ietf-ldap-c-api-xx */
#define LDAP_REFERRAL_LIMIT_EXCEEDED	0x61	/* draft-ietf-ldap-c-api-xx */

/*
 * This structure represents both ldap messages and ldap responses.
 * These are really the same, except in the case of search responses,
 * where a response has multiple messages.
 */

typedef struct ldapmsg LDAPMessage;

/* for modifications */
typedef struct ldapmod {
	int		mod_op;

#define LDAP_MOD_ADD		(0x0000)
#define LDAP_MOD_DELETE		(0x0001)
#define LDAP_MOD_REPLACE	(0x0002)
#define LDAP_MOD_BVALUES	(0x0080)
/* IMPORTANT: do not use code 0x1000 (or above),
 * it is used internally by the backends!
 * (see ldap/servers/slapd/slap.h)
 */

	char		*mod_type;
	union mod_vals_u {
		char		**modv_strvals;
		struct berval	**modv_bvals;
	} mod_vals;
#define mod_values	mod_vals.modv_strvals
#define mod_bvalues	mod_vals.modv_bvals
} LDAPMod;

/*
 * structure representing an ldap session which can
 * encompass connections to multiple servers (in the
 * face of referrals).
 */
typedef struct ldap LDAP;

#define LDAP_DEREF_NEVER		0x00
#define LDAP_DEREF_SEARCHING	0x01
#define LDAP_DEREF_FINDING		0x02
#define LDAP_DEREF_ALWAYS		0x03

#define LDAP_NO_LIMIT			0

/* how many messages to retrieve results for */
#define LDAP_MSG_ONE			0x00
#define LDAP_MSG_ALL			0x01
#define LDAP_MSG_RECEIVED		0x02

/*
 * types for ldap URL handling
 */
typedef struct ldap_url_desc {
	struct ldap_url_desc *lud_next;
	char	*lud_scheme;
	char	*lud_host;
	int		lud_port;
	char	*lud_dn;
	char	**lud_attrs;
	int		lud_scope;
	char	*lud_filter;
	char	**lud_exts;
	int		lud_crit_exts;
} LDAPURLDesc;

#define LDAP_URL_SUCCESS		0x00	/* Success */
#define LDAP_URL_ERR_MEM		0x01	/* can't allocate memory space */
#define LDAP_URL_ERR_PARAM		0x02	/* parameter is bad */

#define LDAP_URL_ERR_BADSCHEME	0x03	/* URL doesn't begin with "ldap[si]://" */
#define LDAP_URL_ERR_BADENCLOSURE 0x04	/* URL is missing trailing ">" */
#define LDAP_URL_ERR_BADURL		0x05	/* URL is bad */
#define LDAP_URL_ERR_BADHOST	0x06	/* host port is bad */
#define LDAP_URL_ERR_BADATTRS	0x07	/* bad (or missing) attributes */
#define LDAP_URL_ERR_BADSCOPE	0x08	/* scope string is invalid (or missing) */
#define LDAP_URL_ERR_BADFILTER	0x09	/* bad or missing filter */
#define LDAP_URL_ERR_BADEXTS	0x0a	/* bad or missing extensions */

/*
 * The API draft spec says we should declare (or cause to be declared)
 * 'struct timeval'.   We don't.  See IETF LDAPext discussions.
 */
struct timeval;

/*
 * in options.c:
 */
LDAP_F( int )
ldap_get_option LDAP_P((
	LDAP *ld,
	int option,
	void *outvalue));

LDAP_F( int )
ldap_set_option LDAP_P((
	LDAP *ld,
	int option,
	LDAP_CONST void *invalue));

/* V3 REBIND Function Callback Prototype */
typedef int (LDAP_REBIND_PROC) LDAP_P((
	LDAP *ld, LDAP_CONST char *url,
	ber_tag_t request, ber_int_t msgid,
	void *params ));

LDAP_F( int )
ldap_set_rebind_proc LDAP_P((
	LDAP *ld,
	LDAP_REBIND_PROC *rebind_proc,
	void *params ));

/*
 * in controls.c:
 */
LDAP_F( int )
ldap_create_control LDAP_P((
	LDAP_CONST char *requestOID,
	BerElement *ber,
	int iscritical,
	LDAPControl **ctrlp ));

LDAP_F( void )
ldap_control_free LDAP_P((
	LDAPControl *ctrl ));

LDAP_F( void )
ldap_controls_free LDAP_P((
	LDAPControl **ctrls ));

/*
 * in dnssrv.c:
 */
LDAP_F( int )
ldap_domain2dn LDAP_P((
	LDAP_CONST char* domain,
	char** dn ));

LDAP_F( int )
ldap_dn2domain LDAP_P((
	LDAP_CONST char* dn,
	char** domain ));

LDAP_F( int )
ldap_domain2hostlist LDAP_P((
	LDAP_CONST char *domain,
	char** hostlist ));

/*
 * in extended.c:
 */
LDAP_F( int )
ldap_extended_operation LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*reqoid,
	struct berval	*reqdata,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int				*msgidp ));

LDAP_F( int )
ldap_extended_operation_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*reqoid,
	struct berval	*reqdata,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	char			**retoidp,
	struct berval	**retdatap ));

LDAP_F( int )
ldap_parse_extended_result LDAP_P((
	LDAP			*ld,
	LDAPMessage		*res,
	char			**retoidp,
	struct berval	**retdatap,
	int				freeit ));

LDAP_F( int )
ldap_parse_extended_partial LDAP_P((
	LDAP			*ld,
	LDAPMessage		*res,
	char			**retoidp,
	struct berval	**retdatap,
	LDAPControl		***serverctrls,
	int				freeit ));

LDAP_F( int )
ldap_parse_intermediate_resp_result LDAP_P((
	LDAP                    *ld,
	LDAPMessage             *res,
	char                    **retoidp,
	struct berval   **retdatap,
	int                             freeit ));

/*
 * in abandon.c:
 */
LDAP_F( int )
ldap_abandon_ext LDAP_P((
	LDAP			*ld,
	int				msgid,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls ));

LDAP_F( int )
ldap_abandon LDAP_P((	/* deprecated */
	LDAP *ld,
	int msgid ));


/*
 * in add.c:
 */
LDAP_F( int )
ldap_add_ext LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAPMod			**attrs,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int 			*msgidp ));

LDAP_F( int )
ldap_add_ext_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAPMod			**attrs,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls ));

LDAP_F( int )
ldap_add LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAPMod **attrs ));

LDAP_F( int )
ldap_add_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAPMod **attrs ));


/*
 * in sasl.c:
 */
LDAP_F( int )
ldap_sasl_bind LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAP_CONST char	*mechanism,
	struct berval	*cred,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int				*msgidp ));

/* Interaction flags (should be passed about in a control)
 *  Automatic (default): use defaults, prompt otherwise
 *  Interactive: prompt always
 *  Quiet: never prompt
 */
#define LDAP_SASL_AUTOMATIC		0U
#define LDAP_SASL_INTERACTIVE	1U
#define LDAP_SASL_QUIET			2U

/*
 * V3 SASL Interaction Function Callback Prototype
 *	when using Cyrus SASL, interact is pointer to sasl_interact_t
 *  should likely passed in a control (and provided controls)
 */
typedef int (LDAP_SASL_INTERACT_PROC) LDAP_P((
	LDAP *ld, unsigned flags, void* defaults, void *interact ));

LDAP_F( int )
ldap_sasl_interactive_bind_s LDAP_P((
	LDAP *ld,
	LDAP_CONST char *dn, /* usually NULL */
	LDAP_CONST char *saslMechanism,
	LDAPControl **serverControls,
	LDAPControl **clientControls,

	/* should be client controls */
	unsigned flags,
	LDAP_SASL_INTERACT_PROC *proc,
	void *defaults ));

LDAP_F( int )
ldap_sasl_bind_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAP_CONST char	*mechanism,
	struct berval	*cred,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	struct berval	**servercredp ));

LDAP_F( int )
ldap_parse_sasl_bind_result LDAP_P((
	LDAP			*ld,
	LDAPMessage		*res,
	struct berval	**servercredp,
	int				freeit ));

/*
 * in bind.c:
 *	(deprecated)
 */
LDAP_F( int )
ldap_bind LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who,
	LDAP_CONST char *passwd,
	int authmethod ));

LDAP_F( int )
ldap_bind_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who,
	LDAP_CONST char *cred,
	int authmethod ));

/*
 * in sbind.c:
 */
LDAP_F( int )
ldap_simple_bind LDAP_P((
	LDAP *ld,
	LDAP_CONST char *who,
	LDAP_CONST char *passwd ));

LDAP_F( int )
ldap_simple_bind_s LDAP_P((
	LDAP *ld,
	LDAP_CONST char *who,
	LDAP_CONST char *passwd ));


/*
 * in kbind.c:
 *	(deprecated)
 */
LDAP_F( int )
ldap_kerberos_bind_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who ));

LDAP_F( int )
ldap_kerberos_bind1 LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who ));

LDAP_F( int )
ldap_kerberos_bind1_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who ));

LDAP_F( int )
ldap_kerberos_bind2 LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who ));

LDAP_F( int )
ldap_kerberos_bind2_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *who ));


/*
 * LDAP Cancel Extended Operation <draft-zeilenga-ldap-cancel-xx.txt>
 */

LDAP_F( int )
ldap_cancel LDAP_P(( LDAP *ld,
	int cancelid,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp ));

LDAP_F( int )
ldap_cancel_s LDAP_P((
	LDAP *ld,
	int cancelid,
	LDAPControl **sctrl,
	LDAPControl **cctrl ));

/*
 * in compare.c:
 */
LDAP_F( int )
ldap_compare_ext LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAP_CONST char	*attr,
	struct berval	*bvalue,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int 			*msgidp ));

LDAP_F( int )
ldap_compare_ext_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAP_CONST char	*attr,
	struct berval	*bvalue,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls ));

LDAP_F( int )
ldap_compare LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *attr,
	LDAP_CONST char *value ));

LDAP_F( int )
ldap_compare_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *attr,
	LDAP_CONST char *value ));


/*
 * in delete.c:
 */
LDAP_F( int )
ldap_delete_ext LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int 			*msgidp ));

LDAP_F( int )
ldap_delete_ext_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls ));

LDAP_F( int )
ldap_delete LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn ));

LDAP_F( int )
ldap_delete_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn ));


/*
 * in error.c:
 */
LDAP_F( int )
ldap_parse_result LDAP_P((
	LDAP			*ld,
	LDAPMessage		*res,
	int				*errcodep,
	char			**matcheddnp,
	char			**errmsgp,
	char			***referralsp,
	LDAPControl		***serverctrls,
	int				freeit ));

LDAP_F( char * )
ldap_err2string LDAP_P((
	int err ));

LDAP_F( int )
ldap_result2error LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAPMessage *r,
	int freeit ));

LDAP_F( void )
ldap_perror LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *s ));


/*
 * in modify.c:
 */
LDAP_F( int )
ldap_modify_ext LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAPMod			**mods,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	int 			*msgidp ));

LDAP_F( int )
ldap_modify_ext_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*dn,
	LDAPMod			**mods,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls ));

LDAP_F( int )
ldap_modify LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAPMod **mods ));

LDAP_F( int )
ldap_modify_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAPMod **mods ));


/*
 * in modrdn.c:
 */
LDAP_F( int )
ldap_rename LDAP_P((
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn,
	LDAP_CONST char *newSuperior,
	int deleteoldrdn,
	LDAPControl **sctrls,
	LDAPControl **cctrls,
	int *msgidp ));

LDAP_F( int )
ldap_rename_s LDAP_P((
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn,
	LDAP_CONST char *newSuperior,
	int deleteoldrdn,
	LDAPControl **sctrls,
	LDAPControl **cctrls ));

LDAP_F( int )
ldap_rename2 LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn,
	LDAP_CONST char *newSuperior,
	int deleteoldrdn ));

LDAP_F( int )
ldap_rename2_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn,
	LDAP_CONST char *newSuperior,
	int deleteoldrdn ));

LDAP_F( int )
ldap_modrdn LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn ));

LDAP_F( int )
ldap_modrdn_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn ));

LDAP_F( int )
ldap_modrdn2 LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn,
	int deleteoldrdn ));

LDAP_F( int )
ldap_modrdn2_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *dn,
	LDAP_CONST char *newrdn,
	int deleteoldrdn));


/*
 * in open.c:
 */
LDAP_F( LDAP * )
ldap_init LDAP_P((
	LDAP_CONST char *host,
	int port ));

LDAP_F( LDAP * )
ldap_open LDAP_P((	/* deprecated */
	LDAP_CONST char *host,
	int port ));

LDAP_F( int )
ldap_create LDAP_P((
	LDAP **ldp ));

LDAP_F( int )
ldap_initialize LDAP_P((
	LDAP **ldp,
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_start_tls_s LDAP_P((
	LDAP *ld,
	LDAPControl **serverctrls,
	LDAPControl **clientctrls ));

/*
 * in messages.c:
 */
LDAP_F( LDAPMessage * )
ldap_first_message LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

LDAP_F( LDAPMessage * )
ldap_next_message LDAP_P((
	LDAP *ld,
	LDAPMessage *msg ));

LDAP_F( int )
ldap_count_messages LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));


/*
 * in references.c:
 */
LDAP_F( LDAPMessage * )
ldap_first_reference LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

LDAP_F( LDAPMessage * )
ldap_next_reference LDAP_P((
	LDAP *ld,
	LDAPMessage *ref ));

LDAP_F( int )
ldap_count_references LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

LDAP_F( int )
ldap_parse_reference LDAP_P((
	LDAP			*ld,
	LDAPMessage		*ref,
	char			***referralsp,
	LDAPControl		***serverctrls,
	int				freeit));


/*
 * in getentry.c:
 */
LDAP_F( LDAPMessage * )
ldap_first_entry LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

LDAP_F( LDAPMessage * )
ldap_next_entry LDAP_P((
	LDAP *ld,
	LDAPMessage *entry ));

LDAP_F( int )
ldap_count_entries LDAP_P((
	LDAP *ld,
	LDAPMessage *chain ));

LDAP_F( int )
ldap_get_entry_controls LDAP_P((
	LDAP			*ld,
	LDAPMessage		*entry,
	LDAPControl		***serverctrls));


/*
 * in addentry.c
 */
LDAP_F( LDAPMessage * )
ldap_delete_result_entry LDAP_P((
	LDAPMessage **list,
	LDAPMessage *e ));

LDAP_F( void )
ldap_add_result_entry LDAP_P((
	LDAPMessage **list,
	LDAPMessage *e ));


/*
 * in getdn.c
 */
LDAP_F( char * )
ldap_get_dn LDAP_P((
	LDAP *ld,
	LDAPMessage *entry ));

typedef struct ldap_ava {
	struct berval la_attr;
	struct berval la_value;
	unsigned la_flags;
#define LDAP_AVA_STRING				0x0000U
#define LDAP_AVA_BINARY				0x0001U
#define LDAP_AVA_NONPRINTABLE		0x0002U

	void *la_private;
} LDAPAVA;

typedef LDAPAVA** LDAPRDN;
typedef LDAPRDN** LDAPDN;

/* DN formats */
#define LDAP_DN_FORMAT_LDAP			0x0000U
#define LDAP_DN_FORMAT_LDAPV3		0x0010U
#define LDAP_DN_FORMAT_LDAPV2		0x0020U
#define LDAP_DN_FORMAT_DCE			0x0030U
#define LDAP_DN_FORMAT_UFN			0x0040U	/* dn2str only */
#define LDAP_DN_FORMAT_AD_CANONICAL	0x0050U	/* dn2str only */
#define LDAP_DN_FORMAT_LBER			0x00F0U /* for testing only */
#define LDAP_DN_FORMAT_MASK			0x00F0U

/* DN flags */
#define LDAP_DN_PRETTY				0x0100U
#define LDAP_DN_SKIP				0x0200U
#define LDAP_DN_P_NOLEADTRAILSPACES	0x1000U
#define LDAP_DN_P_NOSPACEAFTERRDN	0x2000U
#define LDAP_DN_PEDANTIC			0xF000U

LDAP_F( void ) ldap_avafree LDAP_P(( LDAPAVA *ava ));
LDAP_F( void ) ldap_rdnfree LDAP_P(( LDAPRDN *rdn ));
LDAP_F( void ) ldap_dnfree LDAP_P(( LDAPDN *dn ));

LDAP_F( int )
ldap_bv2dn LDAP_P(( 
	struct berval *bv, 
	LDAPDN **dn, 
	unsigned flags ));

LDAP_F( int )
ldap_str2dn LDAP_P((
	LDAP_CONST char *str,
	LDAPDN **dn,
	unsigned flags ));

LDAP_F( int )
ldap_dn2bv LDAP_P((
	LDAPDN *dn,
	struct berval *bv,
	unsigned flags ));

LDAP_F( int )
ldap_dn2str LDAP_P((
	LDAPDN *dn,
	char **str,
	unsigned flags ));

LDAP_F( int )
ldap_bv2rdn LDAP_P((
	struct berval *bv,
	LDAPRDN **rdn,
	char **next,
	unsigned flags ));

LDAP_F( int )
ldap_str2rdn LDAP_P((
	LDAP_CONST char *str,
	LDAPRDN **rdn,
	char **next,
	unsigned flags ));

LDAP_F( int )
ldap_rdn2bv LDAP_P((
	LDAPRDN *rdn,
	struct berval *bv,
	unsigned flags ));

LDAP_F( int )
ldap_rdn2str LDAP_P((
	LDAPRDN *rdn,
	char **str,
	unsigned flags ));

LDAP_F( int )
ldap_dn_normalize LDAP_P((
	LDAP_CONST char *in, unsigned iflags,
	char **out, unsigned oflags ));

LDAP_F( char * )
ldap_dn2ufn LDAP_P(( /* deprecated */
	LDAP_CONST char *dn ));

LDAP_F( char ** )
ldap_explode_dn LDAP_P(( /* deprecated */
	LDAP_CONST char *dn,
	int notypes ));

LDAP_F( char ** )
ldap_explode_rdn LDAP_P(( /* deprecated */
	LDAP_CONST char *rdn,
	int notypes ));

typedef int LDAPDN_rewrite_func LDAP_P(( LDAPDN *dn, unsigned flags ));

LDAP_F( int )
ldap_X509dn2bv LDAP_P(( void *x509_name, struct berval *dn,
	LDAPDN_rewrite_func *func, unsigned flags ));

LDAP_F( char * )
ldap_dn2dcedn LDAP_P(( LDAP_CONST char *dn ));	/* deprecated */

LDAP_F( char * )
ldap_dcedn2dn LDAP_P(( LDAP_CONST char *dce ));	/* deprecated */

LDAP_F( char * )
ldap_dn2ad_canonical LDAP_P(( LDAP_CONST char *dn ));	/* deprecated */

LDAP_F( int )
ldap_get_dn_ber LDAP_P((
	LDAP *ld, LDAPMessage *e, BerElement **berout, struct berval *dn ));

LDAP_F( int )
ldap_get_attribute_ber LDAP_P((
	LDAP *ld, LDAPMessage *e, BerElement *ber, struct berval *attr,
	struct berval **vals ));

/*
 * in getattr.c
 */
LDAP_F( char * )
ldap_first_attribute LDAP_P((
	LDAP *ld,
	LDAPMessage *entry,
	BerElement **ber ));

LDAP_F( char * )
ldap_next_attribute LDAP_P((
	LDAP *ld,
	LDAPMessage *entry,
	BerElement *ber ));


/*
 * in getvalues.c
 */
LDAP_F( struct berval ** )
ldap_get_values_len LDAP_P((
	LDAP *ld,
	LDAPMessage *entry,
	LDAP_CONST char *target ));

LDAP_F( int )
ldap_count_values_len LDAP_P((
	struct berval **vals ));

LDAP_F( void )
ldap_value_free_len LDAP_P((
	struct berval **vals ));

LDAP_F( char ** )
ldap_get_values LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAPMessage *entry,
	LDAP_CONST char *target ));

LDAP_F( int )
ldap_count_values LDAP_P((	/* deprecated */
	char **vals ));

LDAP_F( void )
ldap_value_free LDAP_P((	/* deprecated */
	char **vals ));

/*
 * in result.c:
 */
LDAP_F( int )
ldap_result LDAP_P((
	LDAP *ld,
	int msgid,
	int all,
	struct timeval *timeout,
	LDAPMessage **result ));

LDAP_F( int )
ldap_msgtype LDAP_P((
	LDAPMessage *lm ));

LDAP_F( int )
ldap_msgid   LDAP_P((
	LDAPMessage *lm ));

LDAP_F( int )
ldap_msgfree LDAP_P((
	LDAPMessage *lm ));

LDAP_F( int )
ldap_msgdelete LDAP_P((
	LDAP *ld,
	int msgid ));


/*
 * in search.c:
 */
LDAP_F( int )
ldap_search_ext LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*base,
	int				scope,
	LDAP_CONST char	*filter,
	char			**attrs,
	int				attrsonly,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	struct timeval	*timeout,
	int				sizelimit,
	int				*msgidp ));

LDAP_F( int )
ldap_search_ext_s LDAP_P((
	LDAP			*ld,
	LDAP_CONST char	*base,
	int				scope,
	LDAP_CONST char	*filter,
	char			**attrs,
	int				attrsonly,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls,
	struct timeval	*timeout,
	int				sizelimit,
	LDAPMessage		**res ));

LDAP_F( int )
ldap_search LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *base,
	int scope,
	LDAP_CONST char *filter,
	char **attrs,
	int attrsonly ));

LDAP_F( int )
ldap_search_s LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *base,
	int scope,
	LDAP_CONST char *filter,
	char **attrs,
	int attrsonly,
	LDAPMessage **res ));

LDAP_F( int )
ldap_search_st LDAP_P((	/* deprecated */
	LDAP *ld,
	LDAP_CONST char *base,
	int scope,
	LDAP_CONST char *filter,
    char **attrs,
	int attrsonly,
	struct timeval *timeout,
	LDAPMessage **res ));

/*
 * in unbind.c
 */
LDAP_F( int )
ldap_unbind LDAP_P(( /* deprecated */
	LDAP *ld ));

LDAP_F( int )
ldap_unbind_s LDAP_P(( /* deprecated */
	LDAP *ld ));

LDAP_F( int )
ldap_unbind_ext LDAP_P((
	LDAP			*ld,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls));

LDAP_F( int )
ldap_unbind_ext_s LDAP_P((
	LDAP			*ld,
	LDAPControl		**serverctrls,
	LDAPControl		**clientctrls));

/*
 * in filter.c
 */
LDAP_F( int )
ldap_put_vrFilter LDAP_P((
	BerElement *ber,
	const char *vrf ));

/*
 * in free.c
 */

LDAP_F( void * )
ldap_memalloc LDAP_P((
	ber_len_t s ));

LDAP_F( void * )
ldap_memrealloc LDAP_P((
	void* p,
	ber_len_t s ));

LDAP_F( void * )
ldap_memcalloc LDAP_P((
	ber_len_t n,
	ber_len_t s ));

LDAP_F( void )
ldap_memfree LDAP_P((
	void* p ));

LDAP_F( void )
ldap_memvfree LDAP_P((
	void** v ));

LDAP_F( char * )
ldap_strdup LDAP_P((
	LDAP_CONST char * ));

LDAP_F( void )
ldap_mods_free LDAP_P((
	LDAPMod **mods,
	int freemods ));


/*
 * in sort.c
 *	(deprecated)
 */
typedef int (LDAP_SORT_AD_CMP_PROC) LDAP_P(( /* deprecated */
	LDAP_CONST char *left,
	LDAP_CONST char *right ));

typedef int (LDAP_SORT_AV_CMP_PROC) LDAP_P(( /* deprecated */
	LDAP_CONST void *left,
	LDAP_CONST void *right ));

LDAP_F( int )	/* deprecated */
ldap_sort_entries LDAP_P(( LDAP *ld,
	LDAPMessage **chain,
	LDAP_CONST char *attr,
	LDAP_SORT_AD_CMP_PROC *cmp ));

LDAP_F( int )	/* deprecated */
ldap_sort_values LDAP_P((
	LDAP *ld,
	char **vals,
	LDAP_SORT_AV_CMP_PROC *cmp ));

LDAP_F( int ) /* deprecated */
ldap_sort_strcasecmp LDAP_P((
	LDAP_CONST void *a,
	LDAP_CONST void *b ));


/*
 * in url.c
 */
LDAP_F( int )
ldap_is_ldap_url LDAP_P((
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_is_ldaps_url LDAP_P((
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_is_ldapi_url LDAP_P((
	LDAP_CONST char *url ));

LDAP_F( int )
ldap_url_parse LDAP_P((
	LDAP_CONST char *url,
	LDAPURLDesc **ludpp ));

LDAP_F( char * )
ldap_url_desc2str LDAP_P((
	LDAPURLDesc *ludp ));

LDAP_F( void )
ldap_free_urldesc LDAP_P((
	LDAPURLDesc *ludp ));

/*
 * in sortctrl.c
 */
/*
 * structure for a sort-key
 */
typedef struct ldapsortkey {
	char *  attributeType;
	char *  orderingRule;
	int     reverseOrder;
} LDAPSortKey;

LDAP_F( int )
ldap_create_sort_keylist LDAP_P((
	LDAPSortKey ***sortKeyList,
	char        *keyString ));

LDAP_F( void )
ldap_free_sort_keylist LDAP_P((
	LDAPSortKey **sortkeylist ));

LDAP_F( int )
ldap_create_sort_control LDAP_P((
	LDAP *ld,
	LDAPSortKey **keyList,
	int ctl_iscritical,
	LDAPControl **ctrlp ));

LDAP_F( int )
ldap_parse_sort_control LDAP_P((
	LDAP           *ld,
	LDAPControl    **ctrlp,
	unsigned long  *result,
	char           **attribute ));


/*
 * in vlvctrl.c
 */

/*
 * structure for virtual list.
 */
typedef struct ldapvlvinfo {
	int             ldvlv_version;
    unsigned long   ldvlv_before_count;
    unsigned long   ldvlv_after_count;
    unsigned long   ldvlv_offset;
    unsigned long   ldvlv_count;
    struct berval  *ldvlv_attrvalue;
    struct berval  *ldvlv_context;
    void           *ldvlv_extradata;
} LDAPVLVInfo;

LDAP_F( int )
ldap_create_vlv_control LDAP_P((
	LDAP *ld,
	LDAPVLVInfo *ldvlistp,
	LDAPControl **ctrlp ));

LDAP_F( int )
ldap_parse_vlv_control LDAP_P((
	LDAP          *ld,
	LDAPControl   **ctrls,
	unsigned long *target_posp,
	unsigned long *list_countp,
	struct berval **contextp,
	int           *errcodep ));

/*
 * LDAP Who Am I? (whoami.c)
 */

LDAP_F( int )
ldap_parse_whoami LDAP_P((
	LDAP *ld,
	LDAPMessage *res,
	struct berval **authzid ));

LDAP_F( int )
ldap_whoami LDAP_P(( LDAP *ld,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp ));

LDAP_F( int )
ldap_whoami_s LDAP_P((
	LDAP *ld,
	struct berval **authzid,
	LDAPControl **sctrls,
	LDAPControl **cctrls ));

/*
 * in passwd.c
 */

LDAP_F( int )
ldap_parse_passwd LDAP_P((
	LDAP *ld,
	LDAPMessage *res,
	struct berval *newpasswd ));

LDAP_F( int )
ldap_passwd LDAP_P(( LDAP *ld,
	struct berval	*user,
	struct berval	*oldpw,
	struct berval	*newpw,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp ));

LDAP_F( int )
ldap_passwd_s LDAP_P((
	LDAP *ld,
	struct berval	*user,
	struct berval	*oldpw,
	struct berval	*newpw,
	struct berval *newpasswd,
	LDAPControl **sctrls,
	LDAPControl **cctrls ));

LDAP_END_DECL
#endif /* _LDAP_H */
