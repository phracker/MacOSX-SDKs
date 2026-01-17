/*
 *  QLThumbnailImage.h
 *  Quick Look
 *
 *  Copyright 2007-2010 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLTHUMBNAILIMAGE__)
#define __QUICKLOOK_QLTHUMBNAILIMAGE__

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <QuickLook/QLBase.h>

QL_EXTERN_C_BEGIN

/*!
 *      @function QLThumbnailImageCreate
 *      @abstract Creates a thumbnail for the designated file. Returns NULL if Quick Look does not support this file type.
 *      @param allocator The allocator to use to create the image.
 *      @param url The URL to the file.
 *      @param maxThumbnailSize The maximum desired size.
 *      @param options See options below.
 *      @result The thumbnail image. NULL if not available.
 *      @discussion QLThumbnailImageCreate() does not replace IconServices.
 *                  Also QLThumbnailImageCreate() will block until the thumbnail is generated so you should consider calling it in a thread.
 */
QL_EXPORT CGImageRef QLThumbnailImageCreate(CFAllocatorRef allocator, CFURLRef url, CGSize maxThumbnailSize, CFDictionaryRef options) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 * Options for the thumbnail.
 */

/*!
 *      @constant kQLThumbnailOptionIconModeKey
 *      @abstract If kCFBooleanTrue, QL will produce an icon (ie a thumbnail and all the icon decor, like shadows, curled corner, etc.).
 */
__attribute__((weak_import)) QL_EXPORT const CFStringRef kQLThumbnailOptionIconModeKey;

/*!
 *      @constant kQLThumbnailOptionScaleFactorKey
 *      @abstract This is the user scale factor (as a CFNumber). If absent, default value is 1.0
 */
__attribute__((weak_import)) QL_EXPORT const CFStringRef kQLThumbnailOptionScaleFactorKey;

QL_EXTERN_C_END

#endif

