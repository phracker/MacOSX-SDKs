/*
	File:  MEVideoDecoder.h
	
	Framework:  MediaExtension
 
	Copyright © 2024 Apple Inc. All rights reserved.
	
	Overview

	This file contains the interface/protocol for MediaExtension video decoders. Developers who wish to build MediaExtension
	video decoders using this API will need to include the required entitlement along with a provisioning profile when building
	their extensions. For more information about public entitlements and provisioning profiles see:
	https://developer.apple.com/documentation/bundleresources/entitlements
	https://developer.apple.com/help/account/manage-provisioning-profiles/create-a-development-provisioning-profile

	MediaExtension Video Decoder Entitlement

	The video decoder must include the public entitlement key "com.apple.developer.mediaextension.videodecoder" with a boolean
	value set to true. A provisioning profile will be needed to use this entitlement.

	MediaExtension Video Decoder Info.plist File Information

	The following standard bundle Info.plist keys have significance for MediaExtension video decoders:
 
	- CFBundleVersion
 		This version number will be used to select among any duplicate installations of MediaExtension video decoders with the
		same ClassImplementationID. The version formatting should follow standard CFBundleVersion guidelines, with any major,
		minor, and patch versions all having values in the range of 0-255.
	- CFBundleDisplayName
		This name will be displayed to identify the video decoder in the System Settings listing of extension video decoders.
		The name can be localized using standard bundle localization techniques. If no display name is provided, the system
		will use the file name of the MediaExtension video decoder bundle.
	- CFBundleIconName
	- CFBundleIconFile
		The icon referenced here will displayed along with the CFBundleDisplayName in the System Settings listing of extension
		video decoders. If no icon is provided, the system will use a generic icon.
 
	MediaExtension video decoders will also need to include a specialized EXAppExtensionAttributes dictionary in their Info.plist
	files describing ExtensionKit information.

	EXAppExtensionAttributes Dictionary

	The EXAppExtensionAttributes dictionary is required by ExtensionKit. The following keys will be needed for ExtensionKit
	video decoders (see also MEExtensionPlugin.h):

	- ClassImplementationID
		This should be a string similar to the bundle identifier of the video decoder. It should start with the reverse domain
		identifier of the developer to prevent collisions with other developers, and for clarity contain ".videodecoder." and
		the name of the codec. If the developer envisions multiple variants of the same decoder, the name should include strings
		to make each video decoder unique. An example might be something like "com.mycompany.videodecoder.mycodec.codecvariant".
	- EXExtensionPointIdentifier
		The string "com.apple.mediaextension.videodecoder" (kMEVideoDecoderExtensionPointName).
	- EXPrincipalClass
		The name of the video decoder factory class, conforming to the MEVideoDecoderExtension protocol.
	- CodecInfo
		An array of one or more dictionaries describing the codecs that the decoder supports. Each dictionary must include the
		following keys:
		* CodecType
			A string describing the four-character code of the codec that the decoder supports. Each string should be exactly four
			characters long and use ASCII character set encoding.
		* CodecName
			A user-readable string describing the name of the codec format. This string might be displayed as format information for
			the video track in a player application.
	- ObjectName
		A user-readable string describing the decoder. This string is used for uniquely identifying video decoders and possibly for
		debug logging but is typically not visible to users.
 
 
	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#ifndef MEVIDEODECODER_H
#define MEVIDEODECODER_H


/*!
	MediaExtension Video Decoder Call Flow and Life Cycle Overview

	MediaExtension video decoder operation and life cycle are closely tied to VTDecompressionSession.
	See <VideoToolbox/VTDecompressionSession.h> for more details on this interface.

	Creation:
		An instance of an MEVideoDecoderExtension factory object is created the first time a given decoder is opened
		by the VideoToolbox in a process. The videoDecoderWithCodecType: method on the MEVideoDecoderExtension
		object will be called once for each decoder instance needed. The decoder can evaluate the provided codecType
		and CMVideoFormatDescription at this point and confirm whether it is able to decode the specified format. If the
		decoder cannot decode the format, the factory routine should return MEErrorUnsupportedFeature. This sequence of
		calls will happen inside of VTDecompressionSessionCreate.

	Pixel Buffer Requirement Configuration:
		At any point after instantiation, the decoder can call back into the provided MEVideoDecoderPixelBufferManager object
		to notify the VideoToolbox of its output pixelBuffer requirements. The decoder extension may make multiple calls if
		output requirements change in response to properties being set or due to observed bitstream characteristics.

	Property calls
		Properties can be queried or set on the decoder at any time, before, during or after frame decode, unless otherwise
		noted. These calls generally correspond to calls to VTSessionSetProperty and VTSessionCopyProperty being made
		on the VTDecompressionSession which opened the decoder. There may be cases where the VideoToolbox directly sets or
		queries properties as well.

	Frame Decoding:
		Calls to decodeFrameFromSampleBuffer: will be serialized.  A new frame will not be sent to the decoder until the last
		decodeFrameFromSampleBuffer: has returned, but may be submitted before the decodeFrameFromSampleBuffer: completion
		handler is called if the decode is happening asynchronously. These calls correspond to VTDecompressionSessionDecodeFrame
		calls on the parent VTDecompressionSession.

		Video decoders must write their output frames into CVPixelBuffers allocated through the MEVideoDecoderPixelBufferManager
		createPixelBufferAndReturnError: interface. Returning CVPixelBuffers from any other source may result in degraded performance
		or other issues.

		If the decoder's internal decoding queue is full, and it cannot decode more frames, it should return
		NO when the isReadyForMoreMediaData property is queried.  This property should return YES again when the decoder
		is able to accept new frames -- generally after an earlier asynchronous frame decode is completed.

	Format Description Changes:
		If there is a change in the format description on incoming CMSampleBuffers, the VideoToolbox will confirm whether the
		decoder is able to transition to the new format description by calling the canAcceptFormatDescription: method. If this
		method returns "NO", the decoder will usually be closed and a new instance will be created for the new format description.
		This call may either be triggered by a call to VTDecompressionSessionCanAcceptFormatDescription, or be initiated directly by
		the VideoToolbox if a format description change is seen on incoming CMSampleBuffers.
*/

