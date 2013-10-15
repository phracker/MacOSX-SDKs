/*
 *  CTDefines.h
 *  CoreText
 *
 *  Copyright (c) 2010-2011 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTDEFINES__
#define __CTDEFINES__


#if defined(CT_BUILDING_CoreText)
# define CT_AVAILABLE_STARTING(_mac,_iphone)
# define CT_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)
#else /* defined(CT_BUILDING_CoreText) */
# include <Availability.h>
# define CT_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
# define CT_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
#endif /* defined(CT_BUILDING_CoreText) */

#endif // __CTDEFINES__
