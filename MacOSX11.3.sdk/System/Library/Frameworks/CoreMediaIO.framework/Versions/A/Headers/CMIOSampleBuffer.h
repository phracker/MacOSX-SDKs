/*
     File:       CMIOSampleBuffer.h

     Contains:   Routines/constants/etc. used to create CoreMedia Sample Buffers for use in
				 CMIO graphs.

     Copyright:  (c) 2006-2018 by Apple Inc., all rights reserved.
*/

/*!
	@header		CMIOSampleBuffer.h
	@abstract	API for creating CMSampleBuffers for use by CMIO.
	@discussion	Buffers used by CMIO are CMSampleBuffers that have a required
				set of attachments.<br>
				<br>
				The first required attachment is a sequence number.  Every time a
				buffer is created, a sequence number is attached.  The sequence
				numbers for buffers emitted by an entity must increment monotonically
				by one.  This allows clients of the buffers to easily tell if a
				break has occurred in the stream of buffers that it is receiving
				(such a break might occur if a CMIO Unit in a processing chain
				needs to drop buffers for some reason).<br>
				<br>
				The second required attachment is a UInt32 that consists of a
				bitfield used to indicate a discontinuity in the contents of the
				buffers.  Many types of discontinuities are defined below.<br>
				A client is assured that a given buffer is a valid continuation
				of a media stream if the sequence number is one more than the
				previously experienced sequence number and the discontinity flags
				are all at zero.<br>
				<br>
				A special kind of buffer, called a no-data marker, can be emitted
				by entities that marshall media streams from real-time devices.
				A no-data marker is used to indicate that the device has stopped
				providing buffers;  for example, a tape-based device that has hit
				a blank spot on its media.
*/

#if !defined(__CMIOSampleBuffer_h__)
#define __CMIOSampleBuffer_h__

#include <CoreFoundation/CFString.h>

#include <CoreMedia/CMSampleBuffer.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

//=============================================================================
//	Sequence Number constants and helpers
//=============================================================================

/*!
	@define		kCMIOInvalidSequenceNumber
	@discussion Value for sequence number used to indicate that an entity hasn't
				emitted any buffers yet.  See the discussion above for more information
				about sequence numbers.
*/
#define kCMIOInvalidSequenceNumber		( ~((UInt64) (0)) )

/*!
	@define		CMIOGetNextSequenceNumber
	@discussion Given a current sequcne number, this macro returns next sequence number.
*/
#define CMIOGetNextSequenceNumber( x )	((UInt64) ( ( kCMIOInvalidSequenceNumber == ( x ) ) ? 0 : ( ( x ) + 1 ) ))

//=============================================================================
//	Discontinuity flag constants
//=============================================================================

/*!
	@enum		Discontinuity flags.
	@discussion The following flags are used to tag CMIO Buffers as they flow through the system.
				They denote discontinuities in the buffer's stream that are associated with the buffer.
*/
enum
{
	kCMIOSampleBufferNoDiscontinuities							= 0,			/*! @constant kCMIOSampleBufferNoDiscontinuities							no discontinuities. */
	
