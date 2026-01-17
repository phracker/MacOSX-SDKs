/*
     File:       DiscRecording/DRFSObject.h
 
     Contains:   Protocol defining common features of all filesystem content
     			 objects.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Foundation/Foundation.h>
#import <AvailabilityMacros.h>

@class DRFolder;

typedef UInt32 DRFilesystemInclusionMask;

enum {
	DRFilesystemInclusionMaskISO9660			= (1<<0),
	DRFilesystemInclusionMaskJoliet				= (1<<1),
	DRFilesystemInclusionMaskHFSPlus			= (1<<3)
};

/*!
	@header	DRFSObject
	@discussion
				<h3>About Content Creation</h3>
				Content creation provides an interface for dynamic filesystem creation, allowing
				complex filesystem hierarchies to be created and burned on-the-fly without having
				to generate a complete on-disk representation.
				
				DRFSObject is the root object for the objects contained in the Objective C 
				content creation hierarchy. Through DRFSObject, file and folder objects
				inherit a basic interface to getting and setting filesystem properties,
				names and masks. The DRFSObject class is an abstract class, there are no
				methods available to create a DRFSObject directly, you create DRFile and
				DRFolder objects instead.
				
				
				<h3>Real and Virtual Objects</h3>
				The interface is designed around folder and file objects which are laid out
				in a one-parent-many-children hierarchy - this should be a familiar concept for
				anyone who's ever used a modern filesystem.  There are two kinds of objects in
				this API; "real" objects and "virtual" objects, and the distinction is important.
				
				* A <i>real</i> file or folder object corresponds directly to a file or folder
					on disk.  The data for a real file object comes directly from the on-disk file.
					The hierarchy underneath a real folder object corresponds 1:1 to the
					hierarchy underneath the folder in the on-disk filesystem.
				
				* A <i>virtual</i> file or folder object does not have any actual representation
					on disk.  The data for a virtual file object is specified through the API or
					in a callback function.  The hierarchy underneath a virtual folder object 
					is specified through the API.
				
				
				<h3>Creating a Virtual Hierarchy</h3>
				In the hierarchy specified through this API, only virtual folders may be assigned
				children.  Real files, virtual files, and real folders are all considered leaf
				nodes and may not have children.  (Real folders may of course contain files and
				folders, but the files and folders are specified by the on-disk representation and
				may not be changed through the API unless the real folder is made virtual first.)
				
				A hierarchy may be as simple as a single real folder, or it can be as complicated
				as needed - for example, a virtual folder with a deep hierarchy of children which are
				a complex mix of real files, virtual files, real folders, and virtual folders.
				
				
				<h3>Converting From Real To Virtual</h3>
				A real folder can be dynamically converted to a virtual folder, in which case
				its first level of children is read and converted into a virtual hierarchy.  The children
				thus created will all be real.  For example: A real folder named <i>root</i> is converted
				into a virtual folder.  The on-disk folder contains a file named <i>file1</i> and
				a folder named <i>folder2</i>.  After conversion, the result is a virtual folder named
				<i>root</i> with two children: the real file <i>file1</i> and the real folder <i>folder2</i>.
				
				
				<h3>Base Names and Specific Names</h3>
				Because the content creation API is able to generate multiple filesystems which
				require multiple varied naming conventions, a sensible system for naming is required.
				Thus each file has a <i>base name</i> which corresponds to its default name in any filesystem. 
				Whenever possible, the base name will be used in the generated filesystem without
				modification.
			
				The initial base name for a real object is the name of the corresponding object
				on disk.  The initial base name for a virtual object is specified when the object
				is created.  The base names for both real and virtual objects may be modified using the
				<b>setBaseName:</b> method.
				
				Inside a particular filesytem, if the base name cannot be used as-is (if, for example, it contains illegal
				characters, exceeds the length requirements, or otherwise doesn't meet the required format)
				then an acceptable name that meets the filesystem's criteria will be generated
				automatically from the base name.  The name which is acceptable to a given filesystem
				is that file's <i>specific name</i> for that filesystem.
				
				A specific name may be obtained and modified through this API, or may be left empty to
				be automatically generated from the base name.  When a specific name is set through the API,
				it will be modified to ensure that the name is legal according to the particular filesystem.
				
				Even when a specific name is set or generated through the API, it may not be the actual name
				used on the disc.  If an object's specific name conflicts with the specific name of another
				of the object's siblings in that filesystem, one or both specific names will be <i>mangled</i>
				to obtain a unique name before burning, usually by adding a numeric mangle code such as _001
				to each name.
				
				There are two APIs available for getting the specific name from an object:
				
				* <b>specificNameForFilesystem:</b> returns the unmodified specific name, which would be used if there were
				no conflicts.  
				
				* <b>Filesystem</b> returns a modified specific name, mangled if necessary,
				which is guaranteed to be unique amongst its siblings in the filesystem.  
				
				The filesystem keys are detailed in <b>Filesystem data accessors</b>.  Most of the keys are 
				straightforward; however, ISO-9660
				is a special case, since there are two possible naming conventions for ISO-9660, level 1
				(8.3, limited charset) and level 2 (30 chars, marginally expanded charset).  You can't
				specify DRISO9660 when obtaining a name; instead, you must explicitly specify whether
				you want the level 1 or level 2 name with DRISO9660LevelOne or DRISO9660LevelTwo.
				
				If the object's
				name does not conflict with any of its siblings, <b>mangledNameForFileSystem:</b> will return the same
				value as <b>specificNameForFilesystem:</b>.  The converse is not necessarily true -- one object may get
				the actual specific name, and other files with name collisions will be mangled.
				
				<b>mangledNameForFileSystem:</b> will check each of the object's siblings in the hierarchy and mangle to
				resolve any filename conflicts, so it can be a much more expensive call than <b>specificNameForFilesystem:</b>,
				taking at worst O(N^2) time where N is the number of siblings.  However, actual performance
				tends to be much better, closer to O(N), particularly when there are only a few collisions.
				<b>mangledNameForFileSystem:</b> has the advantage of allowing you to see (and to show the user) the exact
				names which would be generated on the disc if the burn were started immediately.
				
				Both <b>specificNameForFilesystem:</b> and <b>mangledNameForFileSystem:</b> will cache information when possible, so
				that names are only generated and mangled when necessary.  Adding or removing children
				from a folder, or changing the base or specific name on an object, may cause
				the cached names of the object's children or siblings to be recomputed.
				
				
				<h3>Properties and Other Meta-Data</h3>
				Properties are generally accessed similarly to names.  Each object has overall
				properties which apply to every filesystem, and it may also have different properties
				in each filesystem.  For example, a file which has no relevance for a MacOS user
				may be marked invisible in the HFS+ tree, but be visible in the Joliet tree.
				
				The properties, like names, are also differentiated by filesystem. There is one
				properties dictionary for DRAllFilesystems, and one properties dictionary for each
				individual filesystem - DRISO9660, DRJoliet, DRHFSPlus, etc.  
			
				The properties for DRAllFilesystems are treated as the base value, and then the
				properties in the specific filesystem dictionary are treated as overrides.
				
				When obtaining properties with <b>propertyForKey:inFilesystem:mergeWithOtherFilesystems:</b> or
				propertiesForFilesystem:mergeWithOtherFilesystems:, you can specify whether you want to
				automatically coalesce the properties between the specified filesystem dictionary and
				the "all filesystems" dictionary.  This is useful if you want to obtain the effective
				value of the property, because it will return the value from the "all filesystems"
				dictionary if the specific filesystem does not assign an override. 
				
					
				
				<h3>Filesystem Masks</h3>
				It's possible to suppress generation of particular items in a folder tree.  For example,
				you may want a MacOS application file or bundle to only appear in the HFS+ tree, and
				want an .EXE file to only appear in the Joliet tree.
				
				Filesystem-specific suppression is handled through the <i>filesystem mask</i>.  The filesystem
				mask is a bitfield which contains a 1 if the object will appear in the corresponding filesystem,
				and 0 otherwise.  This can be used to generate arbitrarily complex trees, where in the most
				complex case each filesystem may theoretically have its own unique and disjoint tree.
				(Such discs are discouraged, however, since they may be confusing to the user.)
				
				An object can be considered to have two mask values.  The first one is the <i>explicit mask</i>
				which has been set by the client, and may be zero if no mask has been set.  The other is the
				<i>effective mask</i>, which is the actual mask which will be used.
				
				If the explicit mask is non-zero, then the object's effective mask is equal to the
				bitwise AND of the object's explicit mask and its parent's effective mask.
				
				If the explicit mask is zero, the object will use the same mask as its parent.  (In
				other words, the effective mask is equal to the parent's effective mask.)
				
				If the root of the hierarchy does not have an explicit mask set, the effective mask of
				the root and all its descendants will be zero.
				
				The explicit mask may be cleared by changing it to zero.  By doing this, the
				object's explicit mask becomes zero and its effective mask will be inherited
				from its parent.
				
				If an object's effective mask is zero, it will not be included in the burn.  The major
				exception to this rule is when the root folder's explicit/effective mask is zero - when
				this happens, DiscRecording will assign a default mask, typically one which will result in
				the most cross-platform disc possible.
				
				If the effective mask of the root is zero at the time of the burn, DiscRecording will
				automatically pick a default mask, typically one which will result in the most
				cross-platform disc possible.
				
				Some combinations of filesystem mask have special requirements; for example, Joliet is
				based on ISO-9660, and requires that ISO-9660 be enabled on at least the root object.
				(You can still have something appear in Joliet but not ISO-9660, however.)  Some
				combinations in the future may be mutually exclusive. 
				
				You do not have to set an explicit mask for anything but the root if you want all
				filesystems to have the same data.  Since DiscRecording will automatically assign
				a mask if none is provided, you do not even have to set an explicit mask for the root.
				
				
				<h3>Symbolic Link Translation</h3>
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
				
				* ISO-9660 level 1: "MYLONGLO/THISISAN.WIT"
				* ISO-9660 level 2: "MY LONG LONG DIRECTORY/THIS: IS AN UNU.WITH_EXTENSION"
				* Joliet:           "my long, long directory/this: is an unusual filename.with_extension"
				* HFS+:             "my long, long directory/this: is an unusual$ filename.with_extension"
			
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
				
				This is expected behavior.  At present, the only way to create a perfect symlink which
				is guaranteed to have a correct path on <b>all</b> filesystems is to create a virtual symlink
				using <b>symLinkPointingTo:inFilesystem:</b>.  
*/
/*!
	@class 		DRFSObject
	@discussion	DRFSObject is an abstract base class for the content creation framework.
*/
@interface DRFSObject : NSObject 
{ 
@private
	void*	_ref;
}

