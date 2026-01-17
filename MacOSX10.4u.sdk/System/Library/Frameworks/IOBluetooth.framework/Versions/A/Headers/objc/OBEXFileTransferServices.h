/*
	Contains: 		OBEX File Transfer Services object for FTP and ObjectPush operations
	Copyright:		(c) 2004 by Apple Computer, Inc., all rights reserved.
*/


#ifdef	__cplusplus
	extern "C" {
#endif
	
	

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif
		
#import <IOBluetooth/OBEX.h>
#import <IOBluetooth/objc/IOBluetoothOBEXSession.h>

#ifdef __OBJC__

//====================================================================================================================
//	OBEXFileTransferServices
//====================================================================================================================
/*!
    @class			OBEXFileTransferServices
    @abstract		Implements advanced OBEX operations in addition to simple PUT and GET.
    @discussion		All operations are asynchronous and callback over a respective delegate 
					method if the initial return value is successful.
*/

@interface OBEXFileTransferServices : NSObject
{

@private

	id							mOBEXFileGet;
	id							mOBEXFilePut;
	
	id							mFolderListingFileRef;
	int							mActionCommand;
	int							mSavedCommand;
	NSString *					mActionArgument1;
	NSString *					mActionArgument2;
	NSString *					mActionArgument3;
	NSString *					mCurrentRemoteDirectory;

	// Misc status info.
	
	BOOL						mActionInProgress;
	BOOL						mWeOpenedTheOBEXConnection;
	BOOL						mHasTargetHeader;
	
	// Delegate stuff.

	id							mDelegate;
	
	// Activity timer.
	
	BOOL						mAbortedByOwner;
	BOOL						mWeAreAborting;
	NSTimer*					mInactivityTimer;

	// OBEX Session stuff.

	IOBluetoothOBEXSession*		mOBEXSession;
	OBEXMaxPacketLength			mMaxPacketLength;
	OBEXError					mConnectionID;
	
	// Progress stuff.
	
	id							mPUTProgress;
	id							mGETProgress;
			
	void *						mReserved1;
	void *						mReserved2;
 }


//------------------------------------------
// Object construction.
//------------------------------------------
/*!
	@method			withOBEXSession:
    @abstract		Create a new OBEXFileTransferServices object
    @discussion		This object must be constructed with a valid IOBluetoothOBEXSession. The given 
					IOBluetoothOBEXSession does not need to be connected to the remote server.  
					This module can be manually connected through the connect() method. 
	@param			inOBEXSession A valid IOBluetoothOBEXSession
	@result			A newly created OBEXFileTransferServices object on success, nil on failure
*/
+ (OBEXFileTransferServices*) withOBEXSession: (IOBluetoothOBEXSession*) inOBEXSession;


/*!
	@method			initWithOBEXSession:
	@abstract		Create a new OBEXFileTransferServices object
	@discussion		This object must be constructed with a valid IOBluetoothOBEXSession. The given 
					IOBluetoothOBEXSession does not need to be connected to the remote server.  
					This module can be manually connected through the connect() method.
	@param			inOBEXSession A valid IOBluetoothOBEXSession
	@result			A newly created OBEXFileTransferServices object on success, nil on failure
*/
- (id) initWithOBEXSession:(IOBluetoothOBEXSession*)inOBEXSession;



#pragma mark -
#pragma mark ¥ Accessors ¥
//------------------------------------------
// Accessors
//------------------------------------------

/*!
	@method     setDelegate:
	@abstract   Manually set the delegate
	@discussion Manually set the delegate
	@param		inDelegate An object that implements the methods defined in th 
				OBEXFileTransferServicesDelegate category
*/
- (void) setDelegate: (id) inDelegate;
	
/*!
	@method     delegate
	@abstract   Get the delegate
	@discussion Get the delegate
	@result		The delegate object
*/
- (id) delegate;


/*!
	@method     currentPath
	@abstract   Get the remote current directory path during an FTP session
	@discussion This path is changed with each path-specific command called on OBEXFileTransferServices.
	@result		The current path being browsed over FTP
*/
- (NSString*) currentPath;

/*!
	@method     isBusy
	@abstract   Get the action state of the module
	@discussion The actionInProgress flag is set internally when action methods are called 
				on this module and is reset when the operation has completed
	@result		Success or failure code.
*/
- (BOOL) isBusy;

/*!
	@method     isConnected
	@abstract   Get the connected state of this module.
	@discussion Asks the OBEXSession that was passed to it on creation if it has an open OBEX connection
	@result		Success or failure code.
*/
- (BOOL) isConnected;





#pragma mark -
#pragma mark ¥ Actions ¥
//------------------------------------------
// Actions
//------------------------------------------

/*!
	@method     connectToFTPService
	@abstract   Connect to a remote device for FTP operations
	@discussion If the OBEXSession given to OBEXFileTransferServices on creation is not connected it
				can be manually connected through this method. 
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXSessionAlreadyConnectedError, kOBEXNoResourcesError
				initially.  Further results returned through the fileTransferServicesConnectionComplete:
				delegate method if initially successful.
*/
- (OBEXError) connectToFTPService;

/*!
    @method     connectToObjectPushService
    @abstract   Connect to a remote device for ObjectPush operations.
				Most of the FTP functionality of this object will be disabled.
    @discussion If the OBEXSession given to OBEXFileTransferServices on creation is not connected it
				can be manually connected through this method. 
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXSessionAlreadyConnectedError, kOBEXNoResourcesError
				initially.  Further results returned through the fileTransferServicesConnectionComplete: 
				delegate method if initially successful.
*/
- (OBEXError) connectToObjectPushService;


/*!
    @method     disconnect
    @abstract   Disconnect from the remote device
    @discussion The user can manually disconnect the OBEXSession from the remote device if they want
				to.  This object will disconnect the OBEXSession at release only if it was responsible 
				for opening the connection via a connect method on this object.
	@result		kOBEXSuccess, kOBEXSessionNotConnectedError, or kOBEXSessionBusyError initially. Further results 
				returned through the fileTransferServicesDisconnectionComplete: delegate method if initially successful.
*/
- (OBEXError) disconnect;

/*!
    @method     changeCurrentFolderRoot
    @abstract   Asynchronously change to the remote root directory
    @discussion Equivalent to 'cd ~/'
	@result		kOBEXSuccess or kOBEXSessionBusyError initially.  Further results
				returned through the fileTransferServicesPathChangeComplete: delegate method if initially successful.
*/
- (OBEXError) changeCurrentFolderToRoot;

/*!
    @method     changeCurrentFolderBackward
    @abstract   Change to the directory above the current level if not at the root
    @discussion Equivalent to 'cd ..' only if remote path is not already at root.  
	@result		kOBEXSuccess or kOBEXSessionBusyError initially. Further results
				returned through the fileTransferServicesPathChangeComplete: delegate method if initially successful.
*/
- (OBEXError) changeCurrentFolderBackward;

/*!
    @method     changeCurrentFolderForwardToPath:
    @abstract   Change the remote path
    @discussion Equivalent to 'cd dirName'.  
	@param		inDirName The name of the remote folder to be set as current
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError initially. Further results
				returned through the fileTransferServicesPathChangeComplete: delegate method if initially successful.
*/
- (OBEXError) changeCurrentFolderForwardToPath: (NSString*) inDirName;

/*!
    @method     createFolder:
    @abstract   Create a folder on the remote target
    @discussion Equivalent to 'mkdir dirName'.  
	@param		inDirName The name of the folder to be created
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError initially. 
				Further results returned through the fileTransferServicesCreateFolderComplete delegate method
				if initially successful.
*/
- (OBEXError) createFolder: (NSString*) inDirName;

/*!
    @method     removeItem:
    @abstract   Remove a remote item.
    @discussion Not supported for use on Apple computer targets  
	@param		inItemName The name of the remote item to be removed
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError initially.  
				Further results returned through the fileTransferServicesRemoveItemComplete: delegate method 
				if initially successful.
*/					
- (OBEXError) removeItem: (NSString*) inItemName;

/*!
    @method     retrieveFolderListing
    @abstract   Get a remote directory listing
    @discussion Equivalent to 'ls'.  
	@result		kOBEXSuccess or kOBEXSessionBusyError initially.  Further results returned through 
				the fileTransferServicesRetrieveFolderListingComplete: delegate method if initially successful.
*/
- (OBEXError) retrieveFolderListing;

/*!
    @method     sendFile:
    @abstract   Put a local file to the remote target
    @discussion Equivalent to 'mv inLocalFilePath remoteCurrentPath'.
	@param		inLocalPathAndName The name and path of the file to be sent an instance of OBEXFilePut.  
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError initially. Further 
				results returned through the fileTransferServicesSendComplete: and 
				fileTransferServicesSendProgress: delegate methods if initially successful.
*/
- (OBEXError) sendFile: (NSString*) inLocalPathAndName;

/*!
    @method     copyRemoteFile: toLocalPath:
    @abstract   Copy a remote file to a local path
    @discussion Equivalent to 'cp remotePath/remoteFileName localPathAndName'.
	@param		inRemoteFileName The name of the remote file to get
	@param		inLocalPathAndName The path and name of where the received file will go
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError. initially.  Further 
				results returned through the fileTransferServicesGetComplete: and 
				fileTransferServicesGetProgress: delegate methods if initially successful.
*/
- (OBEXError) copyRemoteFile: (NSString*) inRemoteFileName
				 toLocalPath: (NSString*) inLocalPathAndName;

/*!
	@method     sendData: type: name:
	@abstract   Send data to a remote target
	@discussion Use this method when you have file data to send but not file to read from.
	@param		inData The data to be sent
	@param		inType The type of the data to be sent that will used in the OBEX type header.  
				This argument is optional. 
	@param		inName The name of the file that the data can be referenced as.
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError initially. Further 
				results returned through the fileTransferServicesSendComplete: and 
				fileTransferServicesSendProgress: delegate methods if initially successful.
*/
- (OBEXError) sendData:(NSData*)inData
				  type:(NSString*)inType
				  name:(NSString*)inName;

/*!
	@method     getDefaultVCard:
	@abstract   Get the remote default VCard, if its supported
	@discussion Some devices such as cellphones and computers support default VCards
	@param		inLocalPathAndName The path and name of where the received file will go
	@result		kOBEXSuccess, kOBEXSessionBusyError, or kOBEXBadArgumentError. initially.  Further 
				results returned through the fileTransferServicesGetComplete: and 
				fileTransferServicesGetProgress: delegate methods if initially successful.
*/
- (OBEXError) getDefaultVCard:(NSString*) inLocalPathAndName;

/*!
    @method     abort
    @abstract   Abort the current operation
    @discussion Attempts send an abort request to the remote device.  Returns OBEXFileTransferServices to an
				idle state, though the state of the remote device is not guaranteed.
	@result		kOBEXSuccess, or kOBEXGeneralError if no command is in progress. ABORT 
				commands can only be sent on our turn, meaning we may have to timeout if the
				target side never responds to the command in progress.  In that case this object
				will call back with a status of kOBEXTimeoutError and an error. Further results
				returned through the fileTransferServicesAbortComplete: delegate method if initially successful.
*/
- (OBEXError) abort;


@end



#pragma mark -
#pragma mark ¥ Delegate Interface ¥
//====================================================================================================================
//  Delegate Methods
//====================================================================================================================
@interface NSObject (OBEXFileTransferServicesDelegate)

#pragma mark -
#pragma mark Progress Keys
//------------------------------------------
//  Progress Keys
//------------------------------------------
//  These keys are used with the NSDictionary returned from the fileTransferServicesPutProgress:
// and fileTransferServicesGetProgress: delegate methods
//
extern CFStringRef kFTSProgressBytesTransferredKey;	// int
extern CFStringRef kFTSProgressBytesTotalKey;		// int
extern CFStringRef kFTSProgressPrecentageKey;		// float
extern CFStringRef kFTSProgressEstimatedTimeKey;	// double
extern CFStringRef kFTSProgressTimeElapsedKey;		// int
extern CFStringRef kFTSProgressTransferRateKey;		// float

#define kFTSProgressPercentageKey	kFTSProgressPrecentageKey

#pragma mark -
#pragma mark Listing Keys
//------------------------------------------
//  Listing Keys
//------------------------------------------
//  These keys are used with the array of NSDictionary's returned through the delegate method
// fileTransferServicesGetListingComplete: after calling getFolderListing.  
//
extern CFStringRef kFTSListingNameKey;		// NSString
extern CFStringRef kFTSListingTypeKey;		// FTSFileType
extern CFStringRef kFTSListingSizeKey;		// int


//  the int values matching the kFTSListingTypeKey value
//
enum  FTSFileType
{
	kFTSFileTypeFolder = 1,
	kFTSFileTypeFile   = 2
};



#pragma mark -
#pragma mark Delegate Methods
//------------------------------------------
//  Delegate Methods
//------------------------------------------

/*!
	@method			fileTransferServicesConnectionComplete:error:
	@abstract		The delegate method that corresponds to the connect method
	@discussion		inError will either be kOBEXSuccess or it will be an error returned by the OBEX Session
*/
- (void) fileTransferServicesConnectionComplete:(OBEXFileTransferServices*)inServices	error:(OBEXError)inError;

/*!
	@method			fileTransferServicesDisconnectionComplete:error:
	@abstract		The delegate method that corresponds to the disconnect method
	@discussion		inError will be kOBEXSuccess on success.  This method will also be called if the connection
					is lost to the server.  Possible error codes include kOBEXSessionTransportDiedError, 
					kOBEXSessionNoTransportError, and kOBEXSessionNotConnectedError.
*/
- (void) fileTransferServicesDisconnectionComplete:(OBEXFileTransferServices*)inServices	error:(OBEXError)inError;

/*!
	@method			fileTransferServicesAbortComplete:error:
	@abstract		The delegate method that corresponds to the abort method
	@discussion		Possible inError values are kOBEXSuccess and kOBEXTimeoutError
*/
- (void) fileTransferServicesAbortComplete:(OBEXFileTransferServices*)inServices			error:(OBEXError)inError;

/*!
	@method			fileTransferServicesRemoveItemComplete:error:removedItem:
	@abstract		The delegate method that corresponds to the removeItemNamed: method
	@discussion		
	@param			inItemName The name of the remote item that was removed
*/
- (void) fileTransferServicesRemoveItemComplete:(OBEXFileTransferServices*)inServices	error:(OBEXError)inError removedItem:(NSString*)inItemName;

/*!
	@method			fileTransferServicesCreateFolderComplete:error:folderName:
	@abstract		The delegate method that corresponds to the createFolderNamed: method
	@discussion		
	@param			inFolderName The name of the newly created folder
*/
- (void) fileTransferServicesCreateFolderComplete:(OBEXFileTransferServices*)inServices  error:(OBEXError)inError folder:(NSString*)inFolderName;

/*!
	@method			fileTransferServicesPathChangeComplete:error:finalPath:
	@abstract		The delegate method that corresponds to the changeCurrentFolderToRoot:,
					changeCurrentFolderBackward:, and changeCurrentFolderForward: methods
	@discussion	
	@param			inPath The current remote path
*/
- (void) fileTransferServicesPathChangeComplete:(OBEXFileTransferServices*)inServices	error:(OBEXError)inError finalPath:(NSString*)inPath;

/*!
	@method			fileTransferServicesRetrieveFolderListingComplete:error:listing:
	@abstract		The delegate method that corresponds to the retrieveFolderListing method
	@discussion		
	@param			inListing An array of NSDictionary's that detail each file at the current path.  The keys
					to this dictionary are defined above.
*/
- (void) fileTransferServicesRetrieveFolderListingComplete:(OBEXFileTransferServices*)inServices	error:(OBEXError)inError listing:(NSArray*)inListing;

/*!
	@method			fileTransferServicesSendFileProgress:transferProgress:
	@abstract		The delegate method for receiving information on the sendFile: transfer
	@discussion		This method will be called during the transfer operation
	@param			inProgressDescription A dictionary containing information on the state of the transfer. The
					keys are defined above.
*/
- (void) fileTransferServicesSendFileProgress:(OBEXFileTransferServices*)inServices			transferProgress:(NSDictionary*)inProgressDescription;

/*!
	@method			fileTransferServicesSendFileComplete:error:
	@abstract		The delegate method that corresponds to the sendFile: method
	@discussion		This method will be called when the transfer operation has finished
*/
- (void) fileTransferServicesSendFileComplete:(OBEXFileTransferServices*)inServices			error:(OBEXError)inError;


/*!
	@method			fileTransferServicesCopyRemoteFileProgress:transferProgress:
	@abstract		The delegate method for receiving information on the GET transfer
	@discussion		This method will be called during the transfer operation
	@param			inProgressDescription A dictionary containing information on the state of the transfer. The
					keys are defined above.
*/
- (void) fileTransferServicesCopyRemoteFileProgress:(OBEXFileTransferServices*)inServices			transferProgress:(NSDictionary*)inProgressDescription;

/*!
	@method			fileTransferServicesCopyRemoteFileComplete:error:
	@abstract		The delegate method that corresponds to the getFileNamed:toLocalPathAndName: method
	@discussion		This method will be called when the transfer operation has finished
*/
- (void) fileTransferServicesCopyRemoteFileComplete:(OBEXFileTransferServices*)inServices			error:(OBEXError)inError;



@end

#endif  /* __OBJC__ */


#if 0
#pragma mark -
#pragma mark === C API ===
#endif


typedef struct OpaqueFileTransferServicesRef *			OBEXFileTransferServicesRef;


typedef void (*OBEXFileTransferServicesConnectionComplete)(				void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error);

typedef void (*OBEXFileTransferServicesDisconnectionComplete)(			void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error);

typedef void (*OBEXFileTransferServicesAbortComplete)(					void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error);

typedef void (*OBEXFileTransferServicesRemoveItemComplete)(				void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,	
																		OBEXError					error,
																		CFStringRef					itemName);

typedef void (*OBEXFileTransferServicesCreateFolderComplete)(			void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error,
																		CFStringRef					folderName);

typedef void (*OBEXFileTransferServicesPathChangeComplete)(				void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,	
																		OBEXError					error,
																		CFStringRef					finalPath);

typedef void (*OBEXFileTransferServicesRetrieveFolderListingComplete)(  void * 						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error,
																		CFArrayRef					listing);

typedef void (*OBEXFileTransferServicesSendFileProgress)(				void *						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		CFDictionaryRef				progressDict);

typedef void (*OBEXFileTransferServicesSendFileComplete)(				void *						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error);

typedef void (*OBEXFileTransferServicesCopyRemoteFileProgress)(			void *						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		CFDictionaryRef				progressDict);

typedef void (*OBEXFileTransferServicesCopyRemoteFileComplete)(			void *						userRefCon,
																		OBEXFileTransferServicesRef	servicesRef,
																		OBEXError					error);



extern OBEXFileTransferServicesRef OBEXFileTransferServicesCreateWithSession( OBEXSessionRef	inOBEXSession);
extern void		OBEXFileTransferServicesDelete( OBEXFileTransferServicesRef inRef );


extern void 	OBEXFileTransferServicesSetConnectCallback(					OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesConnectionComplete	callback );

extern void 	OBEXFileTransferServicesSetDisconnectCallback(				OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesDisconnectionComplete	callback );

extern void 	OBEXFileTransferServicesSetAbortCallback(					OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesAbortComplete		callback );

extern void 	OBEXFileTransferServicesSetRemoveItemCallback(				OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesRemoveItemComplete	callback );

extern void 	OBEXFileTransferServicesSetCreateFolderCallback(			OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesCreateFolderComplete	callback );

extern void 	OBEXFileTransferServicesSetPathChangeCallback(				OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesPathChangeComplete	callback );

extern void 	OBEXFileTransferServicesSetRetrieveFolderListingCallback(	OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesRetrieveFolderListingComplete	callback );

extern void 	OBEXFileTransferServicesSetSendFileCompleteCallback(		OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesSendFileComplete	callback );

extern void 	OBEXFileTransferServicesSetSendFileProgressCallback(		OBEXFileTransferServicesRef					inRef,
																			OBEXFileTransferServicesSendFileProgress	callback );

extern void 	OBEXFileTransferServicesSetCopyRemoteFileCompleteCallback(	OBEXFileTransferServicesRef						inRef,
																			OBEXFileTransferServicesCopyRemoteFileComplete	callback );

extern void 	OBEXFileTransferServicesSetCopyRemoteFileProgressCallback(	OBEXFileTransferServicesRef						inRef,
																			OBEXFileTransferServicesCopyRemoteFileProgress	callback );


extern void 	OBEXFileTransferServicesSetUserRefCon(						OBEXFileTransferServicesRef	inRef,
																			void *						inUserRefCon );

extern void  *	OBEXFileTransferServicesGetUserRefCon(						OBEXFileTransferServicesRef	inRef,
																			void *						inUserRefCon );


extern OBEXError OBEXFileTransferServicesConnectToFTPService(			OBEXFileTransferServicesRef	inRef);
extern OBEXError OBEXFileTransferServicesConnectToObjectPushService(	OBEXFileTransferServicesRef	inRef );
extern OBEXError OBEXFileTransferServicesDisconnect(					OBEXFileTransferServicesRef	inRef );
extern OBEXError OBEXFileTransferServicesChangeCurrentFolderToRoot(		OBEXFileTransferServicesRef	inRef );
extern OBEXError OBEXFileTransferServicesChangeCurrentFolderBackward(	OBEXFileTransferServicesRef	inRef );
extern OBEXError OBEXFileTransferServicesChangeCurrentFolderForward(	OBEXFileTransferServicesRef	inRef, CFStringRef inDirName );
extern OBEXError OBEXFileTransferServicesCreateFolder(					OBEXFileTransferServicesRef	inRef, CFStringRef inFolderName );
extern OBEXError OBEXFileTransferServicesRemoveItem(					OBEXFileTransferServicesRef	inRef, CFStringRef inItemName );
extern OBEXError OBEXFileTransferServicesRetrieveFolderListing(			OBEXFileTransferServicesRef	inRef );
extern OBEXError OBEXFileTransferServicesSendFile(						OBEXFileTransferServicesRef	inRef, CFStringRef inLocalPathAndName );
extern OBEXError OBEXFileTransferServicesCopyRemoteFile(				OBEXFileTransferServicesRef	inRef, CFStringRef inRemoteFileName, CFStringRef inLocalPathAndName );
extern OBEXError OBEXFileTransferServicesSendData(						OBEXFileTransferServicesRef	inRef, CFDataRef inData, CFStringRef inType, CFStringRef inName );
extern OBEXError OBEXFileTransferServicesGetDefaultVCard(				OBEXFileTransferServicesRef	inRef, CFStringRef inLocalPathAndName );
extern OBEXError OBEXFileTransferServicesAbort(							OBEXFileTransferServicesRef	inRef );

extern CFStringRef OBEXFileTransferServicesCurrentPath(					OBEXFileTransferServicesRef	inRef );
extern BOOL OBEXFileTransferServicesIsBusy(								OBEXFileTransferServicesRef	inRef );
extern BOOL OBEXFileTransferServicesIsConnected(						OBEXFileTransferServicesRef	inRef );



#ifdef	__cplusplus
	}
#endif






