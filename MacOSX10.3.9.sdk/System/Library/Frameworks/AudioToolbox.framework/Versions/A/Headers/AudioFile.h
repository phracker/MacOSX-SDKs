/*
     File:       AudioToolbox/AudioFile.h

     Contains:   API for manipulating Audio Files.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                        http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioFile_h__)
#define __AudioFile_h__

//=============================================================================
//	Includes
//=============================================================================

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <CoreServices/CoreServices.h>
#else
	#include <CoreAudioTypes.h>
	#include <CoreServices.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

// File Types: types used when specifying the type of file to create and returned from get property (file format)
enum {
        kAudioFileAIFFType				= 'AIFF',
        kAudioFileAIFCType				= 'AIFC',
        kAudioFileWAVEType				= 'WAVE',
        kAudioFileSoundDesigner2Type	= 'Sd2f',
        kAudioFileNextType				= 'NeXT',
        kAudioFileMP3Type				= 'MPG3',
		kAudioFileAC3Type				= 'ac-3',
        kAudioFileAAC_ADTSType			= 'adts',
        kAudioFileMPEG4Type             = 'mp4f',
        kAudioFileM4AType               = 'm4af',
		kAudioFileCAFType				= 'caff'
};
typedef UInt32			AudioFileTypeID;

// Error Codes: AudioFile error codes
enum {
        kAudioFileUnspecifiedError						= 'wht?',
        kAudioFileUnsupportedFileTypeError 				= 'typ?',
        kAudioFileUnsupportedDataFormatError 			= 'fmt?',
        kAudioFileUnsupportedPropertyError 				= 'pty?',
        kAudioFileBadPropertySizeError 					= '!siz',
        kAudioFilePermissionsError	 					= 'prm?',
        kAudioFileNotOptimizedError						= 'optm',
        kAudioFileFormatNameUnavailableError			= 'nme?',
        // file format specific error codes
        kAudioFileInvalidChunkError						= 'chk?',	// applies to AIFF, WAVE chunks
        kAudioFileDoesNotAllow64BitDataSizeError		= 'off?',	// applies to AIFF, WAVE files
        kAudioFileInvalidPacketOffsetError				= 'pck?',
        kAudioFileInvalidFileError						= 'dta?',	// data could not be parsed 
		kAudioFileOperationNotSupportedError			= 0x6F703F3F // 'op??', integer used because of trigraph
};

//=============================================================================
//	Types specific to the Audio File API
//=============================================================================

typedef	struct OpaqueAudioFileID	*AudioFileID;
typedef UInt32			AudioFilePropertyID;

enum {
	kAudioFileLoopDirection_NoLooping = 0,
	kAudioFileLoopDirection_Forward = 1,
	kAudioFileLoopDirection_ForwardAndBackward = 2,
	kAudioFileLoopDirection_Backward = 3
};

//=============================================================================
//	Markers, Regions
//=============================================================================


struct AudioFile_SMPTE_Time
{
	SInt8 mHours;
	UInt8 mMinutes;
	UInt8 mSeconds;
	UInt8 mFrames;
	UInt32 mSubFrameSampleOffset;
};
typedef struct AudioFile_SMPTE_Time AudioFile_SMPTE_Time;


// markers
enum {
	kAudioFileMarkerType_Generic			= 0,
};


struct AudioFileMarker
{
	Float64 mFramePosition;
	
	CFStringRef				mName;
	SInt32					mMarkerID;

	AudioFile_SMPTE_Time	mSMPTETime;
	UInt32					mType;
	UInt16					mReserved;
	UInt16					mChannel;
};
typedef struct AudioFileMarker AudioFileMarker;

struct AudioFileMarkerList
{
	UInt32				mSMPTE_TimeType;
	UInt32				mNumberMarkers;
	AudioFileMarker		mMarkers[kVariableLengthArray];
};
typedef struct AudioFileMarkerList AudioFileMarkerList;

#define NumBytesToNumAudioFileMarkers(inNumBytes) ((inNumBytes)<offsetof(AudioFileMarkerList, mMarkers[0])?0:((inNumBytes) - offsetof(AudioFileMarkerList, mMarkers[0])) / sizeof(AudioFileMarker))
#define NumAudioFileMarkersToNumBytes(inNumMarkers) (offsetof(AudioFileMarkerList, mMarkers) + (inNumMarkers) * sizeof(AudioFileMarker))

enum {
	kAudioFileRegionFlag_LoopEnable = 1,
	kAudioFileRegionFlag_PlayForward = 2,
	kAudioFileRegionFlag_PlayBackward = 4
};

struct AudioFileRegion
{
	UInt32				mRegionID;
	CFStringRef			mName;
	UInt32				mFlags;
	UInt32				mNumberMarkers;
	AudioFileMarker		mMarkers[kVariableLengthArray];
};
typedef struct AudioFileRegion AudioFileRegion;


struct AudioFileRegionList
{
	UInt32				mSMPTE_TimeType;
	UInt32				mNumberRegions;
	AudioFileRegion		mRegions[kVariableLengthArray];
};
typedef struct AudioFileRegionList AudioFileRegionList;

/* because AudioFileRegions are variable length, you cannot access them as an array. Use NextAudioFileRegion to walk the list. */
#define NextAudioFileRegion(inAFRegionPtr) \
        ((AudioFileRegion*)((char*)(inAFRegionPtr) + offsetof(AudioFileRegion, mMarkers) + ((inAFRegionPtr)->mNumberMarkers)*sizeof(CAFMarker)))

