#if !__has_include(<AVFCore/AVMediaFormat.h>)
/*
    File:  AVMediaFormat.h

	Framework:  AVFoundation
 
	Copyright 2010-2020 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

// Media types
typedef NSString * AVMediaType NS_EXTENSIBLE_STRING_ENUM;

AVF_EXPORT AVMediaType const AVMediaTypeVideo                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeAudio                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeText                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeClosedCaption         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeSubtitle              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeTimecode              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeMetadata              API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMediaType const AVMediaTypeMuxed                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @enum          AVVideoRange
 @constant      AVVideoRangeSDR
				  Indicates that the video range as SDR
 @constant      AVVideoRangeHLG
				  Indicates that the video range as HLG
 @constant      AVVideoRangePQ
				  Indicates that the video range as PQ
 */
typedef NSString * AVVideoRange NS_TYPED_ENUM;
	AVF_EXPORT AVVideoRange const AVVideoRangeSDR									API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));
	AVF_EXPORT AVVideoRange const AVVideoRangeHLG									API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));
	AVF_EXPORT AVVideoRange const AVVideoRangePQ									API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

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
AVF_EXPORT AVMediaType const AVMediaTypeMetadataObject API_AVAILABLE(ios(9.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos);

AVF_EXPORT AVMediaType const AVMediaTypeDepthData API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);


// Media characteristics
typedef NSString * AVMediaCharacteristic NS_EXTENSIBLE_STRING_ENUM;

/*!
 @constant AVMediaCharacteristicVisual
 @abstract A media characteristic that indicates that a track or media selection option includes visual content.
 @discussion
 AVMediaTypeVideo, AVMediaTypeSubtitle, AVMediaTypeClosedCaption are examples of media types with the characteristic AVMediaCharacteristicVisual.
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicVisual      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicAudible
 @abstract A media characteristic that indicates that a track or media selection option includes audible content.
 @discussion
 AVMediaTypeAudio is a media type with the characteristic AVMediaCharacteristicAudible.
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicAudible     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicLegible
 @abstract A media characteristic that indicates that a track or media selection option includes legible content.
 @discussion
 AVMediaTypeSubtitle and AVMediaTypeClosedCaption are examples of media types with the characteristic AVMediaCharacteristicLegible.
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicLegible     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicFrameBased
 @abstract A media characteristic that indicates that a track or media selection option includes content that's frame-based.
 @discussion
 Frame-based content typically comprises discrete media samples that, once rendered, can remain current for indefinite periods of time without additional processing in support of "time-stretching". Further, any dependencies between samples are always explicitly signalled, so that the operations required to render any single sample can readily be performed on demand. AVMediaTypeVideo is the most common type of frame-based media. AVMediaTypeAudio is the most common counterexample. 
 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicFrameBased  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicUsesWideGamutColorSpace
 @abstract A media characteristic that indicates that a track uses a wide gamut color space and therefore may make use of colors that cannot be accurately represented otherwise.
 @discussion
 A wide color space such as AVVideo*_P3_D65 contains additional dynamic range that may benefit from special treatment when compositing. Care should be taken to avoid clamping. Non-wide spaces include AVVideo*_ITU_R_709_2 and AVVideo*_SMPTE_C.
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicUsesWideGamutColorSpace API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @constant AVMediaCharacteristicContainsHDRVideo
 @abstract A media characteristic that indicates that a track contains HDR video.
 @discussion
 HDR video contains extended dynamic range that requires explicit support when compositing.
 The value of this characteristic is @“public.contains-hdr-video".
 Note for content authors: the presence of this characteristic is strictly inferred from the format description of the associated track.
 */
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicContainsHDRVideo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMediaCharacteristicContainsAlphaChannel
 @abstract A media characteristic that indicates that a track contains an alpha channel.
 @discussion
 To determine whether alpha is straight or pre-multiplied, look for the format description extension with key kCMFormatDescriptionExtension_AlphaChannelMode.
 */
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicContainsAlphaChannel API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/*!
 @constant AVMediaCharacteristicIsMainProgramContent
 @abstract A media characteristic that indicates that a track or media selection option includes content that's marked by the content author as intrinsic to the presentation of the asset.
 @discussion
 Example: an option that presents the main program audio for the presentation, regardless of locale, would typically have this characteristic.
 The value of this characteristic is @"public.main-program-content".
 Note for content authors: the presence of this characteristic for a media option is inferred; any option that does not have the characteristic AVMediaCharacteristicIsAuxiliaryContent is considered to have the characteristic AVMediaCharacteristicIsMainProgramContent.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicIsMainProgramContent API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

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
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicIsAuxiliaryContent API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicIsOriginalContent
 @abstract A media characteristic that indicates that a track or media selection option includes content that's marked by the content author as original to the principal production of the media, as opposed to supplementary or derivative content created by means of language translation or by other means.
 @discussion
 The value of this characteristic is @"public.original-content".
 Example: an option that presents audio media with dialog in the principal language of the production may be tagged with this characteristic; audio media containing dialog dubbed in a language other than the principal language of the production typically would not be tagged with this characteristic.
 Note for content authors: for QuickTime movie and .m4v files and for HTTP Live Streaming, a media option is considered to have the characteristic AVMediaCharacteristicIsOriginalContent only if it's explicitly tagged with the characteristic.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicIsOriginalContent API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*!
 @constant AVMediaCharacteristicContainsOnlyForcedSubtitles
 @abstract A media characteristic that indicates that a track or media selection option presents only forced subtitles.
 @discussion
 Media options with forced-only subtitles are typically selected when 1) the user has not selected a legible option with an accessibility characteristic or an auxiliary purpose and 2) its locale matches the locale of the selected audible media selection option.
 The value of this characteristic is @"public.subtitles.forced-only".
 Note for content authors: the presence of this characteristic for a legible media option may be inferred from the format description of the associated track that presents the subtitle media, if the format description carries sufficient information to indicate the presence or absence of forced and non-forced subtitles. If the format description does not carry this information, the legible media option can be explicitly tagged with the characteristic.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicContainsOnlyForcedSubtitles API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

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
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicTranscribesSpokenDialogForAccessibility API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

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
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicDescribesMusicAndSoundForAccessibility API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

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
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicEasyToRead API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicDescribesVideoForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option provides descriptions of the visual portion of the presentation that are sufficient to comprehend essential information that it depicts, such as action and setting.
 @discussion
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.accessibility.describes-video".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicDescribesVideoForAccessibility only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.

 Also see -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicDescribesVideoForAccessibility API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVMediaCharacteristicLanguageTranslation
 @abstract A media characteristic that indicates that a track or media selection option contains a language or dialect translation of originally or previously produced content, intended to be used as a substitute for that content by users who prefer its designated language.
 @discussion
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.translation".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicLanguageTranslation only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicLanguageTranslation API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

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
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicDubbedTranslation API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
 @constant AVMediaCharacteristicVoiceOverTranslation
 @abstract A media characteristic that indicates that a track or media selection option contains a language translation of originally or previously produced content, created by adding, in its designated language, a verbal interpretation of dialog and translations of other important information to a new mix of the audio content.
 @discussion
 Tracks to which this characteristic is assigned should typically also be assigned the characteristic AVMediaCharacteristicLanguageTranslation.
 See -[AVAssetTrack hasMediaCharacteristic:] and -[AVMediaSelectionOption hasMediaCharacteristic:].
 The value of this characteristic is @"public.translation.voice-over".
 Note for content authors: for QuickTime movie and .m4v files a media option is considered to have the characteristic AVMediaCharacteristicVoiceOverTranslation only if it's explicitly tagged with that characteristic.
 See the discussion of the tagging of tracks with media characteristics below.
*/
AVF_EXPORT AVMediaCharacteristic const AVMediaCharacteristicVoiceOverTranslation API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

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
typedef NSString * AVFileType NS_EXTENSIBLE_STRING_ENUM;

/*!
 @constant AVFileTypeQuickTimeMovie
 @abstract A UTI for the QuickTime movie file format.
 @discussion
 The value of this UTI is @"com.apple.quicktime-movie".
 Files are identified with the .mov and .qt extensions.
 */
AVF_EXPORT AVFileType const AVFileTypeQuickTimeMovie API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeMPEG4
 @abstract A UTI for the MPEG-4 file format.
 @discussion
 The value of this UTI is @"public.mpeg-4".
 Files are identified with the .mp4 extension.
 */
AVF_EXPORT AVFileType const AVFileTypeMPEG4 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeAppleM4V
 @discussion
 The value of this UTI is @"com.apple.m4v-video".
 Files are identified with the .m4v extension.
 */
AVF_EXPORT AVFileType const AVFileTypeAppleM4V API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeAppleM4A
 @discussion
 The value of this UTI is @"com.apple.m4a-audio".
 Files are identified with the .m4a extension.
 */
AVF_EXPORT AVFileType const AVFileTypeAppleM4A API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileType3GPP
 @abstract A UTI for the 3GPP file format.
 @discussion
 The value of this UTI is @"public.3gpp".
 Files are identified with the .3gp, .3gpp, and .sdv extensions.
 */
AVF_EXPORT AVFileType const AVFileType3GPP API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileType3GPP2
 @abstract A UTI for the 3GPP file format.
 @discussion
 The value of this UTI is @"public.3gpp2".
 Files are identified with the .3g2, .3gp2 extensions.
 */
AVF_EXPORT AVFileType const AVFileType3GPP2 API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeCoreAudioFormat
 @abstract A UTI for the CoreAudio file format.
 @discussion
 The value of this UTI is @"com.apple.coreaudio-format".
 Files are identified with the .caf extension.
 */
AVF_EXPORT AVFileType const AVFileTypeCoreAudioFormat API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeWAVE
 @abstract A UTI for the WAVE audio file format.
 @discussion
 The value of this UTI is @"com.microsoft.waveform-audio".
 Files are identified with the .wav, .wave, and .bwf extensions.
 */
AVF_EXPORT AVFileType const AVFileTypeWAVE API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeAIFF
 @abstract A UTI for the AIFF audio file format.
 @discussion
 The value of this UTI is @"public.aiff-audio".
 Files are identified with the .aif and .aiff extensions.
 */
AVF_EXPORT AVFileType const AVFileTypeAIFF API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeAIFC
 @abstract A UTI for the AIFC audio file format.
 @discussion
 The value of this UTI is @"public.aifc-audio".
 Files are identified with the .aifc and .cdda extensions.
 */
AVF_EXPORT AVFileType const AVFileTypeAIFC API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeAMR
 @abstract A UTI for the adaptive multi-rate audio file format.
 @discussion
 The value of this UTI is @"org.3gpp.adaptive-multi-rate-audio".
 Files are identified with the .amr extension.
 */
AVF_EXPORT AVFileType const AVFileTypeAMR API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeMPEGLayer3
 @abstract A UTI for the MPEG layer 3 audio file format.
 @discussion
 The value of this UTI is @"public.mp3".
 Files are identified with the .mp3 extension.
 */
AVF_EXPORT AVFileType const AVFileTypeMPEGLayer3 API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeSunAU
 @abstract A UTI for the Sun/NeXT audio file format.
 @discussion
 The value of this UTI is @"public.au-audio".
 Files are identified with the .au and .snd extensions.
 */
AVF_EXPORT AVFileType const AVFileTypeSunAU API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeAC3
 @abstract A UTI for the AC-3 audio file format.
 @discussion
 The value of this UTI is @"public.ac3-audio".
 Files are identified with the .ac3 extension.
 */
AVF_EXPORT AVFileType const AVFileTypeAC3 API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @constant AVFileTypeEnhancedAC3
 @abstract A UTI for the enhanced AC-3 audio file format.
 @discussion
 The value of this UTI is @"public.enhanced-ac3-audio".
 Files are identified with the .eac3 extension.
 */
AVF_EXPORT AVFileType const AVFileTypeEnhancedAC3 API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
 @constant AVFileTypeJPEG
 @abstract A UTI for the JPEG (JFIF) format.
 @discussion
 The value of this UTI is @"public.jpeg".
 Files are identified with the .jpg or .jpeg extension.
 */
AVF_EXPORT AVFileType const AVFileTypeJPEG API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant AVFileTypeDNG
 @abstract A UTI for the Adobe digital negative file format.
 @discussion
 The value of this UTI is @"com.adobe.raw-image".
 Files are identified with the .dng extension.
 */
AVF_EXPORT AVFileType const AVFileTypeDNG API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant AVFileTypeHEIC
 @abstract A UTI for the high efficiency image file format containing HEVC compressed images.
 @discussion
 The value of this UTI is @"public.heic".
 Files are identified with the .heic extension.
 */
AVF_EXPORT AVFileType const AVFileTypeHEIC API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant AVFileTypeAVCI
 @abstract A UTI for the high efficiency image file format containing H.264 compressed images.
 @discussion
 The value of this UTI is @"public.avci".
 Files are identified with the .avci extension.
 */
AVF_EXPORT AVFileType const AVFileTypeAVCI API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant AVFileTypeHEIF
 @abstract A UTI for the high efficiency image file format containing images compressed with any codec.
 @discussion
 The value of this UTI is @"public.heif".
 Files are identified with the .heif extension.
 */
AVF_EXPORT AVFileType const AVFileTypeHEIF API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant AVFileTypeTIFF
 @abstract A UTI for the tagged image file format.
 @discussion
 The value of this UTI is @"public.tiff".
 Files are identified with the .tiff or .tif extension.
 */
AVF_EXPORT AVFileType const AVFileTypeTIFF API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant AVFileTypeAppleiTT
 @abstract A UTI for the Apple iTT caption file format
 @discussion
 The value of this UTI is @"com.apple.itunes-timed-text".
 Files are identified with the .itt extension.
 */
AVF_EXPORT AVFileType const AVFileTypeAppleiTT API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
 @constant AVFileTypeSCC
 @abstract A UTI for the Scenarist closed caption file format
 @discussion
 The value of this UTI is @"com.scenarist.closed-caption".
 Files are identified with the .scc extension.
 */
AVF_EXPORT AVFileType const AVFileTypeSCC API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
 @constant AVStreamingKeyDeliveryContentKeyType
 @abstract A UTI for streaming key delivery content keys
 @discussion
 The value of this UTI is @"com.apple.streamingkeydelivery.contentkey".
 */
AVF_EXPORT NSString * const AVStreamingKeyDeliveryContentKeyType API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
 @constant AVStreamingKeyDeliveryPersistentContentKeyType
 @abstract A UTI for persistent streaming key delivery content keys
 @discussion
 The value of this UTI is @"com.apple.streamingkeydelivery.persistentcontentkey".
 */
AVF_EXPORT NSString * const AVStreamingKeyDeliveryPersistentContentKeyType API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));


// File type profiles
typedef NSString * AVFileTypeProfile NS_TYPED_ENUM;

/*!
 @constant AVFileTypeProfileMPEG4AppleHLS
 @abstract Apple HTTP Live Streaming profile
 @discussion
 The profile that is suitable for Apple HTTP Live Streaming.
 */
AVF_EXPORT AVFileTypeProfile const AVFileTypeProfileMPEG4AppleHLS API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));

/*!
 @constant AVFileTypeProfileMPEG4CMAFCompliant
 @abstract CMAF compliant profile
 @discussion
 The profile that is compliance with CMAF format.
 */
AVF_EXPORT AVFileTypeProfile const AVFileTypeProfileMPEG4CMAFCompliant API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));


#else
#import <AVFCore/AVMediaFormat.h>
#endif
