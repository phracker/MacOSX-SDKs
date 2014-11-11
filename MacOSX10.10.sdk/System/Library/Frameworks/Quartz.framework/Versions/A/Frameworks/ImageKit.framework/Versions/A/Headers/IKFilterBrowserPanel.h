/* IKFilterBrowserPanel 


   Copyright (c) 2006 Apple Inc.
   All rights reserved. */

/*!
    @header IKFilterBrowserPanel
	@copyright 2006 Apple Inc. All rights reserved.
	@availability Coming to a Leopard installation near you
    @abstract   IKFilterBrowserPanel provides a filter browser in form of a panel, sheet or view.
    @discussion The IKFilterBrowser is modeled close to common AppKit behavior like the NSOpenPanel. It allows you to display the browser in a separate panel, a modal dialog, a sheet or you can just retireve the view to insert it into your own UI.
		The browser offers the user to preview the filters and get additional information about a filter (this filter information is based on the new additional filter description introduced in Leopard). It also allows the user to create 
		filter collections. These collections are stored in the users preferences under com.apple.CoreImageKit with the filterCollections key.
		The IKFilterBrowser can be configured through a styleMask to select between Aqua and brushed metal look. When running the browser, you can pass in an options dictionary allowing for different UI sizes as well as the visibiliy of certain components. 
		The IKFilterBrowser communicates selection changes through notifications and the selected filter can be retrieved through the filterName method - very much like the NSOpenPanel.
*/


#import <AppKit/AppKit.h>

@class IKFilterBrowserView;

/*!
    @class		IKFilterBrowserPanel
    @abstract   The IKFilterBrowserPanel provides the shared IKFilterBrowser with its runtime model.
    @discussion  See information in the introduction.
*/
@interface IKFilterBrowserPanel : NSPanel
{
    IBOutlet id _filterBrowserView;
}

/*!
    @method     filterBrowserPanelWithStyleMask:
    @abstract   Create a shared instance of the IKFilterBrowser
    @discussion Use this method to create a shared instance of the IKFilterBrowser with a specific NSWindow style. Right now it only supports selecting of deselecting the NSTexturedBackgroundWindowMask style bit.
*/
+ (id)filterBrowserPanelWithStyleMask:(unsigned int)styleMask;

/*!
    @method     filterName
    @abstract   Returns the name of the currently selected filter.
    @discussion Use this method in response to a IKFilterBrowserFilterSelectedNotification or IKFilterBrowserFilterDoubleClickNotification or afer returning from a modal session.
*/
- (NSString*)filterName;

@end

/*!
    @category	IKFilterBrowserPanelRuntime
    @abstract    Use the methods in the IKFilterBrowserPanelRuntime to display and run the IKFilterBrowser.
    @discussion  These methods are modeled after the NSOpenPanel methods with additions to allow for different UI configurations and to just get a IKFilterBrowserView to be inserted in your UI.
*/
@interface IKFilterBrowserPanel (IKFilterBrowserPanelRuntime)

/*!
    @method     beginWithOptions:modelessDelegate:didEndSelector:contextInfo:
    @abstract   Displays the FilterBrowser in a new window unless it is already open.
    @discussion Use this method to open the IKFilterBrowser in a seperate window, much like a panel. When the panel operation is ended, didEndSelector is invoked on the modelessDelegate, passing contextInfo as an argument.
			didEndSelector should have the following signature:
			
				- (void)openPanelDidEnd:(NSOpenPanel *)panel returnCode:(int)returnCode  contextInfo:(void  *)contextInfo
				
			The value passed as returnCode will be either NSCancelButton or NSOKButton.
	@param		inOptions	A dictionary describing the desired UI configuration for the IKFilterBrowser
	@param		modelessDelegate	See discussion below
	@param		didEndSelector	See discussion below
	@param		contextInfo	See discussion below
*/
- (void)beginWithOptions:(NSDictionary*)inOptions modelessDelegate:(id)modelessDelegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

/*!
    @method     beginSheetWithOptions:modalForWindow:modalDelegate:didEndSelector:contextInfo:
    @abstract   Displays the FilterBrowser in a sheet attached to the passed in window.
    @discussion Use this method to open the IKFilterBrowser in a sheet attached to a window. When the sheet operation is ended, didEndSelector is invoked on the modalDelegate, passing contextInfo as an argument. 
			didEndSelector should have the following signature:
			
				- (void)openPanelDidEnd:(NSOpenPanel *)panel returnCode:(int)returnCode  contextInfo:(void  *)contextInfo
				
			The value passed as returnCode will be either NSCancelButton or NSOKButton.
	@param		inOptions	A dictionary describing the desired UI configuration for the IKFilterBrowser
	@param		modalForWindow	The window to which the sheet should be attached to.
	@param		modalDelegate	See discussion below
	@param		didEndSelector	See discussion below
	@param		contextInfo	See discussion below
*/
- (void)beginSheetWithOptions:(NSDictionary*)inOptions modalForWindow:(NSWindow *)docWindow modalDelegate:(id)modalDelegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

/*!
    @method     runModalWithOptions
    @abstract   Displays the FilterBrowser in a modal dialog.
    @discussion Use this method to run the IKFilterBrowser in a modal dialog. The value passed as returnCode will be either NSCancelButton or NSOKButton.
	@param		inOptions	A dictionary describing the desired UI configuration for the IKFilterBrowser
*/
- (int)runModalWithOptions:(NSDictionary*)inOptions;

/*!
    @method     filterBrowserViewWithOptions
    @abstract   Returns a view containing the FilterBrowser.
    @discussion Use this method to run the IKFilterBrowser in your own UI. To dismiss it, invoke the finish action as described below.
	@param		inOptions	A dictionary describing the desired UI configuration for the IKFilterBrowser
*/
- (IKFilterBrowserView*)filterBrowserViewWithOptions:(NSDictionary*)inOptions;

/*!
    @method     finish
    @abstract   Closes the IKFilterBrowser.
    @discussion Invoke this action for instance from your OK or Cancel button when you are running the IKFilterBrowserView modal in your own UI.
*/
- (void)finish:(id)sender;	// action for buttons when running modal

@end

/* Notifications */
/*!
    @const      IKFilterBrowserFilterSelectedNotification
    @abstract   IKFilterBrowserFilterSelectedNotification
    @discussion Send when the user clicked on a filter in the Filter Browser. The name of the selected filter is send as the object in the notification
*/
extern NSString *const IKFilterBrowserFilterSelectedNotification;

/*!
    @const      IKFilterBrowserFilterDoubleClickNotification
    @abstract   IKFilterBrowserFilterDoubleClickNotification
    @discussion Send when the user made a double click on a filter in the Filter Browser. The name of the selected filter is send as the object in the notification
*/
extern NSString *const IKFilterBrowserFilterDoubleClickNotification;

/*!
    @const      IKFilterBrowserWillPreviewFilterNotification
    @abstract   IKFilterBrowserWillPreviewFilterNotification
    @discussion Send before a filter is previewed allowing for setting parameters of that filter. The selected CIFilter object is send as the object in the notification
*/
extern NSString *const IKFilterBrowserWillPreviewFilterNotification;

/* Keys */
// NOTE the dictionary also supports the IKUISizeFlavor key


/*!
    @const      IKFilterBrowserShowCategories
    @abstract   IKFilterBrowserShowCategories
    @discussion BOOL - Determines if the filter browser should show the category list
*/
extern NSString *const IKFilterBrowserShowCategories;

/*!
    @const      IKFilterBrowserShowPreview
    @abstract   IKFilterBrowserShowPreview
    @discussion BOOL - Determines if the filter browser should show the preview well
*/
extern NSString *const IKFilterBrowserShowPreview;

/*!
    @const      IKFilterBrowserExcludeCategories
    @abstract   IKFilterBrowserExcludeCategories
    @discussion NSArray - The categories in this array will not be displayed in the browser
*/
extern NSString *const IKFilterBrowserExcludeCategories;

/*!
    @const      IKFilterBrowserExcludeFilters
    @abstract   IKFilterBrowserExcludeFilters
    @discussion NSArray - The filters in this array will not be displayed in the browser
*/
extern NSString *const IKFilterBrowserExcludeFilters;

/*!
    @const      IKFilterBrowserDefaultInputImage
    @abstract   IKFilterBrowserDefaultInputImage - Allows you to set a custom image to be used as the inputImage for the filter preview.
    @discussion CIImage* - You can also set the inputImage among other parameters during the IKFilterBrowserWillPreviewFilterNotification. This image will be set before the notification is called. Setting the image to nil falls back to the image suplied by the framework.
*/
extern NSString *const IKFilterBrowserDefaultInputImage;
