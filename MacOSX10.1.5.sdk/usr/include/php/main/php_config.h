/* main/php_config.h.  Generated automatically by configure.  */
/* main/php_config.h.in.  Generated automatically from configure.in by autoheader.  */
/* Leave this file alone */
#define ZEND_API
#define ZEND_DLEXPORT


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
/* #undef HAVE_ALLOCA_H */

/* Define if you don't have vprintf but do have _doprnt.  */
/* #undef HAVE_DOPRNT */

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

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */

/* Define if lex declares yytext as a char * by default, not a char[].  */
/* #undef YYTEXT_POINTER */

/* #undef uint */
#define ulong unsigned long 

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 1

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* Define if you have the alarm function.  */
#define HAVE_ALARM 1

/* Define if you have the asctime_r function.  */
/* #undef HAVE_ASCTIME_R */

/* Define if you have the atod function.  */
/* #undef HAVE_ATOD */

/* Define if you have the bcmp function.  */
#define HAVE_BCMP 1

/* Define if you have the bfill function.  */
/* #undef HAVE_BFILL */

/* Define if you have the bmove function.  */
/* #undef HAVE_BMOVE */

/* Define if you have the bzero function.  */
#define HAVE_BZERO 1

/* Define if you have the chroot function.  */
#define HAVE_CHROOT 1

/* Define if you have the chsize function.  */
/* #undef HAVE_CHSIZE */

/* Define if you have the crypt function.  */
#define HAVE_CRYPT 1

/* Define if you have the ctermid function.  */
#define HAVE_CTERMID 1

/* Define if you have the ctime_r function.  */
/* #undef HAVE_CTIME_R */

/* Define if you have the cuserid function.  */
/* #undef HAVE_CUSERID */

/* Define if you have the dlerror function.  */
/* #undef HAVE_DLERROR */

/* Define if you have the dlopen function.  */
/* #undef HAVE_DLOPEN */

/* Define if you have the fchmod function.  */
#define HAVE_FCHMOD 1

/* Define if you have the fcntl function.  */
#define HAVE_FCNTL 1

/* Define if you have the fconvert function.  */
/* #undef HAVE_FCONVERT */

/* Define if you have the finite function.  */
#define HAVE_FINITE 1

/* Define if you have the flock function.  */
#define HAVE_FLOCK 1

/* Define if you have the fork function.  */
/* #undef HAVE_FORK */

/* Define if you have the fpclass function.  */
/* #undef HAVE_FPCLASS */

/* Define if you have the fpresetsticky function.  */
/* #undef HAVE_FPRESETSTICKY */

/* Define if you have the fpsetmask function.  */
/* #undef HAVE_FPSETMASK */

/* Define if you have the ftruncate function.  */
#define HAVE_FTRUNCATE 1

/* Define if you have the gai_strerror function.  */
#define HAVE_GAI_STRERROR 1

/* Define if you have the gcvt function.  */
/* #undef HAVE_GCVT */

/* Define if you have the getcwd function.  */
#define HAVE_GETCWD 1

/* Define if you have the gethostbyaddr function.  */
#define HAVE_GETHOSTBYADDR 1

/* Define if you have the gethostbyaddr_r function.  */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define if you have the gethostbyname_r function.  */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define if you have the getlogin function.  */
#define HAVE_GETLOGIN 1

/* Define if you have the getopt function.  */
#define HAVE_GETOPT 1

/* Define if you have the getpass function.  */
#define HAVE_GETPASS 1

/* Define if you have the getpassphrase function.  */
/* #undef HAVE_GETPASSPHRASE */

/* Define if you have the getpgid function.  */
/* #undef HAVE_GETPGID */

/* Define if you have the getpid function.  */
#define HAVE_GETPID 1

/* Define if you have the getprotobyname function.  */
#define HAVE_GETPROTOBYNAME 1

/* Define if you have the getprotobynumber function.  */
#define HAVE_GETPROTOBYNUMBER 1

/* Define if you have the getpwnam function.  */
#define HAVE_GETPWNAM 1

/* Define if you have the getpwuid function.  */
#define HAVE_GETPWUID 1

/* Define if you have the getrlimit function.  */
#define HAVE_GETRLIMIT 1

/* Define if you have the getrusage function.  */
#define HAVE_GETRUSAGE 1

/* Define if you have the getservbyname function.  */
#define HAVE_GETSERVBYNAME 1

/* Define if you have the getservbyport function.  */
#define HAVE_GETSERVBYPORT 1

/* Define if you have the getsid function.  */
/* #undef HAVE_GETSID */

/* Define if you have the gettimeofday function.  */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the getwd function.  */
#define HAVE_GETWD 1

/* Define if you have the gmtime_r function.  */
/* #undef HAVE_GMTIME_R */

/* Define if you have the hstrerror function.  */
/* #undef HAVE_HSTRERROR */

/* Define if you have the index function.  */
#define HAVE_INDEX 1

/* Define if you have the inet_aton function.  */
#define HAVE_INET_ATON 1

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

/* Define if you have the link function.  */
#define HAVE_LINK 1

/* Define if you have the localeconv function.  */
#define HAVE_LOCALECONV 1

/* Define if you have the localtime_r function.  */
/* #undef HAVE_LOCALTIME_R */

/* Define if you have the lockf function.  */
/* #undef HAVE_LOCKF */

/* Define if you have the locking function.  */
/* #undef HAVE_LOCKING */

/* Define if you have the longjmp function.  */
#define HAVE_LONGJMP 1

/* Define if you have the lrand48 function.  */
/* #undef HAVE_LRAND48 */

/* Define if you have the madvise function.  */
#define HAVE_MADVISE 1

