/*
     File:       MusicPlayer.h
 
     Contains:   MusicPlayer application interfaces
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __MusicPlayer
#define __MusicPlayer

#include <CoreServices/CoreServices.h>

#if TARGET_API_MAC_OSX
#include <AudioUnit/MusicDevice.h>
#include <AudioToolbox/AUGraph.h>
#include <CoreMIDI/MIDIServices.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Basic idea behind the Sequencing Services APIs:
//
//		A MusicSequence contains an arbitrary number of tracks (MusicTrack)
//		each of which contains time-stamped (typically in units of beats, or seconds )
//		events in time-increasing order.  There are various types of events, defined below,
//		including the expected MIDI events, tempo, and extended events.
//		A MusicTrack has properties which may be inspected and assigned, including support
//		for looping, muting/soloing, and time-stamp interpretation.
//		APIs exist for iterating through the events in a MusicTrack, and for performing
//		basic editing operations on them.
//
//		Each MusicSequence may have an associated AUGraph object, which represents a set
//		of AudioUnits and the connections between them.  Then, each MusicTrack of the
//		MusicSequence may address its events to a specific AudioUnit within the AUGraph.
//		In such a manner, it's possible to automate arbitrary parameters of AudioUnits,
//		and schedule notes to be played to MusicDevices (AudioUnit software synthesizers)
//		within an arbitrary audio processing network (AUGraph).
//
// MusicSequence global information is:
//		- an AUGraph
//		- copyright and other textual info
//
// MusicTrack properties are:
//		- AUNode (in the AUGraph) of the AudioUnit addressed by the MusicTrack
//		- textual info
//		- mute / solo state
//		- offset time
//		- loop time and number of loops
//		- time units for the event timestamps (beats, seconds, ...)
//			beats go through tempo map, seconds map absolute time



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// definition of the events supported by the sequencer

// music event types, including both MIDI and "extended" protocol
enum
{
	kMusicEventType_NULL					= 0,
	kMusicEventType_ExtendedNote,		// note with variable number of arguments (non-MIDI)
	kMusicEventType_ExtendedControl,	// control change (non-MIDI)
	kMusicEventType_ExtendedTempo,		// tempo change in BPM
	kMusicEventType_User,				// user defined data
	kMusicEventType_Meta,				// standard MIDI file meta event
	kMusicEventType_MIDINoteMessage,	// MIDI note-on with duration (for note-off)
	kMusicEventType_MIDIChannelMessage,	// MIDI channel messages (other than note-on/off)
	kMusicEventType_MIDIRawData,		// for system exclusive data
	kMusicEventType_Last				// always keep at end
};

typedef UInt32		MusicEventType;
typedef Float64		MusicTimeStamp;

// pass this value in to indicate a time passed the last event in the track
// in this way, it's possible to perform edits on tracks which include all events
// starting at some particular time up to and including the last event
#define kMusicTimeStamp_EndOfTrack			1000000000.0


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// event representation

typedef struct MIDINoteMessage
{
	UInt8		channel;
	UInt8		note;
	UInt8		velocity;
	UInt8		reserved;
	Float32		duration;
} MIDINoteMessage;

typedef struct MIDIChannelMessage
{
	UInt8		status;		// contains message and channel
	
	// message specific data
	UInt8		data1;		
	UInt8		data2;
	UInt8		reserved;
} MIDIChannelMessage;

typedef struct MIDIRawData
{
	UInt32		length;
	UInt8		data[1];
} MIDIRawData;

typedef struct MIDIMetaEvent
{
	UInt8		metaEventType;
	UInt32		dataLength;
	UInt8		data[1];
} MIDIMetaEvent;


typedef struct ExtendedNoteOnEvent
{
	MusicDeviceInstrumentID		instrumentID;
	MusicDeviceGroupID			groupID;
	Float32						duration;
	MusicDeviceNoteParams		extendedParams;
} ExtendedNoteOnEvent;

// allocated space for 16 arguments
typedef struct ExtendedNoteOnEvent16
{
	MusicDeviceInstrumentID		instrumentID;
	MusicDeviceGroupID			groupID;
	Float32						duration;
	MusicDeviceNoteParams16		extendedParams;
} ExtendedNoteOnEvent16;

typedef struct ExtendedControlEvent
{
	MusicDeviceGroupID			groupID;
	AudioUnitParameterID		controlID;
	Float32						value;
} ExtendedControlEvent;

typedef struct ExtendedTempoEvent
{
	Float64		bpm;
} ExtendedTempoEvent;

typedef struct OpaqueMusicPlayer		*MusicPlayer;
typedef struct OpaqueMusicSequence		*MusicSequence;
typedef struct OpaqueMusicTrack			*MusicTrack;
typedef struct OpaqueMusicEventIterator *MusicEventIterator;

enum
{
	kAudioToolboxErr_TrackIndexError 		= -10859,
	kAudioToolboxErr_TrackNotFound			= -10858,
	kAudioToolboxErr_EndOfTrack				= -10857,
	kAudioToolboxErr_StartOfTrack			= -10856,
    kAudioToolboxErr_IllegalTrackDestination = -10855,
    kAudioToolboxErr_NoSequence 			= -10854
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicPlayer (transport) API's

extern OSStatus			NewMusicPlayer(			MusicPlayer		*outPlayer );

extern OSStatus			DisposeMusicPlayer(		MusicPlayer		inPlayer );


extern OSStatus			MusicPlayerSetSequence(	MusicPlayer 	inPlayer,
											MusicSequence 	inSequence);

								

extern OSStatus			MusicPlayerSetTime(		MusicPlayer 	inPlayer,
											MusicTimeStamp 	inTime );

extern OSStatus			MusicPlayerGetTime(		MusicPlayer 	inPlayer,
											MusicTimeStamp	*outTime );

// allows synth devices to load instrument samples, etc.
extern OSStatus			MusicPlayerPreroll(		MusicPlayer 	inPlayer);	



extern OSStatus			MusicPlayerStart(		MusicPlayer 	inPlayer);

extern OSStatus			MusicPlayerStop(		MusicPlayer 	inPlayer);





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicSequence API's

extern OSStatus			NewMusicSequence(			MusicSequence		*outSequence );

extern OSStatus			DisposeMusicSequence(		MusicSequence		inSequence );

// create a new track in the sequence
extern OSStatus			MusicSequenceNewTrack(		MusicSequence 		inSequence,
													MusicTrack 			*outTrack );
													
// removes the track from a sequence and disposes the track
extern OSStatus			MusicSequenceDisposeTrack(	MusicSequence 		inSequence,
													MusicTrack 			inTrack );
													

extern OSStatus			MusicSequenceGetTrackCount(	MusicSequence 		inSequence,
													UInt32 				*outNumberOfTracks );
										
extern OSStatus			MusicSequenceGetIndTrack(	MusicSequence 		inSequence,
													UInt32 				inTrackIndex,
													MusicTrack 			*outTrack );

// returns error code if track is not found in the sequence
extern OSStatus			MusicSequenceGetTrackIndex(	MusicSequence 		inSequence,
													MusicTrack 			inTrack,
													UInt32				*outTrackIndex );

// Tempo events are segregated onto a separate track when imported from a MIDI File.
// Only tempo events in this special tempo track (which is not accessible with 
// MusicSequenceGetTrackCount / MusicSequenceGetIndTrack) have effect on playback.
// This track may be edited like any other, however.
extern OSStatus			MusicSequenceGetTempoTrack(	MusicSequence		inSequence,
													MusicTrack			*outTrack);


// To address the sequence events to a particular AUGraph, use MusicSequenceSetAUGraph()
// By default the first AUNode representing a DLS MusicDevice will be used as the destination
// Please see MusicTrackSetDestNode() in order to change the addressing on a track by track basis.
//
// Instead of addressing a sequence to an AUGraph, the MusicSequenceSetMIDIEndpoint() call may
// be used to set all tracks to address the particular MIDI device.
// It is then possible to override individual tracks to address either a different MIDIEndpoint
// with MusicTrackSetDestMIDIEndpoint() or an AudioUnit with MusicTrackSetDestNode().
// This allows the mixing of sequencing software synths (and other AudioUnits) along with
// MIDI devices.

extern OSStatus			MusicSequenceSetAUGraph(	MusicSequence 	inSequence,
													AUGraph 		inGraph );


extern OSStatus			MusicSequenceGetAUGraph(	MusicSequence 	inSequence,
													AUGraph 		*outGraph);

// convenience function which sets the destination of each MusicTrack in the MusicSequence
// to the given MIDIEndpointRef
extern OSStatus			MusicSequenceSetMIDIEndpoint(	MusicSequence 	inSequence,
														MIDIEndpointRef	inEndpoint );
														


// standard MIDI files (SMF, and RMF)


// MusicSequenceLoadSMF() also intelligently parses an RMID file to extract SMF part
extern OSStatus			MusicSequenceLoadSMF(		MusicSequence 	inSequence,
													FSSpec		 	*inFileSpec );
								
// inResolution is relationship between "tick" and quarter note for saving to SMF
//  - pass in zero to use default (480 PPQ, normally)
extern OSStatus			MusicSequenceSaveSMF(			MusicSequence 	inSequence,
													FSSpec		 	*inFileSpec,
													UInt16			inResolution );

// Additional APIs will be created for persistence (loading/saving) of MusicSequences
// which contain non-MIDI events.  A new sequence data format must be defined.


// "reverses" (in time) all events (including tempo events)
extern OSStatus			MusicSequenceReverse(			MusicSequence inSequence);	


													
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicTrack API's

extern OSStatus			MusicTrackGetSequence(	MusicTrack 			inTrack,
												MusicSequence		*outSequence );

// This overrides any previous MIDIEndpoint destination or AUNode destination
extern OSStatus			MusicTrackSetDestNode(	MusicTrack 			inTrack,
												AUNode				inNode );

// This overrides any previous MIDIEndpoint destination or AUNode destination
extern OSStatus			MusicTrackSetDestMIDIEndpoint(	MusicTrack		inTrack,
														MIDIEndpointRef	inEndpoint );


// returns kAudioToolboxErr_IllegalTrackDestination if the track destination is
// a MIDIEndpointRef and NOT an AUNode
extern OSStatus			MusicTrackGetDestNode(	MusicTrack 			inTrack,
												AUNode				*outNode );

// returns kAudioToolboxErr_IllegalTrackDestination if the track destination is
// an AUNode and NOT a MIDIEndpointRef
extern OSStatus			MusicTrackGetDestMIDIEndpoint(	MusicTrack		inTrack,
														MIDIEndpointRef	*outEndpoint );

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SequenceTrack Properties:
//

// inLength is currently ignored for the properties with fixed size...
extern OSStatus			MusicTrackSetProperty(	MusicTrack 			inTrack,
											UInt32 				inPropertyID,
											void				*inData,
											UInt32				inLength );

// if inData is NULL, then the length of the data will be passed back in outLength
// This allows the client to allocate a buffer of the correct size (useful for variable
// length properties -- currently all properties have fixed size)
extern OSStatus			MusicTrackGetProperty(	MusicTrack 			inTrack,
											UInt32 				inPropertyID,
											void				*inData,
											UInt32				*ioLength );

// Notes on properties
//
//	kSequenceTrackProperty_LoopInfo
//		The default looping behaviour is to loop once through the entire track
//		pass zero in for inNumberOfLoops to loop forever
//		

enum
{
	kSequenceTrackProperty_LoopInfo = 0,		// struct {MusicTimeStamp loopLength; long numberOfLoops;};
	kSequenceTrackProperty_OffsetTime = 1,		// struct {MusicTimeStamp offsetTime;};
	kSequenceTrackProperty_MuteStatus = 2,		// struct {Boolean muteState;};
	kSequenceTrackProperty_SoloStatus = 3		// struct {Boolean soloState;};
};



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Editing operations on sequence tracks

// Note: All time ranges are as follows [starttime, endtime)
// In other words, the range includes the start time, but includes events only up
// to, but NOT including the end time...

// inMoveTime may be negative to move events backwards in time
extern OSStatus			MusicTrackMoveEvents(	MusicTrack 			inTrack,
											MusicTimeStamp		inStartTime,
											MusicTimeStamp		inEndTime,
											MusicTimeStamp		inMoveTime );


extern OSStatus			NewMusicTrackFrom(	MusicTrack			inSourceTrack,
										MusicTimeStamp		inSourceStartTime,
										MusicTimeStamp		inSourceEndTime,
										MusicTrack 			*outNewTrack );
												
// removes all events in the given range												
extern OSStatus			MusicTrackClear(	MusicTrack 			inTrack,
										MusicTimeStamp		inStartTime,
										MusicTimeStamp		inEndTime );
// same as MusicTrackClear(), but also moves all following events back
// by the range's duration
extern OSStatus			MusicTrackCut(		MusicTrack 			inTrack,
										MusicTimeStamp		inStartTime,
										MusicTimeStamp		inEndTime );

// the given source range is inserted at inDestInsertTime in inDestTrack
// (all events at and after inDestInsertTime in inDestTrack are moved forward by the
//  range's duration)
extern OSStatus			MusicTrackCopyInsert(	MusicTrack 			inSourceTrack,
											MusicTimeStamp		inSourceStartTime,
											MusicTimeStamp		inSourceEndTime,
											MusicTrack 			inDestTrack,
											MusicTimeStamp		inDestInsertTime );

// the given source range is merged with events starting at inDestInsertTime in inDestTrack
extern OSStatus			MusicTrackMerge(	MusicTrack 			inSourceTrack,
										MusicTimeStamp		inSourceStartTime,
										MusicTimeStamp		inSourceEndTime,
										MusicTrack 			inDestTrack,
										MusicTimeStamp		inDestInsertTime );


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// actual event representation and manipulation within a track....
//
// Here we need to be very careful to be able to deal with both SMF type of MIDI events, and
// also be upwardly compatible with an extended MPEG4-SA like paradigm!
//
// The solution is to hide the internal event representation from the client
// and allow access to the events through accessor functions.  The user, in this way, can
// examine and create standard events, or any user-defined event.


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sequence track event access and manipulation

// event iterator objects on tracks
extern OSStatus			NewMusicEventIterator(			MusicTrack 			inTrack,
													MusicEventIterator	*outIterator );
													
extern OSStatus			DisposeMusicEventIterator(		MusicEventIterator	inIterator );

// passing in kMusicTimeStamp_EndOfTrack for inBeat will position "iterator" to the end of track
//    	(which is pointing to the space just AFTER the last event)
//		(use MusicEventIteratorPreviousEvent() to backup one, if you want last event)
extern OSStatus			MusicEventIteratorSeek(			MusicEventIterator 	inIterator,
													MusicTimeStamp 		inTimeStamp );

// seeks track "iterator" to the next event
extern OSStatus			MusicEventIteratorNextEvent(	MusicEventIterator 	inIterator);

// seeks track "iterator" to the previous event
//  (if the iterator is already at the first event, then it remains unchanged and
//   an error code is returned)
extern OSStatus			MusicEventIteratorPreviousEvent(MusicEventIterator 	inIterator);


// returns an error code if the track's "iterator" is currently at the end of the track

// depending on the event type, cast the returned void* pointer to:
//
//		kMusicEventType_ExtendedNote			ExtendedNoteOnEvent*
//		kMusicEventType_ExtendedControl			ExtendedControlEvent*
//		kMusicEventType_ExtendedTempo			ExtendedTempoEvent*
//		kMusicEventType_User					<user-defined-data>*
//		kMusicEventType_Meta					MIDIMetaEvent*
//		kMusicEventType_MIDINoteMessage			MIDINoteMessage*
//		kMusicEventType_MIDIChannelMessage		MIDIChannelMessage*
//		kMusicEventType_MIDIRawData				MIDIRawData*
extern OSStatus			MusicEventIteratorGetEventInfo(	MusicEventIterator 	inIterator,
													MusicTimeStamp		*outTimeStamp,
													MusicEventType		*outEventType,
													void				**outEventData,
													UInt32				*outEventDataSize );

// deletes the event at the current "iterator"
extern OSStatus			MusicEventIteratorDeleteEvent(	MusicEventIterator 	inIterator);


extern OSStatus			MusicEventIteratorSetEventTime(	MusicEventIterator 		inIterator,
													MusicTimeStamp			inTimeStamp );

extern OSStatus			MusicEventIteratorHasPreviousEvent(	MusicEventIterator 	inIterator,
														Boolean				*outHasPreviousEvent );

extern OSStatus			MusicEventIteratorHasNextEvent(	MusicEventIterator 		inIterator,
													Boolean					*outHasNextEvent );


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// adding time-stamped events to the track

extern OSStatus			MusicTrackNewMIDINoteEvent(		MusicTrack 				inTrack,
													MusicTimeStamp			inTimeStamp,
													const MIDINoteMessage	*inMessage );
										
extern OSStatus			MusicTrackNewMIDIChannelEvent(	MusicTrack 				inTrack,
													MusicTimeStamp			inTimeStamp,
													const MIDIChannelMessage *inMessage );

extern OSStatus			MusicTrackNewMIDIRawDataEvent(	MusicTrack 				inTrack,
													MusicTimeStamp			inTimeStamp,
													const MIDIRawData		*inRawData );

extern OSStatus			MusicTrackNewExtendedNoteEvent(	MusicTrack 					inTrack,
													MusicTimeStamp				inTimeStamp,
													const ExtendedNoteOnEvent	*inInfo );
										
extern OSStatus			MusicTrackNewExtendedControlEvent(	MusicTrack 					inTrack,
														MusicTimeStamp				inTimeStamp,
														const ExtendedControlEvent	*inInfo );
										
extern OSStatus			MusicTrackNewExtendedTempoEvent(	MusicTrack 				inTrack,
														MusicTimeStamp			inTimeStamp,
														Float64					inBPM);
										
extern OSStatus			MusicTrackNewMetaEvent(			MusicTrack 				inTrack,
													MusicTimeStamp			inTimeStamp,
													void					*inMetaEventInfo,
													UInt32					inMetaEventLength );
										
extern OSStatus			MusicTrackNewUserEvent(			MusicTrack 				inTrack,
													MusicTimeStamp			inTimeStamp,
													void					*inUserData,
													UInt32					inUserDataLength );
																												
#if defined(__cplusplus)
}
#endif

#endif // __MusicPlayer
