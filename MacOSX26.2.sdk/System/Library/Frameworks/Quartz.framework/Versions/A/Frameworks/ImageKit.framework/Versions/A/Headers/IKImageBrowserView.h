//
//  IKImageBrowserView.h
//  ImageKit
//
//  Copyright 2006 Apple. All rights reserved.
//

/*!
	@header IKImageBrowserView
    IKImageBrowserView is a view that can display and browse a large amount of images and movies.
*/

#import <AppKit/AppKit.h>
#import <ImageKit/ImageKitBase.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class IKImageBrowserView;
@class IKImageBrowserCell;


/*
 Mask for cells appearance style bitfield
 */
enum{
	IKCellsStyleNone              =0,
	IKCellsStyleShadowed          =1,
	IKCellsStyleOutlined          =2,
	IKCellsStyleTitled            =4,
	IKCellsStyleSubtitled         =8
};

/*
 enum for group style attibute (see below)
 */
enum{
	IKGroupBezelStyle=0,
	IKGroupDisclosureStyle,
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/*
 enum for dropOperation
 */
typedef enum
{
	IKImageBrowserDropOn=0,
	IKImageBrowserDropBefore=1,
}IKImageBrowserDropOperation;
#endif


/*!
  @category NSObject (IKImageBrowserDataSource)
  @abstract The IKImageBrowserDataSource informal protocol declares the methods that an instance of IKImageBrowserView uses to access the contents of its data source object.
*/
@interface NSObject (IKImageBrowserDataSource)

//-- required methods
/*! 
  @method numberOfItemsInImageBrowser:
  @abstract Returns the number of records managed for aBrowser by the data source object (required).
  @discussion An instance of IKImageView uses this method to determine how many cells it should create and display. 
*/
- (NSUInteger) numberOfItemsInImageBrowser:(IKImageBrowserView *) aBrowser;

/*! 
  @method imageBrowser:itemAtIndex:
  @abstract Returns an object for the record in aBrowser corresponding to index <i>index</i> (required).
  @discussion The returned object must implement the required methods of <i>IKImageBrowserItem</i>. 
*/
- (id /*IKImageBrowserItem*/) imageBrowser:(IKImageBrowserView *) aBrowser itemAtIndex:(NSUInteger)index;

//-- optional methods
/*! 
  @method imageBrowser:removeItemsAtIndexes:
  @abstract Invoked by the image browser after it has been determined that a remove operation should be applied (optional)
  @discussion The data source should update itself (usually by removing this indexes).  
*/
- (void) imageBrowser:(IKImageBrowserView *) aBrowser removeItemsAtIndexes:(NSIndexSet *) indexes; 
/*! 
  @method imageBrowser:moveItemsAtIndexes:toIndex:
  @abstract Invoked by the image browser after it has been determined that a reordering operation should be applied (optional).
  @discussion The data source should update itself (usually by reordering its elements).  
*/
- (BOOL) imageBrowser:(IKImageBrowserView *) aBrowser moveItemsAtIndexes: (NSIndexSet *)indexes toIndex:(NSUInteger)destinationIndex;

/*!
	@method imageBrowser:writeItemsAtIndexes:toPasteboard:
	@abstract This method is called after it has been determined that a drag should begin, but before the drag has been started. 'itemIndexes' contains the indexes that will be participating in the drag. Return the number of items effectively written to the pasteboard.
	@discussion optional - drag and drop support
*/
- (NSUInteger) imageBrowser:(IKImageBrowserView *) aBrowser writeItemsAtIndexes:(NSIndexSet *) itemIndexes toPasteboard:(NSPasteboard *)pasteboard;

/*!
	@method numberOfGroupsInImageBrowser:
	@abstract Returns the number of groups
	@discussion this method is optional
*/
- (NSUInteger) numberOfGroupsInImageBrowser:(IKImageBrowserView *) aBrowser;

/*!
	@method imageBrowser:groupAtIndex:
	@abstract Returns the group at index 'index'
	@discussion A group is defined by a dictionay. Keys for this dictionary are defined below.
*/
- (NSDictionary *) imageBrowser:(IKImageBrowserView *) aBrowser groupAtIndex:(NSUInteger) index;

@end


/*!
  @category NSObject (IKImageBrowserItem)
  @abstract The IKImageBrowserItem informal protocol declares the methods that an instance of IKImageBrowserView uses to access the contents of its data source for a given item.
  @discussion Some of the methods in this protocol, such as <i>image</i> are called very frequently, so they must be efficient.
*/
@interface NSObject (IKImageBrowserItem)

/*! 
  @method imageUID
  @abstract Returns a unique string that identify this data source item (required).
  @discussion The image browser uses this identifier to keep the correspondance between its cache and the data source item  
*/
- (NSString *)  imageUID;  /* required */

/*! 
  @method imageRepresentationType
  @abstract Returns the representation of the image to display (required).
  @discussion Keys for imageRepresentationType are defined below.
*/
- (NSString *) imageRepresentationType; /* required */

/*! 
  @method imageRepresentation
  @abstract Returns the image to display (required). Can return nil if the item has no image to display.
*/
- (id) imageRepresentation; /* required */

/*! 
  @method imageVersion
  @abstract Returns a version of this item. The receiver can return a new version to let the image browser knows that it shouldn't use its cache for this item
*/
- (NSUInteger) imageVersion;

/*! 
  @method imageTitle
  @abstract Returns the title to display as a NSString. Use setValue:forKey: with IKImageBrowserCellsTitleAttributesKey on the IKImageBrowserView instance to set text attributes.
*/
- (NSString *) imageTitle;

/*! 
  @method imageSubtitle
  @abstract Returns the subtitle to display as a NSString. Use setValue:forKey: with IKImageBrowserCellsSubtitleAttributesKey on the IKImageBrowserView instance to set text attributes.
*/
- (NSString *) imageSubtitle;

/*! 
  @property selectable
  @abstract Returns whether this item is selectable. 
  @discussion The receiver can implement this methods to forbid selection of this item by returning NO.
*/
@property (readonly, getter=isSelectable) BOOL selectable;

@end


/*! 
  @class IKImageBrowserView
  @abstract An IKImageBrowserView object is a view that display and browse images and movies. It supports scrolling and zooming.  
  @discussion The IKImageBrowserView is deprecated. Please switch to NSCollectionView.
 */
IK_API_DEPRECATED("Deprecated - Please use NSCollectionView instead", macos(10.5, 10.14))
@interface IKImageBrowserView : NSView <NSDraggingSource> {
@private

