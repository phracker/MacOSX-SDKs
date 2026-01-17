/*
 * ImageIO - CGImageSource.h
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef CGIMAGESOURCE_H_
#define CGIMAGESOURCE_H_

typedef struct CGImageSource *CGImageSourceRef;

#include <CoreGraphics/CoreGraphics.h>

CG_EXTERN_C_BEGIN


enum CGImageSourceStatus {
    kCGImageStatusUnexpectedEOF = -5,
    kCGImageStatusInvalidData = -4,
    kCGImageStatusUnknownType = -3,
    kCGImageStatusReadingHeader = -2,
    kCGImageStatusIncomplete = -1,
    kCGImageStatusComplete = 0
};
typedef enum CGImageSourceStatus CGImageSourceStatus;

/** Keys for the options dictionary when creating a CGImageSourceRef. **/

/* Specifies the "best guess" of the type identifier for the format of the
 * image source file. If specified, the value of this key must be a
 * CFStringRef. For more information about type identifiers, see "UTType.h"
 * in the Application Services framework. */

CG_EXTERN const CFStringRef kCGImageSourceTypeIdentifierHint  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Keys for the options dictionary of "CGImageSourceCopyPropertiesAtIndex"
 ** and "CGImageSourceCreateImageAtIndex". **/

/* Specifies whether the image should be cached in a decoded form. The
 * value of this key must be a CFBooleanRef; the default value is
 * kCFBooleanFalse. */

CG_EXTERN const CFStringRef kCGImageSourceShouldCache  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Specifies whether the image should be returned as a floating
 * point CGImageRef if supported by the file format. Extended
 * range floating point CGImageRef may require additional
 * processing  to render pleasingly.  The value of this key must
 * be a CFBooleanRef; the default value is kCFBooleanFalse. */

CG_EXTERN const CFStringRef kCGImageSourceShouldAllowFloat  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/** Keys for the options dictionary of
 ** "CGImageSourceCreateThumbnailAtIndex". **/

/* Specifies whether a thumbnail should be automatically created for an
 * image if a thumbnail isn't present in the image source file.  The
 * thumbnail will be created from the full image, subject to the limit
 * specified by kCGImageSourceThumbnailMaxPixelSize---if a maximum pixel
 * size isn't specified, then the thumbnail will be the size of the full
 * image, which probably isn't what you want. The value of this key must be
 * a CFBooleanRef; the default value of this key is kCFBooleanFalse. */

CG_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageIfAbsent  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Specifies whether a thumbnail should be created from the full image even
 * if a thumbnail is present in the image source file. The thumbnail will
 * be created from the full image, subject to the limit specified by
 * kCGImageSourceThumbnailMaxPixelSize---if a maximum pixel size isn't
 * specified, then the thumbnail will be the size of the full image, which
 * probably isn't what you want. The value of this key must be a
 * CFBooleanRef; the default value of this key is kCFBooleanFalse. */

CG_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageAlways  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Specifies the maximum width and height in pixels of a thumbnail.  If
 * this this key is not specified, the width and height of a thumbnail is
 * not limited and thumbnails may be as big as the image itself.  If
 * present, this value of this key must be a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImageSourceThumbnailMaxPixelSize  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Specifies whether the thumbnail should be rotated and scaled according
 * to the orientation and pixel aspect ratio of the full image. The value
 * of this key must be a CFBooleanRef; the default value of this key is 
 * kCFBooleanFalse. */

CG_EXTERN const CFStringRef kCGImageSourceCreateThumbnailWithTransform  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* Return the CFTypeID for CGImageSources. */

CG_EXTERN CFTypeID CGImageSourceGetTypeID (void)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return an array of supported type identifiers. */

CG_EXTERN CFArrayRef CGImageSourceCopyTypeIdentifiers(void)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create an image source reading from the data provider `provider'. The
 * `options' dictionary may be used to request additional creation options;
 * see the list of keys above for more information. */