	kCMIOSampleBufferDiscontinuityFlag_UnknownDiscontinuity		= (1L << 0),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_UnknownDiscontinuity		0x00000001  data was lost for unknown reasons. */
	kCMIOSampleBufferDiscontinuityFlag_TimecodeDiscontinuity	= (1L << 1),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_TimecodeDiscontinuity		0x00000002  a break in timecode was detected. */
	kCMIOSampleBufferDiscontinuityFlag_PacketError				= (1L << 2),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_PacketError				0x00000004  a packet error occurred. */
	kCMIOSampleBufferDiscontinuityFlag_StreamDiscontinuity		= (1L << 3),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_StreamDiscontinuity		0x00000008  detected in the stream. */
	kCMIOSampleBufferDiscontinuityFlag_MalformedData			= (1L << 4),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_MalformedData				0x00000010  bad data was received. */
	kCMIOSampleBufferDiscontinuityFlag_DataWasFlushed			= (1L << 5),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_DataWasFlushed				0x00000020  data was flushed before read by graph. */
	kCMIOSampleBufferDiscontinuityFlag_DataWasDropped			= (1L << 6),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_DataWasDropped				0x00000040  a unit did not pull on its input fast enough. */
	kCMIOSampleBufferDiscontinuityFlag_BufferOverrun			= (1L << 7),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_BufferOverrun				0x00000080  a unit ran out of buffer space. */
	kCMIOSampleBufferDiscontinuityFlag_DiscontinuityInDTS		= (1L << 8),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_DiscontinuityInDTS			0x00000100  detected a break in adjacent DTS values. */
	kCMIOSampleBufferDiscontinuityFlag_RelatedToDiscontinuity	= (1L << 9),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_RelatedToDiscontinuity		0x00000200  this buffer is OK, but a related buffer
																																								(as in another picture in the same MPEG-2
																																								GOP) exhibits a discontinuity. */
	kCMIOSampleBufferDiscontinuityFlag_ClientSyncDiscontinuity	= (1L << 10),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_ClientSyncDiscontinuity	0x00000400  a client forced a discontinuity, typically
																																								as a way of syncronizing the graph to
																																								a known state. */
	kCMIOSampleBufferDiscontinuityFlag_TrickPlay				= (1L << 11),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_TrickPlay					0x00000800  trick-play buffer. */
	kCMIOSampleBufferDiscontinuityFlag_NoDataMarker				= (1L << 12),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_NoDataMarker				0x00001000  this is a dummy buffer that is sent through the
																																								the graph if the source has no data (for example
																																								an HDV camera running on empty tape). */
	kCMIOSampleBufferDiscontinuityFlag_DataFormatChanged		= (1L << 13),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_DataFormatChanged			0x00002000  data format changed. */
	kCMIOSampleBufferDiscontinuityFlag_TimingReferenceJumped	= (1L << 14),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_TimingReferenceJumped		0x00004000  the timing reference used to synchronize the buffer jumped. */
	kCMIOSampleBufferDiscontinuityFlag_DurationWasExtended		= (1L << 15),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_DurationWasExtended		0x00008000  the unit experience a buffer overrun but was able to accomodate for it
																																								by increasing the duration of known good media;  this is a "soft"
																																								discontinuity, much like kCMIOSampleBufferDiscontinuityFlag_TimecodeDiscontinuity,
																																								meaning that the stream isn't necessarily broken, but clients might want to force
																																								capture of all media. */
	kCMIOSampleBufferDiscontinuityFlag_SleepWakeCycle			= (1L << 16),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_SleepWakeCycle				0x00010000  the buffer was received during a sleep/wake cycle. */
	kCMIOSampleBufferDiscontinuityFlag_CodecSettingsChanged		= (1L << 17),	/*! @constant kCMIOSampleBufferDiscontinuityFlag_CodecSettingsChanged		0x00020000  the buffer has no data and is used to mark a change in format. */
};

/*!
    @define    CMIODiscontinuityFlagsHaveHardDiscontinuities
    @discussion   A macro for checking if the provided discontinuity flags have any "hard" discontinuities
*/
#define CMIODiscontinuityFlagsHaveHardDiscontinuities( flags )  ( ( flags ) & ~kCMIOSampleBufferDiscontinuityFlag_DurationWasExtended )

//=============================================================================
//	No data event constants
//=============================================================================

/*!
	@enum		No data events.
	@discussion The following values are used to define types of no-data events that a device can specify.
*/
enum
{
	kCMIOSampleBufferNoDataEvent_Unknown				= 0,	/*! @constant kCMIOSampleBufferNoDataEvent_Unknown			unknown cause of no data marker. */
	kCMIOSampleBufferNoDataEvent_NoMedia				= 1,	/*! @constant kCMIOSampleBufferNoDataEvent_NoMedia			the device does not see valid media. */
	kCMIOSampleBufferNoDataEvent_DeviceDidNotSync		= 2,	/*! @constant kCMIOSampleBufferNoDataEvent_DeviceDidNotSync	the device did not start sending data. */
	kCMIOSampleBufferNoDataEvent_DeviceInWrongMode	= 3,	/*! @constant kCMIOSampleBufferNoDataEvent_DeviceInWrongMode	the device is not in the proper mode to send expected data. */
	kCMIOSampleBufferNoDataEvent_ProcessingError		= 4,	/*! @constant kCMIOSampleBufferNoDataEvent_ProcessingError	a processing error occurred. */
	kCMIOSampleBufferNoDataEvent_SleepWakeCycle		= 5		/*! @constant kCMIOSampleBufferNoDataEvent_SleepWakeCycle		a sleep/wake cycle is in progress. */
};

//=============================================================================
//	Constants that specify required buffer attachments
//=============================================================================

