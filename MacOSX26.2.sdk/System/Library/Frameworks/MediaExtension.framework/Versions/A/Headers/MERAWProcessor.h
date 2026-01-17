/*
	File:  MERAWProcessor.h
	
	Framework:  MediaExtension
 
	Copyright © 2024 Apple Inc. All rights reserved.
	
	Overview
 
	This file contains the interface/protocol for MediaExtension RAW processors. Developers who wish to build MediaExtension
	RAW processors using this API will need to include the required entitlement along with a provisioning profile when building
	their extensions. For more information about public entitlements and provisioning profiles see:
	https://developer.apple.com/documentation/bundleresources/entitlements
	https://developer.apple.com/help/account/manage-provisioning-profiles/create-a-development-provisioning-profile

	MediaExtension RAW Processor Entitlement

	The RAW processor must include the public entitlement key "com.apple.developer.mediaextension.videodecoder" (the same
	as for video decoders) with a boolean value set to true. A provisioning profile will be needed to use this entitlement.
 
	MediaExtension RAW Processor Info.plist File Information

	The following standard bundle Info.plist keys have significance for MediaExtension RAW Processors:
 
	- CFBundleVersion
 		This version number will be used to select among any duplicate installations of MediaExtension RAW processors with the
		same ClassImplementationID. The version formatting should follow standard CFBundleVersion guidelines, with any major,
		minor, and patch versions all having values in the range of 0-255.
	- CFBundleDisplayName
		This name will be displayed to identify the RAW processor in the System Settings listing of extension RAW processors.
		The name can be localized using standard bundle localization techniques. If no display name is provided, the system
		will use the file name of the MediaExtension RAW processor bundle.
	- CFBundleIconName
	- CFBundleIconFile
		The icon referenced here will displayed along with the CFBundleDisplayName in the System Settings listing of extension
		RAW processors. If no icon is provided, the system will use a generic icon.
 
	MediaExtension RAW Processors will also need to include a specialized EXAppExtensionAttributes dictionary in their Info.plist
	files describing ExtensionKit information.

	EXAppExtensionAttributes Dictionary

	The EXAppExtensionAttributes dictionary is required by ExtensionKit. The following keys will be needed for ExtensionKit
	RAW processors (see also MEExtensionPlugin.h):

	- ClassImplementationID
		This should be a string similar to the bundle identifier of the RAW processor. It should start with the reverse domain
		identifier of the developer to prevent collisions with other developers, and for clarity contain ".rawprocessor." and
		the name of the codec associated with the processor. If the developer envisions multiple variants of the same RAW processor,
		the name should include strings to make each RAW processor unique. An example might be something like
		"com.mycompany.rawprocessor.mycodec.codecvariant".
	- EXExtensionPointIdentifier
		The string "com.apple.mediaextension.rawprocessor" (kMERAWProcessorExtensionPointName).
	- EXPrincipalClass
		The name of the RAW Processor factory class, conforming to the MERAWProcessorExtension protocol.
	- ProcessorInfo
		An array of one or more dictionaries describing the formats that the RAW Processor supports. Each dictionary must include the
		following keys:
		* CodecType
			A string describing the four-character code of the codec associated with the RAW processor. Each string should be exactly four
			characters long and use ASCII character set encoding.
		* CodecName
			A user-readable string describing the name of the RAW processor. This string may be used in user-visible scenarios.
	- ObjectName
		A user-readable string describing the RAW processor. This string is used for uniquely identifying processors and possibly for
		debug logging but is typically not visible to users.
 
 
	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#ifndef MERAWPROCESSOR_H
#define MERAWPROCESSOR_H


/*!
	MediaExtension RAW Processor Call Flow and Life Cycle Overview

	MediaExtension RAW processor operation and life cycle are closely tied to VTRAWProcessingSession.
	See <VideoToolbox/VTRAWProcessingSession.h> for more details on this interface.

	Creation:
		An instance of an MERAWProcessorExtension factory object is created the first time a given processor is opened
		by the VideoToolbox in a process. The processorWithFormatDescription: method on the MERAWProcessorExtension
		object will be called once for each processor instance needed. The processor can evaluate the provided codecType
		and CMVideoFormatDescription at this point and confirm whether it is able to process the specified format. If the
		processor cannot process the format, the factory routine should return MEErrorUnsupportedFeature. This sequence of
		calls will happen inside of VTRAWProcessingSessionCreate.

	Pixel Buffer Requirement Configuration:
		At any point after instantiation, the processor can call back into the provided MERAWProcessorPixelBufferManager object
		to notify the VideoToolbox of its output pixelBuffer requirements. The processor extension may make multiple calls if
		output requirements change in response to properties being set or due to observed bitstream characteristics.

	Frame Processing:
		Calls to processFrameFromImageBuffer: will be serialized.  A new frame will not be sent to the processor until the last
		processFrameFromImageBuffer: has returned, but may be submitted before the processFrameFromImageBuffer: completion
		handler is called if the processing is happening asynchronously. These calls correspond to VTRAWProcessingSessionProcessFrame
		calls on the parent VTRAWProcessingSession.

		RAW processors must write their output frames into CVPixelBuffers allocated through the MERAWProcessorPixelBufferManager
		createPixelBufferAndReturnError: interface. Returning CVPixelBuffers from any other source may result in degraded performance
		or other issues.

		If the processor's internal processing queue is full, and it cannot process more frames, it should return
		NO when the isReadyForMoreMediaData property is queried.  This property should return YES again when the processor
		is able to accept new frames -- generally after an earlier asynchronous frame processing operation is completed.
*/

