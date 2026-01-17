/* main/php_config.h.  Generated automatically by configure.  */
/* main/php_config.h.in.  Generated automatically from configure.in by autoheader.  */
/* Leave this file alone */
/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2010 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Andi Gutmans <andi@zend.com>                                |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/

/* $Id: acconfig.h 293155 2010-01-05 20:46:53Z sebastian $ */

#ifndef ZEND_API

#if defined(__GNUC__) && __GNUC__ >= 4
# define ZEND_API __attribute__ ((visibility("default")))
# define ZEND_DLEXPORT __attribute__ ((visibility("default")))
#else
# define ZEND_API
# define ZEND_DLEXPORT
#endif

#define ZEND_DLIMPORT


/* Define if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* #undef _ALL_SOURCE */
#endif

/* Define if using alloca.c.  */
/* #undef C_ALLOCA */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
   This function is required for alloca.c support on those systems.  */
/* #undef CRAY_STACKSEG_END */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef gid_t */

/* Define if you have alloca, as a function or macro.  */
#define HAVE_ALLOCA 1

/* Define if you have <alloca.h> and it should be used (not on Ultrix).  */
#define HAVE_ALLOCA_H 1

/* Define if you don't have vprintf but do have _doprnt.  */
/* #undef HAVE_DOPRNT */

/* Define if your system has a working fnmatch function.  */
#define HAVE_FNMATCH 1

/* Define if your struct stat has st_blksize.  */
#define HAVE_ST_BLKSIZE 1

/* Define if your struct stat has st_blocks.  */
#define HAVE_ST_BLOCKS 1

/* Define if your struct stat has st_rdev.  */
#define HAVE_ST_RDEV 1

/* Define if your struct tm has tm_zone.  */
#define HAVE_TM_ZONE 1

/* Define if you don't have tm_zone but do have the external array
   tzname.  */
/* #undef HAVE_TZNAME */

/* Define if utime(file, NULL) sets file's timestamp to the present.  */
#define HAVE_UTIME_NULL 1

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF 1

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

/* Define if your C compiler doesn't accept -c and -o together.  */
/* #undef NO_MINUS_C_MINUS_O */

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#define TIME_WITH_SYS_TIME 1

/* Define if your <sys/time.h> declares struct tm.  */
/* #undef TM_IN_SYS_TIME */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef uid_t */

/* #undef uint */
#define ulong unsigned long 

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 1

/* The number of bytes in a char *.  */
#define SIZEOF_CHAR_P 8

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 8

/* The number of bytes in a long int.  */
/* #undef SIZEOF_LONG_INT */

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* The number of bytes in a long long int.  */
#define SIZEOF_LONG_LONG_INT 8

/* The number of bytes in a short.  */
#define SIZEOF_SHORT 2

/* The number of bytes in a size_t.  */
#define SIZEOF_SIZE_T 8

/* Define if you have the CreateProcess function.  */
/* #undef HAVE_CREATEPROCESS */

/* Define if you have the acosh function.  */
#define HAVE_ACOSH 1

/* Define if you have the alphasort function.  */
#define HAVE_ALPHASORT 1

/* Define if you have the asctime_r function.  */
#define HAVE_ASCTIME_R 1

/* Define if you have the asinh function.  */
#define HAVE_ASINH 1

/* Define if you have the asprintf function.  */
#define HAVE_ASPRINTF 1

/* Define if you have the atanh function.  */
#define HAVE_ATANH 1

/* Define if you have the atoll function.  */
#define HAVE_ATOLL 1

/* Define if you have the chroot function.  */
#define HAVE_CHROOT 1

/* Define if you have the clearenv function.  */
/* #undef HAVE_CLEARENV */

/* Define if you have the crypt function.  */
#define HAVE_CRYPT 1

/* Define if you have the crypt_r function.  */
/* #undef HAVE_CRYPT_R */

/* Define if you have the ctermid function.  */
#define HAVE_CTERMID 1

/* Define if you have the ctime_r function.  */
#define HAVE_CTIME_R 1

/* Define if you have the cuserid function.  */
/* #undef HAVE_CUSERID */

/* Define if you have the fabsf function.  */
#define HAVE_FABSF 1

/* Define if you have the finite function.  */
#define HAVE_FINITE 1

/* Define if you have the flock function.  */
#define HAVE_FLOCK 1

/* Define if you have the floorf function.  */
#define HAVE_FLOORF 1

/* Define if you have the fork function.  */
#define HAVE_FORK 1

/* Define if you have the fpclass function.  */
/* #undef HAVE_FPCLASS */

/* Define if you have the ftok function.  */
#define HAVE_FTOK 1

/* Define if you have the funopen function.  */
#define HAVE_FUNOPEN 1

/* Define if you have the gai_strerror function.  */
#define HAVE_GAI_STRERROR 1

/* Define if you have the gcvt function.  */
#define HAVE_GCVT 1

/* Define if you have the getcwd function.  */
#define HAVE_GETCWD 1

/* Define if you have the getgrgid_r function.  */
#define HAVE_GETGRGID_R 1

/* Define if you have the getgrnam_r function.  */
#define HAVE_GETGRNAM_R 1

/* Define if you have the getgroups function.  */
#define HAVE_GETGROUPS 1

/* Define if you have the gethostname function.  */
#define HAVE_GETHOSTNAME 1

/* Define if you have the getloadavg function.  */
#define HAVE_GETLOADAVG 1

/* Define if you have the getlogin function.  */
#define HAVE_GETLOGIN 1

/* Define if you have the getopt function.  */
#define HAVE_GETOPT 1

/* Define if you have the getpgid function.  */
#define HAVE_GETPGID 1

/* Define if you have the getpid function.  */
#define HAVE_GETPID 1

/* Define if you have the getpriority function.  */
/* #undef HAVE_GETPRIORITY */

/* Define if you have the getprotobyname function.  */
#define HAVE_GETPROTOBYNAME 1

/* Define if you have the getprotobynumber function.  */
#define HAVE_GETPROTOBYNUMBER 1

/* Define if you have the getpwnam_r function.  */
#define HAVE_GETPWNAM_R 1

/* Define if you have the getpwuid_r function.  */
#define HAVE_GETPWUID_R 1

/* Define if you have the getrlimit function.  */
#define HAVE_GETRLIMIT 1

/* Define if you have the getrusage function.  */
#define HAVE_GETRUSAGE 1

/* Define if you have the getservbyname function.  */
#define HAVE_GETSERVBYNAME 1

/* Define if you have the getservbyport function.  */
#define HAVE_GETSERVBYPORT 1

/* Define if you have the getsid function.  */
#define HAVE_GETSID 1

/* Define if you have the gettimeofday function.  */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the getwd function.  */
#define HAVE_GETWD 1

/* Define if you have the glob function.  */
#define HAVE_GLOB 1

/* Define if you have the gmtime_r function.  */
#define HAVE_GMTIME_R 1

/* Define if you have the grantpt function.  */
#define HAVE_GRANTPT 1

/* Define if you have the hstrerror function.  */
#define HAVE_HSTRERROR 1

/* Define if you have the hypot function.  */
#define HAVE_HYPOT 1

/* Define if you have the inet_ntoa function.  */
#define HAVE_INET_NTOA 1

/* Define if you have the inet_ntop function.  */
#define HAVE_INET_NTOP 1

/* Define if you have the inet_pton function.  */
#define HAVE_INET_PTON 1

/* Define if you have the initgroups function.  */
#define HAVE_INITGROUPS 1

/* Define if you have the isascii function.  */
#define HAVE_ISASCII 1

/* Define if you have the isfinite function.  */
/* #undef HAVE_ISFINITE */

/* Define if you have the isinf function.  */
#define HAVE_ISINF 1

/* Define if you have the isnan function.  */
#define HAVE_ISNAN 1

/* Define if you have the kill function.  */
#define HAVE_KILL 1

/* Define if you have the lchown function.  */
#define HAVE_LCHOWN 1

/* Define if you have the ldap_parse_reference function.  */
#define HAVE_LDAP_PARSE_REFERENCE 1

/* Define if you have the ldap_parse_result function.  */
#define HAVE_LDAP_PARSE_RESULT 1

/* Define if you have the ldap_start_tls_s function.  */
#define HAVE_LDAP_START_TLS_S 1

/* Define if you have the link function.  */
#define HAVE_LINK 1

/* Define if you have the localeconv function.  */
#define HAVE_LOCALECONV 1

/* Define if you have the localtime_r function.  */
#define HAVE_LOCALTIME_R 1

/* Define if you have the lockf function.  */
#define HAVE_LOCKF 1

/* Define if you have the log1p function.  */
#define HAVE_LOG1P 1

/* Define if you have the lrand48 function.  */
#define HAVE_LRAND48 1

/* Define if you have the makedev function.  */
/* #undef HAVE_MAKEDEV */

/* Define if you have the mblen function.  */
#define HAVE_MBLEN 1

/* Define if you have the mbrlen function.  */
#define HAVE_MBRLEN 1

/* Define if you have the mbsinit function.  */
#define HAVE_MBSINIT 1

/* Define if you have the memcpy function.  */
#define HAVE_MEMCPY 1