/*!
	@const		kCMIOSampleBufferAttachmentKey_DiscontinuityFlags
	@discussion	A CFNumber of kCFNumberSInt32Type. The discontinuity flags
				are used to denote that the given buffer represents a
				discontinuity in a stream of buffers.  Its various values
				are defined in CMIOTypes.h.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_DiscontinuityFlags API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_SequenceNumber
	@discussion	A CFNumber of kCFNumberSInt64Type. Provides a number that
				increments monotonically for every buffer of a given stream;
				it can be inquired upon and used to detect gaps in the
				stream (for example, a buffer was dropped somewhere will
				reveil itself by a gap in the sequence of sequence numbers).
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_SequenceNumber API_AVAILABLE(macos(10.7));

//=============================================================================
//	Constants that specify optional buffer attachments (clients may extend
//	this set)
//=============================================================================

/*!
	@const		kCMIOSampleBufferAttachmentKey_HDV1_PackData
	@discussion An AVS::HDV1PackData structure, as defined by AVC Video Services.
				Attached to video MPEG-2 video buffers that came from a transmit
				stream that had HDV-1 Pack data.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_HDV1_PackData API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_HDV2_VAUX
	@discussion An AVS::HDV2VideoFramePack structure, as defined by AVC Video
				Services.  Attached to video MPEG-2 video buffers that came from
				a transmit stream that had HDV-2 VAUX data.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_HDV2_VAUX API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_CAAudioTimeStamp
	@discussion A CFData that contains a CoreAudio AudioTimeStamp structure, as
				defined CoreAudioTypes.h.  Attached to buffers provided by
				CoreAudio devices.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_CAAudioTimeStamp API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_SMPTETime
	@discussion A CFData that contains CoreAudio SMPTETime structure, as defined
				CoreAudioTypes.h.  Attached to buffers that have an associated
				SMPTE time.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_SMPTETime API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_NativeSMPTEFrameCount
	@discussion A CFNumber of kCFNumberSInt32Type.  Attached to buffers that are
				associated with a SMPTE timecode that increments at a rate that
				is not the rate represented by the buffer.  For example, a buffer
				might contain 24P video that is associated with a 30FPS SMPTE
				timecode;  as the SMPTE timecodes are viewed as a stream, there
				will be gaps.  This attachment allows for an annotation to the
				buffer that will not include gaps.  Buffer clients interested in
				looking for gaps in  the SMPTE timecode can inquire about this
				property, and if it exists, check to see that it increments
				monotonically.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_NativeSMPTEFrameCount API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_NumberOfVideoFramesInBuffer
	@discussion	A CFNumber of kCFNumberSInt32Type.  Attached to buffers containing
				an MPEG-2 transmit stream that was contains multiplexed video frames.
				It specifies how many video frames are represented by the buffer.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_NumberOfVideoFramesInBuffer API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_NumberOfVideoFramesInGOP
	@discussion	A CFNumber of kCFNumberSInt32Type. Attached to buffers containing
				an MPEG-2 video I-Frame that is being multiplexed with audio for
				output.  It specifies how many frames are contained in the GOP
				that is started by the I-Frame.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_NumberOfVideoFramesInGOP API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_MuxedSourcePresentationTimeStamp
	@discussion	A CFDictionary that is a serialized CMTime. Attached to buffers
				of multiplexed data, and indicates a presentation timestamp for
				the muxed data that is based on the source data.  Typically used
				to drive the clock abstraction for an output device in order to
				provide a preview of the source data.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_MuxedSourcePresentationTimeStamp API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_HostTime
	@discussion	A CFNumber of kCFNumberSInt64Type. Attached to buffers that are
				associated with a realtime source or destination that is related
				to the CPU's hosttime in nanoseconds.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_HostTime API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_RepeatedBufferContents
	@discussion	A CFBoolean. Attached to buffers (and having the value
				kCFBooleanTrue) if the contents of that buffer is identical
				to the previous buffer in its stream.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_RepeatedBufferContents API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_SourceAudioFormatDescription
	@discussion	A CMFormatDescription. Audio buffers traveling through a 
                CMIO graph may be converted, mixed, or otherwise transformed.
                Downstream units may still desire to know the source format
                from which an audio buffer was derived.  Units dealing with
                audio data should propagate this attachment if it is present.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_SourceAudioFormatDescription API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_PulldownCadenceInfo
	@discussion	A CMIOPulldownCadenceInfo. Video buffers may come from a source
				that has been pulled down (for example, 24p buffers recorded at
				30p).  These buffers can use this attachment to specify where
				this buffer falls in the cadence.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_PulldownCadenceInfo API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_ClosedCaptionSampleBuffer
	@discussion	A CMSampleBuffer. Video buffers with associated closed caption
				data may attach the data as a CMSampleBuffer.  This technique
				is used by the CMIO VDIG input unit if closed caption data
				is available for the current video frame.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_ClosedCaptionSampleBuffer API_AVAILABLE(macos(10.7));

/*!
	@const		kCMIOSampleBufferAttachmentKey_ClientSequenceID
	@discussion	A CF obect.  Attached to buffers output from units that
				support kCMIOUnitProperty_ClientSequenceID.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_ClientSequenceID API_AVAILABLE(macos(10.8));

/*!
	@const		kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers
	@discussion	A CFDictionary. Screen capture buffers will have this
				attachment so that clients can have some information
				as to the approximate state of the mouse and keyboard
				modifiers when the screen was captured.  The following
				keys will be present in the buffer:
				
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorPositionX
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorPositionY
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_MouseButtonState
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorIsVisible
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorFrameRect
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorReference
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorScale
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_KeyboardModifiers
					kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_KeyboardModifiersEvent
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers API_AVAILABLE(macos(10.8));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorPositionX
	@discussion	Used to look up a CFNumber from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the approximate X coordinate of the cursor hotspot when the screen was
				captured (in the cursor’s flipped coordinate system, origin is the top left of the display and not relative to the capture area).
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorPositionX API_AVAILABLE(macos(10.8));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorPositionY
	@discussion	Used to look up a CFNumber from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the approximate Y coordinate of the cursor hotspot when the screen was
				captured (in the cursor’s flipped coordinate system, origin is the top left of the display and not relative to the capture area).
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorPositionY API_AVAILABLE(macos(10.8));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_MouseButtonState
	@discussion	Used to look up a CFNumber from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the approximate state of the mouse buttons when the screen was
				captured.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_MouseButtonState API_AVAILABLE(macos(10.8));
	
/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorIsVisible
	@discussion	Used to look up a CFBoolean from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the visibility of the mouse cursor when the screen was
				captured.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorIsVisible API_AVAILABLE(macos(10.13));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorFrameRect
	@discussion	Used to look up a CFDictionary representation of a CGRect from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the frame CGRect as dictionary of the cursor when the screen was captured relative to the capture area.
 				The origin is at the lower left of the capture area.
 */
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorFrameRect API_AVAILABLE(macos(10.13));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorReference
	@discussion	Used to look up a NSCursor reference from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the NSCursor when the screen was captured.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorReference API_AVAILABLE(macos(10.13));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorSeed
	@discussion	Used to look up the cursor seed value from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the CFNumber of the seed value for the cursor referenced by
				kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorReference;
				changes in this number reflect that the cursor has changed.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorSeed API_AVAILABLE(macos(10.13));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorScale
	@discussion	Used to look up a CFNumber from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the cursor scaling when the screen was captured.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorScale API_AVAILABLE(macos(10.13));
	
