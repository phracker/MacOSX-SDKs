/*
     File:       DiscRecordingEngine/DRCoreObject.h
 
     Contains:   Core object functionality for Disc Recording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Base types for Disc Recording Core object references. 

	@discussion		These types are for use in polymorphic functions and as general-purpose type identifiers.
*/

#ifndef _H_DRCoreObject
#define _H_DRCoreObject

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@typedef	DRTypeRef
	@abstract	An untyped, generic reference to any Disc Recording object.
	@discussion @link DRTypeRef DRTypeRef @/link is one of the base types defined in Disc Recording, used as a 
				placeholder for parameter and return type in several polymorphic functions. 
				It is a generic object reference that can take a reference to any other 
				Disc Recording object.

*/
typedef CFTypeRef	DRTypeRef;

/*!
	@typedef	DRRefConRetainCallback
	@abstract	A callback used by a Disc Recording object to obtain 
				ownership of its <tt>refCon</tt> (reference context) data.
	@discussion If you name your function <tt>MyDRRefConRetainCallback</tt>, you would 
				declare it like this:
	
				<pre>
					void MyDRRefConRetainCallback (void *refCon);
				</pre>
				
				This callback returns the value to store as the reference context for 
				a Disc Recording object, typically the <tt>refCon</tt> parameter  
				passed to the callback -- but your callback may return any value
				as the reference context.
*/
typedef const void* (*DRRefConRetainCallback)(const void *refCon);

/*!
	@typedef	DRRefConReleaseCallback
	@abstract	A callback used by a Disc Recording object to relinquish 
				ownership of its <tt>refCon</tt> (reference context) data.
	@discussion If you name your function <tt>MyDRRefConReleaseCallback</tt>, you would 
				declare it like this:
	
				<pre>
					void MyDRRefConReleaseCallback (void *refCon);
				</pre>
*/
typedef void		(*DRRefConReleaseCallback)(const void *refCon);

/*!
	@struct		DRRefConCallbacks
	@abstract	Contains a set of callbacks for use by a Disc Recording object in managing its
				reference context.
	@field		version	The version of this structure. The value must be a known version, or zero.
	@field		retain	An optional callback used by a Disc Recording object to retain its reference 
						context. When <tt>NULL</tt>, the Disc Recording object will not retain the  
						reference context when set.
	@field		release An optional callback used by a Disc Recording object to remove a retain 
						previously added for its reference context. When <tt>NULL</tt>, the Disc
						Recording objecting will not release its reference context when the 
						object is destroyed or when a new reference context value is set.
*/
struct DRRefConCallbacks {
    unsigned long version; 
    DRRefConRetainCallback retain; 
    DRRefConReleaseCallback release; 
};

typedef struct DRRefConCallbacks	DRRefConCallbacks;


/*!
	@constant kDRRefConCFTypeCallbacks
	@abstract	A predefined @link DRRefConCallbacks DRRefConCallbacks @/link structure containing a set of callbacks
				appropriate for use when the reference context is a <tt>CFType</tt> object.
*/
extern
const DRRefConCallbacks kDRRefConCFTypeCallbacks;

/*!
	@function	DRSetRefCon
	@abstract	Sets the Disc Recording object's reference context value.
	@param		ref		A generic reference to any Disc Recording object whose reference context you 
						want to set.
	@param		refCon	The reference context value to set for the Disc Recording object. If
						the the Disc Recording object's reference context is not <tt>NULL</tt> when 
						a new value is set, the previous <tt>refCon</tt> value will be released
						using the release callback previously set, if any. The new 
						<tt>refCon</tt> value will be retained by the Disc Recording object using the
						retain callback previously set, if any.
						
						You may pass a value of <tt>NULL</tt>, which results in the Disc Recording 
						object having no value in its reference context.
	@param		callbacks	A pointer to a @link DRRefConCallbacks DRRefConCallbacks @/link structure initialized with the 
							callbacks for the Disc Recording object to use on its reference context.
							A copy of the contents of the callbacks structure is made, so that 
							a pointer to a structure on the stack can be passed in, or can be 
							reused for multiple object references.
							
							If  the structure's version field does not contain a known value, this 
							function's behavior is undefined. The <tt>retain</tt> field may be <tt>NULL</tt>,  
							in which case the Disc Recording object will not retain the reference 
							context when set. The <tt>release</tt> field may also be <tt>NULL</tt>, in which  
							case the Disc Recording object will not release its reference context 
							when the object is destroyed or when a new reference context value is set.
							
							If this parameter itself is <tt>NULL</tt>, this function behaves as if a 
							valid structure of version 0 and with all fields <tt>NULL</tt> 
							had been passed in.
							
							If any of the callback structure's fields are not valid pointers to functions 
							of the correct type, or if this parameter is not a valid pointer to a 
							@link DRRefConCallbacks DRRefConCallbacks @/link callbacks structure, this function's behavior 
							is undefined.
*/
extern
void DRSetRefCon(DRTypeRef ref, void* refCon, const DRRefConCallbacks* callbacks)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRGetRefCon
	@abstract	Gets the Disc Recording object's reference context value.
	@param		ref		A generic reference to any Disc Recording object whose <tt>refCon</tt> value
						you want to get.
	@result		The value currently stored in the Disc Recording object's reference context.
*/
extern
void* DRGetRefCon(DRTypeRef ref)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif	/* _H_DRCoreObject */