struct AudioFramePacketTranslation
{
	SInt64 mFrame;
	SInt64 mPacket;
	UInt32 mFrameOffsetInPacket;
};
typedef struct AudioFramePacketTranslation AudioFramePacketTranslation;


struct AudioFilePacketTableInfo
{
        SInt64  mNumberValidFrames;
        SInt32  mPrimingFrames;
        SInt32  mRemainderFrames;
};
typedef struct AudioFilePacketTableInfo AudioFilePacketTableInfo;

//=============================================================================
//	Info String Keys
//=============================================================================

// Get key values from the InfoDictionary by making CFStrings from the following constants

#define kAFInfoDictionary_Artist                        "artist"
#define kAFInfoDictionary_Album							"album"
#define kAFInfoDictionary_Tempo							"tempo"
#define kAFInfoDictionary_KeySignature					"key signature"
#define kAFInfoDictionary_TimeSignature					"time signature"
#define kAFInfoDictionary_TrackNumber                   "track number"
#define kAFInfoDictionary_Year							"year"
#define kAFInfoDictionary_Composer						"composer"
#define kAFInfoDictionary_Lyricist						"lyricist"
#define kAFInfoDictionary_Genre							"genre"
#define kAFInfoDictionary_Title							"title"
#define kAFInfoDictionary_RecordedDate					"recorded date"
#define kAFInfoDictionary_Comments						"comments"
#define kAFInfoDictionary_Copyright						"copyright"
#define kAFInfoDictionary_SourceEncoder					"source encoder"
#define kAFInfoDictionary_EncodingApplication           "encoding application"
#define kAFInfoDictionary_NominalBitRate                "nominal bit rate"
#define kAFInfoDictionary_ChannelLayout					"channel layout"
#define kAFInfoDictionary_ApproximateDurationInSeconds  "approximate duration in seconds"

//=============================================================================
//	Routines
//=============================================================================
                        
