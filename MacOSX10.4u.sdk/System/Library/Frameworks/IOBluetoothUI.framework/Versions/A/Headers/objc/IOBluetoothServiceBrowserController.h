/*
    File:		IOBluetoothServiceBrowserController.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
*/
 
#import <Cocoa/Cocoa.h>
#import <IOBluetooth/objc/IOBluetoothDevice.h>
#import <IOBluetooth/objc/IOBluetoothSDPServiceRecord.h>
#import <IOBluetoothUI/IOBluetoothUIUserLib.h>

//--------------------------------------------------------------------------------------------------------------------------
/*!	@header		IOBluetoothServiceBrowserController.h
	@abstract	Public Interfaces for Apple's implementation of a service browser window for Bluetooth technology.
	@discussion	This implements a WindowController accessible from Cocoa applications to find a device, and
                        initiate Service Discovery queries on devices.  The user can select a particular service which
                        they want to use for the application.
*/

/*!
 	@class IOBluetoothServiceBrowserController
	@abstract A NSWindowController subclass to display a window to search for and perform SDP queries on bluetooth
                    devices within range.
	@discussion This NSWindowController subclass will bring up a generic Bluetooth search and SDP browsing window
                    allowing the user to find devices within range, perform SDP queries on a particular device, and
                    select a SDP service to connect to.  The client application can provide NSArrays of valid service
                    UUIDs to allow, and an NSArray of valid device types to allow.  The device type filter is not
                    yet implemented.
*/
@interface IOBluetoothServiceBrowserController : NSWindowController
{
}

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	serviceBrowserController:
	@abstract	Allocator work Bluetooth Service Browser window controller.
	@param		inOptions	Bit field for options to set in the newly allocated controller.  Currently no options are available.				
	@result		a new instance of the IOBluetoothServiceBrowserController Controller, nil if unsuccessful.
	@discussion	
*/
+(IOBluetoothServiceBrowserController *)serviceBrowserController:(IOBluetoothServiceBrowserControllerOptions)inOptions;

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	browseDevices:options:
	@abstract	
	@discussion	***WARNING*** This method has been deprecated in favor of -setOptions:, -runModal and -getResults.
	@param		outRecord 	Pointer to a (IOBluetoothSDPServiceRecord *) object.  This will get allocated and returned to the client if the user selects a service.
	@param		inOptions	For future expansion.  Currently no options defined.
	@result		IOReturn - 
        
                            * kIOReturnSuccess  - on successful completion.
                            
                            * kCanceledErr - User canceled.
                            
	@discussion	This method allocates and runs the browser window as a modal window waiting for the user to either select a
                        service, or cancel the browser window.  
*/
+(IOReturn)browseDevices:(IOBluetoothSDPServiceRecord**)outRecord options:(IOBluetoothServiceBrowserControllerOptions)inOptions;

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	browseDevicesAsSheetForWindow:options:window:
	@abstract	
	@discussion	***WARNING*** This method has been deprecated in favor of - beginSheetModalForWindow:modalDelegate:didEndSelector:contextInfo:.
	@param		outRecord 	Pointer to a (IOBluetoothSDPServiceRecord *) object.  This will get allocated and returned to the client if the user selects a service.
	@param		inOptions	For future expansion.  Currently no options defined.
	@param		inWindow	The window to be used as the anchor of the sheet.
	@result		IOReturn - 
        
                            * kIOReturnSuccess  - on successful completion.
                            
                            * kCanceledErr - User canceled.
                            
	@discussion	This method will allocate and run the IOBluetoothServiceBrowserController browser window as a sheet for a window.
*/
+(IOReturn)browseDevicesAsSheetForWindow:(IOBluetoothSDPServiceRecord**)outRecord
								 options:(IOBluetoothServiceBrowserControllerOptions)inOptions
								  window:(NSWindow*)inWindow;


/*!	@method	withServiceBrowserControllerRef:
	@abstract	Method call to convert an IOBluetoothServiceBrowserControllerRef into an IOBluetoothServiceBrowserController *.
        @param	serviceBrowserControllerRef IOBluetoothServiceBrowserControllerRef for which an IOBluetoothServiceBrowserController * is desired.
	@result		Returns the IOBluetoothServiceBrowserController * for the given IOBluetoothServiceBrowserControllerRef.
*/
+ (IOBluetoothServiceBrowserController *)withServiceBrowserControllerRef:(IOBluetoothServiceBrowserControllerRef)serviceBrowserControllerRef;

/*!	@method	getServiceBrowserControllerRef
	@abstract	Returns an IOBluetoothServiceBrowserControllerRef representation of the target IOBluetoothServiceBrowserController object.
	@result		Returns an IOBluetoothServiceBrowserControllerRef representation of the target IOBluetoothServiceBrowserController object.
*/
- (IOBluetoothServiceBrowserControllerRef)getServiceBrowserControllerRef;

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	discover:
	@abstract	Invoke an already created window controller to display, and run the modal dialog.	
	@discussion	***WARNING*** This method has been deprecated in favor of -runModal and -getResults.
	@param		outRecord 	Pointer to a (IOBluetoothSDPServiceRecord *) object.  This will get allocated and returned to the client if the user selects a service.
	@result		IOReturn - 
        
                            * kIOReturnSuccess  - on successful completion.
                            
                            * kCanceledErr - User canceled.
                            
	@discussion	This method will run the IOBluetoothServiceBrowserController browser window modally.
*/
-(IOReturn)discover:(IOBluetoothSDPServiceRecord **)outRecord;

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	discoverAsSheetForWindow:withRecord:
	@abstract	Invoke an already created window controller to display, and run the modal dialog.	
	@discussion	***WARNING*** This method has been deprecated in favor of -beginSheetModalForWindow:... and -getResults.
	@param		sheetWindow 	The window to use for the anchor of the sheet..
	@param		outRecord 	Pointer to a (IOBluetoothSDPServiceRecord *) object.  This will get allocated and returned to the client if the user selects a service.
	@result		IOReturn - 
        
                            * kIOReturnSuccess  - on successful completion.
                            
                            * kCanceledErr - User canceled.
                            
	@discussion	This method will run the IOBluetoothServiceBrowserController browser window as a sheet for the window passed to it in sheetWindow.
*/
-(IOReturn)discoverAsSheetForWindow:(NSWindow *)sheetWindow withRecord:(IOBluetoothSDPServiceRecord **)outRecord;

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	discoverWithDeviceAttributes:serviceList:serviceRecord:
	@abstract	Invoke an already created window controller to display, and run the modal dialog.	
	@discussion	***WARNING*** This method has been deprecated in favor of -setSearchAttributes:, -addAllowedUUID:, -runModal and -getResults.
	@param		deviceArray 	A NSArray of valid device type objects to allow.  Not implemented yet.
	@param		serviceArray 	A NSArray of valid UUIDs to allow. The array should contain NSData objects
                                specifying the UUID to allow.  We currently only support 16-bit short UUID forms, but
                                will allow for any of the 16, 32 or full 128-bit UUID forms.
	@param		outRecord 	Pointer to a (IOBluetoothSDPServiceRecord *) object.  This will get allocated
                                and returned to the client if the user selects a service.
	@result		IOReturn - 
        
                            * kIOReturnSuccess  - on successful completion.
                            
                            * kCanceledErr - User canceled.
                            
	@discussion	This method will run the IOBluetoothServiceBrowserController browser window as a sheet for the window passed to it in sheetWindow.
*/
-(IOReturn)discoverWithDeviceAttributes:(IOBluetoothDeviceSearchAttributes *)deviceAttributes serviceList:(NSArray *)serviceArray serviceRecord:(IOBluetoothSDPServiceRecord**)outRecord;

//--------------------------------------------------------------------------------------------------------------------------
/*!
	@method	setOptions:
	@abstract	Modify the options for the window controller.	
	@param		inOptions 	Bit field to set the options to.
	@result		None.
	@discussion	This method will set the options for the browser to new values.
*/
-(void)setOptions:(IOBluetoothServiceBrowserControllerOptions)inOptions;

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_1

/*!
    @method		runModal
	@abstract	Runs the service browser panel in a modal session to allow the user to select a service on a Bluetooth device.
	@discussion	The controller will use the panel attributes to filter what devices the user sees.  The allowed UUIDs
				will be used to validate the selection the user makes.  The user will only be able to select services
				that match the allowed UUIDs.  Only when a selection has been validated (or
				the panel cancelled), will this method return.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns kIOBluetoothUISuccess if a successful, validated service selection was made by the user.
				Returns kIOBluetoothUIUserCanceledErr if the user cancelled the panel.  These return values are the
				same as NSRunStoppedResponse and NSRunAbortedResponse respectively.  They are the standard values
				used in a modal session.
*/

- (int)runModal;

/*!
    @method		beginSheetModalForWindow:modalDelegate:didEndSelector:contextInfo:
	@abstract	Runs the service browser panel as a sheet on the target window.
	@discussion	This function works the same way as -[NSApplication beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:].
				The didEndSelector has a similar prototype as in NSApplication except that the first argument is the 
				IOBluetoothServiceBrowserController object instead of the window: 
				-(void)sheetDidEnd:(IOBluetoothServiceBrowserController *)controller returnCode:(int)returnCode contextInfo:(void *)contextInfo.
				The returnCode parameter will either be kIOBluetoothUISuccess or kIOBluetoothUIUserCancelledErr as described in
				-runModal.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		sheetWindow		NSWindow to attach the service browser panel to as a sheet.
	@param		modalDelegate	Delegate object that gets sent the didEndSelector when the sheet modal session is finished.
	@param		didEndSelector	Selector sent to the modalDelegate when the sheet modal session is finished.
	@param		contextInfo		User-definied value passed to the modalDelegate in the didEndSelector.
	@result		Returns kIOReturnSuccess if the sheet modal session was started.
*/

- (IOReturn)beginSheetModalForWindow:(NSWindow *)sheetWindow modalDelegate:(id)modalDelegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

/*!
    @method		getResults
	@abstract	Returns the result of the user's selection.
	@discussion	There will only be results if the panel has been run, the user has successfully made a selection and that 
				selection has been validated.  If kIOBluetoothUISuccess was returned for the session, there should be valid 
				results.  Currently only a single device is allowed to be selected, so the results array will only contain 
				one object.  However in the future multiple selection will be supported.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns an NSArray of IOBluetoothSDPServiceRecord objects corresponding to the user's selection.  If the user cancelled
				the panel, nil will be returned.
*/

- (NSArray *)getResults;

/*!
    @method		getOptions
	@abstract	Returns the option bits that control the panel's behavior.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns the option bits set by setOptions:
*/

- (IOBluetoothServiceBrowserControllerOptions)getOptions;

/*!
    @method		setSearchAttributes:
	@abstract	Sets the search attributes that control the panel's search/inquiry behavior.
	@discussion	The device search attributes control the inquiry behavior of the panel.  They allow only devices
				that match the specified attributes (i.e. class of device) to be displayed to the user.  Note that
				this only covers attributes returned in an inquiry result and not actual SDP services on the device.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		searchAttributes Attributes to control the panel's inquiry behavior.
*/

- (void)setSearchAttributes:(const IOBluetoothDeviceSearchAttributes *)searchAttributes;

/*!
    @method		getSearchAttributes
	@abstract	Returns the search attributes that control the panel's search/inquiry behavior.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns the search attributes set by setSearchAttributes:
*/

- (const IOBluetoothDeviceSearchAttributes *)getSearchAttributes;

/*!
    @method		addAllowedUUID:
	@abstract	Adds a UUID to the list of UUIDs that are used to validate the user's selection.
	@discussion	The user's device selection gets validated against the UUIDs passed to -addAllowedUUID:
				addAllowedUUIDArray:.  Each call to those methods essentially adds a filter that the
				selected device gets validated with.  If any of the filters match, the device is considered
				valid.  If they all fail, the device is not valid and the user is presented with an
				error code that the device does not support the required services.  The UUID passed to
				-addAllowedUUID: is the only UUID that must be present in the device's SDP service records.
				Alternatively, all of the UUIDs in the UUID array passed to -addAllowedUUIDArray must be
				present.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		allowedUUID UUID that a device may contain to be selected
*/

- (void)addAllowedUUID:(IOBluetoothSDPUUID *)allowedUUID;

/*!
    @method		addAllowedUUIDArray:
	@abstract	Adds an array of UUIDs to the list of UUIDs that are used to validate the user's selection.
	@discussion	The user's device selection gets validated against the UUIDs passed to -addAllowedUUID:
				addAllowedUUIDArray:.  Each call to those methods essentially adds a filter that the
				selected device gets validated with.  If any of the filters match, the device is considered
				valid.  If they all fail, the device is not valid and the user is presented with an
				error code that the device does not support the required services.  The UUID passed to
				-addAllowedUUID: is the only UUID that must be present in the device's SDP service records.
				Alternatively, all of the UUIDs in the UUID array passed to -addAllowedUUIDArray must be
				present.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		allowedUUIDArray An NSArray of UUIDs that all must be present in a device for it to be selectable.
*/

- (void)addAllowedUUIDArray:(NSArray *)allowedUUIDArray;

/*!
    @method		clearAllowedUUIDs
	@abstract	Resets the controller back to the default state where it will accept any device the user selects.
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
*/

- (void)clearAllowedUUIDs;

/*!
    @method		setTitle:
	@abstract	Sets the title of the panel when not run as a sheet.
	@discussion	The panel title should be localized for best user experience.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		windowTitle Title of the device selector panel.
*/

- (void)setTitle:(NSString *)windowTitle;
/*!
    @method		getTitle
	@abstract	Returns the title of the device selector panel (i.e. what was set in -setTitle:).
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns the title of the device selector panel.
*/

- (NSString *)getTitle;

/*!
    @method		setDescriptionText:
	@abstract	Sets the description text that appears in the device selector panel.
	@discussion	The description text should be localized for best user experience.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		descriptionText String that appears in the description section of the device selector panel.
*/

- (void)setDescriptionText:(NSString *)descriptionText;

/*!
    @method		getDescriptionText
	@abstract	Returns the description text that appears in the device selector panel (i.e. what was set in -setDescriptionText:).
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns the description text of the device selector panel.
*/

- (NSString *)getDescriptionText;

/*!
    @method		setPrompt:
	@abstract	Sets the title of the default/select button in the device selector panel.
	@discussion	The prompt text should be localized for best user experience.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		prompt String that appears in the default/select button in the device selector panel.
*/

- (void)setPrompt:(NSString *)prompt;

/*!
    @method		getPrompt
	@abstract	Returns the title of the default/select button in the device selector panel (i.e. what was set in -setPrompt:).
	@discussion	NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns the default button title of the device selector panel.
*/

- (NSString *)getPrompt;

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_1 */

@end

