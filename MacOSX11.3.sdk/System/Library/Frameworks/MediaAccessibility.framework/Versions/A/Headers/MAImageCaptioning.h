/*!
 @header
 
 @discussion
 Methods to set and get an image's accessibility caption embedded in image metadata.
 */

#ifndef MediaAccessibility_MAImageCaptioning_h
#define MediaAccessibility_MAImageCaptioning_h

#include <AvailabilityMacros.h>

#include <MediaAccessibility/MADefinitions.h>
#include <CoreFoundation/CoreFoundation.h>

CF_ASSUME_NONNULL_BEGIN

/*!
 @function MAImageCaptioningCopyCaption
 @abstract Returns an accessibility caption from an image's metadata.
 @param url The URL locating the image on disk.
 @param error If an error occurs, a description will be provided.
 @result A string with the image caption. Nil if there's no caption.
 @discussion A convenience function for retrieving a caption from an image file that aims to describe the photo accurately.
 This checks for XMP metadata field: Iptc4xmpExt:AOContentDescription.
 */
MA_EXPORT
_Nullable CFStringRef MAImageCaptioningCopyCaption(CFURLRef url, CFErrorRef _Nullable * _Nullable CF_RETURNS_RETAINED error) API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macos(10.15)) CF_RETURNS_RETAINED;

/*!
 @function MAImageCaptioningSetCaption
 @abstract Sets the accessibility caption into an image's metadata.
 @param url The URL locating the image on disk.
 @param error If an error occurs, a description will be provided.
 @param string The accessility caption.
 @result A bool representing whether the operation was successful.
 @discussion A convenience function for setting a caption to an image file that aims to describe the photo accurately.
 This sets the XMP metadata field: Iptc4xmpExt:AOContentDescription.
 */
MA_EXPORT
bool MAImageCaptioningSetCaption(CFURLRef url, CFStringRef __nullable string, CFErrorRef _Nullable * _Nullable CF_RETURNS_RETAINED error) API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macos(10.15));

/*!
 @function MAImageCaptioningCopyMetadataTagPath
 @abstract Returns the metadata tagpath for this key.
 This tag path can be used to copy metadata directly using CGImageMetadataCopyTagWithPath from the CGImageMetadataRef, for example.
 @result A string representing the tag path.
 @discussion This returns the appropriate metadata tag path to be used.
 */
MA_EXPORT
CFStringRef MAImageCaptioningCopyMetadataTagPath(void) API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macos(10.15)) CF_RETURNS_RETAINED;

CF_ASSUME_NONNULL_END

#endif /* MediaAccessibility_MAImageCaptioning_h */
