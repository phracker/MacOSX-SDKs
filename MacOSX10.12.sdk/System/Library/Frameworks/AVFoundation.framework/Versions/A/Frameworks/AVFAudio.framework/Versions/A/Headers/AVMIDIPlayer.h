/*
 	File:		AVMIDIPlayer.h
 	Framework:	AVFoundation
 
 	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioTime;

/*! @typedef AVMIDIPlayerCompletionHandler
	@abstract Generic callback block.
 */
typedef void (^AVMIDIPlayerCompletionHandler)(void);

/*! @class AVMIDIPlayer
	@abstract A player for music file formats (MIDI, iMelody).
 */
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface AVMIDIPlayer : NSObject {
@protected
	void *_impl;
}

/*!	@method initWithContentsOfURL:soundBankURL:error:
 	@abstract Create a player with the contents of the file specified by the URL.
	@discussion
 		'bankURL' should contain the path to a SoundFont2 or DLS bank to be used
 		by the MIDI synthesizer.  For OSX it can be set to nil for the default,
 		but for iOS it must always refer to a valid bank file.
*/
- (nullable instancetype)initWithContentsOfURL:(NSURL *)inURL soundBankURL:(NSURL * __nullable)bankURL error:(NSError **)outError;

/*!	@method initWithData:soundBankURL:error:
	@abstract Create a player with the contents of the data object
	@discussion
		'bankURL' should contain the path to a SoundFont2 or DLS bank to be used
		by the MIDI synthesizer.  For OSX it can be set to nil for the default,
		but for iOS it must always refer to a valid bank file.
 */
- (nullable instancetype)initWithData:(NSData *)data soundBankURL:(NSURL * __nullable)bankURL error:(NSError **)outError;

/* transport control */

/*! @method prepareToPlay
	@abstract Get ready to play the sequence by prerolling all events
	@discussion
		Happens automatically on play if it has not already been called, but may produce a delay in startup.
 */
- (void)prepareToPlay;

/*! @method play:
	@abstract Play the sequence.
 */
- (void)play:(AVMIDIPlayerCompletionHandler __nullable)completionHandler;

/*! @method stop
	@abstract Stop playing the sequence.
 */
- (void)stop;

/* properties */

/*! @property duration
	@abstract The length of the currently loaded file in seconds.
 */
@property(nonatomic, readonly) NSTimeInterval duration;

/*! @property playing
	@abstract Indicates whether or not the player is playing
 */
@property(nonatomic, readonly, getter=isPlaying) BOOL playing;

/*! @property rate
	@abstract The playback rate of the player
	@discussion
		1.0 is normal playback rate.  Rate must be > 0.0.
 */
@property (nonatomic) float rate;

/*! @property currentPosition
	@abstract The current playback position in seconds
	@discussion
		Setting this positions the player to the specified time.  No range checking on the time value is done.
 		This can be set while the player is playing, in which case playback will resume at the new time.
 */
@property(nonatomic) NSTimeInterval currentPosition;

@end

NS_ASSUME_NONNULL_END
