/*
    File:  AVMediaFormat.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

// Media types

AVF_EXPORT NSString *const AVMediaTypeVideo                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeAudio                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeText                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeClosedCaption         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeSubtitle              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeTimecode              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeMetadata              NS_AVAILABLE(10_8, 6_0);
AVF_EXPORT NSString *const AVMediaTypeMuxed                 NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVMediaTypeMetadataObject
 @abstract mediaType of AVCaptureInputPorts that provide AVMetadataObjects.
 @discussion
 Prior to iOS 9.0, camera AVCaptureDeviceInputs provide metadata (detected faces and barcodes) to an
 AVCaptureMetadataOutput through an AVCaptureInputPort whose mediaType is AVMediaTypeMetadata.  The
 AVCaptureMetadataOutput presents metadata to the client as an array of AVMetadataObjects, which are
 defined by Apple and not externally subclassable.  Starting in iOS 9.0, clients may record arbitrary
 metadata to a movie file using the AVCaptureMovieFileOutput.  The movie file output consumes metadata
 in a different format than the AVCaptureMetadataOutput, namely it accepts CMSampleBuffers of type
 'meta'.  Starting in iOS 9.0, two types of AVCaptureInput can produce suitable metadata for the
 movie file output.
 
 <ul>
 <li>The camera AVCaptureDeviceInput now presents an additional AVCaptureInputPort for recording detected
 faces to a movie file. When linked on or after iOS 9, ports that deliver AVCaptureMetadataObjects have a
 mediaType of AVMediaTypeMetadataObject rather than AVMediaTypeMetadata.  Input ports that deliver CMSampleBuffer
 metadata have a mediaType of AVMediaTypeMetadata.</li>
 
 <li>New to iOS 9 is the AVCaptureMetadataInput, which allows clients to record arbitrary metadata to a movie
 file.  Clients package metadata as an AVTimedMetadataGroup, the AVCaptureMetadataInput presents a port of mediaType
 AVMediaTypeMetadata, and when connected to a movie file output, transforms the timed metadata group's AVMetadataItems
 into CMSampleBuffers which can be written to the movie file.</li>
 </ul>
 
 When linked on or after iOS 9, AVCaptureInputPorts with a mediaType of AVMediaTypeMetadata are handled
 specially by the AVCaptureSession. When inputs and outputs are added to the session, the session does
 not form connections implicitly between eligible AVCaptureOutputs and input ports of type AVMediaTypeMetadata.
 If clients want to record a particular kind of metadata to a movie, they must manually form connections
 between a AVMediaTypeMetadata port and the movie file output using AVCaptureSession's -addConnection API.
*/
AVF_EXPORT NSString *const AVMediaTypeMetadataObject NS_AVAILABLE_IOS(9_0);


// Media characteristics

/*!
 @constant AVMediaCharacteristicVisual
 @abstract A media characteristic that indicates that a track or media selection option includes visual content.
 @discussion
 AVMediaTypeVideo, AVMediaTypeSubtitle, AVMediaTypeClosedCaption are examples of media types with the characteristic AVMediaCharacteristicVisual.
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicVisual      NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVMediaCharacteristicAudible
 @abstract A media characteristic that indicates that a track or media selection option includes audible content.
 @discussion
 AVMediaTypeAudio is a media type with the characteristic AVMediaCharacteristicAudible.
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicAudible     NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVMediaCharacteristicLegible
 @abstract A media characteristic that indicates that a track or media selection option includes legible content.
 @discussion
 AVMediaTypeSubtitle and AVMediaTypeClosedCaption are examples of media types with the characteristic AVMediaCharacteristicLegible.
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicLegible     NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVMediaCharacteristicFrameBased
 @abstract A media characteristic that indicates that a track or media selection option includes content that's frame-based.
 @discussion
 Frame-based content typically comprises discrete media samples that, once rendered, can remain current for indefinite periods of time without additional processing in support of "time-stretching". Further, any dependencies between samples are always explicitly signalled, so that the operations required to render any single sample can readily be performed on demand. AVMediaTypeVideo is the most common type of frame-based media. AVMediaTypeAudio is the most common counterexample. 
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicFrameBased  NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVMediaCharacteristicUsesWideGamutColorSpace
 @abstract A media characteristic that indicates that a track uses a wide gamut color space and therefore may make use of colors that cannot be accurately represented otherwise.
 @discussion
 A wide color space such as AVVideo*_P3_D65 contains additional dynamic range that may benefit from special treatment when compositing. Care should be taken to avoid clamping. Non-wide spaces include AVVideo*_ITU_R_709_2 and AVVideo*_SMPTE_C.
*/
AVF_EXPORT NSString *const AVMediaCharacteristicUsesWideGamutColorSpace NS_AVAILABLE(10_12, 10_0);

/*!
 @constant AVMediaCharacteristicIsMainProgramContent
 @abstract A media characteristic that indicates that a track or media selection option includes content that's marked by the content author as intrinsic to the presentation of the asset.
 @discussion
 Example: an option that presents the main program audio for the presentation, regardless of locale, would typically have this characteristic.
 The value of this characteristic is @"public.main-program-content".
 Note for content authors: the presence of this characteristic for a media option is inferred; any option that does not have the characteristic AVMediaCharacteristicIsAuxiliaryContent is considered to have the characteristic AVMediaCharacteristicIsMainProgramContent.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicIsMainProgramContent NS_AVAILABLE(10_8, 5_0);

/*!
 @constant AVMediaCharacteristicIsAuxiliaryContent
 @abstract A media characteristic that indicates that a track or media selection option includes content that's marked by the content author as auxiliary to the presentation of the asset.
 @discussion
 The value of this characteristic is @"public.auxiliary-content".
 Example: an option that presents audio media containing commentary on the presentation would typically have this characteristic.
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicIsAuxiliaryContent if it's explicitly tagged with that characteristic or if, as a member of an alternate track group, its associated track is excluded from autoselection.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicIsAuxiliaryContent NS_AVAILABLE(10_8, 5_0);

/*!
 @constant AVMediaCharacteristicContainsOnlyForcedSubtitles
 @abstract A media characteristic that indicates that a track or media selection option presents only forced subtitles.
 @discussion
 Media options with forced-only subtitles are typically selected when 1) the user has not selected a legible option with an accessibility characteristic or an auxiliary purpose and 2) its locale matches the locale of the selected audible media selection option.
 The value of this characteristic is @"public.subtitles.forced-only".
 Note for content authors: the presence of this characteristic for a legible media option may be inferred from the format description of the associated track that presents the subtitle media, if the format description carries sufficient information to indicate the presence or absence of forced and non-forced subtitles. If the format description does not carry this information, the legible media option can be explicitly tagged with the characteristic.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicContainsOnlyForcedSubtitles NS_AVAILABLE(10_8, 5_0);

/*!
 @constant AVMediaCharacteristicTranscribesSpokenDialogForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option includes legible content in the language of its specified locale that:
 	- transcribes spoken dialog and
 	- identifies speakers whenever other visual cues are insufficient for a viewer to determine who is speaking.
 @discussion
 Legible tracks provided for accessibility purposes are typically tagged both with this characteristic as well as with AVMediaCharacteristicDescribesMusicAndSoundForAccessibility.

 A legible track provided for accessibility purposes that's associated with an audio track that has no spoken dialog can be tagged with this characteristic, because it trivially meets these requirements.

 The value of this characteristic is @"public.accessibility.transcribes-spoken-dialog".

 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicTranscribesSpokenDialogForAccessibility only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicTranscribesSpokenDialogForAccessibility NS_AVAILABLE(10_8, 5_0);

/*!
 @constant AVMediaCharacteristicDescribesMusicAndSoundForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option includes legible content in the language of its specified locale that:
 	- describes music and
 	- describes sound other than spoken dialog, such as sound effects and significant silences, occurring in program audio.
 @discussion
 Legible tracks provided for accessibility purposes are typically tagged both with this characteristic as well as with AVMediaCharacteristicTranscribesSpokenDialogForAccessibility.

 A legible track provided for accessibility purposes that's associated with an audio track without music and without sound other than spoken dialog -- lacking even significant silences -- can be tagged with this characteristic, because it trivially meets these requirements.

 The value of this characteristic is @"public.accessibility.describes-music-and-sound".

 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicDescribesMusicAndSoundForAccessibility only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicDescribesMusicAndSoundForAccessibility NS_AVAILABLE(10_8, 5_0);

/*!
 @constant AVMediaCharacteristicEasyToRead
 @abstract A media characteristic that indicates that a track or media selection option provides legible content in the language of its specified locale that has been edited for ease of reading.
 @discussion
 The value of this characteristic is @"public.easy-to-read".
 
 Closed caption tracks that carry "easy reader" captions (per the CEA-608 specification) should be tagged with this characteristic. Subtitle tracks can also be tagged with this characteristic, where appropriate.

 Note for content authors: for QuickTime movie and .m4v files a track is considered to have the characteristic AVMediaCharacteristicEasyToRead only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicEasyToRead NS_AVAILABLE(10_8, 6_0);

/*!
 @constant AVMediaCharacteristicDescribesVideoForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option includes audible descriptions of the visual portion of the presentation that are sufficient for listeners without access to the visual content to comprehend the essential information, such as action and setting, that it depicts.
 @discussion
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.accessibility.describes-video".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicDescribesVideoForAccessibility only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT NSString *const AVMediaCharacteristicDescribesVideoForAccessibility NS_AVAILABLE(10_8, 5_0);

/*!
 @constant AVMediaCharacteristicLanguageTranslation
 @abstract A media characteristic that indicates that a track or media selection option contains a language or dialect translation of originally or previously produced content, intended to be used as a substitute for that content by users who prefer its designated language.
 @discussion
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.translation".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicLanguageTranslation only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.
*/
AVF_EXPORT NSString *const AVMediaCharacteristicLanguageTranslation NS_AVAILABLE(10_11, 9_0);

/*!
 @constant AVMediaCharacteristicDubbedTranslation
 @abstract A media characteristic that indicates that a track or media selection option contains a language or dialect translation of originally or previously produced content, created by substituting most or all of the dialog in a previous mix of audio content with dialog spoken in its designated language.
 @discussion
 Tracks to which this characteristic is assigned should typically also be assigned the characteristic AVMediaCharacteristicLanguageTranslation.
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.translation.dubbed".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicDubbedTranslation only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.
*/
AVF_EXPORT NSString *const AVMediaCharacteristicDubbedTranslation NS_AVAILABLE(10_11, 9_0);

/*!
 @constant AVMediaCharacteristicVoiceOverTranslation NS_AVAILABLE(10_11, 9_0);
 @abstract A media characteristic that indicates that a track or media selection option contains a language translation of originally or previously produced content, created by adding, in its designated language, a verbal interpretation of dialog and translations of other important information to a new mix of the audio content.
 @discussion
 Tracks to which this characteristic is assigned should typically also be assigned the characteristic AVMediaCharacteristicLanguageTranslation.
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.translation.voice-over".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicVoiceOverTranslation only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.
*/
AVF_EXPORT NSString *const AVMediaCharacteristicVoiceOverTranslation NS_AVAILABLE(10_11, 9_0);

/*
	Tagging of tracks of .mov and .m4v files with media characteristics

	Each track of .mov files and .m4v files (that is, files of type AVFileTypeQuickTimeMovie and AVFileTypeAppleM4V) can optionally carry one or more tagged media characteristics, each of which declares a purpose, a trait, or some other disinguishing property of the track's media.

	For example, a track containing audio that mixes original program content with additional narrative descriptions of visual action may be tagged with the media characteristic "public.accessibility.describes-video" in order to distinguish it from other audio tracks stored in the same file that do not contain additional narrative. 

	Each tagged media characteristic in .mov and .m4v files is stored in track userdata as a userdata item of type 'tagc' (represented as a FourCharCode) that consists of a standard atom header (size and type) followed by an array of US-ASCII characters (8-bit, high bit clear) comprising the value of the tag. The character array is not a C string; there is no terminating zero. The userdata item atom size is sum of the standard atom header size (8) and the size of the US-ASCII character array.

	AVFoundation clients can inspect the tagged media characteristics of a track as follows:

		NSArray *trackUserDataItems = [myAVAssetTrack metadataForFormat:AVMetadataFormatQuickTimeUserData];
		NSArray *trackTaggedMediaCharacteristics = [AVMetadataItem metadataItemsFromArray:trackUserDataItems withKey:AVMetadataQuickTimeUserDataKeyTaggedCharacteristic keySpace:AVMetadataKeySpaceQuickTimeUserData];

		for (AVMetadataItem *metadataItem in trackTaggedMediaCharacteristics) {
			NSString *thisTrackMediaCharacteristic = [metadataItem stringValue];
		}

	-[AVAssetTrack hasMediaCharacteristic:] can be used to determine whether a track has a particular media characteristic, whether the characteristic is inferred from its media type or format descriptions (e.g. AVMediaCharacteristicAudible, AVMediaCharacteristicContainsOnlyForcedSubtitles) or requires explicit tagging (e.g. AVMediaCharacteristicTranscribesSpokenDialogForAccessibility, AVMediaCharacteristicDescribesVideoForAccessibility). Note that explicit tagging can't be used to override inferences from tracks' media types or format descriptions; for example, -[AVAssetTrack hasMediaCharacteristic:AVMediaCharacteristicVisual] will return NO for any audio track, even if the track has been perversely tagged with the visual characteristic.

	Tagged media characteristics can be written to the QuickTime userdata of an output track associated with an AVAssetWriterInput as follows, provided that the outputFileType of the AVAssetWriter is either AVFileTypeQuickTimeMovie or AVFileTypeAppleM4V:

		AVMutableMetadataItem *myTaggedMediaCharacteristic = [[[AVMutableMetadataItem alloc] init] autorelease];

		[myTaggedMediaCharacteristic setKey:AVMetadataQuickTimeUserDataKeyTaggedCharacteristic];
		[myTaggedMediaCharacteristic setKeySpace:AVMetadataKeySpaceQuickTimeUserData];

		[myTaggedMediaCharacteristic setValue:aMeaningfulCharacteristicAsNSString];

		[myMutableArrayOfMetadata addObject:myTaggedMediaCharacteristic];

		[myAssetWriterInput setMetadata:myMutableArrayOfMetadata];

*/

// File format UTIs

/*!
 @constant AVFileTypeQuickTimeMovie
 @abstract A UTI for the QuickTime movie file format.
 @discussion
 The value of this UTI is @"com.apple.quicktime-movie".
 Files are identified with the .mov and .qt extensions.
 */
AVF_EXPORT NSString *const AVFileTypeQuickTimeMovie NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeMPEG4
 @abstract A UTI for the MPEG-4 file format.
 @discussion
 The value of this UTI is @"public.mpeg-4".
 Files are identified with the .mp4 extension.
 */
AVF_EXPORT NSString *const AVFileTypeMPEG4 NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAppleM4V
 @discussion
 The value of this UTI is @"com.apple.m4v-video".
 Files are identified with the .m4v extension.
 */
AVF_EXPORT NSString *const AVFileTypeAppleM4V NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAppleM4A
 @discussion
 The value of this UTI is @"com.apple.m4a-audio".
 Files are identified with the .m4a extension.
 */
AVF_EXPORT NSString *const AVFileTypeAppleM4A NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileType3GPP
 @abstract A UTI for the 3GPP file format.
 @discussion
 The value of this UTI is @"public.3gpp".
 Files are identified with the .3gp, .3gpp, and .sdv extensions.
 */
AVF_EXPORT NSString *const AVFileType3GPP NS_AVAILABLE(10_11, 4_0);

/*!
 @constant AVFileType3GPP2
 @abstract A UTI for the 3GPP file format.
 @discussion
 The value of this UTI is @"public.3gpp2".
 Files are identified with the .3g2, .3gp2 extensions.
 */
AVF_EXPORT NSString *const AVFileType3GPP2 NS_AVAILABLE(10_11, 4_0);

/*!
 @constant AVFileTypeCoreAudioFormat
 @abstract A UTI for the CoreAudio file format.
 @discussion
 The value of this UTI is @"com.apple.coreaudio-format".
 Files are identified with the .caf extension.
 */
AVF_EXPORT NSString *const AVFileTypeCoreAudioFormat NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeWAVE
 @abstract A UTI for the WAVE audio file format.
 @discussion
 The value of this UTI is @"com.microsoft.waveform-audio".
 Files are identified with the .wav, .wave, and .bwf extensions.
 */
AVF_EXPORT NSString *const AVFileTypeWAVE NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAIFF
 @abstract A UTI for the AIFF audio file format.
 @discussion
 The value of this UTI is @"public.aiff-audio".
 Files are identified with the .aif and .aiff extensions.
 */
AVF_EXPORT NSString *const AVFileTypeAIFF NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAIFC
 @abstract A UTI for the AIFC audio file format.
 @discussion
 The value of this UTI is @"public.aifc-audio".
 Files are identified with the .aifc and .cdda extensions.
 */
AVF_EXPORT NSString *const AVFileTypeAIFC NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAMR
 @abstract A UTI for the adaptive multi-rate audio file format.
 @discussion
 The value of this UTI is @"org.3gpp.adaptive-multi-rate-audio".
 Files are identified with the .amr extension.
 */
AVF_EXPORT NSString *const AVFileTypeAMR NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeMPEGLayer3
 @abstract A UTI for the MPEG layer 3 audio file format.
 @discussion
 The value of this UTI is @"public.mp3".
 Files are identified with the .mp3 extension.
 */
AVF_EXPORT NSString *const AVFileTypeMPEGLayer3 NS_AVAILABLE(10_9, 7_0);

/*!
 @constant AVFileTypeSunAU
 @abstract A UTI for the Sun/NeXT audio file format.
 @discussion
 The value of this UTI is @"public.au-audio".
 Files are identified with the .au and .snd extensions.
 */
AVF_EXPORT NSString *const AVFileTypeSunAU NS_AVAILABLE(10_9, 7_0);

/*!
 @constant AVFileTypeAC3
 @abstract A UTI for the AC-3 audio file format.
 @discussion
 The value of this UTI is @"public.ac3-audio".
 Files are identified with the .ac3 extension.
 */
AVF_EXPORT NSString *const AVFileTypeAC3 NS_AVAILABLE(10_9, 7_0);

/*!
 @constant AVFileTypeEnhancedAC3
 @abstract A UTI for the enhanced AC-3 audio file format.
 @discussion
 The value of this UTI is @"public.enhanced-ac3-audio".
 Files are identified with the .eac3 extension.
 */
AVF_EXPORT NSString *const AVFileTypeEnhancedAC3 NS_AVAILABLE(10_11, 9_0);

/*!
 @constant AVStreamingKeyDeliveryContentKeyType
 @abstract A UTI for streaming key delivery content keys
 @discussion
 The value of this UTI is @"com.apple.streamingkeydelivery.contentkey".
 */
AVF_EXPORT NSString *const AVStreamingKeyDeliveryContentKeyType NS_AVAILABLE(10_11, 9_0);

/*!
 @constant AVStreamingKeyDeliveryPersistentContentKeyType
 @abstract A UTI for persistent streaming key delivery content keys
 @discussion
 The value of this UTI is @"com.apple.streamingkeydelivery.persistentcontentkey".
 */
AVF_EXPORT NSString *const AVStreamingKeyDeliveryPersistentContentKeyType NS_AVAILABLE(10_11, 9_0);


