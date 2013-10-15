/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 * @header DirServicesUtils
 */

#ifndef __DirServicesUtils_h__
#define	__DirServicesUtils_h__	1

// App

#include <stdarg.h>

#include <AvailabilityMacros.h>
#include <DirectoryService/DirServicesTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------

/*!
 * @function dsDataBufferAllocate
 */
tDataBufferPtr	dsDataBufferAllocate		(	tDirReference	inDirReference,
												unsigned long	inBufferSize );

/*!
 * @function dsDataBufferDeAllocate
 */
tDirStatus		dsDataBufferDeAllocate		(	tDirReference	inDirReference,
												tDataBufferPtr	inDataBufferPtr );

//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
// Data Node Routines

//-----------------------------------------------

/*!
 * @function dsDataNodeAllocateBlock
 */
tDataNodePtr	dsDataNodeAllocateBlock		(	tDirReference	inDirReference,
												unsigned long	inDataNodeSize,
												unsigned long	inDataNodeLength,
												tBuffer			inDataNodeBuffer );

/*!
 * @function dsDataNodeAllocateString
 */
tDataNodePtr	dsDataNodeAllocateString	(	tDirReference	inDirReference,
												const char		*inCString );

/*!
 * @function dsDataNodeDeAllocate
 */
tDirStatus		dsDataNodeDeAllocate		(	tDirReference	inDirReference,
												tDataNodePtr	inDataNodePtr );

/*!
 * @function dsDataNodeSetLength
 */
tDirStatus		dsDataNodeSetLength			(	tDataNodePtr	inDataNodePtr,
												unsigned long	inDataNodeLength );

/*!
 * @function dsDataNodeGetLength
 */
unsigned long	dsDataNodeGetLength			(	tDataNodePtr	inDataNodePtr );

/*!
 * @function dsDataNodeGetSize
 */
unsigned long	dsDataNodeGetSize			(	tDataNodePtr	inDataNodePtr );



//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
// Data list Routines
//-----------------------------------------------

/*!
 * @function dsDataListAllocate
 */
tDataListPtr	dsDataListAllocate			(	tDirReference	inDirReference );

/*!
 * @function dsDataListDeAllocate
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsDataListDeAllocate() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using it and instead use --> dsDataListDeallocate()   ( <-lower case 'a' ).
 */
tDirStatus		dsDataListDeAllocate		(	tDirReference	inDirReference,
												tDataListPtr	inDataList,
												dsBool			inDeAllocateNodesFlag );

/*!
 * @function dsDataListDeallocate
 * @discussion Note that if the tDataListPtr is a heap based tDataList rather than
 *		stack based, that you must also call free() to release the memory for the
 *		head of the list after calling dsDataListDeallocate().
 */
tDirStatus		dsDataListDeallocate		(	tDirReference	inDirReference,
												tDataListPtr	inDataList );

//-----------------------------------------------

/*!
 * @function dsGetPathFromList
 */
char*			dsGetPathFromList			(	tDirReference	inDirReference,
												const tDataList	*inDataList,
												const char		*inDelimiter );

/*!
 * @function dsBuildFromPath
 */
tDataListPtr	dsBuildFromPath				(	tDirReference	inDirReference,
												const char		*inPathCString,
												const char		*inPathSeparatorCString );

/*!
 * @function dsBuildListFromPathAlloc
 */
tDirStatus		dsBuildListFromPathAlloc	(	tDirReference	inDirReference,
												tDataListPtr	inDataList,
												const char		*inPathCString,
												const char		*inPathSeparatorCString );


/*!
 * @function dsBuildListFromNodes
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsBuildListFromNodes() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using it and instead use --> dsBuildListFromNodesAlloc().
 */
tDataListPtr	dsBuildListFromNodes		(	tDirReference	inDirReferences,
												tDataNodePtr	in1stDataNodePtr,
												... );

/*!
 * @function dsBuildListFromNodesAlloc
 */
tDirStatus		dsBuildListFromNodesAlloc	(	tDirReference	inDirReferences,
												tDataListPtr	inDataList,
												tDataNodePtr	in1stDataNodePtr,
												... );

/*!
 * @function dsBuildListFromStrings
 */
tDataListPtr	dsBuildListFromStrings		(	tDirReference	inDirReference,
												const char		*in1stCString,
												... );

/*!
 * @function dsBuildListFromStringsAlloc
 */
tDirStatus		dsBuildListFromStringsAlloc	(	tDirReference	inDirReferences,
												tDataListPtr	inDataList,
												const char		*in1stCString,
												... );

/*!
 * @function dsBuildListFromStringsAllocV
 */
tDirStatus		dsBuildListFromStringsAllocV ( tDirReference	inDirRef,
												tDataList		*inDataList,
												const char		*in1stCString,
												va_list			args );

/*!
 * @function dsAppendStringToList
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsAppendStringToList() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using it and instead use --> dsAppendStringToListAlloc().
 */
tDirStatus		dsAppendStringToList		(	tDataListPtr	inDataList,
												const char		* inCString );

/*!
 * @function dsAppendStringToListAlloc
 */
tDirStatus		dsAppendStringToListAlloc	(	tDirReference	inDirReferences,
												tDataListPtr	inDataList,
												const char		* inCString );

//-----------------------------------------------

/*!
 * @function dsDataListGetNodeCount
 */
unsigned long	dsDataListGetNodeCount		(	const tDataList	*inDataList );

/*!
 * @function dsAllocStringsFromList
 * @discussion Provides a char** of the strings contained within a tDataList.
 */
char** dsAllocStringsFromList( tDirReference inDirRef, const tDataList *inDataList )
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
 * @function dsGetDataLength
 */
