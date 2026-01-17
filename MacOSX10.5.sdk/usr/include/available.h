/*
     File:       available.h
 
     Copyright:  (c) 2001-2005 by Apple Computer, Inc., all rights reserved.

     More Info:  See TechNote 2064

     Contains:   Double-underbar-prefixed availability macros, derived from
                 AvailabilityMacros.h

                 This header enables a developer to specify build time
                 constraints on what Mac OS X versions the resulting
                 application will be run.  There are two bounds a developer
                 can specify:
                 
                      __MAC_OS_X_VERSION_MIN_REQUIRED
                      __MAC_OS_X_VERSION_MAX_ALLOWED
                      
                The lower bound controls which calls to OS functions will 
                be weak-importing (allowed to be unresolved at launch time).
                The upper bound controls which OS functionality, if used,
                will result in a compiler error because that functionality is
                not available on on any OS is the specifed range.
                
                For example, suppose an application is compiled with:
                
                      __MAC_OS_X_VERSION_MIN_REQUIRED = __MAC_OS_X_VERSION_10_2
                      __MAC_OS_X_VERSION_MAX_ALLOWED  = __MAC_OS_X_VERSION_10_3
                     
                and an OS header contains:
                
                     extern void funcA(void) __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
                     extern void funcB(void) __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2;
                     extern void funcC(void) __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;
                     extern void funcD(void) __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;
                     extern void funcE(void) __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
                     extern void funcF(void) __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
                     extern void funcG(void) __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
                     
                     typedef long TypeA __DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER;
                     typedef long TypeB __DEPRECATED_IN_MAC_OS_X_VERSION_10_1_AND_LATER;
                     typedef long TypeC __DEPRECATED_IN_MAC_OS_X_VERSION_10_2_AND_LATER;
                     typedef long TypeD __DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;
                     typedef long TypeE __DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

                Any application code which uses these declarations will get the following:
                
                                compile         link          run 
                                -------         ------        -------
                     funcA:     normal          normal        normal
                     funcB:     warning         normal        normal
                     funcC:     normal          normal        normal
                     funcD:     normal          normal        normal
                     funcE:     normal          normal        normal
                     funcF:     normal          weak          on 10.3 normal, on 10.2 (&funcF == NULL)
                     funcG:     error           error         n/a
                     typeA:     warning
                     typeB:     warning
                     typeC:     warning
                     typeD:     normal
                     typeE:     normal
                  
  
*/
#ifndef _AVAILABLE_H_
#define _AVAILABLE_H_


/*
 * Set up standard Mac OS X versions
 */
#define __MAC_OS_X_VERSION_10_0 1000
#define __MAC_OS_X_VERSION_10_1 1010
#define __MAC_OS_X_VERSION_10_2 1020
#define __MAC_OS_X_VERSION_10_3 1030
#define __MAC_OS_X_VERSION_10_4 1040
#define __MAC_OS_X_VERSION_10_5 1050


/* 
 * If min OS not specified, assume 10.1
 * Note: gcc driver may set _ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED_ based on MACOSX_DEPLOYMENT_TARGET environment variable
 */
#ifndef __MAC_OS_X_VERSION_MIN_REQUIRED
    #ifdef __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
        #define __MAC_OS_X_VERSION_MIN_REQUIRED __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
    #else
        #if __ppc64__ || __i386__ || __x86_64__
            #define __MAC_OS_X_VERSION_MIN_REQUIRED __MAC_OS_X_VERSION_10_4
        #else
            #define __MAC_OS_X_VERSION_MIN_REQUIRED __MAC_OS_X_VERSION_10_1
        #endif
    #endif
#endif

/*
 * if max OS not specified, assume largerof(10.5, min)
 */
#ifndef __MAC_OS_X_VERSION_MAX_ALLOWED
    #if __MAC_OS_X_VERSION_MIN_REQUIRED > __MAC_OS_X_VERSION_10_5
        #define __MAC_OS_X_VERSION_MAX_ALLOWED __MAC_OS_X_VERSION_MIN_REQUIRED
    #else
        #define __MAC_OS_X_VERSION_MAX_ALLOWED __MAC_OS_X_VERSION_10_5
    #endif
#endif

/*
 * Error on bad values
 */
#if __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_OS_X_VERSION_MIN_REQUIRED
    #error __MAC_OS_X_VERSION_MAX_ALLOWED must be >= __MAC_OS_X_VERSION_MIN_REQUIRED
#endif
#if __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_OS_X_VERSION_10_0
    #error __MAC_OS_X_VERSION_MIN_REQUIRED must be >= __MAC_OS_X_VERSION_10_0
#endif

/*
 * only certain compilers support __attribute__((weak_import))
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))) && (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1020)
    #define __DARWIN_WEAK_IMPORT_ATTRIBUTE __attribute__((weak_import))
#elif defined(__MWERKS__) && (__MWERKS__ >= 0x3205) && (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1020)
    #define __DARWIN_WEAK_IMPORT_ATTRIBUTE __attribute__((weak_import))
#else
    #define __DARWIN_WEAK_IMPORT_ATTRIBUTE
#endif

/*
 * only certain compilers support __attribute__((deprecated))
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define __DARWIN_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#else
    #define __DARWIN_DEPRECATED_ATTRIBUTE
#endif

/*
 * only certain compilers support __attribute__((unavailable))
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define __DARWIN_UNAVAILABLE_ATTRIBUTE __attribute__((unavailable))
#else
    #define __DARWIN_UNAVAILABLE_ATTRIBUTE
#endif



/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
 * 
 * Used on functions introduced in Mac OS X 10.0 
 */
#define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED
 * 
 * Used on functions introduced in Mac OS X 10.0, 
 * and deprecated in Mac OS X 10.0
 */
