/*
    File:  CMTimeRange.h
	
	Framework:  CoreMedia
 
	Copyright © 2007-2018 Apple Inc. All rights reserved.
 
*/

#ifndef CMTIMERANGE_H
#define CMTIMERANGE_H

/*!
	@header
	@abstract	API for creating and manipulating CMTimeRange structs.
	@discussion	CMTimeRange structs are non-opaque mutable structs that represent time ranges.
	
				A CMTimeRange is represented as two CMTime structs, one that specifies the start time of the
				range and another that specifies the duration of the range. A time range does not include the time
				that is the start time plus the duration. In other words, the following expression
				
					CMTimeRangeContainsTime(range, CMTimeRangeGetEnd(range))
					
				always evaluates to false.
				
				CMTimeRanges can be converted to/from immutable CFDictionaries, via CMTimeRangeCopyAsDictionary and
				CMTimeRangeMakeFromDictionary, for use in annotations and various CF containers.
				
				The epoch in a CMTime that represents a duration should always be 0, and the value must be non-negative. 
				The epoch in a CMTime that	represents a timestamp may be non-zero, but range operations (such as
				CMTimeRangeGetUnion) can only be performed on ranges whose start fields have the same epoch. 
				CMTimeRanges cannot span different epochs.
*/

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTime.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	CMTimeRange
	@abstract	A time range represented as two CMTime structures.
*/
typedef struct
{
	CMTime			start;		/*! @field start The start time of the time range. */
	CMTime			duration;	/*! @field duration The duration of the time range. */
} CMTimeRange API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTIMERANGE_IS_VALID
    @abstract   Returns whether a CMTimeRange is valid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange is valid, false if it is invalid.
*/
#define CMTIMERANGE_IS_VALID(range) ((Boolean)(CMTIME_IS_VALID(range.start) && CMTIME_IS_VALID(range.duration) && (range.duration.epoch == 0) && (range.duration.value >= 0)))

/*!
	@function	CMTIMERANGE_IS_INVALID
    @abstract   Returns whether a CMTimeRange is invalid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange is invalid, false if it is valid.
*/
#define CMTIMERANGE_IS_INVALID(range) (! CMTIMERANGE_IS_VALID(range))

/*!
	@function	CMTIMERANGE_IS_INDEFINITE
    @abstract   Returns whether a CMTimeRange is indefinite.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange is indefinite, false if it is not.
*/
#define CMTIMERANGE_IS_INDEFINITE(range) ((Boolean)(CMTIMERANGE_IS_VALID(range) && (CMTIME_IS_INDEFINITE(range.start) || CMTIME_IS_INDEFINITE(range.duration))))

/*!
	@function	CMTIMERANGE_IS_EMPTY
    @abstract   Returns whether a CMTimeRange has a duration of 0.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange has a duration of 0, false if it is not.
*/
#define CMTIMERANGE_IS_EMPTY(range) ((Boolean)(CMTIMERANGE_IS_VALID(range) && (CMTIME_COMPARE_INLINE(range.duration, ==, kCMTimeZero))))

