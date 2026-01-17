/*
	 File:	   CFNetwork/CFNetworkDefs.h
 
	 Contains:   CoreFoundation Network header
 
	 Copyright:  Copyright (c) 2001-2008, Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/

#ifndef __CFNETWORK_DEFS_H_
#define __CFNETWORK_DEFS_H_




/* Required to build on platforms that do not have MacTypes.h */
#if !defined(__MACH__)
	// To pick-up the CALLBACK_API_C definition.
	#include <ConditionalMacros.h>
#endif /* __MACH__ */

/* Standard incantation for exporting/importing DLL symbols */
#if defined(__WIN32__)
  #if defined(CFNETWORK_BUILDING_DLL)
		#define CFN_EXPORT __declspec(dllexport) extern
 #else
	  #define CFN_EXPORT __declspec(dllimport) extern
 #endif
#else
	#define CFN_EXPORT extern
#endif


#endif //__CFNETWORK_DEFS_H_


