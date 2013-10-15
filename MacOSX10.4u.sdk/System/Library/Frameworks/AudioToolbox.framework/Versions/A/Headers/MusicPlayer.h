/*
     File:       MusicPlayer.h
 
     Contains:   MusicPlayer application interfaces
 
     Version:    Mac OS X
 
     Copyright:  (c) 2000-2004 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __MusicPlayer
#define __MusicPlayer

#include <AvailabilityMacros.h>
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AudioUnit/MusicDevice.h>
#include <AudioToolbox/AUGraph.h>
#include <CoreMIDI/MIDIServices.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Basic idea behind the Sequencing Services APIs:
//
//		A MusicSequence contains an arbitrary number of tracks (MusicTrack)
//		each of which contains time-stamped (in units of beats)
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
//		- mute / solo state
//		- offset time
//		- loop time and number of loops
//				The default looping behaviour is to loop once through the entire track
//				pass zero in for inNumberOfLoops to loop forever
//		- time units for the event timestamps (beats, seconds, ...)
//			beats go through tempo map, seconds map absolute time
//		- automated - in this case the track:
//			(1) Can only contain parameter events
//				- these events are interpreted as points in the automation curve
//			(2) Track can only address a v2 AudioUnit 
//		- duration - the time of the last event in the track plus any additional time that is allowed
//			when for instance a MIDI file is read in and puts its end of track event past the last event
//			to allow for fading out of ending notes


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// definition of the events supported by the sequencer

// music event types, including both MIDI and "extended" protocol
enum
{
	// Available: Mac OS X 10.0 and later
	kMusicEventType_NULL				= 0,
	kMusicEventType_ExtendedNote,		// note with variable number of arguments (non-MIDI)
	kMusicEventType_ExtendedControl,	// control change (non-MIDI)
	kMusicEventType_ExtendedTempo,		// tempo change in BPM
	kMusicEventType_User,				// user defined data
	kMusicEventType_Meta,				// standard MIDI file meta event
	kMusicEventType_MIDINoteMessage,	// MIDI note-on with duration (for note-off)
	kMusicEventType_MIDIChannelMessage,	// MIDI channel messages (other than note-on/off)
	kMusicEventType_MIDIRawData,		// for system exclusive data

	kMusicEventType_Parameter,			// general purpose AudioUnit parameter, added in 10.2
	kMusicEventType_AUPreset,			// this is the AU's user preset CFDictionaryRef (the ClassInfo property), added 10.3
	kMusicEventType_Last				// always keep at end
};

// these are flags that can be passed in with MusicSequenceLoadSMFDataWithFlags

enum
{
	//if this flag is set the resultant Sequence will contain:
	// a tempo track
	// 1 track for each MIDI Channel that is found in the SMF
	// 1 track for SysEx or MetaEvents - this will be the last track 
	// in the sequence after the LoadSMFWithFlags calls
	kMusicSequenceLoadSMF_ChannelsToTracks 	= (1 << 0)
};
typedef UInt32		MusicSequenceLoadFlags;

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
	UInt8		releaseVelocity;	// was "reserved". 0 is the correct value when you don't know.
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
	UInt8		unused1;
	UInt8		unused2;
	UInt8		unused3;
	UInt32		dataLength;
	UInt8		data[1];
} MIDIMetaEvent;

typedef struct MusicEventUserData
{
	UInt32		length;
	UInt8		data[1];
} MusicEventUserData;

typedef struct ExtendedNoteOnEvent
{
	MusicDeviceInstrumentID		instrumentID;
	MusicDeviceGroupID			groupID;
	Float32						duration;
	MusicDeviceNoteParams		extendedParams;
} ExtendedNoteOnEvent;

typedef struct ExtendedControlEvent
{
	MusicDeviceGroupID			groupID;
	AudioUnitParameterID		controlID;
	Float32						value;
} ExtendedControlEvent;

typedef struct ParameterEvent
{
	AudioUnitParameterID		parameterID;
	AudioUnitScope				scope;
    AudioUnitElement			element;
	Float32						value;
} ParameterEvent;

typedef struct ExtendedTempoEvent
{
	Float64		bpm;
} ExtendedTempoEvent;

typedef struct AUPresetEvent
{
	AudioUnitScope				scope;
    AudioUnitElement			element;
	CFPropertyListRef 			preset;
} AUPresetEvent;

typedef struct OpaqueMusicPlayer		*MusicPlayer;
typedef struct OpaqueMusicSequence		*MusicSequence;
typedef struct OpaqueMusicTrack			*MusicTrack;
typedef struct OpaqueMusicEventIterator *MusicEventIterator;

// See MusicSequenceSetUserCallback
typedef void (*MusicSequenceUserCallback)(	void					 	*inClientData,
											MusicSequence				inSequence,
											MusicTrack					inTrack,
											MusicTimeStamp				inEventTime,
											const MusicEventUserData	*inEventData,
											MusicTimeStamp				inStartSliceBeat,
											MusicTimeStamp				inEndSliceBeat);

enum
{
	kAudioToolboxErr_TrackIndexError 			= -10859,
	kAudioToolboxErr_TrackNotFound				= -10858,
	kAudioToolboxErr_EndOfTrack					= -10857,
	kAudioToolboxErr_StartOfTrack				= -10856,
    kAudioToolboxErr_IllegalTrackDestination	= -10855,
    kAudioToolboxErr_NoSequence 				= -10854,
	kAudioToolboxErr_InvalidEventType			= -10853,
	kAudioToolboxErr_InvalidPlayerState			= -10852,
	kAudioToolboxErr_CannotDoInCurrentContext	= -10863
};

// Can't dispose a sequence whilst a MusicPlayer has it. Thus either, before disposing a MusicSequence
// you either DiposeMusicPlayer or MusicPlayerSetSequence (NULL or another sequence)
// DisposeMusicSequence will return kAudioToolboxErr_CannotDoInCurrentContext if disposing a sequence 
// that is in use.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicPlayer (transport) API's

extern OSStatus
NewMusicPlayer(			MusicPlayer		*outPlayer)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
DisposeMusicPlayer(		MusicPlayer		inPlayer)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern OSStatus
MusicPlayerSetSequence(	MusicPlayer 	inPlayer,
						MusicSequence 	inSequence)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicPlayerGetSequence(	MusicPlayer 	inPlayer,
						MusicSequence 	*outSequence)							AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

								
// The Get and Set Time calls take a specification of time
// as beats. This positions (or retrieves) the time as beats
// based on the attached Sequence of the MusicPlayer 
extern OSStatus
MusicPlayerSetTime(		MusicPlayer 	inPlayer,
						MusicTimeStamp 	inTime)									AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicPlayerGetTime(		MusicPlayer 	inPlayer,
						MusicTimeStamp	*outTime)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// Returns a host time value for a given beats time based on the
// time that the sequence started playing.
//
// As this call is only valid if the player is playing this
// call will return an error if the player is not playing or
// the postion of the player (its "starting beat") when the
// player was started.
// (see the MusicSequence calls for beat<->seconds calls for these speculations)
//
// This call is totally dependent on the Sequence attached to the Player,
// (primarily the tempo map of the Sequence), so the player must have
// a sequence attached to it or an error is returned.
extern OSStatus
MusicPlayerGetHostTimeForBeats(	MusicPlayer 	inPlayer,
								MusicTimeStamp	inBeats,
								UInt64 *		outHostTime)					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// Returns a time in beats given a host time based on the
// time that the sequence started playing.
//
// As this call is only valid if the player is playing this
// call will return an error if the player is not playing, or
// if inHostTime is sometime before the Player was started.
// (see the MusicSequence calls for beat<->seconds calls for these speculations)
//
// This call is totally dependent on the Sequence attached to the Player,
// (primarily the tempo map of the Sequence), so the player must have
// a sequence attached to it or an error is returned.
extern OSStatus
MusicPlayerGetBeatsForHostTime(	MusicPlayer 	inPlayer,
								UInt64			inHostTime,
								MusicTimeStamp *outBeats)						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// allows synth devices to load instrument samples, etc.
extern OSStatus
MusicPlayerPreroll(		MusicPlayer 	inPlayer)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicPlayerStart(		MusicPlayer 	inPlayer)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicPlayerStop(		MusicPlayer 	inPlayer)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// This call returns a non-zero value in outIsPlaying if the player has been
// started and not stopped. It may have "played" past the valid events of the attached
// MusicSequence, but it is still considered to be playing (and its time value increasing)
// in that situation.
extern OSStatus
MusicPlayerIsPlaying(	MusicPlayer 	inPlayer,
						Boolean *		outIsPlaying)							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// This call will Scale the playback rate by the specified amount
// It will alter the scheduling of events - so cannot be 0 or less than zero.
extern OSStatus
MusicPlayerSetPlayRateScalar(	MusicPlayer		inPlayer,
								Float64			inScaleRate)					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
MusicPlayerGetPlayRateScalar(	MusicPlayer		inPlayer,
								Float64 *		outScaleRate)					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicSequence API's

extern OSStatus
NewMusicSequence(			MusicSequence		*outSequence)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
DisposeMusicSequence(		MusicSequence		inSequence)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// create a new track in the sequence
extern OSStatus
MusicSequenceNewTrack(		MusicSequence 		inSequence,
							MusicTrack 			*outTrack)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
													
// removes the track from a sequence and disposes the track
extern OSStatus
MusicSequenceDisposeTrack(	MusicSequence 		inSequence,
							MusicTrack 			inTrack)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
													

extern OSStatus
MusicSequenceGetTrackCount(	MusicSequence 		inSequence,
							UInt32 				*outNumberOfTracks)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
										
extern OSStatus
MusicSequenceGetIndTrack(	MusicSequence 		inSequence,
							UInt32 				inTrackIndex,
							MusicTrack 			*outTrack)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// returns error if track is not found in the sequence
extern OSStatus
MusicSequenceGetTrackIndex(	MusicSequence 		inSequence,
							MusicTrack 			inTrack,
							UInt32				*outTrackIndex)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// Tempo events are segregated onto a separate track when imported from a MIDI File.
// Only tempo events in this special tempo track (which is not accessible with 
// MusicSequenceGetTrackCount / MusicSequenceGetIndTrack) have effect on playback.
// This track may be edited like any other, however.
extern OSStatus
MusicSequenceGetTempoTrack(	MusicSequence		inSequence,
							MusicTrack			*outTrack)						AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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

extern OSStatus
MusicSequenceSetAUGraph(	MusicSequence 	inSequence,
							AUGraph 		inGraph)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern OSStatus
MusicSequenceGetAUGraph(	MusicSequence 	inSequence,
							AUGraph 		*outGraph)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// convenience function which sets the destination of each MusicTrack in the MusicSequence
// to the given MIDIEndpointRef
extern OSStatus
MusicSequenceSetMIDIEndpoint(	MusicSequence 	inSequence,
								MIDIEndpointRef	inEndpoint)						AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;
														

// standard MIDI files (SMF, and RMF)

// MusicSequenceLoadSMF() also intelligently parses an RMID file to extract SMF part
extern OSStatus
MusicSequenceLoadSMF(		MusicSequence 	inSequence,
							const FSSpec	*inFileSpec)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

extern OSStatus
MusicSequenceLoadSMFData(	MusicSequence	inSequence,
							CFDataRef		inData)								AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// passing a value of zero for the flags makes this call equivalent to MusicSequenceLoadSMFData
// a paramErr is returned if the sequence has ANY data in it and the flags value is != 0
// This will create a sequence with the first tracks containing MIDI Channel data
// IF the MIDI file had Meta events or SysEx data, then the last track in the sequence
// will contain that data.
extern OSStatus
MusicSequenceLoadSMFWithFlags(		MusicSequence			inSequence,
									const FSRef *			inFileRef,
									MusicSequenceLoadFlags	inFlags)			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
MusicSequenceLoadSMFDataWithFlags(	MusicSequence	inSequence,
									CFDataRef				inData,
									MusicSequenceLoadFlags	inFlags)			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

								
// inResolution is relationship between "tick" and quarter note for saving to SMF
//  - pass in zero to use default (480 PPQ, normally)
extern OSStatus
MusicSequenceSaveSMF(		MusicSequence 	inSequence,
							const FSSpec	*inFileSpec,
							UInt16			inResolution)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

// inFlags must be zero
extern OSStatus
MusicSequenceSaveMIDIFile(	MusicSequence	inSequence,
							const FSRef		*inParentDirectory,
							CFStringRef		inFileName,
							UInt16			inResolution,
							UInt32			inFlags)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern OSStatus
MusicSequenceSaveSMFData(	MusicSequence	inSequence,
							CFDataRef		*outData,
							UInt16			inResolution)						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


// Additional APIs will be created for persistence (loading/saving) of MusicSequences
// which contain non-MIDI events.  A new sequence data format must be defined.

// "reverses" (in time) all events (including tempo events)
extern OSStatus
MusicSequenceReverse(		MusicSequence	inSequence)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// Returns a seconds value that would correspond to the supplied beats 
extern OSStatus
MusicSequenceGetSecondsForBeats(	MusicSequence		inSequence,
									MusicTimeStamp		inBeats,
									Float64 *			outSeconds)				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// Returns a beats value that would correspond to the supplied seconds 
extern OSStatus
MusicSequenceGetBeatsForSeconds(	MusicSequence		inSequence,
									Float64				inSeconds,
									MusicTimeStamp *	outBeats)				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// This call is used to register (or remove if inCallback is NULL) a callback 
// that the MusicSequence will call for ANY UserEvents that are added to any of the
// tracks of the sequence.
// If there is a callback registered, then UserEvents WILL BE CHASED when 
// MusicPlayerSetTime is called. In that case the inStartSliceBeat and inEndSliceBeat
// will both be the same value and will be the beat that the player is chasing too.
// In normal cases, where the sequence data is being scheduled for playback, the
// following will apply:
//	inStartSliceBeat <= inEventTime < inEndSliceBeat
// The only exception to this is if the track that owns the MusicEvent is looping.
// In this case the start beat will still be less than the end beat (so your callback
// can still determine that it is playing, and what beats are currently being scheduled),
// however, the inEventTime will be the original time-stamped time of the user event. 
extern OSStatus
MusicSequenceSetUserCallback(	MusicSequence				inSequence,
								MusicSequenceUserCallback	inCallback,
								void*						inClientData)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
												
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicTrack API's

extern OSStatus
MusicTrackGetSequence(	MusicTrack 			inTrack,
						MusicSequence		*outSequence)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// This overrides any previous MIDIEndpoint destination or AUNode destination
extern OSStatus
MusicTrackSetDestNode(	MusicTrack 			inTrack,
						AUNode				inNode)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// This overrides any previous MIDIEndpoint destination or AUNode destination
extern OSStatus
MusicTrackSetDestMIDIEndpoint(	MusicTrack			inTrack,
								MIDIEndpointRef		inEndpoint)					AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

// returns kAudioToolboxErr_IllegalTrackDestination if the track destination is
// a MIDIEndpointRef and NOT an AUNode
extern OSStatus
MusicTrackGetDestNode(			MusicTrack 			inTrack,
								AUNode *			outNode)					AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

// returns kAudioToolboxErr_IllegalTrackDestination if the track destination is
// an AUNode and NOT a MIDIEndpointRef
extern OSStatus
MusicTrackGetDestMIDIEndpoint(	MusicTrack			inTrack,
								MIDIEndpointRef	*	outEndpoint)				AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SequenceTrack Properties:
//

// inLength is currently ignored for the properties with fixed size...
extern OSStatus
MusicTrackSetProperty(	MusicTrack 			inTrack,
						UInt32 				inPropertyID,
						void				*inData,
						UInt32				inLength)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// if outData is NULL, then the length of the data will be passed back in outLength
// This allows the client to allocate a buffer of the correct size (useful for variable
// length properties -- currently all properties have fixed size)
extern OSStatus
MusicTrackGetProperty(	MusicTrack 			inTrack,
						UInt32 				inPropertyID,
						void				*outData,
						UInt32				*ioLength)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


// the values for these properties are always passed by addressed (with get or set)
enum
{
		// struct {MusicTimeStamp loopLength; long numberOfLoops;};
	kSequenceTrackProperty_LoopInfo = 0,

		// MusicTimeStamp offsetTime;
	kSequenceTrackProperty_OffsetTime = 1,

		// Boolean muteState;
	kSequenceTrackProperty_MuteStatus = 2,

		// Boolean soloState;
	kSequenceTrackProperty_SoloStatus = 3,

		// UInt32 automatedState;
	kSequenceTrackProperty_AutomatedParameters = 4,		// added in 10.2

		// MusicTimeStamp trackLength
	kSequenceTrackProperty_TrackLength = 5				// added in 10.3
};



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Editing operations on sequence tracks

// Note: All time ranges are as follows [starttime, endtime)
// In other words, the range includes the start time, but includes events only up
// to, but NOT including the end time...

// inMoveTime may be negative to move events backwards in time
extern OSStatus
MusicTrackMoveEvents(	MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime,
						MusicTimeStamp		inMoveTime)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern OSStatus
NewMusicTrackFrom(		MusicTrack			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			*outNewTrack)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
												
// removes all events in the given range												
extern OSStatus
MusicTrackClear(		MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// same as MusicTrackClear(), but also moves all following events back
// by the range's duration
extern OSStatus
MusicTrackCut(			MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// the given source range is inserted at inDestInsertTime in inDestTrack
// (all events at and after inDestInsertTime in inDestTrack are moved forward by the
//  range's duration)
extern OSStatus
MusicTrackCopyInsert(	MusicTrack 			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			inDestTrack,
						MusicTimeStamp		inDestInsertTime)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// the given source range is merged with events starting at inDestInsertTime in inDestTrack
extern OSStatus
MusicTrackMerge(		MusicTrack 			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			inDestTrack,
						MusicTimeStamp		inDestInsertTime)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
extern OSStatus
NewMusicEventIterator(				MusicTrack 			inTrack,
									MusicEventIterator *outIterator)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
													
extern OSStatus
DisposeMusicEventIterator(			MusicEventIterator	inIterator)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// passing in kMusicTimeStamp_EndOfTrack for inBeat will position "iterator" to the end of track
//    	(which is pointing to the space just AFTER the last event)
//		(use MusicEventIteratorPreviousEvent() to backup one, if you want last event)
extern OSStatus
MusicEventIteratorSeek(				MusicEventIterator 	inIterator,
									MusicTimeStamp 		inTimeStamp)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// seeks track "iterator" to the next event
//  (if the iterator is at the last event, then it moves PAST the last event and no longer points to an event
// ALWAYS check to see if there is an event at the iterator
extern OSStatus
MusicEventIteratorNextEvent(		MusicEventIterator 	inIterator)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// seeks track "iterator" to the previous event
//  (if the iterator is already at the first event, then it remains unchanged and
//   an error is returned)
extern OSStatus
MusicEventIteratorPreviousEvent(	MusicEventIterator 	inIterator)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


// returns an error if the track's "iterator" is currently at the end of the track
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
//		kMusicEventType_Parameter				ParameterEvent*
//		kMusicEventType_AUPreset				AUPresetEvent*
extern OSStatus
MusicEventIteratorGetEventInfo(		MusicEventIterator 		inIterator,
									MusicTimeStamp *		outTimeStamp,
									MusicEventType *		outEventType,
									const void **			outEventData,
									UInt32 *				outEventDataSize)	AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
	
// replaces the current event; note that its type may change but its time may not
extern OSStatus
MusicEventIteratorSetEventInfo(		MusicEventIterator 		inIterator,
									MusicEventType			inEventType,
									const void *			inEventData)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

// deletes the event at the current "iterator"
extern OSStatus
MusicEventIteratorDeleteEvent(		MusicEventIterator	 	inIterator)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern OSStatus
MusicEventIteratorSetEventTime(		MusicEventIterator 		inIterator,
									MusicTimeStamp			inTimeStamp)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// We're NOT CHECKING FOR ERRORS IN THIS EXAMPLE!!!!!!
// To use the iterator going forward when looping...
// 	New Iterator (points at first event)
//	bool hasCurrentEvent;
//	MusicEventIteratorHasCurrentEvent(iter, &hasCurrentEvent);
// 	while (hasCurrentEvent) {
// 		do work... MusicEventIteratorGetEventInfo (iter, ...
//		
//		MusicEventIteratorNextEvent (iter)
//		MusicEventIteratorHasCurrentEvent(iter, &hasCurrentEvent);
//	}

// Or to go back...
// 	New Iterator
// 	MusicEventIteratorSeek (iter, kMusicTimeStamp_EndOfTrack) -> will point it past the last event
//
// 	while (MusicEventIteratorPreviousEvent (iter) == noErr) {
// 		do work... MusicEventIteratorGetEventInfo (iter, ...
//
// 	}

// You can "rock" the Iterator back and forwards as well of course
extern OSStatus
MusicEventIteratorHasPreviousEvent(	MusicEventIterator 	inIterator,
									Boolean	*			outHasPrevEvent)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicEventIteratorHasNextEvent(		MusicEventIterator	inIterator,
									Boolean	*			outHasNextEvent)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicEventIteratorHasCurrentEvent(	MusicEventIterator	inIterator,
									Boolean	*			outHasCurEvent)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// adding time-stamped events to the track

extern OSStatus
MusicTrackNewMIDINoteEvent(			MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDINoteMessage *		inMessage)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
										
extern OSStatus
MusicTrackNewMIDIChannelEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIChannelMessage *	inMessage)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicTrackNewMIDIRawDataEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIRawData *			inRawData)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicTrackNewExtendedNoteEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ExtendedNoteOnEvent	*inInfo)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
										
extern OSStatus
MusicTrackNewExtendedControlEvent(	MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ExtendedControlEvent	*inInfo)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicTrackNewParameterEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ParameterEvent *		inInfo)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
										
extern OSStatus
MusicTrackNewExtendedTempoEvent(	MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									Float64						inBPM)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
										
extern OSStatus
MusicTrackNewMetaEvent(				MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIMetaEvent *		inMetaEvent)	AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
										
extern OSStatus
MusicTrackNewUserEvent(				MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MusicEventUserData *	inUserData)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
MusicTrackNewAUPresetEvent(			MusicTrack 					inTrack,
									MusicTimeStamp			 	inTimeStamp,
									const AUPresetEvent *		inPresetEvent)	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
																								
#if defined(__cplusplus)
}
#endif

#endif // __MusicPlayer
