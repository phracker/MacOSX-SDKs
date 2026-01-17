/*
 * This file is auto generated.
 * Please do not edit it.
 */
/*
 *
 * Copyright 1987, 1988, 2000, 2001, 2002 by the Massachusetts Institute of Technology. 
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 *   require a specific license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license before exporting.
 * 
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.	Furthermore if you modify this software you must label
 * your software as modified software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 * 
 */
 
#ifndef __KERBEROS4__


/* Error tables from krb_err.h */
#define initialize_krb_error_table()
#define KRBET_KSUCCESS                           (39525376L)
#define KRBET_KDC_NAME_EXP                       (39525377L)
#define KRBET_KDC_SERVICE_EXP                    (39525378L)
#define KRBET_KDC_AUTH_EXP                       (39525379L)
#define KRBET_KDC_PKT_VER                        (39525380L)
#define KRBET_KDC_P_MKEY_VER                     (39525381L)
#define KRBET_KDC_S_MKEY_VER                     (39525382L)
#define KRBET_KDC_BYTE_ORDER                     (39525383L)
#define KRBET_KDC_PR_UNKNOWN                     (39525384L)
#define KRBET_KDC_PR_N_UNIQUE                    (39525385L)
#define KRBET_KDC_NULL_KEY                       (39525386L)
#define KRBET_KDC_GEN_ERR                        (39525396L)
#define KRBET_GC_TKFIL                           (39525397L)
#define KRBET_GC_NOTKT                           (39525398L)
#define KRBET_MK_AP_TGTEXP                       (39525402L)
#define KRBET_RD_AP_UNDEC                        (39525407L)
#define KRBET_RD_AP_EXP                          (39525408L)
#define KRBET_RD_AP_NYV                          (39525409L)
#define KRBET_RD_AP_REPEAT                       (39525410L)
#define KRBET_RD_AP_NOT_US                       (39525411L)
#define KRBET_RD_AP_INCON                        (39525412L)
#define KRBET_RD_AP_TIME                         (39525413L)
#define KRBET_RD_AP_BADD                         (39525414L)
#define KRBET_RD_AP_VERSION                      (39525415L)
#define KRBET_RD_AP_MSG_TYPE                     (39525416L)
#define KRBET_RD_AP_MODIFIED                     (39525417L)
#define KRBET_RD_AP_ORDER                        (39525418L)
#define KRBET_RD_AP_UNAUTHOR                     (39525419L)
#define KRBET_GT_PW_NULL                         (39525427L)
#define KRBET_GT_PW_BADPW                        (39525428L)
#define KRBET_GT_PW_PROT                         (39525429L)
#define KRBET_GT_PW_KDCERR                       (39525430L)
#define KRBET_GT_PW_NULLTKT                      (39525431L)
#define KRBET_SKDC_RETRY                         (39525432L)
#define KRBET_SKDC_CANT                          (39525433L)
#define KRBET_INTK_W_NOTALL                      (39525437L)
#define KRBET_INTK_BADPW                         (39525438L)
#define KRBET_INTK_PROT                          (39525439L)
#define KRBET_INTK_ERR                           (39525446L)
#define KRBET_AD_NOTGT                           (39525447L)
#define KRBET_NO_TKT_FIL                         (39525452L)
#define KRBET_TKT_FIL_ACC                        (39525453L)
#define KRBET_TKT_FIL_LCK                        (39525454L)
#define KRBET_TKT_FIL_FMT                        (39525455L)
#define KRBET_TKT_FIL_INI                        (39525456L)
#define KRBET_KNAME_FMT                          (39525457L)
#define KRBET_MAX_KRB_ERR_TXT                    (39525631L)
#define ERROR_TABLE_BASE_krb                     (39525376L)

/* Error tables from Kerberos4Errors.h */
#define initialize_krbm_error_table()
#define KDC_NAME_EXP                             (1L)
#define KDC_SERVICE_EXP                          (2L)
#define KDC_AUTH_EXP                             (3L)
#define KDC_PKT_VER                              (4L)
#define KDC_P_MKEY_VER                           (5L)
#define KDC_S_MKEY_VER                           (6L)
#define KDC_BYTE_ORDER                           (7L)
#define KDC_PR_UNKNOWN                           (8L)
#define KDC_PR_N_UNIQUE                          (9L)
#define KDC_NULL_KEY                             (10L)
#define KDC_GEN_ERR                              (20L)
#define GC_TKFIL                                 (21L)
#define GC_NOTKT                                 (22L)
#define MK_AP_TGTEXP                             (26L)
#define RD_AP_UNDEC                              (31L)
#define RD_AP_EXP                                (32L)
#define RD_AP_NYV                                (33L)
#define RD_AP_REPEAT                             (34L)
#define RD_AP_NOT_US                             (35L)
#define RD_AP_INCON                              (36L)
#define RD_AP_TIME                               (37L)
#define RD_AP_BADD                               (38L)
#define RD_AP_VERSION                            (39L)
#define RD_AP_MSG_TYPE                           (40L)
#define RD_AP_MODIFIED                           (41L)
#define RD_AP_ORDER                              (42L)
#define RD_AP_UNAUTHOR                           (43L)
#define INTK_PW_NULL                             (51L)
#define GT_PW_BADPW                              (52L)
#define GT_PW_PROT                               (53L)
#define GT_PW_KDCERR                             (54L)
#define GT_PW_NULLTKT                            (55L)
#define SKDC_RETRY                               (56L)
#define SKDC_CANT                                (57L)
#define INTK_W_NOTALL                            (61L)
#define INTK_BADPW                               (62L)
#define INTK_PROT                                (63L)
#define INTK_ERR                                 (70L)
#define AD_NOTGT                                 (71L)
#define NO_TKT_FIL                               (76L)
#define TKT_FIL_ACC                              (77L)
#define TKT_FIL_LCK                              (78L)
#define TKT_FIL_FMT                              (79L)
#define TKT_FIL_INI                              (80L)
#define KNAME_FMT                                (81L)
#define ERROR_TABLE_BASE_krbm                    (1L)
#ifndef	__KERBEROS4__
#define __KERBEROS4__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#include <TargetConditionals.h>
    #if TARGET_RT_MAC_CFM
        #error "Use KfM 4.0 SDK headers for CFM compilation."
    #endif
#endif

#if TARGET_OS_MAC
    #include <kerberosIV/des.h>
    #include <profile.h>
#else
    #include <des.h>
    #include <profile.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma import on
        #pragma enumsalwaysint on
    #endif
    #pragma options align=mac68k
#endif

#if !defined(PROTOTYPE)
#if defined(__STDC__) || defined(__cplusplus) || defined(_MSDOS) || defined(_WIN32)
#define PROTOTYPE(x) x
#else
#define PROTOTYPE(x) ()
#endif
#endif

#define	INTERFACE	/* No special declaration */
#define FAR

/* Sizes of types we need */
#ifndef KRB_INT32
#define KRB_INT32 int32_t
#endif
#ifndef KRB_UINT32
#define KRB_UINT32 u_int32_t
#endif

/* Kerberos 4 Error Codes: */
#define KSUCCESS                                 0
#define KFAILURE                                 255

#define KRB_NEVERDATE (0xFFFFFFFFUL)

/* Parameter for rd_ap_req: Maximum allowable clock skew in seconds */
#define 	CLOCK_SKEW	5*60

/* So many different types of OKness... */
#define		KDC_OK			0	/* Request OK */
#define		GC_OK			0	/* Retrieve OK */
#define		RET_OK			0	/* Retrieve OK */
#define		MK_AP_OK		0	/* Success */
#define		RD_AP_OK		0	/* Request authentic */
#define		GT_PW_OK		0	/* Got password changing tkt */
#define		SKDC_OK			0	/* Response received */
#define		INTK_OK			0	/* Ticket obtained */
#define     AD_OK           0	/* Ticket Obtained */

