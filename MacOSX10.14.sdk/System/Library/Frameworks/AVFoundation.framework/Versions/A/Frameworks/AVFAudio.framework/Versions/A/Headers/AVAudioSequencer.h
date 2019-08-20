/*
	File:		AVAudioSequencer.h
	Framework:	AVFoundation

	Copyright (c) 2015 Apple Inc. All Rights Reserved.
*/

#if !0

#import <Foundation/Foundation.h>

#if __has_include(<CoreMIDI/MIDIServices.h>)
	#import <CoreMIDI/MIDIServices.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class AVAudioUnit;
@class AVAudioTime;
@class AVAudioEngine;
@class AVMusicTrack;
@class AVMusicTrackEventIterator;
@class AVAudioSequencer;

/*!	@typedef AVMusicTimeStamp
	@abstract A fractional number of beats
	
	@discussion
		This is used for all sequencer timeline-related methods.  The relationship between this
		value and time in seconds is determined by the sequence's tempo.
*/
typedef Float64 AVMusicTimeStamp;

/*! @typedef AVMusicSequenceLoadOptions
	@abstract Determines whether data on different MIDI channels is mapped to multiple tracks, or
		if the tracks are preserved as-is.
	@discussion
		If AVMusicSequenceLoadSMF_ChannelsToTracks is set, the loaded MIDI Sequence will contain a
		tempo track, one track for each MIDI channel that is found in the SMF, and one track for
		SysEx and/or MetaEvents (this will be the last track in the sequence).

		If AVMusicSequenceLoadSMF_ChannelsToTracks is not set, the loadad MIDI Sequence will
		contain one track for each track that is found in the SMF, plus a tempo track (if not found
		in the SMF).
		
		API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
*/
typedef NS_OPTIONS(NSUInteger, AVMusicSequenceLoadOptions) {
	AVMusicSequenceLoadSMF_PreserveTracks		= 0,				// 0x00
	AVMusicSequenceLoadSMF_ChannelsToTracks		= (1UL << 0)		// 0x01
};

/*! @typedef AVBeatRange
	@abstract Used to describe a specific time range within an AVMusicTrack.
*/
typedef struct _AVBeatRange {
	AVMusicTimeStamp start;
	AVMusicTimeStamp length;
} AVBeatRange;

NS_INLINE AVBeatRange AVMakeBeatRange(AVMusicTimeStamp startBeat, AVMusicTimeStamp lengthInBeats) {
	AVBeatRange r;
	r.start = startBeat;
	r.length = lengthInBeats;
	return r;
}

/*! @class AVAudioSequencer
	@abstract A collection of MIDI events organized into AVMusicTracks, plus a player to play back the events.
*/
OS_EXPORT API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioSequencer : NSObject {
@protected
	void *_impl;
}

/*! @method init
	@abstract
		Initialize a new sequencer, which will not be connected to an audio engine.
	@discussion
		This is used to create a sequencer whose tracks will only send events to external MIDI endpoints.
*/
- (instancetype)init	API_UNAVAILABLE(tvos);

/*! @method initWithAudioEngine:
	@abstract
		Initialize a new sequencer, handing it the audio engine.
*/
- (instancetype)initWithAudioEngine:(AVAudioEngine *)engine;

/*! @method loadFromURL:options:error:
	@abstract Load the file referenced by the URL and add the events to the sequence
	@param fileURL
	@param options
		determines how the file's contents are mapped to tracks inside the sequence
	@param outError
*/
- (BOOL)loadFromURL:(NSURL *)fileURL options:(AVMusicSequenceLoadOptions)options error:(NSError **)outError;

/*! @method loadFromData:options:error:
	@abstract Parse the data and add the its events to the sequence
	@param data
	@param options
		determines how the contents are mapped to tracks inside the sequence
	@param outError
*/
- (BOOL)loadFromData:(NSData *)data options:(AVMusicSequenceLoadOptions)options error:(NSError **)outError;

/*! @method writeToURL:SMPTEResolution:replaceExisting:error:
	@abstract Create and write a MIDI file from the events in the sequence
	@param fileURL
		the path for the file to be created
	@param resolution
		the relationship between "tick" and quarter note for saving to a Standard MIDI File - pass in
		zero to use default - this will be the value that is currently set on the tempo track
	@param replace
		if the file already exists, YES will cause it to be overwritten with the new data.
		Otherwise the call will fail with a permission error.
	@param outError
	@discussion
		Only MIDI events are written when writing to the MIDI file. MIDI files are normally beat
		based, but can also have a SMPTE (or real-time rather than beat time) representation.
		The relationship between "tick" and quarter note for saving to Standard MIDI File
		- pass in zero to use default - this will be the value that is currently set on the tempo track
*/
- (BOOL)writeToURL:(NSURL *)fileURL SMPTEResolution:(NSInteger)resolution replaceExisting:(BOOL)replace error:(NSError **)outError;

