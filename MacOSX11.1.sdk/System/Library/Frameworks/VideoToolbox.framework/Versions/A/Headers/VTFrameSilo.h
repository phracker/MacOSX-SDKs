/*
	File:  VTFrameSilo.h
	
	Framework:  VideoToolbox
	
	Copyright © 2012-2018 Apple Inc. All rights reserved.
	
	A VTFrameSilo stores a large number of sample buffers, as produced by a multi-pass compression session.
*/

#ifndef VTFRAMESILO_H
#define VTFRAMESILO_H

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTimeRange.h>
#include <CoreMedia/CMSampleBuffer.h>

#include <VideoToolbox/VTErrors.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    

CF_IMPLICIT_BRIDGING_ENABLED
/*!
	@typedef	VTFrameSilo
	@abstract	A VTFrameSilo stores a large number of sample buffers, as produced by a multi-pass compression session.
	@discussion
		The sample buffers are ordered by decode timestamp. 
		A VTFrameSilo starts out empty and is populated by calls to VTFrameSiloAddSampleBuffer to add sample buffers in ascending decode order.
		After the first full pass, additional passes may be performed to replace sample buffers.
		Each such pass must begin with a call to VTFrameSiloSetTimeRangesForNextPass, which takes a list of time ranges.
		Samples in these time ranges are deleted, and calls to VTFrameSiloAddSampleBuffer can then be made to provide replacements.
		Call VTFrameSiloCallFunctionForEachSampleBuffer or VTFrameSiloCallBlockForEachSampleBuffer to retrieve sample buffers.
		The VTFrameSilo may write sample buffers and data to the backing file between addition and retrieval; 
		do not expect to get identical object pointers back.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueVTFrameSilo *VTFrameSiloRef; // a CF type, call CFRetain and CFRelease

VT_EXPORT CFTypeID VTFrameSiloGetTypeID(void) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));

CF_IMPLICIT_BRIDGING_DISABLED
/*!
	@function	VTFrameSiloCreate
	@abstract	Creates a VTFrameSilo object using a temporary file.
	@discussion
		The returned VTFrameSilo object may be used to gather frames produced by multi-pass encoding.
	@param fileURL
		Specifies where to put the backing file for the VTFrameSilo object.
		If you pass NULL for fileURL, the video toolbox will pick a unique temporary file name.
	@param options
		Reserved, pass NULL.
	@param timeRange
		The valid time range for the frame silo. Must be valid for progress reporting.
	@param frameSiloOut
		Points to a VTFrameSiloRef to receive the newly created object.
		Call CFRelease to release your retain on the created VTFrameSilo object when you are done with it.
*/
VT_EXPORT OSStatus
VTFrameSiloCreate( 
	CM_NULLABLE CFAllocatorRef				allocator,
	CM_NULLABLE CFURLRef					fileURL,
	CMTimeRange								timeRange, /* can be kCMTimeRangeInvalid */
	CM_NULLABLE CFDictionaryRef				options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTFrameSiloRef * CM_NONNULL frameSiloOut ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	VTFrameSiloAddSampleBuffer
	@abstract	Adds a sample buffer to a VTFrameSilo object.
	@discussion
		Within each pass, sample buffers must have strictly increasing decode timestamps.
		Passes after the first pass are begun with a call to VTFrameSiloSetTimeRangesForNextPass.
		After a call to VTFrameSiloSetTimeRangesForNextPass, sample buffer decode timestamps must also be within 
		the stated time ranges.
		Note that CMTimeRanges are considered to contain their start times but not their end times.
	@return
		Returns kVTFrameSiloInvalidTimeStampErr if an attempt is made to add a sample buffer with an inappropriate decode timestamp.
*/
VT_EXPORT OSStatus
VTFrameSiloAddSampleBuffer( 
	CM_NONNULL VTFrameSiloRef			silo,
	CM_NONNULL CMSampleBufferRef		sampleBuffer ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));

/*!
	@function	VTFrameSiloSetTimeRangesForNextPass
	@abstract	Begins a new pass of samples to be added to a VTFrameSilo object.
	@discussion
		Previously-added sample buffers with decode timestamps within the time ranges will be deleted from the VTFrameSilo.
		It is not necessary to call VTFrameSiloSetTimeRangesForNextPass before adding the first pass' sample buffers.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
*/
VT_EXPORT OSStatus
VTFrameSiloSetTimeRangesForNextPass( 
	CM_NONNULL VTFrameSiloRef		silo,
	CMItemCount						timeRangeCount,
	const CMTimeRange * CM_NONNULL	timeRangeArray ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));

/*!
	@function	VTFrameSiloGetProgressOfCurrentPass
	@abstract	Gets the progress of the current pass.
	@discussion
		Calculates the current progress based on the most recent sample buffer added and the current pass time ranges.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
*/
VT_EXPORT OSStatus
VTFrameSiloGetProgressOfCurrentPass(
	CM_NONNULL VTFrameSiloRef	silo,
	Float32 * CM_NONNULL		progressOut ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));

/*!
	@function	VTFrameSiloCallFunctionForEachSampleBuffer
	@abstract	Retrieves sample buffers from a VTFrameSilo object.
	@discussion
		You call this function to retrieve sample buffers at the end of a multi-pass compression session.
	@param timeRange
		The decode time range of sample buffers to retrieve.
		Pass kCMTimeRangeInvalid to retrieve all sample buffers from the VTFrameSilo.
	@param callback
		A function to be called, in decode order, with each sample buffer that was added.
		To abort iteration early, return a nonzero status.
		The VTFrameSilo may write sample buffers and data to the backing file between addition and retrieval; 
		do not expect to get identical object pointers back.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
		Returns any nonzero status returned by the callback function.
*/
VT_EXPORT OSStatus
VTFrameSiloCallFunctionForEachSampleBuffer( 
	CM_NONNULL VTFrameSiloRef	silo,
	CMTimeRange					timeRange,
	void * CM_NULLABLE			refcon,
	OSStatus	(* CM_NONNULL CF_NOESCAPE callback)( void * CM_NULLABLE refcon, CM_NONNULL CMSampleBufferRef sampleBuffer ) ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2)); // return nonzero to abort iteration

#if __BLOCKS__
/*!
	@function	VTFrameSiloCallBlockForEachSampleBuffer
	@abstract	Retrieves sample buffers from a VTFrameSilo object.
	@discussion
		You call this function to retrieve sample buffers at the end of a multi-pass compression session.
	@param timeRange
		The decode time range of sample buffers to retrieve.
		Pass kCMTimeRangeInvalid to retrieve all sample buffers from the VTFrameSilo.
	@param handler
		A block to be called, in decode order, with each sample buffer that was added.
		To abort iteration early, return a nonzero status.
		The VTFrameSilo may write sample buffers and data to the backing file between addition and retrieval; 
		do not expect to get identical object pointers back.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
		Returns any nonzero status returned by the handler block.
*/
VT_EXPORT OSStatus
VTFrameSiloCallBlockForEachSampleBuffer( 
	CM_NONNULL VTFrameSiloRef			silo,
	CMTimeRange							timeRange,
	OSStatus (^ CM_NONNULL CF_NOESCAPE handler)( CM_NONNULL CMSampleBufferRef sampleBuffer ) ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2)); // return nonzero to abort iteration
#endif // __BLOCKS__

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTFRAMESILO_H
