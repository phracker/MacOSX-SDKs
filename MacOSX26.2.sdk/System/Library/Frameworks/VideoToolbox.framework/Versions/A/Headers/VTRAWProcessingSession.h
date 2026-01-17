/*
	File:  VTRAWProcessingSession.h
	
	Framework:  VideoToolbox
 
	Copyright © 2013-2024 Apple Inc. All rights reserved.
  
	Video Toolbox client API for accessing RAW Video processing components.
*/

#ifndef VTRAWPROCESSINGSESSION_H
#define VTRAWPROCESSINGSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>

#include <CoreMedia/CMFormatDescription.h>
#include <VideoToolbox/VTSession.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push, 4)

CM_ASSUME_NONNULL_BEGIN



/*!
	@typedef	VTRAWProcessingSessionRef
	@abstract	A reference to a Video Toolbox RAW Processing Session.
	@discussion
		A RAW processing session supports processing of frames that have been output from decoders in camera native formats, for example RAW or bayer formats.
		The session reference is a reference-counted CF object.
*/
typedef struct CM_BRIDGED_TYPE(id) OpaqueVTRAWProcessingSession*  VTRAWProcessingSessionRef API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) CM_SWIFT_NONSENDABLE;
CM_SWIFT_INIT_FOR_CF_TYPE(VTRAWProcessingSession, API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos));

/*!
	@typedef	VTRAWProcessingParameterChangeHandler
	@abstract	Block invoked when processing parameters change.
	@discussion
		This block is called when available parameters or parameter values change without an explicit call to VTRAWProcessingSessionSetProcessingParameters.
		This is intended to allow the client to update any UI driven by these parameters.
	@param	newParameters
		A CFArrayRef contaiing the new parameter details.  This follows the same form as the array returned from VTRAWProcessingSessionCopyProcessingParameters.
 */
typedef void (^VTRAWProcessingParameterChangeHandler)( CM_NULLABLE CFArrayRef newParameters ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	VTRAWProcessingSessionCreate
	@abstract	Creates a RAW video frame processing session.
	@discussion
		.
	@param	allocator
		An allocator for the session.  Pass NULL to use the default allocator.
	@param	formatDescription
		The CMVideoFormatDescription corresponding to the original media samples, containing sequence-level processing parameters.
	@param	outputPixelBufferAttributes
		A CoreVideo pixel buffer attributes dictionary describing the client's requirements for pixel buffers for output frames. 
		Pass NULL to receive the RAW processor's native output format.
	@param	processingSessionOptions
		A dictionary of creation-time options for the VTRAWProcessingSession.
	@param	processingSessionOut
		Points to a variable to receive the new RAW processing session.
		When you are done with the session, call VTRAWProcessingSessionInvalidate
		to tear it down and then CFRelease to release your object reference.
*/
VT_EXPORT OSStatus 
VTRAWProcessingSessionCreate(
	CM_NULLABLE CFAllocatorRef							allocator,
	CMVideoFormatDescriptionRef							formatDescription,
	CM_NULLABLE CFDictionaryRef							outputPixelBufferAttributes,
	CM_NULLABLE CFDictionaryRef							processingSessionOptions,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTRAWProcessingSessionRef * CM_NONNULL	processingSessionOut) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	VTRAWProcessingSessionInvalidate
	@abstract	Tears down a RAW processing session.
	@discussion
		When you are done with a decompression session you created, call VTRAWProcessingSessionInvalidate
		to tear it down and then CFRelease to release your object reference.
		When a  session's retain count reaches zero, it is automatically invalidated, but
		since sessions may be retained by multiple parties, it can be hard to predict when this will happen.
		Calling VTRAWProcessingSessionInvalidate ensures a deterministic, orderly teardown.
*/
VT_EXPORT void
VTRAWProcessingSessionInvalidate( VTRAWProcessingSessionRef session ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function VTRAWProcessingSessionGetTypeID
	@abstract Returns the CFTypeID for RAW processing sessions.
*/
VT_EXPORT CFTypeID 
VTRAWProcessingSessionGetTypeID(void) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	VTRAWProcessingSessionSetParameterChangedHandler
	@abstract	Provides a block which will be called when the VTRAWProcessingPlugin changes the set of processing parameters..
	@discussion
		This block will be called the VTRAWProcessingPlugin either changes the set of available processing parameters, or changes the current value of parameters.
		The VTRAWProcessingPlugin may change parameters based on metadata associated with input frames, or in response to other parameters configured by VTRAWProcessingSessionSetProcessingParameters.
		This optional and does not need to be configured if the client is not driving UI based on these parameters, or otherwise does not need this.
	@param	session
		The RAW processing session.
	@param	parameterChangeHandler
		 A VTRAWProcessingParameterChangeHandler block which will be called when the set of processing parameters changes, or the value of a parameter changes without the client explicitly requesting it.
		 Setting this to NULL removes the current handler.
*/
VT_EXPORT OSStatus
VTRAWProcessingSessionSetParameterChangedHandler(
	VTRAWProcessingSessionRef							session,
	CM_NULLABLE VTRAWProcessingParameterChangeHandler	parameterChangeHandler ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

VT_EXPORT OSStatus
VTRAWProcessingSessionSetParameterChangedHander(
	VTRAWProcessingSessionRef							session,
	CM_NULLABLE VTRAWProcessingParameterChangeHandler	parameterChangeHandler ) CF_REFINED_FOR_SWIFT API_DEPRECATED_WITH_REPLACEMENT("VTRAWProcessingSessionSetParameterChangedHandler", macos(15.0, 26.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@typedef	VTRAWProcessingOutputHandler
	@abstract	Block invoked when frame processing is complete.
	@discussion
		On successful processing, will return a CVPixelBuffer conforming to the session's outputPixelBufferAttributes if any were provided.
	@param	status
		noErr if processing request was successful; an error code if it was not successful.
	@param	processedPixelBuffer
		A CVPixelBuffer containing the processed video frame if processing request was successful;
		otherwise, NULL.
 */
typedef void (^VTRAWProcessingOutputHandler)(
		OSStatus status,
		CM_NULLABLE CVPixelBufferRef processedPixelBuffer) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	VTRAWProcessingSessionProcessFrame
	@abstract
		Call this function to submit RAW frames for format-specific processing using sequence and frame level parameters.
	@discussion
		Processed frames may or may not be output before the function returns, 
		The client should not modify the input pixel data after making this call.
		The RAW Processor will retain the input pixel buffer as long as necessary.
		
		For any RAW processor, there is a finite number of frames that can be 
		presented to VTRAWProcessingSessionProcessFrame before the function will block
		until the output callback is invoked.
	@param	session
		The RAW processing session.
	@param	inputPixelBuffer
		A CVPixelBuffer containing an input video frame to be processed.
	@param	frameOptions
		Contains key/value pairs specifying additional properties for processing this frame.
		No keys currently.  Pass NULL.
	@param	outputHandler
		A VTRAWProcessingOutputHandler block which will be called once when processing is complete.
*/
VT_EXPORT OSStatus
VTRAWProcessingSessionProcessFrame(
	VTRAWProcessingSessionRef				session,
	CVPixelBufferRef						inputPixelBuffer,
	CM_NULLABLE CFDictionaryRef				frameOptions,
	VTRAWProcessingOutputHandler 			outputHandler ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function VTRAWProcessingSessionCompleteFrames
	@abstract Forces the RAW Processor to complete processing frames.
	@discussion
		Call this after calling a set of VTRAWProcessingSessionProcessFrame calls to ensure that all frames have been processed.
		Before VTRAWProcessingSessionCompleteFrames returns, the output handler will be invoked for all pending frames.
	@param	session
		The RAW processing session.
*/
VT_EXPORT OSStatus
VTRAWProcessingSessionCompleteFrames( VTRAWProcessingSessionRef session ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);


/*!
	@function VTRAWProcessingSessionCopyProcessingParameters
	@abstract Copies an array of dictionaries describing the parameters provided by the RAW Processor for frame processing
	@discussion
		This will return an array of dictionaries, one dictionary for each parameter that can be controlled in the RAW Processing operation.
		The dictionary for each parameter will contain a set of kVTRAWProcessingParameter keys whose values provide a name, value type,
		value range, and current value for each parameter.
 
		The returned values can be used to contruct dynamic UI presenting RAW Processing controls allowing the various knobs for this
		specific RAW Processor to be viewed and manipulated.
	@param	session
		The RAW processing session.
	@param	outParameterArray
		Pointer for receiving the RAW Processing parameter array..
*/
VT_EXPORT OSStatus
VTRAWProcessingSessionCopyProcessingParameters(
	VTRAWProcessingSessionRef	session,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFArrayRef * CM_NONNULL 	outParameterArray ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // CFArray of CFDictionaries

/*!
	@function VTRAWProcessingSessionSetProcessingParameters
	@abstract Sets a collection of RAW Processing parameters
	@discussion
		This call will set a collection of RAW Processing parameters on the RAW Processor.  These are set as a dictionary where the keys match
		kVTRAWProcessingParameter_Key values that were returned in VTRAWProcessingSessionCopyProcessingParameters and where values conform
		to the type and range defined in the kVTRAWProcessingParameter dictionary for each parameter.
 
		Not all parameters from the RAWProcessingParameter array need to be set at any given time.  Changining the parameters will not change
		processing on frames already submitted for processing, it will only impact frames where VTRAWProcessingSessionProcessFrame is called
		after VTRAWProcessingSessionSetProcessingParameters returns.
 
		If any parameters specified are not in the array reported by VTRAWProcessingSessionCopyProcessingParameters, or are the wrong type or are out of range,
		kVTParameterErr will be returned and none of the parameters will be applied.
	@param	session
		The RAW processing session.
	@param	processingParameters
		A dictionary of keys and values setting parameters reported by VTRAWProcessingSessionCopyProcessingParameters.
	@result
		Returns an error if any of the provided parameters are invalid, disabled or outside of the declared valid range.
		None of the provided parameters will be set on the processor if an error is returned.
*/
VT_EXPORT OSStatus
VTRAWProcessingSessionSetProcessingParameters(
	VTRAWProcessingSessionRef	session,
	CFDictionaryRef				processingParameters ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);


#pragma mark RAW Processing Parameters
/*!
	@constant	kVTRAWProcessingParameter_Key
	@discussion
		The value corresponding to this key is the string used when specifying this parameter when calling VTRAWProcessingSessionSetProcessingParameters.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_Key CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_Name
	@discussion
		The value corresponding to this key is a localized string  which can be displayed in UI representing this parameter.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_Name CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_Description
	@discussion
		The value corresponding to this key is a localized string with a description of the parameter suitable for display in a tooltip or other descriptive UI.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_Description CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_Enabled
	@discussion
		The value corresponding to this key is Boolean indicating whether the parameter is enabled and can be modified.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_Enabled CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_ValueType
	@discussion
		The value corresponding to this key is the type of the parameter - a Boolean, Integer, Float, List, or SubGroup.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_ValueType CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
VT_EXPORT const CFStringRef kVTRAWProcessingParameterValueType_Boolean CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
VT_EXPORT const CFStringRef kVTRAWProcessingParameterValueType_Integer CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
VT_EXPORT const CFStringRef kVTRAWProcessingParameterValueType_Float CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
VT_EXPORT const CFStringRef kVTRAWProcessingParameterValueType_List CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
VT_EXPORT const CFStringRef kVTRAWProcessingParameterValueType_SubGroup CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_ListArray
	@discussion
		The value corresponding to this key is a CFArray of CFDictionaries describing each element in the list..
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_ListArray CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);  // CFArrayRef of CFDictionaries containing kVTRAWProcessingParameterListElement_ keys
VT_EXPORT const CFStringRef kVTRAWProcessingParameterListElement_Label CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);  // value is a CFString containing a human-readable label for the element, suitable for displaying in a list of options
VT_EXPORT const CFStringRef kVTRAWProcessingParameterListElement_Description CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);  // value is a CFString containing a human-readable description for the element, suitable for displaying in a tooltip or other descriptive UI
VT_EXPORT const CFStringRef kVTRAWProcessingParameterListElement_ListElementID CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // value is a CFNumber used as the value when setting a value for the List element in the processingParameters dictionary when calling VTRAWProcessingSessionSetProcessingParameters

/*!
	@constant	kVTRAWProcessingParameter_SubGroup
	@discussion
		The value corresponding to this key is a CFArray of CFDictionaries representing the individual sub-parameters in this group.  
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_SubGroup CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);  // CFArrayRef of CFDictionaries containing kVTRAWProcessingParameter keys


/*!
	@constant	kVTRAWProcessingParameter_MaximumValue
	@discussion
		The value corresponding to this key is the maximum value allowed for this parameter when calling VTRAWProcessingSessionSetProcessingParameters.
		This parameter is optional and not required for parameters where it is not appropriate (such as Boolean or List types).
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_MaximumValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_MinimumValue
	@discussion
		The value corresponding to this key is the minimum value allowed for this parameter when calling VTRAWProcessingSessionSetProcessingParameters.
		This parameter is optional and not required for parameters where it is not appropriate (such as Boolean or List types).
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_MinimumValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_InitialValue
	@discussion
		The value corresponding to this key is the initial value for this parameter as defined by the container and metadata provided at creation time.
		For List types, this is the ListElementID for the List element.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_InitialValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_NeutralValue
	@discussion
		The value corresponding to this key is a neutral setting for the processor.
		For List types, this is the ListElementID for the List element.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_NeutralValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_CameraValue
	@discussion
		The value corresponding to this key is the "As Shot" value for this parameter as originally captured by the camera.
		For List types, this is the ListElementID for the List element.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_CameraValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@constant	kVTRAWProcessingParameter_CurrentValue
	@discussion
		The value corresponding to this key is the currently configured value for this parameter.  For List types, this is the ListElementID for the List element.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingParameter_CurrentValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CM_ASSUME_NONNULL_END

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTRAWPROCESSINGSESSION_H
