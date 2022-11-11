#ifndef _NPY_ENDIAN_H_
#define _NPY_ENDIAN_H_

/*
 * NPY_BYTE_ORDER is set to the same value as BYTE_ORDER set by glibc in
 * endian.h
 */

#ifdef NPY_HAVE_ENDIAN_H
    /* Use endian.h if available */
    #include <endian.h>

    #define NPY_BYTE_ORDER __BYTE_ORDER
    #define NPY_LITTLE_ENDIAN __LITTLE_ENDIAN
    #define NPY_BIG_ENDIAN __BIG_ENDIAN
#else
    /* Set endianness info using target CPU */
    #include "npy_cpu.h"

    #define NPY_LITTLE_ENDIAN 1234
    #define NPY_BIG_ENDIAN 4321

    #if defined(NPY_CPU_X86)            \
            || defined(NPY_CPU_AMD64)   \
            || defined(NPY_CPU_IA64)    \
            || defined(NPY_CPU_ALPHA)   \
            || defined(NPY_CPU_ARMEL)   \
            || defined(NPY_CPU_AARCH64) \
            || defined(NPY_CPU_SH_LE)   \
            || defined(NPY_CPU_MIPSEL)
        #define NPY_BYTE_ORDER NPY_LITTLE_ENDIAN
    #elif defined(NPY_CPU_PPC)          \
            || defined(NPY_CPU_SPARC)   \
            || defined(NPY_CPU_S390)    \
            || defined(NPY_CPU_HPPA)    \
            || defined(NPY_CPU_PPC64)   \
            || defined(NPY_CPU_ARMEB)   \
            || defined(NPY_CPU_SH_BE)   \
            || defined(NPY_CPU_MIPSEB)  \
            || defined(NPY_CPU_M68K)
        #define NPY_BYTE_ORDER NPY_BIG_ENDIAN
    #else
        #error Unknown CPU: can not set endianness
    #endif
#endif

#endif
