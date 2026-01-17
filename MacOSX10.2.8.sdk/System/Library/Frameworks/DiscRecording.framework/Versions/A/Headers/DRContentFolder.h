/*
     File:       DiscRecording/DRContentFolder.h
 
     Contains:   Interface to folder objects used in filesystem creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DRContentFolder
#define _H_DRContentFolder

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef _H_DRContentObject
#include <DiscRecording/DRContentObject.h>
#endif

#ifndef __COREFOUNDATION_CFURL__
#include <CoreFoundation/CFURL.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*!
	@function	DRFolderGetTypeID
	@abstract	Returns the type identifier of all DRFolder instances.
*/
extern
CFTypeID DRFolderGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFolderCreateReal
	@abstract	Creates a new real folder object corresponding to a given FSRef.
	@discussion	A real folder object is a folder object which corresponds to a real
				folder on disk.  The content of the folder object corresponds to the
				actual on-disk content of the folder.  Items cannot be programatically added
				to or removed from a real folder object without making it virtual first.  
	@param		fsRef				Reference to a folder on-disk.
	@result		The newly-created folder.
*/
extern DRFolderRef
DRFolderCreateReal(
	const FSRef *				fsRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFolderCreateRealWithURL
	@abstract	Creates a new real folder object corresponding to a given file URL.
	@discussion	A real folder object is a folder object which corresponds to a real
				folder on disk.  The content of the folder object corresponds to the
				actual on-disk content of the folder.  Items cannot be programatically added
				to or removed from a real folder object without making it virtual first.  
	@param		urlRef				Reference to a folder on-disk.
	@result		The newly-created folder.
*/
extern DRFolderRef
DRFolderCreateRealWithURL(
	const CFURLRef				urlRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFolderCreateVirtual
	@abstract	Creates a new, empty virtual folder object.
	@discussion	A virtual folder object is a folder object which does not correspond
				to any real folder on disk.  It is created and populated using the
				DRContent calls.
	@param		baseName				The base name to assign to the new virtual folder.
	@result		The newly-created folder.
*/
extern DRFolderRef
DRFolderCreateVirtual(
	CFStringRef					baseName)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFolderConvertRealToVirtual
	@abstract	Converts a real folder to a virtual folder.  Conversion happens
				in-place so there is no need to release or reallocate any objects.
	@discussion	The virtual folder created in this way is a snapshot of the on-disk
				folder at the moment of the call.  The newly created virtual folder
				will contain <b>real</b> folder and file objects corresponding to the
				on-disk children of the original on-disk folder.
				
				If the on-disk folder is modified (eg, if the folder attributes change, 
				or if children are added to or removed from the on-disk tree):
				
				<ul>
				 <li><i>during</i> this call, the virtual folder <b>may or may not</b>
				 	reflect the changes.
				 <li><i>after</i> this call, the virtual folder <b>will not</b> reflect
				 	the changes.
				</ul>
	@param		realFolder			Folder reference to convert.  Caller should pass in
										a real folder.  On success it will have been converted
										to a virtual folder.
*/
extern void
DRFolderConvertRealToVirtual(
	DRFolderRef			realFolder)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFolderAddChild
	@abstract	Adds an object reference (either a file or folder) as a child of
				a virtual folder object.
	
				This function only applies to virtual folders.  Real folders
				are considered "leaf nodes" and cannot have children.
	@param		parent					The folder reference that will be the new parent.
	@param		newChild				The object reference that will be the new child.
*/
extern void
DRFolderAddChild(
	DRFolderRef			parent,
	DRFSObjectRef			newChild)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFolderRemoveChild
	@abstract	Removes an object reference (either a file or folder) to make it
				no longer a child of a folder object.

				This function only applies to virtual folders.  Real folders
				are considered "leaf nodes" and cannot have children.
	@param		parent					The folder reference to remove the object from.
	@param		child					The object reference to remove.
*/
extern void
DRFolderRemoveChild(
	DRFolderRef			parent,
	DRFSObjectRef			child)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFolderCountChildren
	@abstract	Returns the number of children of a virtual folder.
	@discussion	This function only applies to virtual folders.  Real folders
				are considered "leaf nodes" and should not be passed into this call.
	@param		folder				The folder reference to query.
	@result		The number of children.
*/
extern UInt32
DRFolderCountChildren(
	const DRFolderRef	folder)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFolderCopyChildren
	@abstract	Returns an array containing the children of a virtual folder.
	@discussion	The order of return is arbitrary -- since the various filesystems being
				generated may have different sorting requirements, there is no one true
				way to sort the children.  The ordering will change only when children
				are added or removed.  You should sort the children according to the needs
				of your display, and in a consistent manner.
				
				This function only applies to virtual folders.  Real folders
				are considered "leaf nodes" and should not be passed into this call.
	@param		folder				The folder reference to query.
	@result		CFArray of the children.
*/
extern CFArrayRef
DRFolderCopyChildren(
	const DRFolderRef	virtualFolder)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* _H_DRContentFolder */

