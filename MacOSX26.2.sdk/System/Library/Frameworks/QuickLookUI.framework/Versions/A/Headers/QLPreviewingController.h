//
//  QLPreviewingController.h
//  Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

@class QLPreviewReply;
@class QLFilePreviewRequest;

/// A type that defines a block used to load a Quick Look preview item.
typedef void(^QLPreviewItemLoadingBlock)(NSError * _Nullable error) API_DEPRECATED("Use void (^)(NSError * _Nullable) instead", macos(10.13,10.14)) API_UNAVAILABLE(ios, watchos, tvos);

/*
 For view based previews, the view controller that implements the QLPreviewingController protocol must at least implement one of the two following methods:
 -[QLPreviewingController preparePreviewOfSearchableItemWithIdentifier:queryString:completionHandler:], to generate previews for Spotlight searchable items.
 -[QLPreviewingController preparePreviewOfFileAtURL:completionHandler:], to generate previews for file URLs.
 
 The main preview should be presented by the view controller implementing QLPreviewingController.
 Avoid presenting additional view controllers over your QLPreviewingController.
 For Catalyst compatibility, avoid using gesture recognizers that take interactions over large portions of the view to avoid collisions with standard macOS preview behaviors.
 Avoid holding the file open during the duration of the preview. If access to the file is necessary for interaction, it is best to keep the file open only for the duration of the interaction.
 
 For data-based previews, subclass QLPreviewProvider which conforms to this protocol.
 */

/**
 A protocol for implementing a custom controller to create previews of files.
 
 A controller that implements the <doc://com.apple.documentation/documentation/quicklook/qlpreviewingcontroller> protocol must at least implement <doc://com.apple.documentation/documentation//quicklook/qlpreviewingcontroller/2882042-preparepreviewofsearchableitem> or <doc://com.apple.documentation/documentation/quicklook/qlpreviewingcontroller/2867936-preparepreviewoffile>.
 */
QL_EXPORT @protocol QLPreviewingController <NSObject>

@optional

/**
 Prepares the preview for a file by using the data from Spotlight’s searchable item.

 The operating system calls this method only once from the main thread before it presents the previewing controller. To avoid blocking the main thread, don’t perform long-running or resource-intensive work.
 - Parameters:
    - identifier: The identifier of the searchable item.
    - queryString: A search string to associate with the searchable item.
    - handler: A completion handler that notifies the platform that a preview is available. The operating system shows a loading spinner, so call the handler as soon as possible. You can call the completion handler asynchronously after returning from the callback.
 */
- (void)preparePreviewOfSearchableItemWithIdentifier:(NSString *)identifier queryString:(NSString * _Nullable)queryString completionHandler:(void (^)(NSError * _Nullable))handler NS_SWIFT_NAME(preparePreviewOfSearchableItem(identifier:queryString:completionHandler:));

/**
 Prepares the preview of a file at the specified file’s URL.

 The operating system calls this method only once from the main thread before it presents the previewing controller. To avoid blocking the main thread, don’t perform long-running or resource-intensive work.

 When preparing and displaying the view controller, avoid holding open a file descriptors while the user is previewing the file.

 - Parameters:
    - url: The URL of the file to preview.
    - handler: A completion handler that notifies the platform that a preview is available. The operating system shows a loading spinner, so call the handler as soon as possible. You can call the completion handler asynchronously after returning from the callback.
  */
- (void)preparePreviewOfFileAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable))handler NS_SWIFT_NAME(preparePreviewOfFile(at:completionHandler:));

/**
 Prepares the preview of a file identified within a file preview request.

 - Parameters:
    - request: The file preview request that identifies the content to preview.
    - handler: The closure to call with a <doc://com.apple.documentation/documentation/quicklook/qlpreviewreply> for the system to display as the preview.
 */
- (void)providePreviewForFileRequest:(QLFilePreviewRequest*)request completionHandler:(void (^)(QLPreviewReply * _Nullable reply, NSError * _Nullable error))handler NS_SWIFT_NAME(providePreview(for:completionHandler:));
@end

NS_ASSUME_NONNULL_END
