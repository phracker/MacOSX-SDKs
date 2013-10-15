#ifndef SNMP_SYSTEM_H
#define SNMP_SYSTEM_H

#ifndef NET_SNMP_CONFIG_H
#error "Please include <net-snmp/net-snmp-config.h> before this file"
#endif

#ifdef __cplusplus
extern          "C" {
#endif

/* Portions of this file are subject to the following copyrights.  See
 * the Net-SNMP's COPYING file for more details and other copyrights
 * that may apply:
 */
/***********************************************************
        Copyright 1993 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of CMU not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

CMU DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
CMU BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************/
/*
 * portions Copyright © 2003 Sun Microsystems, Inc. All rights reserved.
 * Use is subject to license terms specified in the COPYING file
 * distributed with the Net-SNMP package.
 */


    /*
     * function to create a daemon. Will fork and call setsid().
     *
     * Returns: -1 : fork failed
     *           0 : No errors
     */
    int netsnmp_daemonize(int quit_immediately, int stderr_log);

    /*
     * Definitions for the system dependent library file
     */
#ifndef MSVC_PERL
#ifdef WIN32

#ifndef HAVE_DIRENT_H /* MingGW has dirent.h but also defines WIN32 */
    /*
     * structure of a directory entry 
     */
    typedef struct direct {
        long            d_ino;  /* inode number (not used by MS-DOS) */
        int             d_namlen;       /* Name length */
        char            d_name[257];    /* file name */
    } _DIRECT;

    /*
     * structure for dir operations 
     */
    typedef struct _dir_struc {
        char           *start;  /* Starting position */
        char           *curr;   /* Current position */
        long            size;   /* Size of string table */
        long            nfiles; /* number if filenames in table */
        struct direct   dirstr; /* Directory structure to return */
    } DIR;

    DIR            *opendir(const char *filename);
    struct direct  *readdir(DIR * dirp);
    int             closedir(DIR * dirp);
#endif /* HAVE_DIRENT_H */

#ifndef HAVE_GETTIMEOFDAY
    int             gettimeofday(struct timeval *, struct timezone *tz);
#endif
#ifndef HAVE_STRCASECMP
    int             strcasecmp(const char *s1, const char *s2);
#endif
#ifndef HAVE_STRNCASECMP
    int             strncasecmp(const char *s1, const char *s2, size_t n);
#endif

    char           *winsock_startup(void);
    void            winsock_cleanup(void);

#define SOCK_STARTUP winsock_startup()
#define SOCK_CLEANUP winsock_cleanup()

#else                           /* !WIN32 */

#define SOCK_STARTUP
#define SOCK_CLEANUP

#endif                          /* WIN32 */
#endif				/* MSVC_PERL */

#include <net-snmp/types.h>     /* For definition of in_addr_t */

    in_addr_t       get_myaddr(void);
    long            get_uptime(void);

#ifndef HAVE_STRDUP
    char           *strdup(const char *);
#endif
#ifndef HAVE_SETENV
    int             setenv(const char *, const char *, int);
#endif

    int             calculate_time_diff(struct timeval *,
                                        struct timeval *);
    u_int           calculate_sectime_diff(struct timeval *now,
                                           struct timeval *then);

#ifndef HAVE_STRCASESTR
    char           *strcasestr(const char *, const char *);
#endif
#ifndef HAVE_STRTOL
    long            strtol(const char *, char **, int);
#endif
#ifndef HAVE_STRTOUL
    unsigned long   strtoul(const char *, char **, int);
#endif
#ifndef HAVE_STRTOK_R
    char           *strtok_r(char *, const char *, char **);
#endif
#ifndef HAVE_SNPRINTF
    int             snprintf(char *, size_t, const char *, ...);
#endif

    int             mkdirhier(const char *pathname, mode_t mode,
                              int skiplast);
#ifndef HAVE_STRLCPY
    size_t            strlcpy(char *, const char *, size_t);
#endif

    int             netsnmp_os_prematch(const char *ospmname,
                                        const char *ospmrelprefix);

#ifdef __cplusplus
}
#endif
#endif                          /* SNMP_SYSTEM_H */
