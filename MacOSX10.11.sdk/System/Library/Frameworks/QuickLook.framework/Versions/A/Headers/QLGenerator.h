/*
 *  QLGenerator.h
 *  Quick Look
 *
 *  Copyright 2007-2010 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLGENERATOR__)
#define __QUICKLOOK_QLGENERATOR__

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <QuickLook/QLBase.h>


QL_EXTERN_C_BEGIN

#pragma mark Quick Look Plug-in Info.plist Keys

/*
 * QLThumbnailMinimumSize: (ex: <real>17</real>)
 *      Minimum useful size (in points) of generated thumbnails.
 *      Generator Thumbnail callback won't be called for sizes less than
 *      the value for this key. 17 is a good minimum value.
 *
 * QLPreviewWidth, QLPreviewHeight: (ex: <real>800</real>)
 *      Preview size hint. These values are used if the generator takes
 *      too long to produce the preview.
 *
 * QLSupportsConcurrentRequests: (ex: <true/>)
 *      This tells Quick Look never to call generator callbacks twice at the same time.
 *
 * QLNeedsToBeRunInMainThread: (ex: <false/>)
 *      This tells Quick Look to call generator callbacks in a main thread.
 *
 */

#pragma mark Common return code for generator's callback

#define kQLReturnMask 0xaf00
#define kQLReturnNoError noErr
#define kQLReturnHasMore (kQLReturnMask | 10)

#pragma mark Thumbnail generator callback

/*!
 *      @typedef QLThumbnailRequestRef
 *      @abstract This is the type of a reference to Thumbnail requests.
 */
typedef struct CF_BRIDGED_TYPE(id) __QLThumbnailRequest *QLThumbnailRequestRef;

/*!
 *      @function QLThumbnailRequestGetTypeID
 *      @abstract Returns the CoreFoundation type ID for QLThumbnailRequests.
 */
QL_EXPORT CFTypeID QLThumbnailRequestGetTypeID();

/*!
 *      @function QLThumbnailRequestCopyURL
 *      @abstract Returns the url of the file for the thumbnail request.
 *      @param thumbnail The thumbnail request.
 *      @result The url of the file for the thumbnail request.
 */
QL_EXPORT CFURLRef QLThumbnailRequestCopyURL(QLThumbnailRequestRef thumbnail);

/*!
 *      @function QLThumbnailRequestCopyOptions
 *      @abstract Returns the desired options for the thumbnail request.
 *      @param thumbnail The thumbnail request.
 *      @result The desired options for the thumbnail request.
 */
QL_EXPORT CFDictionaryRef QLThumbnailRequestCopyOptions(QLThumbnailRequestRef thumbnail);

/*!
 *      @function QLThumbnailRequestCopyContentUTI
 *      @abstract Returns the UTI for the thumbnail request.
 *      @param thumbnail The thumbnail request.
 *      @result The UTI of the content being thumbnailed, NULL if not available.
 */
QL_EXPORT CFStringRef QLThumbnailRequestCopyContentUTI(QLThumbnailRequestRef thumbnail);

/*!
 *      @function QLThumbnailRequestGetMaximumSize
 *      @abstract Returns the maximum desired size (in points) for the thumbnail request.
 *      @param thumbnail The thumbnail request.
 *      @result The maximum desired size (in points) for the thumbnail request.
 */
QL_EXPORT CGSize QLThumbnailRequestGetMaximumSize(QLThumbnailRequestRef thumbnail);

/*!
 *      @function QLThumbnailRequestGetGeneratorBundle
 *      @abstract Get the thumbnail request generator bundle.
 *      @param thumbnail The thumbnail request.
 */
QL_EXPORT CFBundleRef QLThumbnailRequestGetGeneratorBundle(QLThumbnailRequestRef thumbnail);

/*!
 *      @function QLThumbnailRequestSetDocumentObject
 *      @abstract Store some object in thumbnail request.
 *      @param thumbnail The thumbnail request.
 *      @param object The object representing the document
 *      @param callbacks Callbacks to retain/release/etc. the object.
 *      @discussion You can only call this function once per request.
 */