/* Define if you have the memcpy function.  */
#define HAVE_MEMCPY 1

/* Define if you have the memmove function.  */
#define HAVE_MEMMOVE 1

/* Define if you have the mkfifo function.  */
#define HAVE_MKFIFO 1

/* Define if you have the mkstemp function.  */
#define HAVE_MKSTEMP 1

/* Define if you have the mmap function.  */
#define HAVE_MMAP 1

/* Define if you have the nl_langinfo function.  */
/* #undef HAVE_NL_LANGINFO */

/* Define if you have the perror function.  */
#define HAVE_PERROR 1

/* Define if you have the pread function.  */
/* #undef HAVE_PREAD */

/* Define if you have the pthread_attr_create function.  */
/* #undef HAVE_PTHREAD_ATTR_CREATE */

/* Define if you have the pthread_attr_setprio function.  */
/* #undef HAVE_PTHREAD_ATTR_SETPRIO */

/* Define if you have the pthread_attr_setschedparam function.  */
#define HAVE_PTHREAD_ATTR_SETSCHEDPARAM 1

/* Define if you have the pthread_attr_setstacksize function.  */
#define HAVE_PTHREAD_ATTR_SETSTACKSIZE 1

/* Define if you have the pthread_condattr_create function.  */
/* #undef HAVE_PTHREAD_CONDATTR_CREATE */

/* Define if you have the pthread_getsequence_np function.  */
/* #undef HAVE_PTHREAD_GETSEQUENCE_NP */

/* Define if you have the pthread_setprio function.  */
/* #undef HAVE_PTHREAD_SETPRIO */

/* Define if you have the pthread_setprio_np function.  */
/* #undef HAVE_PTHREAD_SETPRIO_NP */

/* Define if you have the pthread_setschedparam function.  */
#define HAVE_PTHREAD_SETSCHEDPARAM 1

/* Define if you have the pthread_sigmask function.  */
/* #undef HAVE_PTHREAD_SIGMASK */

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the pwrite function.  */
/* #undef HAVE_PWRITE */

/* Define if you have the rand_r function.  */
/* #undef HAVE_RAND_R */

/* Define if you have the random function.  */
#define HAVE_RANDOM 1

/* Define if you have the realpath function.  */
#define HAVE_REALPATH 1

/* Define if you have the regcomp function.  */
#define HAVE_REGCOMP 1

/* Define if you have the rename function.  */
#define HAVE_RENAME 1

/* Define if you have the res_search function.  */
#define HAVE_RES_SEARCH 1

/* Define if you have the rint function.  */
#define HAVE_RINT 1

/* Define if you have the rwlock_init function.  */
/* #undef HAVE_RWLOCK_INIT */

/* Define if you have the setegid function.  */
#define HAVE_SETEGID 1

/* Define if you have the seteuid function.  */
#define HAVE_SETEUID 1

/* Define if you have the setitimer function.  */
#define HAVE_SETITIMER 1

/* Define if you have the setlocale function.  */
#define HAVE_SETLOCALE 1

/* Define if you have the setpgid function.  */
#define HAVE_SETPGID 1

/* Define if you have the setsid function.  */
#define HAVE_SETSID 1

/* Define if you have the setsockopt function.  */
#define HAVE_SETSOCKOPT 1

/* Define if you have the setupterm function.  */
/* #undef HAVE_SETUPTERM */

/* Define if you have the setvbuf function.  */
#define HAVE_SETVBUF 1

/* Define if you have the shutdown function.  */
#define HAVE_SHUTDOWN 1

/* Define if you have the sigaction function.  */
/* #undef HAVE_SIGACTION */

/* Define if you have the sighold function.  */
/* #undef HAVE_SIGHOLD */

/* Define if you have the sigset function.  */
/* #undef HAVE_SIGSET */

/* Define if you have the sigthreadmask function.  */
/* #undef HAVE_SIGTHREADMASK */

/* Define if you have the sin function.  */
#define HAVE_SIN 1

/* Define if you have the snprintf function.  */
#define HAVE_SNPRINTF 1

/* Define if you have the socket function.  */
#define HAVE_SOCKET 1

/* Define if you have the srand48 function.  */
/* #undef HAVE_SRAND48 */

/* Define if you have the srandom function.  */
#define HAVE_SRANDOM 1

/* Define if you have the statfs function.  */
#define HAVE_STATFS 1

/* Define if you have the statvfs function.  */
/* #undef HAVE_STATVFS */

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

/* Define if you have the strftime function.  */
#define HAVE_STRFTIME 1

/* Define if you have the strlcat function.  */
/* #undef HAVE_STRLCAT */

/* Define if you have the strlcpy function.  */
/* #undef HAVE_STRLCPY */

/* Define if you have the strnlen function.  */
/* #undef HAVE_STRNLEN */

/* Define if you have the strpbrk function.  */
#define HAVE_STRPBRK 1

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strtod function.  */
#define HAVE_STRTOD 1

/* Define if you have the strtok_r function.  */
/* #undef HAVE_STRTOK_R */

/* Define if you have the strtol function.  */
#define HAVE_STRTOL 1

/* Define if you have the strtoul function.  */
#define HAVE_STRTOUL 1

/* Define if you have the strtoull function.  */
/* #undef HAVE_STRTOULL */

/* Define if you have the symlink function.  */
#define HAVE_SYMLINK 1

/* Define if you have the tell function.  */
/* #undef HAVE_TELL */

/* Define if you have the tempnam function.  */
#define HAVE_TEMPNAM 1

/* Define if you have the thr_setconcurrency function.  */
/* #undef HAVE_THR_SETCONCURRENCY */

/* Define if you have the tzset function.  */
#define HAVE_TZSET 1