CM_EXPORT const CMTimeRange kCMTimeRangeZero	/*! @constant kCMTimeRangeZero 
													Use this constant to generate an empty CMTimeRange at 0. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));		

CM_EXPORT const CMTimeRange kCMTimeRangeInvalid /*! @constant kCMTimeRangeInvalid 
													Use this constant to generate an invalid CMTimeRange. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeMake
	@abstract	Make a valid CMTimeRange with start and duration.
	@result		The resulting CMTimeRange.
    @discussion The duration parameter must have an epoch of 0; otherwise an invalid time range will be returned.
*/
CM_EXPORT CMTimeRange CMTimeRangeMake(
				CMTime start,					/*! @param start			Initializes the start field of the resulting CMTimeRange. */
				CMTime duration)				/*! @param duration			Initializes the duration field of the resulting CMTimeRange. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));
 
/*!
	@function	CMTimeRangeGetUnion
    @abstract   Returns the union of two CMTimeRanges.
    @discussion	This function returns a CMTimeRange structure that represents the union of the time ranges specified by the <i>range</i> and <i>otherRange</i> parameters.
				This is the smallest range that includes all times that are in either range.
	@result     The union of the two CMTimeRanges.
*/
CM_EXPORT CMTimeRange CMTimeRangeGetUnion(
				CMTimeRange range,				/*! @param range			A CMTimeRange to be unioned. */
				CMTimeRange otherRange)				/*! @param otherRange			Another CMTimeRange to be unioned. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeGetIntersection
    @abstract   Returns the intersection of two CMTimeRanges.
    @discussion	This function returns a CMTimeRange structure that represents the intersection of the time ranges specified by the <i>range</i> and <i>otherRange</i> parameters.
				This is the largest range that both ranges include.
	@result     The intersection of the two CMTimeRanges.
*/
CM_EXPORT CMTimeRange CMTimeRangeGetIntersection(
				CMTimeRange range,				/*! @param range			A CMTimeRange to be intersected. */
				CMTimeRange otherRange)				/*! @param otherRange			Another CMTimeRange to be intersected. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeEqual
    @abstract   Returns a Boolean value that indicates whether two CMTimeRanges are identical.
    @discussion	This function returns a Boolean value that indicates whether the time ranges specified by the <i>range1</i> and <i>range2</i> parameters are identical.
    @result     Returns true if the two time ranges are identical, false if they differ.
*/
CM_EXPORT Boolean CMTimeRangeEqual(
				CMTimeRange range1,				/*! @param range1			A CMTimeRange to be compared for equality. */
				CMTimeRange range2)				/*! @param range2			Another CMTimeRange to be compared for equality. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeContainsTime
	@abstract	Indicates whether a time is contained within a time range.
    @discussion	This function returns a Boolean value that indicates whether the time specified by the <i>time</i> parameter
				is contained within the range specified by the <i>range</i> parameter.
    @result     Returns true if the specified time is contained within the specified time range, false if it is not.
*/
CM_EXPORT Boolean CMTimeRangeContainsTime(
				CMTimeRange range,				/*! @param range			A CMTimeRange to be tested for inclusion. */
				CMTime time)					/*! @param time				A CMTime to be tested for inclusion. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeContainsTimeRange
	@abstract	Indicates whether a time range is contained within a time range.
    @discussion	This function returns a Boolean value that indicates whether the time range specified by the <i>range</i> parameter
				contains the range specified by the <i>otherRange</i> parameter.
    @result     Returns true if the second time range is contained within the first time range, false if it is not.
*/
CM_EXPORT Boolean CMTimeRangeContainsTimeRange(
				CMTimeRange range,				/*! @param range			A CMTimeRange. */
				CMTimeRange otherRange)				/*! @param otherRange			Another CMTimeRange to be tested for inclusion. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeGetEnd
	@abstract	Returns a CMTime structure representing the end of a time range.
    @result		A CMTime structure representing the end of the specified time range.
    @discussion	This function returns a CMTime structure that indicates the end of the time range specified by the <i>range</i> parameter.
    			CMTimeRangeContainsTime(range, CMTimeRangeGetEnd(range)) is always false.
*/
CM_EXPORT CMTime CMTimeRangeGetEnd(
				CMTimeRange range)				/*! @param range			A CMTimeRange. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeMapTimeFromRangeToRange
	@abstract	Translates a time through a mapping from CMTimeRange to CMTimeRange.
	@result		A CMTime structure representing the translated time.
	@discussion	The start and end time of fromRange will be mapped to the start and end time of toRange respectively.
    			Other times will be mapped linearly, using the formula:
    				result = (t-fromRange.start)*(toRange.duration/fromRange.duration)+toRange.start
    			If either CMTimeRange argument is empty, an invalid CMTime will be returned.
    			If t does not have the same epoch as fromRange.start, an invalid CMTime will be returned.
    			If both fromRange and toRange have duration kCMTimePositiveInfinity, 
    			t will be offset relative to the differences between their starts, but not scaled.
*/
CM_EXPORT CMTime CMTimeMapTimeFromRangeToRange( 
				CMTime t, 
				CMTimeRange fromRange, 
				CMTimeRange toRange )
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeClampToRange
	@abstract	For a given CMTime and CMTimeRange, returns the nearest CMTime inside that time range.
	@result		A CMTime structure inside the given time range.
	@discussion	Times inside the given time range will be returned unmodified.
    			Times before the start and after the end time of the time range will return the start and end time of 
    			the range respectively.
    			If the CMTimeRange argument is empty, an invalid CMTime will be returned.
    			If the given CMTime is invalid, the returned CMTime will be invalid, 
*/
CM_EXPORT CMTime CMTimeClampToRange( 
				CMTime time, 
				CMTimeRange range )
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeMapDurationFromRangeToRange
	@abstract	Translates a duration through a mapping from CMTimeRange to CMTimeRange.
	@result		A CMTime structure representing the translated duration.
	@discussion	The duration will be scaled in proportion to the ratio between the ranges' durations:
    				result = dur*(toRange.duration/fromRange.duration)
    			If dur does not have the epoch zero, an invalid CMTime will be returned.
