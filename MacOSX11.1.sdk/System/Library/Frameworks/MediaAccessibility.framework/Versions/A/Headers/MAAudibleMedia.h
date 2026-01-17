/*!
 @header
 
 @discussion
 Access to user preferences for audible media selection
 */

#ifndef MediaAccessibility_MAAudibleMedia_h
#define MediaAccessibility_MAAudibleMedia_h

#include <MediaAccessibility/MADefinitions.h>
#include <AvailabilityMacros.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFBase.h>

MA_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*!
 @constant kMAAudibleMediaSettingsChangedNotification
 @abstract CFNotification sent when any user-defined audible media settings are changed.
 */
MA_EXPORT const CFStringRef kMAAudibleMediaSettingsChangedNotification;

/*!
 @constant MAMediaCharacteristicDescribesVideoForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option includes audible content that descries a video for accessibility.
 */
MA_EXPORT CFStringRef const MAMediaCharacteristicDescribesVideoForAccessibility CF_AVAILABLE(10_10, 8_0);

/*!
 @function MAAudibleMediaCopyPreferredCharacteristics
 @abstract User preference for audible media characteristic
 @result An array containing the preferred order of media characteristics for audible media.
 */
MA_EXPORT CFArrayRef MAAudibleMediaCopyPreferredCharacteristics(void) CF_AVAILABLE(10_10, 8_0);

CF_ASSUME_NONNULL_END
MA_EXTERN_C_END

#endif /* MediaAccessibility_MAAudibleMedia_h */
