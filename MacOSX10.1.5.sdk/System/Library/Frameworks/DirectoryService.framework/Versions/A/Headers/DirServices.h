/*
	File:		DirServices.h

	Contains:	xxx put contents here xxx

	Copyright:	© 1998-2000 by Apple Computer, Inc., all rights reserved.

	NOT_FOR_OPEN_SOURCE <to be reevaluated at a later time>
*/

/*!
 * @header DirectoryServices
 * Directory Services introduction text.
 */

#ifndef __DirServices_h__
#define __DirServices_h__

// App
#include <DirectoryService/DirServicesTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------
// Directory Services Calls

#pragma mark Calls

/*!
 * @function dsOpenDirService
 * @discussion Opens Directory Services API reference. Must be called before any other
 * 		Directory Services API calls because this reference is needed for any other call.
 * @param outDirReference reference to use in subsequent Directory Services API calls
 */
tDirStatus	dsOpenDirService			(	tDirReference	   *outDirReference	);

/*!
 * @function dsCloseDirService
 * @param inDirReference Directory Services API reference to be closed
 */
tDirStatus	dsCloseDirService			(	tDirReference		inDirReference		);


/*!
 * @function dsAddChildPIDToReference
 */
tDirStatus dsAddChildPIDToReference		(	tDirReference		inDirRef,
											long				inValidChildPID,
											unsigned long		inValidAPIReferenceToGrantChild );

/*!
 * @function dsIsDirServiceRunning
 */
tDirStatus dsIsDirServiceRunning		( );

//-------------------------------------------------------------------------
// register custom allocate/deallocate routines MacOS Classic Applications Only
tDirStatus	dsRegisterCustomMemory		(	tDirReference		inDirReference,
											fpCustomAllocate	inCustomAllocate,
											fpCustomDeAllocate	inCustomDeAllocate,
											tClientData			inClientData		);
	
tDirStatus	dsGetCustomAllocate			(	tDirReference		inDirReference,
											fpCustomAllocate	*outCustomAllocate,
											fpCustomDeAllocate	*outCustomDeAllocate,
											tClientData			*outClientData		);

tDirStatus	dsUnRegisterCustomMemory	(	tDirReference		inDirReference,
											fpCustomAllocate	inCustomAllocate,
											fpCustomDeAllocate	inCustomDeAllocate,
											tClientData			inClientData		);

//------------------------------------------------------------
// register custom thread routines MacOS Classic Applications Only
tDirStatus	dsRegisterCustomThread		(	tDirReference			inDirReference,
											fpCustomThreadBlock		inCustomBlock,
											fpCustomThreadUnBlock	inCustomUnBlock,
											fpCustomThreadYield		inCustomYield,
											tClientData				inClientData	);

tDirStatus	dsGetCustomThread			(	tDirReference			inDirReference,
											fpCustomThreadBlock		*outCustomBlock,
											fpCustomThreadUnBlock	*outCustomUnBlock,
											fpCustomThreadYield		*outCustomYield,
											tClientData				*outClientData	);

tDirStatus	dsUnRegisterCustomThread	(	tDirReference			inDirReference,
											fpCustomThreadBlock		inCustomBlock,
											fpCustomThreadUnBlock	inCustomUnBlock,
											fpCustomThreadYield		inCustomYield,
											tClientData				inClientData	);

//-----------------------------------------------

/*! * @function dsGetDirNodeCount * @discussion Get the count of the total number of directory nodes in the system. * @param inDirReference Directory reference established with dsOpenDirService. * @param outDirectoryNodeCount Contains count of the total number of directory nodes.
 */tDirStatus	dsGetDirNodeCount		(	tDirReference	inDirReference,
										unsigned long	*outDirectoryNodeCount	);

/*!
 * @function dsGetDirNodeCountWithInfo
 * @discussion Get the count of the total number of DirNodes in the Directory System with change information
 * 		ie. a token gets returned with a different value if there has been a change in the registered nodes
 * 		so the client can retain the first token and compare with the second to see if any registered nodes have changed
 * @param inDirReference Directory Reference Established with dsOpenDirService
 * @param outDirectoryNodeCount Contains count of the total number of nodes in the directory
 * @param outDirectoryNodeChangeToken Contains token that changes upon any registered node changes.
 */
