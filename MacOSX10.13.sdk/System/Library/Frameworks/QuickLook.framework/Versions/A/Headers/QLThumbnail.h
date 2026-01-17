/*
 *  QLThumbnail.h
 *  Quick Look
 *
 *  Copyright 2007-2010 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLTHUMBNAIL__)
#define __QUICKLOOK_QLTHUMBNAIL__

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <QuickLook/QLBase.h>

#include <QuickLook/QLThumbnailImage.h>
#if __BLOCKS__ && MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
#include <dispatch/dispatch.h>
#endif

QL_EXTERN_C_BEGIN


typedef struct CF_BRIDGED_TYPE(id) __QLThumbnail *QLThumbnailRef;

QL_EXPORT CFTypeID QLThumbnailGetTypeID();

/*
 @function QLThumbnailCreate
 @abstract Creates a thumbnail instance. The thumbnail image will be computed in background.
 @param allocator The allocator to use to create the instance.
 @param url The URL of the document to thumbnail.
 @param maxThumbnailSize Maximum size (in points) allowed for the thumbnail image.
 @param options Optional hints for the thumbnail. (Only kQLThumbnailOptionScaleFactorKey is available for now)
 @result The thumbnail instance.
 */
QL_EXPORT QLThumbnailRef QLThumbnailCreate(CFAllocatorRef allocator, CFURLRef url, CGSize maxThumbnailSize, CFDictionaryRef options) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*
 @function QLThumbnailCopyDocumentURL
 @abstract Returns the URL of the document to thumbnail.
 @param thumbnail The thumbnail to compute.
 */
QL_EXPORT CFURLRef QLThumbnailCopyDocumentURL(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*
 @function QLThumbnailGetMaximumSize
 @abstract Returns the maximum size (in points) allowed for the thumbnail image.
 @param thumbnail The thumbnail to compute.
 */
QL_EXPORT CGSize QLThumbnailGetMaximumSize(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*
 @function QLThumbnailCopyOptions
 @abstract Returns the options for the thumbnail.
 @param thumbnail The thumbnail to compute.
 */
QL_EXPORT CFDictionaryRef QLThumbnailCopyOptions(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#if __BLOCKS__ && MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
/*
 @function QLThumbnailDispatchAsync
 @abstract Start computing thumbnail in background.
 @param thumbnail The thumbnail to compute.
 @param queue Where the completion block will be dispatched.
 @param completion The completion block called upon thumbnail completion.
 @discussion The completion block will always be called, even if the thumbnail computation has been cancelled.
 */
QL_EXPORT void QLThumbnailDispatchAsync(QLThumbnailRef thumbnail, dispatch_queue_t queue, dispatch_block_t completion) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
#endif

/*
 @function QLThumbnailCopyImage
 @abstract Returns the image computed by Quick Look or NULL if not thumbnail was created.
 @param thumbnail The thumbnail to compute.
 @result The thumbnail image or NULL.
 @discussion If called without a previous of QLThumbnailDispatchAsync(), the call will block until the thumbnail is computed.
             QLThumbnailCopyImage() should not be called during async dispatch (before the completion block has been called)
 */
QL_EXPORT CGImageRef QLThumbnailCopyImage(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*
 @function QLThumbnailGetContentRect
 @abstract Returns the the effective rect within the thumbnail image representing the
           content of the document. In icon mode, this is the part of the image without
           all the image decorations.
 @param thumbnail The thumbnail to compute.
 @result The content rect of the thumbnail expressed in pixel coordinates.
 */
QL_EXPORT CGRect QLThumbnailGetContentRect(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/*
 @function QLThumbnailCancel
 @abstract Cancels the computation of the thumbnail.
 @param thumbnail The thumbnail to compute.
 @discussion If used with QLThumbnailDispatchAsync() the completion callback will be called.
             If used in synchronous mode, QLThumbnailCopyImage() will return immediately NULL.
 */
QL_EXPORT void QLThumbnailCancel(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*
 @function QLThumbnailIsCancelled
 @abstract Returns wether the thumbnail computation has been cancelled.
 @param thumbnail The thumbnail to compute.
 */
QL_EXPORT Boolean QLThumbnailIsCancelled(QLThumbnailRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


QL_EXTERN_C_END

#endif
