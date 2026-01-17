/*
    File:  CMTaggedBufferGroup.h
	
	Framework:  CoreMedia
 
	Copyright © 2023-2025 Apple Inc. All rights reserved.
 
*/

#ifndef CMTAGGEDBUFFERGROUP_H
#define CMTAGGEDBUFFERGROUP_H

/*!
	@header
	@abstract	API for creating and manipulating CMTaggedBufferGroups.
	@discussion	CMTaggedBufferGroups are CF objects containing zero or more buffers, each with a corresponding CMTagCollection describing the buffers.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMTag.h>
#include <CoreMedia/CMTagCollection.h>
#include <CoreMedia/CMSampleBuffer.h>
#include <CoreVideo/CVPixelBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif
    
CM_ASSUME_NONNULL_BEGIN

#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

#pragma mark - Errors

/*!
	@enum		CMTaggedBufferGroup Errors
	@discussion The OSStatus errors returned from the CMTaggedBufferGroup routines.
	@constant	kCMTaggedBufferGroupError_ParamErr Returned when caller passes incorrect input or output parameters.
	@constant	kCMTaggedBufferGroupError_AllocationFailed Returned if a necessary allocation failed.
	@constant	kCMTaggedBufferGroupError_InternalError Returned if some kind of internal implementation error occurred.
*/
typedef CF_ENUM(OSStatus, CMTaggedBufferGroupError)
{
	kCMTaggedBufferGroupError_ParamErr = -15780,
	kCMTaggedBufferGroupError_AllocationFailed = -15781,
	kCMTaggedBufferGroupError_InternalError = -15782,
} CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@typedef	CMTaggedBufferGroup
	@abstract	An object gathering zero or more buffers (CMSampleBuffer, CVPixelBuffer) each with a CMTagCollection.
*/
typedef struct CM_BRIDGED_TYPE(id) OpaqueCMTaggedBufferGroup *CMTaggedBufferGroupRef CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

CM_EXPORT CFTypeID CMTaggedBufferGroupGetTypeID(void) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupCreate
	@abstract   Creates a new tagged buffer group.
	@param      allocator       The CFAllocator to use for allocating this buffer group.  May be NULL.
	@param      tagCollections  A CFArray of CMTagCollections for the buffers.
	@param      buffers         A CFArray of buffers, each of type CMSampleBuffer or CVPixelBuffer.  The group will retain these sample buffers and pixel buffers.
								The number of tagCollections must match the number of buffers.
	@param      groupOut        The newly created group will be placed here.  The caller has a responsibility to call CFRelease on it.
	@result     Returns noErr on success.
*/
CM_EXPORT OSStatus CMTaggedBufferGroupCreate(
	CFAllocatorRef CM_NULLABLE allocator,
	CFArrayRef CM_NONNULL tagCollections,
	CFArrayRef CM_NONNULL buffers,
	CM_RETURNS_RETAINED_PARAMETER CMTaggedBufferGroupRef CM_NULLABLE * CM_NONNULL groupOut ) CF_REFINED_FOR_SWIFT
	API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupCreateCombined
	@abstract   Creates a new tagged buffer group by combining all the tagged buffer groups in an array.
	@param      allocator       The CFAllocator to use for allocating this buffer group.  May be NULL.
	@param      taggedBufferGroups  A CFArray of CMTaggedBufferGroups.
	@param      groupOut        The newly created group will be placed here.  The caller has a responsibility to call CFRelease on it.
	@result     Returns noErr on success.
*/
CM_EXPORT OSStatus CMTaggedBufferGroupCreateCombined(
	CFAllocatorRef CM_NULLABLE allocator,
	CFArrayRef CM_NONNULL taggedBufferGroups,
	CM_RETURNS_RETAINED_PARAMETER CMTaggedBufferGroupRef CM_NULLABLE * CM_NONNULL groupOut ) CF_REFINED_FOR_SWIFT
	API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCount
	@abstract   Returns the number of buffers in a CMTaggedBufferGroup.
	@param      group  The CMTaggedBufferGroupRef to retrieve the count from.
	@result     Returns the number of buffers, or 0 on failure or if the group is empty.
*/
CM_EXPORT CMItemCount CMTaggedBufferGroupGetCount( CMTaggedBufferGroupRef CM_NONNULL group ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetTagCollectionAtIndex
	@abstract   Returns a CMTagCollection from a CMTaggedBufferGroup by sequential indexing.
	@param      group   The CMTaggedBufferGroupRef to retrieve the tag collection from.
	@param      index   An index from 0 to count-1.
	@result     Returns the tag collection, or NULL on failure.
*/
CM_EXPORT CMTagCollectionRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetTagCollectionAtIndex( CMTaggedBufferGroupRef CM_NONNULL group, CFIndex index ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCVPixelBufferAtIndex
	@abstract   Returns a CVPixelBuffer from a CMTaggedBufferGroup by sequential indexing.
	@param      group   The CMTaggedBufferGroupRef to retrieve the CVPixelBuffer from.
	@param      index   An index from 0 to count-1.
	@result     Returns the CVPixelBuffer, or NULL on failure (including if the buffer at this index is not a CVPixelBuffer).
*/
CM_EXPORT CVPixelBufferRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetCVPixelBufferAtIndex( CMTaggedBufferGroupRef CM_NONNULL group, CFIndex index ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCVPixelBufferForTag
	@abstract   Returns a CVPixelBuffer from a CMTaggedBufferGroup by looking for a unique match for the provided tag.
	@param      group   	The CMTaggedBufferGroupRef to retrieve the CVPixelBuffer from.
	@param      tag     	The tag to look up.  If more than one buffer's tag collection includes this tag, the lookup will fail.
	@param		indexOut 	On success, index of the returned CVPixelBuffer.  May be NULL.
	@result     Returns the CVPixelBuffer, or NULL on failure (including if the buffer at this index is not a CVPixelBuffer).
*/
CM_EXPORT CVPixelBufferRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetCVPixelBufferForTag( CMTaggedBufferGroupRef CM_NONNULL group, CMTag tag, CFIndex * CM_NULLABLE indexOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCVPixelBufferForTagCollection
	@abstract   Returns a CVPixelBuffer from a CMTaggedBufferGroup by looking for a unique match for the provided tag collection.
	@param      group           The CMTaggedBufferGroupRef to retrieve the CVPixelBuffer from.
	@param      tagCollection   The tag collection to look up.  If more than one buffer's tag collection includes this tag collection, the lookup will fail.
	@param		indexOut 		On success, index of the returned CVPixelBuffer.  May be NULL.
	@result     Returns the CVPixelBuffer, or NULL on failure (including if the buffer at this index is not a CVPixelBuffer).
*/
CM_EXPORT CVPixelBufferRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetCVPixelBufferForTagCollection( CMTaggedBufferGroupRef CM_NONNULL group, CMTagCollectionRef CM_NONNULL tagCollection, CFIndex * CM_NULLABLE indexOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCMSampleBufferAtIndex
	@abstract   Returns a CMSampleBuffer from a CMTaggedBufferGroup by sequential indexing.
	@param      group   The CMTaggedBufferGroupRef to retrieve the CMSampleBuffer from.
	@param      index   An index from 0 to count-1.
	@result     Returns the CMSampleBuffer, or NULL on failure (including if the buffer at this index is not a CMSampleBuffer).
*/
CM_EXPORT CMSampleBufferRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetCMSampleBufferAtIndex( CMTaggedBufferGroupRef CM_NONNULL group, CFIndex index ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCMSampleBufferForTag
	@abstract   Returns a CMSampleBuffer from a CMTaggedBufferGroup by looking for a unique match for the provided tag.
	@param      group   	The CMTaggedBufferGroupRef to retrieve the CMSampleBuffer from.
	@param      tag     	The tag to look up.  If more than one buffer's tag collection includes this tag, the lookup will fail.
	@param		indexOut 	On success, index of the returned CMSampleBuffer.  May be NULL.
	@result     Returns the CMSampleBuffer, or NULL on failure (including if the buffer at this index is not a CMSampleBuffer).
*/
CM_EXPORT CMSampleBufferRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetCMSampleBufferForTag( CMTaggedBufferGroupRef CM_NONNULL group, CMTag tag, CFIndex * CM_NULLABLE indexOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetCMSampleBufferForTagCollection
	@abstract   Returns a CMSampleBuffer from a CMTaggedBufferGroup by looking for a unique match for the provided tag collection.
	@param      group           The CMTaggedBufferGroupRef to retrieve the CMSampleBuffer from.
	@param      tagCollection   The tag collection to look up.  If more than one buffer's tag collection includes this tag collection, the lookup will fail.
	@param		indexOut 		On success, index of the returned CMSampleBuffer.  May be NULL.
	@result     Returns the CMSampleBuffer, or NULL on failure (including if the buffer at this index is not a CMSampleBuffer).
*/
CM_EXPORT CMSampleBufferRef CF_RETURNS_NOT_RETAINED CM_NULLABLE CMTaggedBufferGroupGetCMSampleBufferForTagCollection( CMTaggedBufferGroupRef CM_NONNULL group, CMTagCollectionRef CM_NONNULL tagCollection, CFIndex * CM_NULLABLE indexOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function   CMTaggedBufferGroupGetNumberOfMatchesForTagCollection
	@abstract   Returns the number of matches that a tag collection has in a CMTaggedBufferGroup.
	@discussion If the returned count is less than or greater than 1, buffer lookups using this tag collection will fail and return NULL, since the lookups must be unique and unambiguous.
	@param      group           The CMTaggedBufferGroupRef to examine.
	@param      tagCollection   The tag collection to look up.
	@result     Returns the number of entries in the CMTaggedBufferGroup that match tagCollection.
*/
CM_EXPORT CMItemCount CMTaggedBufferGroupGetNumberOfMatchesForTagCollection( CMTaggedBufferGroupRef CM_NONNULL group, CMTagCollectionRef CM_NONNULL tagCollection ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark Carriage in CMSampleBuffer

/*!
	@function	CMTaggedBufferGroupFormatDescriptionCreateForTaggedBufferGroup
	@abstract	Creates a format description for a CMTaggedBufferGroup.
 	@param	allocator
		CFAllocator to be used when creating the CMFormatDescription. Pass kCFAllocatorDefault to use the default allocator.
 	@param	taggedBufferGroup
		The tagged buffer group for which we are creating the format description.
 	@param	formatDescriptionOut
		Returned newly-created tagged buffer group CMFormatDescription
	@discussion
		The returned CMTaggedBufferGroupFormatDescription could be used to create a CMSampleBuffer
		wrapping the CMTaggedBufferGroup using CMSampleBufferCreateForTaggedBufferGroup.
		If you are going to call CMSampleBufferCreateForTaggedBufferGroup on a series of matching
		CMTaggedBufferGroups, it is more efficient to create the CMTaggedBufferGroupFormatDescription
		once and use it for all of the CMSampleBuffers.
		The caller owns the returned CMFormatDescription, and must release it when done with it.
*/
CM_EXPORT
OSStatus CMTaggedBufferGroupFormatDescriptionCreateForTaggedBufferGroup(
	CFAllocatorRef CM_NULLABLE allocator,
	CMTaggedBufferGroupRef CM_NONNULL taggedBufferGroup,
	CM_RETURNS_RETAINED_PARAMETER CMTaggedBufferGroupFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTaggedBufferGroupFormatDescriptionCreateForTaggedBufferGroupWithExtensions
	@abstract	Creates a format description for a CMTaggedBufferGroup with extensions.
	@param	allocator
		CFAllocator to be used when creating the CMFormatDescription. Pass kCFAllocatorDefault to use the default allocator.
	@param	taggedBufferGroup
		The tagged buffer group for which we are creating the format description.
	@param	extensions
		Dictionary of extension key/value pairs.  Keys are always CFStrings. Values are always property list objects (ie. CFData, CFString, CFArray, CFDictionary, CFDate, CFBoolean, or CFNumber). Can be NULL.
	@param	formatDescriptionOut
		Returned newly-created tagged buffer group CMFormatDescription
	@discussion
		The returned CMTaggedBufferGroupFormatDescription could be used to create a CMSampleBuffer
		wrapping the CMTaggedBufferGroup using CMSampleBufferCreateForTaggedBufferGroup.
		If you are going to call CMSampleBufferCreateForTaggedBufferGroup on a series of matching
		CMTaggedBufferGroups, it is more efficient to create the CMTaggedBufferGroupFormatDescription
		once and use it for all of the CMSampleBuffers.
		The caller owns the returned CMFormatDescription, and must release it when done with it.
		All input parameters are copied (the extensions are deep-copied).  The caller can deallocate them or re-use them after making this call.
*/
CM_EXPORT
OSStatus CMTaggedBufferGroupFormatDescriptionCreateForTaggedBufferGroupWithExtensions(
	CFAllocatorRef CM_NULLABLE allocator,
	CMTaggedBufferGroupRef CM_NONNULL taggedBufferGroup,
	CFDictionaryRef CM_NULLABLE extensions,
	CM_RETURNS_RETAINED_PARAMETER CMTaggedBufferGroupFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
/*!
	@function	CMTaggedBufferGroupFormatDescriptionMatchesTaggedBufferGroup
	@abstract	Checks to see if a given format description matches a tagged buffer group.
  	@param	desc
		The format description to validate.
  	@param	taggedBufferGroup
		The tagged buffer group to validate against.
	@discussion	
		Returns true if the CMTaggedBufferGroupFormatDescription could be used to create a 
		CMSampleBuffer wrapping the CMTaggedBufferGroup using CMSampleBufferCreateForTaggedBufferGroup.
*/
CM_EXPORT
Boolean CMTaggedBufferGroupFormatDescriptionMatchesTaggedBufferGroup(
	CMTaggedBufferGroupFormatDescriptionRef CM_NONNULL desc,
	CMTaggedBufferGroupRef CM_NONNULL taggedBufferGroup) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function    CMSampleBufferCreateForTaggedBufferGroup
	@abstract    Creates a new CMSampleBuffer object with the specified CMTaggedBufferGroup.
	@param	allocator
		CFAllocator with which to create the CMSampleBuffer object. Pass kCFAllocatorDefault to use the default allocator.
	@param	taggedBufferGroup
		The CMTaggedBufferGroup to be stored in the sample buffer. The CMSampleBuffer will retain the CMTaggedBufferGroup internally.
	@param	sbufPTS
		Media time PTS of the sample buffer.
	@param	sbufDuration
		Media time duration of the sample buffer. Can be kCMTimeInvalid if not known or not defined.
	@param	formatDescription
		A CMTaggedBufferGroupFormatDescription describing the CMTaggedBufferGroup.  
		You may create this with CMTaggedBufferGroupFormatDescriptionCreateForTaggedBufferGroup.
		If you are creating a lot of CMSampleBuffers containing matching CMTaggedBufferGroups, 
		it is more efficient to create the CMTaggedBufferGroupFormatDescription once and use it 
		for all of the CMSampleBuffers.  
		You may call CMTaggedBufferGroupFormatDescriptionMatchesTaggedBufferGroup to confirm that
		a reused CMTaggedBufferGroupFormatDescription matches a new CMTaggedBufferGroup.
	@param	sBufOut
		Returned newly created CMSampleBuffer.
	@result	OSStatus with error or noErr if successful.
 */
CM_EXPORT OSStatus CMSampleBufferCreateForTaggedBufferGroup(
	CFAllocatorRef CM_NULLABLE allocator,
	CMTaggedBufferGroupRef CM_NONNULL taggedBufferGroup,
	CMTime sbufPTS,
	CMTime sbufDuration,
	CMTaggedBufferGroupFormatDescriptionRef CM_NONNULL formatDescription,
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)
	CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function    CMSampleBufferGetTaggedBufferGroup
	@abstract    Returns a CMSampleBuffer's TaggedBufferGroup of media data.
	@param sbuf    CMSampleBuffer being interrogated.
	@discussion  The caller does not own the returned CMTaggedBufferGroup, and must retain it explicitly if the caller needs to maintain a reference to it.
	@result      CMTaggedBufferGroup of media data. The result will be NULL if the CMSampleBuffer does not contain a CMTaggedBufferGroup, or if there is some other error.
 */
CM_EXPORT CMTaggedBufferGroupRef CM_NULLABLE CMSampleBufferGetTaggedBufferGroup(CMSampleBufferRef CM_NONNULL sbuf) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
CM_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif
	
#endif // CMTAGGEDBUFFERGROUP_H