/* Duplicates not defined by error tables */
#define		RET_TKFIL      GC_TKFIL	/* Can't read ticket file */
#define		RET_NOTKT      GC_NOTKT	/* Can't find ticket or TGT */
#define		GT_PW_NULL     INTK_PW_NULL

/* Error code returned by krb_mk_safe */
#define		SAFE_PRIV_ERROR	-1	/* syscall error */

/* The maximum sizes for aname, realm, sname, and instance +1 */
#define 	ANAME_SZ	40
#define		REALM_SZ	40
#define		SNAME_SZ	40
#define		INST_SZ		40
/* include space for '.' and '@' */
#define		MAX_K_NAME_SZ	(ANAME_SZ + INST_SZ + REALM_SZ + 2)
#define		KKEY_SZ		100
#define		VERSION_SZ	1
#define		MSG_TYPE_SZ	1
#define		DATE_SZ		26	/* RTI date output */

#ifndef DEFAULT_TKT_LIFE			 /* allow compile-time override */
#define		DEFAULT_TKT_LIFE	120 /* default lifetime 10 hrs */
#endif

/* srvtab filename */
#ifdef VMS
    #define     KEYFILE         "multinet:kerberos.srvtab"
#else
    #define		KEYFILE			"/etc/srvtab"
#endif

#define		TICKET_GRANTING_TICKET	"krbtgt"
#define		REMOTE_COMMAND_TICKET	"rcmd"

/* the lookups for the server instances */
#define 	PWSERV_NAME 			"changepw"
#define 	KADM_SNAME   			"kerberos_master"
#define 	KADM_SINST   			"kerberos"

/* Definition of text structure used to pass text around */
#define		MAX_KTXT_LEN	1250

struct ktext {
    int     length;						/* Length of the text */
    unsigned char dat[MAX_KTXT_LEN];	/* The data itself */
    unsigned long mbz;					/* zero to catch runaway strings */
};

typedef struct ktext *KTEXT;
typedef struct ktext KTEXT_ST;


/* Definitions for send_to_kdc */
#define	CLIENT_KRB_TIMEOUT	4	/* time between retries */
#define CLIENT_KRB_RETRY	5	/* retry this many times */
#define	CLIENT_KRB_BUFLEN	512	/* max unfragmented packet */

/* Definitions for ticket file utilities */
#define	R_TKT_FIL	0
#define	W_TKT_FIL	1

/* Structure definition for rd_ap_req */

struct auth_dat {
    unsigned char k_flags;		/* Flags from ticket */
    char    pname[ANAME_SZ];	/* Principal's name */
    char    pinst[INST_SZ];		/* His Instance */
    char    prealm[REALM_SZ];	/* His Realm */
    KRB_UINT32 checksum;		/* Data checksum (opt) */
    C_Block session;			/* Session Key */
    int     life;				/* Life of ticket */
    KRB_UINT32 time_sec;		/* Time ticket issued */
    KRB_UINT32 address;			/* Address in ticket */
    KTEXT_ST reply;				/* Auth reply (opt) */
};

typedef struct auth_dat AUTH_DAT;

/* Structure definition for credentials returned by get_cred */

struct credentials {
    char    service[ANAME_SZ];	/* Service name */
    char    instance[INST_SZ];	/* Instance */
    char    realm[REALM_SZ];	/* Auth domain */
    C_Block session;			/* Session key */
    int     lifetime;			/* Lifetime */
    int     kvno;				/* Key version number */
    KTEXT_ST ticket_st;			/* The ticket itself */
    long    issue_date;			/* The issue time */
    char    pname[ANAME_SZ];	/* Principal's name */
    char    pinst[INST_SZ];		/* Principal's instance */
    KRB_UINT32 address;			/* Address in ticket */
    KRB_UINT32 stk_type;		/* string_to_key function needed */
};

typedef struct credentials CREDENTIALS;

