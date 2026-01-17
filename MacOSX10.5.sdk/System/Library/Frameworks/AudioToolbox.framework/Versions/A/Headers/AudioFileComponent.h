/*
     File:       AudioToolbox/AudioFileComponent.h

     Contains:   API for implementing Audio File Components.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 2004 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/


#ifndef _AudioFileComponent_h_
#define _AudioFileComponent_h_

//==================================================================================================
//	Includes
//==================================================================================================

#include <TargetConditionals.h>

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreServices/CoreServices.h>
	#include <CoreAudio/CoreAudioTypes.h>
	#include <AudioToolbox/AudioFile.h>
#else
	#include "Components.h"
	#include "CoreAudioTypes.h"
	#include "AudioFile.h"
#endif

#if defined(__cplusplus)
extern "C"
{
#endif


/*!
    @header AudioFileComponent
    @discussion 
		This API is not for clients to call. These are the calls implemented by AudioFileComponents 
		which are called from within the AudioToolbox framework.
		Most of these calls match a call in the AudioFile API which calls through to the component.

		A component may be used in two ways, either associated with a file or not. 
		If a component is not associated with a file, it may be used to answer questions about
		the file type in general and whether some data is recognized by that file type.
		A component is associated with a file by calling one of the AudioFile Create, Open or Initialize calls.
		If a component is associated with a file then it can also be asked to perform any of
		the calls that implement the AudioFile API.
*/


/*!
    @typedef	AudioFileComponent
    @abstract		represents an instance of an AudioFileComponent.
*/
typedef ComponentInstance	AudioFileComponent;
/*!
    @typedef	AudioFileComponentPropertyID
    @abstract		a four char code for a property ID.
*/
typedef UInt32				AudioFileComponentPropertyID;


