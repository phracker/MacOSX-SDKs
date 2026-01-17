/* $Id$
 *
 * Copyright (c) 1997,1998,1999  Tim Bunce  England
 *
 * See COPYRIGHT section in DBI.pm for usage and distribution rights.
 */


/* Some core SQL CLI standard (ODBC) declarations		*/
#ifndef SQL_SUCCESS	/* don't clash with ODBC based drivers	*/

/* SQL datatype codes */
#define SQL_GUID                         (-11)
#define SQL_WLONGVARCHAR                 (-10)
#define SQL_WVARCHAR                      (-9)
#define SQL_WCHAR                         (-8)
#define SQL_BIT                           (-7)
#define SQL_TINYINT                       (-6)
#define SQL_BIGINT                        (-5)
#define SQL_LONGVARBINARY                 (-4)
#define SQL_VARBINARY                     (-3)
#define SQL_BINARY                        (-2)
#define SQL_LONGVARCHAR                   (-1)
#define SQL_UNKNOWN_TYPE                    0
#define SQL_ALL_TYPES                       0
#define SQL_CHAR                            1
#define SQL_NUMERIC                         2
#define SQL_DECIMAL                         3
#define SQL_INTEGER                         4
#define SQL_SMALLINT                        5
#define SQL_FLOAT                           6
#define SQL_REAL                            7
#define SQL_DOUBLE                          8
#define SQL_DATETIME                        9
#define SQL_DATE                            9
#define SQL_INTERVAL                       10
#define SQL_TIME                           10
#define SQL_TIMESTAMP                      11
#define SQL_VARCHAR                        12
#define SQL_BOOLEAN                        16
#define SQL_UDT                            17
#define SQL_UDT_LOCATOR                    18
#define SQL_ROW                            19
#define SQL_REF                            20
#define SQL_BLOB                           30
#define SQL_BLOB_LOCATOR                   31
#define SQL_CLOB                           40
#define SQL_CLOB_LOCATOR                   41
#define SQL_ARRAY                          50
#define SQL_ARRAY_LOCATOR                  51
#define SQL_MULTISET                       55
#define SQL_MULTISET_LOCATOR               56
#define SQL_TYPE_DATE                      91
#define SQL_TYPE_TIME                      92
#define SQL_TYPE_TIMESTAMP                 93
#define SQL_TYPE_TIME_WITH_TIMEZONE        94
#define SQL_TYPE_TIMESTAMP_WITH_TIMEZONE   95
#define SQL_INTERVAL_YEAR                 101
#define SQL_INTERVAL_MONTH                102
#define SQL_INTERVAL_DAY                  103
#define SQL_INTERVAL_HOUR                 104
#define SQL_INTERVAL_MINUTE               105
#define SQL_INTERVAL_SECOND               106
#define SQL_INTERVAL_YEAR_TO_MONTH        107
#define SQL_INTERVAL_DAY_TO_HOUR          108
#define SQL_INTERVAL_DAY_TO_MINUTE        109
#define SQL_INTERVAL_DAY_TO_SECOND        110
#define SQL_INTERVAL_HOUR_TO_MINUTE       111
#define SQL_INTERVAL_HOUR_TO_SECOND       112
#define SQL_INTERVAL_MINUTE_TO_SECOND     113


/* Main return codes						*/
#define	SQL_ERROR			(-1)
#define	SQL_SUCCESS			0
#define	SQL_SUCCESS_WITH_INFO		1
#define	SQL_NO_DATA_FOUND		100

/*
 * for ODBC SQL Cursor Types
 */
#define SQL_CURSOR_FORWARD_ONLY         0UL
#define SQL_CURSOR_KEYSET_DRIVEN        1UL
#define SQL_CURSOR_DYNAMIC              2UL
#define SQL_CURSOR_STATIC               3UL
#define SQL_CURSOR_TYPE_DEFAULT         SQL_CURSOR_FORWARD_ONLY

#endif	/*	SQL_SUCCESS	*/

/* Handy macro for testing for success and success with info.		*/
/* BEWARE that this macro can have side effects since rc appears twice!	*/
/* So DONT use it as if(SQL_ok(func(...))) { ... }			*/
#define SQL_ok(rc)	((rc)==SQL_SUCCESS || (rc)==SQL_SUCCESS_WITH_INFO)


/* end of dbi_sql.h */
