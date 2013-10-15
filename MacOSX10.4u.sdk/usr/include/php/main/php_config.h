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

/* Define if lex declares yytext as a char * by default, not a char[].  */
#define YYTEXT_POINTER 1

/* #undef uint */
#define ulong unsigned long 

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 1

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a intmax_t.  */
#define SIZEOF_INTMAX_T 0

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* The number of bytes in a long long int.  */
#define SIZEOF_LONG_LONG_INT 8

/* The number of bytes in a ptrdiff_t.  */
#define SIZEOF_PTRDIFF_T 0

/* The number of bytes in a size_t.  */
#define SIZEOF_SIZE_T 4

/* The number of bytes in a ssize_t.  */
#define SIZEOF_SSIZE_T 0

/* Define if you have the acosh function.  */
#define HAVE_ACOSH 1

/* Define if you have the alarm function.  */
/* #undef HAVE_ALARM */

/* Define if you have the alphasort function.  */
#define HAVE_ALPHASORT 1

/* Define if you have the asctime_r function.  */
#define HAVE_ASCTIME_R 1

/* Define if you have the asinh function.  */
#define HAVE_ASINH 1

/* Define if you have the atanh function.  */
#define HAVE_ATANH 1

/* Define if you have the atod function.  */
/* #undef HAVE_ATOD */

/* Define if you have the bcmp function.  */
/* #undef HAVE_BCMP */

/* Define if you have the bfill function.  */
/* #undef HAVE_BFILL */

/* Define if you have the bmove function.  */
/* #undef HAVE_BMOVE */

/* Define if you have the bzero function.  */
/* #undef HAVE_BZERO */

/* Define if you have the chroot function.  */
#define HAVE_CHROOT 1

/* Define if you have the chsize function.  */
/* #undef HAVE_CHSIZE */

/* Define if you have the crypt function.  */
#define HAVE_CRYPT 1

/* Define if you have the ctermid function.  */
#define HAVE_CTERMID 1

/* Define if you have the ctime_r function.  */
#define HAVE_CTIME_R 1

/* Define if you have the cuserid function.  */
/* #undef HAVE_CUSERID */

/* Define if you have the dlerror function.  */
/* #undef HAVE_DLERROR */

/* Define if you have the dlopen function.  */
#define HAVE_DLOPEN 1

/* Define if you have the fabsf function.  */
/* #undef HAVE_FABSF */

/* Define if you have the fchmod function.  */
/* #undef HAVE_FCHMOD */

/* Define if you have the fcntl function.  */
/* #undef HAVE_FCNTL */

/* Define if you have the fconvert function.  */
/* #undef HAVE_FCONVERT */

/* Define if you have the finite function.  */
#define HAVE_FINITE 1

/* Define if you have the flock function.  */
#define HAVE_FLOCK 1

/* Define if you have the floorf function.  */
/* #undef HAVE_FLOORF */

/* Define if you have the fork function.  */
/* #undef HAVE_FORK */

/* Define if you have the fpclass function.  */
/* #undef HAVE_FPCLASS */

/* Define if you have the fpresetsticky function.  */
/* #undef HAVE_FPRESETSTICKY */

/* Define if you have the fpsetmask function.  */
/* #undef HAVE_FPSETMASK */

/* Define if you have the ftok function.  */
#define HAVE_FTOK 1

/* Define if you have the ftruncate function.  */
/* #undef HAVE_FTRUNCATE */

/* Define if you have the funopen function.  */
#define HAVE_FUNOPEN 1

/* Define if you have the gai_strerror function.  */
#define HAVE_GAI_STRERROR 1

/* Define if you have the gcvt function.  */
#define HAVE_GCVT 1

/* Define if you have the getcwd function.  */
#define HAVE_GETCWD 1

/* Define if you have the getgroups function.  */
#define HAVE_GETGROUPS 1

/* Define if you have the gethostbyaddr_r function.  */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define if you have the gethostbyname_r function.  */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define if you have the getlogin function.  */
#define HAVE_GETLOGIN 1

/* Define if you have the getopt function.  */
#define HAVE_GETOPT 1

/* Define if you have the getpass function.  */
/* #undef HAVE_GETPASS */

/* Define if you have the getpassphrase function.  */
/* #undef HAVE_GETPASSPHRASE */

/* Define if you have the getpgid function.  */
#define HAVE_GETPGID 1

/* Define if you have the getpid function.  */
#define HAVE_GETPID 1

/* Define if you have the getprotobyname function.  */
#define HAVE_GETPROTOBYNAME 1

/* Define if you have the getprotobynumber function.  */
#define HAVE_GETPROTOBYNUMBER 1

/* Define if you have the getpwnam function.  */
/* #undef HAVE_GETPWNAM */

