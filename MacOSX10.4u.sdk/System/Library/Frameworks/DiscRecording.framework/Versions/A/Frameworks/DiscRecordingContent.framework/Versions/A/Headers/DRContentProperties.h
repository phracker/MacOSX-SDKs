/*
     File:       DiscRecordingContent/DRContentProperties.h
 
     Contains:   Property strings for filesystem objects.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Property strings for filesystem objects.

	@discussion		
*/

#ifndef _H_DRContentProperties
#define _H_DRContentProperties

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------------- */
/* Keys for track properties */


/*! @constant	kDRISOLevel
	@abstract	The key for indicating the ISO level of the ISO-9660 filesystem on the track. 
	@discussion	Value is a CFNumberRef, currently should be 1 or 2.
*/
extern const CFStringRef kDRISOLevel				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRVolumeSet
	@abstract	(ISO/Joliet) The key for indicating the volume set name.
	@discussion	Value is a CFStringRef.
*/
extern const CFStringRef kDRVolumeSet				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRPublisher
	@abstract	(ISO/Joliet) The key for indicating the publisher string.
	@discussion	Value is a CFStringRef.
*/
extern const CFStringRef kDRPublisher				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRDataPreparer
	@abstract	(ISO/Joliet) The key for indicating the data preparer.
	@discussion	Value is a CFStringRef.
*/
extern const CFStringRef kDRDataPreparer			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRSystemIdentifier
	@abstract	(ISO/Joliet) The key for indicating the system identifier.
	@discussion	Value is a CFStringRef.
				Only the first 32 characters (ISO) or 16 characters (Joliet)
				will be used, after being mapped into a legal character set.
				Note, this value will NOT be used if Mac extensions are turned
				on - with Mac extensions, the system identifier will always be
				"APPLE COMPUTER, INC., TYPE: 0002"
*/
extern const CFStringRef kDRSystemIdentifier		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRApplicationIdentifier
	@abstract	(ISO/Joliet) The key for indicating the application identifier.
	@discussion	Value is a CFStringRef.
				Only the first 32 characters (ISO) or 16 characters (Joliet)
				will be used, after being mapped into a legal character set.
*/
extern const CFStringRef kDRApplicationIdentifier	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRCopyrightFile
	@abstract	(ISO/Joliet) The key for indicating the copyright file.
	@discussion	Value is a @link //apple_ref/c/tdef/DRFileRef DRFileRef @/link (which must be in the root directory).
*/
extern const CFStringRef kDRCopyrightFile			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRAbstractFile
	@abstract	(ISO/Joliet) The key for indicating the abstract file.
	@discussion	Value is a @link //apple_ref/c/tdef/DRFileRef DRFileRef @/link (which must be in the root directory).
*/
extern const CFStringRef kDRAbstractFile			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRBibliographicFile
	@abstract	(ISO/Joliet) The key for indicating the bibliographic file.
	@discussion	Value is a @link //apple_ref/c/tdef/DRFileRef DRFileRef @/link (which must be in the root directory).
*/
extern const CFStringRef kDRBibliographicFile		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRBlockSize
	@abstract	The key for indicating the block size of the track.
	@discussion	Value is a CFNumberRef, currently always 2048.  Do not change.
*/
extern const CFStringRef kDRBlockSize				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRDefaultDate
	@abstract	The default date for any unspecified dates in the filesystem.
	@discussion	Value is a CFDateRef.  The current date and time is used if unspecified.
*/
extern const CFStringRef kDRDefaultDate				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRVolumeCreationDate
	@abstract	The key for indicating the volume creation date.
	@discussion	Value is a CFDateRef.  @link kDRDefaultDate kDRDefaultDate @/link is used if unspecified.
*/
extern const CFStringRef kDRVolumeCreationDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRVolumeModificationDate
	@abstract	The key for indicating the volume modification date.
	@discussion	Value is a CFDateRef.  @link kDRDefaultDate kDRDefaultDate @/link is used if unspecified.
*/
extern const CFStringRef kDRVolumeModificationDate	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRVolumeCheckedDate
	@abstract	(HFS+) The key for indicating the volume-checked date.
	@discussion	Value is a CFDateRef.  @link kDRDefaultDate kDRDefaultDate @/link is used if unspecified.
