/*
 *  odbcinst.h
 *
 *  $Id: odbcinst.h,v 1.3 2006/07/10 13:47:26 source Exp $
 *
 *  iODBC Installer defines
 *
 *  The iODBC driver manager.
 *
 *  Copyright (C) 1996-2006 by OpenLink Software <iodbc@openlinksw.com>
 *  All Rights Reserved.
 *
 *  This software is released under the terms of either of the following
 *  licenses:
 *
 *      - GNU Library General Public License (see LICENSE.LGPL)
 *      - The BSD License (see LICENSE.BSD).
 *
 *  Note that the only valid version of the LGPL license as far as this
 *  project is concerned is the original GNU Library General Public License
 *  Version 2, dated June 1991.
 *
 *  While not mandated by the BSD license, any patches you make to the
 *  iODBC source code may be contributed back into the iODBC project
 *  at your discretion. Contributions will benefit the Open Source and
 *  Data Access community as a whole. Submissions may be made at:
 *
 *      http://www.iodbc.org
 *
 *
 *  GNU Library Generic Public License Version 2
 *  ============================================
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; only
 *  Version 2 of the License dated June 1991.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 *  The BSD License
 *  ===============
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *  3. Neither the name of OpenLink Software Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL OPENLINK OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ODBCINST_H
#define _ODBCINST_H

/*
 *  Set default specification to ODBC 3.51
 */
#ifndef ODBCVER
#define ODBCVER 0x0351
#endif

#ifndef _SQL_H
#include <sql.h>
#endif

#ifndef _SQLEXT_H
#include <sqlext.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXPORT
#define EXPORT
#endif

#ifndef SYS_ODBCINST_INI
#  if defined(__BEOS__)
#    define SYS_ODBCINST_INI	"/boot/beos/etc/odbcinst.ini"
#  endif
#  if defined(macintosh)
#    ifdef __POWERPC__
#      define SYS_ODBCINST_INI "Boot:System Folder:Preferences:ODBC Installer Preferences PPC"
#    else
#      define SYS_ODBCINST_INI "Boot:System Folder:Preferences:ODBC Installer Preferences"
#    endif
#  else
#    define SYS_ODBCINST_INI	"/etc/odbcinst.ini"
#  endif
#endif

#ifndef SYS_ODBC_INI
#  if defined(__BEOS__)
#    define SYS_ODBC_INI	"/boot/beos/etc/odbc.ini"
#  endif
#  if defined(macintosh)
#    ifdef __POWERPC__
#      define SYS_ODBC_INI "Boot:System Folder:Preferences:ODBC Preferences PPC"
#    else
#      define SYS_ODBC_INI "Boot:System Folder:Preferences:ODBC Preferences"
#    endif
#  else
#    define SYS_ODBC_INI	"/etc/odbc.ini"
#  endif
#endif

#ifndef DEFAULT_FILEDSNPATH
#  if defined(__BEOS__)
#    define DEFAULT_FILEDSNPATH	"/boot/beos/etc/ODBCDataSources"
#  elif defined(macintosh)
#    ifdef __POWERPC__
#      define DEFAULT_FILEDSNPATH "Boot:System Folder:Preferences:ODBC Preferences PPC:ODBCDataSources"
#    else
#      define DEFAULT_FILEDSNPATH "Boot:System Folder:Preferences:ODBC Preferences:ODBCDataSources"
#    endif
#  elif defined (__APPLE__)
#    define DEFAULT_FILEDSNPATH	"/Library/ODBC/ODBCDataSources"
#  else
#    define DEFAULT_FILEDSNPATH	"/etc/ODBCDataSources"
#  endif
#endif

#define USERDSN_ONLY  0
#define SYSTEMDSN_ONLY  1

#ifdef WIN32
#define INSTAPI __stdcall
#else
#define INSTAPI 
#endif

/*
 *  SQLConfigDataSource 
 */
#define ODBC_ADD_DSN			1
#define ODBC_CONFIG_DSN			2
#define ODBC_REMOVE_DSN			3

#if (ODBCVER >= 0x0250)
#define ODBC_ADD_SYS_DSN 		4			
#define ODBC_CONFIG_SYS_DSN		5	
#define ODBC_REMOVE_SYS_DSN		6	
#if (ODBCVER >= 0x0300)
#define	 ODBC_REMOVE_DEFAULT_DSN	7
#endif  /* ODBCVER >= 0x0300 */

/* install request flags */
#define	ODBC_INSTALL_INQUIRY		1		
#define ODBC_INSTALL_COMPLETE		2

/* config driver flags */
#define ODBC_INSTALL_DRIVER			1
#define ODBC_REMOVE_DRIVER			2
#define ODBC_CONFIG_DRIVER			3
#define ODBC_CONFIG_DRIVER_MAX	100
#endif

/* SQLGetConfigMode and SQLSetConfigMode flags */
#if (ODBCVER >= 0x0300)
#define ODBC_BOTH_DSN		0
#define ODBC_USER_DSN		1
#define ODBC_SYSTEM_DSN		2
#endif  /* ODBCVER >= 0x0300 */

/* SQLInstallerError code */
#if (ODBCVER >= 0x0300)
#define ODBC_ERROR_GENERAL_ERR                   1
#define ODBC_ERROR_INVALID_BUFF_LEN              2
#define ODBC_ERROR_INVALID_HWND                  3
#define ODBC_ERROR_INVALID_STR                   4
#define ODBC_ERROR_INVALID_REQUEST_TYPE          5
#define ODBC_ERROR_COMPONENT_NOT_FOUND           6
#define ODBC_ERROR_INVALID_NAME                  7
#define ODBC_ERROR_INVALID_KEYWORD_VALUE         8
#define ODBC_ERROR_INVALID_DSN                   9
#define ODBC_ERROR_INVALID_INF                  10
#define ODBC_ERROR_REQUEST_FAILED               11
#define ODBC_ERROR_INVALID_PATH                 12
#define ODBC_ERROR_LOAD_LIB_FAILED              13
#define ODBC_ERROR_INVALID_PARAM_SEQUENCE       14
#define ODBC_ERROR_INVALID_LOG_FILE             15
#define ODBC_ERROR_USER_CANCELED                16
#define ODBC_ERROR_USAGE_UPDATE_FAILED          17
#define ODBC_ERROR_CREATE_DSN_FAILED            18
#define ODBC_ERROR_WRITING_SYSINFO_FAILED       19
#define ODBC_ERROR_REMOVE_DSN_FAILED            20
#define ODBC_ERROR_OUT_OF_MEM                   21
#define ODBC_ERROR_OUTPUT_STRING_TRUNCATED      22
#define ODBC_ERROR_DRIVER_SPECIFIC		23
#endif /* ODBCVER >= 0x0300 */

/*
 *  Function Prototypes
 */

