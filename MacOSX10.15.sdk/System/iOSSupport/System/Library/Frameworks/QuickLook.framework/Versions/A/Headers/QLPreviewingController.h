//
//  QLPreviewingController.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 The controller that implements the QLPreviewingController protocol must at least implement one of the two following methods:
 -[QLPreviewingController preparePreviewOfSearchableItemWithIdentifier:queryString:completionHandler:], to generate previews for Spotlight searchable items.
 -[QLPreviewingController preparePreviewOfFileAtURL:completionHandler:], to generate previews for file URLs.
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

@end

NS_ASSUME_NONNULL_END