/* Define if you have the unsetenv function.  */
#define HAVE_UNSETENV 1

/* Define if you have the usleep function.  */
#define HAVE_USLEEP 1

/* Define if you have the utime function.  */
#define HAVE_UTIME 1

/* Define if you have the vidattr function.  */
/* #undef HAVE_VIDATTR */

/* Define if you have the vsnprintf function.  */
#define HAVE_VSNPRINTF 1

/* Define if you have the waitpid function.  */
/* #undef HAVE_WAITPID */

/* Define if you have the <alloca.h> header file.  */
/* #undef HAVE_ALLOCA_H */

/* Define if you have the <arpa/inet.h> header file.  */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <arpa/nameser.h> header file.  */
#define HAVE_ARPA_NAMESER_H 1

/* Define if you have the <crypt.h> header file.  */
/* #undef HAVE_CRYPT_H */

/* Define if you have the <default_store.h> header file.  */
/* #undef HAVE_DEFAULT_STORE_H */

/* Define if you have the <dirent.h> header file.  */
#define HAVE_DIRENT_H 1

/* Define if you have the <dlfcn.h> header file.  */
/* #undef HAVE_DLFCN_H */

/* Define if you have the <errno.h> header file.  */
/* #undef HAVE_ERRNO_H */

/* Define if you have the <fcntl.h> header file.  */
#define HAVE_FCNTL_H 1

/* Define if you have the <float.h> header file.  */
#define HAVE_FLOAT_H 1

/* Define if you have the <floatingpoint.h> header file.  */
/* #undef HAVE_FLOATINGPOINT_H */

/* Define if you have the <grp.h> header file.  */
#define HAVE_GRP_H 1

/* Define if you have the <ieeefp.h> header file.  */
/* #undef HAVE_IEEEFP_H */

/* Define if you have the <langinfo.h> header file.  */
/* #undef HAVE_LANGINFO_H */

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file.  */
#define HAVE_LOCALE_H 1

/* Define if you have the <malloc.h> header file.  */
/* #undef HAVE_MALLOC_H */

/* Define if you have the <memory.h> header file.  */
#define HAVE_MEMORY_H 1

/* Define if you have the <ndir.h> header file.  */
/* #undef HAVE_NDIR_H */

/* Define if you have the <netdb.h> header file.  */
/* #undef HAVE_NETDB_H */

/* Define if you have the <netinet/in.h> header file.  */
#define HAVE_NETINET_IN_H 1

/* Define if you have the <netinet/tcp.h> header file.  */
/* #undef HAVE_NETINET_TCP_H */

/* Define if you have the <pwd.h> header file.  */
#define HAVE_PWD_H 1

/* Define if you have the <resolv.h> header file.  */
#define HAVE_RESOLV_H 1

/* Define if you have the <sched.h> header file.  */
#define HAVE_SCHED_H 1

/* Define if you have the <select.h> header file.  */
/* #undef HAVE_SELECT_H */

/* Define if you have the <sgtty.h> header file.  */
#define HAVE_SGTTY_H 1

/* Define if you have the <signal.h> header file.  */
#define HAVE_SIGNAL_H 1

/* Define if you have the <st.h> header file.  */
/* #undef HAVE_ST_H */

/* Define if you have the <stdarg.h> header file.  */
#define HAVE_STDARG_H 1

/* Define if you have the <stdbool.h> header file.  */
/* #undef HAVE_STDBOOL_H */

/* Define if you have the <stddef.h> header file.  */
#define HAVE_STDDEF_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
#define HAVE_STRINGS_H 1

/* Define if you have the <synch.h> header file.  */
/* #undef HAVE_SYNCH_H */

/* Define if you have the <sys/dir.h> header file.  */
/* #undef HAVE_SYS_DIR_H */

/* Define if you have the <sys/file.h> header file.  */
#define HAVE_SYS_FILE_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/mman.h> header file.  */
#define HAVE_SYS_MMAN_H 1

/* Define if you have the <sys/mount.h> header file.  */
#define HAVE_SYS_MOUNT_H 1

/* Define if you have the <sys/ndir.h> header file.  */
/* #undef HAVE_SYS_NDIR_H */

/* Define if you have the <sys/resource.h> header file.  */
#define HAVE_SYS_RESOURCE_H 1

/* Define if you have the <sys/select.h> header file.  */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/socket.h> header file.  */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/statfs.h> header file.  */
/* #undef HAVE_SYS_STATFS_H */

/* Define if you have the <sys/statvfs.h> header file.  */
/* #undef HAVE_SYS_STATVFS_H */

/* Define if you have the <sys/sysexits.h> header file.  */
/* #undef HAVE_SYS_SYSEXITS_H */

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/timeb.h> header file.  */
#define HAVE_SYS_TIMEB_H 1

/* Define if you have the <sys/types.h> header file.  */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/un.h> header file.  */
#define HAVE_SYS_UN_H 1

/* Define if you have the <sys/utime.h> header file.  */
/* #undef HAVE_SYS_UTIME_H */

/* Define if you have the <sys/vadvise.h> header file.  */
#define HAVE_SYS_VADVISE_H 1

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

/* Define if you have the <term.h> header file.  */
/* #undef HAVE_TERM_H */

/* Define if you have the <termio.h> header file.  */
/* #undef HAVE_TERMIO_H */

/* Define if you have the <termios.h> header file.  */
#define HAVE_TERMIOS_H 1

/* Define if you have the <tuxmodule.h> header file.  */
/* #undef HAVE_TUXMODULE_H */

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <unix.h> header file.  */
/* #undef HAVE_UNIX_H */

/* Define if you have the <utime.h> header file.  */
#define HAVE_UTIME_H 1

