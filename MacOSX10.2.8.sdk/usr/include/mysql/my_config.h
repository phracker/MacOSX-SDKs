/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */
/* acconfig.h
   This file is in the public domain.

   Descriptive text for the C preprocessor macros that
   the distributed Autoconf macros can define.
   No software package will use all of them; autoheader copies the ones
   your configure.in uses into your configuration header file templates.

   The entries are in sort -df order: alphabetical, case insensitive,
   ignoring punctuation (such as underscores).  Although this order
   can split up related entries, it makes it easier to check whether
   a given entry is in the file.

   Leave the following blank line there!!  Autoheader needs it.  */


/* #undef C_ALLOCA */

/* #undef CRAY_STACKSEG_END */

/* Version of .frm files */
#define DOT_FRM_VERSION 6

/* If LOAD DATA LOCAL INFILE should be enabled by default */
/* #undef ENABLED_LOCAL_INFILE */

/* READLINE: */
#define FIONREAD_IN_SYS_IOCTL 1

/* READLINE: Define if your system defines TIOCGWINSZ in sys/ioctl.h.  */
#define GWINSZ_IN_SYS_IOCTL 1

/* Handing of large files on Solaris 2.6 */
/* #undef _FILE_OFFSET_BITS */

/* Do we have FIONREAD */
#define FIONREAD_IN_SYS_IOCTL 1

/* Do we need to define _GNU_SOURCE */
/* #undef _GNU_SOURCE */

/* atomic_add() from <asm/atomic.h> (Linux only) */
/* #undef HAVE_ATOMIC_ADD */

/* atomic_sub() from <asm/atomic.h> (Linux only) */
/* #undef HAVE_ATOMIC_SUB */

/* If we have a working alloca() implementation */
#define HAVE_ALLOCA 1

/* bool is not defined by all C++ compilators */
#define HAVE_BOOL 1

/* Have berkeley db installed */
/* #undef HAVE_BERKELEY_DB */

/* DSB style signals ? */
/* #undef HAVE_BSD_SIGNALS */

/* Can netinet be included */
/* #undef HAVE_BROKEN_NETINET_INCLUDES */

/* READLINE: */
/* #undef HAVE_BSD_SIGNALS */

/* ZLIB and compress: */
#define HAVE_COMPRESS 1

/* Define if we are using OSF1 DEC threads */
/* #undef HAVE_DEC_THREADS */

/* Define if we are using OSF1 DEC threads on 3.2 */
/* #undef HAVE_DEC_3_2_THREADS */

/* fp_except from ieeefp.h */
/* #undef HAVE_FP_EXCEPT */

/* READLINE: */
/* #undef HAVE_GETPW_DECLS */

/* Solaris define gethostbyname_r with 5 arguments. glibc2 defines
   this with 6 arguments */
/* #undef HAVE_GETHOSTBYNAME_R_GLIBC2_STYLE */

/* In OSF 4.0f the 3'd argument to gethostname_r is hostent_data * */
/* #undef HAVE_GETHOSTBYNAME_R_RETURN_INT */

/* Define if int8, int16 and int32 types exist */
/* #undef HAVE_INT_8_16_32 */

/* Using Innobase DB */
/* #undef HAVE_INNOBASE_DB */

/* Define if we have GNU readline */
/* #undef HAVE_LIBREADLINE */

/* Define if have -lwrap */
/* #undef HAVE_LIBWRAP */

/* Define if we are using Xavier Leroy's LinuxThreads */
/* #undef HAVE_LINUXTHREADS */

/* Do we have lstat */
#define HAVE_LSTAT 1

/* Do we use user level threads */
/* #undef HAVE_mit_thread */

/* For some non posix threads */
/* #undef HAVE_NONPOSIX_PTHREAD_GETSPECIFIC */

/* For some non posix threads */
/* #undef HAVE_NONPOSIX_PTHREAD_MUTEX_INIT */

/* READLINE: */
#define HAVE_POSIX_SIGNALS 1

/* Well.. */
/* #undef HAVE_POSIX_SIGSETJMP */