/* Define if you have the getpwuid function.  */
/* #undef HAVE_GETPWUID */

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

/* Define if you have the hstrerror function.  */
#define HAVE_HSTRERROR 1

/* Define if you have the hypot function.  */
#define HAVE_HYPOT 1

/* Define if you have the index function.  */
/* #undef HAVE_INDEX */

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

/* Define if you have the locking function.  */
/* #undef HAVE_LOCKING */

/* Define if you have the log1p function.  */
#define HAVE_LOG1P 1

/* Define if you have the longjmp function.  */
/* #undef HAVE_LONGJMP */

/* Define if you have the lrand48 function.  */
#define HAVE_LRAND48 1

/* Define if you have the madvise function.  */
/* #undef HAVE_MADVISE */

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
#define HAVE_NL_LANGINFO 1

/* Define if you have the perror function.  */
#define HAVE_PERROR 1

/* Define if you have the poll function.  */
#define HAVE_POLL 1

/* Define if you have the pread function.  */
#define HAVE_PREAD 1

/* Define if you have the pthread_attr_create function.  */
/* #undef HAVE_PTHREAD_ATTR_CREATE */

/* Define if you have the pthread_attr_setprio function.  */
/* #undef HAVE_PTHREAD_ATTR_SETPRIO */

/* Define if you have the pthread_attr_setschedparam function.  */
/* #undef HAVE_PTHREAD_ATTR_SETSCHEDPARAM */

/* Define if you have the pthread_attr_setstacksize function.  */
/* #undef HAVE_PTHREAD_ATTR_SETSTACKSIZE */

/* Define if you have the pthread_condattr_create function.  */
/* #undef HAVE_PTHREAD_CONDATTR_CREATE */

/* Define if you have the pthread_getsequence_np function.  */
/* #undef HAVE_PTHREAD_GETSEQUENCE_NP */

/* Define if you have the pthread_setprio function.  */
/* #undef HAVE_PTHREAD_SETPRIO */

/* Define if you have the pthread_setprio_np function.  */
/* #undef HAVE_PTHREAD_SETPRIO_NP */

/* Define if you have the pthread_setschedparam function.  */
/* #undef HAVE_PTHREAD_SETSCHEDPARAM */

/* Define if you have the pthread_sigmask function.  */
/* #undef HAVE_PTHREAD_SIGMASK */

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the rand_r function.  */
#define HAVE_RAND_R 1

/* Define if you have the random function.  */
#define HAVE_RANDOM 1

/* Define if you have the realpath function.  */
#define HAVE_REALPATH 1

/* Define if you have the regcomp function.  */
#define HAVE_REGCOMP 1

/* Define if you have the rename function.  */
/* #undef HAVE_RENAME */

/* Define if you have the res_search function.  */
#define HAVE_RES_SEARCH 1

/* Define if you have the rint function.  */
/* #undef HAVE_RINT */

/* Define if you have the rwlock_init function.  */
/* #undef HAVE_RWLOCK_INIT */

/* Define if you have the scandir function.  */
#define HAVE_SCANDIR 1

/* Define if you have the set_h_errno function.  */
/* #undef HAVE_SET_H_ERRNO */

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

/* Define if you have the strnlen function.  */
/* #undef HAVE_STRNLEN */

/* Define if you have the strpbrk function.  */
/* #undef HAVE_STRPBRK */

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strtod function.  */
#define HAVE_STRTOD 1

/* Define if you have the strtok_r function.  */
#define HAVE_STRTOK_R 1

/* Define if you have the strtol function.  */
#define HAVE_STRTOL 1

/* Define if you have the strtoll function.  */
/* #undef HAVE_STRTOLL */

/* Define if you have the strtoul function.  */
/* #undef HAVE_STRTOUL */

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

/* Define if you have the </nsapi.h> header file.  */
/* #undef HAVE__NSAPI_H */

/* Define if you have the <ApplicationServices/ApplicationServices.h> header file.  */
#define HAVE_APPLICATIONSERVICES_APPLICATIONSERVICES_H 1

/* Define if you have the <JavaVM/JavaVM.h> header file.  */
/* #undef HAVE_JAVAVM_JAVAVM_H */

/* Define if you have the <JavaVM/jni.h> header file.  */
/* #undef HAVE_JAVAVM_JNI_H */

/* Define if you have the <alloca.h> header file.  */
#define HAVE_ALLOCA_H 1

/* Define if you have the <arpa/inet.h> header file.  */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <arpa/nameser.h> header file.  */
#define HAVE_ARPA_NAMESER_H 1

/* Define if you have the <assert.h> header file.  */
#define HAVE_ASSERT_H 1

/* Define if you have the <crypt.h> header file.  */
/* #undef HAVE_CRYPT_H */

/* Define if you have the <default_store.h> header file.  */
/* #undef HAVE_DEFAULT_STORE_H */