/*!
	@method		isVirtual
	@abstract	Indicates whether the receiver is real or virtual.
	@result		<i>YES</i> if the receiver is virtual and <i>NO</i> if real.	
*/	
- (BOOL) isVirtual;

/*!
	@method		sourcePath
	@abstract	Returns the path to a real object.
	@discussion	This method only applies to DRFSObjects pointing to real objects.
	@result		A path
*/	
- (NSString*) sourcePath;

/*!
	@method		parent
	@abstract	Returns the parent folder (if any) of the receiver in the content hierarchy.
	@result		A DRFolder object.	
*/	
- (DRFolder*) parent;

/*!
	@method		baseName
	@abstract	Returns the base name for the receiver.
	@discussion		The base name is the name from which any necessary filesystem-specific
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
				name of the item.
	@result		The base name of the object.	
*/	
- (NSString*) baseName;

/*!
	@method		setBaseName:
	@abstract	Sets the base name for the receiver.
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
				name of the item.
	@param		baseName The new base name of the object.	
*/	
- (void) setBaseName:(NSString*)baseName;

/*!
	@method		specificNameForFilesystem:
	@abstract	Returns a single filesystem-specific name for the receiver.
	@param		filesystem	The filesystem to return the name from.
	@result		The name of the file.
*/
- (NSString*) specificNameForFilesystem:(NSString*)filesystem;

/*!
	@method		specificNames:
	@abstract	Returns all the filesystem-specific names for the receiver.
	@param		filesystem	The filesystem to return the name from.
	@result		An NSDictionary containing the name of the file on all the filesystems.
*/
- (NSDictionary*) specificNames;

/*!
	@method		setSpecificName:forFilesystem:
	@abstract	Sets the name used for the receiver in a particular filesystem.
	@param		name	The name to set.
	@param		filesystem	The filesystem to set the name for.
*/
- (void) setSpecificName:(NSString*)name forFilesystem:(NSString*)filesystem;

/*!
	@method		setSpecificNames:
	@abstract	Sets the names used for the receiver in the different filesystems all at once.
	@discussion	Takes an NSDictionary of filesystem keys with corresponding name strings as
				their values for each specific filesystem name that should be set.
			
				Every effort will be made to use the names passed in.  However, if
				a name is illegal, it will be modified to fit the rules for that
				filesystem's names.  Because of this, you should always call
				<b>specificNames:</b> after <b>setSpecificNames:</b> to ensure
				that you are always displaying the most current names to the user.
	@param		name	The name to set.
	@param		filesystem	The filesystem to set the name for.
*/
- (void) setSpecificNames:(NSDictionary*)specificNames;

/*!
	@method		mangledNameForFilesystem:
	@abstract	Returns a single filesystem-specific name for the receiver, mangled for uniqueness.
	@discussion	The string will be mangled for uniqueness amongst its siblings; if the burn
				were to happen immediately after this call, this is the name which would be used 
				on the resulting disc.
	@param		filesystem	The filesystem to set the name for.
	@result		The name of the file mangled for filesystem constraints.
*/
- (NSString*)mangledNameForFilesystem:(NSString*)filesystem;