/* Structure definition for rd_private_msg and rd_safe_msg */

struct msg_dat {
    unsigned char *app_data;	/* pointer to appl data */
    KRB_UINT32 app_length; 		/* length of appl data */
    unsigned long hash;			/* hash to lookup replay */
    int     swap;				/* swap bytes? */
    KRB_INT32    time_sec;		/* msg timestamp seconds */
    unsigned char time_5ms;		/* msg timestamp 5ms units */
};

typedef struct msg_dat MSG_DAT;


/* Location of default ticket file for save_cred and get_cred */
#ifndef	TKT_FILE
#define	TKT_FILE				tkt_string()
#endif /* TKT_FILE */

/* Defines for krb_sendauth, krb_mk_auth, krb_check_auth, and krb_recvauth */

#define	KOPT_DONT_MK_REQ 0x00000001 /* don't call krb_mk_req */
#define	KOPT_DO_MUTUAL   0x00000002 /* do mutual auth */

#define	KOPT_DONT_CANON  0x00000004 /*
				     * dont canonicalize inst as
                     * a hostname
				     */

#define	KRB_SENDAUTH_VLEN 8	    /* length for version strings */

#ifdef ATHENA_COMPAT
#define	KOPT_DO_OLDSTYLE 0x00000008 /* use the old-style protocol */
#endif /* ATHENA_COMPAT */

/* Constants for KerberosProfileLib */
#define		REALMS_V4_PROF_REALMS_SECTION		"v4 realms"
#define		REALMS_V4_PROF_KDC					"kdc"
#define		REALMS_V4_PROF_ADMIN_KDC			"admin_server"
#define		REALMS_V4_PROF_KPASSWD_KDC			"kpasswd_server"
#define		REALMS_V4_PROF_DOMAIN_SECTION		"v4 domain_realm"
#define		REALMS_V4_PROF_LIBDEFAULTS_SECTION	"libdefaults"
#define		REALMS_V4_PROF_LOCAL_REALM			"default_realm"
#define		REALMS_V4_PROF_STK					"string_to_key_type"
#define		REALMS_V4_MIT_STK					"mit_string_to_key"
#define		REALMS_V4_AFS_STK					"afs_string_to_key"
#define		REALMS_V4_COLUMBIA_STK				"columbia_string_to_key"
#define		REALMS_V4_DEFAULT_REALM				"default_realm"
#define		REALMS_V4_NO_ADDRESSES				"noaddresses"

/* Define a couple of function types including parameters.  These
   are needed on MS-Windows to convert arguments of the function pointers
   to the proper types during calls.  */
typedef int (*key_proc_type) PROTOTYPE ((char *, char *, char *,
					     char *, C_Block));
typedef int (*decrypt_tkt_type) PROTOTYPE ((char *, char *, char *, char *,
				     key_proc_type, KTEXT *));
#define	KEY_PROC_TYPE_DEFINED
#define	DECRYPT_TKT_TYPE_DEFINED

/******************************************/
/*** EXPORTED FUNTIONS (by source file) ***/
/******************************************/

/* change_password.c */
extern int INTERFACE
krb_change_password PROTOTYPE ((char *, char *, char *, char *, char *));

/* decomp_tkt.c */ 
extern int INTERFACE
decomp_ticket PROTOTYPE ((KTEXT, unsigned char *, char *, char *, char *, KRB_UINT32 *, C_Block,
	int *, KRB_UINT32 *, char *, char *, C_Block, Key_schedule));

/* err_txt.c */
extern const char * const * krb_err_txt;
extern const char * INTERFACE
krb_get_err_text PROTOTYPE ((int));

/* g_ad_tkt.c */
extern int INTERFACE
get_ad_tkt PROTOTYPE ((char *service, char *sinstance, char *realm, int lifetime));

/* g_in_tkt.c */
extern int INTERFACE
krb_get_in_tkt PROTOTYPE ((char *, char *, char *, char *, char *, int,
			   key_proc_type, decrypt_tkt_type, char *arg));