*/
CM_EXPORT CMTime CMTimeMapDurationFromRangeToRange( 
				CMTime dur, 
				CMTimeRange fromRange, 
				CMTimeRange toRange )
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeFoldIntoRange
	@abstract	Folds a time into the given range.  This can be used in looping time calculations.
	@result		A CMTime structure representing the translated duration.
	@discussion	Note that for certain types of looping, you may want to NOT fold times that are prior
				to the loop range.  That's up to the client.
*/
CM_EXPORT CMTime
CMTimeFoldIntoRange(
				CMTime time,					/*! @param time				The CMTime to fold. */
				CMTimeRange foldRange )			/*! @param foldRange		The CMTimeRange into which to fold it. */
							API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(6.0));

/*!
	@function	CMTimeRangeFromTimeToTime
	@abstract	Make a valid CMTimeRange with the given starting and ending times.
	@result		The resulting CMTimeRange.
*/
CM_EXPORT CMTimeRange CMTimeRangeFromTimeToTime(
				CMTime start, 
				CMTime end )
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeCopyAsDictionary
    @abstract   Returns a CFDictionary version of a CMTimeRange.
    @discussion This is useful when putting CMTimeRanges in CF container types.
    @result     A CFDictionary version of the CMTimeRange.
*/
CM_EXPORT CFDictionaryRef CM_NULLABLE CMTimeRangeCopyAsDictionary(
				CMTimeRange range,							/*! @param range			The CMTimeRange from which to create a dictionary. */
				CFAllocatorRef CM_NULLABLE  allocator)		/*! @param allocator		CFAllocator with which to create a dictionary. Pass kCFAllocatorDefault to use the default allocator. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeMakeFromDictionary
    @abstract   Reconstitutes a CMTimeRange struct from a CFDictionary previously created by CMTimeRangeCopyAsDictionary.
    @discussion This is useful when getting CMTimeRanges from CF container types.  If the CFDictionary does not
				have the requisite keyed values, an invalid time range is returned.
	@result		The created CMTimeRange.  
*/
CM_EXPORT CMTimeRange CMTimeRangeMakeFromDictionary(
				CFDictionaryRef CM_NONNULL dictionaryRepresentation)			/*! @param dictionaryRepresentation				A CFDictionary from which to create a CMTimeRange. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

CM_ASSUME_NONNULL_BEGIN

/*!
	@constant kCMTimeRangeStartKey
	@discussion CFDictionary key for start field of a CMTimeRange (CMTime)
*/
CM_EXPORT const CFStringRef kCMTimeRangeStartKey
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@constant kCMTimeRangeDurationKey
	@discussion CFDictionary key for timescale field of a CMTimeRange (CMTime)
*/
CM_EXPORT const CFStringRef kCMTimeRangeDurationKey
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

CM_ASSUME_NONNULL_END

/*!
	@function	CMTimeRangeCopyDescription
    @abstract   Creates a CFString with a description of a CMTimeRange (just like CFCopyDescription).
    @discussion This is used from within CFShow on an object that contains CMTimeRange fields. It is
				also useful from other client debugging code.  The caller owns the returned CFString and is responsible for releasing it.
	@result		The created CFString description.  
*/
CM_EXPORT CFStringRef CM_NULLABLE CMTimeRangeCopyDescription(
				CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator		CFAllocator with which to create description. Pass kCFAllocatorDefault to use the default allocator. */
				CMTimeRange range)							/*! @param range			The CMTimeRange to describe. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeRangeShow
    @abstract   Prints a description of the CMTimeRange (just like CFShow).
    @discussion This is most useful from within gdb.
*/
CM_EXPORT void CMTimeRangeShow(
				CMTimeRange range)				/*! @param range			The CMTimeRange to show. */
							API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@typedef	CMTimeMapping
	@abstract	A CMTimeMapping specifies the mapping of a segment of one time line (called "source") into another time line (called "target").
	@discussion
		When used for movie edit lists, the source time line is the media and the target time line is the track/movie.
	@field	source
		The time range on the source time line.  
		For an empty edit, source.start is an invalid CMTime, in which case source.duration shall be ignored.
		Otherwise, source.start is the starting time within the source, and source.duration is the duration 
		of the source timeline to be mapped to the target time range.
	@field	target
		The time range on the target time line.
		If target.duration and source.duration are different, then the source segment should
		be played at rate source.duration/target.duration to fit.
*/
typedef struct 
{
	CMTimeRange source; // eg, media.  source.start is kCMTimeInvalid for empty edits.
	CMTimeRange target; // eg, track.
} CMTimeMapping API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTIMEMAPPING_IS_VALID
    @abstract   Returns whether a CMTimeMapping is valid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeMapping is valid, false if it is invalid.
*/
#define CMTIMEMAPPING_IS_VALID(mapping) (CMTIMERANGE_IS_VALID(mapping.target))

