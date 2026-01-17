/*
 *  CTDefines.h
 *  CoreText
 *
 *  Copyright (c) 2010-2012 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTDEFINES__
#define __CTDEFINES__

#ifndef __has_feature
# define __has_feature(x) 0
#endif

#ifndef __has_attribute
# define __has_attribute(x) 0
#endif

#ifndef __has_extension
# define __has_extension __has_feature
#endif

#if !defined(__CT_DEPRECATED_ENUMERATOR)
# if __has_attribute(deprecated) && __has_extension(enumerator_attributes)
#  define __CT_DEPRECATED_ENUMERATOR __attribute__((deprecated))
# else
#  define __CT_DEPRECATED_ENUMERATOR
# endif
#endif

#if defined(CT_BUILDING_CoreText)
# define CT_AVAILABLE_STARTING(_mac,_iphone)
# define CT_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)
# define CT_DEPRECATED_ENUMERATOR
#else /* defined(CT_BUILDING_CoreText) */
# include <Availability.h>
# define CT_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
# define CT_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
# define CT_DEPRECATED_ENUMERATOR __CT_DEPRECATED_ENUMERATOR
#endif /* defined(CT_BUILDING_CoreText) */

#endif