/* Define if you have the <dirent.h> header file.  */
#define HAVE_DIRENT_H 1

/* Define if you have the <dlfcn.h> header file.  */
#define HAVE_DLFCN_H 1

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <fcntl.h> header file.  */
#define HAVE_FCNTL_H 1

/* Define if you have the <float.h> header file.  */
/* #undef HAVE_FLOAT_H */

/* Define if you have the <floatingpoint.h> header file.  */
/* #undef HAVE_FLOATINGPOINT_H */

/* Define if you have the <gcrypt.h> header file.  */
/* #undef HAVE_GCRYPT_H */

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

/* Define if you have the <mach-o/dyld.h> header file.  */
#define HAVE_MACH_O_DYLD_H 1

/* Define if you have the <malloc.h> header file.  */
/* #undef HAVE_MALLOC_H */

/* Define if you have the <memory.h> header file.  */
/* #undef HAVE_MEMORY_H */

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

/* Define if you have the <sched.h> header file.  */
/* #undef HAVE_SCHED_H */

/* Define if you have the <select.h> header file.  */
/* #undef HAVE_SELECT_H */

/* Define if you have the <sgtty.h> header file.  */
/* #undef HAVE_SGTTY_H */

/* Define if you have the <signal.h> header file.  */
#define HAVE_SIGNAL_H 1

/* Define if you have the <st.h> header file.  */
/* #undef HAVE_ST_H */

/* Define if you have the <stdarg.h> header file.  */
#define HAVE_STDARG_H 1

/* Define if you have the <stdbool.h> header file.  */
/* #undef HAVE_STDBOOL_H */

/* Define if you have the <stddef.h> header file.  */
/* #undef HAVE_STDDEF_H */

/* Define if you have the <stdint.h> header file.  */
#define HAVE_STDINT_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
/* #undef HAVE_STRINGS_H */

/* Define if you have the <synch.h> header file.  */
/* #undef HAVE_SYNCH_H */

/* Define if you have the <sys/dir.h> header file.  */
/* #undef HAVE_SYS_DIR_H */

/* Define if you have the <sys/file.h> header file.  */
#define HAVE_SYS_FILE_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
/* #undef HAVE_SYS_IOCTL_H */

/* Define if you have the <sys/ipc.h> header file.  */
#define HAVE_SYS_IPC_H 1

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

/* Define if you have the <sys/statfs.h> header file.  */
/* #undef HAVE_SYS_STATFS_H */

/* Define if you have the <sys/statvfs.h> header file.  */
#define HAVE_SYS_STATVFS_H 1

/* Define if you have the <sys/sysexits.h> header file.  */
/* #undef HAVE_SYS_SYSEXITS_H */

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/timeb.h> header file.  */
/* #undef HAVE_SYS_TIMEB_H */

/* Define if you have the <sys/types.h> header file.  */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/un.h> header file.  */
#define HAVE_SYS_UN_H 1

/* Define if you have the <sys/utime.h> header file.  */
/* #undef HAVE_SYS_UTIME_H */

/* Define if you have the <sys/utsname.h> header file.  */
#define HAVE_SYS_UTSNAME_H 1

/* Define if you have the <sys/vadvise.h> header file.  */
/* #undef HAVE_SYS_VADVISE_H */

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
/* #undef HAVE_TERMIOS_H */

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

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */

/* Define if processor uses big-endian word */
#define WORDS_BIGENDIAN 

/* Enabling BIND8 compatibility for Panther */
/* #undef BIND_8_COMPAT */

/* Whether you have AOLserver */
/* #undef HAVE_AOLSERVER */

/*   */
#define HAVE_AP_CONFIG_H 1

/*   */
#define HAVE_AP_COMPAT_H 1

/*   */
#define HAVE_APACHE 1

/*   */
#define HAVE_APACHE 1

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
/* #undef USE_TRANSFER_TABLES */

/*   */
#define PHP_APACHE_HAVE_CLIENT_FD 1

/* Whether to compile with Caudium support */
/* #undef HAVE_CAUDIUM */

/*   */
/* #undef WITH_ZEUS */

/* Whether you have a Netscape/iPlanet/SunONE Server */
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

/* whether write(2) works */
/* #undef PHP_WRITE_STDOUT */

/*   */
/* #undef FORCE_CGI_REDIRECT */

/*   */
/* #undef DISCARD_PATH */

/*   */
/* #undef ENABLE_PATHINFO_CHECK */

/*   */
/* #undef PHP_FASTCGI */

/*   */
/* #undef PHP_FCGI_STATIC */

/* Define to the necessary symbol if this constant
                           uses a non-standard name on your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define if sockaddr_un in sys/un.h contains a sun_len component */
