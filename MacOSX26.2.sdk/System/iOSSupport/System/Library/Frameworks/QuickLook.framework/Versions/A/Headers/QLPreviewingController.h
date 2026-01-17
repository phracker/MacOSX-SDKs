#if (defined(USE_PUBLIC_QUICKLOOKUICORE_HEADERS) && USE_PUBLIC_QUICKLOOKUICORE_HEADERS) || !__has_include(<QuickLookUICore/QLPreviewingController.h>)
//
//  QLPreviewingController.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

@class QLPreviewReply;
@class QLFilePreviewRequest;
/**
 For view based previews, the view controller that implements the QLPreviewingController protocol must at least implement one of the two following methods:
 -[QLPreviewingController preparePreviewOfSearchableItemWithIdentifier:queryString:completionHandler:], to generate previews for Spotlight searchable items.
 -[QLPreviewingController preparePreviewOfFileAtURL:completionHandler:], to generate previews for file URLs.
 
 The main preview should be presented by the view controller implementing QLPreviewingController.
 Avoid presenting additional view controllers over your QLPreviewingController.
 For Catalyst compatibility, avoid using gesture recognizers that take interactions over large portions of the view to avoid collisions with standard macOS preview behaviors.
 Avoid holding the file open during the duration of the preview. If access to the file is necessary for interaction, it is best to keep the file open only for the duration of the interaction.
 
 For data-based previews, subclass QLPreviewProvider which conforms to this protocol.
 */
QL_EXPORT @protocol QLPreviewingController <NSObject>

@optional

/**
 @abstract
 Use this method to prepare the content of the view controller with the data that the searchable item represents.
 
 @discussion
 This method will be called only once. It will be called in the main thread before presenting the view controller.
 Heavy work potentially blocking the main thread should be avoided in this method.
 
 @param identifier The identifier of the CSSearchableItem the user interacted with in Spotlight.
 @param queryString The query string the user entered in Spotlight before interacting with the CSSearchableItem.
 @param handler The completion handler should be called whenever the view is ready to be displayed. A loading spinner will be shown until the handler is called.
 It can be called asynchronously after the method has returned.
 */
- (void)preparePreviewOfSearchableItemWithIdentifier:(NSString *)identifier queryString:(NSString * _Nullable)queryString completionHandler:(void (^)(NSError * _Nullable))handler NS_SWIFT_NAME(preparePreviewOfSearchableItem(identifier:queryString:completionHandler:));

/**
 @abstract
 Use this method to prepare the content of the view controller with the given file URL.

 @discussion
 This method will be called only once. It will be called in the main thread before presenting the view controller.
 Heavy work potentially blocking the main thread should be avoided in this method.
 
 @param url The URL of the file the user is about to preview.
 @param handler The completion handler should be called whenever the view is ready to be displayed. A loading spinner will be shown until the handler is called.
 It can be called asynchronously after the method has returned.
 */
- (void)preparePreviewOfFileAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable))handler NS_SWIFT_NAME(preparePreviewOfFile(at:completionHandler:));

/**
 @abstract Use this method to provide a QLPreviewReply that provides preview in the form of NSData, NSURL, PDFDocument, or a drawing into a context.
 @param request An object which contains information about the preview that should be provided. It contains the URL of the file to provide a preview for.
 @param handler Call the completion handler with a QLPreviewReply if you can provide a preview, or with an NSError if you cannot. If an error is passed or reply is nil, a generic preview will be provided instead. The handler can be called asynchronously after the method has returned.
 */
- (void)providePreviewForFileRequest:(QLFilePreviewRequest*)request completionHandler:(void (^)(QLPreviewReply * _Nullable reply, NSError * _Nullable error))handler NS_SWIFT_NAME(providePreview(for:completionHandler:));
@end

NS_ASSUME_NONNULL_END

#else
#import <QuickLookUICore/QLPreviewingController.h>
#endif
