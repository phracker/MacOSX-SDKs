/*                                                                -*- C -*-
   +----------------------------------------------------------------------+
   | PHP version 4.0                                                      |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2001 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Stig Sæther Bakken <ssb@fast.no>                            |
   +----------------------------------------------------------------------+
*/

/* $Id: build-defs.h.in,v 1.1.1.2 2001/07/19 00:20:36 zarzycki Exp $ */

#define CONFIGURE_COMMAND " '/SourceCache/apache_mod_php/apache_mod_php-7/php/configure' '--prefix=/usr' '--mandir=/usr/share/man' '--infodir=/usr/share/info' '--with-apxs'"
#define PHP_ADA_INCLUDE		""
#define PHP_ADA_LFLAGS		""
#define PHP_ADA_LIBS		""
#define PHP_APACHE_INCLUDE	""
#define PHP_APACHE_TARGET	""
#define PHP_FHTTPD_INCLUDE      ""
#define PHP_FHTTPD_LIB          ""
#define PHP_FHTTPD_TARGET       ""
#define PHP_CFLAGS		"-arch i386 -arch ppc -g -Os -pipe -no-cpp-precomp -prefer-pic"
#define PHP_DBASE_LIB		""
#define PHP_BUILD_DEBUG		""
#define PHP_GDBM_INCLUDE	""
#define PHP_HSREGEX		""
#define PHP_IBASE_INCLUDE	""
#define PHP_IBASE_LFLAGS	""
#define PHP_IBASE_LIBS		""
#define PHP_IFX_INCLUDE		""
#define PHP_IFX_LFLAGS		""
#define PHP_IFX_LIBS		""
#define PHP_INSTALL_IT		"$(mkinstalldirs) "$(INSTALL_ROOT)/usr/libexec/httpd" && apxs -S LIBEXECDIR="$(INSTALL_ROOT)/usr/libexec/httpd" -i -a -n php4 libs/libphp4.so"
#define PHP_IODBC_INCLUDE	""
#define PHP_IODBC_LFLAGS	""
#define PHP_IODBC_LIBS		""
#define PHP_MSQL_INCLUDE	""
#define PHP_MSQL_LFLAGS		""
#define PHP_MSQL_LIBS		""
#define PHP_MYSQL_INCLUDE	""
#define PHP_MYSQL_LIBS		""
#define PHP_MYSQL_TYPE		"builtin"
#define PHP_ODBC_INCLUDE	""
#define PHP_ODBC_LFLAGS		""
#define PHP_ODBC_LIBS		""
#define PHP_ODBC_TYPE		""
#define PHP_OCI8_SHARED_LIBADD 	""
#define PHP_OCI8_DIR			""
#define PHP_OCI8_VERSION		""
#define PHP_ORACLE_SHARED_LIBADD 	""
#define PHP_ORACLE_DIR				""
#define PHP_ORACLE_VERSION			""
#define PHP_PGSQL_INCLUDE	""
#define PHP_PGSQL_LFLAGS	""
#define PHP_PGSQL_LIBS		""
#define PHP_PROG_SENDMAIL	"/usr/sbin/sendmail"
#define PHP_REGEX_LIB		""
#define PHP_SOLID_INCLUDE	""
#define PHP_SOLID_LIBS		""
#define PHP_EMPRESS_INCLUDE	""
#define PHP_EMPRESS_LIBS	""
#define PHP_SYBASE_INCLUDE	""
#define PHP_SYBASE_LFLAGS	""
#define PHP_SYBASE_LIBS		""
#define PHP_DBM_TYPE		""
#define PHP_DBM_LIB		""
#define PHP_LDAP_LFLAGS		""
#define PHP_LDAP_INCLUDE	""
#define PHP_LDAP_LIBS		""
#define PHP_VELOCIS_INCLUDE     ""
#define PHP_VELOCIS_LIBS        ""
#define PEAR_INSTALLDIR         "/usr/lib/php"
#define PHP_INCLUDE_PATH	".:/usr/lib/php"
#define PHP_EXTENSION_DIR       "/usr/lib/php/extensions/no-debug-non-zts-20010901"
#define PHP_BINDIR              "/usr/bin"
#define PHP_LIBDIR              "/usr/lib/php"
#define PHP_DATADIR             "/usr/share/php"
#define PHP_SYSCONFDIR          "/usr/etc"
#define PHP_LOCALSTATEDIR       "/usr/var"
#define PHP_CONFIG_FILE_PATH    "/usr/lib"