/* sigwait with one argument */
/* #undef HAVE_NONPOSIX_SIGWAIT */

/* pthread_attr_setscope */
#define HAVE_PTHREAD_ATTR_SETSCOPE 1

/* pthread_yield that doesn't take any arguments */
/* #undef HAVE_PTHREAD_YIELD_ZERO_ARG */

/* pthread_yield function with one argument */
/* #undef HAVE_PTHREAD_YIELD_ONE_ARG */

/* POSIX readdir_r */
#define HAVE_READDIR_R 1

/* Have Gemini db installed */
/* #undef HAVE_GEMINI_DB */

/* POSIX sigwait */
#define HAVE_SIGWAIT 1

/* crypt */
#define HAVE_CRYPT 1

/* Solaris define gethostbyaddr_r with 7 arguments. glibc2 defines
   this with 8 arguments */
/* #undef HAVE_SOLARIS_STYLE_GETHOST */

/* MIT pthreads does not support connecting with unix sockets */
/* #undef HAVE_THREADS_WITHOUT_SOCKETS */

/* Timespec has a ts_sec instead of tv_sev  */
/* #undef HAVE_TIMESPEC_TS_SEC */

/* Have the tzname variable */
#define HAVE_TZNAME 1

/* Define if the system files define uchar */
/* #undef HAVE_UCHAR */

/* Define if the system files define uint */
#define HAVE_UINT 1

/* Define if the system files define ulong */
/* #undef HAVE_ULONG */

/* UNIXWARE7 threads are not posix */
/* #undef HAVE_UNIXWARE7_THREADS */

/* new UNIXWARE7 threads that are not yet posix */
/* #undef HAVE_UNIXWARE7_POSIX */

/* READLINE: */
/* #undef HAVE_USG_SIGHOLD */

/* Handling of large files on Solaris 2.6 */
/* #undef _LARGEFILE_SOURCE */

/* Handling of large files on Solaris 2.6 */
/* #undef _LARGEFILE64_SOURCE */

/* Define if want -lwrap */
/* #undef LIBWRAP */

/* Define to machine type name eg sun10 */
#define MACHINE_TYPE "powerpc"

/* #undef MUST_REINSTALL_SIGHANDLERS */

/* Defined to used character set */
/* #undef MY_CHARSET_CURRENT */

/* READLINE: no sys file*/
/* #undef NO_SYS_FILE */

/* Program name */
#define PACKAGE "mysql"

/* mysql client protocoll version */
#define PROTOCOL_VERSION 10

/* Define if qsort returns void */
#define QSORT_TYPE_IS_VOID 1

/* Define as the return type of qsort (int or void). */
#define RETQSORTTYPE void

/* Size of off_t */
#define SIZEOF_OFF_T 8

/* Define as the base type of the last arg to accept */
#define SOCKET_SIZE_TYPE int

/* Last argument to get/setsockopt */
/* #undef SOCKOPT_OPTLEN_TYPE */

/* #undef SPEED_T_IN_SYS_TYPES */
/* #undef SPRINTF_RETURNS_PTR */
#define SPRINTF_RETURNS_INT 1
/* #undef SPRINTF_RETURNS_GARBAGE */

/* Needed to get large file supportat HPUX 10.20 */
/* #undef __STDC_EXT__ */

#define STACK_DIRECTION -1

/* #undef STRCOLL_BROKEN */

/* #undef STRUCT_DIRENT_HAS_D_FILENO */
#define STRUCT_DIRENT_HAS_D_INO 1

/* #undef STRUCT_WINSIZE_IN_SYS_IOCTL */
/* #undef STRUCT_WINSIZE_IN_TERMIOS */

/* Define to name of system eg solaris*/
#define SYSTEM_TYPE "apple-darwin6.0"

/* Define if you want to have threaded code. This may be undef on client code */
#define THREAD 1

/* Should be client be thread safe */
/* #undef THREAD_SAFE_CLIENT */

/* READLINE: */
#define TIOCSTAT_IN_SYS_IOCTL 1

/* Use multi-byte character routines */
/* #undef USE_MB */
/* #undef USE_MB_IDENT */

/* Use MySQL RAID */
/* #undef USE_RAID */

/* Use strcoll() functions when comparing and sorting. */
/* #undef USE_STRCOLL */

/* Program version */
#define VERSION "3.23.53"

/* READLINE: */
#define VOID_SIGHANDLER 1


/* Leave that blank line there!!  Autoheader needs it.
   If you're adding to this file, keep in mind:
   The entries are in sort -df order: alphabetical, case insensitive,
   ignoring punctuation (such as underscores).  */

/* Define if you have the `alarm' function. */
#define HAVE_ALARM 1

/* Define if you have the <alloca.h> header file. */
/* #undef HAVE_ALLOCA_H */

/* Define if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <asm/termbits.h> header file. */
/* #undef HAVE_ASM_TERMBITS_H */

/* Define if you have the `atod' function. */
/* #undef HAVE_ATOD */

/* Define if you have the `bcmp' function. */
#define HAVE_BCMP 1

/* Define if you have the `bfill' function. */
/* #undef HAVE_BFILL */

/* Define if you have the `bmove' function. */
/* #undef HAVE_BMOVE */

/* Define if you have the `bzero' function. */
#define HAVE_BZERO 1

/* Define if you have the `chsize' function. */
/* #undef HAVE_CHSIZE */

/* Define if you have the <crypt.h> header file. */
/* #undef HAVE_CRYPT_H */

/* Define if you have the <curses.h> header file. */
#define HAVE_CURSES_H 1

/* Define if you have the `cuserid' function. */
/* #undef HAVE_CUSERID */

/* Define if you have the <dirent.h> header file. */
#define HAVE_DIRENT_H 1

/* Define if you have the `dlerror' function. */
/* #undef HAVE_DLERROR */

/* Define if you have the `dlopen' function. */
/* #undef HAVE_DLOPEN */

/* Define if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define if you have the `fchmod' function. */
#define HAVE_FCHMOD 1

/* Define if you have the `fcntl' function. */
#define HAVE_FCNTL 1

/* Define if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define if you have the `fconvert' function. */
/* #undef HAVE_FCONVERT */

/* Define if you have the `finite' function. */
#define HAVE_FINITE 1

/* Define if you have the <floatingpoint.h> header file. */
/* #undef HAVE_FLOATINGPOINT_H */

/* Define if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define if you have the `fpresetsticky' function. */
/* #undef HAVE_FPRESETSTICKY */

/* Define if you have the `fpsetmask' function. */
/* #undef HAVE_FPSETMASK */

/* Define if you have the `fseeko' function. */
#define HAVE_FSEEKO 1

/* Define if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define if you have the `gethostbyaddr_r' function. */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define if you have the `gethostbyname_r' function. */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define if you have the `getpass' function. */
#define HAVE_GETPASS 1

/* Define if you have the `getpassphrase' function. */
/* #undef HAVE_GETPASSPHRASE */

/* Define if you have the `getpwnam' function. */
#define HAVE_GETPWNAM 1

/* Define if you have the `getpwuid' function. */
#define HAVE_GETPWUID 1

/* Define if you have the `getrlimit' function. */
#define HAVE_GETRLIMIT 1

/* Define if you have the `getrusage' function. */
#define HAVE_GETRUSAGE 1

/* Define if you have the `getwd' function. */
#define HAVE_GETWD 1

/* Define if you have the <grp.h> header file. */
#define HAVE_GRP_H 1

/* Define if you have the <ieeefp.h> header file. */
/* #undef HAVE_IEEEFP_H */

/* Define if you have the `index' function. */
#define HAVE_INDEX 1

/* Define if you have the `initgroups' function. */
#define HAVE_INITGROUPS 1

/* Define if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have the `isnan' function. */
#define HAVE_ISNAN 1

/* Define if you have the `bind' library (-lbind). */
/* #undef HAVE_LIBBIND */

