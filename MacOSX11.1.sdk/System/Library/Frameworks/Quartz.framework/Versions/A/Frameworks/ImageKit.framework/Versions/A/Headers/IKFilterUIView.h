//
//  IKFilterUIView.h
//
//  Copyright 2006 Apple Inc.  All rights reserved.
//

/*!
    @header IKFilterUIView
    @abstract   The IKFilterUIView is the view that holds the UI elements to control the inputKeys of a filter.
    @discussion (description)
*/

#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>
#import <ImageKit/ImageKitBase.h>

@interface IKFilterUIView : NSView 
{
@private
    void *_priv[8];
}

/*!
    @method     viewWithFrame:filter:
    @abstract   The viewWithFrame method creates a view that retains the filter passed into it.
*/
+ (id)viewWithFrame:(NSRect)frameRect filter:(CIFilter*)inFilter;
/*!
    @method     initWithFrame:filter:
    @abstract   The initWithFrame method initializes a view that retains the filter passed into it.
*/
- (id)initWithFrame:(NSRect)frameRect filter:(CIFilter*)inFilter;
/*!
    @method     filter
    @abstract   Accessor method to return the filter instance that the view controls.
*/
- (CIFilter*)filter;
/*!
    @method     objectController
    @abstract   Accessor method for the object controller for all bindings between the filter and the UI representation.
*/
- (NSObjectController*)objectController;

@end