/* Define if you have the memmove function.  */
#define HAVE_MEMMOVE 1

/* Define if you have the mempcpy function.  */
/* #undef HAVE_MEMPCPY */

/* Define if you have the mkfifo function.  */
#define HAVE_MKFIFO 1

/* Define if you have the mknod function.  */
#define HAVE_MKNOD 1

/* Define if you have the mkstemp function.  */
#define HAVE_MKSTEMP 1

/* Define if you have the mmap function.  */
#define HAVE_MMAP 1

/* Define if you have the mremap function.  */
/* #undef HAVE_MREMAP */

/* Define if you have the mysql_commit function.  */
/* #undef HAVE_MYSQL_COMMIT */

/* Define if you have the mysql_next_result function.  */
/* #undef HAVE_MYSQL_NEXT_RESULT */

/* Define if you have the mysql_sqlstate function.  */
/* #undef HAVE_MYSQL_SQLSTATE */

/* Define if you have the mysql_stmt_prepare function.  */
/* #undef HAVE_MYSQL_STMT_PREPARE */

/* Define if you have the nanosleep function.  */
#define HAVE_NANOSLEEP 1

/* Define if you have the nice function.  */
#define HAVE_NICE 1

/* Define if you have the nl_langinfo function.  */
#define HAVE_NL_LANGINFO 1

/* Define if you have the perror function.  */
#define HAVE_PERROR 1

/* Define if you have the poll function.  */
#define HAVE_POLL 1

/* Define if you have the ptsname function.  */
#define HAVE_PTSNAME 1

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the rand_r function.  */
#define HAVE_RAND_R 1

/* Define if you have the random function.  */
#define HAVE_RANDOM 1

/* Define if you have the realpath function.  */
#define HAVE_REALPATH 1

/* Define if you have the rl_completion_matches function.  */
/* #undef HAVE_RL_COMPLETION_MATCHES */

/* Define if you have the scandir function.  */
#define HAVE_SCANDIR 1

/* Define if you have the setegid function.  */
#define HAVE_SETEGID 1

/* Define if you have the setenv function.  */
#define HAVE_SETENV 1

/* Define if you have the seteuid function.  */
#define HAVE_SETEUID 1

/* Define if you have the setitimer function.  */
#define HAVE_SETITIMER 1

/* Define if you have the setlocale function.  */
#define HAVE_SETLOCALE 1

/* Define if you have the setpgid function.  */
#define HAVE_SETPGID 1

/* Define if you have the setpriority function.  */
/* #undef HAVE_SETPRIORITY */

/* Define if you have the setproctitle function.  */
/* #undef HAVE_SETPROCTITLE */

/* Define if you have the setsid function.  */
#define HAVE_SETSID 1

/* Define if you have the setsockopt function.  */
#define HAVE_SETSOCKOPT 1

/* Define if you have the setvbuf function.  */
#define HAVE_SETVBUF 1

/* Define if you have the shutdown function.  */
#define HAVE_SHUTDOWN 1

/* Define if you have the sigaction function.  */
/* #undef HAVE_SIGACTION */

/* Define if you have the sigprocmask function.  */
/* #undef HAVE_SIGPROCMASK */

/* Define if you have the sigsetjmp function.  */
#define HAVE_SIGSETJMP 1

/* Define if you have the sigtimedwait function.  */
/* #undef HAVE_SIGTIMEDWAIT */

/* Define if you have the sigwaitinfo function.  */
/* #undef HAVE_SIGWAITINFO */

/* Define if you have the sin function.  */
#define HAVE_SIN 1

/* Define if you have the snprintf function.  */
#define HAVE_SNPRINTF 1

/* Define if you have the socketpair function.  */
#define HAVE_SOCKETPAIR 1

/* Define if you have the srand48 function.  */
#define HAVE_SRAND48 1

/* Define if you have the srandom function.  */
#define HAVE_SRANDOM 1

/* Define if you have the statfs function.  */
#define HAVE_STATFS 1

/* Define if you have the statvfs function.  */
#define HAVE_STATVFS 1

/* Define if you have the std_syslog function.  */
/* #undef HAVE_STD_SYSLOG */

/* Define if you have the strcasecmp function.  */
#define HAVE_STRCASECMP 1

/* Define if you have the strcoll function.  */
#define HAVE_STRCOLL 1

/* Define if you have the strdup function.  */
#define HAVE_STRDUP 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strfmon function.  */
#define HAVE_STRFMON 1

/* Define if you have the strftime function.  */
#define HAVE_STRFTIME 1

/* Define if you have the strlcat function.  */
#define HAVE_STRLCAT 1

/* Define if you have the strlcpy function.  */
#define HAVE_STRLCPY 1

/* Define if you have the strndup function.  */
/* #undef HAVE_STRNDUP */

/* Define if you have the strnlen function.  */
/* #undef HAVE_STRNLEN */

/* Define if you have the strpbrk function.  */
#define HAVE_STRPBRK 1

/* Define if you have the strpncpy function.  */
/* #undef HAVE_STRPNCPY */

/* Define if you have the strptime function.  */
#define HAVE_STRPTIME 1

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strtod function.  */
#define HAVE_STRTOD 1

/* Define if you have the strtok_r function.  */
#define HAVE_STRTOK_R 1

/* Define if you have the strtol function.  */
#define HAVE_STRTOL 1

/* Define if you have the strtoll function.  */
#define HAVE_STRTOLL 1

/* Define if you have the strtoul function.  */
#define HAVE_STRTOUL 1

/* Define if you have the strtoull function.  */
#define HAVE_STRTOULL 1

/* Define if you have the symlink function.  */
#define HAVE_SYMLINK 1

/* Define if you have the tempnam function.  */
#define HAVE_TEMPNAM 1

/* Define if you have the tzset function.  */
#define HAVE_TZSET 1

/* Define if you have the unlockpt function.  */
#define HAVE_UNLOCKPT 1

/* Define if you have the unsetenv function.  */
#define HAVE_UNSETENV 1

/* Define if you have the usleep function.  */
#define HAVE_USLEEP 1

/* Define if you have the utime function.  */
#define HAVE_UTIME 1

/* Define if you have the utimes function.  */
#define HAVE_UTIMES 1

/* Define if you have the vasprintf function.  */
#define HAVE_VASPRINTF 1

/* Define if you have the vsnprintf function.  */
#define HAVE_VSNPRINTF 1

/* Define if you have the wait3 function.  */
/* #undef HAVE_WAIT3 */

/* Define if you have the waitpid function.  */
/* #undef HAVE_WAITPID */

/* Define if you have the </nsapi.h> header file.  */
/* #undef HAVE__NSAPI_H */

/* Define if you have the <ApplicationServices/ApplicationServices.h> header file.  */
#define HAVE_APPLICATIONSERVICES_APPLICATIONSERVICES_H 1

/* Define if you have the <alloca.h> header file.  */
#define HAVE_ALLOCA_H 1

/* Define if you have the <arpa/inet.h> header file.  */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <arpa/nameser.h> header file.  */
#define HAVE_ARPA_NAMESER_H 1

/* Define if you have the <assert.h> header file.  */
#define HAVE_ASSERT_H 1

/* Define if you have the <atomic.h> header file.  */
/* #undef HAVE_ATOMIC_H */

/* Define if you have the <crypt.h> header file.  */
/* #undef HAVE_CRYPT_H */

/* Define if you have the <default_store.h> header file.  */
/* #undef HAVE_DEFAULT_STORE_H */

/* Define if you have the <dirent.h> header file.  */
#define HAVE_DIRENT_H 1

/* Define if you have the <dlfcn.h> header file.  */
#define HAVE_DLFCN_H 1

/* Define if you have the <dns.h> header file.  */
#define HAVE_DNS_H 1

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <fcntl.h> header file.  */
#define HAVE_FCNTL_H 1

/* Define if you have the <grp.h> header file.  */
#define HAVE_GRP_H 1

/* Define if you have the <ieeefp.h> header file.  */
/* #undef HAVE_IEEEFP_H */

/* Define if you have the <inttypes.h> header file.  */
#define HAVE_INTTYPES_H 1

/* Define if you have the <langinfo.h> header file.  */
#define HAVE_LANGINFO_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file.  */
#define HAVE_LOCALE_H 1

/* Define if you have the <malloc.h> header file.  */
/* #undef HAVE_MALLOC_H */

/* Define if you have the <monetary.h> header file.  */
#define HAVE_MONETARY_H 1

/* Define if you have the <ndir.h> header file.  */
/* #undef HAVE_NDIR_H */

/* Define if you have the <netdb.h> header file.  */
#define HAVE_NETDB_H 1

/* Define if you have the <netinet/in.h> header file.  */
#define HAVE_NETINET_IN_H 1

/* Define if you have the <netinet/tcp.h> header file.  */
#define HAVE_NETINET_TCP_H 1

/* Define if you have the <openssl/crypto.h> header file.  */
#define HAVE_OPENSSL_CRYPTO_H 1

/* Define if you have the <pwd.h> header file.  */
#define HAVE_PWD_H 1

/* Define if you have the <resolv.h> header file.  */
#define HAVE_RESOLV_H 1

/* Define if you have the <signal.h> header file.  */
#define HAVE_SIGNAL_H 1

/* Define if you have the <st.h> header file.  */
/* #undef HAVE_ST_H */

/* Define if you have the <stdarg.h> header file.  */
#define HAVE_STDARG_H 1

/* Define if you have the <stdbool.h> header file.  */
/* #undef HAVE_STDBOOL_H */

/* Define if you have the <stdint.h> header file.  */
#define HAVE_STDINT_H 1

/* Define if you have the <stdio.h> header file.  */
/* #undef HAVE_STDIO_H */

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
#define HAVE_STRINGS_H 1

/* Define if you have the <sys/dir.h> header file.  */
/* #undef HAVE_SYS_DIR_H */

/* Define if you have the <sys/file.h> header file.  */
#define HAVE_SYS_FILE_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/ipc.h> header file.  */
#define HAVE_SYS_IPC_H 1

/* Define if you have the <sys/loadavg.h> header file.  */
/* #undef HAVE_SYS_LOADAVG_H */

/* Define if you have the <sys/mkdev.h> header file.  */
/* #undef HAVE_SYS_MKDEV_H */

/* Define if you have the <sys/mman.h> header file.  */
#define HAVE_SYS_MMAN_H 1

/* Define if you have the <sys/mount.h> header file.  */
#define HAVE_SYS_MOUNT_H 1

/* Define if you have the <sys/ndir.h> header file.  */
/* #undef HAVE_SYS_NDIR_H */

/* Define if you have the <sys/param.h> header file.  */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/poll.h> header file.  */
#define HAVE_SYS_POLL_H 1

/* Define if you have the <sys/resource.h> header file.  */
#define HAVE_SYS_RESOURCE_H 1

/* Define if you have the <sys/select.h> header file.  */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/socket.h> header file.  */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/stat.h> header file.  */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/statfs.h> header file.  */
/* #undef HAVE_SYS_STATFS_H */

/* Define if you have the <sys/statvfs.h> header file.  */
#define HAVE_SYS_STATVFS_H 1

/* Define if you have the <sys/sysexits.h> header file.  */
/* #undef HAVE_SYS_SYSEXITS_H */

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/times.h> header file.  */
#define HAVE_SYS_TIMES_H 1

/* Define if you have the <sys/types.h> header file.  */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/uio.h> header file.  */
/* #undef HAVE_SYS_UIO_H */

/* Define if you have the <sys/un.h> header file.  */
#define HAVE_SYS_UN_H 1

/* Define if you have the <sys/utsname.h> header file.  */
#define HAVE_SYS_UTSNAME_H 1

/* Define if you have the <sys/varargs.h> header file.  */
/* #undef HAVE_SYS_VARARGS_H */

/* Define if you have the <sys/vfs.h> header file.  */
/* #undef HAVE_SYS_VFS_H */

/* Define if you have the <sys/wait.h> header file.  */
#define HAVE_SYS_WAIT_H 1

/* Define if you have the <sysexits.h> header file.  */
#define HAVE_SYSEXITS_H 1

/* Define if you have the <syslog.h> header file.  */
#define HAVE_SYSLOG_H 1

/* Define if you have the <termios.h> header file.  */
#define HAVE_TERMIOS_H 1

/* Define if you have the <time.h> header file.  */
#define HAVE_TIME_H 1

/* Define if you have the <tuxmodule.h> header file.  */
/* #undef HAVE_TUXMODULE_H */

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <unix.h> header file.  */
/* #undef HAVE_UNIX_H */

/* Define if you have the <utime.h> header file.  */
#define HAVE_UTIME_H 1

/* Define if you have the <wchar.h> header file.  */
#define HAVE_WCHAR_H 1

/* Define if you have the <xmlparse.h> header file.  */
/* #undef HAVE_XMLPARSE_H */

/* Define if you have the <xmltok.h> header file.  */
/* #undef HAVE_XMLTOK_H */

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* Define if the target system has /dev/urandom device */
#define HAVE_DEV_URANDOM 1

/* Whether you have AOLserver */
/* #undef HAVE_AOLSERVER */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_APACHE */

/*   */
/* #undef HAVE_APACHE */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef USE_TRANSFER_TABLES */

/*   */
/* #undef PHP_APACHE_HAVE_CLIENT_FD */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_APACHE_HOOKS */

/*   */
/* #undef HAVE_APACHE */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef HAVE_AP_CONFIG_H */

/*   */
/* #undef HAVE_AP_COMPAT_H */

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef USE_TRANSFER_TABLES */

/*   */
/* #undef PHP_APACHE_HAVE_CLIENT_FD */

/* Whether to compile with Caudium support */
/* #undef HAVE_CAUDIUM */

/* Whether you have a Continuity Server */
/* #undef HAVE_CONTINUITY */

/* do we have prctl? */
/* #undef HAVE_PRCTL */

/* do we have clock_gettime? */
/* #undef HAVE_CLOCK_GETTIME */

/* do we have clock_get_time? */
/* #undef HAVE_CLOCK_GET_TIME */

/* do we have ptrace? */
/* #undef HAVE_PTRACE */

/* do we have mach_vm_read? */
/* #undef HAVE_MACH_VM_READ */

/* /proc/pid/mem interface */
/* #undef PROC_MEM_FILE */

/* Define to 1 if gcc supports __sync_bool_compare_and_swap() a.o. */
/* #undef HAVE_BUILTIN_ATOMIC */

/* do we have TCP_INFO? */
/* #undef HAVE_LQ_TCP_INFO */

/* do we have SO_LISTENQxxx? */
/* #undef HAVE_LQ_SO_LISTENQ */

/* fpm user name */
/* #undef PHP_FPM_USER */

/* fpm group name */
/* #undef PHP_FPM_GROUP */

/*   */
/* #undef WITH_ZEUS */

/* Whether you have a Netscape/iPlanet/Sun Webserver */
/* #undef HAVE_NSAPI */

/* Whether you have phttpd */
/* #undef HAVE_PHTTPD */

/* whether you want Pi3Web support */
/* #undef WITH_PI3WEB */

/* Whether you use Roxen */
/* #undef HAVE_ROXEN */

/* Whether to use Roxen in ZTS mode */
/* #undef ROXEN_USE_ZTS */

/* Define if the socklen_t typedef is in sys/socket.h */
#define HAVE_SOCKLEN_T 1

/* Define if sockaddr_un in sys/un.h contains a sun_len component */
/* #undef HAVE_SOCKADDR_UN_SUN_LEN */

/* Define if cross-process locking is required by accept() */
/* #undef USE_LOCKING */

/* Define if system uses EBCDIC */
/* #undef CHARSET_EBCDIC */

/* Define if processor uses big-endian word */
/* #undef WORDS_BIGENDIAN */

/* whether write(2) works */
#define PHP_WRITE_STDOUT 1

/*   */
#define HAVE_SOCKET 1

/*   */
#define HAVE_SOCKET 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_SOCKETPAIR 1

/*   */
#define HAVE_SOCKETPAIR 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_HTONL 1

/*   */
#define HAVE_HTONL 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_GETHOSTNAME 1

/*   */
#define HAVE_GETHOSTNAME 1

/*   */
/* #undef HAVE_LIBNSL */

/*   */
#define HAVE_GETHOSTBYADDR 1

/*   */
#define HAVE_GETHOSTBYADDR 1

/*   */
/* #undef HAVE_LIBNSL */

/*   */
#define HAVE_YP_GET_DEFAULT_DOMAIN 1

/*   */
#define HAVE_YP_GET_DEFAULT_DOMAIN 1

/*   */
/* #undef HAVE_LIBNSL */

/*   */
#define HAVE_DLOPEN 1

/*   */
#define HAVE_DLOPEN 1

/*   */
#define HAVE_LIBDL 1

/*   */
#define HAVE_LIBDL 1

/*   */
#define HAVE_INET_ATON 1

/*   */
#define HAVE_INET_ATON 1

/*   */
#define HAVE_LIBRESOLV 1

/*   */
#define HAVE_INET_ATON 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
/* #undef HAVE_FOPENCOOKIE */

/*   */
/* #undef COOKIE_IO_FUNCTIONS_T */

/*   */
/* #undef COOKIE_SEEKER_USES_OFF64_T */

/* Define if system has broken getcwd */
/* #undef HAVE_BROKEN_GETCWD */

/* Define if your glibc borks on fopen with mode a+ */
/* #undef HAVE_BROKEN_GLIBC_FOPEN_APPEND */

/* Whether localtime_r is declared */
/* #undef MISSING_LOCALTIME_R_DECL */

/* Whether gmtime_r is declared */
/* #undef MISSING_GMTIME_R_DECL */

/* Whether asctime_r is declared */
/* #undef MISSING_ASCTIME_R_DECL */

/* Whether ctime_r is declared */
/* #undef MISSING_CTIME_R_DECL */

/* Whether strtok_r is declared */
/* #undef MISSING_STRTOK_R_DECL */

/*   */
#define MISSING_FCLOSE_DECL 0

/*   */
#define MISSING_FCLOSE_DECL 0

/* whether you have tm_gmtoff in struct tm */
#define HAVE_TM_GMTOFF 1

/* whether you have struct flock */
#define HAVE_STRUCT_FLOCK 1

/* Whether you have socklen_t */
#define HAVE_SOCKLEN_T 1

/* Size of intmax_t */
#define SIZEOF_INTMAX_T 8

/* Whether intmax_t is available */
#define HAVE_INTMAX_T 1

/* Size of ssize_t */
#define SIZEOF_SSIZE_T 8

/* Whether ssize_t is available */
#define HAVE_SSIZE_T 1

/* Size of ptrdiff_t */
#define SIZEOF_PTRDIFF_T 8

/* Whether ptrdiff_t is available */
#define HAVE_PTRDIFF_T 1

/* Whether you have struct sockaddr_storage */
#define HAVE_SOCKADDR_STORAGE 1

/* Whether struct sockaddr has field sa_len */
#define HAVE_SOCKADDR_SA_LEN 1

/*   */
#define HAVE_NANOSLEEP 1

/*   */
/* #undef HAVE_LIBRT */

/* Define if you have the getaddrinfo function */
#define HAVE_GETADDRINFO 1

/* Whether system headers declare timezone */
#define HAVE_DECLARED_TIMEZONE 1

/* Whether you have HP-UX 10.x */
/* #undef PHP_HPUX_TIME_R */

/* Whether you have IRIX-style functions */
/* #undef PHP_IRIX_TIME_R */

/* whether you have POSIX readdir_r */
#define HAVE_POSIX_READDIR_R 1

/* whether you have old-style readdir_r */
/* #undef HAVE_OLD_READDIR_R */

/*   */
/* #undef in_addr_t */

/* Define if crypt_r has uses CRYPTD */
/* #undef CRYPT_R_CRYPTD */

/* Define if crypt_r uses struct crypt_data */
/* #undef CRYPT_R_STRUCT_CRYPT_DATA */

/* Define if struct crypt_data requires _GNU_SOURCE */
/* #undef CRYPT_R_GNU_SOURCE */

/* Whether you have gcov */
/* #undef HAVE_GCOV */

/*   */
#define PHP_SAFE_MODE 0

/*   */
#define PHP_SAFE_MODE 0

/*   */
#define PHP_SAFE_MODE_EXEC_DIR "/usr/local/php/bin"

/*   */
#define PHP_SAFE_MODE_EXEC_DIR "/usr/local/php/bin"

/*   */
#define PHP_SIGCHILD 0

/*   */
#define PHP_SIGCHILD 0

/*   */
#define MAGIC_QUOTES 0

/*   */
#define MAGIC_QUOTES 0

/*   */
#define DEFAULT_SHORT_OPEN_TAG "1"

/*   */
#define DEFAULT_SHORT_OPEN_TAG "1"

/* Whether you have dmalloc */
/* #undef HAVE_DMALLOC */

/* Whether to enable IPv6 support */
#define HAVE_IPV6 1

/*  Define if int32_t type is present.  */
#define HAVE_INT32_T 1

/*  Define if uint32_t type is present.  */
#define HAVE_UINT32_T 1

/* Whether to build date as dynamic module */
/* #undef COMPILE_DL_DATE */

/* Whether to build ereg as dynamic module */
/* #undef COMPILE_DL_EREG */

/*   */
#define HAVE_REGEX_T_RE_MAGIC 1

/*   */
#define HSREGEX 1

/*   */
#define REGEX 1

/*   */
#define REGEX 1

/* 1 */
#define HAVE_REGEX_T_RE_MAGIC 1

/*   */
#define HAVE_LIBXML 1

/*   */
#define HAVE_LIBXML 1

/* Whether to build libxml as dynamic module */
/* #undef COMPILE_DL_LIBXML */

/* Whether to build openssl as dynamic module */
/* #undef COMPILE_DL_OPENSSL */

/* OpenSSL 0.9.7 or later */
/* #undef HAVE_DSA_DEFAULT_METHOD */

/*   */
#define HAVE_OPENSSL_EXT 1

/*   */
#define HAVE_PCRE 1

/* Whether to build pcre as dynamic module */
/* #undef COMPILE_DL_PCRE */

/* Whether to build pcre as dynamic module */
/* #undef COMPILE_DL_PCRE */

/*   */
/* #undef HAVE_BUNDLED_PCRE */

/* have commercial sqlite3 with crypto support */
/* #undef HAVE_SQLITE3_KEY */

/* have sqlite3 with extension support */
/* #undef SQLITE_OMIT_LOAD_EXTENSION */

/*   */
#define HAVE_SQLITE3 1

/* Whether to build sqlite3 as dynamic module */
/* #undef COMPILE_DL_SQLITE3 */

/* Whether to build zlib as dynamic module */
/* #undef COMPILE_DL_ZLIB */

/*   */
#define HAVE_ZLIB 1

/* Whether to build bcmath as dynamic module */
/* #undef COMPILE_DL_BCMATH */

/* Whether you have bcmath */
#define HAVE_BCMATH 1

/*   */
#define HAVE_BZ2 1

/* Whether to build bz2 as dynamic module */
/* #undef COMPILE_DL_BZ2 */

/*   */
#define HAVE_CALENDAR 1

/* Whether to build calendar as dynamic module */
/* #undef COMPILE_DL_CALENDAR */

/*   */
#define HAVE_CTYPE 1

/* Whether to build ctype as dynamic module */
/* #undef COMPILE_DL_CTYPE */

/* Have cURL with  SSL support */
#define HAVE_CURL_SSL 1

/* Have cURL with OpenSSL support */
#define HAVE_CURL_OPENSSL 1

/* Have cURL with GnuTLS support */
/* #undef HAVE_CURL_GNUTLS */

/*   */
#define HAVE_CURL 1

/*   */
#define HAVE_CURL_VERSION_INFO 1

/*   */
#define HAVE_CURL_EASY_STRERROR 1

/*   */
#define HAVE_CURL_MULTI_STRERROR 1

/*   */
/* #undef PHP_CURL_URL_WRAPPERS */

/* Whether to build curl as dynamic module */
/* #undef COMPILE_DL_CURL */

/*   */
/* #undef QDBM_INCLUDE_FILE */

/*   */
/* #undef DBA_QDBM */

/*   */
/* #undef GDBM_INCLUDE_FILE */

/*   */
/* #undef DBA_GDBM */

/*   */
/* #undef NDBM_INCLUDE_FILE */

/*   */
/* #undef DBA_NDBM */

/*   */
/* #undef DBA_DB4 */

/*   */
/* #undef DB4_INCLUDE_FILE */

/*   */
/* #undef DBA_DB3 */

/*   */
/* #undef DB3_INCLUDE_FILE */

/*   */
/* #undef DBA_DB2 */

/*   */
/* #undef DB2_INCLUDE_FILE */

/*   */
/* #undef DB1_VERSION */

/*   */
/* #undef DB1_VERSION */

/*   */
/* #undef DB1_INCLUDE_FILE */

/*   */
/* #undef DBA_DB1 */

/*   */
/* #undef DBM_INCLUDE_FILE */

/*   */
/* #undef DBM_VERSION */

/*   */
/* #undef DBM_VERSION */

/*   */
/* #undef DBA_DBM */

/*   */
/* #undef DBA_CDB_BUILTIN */

/*   */
/* #undef DBA_CDB_MAKE */

/*   */
/* #undef DBA_CDB */

/*   */
/* #undef CDB_INCLUDE_FILE */

/*   */
/* #undef DBA_CDB */

/*   */
/* #undef DBA_INIFILE */

/*   */
/* #undef DBA_FLATFILE */

/*   */
/* #undef HAVE_DBA */

/* Whether to build dba as dynamic module */
/* #undef COMPILE_DL_DBA */

/*   */
#define HAVE_LIBXML 1

/*   */
#define HAVE_DOM 1

/* Whether to build dom as dynamic module */
/* #undef COMPILE_DL_DOM */

/* Whether to build enchant as dynamic module */
/* #undef COMPILE_DL_ENCHANT */

/*   */
/* #undef HAVE_ENCHANT */

/*   */
/* #undef HAVE_ENCHANT_BROKER_SET_PARAM */

/*   */
/* #undef ENCHANT_VERSION_STRING */

/* Whether you want EXIF (metadata from images) support */
#define HAVE_EXIF 1

/* Whether to build exif as dynamic module */
/* #undef COMPILE_DL_EXIF */

/* Whether to build fileinfo as dynamic module */
/* #undef COMPILE_DL_FILEINFO */

/* Whether to build filter as dynamic module */
/* #undef COMPILE_DL_FILTER */

/* Whether you want FTP support */
#define HAVE_FTP 1

/* Whether to build ftp as dynamic module */
/* #undef COMPILE_DL_FTP */

/*   */
#define USE_GD_IMGSTRTTF 1

/*   */
#define USE_GD_IMGSTRTTF 1

/*   */
/* #undef HAVE_LIBFREETYPE */

/*   */
/* #undef ENABLE_GD_TTF */

/*   */
/* #undef HAVE_LIBT1 */

/*   */
#define HAVE_LIBGD 1

/*   */
#define HAVE_LIBGD13 1

