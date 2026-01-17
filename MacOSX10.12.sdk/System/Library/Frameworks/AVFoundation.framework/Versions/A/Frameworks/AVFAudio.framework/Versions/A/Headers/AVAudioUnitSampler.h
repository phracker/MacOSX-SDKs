/*
	File:		AVAudioUnitSampler.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioUnitMIDIInstrument.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVAudioUnitSampler
 @abstract Apple's sampler audio unit.
 @discussion
    An AVAudioUnit for Apple's Sampler Audio Unit. The sampler can be configured by loading
    instruments from different types of files such as an aupreset, a DLS or SF2 sound bank,
    an EXS24 instrument, a single audio file, or an array of audio files.

    The output is a single stereo bus. 
*/
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface AVAudioUnitSampler : AVAudioUnitMIDIInstrument

/*! @method loadSoundBankInstrumentAtURL:program:bankMSB:bankLSB:error:
	@abstract loads a specific instrument from the specified sound bank
	@param bankURL
		URL for a Soundbank file. The file can be either a DLS bank (.dls) or a SoundFont bank (.sf2).
	@param program
		program number for the instrument to load
	@param bankMSB
		MSB for the bank number for the instrument to load.  This is usually 0x79 for melodic
		instruments and 0x78 for percussion instruments.
	@param bankLSB
		LSB for the bank number for the instrument to load.  This is often 0, and represents the "bank variation".
	@param outError
    	the status of the operation
	@discussion
 		This method reads from file and allocates memory, so it should not be called on a real time thread.
 */
- (BOOL)loadSoundBankInstrumentAtURL:(NSURL *)bankURL program:(uint8_t)program bankMSB:(uint8_t)bankMSB bankLSB:(uint8_t)bankLSB error:(NSError **)outError;

/*! @method loadInstrumentAtURL:error:
	@abstract configures the sampler by loading the specified preset file.
	@param instrumentURL
    	URL to the preset file or audio file
	@param outError
		the status of the operation
	@discussion
		The file can be of one of the following types: Logic/GarageBand EXS24 instrument,
		the Sampler AU's native aupreset, or an audio file (eg. .caf, .aiff, .wav, .mp3).
	 
		If an audio file URL is loaded, it will become the sole sample in a new default instrument.
		Any information contained in the file regarding its keyboard placement (e.g. root key,
		key range) will be used.
		This method reads from file and allocates memory, so it should not be called on a real time thread.
 
 */
- (BOOL)loadInstrumentAtURL:(NSURL *)instrumentURL error:(NSError **)outError;

/*! @method loadAudioFilesAtURLs:error:
	@abstract configures the sampler by loading a set of audio files.
	@param audioFiles
		array of URLs for audio files to be loaded
	@param outError
		the status of the operation
	@discussion
		The audio files are loaded into a new default instrument with each audio file placed
		into its own sampler zone. Any information contained in the audio file regarding
		their placement on the keyboard (e.g. root key, key range) will be used.
		This method reads from file and allocates memory, so it should not be called on a real time thread.
 
 */
- (BOOL)loadAudioFilesAtURLs:(NSArray<NSURL *> *)audioFiles error:(NSError **)outError;

/*! @property stereoPan
	@abstract
		adjusts the pan for all the notes played.
		Range:     -1 -> +1
		Default:   0
 */
@property (nonatomic) float     stereoPan;

/*! @property masterGain
	@abstract
    	adjusts the gain of all the notes played
		Range:     -90.0 -> +12 db
		Default: 0 db
 */
@property (nonatomic) float     masterGain;

/*! @property globalTuning
	@abstract
		adjusts the tuning of all the notes played.
		Range:     -2400 -> +2400 cents
		Default:   0
 */
@property (nonatomic) float     globalTuning;


@end

NS_ASSUME_NONNULL_END