extern int INTERFACE
krb_get_in_tkt_creds PROTOTYPE ((char *, char *, char *, char *, char *, int, 
		key_proc_type, decrypt_tkt_type, char *, CREDENTIALS *));

/* g_phost.c */
extern char * INTERFACE
krb_get_phost PROTOTYPE ((char  *));

/* g_pw_in_tkt.c */
extern int INTERFACE
krb_get_pw_in_tkt PROTOTYPE ((char *, char *, char *,
		char *, char *, int, char *));

extern int INTERFACE
krb_get_pw_in_tkt_creds PROTOTYPE ((char *, char *, char *, 
	char *, char *, int, char *, CREDENTIALS *));

/* g_pw_tkt.c */
extern int INTERFACE
get_pw_tkt PROTOTYPE ((char *, char *, char *,
	char *));

/* g_svc_in_tkt.c */
extern int INTERFACE
krb_get_svc_in_tkt PROTOTYPE ((char *, char *, char *,
	char *, char *, int, char *));

#if TARGET_OS_MAC && defined(__FILES__)
extern int INTERFACE
FSp_krb_get_svc_in_tkt PROTOTYPE ((char *, char *, char *, 
	char *, char *, int, const FSSpec *));
#endif

/* g_tkt_svc.c */
extern int INTERFACE
krb_get_ticket_for_service PROTOTYPE ((char *, char *,
	KRB_UINT32 *, int, des_cblock, Key_schedule, char *, int));
 
/* kname_parse.c */
extern int INTERFACE 
k_isname PROTOTYPE((const char *s));

extern int INTERFACE 
k_isinst PROTOTYPE((const char *s));

extern int INTERFACE 
k_isrealm PROTOTYPE((const char *s));

extern int INTERFACE 
kname_parse PROTOTYPE((char *, char *, char *, const char *));

extern int INTERFACE 
kname_unparse PROTOTYPE((char *, const char *, const char *, const char *));

/* kuserok.c */
extern int INTERFACE 
kuserok PROTOTYPE((AUTH_DAT *kdata, char *luser));

/* lifetime.c */
extern KRB_UINT32 INTERFACE 
krb_life_to_time PROTOTYPE((KRB_UINT32 start, int life));

extern int INTERFACE
krb_time_to_life PROTOTYPE((KRB_UINT32 start, KRB_UINT32 end));

/* mk_auth.c */
extern int INTERFACE
krb_check_auth PROTOTYPE ((KTEXT, KRB_UINT32, MSG_DAT *,
		C_Block FAR, Key_schedule, struct sockaddr_in *,
		struct sockaddr_in *));

extern int INTERFACE
krb_mk_auth PROTOTYPE ((long, KTEXT, char *, char *, char *, 
		KRB_UINT32, char *, KTEXT));

/* mk_err.c */
extern long INTERFACE
krb_mk_err PROTOTYPE ((unsigned char *, KRB_INT32, char *));

/* mk_priv.c */
extern long INTERFACE
krb_mk_priv PROTOTYPE ((unsigned char *, unsigned char *, KRB_UINT32, 
	Key_schedule FAR, C_Block, struct sockaddr_in *, struct sockaddr_in *));

/* mk_req.c */
extern int INTERFACE
krb_mk_req PROTOTYPE ((KTEXT, char *, char *, char *, KRB_INT32));

extern int INTERFACE
krb_mk_req_creds PROTOTYPE ((register KTEXT, CREDENTIALS *, KRB_INT32));

int
krb_set_lifetime(int newval);

/* mk_safe.c */
extern long INTERFACE
krb_mk_safe PROTOTYPE ((unsigned char *, unsigned char *,
	KRB_UINT32, C_Block, struct sockaddr_in *,
	struct sockaddr_in *));

/* rd_err.c */
extern int INTERFACE
krb_rd_err PROTOTYPE ((unsigned char *, unsigned long, long *, MSG_DAT *));

