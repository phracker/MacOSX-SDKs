/*
 *  iodbcext.h
 *
 *  $Id: iodbcext.h,v 1.2 2004/11/11 01:52:36 luesang Exp $
 *
 *  iODBC extensions and changes to the SAG specifications
 *  for third party drivers
 *
 *  Driver specific constants.
 *
 */

#ifndef _IODBCEXT_H
#define _IODBCEXT_H


/*
 * OpenLink API Extensions
 */
#define SQL_GETLASTROWID	1048L
#define SQL_GETLASTSERIAL	1049L
#define SQL_CONCUR_VAL_EXTENT	1050L
#define SQL_APPLICATION_NAME	1051L /* connect option */
#define SQL_PARSE_FWD_ONLY_REQ		1052L
#define SQL_DESC_KEY			1053L
#define SQL_APPEND_KEYS			1054L
#define SQL_DESC_EXPR			1055L
#define SQL_ATTR_WCHAR_SIZE		1056L

#define SQL_COLUMN_ROWVER 		SQL_DESC_ROWVER
#define SQL_COLUMN_KEY 			SQL_DESC_KEY
#define SQL_COLUMN_EXPR			SQL_DESC_EXPR
#define SQL_ATTR_PARSE_FWD_ONLY_REQ  	SQL_PARSE_FWD_ONLY_REQ
#define SQL_ATTR_APPEND_KEYS            SQL_APPEND_KEYS


/*
 *  Microsoft extensions for SQLServer
 */

/*
 *  SQLSetConnectOption/SQLSetStmtOption driver specific defines.
 *  Microsoft has 1200 thru 1249 reserved for Microsoft SQL Server 
 *  driver usage.
 */
#define SQL_ATTR_ENLIST_IN_DTC		1207
#define SQL_ATTR_ENLIST_IN_XA		1208
#define SQL_ATTR_CONNECTION_DEAD	1209	/* GetConnectAttr only */
#define SQL_COPT_SS_BASE		1200
#define SQL_COPT_SS_REMOTE_PWD		(SQL_COPT_SS_BASE+1) /* dbrpwset SQLSetConnectOption only */
#define SQL_COPT_SS_USE_PROC_FOR_PREP	(SQL_COPT_SS_BASE+2) /* Use create proc for SQLPrepare */
#define SQL_COPT_SS_INTEGRATED_SECURITY	(SQL_COPT_SS_BASE+3) /* Force integrated security on login */
#define SQL_COPT_SS_PRESERVE_CURSORS	(SQL_COPT_SS_BASE+4) /* Preserve server cursors after SQLTransact */
#define SQL_COPT_SS_USER_DATA		(SQL_COPT_SS_BASE+5) /* dbgetuserdata/dbsetuserdata */
#define SQL_COPT_SS_ANSI_OEM		(SQL_COPT_SS_BASE+6) /* dbsetopt/DBANSItoOEM/DBOEMtoANSI */
#define SQL_COPT_SS_ENLIST_IN_DTC	SQL_ATTR_ENLIST_IN_DTC /* Enlist in a DTC transaction */
#define SQL_COPT_SS_ENLIST_IN_XA	SQL_ATTR_ENLIST_IN_XA /* Enlist in a XA transaction */
#define SQL_COPT_SS_CONNECTION_DEAD	SQL_ATTR_CONNECTION_DEAD /* dbdead SQLGetConnectOption only */
#define SQL_COPT_SS_FALLBACK_CONNECT	(SQL_COPT_SS_BASE+10) /* Enables FallBack connections */
#define SQL_COPT_SS_PERF_DATA		(SQL_COPT_SS_BASE+11) /* Used to access SQL Server ODBC driver performance data */
#define SQL_COPT_SS_PERF_DATA_LOG	(SQL_COPT_SS_BASE+12) /* Used to set the logfile name for the Performance data */
#define SQL_COPT_SS_PERF_QUERY_INTERVAL (SQL_COPT_SS_BASE+13) /* Used to set the query logging threshold in milliseconds. */
#define SQL_COPT_SS_PERF_QUERY_LOG	(SQL_COPT_SS_BASE+14) /* Used to set the logfile name for saving queries. */
#define SQL_COPT_SS_PERF_QUERY		(SQL_COPT_SS_BASE+15) /* Used to start and stop query logging. */
#define SQL_COPT_SS_PERF_DATA_LOG_NOW	(SQL_COPT_SS_BASE+16) /* Used to make a statistics log entry to disk. */
#define SQL_COPT_SS_QUOTED_IDENT	(SQL_COPT_SS_BASE+17) /* Enable/Disable Quoted Identifiers */
#define SQL_COPT_SS_ANSI_NPW		(SQL_COPT_SS_BASE+18) /* Enable/Disable ANSI NULL, Padding and Warnings */
#define SQL_COPT_SS_BCP			(SQL_COPT_SS_BASE+19) /* Allow BCP usage on connection */

