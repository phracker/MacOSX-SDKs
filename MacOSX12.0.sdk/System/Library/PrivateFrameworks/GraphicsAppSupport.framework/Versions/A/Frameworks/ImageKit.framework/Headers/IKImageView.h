/*
    IKImageView.h
    ImageKit Framework
    Copyright (c) 2006 - 2008, Apple, Inc.
    All rights reserved.
 */

#ifndef IKImageView_h
#define IKImageView_h

#import <AppKit/NSView.h>
#import <QuartzCore/QuartzCore.h>
#import <ImageKit/ImageKitBase.h>

extern NSString *const IKToolModeNone;
extern NSString *const IKToolModeMove;
extern NSString *const IKToolModeSelect;
extern NSString *const IKToolModeSelectRect;        /* same as IKToolModeSelect */
extern NSString *const IKToolModeSelectEllipse;
extern NSString *const IKToolModeSelectLasso;
extern NSString *const IKToolModeCrop;
extern NSString *const IKToolModeRotate;
extern NSString *const IKToolModeAnnotate;

extern NSString *const IKOverlayTypeBackground;
extern NSString *const IKOverlayTypeImage;


/*! 
 @class IKImageView
 @abstract The IKImageView class provides an efficient way to display images in a view while at the same time supporting a number of image editing operations.
 */
IK_CLASS_AVAILABLE(10.5)
@interface IKImageView : NSView
{
@private
    void * _privateData;
}

/*!
 @property delegate
 @abstract Specifies the delegate object of the receiver.
 */
@property(assign) IBOutlet id delegate;

/*!
 @property zoomFactor
 @abstract Specifies the zoom factor for the image view.
 */
@property CGFloat zoomFactor;

/*!
 @property rotationAngle
 @abstract Specifies the rotation angle for the image view.
 */
@property CGFloat rotationAngle;

/*!
 @property currentToolMode
 @abstract Specifies the current tool mode for the image view.
 */
@property(copy) NSString * currentToolMode;

/*!
 @property autoresizes
 @abstract Specifies the automatic resizing state for the image view.
 */
@property BOOL autoresizes;

/*!
 @property hasHorizontalScroller
 @abstract Specifies the horizontal scroll bar state for the image view.
 */
@property BOOL hasHorizontalScroller;

/*!
 @property hasVerticalScroller
 @abstract Specifies the vertical scroll bar state for the image view.
 */
@property BOOL hasVerticalScroller;

/*!
 @property autohidesScrollers
 @abstract Specifies the automatic-hiding scroll bar state for the image view.
 */
@property BOOL autohidesScrollers;

/*!
 @property supportsDragAndDrop
 @abstract Specifies the drag-and-drop support state for the image view.
 */
@property BOOL supportsDragAndDrop;

/*!
 @property editable
 @abstract Specifies the editable state for the image view.
 */
@property BOOL editable;

/*!
 @property doubleClickOpensImageEditPane
 @abstract Specifies the image-opening state of the editing pane in the image view.
 */
@property BOOL doubleClickOpensImageEditPanel;

/*!
 @property imageCorrection
 @abstract Specifies a Core Image filter for image correction.
 */
@property(assign) CIFilter * imageCorrection;

/*!
 @property backgroundColor
 @abstract Specifies the background color for the image view.
 */
@property(assign) NSColor * backgroundColor;

/*! 
 @method setImage:imageProperties:
 @abstract Sets the image & metadata (both retrieved from ImageIO).
 */
- (void)setImage: (CGImageRef)image imageProperties: (NSDictionary *)metaData;


/*! 
 @method setImageWithURL:
 @abstract Initializes an image view with the image specified by a URL.
 */
- (void)setImageWithURL: (NSURL *)url;

/*! 
 @method image
 @abstract Returns the image associated with the view, after any image corrections.
 */
- (CGImageRef)image;

/*! 
 @method imageSize
 @abstract Returns the size of the image in the image view.
 */
- (NSSize)imageSize;

/*! 
 @method imageProperties
 @abstract Returns the metadata for the image in the view.
 */
- (NSDictionary *)imageProperties;

/*! 
 @method setRotationAngle:centerPoint:
 @abstract Sets the rotation angle at the provided origin.
 */
- (void)setRotationAngle: (CGFloat)rotationAngle centerPoint: (NSPoint)centerPoint;

/*! 
 @method rotateImageLeft:
 @abstract Rotates the image left.
 */
- (IBAction)rotateImageLeft: (id)sender;

/*! 
 @method rotateImageRight:
 @abstract Rotates the image right.
 */
- (IBAction)rotateImageRight: (id)sender;

/*! 
 @method setImageZoomFactor:centerPoint:
 @abstract Sets the zoom factor at the provided origin.
 */
- (void)setImageZoomFactor: (CGFloat)zoomFactor centerPoint: (NSPoint)centerPoint;

/*! 
 @method zoomImageToRect:
 @abstract Zooms the image so that it fits in the specified rectangle.
 */
- (void)zoomImageToRect: (NSRect)rect;

/*! 
 @method zoomImageToFit:
 @abstract Zooms the image so that it fits in the image view.
 */
- (IBAction)zoomImageToFit: (id)sender;

/*! 
 @method zoomImageToActualSize:
 @abstract Zooms the image so that it is displayed using its true size.
 */
- (IBAction)zoomImageToActualSize: (id)sender;

/*! 
 @method zoomIn:
 @abstract Zooms the image in.
 */
- (IBAction)zoomIn: (id)sender;

/*! 
 @method zoomOut:
 @abstract Zooms the image out.
 */
- (IBAction)zoomOut: (id)sender;

/*! 
 @method flipImageHorizontal:
 @abstract Flips an image along the horizontal axis.
 */
- (IBAction)flipImageHorizontal: (id)sender;

/*! 
 @method flipImageVertical:
 @abstract Flips an image along the vertical axis.
 */
- (IBAction)flipImageVertical: (id)sender;

/*! 
 @method crop:
 @abstract Crops the image using the current selection.
 */
- (IBAction)crop: (id)sender;

/*! 
 @method setOverlay:forType:
 @abstract Sets an overlay (Core Animation layer) for the image or the image background.
 */
- (void)setOverlay: (CALayer *)layer forType: (NSString *)layerType;

/*! 
 @method overlayForType:
 @abstract Returns the overlay (Core Animation layer) for the image or the image background.
 */
- (CALayer *)overlayForType: (NSString *)layerType;

/*! 
 @method scrollToPoint:
 @abstract Scrolls the view to the specified point.
 */
- (void)scrollToPoint:(NSPoint)point;

/*! 
 @method scrollToRect:
 @abstract Scrolls the view so that it includes the provided rectangular area.
 */
- (void)scrollToRect:(NSRect)rect;

/*! 
 @method convertViewPointToImagePoint:
 @abstract Converts an image view coordinate to an image coordinate.
 */
- (NSPoint)convertViewPointToImagePoint: (NSPoint)viewPoint;

/*! 
 @method convertViewRectToImageRect:
 @abstract Converts an image view rectangle to an image rectangle.
 */
- (NSRect)convertViewRectToImageRect: (NSRect)viewRect;

/*! 
 @method convertImagePointToViewPoint:
 @abstract Converts an image coordinate to an image view coordinate.
 */
- (NSPoint)convertImagePointToViewPoint: (NSPoint)imagePoint;

/*! 
 @method convertImageRectToViewRect:
 @abstract Converts an image rectangle to an image view rectangle.
 */
- (NSRect)convertImageRectToViewRect: (NSRect)imageRect;

@end

#endif