QL_EXPORT void QLThumbnailRequestSetDocumentObject(QLThumbnailRequestRef thumbnail, const void* object, const CFArrayCallBacks* callbacks) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLThumbnailRequestGetDocumentObject
 *      @abstract Get the object previously stored with QLThumbnailRequestSetDocumentObject.
 *      @param thumbnail The thumbnail request.
 *      @result The object representing the document
 */
QL_EXPORT const void* QLThumbnailRequestGetDocumentObject(QLThumbnailRequestRef thumbnail) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLThumbnailRequestSetImage
 *      @abstract Sets the thumbnail request response to image.
 *      @param thumbnail The thumbnail request.
 *      @param image The thumbnail image response.
 *      @param properties See possible properties below.
 */
QL_EXPORT void QLThumbnailRequestSetImage(QLThumbnailRequestRef thumbnail, CGImageRef image, CFDictionaryRef properties);

/*!
 *      @function QLThumbnailRequestSetImageWithData
 *      @abstract Sets the thumbnail request response to image data.
 *      @param thumbnail The thumbnail request.
 *      @param data The thumbnail image response as data. The image format should be supported by ImageIO
 *      @param properties See possible properties below. Additional useful properties: kCGImageSourceTypeIdentifierHint (see ImageIO documentation).
 */
QL_EXPORT void QLThumbnailRequestSetImageWithData(QLThumbnailRequestRef thumbnail, CFDataRef data, CFDictionaryRef properties);

/*!
 *      @function QLThumbnailRequestCreateContext
 *      @abstract Creates a graphic context to draw the thumbnail response in.
 *      @param thumbnail The thumbnail request.
 *      @param size Size in points of the context for the thumbnail response.
 *      @param isBitmap True if thumbnail contents is based on bitmap. size will then be interpreted as pixels, not points.
 *      @param properties See possible properties below.
 *      @result A graphic context to draw to.
 *      @discussion Once the thumbnail is fully drawn, you should call QLThumbnailRequestFlushContext().
 */
QL_EXPORT CGContextRef QLThumbnailRequestCreateContext(QLThumbnailRequestRef thumbnail, CGSize size, Boolean isBitmap, CFDictionaryRef properties);

/*!
 *      @function QLThumbnailRequestFlushContext
 *      @abstract Flushes the graphic context and creates the thumbnail image response.
 *      @param thumbnail The thumbnail request.
 *      @param context The graphic context created by QLThumbnailRequestCreateContext().
 */
QL_EXPORT void QLThumbnailRequestFlushContext(QLThumbnailRequestRef thumbnail, CGContextRef context);

/*!
 *      @function QLThumbnailRequestSetImageAtURL
 *      @abstract Sets the thumbnail request response to the image contained at url.
 *      @param thumbnail The thumbnail request.
 *      @param url The url to the thumbnail image response.
 *      @param properties Currently unused.
 */
QL_EXPORT void QLThumbnailRequestSetImageAtURL(QLThumbnailRequestRef thumbnail, CFURLRef url, CFDictionaryRef properties);

/*!
 *      @function QLThumbnailRequestSetThumbnailWithDataRepresentation
 *      @abstract Sets the thumbnail request response to the image produced by the equivalent preview representation.
 *      @param thumbnail The thumbnail request.
 *      @param data The content data.
 *      @param contentTypeUTI The contentTypeUTI for the preview representation.
 *      @param previewProperties Additional properties for the preview response.
 *      @param properties Currently unused.
 *      @discussion Currently supported UTIs are: none. This call only works if your generator is set to be run in the main thread
 */
QL_EXPORT void QLThumbnailRequestSetThumbnailWithDataRepresentation(QLThumbnailRequestRef thumbnail, CFDataRef data, CFStringRef contentTypeUTI, CFDictionaryRef previewProperties, CFDictionaryRef properties) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLThumbnailRequestSetThumbnailWithURLRepresentation
 *      @abstract Sets the thumbnail request response to the image produced by the equivalent preview representation.
 *      @param thumbnail The thumbnail request.
 *      @param url The url to the preview response.
 *      @param contentTypeUTI The contentTypeUTI for the preview representation.
 *      @param properties Additional properties for the preview response.
 *      @discussion Currently supported UTIs are: none. This call only works if your generator is set to be run in the main thread
 */
