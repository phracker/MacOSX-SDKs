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
/// Styles for a Preview View.
typedef NS_ENUM(NSUInteger, QLPreviewViewStyle) {
    
    /// Provides the default preview style for larger, full-sized previews.
    ///
    /// The default style for a ``QuickLookUI/QLPreviewView`` object. Use this
    /// style should for larger, full-size previews.
    QLPreviewViewStyleNormal = 0,

    /// Provides a compact preview style suited for smaller previews or inspectors.
    ///
    /// A more compact style for a ``QuickLookUI/QLPreviewView`` object. Use this
    /// style for smaller previews or inspectors.
    QLPreviewViewStyleCompact = 1
};

/*!
 * @abstract A QLPreviewView shows a preview of an item.
 */


/// A Quick Look preview of an item that you can embed into your view hierarchy.
NS_CLASS_AVAILABLE_MAC(10_6)
@interface QLPreviewView : NSView
{
@private
    QLPreviewViewReserved * _reserved;
}

/*!
 * @discussion This is the designated initializer
 */

/// Creates a preview view with the provided frame and style.
///
/// This is the designated initializer for the `QLPreviewView` class.
///
/// - Parameters:
///   - frame: The frame rectangle for the initialized `QLPreviewView` object.
///   - style: The desired style for the `QLPreviewView` object. For a list of
/// possible styles, see ``QuickLookUI/QLPreviewViewStyle``.
///
/// - Returns: Returns a `QLPreviewView` object with the designated frame and
/// style.
- (id)initWithFrame:(NSRect)frame style:(QLPreviewViewStyle)style AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 * @abstract Equivalent to initWithFrame:style: with style being QLPreviewViewStyleNormal
 */

/// Creates a preview view with the provided frame.
///
/// Calling this method is equivalent to calling
/// ``QuickLookUI/QLPreviewView/initWithFrame:style:`` with the `style`
/// parameter being ``QuickLookUI/QLPreviewViewStyle/QLPreviewViewStyleNormal``.
///
/// - Parameters:
///   - frame: The frame rectangle for the initialized `QLPreviewView` object.
///
/// - Returns: Returns a `QLPreviewView` object with the designated frame and
/// the default style.
- (id)initWithFrame:(NSRect)frame;

/*!
 * @abstract The item to preview.
 */

/// The item to preview.
///
/// Quick Look requires Items you wish to conform to the
/// <doc://com.apple.documentation/documentation/quicklook/qlpreviewitem>
/// protocol. When you set this property, the ``QuickLookUI/QLPreviewView``
/// loads the preview asynchronously. Due to this asynchronous behavior, don’t
/// assume that the preview is ready immediately after assigning it to this
/// property.
@property(retain) id <QLPreviewItem> previewItem;

/*!
 * @abstract Asks the Preview view to recompute the preview of the currently previewed item.
 */

/// Updates the preview to display the currently previewed item.
///
/// When you modify the object that the
/// ``QuickLookUI/QLPreviewView/previewItem`` property points to, call this
/// method to generate and display the new preview.
- (void)refreshPreviewItem;

/*!
 * @abstract The current display state (e.g. visible page) of the preview item.
 * @discussion The display state is an opaque object used by the Preview Panel and Preview Views.
 */

/// The current display state of the
/// <doc://com.apple.documentation/documentation/quicklookui/qlpreviewview/1504747-previewitem>.
///
/// This property is an opaque object that Quick Look uses to get and set the
/// current display state of the preview. The display state could be, for
/// example, the currently displayed page, the zoom factor on an image, or the
/// position in a movie.
///
/// You can use this property to get and save the current display state of the
/// preview before switching to another. This saving allows you to restore a
/// preview later on when the user switches back to it.
@property(retain) id displayState;

/*!
 @abstract Closes the receiver, releasing the current preview item.
 Once the receiver has closed, it will no longer accept preview items.
 @discussion The application is required to call close when the receiver is no longer needed if shouldCloseWithWindow is NO.
 The close method will be called automatically when the window closes if shouldCloseWithWindow is YES.
 */

/// Closes the view, releasing the current preview item.
///
/// Once a ``QuickLookUI/QLPreviewView`` is closed, it won’t accept any more
/// preview items. You only need to call this method if
/// ``QuickLookUI/QLPreviewView/shouldCloseWithWindow`` is set to
/// <doc://com.apple.documentation/documentation/objectivec/no>. If you don’t
/// close a ``QuickLookUI/QLPreviewView`` when you are done using it, your app
/// will leak memory.
- (void)close;

/*!
 @abstract Set whether the receiver closes when its window closes (see discussion of -close).
 */

/// A Boolean value that determines whether the preview should close when its
/// window closes.
///
/// The default value of this property is
/// <doc://com.apple.documentation/documentation/objectivec/yes>, which means
/// that the preview automatically closes when its window closes. If you set
/// this property to
/// <doc://com.apple.documentation/documentation/objectivec/no>, close the
/// preview by calling the ``QuickLookUI/QLPreviewView/close`` method when
/// finished with it. Once you close a ``QuickLookUI/QLPreviewView``, it won’t
/// accept any more preview items.
@property BOOL shouldCloseWithWindow;


/// A Boolean value that determines whether the preview starts automatically.
///
/// Set this property to allow previews of movie files to start playback
/// automatically when displayed.
@property BOOL autostarts;

@end
