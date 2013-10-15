#ifndef _JAVASOFT_MACOSX_TYPES_MD_H_
#define _JAVASOFT_MACOSX_TYPES_MD_H_

#include <sys/types.h>
#include <sys/stat.h>

// This has all of the typedefs we need on Mac OS X.
#include <stdint.h>

// long long macros don't appear to be used anywhere, so leave them out.
// VARGS macro doesn't appear to be used anywhere, so leave it out.

#if defined(__ppc__)
  #ifndef HAVE_ALIGNED_DOUBLES
    #define HAVE_ALIGNED_DOUBLES
  #endif
  #ifndef HAVE_ALIGNED_LONGLONGS
    #define HAVE_ALIGNED_LONGLONGS
  #endif
#endif

#if defined(__i386__)
  // x86 doesn't require aligned doubles
#endif

/* printf format modifier for 64-bit int */
#define FORMAT64_MODIFIER "ll"

#endif /* !_JAVASOFT_MACOSX_TYPES_MD_H_ */