/*!
    @function	AudioFileComponentCreateURL
    @abstract   creates a new (or initialises an existing) audio file specified by the URL.
    @discussion	creates a new (or initialises an existing) audio file specified by the URL.
    @param inComponent		an AudioFileComponent
    @param inFileRef		an CFURLRef fully specifying the path of the file to create/initialise
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. 
								if kAudioFileFlags_EraseFile is set, it will erase an existing file
								 if not set, then the Create call will fail if the URL is an existing file
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileComponentCreateURL (
							AudioFileComponent					inComponent,
							CFURLRef							inFileRef,
							const AudioStreamBasicDescription	*inFormat,
							UInt32								inFlags)		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function				AudioFileComponentOpenURL
    @abstract				Open an existing audio file.
    @discussion				Open an existing audio file for reading or reading and writing.
    @param inComponent		an AudioFileComponent
    @param inFileRef		the CFURLRef of an existing audio file.
    @param inPermissions	use the permission constants used by FSOpenFork().
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileComponentOpenURL (	
					AudioFileComponent			inComponent,
					CFURLRef					inFileRef, 
					SInt8						inPermissions, 
					int							inFileDescriptor)							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
    @function	AudioFileComponentCreate
    @abstract   implements AudioFileCreate
    @param inComponent		an AudioFileComponent
    @param inParentRef		an FSRef to the directory where  the new file should be created.
    @param inFileName		a CFStringRef containing the name of the file to be created.
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. Currently zero.
    @param outNewFileRef	if successful, the FSRef of the newly created file.
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentCreate(
								AudioFileComponent					inComponent,
								const FSRef							*inParentRef, 
                                CFStringRef							inFileName,
                                const AudioStreamBasicDescription	*inFormat,
                                UInt32								inFlags,
                                FSRef								*outNewFileRef);
                                

/*!
    @function	AudioFileComponentInitialize
    @abstract   implements AudioFileInitialize
    @param inComponent		an AudioFileComponent
    @param inFileRef		the FSRef of an existing audio file.
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			flags for creating/opening the file. Currently zero.
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentInitialize(
								AudioFileComponent					inComponent,
								const FSRef							*inFileRef,
								const AudioStreamBasicDescription	*inFormat,
								UInt32								inFlags);
							
/*!
    @function	AudioFileComponentOpenFile
    @abstract   implements AudioFileOpen
    @param inComponent		an AudioFileComponent
    @param inFileRef		the FSRef of an existing audio file.
    @param inPermissions	use the permission constants used by FSOpenFork().
    @param inRefNum			the file refNum for the opened file. This avoids opening the file twice
							- once to determine which file type to which to delegate and once to parse it.
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentOpenFile(
								AudioFileComponent					inComponent,
								const FSRef							*inFileRef, 
								SInt8  								inPermissions,
								SInt16								inRefNum);

/*!
    @function	AudioFileComponentOpenWithCallbacks
    @abstract   implements AudioFileOpenWithCallbacks
    @param inComponent		an AudioFileComponent
    @param inClientData 	a constant that will be passed to your callbacks.
	@param inReadFunc		a function that will be called when AudioFile needs to read data.
	@param inWriteFunc		a function that will be called when AudioFile needs to write data.
	@param inGetSizeFunc	a function that will be called when AudioFile needs to know the file size.
	@param inSetSizeFunc	a function that will be called when AudioFile needs to set the file size.
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentOpenWithCallbacks(
								AudioFileComponent					inComponent,
								void								*inClientData, 
								AudioFile_ReadProc					inReadFunc, 
								AudioFile_WriteProc					inWriteFunc, 
								AudioFile_GetSizeProc				inGetSizeFunc,
								AudioFile_SetSizeProc				inSetSizeFunc);

/*!
    @function	AudioFileComponentInitializeWithCallbacks
    @abstract   implements AudioFileInitializeWithCallbacks
    @param inComponent		an AudioFileComponent
    @param inClientData 	a constant that will be passed to your callbacks.
	@param inReadFunc		a function that will be called when AudioFile needs to read data.
	@param inWriteFunc		a function that will be called when AudioFile needs to write data.
	@param inGetSizeFunc	a function that will be called when AudioFile needs to know the file size.
	@param inSetSizeFunc	a function that will be called when AudioFile needs to set the file size.
    @param inFileType 		an AudioFileTypeID indicating the type of audio file to which to initialize the file. 
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. Currently zero.
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentInitializeWithCallbacks(
								AudioFileComponent					inComponent,
								void								*inClientData, 
								AudioFile_ReadProc					inReadFunc, 
								AudioFile_WriteProc					inWriteFunc, 
								AudioFile_GetSizeProc				inGetSizeFunc,
								AudioFile_SetSizeProc				inSetSizeFunc,
								UInt32								inFileType,
								const AudioStreamBasicDescription	*inFormat,
								UInt32								inFlags);


/*!
    @function	AudioFileComponentCloseFile
    @abstract   implements AudioFileClose.
    @param inComponent		an AudioFileComponent
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentCloseFile(
								AudioFileComponent					inComponent);
				
/*!
    @function	AudioFileComponentOptimize
    @abstract   implements AudioFileOptimize.
    @param inComponent		an AudioFileComponent
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentOptimize(
								AudioFileComponent					inComponent);
				
/*!
    @function	AudioFileComponentReadBytes
    @abstract   implements AudioFileReadBytes. 
				
    @discussion				Returns eofErr when read encounters end of file.
    @param inComponent		an AudioFileComponent
    @param inUseCache 		true if it is desired to cache the data upon read, else false
    @param inStartingByte	the byte offset of the audio data desired to be returned
    @param ioNumBytes 		on input, the number of bytes to read, on output, the number of
							bytes actually read.
    @param outBuffer 		outBuffer should be a void * to user allocated memory large enough for the requested bytes. 
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentReadBytes(		
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								SInt64							inStartingByte, 
								UInt32							*ioNumBytes, 
								void							*outBuffer);
						
/*!
    @function				AudioFileComponentWriteBytes
    @abstract				implements AudioFileWriteBytes.
    @param inComponent		an AudioFileComponent
    @param inUseCache 		true if it is desired to cache the data upon write, else false
    @param inStartingByte	the byte offset where the audio data should be written
    @param ioNumBytes 		on input, the number of bytes to write, on output, the number of
							bytes actually written.
    @param inBuffer 		inBuffer should be a void * containing the bytes to be written 
    @result					returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentWriteBytes(		
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								SInt64							inStartingByte, 
								UInt32							*ioNumBytes, 
								const void						*inBuffer);
						
/*!
    @function	AudioFileComponentReadPackets
    @abstract   implements AudioFileReadPackets.
    @discussion For all uncompressed formats, packets == frames.
				ioNumPackets less than requested indicates end of file.

    @param inComponent				an AudioFileComponent
    @param inUseCache 				true if it is desired to cache the data upon read, else false
    @param outNumBytes				on output, the number of bytes actually returned
    @param outPacketDescriptions 	on output, an array of packet descriptions describing
									the packets being returned. NULL may be passed for this
									parameter. Nothing will be returned for linear pcm data.   
    @param inStartingPacket 		the packet index of the first packet desired to be returned
    @param ioNumPackets 			on input, the number of packets to read, on output, the number of
									packets actually read.
    @param outBuffer 				outBuffer should be a pointer to user allocated memory of size: 
									number of packets requested times file's maximum (or upper bound on)
									packet size.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentReadPackets(		
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								UInt32							*outNumBytes,
								AudioStreamPacketDescription	*outPacketDescriptions,
								SInt64							inStartingPacket, 
								UInt32  						*ioNumPackets, 
								void							*outBuffer);
									
/*!
    @function	AudioFileComponentWritePackets
    @abstract   implements AudioFileWritePackets.
    @discussion For all uncompressed formats, packets == frames.
    @param inComponent				an AudioFileComponent
    @param inUseCache 				true if it is desired to cache the data upon write, else false
    @param inNumBytes				the number of bytes being provided for write
    @param inPacketDescriptions 	an array of packet descriptions describing the packets being 
									provided. Not all formats require packet descriptions to be 
									provided. NULL may be passed if no descriptions are required.   
    @param inStartingPacket 		the packet index of where the first packet provided should be placed.
    @param ioNumPackets 			on input, the number of packets to write, on output, the number of
									packets actually written.
    @param inBuffer 				a void * to user allocated memory containing the packets to write.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentWritePackets(	
								AudioFileComponent					inComponent,
								Boolean								inUseCache,
								UInt32								inNumBytes,
								const AudioStreamPacketDescription	*inPacketDescriptions,
								SInt64								inStartingPacket, 
								UInt32								*ioNumPackets, 
								const void							*inBuffer);


/*!
    @function	AudioFileComponentGetPropertyInfo
    @abstract   implements AudioFileGetPropertyInfo.
    @param		inComponent			an AudioFileComponent
    @param      inPropertyID		an AudioFileProperty constant.
    @param      outPropertySize		the size in bytes of the current value of the property. In order to get the property value, 
									you will need a buffer of this size.
    @param      isWritable			will be set to 1 if writable, or 0 if read only.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentGetPropertyInfo(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							*outPropertySize,
								UInt32							*outWritable);


/*!
    @function	AudioFileComponentGetProperty
    @abstract   implements AudioFileGetProperty.
    @param		inComponent			an AudioFileComponent
    @param      inPropertyID		an AudioFileProperty constant.
    @param      ioPropertyDataSize	on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentGetProperty(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							*ioPropertyDataSize,
								void							*outPropertyData);

/*!
    @function	AudioFileComponentSetProperty
    @abstract   implements AudioFileSetProperty.
    @param		inComponent			an AudioFileComponent
    @param      inPropertyID		an AudioFileProperty constant.
    @param      inPropertyDataSize	the size of the property data.
    @param      inPropertyData		the buffer containing the property data.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentSetProperty(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							inPropertyDataSize,
								const void						*inPropertyData);


/*!
    @function	AudioFileComponentCountUserData
    @abstract   implements AudioFileCountUserData
    @discussion		"User Data" refers to chunks in AIFF, CAF and WAVE files, or resources 
					in Sound Designer II files, and possibly other things in other files.
					For simplicity, referred to below as "chunks".
    @param inComponent				an AudioFileComponent
    @param inUserDataID				the four char code of the chunk.
    @param outNumberItems			on output, if successful, number of chunks of this type in the file.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentCountUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							*outNumberItems);

/*!
    @function	AudioFileComponentGetUserDataSize
    @abstract   implements AudioFileGetUserDataSize
    @param inComponent				an AudioFileComponent
    @param inUserDataID				the four char code of the chunk.
    @param inIndex					an index specifying which chunk if there are more than one.
    @param outUserDataSize			on output, if successful, the size of the user data chunk.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentGetUserDataSize(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex,
								UInt32							*outUserDataSize);

/*!
    @function	AudioFileGetUserData
    @abstract   implements AudioFileGetUserData.
    @param		inComponent			an AudioFileComponent
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
	@param		ioUserDataSize		the size of the buffer on input, size of bytes copied to buffer on output 
    @param      outUserData			a pointer to a buffer in which to copy the chunk data.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentGetUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex,
								UInt32							*ioUserDataSize,
								void							*outUserData);

/*!
    @function	AudioFileComponentSetUserData
    @abstract   implements AudioFileSetUserData.
    @param		inComponent			an AudioFileComponent
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
	@param		inUserDataSize		on input the size of the data to copy, on output, size of bytes copied from the buffer  
    @param      inUserData			a pointer to a buffer from which to copy the chunk data 
									(only the contents of the chunk, not including the chunk header).
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentSetUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex,
								UInt32							inUserDataSize,
								const void						*inUserData);


/*!
    @function	AudioFileComponentRemoveUserData
    @abstract   implements AudioFileRemoveUserData.
    @param		inComponent			an AudioFileComponent
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentRemoveUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex)			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	The following calls are not made on AudioFile instances.
//  These calls are used to determine the audio file type of some data. 
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*!
    @function	AudioFileComponentExtensionIsThisFormat
    @abstract   used by the AudioFile API to determine if this component is appropriate for handling a file.
    @param		inComponent			an AudioFileComponent
    @param      inExtension			a CFString containing a file name extension.
    @param      outResult			on output, is set to 1 if the extension is recognized by this component, 0 if not.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentExtensionIsThisFormat(	
								AudioFileComponent				inComponent,
								CFStringRef 					inExtension,
								UInt32							*outResult);


/*!
    @function	AudioFileComponentFileDataIsThisFormat
    @abstract   used by the AudioFile API to determine if this component is appropriate for handling a file.
    @param		inComponent			an AudioFileComponent
    @param      inDataByteSize		the size of inData in bytes.
    @param      inData				a pointer to a buffer of audio file data.
    @param      outResult			on output, is set to 1 if the file is recognized by this component, 0 if not.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentFileDataIsThisFormat(	
								AudioFileComponent				inComponent,
								UInt32							inDataByteSize,
								const void*						inData,
								UInt32							*outResult);


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	The following two calls are deprecated. 
//  Please implement AudioFileComponentFileDataIsThisFormat instead.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*!
    @function	AudioFileComponentFileIsThisFormat
    @abstract   deprecated. use AudioFileComponentFileDataIsThisFormat instead.
    @param		inComponent			an AudioFileComponent
    @param      inFileRefNum		a refNum of a file.
    @param      outResult			on output, is set to 1 if the file is recognized by this component, 0 if not.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentFileIsThisFormat(	
								AudioFileComponent				inComponent,
								SInt16							inFileRefNum,
								UInt32							*outResult)			DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER; 
	
/*!
    @function	AudioFileComponentDataIsThisFormat
    @abstract   deprecated. use AudioFileComponentFileDataIsThisFormat instead.
    @param		inComponent			an AudioFileComponent
    @param		inClientData		a constant that will be passed to your callbacks.
	@param		inReadFunc			a function that will be called when AudioFile needs to read data.
	@param		inWriteFunc			a function that will be called when AudioFile needs to write data.
	@param		inGetSizeFunc		a function that will be called when AudioFile needs to know the file size.
	@param		inSetSizeFunc		a function that will be called when AudioFile needs to set the file size.
    @param      outResult			on output, is set to 1 if the file data is recognized by this component, 0 if not.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentDataIsThisFormat(	
								AudioFileComponent				inComponent,
								void							*inClientData, 
								AudioFile_ReadProc				inReadFunc, 
								AudioFile_WriteProc				inWriteFunc, 
								AudioFile_GetSizeProc			inGetSizeFunc,
								AudioFile_SetSizeProc			inSetSizeFunc,
								UInt32							*outResult)			DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER; 


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	The following calls are not made on AudioFile instances.
//  They implement the AudioFileGetGlobalInfo calls.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/*!
    @function	AudioFileComponentGetGlobalInfoSize
    @abstract   implements AudioFileGetGlobalInfoSize.
    @param		inComponent			an AudioFileComponent
    @param      inPropertyID		an AudioFileGlobalInfo property constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the global info properties.
    @param      outPropertySize		the size in bytes of the current value of the property. In order to get the property value, 
									you will need a buffer of this size.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentGetGlobalInfoSize(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							inSpecifierSize,
								const void						*inSpecifier,
								UInt32							*outPropertySize);

/*!
    @function	AudioFileComponentGetGlobalInfo
    @abstract   implements AudioFileGetGlobalInfo.
    @param      inPropertyID		an AudioFileGlobalInfo property constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the global info properties.
    @param      ioPropertyDataSize	on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data.
    @result							returns noErr if successful.
*/
extern ComponentResult 
AudioFileComponentGetGlobalInfo(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							inSpecifierSize,
								const void						*inSpecifier,
								UInt32							*ioPropertyDataSize,
								void							*outPropertyData);

//==================================================================================================
//	Properties for AudioFileComponentGetGlobalInfo. 
//==================================================================================================

/*!
    @enum AudioFileComponent specific properties
    @constant   kAudioFileComponent_CanRead
					Is file type readable? Returns a UInt32 1 or 0. 
    @constant   kAudioFileComponent_CanWrite
					Is file type writeable? Returns a UInt32 1 or 0. 
    @constant   kAudioFileComponent_FileTypeName
					Returns a CFString containing the name for the file type. 
    @constant   kAudioFileComponent_ExtensionsForType
					Returns a CFArray of CFStrings containing the file extensions 
					that are recognized for this file type. 
    @constant   kAudioFileComponent_AvailableFormatIDs
					Returns a array of format IDs for formats that can be read. 
    @constant   kAudioFileComponent_AvailableStreamDescriptionsForFormat
					The specifier is the format ID for the requested format.
					Returns an array of AudioStreamBasicDescriptions which have all of the 
					formats for a particular file type and format ID. The AudioStreamBasicDescriptions
					have the following fields filled in: mFormatID, mFormatFlags, mBitsPerChannel
    @constant   kAudioFileComponent_FastDispatchTable
					AudioFile gets an AudioFileFDFTable to speed up dispatching. 
    @constant   kAudioFileComponent_HFSTypeCodesForType
					Returns an array of HFSTypeCodes corresponding to this file type.
					The first type in the array is the preferred one for use when
					writing new files.
*/
enum
{
	kAudioFileComponent_CanRead									= 'cnrd',
	kAudioFileComponent_CanWrite								= 'cnwr',
	kAudioFileComponent_FileTypeName							= 'ftnm',
	kAudioFileComponent_ExtensionsForType						= 'fext',
	kAudioFileComponent_AvailableFormatIDs						= 'fmid',
	kAudioFileComponent_AvailableStreamDescriptionsForFormat	= 'sdid',
	kAudioFileComponent_FastDispatchTable						= 'fdft',
	kAudioFileComponent_HFSTypeCodesForType						= 'fhfs'
};