#define SQL_COPT_SS_MAX_USED		SQL_COPT_SS_BCP

#define SQL_SOPT_SS_BASE		1225
#define SQL_SOPT_SS_TEXTPTR_LOGGING	(SQL_SOPT_SS_BASE+0) /* Text pointer logging */
#define SQL_SOPT_SS_CURRENT_COMMAND	(SQL_SOPT_SS_BASE+1) /* dbcurcmd SQLGetStmtOption only */
#define SQL_SOPT_SS_HIDDEN_COLUMNS	(SQL_SOPT_SS_BASE+2) /* Expose FOR BROWSE hidden columns */
#define SQL_SOPT_SS_NOBROWSETABLE	(SQL_SOPT_SS_BASE+3) /* Set NOBROWSETABLE option */
#define SQL_SOPT_SS_REGIONALIZE		(SQL_SOPT_SS_BASE+4) /* Regionalize output character conversions */
#define SQL_SOPT_SS_MAX_USED		SQL_SOPT_SS_REGIONALIZE


/* Defines for use with SQL_COPT_SS_USE_PROC_FOR_PREP */
#define SQL_UP_OFF		0L	/*Procedures won't be used for prepare*/
#define SQL_UP_ON		1L	/*Procedures will be used for prepare*/
#define SQL_UP_ON_DROP	2L		/*Temp procedures will be explicitly dropped*/
#define SQL_UP_DEFAULT	SQL_UP_ON

/* Defines for use with SQL_COPT_SS_INTEGRATED_SECURITY - Pre-Connect Option only */
#define SQL_IS_OFF		0L	/* Integrated security isn't used */
#define SQL_IS_ON		1L	/* Integrated security is used */
#define SQL_IS_DEFAULT	SQL_IS_OFF

/*	Defines for use with SQL_COPT_SS_PRESERVE_CURSORS */
#define SQL_PC_OFF		0L	/* Cursors are closed on SQLTransact */
#define SQL_PC_ON		1L	/* Cursors remain open on SQLTransact */
#define SQL_PC_DEFAULT	SQL_PC_OFF

/* Defines for use with SQL_COPT_SS_USER_DATA */
#define SQL_UD_NOTSET	NULL		/* No user data pointer set */

/* Defines for use with SQL_COPT_SS_ANSI_OEM */
#define SQL_AO_OFF		0L	/* ANSI/OEM translation is not performed */
#define SQL_AO_ON		1L	/* ANSI/OEM translation is performed */
#define SQL_AO_DEFAULT	SQL_AO_OFF	/* Default unless DSN OEM/ANSI checkbox is checked */

/* Defines for use with SQL_COPT_SS_FALLBACK_CONNECT */
#define SQL_FB_OFF		0L	/* FallBack connections are disabled */
#define SQL_FB_ON		1L	/* FallBack connections are enabled */
#define SQL_FB_DEFAULT	SQL_FB_OFF

/* Defines for use with SQL_COPT_SS_BCP */
#define SQL_BCP_OFF		0L	/* BCP is not allowed on connection */
#define SQL_BCP_ON		1L	/* BCP is allowed on connection */
#define SQL_BCP_DEFAULT	SQL_BCP_OFF

/* Defines for use with SQL_COPT_SS_QUOTED_IDENT - Pre-Connect Option only */
#define SQL_QI_OFF		0L	/* Quoted identifiers are not supported */
#define SQL_QI_ON		1L	/* Quoted identifiers are supported */
#define SQL_QI_DEFAULT	SQL_QI_ON

/* Defines for use with SQL_COPT_SS_ANSI_NPW - Pre-Connect Option only */
#define SQL_AD_OFF		0L	/* ANSI NULLs, Padding and Warnings are not supported */
#define SQL_AD_ON		1L	/* ANSI NULLs, Padding and Warnings are supported */
#define SQL_AD_DEFAULT	SQL_AD_ON


