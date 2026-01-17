/*!
 @header
 
 @discussion
 Access to user preference for desire to dim flashing or strobing lights in video content.
 */

#ifndef MediaAccessibility_MAVideoAccommodations_h
#define MediaAccessibility_MAVideoAccommodations_h

#include <MediaAccessibility/MADefinitions.h>
#include <CoreFoundation/CoreFoundation.h>

CF_ASSUME_NONNULL_BEGIN

/*!
 @function MADimFlashingLightsEnabled
 @abstract Returns whether the user has enabled the setting to reduce flashing or strobing lights in video content. This setting can also be used to determine if UI in playback controls should be shown.
 @result A boolean
 */

MA_EXPORT
bool MADimFlashingLightsEnabled(void) CF_AVAILABLE(13_3, 16_4);

/*!
 @constant kMADimFlashingLightsChangedNotification
 @abstract CFNotification sent to local notification center when mitigation for flashing or strobing lights settings are changed.
 */
MA_EXPORT
const CFStringRef kMADimFlashingLightsChangedNotification CF_AVAILABLE(13_3, 16_4);

CF_ASSUME_NONNULL_END

#endif