BOOL INSTAPI 
SQLGetConfigMode (
    UWORD* pwConfigMode) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLInstallDriverEx (
    LPCSTR lpszDriver,
    LPCSTR lpszPathIn,
    LPSTR lpszPathOut,
    WORD cbPathOutMax,
    WORD* pcbPathOut,
    WORD fRequest,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLInstallDriverExW (
    LPCWSTR lpszDriver,
    LPCWSTR lpszPathIn,
    LPWSTR lpszPathOut,
    WORD cbPathOutMax,
    WORD* pcbPathOut,
    WORD fRequest,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

RETCODE INSTAPI
SQLInstallerError (
    WORD iError,
    DWORD* pfErrorCode,
    LPSTR lpszErrorMsg,
    WORD cbErrorMsgMax,
    WORD* pcbErrorMsg) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

RETCODE INSTAPI
SQLInstallerErrorW (
    WORD iError,
    DWORD* pfErrorCode,
    LPWSTR lpszErrorMsg,
    WORD cbErrorMsgMax,
    WORD* pcbErrorMsg) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

RETCODE INSTAPI
SQLPostInstallerError (
    DWORD fErrorCode,
    LPSTR szErrorMsg) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

RETCODE INSTAPI
SQLPostInstallerErrorW (
    DWORD fErrorCode,
    LPWSTR szErrorMsg) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLInstallTranslatorEx (
    LPCSTR lpszTranslator,
    LPCSTR lpszPathIn,
    LPSTR lpszPathOut,
    WORD cbPathOutMax,
    WORD* pcbPathOut,
    WORD fRequest,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLInstallTranslatorExW (
    LPCWSTR lpszTranslator,
    LPCWSTR lpszPathIn,
    LPWSTR lpszPathOut,
    WORD cbPathOutMax,
    WORD* pcbPathOut,
    WORD fRequest,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLReadFileDSN (
    LPCSTR lpszFileName,
    LPCSTR lpszAppName,
    LPCSTR lpszKeyName,
    LPSTR lpszString,
    WORD cbString,
    WORD* pcbString) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLReadFileDSNW (
    LPCWSTR lpszFileName,
    LPCWSTR lpszAppName,
    LPCWSTR lpszKeyName,
    LPWSTR lpszString,
    WORD cbString,
    WORD* pcbString) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLWriteFileDSN (
    LPCSTR lpszFileName,
    LPCSTR lpszAppName,
    LPCSTR lpszKeyName,
    LPSTR lpszString) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLWriteFileDSNW (
    LPCWSTR lpszFileName,
    LPCWSTR lpszAppName,
    LPCWSTR lpszKeyName,
    LPWSTR lpszString) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI
SQLSetConfigMode (
    UWORD wConfigMode) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallODBC (
    HWND hwndParent,
    LPCSTR lpszInfFile,
    LPCSTR lpszSrcPath,
    LPCSTR lpszDrivers) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallODBCW (
    HWND hwndParent,
    LPCWSTR lpszInfFile,
    LPCWSTR lpszSrcPath,
    LPCWSTR lpszDrivers) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLManageDataSources (HWND hwndParent) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLCreateDataSource (
    HWND hwndParent,
    LPCSTR lpszDSN) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLCreateDataSourceW (
    HWND hwndParent,
    LPCWSTR lpszDSN) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLGetTranslator (
    HWND hwnd,
    LPSTR lpszName,
    WORD cbNameMax,
    WORD * pcbNameOut,
    LPSTR lpszPath,
    WORD cbPathMax,
    WORD * pcbPathOut,
    DWORD * pvOption) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLGetTranslatorW (
    HWND hwnd,
    LPWSTR lpszName,
    WORD cbNameMax,
    WORD * pcbNameOut,
    LPWSTR lpszPath,
    WORD cbPathMax,
    WORD * pcbPathOut,
    DWORD * pvOption) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

/*  Low level APIs
 *  NOTE: The high-level APIs should always be used. These APIs
 *        have been left for compatibility.
 */
BOOL INSTAPI SQLInstallDriver (
    LPCSTR lpszInfFile,
    LPCSTR lpszDriver,
    LPSTR lpszPath,
    WORD cbPathMax,
    WORD * pcbPathOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallDriverW (
    LPCWSTR lpszInfFile,
    LPCWSTR lpszDriver,
    LPWSTR lpszPath,
    WORD cbPathMax,
    WORD * pcbPathOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallDriverManager (
    LPSTR lpszPath,
    WORD cbPathMax,
    WORD * pcbPathOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallDriverManagerW (
    LPWSTR lpszPath,
    WORD cbPathMax,
    WORD * pcbPathOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLGetInstalledDrivers (
    LPSTR lpszBuf,
    WORD cbBufMax,
    WORD * pcbBufOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLGetInstalledDriversW (
    LPWSTR lpszBuf,
    WORD cbBufMax,
    WORD * pcbBufOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLGetAvailableDrivers (
    LPCSTR lpszInfFile,
    LPSTR lpszBuf,
    WORD cbBufMax,
    WORD * pcbBufOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLGetAvailableDriversW (
    LPCWSTR lpszInfFile,
    LPWSTR lpszBuf,
    WORD cbBufMax,
    WORD * pcbBufOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLConfigDataSource (
    HWND hwndParent,
    WORD fRequest,
    LPCSTR lpszDriver,
    LPCSTR lpszAttributes) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLConfigDataSourceW (
    HWND hwndParent,
    WORD fRequest,
    LPCWSTR lpszDriver,
    LPCWSTR lpszAttributes) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveDefaultDataSource (void) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLWriteDSNToIni (
    LPCSTR lpszDSN,
    LPCSTR lpszDriver) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLWriteDSNToIniW (
    LPCWSTR lpszDSN,
    LPCWSTR lpszDriver) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveDSNFromIni (LPCSTR lpszDSN) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveDSNFromIniW (LPCWSTR lpszDSN) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLValidDSN (LPCSTR lpszDSN) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLValidDSNW (LPCWSTR lpszDSN) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLWritePrivateProfileString (
    LPCSTR lpszSection,
    LPCSTR lpszEntry,
    LPCSTR lpszString,
    LPCSTR lpszFilename) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLWritePrivateProfileStringW (
    LPCWSTR lpszSection,
    LPCWSTR lpszEntry,
    LPCWSTR lpszString,
    LPCWSTR lpszFilename) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

int INSTAPI SQLGetPrivateProfileString (
    LPCSTR lpszSection,
    LPCSTR lpszEntry,
    LPCSTR lpszDefault,
    LPSTR lpszRetBuffer,
    int cbRetBuffer,
    LPCSTR lpszFilename) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

int INSTAPI SQLGetPrivateProfileStringW (
    LPCWSTR lpszSection,
    LPCWSTR lpszEntry,
    LPCWSTR lpszDefault,
    LPWSTR lpszRetBuffer,
    int cbRetBuffer,
    LPCWSTR lpszFilename) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveDriverManager (LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallTranslator (
    LPCSTR lpszInfFile,
    LPCSTR lpszTranslator,
    LPCSTR lpszPathIn,
    LPSTR lpszPathOut,
    WORD cbPathOutMax,
    WORD * pcbPathOut,
    WORD fRequest,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLInstallTranslatorW (
    LPCWSTR lpszInfFile,
    LPCWSTR lpszTranslator,
    LPCWSTR lpszPathIn,
    LPWSTR lpszPathOut,
    WORD cbPathOutMax,
    WORD * pcbPathOut,
    WORD fRequest,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveTranslator (
    LPCSTR lpszTranslator,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveTranslatorW (
    LPCWSTR lpszTranslator,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveDriver (
    LPCSTR lpszDriver,
    BOOL fRemoveDSN,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLRemoveDriverW (
    LPCWSTR lpszDriver,
    BOOL fRemoveDSN,
    LPDWORD lpdwUsageCount) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLConfigDriver (
    HWND hwndParent,
    WORD fRequest,
    LPCSTR lpszDriver,
    LPCSTR lpszArgs,
    LPSTR lpszMsg,
    WORD cbMsgMax,
    WORD * pcbMsgOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI SQLConfigDriverW (
    HWND hwndParent,
    WORD fRequest,
    LPCWSTR lpszDriver,
    LPCWSTR lpszArgs,
    LPWSTR lpszMsg,
    WORD cbMsgMax,
    WORD * pcbMsgOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

/* Driver specific Setup APIs called by installer */

typedef BOOL INSTAPI (*pConfigDSNFunc) (
    HWND hwndParent,
    WORD fRequest,
    LPCSTR lpszDriver,
    LPCSTR lpszAttributes) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

typedef BOOL INSTAPI (*pConfigDSNWFunc) (
    HWND hwndParent,
    WORD fRequest,
    LPCWSTR lpszDriver,
    LPCWSTR lpszAttributes) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

typedef BOOL INSTAPI (*pConfigDriverFunc) (
    HWND hwndParent,
    WORD fRequest,
    LPCSTR lpszDriver,
    LPCSTR lpszArgs,
    LPSTR lpszMsg,
    WORD cbMsgMax,
    WORD * pcbMsgOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

typedef BOOL INSTAPI (*pConfigDriverWFunc) (
    HWND hwndParent,
    WORD fRequest,
    LPCWSTR lpszDriver,
    LPCWSTR lpszArgs,
    LPWSTR lpszMsg,
    WORD cbMsgMax,
    WORD * pcbMsgOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

typedef BOOL INSTAPI (*pConfigTranslatorFunc) (
    HWND hwndParent,
    DWORD *pvOption) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI ConfigDSN (
    HWND hwndParent,
    WORD fRequest,
    LPCSTR lpszDriver,
    LPCSTR lpszAttributes) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI ConfigDSNW (
    HWND hwndParent,
    WORD fRequest,
    LPCWSTR lpszDriver,
    LPCWSTR lpszAttributes) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI ConfigTranslator (HWND hwndParent,
    DWORD * pvOption) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI ConfigDriver (
    HWND hwndParent,
    WORD fRequest,
    LPCSTR lpszDriver,
    LPCSTR lpszArgs,
    LPSTR lpszMsg,
    WORD cbMsgMax,
    WORD * pcbMsgOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

BOOL INSTAPI ConfigDriverW (
    HWND hwndParent,
    WORD fRequest,
    LPCWSTR lpszDriver,
    LPCWSTR lpszArgs,
    LPWSTR lpszMsg,
    WORD cbMsgMax,
    WORD * pcbMsgOut) DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

#ifndef	SQL_NOUNICODEMAP
#ifdef 	UNICODE

#define  SQLInstallODBC               SQLInstallODBCW
#define  SQLCreateDataSource          SQLCreateDataSourceW
#define  SQLGetTranslator             SQLGetTranslatorW
#define  SQLInstallDriver             SQLInstallDriverW
#define  SQLInstallDriverManager      SQLInstallDriverManagerW
#define  SQLGetInstalledDrivers       SQLGetInstalledDriversW
#define  SQLGetAvailableDrivers       SQLGetAvailableDriversW
#define  SQLConfigDataSource          SQLConfigDataSourceW
#define  SQLWriteDSNToIni             SQLWriteDSNToIniW
#define  SQLRemoveDSNFromIni          SQLRemoveDSNFromIniW
#define  SQLValidDSN                  SQLValidDSNW
#define  SQLWritePrivateProfileString SQLWritePrivateProfileStringW
#define	 SQLGetPrivateProfileString   SQLGetPrivateProfileStringW
#define  SQLInstallTranslator         SQLInstallTranslatorW
#define  SQLRemoveTranslator          SQLRemoveTranslatorW
#define  SQLRemoveDriver              SQLRemoveDriverW
#define  SQLConfigDriver              SQLConfigDriverW
#define	 SQLInstallerError            SQLInstallerErrorW
#define	 SQLPostInstallerError        SQLPostInstallerErrorW
#define  SQLReadFileDSN               SQLReadFileDSNW
#define  SQLWriteFileDSN              SQLWriteFileDSNW
#define  SQLInstallDriverEx           SQLInstallDriverExW
#define  SQLInstallTranslatorEx       SQLInstallTranslatorExW

#endif /* UNICODE */
#endif /* SQL_NOUNICODEMAP */

#ifdef __cplusplus
} 
#endif

#endif /* _ODBCINST_H */