/*!
 	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorIsDrawnInFramebuffer
 	@discussion	Used to look up a CFBoolean from the CFDictionary specified by
 				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
 				if the cursor is being drawn at the display level when the screen was
 				captured (if TRUE, the CursorFrameRect may not represent accurately the frame CGRect of the cursor image being drawn).
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_CursorIsDrawnInFramebuffer API_AVAILABLE(macos(10.14));

/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_KeyboardModifiers
	@discussion	Used to look up a CFNumber from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the approximate state of the keyboard modifiers when the screen was
				captured.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_KeyboardModifiers API_AVAILABLE(macos(10.8));
	
/*!
	@const		kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_KeyboardModifiersEvent
	@discussion	Used to look up a CFNumber from the CFDictionary specified by
				kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers.  It specifies
				the approximate state of the keyboard modifiers when the screen was
				captured as define in NSEvent.
*/
extern CFStringRef kCMIOSampleBufferAttachment_MouseAndKeyboardModifiersKey_KeyboardModifiersEvent API_AVAILABLE(macos(10.14));

//=============================================================================
//	Constants that specify marker buffers
//=============================================================================

/*!
	@const		kCMIOSampleBufferAttachmentKey_NoDataMarker
	@discussion	A CFNumber of kCFNumberSInt32Type. Attached to buffers representing
				that a device has stopped returning data.  The value of this attachment
				is the same as for the discontinuity flags.
*/
extern CFStringRef kCMIOSampleBufferAttachmentKey_NoDataMarker API_AVAILABLE(macos(10.7));