/*----------------------------------------------------------------------------------
    AudioFileCreate - creates a new audio file located in the parent directory 
                      provided. Upon success, an AudioFileID is returned which can
                      be used for subsequent calls to the AudioFile APIs.
                      
    inParentRef 	- an FSRef to the directory where  the new file should be created.
    inFileName 		- a CFStringRef containing the name of the file to be created.
    inFileType 		- an AudioFileTypeID indicating the type of audio file to create. Constants are
                      provided above in the header file.
    inFormat 		- an AudioStreamBasicDescription describing the data format that will be
                      added to the audio file.
    inFlags 		- relevent flags for creating/opening the file. Currently zero.
    outNewFileRef 	- on success, the FSRef of the newly created file.
    outAudioFile  	- upon success, an AudioFileID that can be used for subsequent AudioFile calls.
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileCreate (	const FSRef							*inParentRef, 
                    CFStringRef							inFileName,
                    AudioFileTypeID						inFileType,
                    const AudioStreamBasicDescription	*inFormat,
                    UInt32								inFlags,
                    FSRef								*outNewFileRef,
                    AudioFileID							*outAudioFile)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileInitialize - Use AudioFileInitialize to wipe clean an existing audio file
                          and prepare it to be populated with new data.
    
    inFileRef 		- the FSRef of an existing audio file.
    inFileType 		- an AudioFileTypeID indicating the type of audio file to initialize the file to. 
                      Constants are provided above in the header file.
    inFormat 		- an AudioStreamBasicDescription describing the data format that will be
                      added to the audio file.
    inFlags 		- relevent flags for creating/opening the file. Currently zero.
    outAudioFile	- upon success, an AudioFileID that can be used for subsequent
                      AudioFile calls.
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileInitialize (	const FSRef							*inFileRef,
                        AudioFileTypeID						inFileType,
                        const AudioStreamBasicDescription	*inFormat,
                        UInt32								inFlags,
                        AudioFileID							*outAudioFile)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileOpen - Open an existing audio file.
    
    inFileRef 		- the FSRef of an existing audio file.
    inPermissions 	- use the permission constants used by FSOpenFork().
    inFileTypeHint 	- For files which have no filename extension and whose type cannot be easily or
		uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
		Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
		For OS versions prior to that, opening files of the above description will fail.
    outAudioFile	- upon success, an AudioFileID that can be used for subsequent AudioFile calls.
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileOpen (	const FSRef		*inFileRef, 
                SInt8  			inPermissions, 
                AudioFileTypeID	inFileTypeHint,
                AudioFileID		*outAudioFile)								AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*----------------------------------------------------------------------------------
    AudioFileInitializeWithCallbacks - Wipe clean an existing file. You provide callbacks that the AudioFile API
		will use to get the data. 
    
    inRefCon 				- a constant that will be passed to your callbacks.
	AudioFile_ReadProc		- a function that will be called when AudioFile needs to read data.
	AudioFile_WriteProc		- a function that will be called when AudioFile needs to write data.
	AudioFile_GetSizeProc	- a function that will be called when AudioFile needs to know the file size.
	AudioFile_SetSizeProc	- a function that will be called when AudioFile needs to set the file size.
	
    inFileType 		- an AudioFileTypeID indicating the type of audio file to initialize the file to. 
                      Constants are provided above in the header file.
    inFormat 		- an AudioStreamBasicDescription describing the data format that will be
                      added to the audio file.
    inFlags 		- relevent flags for creating/opening the file. Currently zero.
    outAudioFile	- upon success, an AudioFileID that can be used for subsequent
                      AudioFile calls.
//----------------------------------------------------------------------------------*/

typedef OSStatus (*AudioFile_ReadProc)(
								void *		inRefCon,
								SInt64		inPosition, 
								ByteCount	requestCount, 
								void *		buffer, 
								ByteCount *	actualCount);

typedef OSStatus (*AudioFile_WriteProc)(
								void * 		inRefCon,
								SInt64		inPosition, 
								ByteCount	requestCount, 
								const void *buffer, 
								ByteCount * actualCount);
								
typedef SInt64 (*AudioFile_GetSizeProc)(
								void * 		inRefCon);

typedef OSStatus (*AudioFile_SetSizeProc)(
								void *		inRefCon,
								SInt64		inSize);

extern OSStatus	
AudioFileInitializeWithCallbacks (	
						void *								inRefCon, 
						AudioFile_ReadProc					inReadFunc, 
						AudioFile_WriteProc					inWriteFunc, 
						AudioFile_GetSizeProc				inGetSizeFunc,
						AudioFile_SetSizeProc				inSetSizeFunc,
                        AudioFileTypeID						inFileType,
                        const AudioStreamBasicDescription	*inFormat,
                        UInt32								inFlags,
                        AudioFileID							*outAudioFile)	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*----------------------------------------------------------------------------------
    AudioFileOpenWithCallbacks - Open an existing file. You provide callbacks that the AudioFile API
		will use to get the data. 
    
    inRefCon 				- a constant that will be passed to your callbacks.
	AudioFile_ReadProc		- a function that will be called when AudioFile needs to read data.
	AudioFile_WriteProc		- a function that will be called when AudioFile needs to write data.
	AudioFile_GetSizeProc	- a function that will be called when AudioFile needs to know the file size.
	AudioFile_SetSizeProc	- a function that will be called when AudioFile needs to set the file size.
	
    inFileTypeHint 	- For files which have no filename extension and whose type cannot be easily and
		uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
		Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
		For OS versions prior to that, opening files of the above description will fail.
    outAudioFile	- upon success, an AudioFileID that can be used for subsequent
                      AudioFile calls.
//----------------------------------------------------------------------------------*/

extern OSStatus	
AudioFileOpenWithCallbacks ( // not seekable, read only
				void *					inRefCon, 
				AudioFile_ReadProc		inReadFunc, 
				AudioFile_WriteProc		inWriteFunc, 
				AudioFile_GetSizeProc	inGetSizeFunc,
				AudioFile_SetSizeProc	inSetSizeFunc,
                AudioFileTypeID			inFileTypeHint,
                AudioFileID				*outAudioFile)						AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*----------------------------------------------------------------------------------
    AudioFileClose - Close an existing audio file.
//----------------------------------------------------------------------------------*/
extern OSStatus
AudioFileClose	(AudioFileID		inAudioFile)							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileOptimize - Optimize the file so additional audio data can be appended to 
                        the existing data. Generally, this will place the audio data at 
                        the end of the file so additional writes can be placed to the 
                        file end. This can be a potentially expensive and time-consuming operation 
                        and should not be used during time critical operations. There is 
                        a kAudioFilePropertyIsOptimized property for checking on the optimized state 
                        of the file.
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileOptimize (AudioFileID  	inAudioFile)							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileReadBytes - Read bytes of audio data from the audio file. 
						Returns eofErr when read encounters end of file.
     
    inUseCache 		- true if it is desired to cache the data upon read, else false
    inStartingByte	- the byte offset of the audio data desired to be returned
    ioNumBytes 		- on input, the number of bytes to read, on output, the number of
                      bytes actually read.
    outBuffer 		- outBuffer should be a void * to user allocated memory of size: 
                      number of bytes requested.
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileReadBytes (	AudioFileID  	inAudioFile,
                        Boolean			inUseCache,
                        SInt64			inStartingByte, 
                        UInt32			*ioNumBytes, 
                        void			*outBuffer)							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileWriteBytes - Read bytes of audio data from the audio file. 
     
    inUseCache 		- true if it is desired to cache the data upon write, else false
    inStartingByte 	- the byte offset where the audio data should be written
    ioNumBytes 		- on input, the number of bytes to write, on output, the number of
                      bytes actually written.
    inBuffer 		- inBuffer should be a void * containing the bytes to be written
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileWriteBytes (	AudioFileID  	inAudioFile,  
                        Boolean			inUseCache,
                        SInt64			inStartingByte, 
                        UInt32			*ioNumBytes, 
                        const void		*inBuffer)							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileReadPackets - Read packets of audio data from the audio file. For all 
                           uncompressed formats, packet = frame. 
						   ioNumPackets less than requested indicates end of file.
						   

    inUseCache 				- true if it is desired to cache the data upon read, else false
    outNumBytes 			- on output, the number of bytes actually returned
    outPacketDescriptions 	- on output, an array of packet descriptions describing
                              the packets being returned. NULL may be passed for this
                              parameter. Nothing will be returned for linear pcm data.   
    inStartingPacket 		- the packet index of the first packet desired to be returned
    ioNumPackets 			- on input, the number of packets to read, on output, the number of
                              packets actually read.
    outBuffer 				- outBuffer should be a pointer to user allocated memory of size: 
                              number of packets requested times file's maximum (or upper bound on)
							  packet size.
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileReadPackets (	AudioFileID  					inAudioFile, 
                        Boolean							inUseCache,
                        UInt32							*outNumBytes,
                        AudioStreamPacketDescription	*outPacketDescriptions,
                        SInt64							inStartingPacket, 
                        UInt32  						*ioNumPackets, 
                        void							*outBuffer)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileWritePackets - Write packets of audio data to the audio file. For all 
                            uncompressed formats, packet = frame
							
    inUseCache 				- true if it is desired to cache the data upon write, else false
    inNumBytes 				- the number of bytes being provided for write
    inPacketDescriptions 	- an array of packet descriptions describing the packets being 
                              provided. Not all formats require packet descriptions to be 
                              provided. NULL may be passed if no descriptions are required.
    inStartingPacket 		- the packet index of where the first packet provided should be placed
    ioNumPackets 			- on input, the number of packets to write, on output, the number of
                              packets actually written.
    inBuffer 				- a void * to user allocated memory containing the packets to write
//----------------------------------------------------------------------------------*/
extern OSStatus	
AudioFileWritePackets (	AudioFileID  					inAudioFile,  
                        Boolean							inUseCache,
                        UInt32							inNumBytes,
                        AudioStreamPacketDescription	*inPacketDescriptions,
                        SInt64							inStartingPacket, 
                        UInt32  						*ioNumPackets, 
                        const void						*inBuffer)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*----------------------------------------------------------------------------------
	Functions for accessing User Data.
	"User Data" refers to chunks in AIFF and WAVE files, or resources 
	in Sound Designer II files, and possibly other things in other files.
	For simplicity, referred to below as "chunks".
//----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------
    AudioFileCountUserData - Get the number of user data items with a certain ID in the file
	
	inUserDataID		- four char code of the chunk
	outNumberItems		- number of chunks of this type
//----------------------------------------------------------------------------------*/

extern OSStatus	
AudioFileCountUserData (	AudioFileID			inAudioFile, 
							UInt32				inUserDataID, 
							UInt32				*outNumberItems)			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileGetUserDataSize - Get the size of user data in a file
	
	inUserDataID		- four char code of the user data
	inIndex				- an index specifying which chunk if there are more than one.
	outUserDataSize		- size of the user data
//----------------------------------------------------------------------------------*/

extern OSStatus	
AudioFileGetUserDataSize (	AudioFileID			inAudioFile, 
							UInt32				inUserDataID, 
							UInt32				inIndex, 
							UInt32				*outUserDataSize)			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileGetUserData - Get the data of a chunk in an AIFF or WAVE file
	
	inUserDataID			- four char code of the chunk
	inIndex					- an index specifying which chunk if there are more than one.
	ioUserDataSize			- size of the buffer on input, size of bytes copied to buffer on output 
	outUserData				- pointer to a buffer where to copy the chunk data.
//----------------------------------------------------------------------------------*/

extern OSStatus	
AudioFileGetUserData (	AudioFileID			inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex, 
						UInt32				*ioUserDataSize, 
						void				*outUserData)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*----------------------------------------------------------------------------------
    AudioFileSetUserData - Get the data of a chunk in an AIFF or WAVE file
	
	inUserDataID		- four char code of the chunk
	inIndex				- an index specifying which chunk if there are more than one.
	inUserDataSize		- size of the buffer on input, size of bytes copied to buffer on output 
	inUserData			- pointer to a buffer of chunk data (only the contents, not including the chunk header).
//----------------------------------------------------------------------------------*/

extern OSStatus	
AudioFileSetUserData ( AudioFileID			inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex, 
						UInt32				inUserDataSize, 
						const void			*inUserData)					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


//=============================================================================
//	Audio File Properties
//=============================================================================

