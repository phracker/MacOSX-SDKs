#ifndef NET_SNMP_TYPES_H
#define NET_SNMP_TYPES_H

    /**
     *  Definitions of data structures, used within the library API.
     */

#include <stdio.h>

#ifndef NET_SNMP_CONFIG_H
#error "Please include <net-snmp/net-snmp-config.h> before this file"
#endif

                        /*
                         * For 'timeval' 
                         */
#if TIME_WITH_SYS_TIME
# ifdef WIN32
#  include <sys/timeb.h>
# else
#  include <sys/time.h>
# endif
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <sys/types.h>
#ifdef HAVE_WINSOCK_H
#include <winsock.h>
#endif

#if HAVE_NETINET_IN_H
#include <netinet/in.h>		/* For definition of in_addr_t */
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_SUBID               /* temporary - duplicate definition protection */
#ifndef EIGHTBIT_SUBIDS
typedef u_long  oid;
#define MAX_SUBID   0xFFFFFFFF
#else
typedef u_char  oid;
#define MAX_SUBID   0xFF
#endif
#endif

#ifndef HAVE_SOCKLEN_T
typedef u_int socklen_t;
#endif

#ifndef HAVE_IN_ADDR_T
typedef u_int in_addr_t;
#endif

#ifndef HAVE_SSIZE_T
#if defined(__INT_MAX__) && __INT_MAX__ == 2147483647
typedef int ssize_t;
#else
typedef long ssize_t;
#endif
#endif

    /*
     * Try to ensure we have 32-bit (and hopefully 64-bit)
     *    integer types available.
     */

#ifndef HAVE_INT8_T
typedef signed char int8_t;
#endif /* !HAVE_INT8_T */

#ifndef HAVE_UINT8_T
#ifdef HAVE_U_INT8_T
typedef u_int8_t      uint8_t;
#else
typedef unsigned char uint8_t;
#endif
#endif /* !HAVE_UINT8_T */

#ifndef HAVE_INT16_T
#if   SIZEOF_INT == 2
#define INT16_T int
#elif SIZEOF_SHORT == 2
#define INT16_T short
#else
#define _INT16_IS_NOT_16BIT
#define INT16_T short
#endif
typedef INT16_T int16_t;
#endif /* !HAVE_INT16_T */

#ifndef HAVE_UINT16_T
#ifdef HAVE_U_INT16_T
typedef u_int16_t        uint16_t;
#else
#ifdef INT16_T
typedef unsigned INT16_T uint16_t;
#else
typedef unsigned short   uint16_t;
#endif
#endif
#endif /* !HAVE_UINT16_T */

#ifndef HAVE_INT32_T
#if   SIZEOF_INT == 4
#define INT32_T int 
#elif SIZEOF_LONG == 4
#define INT32_T long 
#elif SIZEOF_SHORT == 4
#define INT32_T short 
#else
#define _INT32_IS_NOT_32BIT
#define INT32_T int 
#endif
typedef INT32_T int32_t;
#endif /* !HAVE_INT32_T */

#ifndef HAVE_UINT32_T
#ifdef HAVE_U_INT32_T
typedef u_int32_t        uint32_t;
#else
#ifdef INT32_T
typedef unsigned INT32_T uint32_t;
#else
typedef unsigned int     uint32_t;
#endif
#endif
#endif /* !HAVE_UINT32_T */

#ifndef HAVE_INT64_T
#if SIZEOF_LONG == 8
#define INT64_T long 
#elif SIZEOF_LONG_LONG == 8
#define INT64_T long long
#elif   SIZEOF_INT == 8
#define INT64_T int 
#elif SIZEOF_LONG >= 8
#define INT64_T long 
#define _INT64_IS_NOT_64BIT
#endif
#ifdef INT64_T
typedef INT64_T int64_t;
#define HAVE_INT64_T 1
#endif
#endif /* !HAVE_INT64_T */

#ifndef HAVE_UINT64_T
#ifdef HAVE_U_INT64_T
typedef u_int64_t        uint64_t;
#elif defined(INT64_T)
typedef unsigned INT64_T uint64_t;
#endif
#define HAVE_UINT64_T 1
#endif

#ifndef HAVE_INTMAX_T
#ifdef SIZEOF_LONG_LONG
typedef long long intmax_t;
#define SIZEOF_INTMAX_T SIZEOF_LONG_LONG
#elif defined(HAVE_INT64_T) && !defined(_INT64_IS_NOT_64BIT)
typedef int64_t   intmax_t;
#define SIZEOF_INTMAX_T 8
#else
typedef long      intmax_t;
#define SIZEOF_INTMAX_T SIZEOF_LONG
#endif
#define HAVE_INTMAX_T 1
#endif

#ifndef HAVE_UINTMAX_T
#ifdef SIZEOF_LONG_LONG
typedef unsigned long long uintmax_t;
#elif defined(HAVE_UINT64_T) && !defined(_INT64_IS_NOT_64BIT)
typedef uint64_t           uintmax_t;
#else
typedef unsigned long      uintmax_t;
#endif
#define HAVE_UINTMAX_T 1
#endif

#ifndef HAVE_UINTPTR_T
#if SIZEOF_LONG == 8
/* likely 64bit machine with 64bit addressing? */
    typedef unsigned long uintptr_t;
#else
    typedef unsigned uintptr_t;
#endif
#endif

#ifndef HAVE_INTPTR_T
#if SIZEOF_LONG == 8
/* likely 64bit machine with 64bit addressing? */
    typedef long intptr_t;
#else
    typedef int intptr_t;
#endif
#endif
    
    /*
     *  For the initial release, this will just refer to the
     *  relevant UCD header files.
     *    In due course, the types and structures relevant to the
     *  Net-SNMP API will be identified, and defined here directly.
     *
     *  But for the time being, this header file is primarily a placeholder,
     *  to allow application writers to adopt the new header file names.
     */


#include <net-snmp/definitions.h>
#include <net-snmp/library/snmp_api.h>
/*
 * #include <net-snmp/library/libsnmp.h> 
 */

    typedef struct netsnmp_index_s {
       size_t      len;
       oid         *oids;
    } netsnmp_index;


    typedef struct netsnmp_void_array_s {
       size_t  size;
       void * *array;
    } netsnmp_void_array;

    /*
     * references to various types
     */
    typedef struct netsnmp_ref_void {
       void * val;
    } netsnmp_ref_void;

    typedef union {
        u_long  ul;
        u_int   ui;
        u_short us;
        u_char  uc;
        long    sl;
        int     si;
        short   ss;
        char    sc;
        char *  cp;
        void *  vp;
    } netsnmp_cvalue;

#if 0
    typedef struct netsnmp_ref_u_char {
       u_char * val;
    } netsnmp_ref_U_char;

    typedef struct netsnmp_ref_char {
       char * val;
    } netsnmp_ref_void;

    typedef struct netsnmp_ref_int_s {
       int val;
    } netsnmp_ref_int;

    typedef struct netsnmp_ref_u_int_s {
       u_int val;
    } netsnmp_ref_int;

    typedef struct netsnmp_ref_u_long_s {
       u_long val;
    } netsnmp_ref_u_long;
#endif

    typedef struct netsnmp_ref_size_t_s {
       size_t val;
    } * netsnmp_ref_size_t;

#ifdef __cplusplus
}
#endif

#endif                          /* NET_SNMP_TYPES_H */