    IBOutlet __weak id                            _dataSource;
    IBOutlet __weak id /*<NSDraggingDestination>*/_dragDestinationDelegate;
    IBOutlet __weak NSScroller*                   _verticalScroller;
    IBOutlet __weak NSScroller*                   _horizontalScroller;
    IBOutlet __weak id                            _delegate;

    void*                                         _reserved;
}
@end

/*!
  @category IKImageBrowserView (IKMainMethods)
*/
@interface IKImageBrowserView (IKMainMethods)

/*! 
  @method initWithFrame:
  @abstract Initializes and returns a newly allocated IKImageBrowserView object with a specified frame rectangle.
  @param frame The frame rectangle for the created view object. 
*/
- (id) initWithFrame:(NSRect) frame;

/*!
  @property datasource
  @abstract The receiver's data source. the data source is not retained by the receiver.
*/
@property (assign) IBOutlet id /* <IKImageBrowserDataSource> */ dataSource;

/*!
  @method reloadData
  @abstract Marks the receiver as needing redisplay, so it will reload the data and draw the new values.
*/
- (void) reloadData;

/*!
  @property delegate
  @abstract The receiver's delegate. aDelegate is expected to implement the IKImageBrowserDelegate informal protocol.
*/
@property (assign) IBOutlet id delegate;

@end


/*!
  @category IKImageBrowserView (IKAppearance)
*/
@interface IKImageBrowserView (IKAppearance)

/*! 
  @method setCellsStyleMask:
  @abstract Defines the cells appearance style.
  @param mask An integer bit mask; see the discussion below.
  @discussion mask can be specified by combining any of the options below using the C bitwise OR operator 
*/
- (void)  setCellsStyleMask:(NSUInteger) mask;

/*! 
  @method cellsStyleMask
  @abstract Return the cells appearance style mask.
*/
- (NSUInteger) cellsStyleMask;


/*! 
  @method setConstrainsToOriginalSize:
  @abstract Sets whether the receiver constraints the cells's image to their original size. Default is NO.
*/
- (void) setConstrainsToOriginalSize: (BOOL) flag;
/*! 
  @method constrainsToOriginalSize
  @abstract Returns whether the receiver constraints the cells's image to their original size.
*/
- (BOOL) constrainsToOriginalSize;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/*! 
 @method setBackgroundLayer:
 @abstract Specifies the receiver’s background layer.
 */
- (void) setBackgroundLayer:(CALayer *) aLayer;

/*! 
 @method backgroundLayer
 @abstract Provides the receiver’s background layer.
 */
- (CALayer *) backgroundLayer;


/*! 
 @method setForegroundLayer:
 @abstract Specifies the receiver’s foreground layer.
 */
- (void) setForegroundLayer:(CALayer *) aLayer;

/*! 
 @method foregroundLayer
 @abstract Provides the receiver’s foreground layer.
 */
- (CALayer *) foregroundLayer;


/*! 
 @method newCellForRepresentedItem:
 @abstract Returns the cell to use for the specified item. The returned cell should not be autoreleased.
 @param The item that the returned cell will represent.
 @discussion Subclasses can override this method to customize the appearance of the cell that will represent "anItem".
 */
- (IKImageBrowserCell *) newCellForRepresentedItem:(id /* <IKImageBrowserItem> */) anItem;


/*! 
 @method cellForItemAtIndex:
 @abstract Returns the cell at the specified index.
 @discussion Subclasses must not override this method.
 */
- (IKImageBrowserCell *) cellForItemAtIndex:(NSUInteger) index;

#endif


@end


/*!
  @category IKImageBrowserView (IKBrowsing)
*/
@interface IKImageBrowserView (IKBrowsing)

/*! 
  @method setZoomValue:
  @abstract Sets the zoom value to <i>aValue</i>.
  @discussion This value should be greater or equal to zero and less or equal than one. A zoom value of zero corresponds to the minimum size (40x40 pixels), A zoom value of one means images fit the browser bounds. Other values are interpolated.
*/
- (void) setZoomValue:(float)aValue; 

/*! 
  @method zoomValue
  @abstract Returns the current zoom value.
*/
- (float) zoomValue;

/*!
  @method setContentResizingMask
  @abtract Determines how the receiver resize its content when zooming.
  @discussion mask can be specified by combining any of the following options using the C bitwise OR operator:NSViewWidthSizable NSViewHeightSizable, other values are ignored.
*/
- (void) setContentResizingMask:(NSUInteger) mask;

/*!
  @method setContentResizingMask
  @abtract Returns the receiver’s content resizing mask, which determines how it’s content is resized while zooming.
*/
- (NSUInteger) contentResizingMask;

/*!
  @method scrollIndexToVisible:
  @abstract Scrolls the receiver so the item at the specified index is visible.
*/
- (void) scrollIndexToVisible:(NSInteger) index;

/*!
  @method setCellSize:
  @abstract sets the size of the cells to size
*/
- (void) setCellSize:(NSSize) size;

/*!
  @method setCellSize:
  @abstract Returns the size of the cells
*/
- (NSSize) cellSize;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/*! 
 @method intercellSpacing
 @abstract Returns the spacing between cells in the image browser.
 */
- (NSSize) intercellSpacing;

/*! 
 @method setIntercellSpacing:
 @abstract Sets the spacing between cells in the matrix.
 @param aSize The vertical and horizontal spacing to use between cells in the receiver. By default, both values are 10.0 in the receiver’s coordinate system.
 */
- (void)setIntercellSpacing:(NSSize)aSize;
#endif

/*!
  @method indexOfItemAtPoint:
  @abstract Returns the item at the specified location or NSNotFound if no item at this location.
*/
- (NSInteger) indexOfItemAtPoint: (NSPoint)point;

/*!
  @method itemFrameAtIndex:
  @abstract Returns the frame rectangle of the item that would be drawn at the specified location.
*/
- (NSRect) itemFrameAtIndex: (NSInteger)index;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/*! 
 @method visibleItemIndexes
 @abstract Returns indexes of the receiver’s currently visible items.
 */
- (NSIndexSet *) visibleItemIndexes;


/*! 
 @method rowIndexesInRect:
 @abstract Returns the indexes of the receiver’s rows that intersect the specified rectangle.
 */
- (NSIndexSet *) rowIndexesInRect:(NSRect) rect;

/*! 
 @method columnIndexesInRect:
 @abstract Returns the indexes of the receiver’s columns that intersect the specified rectangle.
 */
- (NSIndexSet *) columnIndexesInRect:(NSRect) rect;

/*! 
 @method rectOfColumn:
 @abstract Returns the rectangle containing the column at a given index.
 @param columnIndex The index of a column in the receiver.
 */
- (NSRect) rectOfColumn:(NSUInteger) columnIndex;

/*! 
 @method rectOfRow:
 @abstract Returns the rectangle containing the row at a given index.
 @param rowIndex The index of a row in the receiver.
 */
- (NSRect) rectOfRow:(NSUInteger) rowIndex;

/*! 
 @method numberOfRows
 @abstract Returns the number of rows in the receiver.
 */
- (NSUInteger)numberOfRows;

/*! 
 @method numberOfColumns
 @abstract Returns the number of columns in the receiver.
 */
- (NSUInteger)numberOfColumns;


/*! 
 @method setCanControlQuickLookPanel:
 @abstract Sets whether the receiver can automatically take control of the Quick Look panel.
 @param flag if YES, KImageBrowser can take control of the Quick Look panel automatically whenever it becomes first responder. This means that it provides the spacebar key store to open/close Quick Look panel and sets itself as the panel's datasource and delegate.
 @discussion default value is NO. IKImageBrowserView's datasource items should provide file paths or URLs as their representation (see IKImageBrowserItem protocol).
 */
- (void) setCanControlQuickLookPanel:(BOOL)flag;

/*! 
 @method canControlQuickLookPanel
 @abstract Returns a Boolean value that indicates whether the receiver can automatically take control of the Quick Look panel.
 */
- (BOOL) canControlQuickLookPanel;

#endif

@end


/*!
  @category IKImageBrowserView (IKSelectionReorderingAndGrouping)
*/
@interface IKImageBrowserView (IKSelectionReorderingAndGrouping)

/*! 
  @method selectionIndexes
  @abstract Returns the indexes of the selected cells
*/
- (NSIndexSet *) selectionIndexes;
/*! 
  @method setSelectionIndexes:byExtendingSelection:
  @abstract Selects cells at indexes <i>indexes</i>. If <i>extendSelection</i> is YES it extends the current selection, otherwise it replaces the current selection.
*/
- (void) setSelectionIndexes:(NSIndexSet *) indexes byExtendingSelection:(BOOL) extendSelection;

/*! 
  @method setAllowsMultipleSelection:
  @abstract Controls whether the user can select more than one cell at a time. 
*/  
- (void) setAllowsMultipleSelection: (BOOL) flag;
/*! 
  @method allowsMultipleSelection
  @abstract Returns YES if the receiver allows the user to select more than one cell at a time, NO otherwise. 
*/
- (BOOL) allowsMultipleSelection;

/*! 
  @method setAllowsMultipleSelection:
  @abstract Controls whether the receiver allows zero cell to be selected. 
*/  
- (void) setAllowsEmptySelection: (BOOL) flag;
/*! 
  @method setAllowsEmptySelection
  @abstract Returns YES if the receiver allows the user to select zero cell, NO otherwise. 
*/
- (BOOL) allowsEmptySelection;

/*! 
  @method setAllowsReordering:
  @abstract Controls whether the user can reorder items. 
*/  
- (void) setAllowsReordering: (BOOL) flag;
/*! 
  @method allowsReordering
  @abstract Returns YES if the receiver allows the user to reorder items, NO otherwise. 
*/
- (BOOL) allowsReordering;

/*! 
  @method setAnimates:
  @abstract Controls whether the receiver animate reordering and changes of the data source. 
*/  
- (void) setAnimates: (BOOL) flag;
/*! 
  @method animates
  @abstract Returns YES if the receiver animate changes of the data source, NO otherwise. 
*/
- (BOOL) animates;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

/* Group Control */
/*! 
  @method expandGroupAtIndex:
  @abstract Expands group at index 'index' if it is not already expanded; otherwise, does nothing.
*/
- (void) expandGroupAtIndex:(NSUInteger) index;

/*! 
  @method collapseGroupAtIndex:
  @abstract Collapse group at index 'index' if it is expanded; otherwise, does nothing.
*/
- (void) collapseGroupAtIndex:(NSUInteger) index;

/*! 
  @method isGroupExpandedAtIndex:
  @abstract Returns YES if the group at index 'index' is expanded.
*/
- (BOOL) isGroupExpandedAtIndex:(NSUInteger) index;

#endif

@end


/*!
  @category IKImageBrowserView (IKDragNDrop)
*/
@interface IKImageBrowserView (IKDragNDrop)

/*!
  @method setDraggingDestinationDelegate:
  @abstract Sets the receiver's dragging destination delegate to <i>delegate</i>.
*/
- (void) setDraggingDestinationDelegate:(id /*NSDraggingDestination*/) delegate;
/*!
  @method draggingDestinationDelegate
  @abstract Returns the receiver's dragging destination delegate.
*/
- (id) draggingDestinationDelegate;
/*!
  @method indexAtLocationOfDroppedItem
  @abstract Returns the index of the cell where the drop operation occured. This index is valid when a drop occurred and until next drop.
*/
- (NSUInteger) indexAtLocationOfDroppedItem; 


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/*!
 @method dropOperation
 @abstract Returns the current dropOperation. The returned value is valid when a drop occurred and until next drop.
 @discussion Returns IKImageBrowserDropOn if the drop occurs on an item. Returns IKImageBrowserDropBefore otherwise.
 In drag and drop, used to specify a dropOperation.  For example, given a browser with N cells (numbered with cell 0 at the top left visually), a cell of N-1 and operation of IKImageBrowserDropOn would specify a drop on the last cell.  To specify a drop after the last cell, one would use an index of N and IKImageBrowserDropBefore for the operation.
 */

- (IKImageBrowserDropOperation) dropOperation;


/*! 
 @method setAllowsDroppingOnItems:
 @abstract Controls whether the user can drop on items. Default is NO. 
 */  
- (void) setAllowsDroppingOnItems: (BOOL) flag;

/*! 
 @method allowsDroppingOnItems
 @abstract Returns YES if the receiver allows the user to drop on items, NO otherwise. 
 */ 
- (BOOL) allowsDroppingOnItems;


/*! 
 @method setDropIndex:dropOperation:
 @abstract Used if you wish to “retarget” the proposed drop.
 @discussion To specify a drop on the second item, one would specify index as 1, and operation as IKImageBrowserDropOn. To specify a drop after the last item, one would specify index as the number of items and operation as IKImageBrowserDropBefore. Passing a value of –1 for index, and IKImageBrowserDropOn as the operation causes the entire browser view to be highlighted rather than a specific item. This is useful if the data displayed by the receiver does not allow the user to drop items at a specific item location.
 */
- (void) setDropIndex:(NSInteger)index dropOperation:(IKImageBrowserDropOperation)operation;

#endif


@end



/*!
  @category NSObject (IKImageBrowserDelegate)
  @abstract Informal protocol for image browser 's delegate 
*/
@interface NSObject (IKImageBrowserDelegate)

/*!
  @method imageBrowserSelectionDidChange:
  @abstract Invoked by 'aBrowser' when the selection did change 
*/
- (void) imageBrowserSelectionDidChange:(IKImageBrowserView *) aBrowser;

/*!
  @method imageBrowser:cellWasDoubleClickedAtIndex:
  @abstract Invoked by 'aBrowser' when a cell was double clicked.
  @param index Index of the cell that was double clicked.
*/
- (void) imageBrowser:(IKImageBrowserView *) aBrowser cellWasDoubleClickedAtIndex:(NSUInteger) index;

/*!
  @method imageBrowser:cellWasRightClickedAtIndex:withEvent:
  @abstract Invoked by 'aBrowser' when a cell was right clicked or left clicked with the Alt key pressed.
  @param index Index of the cell that was right clicked.
*/
- (void) imageBrowser:(IKImageBrowserView *) aBrowser cellWasRightClickedAtIndex:(NSUInteger) index withEvent:(NSEvent *) event;

/*!
  @method imageBrowser:backgroundWasRightClickedWithEvent:
  @abstract Invoked by 'aBrowser' when a the background was right clicked or left clicked with the Alt key pressed.
*/
- (void) imageBrowser:(IKImageBrowserView *) aBrowser backgroundWasRightClickedWithEvent:(NSEvent *) event;

@end


/*
	Image representation types for - (NSString *) imageRepresentationType; defined by the IKImageBrowserItem protocol
*/
extern NSString * const IKImageBrowserPathRepresentationType;				/* NSString */
extern NSString * const IKImageBrowserNSURLRepresentationType;				/* NSURL */
extern NSString * const IKImageBrowserNSImageRepresentationType;			/* NSImage */
extern NSString * const IKImageBrowserCGImageRepresentationType;			/* CGImageRef */
extern NSString * const IKImageBrowserCGImageSourceRepresentationType;		/* CGImageSourceRef */
extern NSString * const IKImageBrowserNSDataRepresentationType;				/* NSData */
extern NSString * const IKImageBrowserNSBitmapImageRepresentationType;		/* NSBitmapImageRep */
extern NSString * const IKImageBrowserQTMovieRepresentationType;			/* QTMovie */
extern NSString * const IKImageBrowserQTMoviePathRepresentationType;		/* NSString or NSURL */
extern NSString * const IKImageBrowserQCCompositionRepresentationType;		/* QCComposition */
extern NSString * const IKImageBrowserQCCompositionPathRepresentationType;	/* NSString or NSURL */
extern NSString * const IKImageBrowserQuickLookPathRepresentationType;		/* NSString or NSURL*/
extern NSString * const IKImageBrowserIconRefPathRepresentationType;		/* NSString */
extern NSString * const IKImageBrowserIconRefRepresentationType;			/* IconRef */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
extern NSString * const IKImageBrowserPDFPageRepresentationType;            /* PDFPage or CGPDFPageRef */ 
#endif

 
/*
	IKImageBrowserView key for setValue:forKey and valueForKey:
*/
extern NSString * const IKImageBrowserBackgroundColorKey;					/*NSColor*/
extern NSString * const IKImageBrowserSelectionColorKey;					/*NSColor*/
extern NSString * const IKImageBrowserCellsOutlineColorKey;					/*NSColor*/
extern NSString * const IKImageBrowserCellsTitleAttributesKey;				/*NSDictionary*/
extern NSString * const IKImageBrowserCellsHighlightedTitleAttributesKey;	/*NSDictionary*/
extern NSString * const IKImageBrowserCellsSubtitleAttributesKey;			/*NSDictionary*/

/*
	IKImageBrowserView key for groups
*/
extern NSString * const IKImageBrowserGroupRangeKey;						/*NSValue (NSRange value) -- required-- */
extern NSString * const IKImageBrowserGroupBackgroundColorKey;				/*NSColor (for bezel style only)*/
extern NSString * const IKImageBrowserGroupTitleKey;						/*NSString (for diclosure style only) */
extern NSString * const IKImageBrowserGroupStyleKey;						/*NSNumber (see enum above) */
extern NSString * const IKImageBrowserGroupHeaderLayer;		                /* CALayer */				
extern NSString * const IKImageBrowserGroupFooterLayer;	                    /* CALayer */



#endif //MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