enum
{
	kAudioFilePropertyFileFormat			=	'ffmt',
		// An AudioFileTypeID that identifies the format of the file
	kAudioFilePropertyDataFormat			=	'dfmt',
		// An AudioStreamBasicDescription describing the format of the audio data
	kAudioFilePropertyIsOptimized			=	'optm',
		// A UInt32 indicating whether an Audio File has been optimized.
        // Optimized meaning it is ready to start having sound data written
        // to it. A value of 0 indicates the file needs to be optimized.
        // A value of 1 indicates the file is currently optimized
	kAudioFilePropertyMagicCookieData		=	'mgic',
		// A void * pointing to memory set up by the caller.
        // Some file types require that a magic cookie be provided before packets can be written
        // to the file, so this property should be set before calling 
        // AudioFileWriteBytes()/AudioFileWritePackets() if a magic cookie exists.
	kAudioFilePropertyAudioDataByteCount	=	'bcnt',
		// a UInt64 that indicates the number of bytes of audio data contained in the file
	kAudioFilePropertyAudioDataPacketCount	=	'pcnt',
		// a UInt64 that indicates the number of packets of audio data contained in the file
	kAudioFilePropertyMaximumPacketSize		=	'psze',
		// a UInt32 that indicates the maximum size of a packet for the data contained in the file
	kAudioFilePropertyDataOffset			=	'doff',
		// a SInt64 that indicates the byte offset in the file of the audio data.
	kAudioFilePropertyChannelLayout			=	'cmap',
		// An AudioChannelLayout struct.
	kAudioFilePropertyDeferSizeUpdates		=	'dszu',
		// A UInt32. If 1, then updating the files sizes in the header is not done for every write, 
		// but deferred until the file is read, optimized or closed. This is more efficient, but less safe
		// since, if the application crashes before the size is updated, the file may not be readable.
		// The default value is zero, it always updates header.
	kAudioFilePropertyDataFormatName		=	'fnme',
		// This is deprecated. Use kAudioFormatProperty_FormatName in AudioFormat.h instead.
		
	kAudioFilePropertyMarkerList			=	'mkls',
		// access the list of markers defined in the file. returns an AudioFileMarkerList.
		// The CFStringRefs in the returned structs must be released by the client.
		// (available in 10.2.4 and later)
	kAudioFilePropertyRegionList			=	'rgls',
		// access the list of regions defined in the file. returns an Array of AudioFileRegions.
		// The CFStringRefs in the returned structs must be released by the client.
		// (available in 10.2.4 and later)
	kAudioFilePropertyPacketToFrame			=	'pkfr',
		// pass a AudioFramePacketTranslation with mPacket filled out and get mFrame back. mFrameOffsetInPacket is ignored.
	kAudioFilePropertyFrameToPacket			=	'frpk',
		// pass a AudioFramePacketTranslation with mFrame filled out and get mPacket and mFrameOffsetInPacket back.
	kAudioFilePropertyChunkIDs				=	'chid',
		// returns an array of OSType four char codes for each kind of chunk in the file.
	kAudioFilePropertyInfoDictionary        =	'info',
        // returns a CFDictionary filled with information about the data contined in the file. 
		// See dictionary key constants already defined for info string types. 
        // AudioFileComponents are free to add keys to the dictionaries that they return for this property...
        // caller is responsible for releasing the CFObject
	kAudioFilePropertyPacketTableInfo		=	'pnfo'
		// Gets or sets an AudioFilePacketTableInfo struct for CAF files.
		// When setting, the sum of mNumberValidFrames, mPrimingFrames and mRemainderFrames must be the same as the total
		// number of frames in all packets. If not you will get a paramErr. The best way to ensure this is to get the value of
		// the property and make sure the sum of the three values you set has the same sum as the three values you got.
};

//-----------------------------------------------------------------------------
//	AudioFileGetPropertyInfo
//-----------------------------------------------------------------------------
extern OSStatus
AudioFileGetPropertyInfo(		AudioFileID				inAudioFile,
                                AudioFilePropertyID		inPropertyID,
                                UInt32					*outDataSize,
                                UInt32					*isWritable)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
                                
