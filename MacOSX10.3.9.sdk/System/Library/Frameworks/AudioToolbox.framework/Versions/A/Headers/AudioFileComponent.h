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


//==================================================================================================
//	AudioFileComponent APIs
//
//  This API is not for clients to call. These are the calls implemented by AudioFileComponents 
//  which are called from within the AudioToolbox framework.
//  Most of these calls match a call in the AudioFile API which calls through to the component.
//
//  A component may be used in two ways, either associated with a file or not. 
//  If a component is not associated with a file, it may be used to answer questions about
//  the file type in general and whether some data is recognized by that file type.
//  A component is associated with a file by calling one of the AudioFile Create, Open or Initialize calls.
//  If a component is associated with a file then it can also be asked to perform any of
//  the calls that implement the AudioFile API.
//==================================================================================================


typedef ComponentInstance	AudioFileComponent;
typedef UInt32				AudioFileComponentPropertyID;

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentCreate - implements AudioFileCreate
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentCreate(
								AudioFileComponent					inComponent,
								const FSRef							*inParentRef, 
                                CFStringRef							inFileName,
                                const AudioStreamBasicDescription	*inFormat,
                                UInt32								inFlags,
                                FSRef								*outNewFileRef);
                                

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentInitialize - implements AudioFileInitialize
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentInitialize(
								AudioFileComponent					inComponent,
								const FSRef							*inFileRef,
								const AudioStreamBasicDescription	*inFormat,
								UInt32								inFlags);
							
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentOpenFile - implements AudioFileOpen
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentOpenFile(
								AudioFileComponent					inComponent,
								const FSRef							*inFileRef, 
								SInt8  								inPermissions,
								SInt16								inRefNum);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentOpenWithCallbacks - implements AudioFileOpenWithCallbacks
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentOpenWithCallbacks(
								AudioFileComponent					inComponent,
								void								*inClientData, 
								AudioFile_ReadProc					inReadFunc, 
								AudioFile_WriteProc					inWriteFunc, 
								AudioFile_GetSizeProc				inGetSizeFunc,
								AudioFile_SetSizeProc				inSetSizeFunc);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentInitializeWithCallbacks - implements AudioFileInitializeWithCallbacks
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
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


//--------------------------------------------------------------------------------------------------
//	AudioFileComponentCloseFile - implements AudioFileClose
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentCloseFile(
								AudioFileComponent					inComponent);
				
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentOptimize - implements AudioFileOptimize
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentOptimize(
								AudioFileComponent					inComponent);
				
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentReadBytes - implements AudioFileReadBytes
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentReadBytes(		
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								SInt64							inStartingByte, 
								UInt32							*ioNumBytes, 
								void							*outBuffer);
						
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentWriteBytes - implements AudioFileWriteBytes
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentWriteBytes(		
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								SInt64							inStartingByte, 
								UInt32							*ioNumBytes, 
								const void						*inBuffer);
						
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentOptimize - implements AudioFileReadPackets
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentReadPackets(		
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								UInt32							*outNumBytes,
								AudioStreamPacketDescription	*outPacketDescriptions,
								SInt64							inStartingPacket, 
								UInt32  						*ioNumPackets, 
								void							*outBuffer);
									
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentWritePackets - implements AudioFileWritePackets
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentWritePackets(	
								AudioFileComponent				inComponent,
								Boolean							inUseCache,
								UInt32							inNumBytes,
								AudioStreamPacketDescription	*inPacketDescriptions,
								SInt64							inStartingPacket, 
								UInt32  						*ioNumPackets, 
								const void						*inBuffer);


//--------------------------------------------------------------------------------------------------
//	AudioFileComponentGetPropertyInfo - implements AudioFileGetPropertyInfo
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentGetPropertyInfo(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							*outPropertySize,
								UInt32							*outWritable);


//--------------------------------------------------------------------------------------------------
//	AudioFileComponentGetProperty - implements AudioFileGetProperty
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentGetProperty(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							*ioPropertyDataSize,
								void							*outPropertyData);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentSetProperty - implements AudioFileSetProperty
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentSetProperty(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							inPropertyDataSize,
								const void						*inPropertyData);


//--------------------------------------------------------------------------------------------------
//	AudioFileComponentCountUserData - implements AudioFileCountUserData
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentCountUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							*outNumberItems);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentGetUserDataSize - implements AudioFileGetUserDataSize
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentGetUserDataSize(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex,
								UInt32							*outUserDataSize);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentGetUserData - implements AudioFileGetUserData
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentGetUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex,
								UInt32							*ioUserDataSize,
								void							*outUserData);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentSetUserData - implements AudioFileSetUserData
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentSetUserData(	
								AudioFileComponent				inComponent,
								UInt32							inUserDataID,
								UInt32							inIndex,
								UInt32							inUserDataSize,
								const void						*outUserData);

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	The following calls are not made on AudioFile instances.
//  These calls are used to determine the audio file type of some data. 
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentExtensionIsThisFormat
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentExtensionIsThisFormat(	
								AudioFileComponent				inComponent,
								CFStringRef 					inExtension,
								UInt32							*outResult);
	
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentFileIsThisFormat
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentFileIsThisFormat(	
								AudioFileComponent				inComponent,
								SInt16							inFileRefNum,
								UInt32							*outResult); 
	
//--------------------------------------------------------------------------------------------------
//	AudioFileComponentDataIsThisFormat
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentDataIsThisFormat(	
								AudioFileComponent				inComponent,
								void							*inClientData, 
								AudioFile_ReadProc				inReadFunc, 
								AudioFile_WriteProc				inWriteFunc, 
								AudioFile_GetSizeProc			inGetSizeFunc,
								AudioFile_SetSizeProc			inSetSizeFunc,
								UInt32							*outResult); 


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	The following calls are not made on AudioFile instances.
//  They implement the AudioFileGetGlobalInfo calls.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentGetGlobalInfoSize - implements AudioFileGetGlobalInfoSize
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
AudioFileComponentGetGlobalInfoSize(	
								AudioFileComponent				inComponent,
								AudioFileComponentPropertyID	inPropertyID,
								UInt32							inSpecifierSize,
								const void						*inSpecifier,
								UInt32							*outPropertySize);

//--------------------------------------------------------------------------------------------------
//	AudioFileComponentGetGlobalInfo - implements AudioFileGetGlobalInfo
//--------------------------------------------------------------------------------------------------
EXTERN_API(ComponentResult)
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

enum
{
	kAudioFileComponent_CanRead									= 'cnrd',
		// Is file type readable? Returns a UInt32 1 or 0. 
		
	kAudioFileComponent_CanWrite								= 'cnwr',
		// Is file type writeable? Returns a UInt32 1 or 0. 
	
	kAudioFileComponent_FileTypeName							= 'ftnm',
		// Returns a CFString containing the name for the file type. 
	
	kAudioFileComponent_ExtensionsForType						= 'fext',
		// Returns a CFArray of CFStrings containing the file extensions 
		// that are recognized for this file type. 
	
	kAudioFileComponent_AvailableFormatIDs						= 'fmid',
		// Returns a array of format IDs for formats that can be read. 
	
	kAudioFileComponent_AvailableStreamDescriptionsForFormat	= 'sdid',
		// The specifier is the format ID for the requested format.
		// Returns an array of AudioStreamBasicDescriptions which have all of the 
		// formats for a particular file type and format ID. The AudioStreamBasicDescriptions
		// have the following fields filled in: mFormatID, mFormatFlags, mBitsPerChannel

	kAudioFileComponent_FastDispatchTable						= 'fdft',
		// AudioFile gets an AudioFileFDFTable to speed up dispatching. 
		
	kAudioFileComponent_HFSTypeCodesForType						= 'fhfs'
		// Returns an array of HFSTypeCodes corresponding to this file type.
		// The first type in the array is the preferred one for use when
		// writing new files.
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
								
typedef OSStatus (*WritePacketsFDF)(	void							*inComponentStorage,
										Boolean							inUseCache,
										UInt32							inNumBytes,
										AudioStreamPacketDescription	*inPacketDescriptions,
										SInt64							inStartingPacket, 
										UInt32  						*ioNumPackets, 
										const void						*inBuffer);
								
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
