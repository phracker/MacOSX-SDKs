//
//  QLPreviewView.h
//  Quick Look
//
//  Copyright 2007-2010 Apple Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

#include <QuickLook/QuickLook.h>

@protocol QLPreviewItem;
@class QLPreviewViewReserved;

NS_ENUM_AVAILABLE_MAC(10_7)
typedef NS_ENUM(NSUInteger, QLPreviewViewStyle) {
    QLPreviewViewStyleNormal = 0,
    QLPreviewViewStyleCompact = 1
};

/*!
 * @abstract A QLPreviewView shows a preview of an item.
 */

NS_CLASS_AVAILABLE_MAC(10_6)
@interface QLPreviewView : NSView
{
@private
    QLPreviewViewReserved * _reserved;
}

/*!
 * @discussion This is the designated initializer
 */
- (id)initWithFrame:(NSRect)frame style:(QLPreviewViewStyle)style AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 * @abstract Equivalent to initWithFrame:style: with style being QLPreviewViewStyleNormal
 */
- (id)initWithFrame:(NSRect)frame;

/*!
 * @abstract The item to preview.
 */
@property(retain) id <QLPreviewItem> previewItem;

/*!
 * @abstract Asks the Preview view to recompute the preview of the currently previewed item.
 */
- (void)refreshPreviewItem;

/*!
 * @abstract The current display state (e.g. visible page) of the preview item.
 * @discussion The display state is an opaque object used by the Preview Panel and Preview Views.
 */
@property(retain) id displayState;

/*!
 @abstract Closes the receiver, releasing the current preview item.
 Once the receiver has closed, it will no longer accept preview items.
 @discussion The application is required to call close when the receiver is no longer needed if shouldCloseWithWindow is NO.
 The close method will be called automatically when the window closes if shouldCloseWithWindow is YES.
 */
- (void)close;

/*!
 @abstract Set whether the receiver closes when its window closes (see discussion of -close).
 */
@property BOOL shouldCloseWithWindow;

@property BOOL autostarts;

@end
