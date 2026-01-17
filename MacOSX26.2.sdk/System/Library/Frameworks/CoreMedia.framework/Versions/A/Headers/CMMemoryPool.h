/*
	File:  CMMemoryPool.h
 
	Framework:  CoreMedia
 
	Copyright 2006-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMMEMORYPOOL_H
#define CMMEMORYPOOL_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMBase.h>

#ifdef __cplusplus
extern "C" {
#endif
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@header		CMMemoryPool.h
	@abstract	Memory pool for optimizing repeated large block allocation.
	@discussion
		CMMemoryPool is a memory allocation service that holds onto a pool of
		recently deallocated memory so as to speed up subsequent allocations of the same size.  
		It's intended for cases where large memory blocks need to be repeatedly allocated --
		for example, the compressed data output by a video encoder.
		
		All of its allocations are on the granularity of page sizes; it does not suballocate
		memory within pages, so it is a poor choice for allocating tiny blocks.
		For example, it's appropriate to use as the blockAllocator argument to
		CMBlockBufferCreateWithMemoryBlock, but not the structureAllocator argument --
		use kCFAllocatorDefault instead.

		When you no longer need to allocate memory from the pool, call CMMemoryPoolInvalidate
		and CFRelease.  Calling CMMemoryPoolInvalidate tells the pool to stop holding onto
		memory for reuse.  Note that the pool's CFAllocator can outlive the pool, owing
		to the way that CoreFoundation is designed: CFAllocators are themselves CF objects,
		and every object allocated with a CFAllocator implicitly retains the CFAllocator 
		until it is finalized.  After the CMMemoryPool is invalidated or finalized,
		its CFAllocator allocates and deallocates with no pooling behavior.
		
		CMMemoryPool deallocates memory if it has not been recycled in 0.5 second,
		so that short-term peak usage does not cause persistent bloat.
		(This period may be overridden by specifying kCMMemoryPoolOption_AgeOutPeriod.)
		Such "aging out" is done during the pool's CFAllocatorAllocate and
		CFAllocatorDeallocate methods.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMMemoryPool *CMMemoryPoolRef API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0)) CM_SWIFT_SENDABLE; // a CF type; use CFRetain and CFRelease.

/*!
	@enum CMMemoryPool Errors
	@discussion The errors returned from the CMMemoryPool APIs
	@constant	kCMMemoryPoolError_AllocationFailed Returned when allocation of an internal data structure fails.
	@constant	kCMMemoryPoolError_InvalidParameter Returned when an API parameter was NULL or otherwise invalid.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMMemoryPoolError_AllocationFailed		= -15490,
	kCMMemoryPoolError_InvalidParameter		= -15491,
} API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));

CM_EXPORT CFTypeID CMMemoryPoolGetTypeID(void)
						API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));

/*!
	@const		kCMMemoryPoolOption_AgeOutPeriod
	@abstract	Specifies how long memory should be allowed to hang out in the pool before being deallocated.
	@discussion	Pass this in the options dictionary to CMMemoryPoolCreate.
*/
CM_EXPORT const CFStringRef CM_NONNULL kCMMemoryPoolOption_AgeOutPeriod // CFNumber (seconds)
								API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));

/*!
	@function	CMMemoryPoolCreate
	@abstract	Creates a new CMMemoryPool.
*/
CM_EXPORT CMMemoryPoolRef CM_NONNULL CMMemoryPoolCreate( CFDictionaryRef CM_NULLABLE options ) // pass NULL for defaults
								API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));

/*!
	@function	CMMemoryPoolGetAllocator
	@abstract	Returns the pool's CFAllocator.
*/
CM_EXPORT CFAllocatorRef CM_NONNULL CMMemoryPoolGetAllocator( CMMemoryPoolRef CM_NONNULL pool )
								API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));

/*!
	@function	CMMemoryPoolFlush
	@abstract	Deallocates all memory the pool was holding for recycling.
*/
CM_EXPORT void CMMemoryPoolFlush( CMMemoryPoolRef CM_NONNULL pool )
					API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));

/*!
	@function	CMMemoryPoolInvalidate
	@abstract	Stops the pool from recycling.
	@discussion
		When CMMemoryPoolInvalidate is called the pool's allocator stops recycling memory.
		The pool deallocates any memory it was holding for recycling.
		This also happens when the retain count of the CMMemoryPool drops to zero, 
		except that under GC it may be delayed.
*/
CM_EXPORT void CMMemoryPoolInvalidate( CMMemoryPoolRef CM_NONNULL pool )
					API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0), visionos(1.0));
	
CF_IMPLICIT_BRIDGING_DISABLED

#ifdef __cplusplus
}
#endif

#endif // CMMEMORYPOOL_H