/*!
	@function	CMTIMEMAPPING_IS_INVALID
    @abstract   Returns whether a CMTimeMapping is invalid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeMapping is invalid, false if it is valid.
*/
#define CMTIMEMAPPING_IS_INVALID(mapping) (! CMTIMEMAPPING_IS_VALID(mapping))

/*!
	@function	CMTIMEMAPPING_IS_EMPTY
    @abstract   Returns whether a CMTimeMapping is empty.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeMapping is empty, false if it is not empty.
*/
#define CMTIMEMAPPING_IS_EMPTY(mapping) ((Boolean)((! CMTIME_IS_NUMERIC(mapping.source.start)) && CMTIMERANGE_IS_VALID(mapping.target)))

CM_EXPORT const CMTimeMapping kCMTimeMappingInvalid /*! @constant kCMTimeMappingInvalid 
													Use this constant to generate an invalid CMTimeMapping. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeMappingMake
	@abstract	Make a valid CMTimeMapping with source and target.
	@result		The resulting CMTimeMapping.
    @discussion The source and target parameters must have durations whose epoch is 0; otherwise an invalid time mapping will be returned.
*/
CM_EXPORT CMTimeMapping CMTimeMappingMake(
				CMTimeRange source,				/*! @param source			Initializes the source field of the resulting CMTimeMapping. */
				CMTimeRange target)				/*! @param target			Initializes the target field of the resulting CMTimeMapping. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
 
/*!
	@function	CMTimeMappingMakeEmpty
	@abstract	Make a valid CMTimeMapping with an empty source.
	@result		The resulting CMTimeMapping.
    @discussion The target parameter must have a duration whose epoch is 0; otherwise an invalid time mapping will be returned.
*/
CM_EXPORT CMTimeMapping CMTimeMappingMakeEmpty(
				CMTimeRange target)				/*! @param target			Initializes the target field of the resulting CMTimeMapping. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
 
/*!
	@function	CMTimeMappingCopyAsDictionary
    @abstract   Returns a CFDictionary version of a CMTimeMapping.
    @discussion This is useful when putting CMTimeMappings in CF container types.
    @result     A CFDictionary version of the CMTimeMapping.
*/
CM_EXPORT CFDictionaryRef CM_NULLABLE CMTimeMappingCopyAsDictionary(
				CMTimeMapping mapping,			/*! @param mapping			The CMTimeMapping from which to create a dictionary. */
				CFAllocatorRef CM_NULLABLE allocator)		/*! @param allocator		CFAllocator with which to create a dictionary. Pass kCFAllocatorDefault to use the default allocator. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeMappingMakeFromDictionary
    @abstract   Reconstitutes a CMTimeMapping struct from a CFDictionary previously created by CMTimeMappingCopyAsDictionary.
    @discussion This is useful when getting CMTimeMappings from CF container types.  If the CFDictionary does not
				have the requisite keyed values, an invalid time mapping is returned.
	@result		The created CMTimeMapping.  
*/
CM_EXPORT CMTimeMapping CMTimeMappingMakeFromDictionary(
				CFDictionaryRef CM_NONNULL dictionaryRepresentation)			/*! @param dictionaryRepresentation				A CFDictionary from which to create a CMTimeMapping. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
CM_ASSUME_NONNULL_BEGIN
/*!
	@constant kCMTimeMappingSourceKey
	@discussion CFDictionary key for source field of a CMTimeMapping (CMTimeRange)
*/
CM_EXPORT const CFStringRef kCMTimeMappingSourceKey
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));

/*!
	@constant kCMTimeMappingTargetKey
	@discussion CFDictionary key for target field of a CMTimeMapping (CMTimeRange)
*/
CM_EXPORT const CFStringRef kCMTimeMappingTargetKey
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
CM_ASSUME_NONNULL_END
/*!
	@function	CMTimeMappingCopyDescription
    @abstract   Creates a CFString with a description of a CMTimeMapping (just like CFCopyDescription).
    @discussion This is used from within CFShow on an object that contains CMTimeMapping fields. It is
				also useful from other client debugging code.  The caller owns the returned CFString and is responsible for releasing it.
	@result		The created CFString description.  
*/
CM_EXPORT CFStringRef CM_NULLABLE CMTimeMappingCopyDescription(
				CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator		CFAllocator with which to create description. Pass kCFAllocatorDefault to use the default allocator. */
				CMTimeMapping mapping)			/*! @param mapping			The CMTimeMapping to describe. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeMappingShow
    @abstract   Prints a description of a CMTimeMapping (just like CFShow).
    @discussion This is most useful from within gdb.
*/
CM_EXPORT void CMTimeMappingShow(
				CMTimeMapping mapping)			/*! @param mapping			The CMTimeMapping to show. */
							API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
	
#endif // CMTIMERANGE_H
