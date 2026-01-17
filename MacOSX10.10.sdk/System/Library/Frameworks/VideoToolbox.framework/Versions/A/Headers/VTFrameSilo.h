/*
	File:  VTFrameSilo.h
	
	Framework:  VideoToolbox
	
	Copyright 2012-2013 Apple Inc. All rights reserved.
	
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

typedef struct OpaqueVTFrameSilo *VTFrameSiloRef; // a CF type, call CFRetain and CFRelease

VT_EXPORT CFTypeID VTFrameSiloGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

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
	@param siloOut
		Points to a VTFrameSiloRef to receive the newly created object.
		Call CFRelease to release your retain on the created VTFrameSilo object when you are done with it.
*/
VT_EXPORT OSStatus
VTFrameSiloCreate( 
	CFAllocatorRef			allocator,                 /* can be NULL */
	CFURLRef				fileURL,                   /* can be NULL */
	CMTimeRange				timeRange,				   /* can be kCMTimeRangeInvalid */
	CFDictionaryRef			options,                   /* can be NULL */
	VTFrameSiloRef			*siloOut ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

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
	VTFrameSiloRef			silo,
	CMSampleBufferRef		sampleBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

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
	VTFrameSiloRef			silo,
	CMItemCount				timeRangeCount,
	const CMTimeRange *		timeRangeArray ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

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
	VTFrameSiloRef			silo,
	Float32					*progressOut ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

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
	VTFrameSiloRef			silo,
	CMTimeRange				timeRange,
	void *					callbackInfo,
	OSStatus 				(*callback)( void *callbackInfo, CMSampleBufferRef sampleBuffer ) ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // return nonzero to abort iteration

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
	VTFrameSiloRef			silo,
	CMTimeRange				timeRange,
	OSStatus 				(^handler)( CMSampleBufferRef sampleBuffer ) ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // return nonzero to abort iteration
#endif // __BLOCKS__

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTFRAMESILO_H
