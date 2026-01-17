/*
     File:       DiscRecording/DRContentObject.h
 
     Contains:   Base class for items used in filesystem creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*!
	@header DRContentObject
	
	This is the header file for the base filesystem object in DiscRecording's
	content-creation APIs.
	
	Content creation provides an interface for dynamic filesystem creation, allowing
	complex filesystem hierarchies to be created and burned on-the-fly without having
	to generate a complete on-disk representation.
	
	This class serves as a base class for both files and folders.
	
	Quick links:
	<ul>
	 <li><a href="#About the Objects">Real and Virtual Objects</a>
	 <li><a href="#Adding Children">Creating a Virtual Hierarchy</a>
	 <li><a href="#Real To Virtual">Converting From Real To Virtual</a>
	 <li><a href="#Base Names and Specific Names">Base Names and Specific Names</a>
	 <li><a href="#Properties and Other Meta-Data">Properties and Other Meta-Data</a>
	 <li><a href="#Filesystem Masks">Filesystem Masks</a>
	 <li><a href="#Symbolic Link Translation">Symbolic Link Translation</a>
	</ul>
	
	
	
	
	<h3><a name="About the Objects">Real and Virtual Objects</a></h3>
	The interface is designed around folder and file objects which are laid out
	in a one-parent-many-children hierarchy - this should be a familiar concept for
	anyone who's ever used a modern filesystem.  There are two kinds of objects in
	this API; "real" objects and "virtual" objects, and the distinction is important.
	<ul>
	<li>A <b>real</b> file or folder object corresponds directly to a file or folder
		on disk.  The data for a real file object comes directly from the on-disk file.
		The hierarchy underneath a real folder object corresponds 1:1 to the
		hierarchy underneath the folder in the on-disk filesystem.
	
	<li>A <b>virtual</b> file or folder object does not have any actual representation
		on disk.  The data for a virtual file object is specified through the API or
		in a callback function.  The hierarchy underneath a virtual folder object 
		is specified through the API.
	</ul>
	
	
	<h3><a name="Adding Children">Creating a Virtual Hierarchy</a></h3>
	In the hierarchy specified through this API, only virtual folders may be assigned
	children.  Real files, virtual files, and real folders are all considered leaf
	nodes and may not have children.  (Real folders can of course contain files and
	folders, but the files and folders are specified by the on-disk representation. 
	They cannot be changed through this API unless the real folder is made virtual first.)
	
	A hierarchy may be as simple as a single real folder, or it can be as complicated
	as needed - for example, a virtual folder with a deep hierarchy of children which are
	a complex mix of real files, virtual files, real folders, and virtual folders.
	
	
	<h3><a name="Real To Virtual">Converting From Real To Virtual</a></h3>
	A real folder can be dynamically converted to a virtual folder, with the
	<code>DRFolderConvertRealToVirtual</code> call.  When this happens, its first level of
	children is read and converted into a virtual hierarchy.  The children thus created will
	all be real.
	
	For example: A real folder is converted into a virtual folder.  The on-disk folder is named
	<i>root</i>, and contains a file named <i>file1</i> and a folder named <i>folder2</i>.
	After conversion, the result is a virtual folder named <i>root</i>, with two children: the
	real file <i>file1</i> and the real folder <i>folder2</i>.
	
	
	<h3><a name="Base Names and Specific Names">Base Names and Specific Names</a></h3>
	Because the content creation API is able to generate multiple filesystems which
	require multiple varied naming conventions, a sensible system for naming is required.
	Thus each file has a <b>base name</b> which corresponds to its default name in any filesystem. 
	Whenever possible, the base name will be used in the generated filesystem without
	modification.

	The initial base name for a real object is the name of the corresponding object
	on disk.  The initial base name for a virtual object is specified when the object
	is created.  The base names for both real and virtual objects may be modified using the
	<code>DRFSObjectSetBaseName</code> call.
	
	Inside a particular filesytem, if the base name cannot be used as-is (if, for example,
	it contains illegal characters, exceeds the length requirements, or otherwise doesn't
	meet the required format) then an acceptable name that meets the filesystem's criteria
	will be generated automatically from the base name.  The name which is acceptable to
	a given filesystem is that file's <b>specific name</b> for that filesystem.
	
	A specific name may be obtained and modified through this API, or may be left empty to
	be automatically generated from the base name.  When a specific name is set through the API,
	it will be modified to ensure that the name is legal according to the particular filesystem.
	
	Even when a specific name is set or generated through the API, it may not be the actual name
	used on the disc.  If an object's specific name conflicts with the specific name of another
	of the object's siblings in that filesystem, one or both specific names will be <b>mangled</b>
	to obtain a unique name before burning, usually by adding a numeric mangle code such as
	<code>_001</code> to each name.
	
	There are two APIs available for getting the specific name from an object:
	<ul>
	<li><code>DRFSObjectCopySpecificName</code> returns the unmodified specific name, which
	would be used if there were no conflicts.
	<li><code>DRFSObjectCopyMangledName</code> returns a modified specific name, mangled if
	necessary, which is guaranteed to be unique amongst its siblings in the filesystem.
	</ul>
	Both of these calls take a key indicating which filesystem to query.  The filesystem keys are
	listed in DRContentProperties.h.  Most of the keys are straightforward; however, ISO-9660
	is a special case, since there are two possible naming conventions for ISO-9660, level 1
	(8.3, limited charset) and level 2 (30 chars, marginally expanded charset).  You can't
	specify kDRISO9660 when obtaining a name; instead, you must explicitly specify whether
	you want the level 1 or level 2 name with kDRISO9660LevelOne or kDRISO9660LevelTwo.
	
	If the object's name does not conflict with any of its siblings, CopyMangledName will 
	return the same value as CopySpecificName.  The converse
	is not necessarily true -- in general, when more than one object attempts to use a
	particular name, one object will get the name unmodified, while the remaining objects
	will get mangled names.
	
	CopyMangledName will check each of the object's siblings in the hierarchy and mangle to
	resolve any filename conflicts, so it can be a much more expensive call than CopySpecificName,
	taking at worst O(N^2) time where N is the number of siblings.  However, actual performance
	tends to be much better, closer to O(N), particularly when there are no (or only a few)
	collisions.  For user display, CopyMangledName is recommended, since it has the advantage
	of allowing you to show the user the exact names which would be generated on the disc
	if the burn were started immediately.
	
	Both CopySpecificName and CopyMangledName will cache information when possible, so
	that names are only generated and mangled when necessary.  Thus, the first CopyMangledName
	call in a set of siblings can be expensive, because all the specific names of the siblings
	must be both generated and mangled.  However, a subsequent call to CopyMangledName on a
	different sibling will simply return the cached value which was indirectly generated by
	the previous call, in O(1) time. 
	
	Adding or removing children from a folder may cause the cached names of the folder's children
	to be invalidated.  Changing the base or specific name of an object may cause the cached
	names of the object's siblings to be invalidated.
	
	
	<h3><a name="Properties and Other Meta-Data">Properties and Other Meta-Data</a></h3>
	Properties are generally accessed similarly to names.  Each object has overall
	properties which apply to every filesystem, and it may also have different properties
	in each filesystem.  For example, a file which has no relevance for a MacOS user
	may be marked invisible in the HFS+ tree, but be visible in the Joliet tree.
	
	The properties, like names, are also differentiated by filesystem. There is one
	properties dictionary for kDRAllFilesystems, and one properties dictionary for each
	individual filesystem - kDRISO9660, kDRJoliet, kDRHFSPlus, etc.  
	
	The properties for kDRAllFilesystems are treated as the base value, and then the
	properties in the specific filesystem dictionary are treated as overrides.
	
	When obtaining properties with <code>DRFSObjectCopyProperty</code> or
	<code>DRFSObjectCopyProperties</code>, you can specify whether you want to
	automatically coalesce the properties between the specified dictionary and
	the "all filesystems" dictionary.  This is useful if you want to obtain the effective
	value of the property, because it will return the value from the "all filesystems"
	dictionary if the specific filesystem does not assign an override.
	
	
	<h3><a name="Filesystem Masks">Filesystem Masks</a></h3>
	It's possible to suppress generation of particular items in a folder tree.  For example,
	you may want a MacOS application file or bundle to only appear in the HFS+ tree, and
	want an .EXE file to only appear in the Joliet tree.
	
	Filesystem-specific suppression is handled through the <b>filesystem mask</b>.  The filesystem
	mask is a bitfield which contains a 1 if the object will appear in the corresponding filesystem,
	and 0 otherwise.  This can be used to generate arbitrarily complex trees, where in the most
	complex case each filesystem may theoretically have its own unique and disjoint tree.
	(Such discs are discouraged, however, since they may be confusing to the user.)
	
	An object can be considered to have two mask values.  The first one is the <b>explicit mask</b>
	which can be set by the client.  The other is the <b>effective mask</b>, which is the
	actual mask which will be used.
	
	When an object is created, its default explicit mask is kDRFilesystemMaskDefault, which
	has all bits set to 1. Prior to the burn, the following rules apply:
	
	<ul>
	<li>An object's effective mask is equal to the bitwise AND of the object's explicit mask
		and its parent's effective mask.
		
		(Therefore, an explicit mask of 0 implies an effective mask of 0, and an
		explicit mask of kDRFilesystemMaskDefault implies an effective mask
		that is equal to the parent's effective mask.)
		
	<li>An effective mask of 0 removes an object from all filesystems, so that it will
		not be included in the burn.
	</ul>
	
	Note: even though a bit may be set in the explicit mask, that does not necessarily
	mean that the object will appear in the corresponding filesystem.  The effective mask
	must always be considered.  An easy way to think about this is to realize that for an object to
	appear in a filesystem, its parent folder (and all ancestors, up to the root) must also
	be in the filesystem.
	
	When the burn is performed, DiscRecording performs a few additional steps in determining
	the actual filesystems that will be used.
	
	<ul>
	<li>If the root folder has an explicit mask of kDRFilesystemMaskDefault or zero,
		DiscRecording will assign a default explicit mask of its own choosing.
		
		The default explicit mask will typically be one which will result in the most compatible
		cross-platform disc possible.  This is not necessarily always going to be the same.
		It may be different for different types of media - for example, UDF/HFS+ for DVD, and
		ISO/Joliet/HFS+ for CD. It may also change in the future.
		
		If you need to know exactly which filesystems will be generated, you should always
		set a non-default explicit mask for the root folder.
		
	<li>If the root folder's mask requests a filesystem that requires another filesystem
		that is not in the mask, DiscRecording will resolve the conflict by enabling the
		required filesystem.
		
		For example, Joliet requires ISO-9660.  If the root folder's mask is
		kDRFilesystemMaskJoliet, DiscRecording will automatically enable
		kDRFilesystemMaskISO9660 as well.
	
	<li>If the root folder's mask requests a filesystem that is mutually exclusive with 
		another filesystem, DiscRecording will resolve the conflict by disabling one of
		the conflicting filesystems.
		
		Currently, none of the filesystems that can be generated are mutually exclusive.
		(To provide a hypothetical example:  If DiscRecording supported both HFS and HFS+
		in a mutually exclusive manner, and the root folder had a mask that enabled both,
		the burn engine would automatically disable HFS in favor of HFS+.)
	</ul>
	
	You do not have to set an explicit mask for anything but the root if you want all
	filesystems to have the same data.  Since DiscRecording will automatically assign
	a mask if none is provided, in most cases you do not even have to set an explicit
	mask for the root.
	
	
	<h3><a name="Symbolic Link Translation">Symbolic Link Translation</a></h3>
	During the burn, when a symbolic link is encountered in the on-disk filesystem corresponding
	to a real file or folder, the semantics of the link will be preserved as closely as possible.
	If the link contains an absolute path, it will be copied unmodified.  If the link contains a
	relative path, it will be modified to contain an appropriate path.  An important detail to
	recognize is that since naming requirements vary between filesystems, the appropriate
	path may be different for each filesystem.
	
	For example, a relative link to
	"my long, long directory/this: is an unusual$ filename.with_extension" 
	will be modified to contain something like the following.  Note that each component of
	the path has been modified to conform to the rules of the target filesystem.
	<ul>
	<li> ISO-9660 level 1: "MYLONGLO/THISISAN.WIT"
	<li> ISO-9660 level 2: "MY LONG LONG DIRECTORY/THIS: IS AN UNU.WITH_EXTENSION"
	<li> Joliet:           "my long, long directory/this: is an unusual filename.with_extension"
	<li> HFS+:             "my long, long directory/this: is an unusual$ filename.with_extension"
	</ul>
	The burn engine will make an effort to appropriately translate each component of the path.
	However, it's still possible that the symlink might break in complex cases.
	(For example, in the case of a relative-path symlink which traverses through an absolute-path
	symlink, or when there are filename conflicts along a symlink's path which the burn
	engine has to resolve by mangling.)
	
	The burn engine's symlink preservation is usually good enough for most situations in which
	symlinks are used.  And, when the source filesystem is the same as the target filesystem,
	symlinks will be preserved perfectly.  (For example, the HFS+ filesystem generated from
	an HFS+ source should never have symlink problems.)
	
	However, the odds of symlink failure go up when there are complex arrangements of symlinks,
	or when there are filename collisions which the burn engine resolves by mangling. 
	
	This is expected behavior.  The only way to create a perfect symlink which is guaranteed
	to have a correct path on <b>all</b> filesystems is to create a virtual symlink using
	<code>DRFileCreateVirtualLink</code>.  
	
*/
#ifndef _H_DRContentObject
#define _H_DRContentObject

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecording/DRCoreObject.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif



/*!
	@typedef DRFileRef
	This is the type of a reference to DRFile instances.
*/
typedef struct __DRFile*		DRFileRef;

/*!
	@typedef DRFolderRef
	This is the type of a reference to DRFolder instances.
*/
typedef struct __DRFolder*		DRFolderRef;

/*!
	@typedef DRFSObjectRef
	This is the polymorphic type used for both file and folder instances.
*/
typedef DRTypeRef DRFSObjectRef;





typedef UInt32 DRFilesystemMask;
enum {
	/*!	@constant	kDRFilesystemMaskISO9660
		@abstract	The mask indicating the ISO9660 filesystem.  */
	kDRFilesystemMaskISO9660			= (1<<0),
	
	/*!	@constant	kDRFilesystemMaskJoliet
		@abstract	The mask indicating the Joliet filesystem, an extension to ISO9660. */
	kDRFilesystemMaskJoliet				= (1<<1),
	
	/*! @constant	kDRFilesystemMaskHFSPlus
		@abstract	The mask indicating the HFS+ filesystem.	*/
	kDRFilesystemMaskHFSPlus			= (1<<3),
	
	/*!	@constant	kDRFilesystemMaskDefault
		@abstract	The default (unrestricted) mask for newly-created objects. */
	kDRFilesystemMaskDefault			= 0xFFFFFFFF
};




/*!	@function	DRFSObjectIsVirtual
	@abstract	Indicates whether a given object ref is real or virtual.
	@param		object					Object reference to query.
	@result		TRUE if the object is virtual, or FALSE otherwise.
*/
extern Boolean
DRFSObjectIsVirtual(
	const DRFSObjectRef			object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectGetRealFSRef
	@abstract	Given a real file or folder object, returns a reference to the on-disk
				file or folder.
	@param		object					Object reference to query.
	@param		fsRef					Will be filled with a valid FSRef on success.
*/
extern void
DRFSObjectGetRealFSRef(
	const DRFSObjectRef			object,
	FSRef *						fsRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopyRealURL
	@abstract	Given a real file or folder object, returns a reference to the on-disk
				file or folder.
	@param		object					Object reference to query.
	@result		A file URL to the on-disk file or folder, or NULL if not real.
*/
extern CFURLRef
DRFSObjectCopyRealURL(
	const DRFSObjectRef		objectRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectGetParent
	@abstract	Returns the parent object (if any) of a given object in a hierarchy.
	@param		object					The object reference to query.
	@result		The object's parent.
*/
extern DRFolderRef
DRFSObjectGetParent(
	const DRFSObjectRef			object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopyBaseName
	@abstract	Returns the base name for the object (either a file or folder).
	@discussion	The base name is the name from which any necessary filesystem-specific
				names are automatically generated.  
				
				Because the content creation API is able to generate multiple filesystems
				which require multiple varied naming conventions, a sensible system for
				naming is required.  Thus each file has a "base name" which corresponds
				to its default name in any filesystem.
				
				Whenever possible, the "base name" will be used in the generated filesystem
				without modification.  If the name cannot be used as-is (if, for example, it
				contains illegal characters, exceeds the length requirements, doesn't
				meet the required format, or a name collision is detected) then an acceptable
				name that meets the filesystem's criteria will be generated automatically
				from the base name.
				
				The default base name for a real file or folder is the actual on-disk
				name of the file.  
	@param		object					Object reference to query.
	@result		A copy of the base name.
*/
extern CFStringRef
DRFSObjectCopyBaseName(
	const DRFSObjectRef			object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopySpecificName
	@abstract	Returns a single filesystem-specific name for a given object.
	@param		object					Object reference to query.
	@param		fsKey					Key for the particular name being queried.
	@result		The specific name for the filesystem.
*/
extern CFStringRef
DRFSObjectCopySpecificName(
	const DRFSObjectRef			object,
	CFStringRef					fsKey)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopySpecificNames
	@abstract	Returns a dictionary containing all of the filesystem-specific names
				for a given object.
	@discussion	The dictionary will return only the names which are indicated by the
				object's effective mask.  If the object's effective mask is zero, an
				empty dictionary is returned.
	@param		object					Object reference to query.
	@result		Dictionary of names.
*/
extern CFDictionaryRef
DRFSObjectCopySpecificNames(
	const DRFSObjectRef			object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopyMangledName
	@abstract	Returns a single filesystem-specific name for a given object, mangled for uniqueness.
	@discussion	The string will be mangled for uniqueness amongst its siblings; if the burn
				were to happen immediately after this call, this is the name which would be used 
				on the resulting disc.
	@param		object					Object reference to query.
	@param		fsKey					Key for the particular name being queried.
	@result		The specific name for the filesystem, mangled for uniqueness.
*/
extern CFStringRef
DRFSObjectCopyMangledName(
	const DRFSObjectRef			object,
	CFStringRef					fsKey)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopyMangledNames
	@abstract	Returns a dictionary containing all of the filesystem-specific names
				for a given object, each one mangled for uniqueness.
	@discussion	The dictionary will return only the names which are indicated by the
				object's effective mask.  If the object's effective mask is zero, an
				empty dictionary is returned.
	@param		object					Object reference to query.
	@result		Dictionary of names, each one mangled for uniqueness.
*/
extern CFDictionaryRef
DRFSObjectCopyMangledNames(
	const DRFSObjectRef			object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopyFilesystemProperty
	@abstract	Returns a single property for a given object.
	@param		object					Object reference to query.
	@param		fsKey					Filesystem to query.
	@param		propertyKey				Property to query.
	@param		coalesce				If TRUE, will check the "all filesystems" properties if the property isn't found in the requested filesystem dictionary.
	@result		The property, or NULL if not found.
*/
extern CFTypeRef
DRFSObjectCopyFilesystemProperty(
	const DRFSObjectRef			object,
	CFStringRef					fsKey,
	CFStringRef					propertyKey,
	Boolean						coalesce)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectCopyFilesystemProperties
	@abstract	Returns a CFDictionary of filesystem properties for a given object.
	@param		object					Object reference to query.
	@param		fsKey					Filesystem to query.
	@param		coalesce				If TRUE, will also get the "all filesystems" dictionary, and merge it with the requested filesystem dictionary.
	@result		The properties, or NULL if none have been set.
*/
extern CFDictionaryRef
DRFSObjectCopyFilesystemProperties(
	const DRFSObjectRef			object,
	CFStringRef					fsKey,
	Boolean						coalesce)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFSObjectGetFilesystemMask
	@abstract	Returns the masks indicating in which filesystems this object should appear.
	@discussion	See the introduction for an explanation of explicit vs effective masks.
	@param		object					Object reference to query.
	@param		outExplicitMask			Filled in with the object's explicit mask.  May be NULL.
	@param		outEffectiveMask		Filled in with the object's effective mask.  May be NULL.
	@result		For convenience, the effective mask is returned.
*/
extern DRFilesystemMask
DRFSObjectGetFilesystemMask(
	const DRFSObjectRef			object,
	DRFilesystemMask *			explicitMask,
	DRFilesystemMask *			effectiveMask)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectSetBaseName
	@abstract	Sets the base name for the object (either a file or a folder).
	@discussion	The base name is the name from which any necessary filesystem-specific
				names are automatically generated.  
				
				Because the content creation API is able to generate multiple filesystems
				which require multiple varied naming conventions, a sensible system for
				naming is required.  Thus each file has a "base name" which corresponds
				to its default name in any filesystem.
				
				Whenever possible, the "base name" will be used in the generated filesystem
				without modification.  If the name cannot be used as-is (if, for example, it
				contains illegal characters, exceeds the length requirements, doesn't
				meet the required format, or a name collision is detected) then an acceptable
				name that meets the filesystem's criteria will be generated automatically
				from the base name.
				
				<b>NOTE:</b>Changing the base name will <b>remove</b> any filesystem-specific
				name overrides that may have been installed.
	@param		object					Object reference to modify.
	@param		baseName				The new name of the object.
*/
extern void
DRFSObjectSetBaseName(
	DRFSObjectRef				object,
	CFStringRef					baseName)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@function	DRFSObjectSetSpecificName
	@abstract	Changes a single filesystem-specific name for a given object.
	@discussion	Every effort will be made to use the name passed in.  However, if
				the name is illegal, it will be modified to fit the rules for that
				filesystem's names.  Because of this, you should always call
				DRContentGetSpecificName after DRContentSetSpecificName to ensure
				that you are always displaying the most current name to the user.
	@param		object					Object reference to modify.
	@param		fsKey					Key for the particular filesystem-specific name being modified.
	@param		specificName			Name to apply to the object.
*/
extern void
DRFSObjectSetSpecificName(
	DRFSObjectRef				object,
	CFStringRef					fsKey,
	CFStringRef					specificName)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*!	@function	DRFSObjectSetSpecificNames
	@abstract	Changes the filesystem-specific names for a given object.
	@discussion	Every effort will be made to use the names passed in.  However, if
				the given name for a key is illegal, it will be modified to fit the
				rules for that filesystem's names.  Because of this, you should always
				call DRContentGetSpecificNames after DRContentSetSpecificNames to ensure
				that you are always displaying the most current name to the user.
	@param		object					Object reference to modify.
	@param		specificNames			Dictionary containing the names to apply to the object.
	@result		Error code.
*/
extern void
DRFSObjectSetSpecificNames(
	DRFSObjectRef				object,
	CFDictionaryRef				specificNames)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFSObjectSetFilesystemProperty
	@abstract	Sets a single filesystem property for a specific object.
	@param		object					Object reference to modify.
	@param		fsKey					Filesystem to modify.
	@param		propertyKey				Which property to modify.
	@param		value					New value for the property.
	@result		Error code.
*/
extern void
DRFSObjectSetFilesystemProperty(
	DRFSObjectRef				object,
	CFStringRef					fsKey,
	CFStringRef					propertyKey,
	CFTypeRef					value)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFSObjectSetFilesystemProperties
	@abstract	Changes the filesystem properties for a specific object.
	@param		object					Object reference to modify.
	@param		fsKey					Filesystem to modify.
	@param		properties				Dictionary of properties to set.
*/
extern void
DRFSObjectSetFilesystemProperties(
	DRFSObjectRef				object,
	CFStringRef					fsKey,
	CFDictionaryRef				properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFSObjectSetFilesystemMask
	@abstract	Sets the explicit mask indicating in which filesystems this object should appear.
	@discussion	See the introduction for an explanation of explicit vs effective masks.
	@param		object					Object reference to modify
	@param		newMask					New explicit mask.
*/
extern void
DRFSObjectSetFilesystemMask(
	DRFSObjectRef				object,
	DRFilesystemMask			newMask)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#ifdef __cplusplus
}
#endif

#endif /* _H_DRContentObject */

