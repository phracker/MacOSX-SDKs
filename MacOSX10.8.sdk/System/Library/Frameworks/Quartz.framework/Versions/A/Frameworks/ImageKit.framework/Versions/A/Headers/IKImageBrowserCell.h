//
//  IKImageBrowserCell.h
//  ImageKit
//
//  Copyright 2008 Apple. All rights reserved.
//


/*!
 @header IKImageBrowserCell
 The IKImageBrowserCell class provides a mechanism for displaying the IKImageBrowserItem in an IKImageBrowserView. 
 */

#import <AppKit/AppKit.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@class IKImageBrowserView;

typedef enum{
	IKImageStateNoImage=0,
	IKImageStateInvalid,
	IKImageStateReady,
}IKImageBrowserCellState;


/* types for layerForType: */
extern NSString *const IKImageBrowserCellBackgroundLayer;
extern NSString *const IKImageBrowserCellForegroundLayer;
extern NSString *const IKImageBrowserCellSelectionLayer;
extern NSString *const IKImageBrowserCellPlaceHolderLayer;

@interface IKImageBrowserCell : NSObject
{
	__weak id                   _parent;
	void* __strong              _ibCellReserved;
}

/*! 
 @method imageBrowserView
 @abstract Returns the view the receiver uses to display its represented object.
 @discussion Subclasses should not override this method.
 */
- (IKImageBrowserView *) imageBrowserView;

/*! 
 @method representedItem
 @abstract Returns the receiverÕs represented object.
 @discussion Subclasses should not override this method.
 */
- (id) representedItem;

/*! 
 @method indexOfRepresentedItem
 @abstract Returns the index of the receiverÕs represented object in the datasource.
 @discussion Subclasses should not override this method.
 */
- (NSUInteger) indexOfRepresentedItem;

//-- Layout
/*! 
 @method frame
 @abstract Returns the receiverÕs frame rectangle, which defines its position in its IKImageBrowserView.
 @discussion The coordinates of this frame are in view's coordinate space. Subclasses should not override this method.
 */
- (NSRect) frame;

/*! 
 @method imageContainerFrame
 @abstract Returns the receiverÕs image container frame rectangle, which defines the position of the container of the thumbnail in its IKImageBrowserView.
 @discussion The coordinates of this frame are in view's coordinate space. Subclasses can override this method to customize the position of the thumbnail container. The image frame is computed automatically from the image container frame by taking in account the image alignment and the image aspect ratio.
 */
- (NSRect) imageContainerFrame; 

/*! 
 @method imageFrame
 @abstract Returns the receiverÕs image frame rectangle, which defines the position of the thumbnail in its IKImageBrowserView.
 @discussion The coordinates of this frame are in view's coordinate space. Subclasses can override this method to customize the position of the thumbnail.
 */
- (NSRect) imageFrame; 

/*! 
 @method selectionFrame
 @abstract Returns the receiverÕs selection frame rectangle, which defines the position of the selection rectangle in its IKImageBrowserView.
 @discussion The coordinates of this frame are in view's coordinate space. Subclasses can override this method to customize the position of the selection frame.
 */
- (NSRect) selectionFrame;

/*! 
 @method titleFrame
 @abstract Returns the receiverÕs title frame rectangle, which defines the position of the title in its IKImageBrowserView.
 @discussion The coordinates of this frame are in view's coordinate space. Subclasses can override this method to customize the position of the title.
 */
- (NSRect) titleFrame;

/*! 
 @method subtitleFrame
 @abstract Returns the receiverÕs subtitle frame rectangle, which defines the position of the subtitle in its IKImageBrowserView.
 @discussion The coordinates of this frame are in view's coordinate space. Subclasses can override this method to customize the position of the subtitle.
 */
- (NSRect) subtitleFrame;

/*! 
 @method imageAlignment
 @abstract Returns the position of the cellÕs image in the frame. The default is NSImageAlignCenter.
 @discussion Subclasses can override this method to customize the image alignment. For the list of possible alignments, see [NSImageView setImageAlignment:].
 The image frame will be computed automatically from the image container frame by taking in account the image alignment and the image aspect ratio.
 */
- (NSImageAlignment) imageAlignment;

//-- State
/*! 
 @method isSelected
 @abstract Returns the selection state of the receiver.
 @discussion Returns YES if the receiver is selected, otherwise NO. Subclasses should not override this method.
 */
- (BOOL) isSelected;

/*! 
 @method cellState
 @abstract Returns the current cell state of the receiver.
 @discussion Returns IKImageStateReady if the receiverÕs represented object has been set and the cell is ready to display. The IKImageBrowserView creates thumbnails asynchronously; This method returns IKImageStateNoImage until a thumbnail has been created from the represented object. 
 */
- (IKImageBrowserCellState) cellState;

/*! 
 @method opacity
 @abstract Determines the opacity of the receiver.
 @discussion Possible values are between 0.0 (transparent) and 1.0 (opaque). Subclasses can override this method to customize the opacity of the cell.
 */
- (CGFloat) opacity;


//-- Layers
/*! 
 @method layerForType:
 @abstract Provides the receiverÕs layer for the given type. The default is nil.
 @discussion Subclasses can override this method to add a layer in the background, foreground... of the cell (see possible types above).
 */
- (CALayer *) layerForType:(NSString *) type;

@end


#endif //MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