tDirStatus	dsGetDirNodeCountWithInfo		(	tDirReference	inDirReference,
										unsigned long	*outDirectoryNodeCount,
										unsigned long	*outDirectoryNodeChangeToken	);

/*!
 * @function dsGetDirNodeList
 * @discussion Fill a buffer with the names of all the directory nodes.
 * @param inDirReference Directory reference established with dsOpenDirService
 * @param inOutDataBufferPtr Contains a client allocated buffer to store results..data is extracted with dsGetDirNodeName
 * @param outDirNodeCount Number of directory node names contained in dataBuffer
 * @param inOutContinueData Pointer to a tContextData variable, if (*inOutCountinueData == NULL) there is no more data
 * 		otherwise can be used in a 2nd call to the same routine to get the remainder of the directory node list.
 * 		if client does not use  if (*inOutCountinueData != NULL) and the client doesn't wish to continue
 * 		then dsReleaseContinueData should be called to clean up..
 */
tDirStatus	dsGetDirNodeList		(	tDirReference	inDirReference,
										tDataBufferPtr	inOutDataBufferPtr,
										unsigned long	*outDirNodeCount,
										tContextData	*inOutContinueData		);

/*!
 * @function dsReleaseContinueData
 * @discussion If continue data from dsGetDirNodeList or any other Directory Services
 * 		function is non-NULL, then call this routine to release the continue data
 * 		if the client chooses not to continue the directory node listing or other operation.
 * @param inDirReference Directory reference established with dsOpenDirService
 * @param inContinueData Pointer to a tContextData variable which will be cleaned up by Directory Services
 */
tDirStatus	dsReleaseContinueData	(	tDirReference	inDirReference,	
										tContextData	inContinueData		);

/*!
 * @function dsFindDirNodes
 * @discussion Find directory nodes matching a certain pattern.
 * @param inDirReference Directory reference established with dsOpenDirService
 * @param inOutDataBufferPtr Contains a client allocated buffer to store results. Data is extracted with dsGetDirNodeName.
 * @param inNodeNamePattern A tDataList pointer, which contains the pattern to be matched.
 * @param inPatternMatchType What type of match to perform on inNodeNamePattern.
 * 		Valid values for this are: 	eDSExact, eDSStartsWith, eDSEndsWith, eDSContains.
 * 		Other match types will return an error.
 * @param outDirNodeCount Number of items in the client buffer.
 * @param inOutContinueData Pointer to a tContextData variable, if (*inOutCountinueData == NULL) there is no more data
 * 		otherwise can be used in a 2nd call to the same routine to get the remainder of the directory node list.
 * 		if client does not use  if (*inOutCountinueData != NULL) and the client doesn't wish to continue
 * 		then dsReleaseContinueData should be called to clean up.
 */
tDirStatus	dsFindDirNodes			(	tDirReference		inDirReference,
										tDataBufferPtr		inOutDataBufferPtr,
										tDataListPtr		inNodeNamePattern,
										tDirPatternMatch	inPatternMatchType,
										unsigned long		*outDirNodeCount,
										tContextData		*inOutContinueData );

										
/*!
 * @function dsGetDirNodeName
 * @discussion Parse the return Buffer from dsFindDirNodes or dsGetDirNodeList
 * 		and build a tDataList representing the directory node's name.
 * @param inDirReference Directory reference established with dsOpenDirService
 * @param inOutDataBuffer A buffer containing all the directory node names from
 * 		dsGetDirNodeList or dsFindDirNodes
 * @param inDirNodeIndex One-based index of directory node name to fetch/build.
 * @param inOutDataList Address of tDataListPtr that is built by this call.
 * 		The client is responsible for disposing of it with dsDataListDeAllocate.
 */