//-----------------------------------------------------------------------------
//	AudioFileGetProperty
//-----------------------------------------------------------------------------
extern OSStatus
AudioFileGetProperty(	AudioFileID				inAudioFile,
                        AudioFilePropertyID		inPropertyID,
                        UInt32					*ioDataSize,
                        void					*outPropertyData)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
                        
//-----------------------------------------------------------------------------
//	AudioFileSetProperty
//-----------------------------------------------------------------------------
extern OSStatus
AudioFileSetProperty(	AudioFileID				inAudioFile,
                        AudioFilePropertyID		inPropertyID,
                        UInt32					inDataSize,
                        const void				*inPropertyData)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



//=============================================================================
//	Audio File Global Info Properties
//=============================================================================

enum
{
	kAudioFileGlobalInfo_ReadableTypes							= 'afrf',
		// No specifier needed. Must be set to NULL.
		// Returns an array of UInt32 containing the file types 
		// (i.e. AIFF, WAVE, etc) that can be opened for reading.
	
	kAudioFileGlobalInfo_WritableTypes							= 'afwf',
		// No specifier needed. Must be set to NULL.
		// Returns an array of UInt32 containing the file types 
		// (i.e. AIFF, WAVE, etc) that can be opened for writing.
	
	kAudioFileGlobalInfo_FileTypeName							= 'ftnm',
		// Specifier is a pointer to a AudioFileTypeID containing a file type.
		// Returns a CFString containing the name for the file type. 
	
	kAudioFileGlobalInfo_ExtensionsForType						= 'fext',
		// Specifier is a pointer to a AudioFileTypeID containing a file type.
		// Returns a CFArray of CFStrings containing the file extensions 
		// that are recognized for this file type. 
	
	kAudioFileGlobalInfo_AllExtensions							= 'alxt',
		// No specifier needed. Must be set to NULL.
		// Returns a CFArray of CFStrings containing all file extensions 
		// that are recognized. The array be used when creating an NSOpenPanel.

	kAudioFileGlobalInfo_AvailableFormatIDs						= 'fmid',
		// Specifier is a pointer to a AudioFileTypeID containing a file type.
		// Returns a array of format IDs for formats that can be read. 
	
	kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat	= 'sdid',
		// Specifier is a pointer to a AudioFileTypeAndFormatID struct defined below.
		// Returns an array of AudioStreamBasicDescriptions which have all of the 
		// formats for a particular file type and format ID. The AudioStreamBasicDescriptions
		// have the following fields filled in: mFormatID, mFormatFlags, mBitsPerChannel

	kAudioFileGlobalInfo_HFSTypeCodesForType		= 'fhfs',
		// Specifier is a pointer to an AudioFileTypeID.
		// Returns an array of HFSTypeCodes corresponding to that file type.
		// The first type in the array is the preferred one for use when
		// writing new files.
	
	kAudioFileGlobalInfo_AllHFSTypeCodes			= 'ahfs'
		// No specifier needed. Must be set to NULL.
		// Returns an array of HFSTypeCode's containing all HFSTypeCodes
		// that are recognized.

};


// This is used as a specifier for kAudioFileGlobalInfo_AvailableStreamDescriptions
struct AudioFileTypeAndFormatID
{
	AudioFileTypeID  mFileType;
	UInt32			mFormatID;
};
typedef struct AudioFileTypeAndFormatID AudioFileTypeAndFormatID;

//-----------------------------------------------------------------------------
//	AudioFileGetGlobalInfoSize
//-----------------------------------------------------------------------------
extern OSStatus
AudioFileGetGlobalInfoSize(		AudioFilePropertyID		inPropertyID,
                                UInt32					inSpecifierSize,
                                void					*inSpecifier,
                                UInt32					*outDataSize)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
                                
//-----------------------------------------------------------------------------
//	AudioFileGetGlobalInfo
//-----------------------------------------------------------------------------
extern OSStatus
AudioFileGetGlobalInfo(			AudioFilePropertyID		inPropertyID,
								UInt32					inSpecifierSize,
								void					*inSpecifier,
                    		    UInt32					*ioDataSize,
                    		    void					*outPropertyData)	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
                        


#if defined(__cplusplus)
}
#endif

#endif