/* #undef HAVE_SOCKADDR_UN_SUN_LEN */

/* Define if the fpos_t typedef is in stdio.h */
/* #undef HAVE_FPOS */

/* Define if there's a fileno() prototype in stdio.h */
/* #undef HAVE_FILENO_PROTO */

/* Define if the socklen_t typedef is in sys/socket.h */
/* #undef HAVE_SOCKLEN */

/* Define if cross-process locking is required by accept() */
/* #undef USE_LOCKING */

/* Define if va_arg(arg, long double) crashes the compiler */
/* #undef HAVE_VA_ARG_LONG_DOUBLE_BUG */

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

/* whether you have sendmail */
#define HAVE_SENDMAIL 1

/* Define if system uses EBCDIC */
/* #undef CHARSET_EBCDIC */

/*   */
#define HAVE_SOCKET 1

/*   */
#define HAVE_SOCKET 1

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
#define HAVE_RES_SEARCH 1

/*   */
#define HAVE_RES_SEARCH 1

/*   */
/* #undef HAVE_LIBRESOLV */

/*   */
#define HAVE_RES_SEARCH 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define HAVE_RES_SEARCH 1

/*   */
/* #undef HAVE_LIBSOCKET */

/*   */
#define HAVE_INET_ATON 1

/*   */
#define HAVE_INET_ATON 1

/*   */
/* #undef HAVE_LIBRESOLV */

/*   */
#define HAVE_INET_ATON 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
/* #undef HAVE_LIBRESOLV */

/*   */
#define HAVE_DN_SKIPNAME 1

/*   */
/* #undef HAVE_LIBBIND */

/*   */
#define MISSING_FCLOSE_DECL 0

/*   */
#define MISSING_FCLOSE_DECL 0

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

/* whether you have tm_gmtoff in struct tm */
#define HAVE_TM_GMTOFF 1

/* whether you have struct flock */
#define HAVE_STRUCT_FLOCK 1

/* Whether you have socklen_t */
#define HAVE_SOCKLEN_T 1

/* Whether you have struct sockaddr_storage */
#define HAVE_SOCKADDR_STORAGE 1

/* Whether sockaddr struct has sa_len */
#define HAVE_SOCKADDR_LEN 1

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

/* Whether to enable IPv6 support */
#define HAVE_IPV6 1

/* Whether to build openssl as dynamic module */
/* #undef COMPILE_DL_OPENSSL */

/*   */
/* #undef HAVE_OPENSSL_SHARED_EXT */

/*   */
/* #undef HAVE_OPENSSL_EXT */

/* Whether to build pcre as dynamic module */
/* #undef COMPILE_DL_PCRE */

/*   */
#define HAVE_BUNDLED_PCRE 1

/*   */
/* #undef HAVE_PCRE */

/* Whether to build pcre as dynamic module */
/* #undef COMPILE_DL_PCRE */

/* Whether to build zlib as dynamic module */
/* #undef COMPILE_DL_ZLIB */

/*   */
#define HAVE_ZLIB 1

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

/* Whether to build cpdf as dynamic module */
/* #undef COMPILE_DL_CPDF */

/* Whether you have cpdflib */
/* #undef HAVE_CPDFLIB */

/* Whether to build crack as dynamic module */
/* #undef COMPILE_DL_CRACK */

/*   */
/* #undef HAVE_CRACK */

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

/* Whether to build curl as dynamic module */
/* #undef COMPILE_DL_CURL */

/* Whether to build cyrus as dynamic module */
/* #undef COMPILE_DL_CYRUS */

/*   */
/* #undef HAVE_CYRUS */

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
/* #undef DBA_CDB_BUILTIN */

/*   */
/* #undef DBA_CDB_MAKE */

/*   */
/* #undef DBA_CDB */

/*   */
/* #undef DBA_INIFILE */

/*   */
/* #undef DBA_INIFILE */

/*   */
/* #undef DBA_FLATFILE */

/*   */
/* #undef DBA_FLATFILE */

/*   */
/* #undef HAVE_DBA */

/* Whether to build dba as dynamic module */
/* #undef COMPILE_DL_DBA */

/*   */
/* #undef DBASE */

/* Whether to build dbase as dynamic module */
/* #undef COMPILE_DL_DBASE */

/* Whether to build dbx as dynamic module */
/* #undef COMPILE_DL_DBX */

/* Whether to build dio as dynamic module */
/* #undef COMPILE_DL_DIO */

/*   */
/* #undef HAVE_DOMXML */

/* Whether to build domxml as dynamic module */
/* #undef COMPILE_DL_DOMXML */

/*   */
/* #undef HAVE_DOMXSLT */

/*   */
/* #undef HAVE_DOMEXSLT */

/* Whether you want EXIF (metadata from images) support */
#define HAVE_EXIF 1

/* Whether to build exif as dynamic module */
/* #undef COMPILE_DL_EXIF */

/* Whether you have FrontBase */
/* #undef HAVE_FBSQL */

/* Whether to build fbsql as dynamic module */
/* #undef COMPILE_DL_FBSQL */

/*   */
/* #undef HAVE_FDFTK_H_LOWER */

/*   */
/* #undef HAVE_FDFTK_5 */

/* Whether to build fdf as dynamic module */
/* #undef COMPILE_DL_FDF */

/*   */
/* #undef HAVE_FDFLIB */

/*   */
/* #undef HAVE_FILEPRO */

/* Whether to build filepro as dynamic module */
/* #undef COMPILE_DL_FILEPRO */

/* Whether to build fribidi as dynamic module */
/* #undef COMPILE_DL_FRIBIDI */

/*   */
/* #undef HAVE_FRIBIDI */

/* Whether you want FTP support */
#define HAVE_FTP 1

/* Whether to build ftp as dynamic module */
/* #undef COMPILE_DL_FTP */

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
/* #undef HAVE_LIBGD */

/*   */
/* #undef HAVE_LIBGD13 */

/*   */
/* #undef HAVE_LIBGD15 */

/*   */
/* #undef HAVE_LIBGD20 */

/*   */
/* #undef HAVE_LIBGD204 */

/*   */
/* #undef HAVE_GD_IMAGESETTILE */

/*   */
/* #undef HAVE_GD_IMAGESETBRUSH */

/*   */
/* #undef HAVE_GDIMAGECOLORRESOLVE */

/*   */
/* #undef HAVE_COLORCLOSESTHWB */

/*   */
/* #undef HAVE_GD_WBMP */

/*   */
/* #undef HAVE_GD_GD2 */

/*   */
/* #undef HAVE_GD_PNG */

/*   */
/* #undef HAVE_GD_XBM */

/*   */
/* #undef HAVE_GD_BUNDLED */

/*   */
/* #undef HAVE_GD_GIF_READ */

/*   */
/* #undef HAVE_GD_GIF_CREATE */

/*   */
/* #undef HAVE_GD_IMAGEELLIPSE */

/*   */
/* #undef HAVE_GD_FONTCACHESHUTDOWN */

/*   */
/* #undef HAVE_GD_DYNAMIC_CTX_EX */

/*   */
/* #undef HAVE_GD_GIF_CTX */

/*   */
/* #undef HAVE_GD_JPG */

/*   */
/* #undef HAVE_GD_XPM */

/*   */
/* #undef HAVE_GD_STRINGFT */

/*   */
/* #undef HAVE_GD_STRINGFTEX */

/*   */
/* #undef USE_GD_JISX0208 */

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
/* #undef HAVE_GD_IMAGEELLIPSE */

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
/* #undef HAVE_GD_CACHE_CREATE */

/*   */
/* #undef HAVE_GD_FONTCACHESHUTDOWN */

/*   */
/* #undef HAVE_GD_FREEFONTCACHE */

/*   */
/* #undef HAVE_GD_DYNAMIC_CTX_EX */

/*   */
/* #undef HAVE_LIBGD204 */

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
/* #undef HAVE_HWAPI */

/* Whether to build hwapi as dynamic module */
/* #undef COMPILE_DL_HWAPI */

/*   */
#define HYPERWAVE 0

/* Whether to build hyperwave as dynamic module */
/* #undef COMPILE_DL_HYPERWAVE */

/*   */
#define HYPERWAVE 0

/*   */
#define HYPERWAVE 0

/*   */
/* #undef HAVE_GICONV_H */

/*   */
/* #undef HAVE_ICONV */

/* Which iconv implementation to use */
/* #undef PHP_ICONV_IMPL */

/* Konstantin Chuguev's iconv implementation */
/* #undef HAVE_BSD_ICONV */

/* Which iconv implementation to use */
/* #undef PHP_ICONV_IMPL */

/* glibc's iconv implementation */
/* #undef HAVE_GLIBC_ICONV */

/* Which iconv implementation to use */
/* #undef PHP_ICONV_IMPL */

/* Whether iconv supports error no or not */
/* #undef ICONV_SUPPORTS_ERRNO */

/* Whether iconv supports error no or not */
/* #undef ICONV_SUPPORTS_ERRNO */

/* Path to iconv.h */
/* #undef PHP_ICONV_H_PATH */

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
/* #undef IFX_VERSION */

/*   */
/* #undef HAVE_IFX_IUS */

/* Whether to build informix as dynamic module */
/* #undef COMPILE_DL_INFORMIX */

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

/*   */
/* #undef HAVE_JAVA */

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
/* #undef HAVE_NSLDAP */

/*   */
/* #undef HAVE_ORALDAP */

/*   */
/* #undef HAVE_ORALDAP_10 */

/*   */
#define HAVE_LDAP 1

/* Whether 3 arg set_rebind_proc() */
#define HAVE_3ARG_SETREBINDPROC 1

/* whether to have multibyte string support */
#define HAVE_MBSTRING 1

/* whether to have multibyte regex support */
#define HAVE_MBREGEX 1

/* Whether to build mbstring as dynamic module */
/* #undef COMPILE_DL_MBSTRING */

/*   */
/* #undef HAVE_MCAL */

/* Whether to build mcal as dynamic module */
/* #undef COMPILE_DL_MCAL */

/*   */
/* #undef HAVE_LIBMCRYPT24 */

/*   */
/* #undef HAVE_MCRYPT_GENERIC_DEINIT */

/*   */
/* #undef HAVE_LIBMCRYPT24 */

/*   */
/* #undef HAVE_MCRYPT_GENERIC_DEINIT */

/*   */
/* #undef HAVE_LIBMCRYPT22 */

/* Whether to build mcrypt as dynamic module */
/* #undef COMPILE_DL_MCRYPT */

/*   */
/* #undef HAVE_LIBMCRYPT */

/* Whether or not we're using libmonetra 4.2 or higher  */
/* #undef LIBMONETRA_BELOW_4_2 */

/*   */
/* #undef HAVE_MCVE */

/* Whether to build mcve as dynamic module */
/* #undef COMPILE_DL_MCVE */

/* Whether to build mhash as dynamic module */
/* #undef COMPILE_DL_MHASH */

/*   */
/* #undef HAVE_LIBMHASH */

/* Whether to build mime_magic as dynamic module */
/* #undef COMPILE_DL_MIME_MAGIC */

/* magic file path */
/* #undef PHP_MIME_MAGIC_FILE_PATH */

/*   */
/* #undef HAVE_MING */

/*   */
/* #undef HAVE_DESTROY_SWF_BLOCK */

/*   */
/* #undef HAVE_NEW_MING */

/*   */
/* #undef HAVE_MING_ZLIB */

/* Whether to build ming as dynamic module */
/* #undef COMPILE_DL_MING */

/*   */
/* #undef HAVE_MNOGOSEARCH */

/* Whether to build mnogosearch as dynamic module */
/* #undef COMPILE_DL_MNOGOSEARCH */

/*   */
/* #undef HAVE_MSESSION */

/* Whether to build msession as dynamic module */
/* #undef COMPILE_DL_MSESSION */

/*   */
/* #undef HAVE_MSQL */

/* Whether to build msql as dynamic module */
/* #undef COMPILE_DL_MSQL */

/*   */
/* #undef MSQL1 */

/*   */
/* #undef MSQL1 */

/* Whether to build mssql as dynamic module */
/* #undef COMPILE_DL_MSSQL */

/*   */
/* #undef HAVE_LIBDNET_STUB */

/*   */
/* #undef HAVE_MSSQL */

/*   */
/* #undef HAVE_FREETDS */

/* Whether you have MySQL */
#define HAVE_MYSQL 1

/*   */
#define MYSQL_UNIX_ADDR "/var/mysql/mysql.sock"

/*   */
#define MYSQL_UNIX_ADDR "/var/mysql/mysql.sock"

/*   */
/* #undef UNDEF_THREADS_HACK */

/*   */
/* #undef HAVE_ULONG */

/*   */
/* #undef HAVE_UCHAR */

/*   */
#define HAVE_UINT 

/*   */
#define HAVE_USHORT 

/*   */
/* #undef HAVE_INT_8_16_32 */

/*   */
#define SOCKET_SIZE_TYPE socklen_t

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

/* Whether to build mysql as dynamic module */
/* #undef COMPILE_DL_MYSQL */

/*   */
/* #undef HAVE_ULONG */

/*   */
/* #undef HAVE_UCHAR */

/*   */
#define HAVE_UINT 

/*   */
#define HAVE_USHORT 

/*   */
/* #undef HAVE_INT_8_16_32 */

/*   */
#define SOCKET_SIZE_TYPE socklen_t

/*   */
#define RETQSORTTYPE void

/*   */
#define QSORT_TYPE_IS_VOID 1

/* Whether to build mysql as dynamic module */
/* #undef COMPILE_DL_MYSQL */

/*   */
/* #undef HAVE_NCURSES_H */

/*   */
/* #undef HAVE_NCURSESLIB */

/*   */
/* #undef HAVE_NCURSES_PANEL */

/*   */
/* #undef HAVE_NCURSES_COLOR_SET */

/*   */
/* #undef HAVE_NCURSES_SLK_COLOR */

/*   */
/* #undef HAVE_NCURSES_ASSUME_DEFAULT_COLORS */