#import <Foundation/Foundation.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreFoundation/CoreFoundation.h>
#import <VideoToolbox/VideoToolbox.h>
#import <CoreVideo/CVPixelBuffer.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MEVideoDecoder;
@class MEVideoDecoderPixelBufferManager;

/*!
	@protocol		MEVideoDecoderExtension
	@abstract		Provides a stateless factory interface for creating new MEVideoDecoder instances.
	@discussion		The MEVideoDecoderExtension protocol provides a factory method to create a new MEVideoDecoder instance for a codecType implemented by the extension. A single MEVideoDecoderExtension is instantiated by the Video Toolbox, and will be called to create individual MEVideoDecoder instances as needed. If the codecType or FormatDescription passed to videoDecoderWithCodecType is not compatible with the MEVideoDecoder implementation, the factory call should fail and return MEErrorUnsupportedFeature.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MEVideoDecoderExtension <NSObject>

- (instancetype)init;

/*!
	@method			videoDecoderWithCodecType
	@abstract		The factory method to create a new MEVideoDecoder.
	@discussion		Creates a new MEVideoDecoder matching the given CMVideoCodecType and CMVideoFormatDescriptionRef.  If these parameters are not compatible with the MEVideoDecoder, the call should fail, returnig MEErrorUnsupportedFeature.
	@param			codecType
		The codec type for the requested decoder
	@param			videoFormatDescription
		A CMVideoFormatDescription describing the video data.
	@param			videoDecoderSpecifications
		A dictionary of videoDecoderSpecification values (See kVTVideoDecoderSpecification keys in VideoToolbox/VTDecompressionProperties.h).  This may be empty.
	@param			extensionDecoderPixelBufferManager
		An MEVideoDecoderPixelBufferManager instance that should be retained by the new MEVideoDecoder instance and used for output pixelBuffer configuration and allocation.
	@param			error
		On return, if initialization of the MEVideoDecoder fails, points to an NSError describing the nature of the failure.
	@result			A newly created instance conforming to MEVideoDecoder.
*/
- (id<MEVideoDecoder> _Nullable)videoDecoderWithCodecType:(CMVideoCodecType)codecType
								   videoFormatDescription: (CMVideoFormatDescriptionRef) videoFormatDescription
							   videoDecoderSpecifications: (NSDictionary<NSString *, id> * )videoDecoderSpecifications
					   extensionDecoderPixelBufferManager: (MEVideoDecoderPixelBufferManager *)extensionDecoderPixelBufferManager
													error:(NSError *__autoreleasing _Nullable * _Nullable)error NS_SWIFT_NAME(makeVideoDecoder(codecType:videoFormatDescription:videoDecoderSpecifications:pixelBufferManager:));

@end

/*!
	@interface		MEVideoDecoderPixelBufferManager
	@abstract		Describes pixel buffer requirements and creates new pixel buffers.
	@discussion		Contains the interfaces that the App Extension video decoder uses for two tasks. First, to declare its set of requirements for output CVPixelBuffers in the form of a pixelBufferAttributes dictionary. Second, to create pixelBuffers which match decoder output requirements but also satisfy VideoToolbox and client requirements.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEVideoDecoderPixelBufferManager : NSObject

/*!
	@property		pixelBufferAttributes
	@abstract		VideoToolbox will use these attributes when creating a PixelBuffer for the decoder.
	@discussion		This can be updated by the decoder before requesting a new pixelBuffer.
*/
@property(nonatomic, copy,readwrite) NSDictionary<NSString*, id> * pixelBufferAttributes;


/*!
	@method			createPixelBufferAndReturnError:
	@abstract		Generates a pixel buffer using the session's pixel buffer pool.
	@discussion		If implemented in Objective-C, the caller is responsible for releasing the returned CVPixelBuffer.
	@param			error
		If provided, returns error information in the event that the method fails.
	@result
		A pixel buffer compatible with the extension's most recently set pixelBufferAttributes
*/
- (CVPixelBufferRef _Nullable) createPixelBufferAndReturnError: (NSError **)error CF_RETURNS_RETAINED NS_SWIFT_NAME(makePixelBuffer());


/*!
	@method			registerCustomPixelFormat
	@abstract		VideoToolbox will register the described pixelFormat in both the Extension process and the client process.
	@discussion		This property is appropriate for decoders which produce output in a custom pixel format.  This will generally only be used by decoders which produce RAW output, where the decoder's output buffers will only be consumed by an MERAWProcessor extension which registers the same pixel format. MERAWProcessor needs to manually register the custom pixel format using CVPixelFormatDescriptionRegisterDescriptionWithPixelFormatType().
	@param			customPixelFormat
		This dictionary contains a set of keys and values as described in CoreVideo/CVPixelFormatDescription.h suitable for providing
		as the 'description' parameter to CVPixelFormatDescriptionRegisterDescriptionWithPixelFormatType.  This must contain the
		custom pixel format fourCC as the value for the kCVPixelFormatCodecType key.
*/
- (void) registerCustomPixelFormat: (NSDictionary<NSString*, id> *) customPixelFormat;

@end


/*!
	@interface		MEDecodeFrameOptions
	@abstract		Conveys directives or options from the VideoToolbox to guide decoder operation on a per-frame basis.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEDecodeFrameOptions : NSObject

/*!
	@property		doNotOutputFrame
	@abstract		A hint to the video decoder that a CVImageBuffer should not be emitted for this frame.  NULL will be returned instead.
*/
@property(readwrite) BOOL doNotOutputFrame;


/*!
	@property		realTimePlayback
	@abstract		A hint to the video decoder that it would be OK to use a low-power mode that can not decode faster than 1x realtime.
	@discussion		Note that this hint only takes the current decode session into account.  For example, if multiple instances of a decoder are operating at once, it may not actually be OK to use such a low-power mode if real-time playback might not be sustained across all the streams. This hint will be set to false during all uses other than 1x forward real-time playback, including seeking, playback at other rates, and export.
*/
@property(readwrite) BOOL realTimePlayback;

@end


// This notification is used to notify the VideoToolbox that the value of the readyForMoreMediaData property has changed
ME_EXPORT NSNotificationName const MEVideoDecoderReadyForMoreMediaDataDidChangeNotification API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);



/*!
	@enum			MEDecodeFrameStatus
	@abstract		These values are used to convey non-error status related to a frame decode operation.
	@constant		MEDecodeFrameNoStatus
		Set by the decoder to indicate that no non-error status information is available.
	@constant		MEDecodeFrameFrameDropped
		Set by the decoder to report that output of this frame was dropped for non-error reasons, for example, if doNotOutputFrame was specified.
*/
typedef NS_OPTIONS(NSUInteger, MEDecodeFrameStatus) {
	MEDecodeFrameNoStatus				= 0UL,
	MEDecodeFrameFrameDropped			= 1UL << 0,
} API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);


/*!
	@protocol		MEVideoDecoder
	@abstract		The primary object for a MediaExtension video decoder, providing an interface for VideoToolbox to talk to the decoder.
	@discussion		The MEVideoDecoder protocol provides an interface for the VideoToolbox to interact with MediaExtension video decoders. MEVideoDecoder objects are always instantiated by the VideoToolbox. To create an MEVideoDecoder, the VideoToolbox first creates an MEVideoDecoderExtension object and calls its videoDecoderWithCodecType: method. MEVideoDecoders should expect to run in a sandboxed process without access to the file system, network, or other kernel resources.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MEVideoDecoder <NSObject>


@optional

/*!
	@property		producesRAWOutput
	@abstract		The extension should implement this property returning YES if the decoder produces RAW ouput which requires the use of an MERAWProcessor for post-decode processing to produce renderable output.
	@discussion		This optional property is queried on the extension when a VideoToolbox client queries the kVTDecompressionPropertyKey_DecoderProducesRAWOutput property on the hosting VTDecompressionSession.
*/
@property (readonly) BOOL producesRAWOutput;

/*!
	@property		contentHasInterframeDependencies
	@abstract		The extension should return whether the content being decoded has interframe dependencies, if the decoder knows.
	@discussion		This optional property is queried on the extension when a VideoToolbox client queries the kVTDecompressionPropertyKey_ContentHasInterframeDependencies property on the hosting VTDecompressionSession.
*/
@property (readonly) BOOL contentHasInterframeDependencies;


/*!
	@property		recommendedThreadCount
	@abstract		Sets the recommended number of threads to be used by the decoder.
	@discussion		This optional property is set when a VideoToolbox client sets the kVTDecompressionPropertyKey_ThreadCount property on the hosting VTDecompressionSession.
*/
@property (readwrite) NSInteger recommendedThreadCount;


/*!
	@property		actualThreadCount
	@abstract		Returns the actual number of threads used by decoder.
	@discussion		This optional property is queried when a VideoToolbox client queries the kVTDecompressionPropertyKey_ThreadCount property on the hosting VTDecompressionSession.
*/
@property (readonly) NSInteger actualThreadCount;


/*!
	@property		supportedPixelFormatsOrderedByQuality
	@abstract		Provides hints about quality tradeoffs between pixel formats.
	@discussion		This optional property value is an array of NSNumbers with CMPixelFormatTypes values, ordered by quality from best to worse. This property is queried when a VideoToolbox client queries the kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByQuality property on the hosting VTDecompressionSession.
*/
@property (readonly) NSArray<NSNumber *> * supportedPixelFormatsOrderedByQuality;


/*!
	@property		reducedResolution
	@abstract		Requests decoding at a smaller resolution than full-size.
	@discussion		This optional property conveys a request for reduced resolution for decoding. Decoders that only support a fixed set of resolutions should pick the smallest resolution greater than or equal to the requested { width, height }. If the output CVPixelBuffer is not in a format where reduced resolution decoding is supported, this setting should be disregarded. This property is set on the extension when a VideoToolbox client sets the kVTDecompressionPropertyKey_ReducedResolutionDecode property on the hosting VTDecompressionSession.
*/
@property (readwrite) CGSize reducedResolution;

/*!
	@property		pixelFormatsWithReducedResolutionDecodeSupport
	@abstract		Provides a list of output pixel formats where the decoder supports reduced resolution decoding
	@discussion		This optional property should return an array of NSNumbers holding CMPixelFormatType values. This property is queried when a VideoToolbox client queries the kVTDecompressionPropertyKey_PixelFormatsWithReducedResolutionSupport property on the hosting VTDecompressionSession.
*/
@property (readonly) NSArray<NSNumber *> * pixelFormatsWithReducedResolutionDecodeSupport;


@required

/*!
	@property		readyForMoreMediaData
	@abstract		Indicates the readiness of the decoder to accept more sample buffers.
	@discussion		Video decoders which operate asynchronously often have a fixed capacity for buffers in flight in the decoder. This property allows the decoder to signal to the VideoToolbox that its internal buffers are full and it cannot accept more samples at this time. The decoder must use MEVideoDecoderReadyForMoreMediaDataDidChangeNotification to notify the VideoToolbox when this property changes.
*/
@property (nonatomic, readonly, getter=isReadyForMoreMediaData) BOOL readyForMoreMediaData;

/*!
	@method			decodeFrameFromSampleBuffer:options:completionHandler:
	@abstract		Requests that the extension decode a video frame.
	@discussion		The completionHandler block must be called for every decodeFrameFromSampleBuffer call when decode is complete. The completion handler block should return either a decoded pixelBuffer, an error, or a decodeStatus indicating the frame was dropped.
	@param			sampleBuffer
		A CMSampleBuffer containing one video frame.
	@param			options
		A MEDecodeFrameOptions containing specific requests for this frame.
	@param			completionHandler
		The handler that will be invoked when a frame is decoded and ready to be sent back to
		caller. This block will not necessarily be called in display order.
		'imageBuffer'
			Contains the decompressed frame if decompression was successful, otherwise NULL. The imageBuffer must be allocated using MEVideoDecoderPixelBufferManager.
		'decodeStatus'
			Reports the status of decoding the sampleBuffer.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil. Errors outside of MediaExtensionErrorDomain will be reported as kVTVideoDecoderUnknownErr to the VTDecompressionSession client.
*/
- (void) decodeFrameFromSampleBuffer: (CMSampleBufferRef)sampleBuffer
							 options: (MEDecodeFrameOptions *)options
				   completionHandler: (void (^)(CVImageBufferRef _Nullable imageBuffer,
												MEDecodeFrameStatus decodeStatus,
												NSError * _Nullable error))completionHandler;

@optional
/*!
	@method			canAcceptFormatDescription:
	@abstract		Asks the extension whether the decoder can decode frames with the given format description.
	@discussion		Some video decoders are able to accommodate minor changes in format without needing to be completely reset in a new session. This function can be used to test whether a format change is allowed.
	@param			formatDescription
		The new format description that need to be evaluated.
	@result			YES if the decoder can continue decoding samples without being reset, NO if this is not possible. If this method returns NO, typically the VideoToolbox will release the current decoder instance and instantiate a new one using the new format description.
*/
- (BOOL) canAcceptFormatDescription: (CMFormatDescriptionRef) formatDescription;


@end


NS_ASSUME_NONNULL_END


#endif /* MEVIDEODECODER_H */