tDirStatus	dsGetDirNodeName		(	tDirReference	inDirReference,
										tDataBufferPtr	inOutDataBuffer,
										unsigned long	inDirNodeIndex,
										tDataListPtr	*inOutDataList			);

/*!
 * @function dsOpenDirNode
 * @discussion Establish a session for a particular directory node.
 * @param inDirReference Directory reference established with dsOpenDirService.
 * @param inDirNodeName Directory node name to open. Should be split into path
 * 		components, for example as a result of dsBuildListFromPath
 * @param outDirNodeReference Valid call with noErr, results in a directory node session reference.
 * 		This reference represents the client's session context for the contents of the given directory node.
 */
tDirStatus	dsOpenDirNode				(	tDirReference	inDirReference,
											tDataListPtr	inDirNodeName,
											tDirNodeReference	*outDirNodeReference	);

/*!
 * @function dsCloseDirNode
 * @discussion Tear down a directory node session.
 * @param inDirNodeReference Directory node reference obtained from dsOpenDirNode
 */
tDirStatus	dsCloseDirNode				(	tDirNodeReference	inDirNodeReference		);


/*!
 * @function dsGetDirNodeInfo
 * @discussion Get information about a directory node: authentication methods, unique ID's,
 * 		ICON information, access controls, record types contained in this node, plug-in information,
 * 		directory node/type/signature.
 * @param inDirNodeReference Directory node reference obtained from dsOpenDirNode.
 * @param inDirNodeInfoTypeList tDataList containing the types of requested data.
 * @param inOutDataBuffer Client-allocated buffer to hold the data results.
 * @param inAttributeInfoOnly This flag is set to true if the client wants attribute info only,
 * 		not attribute values.
 * @param outAttributeInfoCount A count of the number of data types present in the DataBuffer.
 * @param inOutContinueData Pointer to a tContextData variable. If (*inOutCountinueData == NULL)
 * 		there is no more data. Otherwise can be used in the next call to the same routine to get
 * 		the remainder of the information. If client does not use non-NULL continue data,
 * 		then dsReleaseContinueData should be called to clean up.
 */
tDirStatus	dsGetDirNodeInfo		(	tDirNodeReference	inDirNodeReference,
										tDataListPtr		inDirNodeInfoTypeList,
										tDataBufferPtr		inOutDataBuffer,
										dsBool				inAttributeInfoOnly,
										unsigned long		*outAttributeInfoCount,
										tAttributeListRef	*outAttributeListRef,
										tContextData		*inOutContinueData			);

/*!
 * @function dsGetRecordList
 * @discussion Get a list of records, optionally: by name, by type, with or without attribute info,
 * 		with or without attribute value data.
 * @param inDirNodeReference Directory node reference obtained from dsOpenDirNode.
 * @param inOutDataBuffer A client-allocated buffer to hold the data results.
 * @param inRecordNameList A tDataList of Record names to be matched.
 * 		Pass NULL if there are no record names to be matched.
 * @param inPatternMatchType How is the pattern matched for the inRecordNameList.
 * 		Ignored if inRecordNameList is NULL.
 * @param inRecordTypeList What record types do we want returned? Pass NULL for all record types.
 * @param inAttributeTypeList What type of attributes do we want for each record.
 * 		NULL for all types for each record.
 * @param inAttributeInfoOnly Do we want attribute information only, or do we also want attribute values.
 * @param inOutRecordEntryCount How many record entries are there in the client buffer.
 * 		However, also a limit of the maximum records returned as provided by the client.
 * 		If zero or less, then assuming no limit on number of records to be returned.
 * @param inOutContinueData Pointer to a tContextData variable. If (*inOutCountinueData == NULL)
 * 		there is no more data. Otherwise can be used in the next call to the same routine to get
 * 		the remainder of the information. If client does not use and continue data is non-NULL
 * 		then dsReleaseContinueData should be called to clean up.
 */
tDirStatus	dsGetRecordList		(	tDirNodeReference		inDirNodeReference,
									tDataBufferPtr			inOutDataBuffer,
									tDataListPtr			inRecordNameList,
									tDirPatternMatch		inPatternMatchType,
									tDataListPtr			inRecordTypeList,
									tDataListPtr			inAttributeTypeList,
									dsBool					inAttributeInfoOnly,
									unsigned long			*inOutRecordEntryCount,
									tContextData			*inOutContinueData		);
/*!
 * @function dsGetRecordEntry
 * @discussion Get a record entry from a buffer.
 * @param inDirNodeReference Directory node reference obtained from dsOpenDirNode.
 * @param inOutDataBuffer A client-allocated buffer to hold the data results.
 */
tDirStatus	dsGetRecordEntry	(	tDirNodeReference	inDirNodeReference,
									tDataBufferPtr		inOutDataBuffer,
									unsigned long		inRecordEntryIndex,

									tAttributeListRef	*outAttributeListRef,
									tRecordEntryPtr		*outRecordEntryPtr		);

/*!
 * @function dsGetAttributeEntry
 * @discussion Get an attribute entry from a buffer.
 */
tDirStatus	dsGetAttributeEntry	(	tDirNodeReference		inDirNodeReference,
									tDataBufferPtr			inOutDataBuffer,
									tAttributeListRef		inAttributeListRef,
									unsigned long			inAttributeInfoIndex,
									tAttributeValueListRef	*outAttributeValueListRef,
									tAttributeEntryPtr		*outAttributeInfoPtr			);

/*!
 * @function dsGetAttributeValue
 * @discussion Get an attribute value from a buffer.
 */
tDirStatus	dsGetAttributeValue			(	tDirNodeReference		inDirNodeReference,
											tDataBufferPtr			inOutDataBuffer,
											unsigned long			inAttributeValueIndex,
											tAttributeValueListRef	inAttributeValueListRef,
											tAttributeValueEntryPtr	*outAttributeValue		);

/*!
 * @function dsCloseAttributeList
 */
tDirStatus	dsCloseAttributeList		(	tAttributeListRef		inAttributeListRef	);

/*!
 * @function dsCloseAttributeValueList
 */
tDirStatus	dsCloseAttributeValueList	(	tAttributeValueListRef	inAttributeValueListRef	);


/*!
 * @function dsOpenRecord
 */
tDirStatus	dsOpenRecord						(	tDirNodeReference	inDirNodeReference,
													tDataNodePtr		inRecordType,
													tDataNodePtr		inRecordName,
													tRecordReference	*outRecordReference	);

/*!
 * @function dsGetRecordReferenceInfo
 */
tDirStatus	dsGetRecordReferenceInfo			(	tRecordReference	inRecordReference,
													tRecordEntryPtr		*outRecordInfo			);

/*!
 * @function dsGetRecordAttributeInfo
 */
tDirStatus	dsGetRecordAttributeInfo			(	tRecordReference	inRecordReference,
													tDataNodePtr		inAttributeType,											
													tAttributeEntryPtr	*outAttributeInfoPtr	);

/*!
 * @function dsGetRecordAttributeValueByID
 */
tDirStatus	dsGetRecordAttributeValueByID		(	tRecordReference		inRecordReference,
													tDataNodePtr			inAttributeType,											
													unsigned long			inValueID,
													tAttributeValueEntryPtr	*outEntryPtr		);
/*!
 * @function dsGetRecordAttributeValueByIndex
 */
tDirStatus	dsGetRecordAttributeValueByIndex	(	tRecordReference		inRecordReference,
													tDataNodePtr			inAttributeType,											
													unsigned long			inValueIndex,
													tAttributeValueEntryPtr	*outEntryPtr		);

/*!
 * @function dsFlushRecord
 */
tDirStatus	dsFlushRecord						(	tRecordReference		inRecordReference	);

/*!
 * @function dsCloseRecord
 */
tDirStatus	dsCloseRecord						(	tRecordReference		inRecordReference	);


/*!
 * @function dsSetRecordName
 */
tDirStatus	dsSetRecordName			(	tRecordReference	inRecordReference,
										tDataNodePtr		inNewRecordName			);
										