QL_EXPORT void QLThumbnailRequestSetThumbnailWithURLRepresentation(QLThumbnailRequestRef thumbnail, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef previewProperties, CFDictionaryRef properties) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLThumbnailRequestIsCancelled
 *      @abstract Returns wether the thumbnail request was cancelled or not.
 *      @param thumbnail The thumbnail request.
 *      @result true if the request was cancelled.
 */
QL_EXPORT Boolean QLThumbnailRequestIsCancelled(QLThumbnailRequestRef thumbnail);

/*!
 *      @constant kQLThumbnailPropertyExtensionKey
 *      @abstract Value should be a CFString. The extension is used as a badge when producing an icon.
 */
QL_EXPORT const CFStringRef kQLThumbnailPropertyExtensionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @constant kQLThumbnailPropertyExtensionKey
 *      @abstract Value should be a CGImage. The badge is used when producing an icon.
 */
QL_EXPORT const CFStringRef kQLThumbnailPropertyBadgeImageKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @constant kQLThumbnailPropertyExtensionKey
 *      @abstract Extends the security scope where Quick Look will accept to look at a file. Value is a path as CFString.
 *      @discussion Only useful when using QLThumbnailRequestSetImageAtURL() or QLThumbnailRequestSetThumbnailWithURLRepresentation().
 *                  By default, Quick Look will only accept files within the current document bundle.
 */
QL_EXPORT const CFStringRef kQLThumbnailPropertyBaseBundlePathKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#pragma mark Preview generator callback

/*!
 *      @typedef QLPreviewRequestRef
 *      This is the type of a reference to Preview requests.
 */
typedef struct CF_BRIDGED_TYPE(id) __QLPreviewRequest *QLPreviewRequestRef;

/*!
 *      @function QLPreviewRequestGetTypeID
 *      @abstract Returns the CoreFoundation type ID for QLPreviewRequests.
 */
QL_EXPORT CFTypeID QLPreviewRequestGetTypeID();

/*!
 *      @constant kQLPreviewPropertyDisplayNameKey
 *      @abstract Customizes Displayed name in the preview panel. This replaces the document's display name. Value is a CFString.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyDisplayNameKey; // useful to customize the title of the QuickLook panel

/*!
 *      @constant kQLPreviewPropertyWidthKey
 *      @abstract Gives the width (in points) of the preview. Value is a CFNumber.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyWidthKey;

/*!
 *      @constant kQLPreviewPropertyHeightKey
 *      @abstract Gives the height (in points) of the preview. Value is a CFNumber.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyHeightKey;

/*!
 *      @constant kQLPreviewPropertyBaseBundlePathKey
 *      @abstract Extends the security scope where Quick Look will accept to look at a file. Value is a path as CFString.
 *      @discussion Only useful when using QLPreviewRequestSetURLRepresentation().
 *                  By default, Quick Look will only accept files within the current document bundle.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyBaseBundlePathKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @constant kQLPreviewPropertyStringEncodingKey
 *      @abstract Gives the CFStringEncoding of the preview data if the preview type is plain text. Value is a CFNumber.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyStringEncodingKey;

typedef enum {
    kQLPreviewPDFStandardStyle						= 0,
    kQLPreviewPDFPagesWithThumbnailsOnRightStyle	= 3,
    kQLPreviewPDFPagesWithThumbnailsOnLeftStyle		= 4,
} QLPreviewPDFStyle;

/*!
 *      @constant kQLPreviewPropertyPDFStyleKey
 *      @abstract Specify the preferred way to display PDF content. Value is a CFNumber using QLPreviewPDFStyle values.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyPDFStyleKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @constant kQLPreviewOptionCursorKey
 *      @abstract Value is the same CFNumber passed by potential previous calls to generator's preview callback for the same document with kQLPreviewPropertyCursorKey.
 *      @discussion Use this value to provide more of the preview content.
 */
QL_EXPORT const CFStringRef kQLPreviewOptionCursorKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @constant kQLPreviewPropertyCursorKey
 *      @abstract Value should be a CFNumber. This value will be used to get more of the document's preview if necessary
 *                (and if the preview genererator returns kQLReturnHasMore)
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyCursorKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLPreviewRequestCopyURL
 *      @abstract Returns the url of the file for the preview request.
 *      @param preview The preview request.
 *      @result The url of the file for the preview request.
 */
