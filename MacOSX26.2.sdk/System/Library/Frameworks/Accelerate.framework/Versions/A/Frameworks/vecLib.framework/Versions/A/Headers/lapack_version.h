
#pragma once

#define __LAPACK_SUFFIX_NEW_LAPACK "$NEWLAPACK"

#if defined(__arm64__) || defined(__x86_64__)
#define __LAPACK_SUFFIX_ILP64 "$ILP64"
#else
#define __LAPACK_SUFFIX_ILP64
#endif // #if defined(__arm64__) || defined(__x86_64__)

#if defined( ACCELERATE_LAPACK_ILP64 )

#define __LAPACK_ALIAS(sym) __asm("_" __STRING(sym) __LAPACK_SUFFIX_NEW_LAPACK __LAPACK_SUFFIX_ILP64)

#else

#define __LAPACK_ALIAS(sym) __asm("_" __STRING(sym) __LAPACK_SUFFIX_NEW_LAPACK)

#endif // #if defined( ACCELERATE_LAPACK_ILP64 )