//=============================================================================
//	Constants that specify known block buffer attachments
//=============================================================================

/*!
	@const		kCMIOBlockBufferAttachmentKey_CVPixelBufferReference
	@discussion A CVPixelBufferRef, as defined by CoreVideo.
				Attached to block buffers that wrap a Core Video Pixel Buffer.
*/
extern CFStringRef kCMIOBlockBufferAttachmentKey_CVPixelBufferReference API_AVAILABLE(macos(10.7));

//=============================================================================
//	Creators/Destructors
//=============================================================================

/*!
	@function	CMIOSampleBufferCreate
	
	@abstract	Creates a CoreMedia Sample Buffer that can be used in a CMIO Graph.
	@discussion	While CoreMedia Sample Buffers are used in CMIO Graphs, the breadth
				of their flexibility is not supported.  For example, CoreMedia Sample
				Buffers may represent more than one frame of video data;  CMIO
				Graphs support only one frame of video per buffer.
				
				All parameters are copied; on return, the caller can release them,
				free them, reuse them or whatever.  On return, the caller owns the returned CMSampleBuffer, and
				must release it when done with it.
				
				Example of usage for in-display-order video frames:
<ul>				dataBuffer: contains 1 Motion JPEG frame
<br>				dataFormatDescription: describes Motion JPEG video
<br>				numSamples: 1
<br>				numSampleTimingEntries: 1
<br>				sampleTimingArray: {duration = 3003/90000, presentationTimeStamp = 0/90000, decodeTimeStamp = invalid }
<br>				numSampleSizeEntries = 1
<br>				sampleSizeArray: {size of the video frame}
</ul>
				Example of usage for out-of-display-order video frames:
<ul>				dataBuffer: contains 1 HDV frame
<br>				dataFormatDescription: describes H.264 video
<br>				numSamples: 1
<br>				numSampleTimingEntries: 1
<br>				sampleTimingArray: {duration = 3003/90000, presentationTimeStamp = 9009/90000, decodeTimeStamp = 3003/90000}
<br>				numSampleSizeEntries = 1
<br>				sampleSizeArray: {size of the video frame}
</ul>
				Example of usage for compressed audio:
<ul>				dataBuffer: contains 24 compressed AAC packets
<br>				dataFormatDescription: describes 44.1kHz AAC audio
<br>				numSamples: 24
<br>				numSampleTimingEntries: 1
<br>				sampleTimingArray: {duration = 1024/44100, presentationTimeStamp = 0/44100, decodeTimeStamp = invalid }
<br>				numSampleSizeEntries: 24
<br>				sampleSizeArray:
<ul>					{191, 183, 208, 213, 202, 206, 209, 206, 204, 192, 202, 277,
<br>					 282, 240, 209, 194, 193, 197, 196, 198, 168, 199, 171, 194}
</ul>
				Example of usage for compressed audio:
<ul>				dataBuffer: contains 1 HDV audio packet
<br>				dataFormatDescription: describes 48kHz MPEG-1 Layer II audio
<br>				numSamples: 1
<br>				numSampleTimingEntries: 1
<br>				sampleTimingArray: {duration = 2160/90000, presentationTimeStamp = 0/90000, decodeTimeStamp = invalid }
<br>				numSampleSizeEntries = 1
<br>				sampleSizeArray: {1152}
</ul>
				Example of usage for uncompressed interleaved audio:
<ul>				dataBuffer: contains 24000 uncompressed interleaved stereo frames, each containing 2 Float32s =
<ul>					{{L,R},
<br>					 {L,R},
<br>					 {L,R}, ...}
</ul>
<br>				dataFormatDescription: describes two-channel 48kHz Float32 interleaved audio
<br>				numSamples: 24000
<br>				numSampleTimingEntries: 1
<br>				sampleTimingArray: {duration = 1/48000, presentationTimeStamp = 0/90000, decodeTimeStamp = invalid }
<br>				numSampleSizeEntries: 1
<br>				sampleSizeArray: {8}
</ul>
				Example of usage for uncompressed non-interleaved audio:
<ul>				dataBuffer: contains 24000 uncompressed interleaved stereo frames, each containing 2 (non-contiguous) Float32s =
<ul>					{{L,L,L,L,L,...},
<br>					 {R,R,R,R,R,...}}
</ul>
<br>				dataFormatDescription: describes two-channel 48kHz Float32 non-interleaved audio
<br>				numSamples: 24000
<br>				numSampleTimingEntries: 1
<br>				sampleTimingArray: {duration = 1/48000, presentationTimeStamp = 0/90000, decodeTimeStamp = invalid }
<br>				numSampleSizeEntries: 0
<br>				sampleSizeArray: NULL (because the samples are not contiguous)
</ul>

	@result		Returns paramErr if there is an error in parameters, memFullErr if memory
				could not be allocated, and noErr for success.  In addition, errors
				returned by CMSampleBufferCreate() will be passed back.
*/
extern OSStatus CMIOSampleBufferCreate(
	CFAllocatorRef allocator,						/*! @param allocator
														The allocator to use for allocating the CMSampleBuffer object.
														Pass kCFAllocatorDefault to use the default allocator. */
	CMBlockBufferRef dataBuffer,					/*! @param dataBuffer
														CMBlockBuffer for the media data. This can be NULL for special-use
														cases (such as a no-data proxy buffer), or a CMBlockBuffer
														that already contains the media data. */
	CMFormatDescriptionRef formatDescription,		/*! @param formatDescription
														A description of the media data's format. */
	UInt32 numSamples,								/*! @param numSamples
														Number of samples represented by the buffer. */
	UInt32 numSampleTimingEntries,					/*! @param numSampleTimingEntries
														Number of entries in sampleTimingArray. Must be 0, 1, or numSamples. */
	const CMSampleTimingInfo *sampleTimingArray,	/*! @param sampleTimingArray
														A CMSampleTimingInfo struct that provides the timing information
														for the sample. */
	UInt32 numSampleSizeEntries,					/*! @param numSampleSizeEntries
														Number of entries in sampleSizeArray. Must be 0, 1, or numSamples. */
	const size_t *sampleSizeArray,					/*! @param sampleSize
														Array of size entries, one entry per sample. If all samples have the
														same size, you can pass a single size entry containing the size of one sample. Can be NULL. Must be
														NULL if the samples are non-contiguous in the buffer (eg. non-interleaved audio, where the channel
														values for a single sample are scattered through the buffer). */
	UInt64 sequenceNumber,							/*! @param sequenceNumber
														Denotes the position of a buffer in a stream.  The sequence number should increment by 1
														for every buffer in the stream;  clients examine this value in order to determine
														if data has been dropped due to some exception during processing (most commonly
														due to insufficient bandwidth). */
	UInt32 discontinuityFlags,						/*! @param discontinuityFlags
														This value will be non-zero for buffers that represent a point of discontinuity
														in their constituant stream.  Values as specified in CMIOTypes.h. */
	CMSampleBufferRef *sBufOut						/*! @param sBufOut
														Returned newly created CMSampleBuffer. */
	) API_AVAILABLE(macos(10.7));