/*   */
/* #undef HAVE_NCURSES_USE_EXTENDED_NAMES */

/* Whether to build ncurses as dynamic module */
/* #undef COMPILE_DL_NCURSES */

/*   */
/* #undef HAVE_OCI8_ATTR_STATEMENT */

/*   */
/* #undef HAVE_OCI8_ATTR_STATEMENT */

/*   */
/* #undef HAVE_OCI_9_2 */

/*   */
/* #undef HAVE_OCI8_ATTR_STATEMENT */

/*   */
/* #undef HAVE_OCI_9_2 */

/*   */
/* #undef HAVE_OCI8_TEMP_LOB */

/*   */
/* #undef PHP_OCI8_HAVE_COLLECTIONS */

/*   */
/* #undef HAVE_OCI8_TEMP_LOB */

/*   */
/* #undef HAVE_OCI8_TEMP_LOB */

/*   */
/* #undef PHP_OCI8_HAVE_COLLECTIONS */

/* Whether to build oci8 as dynamic module */
/* #undef COMPILE_DL_OCI8 */

/*   */
/* #undef HAVE_OCI8 */

/*   */
/* #undef HAVE_OCI8_ATTR_STATEMENT */

/*   */
/* #undef HAVE_OCI_9_2 */

/*   */
/* #undef HAVE_OCI8_TEMP_LOB */

/*   */
/* #undef PHP_OCI8_HAVE_COLLECTIONS */

/*   */
/* #undef HAVE_OCI_INSTANT_CLIENT */

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

/* Whether to build oracle as dynamic module */
/* #undef COMPILE_DL_ORACLE */

/*   */
/* #undef HAVE_ORACLE */

/*   */
#define HAVE_OVERLOAD 1

/* Whether to build overload as dynamic module */
/* #undef COMPILE_DL_OVERLOAD */

/*   */
/* #undef HAVE_FORK */

/*   */
/* #undef HAVE_WAITPID */

/*   */
/* #undef HAVE_SIGACTION */

/* Whether to build pcntl as dynamic module */
/* #undef COMPILE_DL_PCNTL */

/* Whether to build pdf as dynamic module */
/* #undef COMPILE_DL_PDF */

/*   */
/* #undef HAVE_PDFLIB */

/*   */
/* #undef HAVE_PDFLIB */

/* Version of SDK */
/* #undef PFPRO_VERSION */

/* Whether to build pfpro as dynamic module */
/* #undef COMPILE_DL_PFPRO */

/*   */
/* #undef HAVE_PFPRO */

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
/* #undef HAVE_PQSETERRORVERBOSITY */

/* Whether libpq is compiled with --enable-multibyte */
/* #undef HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT */

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

/* Whether to build qtdom as dynamic module */
/* #undef COMPILE_DL_QTDOM */

/* Whether you have qtdom */
/* #undef HAVE_QTDOM */

/*   */
/* #undef HAVE_RL_CALLBACK_READ_CHAR */

/* Whether to build readline as dynamic module */
/* #undef COMPILE_DL_READLINE */

/*   */
/* #undef HAVE_LIBREADLINE */

/* Whether to build readline as dynamic module */
/* #undef COMPILE_DL_READLINE */

/*   */
/* #undef HAVE_LIBEDIT */

/* Whether we have librecode 3.5 */
/* #undef HAVE_BROKEN_RECODE */

/* Whether we have librecode 3.5 or higher */
/* #undef HAVE_LIBRECODE */

/* Whether to build recode as dynamic module */
/* #undef COMPILE_DL_RECODE */

/*   */
/* #undef HAVE_PWRITE */

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
/* #undef HAVE_SHMOP */

/* Whether to build shmop as dynamic module */
/* #undef COMPILE_DL_SHMOP */

/*   */
/* #undef HAVE_NET_SNMP */

/*   */
/* #undef HAVE_SNMP_PARSE_OID */

/*   */
/* #undef HAVE_SNMP */

/* Whether to build snmp as dynamic module */
/* #undef COMPILE_DL_SNMP */

/*   */
/* #undef UCD_SNMP_HACK */

/* Whether you have struct cmsghdr */
#define HAVE_CMSGHDR 1

/*   */
/* #undef MISSING_MSGHDR_MSGFLAGS */

/*   */
#define HAVE_SOCKETS 1

/* Whether to build sockets as dynamic module */
/* #undef COMPILE_DL_SOCKETS */

/*   */
#define HAVE_CRYPT 1

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

/*  see #24142  */
#define PHP_ROUND_FUZZ 0.5

/* Whether to enable chroot() function */
/* #undef ENABLE_CHROOT_FUNC */

/* whether atof() accepts NAN */
#define HAVE_ATOF_ACCEPTS_NAN 1

/* whether atof() accepts INF */
#define HAVE_ATOF_ACCEPTS_INF 1

/* whether HUGE_VAL == INF */
#define HAVE_HUGE_VAL_INF 1

/* whether HUGE_VAL + -HUGEVAL == NAN */
#define HAVE_HUGE_VAL_NAN 1

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

/*   */
/* #undef HAVE_SYSVMSG */

/* Whether to build sysvmsg as dynamic module */
/* #undef COMPILE_DL_SYSVMSG */

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

/* Whether to build tokenizer as dynamic module */
/* #undef COMPILE_DL_TOKENIZER */

/*   */
/* #undef HAVE_WDDX */

/* Whether to build wddx as dynamic module */
/* #undef COMPILE_DL_WDDX */

/* Define if processor uses big-endian word */
#define WORDS_BIGENDIAN 

/*   */
#define HAVE_LIBEXPAT 1

/* Bundled libexpat is used. */
#define HAVE_LIBEXPAT_BUNDLED 1

/* Define to make XML Namespaces functionality available. */
#define XML_NS 1

/* Define to make parameter entity parsing functionality available. */
#define XML_DTD 1

/* Define to specify how much context to retain around the current parse point. */
#define XML_CONTEXT_BYTES 1024

/* Whether to build xml as dynamic module */
/* #undef COMPILE_DL_XML */

/* Whether to build xml as dynamic module */
/* #undef COMPILE_DL_XML */

/*   */
/* #undef HAVE_XMLRPC */

/*   */
/* #undef HAVE_LIBEXPAT2 */

/*   */
/* #undef HAVE_GICONV_H */

/*   */
/* #undef HAVE_ICONV */

/*   */
/* #undef UNDEF_THREADS_HACK */

/* Whether to build xmlrpc as dynamic module */
/* #undef COMPILE_DL_XMLRPC */

/* Whether to build xslt as dynamic module */
/* #undef COMPILE_DL_XSLT */

/* Whether the Sablotron config file is found */
/* #undef HAVE_SABLOT_CONFIG */

/*   */
/* #undef HAVE_LIBEXPAT2 */

/*   */
/* #undef HAVE_GICONV_H */

/*   */
/* #undef HAVE_ICONV */

/*   */
/* #undef HAVE_SABLOT_SET_ENCODING */

/* Whether Sablotron supports SablotGetOptions */
/* #undef HAVE_SABLOT_GET_OPTIONS */

/*   */
/* #undef HAVE_SABLOT_BACKEND */

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

/*   */
/* #undef HAVE_NEW_ZZIPLIB */

/*   */
/* #undef HAVE_ZZIPLIB */

/* Whether to build zip as dynamic module */
/* #undef COMPILE_DL_ZIP */

/* Define if int32_t type is present.  */
#define HAVE_INT32_T 1

/* Define if uint32_t type is present.  */
#define HAVE_UINT32_T 1

/* whether floatingpoint.h defines fp_except */
/* #undef HAVE_FP_EXCEPT */

/* Define if dlsym() requires a leading underscore in symbol names.  */
/* #undef DLSYM_NEEDS_UNDERSCORE */

/*   */
#define ZEND_DEBUG 0

/*   */
#define ZEND_DEBUG 0

/* Use Zend memory manager */
#define USE_ZEND_ALLOC 1

/* Use Zend memory manager */
#define USE_ZEND_ALLOC 1

/*   */
/* #undef ZTS */

/* Memory limit */
#define MEMORY_LIMIT 0

/* Memory limit */
#define MEMORY_LIMIT 0

/*   */
/* #undef ZEND_MULTIBYTE */

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
#define PHP_BUILD_DATE "2008-02-22"

/* hardcode for each of the cross compiler host */
#define PHP_OS "Darwin"

/* hardcode for each of the cross compiler host */
#define PHP_UNAME "Darwin b37.apple.com 8.0 Darwin Kernel Version 8.8.4: Sun Oct 29 15:30:27 PST 2006; root:xnu-792.16.4.obj~1/RELEASE_PPC Power Macintosh powerpc"

/* uname -a output */
#define PHP_UNAME "Darwin b37.apple.com 8.0 Darwin Kernel Version 8.8.4: Sun Oct 29 15:30:27 PST 2006; root:xnu-792.16.4.obj~1/RELEASE_PPC Power Macintosh powerpc"

/* uname output */
#define PHP_OS "Darwin"

/*   */
#define HAVE_BUILD_DEFS_H 1


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

int zend_sprintf(char *buffer, const char *format, ...);

#include <math.h>

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

#ifdef NETWARE
#ifdef USE_WINSOCK
#/*This detection against winsock is of no use*/ undef HAVE_SOCKLEN_T
#/*This detection against winsock is of no use*/ undef HAVE_SYS_SOCKET_H
#endif
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
/* #undef PTHREADS */
