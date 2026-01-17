/*
	File:		AVAudioSequencer.h
	Framework:	AVFAudio

	Copyright (c) 2015 Apple Inc. All Rights Reserved.
*/

#import <Foundation/Foundation.h>
#import <AVFAudio/AVAudioTypes.h>

#if __has_include(<CoreMIDI/MIDIServices.h>)
	#import <CoreMIDI/MIDIServices.h>
#endif

#define AVAS_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

@class AVAudioUnit;
@class AVAudioTime;
@class AVAudioEngine;
@class AVMusicTrack;
@class AVAudioSequencer;

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
	AVMusicSequenceLoadSMF_PreserveTracks		= 0,
	AVMusicSequenceLoadSMF_ChannelsToTracks		= (1UL << 0)
};

/*! @typedef AVBeatRange
	@abstract Used to describe a specific time range within an AVMusicTrack.
*/
NS_SWIFT_SENDABLE
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

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
typedef NSString *AVAudioSequencerInfoDictionaryKey NS_TYPED_ENUM;

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyAlbum
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyApproximateDurationInSeconds
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyArtist
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyChannelLayout
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyComments
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyComposer
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyCopyright
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyEncodingApplication
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyGenre
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyISRC
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyKeySignature
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyLyricist
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyNominalBitRate
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyRecordedDate
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeySourceBitDepth
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeySourceEncoder
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeySubTitle
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyTempo
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyTimeSignature
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyTitle
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyTrackNumber
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

AVAS_EXPORT
AVAudioSequencerInfoDictionaryKey AVAudioSequencerInfoDictionaryKeyYear
				API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*! @class AVAudioSequencer
	@abstract A collection of MIDI events organized into AVMusicTracks, plus a player to play back the events.
*/
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
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
        the URL to the file
	@param options
		determines how the file's contents are mapped to tracks inside the sequence
	@param outError
        on exit, if an error occurs, a description of the error
*/
- (BOOL)loadFromURL:(NSURL *)fileURL options:(AVMusicSequenceLoadOptions)options error:(NSError **)outError;

/*! @method loadFromData:options:error:
	@abstract Parse the data and add the its events to the sequence
	@param data
        the data to load from
	@param options
		determines how the contents are mapped to tracks inside the sequence
	@param outError
        on exit, if an error occurs, a description of the error
*/
- (BOOL)loadFromData:(NSData *)data options:(AVMusicSequenceLoadOptions)options error:(NSError **)outError;

/*! @method writeToURL:SMPTEResolution:replaceExisting:error:
	@abstract Create and write a MIDI file containing the events and complete state of the sequence
	@param fileURL
		the path for the file to be created
	@param resolution
		the relationship between "tick" and quarter note for saving to a Standard MIDI File - pass in
		zero to use default - this will be the value that is currently set on the tempo track
	@param replace
		if the file already exists, YES will cause it to be overwritten with the new data.
		Otherwise the call will fail with a permission error.
	@param outError
        on exit, if an error occurs, a description of the error
	@discussion
		A MIDI file saved via this method will contain not only the complete MIDI content of the sequence,
		but also the state of all tracks, including muting, loop points and enablement, etc.  It will also
		contain all non-MIDI AVMusicEvent types which had been added to the sequence's track.
 
		MIDI files are normally beat based, but can also have a SMPTE (or real-time rather than beat time) representation.
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
	@abstract Get the time in seconds for the given beat position (timestamp) in the AVMusicTrack
*/
- (NSTimeInterval)secondsForBeats:(AVMusicTimeStamp)beats;

/*!	@method beatsForSeconds:
	@abstract Get the beat position (timestamp) for the given time in the AVMusicTrack
*/
- (AVMusicTimeStamp)beatsForSeconds:(NSTimeInterval)seconds;

/*!	@method reverseEvents:
	@abstract Reverse the order of all events in all AVMusicTracks, including the tempo track
*/
- (void)reverseEvents API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!	@method createAndAppendTrack:
	@abstract Create a new AVMusicTrack and append it to the AVMusicSequencer's list
*/
- (AVMusicTrack *)createAndAppendTrack API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!	@method removeTrack:
	@abstract Remove the given AVMusicTrack from the AVMusicSequencer.
	@discussion This does not destroy the AVMusicTrack because it may be re-used.
