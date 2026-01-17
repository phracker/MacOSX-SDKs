/*
 *  QLPreviewPanel.h
 *  Quick Look
 *
 *  Copyright 2007-2010 Apple Inc. All rights reserved.
 *
 */

#import <AppKit/AppKit.h>

@class QLPreviewPanelReserved;

@protocol QLPreviewPanelDelegate;
@protocol QLPreviewPanelDataSource;
@protocol QLPreviewItem;

/*!
 * @abstract The QLPreviewPanel class implements the Preview Panel - a user interface object that displays the preview of a list of items.
 * @discussion Each application has only one instance of QLPreviewPanel. You can not subclass QLPreviewPanel.
 *
 *      QLPreviewPanel follows the responder chain and adapts to the first responder willing to control it. It uses a data source to
 *      gets its content. QLPreviewPanel can also have a delegate.
 */


/// A class that implements the Quick Look preview panel to display a preview of
/// a list of items.
///
/// Every application has a single shared instance of
/// ``QuickLookUI/QLPreviewPanel`` accessible through
/// ``QuickLookUI/QLPreviewPanel/sharedPreviewPanel``. The preview panel follows
/// the responder chain and adapts to the first responder willing to control it.
/// A preview panel controller provides the content through methods defined in
/// the ``QuickLookUI/QLPreviewPanelDataSource`` protocol.
///
/// You can’t subclass ``QuickLookUI/QLPreviewPanel``; you can, however,
/// customize its behavior using a ``QuickLookUI/QLPreviewPanel/delegate``. See
/// the ``QuickLookUI/QLPreviewPanelDelegate`` protocol for the methods to
/// customize a preview panel’s behavior.
NS_CLASS_AVAILABLE_MAC(10_6)
@interface QLPreviewPanel : NSPanel
{
@private
    QLPreviewPanelReserved * _reserved;
}

/*
 * Getting the Preview Panel
 */

/// Returns the shared Quick Look preview panel instance.
///
/// This method creates the panel if it doesn’t exist yet. Use
/// ``QuickLookUI/QLPreviewPanel/sharedPreviewPanelExists`` if you want to
/// determine whether the panel exists without creating it.
///
/// - Returns: The shared Quick Look preview panel instance for the application.
+ (QLPreviewPanel *)sharedPreviewPanel;

/// Returns a Boolean value that indicates whether the system has created a
/// shared Quick Look preview panel.
///
/// - Returns: <doc://com.apple.documentation/documentation/objectivec/yes> if
/// the shared Quick Look preview panel instance has been created, otherwise
/// <doc://com.apple.documentation/documentation/objectivec/no>.
+ (BOOL)sharedPreviewPanelExists;

/*
 * Getting the Preview Panel controller
 */

/*!
 * @abstract The current first responder accepting to control the Preview Panel.
 * @discussion You should never change preview panel state (delegate, datasource, etc.) if you are not controlling it.
 */

/// The current first responder accepting to control the preview panel.
///
/// You should never change the preview panel’s state (for example, its
/// delegate, datasource, and so on) if you aren’t controlling it.
@property(readonly) id currentController;

/*!
 * @abstract Asks the Preview Panel to update its current controller.
 * @discussion The Preview Panel automatically updates its controller (by searching the responder chain) whenever the main or key window changes. Invoke updateController if the responder chain changes without explicit notice.
 */

/// Asks the preview panel to update its current controller.
///
/// The preview panel automatically updates its controller (by searching the
/// responder chain) whenever the main or key window changes. You should only
/// invoke this method if the responder chain changes without explicit notice.
- (void)updateController;

/*
 * Accessing the previewed items
 */

/*!
 * @abstract The Preview Panel data source.
 */

/// The preview panel data source.
@property(assign) id <QLPreviewPanelDataSource> dataSource;

/*!
 * @abstract Asks the Preview Panel to reload its data from its data source.
 * @discussion This method does not refresh the visible item if it has not changed.
 */

/// Asks the preview panel to reload its data from its data source.
///
/// This method doesn’t refresh the visible item if it hasn’t changed.
- (void)reloadData;

/*!
 * @abstract Asks the Preview Panel to recompute the preview of the currently previewed item.
 */

/// Asks the preview panel to recompute the preview of the current preview item.
- (void)refreshCurrentPreviewItem;