/*!
	@function	CMIOSampleBufferCreateForImageBuffer
	@abstract	Creates a CMSampleBuffer that can be used in a CMIO Graph, that contains a CVImageBuffer
				instead of a CMBlockBuffer.
	@discussion	This routine is a specialized version of CMIOSampleBufferCreate.
				See the description of that routine for background information.
				
				Unlike a CMBlockBuffer which can reference many samples, a CVImageBuffer is defined to
				reference only one sample;  therefore this routine has fewer parameters then
				CMIOSampleBufferCreate.
				
				Sample timing information, which is a vector for CMIOSampleBufferCreate,
				consists of only one value for this routine.
				
				The concept of sample size does not apply to CVImageBuffers.  As such, CMSampleBufferGetSampleSizeArray
				will return kCMSampleBufferError_BufferHasNoSampleSizes, and CMSampleBufferGetSampleSize
				will return 0.
				
				Because CVImageBuffers hold visual data, the format description provided is a
				CMVideoFormatDescription.  The format description must be consistent with formatting
				information attached to the CVImageBuffer. The width, height, and codecType must match
				(for CVPixelBuffers the codec type is given by CVPixelBufferGetPixelFormatType(pixelBuffer);
				for other CVImageBuffers, the codecType must be 0). The format description extensions must
				match the image buffer attachments for all the keys in the list returned by
				CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers (if absent in either they
				must be absent in both).
*/
extern OSStatus CMIOSampleBufferCreateForImageBuffer(
	CFAllocatorRef allocator,						/*! @param allocator
														The allocator to use for allocating the CMSampleBuffer object.
														Pass kCFAllocatorDefault to use the default allocator. */
	CVImageBufferRef imageBuffer,					/*! @param imageBuffer
														CVImageBuffer for the media data. This can be a CVImageBuffer whose content
														has not yet been rendered, or a CVImageBuffer that already contains the media data
														(in which case dataReady should be true).  May not be NULL. */
	CMVideoFormatDescriptionRef formatDescription,	/*! @param formatDescription
														A description of the media data's format. See discussion above for constraints.
														May not be NULL. */
	const CMSampleTimingInfo *sampleTiming,			/*! @param sampleTiming
														A CMSampleTimingInfo struct that provides the timing information for the media
														represented by the CVImageBuffer. */
	UInt64 sequenceNumber,							/*! @param sequenceNumber
														Denotes the position of a buffer in a stream.  The sequence number should increment by 1
														for every buffer in the stream;  clients examine this value in order to determine
														if data has been dropped due to some exception during processing (most commonly
														due to insufficient bandwidth). */
	UInt32 discontinuityFlags,						/*! @param discontinuityFlags
														This value will be non-zero for buffers that represent a point of discontinuity
														in their constituant stream.  Values as specified in CMIOTypes.h. */
	CMSampleBufferRef *sBufOut						/*! @param sBufOut
														Returned newly created CMSampleBuffer. */
	) API_AVAILABLE(macos(10.7));