QL_EXPORT CFURLRef QLPreviewRequestCopyURL(QLPreviewRequestRef preview);

/*!
 *      @function QLPreviewRequestCopyOptions
 *      @abstract Returns the desired options for the preview request.
 *      @param preview The preview request.
 *      @result The desired options for the preview request.
 */
QL_EXPORT CFDictionaryRef QLPreviewRequestCopyOptions(QLPreviewRequestRef preview);

/*!
 *      @function QLPreviewRequestCopyContentUTI
 *      @abstract Returns the UTI for the preview request.
 *      @param preview The preview request.
 *      @result The UTI of the content being previewed, NULL if not available.
 */
QL_EXPORT CFStringRef QLPreviewRequestCopyContentUTI(QLPreviewRequestRef preview);

/*!
 *      @function QLPreviewRequestGetGeneratorBundle
 *      @abstract Gets the preview request generator bundle.
 *      @param preview The preview request.
 */
QL_EXPORT CFBundleRef QLPreviewRequestGetGeneratorBundle(QLPreviewRequestRef preview);

/*!
 *      @function QLPreviewRequestSetDocumentObject
 *      @abstract Store some object in preview request.
 *      @param thumbnail The preview request.
 *      @param object The object representing the document
 *      @param callbacks Callbacks to retain/release/etc. the object.
 *      @discussion You can only call this function once per request.
 */
QL_EXPORT void QLPreviewRequestSetDocumentObject(QLPreviewRequestRef preview, const void* object, const CFArrayCallBacks* callbacks) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLPreviewRequestGetDocumentObject
 *      @abstract Get the object previously stored with QLPreviewRequestSetDocumentObject.
 *      @param preview The preview request.
 *      @result The object representing the document
 */
QL_EXPORT const void* QLPreviewRequestGetDocumentObject(QLPreviewRequestRef preview) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
 *      @function QLPreviewRequestIsCancelled
 *      @abstract Returns wether the preview request was cancelled or not.
 *      @param preview The preview request.
 *      @result true if the request was cancelled.
 */
QL_EXPORT Boolean QLPreviewRequestIsCancelled(QLPreviewRequestRef preview);

#pragma mark Set preview to some native type preview data

/*!
 * @function QLPreviewRequestSetDataRepresentation
 * @abstract Sets the preview response with the provided data.
 * @param preview The preview request.
 * @param data The content data.
 * @param contentTypeUTI The contentTypeUTI for the preview representation.
 * @param properties Additional properties for the preview response.
 * @discussion Currently supported UTIs are: kUTTypeImage, kUTTypePDF, kUTTypeHTML,
 *             kUTTypeXML, kUTTypePlainText, kUTTypeRTF, kUTTypeMovie, kUTTypeAudio,
 *             and "org.khronos.collada.digital-asset-exchange" (from OSX 10.9)
 */
QL_EXPORT void QLPreviewRequestSetDataRepresentation(QLPreviewRequestRef preview, CFDataRef data, CFStringRef contentTypeUTI, CFDictionaryRef properties);

/*!
 *      @function QLPreviewRequestSetURLRepresentation
 *      @abstract Sets the preview request response with contents at url.
 *      @param preview The preview request.
 *      @param url The url to the preview response.
 *      @param contentTypeUTI The contentTypeUTI for the preview representation.
 *      @param properties Additional properties for the preview response.
 *      @discussion Currently supported UTIs are: kUTTypeImage, kUTTypePDF, kUTTypeHTML,
 *                  kUTTypeXML, kUTTypePlainText, kUTTypeRTF, kUTTypeRTFD, kUTTypeMovie, kUTTypeAudio,
 *                  and "org.khronos.collada.digital-asset-exchange" (from OSX 10.9)
 */
QL_EXPORT void QLPreviewRequestSetURLRepresentation(QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef properties);

#pragma mark Draw preview in a context

/*!
 *      @function QLPreviewRequestCreateContext
 *      @abstract Creates a context to draw the preview in. Context should be flushed with QLPreviewRequestFlushContext()
 *      @param preview The preview request.
 *      @param size The size of the context.
 *      @param isBitmap true if preview is bitmap-based.
 *      @param properties Additional properties for the preview response.
 */
