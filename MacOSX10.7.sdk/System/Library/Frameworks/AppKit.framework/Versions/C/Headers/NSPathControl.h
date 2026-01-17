/*
    NSPathControl.h
    Application Kit
    Copyright (c) 2005-2011, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>


#import <AppKit/NSControl.h>
#import <AppKit/NSPathCell.h>
#import <AppKit/NSDragging.h>

@class NSMutableArray, NSPathComponentCell, NSOpenPanel;
@protocol NSPathControlDelegate;

/* 
    NSPathControl

    The NSPathControl is closely tied to the NSPathCell and NSPathComponentCell. See those classes for more detailed information.
 
    To accept drag and drop, the NSPathControl automatically calls registerForDraggedTypes: with NSFilenamesPboardType and NSURLPboardType.
 
    When the URL value in the NSPathControl changes from an automatic drag and drop operation, or from the user selecting a new path via the open panel, the action is sent, but the clickedPathComponentCell will be nil.
*/
NS_CLASS_AVAILABLE(10_5, NA)
@interface NSPathControl : NSControl {
@private
    NSDragOperation _draggingSourceOperationMaskForLocal;
    NSDragOperation _draggingSourceOperationMaskForNonLocal;
    NSInteger _reserved;
    id _delegate;
    id _aux;
}

/* See NSPathCell for documentation on all the properties listed below. The NSPathControl directly calls the cell's methods.
*/

- (NSURL *)URL;
- (void)setURL:(NSURL *)url;

- (SEL)doubleAction;
- (void)setDoubleAction:(SEL)action;

- (NSPathStyle)pathStyle;
- (void)setPathStyle:(NSPathStyle)style;

- (NSPathComponentCell *)clickedPathComponentCell;

- (NSArray *)pathComponentCells;
- (void)setPathComponentCells:(NSArray *)cells;

/* The background color to be drawn; this is a cover method for the contained cell. NSControl will return the result from isOpaque from the contained cell. The NSPathCell in an NSPathControl will return YES from isOpaque if the backgroundColor of the cell has an alphaComponent of 1.0, and NO otherwise.
 */
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

/* Gets and sets the delegate for this control. The delegate is not retained.
*/
- (id <NSPathControlDelegate>)delegate;
- (void)setDelegate:(id <NSPathControlDelegate>)delegate;

/* Configures the default value returned from -draggingSourceOperationMaskForLocal:. An 'isLocal' value of YES indicates that 'mask' applies when the destination object is in the same application. An 'isLocal' value of NO indicates that 'mask' applies when the destination object in a destination object outside the receiver's application. By default, -draggingSourceOperationMaskForLocal: returns NSDragOperationEvery when 'isLocal' is YES, and NSDragOperationNone when 'isLocal' is NO.

*/
- (void)setDraggingSourceOperationMask:(NSDragOperation)mask forLocal:(BOOL)isLocal;

/* NSPathControl overrides the default NSView implementation of menu/setMenu: and forwards the method call to the cell.
 */
- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;

@end


@protocol NSPathControlDelegate <NSObject>

@optional

/* Optional dragging source support. This method is called when a drag is about to begin. This method must be implemented to allow dragging from the control. You can refuse to allow the drag to happen by returning NO, and allow it by returning YES. By default, 'pasteboard' automatically have the following types on it: NSStringPboardType, NSURLPboardType (if there is a URL value for the cell being dragged), and NSFilenamesPboardType (if the URL value returns YES from -isFileURL). You can customize the types placed on the pasteboard at this time, if desired.
*/
- (BOOL)pathControl:(NSPathControl *)pathControl shouldDragPathComponentCell:(NSPathComponentCell *)pathComponentCell withPasteboard:(NSPasteboard *)pasteboard;

/* Optional dragging destination support. This method is called when something is dragged over the control. This method can be implemented to allow dragging onto the control. The delegate method will be called even for instances that are "disabled" (ie: return NO from -isEnabled). Return NSDragOperationNone to refuse the drop, or anything else to accept it.

    If not implemented, and the control isEnabled, with the control's cell isEditable, the drop will be accepted if it contains an NSURLPboardType or NSFilenamesPboardType that conforms to the [cell allowedTypes].
*/
- (NSDragOperation)pathControl:(NSPathControl *)pathControl validateDrop:(id <NSDraggingInfo>)info;

/* Optional dragging destination support. In order to accept the dropped contents previously accepted from validateDrop:, you must implement this method. This method is called from -performDragOperation:. You should change the URL value based on the dragged information.

    If not implemented, and the control's cell isEditable, the drop will be accepted if it contains an NSURLPboardType or NSFilenamesPboardType that conforms to the [cell allowedTypes]. The cell's URL value will automatically be changed, and the action will be invoked.

*/
- (BOOL)pathControl:(NSPathControl *)pathControl acceptDrop:(id <NSDraggingInfo>)info;

/* The following two optional methods are described in NSPathCell's delegate. By default, the cell's delegate is set to the control, and the cell's delegate methods are delegated to the control's delegate.
*/

/* Called before the 'openPanel' is shown, but after the 'openPanel' has allowedFileTypes set to the cell's allowedTypes. At this time, you can further customize the 'openPanel' as required. This is only ever called when the style is set to NSPathStylePopUp.
*/
- (void)pathControl:(NSPathControl *)pathControl willDisplayOpenPanel:(NSOpenPanel *)openPanel;

/* Called before the 'menu' is shown. At this time, you can further customize the 'menu' as required, adding and removing items. This is only ever called when the style is set to NSPathStylePopUp.
*/
- (void)pathControl:(NSPathControl *)pathControl willPopUpMenu:(NSMenu *)menu;

@end