/* Define if you have the <xmlparse.h> header file.  */
/* #undef HAVE_XMLPARSE_H */

/* Define if you have the <xmltok.h> header file.  */
/* #undef HAVE_XMLTOK_H */

/* Define if you have the crypt library (-lcrypt).  */
/* #undef HAVE_LIBCRYPT */

/* Define if you have the jpeg library (-ljpeg).  */
/* #undef HAVE_LIBJPEG */

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* Define if you have the pam library (-lpam).  */
/* #undef HAVE_LIBPAM */

/* Define if you have the resolv library (-lresolv).  */
/* #undef HAVE_LIBRESOLV */

/* Define if you have the sqlcli library (-lsqlcli).  */
/* #undef HAVE_LIBSQLCLI */

/* Define if you have the tiff library (-ltiff).  */
/* #undef HAVE_LIBTIFF */

/* Whether you have AOLserver */
/* #undef HAVE_AOLSERVER */

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_COMPAT_H 1

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_COMPAT_H 1

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_COMPAT_H 1

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_COMPAT_H 1

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_COMPAT_H 1

/*   */
/* #undef HAVE_OLD_COMPAT_H */

/*   */
/* #undef USE_TRANSFER_TABLES */

/* Whether to compile with Caudium support */
/* #undef HAVE_CAUDIUM */

/* whether write(2) works */
/* #undef PHP_WRITE_STDOUT */

/*   */
/* #undef FORCE_CGI_REDIRECT */

/*   */
/* #undef DISCARD_PATH */

/*   */
/* #undef FHTTPD */

/*   */
/* #undef WITH_ZEUS */

/* Whether you have a Netscape Server */
/* #undef HAVE_NSAPI */

/* Whether you have phttpd */
/* #undef HAVE_PHTTPD */

/* whether you want Pi3Web support */
/* #undef WITH_PI3WEB */

/* Whether you use Roxen */
/* #undef HAVE_ROXEN */

/* Whether to use Roxen in ZTS mode */
/* #undef ROXEN_USE_ZTS */

/* Whether you use Servlet */
/* #undef SAPI_SERVLET */

/* Whether localtime_r is declared */
#define MISSING_LOCALTIME_R_DECL 1

/* Whether gmtime_r is declared */
#define MISSING_GMTIME_R_DECL 1

/* Whether asctime_r is declared */
#define MISSING_ASCTIME_R_DECL 1

/* Whether ctime_r is declared */
#define MISSING_CTIME_R_DECL 1

/* Whether strtok_r is declared */
#define MISSING_STRTOK_R_DECL 1

/* whether you have sendmail */
#define HAVE_SENDMAIL 1

/* Define if system uses EBCDIC */
/* #undef CHARSET_EBCDIC */

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
/* #undef HAVE_LIBNSL */

/*   */
/* #undef HAVE_LIBNSL */

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
/* #undef HAVE_LIBRESOLV */

/*   */
#define MISSING_FCLOSE_DECL 0

/*   */
#define MISSING_FCLOSE_DECL 0

/* whether you have tm_gmtoff in struct tm */
#define HAVE_TM_GMTOFF 1

/* whether you have struct flock */
#define HAVE_STRUCT_FLOCK 1

/* Whether you have socklen_t */
/* #undef HAVE_SOCKLEN_T */

/* Whether you have IPv6 support */
#define HAVE_IPV6 1

/* Define if you have the getaddrinfo function */
#define HAVE_GETADDRINFO 1

/*   */
#define PHP_BROKEN_SPRINTF 0

/*   */
#define PHP_BROKEN_SPRINTF 0

/* Whether system headers declare timezone */
#define HAVE_DECLARED_TIMEZONE 1

/* Whether you have HP-UX 10.x */
/* #undef PHP_HPUX_TIME_R */

/* Whether you have IRIX-style functions */
/* #undef PHP_IRIX_TIME_R */

/* whether you have POSIX readdir_r */
/* #undef HAVE_POSIX_READDIR_R */

/* whether you have old-style readdir_r */
/* #undef HAVE_OLD_READDIR_R */

/*   */
#define in_addr_t u_int

/*   */
#define PHP_SAFE_MODE 0

/*   */
#define PHP_SAFE_MODE 0

/*   */
#define PHP_SAFE_MODE_EXEC_DIR "/usr/local/php/bin"

/*   */
#define PHP_SAFE_MODE_EXEC_DIR "/usr/local/php/bin"

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

/* Whether to use php streams */
/* #undef HAVE_PHP_STREAM */

/*   */
#define HAVE_CRYPT 1

/* Whether to build zlib as dynamic module */
/* #undef COMPILE_DL_ZLIB */

/*   */
/* #undef HAVE_ZLIB */

/*   */
/* #undef HAVE_FOPENCOOKIE */

/*   */
/* #undef COOKIE_IO_FUNCTIONS_T */

/* Whether you have aspell */
/* #undef HAVE_ASPELL */

/* Whether to build aspell as dynamic module */
/* #undef COMPILE_DL_ASPELL */

/* Whether you have bcmath */
/* #undef WITH_BCMATH */

/* Whether to build bcmath as dynamic module */
/* #undef COMPILE_DL_BCMATH */

/*   */
/* #undef HAVE_BZ2 */

/* Whether to build bz2 as dynamic module */
/* #undef COMPILE_DL_BZ2 */

/*   */
/* #undef HAVE_CALENDAR */

/* Whether to build calendar as dynamic module */
/* #undef COMPILE_DL_CALENDAR */

/* Whether to build ccvs as dynamic module */
/* #undef COMPILE_DL_CCVS */

/* Whether to build cpdf as dynamic module */
/* #undef COMPILE_DL_CPDF */

/* Whether you have cpdflib */
/* #undef HAVE_CPDFLIB */

/* Whether to build cpdf as dynamic module */
/* #undef COMPILE_DL_CPDF */

/* Whether you have cpdflib */
/* #undef HAVE_CPDFLIB */

/* Whether to build crack as dynamic module */
/* #undef COMPILE_DL_CRACK */

/*   */
/* #undef HAVE_CRACK */

/*   */
/* #undef HAVE_CTYPE */

/* Whether to build ctype as dynamic module */
/* #undef COMPILE_DL_CTYPE */

/*   */
/* #undef HAVE_CURL */

/* Whether to build curl as dynamic module */
/* #undef COMPILE_DL_CURL */

/* Whether to build cybercash as dynamic module */
/* #undef COMPILE_DL_CYBERCASH */

/*   */
/* #undef HAVE_MCK */

/*   */
/* #undef HAVE_CYBERMUT */

/* Whether to build cybermut as dynamic module */
/* #undef COMPILE_DL_CYBERMUT */

/*   */
/* #undef HAVE_CYRUS */

/* Whether to build cyrus as dynamic module */
/* #undef COMPILE_DL_CYRUS */

/* Whether you have GDBM */
/* #undef GDBM */

/*   */
/* #undef NDBM */

/*   */
/* #undef NDBM */

/* Whether you have NDBM */
/* #undef NDBM */

/* Whether to build db as dynamic module */
/* #undef COMPILE_DL_DB */

/*   */
/* #undef DBA_GDBM */

/*   */
/* #undef NDBM_INCLUDE_FILE */

/*   */
/* #undef DBA_NDBM */

/*   */
/* #undef DB2_INCLUDE_FILE */

/*   */
/* #undef DBA_DB2 */

/*   */
/* #undef DB3_INCLUDE_FILE */

/*   */
/* #undef DBA_DB3 */

/*   */
/* #undef DBA_DBM */

/*   */
/* #undef DBA_CDB */

/*   */
#define HAVE_DBA 0

/* Whether to build dba as dynamic module */
/* #undef COMPILE_DL_DBA */

/*   */
#define HAVE_DBA 0

/*   */
/* #undef DBASE */

/* Whether to build dbase as dynamic module */
/* #undef COMPILE_DL_DBASE */

/*   */
/* #undef HAVE_DBPLUSLIB */

/* Whether to build dbplus as dynamic module */
/* #undef COMPILE_DL_DBPLUS */

/* Whether to build dbx as dynamic module */
/* #undef COMPILE_DL_DBX */

/*   */
/* #undef HAVE_DOMXML */

/* Whether to build domxml as dynamic module */
/* #undef COMPILE_DL_DOMXML */

/* Whether you want exif support */
/* #undef HAVE_EXIF */

/* Whether to build exif as dynamic module */
/* #undef COMPILE_DL_EXIF */

/* Whether you have FrontBase */
/* #undef HAVE_FBSQL */

/* Whether to build fbsql as dynamic module */
/* #undef COMPILE_DL_FBSQL */

/*   */
/* #undef HAVE_FDFLIB */

/* Whether to build fdf as dynamic module */
/* #undef COMPILE_DL_FDF */

/*   */
/* #undef HAVE_FILEPRO */

/* Whether to build filepro as dynamic module */
/* #undef COMPILE_DL_FILEPRO */

/*   */
/* #undef HAVE_FRIBIDI */

/* Whether to build fribidi as dynamic module */
/* #undef COMPILE_DL_FRIBIDI */

/* Whether you want FTP support */
/* #undef HAVE_FTP */

/* Whether to build ftp as dynamic module */
/* #undef COMPILE_DL_FTP */

/* Whether to build gd as dynamic module */
/* #undef COMPILE_DL_GD */

/*   */
/* #undef USE_GD_IMGSTRTTF */

/*   */
/* #undef USE_GD_IMGSTRTTF */

/*   */
/* #undef HAVE_LIBFREETYPE */

/*   */
/* #undef HAVE_LIBTTF */

/*   */
/* #undef HAVE_LIBT1 */

/*   */
/* #undef HAVE_LIBGD13 */

/*   */
/* #undef HAVE_LIBGD15 */

/*   */
/* #undef HAVE_GD_PNG */

/*   */
/* #undef HAVE_GD_GIF_READ */

/*   */
/* #undef HAVE_GD_GIF_CREATE */

/*   */
/* #undef HAVE_GD_WBMP */

/*   */
/* #undef HAVE_GD_JPG */

/*   */
/* #undef HAVE_GD_XPM */

/*   */
/* #undef HAVE_GD_GD2 */

/*   */
/* #undef HAVE_LIBGD20 */

/*   */
/* #undef HAVE_GD_IMAGESETTILE */

/*   */
/* #undef HAVE_GD_IMAGESETBRUSH */

/*   */
/* #undef HAVE_GD_STRINGTTF */

/*   */
/* #undef HAVE_GD_STRINGFT */

/*   */
/* #undef HAVE_GD_STRINGFTEX */

/*   */
/* #undef HAVE_COLORCLOSESTHWB */

/*   */
/* #undef HAVE_GDIMAGECOLORRESOLVE */

/*   */
/* #undef HAVE_GD_GIF_CTX */

/*   */
/* #undef HAVE_LIBGD */

/*   */
/* #undef HAVE_LIBGD */

/*   */
/* #undef HAVE_LIBGD13 */

/*   */
/* #undef HAVE_LIBGD15 */

/*   */
/* #undef HAVE_GD_PNG */

/*   */
/* #undef HAVE_GD_GIF_READ */

/*   */
/* #undef HAVE_GD_GIF_CREATE */

/*   */
/* #undef HAVE_GD_WBMP */

