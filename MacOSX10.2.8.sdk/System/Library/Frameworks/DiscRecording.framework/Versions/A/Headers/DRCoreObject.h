/*
     File:       DiscRecording/DRCoreObject.h
 
     Contains:   Core object functionality for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*!
	@header DRCoreObject
	
	DRCoreObject defines a couple of base types for DiscRecording Core object refs. 
	These types are intended for use in polymorphic functions and as 
	general-purpose type identifiers.

	DRCoreObject defines a generic DiscRecording object-reference type,
	<tt>DRTypeRef</tt>. This generic reference serves as a placeholder 
	type for parameters and returned values of polymorphic functions, 
	which can take references to any DiscRecording object.
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
	@abstract	An untyped "generic" reference to any DiscRecording object
	@discussion The DRTypeRef type is one of the base types defined in DiscRecording. 
				It is used as the type and return value in several "polymorphic" functions defined 
				in DiscRecording. It is a generic object reference that acts as a placeholder for 
				references to true DiscRecording objects.

*/
typedef CFTypeRef	DRTypeRef;

/*!
	@typedef	DRRefConRetainCallback
	@abstract	The callback used by a DiscRecording object when it needs to obtain 
				ownership of the refCon.
	@discussion If you name your function <tt>MyCallback</tt>, you would declare it like this:
	
				<pre>
					void MyCallback(void *refCon);
				</pre>
*/
typedef const void* (*DRRefConRetainCallback)(const void *refCon);

/*!
	@typedef	DRRefConReleaseCallback
	@abstract	The callback used by a DiscRecording object when it needs to relinquish 
				ownership of the refCon.
	@discussion If you name your function <tt>MyCallback</tt>, you would declare it like this:
	
				<pre>
					void MyCallback(void *refCon);
				</pre>
*/
typedef void		(*DRRefConReleaseCallback)(const void *refCon);

/*!
	@struct		DRRefConCallbacks
	@field		version	The version of this structure.
	@field		retain	The callback used to add a retain for the DiscRecording object on 
						its refCon. This callback returns the value to store as 
						the refCon, which is usually the refCon parameter passed to this 
						callback, but may be a different value if a different value should 
						be stored as the refCon.
	@field		release The callback used to remove a retain previously added
						for the DiscRecording object from its refCon.
*/
struct DRRefConCallbacks {
    unsigned long version; 
    DRRefConRetainCallback retain; 
    DRRefConReleaseCallback release; 
};

typedef struct DRRefConCallbacks	DRRefConCallbacks;


/*!
	@constant kDRRefConCFTypeCallbacks
	Predefined DRRefConCallbacks structure containing a set of callbacks
	appropriate for use when the refCon is a CFType.
*/
extern
const DRRefConCallbacks kDRRefConCFTypeCallbacks;

/*!
	@function	DRSetRefCon
	@abstract	Sets the refCon for the DiscRecording object
	@param		ref		A generic reference of type DRTypeRef. Pass a reference to any 
						DiscRecording object whose refCon you want to set.
	@param		refCon	The refCon value to be stored by the DiscRecording object. If
						the refCon of the DiscRecording object is not NULL at the time 
						a new value is set, the previous refCon value will be released,
						using the release callback previously set (if any). The new 
						refCon value will be retained by the DiscRecording object using the
						retain callback previously set (if any). A value of NULL may be
						passed in, which indicates to the DiscRecording object that no
						refCon should be stored.
	@param		callbacks	A pointer to a DRRefConCallbacks structure initialized with the 
							callbacks for the object reference to use on its refCon.
							A copy of the contents of the Callbacks structure is made, so that 
							a pointer to a structure on the stack can be passed in, or can be 
							reused for multiple object references. If the version field of this
							callbacks structure is not one of the defined ones the behavior is 
							undefined. The retain field may be NULL, in which case the 
							DiscRecording object will do nothing to add a retain to its refCon 
							when it is set. The release field may be NULL, in which case the 
							DiscRecording object will do nothing to remove the objects's retain 
							(if any) on the refCon when the object is destroyed a new refCon
							value is set. This callbacks parameter itself may be NULL, which is 
							treated as if a valid structure of version 0 with all fields NULL 
							had been passed in. Otherwise, if any of the fields are not valid 
							pointers to functions of the correct type, or this parameter is not a
							valid pointer to a DRRefConCallbacks Callbacks structure, the behavior 
							is undefined.
*/
extern
void DRSetRefCon(DRTypeRef ref, void* refCon, const DRRefConCallbacks* callbacks)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRGetRefCon
	@abstract	Returns the DiscRecording object's refCon value.
	@param		ref		A generic reference of type DRTypeRef. Pass a reference to any 
						DiscRecording object whose refCon you want to set.
	@result		The value currently stored in the DiscRecording object refCon.
*/
extern
void* DRGetRefCon(DRTypeRef ref)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif	/* _H_DRCoreObject */