/* Defines for use with SQL_SOPT_SS_TEXTPTR_LOGGING */
#define SQL_TL_OFF		0L	/* No logging on text pointer ops */
#define SQL_TL_ON		1L	/* Logging occurs on text pointer ops */
#define SQL_TL_DEFAULT	SQL_TL_ON

/* Defines for use with SQL_SOPT_SS_HIDDEN_COLUMNS */
#define SQL_HC_OFF		0L	/* FOR BROWSE columns are hidden */
#define SQL_HC_ON		1L	/* FOR BROWSE columns are exposed */
#define SQL_HC_DEFAULT	SQL_HC_OFF

/* Defines for use with SQL_SOPT_SS_NOBROWSETABLE */
#define SQL_NB_OFF		0L	/* NO_BROWSETABLE is off */
#define SQL_NB_ON		1L	/* NO_BROWSETABLE is on */
#define SQL_NB_DEFAULT	SQL_NB_OFF

/* Defines for use with SQL_SOPT_SS_REGIONALIZE */
#define SQL_RE_OFF		0L	/* No regionalization occurs on output character conversions */
#define SQL_RE_ON		1L	/* Regionalization occurs on output character conversions */
#define SQL_RE_DEFAULT	SQL_RE_OFF

/*
 * IBM extensions for DB2
 */

/* Options for SQLGetStmtOption/SQLSetStmtOption extensions */
#define  SQL_CURSOR_HOLD              1250
#define  SQL_ATTR_CURSOR_HOLD         1250
#define  SQL_NODESCRIBE_OUTPUT        1251
#define  SQL_ATTR_NODESCRIBE_OUTPUT   1251
#define  SQL_NODESCRIBE_INPUT         1264
#define  SQL_ATTR_NODESCRIBE_INPUT    1264
#define  SQL_NODESCRIBE               SQL_NODESCRIBE_OUTPUT
#define  SQL_ATTR_NODESCRIBE          SQL_NODESCRIBE_OUTPUT
#define  SQL_CLOSE_BEHAVIOR           1257
#define  SQL_ATTR_CLOSE_BEHAVIOR      1257
#define  SQL_ATTR_CLOSEOPEN           1265
#define  SQL_ATTR_CURRENT_PACKAGE_SET 1276
#define  SQL_ATTR_DEFERRED_PREPARE    1277
#define  SQL_ATTR_EARLYCLOSE          1268
#define  SQL_ATTR_PROCESSCTL          1278

/* SQL_CLOSE_BEHAVIOR values.                  */
#define SQL_CC_NO_RELEASE             0
#define SQL_CC_RELEASE                1
#define SQL_CC_DEFAULT                SQL_CC_NO_RELEASE

/* SQL_ATTR_DEFERRED_PREPARE values  */
#define SQL_DEFERRED_PREPARE_ON       1
#define SQL_DEFERRED_PREPARE_OFF      0
#define SQL_DEFERRED_PREPARE_DEFAULT  SQL_DEFERRED_PREPARE_ON

/* SQL_ATTR_EARLYCLOSE values  */
#define SQL_EARLYCLOSE_ON             1
#define SQL_EARLYCLOSE_OFF            0
#define SQL_EARLYCLOSE_DEFAULT        SQL_EARLYCLOSE_ON

/* SQL_ATTR_PROCESSCTL masks  */
#define SQL_PROCESSCTL_NOTHREAD       0x00000001L
#define SQL_PROCESSCTL_NOFORK         0x00000002L

/* Options for SQL_CURSOR_HOLD */
#define SQL_CURSOR_HOLD_ON        1
#define SQL_CURSOR_HOLD_OFF       0
#define SQL_CURSOR_HOLD_DEFAULT   SQL_CURSOR_HOLD_ON

/* Options for SQL_NODESCRIBE_INPUT/SQL_NODESCRIBE_OUTPUT */
#define SQL_NODESCRIBE_ON          1
#define SQL_NODESCRIBE_OFF         0
#define SQL_NODESCRIBE_DEFAULT     SQL_NODESCRIBE_OFF

