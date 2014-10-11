/*
	File:		DirServicesUtils.h

	Contains:	xxx put contents here xxx

	Copyright:	© 1998-2000 by Apple Computer, Inc., all rights reserved.

	NOT_FOR_OPEN_SOURCE <to be reevaluated at a later time>
*/

/*!
 * @header DirectoryServices
 * Directory Services introduction text.
 */

#ifndef __DirServicesUtils_h__
#define	__DirServicesUtils_h__	1

// App

#include <stdarg.h>

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

#ifdef __cplusplus
}
#endif

#endif
