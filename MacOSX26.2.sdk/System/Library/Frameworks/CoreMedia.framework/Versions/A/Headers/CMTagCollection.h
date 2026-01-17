/*
    File:  CMTagCollection.h
	
	Framework:  CoreMedia
 
	Copyright © 2023 Apple Inc. All rights reserved.
 
*/

#ifndef CMTAGCOLLECTION_H
#define CMTAGCOLLECTION_H

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMTag.h>

#ifdef __cplusplus
extern "C" {
#endif

CF_IMPLICIT_BRIDGING_ENABLED

CM_ASSUME_NONNULL_BEGIN

#pragma pack(push)
#pragma pack()

#pragma mark - Errors

/*!
	@enum		CMTagCollection Errors
	@discussion The OSStatus errors returned from the CMTagCollection routines.
	@constant	kCMTagCollectionError_ParamErr Returned when caller passes incorrect input or output parameters.
	@constant	kCMTagCollectionError_AllocationFailed Returned if a necessary allocation failed.
	@constant	kCMTagCollectionError_InternalError Returned if some kind of internal implementation error occurred.
	@constant	kCMTagCollectionError_InvalidTag Returned if the tag is kCMTagInvalid.
	@constant	kCMTagCollectionError_InvalidTagCollectionDictionary Returned if the CFDictionary being deserialized is not valid to create a CMTagCollection.
	@constant	kCMTagCollectionError_InvalidTagCollectionData Returned if structure of the CFData being deserialized is not valid to create a CMTagCollection.
	@constant	kCMTagCollectionError_TagNotFound Returned if a search for a CMTag in the collection failed, including if the collection is empty.
	@constant	kCMTagCollectionError_InvalidTagCollectionDataVersion Returned if the CFData deserialized to create a CMTagCollection has an unknown version.
	@constant	kCMTagCollectionError_ExhaustedBufferSize Returned if the buffer size to retrieve CMTags is smaller than necessary.
	@constant	kCMTagCollectionError_NotYetImplemented Returned if the function is not yet implemented.
*/
typedef CF_ENUM(OSStatus, CMTagCollectionError)
{
	kCMTagCollectionError_ParamErr 							= -15740,
	kCMTagCollectionError_AllocationFailed 					= -15741,
	kCMTagCollectionError_InternalError 					= -15742,
	kCMTagCollectionError_InvalidTag						= -15743,
	kCMTagCollectionError_InvalidTagCollectionDictionary	= -15744,
	kCMTagCollectionError_InvalidTagCollectionData			= -15745,
	kCMTagCollectionError_TagNotFound						= -15746,
	kCMTagCollectionError_InvalidTagCollectionDataVersion 	= -15747,
	kCMTagCollectionError_ExhaustedBufferSize 				= -15748,
	kCMTagCollectionError_NotYetImplemented					= -15749
} CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTagCollectionRef

/*!
	@typedef CMTagCollectionRef
	@discussion	A reference to a CMTagCollection, a CF object that adheres to retain/release semantics. This value type represents an unordered collection of zero or more CMTags. This type is roughly analogous to CFSetRef in that it is unordered and has operations for Boolean set math. It is however optimized for the storage of CMTag structures.
*/
typedef const struct CM_BRIDGED_TYPE(id) OpaqueCMTagCollection * CMTagCollectionRef CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMTagCollection * CMMutableTagCollectionRef CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionGetTypeID
	@abstract	Obtains the CoreFoundation type ID for the CMTagCollection type.
	@discussion	Obtains the CoreFoundation type ID for the CMTagCollection type.
	@result	Returns the CFTypeID corresponding to CMTagCollection.
*/
CM_EXPORT CFTypeID CMTagCollectionGetTypeID(void) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Tag collection related struct constants

/*!
	@typedef CMTagCollectionApplierFunction
	@discussion A callback function that can be used to iterate over a CMTagCollection. The callback is passed a CMTag and a potentially NULL context reference that can be used to implement some operation for each tag.
	@param tag The CMTag to evaluate.
	@param context A valid pointer or NULL used by the callback implementation.
*/
typedef void (*CMTagCollectionApplierFunction)(CMTag tag, void * CM_NULLABLE context) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@typedef CMTagCollectionTagFilterFunction
	@discussion A callback function that can be used to implement a filtering operation during iteration over a CMTagCollection. For each CMTag that satisfies the predicate, the callback should return true. Otherwise, it should return false.  The callback is passed a CMTag and a potentially NULL context reference that can be used to implement some operation for each tag.
	@param tag The CMTag to evaluate.
	@param context A valid pointer or NULL used by the callback implementation.
	@result A Boolean indicating if the tag passed the callback test.
*/
typedef Boolean (*CMTagCollectionTagFilterFunction)(CMTag tag, void * CM_NULLABLE context) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Tag collection creation

/*!
	@function	CMTagCollectionCreate
	@abstract   Creates a CMTagCollectionRef described by a number of parameters.
	@discussion This can be used to construct a CMTagCollectionRef from zero or more CMTags.
	@param allocator	CFAllocator to use to create the collection and internal data structures.
	@param tags			Zero or more CMTag structs to copy into the collection. May pass NULL if tagCount is also zero (0).
	@param tagCount		Number of tags in the 'tags' array.
	@param newCollectionOut		Address of a location to return the newly created CMTagCollectionRef.  The client is responsible for releasing the returned CMTagCollection.
	@result     OSStatus with error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionCreate( CFAllocatorRef CM_NULLABLE allocator,
				const CMTag * CM_NULLABLE tags,
				CMItemCount tagCount,
				CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL newCollectionOut ) CF_REFINED_FOR_SWIFT
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionCreateMutable
	@abstract   Creates a CMMutableTagCollectionRef.
	@discussion This can be used to construct a mutable CMTagCollectionRef with a capacity limit or without a capacity limit. A capacity greater than zero indicates a maximum number of CMTags the collection can contain. The actual number of tags may be less than this value depending upon how many tags have been added to the collection.
	If capacity is 0, the mutable collection can contain any number of tags.
	@param allocator	CFAllocator to use to create the collection and internal data structures.
	@param capacity		Capacity limit set to zero to indicate no limit or a value greater than zero for a limit.
	@param newMutableCollectionOut	Address of a location to return the newly created CMMutabbleTagCollectionRef.  The client is responsible for releasing the returned CMMutableTagCollection.
	@result     OSStatus with error, or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionCreateMutable( CFAllocatorRef CM_NULLABLE allocator,
				CFIndex capacity,
				CM_RETURNS_RETAINED_PARAMETER CMMutableTagCollectionRef CM_NULLABLE * CM_NONNULL newMutableCollectionOut ) CF_REFINED_FOR_SWIFT
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));
/*!
	@function	CMTagCollectionCreateCopy
	@abstract   Creates a duplicate CMTagCollectionRef.
	@discussion This can be used to construct a CMTagCollectionRef that contains all the same tags as another collection.
	@param tagCollection	CMTagCollectionRef used to create the copy.
	@param allocator	CFAllocator used to create the copy.
	@param newCollectionCopyOut		Address of a location to return the newly created CMTagCollectionRef.  The client is responsible for releasing the returned CMTagCollection.
	@result     OSStatus with error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionCreateCopy( CMTagCollectionRef CM_NONNULL tagCollection,
				CFAllocatorRef CM_NULLABLE allocator,
				CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL newCollectionCopyOut ) CF_REFINED_FOR_SWIFT
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionCreateMutableCopy
	@abstract   Creates a duplicate mutable CMTagCollectionRef.
	@discussion This can be used to construct a CMMutableTagCollectionRef that contains all the same tags as another collection.
	@param tagCollection CMTagCollectionRef used to create the copy.
	@param allocator CFAllocator used to create the copy.
	@param newMutableCollectionCopyOut Address of a location to return the newly created CMMutableTagCollectionRef.  The client is responsible for releasing the returned CMMutableTagCollection.
	@result     OSStatus with error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionCreateMutableCopy( CMTagCollectionRef CM_NONNULL tagCollection,
				CFAllocatorRef CM_NULLABLE allocator,
				CM_RETURNS_RETAINED_PARAMETER CMMutableTagCollectionRef CM_NULLABLE * CM_NONNULL newMutableCollectionCopyOut ) CF_REFINED_FOR_SWIFT
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Tag collection accessors

/*!
	@function	CMTagCollectionCopyDescription
	@abstract   Creates a CFString with a description of a CMTagCollection.
	@discussion This can be used from within CFShow on a CMTagCollection object. It is also useful from other client debugging code.  The caller owns the returned CFString, and is responsible for releasing it.  Descriptions are not localized so are likely suitable only for debugging.
	@param allocator CFAllocator to use in creating the description string.
	@param tagCollection CMTagCollectionRef to describe.
	@result		The created CFString description.
*/
CM_EXPORT CM_RETURNS_RETAINED CFStringRef CM_NULLABLE CMTagCollectionCopyDescription(
			CFAllocatorRef CM_NULLABLE allocator,
			CMTagCollectionRef CM_NULLABLE tagCollection) CF_REFINED_FOR_SWIFT
			API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionGetCount
	@abstract   Returns the number of CMTags held in the CMTagCollectionRef.
	@param tagCollection	CMTagCollectionRef to evaluate for the tag count.
	@result     CMItemCount holding the count.
*/
CM_EXPORT CMItemCount CMTagCollectionGetCount( CMTagCollectionRef CM_NONNULL tagCollection ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionContainsTag
	@abstract	Checks if the tag collection contains a specific tag.
	@param tagCollection	CMTagCollection to check.
	@param tag	CMTag to find.
	@result     Returns true if the indicated CMTag is contained within the CMTagCollection, false otherwise.
*/
CM_EXPORT Boolean CMTagCollectionContainsTag( CMTagCollectionRef CM_NONNULL tagCollection, CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionContainsTagsOfCollection
	@abstract	Checks if all the tags in a tag collection are present in another tag collection.
	@discussion Tests if a collection of tags specified by a CMTagCollection are contained within another tag collection in its entirety. Partial containment will report false. Complete containment will report true.
	@param tagCollection	CMTagCollectionRef used to check.
	@param containedTagCollection	CMTagCollectionRef whose contents should be checked for containment in tagCollection.
	@result     Returns true if all CMTags in a collection are contained within the specified CMTagCollection, false otherwise.
*/
CM_EXPORT Boolean CMTagCollectionContainsTagsOfCollection( CMTagCollectionRef CM_NONNULL tagCollection,
					CMTagCollectionRef CM_NONNULL containedTagCollection ) CF_REFINED_FOR_SWIFT
					API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionContainsSpecifiedTags
	@abstract	Checks if all the specified tags are contained in a tag collection.
	@discussion Tests if the tags specified by a buffer of CMTags are contained within another tag collection in its entirety. Partial containment will report false. Complete containment will report true.
	@param tagCollection	CMTagCollectionRef to check.
	@param containedTags	The non-NULL address to a CMTag array whose CMTags should be checked for containment in tagCollection.
	@param containedTagCount	The number of CMTag elements in the buffer containedTags. Zero is allowed but will report true.
	@result     Returns true if all CMTags in a buffer of CMTags are contained within the CMTagCollection, false otherwise.
*/
CM_EXPORT Boolean CMTagCollectionContainsSpecifiedTags( CMTagCollectionRef CM_NONNULL tagCollection,
					const CMTag * CM_NONNULL containedTags, CMItemCount containedTagCount ) CF_REFINED_FOR_SWIFT
					API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionContainsCategory
	@abstract   Tests if a CMTagCategory is used by any CMTags within the tag container.
	@param tagCollection	CMTagCollectionRef to check.
	@param category	CMTagCategory whose value should be checked for containment in tagCollection.
	@result     Returns true if tagCollection contains at least one CMTag with the specified category, false otherwise.
*/
CM_EXPORT Boolean CMTagCollectionContainsCategory( CMTagCollectionRef CM_NONNULL tagCollection, CMTagCategory category ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionGetCountOfCategory
 @abstract Counts an returns the number of tags in the tag collection matching the specified category.
 @discussion Returns the count of tags having the specified category. It will return 0 if there are no tags.
 @param tagCollection	CMTagCollectionRef to evaluate.
 @param category CMTagCategory to check for.
 @result Returns the count of tags having the specified category.
*/
CM_EXPORT CMItemCount CMTagCollectionGetCountOfCategory( CMTagCollectionRef CM_NONNULL tagCollection, CMTagCategory category ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionGetTags
 @abstract Retrieve all CMTags and copy into a supplied buffer.
 @discussion The function retrieves a specified number of CMTags from the CMTagCollectionRef and copies them to a supplied buffer. The routine populates a provided sized buffer with each CMTag in the collection. If the provided buffer is smaller than needed to retrieve all tags, the routine will fill the buffer, return the number actually copied and return kCMTagCollectionError_ExhaustedBufferSize. If the provided buffer is larger than the number of CMTags in the collection to retrieve, the routine will fill the buffer with the number of available CMTags, return the number copied and fill the remainder of the buffer with kCMTagInvalid while returning noErr.
 @param tagCollection CMTagCollectionRef to iterate.
 @param tagBuffer A non-NULL address of a buffer to fill with CMTags with CMTagCategory 'category'.
 @param tagBufferCount The number of CMTags the buffer 'tagBuffer' can hold.
 @param numberOfTagsCopied The address of a CMItemCount that is filled with the number of tags retrieved, may be NULL.
 @result OSStatus with an error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionGetTags( CMTagCollectionRef CM_NONNULL tagCollection, CMTag * CM_NONNULL tagBuffer, CMItemCount tagBufferCount, CMItemCount * CM_NULLABLE numberOfTagsCopied ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionGetTagsWithCategory
 @abstract Retrieve CMTags having a specified CMTagCategory and copy to a supplied buffer.
 @discussion Populates a provided buffer with each CMTag in the collection that has the specified CMTagCategory. If the provided buffer is smaller than needed, the routine will fill the buffer, return the number of CMTags actually copied and return kCMTagCollectionError_ExhaustedBufferSize. If the provided buffer is larger than needed, it will fill the buffer with the number of available CMTags, return the number copied and fill the remainder of the buffer with kCMTagInvalid.
 @param tagCollection CMTagCollectionRef to iterate.
 @param category CMTagCategory to match.
 @param tagBuffer A non-NULL address of a buffer to fill with CMTags with CMTagCategory 'category'.
 @param tagBufferCount The number of CMTags the buffer 'tagBuffer' can hold.
 @param numberOfTagsCopied The address of a CMItemCount that is filled with the number of tags retrieved, may be NULL.
 @result OSStatus with an error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionGetTagsWithCategory( CMTagCollectionRef CM_NONNULL tagCollection, CMTagCategory category, CMTag * CM_NONNULL tagBuffer, CMItemCount tagBufferCount, CMItemCount * CM_NULLABLE numberOfTagsCopied ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionCountTagsWithFilterFunction
 @abstract Count the number of tags satisfying a callback.
 @discussion Iterates over the CMTags of the tag collection calling the supplied callback and incrementing a counter for each tag satisfying the callback. Returns this counter value upon completing iteration.
 @param tagCollection CMTagCollectionRef to iterate.
 @param filterApplier The CMTagCollectionTagFilterFunction callback to call with each tag.
 @param context A void * or NULL to pass to applier.
 @result CMItemCount indicating the number of CMTags satisfying 'filterApplier'.
*/
CM_EXPORT CMItemCount CMTagCollectionCountTagsWithFilterFunction( CMTagCollectionRef CM_NONNULL tagCollection, CMTagCollectionTagFilterFunction CM_NONNULL filterApplier, void * CM_NULLABLE context ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionGetTagsWithFilterFunction
 @abstract Retrieve CMTags satisfying a callback function and copy them to a supplied buffer.
 @discussion Applies a CMTagCollectionTagFilterFunction predicate and populates a provided buffer with each CMTag that for each tag when the filter returns true.  If the provided buffer is smaller than the number of tags the predicate satisfies, the routine will fill the buffer, return the copy CMTags actually copied and return kCMTagCollectionError_ExhaustedBufferSize. If the provided buffer is larger than needed, it will fill the buffer with the number of available CMTags, fill the remainder of the buffer with kCMTagInvalid and return a result of noErr.
 @param tagCollection CMTagCollectionRef to iterate.
 @param tagBuffer A non-NULL address of a buffer to fill with CMTags with CMTagCategory 'category'.
 @param tagBufferCount The number of CMTags the buffer 'tagBuffer' can hold.
 @param numberOfTagsCopied The address of a CMItemCount that is filled with the number of tags retrieved, may be NULL.
 @param filter The CMTagCollectionTagFilterFunction callback to call with each tag.
 @param context A void * or NULL to pass to filter.
 @result OSStatus with an error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionGetTagsWithFilterFunction( CMTagCollectionRef CM_NONNULL tagCollection, CMTag * CM_NONNULL tagBuffer, CMItemCount tagBufferCount, CMItemCount * CM_NULLABLE numberOfTagsCopied, CMTagCollectionTagFilterFunction CM_NONNULL filter, void * CM_NULLABLE context ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionCopyTagsOfCategories
 @abstract Copies all tags belonging to a specified list of CMTagCategory from one tag collection to a newly created tag collection.
 @discussion This routine copies all tags belonging to a specified list of CMTagCategory from one tag collection to a newly created tag collection.
 @param allocator CFAllocatorRef to use in allocations of the operation.
 @param tagCollection CMTagCollectionRef from which to copy tags.
 @param categories A non-NULL address of a buffer containing a list of CMTagCategory.
 @param categoriesCount The number of CMTagCategory the buffer 'categories' is holding.
 @param collectionWithTagsOfCategories The address of a CMTagCollectionRef that contains all tags copied from 'tagCollection'.  The client is responsible for releasing the returned CMTagCollection.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionCopyTagsOfCategories(
				CFAllocatorRef CM_NULLABLE allocator,
				CMTagCollectionRef CM_NONNULL tagCollection,
				const CMTagCategory * CM_NONNULL categories,
				CMItemCount categoriesCount,
				CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL collectionWithTagsOfCategories ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Tag collection iteration

/*!
 @function CMTagCollectionApply
 @abstract Iterate over a tag collection calling the provided callback.
 @discussion Iterates over the CMTags of the tag collection executing the callback with each tag.
 @param tagCollection CMTagCollectionRef to iterate.
 @param applier The CMTagCollectionApplierFunction callback to call with each tag.
 @param context A void * or NULL to pass to applier.
*/
CM_EXPORT void CMTagCollectionApply( CMTagCollectionRef CM_NONNULL tagCollection,
				CMTagCollectionApplierFunction CM_NONNULL applier,
				void * CM_NULLABLE context ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionApplyUntil
 @abstract Iterate over a tag collection until the callback is satisfied.
 @discussion Function iterates over the CMTags of the tag collection until the function returns true and then returns the CMTag at that position. Once the callback is satisfied by returning true, CMTagCollectionApplyUntil() stops iteration and returns the CMTag that evaluated to true. If no CMTags satisfy the callback, the value kCMTagInvalid will be returned.
 @param tagCollection CMTagCollectionRef to iterate.
 @param applier The CMTagCollectionTagFilterFunction callback to call with each tag.
 @param context A void * or NULL to pass to applier.
 @result CMTag having the value of the first tag the callback returned true for or kCMTagInvalid if none was found.
*/
CM_EXPORT CMTag CMTagCollectionApplyUntil( CMTagCollectionRef CM_NONNULL tagCollection,
				CMTagCollectionTagFilterFunction CM_NONNULL applier,
				void * CM_NULLABLE context ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Tag collection set like operations

/*!
 @function CMTagCollectionIsEmpty
 @abstract Reports if the tag collection contains no tags.
 @discussion This is a convenience name for set like use but is the same as the expression: CMTagCollectionIsEmptyGetCount() == 0.
 @param tagCollection CMTagCollectionRef to iterate.
 @result True if there are no tags, false otherwise.
*/
CM_EXPORT Boolean CMTagCollectionIsEmpty( CMTagCollectionRef CM_NONNULL tagCollection ) CF_SWIFT_UNAVAILABLE("Use isEmpty") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionCreateIntersection
 @abstract Calculates the intersection of two tag collections to produce a new tag collection.
 @discussion This routine creates an intersection of two tag collection by finding common tags among two source tag collections and produces a new tag collection containing those common tags.
 @param tagCollection1 CMTagCollectionRef to use in the intersection operation.
 @param tagCollection2 CMTagCollectionRef to use in the intersection operation.
 @param tagCollectionOut The address of a CMTagCollectionRef that contains all tags that are common to 'tagCollection1' and 'tagCollection2'.  The client is responsible for releasing the returned CMTagCollection.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionCreateIntersection(
			CMTagCollectionRef CM_NULLABLE tagCollection1,
			CMTagCollectionRef CM_NULLABLE tagCollection2,
			CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL tagCollectionOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
			API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionCreateUnion
 @abstract Calculates the union of two tag collections to produce a new tag collection.
 @discussion This routine creates an union of two tag collection by adding all tags from two tag collections and produces a new tag collection containing all the tags. Duplicate tags will not be added twice.  Note that if no tags are common among the source tag collections, the new tag collection will contain as many tags as the sum of the number of tags in each source tag collection. If two source tag collections contain the same tags, the resulting tag collection will have the same number of tags as each source tag collection.
 @param tagCollection1 CMTagCollectionRef to use in the union operation.
 @param tagCollection2 CMTagCollectionRef to use in the union operation.
 @param tagCollectionOut The address of a CMTagCollectionRef that contains all tags that are common to 'tagCollection1' and 'tagCollection2'.  The client is responsible for releasing the returned CMTagCollection.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionCreateUnion(
			CMTagCollectionRef CM_NULLABLE tagCollection1,
			CMTagCollectionRef CM_NULLABLE tagCollection2,
			CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL tagCollectionOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
			API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionCreateDifference
 @abstract Calculates the difference of two tag collections to produce a new tag collection.
 @discussion This routine creates the difference by considering a first source tag collection and removing all tags found in the first tag collection to produce a new tag collection containing only the tags not in the second tag collection.  Note that if the second tag collection has no tags found in the first tag collection, the produced tag collection will have the same tags as the first tag collection. If the second tag collection is empty, the produced tag collection will also have the same tags as the first tag collection.  If the second tag collection contains all the tags found in the source tag collection, the produced tag collection will be empty.  The order of parameters is important. Given two tag collections 'A' and 'B', the calculaton of 'A' - 'B' is not the same as 'B' - 'A'.
 @param tagCollectionMinuend CMTagCollectionRef from which to remove tags.
 @param tagCollectionSubtrahend CMTagCollectionRef to consult to determine tags to remove from 'tagCollectionMinuend'.
 @param tagCollectionOut The address of a CMTagCollectionRef that contains tags from a first tag collection without tags found in a second tag collection.  The client is responsible for releasing the returned CMTagCollection.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT
OSStatus CMTagCollectionCreateDifference(
			CMTagCollectionRef CM_NULLABLE tagCollectionMinuend,
			CMTagCollectionRef CM_NULLABLE tagCollectionSubtrahend,
			CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL tagCollectionOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
			API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionCreateExclusiveOr
 @abstract Calculates the exclusive OR of two tag collections to produce a new tag collection.
 @discussion This routine determines tags that are in only one of two source tag collections and adds only those to produce a new tag collection. If both source tag collections have no tags in common, the produced tag collection will contain a union of both source tag collections. If both source tag collections have the same tags, the produced tag collection will be empty.
 @param tagCollection1 CMTagCollectionRef to use in the xor operation.
 @param tagCollection2 CMTagCollectionRef to use in the xor operation.
 @param tagCollectionOut The address of a CMTagCollectionRef that contains the xor of the tags from the two tag collections.  The client is responsible for releasing the returned CMTagCollection.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionCreateExclusiveOr(
			CMTagCollectionRef CM_NULLABLE tagCollection1,
			CMTagCollectionRef CM_NULLABLE tagCollection2,
			CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL tagCollectionOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
			API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMMutableTagCollection routines

/*!
 @function CMTagCollectionAddTag
 @abstract Adds a tag to a mutable tag collection guaranteeing it is only added once.
 @discussion This routine adds a CMTag to a CMMutableTagCollection. If the CMTag already exists in the tag collection, the tag is not added again. If the tag doesn't exist in the tag collection, the tag collection is updated to contain the tag. Note that there is no ordering for tags within a tag collection.
 @param tagCollection CMMutableTagCollectionRef to which to add a tag.
 @param tagToAdd A CMTag to add to the tag collection.
 @result OSStatus indicating if the operation succeeded.  Returns noErr if the tag was already in the collection.
*/
CM_EXPORT OSStatus CMTagCollectionAddTag(
				CMMutableTagCollectionRef CM_NONNULL tagCollection,
				CMTag tagToAdd ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionRemoveTag
 @abstract Removes one tag from a mutable tag collection.
 @discussion This routine removes a CMTag if present from a CMMutableTagCollection. If the CMTag exists in the tag collection, the tag collection is updated to no longer contain the tag. If the tag doesn't exist in the tag collection, the tag collection is left unchanged.  The OSStatus will return kCMTagCollectionError_TagNotFound if the tag does not exist in the collection or if the tag collection is empty.
 @param tagCollection CMMutableTagCollectionRef from which to remove a tag.
 @param tagToRemove A CMTag to match to the tag collection.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionRemoveTag(
				CMMutableTagCollectionRef CM_NONNULL tagCollection,
				CMTag tagToRemove ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionRemoveAllTags
 @abstract Removes all tags from a mutable tag collection.
 @discussion This routine removes all CMTags from a CMMutableTagCollection producing an empty collection.
 @param tagCollection CMMutableTagCollectionRef from which to remove all tags.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionRemoveAllTags( CMMutableTagCollectionRef CM_NONNULL tagCollection ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionRemoveAllTagsOfCategory
 @abstract Removes all tags having a specified category from a mutable tag collection.
 @discussion This routine removes all CMTags having a specified CMTagCategory from a CMMutableTagCollection perhaps producing an empty collection.
 @param tagCollection CMMutableTagCollectionRef from which to remove all tags.
 @param category CMTagCategory to match.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionRemoveAllTagsOfCategory(
				CMMutableTagCollectionRef CM_NONNULL tagCollection,
				CMTagCategory category ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionAddTagsFromCollection
 @abstract Add all tags from one tag collection to a mutable tag collection.  Tags already existing in tagCollection will not be added.
 @param tagCollection CMMutableTagCollectionRef to which to add tags.
 @param collectionWithTagsToAdd CMTagCollectionRef from which to copy all tags.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionAddTagsFromCollection(
				CMMutableTagCollectionRef CM_NONNULL tagCollection,
				CMTagCollectionRef CM_NONNULL collectionWithTagsToAdd ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @function CMTagCollectionAddTagsFromArray
 @abstract Adds all tags specified in a C array to a mutable tag collection.  Tags already existing in tagCollection will not be added.
 @param tagCollection CMMutableTagCollectionRef to which to add tags.
 @param tags The address of a buffer of CMTags.
 @param tagCount CMItemCount of the number of tags in 'tags' array.
 @result OSStatus indicating if the operation succeeded.
*/
CM_EXPORT OSStatus CMTagCollectionAddTagsFromArray(
				CMMutableTagCollectionRef CM_NONNULL tagCollection,
				CMTag * CM_NONNULL tags,
				CMItemCount tagCount ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTagCollection dictionary serialization

/*!
	@function	CMTagCollectionCopyAsDictionary
	@abstract   Returns a CFDictionary representation of a CMTagCollection.
	@discussion This is useful when putting CMTagCollections in CF container types.
	@param 		tagCollection	CMTagCollection to serialize as a CFDictionary.
	@param		allocator	CFAllocator with which to create a dictionary. Pass kCFAllocatorDefault to use the default allocator.
	@result     A CFDictionaryRef holding the serialized contents of the CMTagCollection.  The client is responsible for releasing the returned CFDictionary.
*/
CM_EXPORT CM_RETURNS_RETAINED CFDictionaryRef CM_NULLABLE CMTagCollectionCopyAsDictionary(
				CMTagCollectionRef CM_NONNULL tagCollection,
				CFAllocatorRef CM_NULLABLE  allocator ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionCreateFromDictionary
	@abstract   Reconstitutes a CMTagCollection from a CFDictionary previously created by CMTagCollectionCopyAsDictionary.
	@discussion This is useful when getting CMTagCollection from CF container types.  If the CFDictionary does not have the requisite keyed values, newCollectionOut will contain NULL.
	@param dict	A CFDictionary from which to create a CMTagCollection.
	@param allocator CFAllocator to use in allocation CMTagCollectionRef
	@param newCollectionOut Address of an CMTagCollectionRef to return the newly created tag collection.  The client is responsible for releasing the returned CMTagCollection.
	@result OSStatus with error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionCreateFromDictionary(
				CFDictionaryRef CM_NONNULL dict,
				CFAllocatorRef CM_NULLABLE allocator,
				CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL newCollectionOut ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTagCollection data serialization

/*
	CMTagCollection serialization as transport neutral CFData (e.g., always big endian)
*/

/*!
	@function	CMTagCollectionCopyAsData
	@abstract   Returns a CFDataRef version of a CMTagCollection.
	@discussion This is useful when putting CMTagCollections in CF container types.
	@param 		tagCollection	CMTagCollection to serialize as a CFData.
	@param 		allocator	CFAllocator with which to create a CFData. Pass kCFAllocatorDefault to use the default allocator.
	@result     A CFDataRef holding the serialized contents of the CMTagCollection.  The client is responsible for releasing the returned CFData.
*/
CM_EXPORT CM_RETURNS_RETAINED CFDataRef CM_NULLABLE CMTagCollectionCopyAsData(
				CMTagCollectionRef CM_NONNULL tagCollection,
				CFAllocatorRef CM_NULLABLE  allocator ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCollectionCreateFromData
	@abstract   Reconstitutes a CMTagCollection from a CFData previously created by CMTagCollectionCopyAsData.
	@discussion This is useful when getting CMTagCollection from CF container types.  If the CFData does not
				have the requisite keyed values, newCollectionOut will contain NULL.
	@param data	A CFData from which to create a CMTagCollection.
	@param allocator CFAllocator to use in allocation CMTagCollectionRef.  Pass kCFAllocatorDefault to use the default allocator.
	@param newCollectionOut Address of an CMTagCollectionRef to return the newly created tag collection.  The client is responsible for releasing the returned CMTagCollection.
	@result OSStatus with error or noErr if successful.
*/
CM_EXPORT OSStatus CMTagCollectionCreateFromData(
				CFDataRef CM_NONNULL data,
				CFAllocatorRef CM_NULLABLE allocator,
				CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL newCollectionOut) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Serialization Dictionary Keys

/*!
	@constant kCMTagCollectionTagsArrayKey
	@discussion CFDictionary key for a CFArray of serialized CMTag dictionaries of a CMTagCollection as used with CMTagCollectionCopyAsDictionary
 */
CM_EXPORT const CFStringRef kCMTagCollectionTagsArrayKey CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma pack(pop)

CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#ifdef __cplusplus
}
#endif
	
#endif // CMTAGCOLLECTION_H
