/*
	IKImageView.h
	ImageKit Framework
	Copyright (c) 2006 - 2007, Apple, Inc.
	All rights reserved.
 */

#ifndef IKIMAGEVIEW_H_
#define IKIMAGEVIEW_H_

#import <AppKit/NSView.h>
#import <QuartzCore/QuartzCore.h>

extern NSString *const IKToolModeNone;
extern NSString *const IKToolModeMove;
extern NSString *const IKToolModeSelect;
extern NSString *const IKToolModeCrop;
extern NSString *const IKToolModeRotate;
extern NSString *const IKToolModeAnnotate;

extern NSString *const IKOverlayTypeBackground;
extern NSString *const IKOverlayTypeImage;


@interface IKImageView : NSView
{
@private
    void * _privateData;
}

@property(assign) id        	delegate;
@property CGFloat           	zoomFactor;
@property CGFloat           	rotationAngle;
@property(assign) NSString* 	currentToolMode;
@property BOOL                  autoresizes;	
@property BOOL                  hasHorizontalScroller;
@property BOOL                  hasVerticalScroller;
@property BOOL                  autohidesScrollers;
@property BOOL                  supportsDragAndDrop;
@property BOOL                  editable;
@property BOOL                  doubleClickOpensImageEditPanel;
@property(assign) CIFilter *    imageCorrection;
@property(assign) NSColor *     backgroundColor;

    // setting the image to display

    // set the image & metadata (both retrieved from ImageIO)
- (void)setImage: (CGImageRef)image
 imageProperties: (NSDictionary*)metaData;


    // setImageWithURL is the preferred initializer for RAW images
    // note: if used for multi-page TIFF documents, only the first page will
    //       be displayed
- (void)setImageWithURL: (NSURL*)url;

    // resulting image (including image corrections)
- (CGImageRef)image;

    // resulting image size 
    // note: the image size is changed when rotating or cropping an image
- (NSSize)imageSize;

    // meta data
- (NSDictionary*)imageProperties;

    // rotating 
- (void)setRotationAngle: (CGFloat)rotationAngle
             centerPoint: (NSPoint)centerPoint;

    // zooming 
- (void)setImageZoomFactor: (CGFloat)zoomFactor
               centerPoint: (NSPoint)centerPoint;
- (void)zoomImageToFit: (id)sender;
- (void)zoomImageToActualSize: (id)sender;
- (void)zoomImageToRect: (NSRect)rect;

    // flipping 
- (void)flipImageHorizontal: (id)sender;
- (void)flipImageVertical: (id)sender;

    // Core Animation related
- (void)setOverlay: (CALayer*)layer
		   forType: (NSString*)layerType;
- (CALayer*)overlayForType: (NSString*)layerType;

    // scroller related
- (void)scrollToPoint:(NSPoint)point;
- (void)scrollToRect:(NSRect)rect;

    // conversions
- (NSPoint)convertViewPointToImagePoint: (NSPoint)viewPoint;
- (NSRect)convertViewRectToImageRect: (NSRect)viewRect;

- (NSPoint)convertImagePointToViewPoint: (NSPoint)imagePoint;
- (NSRect)convertImageRectToViewRect: (NSRect)imageRect;

@end

#endif