/*!	@method dataWithSMPTEResolution:error:
	@abstract Return a data object containing the events from the sequence
	@discussion
		All details regarding the SMPTE resolution apply here as well.
		The returned NSData lifetime is controlled by the client.
*/
- (NSData *)dataWithSMPTEResolution:(NSInteger)SMPTEResolution error:(NSError **)outError;

/*!	@method secondsForBeats:
	@abstract Get the time in seconds for the given beat position (timestamp) in the track
*/
- (NSTimeInterval)secondsForBeats:(AVMusicTimeStamp)beats;

/*!	@method beatsForSeconds:
	@abstract Get the beat position (timestamp) for the given time in the track
*/
- (AVMusicTimeStamp)beatsForSeconds:(NSTimeInterval)seconds;

/* properties */

/*!	@property tracks
	@abstract An NSArray containing all the tracks in the sequence
	@discussion
		Track indices count from 0, and do not include the tempo track.
*/
@property (nonatomic, readonly) NSArray<AVMusicTrack *> *tracks;

/*!	@property tempoTrack
	@abstract The tempo track
	 @discussion
		 Each sequence has a single tempo track. All tempo events are placed into this track (as well
		 as other appropriate events (for instance, the time signature from a MIDI file). The tempo
		 track can be edited and iterated upon as any other track. Non-tempo events in a tempo track
		 are ignored.
*/
@property (nonatomic, readonly) AVMusicTrack *tempoTrack;

/*!	@property userInfo
	@abstract A dictionary containing meta-data derived from a sequence
	@discussion
		The dictionary can contain one or more of the kAFInfoDictionary_* keys
		specified in <AudioToolbox/AudioFile.h>
*/
@property (nonatomic, readonly) NSDictionary<NSString *, id> *userInfo;

@end

@interface AVAudioSequencer(AVAudioSequencer_Player)

/*! @property currentPositionInSeconds
	@abstract The current playback position in seconds
	@discussion
		Setting this positions the sequencer's player to the specified time.  This can be set while
		the player is playing, in which case playback will resume at the new position.
*/
@property(nonatomic) NSTimeInterval currentPositionInSeconds;

/*! @property currentPositionInBeats
	@abstract The current playback position in beats
	@discussion
		Setting this positions the sequencer's player to the specified beat.  This can be set while
		the player is playing, in which case playback will resume at the new position.
*/
@property(nonatomic) NSTimeInterval currentPositionInBeats;


/*! @property playing
	@abstract Indicates whether or not the sequencer's player is playing
	@discussion
		Returns TRUE if the sequencer's player has been started and not stopped. It may have
		"played" past the end of the events in the sequence, but it is still considered to be
		playing (and its time value increasing) until it is explicitly stopped.
*/
@property(nonatomic, readonly, getter=isPlaying) BOOL playing;

/*! @property rate
	@abstract The playback rate of the sequencer's player
	@discussion
		1.0 is normal playback rate.  Rate must be > 0.0.
*/
@property (nonatomic) float rate;

/*!	@method hostTimeForBeats:error:
	@abstract Returns the host time that will be (or was) played at the specified beat.
	@discussion
		This call is only valid if the player is playing and will return 0 with an error if the
		player is not playing or if the starting position of the player (its "starting beat") was 
		after the specified beat.  The method uses the sequence's tempo map to translate a beat
		time from the starting time and beat of the player.
*/
- (UInt64)hostTimeForBeats:(AVMusicTimeStamp)inBeats error:(NSError **)outError;

/*!	@method beatsForHostTime:error:
	@abstract Returns the beat that will be (or was) played at the specified host time.
	@discussion
		This call is only valid if the player is playing and will return 0 with an error if the
		player is not playing or if the starting time of the player was after the specified host
		time.  The method uses the sequence's tempo map to retrieve a beat time from the starting
		and specified host time.
*/
- (AVMusicTimeStamp)beatsForHostTime:(UInt64)inHostTime error:(NSError **)outError;

/*! @method prepareToPlay
	@abstract Get ready to play the sequence by prerolling all events
	@discussion
		Happens automatically on play if it has not already been called, but may produce a delay in
		startup.
*/
- (void)prepareToPlay;

/*!	@method	startAndReturnError:
	@abstract	Start the sequencer's player
	@discussion
		If the AVAudioSequencer has not been prerolled, it will pre-roll itself and then start.
*/
- (BOOL)startAndReturnError:(NSError **)outError;