/*!
	@function	CMIOSampleBufferCreateNoDataMarker
	@abstract	Creates a CMSampleBuffer with no data and one buffer-level special marker attachment that
				denotes that no data is available from the device.
	@discussion	It is often important for elements of a CMIO graph to know that a device has stopped
				sending data.  A special buffer can be placed in the stream of buffers processed by the
				Graph so that Units will synchronously get notified that the device has stopped sending
				data.

	@result		Returns paramErr if there is an error in parameters, memFullErr if memory
				could not be allocated, and noErr for success.
*/
extern OSStatus CMIOSampleBufferCreateNoDataMarker
(
	CFAllocatorRef allocator,		/*! @param allocator
										The allocator to use for allocating the CMSampleBuffer object.
										Pass kCFAllocatorDefault to use the default allocator. */
	UInt32 noDataEvent,				/*! @param noDataEvent
										Type of no-data event being noted.  Defined events are listed in CMIOTypes.h */
	CMFormatDescriptionRef formatDescription,	/*! @param formatDescription
										A description of the media data's format. Can be NULL. */
	UInt64 sequenceNumber,			/*! @param sequenceNumber
										Denotes the position of a buffer in a stream.  The sequence number should increment by 1
										for every buffer in the stream;  clients examine this value in order to determine
										if data has been dropped due to some exception during processing (most commonly
										due to insufficient bandwidth). */
	UInt32 discontinuityFlags,		/*! @param discontinuityFlags
										Discontinuity flags to be associated with the no-data event.  They will be
										augmented to have the kCMIOSampleBufferFlag_NoDataMarker bit set. */
	CMSampleBufferRef *sBufOut		/*! @param sBufOut
										Returned newly created marker CMSampleBuffer. */
	) API_AVAILABLE(macos(10.7));

//=============================================================================
//	Getters/Setters
//=============================================================================

/*!
	@function	CMIOSampleBufferSetSequenceNumber
	@abstract	Sets the sequence number for a CoreMedia Sample Buffer that is being used in a CMIO Graph.
	@discussion	Sequence numbers are a required attachment to CoreMedia Sample Buffers being used in a
				CMIO Graph.  They allow a unit to know the position of a buffer in a sequence of
				buffers, and to look for gaps where data may have been lost.  Normally, the sequence
				number starts at 0 and increases by one for each subsequent buffer.  As the buffer
				flows through a CMIO Graph, a Unit may have reason to reassign the sequence number
				to a new value.  NOTE:  in order to prevent memory corruption and other errors,
				this function should only be called if the caller is sure that it has the sole
				reference to the buffer;  if this cannot be guarenteed, then the caller should
				first create a copy of the buffer using CMSampleBufferCreateCopy().
*/
extern void CMIOSampleBufferSetSequenceNumber(
	CFAllocatorRef allocator,	/*! @param allocator
										The allocator to use for allocating the CFNumber needed to store the flags.
										Pass kCFAllocatorDefault to use the default allocator. */
	CMSampleBufferRef sbuf,		/*! @param sbuf
										CMSampleBuffer being modified. */
	UInt64 sequenceNumber		/*! @param sequenceNumber
										New sequence number for the buffer. */
	) API_AVAILABLE(macos(10.7));

