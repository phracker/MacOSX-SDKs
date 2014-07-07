/*
     File:       PMPluginHeader.h
 
     Contains:   Mac OS X Printing Manager Plugin Header Defintions.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __PMPLUGINHEADER__
#define __PMPLUGINHEADER__

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
	#include <CoreFoundation/CFPlugInCOM.h>
#endif /* COREFOUNDATION_CFPLUGINCOM_SEPARATE */

#ifdef __cplusplus
extern "C" {
#endif

/* API Version is used for plugin object API compatibility check. */
struct PMPlugInAPIVersion {
   	/* API build version. */
  	/* This is the API version this object was compiled with. */
    UInt32                          buildVersionMajor;
    UInt32                          buildVersionMinor;

	/* Base API version this object is upward compatible with. */
	/* The object guarantees to be a super-set of said API. */
    UInt32                          baseVersionMajor;
    UInt32                          baseVersionMinor;

};
typedef struct PMPlugInAPIVersion       PMPlugInAPIVersion;

/* The plugin header interface, and its vtable. */
/* Plugin interface is an address of an object which contains a vtable pointer */
/* as its first member. Every plugin interface (except 'iunknown') must begin */
/* with PMPlugInHeader which must not change. */

typedef struct PMPlugInHeader                   PMPlugInHeader;
typedef struct PMPlugInHeaderInterface          PMPlugInHeaderInterface;

struct PMPlugInHeaderInterface
{
    const PMPlugInHeader* vtable;
};

struct PMPlugInHeader
{
    /* ---- API 'IMMUTABLE' Begin: ---- */

    /* Retain an object. */
    CALLBACK_API_C( OSStatus, Retain )( \
        PMPlugInHeaderInterface*        obj );

    /* Release an object. When reference count goes down to zero object
     * is deleted. The call clears caller's reference to the object. */
    CALLBACK_API_C( OSStatus, Release )( \
        PMPlugInHeaderInterface**       objPtr );

    /* GetAPIVersion method is required with all plugin modules
     * to be able to get object's API build and compatibility version.
     * This version is used for plugin API compatibility check. */
    CALLBACK_API_C( OSStatus, GetAPIVersion )( \
        PMPlugInHeaderInterface*        obj,
        PMPlugInAPIVersion*         versionPtr );
};

#ifdef __cplusplus
}
#endif

#endif /* __PMPLUGINHEADER__ */