/*!
 * @function dsSetRecordType
 */
tDirStatus	dsSetRecordType			(	tRecordReference	inRecordReference,
										tDataNodePtr		inNewRecordType			);

/*!
 * @function dsDeleteRecord
 */
tDirStatus	dsDeleteRecord			(	tRecordReference	inRecordReference		);

/*!
 * @function dsCreateRecord
 */
tDirStatus	dsCreateRecord			(	tDirNodeReference		inDirNodeReference,
										tDataNodePtr			inRecordType,
										tDataNodePtr			inRecordName		);

/*!
 * @function dsCreateRecordAndOpen
 */
tDirStatus	dsCreateRecordAndOpen	(	tDirNodeReference		inDirNodeReference,
										tDataNodePtr			inRecordType,
										tDataNodePtr			inRecordName,
										tRecordReference	   *outRecordReference	);

/*!
 * @function dsAddAttribute
 * @discussion Add an attribute type to a record.
 */
tDirStatus	dsAddAttribute			(	tRecordReference		inRecordReference,
										tDataNodePtr			inNewAttribute,
										tAccessControlEntryPtr	inNewAttributeAccess,
										tDataNodePtr			inFirstAttributeValue	);

/*!
 * @function dsRemoveAttribute
 */
tDirStatus	dsRemoveAttribute		(	tRecordReference		inRecordReference,
										tDataNodePtr			inAttribute			);

/*!
 * @function dsAddAttributeValue
 * @discussion Add data to a record.
 */
tDirStatus	dsAddAttributeValue		(	tRecordReference		inRecordReference,
										tDataNodePtr			inAttributeType,
										tDataNodePtr			inAttributeValue			);

/*!
 * @function dsRemoveAttributeValue
 */
tDirStatus	dsRemoveAttributeValue	(	tRecordReference		inRecordReference,
										tDataNodePtr			inAttributeType,
										unsigned long			inAttributeValueID			);

/*!
 * @function dsSetAttributeValue
 */
tDirStatus	dsSetAttributeValue		(	tRecordReference		inRecordReference,
										tDataNodePtr			inAttributeType,
										tAttributeValueEntryPtr	inAttributeValuePtr			);
										
//-----------------------------------------------
//
//	Do an authentication session with the given authentication type
//

/*!
 * @function dsDoDirNodeAuth
 * @discussion When a authentication is successful the error code 'eDSNoErr' is returned
 * 		and the outAuthStepDataResponse parameter will contain a correctly formed
 * 		kDS1AttrAuthCredential value.  This AuthCredential can be used for future
 * 		authentications for this and other directory nodes in the directory system.
 * 		Not all directory nodes will support authenticating in this manner, but most
 * 		should.  In addition the current kDS1AttrAuthCredential value can always be
 * 		obtained via dsGetDirNodeInfo call with kDS1AttrAuthCredential as one of the
 * 		requested attributes.  Directory Nodes that support using a kDS1AttrAuthCredential
 * 		will list DSAuthCredential as a support authentication method.  Support
 * 		authentication methods can be determined by calling dsGetDirNodeInfo and requesting
 * 		the kDSNAttrAuthMethod attribute for that directory node.
 * 		NOTE: it is important to note that while some Directory Nodes may support
 * 		the attempt of using a kDS1AttrAuthCredential to authenticate, when the Directory
 * 		Node plug-in decodes the Credential the authentication attempt may still fail
 * 		for plug-in specific reasons (the plug-in may find the level of original authentication
 * 		insufficient for it's requirements or configuration, or the credential may have expired
 * 		and is no longer valid).  In addition when using a kDS1AttrAuthCredential to authentication
 * 		to a different directory node than the original kDS1AttrAuthCredential was generated, the
 * 		level of access granted by the directory node plug-in may not match the level in the
 * 		original directory node.  Access granted to the contents of a directory node is entirely
 * 		at the descretion of the directory node plug-in and the directory system it represents.
 * @param inDirNodeAuthOnlyFlag Indicates if the client wishes to use
 * 		the results of this authentication process as their identity for this directory session
 * 		(inDirNodeReference) for directory node access authorization.
 * 		If the flag value is "false", then at the completion of the auth process both the
 * 		Directory Services API and the Plug-in should use this "identity" to grant
 * 		or deny access for all future directory service calls.
 * 		If the flag value is "true", then at the completion of of the auth process no identity
 * 		information will be used by the directory services or Plug-in for authorization purposes.
 * 		A file server just wishing to authenticate a user, but not change how/who it is accessing
 * 		the directory as would set this parameter to "true".
 */