/* Define if you have the `compat' library (-lcompat). */
/* #undef HAVE_LIBCOMPAT */

/* Define if you have the `crypt' library (-lcrypt). */
/* #undef HAVE_LIBCRYPT */

/* Define if you have the `c_r' library (-lc_r). */
/* #undef HAVE_LIBC_R */

/* Define if you have the `dl' library (-ldl). */
/* #undef HAVE_LIBDL */

/* Define if you have the `gen' library (-lgen). */
/* #undef HAVE_LIBGEN */

/* Define if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* Define if you have the `nsl_r' library (-lnsl_r). */
/* #undef HAVE_LIBNSL_R */

/* Define if you have the `posix4' library (-lposix4). */
/* #undef HAVE_LIBPOSIX4 */

/* Define if you have the `pthread' library (-lpthread). */
#define HAVE_LIBPTHREAD 1

/* Define if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define if you have the `locking' function. */
/* #undef HAVE_LOCKING */

/* Define if you have the `longjmp' function. */
#define HAVE_LONGJMP 1

/* Define if you have the `lrand48' function. */
#define HAVE_LRAND48 1

/* Define if you have the `lstat' function. */
#define HAVE_LSTAT 1

/* Define if you have the `madvise' function. */
#define HAVE_MADVISE 1

/* Define if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define if you have the `mlockall' function. */
#define HAVE_MLOCKALL 1

/* Define if you have a working `mmap' system call. */
#define HAVE_MMAP 1

/* Define if you have the <ndir.h> header file. */
/* #undef HAVE_NDIR_H */

/* Define if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define if you have the <paths.h> header file. */
#define HAVE_PATHS_H 1

/* Define if you have the `perror' function. */
#define HAVE_PERROR 1

/* Define if you have the `poll' function. */
/* #undef HAVE_POLL */

/* Define if you have the `pread' function. */
#define HAVE_PREAD 1

/* Define if you have the `pthread_attr_create' function. */
/* #undef HAVE_PTHREAD_ATTR_CREATE */

/* Define if you have the `pthread_attr_setprio' function. */
/* #undef HAVE_PTHREAD_ATTR_SETPRIO */

/* Define if you have the `pthread_attr_setschedparam' function. */
#define HAVE_PTHREAD_ATTR_SETSCHEDPARAM 1

/* Define if you have the `pthread_attr_setstacksize' function. */
#define HAVE_PTHREAD_ATTR_SETSTACKSIZE 1

/* Define if you have the `pthread_condattr_create' function. */
/* #undef HAVE_PTHREAD_CONDATTR_CREATE */

/* Define if you have the `pthread_getsequence_np' function. */
/* #undef HAVE_PTHREAD_GETSEQUENCE_NP */

/* Define if you have the `pthread_init' function. */
/* #undef HAVE_PTHREAD_INIT */

/* Define if you have the `pthread_rwlock_rdlock' function. */
#define HAVE_PTHREAD_RWLOCK_RDLOCK 1

/* Define if you have the `pthread_setprio' function. */
/* #undef HAVE_PTHREAD_SETPRIO */

/* Define if you have the `pthread_setprio_np' function. */
/* #undef HAVE_PTHREAD_SETPRIO_NP */

/* Define if you have the `pthread_setschedparam' function. */
#define HAVE_PTHREAD_SETSCHEDPARAM 1

/* Define if you have the `pthread_sigmask' function. */
#define HAVE_PTHREAD_SIGMASK 1

/* Define if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define if you have the `readlink' function. */
#define HAVE_READLINK 1

/* Define if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define if you have the `rename' function. */
#define HAVE_RENAME 1

/* Define if system calls automatically restart after interruption by a
   signal. */
#define HAVE_RESTARTABLE_SYSCALLS 1

/* Define if you have the `rint' function. */
#define HAVE_RINT 1

/* Define if you have the `rwlock_init' function. */
/* #undef HAVE_RWLOCK_INIT */

/* Define if you have the <sched.h> header file. */
#define HAVE_SCHED_H 1

