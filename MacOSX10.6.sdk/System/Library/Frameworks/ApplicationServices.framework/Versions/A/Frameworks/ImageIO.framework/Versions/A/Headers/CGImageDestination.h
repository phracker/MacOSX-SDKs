/*
 * ImageIO - CGImageDestination.h
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef CGIMAGEDESTINATION_H_
#define CGIMAGEDESTINATION_H_

typedef struct CGImageDestination *CGImageDestinationRef;

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/CGImageSource.h>



/** Properties which may be passed to "CGImageDestinationAddImage"
 ** or "CGImageDestinationAddImageFromSource" to effect the output.
 ** The values apply to a single image of an image destination. **/


/* The desired compression quality to use when writing to an image 
 * destination. If present, the value of this key is a CFNumberRef 
 * in the range 0.0 to 1.0. A value of 1.0 implies lossless
 * compression is desired if destination format supports it. 
 * A value of 0.0 implies that that maximum compression is 
 * desired. */

CG_EXTERN const CFStringRef kCGImageDestinationLossyCompressionQuality  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);


/* The desired background color to composite against when writing 
 * an image with alpha to a destination format that does not support 
 * alpha. If present, the value of this key is a CGColorRef without
 * any alpha component of its own.  If not present a white color
 * will be used if needed. */

CG_EXTERN const CFStringRef kCGImageDestinationBackgroundColor  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);



/* Return the CFTypeID for CGImageDestinations. */

CG_EXTERN CFTypeID CGImageDestinationGetTypeID(void)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Return an array of supported type identifiers. */

CG_EXTERN CFArrayRef CGImageDestinationCopyTypeIdentifiers(void)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Create an image destination writing to the data consumer `consumer'.
 * The parameter `type' specifies the type identifier of the resulting
 * image file.  The parameter `count' specifies number of images (not
 * including thumbnails) that the image file will contain. The `options'
 * dictionary is reserved for future use; currently, you should pass NULL
 * for this parameter. */

CG_EXTERN CGImageDestinationRef CGImageDestinationCreateWithDataConsumer(CGDataConsumerRef consumer, CFStringRef type, size_t count, CFDictionaryRef options)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Create an image destination writing to `data'. The parameter `type'
 * specifies the type identifier of the resulting image file.  The
 * parameter `count' specifies number of images (not including thumbnails)
 * that the image file will contain. The `options' dictionary is reserved
 * for future use; currently, you should pass NULL for this parameter. */

CG_EXTERN CGImageDestinationRef CGImageDestinationCreateWithData(CFMutableDataRef data, CFStringRef type, size_t count, CFDictionaryRef options)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Create an image destination writing to `url'. The parameter `type'
 * specifies the type identifier of the resulting image file.  The
 * parameter `count' specifies number of images (not including thumbnails)
 * that the image file will contain. The `options' dictionary is reserved
 * for future use; currently, you should pass NULL for this parameter.
 * Note that if `url' already exists, it will be overwritten. */

CG_EXTERN CGImageDestinationRef CGImageDestinationCreateWithURL(CFURLRef url, CFStringRef type, size_t count, CFDictionaryRef options)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Specify the dictionary `properties' of properties which apply to all
 * images in the image destination `idst'. */

CG_EXTERN void CGImageDestinationSetProperties(CGImageDestinationRef idst, CFDictionaryRef properties)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Set the next image in the image destination `idst' to be `image' with
 * optional properties specified in `properties'.  An error is logged if
 * more images are added than specified in the original count of the image
 * destination. */

CG_EXTERN void CGImageDestinationAddImage(CGImageDestinationRef idst, CGImageRef image, CFDictionaryRef properties)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Set the next image in the image destination `idst' to be the image at
 * `index' in the image source `isrc'.  The index is zero-based. The
 * properties of the source image can be added to or overriden by supplying
 * additional keys/values in `properties'.  If a key in `properties' has
 * the value kCFNull, the corresponding property in the destination will be
 * removed. */

CG_EXTERN void CGImageDestinationAddImageFromSource(CGImageDestinationRef idst, CGImageSourceRef isrc, size_t index, CFDictionaryRef properties)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Write everything to the destination data, url or consumer of the image
 * destination `idst'.  You must call this function or the image
 * destination will not be valid.  After this function is called, no
 * additional data will be written to the image destination.  Return true
 * if the image was successfully written; false otherwise. */

CG_EXTERN bool CGImageDestinationFinalize(CGImageDestinationRef idst)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);



#endif /* CGIMAGEDESTINATION_H_ */
