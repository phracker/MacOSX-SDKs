/*
 *  CVHostTime.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2014 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVHostTime.h
	@copyright 2004-2014 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion Utility functions for retrieving and working with the host time.
*/

#if !defined(__COREVIDEO_CVHOSTTIME_H__)
#define __COREVIDEO_CVHOSTTIME_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @function   CVGetCurrentHostTime
    @abstract   Retrieve the current value of the host time base.
    @discussion On Mac OS X, the host time base for CoreVideo and CoreAudio are identical, and the values returned from either API
                may be used interchangeably.
    @result     The current host time.
*/
CV_EXPORT uint64_t CVGetCurrentHostTime() __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVGetHostClockFrequency
    @abstract   Retrieve the frequency of the host time base.
    @discussion On Mac OS X, the host time base for CoreVideo and CoreAudio are identical, and the values returned from either API
                may be used interchangeably.
    @result     The current host frequency.
*/
CV_EXPORT double   CVGetHostClockFrequency() __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVGetHostClockMinimumTimeDelta
    @abstract   Retrieve the smallest possible increment in the host time base.
    @result     The smallest valid increment in the host time base.
*/
CV_EXPORT uint32_t CVGetHostClockMinimumTimeDelta() __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

#if defined(__cplusplus)
}
#endif

#endif
