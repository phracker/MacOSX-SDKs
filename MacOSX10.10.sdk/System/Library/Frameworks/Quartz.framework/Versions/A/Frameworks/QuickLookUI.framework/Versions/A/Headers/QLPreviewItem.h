//
//  QLPreviewItem.h
//  Quick Look
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * @abstract The QLPreviewItem protocol declares the methods that a QLPreviewPanel  instance uses to access the contents of a given item.
 */
NS_AVAILABLE_MAC(10_6)
@protocol QLPreviewItem <NSObject>

@required

/*!
 * @abstract The URL of the item to preview.
 * @discussion The URL must be a file URL. Return nil if the item is not available for preview (The Preview Panel or View will then display the Loading view).
 */
@property(readonly) NSURL * previewItemURL;

@optional

/*!
 * @abstract The item's title this will be used as apparent item title.
 * @discussion The title replaces the default item display name. This property is optional.
 */
@property(readonly) NSString * previewItemTitle;

/*!
 * @abstract The preview display state (e.g.: visible page).
 * @discussion The display state is an opaque object used by the Preview Panel and Preview Views. This property is optional.
 */
@property(readonly) id previewItemDisplayState;

@end

/*!
 * @abstract This category makes NSURL instances as suitable items for the Preview Panel or a Preview View.
 */
@interface NSURL (QLPreviewConvenienceAdditions) <QLPreviewItem>
@end