*/
extern const CFStringRef kDRVolumeCheckedDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRVolumeExpirationDate
	@abstract	(ISO/Joliet) The date and time at which the volume expires.
	@discussion	Value is a CFDateRef.  Empty if unspecified.
*/
extern const CFStringRef kDRVolumeExpirationDate	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRVolumeEffectiveDate
	@abstract	(ISO/Joliet) The date and time at which the volume is effective.
	@discussion	Value is a CFDateRef.  Empty if unspecified.
*/
extern const CFStringRef kDRVolumeEffectiveDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRISOMacExtensions
	@abstract	(ISO/Joliet) Whether to add ISO/Joliet Mac extensions when appropriate.
	@discussion	Value is a CFBooleanRef.
*/
extern const CFStringRef kDRISOMacExtensions		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRISORockRidgeExtensions
	@abstract	(ISO/Joliet) Whether to add RockRidge (POSIX extensions) when appropriate.
	@discussion	Value is a CFBooleanRef.
*/
extern const CFStringRef kDRISORockRidgeExtensions	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRSuppressMacSpecificFiles
	@abstract	Whether to suppress Mac-specific files from non-HFS filesystems.
	@discussion	Value is a CFBooleanRef.
*/
extern const CFStringRef kDRSuppressMacSpecificFiles	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* -------------------------------------------------------------------------------- */
/* Keys for accessing names and properties */

/*!
	@constant	kDRAllFilesystems
	@abstract	The key for accessing the name or properties for the file in
				all filesystems together.
	@discussion	When this key is used to refer to a name, it refers to the
				base name (which has no naming restrictions).
*/
extern const CFStringRef kDRAllFilesystems			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@constant	kDRISO9660
	@abstract	The key for accessing the ISO-9660 properties for the file.
	@discussion	This key is used to refer specifically to the properties for the file.
	
				This key cannot be used to refer to the name of the file; it is ambiguous,
				since the name may be in either level 1 or level 2 format.