*/
- (BOOL)removeTrack:(AVMusicTrack *)track API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!	@typedef AVAudioSequencerUserCallback
	@abstract
		A block which is called asynchronously during playback whenever an AVMusicUserEvent is
		encountered (see AVMusicUserEvent).
	@param track
		The track which contains the AVMusicUserEvent.
	@param userData
		The raw data that was used to initialize the AVMusicUserEvent.
	@param timeStamp
		The beat location at which the event was found.  This will necessarily be in the past due
		to the asynchronous nature of the callback.
	@discussion
		This callback is delivered on an internal queue and is asynchronous to the rendering thread.
 
		The returned 'userData' will be unique to each AVMusicUserEvent instance.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
typedef void (^AVAudioSequencerUserCallback)(AVMusicTrack *track, NSData *userData, AVMusicTimeStamp timeStamp);

/*!	@method setUserCallback:
	@abstract
		Add a block which will be called each time the AVAudioSequencer encounters an AVMusicUserEvent during playback.
	@discussion
		The same callback is called for events which occur on any track in the sequencer.
 
		Set the block to nil to disable it.
*/
- (void)setUserCallback:(AVAudioSequencerUserCallback _Nullable)userCallback API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/* properties */

/*!	@property tracks
	@abstract An NSArray containing all the AVMusicTracks in the sequence
	@discussion
		This list will not include the tempo track.
*/
@property (nonatomic, readonly) NSArray<AVMusicTrack *> *tracks;

/*!	@property tempoTrack
	@abstract The tempo track
	 @discussion
		Each AVMusicSequence has a single tempo track.
 
		All tempo events read from external MIDI files are placed into this track (as well as other
		appropriate events (e.g., the time signature meta event from the file).
 
		The tempo track can be edited and iterated upon as any other track.
 
		Non-tempo-related events will generate exceptions if added.
*/
@property (nonatomic, readonly) AVMusicTrack *tempoTrack;

/*!	@property userInfo
	@abstract A dictionary containing meta-data derived from a sequence
	@discussion
		The dictionary can contain one or more of the values accessible via the AVAudioSequencerInfoDictionaryKeys.
*/
@property (nonatomic, readonly) NSDictionary<NSString *, id> *userInfo;

@end

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
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
		When the sequencer is associated with an audio engine, the sequencer's player will only
		play if the audio engine is running.
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

/*!
	@define AVMusicTimeStampEndOfTrack
	@abstract	A timestamp used to access all events in a AVMusicTrack via an AVBeatRange.
	@discussion Pass this value as the length of an AVBeatRange to indicate a end time beyond the last
				event in the track.  In this way, it's possible to specify a AVBeatRange which
				include all events starting at some particular time up to and including the last event.
*/
#define AVMusicTimeStampEndOfTrack			DBL_MAX

/*! @class AVMusicTrack
	@abstract	A collection of music events which will be sent to a given destination, and which can be
				offset, muted, etc. independently of events in other tracks.
	@discussion
				AVMusicTrack is not a container of AVMusicEvents - it will not hold references to
				AVMusicEvents that are added, so an application should maintain its own if it is
				desired.
*/
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
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

@class AVMusicEvent;

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMusicTrack(AVMusicTrackEditor)

/*!	@property usesAutomatedParameters
	@abstract	Indicates whether the track is an automation track.
	@discussion
				If set to YES, this can be used to contain, parameter automation events, exclusively.
				Adding any other event types will generate exceptions.
 
				If a track already contains non-parameter events, setting this to YES will
				generate an exception.
 */
@property (readwrite) BOOL usesAutomatedParameters;

/*!	@method	addAvent:atBeat
	@abstract	Adds an AVMusicEvent's contents to a track at the specified AVMusicTimeStamp.
	@param		event			the event to be added
	@param		beat			the AVMusicTimeStamp
	@discussion
				Because event contents are copied into the track, the same event may be added multiple
				times at different timestamps.
 
				There are restrictions on which AVMusicEvent subclasses may be added to different tracks:
 
				- Only AVExtendedTempoEvents and AVMIDIMetaEvents with certain AVMIDIMetaEventTypes
				  can be added to an AVMusicSequence's tempo track (see AVMIDIMetaEvent).
 
				- AVParameterEvents can only be added to automation tracks (see AVParameterEvent).
 
				- All other event subclasses cannot be added to tempo or automation tracks.
*/