tDirStatus dsDoDirNodeAuth			(	tDirNodeReference	inDirNodeReference,
										tDataNodePtr		inDirNodeAuthName,
										dsBool				inDirNodeAuthOnlyFlag,
										tDataBufferPtr		inAuthStepData,
										tDataBufferPtr		outAuthStepDataResponse,
										tContextData		*inOutContinueData			);

/*!
 * @function dsDoAttributeValueSearch
 * @discussion Use dsGetRecordEntry, dsGetAttributeEntry, and dsGetAttributeValue
 * 		to parse the inOutDataBuffer parameter for results.
 * @param inOutDataBuffer A client-allocated buffer to hold the data results.
 * @param inRecordTypeList The list of record types to search within.
 * @param inAttributeType What type of attributes we want for each record.
 * @param inOutMatchRecordCount How many records we found that met the match criteria.
 * 		However, also a limit of the maximum records returned as provided by the client.
 * 		If zero or less, then assuming no limit on number of records to be returned.
 */
tDirStatus	dsDoAttributeValueSearch	(	tDirNodeReference	inDirNodeReference,
											tDataBufferPtr		inOutDataBuffer,
											tDataListPtr		inRecordTypeList,
											tDataNodePtr		inAttributeType,
											tDirPatternMatch	inPatternMatchType,
											tDataNodePtr		inPattern2Match,
											unsigned long		*inOutMatchRecordCount,
											tContextData		*inOutContinueData			);



/*!
 * @function dsDoAttributeValueSearchWithData
 * @param inOutDataBuffer A client-allocated buffer to hold the data results.
 * @param inRecordTypeList The type of records to search for.
 * @param inAttributeMatchType Which attribute we are to match on.
 * @param inPatternMatchType Pattern match.
 * @param inPatternToMatch Value to match for the above attribute.
 * @param inAttributeTypeRequestList What type of attributes do we want for each record.
 * @param inAttributeInfoOnly Do we want attribute information only, or values too.
 * @param inOutMatchRecordCount How many records we found that met the match criteria.
 * 		However, also a limit of the maximum records returned as provided by the client.
 * 		If zero or less, then assuming no limit on number of records to be returned.
 */
tDirStatus	dsDoAttributeValueSearchWithData	(	tDirNodeReference	inDirNodeReference,
													tDataBufferPtr		inOutDataBuffer,
													tDataListPtr		inRecordTypeList,
													tDataNodePtr		inAttributeMatchType,
													tDirPatternMatch	inPatternMatchType,
													tDataNodePtr		inPatternToMatch,
													tDataListPtr		inAttributeTypeRequestList,
													dsBool				inAttributeInfoOnly,
													unsigned long		*inOutMatchRecordCount,
													tContextData		*inOutContinueData			);

/*!
 * @function dsDoPlugInCustomCall
 * @discussion Used for custom direct communications with plugs-ins.
 */
tDirStatus	dsDoPlugInCustomCall		(	tDirNodeReference	inDirNodeReference,
											unsigned long	inCustomRequestCode,
											tDataBufferPtr	inCustomRequestData,
											tDataBufferPtr	outCustomRequestResponse	);
											

/*!
 * @function dsVerifyDirRefNum
 * @discussion Verify an existing tDirReference.
 */
tDirStatus		dsVerifyDirRefNum			(	tDirReference inDirReference	);

#ifdef __cplusplus
}
#endif

#endif