/*   */
/* #undef HAVE_GD_JPG */

/*   */
/* #undef HAVE_GD_XPM */

/*   */
/* #undef HAVE_GD_GD2 */

/*   */
/* #undef HAVE_LIBGD20 */

/*   */
/* #undef HAVE_GD_IMAGESETTILE */

/*   */
/* #undef HAVE_GD_IMAGESETBRUSH */

/*   */
/* #undef HAVE_GD_STRINGTTF */

/*   */
/* #undef HAVE_GD_STRINGFT */

/*   */
/* #undef HAVE_GD_STRINGFTEX */

/*   */
/* #undef HAVE_COLORCLOSESTHWB */

/*   */
/* #undef HAVE_GDIMAGECOLORRESOLVE */

/*   */
/* #undef HAVE_GD_GIF_CTX */

/*   */
/* #undef HAVE_LIBINTL */

/* Whether to build gettext as dynamic module */
/* #undef COMPILE_DL_GETTEXT */

/* Whether to build gmp as dynamic module */
/* #undef COMPILE_DL_GMP */

/*   */
/* #undef HAVE_GMP */

/*   */
#define HYPERWAVE 0

/* Whether to build hyperwave as dynamic module */
/* #undef COMPILE_DL_HYPERWAVE */

/*   */
#define HYPERWAVE 0

/*   */
#define HYPERWAVE 0

/*   */
/* #undef HAVE_ICAP */

/* Whether to build icap as dynamic module */
/* #undef COMPILE_DL_ICAP */

/*   */
/* #undef HAVE_ICONV */

/*   */
/* #undef HAVE_LIBICONV */

/*   */
/* #undef HAVE_ICONV */

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
/* #undef HAVE_IMAP2001 */

/*   */
/* #undef HAVE_IMAP_KRB */

/*   */
/* #undef HAVE_IMAP_SSL */

/* Whether to build informix as dynamic module */
/* #undef COMPILE_DL_INFORMIX */

/*   */
/* #undef IFX_VERSION */

/*   */
/* #undef HAVE_IFX_IUS */

/*   */
/* #undef HAVE_IFX */

/* Whether you have Ingres II */
/* #undef HAVE_II */

/* Whether to build ingres_ii as dynamic module */
/* #undef COMPILE_DL_INGRES_II */

/*   */
/* #undef HAVE_IBASE */

/* Whether to build interbase as dynamic module */
/* #undef COMPILE_DL_INTERBASE */

/* Whether thttpd is available */
/* #undef IRCG_WITH_THTTPD */

/* Whether you want IRCG support */
/* #undef HAVE_IRCG */

/* Whether to build ircg as dynamic module */
/* #undef COMPILE_DL_IRCG */

/*   */
/* #undef HAVE_JAVA */

/* Whether to build java as dynamic module */
/* #undef COMPILE_DL_JAVA */

/* Whether to build ldap as dynamic module */
/* #undef COMPILE_DL_LDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_ORALDAP */

/*   */
/* #undef HAVE_LDAP */

/* Whether to build mailparse as dynamic module */
/* #undef COMPILE_DL_MAILPARSE */

/*   */
/* #undef HAVE_MBSTRING */

/* Whether to build mbstring as dynamic module */
/* #undef COMPILE_DL_MBSTRING */

/*   */
/* #undef MBSTR_ENC_TRANS */

/*   */
/* #undef HAVE_MCAL */

/* Whether to build mcal as dynamic module */
/* #undef COMPILE_DL_MCAL */

/*   */
/* #undef HAVE_LIBMCRYPT24 */

/*   */
/* #undef HAVE_LIBMCRYPT22 */

/*   */
/* #undef HAVE_LIBMCRYPT */

/* Whether to build mcrypt as dynamic module */
/* #undef COMPILE_DL_MCRYPT */

/*   */
/* #undef HAVE_LIBMHASH */

/* Whether to build mhash as dynamic module */
/* #undef COMPILE_DL_MHASH */

/*   */
/* #undef HAVE_MING */

/* Whether to build ming as dynamic module */
/* #undef COMPILE_DL_MING */

/*   */
/* #undef HAVE_MNOGOSEARCH */

/* Whether to build mnogosearch as dynamic module */
/* #undef COMPILE_DL_MNOGOSEARCH */

/*   */
/* #undef HAVE_MSQL */

/* Whether to build msql as dynamic module */
/* #undef COMPILE_DL_MSQL */

/*   */
/* #undef MSQL1 */

/*   */
/* #undef MSQL1 */

/* Whether to build muscat as dynamic module */
/* #undef COMPILE_DL_MUSCAT */

/*   */
/* #undef HAVE_MUSCAT */

/*   */
/* #undef PHP_MUSCAT_DIR */

/* Whether you have MySQL */
#define HAVE_MYSQL 1

/* Whether to build mysql as dynamic module */
/* #undef COMPILE_DL_MYSQL */

/*   */
#define MYSQL_UNIX_ADDR "/tmp/mysql.sock"

/*   */
#define UNDEF_THREADS_HACK 

/*   */
/* #undef HAVE_ULONG */

/*   */
/* #undef HAVE_UCHAR */

/*   */
#define HAVE_UINT 

/*   */
/* #undef HAVE_INT_8_16_32 */

/*   */
#define SOCKET_SIZE_TYPE int

/*   */
#define RETQSORTTYPE void

/*   */
#define QSORT_TYPE_IS_VOID 1

/*   */
/* #undef HAVE_GETHOSTBYNAME_R_GLIBC2_STYLE */

/*   */
/* #undef HAVE_GETHOSTBYNAME_R_RETURN_INT */

/*   */
/* #undef HAVE_NONPOSIX_PTHREAD_GETSPECIFIC */

