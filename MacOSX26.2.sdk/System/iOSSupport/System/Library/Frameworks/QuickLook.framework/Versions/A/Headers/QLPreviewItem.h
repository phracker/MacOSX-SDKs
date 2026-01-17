#if (defined(USE_PUBLIC_QUICKLOOKUICORE_HEADERS) && USE_PUBLIC_QUICKLOOKUICORE_HEADERS) || !__has_include(<QuickLookUICore/QLPreviewItem.h>)
//
//  QLPreviewItem.h
//  Quick Look
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <QuickLook/QLBase.h>

/*!
 * @abstract The QLPreviewItem protocol declares the methods that a QLPreviewController instance uses to access the contents of a given item.
 */
QL_EXPORT @protocol QLPreviewItem <NSObject>

@required

/*!
 * @abstract The URL of the item to preview.
 * @discussion The URL must be a file URL.
 */
@property(readonly, nullable, nonatomic) NSURL * previewItemURL;

@optional

/*!
 * @abstract The item's title this will be used as apparent item title.
 * @discussion The title replaces the default item display name. This property is optional.
 */
@property(readonly, nullable, nonatomic) NSString * previewItemTitle;


@end

/*!
 * @abstract This category makes NSURL instances as suitable items for the Preview Controller.
 */
@interface NSURL (QLPreviewConvenienceAdditions) <QLPreviewItem>
@end

#else
#import <QuickLookUICore/QLPreviewItem.h>
#endif