#import <Foundation/Foundation.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreFoundation/CoreFoundation.h>
#import <VideoToolbox/VideoToolbox.h>
#import <CoreVideo/CVPixelBuffer.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MERAWProcessor;
@class MERAWProcessorPixelBufferManager;

/*!
	@protocol		MERAWProcessorExtension
	@abstract		Provides a stateless factory interface for creating new MERAWProcessor instances.
	@discussion		The MERAWProcessorExtension protocol provides a factory method to create a new MERAWProcessor instance for a codecType implemented by the extension. A single MERAWProcessorExtension is instantiated by the Video Toolbox, and will be called to create individual MERAWProcessor instances as needed. If the codecType or FormatDescription passed to processorWithCodecType is not compatible with the MERAWProcessor implementation, the factory call should fail and return MEErrorUnsupportedFeature.
*/
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MERAWProcessorExtension <NSObject>

- (instancetype)init;

/*!
	@method			processorWithFormatDescription
	@abstract		The factory method to create a new MERAWProcessor.
	@discussion		Creates a new MERAWProcessor matching the given CMVideoFormatDescriptionRef.  If these parameters are not compatible with the MERAWProcessor, the call should fail, returning MEErrorUnsupportedFeature.
	@param			formatDescription
		A CMVideoFormatDescription describing the video data that was decoded to produce the RAW input for the RAW Processor.
	@param			extensionPixelBufferManager
		An MERAWProcessorPixelBufferManager instance that should be retained by the new MERAWProcessor instance and used for output pixelBuffer configuration and allocation.
	@param			error
		On return, if initialization of the MERAWProcessor fails, points to an NSError describing the nature of the failure.  Failures could be due to incompatible formatDescription or may be do to some other resource required by the processor not being found.  Errors should be  from the MediaExtensionErrorDomain domain.
	@result			A newly created instance conforming to MERAWProcessor.
*/
- (id<MERAWProcessor> _Nullable)processorWithFormatDescription: (CMVideoFormatDescriptionRef) formatDescription
								   extensionPixelBufferManager: (MERAWProcessorPixelBufferManager *)extensionPixelBufferManager
														 error: (NSError *__autoreleasing _Nullable * _Nullable)error NS_SWIFT_NAME(makeProcessor(formatDescription:pixelBufferManager:));

@end

/*!
	@interface		MERAWProcessorPixelBufferManager
	@abstract		Describes pixel buffer requirements and creates new pixel buffers.
	@discussion		Contains the interfaces that the App Extension RAW processor uses for two tasks. First, to declare its set of requirements for output CVPixelBuffers in the form of a pixelBufferAttributes dictionary. Second, to create pixelBuffers which match processor output requirements but also satisfy VideoToolbox and client requirements.
*/
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MERAWProcessorPixelBufferManager : NSObject

/*!
	@property		pixelBufferAttributes
	@abstract		VideoToolbox will use these attributes when creating a pixelBuffer for the RAW Processor.
	@discussion		This can be updated by the processor before requesting a new pixelBuffer.
*/
@property(nonatomic, copy, readwrite) NSDictionary<NSString*, id> * pixelBufferAttributes NS_REFINED_FOR_SWIFT;


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

@end

/*!
	@interface		MERAWProcessingParameter
	@abstract		An object implementing this protocol is implemented by the RAW Processor to describe each processing parameter the Processor exposes.
	@discussion		The MERAWProcessingParameter protocol provides an interface for the VideoToolbox to query descriptions of the different parameters that can be used to influence Processor operation.  A distinct MERAWProcessingParameter is created for each parameter supported by the Processor, and the set of supported parameters is returned by the MERAWProcessor's processingParameters interface.
*/
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MERAWProcessingParameter : NSObject

/*!
 @property		name
 @abstract		A localized human-readable name for the parameter, suitable for displaying in application UI.
 */
@property(readonly) NSString * name;

/*!
 @property		key
 @abstract		A unique key string identifying this parameter.
 */
@property(readonly) NSString * key;

/*!
 @property		longDescription
 @abstract		A localized description of the parameter, suitable for displaying in a tool tip or similar explanatory UI.
 */
@property(readonly) NSString * longDescription;

/*!
 @property		enabled
 @abstract		Indicates whether the parameter is enabled or disabled by the extension.
 @discussion	This parameter can only be modified by the extension.  From the application-facing interface, VTRAWProcessingSession, this is a read-only value which indicates whether the parameter should be greyed out and disabled in any UI being generated.
 */
@property(readwrite) BOOL enabled;

@end

/*!
	@interface		MERAWProcessingListElementParameter
	@abstract		An object implementing this protocol is implemented by the RAW Processor to describe each processing parameter the Processor exposes.
	@discussion		The MERAWProcessingListElementParameter protocol provides an interface for VideoToolbox to query descriptions of the different elements in a parameter list  for a List element in a MERAWProcessingParameter.  A distinct MERAWProcessingListElementParameter is created for each list element.
*/
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(MERAWProcessingParameter.ListElement)
@interface MERAWProcessingListElementParameter : MERAWProcessingParameter

- (instancetype)initWithName:(NSString *)name description:(NSString*)description elementID:(NSInteger)elementID;

/*!
	@property		listElementID
	@abstract		A unique number in this list which represents this list option.
	@discussion 	The set of elements in the list may change depending on other configuration parameters, so while the index of an element in this list may change, this ID never changes and is used to report list element selection
*/
@property(readonly) NSInteger listElementID;

@end

API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(MERAWProcessingParameter.Boolean)
@interface MERAWProcessingBooleanParameter : MERAWProcessingParameter
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(BOOL)initialValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(BOOL)initialValue neutralValue:(BOOL)neutralValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(BOOL)initialValue cameraValue:(BOOL)cameraValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(BOOL)initialValue neutralValue:(BOOL)neutralValue cameraValue:(BOOL)cameraValue NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
 @property		initialValue
 @abstract		The initial value for this parameter as defined in the sequence metadata.
 */
@property(readonly) BOOL initialValue;

/*!
 @property		currentValue
 @abstract		Get or set the current value for this parameter.
 @discussion	This property can be observed if appropriate in order to react to changes which would result in changes to the set of MERAWProcessingParameters vended by the extension.
 */
@property(readwrite) BOOL currentValue;

/*!
 @property		hasNeutralValue
 @abstract		Return value indicates whether the MERAWProcessingBooleanParameter has an optional declared Neutral value.
 @discussion	If the return value is YES and outNeutralValue is not nil, the value held by outNeutralValue will be set to the neutral value.
				If the return value is NO and outNeutralValue is not nil, the value held by outNeutralValue will be set to NO.
 */
- (BOOL)hasNeutralValue:(BOOL * _Nullable)outNeutralValue NS_REFINED_FOR_SWIFT;

/*!
 @property		hasCameraValue
 @abstract		Return value indicates whether the MERAWProcessingBooleanParameter has an optional declared Camera value.
 @discussion	If the return value is YES and outCameraValue is not nil, the value held by outCameraValue will be set to the camera value.
				If the return value is NO and outCameraValue is not nil, the value held by outCameraValue will be set to NO.
 */
- (BOOL)hasCameraValue:(BOOL * _Nullable)outCameraValue NS_REFINED_FOR_SWIFT;

@end

API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(MERAWProcessingParameter.Integer)
@interface MERAWProcessingIntegerParameter : MERAWProcessingParameter
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(NSInteger)initialValue maximum:(NSInteger)maximum minimum:(NSInteger)minimum NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(NSInteger)initialValue maximum:(NSInteger)maximum minimum:(NSInteger)minimum neutralValue:(NSInteger)neutralValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(NSInteger)initialValue maximum:(NSInteger)maximum minimum:(NSInteger)minimum cameraValue:(NSInteger)cameraValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(NSInteger)initialValue maximum:(NSInteger)maximum minimum:(NSInteger)minimum neutralValue:(NSInteger)neutralValue cameraValue:(NSInteger)cameraValue NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
	@property		maximumValue
	@abstract		The maximum value for this parameter.
*/
@property(readonly) NSInteger maximumValue;
/*!
	@property		minimumValue
	@abstract		The minimum value for this parameter.
*/
@property(readonly) NSInteger minimumValue;

/*!
	@property		initialValue
	@abstract		The initial value for this parameter as defined in the sequence metadata.
*/
@property(readonly) NSInteger initialValue;

/*!
	@property		currentValue
	@abstract		Get or set the current value for this parameter. 
	@discussion		This property can be observed if appropriate in order to react to changes which would result in changes to the set of MERAWProcessingParameters vended by the extension.
*/
@property(readwrite) NSInteger currentValue;

/*!
 @property		hasNeutralValue
 @abstract		Return value indicates whether the MERAWProcessingIntegerParameter has an optional declared Neutral value.
 @discussion	If the return value is YES and outNeutralValue is not nil, the value held by outNeutralValue will be set to the neutral value.
				If the return value is NO and outNeutralValue is not nil, the value held by outNeutralValue will be set to 0.
 */
- (BOOL)hasNeutralValue:(NSInteger * _Nullable)outNeutralValue NS_REFINED_FOR_SWIFT;

/*!
 @property		hasCameraValue
 @abstract		Return value indicates whether the MERAWProcessingIntegerParameter has an optional declared Camera value.
				If the return value is YES and outCameraValue is not nil, the value held by outCameraValue will be set to the camera value.
				If the return value is NO and outCameraValue is not nil, the value held by outCameraValue will be set to 0.
 */
- (BOOL)hasCameraValue:(NSInteger * _Nullable)outCameraValue NS_REFINED_FOR_SWIFT;

@end

API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(MERAWProcessingParameter.FloatingPoint)
@interface MERAWProcessingFloatParameter : MERAWProcessingParameter

- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(float)initialValue maximum:(float)maximum minimum:(float)minimum NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(float)initialValue maximum:(float)maximum minimum:(float)minimum neutralValue:(float)neutralValue  NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(float)initialValue maximum:(float)maximum minimum:(float)minimum cameraValue:(float)cameraValue  NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description initialValue:(float)initialValue maximum:(float)maximum minimum:(float)minimum neutralValue:(float)neutralValue cameraValue:(float)cameraValue NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
	@property		maximumValue
	@abstract		The maximum value for this parameter.
*/
@property(readonly) float maximumValue;
/*!
	@property		minimumValue
	@abstract		The minimum value for this parameter.
*/
@property(readonly) float minimumValue;

/*!
	@property		initialValue
	@abstract		The initial value for this parameter as defined in the sequence metadata.
*/
@property(readonly) float initialValue;

/*!
	@property		currentValue
	@abstract		Get or set the current value for this parameter. 
	@discussion		This property can be observed if appropriate in order to react to changes which would result in changes to the set of MERAWProcessingParameters vended by the extension.
*/
@property(readwrite) float currentValue;

/*!
 @property		hasNeutralValue
 @abstract		Return value indicates whether the MERAWProcessingFloatParameter has an optional declared Neutral value.
 @discussion	If the return value is YES and outNeutralValue is not nil, the value held by outNeutralValue will be set to the neutral value.
				If the return value is NO and outNeutralValue is not nil, the value held by outNeutralValue will be set to 0.
 */
- (BOOL)hasNeutralValue:(float * _Nullable)outNeutralValue NS_REFINED_FOR_SWIFT;

/*!
 @property		hasCameraValue
 @abstract		Return value indicates whether the MERAWProcessingFloatParameter has an optional declared Camera value.
 @discussion	If the return value is YES and outCameraValue is not nil, the value held by outCameraValue will be set to the camera value.
				If the return value is NO and outCameraValue is not nil, the value held by outCameraValue will be set to 0.
 */
- (BOOL)hasCameraValue:(float * _Nullable)outCameraValue NS_REFINED_FOR_SWIFT;

@end


API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(MERAWProcessingParameter.List)
@interface MERAWProcessingListParameter : MERAWProcessingParameter
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description list:(NSArray<MERAWProcessingListElementParameter *>*)listElements initialValue:(NSInteger)initialValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description list:(NSArray<MERAWProcessingListElementParameter *>*)listElements initialValue:(NSInteger)initialValue neutralValue:(NSInteger)neutralValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description list:(NSArray<MERAWProcessingListElementParameter *>*)listElements initialValue:(NSInteger)initialValue cameraValue:(NSInteger)cameraValue NS_REFINED_FOR_SWIFT;
- (instancetype)initWithName:(NSString *)name key:(NSString*)key description:(NSString*)description list:(NSArray<MERAWProcessingListElementParameter *>*)listElements initialValue:(NSInteger)initialValue neutralValue:(NSInteger)neutralValue cameraValue:(NSInteger)cameraValue NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
	@property		listElements
	@abstract		The ordered array of MERAWProcessingListElementParameter which make up this list.
*/
@property(readonly) NSArray<MERAWProcessingListElementParameter *> * listElements;

/*!
	@property		initialValue
	@abstract		The initial value for this parameter as defined in the sequence metadata.  The value is the listElementID value of the MERAWProcessingListElementParameter for initial settings.
*/
@property(readonly) NSInteger initialValue;

/*!
	@property		currentValue
	@abstract		Get or set the current value for this parameter.
	@discussion		The value is the listElementID value of the selected MERAWProcessingListElementParameter.   This property can be observed if appropriate in order to react to changes which would result in changes to the set of MERAWProcessingParameters vended by the extension.
*/
@property(readwrite) NSInteger currentValue;

/*!
 @property		hasNeutralValue
 @abstract		Return value indicates whether the MERAWProcessingListParameter has an optional declared Neutral value.
 @discussion	If the return value is YES and outNeutralValue is not nil, the value held by outNeutralValue will be set to the neutral value.
				If the return value is NO and outNeutralValue is not nil, the value held by outNeutralValue will be set to 0.
 */
- (BOOL)hasNeutralValue:(NSInteger * _Nullable)outNeutralValue NS_REFINED_FOR_SWIFT;

/*!
 @property		hasCameraValue
 @abstract		Return value indicates whether the MERAWProcessingListParameter has an optional declared Camera value.
 @discussion	If the return value is YES and outCameraValue is not nil, the value held by outCameraValue will be set to the camera value.
				If the return value is NO and outCameraValue is not nil, the value held by outCameraValue will be set to 0.
 */
- (BOOL)hasCameraValue:(NSInteger * _Nullable)outCameraValue NS_REFINED_FOR_SWIFT;

@end

API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(MERAWProcessingParameter.SubGroup)
@interface MERAWProcessingSubGroupParameter : MERAWProcessingParameter
- (instancetype)initWithName:(NSString *)name description:(NSString*)description parameters:(NSArray<MERAWProcessingParameter *>*)parameters;

@property(readonly) NSArray<MERAWProcessingParameter *> *subGroupParameters;

@end

// This notification is used to notify the client that processor has changed the set of available MERAWProcessingParameters.
// This includes changing the set of available parameters, changing the enabled state for parameters, or changing default values for parameters.
// This may occur in response to incoming parameter changes, for example, a change in a selected MERAWProcessingListElementParameter, or due to metadata-driven changes.
ME_EXPORT NSNotificationName const MERAWProcessorValuesDidChangeNotification API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) NS_REFINED_FOR_SWIFT;

// This notification is used to notify the VideoToolbox that the value of the readyForMoreMediaData property has changed
ME_EXPORT NSNotificationName const MERAWProcessorReadyForMoreMediaDataDidChangeNotification API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) NS_REFINED_FOR_SWIFT;

/*!
	@protocol		MERAWProcessor
	@abstract		The primary object for a MediaExtension RAW Processor, providing an interface for VideoToolbox to talk to the processor.
	@discussion		The MERAWProcessor protocol provides an interface for the VideoToolbox to interact with MediaExtension RAW Processors. MERAWProcessor objects are always instantiated by the VideoToolbox. To create an MERAWProcessor, the VideoToolbox first creates an MERAWProcessorExtension object and calls its processorWithFormatDescription: method. MERAWProcessors should expect to run in a sandboxed process without access to the file system, network, or other kernel resources.
*/
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MERAWProcessor <NSObject>

@optional
/*!
	@property		metalDeviceID
	@abstract		Requests that processor use the provided MTLDevice for Metal based processing.
	@discussion		This optional property requests that the RAWProcessor use the MTLDevice corresponding to this ID for any Metal-based processing.
					This is optional and does not need to be implemented If the processor does not use Metal.
*/
@property (nonatomic) uint64_t metalDeviceRegistryID;

/*!
	@property		outputColorAttachments
	@abstract		Returns the color-related CVImageBuffer keys and values that will be attachments to the output pixel buffers.
	@discussion		This is an optional property. Only color-related keys from CVImageBuffer.h are permitted in the returned dictionary.
*/
@property (readonly) NSDictionary<NSString *, id> *outputColorAttachments;

/*!
	@property       metadataForSidecarFile
	@abstract       The metadata returned is a pre-formatted NSData that represents a fully-formed sidecar file, and should be compatible with the MediaExtension FormatReader.
	@discussion     The metadata will contain the initial processing parameters from the sidecar file, along with any adjustments made on the RAW processor.
*/
@property (readonly) NSData *metadataForSidecarFile API_AVAILABLE(macos(26.0));

@required

/*!
	@property		processingParameters
	@abstract		Provides a list of processing parameters which can be changed by the client of the VideoToolbox session to influence processing behavior.
	@discussion		This property value is an array of MERAWProcessingParameters each of which describes the parameter and provides an interface where the processing parameter value may be modified.
*/
@property (readonly) NSArray<MERAWProcessingParameter *> *processingParameters;

/*!
	@property		readyForMoreMediaData
	@abstract		Indicates the readiness of the RAW Processor to accept more sample buffers.
	@discussion		RAW Processors which operate asynchronously often have a fixed capacity for buffers in flight in the processor. This property allows the processor to signal to the VideoToolbox that its internal buffers are full and it cannot accept more samples at this time. The processor must use MERAWProcessorReadyForMoreMediaDataDidChangeNotification to notify the VideoToolbox when this property changes.
*/
@property (nonatomic, readonly, getter=isReadyForMoreMediaData) BOOL readyForMoreMediaData;

/*!
	@method			processFrameFromImageBuffer:completionHandler:
	@abstract		Requests that the extension process a video frame.
	@discussion		The completionHandler block must be called for every processFrameFromImageBuffer call when processing is complete. The completion handler block should return either a processed pixelBuffer or an error.
	@param			inputFrame
		A CVPixelBuffer containing a video frame to be processed.
	@param			completionHandler
		The handler that will be invoked when a frame is processed and ready to be sent back to caller. This block does not need to be called in the order that frames were submitted.
		'imageBuffer'
			Contains the processed frame if processing was successful, otherwise NULL. The imageBuffer must be allocated using MERAWProcessorPixelBufferManager.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil. Errors outside of MediaExtensionErrorDomain will be reported as kVTRAWProcessorUnknownErr to the VTRAWProcessingSession client.
*/
- (void) processFrameFromImageBuffer: (CVPixelBufferRef)inputFrame
				   completionHandler: (void (^)(CVPixelBufferRef _Nullable imageBuffer,
												NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif /* MERAWPROCESSOR_H */