/* rd_priv.c */
extern long INTERFACE
krb_rd_priv PROTOTYPE ((unsigned char *, KRB_UINT32,
	Key_schedule FAR, C_Block, struct sockaddr_in *,
	struct sockaddr_in *, MSG_DAT *));

/* rd_req.c */
extern int INTERFACE
krb_rd_req PROTOTYPE ((KTEXT, char *, char *,
	KRB_UINT32, AUTH_DAT *, char *));

/* rd_req_int.c */
extern int INTERFACE
krb_rd_req_int PROTOTYPE ((KTEXT, char *, char *,
	KRB_UINT32, AUTH_DAT *, C_Block));

/* rd_svc_key.c */
extern int INTERFACE
read_service_key PROTOTYPE ((char *, char *, char *, int, char *, char *));

#if TARGET_OS_MAC && defined(__FILES__)
extern int INTERFACE
FSp_read_service_key PROTOTYPE ((char *, char *, char *, int, const FSSpec*, char *));
#endif

/* rd_safe.c */
extern long INTERFACE
krb_rd_safe PROTOTYPE ((unsigned char *, KRB_UINT32,
	C_Block, struct sockaddr_in *, struct sockaddr_in *, MSG_DAT *));

/* recvauth.c */
extern int INTERFACE
krb_recvauth PROTOTYPE ((long, int, KTEXT, char *, char *,
	struct sockaddr_in *, struct sockaddr_in *,
	AUTH_DAT *, char *, Key_schedule FAR, char *));

/* sendauth.c */
extern int INTERFACE 
krb_sendauth PROTOTYPE ((long, int, KTEXT, char *, char *, char *, 
	KRB_UINT32, MSG_DAT *, CREDENTIALS *, Key_schedule, 
	struct sockaddr_in *, struct sockaddr_in *, char *));

/* CCache-glue.c */
extern int INTERFACE
krb_get_tf_realm PROTOTYPE ((const char *, char *));

extern int INTERFACE
krb_get_tf_fullname PROTOTYPE ((const char *, char *, char *,
	char *));

extern int INTERFACE
krb_get_cred PROTOTYPE ((char *, char *, char *, CREDENTIALS *));

extern const char * INTERFACE 
tkt_string PROTOTYPE ((void));

extern void INTERFACE
krb_set_tkt_string PROTOTYPE ((const char *));

extern int INTERFACE
dest_tkt PROTOTYPE ((void));

#if TARGET_OS_MAC
/* The following functions are not part of the standard Kerberos v4 API. 
 * They were created for Mac implementation, and used by admin tools 
 * such as CNS-Config. */
extern int INTERFACE 
krb_get_num_cred PROTOTYPE ((void));

extern int INTERFACE
krb_get_nth_cred PROTOTYPE ((char *, char *, char *, int));

extern int INTERFACE
krb_delete_cred PROTOTYPE ((char *, char *,char *));

extern int INTERFACE
dest_all_tkts PROTOTYPE ((void));

#endif /* TARGET_OS_MAC */

/* RealmConfig-glue.c */
extern int INTERFACE
krb_get_profile PROTOTYPE ((profile_t* profile));

extern int INTERFACE
krb_get_lrealm PROTOTYPE ((char *, int));

extern int INTERFACE
krb_get_admhst PROTOTYPE ((char *, char *, int));

extern int INTERFACE
krb_get_krbhst PROTOTYPE ((char *, const char *, int));

extern char * INTERFACE
krb_realmofhost PROTOTYPE ((char *));

extern int INTERFACE
put_svc_key PROTOTYPE ((char *, char *, char *, char *, int, char *));

#if TARGET_OS_MAC && defined(__FILES__)
extern int INTERFACE
FSp_put_svc_key PROTOTYPE ((const FSSpec *, char *, char *, char *, int, char *));
#endif

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma enumsalwaysint reset
        #pragma import reset
    #endif
	#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif	/* __KERBEROS4__ */
#endif /* __KERBEROS4__  */