/*!
 * @abstract The index of the currently previewed item in the preview panel or NSNotFound if there is none.
 */

/// The index of the current preview item.
///
/// The value is `NSNotFound` if there’s no current preview item.
@property NSInteger currentPreviewItemIndex;

/*!
 * @abstract The currently previewed item in the preview panel or nil if there is none.
 */

/// The currently previewed item.
///
/// The value is `nil` if there’s no current preview item.
@property(readonly) id <QLPreviewItem> currentPreviewItem;

/*!
 * @abstract The current panel's display state.
 */

/// The preview panel’s display state.
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

/*
 * Setting the delegate
 */

/*!
 * @abstract The Preview Panel delegate.
 */

/// The delegate object that controls the preview panel’s behavior.
///
/// The class assigned as the delegate should conform to the
/// ``QuickLookUI/QLPreviewPanelDelegate`` protocol.
@property(assign) id /** <QLPreviewPanelDelegate>*/ delegate;

/*
 * Managing Full screen mode
 */

/*!
 * @abstract Enters full screen mode.
 * @discussion If panel is not on-screen, the panel will go directly to full screen mode.
 */

/// Instructs the panel to enter full screen mode.
///
/// If the panel isn’t onscreen, the panel goes directly to full screen mode.
///
/// The panel chooses the appropriate screen depending on where the panel is or,
/// if entering fullscreen directly, where the panel zooms from.
///
/// - Parameters:
///   - screen: This parameter isn’t currently used—pass `nil`.
///
///   - options: This parameter isn’t currently used—pass `nil`.
///
/// - Returns: <doc://com.apple.documentation/documentation/objectivec/yes> if
/// the panel was able to enter full screen mode; otherwise,
/// <doc://com.apple.documentation/documentation/objectivec/no>.
- (BOOL)enterFullScreenMode:(NSScreen *)screen withOptions:(NSDictionary *)options;

/*!
 * @abstract Exits full screen mode.
 */

/// Instructs the panel to exit full screen mode.
///
/// - Parameters:
///   - options: This parameter isn’t used — pass `nil`.
- (void)exitFullScreenModeWithOptions:(NSDictionary *)options;

/*!
 * @abstract YES if the panel is currently open and in full screen mode.
 */

/// The property that indicates whether the panel is in full screen mode.
///
/// The value is <doc://com.apple.documentation/documentation/objectivec/yes> if
/// the panel is currently open and in full screen mode; otherwise it’s
/// <doc://com.apple.documentation/documentation/objectivec/no>.
@property(readonly, getter=isInFullScreenMode) BOOL inFullScreenMode;

@end


/*!
 * @abstract Methods to implement by any object in the responder chain to control the Preview Panel
 * @discussion QLPreviewPanel shows previews for items provided by the first object in the responder chain accepting to control it. You generally implement these methods in your window controller or delegate. You should never try to modify Preview panel state if you're not controlling the panel.
 */
@interface NSObject (QLPreviewPanelController)

/*!
 * @abstract Sent to each object in the responder chain to find a controller.
 * @param panel The Preview Panel looking for a controller.
 * @result YES if the receiver accepts to control the panel. You should never call this method directly.
 */
- (BOOL)acceptsPreviewPanelControl:(QLPreviewPanel *)panel;

/*!
 * @abstract Sent to the object taking control of the Preview Panel.
 * @param panel The Preview Panel the receiver will control.
 * @discussion The receiver should setup the preview panel (data source, delegate, binding, etc.) here. You should never call this method directly.
 */
- (void)beginPreviewPanelControl:(QLPreviewPanel *)panel;

/*!
 * @abstract Sent to the object in control of the Preview Panel just before stopping its control.
 * @param panel The Preview Panel that the receiver will stop controlling.
 * @discussion The receiver should unsetup the preview panel (data source, delegate, binding, etc.) here. You should never call this method directly.
 */
- (void)endPreviewPanelControl:(QLPreviewPanel *)panel;

@end


/*!
 * @abstract The QLPreviewPanelDataSource protocol declares the methods that the Preview Panel uses to access the contents of its data source object.
 */

/// A protocol that the Quick Look preview panel uses to access the contents of
/// its data source object.
@protocol QLPreviewPanelDataSource