#define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED    __DARWIN_DEPRECATED_ATTRIBUTE

/*
 * __DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER
 * 
 * Used on types deprecated in Mac OS X 10.0 
 */
#define __DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER     __DARWIN_DEPRECATED_ATTRIBUTE






/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
 * 
 * Used on declarations introduced in Mac OS X 10.1 
 */
#if __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_OS_X_VERSION_10_1
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER     __DARWIN_UNAVAILABLE_ATTRIBUTE
#elif __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_OS_X_VERSION_10_1
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER     __DARWIN_WEAK_IMPORT_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED
 * 
 * Used on declarations introduced in Mac OS X 10.1, 
 * and deprecated in Mac OS X 10.1
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_1
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED    __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_1
 * 
 * Used on declarations introduced in Mac OS X 10.0, 
 * but later deprecated in Mac OS X 10.1
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_1
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_1    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_1    __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif

/*
 * __DEPRECATED_IN_MAC_OS_X_VERSION_10_1_AND_LATER
 * 
 * Used on types deprecated in Mac OS X 10.1 
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_1
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_1_AND_LATER    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_1_AND_LATER
#endif







/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
 * 
 * Used on declarations introduced in Mac OS X 10.2 
 */
#if __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_OS_X_VERSION_10_2
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER     __DARWIN_UNAVAILABLE_ATTRIBUTE
#elif __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_OS_X_VERSION_10_2
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER     __DARWIN_WEAK_IMPORT_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED
 * 
 * Used on declarations introduced in Mac OS X 10.2, 
 * and deprecated in Mac OS X 10.2
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_2
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED    __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2
 * 
 * Used on declarations introduced in Mac OS X 10.0, 
 * but later deprecated in Mac OS X 10.2
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_2
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2    __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2
 * 
 * Used on declarations introduced in Mac OS X 10.1, 
 * but later deprecated in Mac OS X 10.2
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_2
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2    __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif

/*
 * __DEPRECATED_IN_MAC_OS_X_VERSION_10_2_AND_LATER
 * 
 * Used on types deprecated in Mac OS X 10.2 
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_2
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_2_AND_LATER    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_2_AND_LATER
#endif





/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
 * 
 * Used on declarations introduced in Mac OS X 10.3 
 */
#if __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_OS_X_VERSION_10_3
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER     __DARWIN_UNAVAILABLE_ATTRIBUTE
#elif __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_OS_X_VERSION_10_3
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER     __DARWIN_WEAK_IMPORT_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED
 * 
 * Used on declarations introduced in Mac OS X 10.3, 
 * and deprecated in Mac OS X 10.3
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_3
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED    __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3
 * 
 * Used on declarations introduced in Mac OS X 10.0, 
 * but later deprecated in Mac OS X 10.3
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_3
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3    __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3
 * 
 * Used on declarations introduced in Mac OS X 10.1, 
 * but later deprecated in Mac OS X 10.3
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_3
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3    __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3
 * 
 * Used on declarations introduced in Mac OS X 10.2, 
 * but later deprecated in Mac OS X 10.3
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_3
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3    __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif

/*
 * __DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER
 * 
 * Used on types deprecated in Mac OS X 10.3 
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_3
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER
#endif






/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
 * 
 * Used on declarations introduced in Mac OS X 10.4 
 */
#if __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER     __DARWIN_UNAVAILABLE_ATTRIBUTE
#elif __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER     __DARWIN_WEAK_IMPORT_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED
 * 
 * Used on declarations introduced in Mac OS X 10.4, 
 * and deprecated in Mac OS X 10.4
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED    __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4
 * 
 * Used on declarations introduced in Mac OS X 10.0, 
 * but later deprecated in Mac OS X 10.4
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4
 * 
 * Used on declarations introduced in Mac OS X 10.1, 
 * but later deprecated in Mac OS X 10.4
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4
 * 
 * Used on declarations introduced in Mac OS X 10.2, 
 * but later deprecated in Mac OS X 10.4
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4
 * 
 * Used on declarations introduced in Mac OS X 10.3, 
 * but later deprecated in Mac OS X 10.4
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_4
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4    __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#endif

/*
 * __DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER
 * 
 * Used on types deprecated in Mac OS X 10.4 
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_4
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER
#endif





/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
 * 
 * Used on declarations introduced in Mac OS X 10.5 
 */
#if __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER     __DARWIN_UNAVAILABLE_ATTRIBUTE
#elif __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER     __DARWIN_WEAK_IMPORT_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED
 * 
 * Used on declarations introduced in Mac OS X 10.5, 
 * and deprecated in Mac OS X 10.5
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED    __AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
 * 
 * Used on declarations introduced in Mac OS X 10.0, 
 * but later deprecated in Mac OS X 10.5
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
 * 
 * Used on declarations introduced in Mac OS X 10.1, 
 * but later deprecated in Mac OS X 10.5
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
 * 
 * Used on declarations introduced in Mac OS X 10.2, 
 * but later deprecated in Mac OS X 10.5
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
 * 
 * Used on declarations introduced in Mac OS X 10.3, 
 * but later deprecated in Mac OS X 10.5
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#endif

/*
 * __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
 * 
 * Used on declarations introduced in Mac OS X 10.4, 
 * but later deprecated in Mac OS X 10.5
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5    __AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#endif

/*
 * __DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER
 * 
 * Used on types deprecated in Mac OS X 10.5 
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_OS_X_VERSION_10_5
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER    __DARWIN_DEPRECATED_ATTRIBUTE
#else
    #define __DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER
#endif

#endif  /* _AVAILABLE_H_ */