*/
extern const CFStringRef kDRISO9660					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRISO9660LevelOne
	@abstract	The key for accessing the ISO-9660 level 1 name for the file.
	@discussion	This key is used to refer specifically to the name generated for ISO-9660 if
				the ISO level is set to 1.  When used for a property, it is equivalent
				in use to the @link kDRISO9660 kDRISO9660 @/link key and acts as a synonym for that key.
				
				ISO9660 level 1 names are in the form typically known as 8.3 - eight
				characters of name and three characters of extension (if it's a file;
				directories can't have extensions).  Character set is limited to
				A-Z, 0-9, and _.
*/
extern const CFStringRef kDRISO9660LevelOne			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRISO9660LevelTwo
	@abstract	The key for accessing the ISO-9660 level 2 name for the file.
	@discussion	This key is used to refer specifically to the name generated for ISO-9660 if
				the ISO level is set to 2.  When used for a property, it is equivalent
				in use to the @link kDRISO9660 kDRISO9660 @/link key and acts as a synonym for that key.
	
				ISO9660 level 2 names can be 32 chars long, are limited to a subset
				of the 7-bit ASCII chars (capital letters, numbers, space, punctuation),
				and are only allowed one "." character.
*/
extern const CFStringRef kDRISO9660LevelTwo			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRJoliet
	@abstract	The key for accessing the Joliet name/properties for the file.
	@discussion	Joliet names can be 64 precomposed unicode characters long, but are only
				allowed one "." character and many punctuation characters are illegal.
*/
extern const CFStringRef kDRJoliet					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRHFSPlus
	@abstract	The key for accessing the HFS+ name/properties for the file.
	@discussion	HFS+ names can be up to 255 decomposed unicode characters long.
*/
extern const CFStringRef kDRHFSPlus					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@constant	kDRUDF
	@abstract	The key for accessing the UDF name/properties for the file.
*/
extern const CFStringRef kDRUDF						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* -------------------------------------------------------------------------------- */
/* Keys for file/folder properties */

/*!	@constant	kDRISO9660VersionNumber
	@abstract	The property key for the ISO9660 version number for the object.
	@discussion	Value is a CFNumber, default value is 1.
*/
extern const CFStringRef kDRISO9660VersionNumber	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRInvisible
	@abstract	The property key for the invisibility of the object.
	@discussion	Value is a CFBooleanRef.
*/
extern const CFStringRef kDRInvisible				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRCreationDate
	@abstract	The property key for the item's creation date.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRCreationDate			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRContentModificationDate
	@abstract	The property key for the item's content modification date.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRContentModificationDate	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRAttributeModificationDate
	@abstract	The property key for the item's attribute modification date.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRAttributeModificationDate	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRAccessDate
	@abstract	The property key for the item's last-accessed date.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRAccessDate				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRBackupDate
	@abstract	The property key for the item's backup date.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRBackupDate				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRRecordingDate
	@abstract	The property key for the item's recording date.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRRecordingDate			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDREffectiveDate
	@abstract	The property key for the item's effective date, the date at which
				the contents become valid.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDREffectiveDate			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRExpirationDate
	@abstract	The property key for the item's expiration date, the date at which
				the contents become no longer valid.
	@discussion	Value is a CFDateRef.
*/
extern const CFStringRef kDRExpirationDate			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRPosixFileMode
	@abstract	The posix file mode.
	@discussion	Value is a CFNumber.
*/
extern const CFStringRef kDRPosixFileMode			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRPosixUID
	@abstract	The posix file UID.
	@discussion	Value is a CFNumber.
*/
extern const CFStringRef kDRPosixUID				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRPosixGID
	@abstract	The posix file GID.
	@discussion	Value is a CFNumber.
*/
extern const CFStringRef kDRPosixGID				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRHFSPlusTextEncodingHint
	@abstract	The property key for the item's text encoding hint (HFS+ only).
	@discussion	Value is a CFNumber.  This value is used by the MacOS to help when converting
				the natively UTF-16 filename into an 8-bit-per-character representation (such
				as MacRoman, Shift-JIS, or UTF8).  If not set, default behavior is to call
				@link //apple_ref/c/func/CFStringGetMostCompatibleMacStringEncoding CFStringGetMostCompatibleMacStringEncoding @/link(@link //apple_ref/c/func/CFStringGetSmallestEncoding CFStringGetSmallestEncoding @/link()).
*/
extern const CFStringRef kDRHFSPlusTextEncodingHint	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRHFSPlusCatalogNodeID
	@abstract	The property key for the item's catalog node ID (HFS+ only).
	@discussion	Value is a CFNumber.  Currently, this value if set is only a suggestion.
				The burn engine will attempt to use this node ID, but may use another value
				if it needs to resolve conflicts.  Default behavior is to allocate node IDs
				incrementally from @link //apple_ref/c/econst/kHFSFirstUserCatalogNodeID kHFSFirstUserCatalogNodeID @/link.
*/
extern const CFStringRef kDRHFSPlusCatalogNodeID	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacFileType
	@abstract	The property key for a file's type (MacOS only).
	@discussion	Value is a CFDataRef containing an OSType.
*/
extern const CFStringRef kDRMacFileType				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacFileCreator
	@abstract	The property key for a file's creator (MacOS only).
	@discussion	Value is a CFDataRef containing an OSType.
*/
extern const CFStringRef kDRMacFileCreator			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @constant	kDRMacWindowBounds
	@abstract	The property key for the window bounds for a folder (MacOS only).
	@discussion	Value is a CFDataRef containing a Rect.
*/
extern const CFStringRef kDRMacWindowBounds			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacIconLocation
	@abstract	The property key for the item's icon location in its parent folder (MacOS only).
	@discussion	Value is a CFDataRef containing a Point.
*/
extern const CFStringRef kDRMacIconLocation			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacScrollPosition
	@abstract	The property key for the folder's scroll position (MacOS only).
	@discussion	Value is a CFDataRef containing a Point.
*/
extern const CFStringRef kDRMacScrollPosition		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacWindowView
	@abstract	The property key for the folder's window view (MacOS only).
	@discussion	Value is a CFNumber.
*/
extern const CFStringRef kDRMacWindowView			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacFinderFlags
	@abstract	The property key for the item's Finder flags (MacOS only).
	@discussion	Value is a CFNumber.  The "invisible" bit is ignored - use @link kDRInvisible kDRInvisible @/link instead.
*/
extern const CFStringRef kDRMacFinderFlags			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	@constant	kDRMacExtendedFinderFlags
	@abstract	The property key for the item's extended Finder flags (MacOS only).
	@discussion	Value is a CFNumber.
*/
extern const CFStringRef kDRMacExtendedFinderFlags	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!	@const		kDRUDFWriteVersion
	@discussion	Optional key. This property key defines the version for the UDF
				structures written to disk. Values are definde in UDF Version types.
*/
extern const CFStringRef kDRUDFWriteVersion			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ------------------------------------ */
/* UDF Version types */
/*!	@const		kDRUDFVersion102
	@discussion	This value is used in @link kDRUDFWriteVersion kDRUDFWriteVersion @/link.
*/
extern const CFStringRef kDRUDFVersion102			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!	@const		kDRUDFVersion150
	@discussion	This value is used in @link kDRUDFWriteVersion kDRUDFWriteVersion @/link.
*/
extern const CFStringRef kDRUDFVersion150			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
	@const		kDRUDFPrimaryVolumeDescriptorNumber
	@discussion	Optional key. This property key defines the primary volume sequence number.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFPrimaryVolumeDescriptorNumber	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFVolumeSequenceNumber
	@discussion	Optional key. This property key defines the volume sequence number.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFVolumeSequenceNumber				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFMaxVolumeSequenceNumber
	@discussion	Optional key. This property key defines the maximum volume sequence number.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFMaxVolumeSequenceNumber			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFInterchangeLevel
	@discussion	Optional key. This property key defines the volume interchange level.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFInterchangeLevel					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFMaxInterchangeLevel
	@discussion	Optional key. This property key defines the maximum volume interchange level number.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFMaxInterchangeLevel				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFApplicationIdentifierSuffix
	@discussion	Optional key.  A CFData object containing at most 8 bytes of data.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFApplicationIdentifierSuffix		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFVolumeSetIdentifier
	@discussion	Optional key. The Volume Set Identifier for the UDF volume set. If this key
				is not present, @link kDRVolumeSet kDRVolumeSet @/link will be used if present.
				The Volume Set Identifier is composed of the Volume Set Timestamp, the 
				Implementation Use, and a the string contained in this property.
*/
extern const CFStringRef kDRUDFVolumeSetIdentifier				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFVolumeSetTimestamp
	@discussion	Optional key. 
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFVolumeSetTimestamp				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRUDFVolumeSetImplementationUse
	@discussion	Optional key. A CFData object containing at most 8 bytes of data.
				See the UDF specs for details.
*/
extern const CFStringRef kDRUDFVolumeSetImplementationUse		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!	@constant	kDRUDFRealTimeFile
	@abstract	Optional key. Specifies whether this file is to be marked as a UDF Real-Time file.
	@discussion	Value is a CFBooleanRef.
*/
extern const CFStringRef kDRUDFRealTimeFile						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!	@constant	kDRUDFExtendedFilePermissions
	@abstract	Optional key. Specifies the extended UDF file permissions of this file.
	@discussion	Value is a CFNumberRef.
				Bit 0: Change attributes for others (low order bit)
				Bit 1: Delete permissions for others
				Bit 2: Change attributes for group
				Bit 3: Delete permissions for group
				Bit 4: Change attributes for owner
				Bit 5: Delete permissions for owner
				Bit 6 & 7: Reserved
				If this key is not present, @link kDRPosixFileMode kDRPosixFileMode @/link will be used with the above bits
				being set to the corresponding write bit for owner, group, and others.
				If @link kDRPosixFileMode kDRPosixFileMode @/link is not present, the file mode from the file on disc will
				be used, again using the write bit for these permissions.
*/
extern const CFStringRef kDRUDFExtendedFilePermissions			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#ifdef __cplusplus
}
#endif


#endif /* _H_DRContentProperties */