/*!	@method	stop
	@abstract	Stop the sequencer's player
	@discussion
		Stopping the player leaves it in an un-prerolled state, but stores the playback position so
		that a subsequent call to startAndReturnError will resume where it left off. This action
		will not stop an associated audio engine.
*/
- (void)stop;

@end


/*! @class AVMusicTrack
	@abstract A collection of music events which will be sent to a given destination, and which can be 
				offset, muted, etc. independently of events in other tracks.
*/
OS_EXPORT API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMusicTrack : NSObject {
@protected
	void *_impl;
}

/* properties */

/*!	@property destinationAudioUnit
	@abstract The AVAudioUnit which will receive the track's events
	@discussion
		This is mutually exclusive with setting a destination MIDIEndpoint.  The AU must already be
		attached to an audio engine, and the track must be part of the AVAudioSequencer associated
		with that engine. When playing, the track will send its events to that AVAudioUnit. The
		destination AU cannot be changed while the track's sequence is playing.
*/
@property (nonatomic, retain, nullable) AVAudioUnit *destinationAudioUnit;

/*!	@property destinationMIDIEndpoint
	@abstract Set the track's target to the specified MIDI endpoint
	@discussion
		This is mutually exclusive with setting a destination audio unit.  Setting this will remove
		the track's reference to an AVAudioUnit destination.  When played, the track will send its
		events to the MIDI Endpoint.  See also MIDIDestinationCreate.  The endpoint cannot be
		changed while the track's sequence is playing.
*/
#if TARGET_OS_OSX || TARGET_OS_IOS
@property (nonatomic) MIDIEndpointRef destinationMIDIEndpoint;
#endif

/*!	@property loopRange
	@abstract The timestamp range in beats for the loop
	@discussion
		The loop is set by specifying its beat range.
*/
@property (nonatomic) AVBeatRange loopRange;

/*!	@property loopingEnabled
	@abstract Determines whether or not the track is looped.
	@discussion
		If loopRange has not been set, the full track will be looped.
*/
@property (nonatomic,getter=isLoopingEnabled) BOOL loopingEnabled;

typedef NS_ENUM(NSInteger, AVMusicTrackLoopCount) {
	AVMusicTrackLoopCountForever		= -1
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!	@property numberOfLoops
	@abstract The number of times that the track's loop will repeat
	@discussion
		If set to AVMusicTrackLoopCountForever, the track will loop forever.
		Otherwise, legal values start with 1.
*/
@property (nonatomic) NSInteger numberOfLoops;

/*! @property offsetTime
	@abstract Offset the track's start time to the specified time in beats
	@discussion
		By default this value is zero.
*/
@property (nonatomic) AVMusicTimeStamp offsetTime;

/*! @property muted
	@abstract Whether the track is muted
*/
@property (nonatomic,getter=isMuted) BOOL muted;

/*! @property soloed
	@abstract Whether the track is soloed
*/
@property (nonatomic,getter=isSoloed) BOOL soloed;

/*! @property lengthInBeats
	@abstract The total duration of the track in beats
	@discussion
		This will return the beat of the last event in the track plus any additional time that may
		be needed for fading out of ending notes or round a loop point to musical bar, etc.  If this
		has not been set by the user, the track length will always be adjusted to the end of the
		last active event in a track and is adjusted dynamically as events are added or removed.

		The property will return the maximum of the user-set track length, or the calculated length.
*/
@property (nonatomic) AVMusicTimeStamp lengthInBeats;

/*! @property lengthInSeconds
	@abstract The total duration of the track in seconds
	@discussion
		This will return time of the last event in the track plus any additional time that may be
		needed for fading out of ending notes or round a loop point to musical bar, etc.  If this
		has not been set by the user, the track length will always be adjusted to the end of the
		last active event in a track and is adjusted dynamically as events are added or removed.

		The property will return the maximum of the user-set track length, or the calculated length.
*/
@property (nonatomic) NSTimeInterval lengthInSeconds;


/*! @property timeResolution
	@abstract The time resolution value for the sequence, in ticks (pulses) per quarter note (PPQN)
	@discussion
		If a MIDI file was used to construct the containing sequence, the resolution will be what
		was in the file. If you want to keep a time resolution when writing a new file, you can
		retrieve this value and then specify it when calling -[AVAudioSequencer
		writeToFile:flags:withResolution]. It has no direct bearing on the rendering or notion of
		time of the sequence itself, just its representation in MIDI files. By default this is set
		to either 480 if the sequence was created manually, or a value based on what was in a MIDI
		file if the sequence was created from a MIDI file.
		
		This can only be retrieved from the tempo track.
*/
@property (nonatomic, readonly) NSUInteger timeResolution;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_BRIDGE