/*!
	@method		mangledNames:
	@abstract	Returns a dictionary containing all of the filesystem-specific names
				for the receiver, each one mangled for uniqueness.
	@discussion	The dictionary will return only the names which are indicated by the
				receiver's effective mask.  If the receiver's effective mask is zero, an
				empty dictionary is returned.
	@param		filesystem	The filesystem to set the name for.
	@result		The name of the file mangled for filesystem constraints.
*/
- (NSDictionary*) mangledNames;

/*!
	@method		propertyForKey:inFilesystem:mergeWithOtherFilesystems:
	@abstract	Returns a file/folder property specified by key for the specified filesystem.
	@discussion	If the property key is not set for the specific filesystem queried and 
				merge is <i>YES</i> then the umbrella DRAllFilesystems property will be 
				checked. Returns nil if the property key cannot be found.
	@param		key	The property to return.
	@param		filesystem	The filesystem to look in.
	@param		merge		If <i>YES</i>, look for the property in the umbrella DRAllFilesystems.
	@result		The value associated with the property.
*/
- (id) propertyForKey:(NSString*)key inFilesystem:(NSString*)filesystem mergeWithOtherFilesystems:(BOOL)merge;

/*!
	@method		propertiesForFilesystem:mergeWithOtherFilesystems:
	@abstract	Returns all the filesystem properties set for the specified filesystem.
	@discussion	If merge is <i>YES</i> then the umbrella DRAllFilesystems property will be 
				checked.
	@param		filesystem	The filesystem to look in.
	@param		merge		If <i>YES</i>, look for the properties in the umbrella DRAllFilesystems.
	@result		The value associated with the property.
*/
- (NSDictionary*) propertiesForFilesystem:(NSString*)filesystem mergeWithOtherFilesystems:(BOOL)merge;

/*!
	@method		setProperty:forKey:inFilesystem:
	@abstract	Sets the value of the receiver's property specified by key for the specific
				filesystem.
	@discussion	DRAllFilesystems may be specified as the filesystem in which case
				the umbrella property affecting all filesystems at once will be set. Setting
				a property for DRAllFilesystems does not preclude setting a filesystem specific 
				property.
	@param		property	The value of the property.
	@param		key			The property key.
	@param		filesystem	The filesystem to set the property in.
*/
- (void) setProperty:(id)property forKey:(NSString*)key inFilesystem:(NSString*)filesystem;

/*!
	@method		setProperties:inFilesystem:
	@abstract	Sets the value of all the receiver's properties specified by the keys in properties
				for the specific filesystem.
	@discussion	DRAllFilesystems may be specified as the filesystem 
				in which case he umbrella property affecting all filesystems at once will be set. 
				Setting properties for DRAllFilesystems does not preclude setting a filesystem specific 
				property.
	@param		properties	The value of the property.
	@param		filesystem	The filesystem to set the property in.
*/
- (void) setProperties:(NSDictionary*)properties inFilesystem:(NSString*)filesystem;

/*!
	@method		explicitFilesystemMask
	@abstract	Returns the explicit filesystem mask set for the reciever.
	@discussion	The explicit mask is one that has been explicitly set by a client 
				through the <b>setExplicitFilesystemMask:</b> method.
	@result		A filesystem mask
*/
- (DRFilesystemInclusionMask) explicitFilesystemMask;

/*!
	@method		explicitFilesystemMask
	@abstract	Sets the filesystems the receiver will be included on.
	@discussion	The explicit mask for an item cannot be more inclusive than the 
				effective mask of it's parent.
	@param		mask	A filesystem mask
*/
- (void) setExplicitFilesystemMask:(DRFilesystemInclusionMask)mask;

/*!
	@method		explicitFilesystemMask
	@abstract	Returns the effective filesystem mask set for the reciever.
	@discussion	The parent filesystem mask is taken into account for the receiver.
	@result		A filesystem mask
*/
- (DRFilesystemInclusionMask) effectiveFilesystemMask;

@end

/* -------------------------------------------------------------------------------- */
/* Filesystem data accessors */
/*	These define the filesystems supported by the content creation framework. If 
	a method requests a filesystem specification, one of these values should be 
	passed in to indicate which filesystem to return or set the property for.
*/	
/*!
	@const		DRAllFilesystems
	@discussion	The key for accessing the name or properties for the file in
						all filesystems together. When this key is used to refer to a name, it refers to the
						base name (which has no naming restrictions).
*/
extern NSString* const DRAllFilesystems		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRISO9660
	@discussion	Thekey for accessing the ISO-9660 properties for the file.
						This key is used to refer specifically to the properties for the file.
			
						This key cannot be used to refer to the name of the file; it is ambiguous,
						since the name may be in either level 1 or level 2 format.