@required

/*!
 * @abstract Returns the number of items that the preview panel should preview.
 * @param panel The Preview Panel.
 * @result The number of items.
 */

/// Returns the number of items that the preview panel should preview.
///
/// - Parameters:
///   - panel: The preview panel.
///
/// - Returns: The number of items the preview panel should display.
- (NSInteger)numberOfPreviewItemsInPreviewPanel:(QLPreviewPanel *)panel;

/*!
 * @abstract Returns the item that the preview panel should preview.
 * @param panel The Preview Panel.
 * @param index The index of the item to preview.
 * @result An item conforming to the QLPreviewItem protocol.
 */

/// Returns the item that the preview panel should preview at a given index.
///
/// - Parameters:
///   - panel: The preview panel.
///
///   - index: The index of the item to preview.
///
/// - Returns: The item that the preview panel should preview at index `index`.
- (id <QLPreviewItem>)previewPanel:(QLPreviewPanel *)panel previewItemAtIndex:(NSInteger)index;

@end


/*!
 * @abstract QLPreviewPanelDelegate is the protocol for the delegate of the Preview Panel object. You can implement these methods to perform custom tasks in response to events in the Preview Panel.
 */



/// A protocol for the delegate of the Quick Look preview panel.
///
/// You can implement these methods to perform custom tasks in response to
/// events in the preview panel.
@protocol QLPreviewPanelDelegate <NSWindowDelegate>

@optional

/*!
 * @abstract Invoked by the preview panel when it receives an event it doesn't handle.
 * @result Returns NO if the receiver did not handle the event.
 * 
 */

/// Handles an event that the preview panel receives, but doesn’t handle.
///
/// The preview panel invokes this optional method when it receives an event it
/// doesn’t handle.
///
/// - Parameters:
///   - panel: The preview panel.
///
///   - event: The event that the preview panel wasn’t able to handle.
///
/// - Returns: <doc://com.apple.documentation/documentation/objectivec/yes> if
/// the receiver handled the event; otherwise,
/// <doc://com.apple.documentation/documentation/objectivec/no>.
- (BOOL)previewPanel:(QLPreviewPanel *)panel handleEvent:(NSEvent *)event;

/*
 * Zoom effect
 */

/*!
 * @abstract Invoked when the preview panel opens or closes to provide a zoom effect.
 * @discussion Return NSZeroRect if there is no origin point, this will produce a fade of the panel. The coordinates are screen based.
 */

/// Returns the screen rectangle for a given preview item.
///
/// The system invokes this optional method when the preview panel opens or
/// closes to provide a zoom effect. You should return — in screen coordinates —
/// the rectangle that displays the specified preview item.
///
/// - Parameters:
///   - panel: The preview panel.
///
///   - item: The preview item for which the screen rectangle is required.
///
/// - Returns: The screen rectangle for the given preview item. Return
/// <doc://com.apple.documentation/documentation/foundation/nszerorect> if there
/// is no origin point (this will produce a fade of the panel).
- (NSRect)previewPanel:(QLPreviewPanel *)panel sourceFrameOnScreenForPreviewItem:(id <QLPreviewItem>)item;

/*!
 * @abstract Invoked when the preview panel opens or closes to provide a smooth transition when zooming.
 * @param contentRect The rect within the image that actually represents the content of the document. For example, for icons the actual rect is generally smaller than the icon itself. It should be expressed in points.
 * @discussion Return an image the panel will crossfade with when opening or closing. You can specify the actual "document" content rect in the image in contentRect.
 */

/// Returns the image to use for the transition zoom effect for a given item.
///
/// The system invokes this optional method when the preview panel opens or
/// closes to provide a smooth transition when zooming. The return type of the
/// function should be an instance of
/// <doc://com.apple.documentation/documentation/appkit/nsimage>.
///
/// - Parameters:
///   - panel: The preview panel.
///
///   - item: The item the system is previewing.
///
/// - contentRect: The rectangle within a preview image that actually represents
/// the content of the document. For icons, the actual rectangle is typically
/// smaller than the icon itself.
///
/// - Returns: The image to use for the transition zoom effect for the `item`.
- (id)previewPanel:(QLPreviewPanel *)panel transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(NSRect *)contentRect;

@end