/*   */
/* #undef HAVE_NONPOSIX_PTHREAD_MUTEX_INIT */

/*   */
/* #undef HAVE_READDIR_R */

/*   */
/* #undef HAVE_SIGWAIT */

/*   */
/* #undef HAVE_NONPOSIX_SIGWAIT */

/*   */
#define MYSQL_UNIX_ADDR "/tmp/mysql.sock"

/*   */
/* #undef HAVE_NCURSESLIB */

/* Whether to build ncurses as dynamic module */
/* #undef COMPILE_DL_NCURSES */

/*   */
/* #undef HAVE_OCI8_TEMP_LOB */

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
/* #undef HAVE_EMPRESS */

/*   */
/* #undef HAVE_EMPRESS */

/*   */
/* #undef HAVE_VELOCIS */

/*   */
/* #undef HAVE_CODBC */

/*   */
/* #undef HAVE_IODBC */

/*   */
/* #undef HAVE_ESOOB */

/*   */
/* #undef HAVE_UNIXODBC */

/*   */
/* #undef HAVE_IODBC */

/* Whether you want DBMaker */
/* #undef HAVE_DBMAKER */

/*   */
/* #undef HAVE_UODBC */

/* Whether to build odbc as dynamic module */
/* #undef COMPILE_DL_ODBC */

/* Whether to build openssl as dynamic module */
/* #undef COMPILE_DL_OPENSSL */

/*   */
/* #undef HAVE_OPENSSL_EXT */

/* Whether to build oracle as dynamic module */
/* #undef COMPILE_DL_ORACLE */

/*   */
/* #undef HAVE_ORACLE */

/*   */
/* #undef HAVE_LIBSQLCLI */

/* Whether to build ovrimos as dynamic module */
/* #undef COMPILE_DL_OVRIMOS */

/*   */
/* #undef HAVE_FORK */

/*   */
/* #undef HAVE_WAITPID */

/*   */
/* #undef HAVE_SIGACTION */

/* Whether to build pcntl as dynamic module */
/* #undef COMPILE_DL_PCNTL */

/* Whether to build pcre as dynamic module */
/* #undef COMPILE_DL_PCRE */

/*   */
#define HAVE_BUNDLED_PCRE 1

/*   */
/* #undef HAVE_PCRE */

/*   */
/* #undef USE_BCOPY */

/* Whether to build pdf as dynamic module */
/* #undef COMPILE_DL_PDF */

/*   */
/* #undef HAVE_PDFLIB */

/*   */
/* #undef HAVE_PDFLIB */

/* Version of SDK */
/* #undef PFPRO_VERSION */

/*   */
/* #undef HAVE_PFPRO */

/* Whether to build pfpro as dynamic module */
/* #undef COMPILE_DL_PFPRO */

/*   */
/* #undef HAVE_PQCMDTUPLES */

/*   */
/* #undef HAVE_PQOIDVALUE */

/*   */
/* #undef HAVE_PQCLIENTENCODING */

/*   */
/* #undef HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT */

/*   */
/* #undef HAVE_PGSQL */

/* Whether to build pgsql as dynamic module */
/* #undef COMPILE_DL_PGSQL */

/* whether to include POSIX-like functions */
#define HAVE_POSIX 1

/* Whether to build posix as dynamic module */
/* #undef COMPILE_DL_POSIX */

/* Whether to build pspell as dynamic module */
/* #undef COMPILE_DL_PSPELL */

/*   */
/* #undef HAVE_PSPELL */

/* Wheter you have qtdom */
/* #undef HAVE_QTDOM */

/* Whether to build qtdom as dynamic module */
/* #undef COMPILE_DL_QTDOM */

/* Wheter you have qtdom */
/* #undef HAVE_QTDOM */

/* Whether to build qtdom as dynamic module */
/* #undef COMPILE_DL_QTDOM */

/*   */
/* #undef HAVE_LIBREADLINE */

/* Whether to build readline as dynamic module */
/* #undef COMPILE_DL_READLINE */

/*   */
/* #undef HAVE_LIBEDIT */

/* Whether to build readline as dynamic module */
/* #undef COMPILE_DL_READLINE */

/* Whether we have librecode 3.5 or higher */
/* #undef HAVE_LIBRECODE */

/* Whether to build recode as dynamic module */
/* #undef COMPILE_DL_RECODE */

/* Whether to build satellite as dynamic module */
/* #undef COMPILE_DL_SATELLITE */

/*   */
/* #undef HAVE_SATELLITE */

/* Whether you have libmm */
/* #undef HAVE_LIBMM */

/* Whether you want transparent session id propagation */
/* #undef TRANS_SID */

/* whether pwrite64 is default */
/* #undef PHP_PWRITE_64 */

/* whether pread64 is default */
/* #undef PHP_PREAD_64 */

/* Whether to build session as dynamic module */
/* #undef COMPILE_DL_SESSION */

/*   */
#define HAVE_PHP_SESSION 1

/*   */
/* #undef HAVE_SHMOP */

/* Whether to build shmop as dynamic module */
/* #undef COMPILE_DL_SHMOP */

/*   */
/* #undef HAVE_SNMP */

/* Whether to build snmp as dynamic module */
/* #undef COMPILE_DL_SNMP */

/*   */
/* #undef UCD_SNMP_HACK */

/*   */
/* #undef HAVE_SOCKETS */

/* Whether to build sockets as dynamic module */
/* #undef COMPILE_DL_SOCKETS */

/*   */
/* #undef HAVE_LIBDL */

/*   */
/* #undef HAVE_LIBPAM */

/* Whether the system supports standard DES salt */
#define PHP_STD_DES_CRYPT 1

/* Whether the system supports extended DES salt */
#define PHP_EXT_DES_CRYPT 1

/* Whether the system supports MD5 salt */
#define PHP_MD5_CRYPT 0

/* Whether the system supports BlowFish salt */
#define PHP_BLOWFISH_CRYPT 0

/* Define if flush should be called explicitly after a buffered io. */
#define HAVE_FLUSHIO 1

/* Whether to build standard as dynamic module */
/* #undef COMPILE_DL_STANDARD */

/*   */
/* #undef HAVE_SWF */

/* Whether to build swf as dynamic module */
/* #undef COMPILE_DL_SWF */

/* Whether to build sybase as dynamic module */
/* #undef COMPILE_DL_SYBASE */

/*   */
/* #undef HAVE_LIBDNET_STUB */

/*   */
/* #undef HAVE_SYBASE */

/*   */
/* #undef PHP_SYBASE_DBOPEN */

/*   */
/* #undef DBMFIX */

/*   */
/* #undef PHP_SYBASE_DBOPEN */

/*   */
/* #undef HAVE_SYBASE_CT */

/* Whether to build sybase_ct as dynamic module */
/* #undef COMPILE_DL_SYBASE_CT */

/* Whether to build sysvsem as dynamic module */
/* #undef COMPILE_DL_SYSVSEM */

/*   */
/* #undef HAVE_SYSVSEM */

/*   */
/* #undef HAVE_SEMUN */

/*   */
/* #undef HAVE_SEMUN */

/*   */
/* #undef HAVE_SYSVSHM */

/* Whether to build sysvshm as dynamic module */
/* #undef COMPILE_DL_SYSVSHM */

/* Whether vpopmail has vauth.h */
/* #undef HAVE_VPOPMAIL_VAUTH */

/* Whether vpopmail has valias support */
/* #undef HAVE_VPOPMAIL_VALIAS */

/* Whether you have vpopmail */
/* #undef HAVE_VPOPMAIL */

/* vpopmail bin path */
/* #undef VPOPMAIL_BIN_DIR */

/* Whether to build vpopmail as dynamic module */
/* #undef COMPILE_DL_VPOPMAIL */

/*   */
/* #undef HAVE_WDDX */

/* Whether to build wddx as dynamic module */
/* #undef COMPILE_DL_WDDX */

/*   */
#define HAVE_LIBEXPAT 1

/*   */
#define HAVE_LIBEXPAT_BUNDLED 1

/* Whether to build xml as dynamic module */
/* #undef COMPILE_DL_XML */

/* Whether to build xml as dynamic module */
/* #undef COMPILE_DL_XML */

/*   */
#define HAVE_LIBEXPAT 1

/* Whether to build xmlrpc as dynamic module */
/* #undef COMPILE_DL_XMLRPC */

/*   */
/* #undef HAVE_XMLRPC */

/*   */
/* #undef HAVE_LIBEXPAT2 */

/*   */
#define UNDEF_THREADS_HACK 

/* Whether to build xslt as dynamic module */
/* #undef COMPILE_DL_XSLT */

/*   */
/* #undef HAVE_LIBEXPAT2 */

/*   */
/* #undef HAVE_SABLOT_BACKEND */

/*   */
/* #undef HAVE_SABLOT_SET_ENCODING */

/*   */
/* #undef HAVE_XSLT */

/* Whether you have YAZ */
/* #undef HAVE_YAZ */

/* Whether to build yaz as dynamic module */
/* #undef COMPILE_DL_YAZ */

/*   */
/* #undef HAVE_YP */

/* Whether to build yp as dynamic module */
/* #undef COMPILE_DL_YP */

/*   */
/* #undef SOLARIS_YP */

/* Whether to build zip as dynamic module */
/* #undef COMPILE_DL_ZIP */

/*   */
/* #undef HAVE_ZZIPLIB */

/*   */
/* #undef HAVE_FOPENCOOKIE */

/*   */
/* #undef COOKIE_IO_FUNCTIONS_T */

/*   */
#define HSREGEX 1

/*   */
#define REGEX 1

/*   */
#define REGEX 1

/*   */
/* #undef HAVE_LIBDL */

/* Whether sprintf is broken */
#define ZEND_BROKEN_SPRINTF 0

/* whether floatingpoint.h defines fp_except */
/* #undef HAVE_FP_EXCEPT */

/*   */
#define ZEND_DEBUG 0

/*   */
#define ZEND_DEBUG 0

/*   */
/* #undef ZTS */

/* Memory limit */
#define MEMORY_LIMIT 0

/* Memory limit */
#define MEMORY_LIMIT 0

/*   */
/* #undef ZTS */

/* Whether you use GNU Pth */
/* #undef GNUPTH */

/*   */
/* #undef TSRM_ST */

/* Whether to use Pthreads */
/* #undef PTHREADS */

/* PHP build date */
#define PHP_BUILD_DATE "2002-05-02"

/* uname -a output */
#define PHP_UNAME "Darwin smallsoldiers 1.4 Darwin Kernel Version 5.2: Fri Dec  7 21:39:35 PST 2001; root:xnu/xnu-201.14.obj~1/RELEASE_PPC  Power Macintosh powerpc"

/* uname output */
#define PHP_OS "Darwin"


#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
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

#ifdef HAVE_ISNAN
#define zend_isnan(a) isnan(a)
#elif defined(NAN)
#define zend_isnan(a) (((a)==NAN)?1:0)
#elif defined(HAVE_FPCLASS)
#define zend_isnan(a) ((fpclass(a) == FP_SNAN) || (fpclass(a) == FP_QNAN))
#else
#define zend_isnan(a) 0
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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
/* #undef PTHREADS */