- (void)addEvent:(AVMusicEvent *)event atBeat:(AVMusicTimeStamp)beat;

/*!	@method moveEventsInRange:byAmount
	@abstract	Shift the beat location of all events in the given beat range by the amount specified.
	@param		range			the range of beats.  Must be a valid AVBeatRange.
	@param		beatAmount		the amount in beats to shift each event.  The amount may be positive or negative.
 */
- (void)moveEventsInRange:(AVBeatRange)range byAmount:(AVMusicTimeStamp)beatAmount;

/*!	@method clearEventsInRange:
	@abstract	Removes all events in the given beat range, erasing that portion of the AVMusicTrack.
	@param		range			the range of beats.  Must be a valid AVBeatRange.
	@discussion	All events outside of the specified range left unmodified.
 */
- (void)clearEventsInRange:(AVBeatRange)range;

/*!	@method cutEventsInRange:
	@abstract	Removes all events in the given beat range, splicing out that portion of the AVMusicTrack.
	@param		range			the range of beats.  Must be a valid AVBeatRange.
	@discussion	All events past the end of the specified range will be shifted backward by the duration of the range.
 */
- (void)cutEventsInRange:(AVBeatRange)range;

/*!	@method copyEventsInRange:fromTrack:insertAtBeat
	@abstract	Copies all events in the given beat range from the specified AVMusicTrack,
				splicing them into the current AVMusicTrack.
	@param		range			the range of beats.  Must be a valid AVBeatRange.
	@param		sourceTrack		the AVMusicTrack to copy the events from.
	@param		insertStartBeat	the start beat at which the copied events should be spliced in.
	@discussion	All events originally at or past insertStartBeat will be shifted forward by the duration
				of the copied-in range.
 */
- (void)copyEventsInRange:(AVBeatRange)range fromTrack:(AVMusicTrack *)sourceTrack insertAtBeat:(AVMusicTimeStamp)insertStartBeat;

/*!	@method copyAndMergeEventsInRange:fromTrack:mergeAtBeat
	@abstract	Copies all events in the given beat range from the specified AVMusicTrack,
				merging them into the current AVMusicTrack.
	@param		range			the range of beats.  Must be a valid AVBeatRange.
	@param		sourceTrack		the AVMusicTrack to copy the events from.
	@param		insertStartBeat	the start beat at which the copied events should be merged.
	@discussion	All events originally at or past mergeStartBeat will be left unmodified.
 
				Copying events from track to track follows the same type-exclusion rules as adding
				events:  The operation will generate an exception.
 */
- (void)copyAndMergeEventsInRange:(AVBeatRange)range fromTrack:(AVMusicTrack *)sourceTrack mergeAtBeat:(AVMusicTimeStamp)mergeStartBeat;

/*!	@typedef AVMusicEventEnumerationBlock
	@abstract	The block type used to enumerate and optionally remove AVMusicEvents when using
				`AVMusicTrack(enumerateEventsInRange:usingBlock:)`
	@param		event			the AVMusicEvent returned by this enumeration block call.  If this
								event is modified by the block, the corresponding track event will be changed.
	@param		timeStamp		the beat position of this event in the AVMusicTrack.  If the block
								sets *timeStamp to a new value, the corresponding event's beat position
								in the track will be updated.
	@param		removeEvent		If the block sets *removeEvent to YES, the current event will be
								removed from the track.
*/
typedef void (^AVMusicEventEnumerationBlock)(AVMusicEvent *event, AVMusicTimeStamp *timeStamp, BOOL *removeEvent);

/*!	@method enumerateEventsInRange:usingBlock:
	@abstract	Iterates through the AVMusicEvents within the AVMusicTrack whose timestamps fit within the range,
				calling the block for each.
	@param		block			the AVMusicEventEnumerationBlock to call for each event.
	@discussion	Each event returned via the block should be examined using `NSObject(isKindOfClass:)`
				to determine its subclass and then cast and accessed/edited accordingly.
 
				The iteration may continue after removing an event.
 
				The event objects returned via the block will not be the same instances
				which were added to the AVMusicTrack, though their contents will be identical.
 */
- (void)enumerateEventsInRange:(AVBeatRange)range usingBlock:(NS_NOESCAPE AVMusicEventEnumerationBlock)block;

@end

NS_ASSUME_NONNULL_END
