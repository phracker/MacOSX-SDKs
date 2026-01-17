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

NS_CLASS_AVAILABLE_MAC(10_6)
@interface QLPreviewPanel : NSPanel
{
@private
    QLPreviewPanelReserved * _reserved;
}

/*
 * Getting the Preview Panel
 */

/*!
 * @abstract Returns the QLPreviewPanel instance, creating it if it doesn’t exist yet.
 */
+ (QLPreviewPanel *)sharedPreviewPanel;

/*!
 * @abstract Returns YES if the shared Preview Panel has been created, NO if it hasn’t..
 */
+ (BOOL)sharedPreviewPanelExists;

/*
 * Getting the Preview Panel controller
 */

/*!
 * @abstract The current first responder accepting to control the Preview Panel.
 * @discussion You should never change preview panel state (delegate, datasource, etc.) if you are not controlling it.
 */
@property(readonly) id currentController;

/*!
 * @abstract Asks the Preview Panel to update its current controller.
 * @discussion The Preview Panel automatically updates its controller (by searching the responder chain) whenever the main or key window changes. Invoke updateController if the responder chain changes without explicit notice.
 */
- (void)updateController;

/*
 * Acessing the previewed items
 */

/*!
 * @abstract The Preview Panel data source.
 */
@property(assign) id <QLPreviewPanelDataSource> dataSource;

/*!
 * @abstract Asks the Preview Panel to reload its data from its data source.
 * @discussion This method does not refresh the visible item if it has not changed.
 */
- (void)reloadData;

/*!
 * @abstract Asks the Preview Panel to recompute the preview of the currently previewed item.
 */
- (void)refreshCurrentPreviewItem;

/*!
 * @abstract The index of the currently previewed item in the preview panel or NSNotFound if there is none.
 */
@property NSInteger currentPreviewItemIndex;

/*!
 * @abstract The currently previewed item in the preview panel or nil if there is none.
 */
@property(readonly) id <QLPreviewItem> currentPreviewItem;

/*!
 * @abstract The current panel's display state.
 */
@property(retain) id displayState;

/*
 * Setting the delegate
 */

/*!
 * @abstract The Preview Panel delegate.
 */
@property(assign) id /*<QLPreviewPanelDelegate>*/ delegate;

/*
 * Managing Full screen mode
 */

/*!
 * @abstract Enters full screen mode.
 * @discussion If panel is not on-screen, the panel will go directly to full screen mode.
 */
- (BOOL)enterFullScreenMode:(NSScreen *)screen withOptions:(NSDictionary *)options;

/*!
 * @abstract Exits full screen mode.
 */
- (void)exitFullScreenModeWithOptions:(NSDictionary *)options;

/*!
 * @abstract YES if the panel is currently open and in full screen mode.
 */
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
@protocol QLPreviewPanelDataSource

@required

/*!
 * @abstract Returns the number of items that the preview panel should preview.
 * @param panel The Preview Panel.
 * @result The number of items.
 */
- (NSInteger)numberOfPreviewItemsInPreviewPanel:(QLPreviewPanel *)panel;

/*!
 * @abstract Returns the item that the preview panel should preview.
 * @param panel The Preview Panel.
 * @param index The index of the item to preview.
 * @result An item conforming to the QLPreviewItem protocol.
 */
- (id <QLPreviewItem>)previewPanel:(QLPreviewPanel *)panel previewItemAtIndex:(NSInteger)index;

@end


/*!
 * @abstract QLPreviewPanelDelegate is the protocol for the delegate of the Preview Panel object. You can implement these methods to perform custom tasks in response to events in the Preview Panel.
 */


@protocol QLPreviewPanelDelegate <NSWindowDelegate>

@optional

/*!
 * @abstract Invoked by the preview panel when it receives an event it doesn't handle.
 * @result Returns NO if the receiver did not handle the event.
 * 
 */
- (BOOL)previewPanel:(QLPreviewPanel *)panel handleEvent:(NSEvent *)event;

/*
 * Zoom effect
 */

/*!
 * @abstract Invoked when the preview panel opens or closes to provide a zoom effect.
 * @discussion Return NSZeroRect if there is no origin point, this will produce a fade of the panel. The coordinates are screen based.
 */
- (NSRect)previewPanel:(QLPreviewPanel *)panel sourceFrameOnScreenForPreviewItem:(id <QLPreviewItem>)item;

/*!
 * @abstract Invoked when the preview panel opens or closes to provide a smooth transition when zooming.
 * @param contentRect The rect within the image that actually represents the content of the document. For example, for icons the actual rect is generally smaller than the icon itself. It should be expressed in points.
 * @discussion Return an image the panel will crossfade with when opening or closing. You can specify the actual "document" content rect in the image in contentRect.
 */
- (id)previewPanel:(QLPreviewPanel *)panel transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(NSRect *)contentRect;

@end