/*!
	@function	CMIOSampleBufferGetSequenceNumber
	@abstract	Returns the sequence number for a CoreMedia Sample Buffer that is being used in a CMIO Graph.
	@discussion Sequence numbers are a required attachment to CoreMedia Sample Buffers being used in a CMIO Graph.

	@result		Returns kCMIOInvalidSequenceNumber if there is an error in parameters, or if no sequence number
				was attached to the buffer.
*/
extern UInt64 CMIOSampleBufferGetSequenceNumber(
	CMSampleBufferRef sbuf		/*! @param sbuf
									CMSampleBuffer being interrogated. */
	) API_AVAILABLE(macos(10.7));

/*!
	@function	CMIOSampleBufferSetDiscontinuityFlags
	@abstract	Sets the discontinuity flags for a CoreMedia Sample Buffer that is being used in a CMIO Graph.
	@discussion	Discontinuity flags are a required attachment to CoreMedia Sample Buffers being used in a
				CMIO Graph.  As the buffer flows through a CMIO Graph, a Unit may detect a discontinuity
				and flag the buffer as having such.  NOTE:  in order to prevent memory corruption and other
				errors, this function should only be called if the caller is sure that it has the sole
				reference to the buffer;  if this cannot be guarenteed, then the caller should first create
				a copy of the buffer using CMSampleBufferCreateCopy().
*/
extern void CMIOSampleBufferSetDiscontinuityFlags(
	CFAllocatorRef allocator,		/*! @param allocator
										The allocator to use for allocating the CFNumber needed to store the flags.
										Pass kCFAllocatorDefault to use the default allocator. */
	CMSampleBufferRef sbuf,			/*! @param sbuf
										CMSampleBuffer being modified. */
	UInt32 discontinuityFlags		/*! @param discontinuityFlags
										New state of the buffer's discontinuity. */
	) API_AVAILABLE(macos(10.7));

/*!
	@function	CMIOSampleBufferGetDiscontinuityFlags
	@abstract	Returns the discontinuity flags for a CoreMedia Sample Buffer that is being used in a CMIO Graph.
	@discussion Discontinuity flags are a required attachment to CoreMedia Sample Buffers being used in a
				CMIO Graph.

	@result		Returns kCMIOSampleBufferDiscontinuityFlag_UnknownDiscontinuity if an error occurs.
*/
extern UInt32 CMIOSampleBufferGetDiscontinuityFlags(
	CMSampleBufferRef sbuf		/*! @param sbuf
										CMSampleBuffer being interrogated. */
	) API_AVAILABLE(macos(10.7));

/*!
	@function	CMIOSampleBufferCopyNonRequiredAttachments
	@abstract	Copies all optional attachments.
	@discussion This convenience function copies all non-required attachment
				values (i.e., the sequence number and discontinuity flags will not be
				copied).

	@result		Returns paramErr if there is an error in parameters, and noErr for success.
*/
extern OSStatus CMIOSampleBufferCopyNonRequiredAttachments(
	CMSampleBufferRef sourceSBuf,		/*! @param sourceSBuf
											CMSampleBuffer whose attachments are being copied. */
	CMSampleBufferRef destSBuf,			/*! @param destSBuf
											CMSampleBuffer that will receive the copies. */
	CMAttachmentMode attachmentMode		/*! @param attachmentMode
											Mode of the attachments being copied. */
	) API_AVAILABLE(macos(10.7));
											
											
/*!
	@function	CMIOSampleBufferCopySampleAttachments
	@abstract	Copies sample attachments from the CMSampleBufferGetSampleAttachmentsArray()
				CFArrayRef from the source CMSampleBuffer to the destination
				CMSampleBuffer.
	@discussion This convenience function copies all sample attachments from the
				source buffer's sample attachments array to the destination buffer's.
				If the source CMSampleBuffer has no sample attachments, nothing
				happens.

	@result		Returns paramErr if there is an error in parameters, and noErr for success.
*/
extern OSStatus CMIOSampleBufferCopySampleAttachments(
	CMSampleBufferRef sourceSBuf,		/*! @param sourceSBuf
											CMSampleBuffer whose attachments are being copied. */
	CMSampleBufferRef destSBuf			/*! @param destSBuf
											CMSampleBuffer that will receive the copies. */
	) API_AVAILABLE(macos(10.7));

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif
