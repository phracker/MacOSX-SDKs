/*
	File:  MEExtensionPlugin.h
	
	Framework:	MediaExtension
 
	Copyright © 2023 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#ifndef MEExtensionPlugin_h
#define MEExtensionPlugin_h

/*!
	@abstract		Extension point names identify a bundle as a particular type of extension.
	@constant		kMEFormatReaderExtensionPointName
		The extension point name for MediaExtension MediaToolbox format readers.
	@constant		kMEVideoDecoderExtensionPointName
		The extension point name for MediaExtension VideoToolbox decoders.
	@constant		kMERAWProcessorExtensionPointName
		The extension point name for MediaExtension RAW Processors.
*/
#define kMEFormatReaderExtensionPointName					@"com.apple.mediaextension.formatreader"
#define kMEVideoDecoderExtensionPointName					@"com.apple.mediaextension.videodecoder"
#define kMERAWProcessorExtensionPointName					@"com.apple.mediaextension.rawprocessor"


/*!
	@abstract		Extension attribute field keys for MediaExtension format reader plugin bundles.
	@constant		kMEFormatReaderClassImplementationID
		A string that uniquely identifies the format reader. It should start with the reverse domain identifier of the developer and for clarity contain ".formatreader." and the name of the media format.
	@constant		kMEFormatReaderUTTypeArrayKey
		An array of UTType identifiers supported by the format reader plugin.
	@constant		kMEFormatReaderFileNameExtensionArrayKey
		An array of file extensions supported by the format reader plugin. This should include file extensions for any type of related files.
	@constant		kMEFormatReaderObjectNameKey
		A user-readable string describing the format reader. This string is used for uniquely identifying format readers and possibly for debug logging but is typically not visible to users.
*/
#define kMEFormatReaderClassImplementationIDKey				@"ClassImplementationID"
#define kMEFormatReaderUTTypeArrayKey						@"MTUTTypeArray"
#define kMEFormatReaderFileNameExtensionArrayKey			@"MTFileNameExtensionArray"
#define kMEFormatReaderObjectNameKey						@"ObjectName"


/*!
	@abstract		Extension attribute field keys for MediaExtension video decoder plugin bundles.
	@constant		kMEVideoDecoderClassImplementationIDKey
		A string that uniquely identifies the video decoder. It should start with the reverse domain identifier of the developer and for clarity contain ".videodecoder." and the name of the codec.
	@constant		kMEVideoDecoderCodecInfoKey
		An array of one or more dictionaries describing the codecs that the decoder supports. Each dictionary will have entries for at least the kMEVideoDecoderCodecTypeKey and kMEVideoDecoderCodecNameKey.
	@constant		kMEVideoDecoderCodecTypeKey
		A string describing the four-character code of the codec that the decoder supports. Each string should be exactly four characters long and use ASCII character set encoding.
	@constant		kMEVideoDecoderCodecNameKey
		A user-readable string describing the name of the codec format. This string might be displayed as format information for the video track in a player application.
	@constant		kMEVideoDecoderObjectNameKey
		A user-readable string describing the video decoder. This string is used for uniquely identifying video decoders and possibly for debug logging but is typically not visible to users.
*/
#define kMEVideoDecoderClassImplementationIDKey				@"ClassImplementationID"
#define kMEVideoDecoderCodecInfoKey							@"CodecInfo"
#define kMEVideoDecoderCodecTypeKey							@"CodecType"
#define kMEVideoDecoderCodecNameKey							@"CodecName"
#define kMEVideoDecoderObjectNameKey						@"ObjectName"


/*!
	@abstract		Extension attribute field keys for MediaExtension RAW processor plugin bundles.
	@constant		kMERAWProcessorClassImplementationIDKey
		A string that uniquely identifies the RAW processor. It should start with the reverse domain identifier of the developer and for clarity contain ".rawprocessor." and the name of the codec.
	@constant		kMERAWProcessorProcessorInfoKey
		An array of one or more dictionaries describing the codecs that the RAW processor supports. Each dictionary will have entries for at least the kMERAWProcessorCodecTypeKey and kMERAWProcessorCodecNameKey.
	@constant		kMERAWProcessorCodecTypeKey
		A string describing the four-character code of the codec that the RAW processor supports. Each string should be exactly four characters long and use ASCII character set encoding.
	@constant		kMERAWProcessorCodecNameKey
		A user-readable string describing the name of the codec format. This string might be displayed as format information for the video track in a player application.
	@constant		kMERAWProcessorObjectNameKey
		A user-readable string describing the RAW processor. This string is used for uniquely identifying RAW processors and possibly for debug logging but is typically not visible to users.
*/
#define kMERAWProcessorClassImplementationIDKey				@"ClassImplementationID"
#define kMERAWProcessorProcessorInfoKey						@"ProcessorInfo"
#define kMERAWProcessorCodecTypeKey							@"CodecType"
#define kMERAWProcessorCodecNameKey							@"CodecName"
#define kMERAWProcessorObjectNameKey						@"ObjectName"


#endif /* MEExtensionPlugin_h */
