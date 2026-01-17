//
//  QLPreviewingController.h
//  QuickLook
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

typedef void(^QLPreviewItemLoadingBlock)(NSError * _Nullable error);


QL_EXPORT @protocol QLPreviewingController <NSObject>

/**
 @abstract
 Use this method to prepare the content of the view controller with the data that the searchable item represents.
 
 @discussion
 This method will be called only once. It will be called in the main thread before presenting the view controller.
 Heavy work potentially blocking the main thread should be avoided in this method.
 
 @param identifier The identifier of the CSSearchableItem the user interacted with in Spotlight.
 @param handler The completion handler should be called whenever the view is ready to be displayed. A loading spinner will be shown until the handler is called.
 It can be called asynchronously after the method has returned.
 */
- (void)preparePreviewOfSearchableItemWithIdentifier:(NSString*)identifier queryString:(NSString *)queryString completionHandler:(QLPreviewItemLoadingBlock)handler;

@end

NS_ASSUME_NONNULL_END
