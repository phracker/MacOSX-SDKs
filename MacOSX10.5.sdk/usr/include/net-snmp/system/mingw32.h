/*
 * The Win32 API is maintained by the MinGW developers.
 * The licensing for the Win32 API is defined in the
 * MinGW file README.w32api, which states:

   "Unless otherwise stated in individual source files,

    THIS SOFTWARE IS NOT COPYRIGHTED

    This source code is offered for use in the public domain.  You may use,
    modify or distribute it freely.

    This source code is distributed in the hope that it will be useful but
    WITHOUT ANY WARRANTY.  ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
    DISCLAIMED.  This includes but is not limited to warranties of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
 
 */
#include <net-snmp/system/generic.h>

#ifdef HAVE_STDINT_H
#include <stdint.h>	/* uint32_t */
#endif

#undef bsdlike
#undef MBSTAT_SYMBOL
#undef TOTAL_MEMORY_SYMBOL
#undef HAVE_GETOPT_H
#undef HAVE_SOCKET
#undef HAVE_SIGNAL

/* Define if you have the gettimeofday function.  */
/* Only when compiling Perl module                */
#ifdef MINGW_PERL
#define HAVE_GETTIMEOFDAY 1
#endif

/* Define if you have the gethostbyname function.  */
#define HAVE_GETHOSTBYNAME 1

/* Define if you have the gethostname function.  */
#define HAVE_GETHOSTNAME 1

/* Define if you have raise() instead of alarm() */
#define HAVE_RAISE 1

/* Define to 1 if you have the `execv' function. */
#undef HAVE_EXECV

/* Define to 1 if you have the `fork' function. */
#undef HAVE_FORK

/*
 * I'm sure there is a cleaner way to do this.
 * Probably should be in net_snmp_config.h and
 * set during config.
 */
#ifndef LOG_DAEMON
#define	LOG_DAEMON	(3<<3)	/* System daemons */
#endif

/* got socklen_t? */
#define HAVE_SOCKLEN_T 1

/* This was taken from the win32 config file - see licensing information above */
#define EADDRINUSE		WSAEADDRINUSE

/*
 * File io stuff. Odd that this is not defined by MinGW.
 * Maybe there is an M$ish way to do it.
 */
#define	F_SETFL		4
#define	O_NONBLOCK	0x4000  /* non blocking I/O (POSIX style) */

/*
 * I dunno why. It's just not there. Define struct timezone.
 * If other systems need this it could be moved to system.h
 * and the proper checking done at config time. Right now I have
 * just put it here to keep the MinGW out of the main tree as much
 * as possible.
 */
struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