/* Define if you have the `select' function. */
#define HAVE_SELECT 1

/* Define if you have the <select.h> header file. */
/* #undef HAVE_SELECT_H */

/* Define if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define if you have the `setupterm' function. */
/* #undef HAVE_SETUPTERM */

/* Define if you have the `sighold' function. */
#define HAVE_SIGHOLD 1

/* Define if you have the `sigset' function. */
/* #undef HAVE_SIGSET */

/* Define if you have the `sigthreadmask' function. */
/* #undef HAVE_SIGTHREADMASK */

/* Define if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if you have the `stpcpy' function. */
/* #undef HAVE_STPCPY */

/* Define if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define if you have the `strcoll' function. */
#define HAVE_STRCOLL 1

/* Define if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define if you have the `strnlen' function. */
/* #undef HAVE_STRNLEN */

/* Define if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define if you have the `strtok_r' function. */
#define HAVE_STRTOK_R 1

/* Define if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define if you have the `strtoll' function. */
#define HAVE_STRTOLL 1

/* Define if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define if you have the `strtoull' function. */
#define HAVE_STRTOULL 1

/* Define if `st_rdev' is member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_RDEV 1

/* Define if your `struct stat' has `st_rdev'. Deprecated, use
   `HAVE_STRUCT_STAT_ST_RDEV' instead. */
#define HAVE_ST_RDEV 1

/* Define if you have the <synch.h> header file. */
/* #undef HAVE_SYNCH_H */

/* Define if you have the <sys/dir.h> header file. */
#define HAVE_SYS_DIR_H 1

/* Define if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define if you have the <sys/ndir.h> header file. */
/* #undef HAVE_SYS_NDIR_H */

/* Define if you have the <sys/ptem.h> header file. */
/* #undef HAVE_SYS_PTEM_H */

/* Define if you have the <sys/pte.h> header file. */
/* #undef HAVE_SYS_PTE_H */

/* Define if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/stream.h> header file. */
/* #undef HAVE_SYS_STREAM_H */

/* Define if you have the <sys/timeb.h> header file. */
#define HAVE_SYS_TIMEB_H 1

/* Define if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define if you have the <sys/utime.h> header file. */
/* #undef HAVE_SYS_UTIME_H */

/* Define if you have the <sys/vadvise.h> header file. */
#define HAVE_SYS_VADVISE_H 1

/* Define if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define if you have the `tcgetattr' function. */
#define HAVE_TCGETATTR 1

/* Define if you have the `tell' function. */
/* #undef HAVE_TELL */

/* Define if you have the `tempnam' function. */
#define HAVE_TEMPNAM 1

/* Define if you have the <termbits.h> header file. */
/* #undef HAVE_TERMBITS_H */

/* Define if you have the <termcap.h> header file. */
#define HAVE_TERMCAP_H 1

/* Define if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define if you have the <termio.h> header file. */
/* #undef HAVE_TERMIO_H */

/* Define if you have the <term.h> header file. */
#define HAVE_TERM_H 1

/* Define if you have the `thr_setconcurrency' function. */
/* #undef HAVE_THR_SETCONCURRENCY */

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define if `utime(file, NULL)' sets file's timestamp to the present. */
#define HAVE_UTIME_NULL 1

/* Define if you have the <varargs.h> header file. */
#define HAVE_VARARGS_H 1

/* Define if you have the `vidattr' function. */
/* #undef HAVE_VIDATTR */

/* Define if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Name of package */
#define PACKAGE "mysql"

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* The size of a `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of a `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* Define if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Version number of package */
#define VERSION "3.23.53"

/* Define if your processor stores words with the most significant byte first
   (like Motorola and SPARC, unlike Intel and VAX). */
#define WORDS_BIGENDIAN 1

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to make fseeko etc. visible, on some hosts. */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define as `__inline' if that's what the C compiler calls it, or to nothing
   if it is not supported. */
/* #undef inline */

/* Define to `long' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `unsigned' if <sys/types.h> does not define. */
/* #undef size_t */