unsigned long	dsGetDataLength				(	const tDataList	*inDataList );


/*!
 * @function dsDataListInsertNode
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsDataListInsertNode() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using it and instead use --> dsDataListInsertAfter().
 */
tDirStatus		dsDataListInsertNode		(	tDataListPtr	inDataList,
												tDataNodePtr	inAfterDataNode,
												tDataNodePtr	inInsertDataNode );

/*!
 * @function dsDataListInsertAfter
 * @param inNodeIndex One-based index of the existing node to insert the new node after.
 * 		If inNodeIndex is 0, then it is inserted at the head of the list.
 * @discussion The datanode is copied into the datalist.  The caller owns the original
 *		datanode, therefore must deallocate after adding to the list.
 */
tDirStatus		dsDataListInsertAfter		(	tDirReference	inDirReferences,
												tDataListPtr	inDataList,
												tDataNodePtr	inInsertDataNode,
												const unsigned long	inNodeIndex );

/*!
 * @function dsDataListMergeList
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsDataListMergeList() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using it and instead use --> dsDataListMergeListAfter().
 */
tDirStatus		dsDataListMergeList			(	tDataListPtr	inDataList,
												tDataNodePtr	inAfterDataNode,
												tDataListPtr	inMergeDataList );

/*!
 * @function dsDataListMergeListAfter
 */
tDirStatus		dsDataListMergeListAfter	(	tDataListPtr	inTargetList,
												tDataListPtr	inSourceList,
												const unsigned long	inNodeIndex );

/*!
 * @function dsDataListCopyList
 */
tDataListPtr	dsDataListCopyList			(	tDirReference	inDirReference,
												const tDataList	*inDataListSource );

/*!
 * @function dsDataListRemoveNodes
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsDataListRemoveNodes() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using them and instead use --> dsDataListDeleteThisNode()
 */
tDirStatus		dsDataListRemoveNodes		(	tDataListPtr	inDataList,
												tDataNodePtr	in1stDataNode,
												unsigned long	inDeleteCount );

/*!
 * @function dsDataListRemoveThisNode
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsDataListRemoveThisNode() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using them and instead use --> dsDataListDeleteThisNode()
 */
tDirStatus		dsDataListRemoveThisNode	(	tDataListPtr	inDataList,
												unsigned long	inNodeIndex,
												unsigned long	inDeleteCount );

/*!
 * @function dsDataListDeleteThisNode
 */
tDirStatus		dsDataListDeleteThisNode	(	tDirReference	inDirReference,
												tDataListPtr	inDataList,
												unsigned long	inNodeIndex );

/*!
 * @function dsDataListGetNode
 * @discussion Please Note: ******** API Change Soon ********
 * 		dsDataListGetNode() will be soon be obsoleted and no longer supported.
 * 		Please discontinue using it and instead use --> dsDataListGetNodeAlloc().
 */
tDirStatus		dsDataListGetNode			(	tDataListPtr	inDataListPtr,
												unsigned long	inNodeIndex,
												tDataNodePtr	*outDataNode );

/*!
 * @function dsDataListGetNodeAlloc
 */
tDirStatus		dsDataListGetNodeAlloc		(	tDirReference	inDirReference,
												const tDataList	*inDataListPtr,
												unsigned long	inNodeIndex,
												tDataNodePtr	*outDataNode );

//-----------------------------------------------

/*!
 * @function dsAllocAttributeValueEntry
 */
tAttributeValueEntryPtr		dsAllocAttributeValueEntry		(	tDirReference			inDirRef,
																unsigned long			inAttrValueID,
																void				   *inAttrValueData,
																unsigned long			inAttrValueDataLen );

/*!
 * @function dsDeallocAttributeValueEntry
 */
tDirStatus					dsDeallocAttributeValueEntry	(	tDirReference			inDirRef,
																tAttributeValueEntryPtr	inAttrValueEntry );

/*!
 * @function dsDeallocAttributeEntry
 */
tDirStatus					dsDeallocAttributeEntry			(	tDirReference			inDirRef,
																tAttributeEntryPtr		inAttrEntry );

/*!
 * @function dsDeallocRecordEntry
 */
tDirStatus					dsDeallocRecordEntry			(	tDirReference			inDirRef,
																tRecordEntryPtr			inRecEntry );


//-----------------------------------------------

/*!
 * @function dsGetRecordNameFromEntry
 * @param outRecName Used to return the record name to the client. Client is responsible for freeing
 * 		the resulting string.
 */
tDirStatus		dsGetRecordNameFromEntry	(	tRecordEntryPtr inRecEntryPtr, char **outRecName );

/*!
 * @function dsGetRecordTypeFromEntry
 * @param outRecType Used to return the record name to the client. Client is responsible for freeing
 * 		the resulting string.
 */
tDirStatus		dsGetRecordTypeFromEntry	(	tRecordEntryPtr inRecEntryPtr, char **outRecType );

/*!
 * @function dsParseAuthAuthority
 * Pass in a complete authentication authority attribute
 * format is version;tag;data
 * retrieve version, tag, and data as separate strings
 * Memory for the char** parameters is the responsibility of the client
 * and can be cleaned up using free().
 */
tDirStatus		dsParseAuthAuthority		(   const char *inAuthAuthority, char **outVersion, char **outAuthTag, char **outAuthData ) 
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
 * @function dsCopyDirStatusName
 * Pass in the tDirStatus enum and receive the string of the enum name.
 * Memory for the char* is the responsibility of the client
 * and can be cleaned up using free().
 */
char*			dsCopyDirStatusName			(   long inDirStatus ) 
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif
