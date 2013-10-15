//
//  IOBluetoothObjectPushUIController.h
//  IOBluetoothFamily
//
//  Copyright (c) 2004 Apple Computer. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class IOBluetoothDevice;

@interface IOBluetoothObjectPushUIController : NSWindowController {

}


/*!
	@method		initObjectPushWithBluetoothDevice: withFiles: andEventDelegate:
	@abstract	Creates and returns a new IOBluetoothObjectPush object
	@discussion	The event delegate should implement a single delegate method:
 
				- (void) objectPushComplete: (IOBluetoothObjectPushUIController*) inPusher
 
				The method will be called when the transaction is complete and
				should be used to release the push object by the delegate. If no delegate is set
				the object will release itself when the transfer is finished.
	@param		inDevice	The remote device to send the files to
	@param		inFiles		An array of file paths to send
	@param		inDelegate  A delegate object that implements the single method above.  If no delegate
							is specified this object will release itself when the transaction is complete.
	@result		An IOBluetoothObjectPushUIController object on success, nil on fail.
 */
- (IOBluetoothObjectPushUIController*) initObjectPushWithBluetoothDevice: (IOBluetoothDevice*) inDevice 
															   withFiles: (NSArray *) inFiles 
																delegate: (id) inDelegate;

/*!
    @method		runModal
	@abstract	Runs the transfer UI panel in a modal session
	@discussion	Returns when the modal session has ended. This object will call back over the 
				delegate method (above) when the transfer is complete.  Users should release 
				the object then. If no delegate is set the object will release itself.
	@result		The call will stall in this method until the modal session is complete.
*/
- (void) runModal;


/*!
	@method		runPanel
	@abstract	Runs the transfer UI as a panel with no modal session
	@discussion	Returns immediately.  The object will callback over the delegate method (above)
				when the transfer is completed.  If no delegate is set the object will release itself.
	@result		The method will return immediately.
*/
- (void) runPanel;


/*!
    @method		beginSheetModalForWindow:modalDelegate:didEndSelector:contextInfo:
	@abstract	Runs the  transfer UI as a sheet on the target window.
	@discussion	This function works the same way as -[NSApplication beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:].
				The didEndSelector has a similar prototype as in NSApplication except that the first argument is the 
				IOBluetoothDeviceSelectorController object instead of the window: 
 
				-(void)sheetDidEnd:(IOBluetoothDeviceSelectorController *)controller returnCode:(int)returnCode contextInfo:(void *)contextInfo.
				The returnCode parameter will either be kIOBluetoothUISuccess or kIOBluetoothUIUserCancelledErr as described in
				-runModal.

	@param		sheetWindow		NSWindow to attach the device selector panel to as a sheet.
	@param		modalDelegate	Delegate object that gets sent the didEndSelector when the sheet modal session is finished.
	@param		didEndSelector	Selector sent to the modalDelegate when the sheet modal session is finished.
	@param		contextInfo		User-definied value passed to the modalDelegate in the didEndSelector.
	@result		Returns kIOReturnSuccess if the sheet modal session was started.
*/

- (IOReturn) beginSheetModalForWindow: (NSWindow *) sheetWindow 
						modalDelegate: (id) modalDelegate 
					   didEndSelector: (SEL) didEndSelector 
						  contextInfo: (void *) contextInfo;


/*!
	@method		stop
	@abstract	Stops the transfer UI
	@discussion	Returns immediately. The object will callback over the delegate method (above)
				when the transfer is completed, or will release itself if no delegate is set.
	@result		The method will return immediately.
*/
- (void) stop;


/*!
    @method		setTitle:
	@abstract	Sets the title of the panel when not run as a sheet.
	@discussion	The panel title should be localized for best user experience.
	@param		windowTitle Title of the device selector panel.
*/
- (void) setTitle: (NSString *) windowTitle;


/*!
    @method		getTitle
	@abstract	Returns the title of the transfer panel (i.e. what was set in -setTitle:).
	@discussion	
	@result		Returns the title of the transfer panel.
*/
- (NSString *) getTitle;


/*!
	@method		setIconImage:
	@abstract	Manually sets the icon used in the panel.
	@discussion	The panel icon should be set to the icon of the calling application.  If not set, the panel
				will try to load up the correct icon for the target device, and will default to the icon of
				the running application on fail.
	@param		image Image to use as the icon.
*/
- (void) setIconImage:(NSImage*)image;


/*!
	@method		getDevice:
	@abstract	Gets the object representing the remote target device in the transfer.
	@discussion	
	@result		The remote device of the transfer.
*/
- (IOBluetoothDevice*) getDevice;

@end





