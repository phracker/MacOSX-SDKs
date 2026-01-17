/**
 * @file tools.h
 * @defgroup util Memory Utility Routines
 * @ingroup library
 * @{
 */

#ifndef _TOOLS_H
#define _TOOLS_H

#ifdef __cplusplus
extern          "C" {
#endif



    /*
     * General acros and constants.
     */
#ifdef WIN32
#  define SNMP_MAXPATH MAX_PATH
#else
#  ifdef PATH_MAX
#    define SNMP_MAXPATH PATH_MAX
#  else
#    ifdef MAXPATHLEN
#      define SNMP_MAXPATH MAXPATHLEN
#    else
#      define SNMP_MAXPATH 1024		/* Should be safe enough */
#    endif
#  endif
#endif

#define SNMP_MAXBUF		(1024 * 4)
#define SNMP_MAXBUF_MEDIUM	1024
#define SNMP_MAXBUF_SMALL	512

#define SNMP_MAXBUF_MESSAGE	1500

#define SNMP_MAXOID		64
#define SNMP_MAX_CMDLINE_OIDS	128

#define SNMP_FILEMODE_CLOSED	0600
#define SNMP_FILEMODE_OPEN	0644

#define BYTESIZE(bitsize)       ((bitsize + 7) >> 3)
#define ROUNDUP8(x)		( ( (x+7) >> 3 ) * 8 )



/** @def SNMP_FREE(s)
    Frees a pointer only if it is !NULL and sets its value to NULL */
#define SNMP_FREE(s)    do { if (s) { free((void *)s); s=NULL; } } while(0)

/** @def SNMP_SWIPE_MEM(n, s)
    Frees pointer n only if it is !NULL, sets n to s and sets s to NULL */
#define SNMP_SWIPE_MEM(n,s) do { if (n) free((void *)n); n = s; s=NULL; } while(0)

    /*
     * XXX Not optimal everywhere. 
     */
/** @def SNMP_MALLOC_STRUCT(s)
    Mallocs memory of sizeof(struct s), zeros it and returns a pointer to it. */
#define SNMP_MALLOC_STRUCT(s)   (struct s *) calloc(1, sizeof(struct s))

/** @def SNMP_MALLOC_TYPEDEF(t)
    Mallocs memory of sizeof(t), zeros it and returns a pointer to it. */
#define SNMP_MALLOC_TYPEDEF(td)  (td *) calloc(1, sizeof(td))

/** @def SNMP_ZERO(s,l)
    Zeros l bytes of memory starting at s. */
#define SNMP_ZERO(s,l)	do { if (s) memset(s, 0, l); } while(0)


#define TOUPPER(c)	(c >= 'a' && c <= 'z' ? c - ('a' - 'A') : c)
#define TOLOWER(c)	(c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c)

#define HEX2VAL(s) \
	((isalpha(s) ? (TOLOWER(s)-'a'+10) : (TOLOWER(s)-'0')) & 0xf)
#define VAL2HEX(s)	( (s) + (((s) >= 10) ? ('a'-10) : '0') )


/** @def SNMP_MAX(a, b)
    Computers the maximum of a and b. */
#define SNMP_MAX(a,b) ((a) > (b) ? (a) : (b))

/** @def SNMP_MIN(a, b)
    Computers the minimum of a and b. */
#define SNMP_MIN(a,b) ((a) > (b) ? (b) : (a))

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  1
#endif

    /*
     * QUIT the FUNction:
     *      e       Error code variable
     *      l       Label to goto to cleanup and get out of the function.
     *
     * XXX  It would be nice if the label could be constructed by the
     *      preprocessor in context.  Limited to a single error return value.
     *      Temporary hack at best.
     */
#define QUITFUN(e, l)			\
	if ( (e) != SNMPERR_SUCCESS) {	\
		rval = SNMPERR_GENERR;	\
		goto l ;		\
	}

    /*
     * DIFFTIMEVAL
     *      Set <diff> to the difference between <now> (current) and <then> (past).
     *
     * ASSUMES that all inputs are (struct timeval)'s.
     * Cf. system.c:calculate_time_diff().
     */
#define DIFFTIMEVAL(now, then, diff) 			\
{							\
	now.tv_sec--;					\
	now.tv_usec += 1000000L;			\
	diff.tv_sec  = now.tv_sec  - then.tv_sec;	\
	diff.tv_usec = now.tv_usec - then.tv_usec;	\
	if (diff.tv_usec > 1000000L){			\
		diff.tv_usec -= 1000000L;		\
		diff.tv_sec++;				\
	}						\
}


    /*
     * ISTRANSFORM
     * ASSUMES the minimum length for ttype and toid.
     */
#define USM_LENGTH_OID_TRANSFORM	10

#define ISTRANSFORM(ttype, toid)					\
	!snmp_oid_compare(ttype, USM_LENGTH_OID_TRANSFORM,		\
		usm ## toid ## Protocol, USM_LENGTH_OID_TRANSFORM)

#define ENGINETIME_MAX	2147483647      /* ((2^31)-1) */
#define ENGINEBOOT_MAX	2147483647      /* ((2^31)-1) */




    /*
     * Prototypes.
     */

    int             snmp_realloc(u_char ** buf, size_t * buf_len);

    void            free_zero(void *buf, size_t size);

    u_char         *malloc_random(size_t * size);
    u_char         *malloc_zero(size_t size);
    int             memdup(u_char ** to, const u_char * from, size_t size);

    u_int           binary_to_hex(const u_char * input, size_t len,
                                  char **output);
                    /* preferred */
    int             netsnmp_hex_to_binary(u_char ** buf, size_t * buf_len,
                                         size_t * out_len, int allow_realloc,
                                         const char *hex, const char *delim);
                    /* calls netsnmp_hex_to_binary w/delim of " " */
    int             snmp_hex_to_binary(u_char ** buf, size_t * buf_len,
                                       size_t * out_len, int allow_realloc,
                                       const char *hex);
                    /* handles odd lengths */
    int             hex_to_binary2(const u_char * input, size_t len,
                                   char **output);

    int             snmp_decimal_to_binary(u_char ** buf, size_t * buf_len,
                                           size_t * out_len,
                                           int allow_realloc,
                                           const char *decimal);
    int             snmp_strcat(u_char ** buf, size_t * buf_len,
                                size_t * out_len, int allow_realloc,
                                const u_char * s);
    char           *netsnmp_strdup_and_null(const u_char * from,
                                            size_t from_len);

    void            dump_chunk(const char *debugtoken, const char *title,
                               const u_char * buf, int size);
    char           *dump_snmpEngineID(const u_char * buf, size_t * buflen);

    typedef void   *marker_t;
    marker_t        atime_newMarker(void);
    void            atime_setMarker(marker_t pm);
    long            atime_diff(marker_t first, marker_t second);
    u_long          uatime_diff(marker_t first, marker_t second);       /* 1/1000th sec */
    u_long          uatime_hdiff(marker_t first, marker_t second);      /* 1/100th sec */
    int             atime_ready(marker_t pm, int deltaT);
    int             uatime_ready(marker_t pm, unsigned int deltaT);

    int             marker_tticks(marker_t pm);
    int             timeval_tticks(struct timeval *tv);
    char            *netsnmp_getenv(const char *name);
    
#ifdef __cplusplus
}
#endif
#endif                          /* _TOOLS_H */
/* @} */