//==================================================================================================
//	Selectors for the component routines 
//==================================================================================================

enum
{

	kAudioFileCreateSelect						= 0x0001,
	kAudioFileOpenSelect						= 0x0002,
	kAudioFileInitializeSelect					= 0x0003,
	kAudioFileOpenWithCallbacksSelect			= 0x0004,
	kAudioFileInitializeWithCallbacksSelect		= 0x0005,
	kAudioFileCloseSelect						= 0x0006,
	kAudioFileOptimizeSelect					= 0x0007,
	kAudioFileReadBytesSelect					= 0x0008,
	kAudioFileWriteBytesSelect					= 0x0009,
	kAudioFileReadPacketsSelect					= 0x000A,
	kAudioFileWritePacketsSelect				= 0x000B,
	kAudioFileGetPropertyInfoSelect				= 0x000C,
	kAudioFileGetPropertySelect					= 0x000D,
	kAudioFileSetPropertySelect					= 0x000E,
	
	kAudioFileExtensionIsThisFormatSelect		= 0x000F,
	kAudioFileFileIsThisFormatSelect			= 0x0010,
	kAudioFileDataIsThisFormatSelect			= 0x0011,
	kAudioFileGetGlobalInfoSizeSelect			= 0x0012,
	kAudioFileGetGlobalInfoSelect				= 0x0013,

	kAudioFileCountUserDataSelect				= 0x0014,
	kAudioFileGetUserDataSizeSelect				= 0x0015,
	kAudioFileGetUserDataSelect					= 0x0016,
	kAudioFileSetUserDataSelect					= 0x0017,
	kAudioFileRemoveUserDataSelect				= 0x0018,
#define __defined_kAudioFileRemoveUserDataSelect__ 1
	kAudioFileCreateURLSelect					= 0x0019,
	kAudioFileOpenURLSelect						= 0x001A,
	kAudioFileFileDataIsThisFormatSelect		= 0x001B,
};


//==================================================================================================
// Fast Dispatch Function typedefs for those component operations that need to be fast.
//==================================================================================================

typedef OSStatus (*ReadBytesFDF)(	void			*inComponentStorage,
									Boolean			inUseCache,
									SInt64			inStartingByte, 
									UInt32			*ioNumBytes, 
									void			*outBuffer);
								
typedef OSStatus (*WriteBytesFDF)(	void			*inComponentStorage,
									Boolean			inUseCache,
									SInt64			inStartingByte, 
									UInt32			*ioNumBytes, 
									const void		*inBuffer);
							
typedef OSStatus (*ReadPacketsFDF)(	void							*inComponentStorage,
									Boolean							inUseCache,
									UInt32							*outNumBytes,
									AudioStreamPacketDescription	*outPacketDescriptions,
									SInt64							inStartingPacket, 
									UInt32  						*ioNumPackets, 
									void							*outBuffer);
								
typedef OSStatus (*WritePacketsFDF)(	void								*inComponentStorage,
										Boolean								inUseCache,
										UInt32								inNumBytes,
										const AudioStreamPacketDescription	*inPacketDescriptions,
										SInt64								inStartingPacket, 
										UInt32								*ioNumPackets, 
										const void							*inBuffer);
								
typedef OSStatus (*GetPropertyInfoFDF)(	void					*inComponentStorage,
										AudioFilePropertyID		inPropertyID,
										UInt32					*outDataSize,
										UInt32					*isWritable);
								
typedef OSStatus (*GetPropertyFDF)(		void					*inComponentStorage,
										AudioFilePropertyID		inPropertyID,
										UInt32					*ioDataSize,
										void					*ioPropertyData);
							
typedef OSStatus (*SetPropertyFDF)(		void					*inComponentStorage,
										AudioFilePropertyID		inPropertyID,
										UInt32					inDataSize,
										const void				*inPropertyData);

typedef OSStatus (*CountUserDataFDF)(   void					*inComponentStorage,
										UInt32					inUserDataID,
										UInt32					*outNumberItems);

typedef OSStatus (*GetUserDataSizeFDF)( void					*inComponentStorage,
										UInt32					inUserDataID,
										UInt32					inIndex,
										UInt32					*outDataSize);

typedef OSStatus (*GetUserDataFDF)(		void					*inComponentStorage,
										UInt32					inUserDataID,
										UInt32					inIndex,
										UInt32					*ioUserDataSize,
										void					*outUserData);

typedef OSStatus (*SetUserDataFDF)(		void					*inComponentStorage,
										UInt32					inUserDataID,
										UInt32					inIndex,
										UInt32					inUserDataSize,
										const void				*inUserData);
										
/* no fast dispatch for kAudioFileRemoveUserDataSelect */

//==================================================================================================
// Fast Dispatch Function table.
//==================================================================================================

typedef struct AudioFileFDFTable
{
	void				*mComponentStorage;
	ReadBytesFDF 		mReadBytesFDF;
	WriteBytesFDF 		mWriteBytesFDF;
	ReadPacketsFDF		mReadPacketsFDF;
	WritePacketsFDF		mWritePacketsFDF;

	GetPropertyInfoFDF	mGetPropertyInfoFDF;
	GetPropertyFDF		mGetPropertyFDF;
	SetPropertyFDF		mSetPropertyFDF;
	
	CountUserDataFDF	mCountUserDataFDF;
	GetUserDataSizeFDF  mGetUserDataSizeFDF;
	GetUserDataFDF		mGetUserDataFDF;
	SetUserDataFDF		mSetUserDataFDF;
} AudioFileFDFTable;



#if defined(__cplusplus)
}
#endif

#endif