/*   */
#define HAVE_LIBGD15 1

/*   */
#define HAVE_LIBGD20 1

/*   */
#define HAVE_LIBGD204 1

/*   */
#define HAVE_GD_IMAGESETTILE 1

/*   */
#define HAVE_GD_IMAGESETBRUSH 1

/*   */
#define HAVE_GDIMAGECOLORRESOLVE 1

/*   */
#define HAVE_COLORCLOSESTHWB 1

/*   */
#define HAVE_GD_WBMP 1

/*   */
#define HAVE_GD_GD2 1

/*   */
#define HAVE_GD_PNG 1

/*   */
#define HAVE_GD_XBM 1

/*   */
#define HAVE_GD_BUNDLED 1

/*   */
#define HAVE_GD_GIF_READ 1

/*   */
#define HAVE_GD_GIF_CREATE 1

/*   */
#define HAVE_GD_IMAGEELLIPSE 1

/*   */
#define HAVE_GD_FONTCACHESHUTDOWN 1

/*   */
#define HAVE_GD_FONTMUTEX 1

/*   */
#define HAVE_GD_DYNAMIC_CTX_EX 1

/*   */
#define HAVE_GD_GIF_CTX 1

/*   */
#define HAVE_GD_JPG 1

/*   */
/* #undef HAVE_GD_XPM */

/*   */
/* #undef HAVE_GD_STRINGFT */

/*   */
/* #undef HAVE_GD_STRINGFTEX */

/*   */
/* #undef ENABLE_GD_TTF */

/*   */
/* #undef USE_GD_JISX0208 */

/*   */
#define USE_GD_IMGSTRTTF 1

/*   */
#define USE_GD_IMGSTRTTF 1

/*   */
/* #undef HAVE_LIBFREETYPE */

/*   */
/* #undef ENABLE_GD_TTF */

/*   */
/* #undef HAVE_LIBT1 */

/*   */
#define HAVE_LIBGD 1

/*   */
#define HAVE_LIBGD13 1

/*   */
#define HAVE_LIBGD15 1

/*   */
#define HAVE_GD_PNG 1

/*   */
#define HAVE_GD_GIF_READ 1

/*   */
#define HAVE_GD_GIF_CREATE 1

/*   */
#define HAVE_GD_WBMP 1

/*   */
#define HAVE_GD_JPG 1

/*   */
/* #undef HAVE_GD_XPM */

/*   */
#define HAVE_GD_GD2 1

/*   */
#define HAVE_LIBGD20 1

/*   */
#define HAVE_GD_IMAGESETTILE 1

/*   */
#define HAVE_GD_IMAGEELLIPSE 1

/*   */
#define HAVE_GD_IMAGESETBRUSH 1

/*   */
/* #undef HAVE_GD_STRINGTTF */

/*   */
/* #undef HAVE_GD_STRINGFT */

/*   */
/* #undef HAVE_GD_STRINGFTEX */

/*   */
#define HAVE_COLORCLOSESTHWB 1

/*   */
#define HAVE_GDIMAGECOLORRESOLVE 1

/*   */
#define HAVE_GD_GIF_CTX 1

/*   */
/* #undef HAVE_GD_CACHE_CREATE */

/*   */
#define HAVE_GD_FONTCACHESHUTDOWN 1

/*   */
/* #undef HAVE_GD_FREEFONTCACHE */

/*   */
#define HAVE_GD_FONTMUTEX 1

/*   */
#define HAVE_GD_DYNAMIC_CTX_EX 1

/*   */
#define HAVE_LIBGD204 1

/* Whether to build gd as dynamic module */
/* #undef COMPILE_DL_GD */

/*   */
/* #undef HAVE_LIBINTL */

/* Whether to build gettext as dynamic module */
/* #undef COMPILE_DL_GETTEXT */

/*   */
/* #undef HAVE_NGETTEXT */

/*   */
/* #undef HAVE_DNGETTEXT */

/*   */
/* #undef HAVE_DCNGETTEXT */

/*   */
/* #undef HAVE_BIND_TEXTDOMAIN_CODESET */

/* Whether to build gmp as dynamic module */
/* #undef COMPILE_DL_GMP */

/*   */
/* #undef HAVE_GMP */

/*   */
/* #undef PHP_MHASH_BC */

/* Have HASH Extension */
#define HAVE_HASH_EXT 1

/* Define if processor uses big-endian word */
/* #undef WORDS_BIGENDIAN */

/* Whether to build hash as dynamic module */
/* #undef COMPILE_DL_HASH */

/*   */
/* #undef HAVE_LIBICONV */

/*   */
/* #undef HAVE_GICONV_H */

/*   */
/* #undef HAVE_LIBICONV */

/* iconv() is aliased to libiconv() in -liconv */
/* #undef ICONV_ALIASED_LIBICONV */

/*   */
#define HAVE_ICONV 1

/* Which iconv implementation to use */
#define PHP_ICONV_IMPL "libiconv"

/* Konstantin Chuguev's iconv implementation */
/* #undef HAVE_BSD_ICONV */

/* Which iconv implementation to use */
#define PHP_ICONV_IMPL "libiconv"

/* glibc's iconv implementation */
/* #undef HAVE_GLIBC_ICONV */

/* Which iconv implementation to use */
#define PHP_ICONV_IMPL "libiconv"

/* IBM iconv implementation */
/* #undef HAVE_IBM_ICONV */

/* Which iconv implementation to use */
#define PHP_ICONV_IMPL "libiconv"

/* Whether iconv supports error no or not */
#define ICONV_SUPPORTS_ERRNO 1

/* Whether iconv supports error no or not */
#define ICONV_SUPPORTS_ERRNO 1

/* Whether iconv supports error no or not */
#define ICONV_SUPPORTS_ERRNO 1

/* Path to iconv.h */
#define PHP_ICONV_H_PATH </usr/include/iconv.h>

/* Whether to build iconv as dynamic module */
/* #undef COMPILE_DL_ICONV */

/* Whether to build imap as dynamic module */
/* #undef COMPILE_DL_IMAP */

/*   */
/* #undef HAVE_IMAP */

/*   */
/* #undef HAVE_IMAP2000 */

/*   */
/* #undef HAVE_IMAP2000 */

/*   */
/* #undef HAVE_IMAP2000 */

/*   */
/* #undef HAVE_IMAP2000 */

/*   */
/* #undef HAVE_IMAP2000 */

/*   */
/* #undef HAVE_IMAP2000 */

/*   */
/* #undef HAVE_IMAP2004 */

/* Whether utf8_mime2text() has new signature */
/* #undef HAVE_NEW_MIME2TEXT */

/*   */
/* #undef HAVE_IMAP2001 */

/*   */
/* #undef HAVE_LIBPAM */

/*   */
/* #undef HAVE_LIBCRYPT */

/*   */
/* #undef HAVE_IMAP_KRB */

/*   */
/* #undef HAVE_IMAP_SSL */

/*   */
/* #undef HAVE_IMAP_AUTH_GSS */

/*   */
/* #undef HAVE_IMAP_MUTF7 */

/*   */
/* #undef HAVE_RFC822_OUTPUT_ADDRESS_LIST */

/*   */
/* #undef HAVE_IBASE */

/* Whether to build interbase as dynamic module */
/* #undef COMPILE_DL_INTERBASE */

/* Whether to build intl as dynamic module */
/* #undef COMPILE_DL_INTL */

/* whether to enable JavaScript Object Serialization support */
#define HAVE_JSON 1 

/* Whether to build json as dynamic module */
/* #undef COMPILE_DL_JSON */

/* Whether to build ldap as dynamic module */
/* #undef COMPILE_DL_LDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_ORALDAP */

/*   */
/* #undef HAVE_ORALDAP_10 */

/*   */
#define HAVE_LDAP 1

/* Whether 3 arg set_rebind_proc() */
#define HAVE_3ARG_SETREBINDPROC 1

/*   */
#define HAVE_LDAP_SASL_SASL_H 1

/*   */
/* #undef HAVE_LDAP_SASL_H */

/* LDAP SASL support */
#define HAVE_LDAP_SASL 1

/* whether to have multibyte string support */
#define HAVE_MBSTRING 1

/* whether to check multibyte regex backtrack */
#define USE_COMBINATION_EXPLOSION_CHECK 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_PROTOTYPES 1

/* Define to 1 if the bundled oniguruma is used */
#define PHP_ONIG_BUNDLED 1

/* Define to 1 if the oniguruma library is available */
#define HAVE_ONIG 1

/* Define to 1 if the oniguruma library is available */
#define HAVE_ONIG 1

/* define to 1 if oniguruma has an invalid entry for KOI8 encoding */
/* #undef PHP_ONIG_BAD_KOI8_ENTRY */

/* whether to have multibyte regex support */
#define HAVE_MBREGEX 1

/* Whether to build mbstring as dynamic module */
/* #undef COMPILE_DL_MBSTRING */

/*   */
/* #undef HAVE_LIBMCRYPT */

/*   */
/* #undef HAVE_LIBMCRYPT */

/* Whether to build mcrypt as dynamic module */
/* #undef COMPILE_DL_MCRYPT */