*/
extern NSString* const DRISO9660			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRISO9660LevelOne
	@discussion	The key for accessing the ISO-9660 level 1 name for the file.
						This key is used to refer specifically to the name generated for ISO-9660 if
						the ISO level is set to 1.  When used for a property, it is equivalent
						in use to the DRISO9660 key and acts as a synonym for that key.
						
						ISO9660 level 1 names are in the form typically known as 8.3 - eight
						characters of name and three characters of extension (if it's a file;
						directories can't have extensions).  Character set is limited to
						A-Z, 0-9, and _.
*/
extern NSString* const DRISO9660LevelOne	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRISO9660LevelTwo
	@discussion	The key for accessing the ISO-9660 level 2 name for the file.
				This key is used to refer specifically to the name generated for ISO-9660 if
				the ISO level is set to 2.  When used for a property, it is equivalent
				in use to the DRISO9660 key and acts as a synonym for that key.
	
				ISO9660 level 2 names can be 32 chars long, are limited to a subset
				of the 7-bit ASCII chars (capital letters, numbers, space, punctuation),
				and are only allowed one "." character.
*/
extern NSString* const DRISO9660LevelTwo	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRJoliet
	@discussion	The key for accessing the Joliet name/properties for the file.
				Joliet names can be 64 precomposed unicode characters long, but are only
				allowed one "." character and many punctuation characters are illegal.
*/
extern NSString* const DRJoliet				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRHFSPlus
	@discussion	The key for accessing the HFS+ name/properties for the file.
				HFS+ names can be up to 255 decomposed unicode characters long.
*/
extern NSString* const DRHFSPlus			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




/* -------------------------------------------------------------------------------- */
/* Keys for file/folder properties */

/*!
	@const		DRISO9660VersionNumber
	@discussion	NSNumber containing the ISO9660 version number for the object. Default value is 1.
*/
extern NSString* const DRISO9660VersionNumber			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRInvisible
	@discussion	NSBoolean indicating whether the item is invisibile or not.
*/
extern NSString* const DRInvisible						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRCreationDate
	@discussion	NSDate containing the item's creation date.
*/
extern NSString* const DRCreationDate					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRContentModificationDate
	@discussion	NSDate containing the item's content modification date.
*/
extern NSString* const DRContentModificationDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRAttributeModificationDate
	@discussion	NSDate containing the item's attribute modification date.
*/
extern NSString* const DRAttributeModificationDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRAccessDate
	@discussion	NSDate containing the item's last-accessed date.
*/
extern NSString* const DRAccessDate						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBackupDate
	@discussion	NSDate containing the item's backup date.
*/
extern NSString* const DRBackupDate						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DREffectiveDate
	@discussion	NSDate containing the item's effective date.
*/
extern NSString* const DREffectiveDate					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRExpirationDate
	@discussion	NSDate containing the item's expiration date.
*/
extern NSString* const DRExpirationDate					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRRecordingDate
	@discussion	NSDate containing the item's recording date.
*/
extern NSString* const DRRecordingDate					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPosixFileMode
	@discussion	NSNumber containing the item's POSIX file mode.
*/
extern NSString* const DRPosixFileMode					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPosixUID
	@discussion	NSNumber containing the item's POSIX UID.
*/
extern NSString* const DRPosixUID						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPosixGID
	@discussion	NSNumber containing the item's POSIX GID.
*/
extern NSString* const DRPosixGID						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRHFSPlusTextEncodingHint
	@discussion	NSNumber containing the item's text encoding hint (HFS+ only).
				
				This value is used by the MacOS to help when converting
				the natively UTF-16 filename into an 8-bit-per-character representation (such
				as MacRoman, Shift-JIS, or UTF8).  If not set, default behavior is to call
				CFStringGetMostCompatibleMacStringEncoding(CFStringGetSmallestEncoding()).
*/
extern NSString* const DRHFSPlusTextEncodingHint		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRHFSPlusCatalogNodeID
	@discussion	NSNumber containing item's catalog node ID (HFS+ only).
				Currently, this value if set is only a suggestion.
				The burn engine will attempt to use this node ID, but may use another value
				if it needs to resolve conflicts.  Default behavior is to allocate node IDs
				incrementally from kHFSFirstUserCatalogNodeID.
*/
extern NSString* const DRHFSPlusCatalogNodeID			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacFileType
	@discussion	NSData containing the OSType for the file type (MacOS only).
*/
extern NSString* const DRMacFileType					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacFileCreator
	@discussion	NSData containing the OSType for the file creator (MacOS only).
*/
extern NSString* const DRMacFileCreator					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacWindowBounds
	@discussion	NSData containing a Rect (not NSRect) for the window bounds for a folder (MacOS only).
*/
extern NSString* const DRMacWindowBounds				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacIconLocation
	@discussion	NSData containing a Point (not NSPoint) for the item's icon location in its parent folder (MacOS only).
*/
extern NSString* const DRMacIconLocation				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacScrollPosition
	@discussion	NSData containing a Point (not NSPoint) for the folder's scroll position (MacOS only).
*/
extern NSString* const DRMacScrollPosition				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacWindowView
	@discussion	NSNumber containing the folder's window view type (MacOS only).
*/
extern NSString* const DRMacWindowView					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacFinderFlags
	@discussion	NSNumber containing the item's Finder flags (MacOS only). The "invisible" bit is ignored - use DRInvisible instead.
*/
extern NSString* const DRMacFinderFlags					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMacExtendedFinderFlags
	@discussion	NSNumber containing the item's extended Finder flags (MacOS only).
*/
extern NSString* const DRMacExtendedFinderFlags			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
