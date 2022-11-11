//
//  QLPreviewReply.h
//  Quick Look
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && !defined(USE_PUBLIC_QUICKLOOK_HEADERS_CATALYST) && __has_include(<QuickLookSupport/QLPreviewReply.h>)
#import <QuickLookSupport/QLPreviewReply.h>
#else

#import <Foundation/Foundation.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract QLPreviewReplyAttachment is used to provide data for attachment in html data-based previews.
 */
API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLPreviewReplyAttachment:NSObject

/** The data content of an html preview*/
@property (readonly) NSData* data;

/** The content type of the attachment for an html preview*/
@property (readonly) UTType* contentType;

/**
 @abstract Create an attachment for html previews by providing the data and mime type of the attachment.
 @param data The data content of an html preview
 @param contentType The UTType of the attachment for an html preview
 */
- (instancetype)initWithData:(NSData*)data contentType:(UTType*)contentType;

@end

/**
 @abstract To provide a data-based preview, you have to return a QLPreviewReply object.
 */
API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLPreviewReply : NSObject

/** String encoding for text or html based previews. Defaults to NSUTF8StringEncoding. */
@property NSStringEncoding stringEncoding;

/** Attachments for HTML data previews. The keys of the dictionary are the attachment identifiers (eg foo) that can be referenced with the cid:id URL (eg cid:foo).*/
@property (copy) NSDictionary<NSString*, QLPreviewReplyAttachment*>* attachments;

/** Custom display title for the preview. If left as the empty string, QuickLook will use the file name.*/
@property (copy) NSString* title;

/**
 @abstract
 Use this method to provide a preview by drawing into a context.
 
 @param contextSize The size of your image.
 @param isBitmap Whether the context should be bitmap or vector.
 @param drawingBlock The preview should be drawn into the context passed to this block. The QLPreviewReply passed into this block is the same as the one created by this method and is provided for convenience for any further updates to its properties during the drawing block. Return YES if the preview was successfully drawn into the context. Return NO and populate error otherwise.
 */
- (instancetype)initWithContextSize:(CGSize)contextSize isBitmap:(BOOL)isBitmap drawingBlock:(BOOL (^)(CGContextRef context, QLPreviewReply * reply, NSError** error))drawingBlock;


/**
 @abstract
 Use this method to provide a preview by providing a URL to a file of a supported type.
 
 @param fileURL  A file URL representing a preview of the previewed URL. Currently supported types include: UTTypeImage, UTTypePDF, UTTypeHTML, UTTypeXML, UTTypePlainText, UTTypeRTF, UTTypeRTFD, UTTypeMovie, UTTypeAudio
 */
- (instancetype)initWithFileURL:(NSURL *)fileURL;

/**
 @abstract
 Use this method to provide a preview with data of a supported format.
 
 @param contentType The content type of the data.
 @param contentSize  A hint for the size you would like to display your content at. If your content has an intrinsic size built in, such as images and PDFs, that will be used as the final size, but providing the correct size here will allow QuickLook to present loading UI at the correct size before you are finished creating the data. QuickLook will use a default size if NSZeroSize is passed in.
 @param dataCreationBlock Create and return data representing the file preview. Supported types include: UTTypeImage, UTTypePDF, UTTypeHTML, UTTypeXML, UTTypePlainText, UTTypeRTF. Heavy lifting should be done inside of the dataCreationBlock instead of when creating the QLPreviewReply. The QLPreviewReply passed into this block is the same as the one created by this method and is provided for convenience for any further updates to its properties, such as attachments, during the data generation. Return the data if successful. Populate error if unsuccessful.
 */

- (instancetype)initWithDataOfContentType:(UTType *)contentType contentSize:(CGSize)contentSize dataCreationBlock:(NSData * _Nullable (^)(QLPreviewReply * reply, NSError ** error))dataCreationBlock;

@end

NS_ASSUME_NONNULL_END
#endif

#import <PDFKit/PDFKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QLPreviewReply (UI)

/**
 @abstract
 Use this method to provide a preview with a PDFDocument
 
 @param defaultPageSize The size of your pages in the document. If the page size varies, use the first page's size.
 @param documentCreationBlock Create and return the PDFDocument. Heavy lifting should be done inside of the documentCreationBlock instead of when creating the QLPreviewReply. The QLPreviewReply passed into this block is the same as the one created by this method and is provided for convenience for any further updates to its properties during document creation. Return the PDFDocument if successfully created. Populate error if unsuccessful.
 */
- (instancetype)initForPDFWithPageSize:(CGSize)defaultPageSize documentCreationBlock:(PDFDocument * _Nullable (^)(QLPreviewReply * reply, NSError ** error))documentCreationBlock;

@end

NS_ASSUME_NONNULL_END