/* Whether to build mssql as dynamic module */
/* #undef COMPILE_DL_MSSQL */

/*   */
/* #undef HAVE_LIBDNET_STUB */

/*   */
/* #undef HAVE_MSSQL */

/*   */
/* #undef HAVE_FREETDS */

/*   */
#define PHP_MYSQL_UNIX_SOCK_ADDR "/var/mysql/mysql.sock"

/*   */
#define PHP_MYSQL_UNIX_SOCK_ADDR "/var/mysql/mysql.sock"

/* Whether you have MySQL */
#define HAVE_MYSQL 1

/* Whether to build mysql as dynamic module */
/* #undef COMPILE_DL_MYSQL */

/* Whether mysqlnd is enabled */
#define MYSQL_USE_MYSQLND 1

/* embedded MySQL support enabled */
/* #undef HAVE_EMBEDDED_MYSQLI */

/*   */
/* #undef HAVE_MYSQLILIB */

/*   */
/* #undef HAVE_STMT_NEXT_RESULT */

/* Whether to build mysqli as dynamic module */
/* #undef COMPILE_DL_MYSQLI */

/* Whether mysqlnd is enabled */
#define MYSQLI_USE_MYSQLND 1

/*   */
/* #undef HAVE_OCI_LOB_READ2 */

/* Whether to build oci8 as dynamic module */
/* #undef COMPILE_DL_OCI8 */

/*   */
/* #undef HAVE_OCI8 */

/*   */
/* #undef PHP_OCI8_DEF_DIR */

/*   */
/* #undef PHP_OCI8_DEF_SHARED_LIBADD */

/*   */
/* #undef HAVE_OCI_INSTANT_CLIENT */

/*   */
/* #undef HAVE_OCI_LOB_READ2 */

/* Whether to build oci8 as dynamic module */
/* #undef COMPILE_DL_OCI8 */

/*   */
/* #undef HAVE_OCI8 */

/*   */
/* #undef HAVE_ADABAS */

/*   */
/* #undef HAVE_SAPDB */

/*   */
/* #undef HAVE_SOLID_35 */

/*   */
/* #undef HAVE_SOLID_30 */

/*   */
/* #undef HAVE_SOLID */

/* Needed in sqlunix.h  */
/* #undef SS_LINUX */

/* Needed in sqlunix.h  */
/* #undef SS_LINUX */

/* Needed in sqlunix.h for wchar defs  */
/* #undef SS_FBX */

/* Needed in sqlunix.h for wchar defs  */
/* #undef SS_FBX */

/*   */
/* #undef HAVE_IBMDB2 */

/*   */
/* #undef HAVE_ODBC_ROUTER */

/*   */
/* #undef HAVE_EMPRESS */

/*   */
/* #undef HAVE_EMPRESS */

/*   */
/* #undef AIX */

/*   */
/* #undef HPUX */

/*   */
/* #undef LINUX */

/*   */
/* #undef NEUTRINO */

/*   */
/* #undef ISOLARIS */

/*   */
/* #undef SOLARIS */

/*   */
/* #undef UNIXWARE */

/*   */
/* #undef HAVE_BIRDSTEP */

/*   */
/* #undef HAVE_CODBC */

/*   */
#define HAVE_IODBC 1

/*   */
#define HAVE_ODBC2 1

/*   */
/* #undef HAVE_ESOOB */

/*   */
/* #undef HAVE_UNIXODBC */

/* Whether you want DBMaker */
/* #undef HAVE_DBMAKER */

/*   */
#define HAVE_SQLDATASOURCES 1

/*   */
#define HAVE_UODBC 1

/* Whether to build odbc as dynamic module */
/* #undef COMPILE_DL_ODBC */

/*   */
#define HAVE_FORK 1

/*   */
/* #undef HAVE_WAITPID */

/*   */
/* #undef HAVE_SIGACTION */

/* Whether to build pcntl as dynamic module */
/* #undef COMPILE_DL_PCNTL */

/* Whether to build pdo as dynamic module */
/* #undef COMPILE_DL_PDO */

/* Whether to build pdo_dblib as dynamic module */
/* #undef COMPILE_DL_PDO_DBLIB */

/*   */
/* #undef HAVE_LIBDNET_STUB */

/*   */
/* #undef HAVE_PDO_DBLIB */

/*   */
/* #undef HAVE_FREETDS */

/*   */
/* #undef HAVE_PDO_FIREBIRD */

/* Whether to build pdo_firebird as dynamic module */
/* #undef COMPILE_DL_PDO_FIREBIRD */

/* Whether pdo_mysql uses mysqlnd */
#define PDO_USE_MYSQLND 1

/* Whether you have MySQL */
#define HAVE_MYSQL 1

/*   */
/* #undef PDO_MYSQL_UNIX_ADDR */

/* Whether to build pdo_mysql as dynamic module */
/* #undef COMPILE_DL_PDO_MYSQL */

/*   */
/* #undef HAVE_OCIENVCREATE */

/*   */
/* #undef HAVE_OCIENVNLSCREATE */

/*   */
/* #undef HAVE_OCILOBISTEMPORARY */

/*   */
/* #undef HAVE_OCILOBISTEMPORARY */

/*   */
/* #undef HAVE_OCICOLLASSIGN */

/*   */
/* #undef HAVE_OCISTMTFETCH2 */

/* Whether to build pdo_oci as dynamic module */
/* #undef COMPILE_DL_PDO_OCI */

/*   */
/* #undef PHP_PDO_OCI_CLIENT_VERSION */

/*   */
/* #undef HAVE_ODBC_H */

/*   */
/* #undef HAVE_ODBCSDK_H */

/*   */
/* #undef HAVE_IODBC_H */

/*   */
/* #undef HAVE_SQLUNIX_H */

/*   */
/* #undef HAVE_SQLTYPES_H */

/*   */
/* #undef HAVE_SQLUCODE_H */

/*   */
/* #undef HAVE_SQL_H */

/*   */
/* #undef HAVE_ISQL_H */

/*   */
/* #undef HAVE_SQLEXT_H */

/*   */
/* #undef HAVE_ISQLEXT_H */

/*   */
/* #undef HAVE_UDBCEXT_H */

/*   */
/* #undef HAVE_SQLCLI1_H */

/*   */
/* #undef HAVE_LIBRARYMANAGER_H */

/*   */
/* #undef HAVE_CLI0CORE_H */

/*   */
/* #undef HAVE_CLI0EXT_H */

/*   */
/* #undef HAVE_CLI0CLI_H */

/*   */
/* #undef HAVE_CLI0DEFS_H */

/*   */
/* #undef HAVE_CLI0ENV_H */

/* Whether to build pdo_odbc as dynamic module */
/* #undef COMPILE_DL_PDO_ODBC */

/* Whether to have pg_config.h */
/* #undef HAVE_PG_CONFIG_H */

/* Whether to have pg_config.h */
/* #undef HAVE_PG_CONFIG_H */

/* Whether to build PostgreSQL for PDO support or not */
/* #undef HAVE_PDO_PGSQL */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQPARAMETERSTATUS */

/* PostgreSQL 8.0 or later */
/* #undef HAVE_PQPREPARE */

/* PostgreSQL 8.1.4 or later */
/* #undef HAVE_PQESCAPE_CONN */

/* PostgreSQL 8.1.4 or later */
/* #undef HAVE_PQESCAPE_BYTEA_CONN */

/* Whether libpq is compiled with --enable-multibyte */
/* #undef HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT */

/* Whether to build pdo_pgsql as dynamic module */
/* #undef COMPILE_DL_PDO_PGSQL */

/*   */
/* #undef HAVE_PDO_SQLITELIB */

/* have commercial sqlite3 with crypto support */
/* #undef HAVE_SQLITE3_KEY */

/* Whether to build pdo_sqlite as dynamic module */
/* #undef COMPILE_DL_PDO_SQLITE */

/* Whether to build pdo_sqlite as dynamic module */
/* #undef COMPILE_DL_PDO_SQLITE */

/* Whether to have pg_config.h */
/* #undef HAVE_PG_CONFIG_H */

/* Whether to have pg_config.h */
/* #undef HAVE_PG_CONFIG_H */

/* Whether to build PostgreSQL support or not */
/* #undef HAVE_PGSQL */

/* PostgreSQL 7.2.0 or later */
/* #undef HAVE_PQESCAPE */

/* PostgreSQL 7.3.0 or later */
/* #undef HAVE_PQUNESCAPEBYTEA */

/* PostgreSQL 7.0.x or later */
/* #undef HAVE_PQSETNONBLOCKING */

/* Broken libpq under windows */
/* #undef HAVE_PQCMDTUPLES */

/* Older PostgreSQL */
/* #undef HAVE_PQOIDVALUE */

/* PostgreSQL 7.0.x or later */
/* #undef HAVE_PQCLIENTENCODING */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQPARAMETERSTATUS */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQPROTOCOLVERSION */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PGTRANSACTIONSTATUS */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQEXECPARAMS */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQPREPARE */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQEXECPREPARED */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQRESULTERRORFIELD */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQSENDQUERYPARAMS */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQSENDPREPARE */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQSENDQUERYPREPARED */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQPUTCOPYDATA */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQPUTCOPYEND */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQGETCOPYDATA */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQFREEMEM */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQSETERRORVERBOSITY */

/* PostgreSQL 7.4 or later */
/* #undef HAVE_PQFTABLE */

/* PostgreSQL 8.1.4 or later */
/* #undef HAVE_PQESCAPE_CONN */

/* PostgreSQL 8.1.4 or later */
/* #undef HAVE_PQESCAPE_BYTEA_CONN */

/* Whether libpq is compiled with --enable-multibyte */
/* #undef HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT */

/* PostgreSQL 8.1 or later */
/* #undef HAVE_PG_LO_CREATE */

/* PostgreSQL 8.4 or later */
/* #undef HAVE_PG_LO_IMPORT_WITH_OID */

/* Whether to build pgsql as dynamic module */
/* #undef COMPILE_DL_PGSQL */

/* Whether to build phar as dynamic module */
/* #undef COMPILE_DL_PHAR */

/*   */
#define PHAR_HASH_OK 1

/*   */
/* #undef PHAR_HAVE_OPENSSL */

/* whether to include POSIX-like functions */
#define HAVE_POSIX 1

/* Whether to build posix as dynamic module */
/* #undef COMPILE_DL_POSIX */

/* Whether you have a working ttyname_r */
/* #undef HAVE_TTYNAME_R */

/* Wether struct utsname has domainname */
/* #undef HAVE_UTSNAME_DOMAINNAME */

/* Whether to build pspell as dynamic module */
/* #undef COMPILE_DL_PSPELL */

/*   */
/* #undef HAVE_PSPELL */

/*   */
/* #undef HAVE_RL_CALLBACK_READ_CHAR */

/*   */
/* #undef HAVE_LIBREADLINE */

/*   */
/* #undef HAVE_LIBEDIT */

/* Whether to build readline as dynamic module */
/* #undef COMPILE_DL_READLINE */

/* Whether we have librecode 3.5 */
/* #undef HAVE_BROKEN_RECODE */

/* Whether we have librecode 3.5 or higher */
/* #undef HAVE_LIBRECODE */

/* Whether to build recode as dynamic module */
/* #undef COMPILE_DL_RECODE */

/* Whether Reflection is enabled */
#define HAVE_REFLECTION 1

/* Whether to build reflection as dynamic module */
/* #undef COMPILE_DL_REFLECTION */

/*   */
#define HAVE_PWRITE 1

/* whether pwrite64 is default */
/* #undef PHP_PWRITE_64 */

/*   */
#define HAVE_PREAD 1

/* whether pread64 is default */
/* #undef PHP_PREAD_64 */

/* Whether to build session as dynamic module */
/* #undef COMPILE_DL_SESSION */

/*   */
#define HAVE_PHP_SESSION 1

/* Whether you have libmm */
/* #undef HAVE_LIBMM */

/*   */
#define HAVE_SHMOP 1

/* Whether to build shmop as dynamic module */
/* #undef COMPILE_DL_SHMOP */

/*   */
#define HAVE_LIBXML 1

/*   */
#define HAVE_SIMPLEXML 1

/* Whether to build simplexml as dynamic module */
/* #undef COMPILE_DL_SIMPLEXML */

/*   */
#define HAVE_NET_SNMP 1

/*   */
#define HAVE_SNMP_PARSE_OID 1

/*   */
#define HAVE_SNMP 1

/*   */
/* #undef UCD_SNMP_HACK */

/* Whether to build snmp as dynamic module */
/* #undef COMPILE_DL_SNMP */

/*   */
#define HAVE_LIBXML 1

/*   */
#define HAVE_SOAP 1

/* Whether to build soap as dynamic module */
/* #undef COMPILE_DL_SOAP */

/* Whether you have struct cmsghdr */
#define HAVE_CMSGHDR 1

/*   */
/* #undef MISSING_MSGHDR_MSGFLAGS */

/*   */
#define HAVE_SOCKETS 1

/* Whether to build sockets as dynamic module */
/* #undef COMPILE_DL_SOCKETS */

/* Whether struct _zend_object_value is packed */
#define HAVE_PACKED_OBJECT_VALUE 0

/* Whether you want SPL (Standard PHP Library) support */
#define HAVE_SPL 1

/* Whether to build spl as dynamic module */
/* #undef COMPILE_DL_SPL */

/* Have PDO */
#define PHP_SQLITE2_HAVE_PDO 1

/* Whether to build sqlite as dynamic module */
/* #undef COMPILE_DL_SQLITE */

/* Size of a pointer */
#define SQLITE_PTR_SZ SIZEOF_CHAR_P

/*   */
/* #undef SQLITE_UTF8 */

/* Define if flush should be called explicitly after a buffered io. */
#define HAVE_FLUSHIO 1

/*   */
#define HAVE_CRYPT 1

/* whether the compiler supports __alignof__ */
#define HAVE_ALIGNOF 1

/* whether the compiler supports __attribute__ ((__aligned__)) */
#define HAVE_ATTRIBUTE_ALIGNED 1

/* Whether PHP has to use its own crypt_r for blowfish, des, ext des and md5 */
#define PHP_USE_PHP_CRYPT_R 1

/* Whether the system supports standard DES salt */
#define PHP_STD_DES_CRYPT 1

/* Whether the system supports BlowFish salt */
#define PHP_BLOWFISH_CRYPT 1

/* Whether the system supports extended DES salt */
#define PHP_EXT_DES_CRYPT 1

/* Whether the system supports MD5 salt */
#define PHP_MD5_CRYPT 1

/* Whether the system supports SHA512 salt */
#define PHP_SHA512_CRYPT 1

/* Whether the system supports SHA256 salt */
#define PHP_SHA256_CRYPT 1

/* Whether the system supports standard DES salt */
#define PHP_STD_DES_CRYPT 1

/* Whether the system supports BlowFish salt */
#define PHP_BLOWFISH_CRYPT 1

/* Whether the system supports extended DES salt */
#define PHP_EXT_DES_CRYPT 1

/* Whether the system supports MD5 salt */
#define PHP_MD5_CRYPT 1

/* Whether the system supports SHA512 salt */
#define PHP_SHA512_CRYPT 1

/* Whether the system supports SHA256 salt */
#define PHP_SHA256_CRYPT 1

/* Whether PHP has to use its own crypt_r for blowfish, des and ext des */
#define PHP_USE_PHP_CRYPT_R 1

/* Define if your system has fork/vfork/CreateProcess */
#define PHP_CAN_SUPPORT_PROC_OPEN 1

/* Whether to enable chroot() function */
/* #undef ENABLE_CHROOT_FUNC */

/*   */
/* #undef HAVE_RES_NSEARCH */

/*   */
/* #undef HAVE_RES_NSEARCH */

/*   */
#define HAVE_LIBRESOLV 1

/*   */
/* #undef HAVE_RES_NSEARCH */

/*   */
/* #undef HAVE_LIBBIND */

/*   */
/* #undef HAVE_RES_NSEARCH */

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_DNS_SEARCH 1

/*   */
#define HAVE_DNS_SEARCH 1

/*   */
#define HAVE_LIBRESOLV 1

/*   */
#define HAVE_DNS_SEARCH 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define HAVE_DNS_SEARCH 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_DN_EXPAND 1

/*   */
#define HAVE_DN_EXPAND 1

/*   */
#define HAVE_LIBRESOLV 1

/*   */
#define HAVE_DN_EXPAND 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define HAVE_DN_EXPAND 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
#define HAVE_LIBRESOLV 1

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_RES_SEARCH 1

/*   */
#define HAVE_RES_SEARCH 1

/*   */
#define HAVE_LIBRESOLV 1

/*   */
#define HAVE_RES_SEARCH 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define HAVE_RES_SEARCH 1

/*   */
/* #undef HAVE_LIBSOCKET */

/* whether atof() accepts NAN */
#define HAVE_ATOF_ACCEPTS_NAN 1

/* whether atof() accepts INF */
#define HAVE_ATOF_ACCEPTS_INF 1

/* whether HUGE_VAL == INF */
#define HAVE_HUGE_VAL_INF 1

/* whether HUGE_VAL + -HUGEVAL == NAN */
#define HAVE_HUGE_VAL_NAN 1

/* whether strptime() declaration fails */
#define HAVE_STRPTIME_DECL_FAILS 1

/* Define if your system has mbstate_t in wchar.h */
/* #undef HAVE_MBSTATE_T */

/* Whether to build standard as dynamic module */
/* #undef COMPILE_DL_STANDARD */

/*   */
/* #undef HAVE_SYBASE_CT */

/* Whether to build sybase_ct as dynamic module */
/* #undef COMPILE_DL_SYBASE_CT */

/*   */
#define HAVE_SYSVMSG 1

/* Whether to build sysvmsg as dynamic module */
/* #undef COMPILE_DL_SYSVMSG */

/* Whether to build sysvsem as dynamic module */
/* #undef COMPILE_DL_SYSVSEM */

/*   */
#define HAVE_SYSVSEM 1

/*   */
#define HAVE_SEMUN 1

/*   */
#define HAVE_SEMUN 1

/*   */
#define HAVE_SYSVSHM 1

/* Whether to build sysvshm as dynamic module */
/* #undef COMPILE_DL_SYSVSHM */

/*   */
/* #undef HAVE_TIDYOPTGETDOC */

/* Whether to build tidy as dynamic module */
/* #undef COMPILE_DL_TIDY */

/*   */
/* #undef HAVE_TIDY */

/* Whether to build tokenizer as dynamic module */
/* #undef COMPILE_DL_TOKENIZER */

/*   */
#define HAVE_LIBXML 1

/*   */
/* #undef HAVE_LIBEXPAT */

/*   */
#define HAVE_WDDX 1

/* Whether to build wddx as dynamic module */
/* #undef COMPILE_DL_WDDX */

/*   */
#define HAVE_LIBXML 1

/*   */
/* #undef HAVE_LIBEXPAT */

/* Whether to build xml as dynamic module */
/* #undef COMPILE_DL_XML */

/*   */
#define HAVE_XML 1

/*   */
#define HAVE_LIBXML 1

/*   */
#define HAVE_XMLREADER 1

/* Whether to build xmlreader as dynamic module */
/* #undef COMPILE_DL_XMLREADER */

/*   */
#define HAVE_XMLRPC 1

/*   */
#define HAVE_LIBXML 1

/*   */
/* #undef HAVE_LIBEXPAT */

/*   */
/* #undef HAVE_LIBICONV */

/*   */
/* #undef HAVE_GICONV_H */

/*   */
/* #undef HAVE_LIBICONV */

/* iconv() is aliased to libiconv() in -liconv */
/* #undef ICONV_ALIASED_LIBICONV */

/*   */
#define HAVE_ICONV 1

/*   */
#define UNDEF_THREADS_HACK 

/* Whether to build xmlrpc as dynamic module */
/* #undef COMPILE_DL_XMLRPC */

/* Whether to build xmlrpc as dynamic module */
/* #undef COMPILE_DL_XMLRPC */

/*   */
#define HAVE_LIBXML 1

/*   */
#define HAVE_XMLWRITER 1

/* Whether to build xmlwriter as dynamic module */
/* #undef COMPILE_DL_XMLWRITER */

/*   */
#define HAVE_XSL_EXSLT 1

/*   */
#define HAVE_XSL 1

/* Whether to build xsl as dynamic module */
/* #undef COMPILE_DL_XSL */

/*   */
#define HAVE_ZIP 1

/* Whether to build zip as dynamic module */
/* #undef COMPILE_DL_ZIP */

/* Whether to build mysqlnd as dynamic module */
/* #undef COMPILE_DL_MYSQLND */

/* Enable compressed protocol support */
/* #undef MYSQLND_COMPRESSION_ENABLED */

/* Enable SSL support */
#define MYSQLND_SSL_SUPPORTED 1

/* Define if int32_t type is present.  */
#define HAVE_INT32_T 1

/* Define if uint32_t type is present.  */
#define HAVE_UINT32_T 1

/* Whether sprintf is broken */
#define ZEND_BROKEN_SPRINTF 0

/* whether floatingpoint.h defines fp_except */
/* #undef HAVE_FP_EXCEPT */

/* whether _FPU_SETCW is present and usable */
/* #undef HAVE__FPU_SETCW */

/* whether fpsetprec is present and usable */
/* #undef HAVE_FPSETPREC */

/* whether _controlfp is present usable */
/* #undef HAVE__CONTROLFP */

/* whether _controlfp_s is present and usable */
/* #undef HAVE__CONTROLFP_S */

/* whether FPU control word can be manipulated by inline assembler */
/* #undef HAVE_FPU_INLINE_ASM_X86 */

/* Define if double cast to long preserves least significant bits */
/* #undef ZEND_DVAL_TO_LVAL_CAST_OK */

/* Define if dlsym() requires a leading underscore in symbol names.  */
/* #undef DLSYM_NEEDS_UNDERSCORE */

/* virtual machine dispatch method */
#define ZEND_VM_KIND ZEND_VM_KIND_CALL

/* virtual machine dispatch method */
#define ZEND_VM_KIND ZEND_VM_KIND_CALL

/* virtual machine dispatch method */
#define ZEND_VM_KIND ZEND_VM_KIND_CALL

/*   */
#define ZEND_DEBUG 0

/*   */
#define ZEND_DEBUG 0

/*   */
/* #undef ZTS */

/*   */
#define ZEND_MULTIBYTE 1

/* Define if the target system is darwin */
#define DARWIN 1

/*   */
#define ZEND_MM_ALIGNMENT 8

/*   */
#define ZEND_MM_ALIGNMENT_LOG2 3

/* Define if the target system has support for memory allocation using mmap(MAP_ANON) */
#define HAVE_MEM_MMAP_ANON 1

/* Define if the target system has support for memory allocation using mmap(/dev/zero) */
/* #undef HAVE_MEM_MMAP_ZERO */

/*   */
/* #undef ZTS */

/* Whether you use GNU Pth */
/* #undef GNUPTH */

/*   */
/* #undef TSRM_ST */

/* Whether to use native BeOS threads */
/* #undef BETHREADS */

/* Whether to use Pthreads */
/* #undef PTHREADS */

/* PHP build date */
#define PHP_BUILD_DATE "2010-12-15"

/* hardcode for each of the cross compiler host */
#define PHP_OS "Darwin"

/* hardcode for each of the cross compiler host */
#define PHP_UNAME "Darwin b01.apple.com 10.0 Darwin Kernel Version 10.0.0: Fri Jul 31 22:46:25 PDT 2009; root:xnu-1456.1.25~1/RELEASE_X86_64 x86_64"

/* uname -a output */
#define PHP_UNAME "Darwin b01.apple.com 10.0 Darwin Kernel Version 10.0.0: Fri Jul 31 22:46:25 PDT 2009; root:xnu-1456.1.25~1/RELEASE_X86_64 x86_64"

/* uname output */
#define PHP_OS "Darwin"

/*   */
#define HAVE_BUILD_DEFS_H 1


#ifndef ZEND_ACCONFIG_H_NO_C_PROTOS

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef HAVE_IEEEFP_H
# include <ieeefp.h>
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif

#if ZEND_BROKEN_SPRINTF
int zend_sprintf(char *buffer, const char *format, ...);
#else
# define zend_sprintf sprintf
#endif

#include <math.h>

/* To enable the is_nan, is_infinite and is_finite PHP functions */
#ifdef NETWARE
	#define HAVE_ISNAN 1
	#define HAVE_ISINF 1
	#define HAVE_ISFINITE 1
#endif

#ifndef zend_isnan
#ifdef HAVE_ISNAN
#define zend_isnan(a) isnan(a)
#elif defined(HAVE_FPCLASS)
#define zend_isnan(a) ((fpclass(a) == FP_SNAN) || (fpclass(a) == FP_QNAN))
#else
#define zend_isnan(a) 0
#endif
#endif

#ifdef HAVE_ISINF
#define zend_isinf(a) isinf(a)
#elif defined(INFINITY)
/* Might not work, but is required by ISO C99 */
#define zend_isinf(a) (((a)==INFINITY)?1:0)
#elif defined(HAVE_FPCLASS)
#define zend_isinf(a) ((fpclass(a) == FP_PINF) || (fpclass(a) == FP_NINF))
#else
#define zend_isinf(a) 0
#endif

#ifdef HAVE_FINITE
#define zend_finite(a) finite(a)
#elif defined(HAVE_ISFINITE) || defined(isfinite)
#define zend_finite(a) isfinite(a)
#elif defined(fpclassify)
#define zend_finite(a) ((fpclassify((a))!=FP_INFINITE&&fpclassify((a))!=FP_NAN)?1:0)
#else
#define zend_finite(a) (zend_isnan(a) ? 0 : zend_isinf(a) ? 0 : 1)
#endif

#endif /* ifndef ZEND_ACCONFIG_H_NO_C_PROTOS */

#ifdef NETWARE
#ifdef USE_WINSOCK
#/*This detection against winsock is of no use*/ undef HAVE_SOCKLEN_T
#/*This detection against winsock is of no use*/ undef HAVE_SYS_SOCKET_H
#endif
#endif

/*
 * Darwin's GCC can generate multiple architectures in a single pass so the size and
 * byte order will only be accurate for the one architecture that happened to invoke
 * configure.
 */
#ifdef __DARWIN_BYTE_ORDER
#/* This symbol must be allowed to be cleared. */ undef WORDS_BIGENDIAN
# if (__DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN)
#  define WORDS_BIGENDIAN 1
# endif
#/* This symbol must be allowed to be cleared. */ undef SIZEOF_LONG
#/* This symbol must be allowed to be cleared. */ undef SIZEOF_SIZE_T
# ifdef __LP64__
#/* This symbol should not be modified by configure. */  define SIZEOF_LONG 8
#/* This symbol should not be modified by configure. */  define SIZEOF_SIZE_T 8
# else
#/* This symbol should not be modified by configure. */  define SIZEOF_LONG 4
#/* This symbol should not be modified by configure. */  define SIZEOF_SIZE_T 4
# endif
#endif

#endif	/* ZEND_API */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
/* #undef PTHREADS */