QL_EXPORT CGContextRef QLPreviewRequestCreateContext(QLPreviewRequestRef preview, CGSize size, Boolean isBitmap, CFDictionaryRef properties);

/*!
 *      @function QLPreviewRequestCreatePDFContext
 *      @abstract Creates a PDF context to draw the preview in, likely to be multi-pages. Context should be flushed with QLPreviewRequestFlushContext()
 *      @param preview The preview request.
 *      @param mediaBox The media box of the context. see CGPDFContextCreate().
 *      @param auxiliaryInfo The PDF auxiliary info. see CGPDFContextCreate().
 *      @param properties Additional properties for the preview response.
 */
QL_EXPORT CGContextRef QLPreviewRequestCreatePDFContext(QLPreviewRequestRef preview, const CGRect * mediaBox, CFDictionaryRef auxiliaryInfo, CFDictionaryRef properties);


/*!
 *      @function QLPreviewRequestFlushContext
 *      @abstract Flush the context and sets the preview response.
 *      @param preview The preview request.
 *      @param context context previously created by QLPreviewRequestCreateContext() or QLPreviewRequestCreatePDFContext().
 */

QL_EXPORT void QLPreviewRequestFlushContext(QLPreviewRequestRef preview, CGContextRef context);

#pragma mark Provide preview as Web content using QLPreviewRequestSetDataRepresentation

/*!
 *      @constant kQLPreviewPropertyMIMETypeKey
 *      @abstract Gives the web content or attachment mime type. For the main data, default is text/html. Value is a CFString.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyMIMETypeKey;

/*!
 *      @constant kQLPreviewPropertyTextEncodingNameKey
 *      @abstract Gives the web content or attachment text encoding. Use IANA encodings like UTF-8. Value is a CFString.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyTextEncodingNameKey;

/*!
 *      @constant kQLPreviewPropertyAttachmentDataKey
 *      @abstract Gives the attachment data. Value is a CFData.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyAttachmentDataKey;

/*!
 *      @constant kQLPreviewPropertyAttachmentsKey
 *      @abstract Gives the list of attachments (or sub-resources). Value is a CFDictionary.
 *      @discussion Keys are the attachment ids (CFStringRef) that can be referenced with "cid:id" URL and
 *                  Values are dictionaries using kQLPreviewPropertyAttachmentDataKey,
 *                  kQLPreviewPropertyMIMETypeKey and kQLPreviewPropertyTextEncodingNameKey keys.
 */
QL_EXPORT const CFStringRef kQLPreviewPropertyAttachmentsKey;

/*!
 *      @constant kQLPreviewContentIDScheme
 *      @abstract Is the "cid" URL scheme.
 */
QL_EXPORT const CFStringRef kQLPreviewContentIDScheme;

#pragma mark

/*
 * Definition of the Quick Look Generator interface.
 *
 */

// 5E2D9680-5022-40FA-B806-43349622E5B9
#define kQLGeneratorTypeID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault, 0x5E, 0x2D, 0x96, 0x80, 0x50, 0x22, 0x40, 0xFA, 0xB8, 0x06, 0x43, 0x34, 0x96, 0x22, 0xE5, 0xB9)
// 865AF5E0-6D30-4345-951B-D37105754F2D
#define kQLGeneratorCallbacksInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault, 0x86, 0x5A, 0xF5, 0xE0, 0x6D, 0x30, 0x43, 0x45, 0x95, 0x1B, 0xD3, 0x71, 0x05, 0x75, 0x4F, 0x2D)

#if defined(__COREFOUNDATION_CFPLUGINCOM__)
typedef struct {
    IUNKNOWN_C_GUTS;
    OSStatus    (*GenerateThumbnailForURL)(void *thisInterface, QLThumbnailRequestRef thumbnail, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options, CGSize maxSize);
    void        (*CancelThumbnailGeneration)(void *thisInterface, QLThumbnailRequestRef thumbnail);
    OSStatus    (*GeneratePreviewForURL)(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options);
    void        (*CancelPreviewGeneration)(void *thisInterface, QLPreviewRequestRef preview);
} QLGeneratorInterfaceStruct;
#endif

QL_EXTERN_C_END

#endif