CG_EXTERN CGImageSourceRef CGImageSourceCreateWithDataProvider(CGDataProviderRef provider, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create an image source reading from `data'.  The `options' dictionary
 * may be used to request additional creation options; see the list of keys
 * above for more information. */

CG_EXTERN CGImageSourceRef CGImageSourceCreateWithData(CFDataRef data, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create an image source reading from `url'. The `options' dictionary may
 * be used to request additional creation options; see the list of keys
 * above for more information. */

CG_EXTERN CGImageSourceRef CGImageSourceCreateWithURL(CFURLRef url, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the type identifier of the image source `isrc'.  This type is the
 * type of the source "container", which is not necessarily the type of the
 * image(s) in the container.  For example, the .icns format supports
 * embedded JPEG2000 but the source type will be "com.apple.icns". */

CG_EXTERN CFStringRef CGImageSourceGetType(CGImageSourceRef isrc)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the number of images (not including thumbnails) in the image
 * source `isrc'. */

CG_EXTERN size_t CGImageSourceGetCount(CGImageSourceRef isrc)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the properties of the image source `isrc'.  These properties
 * apply to the container in general but not necessarily to any individual
 * image that it contains. */

CG_EXTERN CFDictionaryRef CGImageSourceCopyProperties(CGImageSourceRef isrc, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the properties of the image at `index' in the image source
 * `isrc'.  The index is zero-based. The `options' dictionary may be used
 * to request additional options; see the list of keys above for more
 * information. */

CG_EXTERN CFDictionaryRef CGImageSourceCopyPropertiesAtIndex(CGImageSourceRef isrc, size_t index, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the image at `index' in the image source `isrc'.  The index is
 * zero-based. The `options' dictionary may be used to request additional
 * creation options; see the list of keys above for more information. */

CG_EXTERN CGImageRef CGImageSourceCreateImageAtIndex(CGImageSourceRef isrc, size_t index, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the thumbnail of the image at `index' in the image source `isrc'.
 * The index is zero-based. The `options' dictionary may be used to request
 * additional thumbnail creation options; see the list of keys above for
 * more information. */

CG_EXTERN CGImageRef CGImageSourceCreateThumbnailAtIndex(CGImageSourceRef isrc, size_t index, CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create an incremental image source. No data is provided at creation
 * time; it is assumed that data will eventually be provided using
 * "CGImageSourceUpdateDataProvider" or "CGImageSourceUpdateData".  The
 * `options' dictionary may be used to request additional creation options;
 * see the list of keys above for more information. */

CG_EXTERN CGImageSourceRef CGImageSourceCreateIncremental(CFDictionaryRef options)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Update the incremental image source `isrc' with new data.  The new data
 * must include all the previous data plus any additional new data. The
 * `final' parameter should be true when the final set of data is provided;
 * false otherwise. */

CG_EXTERN void CGImageSourceUpdateData(CGImageSourceRef isrc, CFDataRef data, bool final)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Update the incremental image source `isrc' with a new data provider.
 * The new data provider must provide all the previous data plus any
 * additional new data. The `final' parameter should be true when the final
 * set of data is provided; false otherwise. */

CG_EXTERN void CGImageSourceUpdateDataProvider(CGImageSourceRef isrc, CGDataProviderRef provider, bool final)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the overall status of the image source `isrc'.  The status is
 * particularly informative for incremental image sources, but may be used
 * by clients providing non-incremental data as well. */

CG_EXTERN CGImageSourceStatus CGImageSourceGetStatus(CGImageSourceRef isrc)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the current status of the image at `index' in the image source
 * `isrc'. The index is zero-based. The returned status is particularly
 * informative for incremental image sources but may used by clients
 * providing non-incremental data as well. */

CG_EXTERN CGImageSourceStatus CGImageSourceGetStatusAtIndex(CGImageSourceRef isrc, size_t index)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


CG_EXTERN_C_END

#endif	/* CGIMAGESOURCE_H_ */
