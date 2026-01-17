/* IKFilterBrowserView  


   Copyright (c) 2006 Apple Inc.
   All rights reserved. */

#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>
/*!
    @header IKFilterBrowserView
	@copyright 2006 Apple Inc. All rights reserved.
	@availability Coming to a Leopard installation near you
    @abstract   View containing the elements of the IKFilterBrowser
    @discussion See discussion in IKFilterBrowserPanel
*/

@interface IKFilterBrowserView : NSView
{
	
@private
    IBOutlet id _actionButton;
    IBOutlet id _addCollectionButton;
    IBOutlet id _browser;
    IBOutlet id _descriptionField;
    IBOutlet id _previewView;
    IBOutlet id _removeCollectionButton;
    IBOutlet id _searchField;
    IBOutlet id _OKButton;
    IBOutlet id _CancelButton;
	
	NSMutableArray	*_foundFilters;
	NSDictionary	*_options;
	BOOL			_showPreviewView;
	BOOL			_useNarrowLayout;
	id				_modalDelegate;
	void*			_priv[8];
}


/*!
    @method     setPreviewState:
    @abstract   Use this method to show and hide the Preview
    @discussion Use this method to show and hide the Preview from the program.
    @param      inState Boolean for visibility of the preview.
*/
- (void)setPreviewState:(BOOL)inState;

/*!
    @method     filterName
    @abstract   Returns the name of the currently selected filter.
    @discussion Use this method in response to a IKFilterBrowserFilterSelectedNotification or IKFilterBrowserFilterDoubleClickNotification or afer returning from a modal session.
*/
- (NSString*)filterName;

@end