/* Options for SQLGetConnectOption/SQLSetConnectOption extensions */
#define SQL_WCHARTYPE                1252
#define SQL_LONGDATA_COMPAT          1253
#define SQL_CURRENT_SCHEMA           1254
#define SQL_DB2EXPLAIN               1258
#define SQL_DB2ESTIMATE              1259
#define SQL_PARAMOPT_ATOMIC          1260
#define SQL_STMTTXN_ISOLATION        1261
#define SQL_MAXCONN                  1262
#define SQL_ATTR_WCHARTYPE          SQL_WCHARTYPE
#define SQL_ATTR_LONGDATA_COMPAT    SQL_LONGDATA_COMPAT
#define SQL_ATTR_CURRENT_SCHEMA     SQL_CURRENT_SCHEMA
#define SQL_ATTR_DB2EXPLAIN         SQL_DB2EXPLAIN
#define SQL_ATTR_DB2ESTIMATE        SQL_DB2ESTIMATE
#define SQL_ATTR_PARAMOPT_ATOMIC    SQL_PARAMOPT_ATOMIC
#define SQL_ATTR_STMTTXN_ISOLATION  SQL_STMTTXN_ISOLATION
#define SQL_ATTR_MAXCONN            SQL_MAXCONN

/* Options for SQLSetConnectOption, SQLSetEnvAttr */
#define SQL_CONNECTTYPE              1255
#define SQL_SYNC_POINT               1256
#define SQL_MINMEMORY_USAGE          1263
#define SQL_CONN_CONTEXT             1269
#define SQL_ATTR_INHERIT_NULL_CONNECT    1270
#define SQL_ATTR_FORCE_CONVERSION_ON_CLIENT 1275
#define SQL_ATTR_CONNECTTYPE         SQL_CONNECTTYPE
#define SQL_ATTR_SYNC_POINT          SQL_SYNC_POINT
#define SQL_ATTR_MINMEMORY_USAGE     SQL_MINMEMORY_USAGE
#define SQL_ATTR_CONN_CONTEXT        SQL_CONN_CONTEXT

/* Options for SQL_LONGDATA_COMPAT */
#define SQL_LD_COMPAT_YES            1
#define SQL_LD_COMPAT_NO             0
#define SQL_LD_COMPAT_DEFAULT        SQL_LD_COMPAT_NO

/*  Options for SQL_PARAMOPT_ATOMIC */
#define SQL_ATOMIC_YES               1
#define SQL_ATOMIC_NO                0
#define SQL_ATOMIC_DEFAULT           SQL_ATOMIC_YES

/* Options for SQL_CONNECT_TYPE */
#define SQL_CONCURRENT_TRANS         1
#define SQL_COORDINATED_TRANS        2
#define SQL_CONNECTTYPE_DEFAULT      SQL_CONCURRENT_TRANS

/* Options for SQL_SYNCPOINT */
#define SQL_ONEPHASE                 1
#define SQL_TWOPHASE                 2
#define SQL_SYNCPOINT_DEFAULT        SQL_ONEPHASE

/* Options for SQL_DB2ESTIMATE */
#define SQL_DB2ESTIMATE_ON           1
#define SQL_DB2ESTIMATE_OFF          0
#define SQL_DB2ESTIMATE_DEFAULT      SQL_DB2ESTIMATE_OFF

/* Options for SQL_DB2EXPLAIN */
#define SQL_DB2EXPLAIN_OFF              0x00000000L
#define SQL_DB2EXPLAIN_SNAPSHOT_ON      0x00000001L
#define SQL_DB2EXPLAIN_MODE_ON          0x00000002L
#define SQL_DB2EXPLAIN_SNAPSHOT_MODE_ON SQL_DB2EXPLAIN_SNAPSHOT_ON+SQL_DB2EXPLAIN_MODE_ON
#define SQL_DB2EXPLAIN_ON               SQL_DB2EXPLAIN_SNAPSHOT_ON
#define SQL_DB2EXPLAIN_DEFAULT          SQL_DB2EXPLAIN_OFF

/* Options for SQL_WCHARTYPE
 * Note that you can only specify SQL_WCHARTYPE_CONVERT if you have an
 * external compile flag SQL_WCHART_CONVERT defined
 */
#ifdef SQL_WCHART_CONVERT
#define SQL_WCHARTYPE_CONVERT        1
#endif
#define SQL_WCHARTYPE_NOCONVERT      0
#define SQL_WCHARTYPE_DEFAULT        SQL_WCHARTYPE_NOCONVERT

#endif /* _IODBCEXT_H */
