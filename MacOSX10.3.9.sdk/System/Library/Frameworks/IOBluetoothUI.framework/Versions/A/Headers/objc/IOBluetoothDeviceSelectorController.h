/*
    File:		IOBluetoothDeviceSelectorController.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
*/
 
#import <Cocoa/Cocoa.h>
#import <IOBluetooth/objc/IOBluetoothDevice.h>
#import <IOBluetooth/objc/IOBluetoothSDPServiceRecord.h>
#import <IOBluetoothUI/IOBluetoothUIUserLib.h>

//--------------------------------------------------------------------------------------------------------------------------
/*!	@header		IOBluetoothDeviceSelectorController.h
	@abstract	Public Interfaces for Apple's implementation of a pairing window for Bluetooth technology.
	@discussion	This implements a WindowController accessible from Cocoa applications to select a device, and
                        initiate pairing.
*/



/*!
 	@class IOBluetoothDeviceSelectorController
	@abstract A NSWindowController subclass to display a window to initiate pairing to other bluetooth devices.
	@discussion Implementation of a window controller to return a NSArray of selected bluetooth devices.  This
                    class will handle connecting to the Bluetooth Daemon for the purposes of searches, and displaying
                    the results.  This controller will return a NSArray of IOBluetoothDevice objects to the user.

*/
@interface IOBluetoothDeviceSelectorController : NSWindowController
{
}

// Public methods
//--------------------------------------------------------------------------------------------------------------------------
/*!	@method	deviceSelector
	@abstract	
	@discussion	Method call to instantiate a new IOBluetoothDeviceSelectorController object.
	@result
        
                        Success - a new instance of the device selector Controller
        
                        Failure	- nil
*/
+ (IOBluetoothDeviceSelectorController *)deviceSelector;

/*!	@method	withDeviceSelectorControllerRef:
	@abstract	Method call to convert an IOBluetoothDeviceSelectorControllerRef into an IOBluetoothDeviceSelectorController *.
        @param	deviceSelectorControllerRef IOBluetoothDeviceSelectorControllerRef for which an IOBluetoothDeviceSelectorController * is desired.
	@result		Returns the IOBluetoothDeviceSelectorController * for the given IOBluetoothDeviceSelectorControllerRef.
*/
+ (IOBluetoothDeviceSelectorController *)withDeviceSelectorControllerRef:(IOBluetoothDeviceSelectorControllerRef)deviceSelectorControllerRef;

/*!	@method	getDeviceSelectorControllerRef
	@abstract	Returns an IOBluetoothDeviceSelectorControllerRef representation of the target IOBluetoothDeviceSelectorController object.
	@result		Returns an IOBluetoothDeviceSelectorControllerRef representation of the target IOBluetoothDeviceSelectorController object.
*/
- (IOBluetoothDeviceSelectorControllerRef)getDeviceSelectorControllerRef;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@method	runPanelWithAttributes
	@discussion	***WARNING*** This method has been deprecated in favor of -setSearchAttributes:, -runModal and -getResults.	
	@param	attributes	(IOBluetoothDeviceSearchAttributes *) A pointer to a list of device attributes to allow.  This list of attributes is used to determine which device types to display in the UI.
	@result		NSArray * of the selected IOBluetoothDevice objects.
*/
-(NSArray *)runPanelWithAttributes:(IOBluetoothDeviceSearchAttributes *)attributes;

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_1_1

/*!
    @method		runModal
	@abstract	Runs the device selector panel in a modal session to allow the user to select a Bluetooth device.
	@discussion	The controller will use the panel attributes to filter what devices the user sees.  The allowed UUIDs
				will be used to validate the selection the user makes.  Only when a selection has been validated (or
				the panel cancelled), will this method return.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		Returns kIOBluetoothUISuccess if a successful, validated device selection was made by the user.
				Returns kIOBluetoothUIUserCanceledErr if the user cancelled the panel.  These return values are the
				same as NSRunStoppedResponse and NSRunAbortedResponse respectively.  They are the standard values
				used in a modal session.
*/

- (int)runModal;

/*!
    @method		beginSheetModalForWindow:modalDelegate:didEndSelector:contextInfo:
	@abstract	Runs the device selector panel as a sheet on the target window.
	@discussion	This function works the same way as -[NSApplication beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:].
				The didEndSelector has a similar prototype as in NSApplication except that the first argument is the 
				IOBluetoothDeviceSelectorController object instead of the window: 
				-(void)sheetDidEnd:(IOBluetoothDeviceSelectorController *)controller returnCode:(int)returnCode contextInfo:(void *)contextInfo.
				The returnCode parameter will either be kIOBluetoothUISuccess or kIOBluetoothUIUserCancelledErr as described in
				-runModal.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		sheetWindow		NSWindow to attach the device selector panel to as a sheet.
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
	@result		Returns an NSArray of IOBluetoothDevice objects corresponding to the user's selection.  If the user cancelled
				the panel, nil will be returned.
*/

- (NSArray *)getResults;

/*!
    @method		setOptions:
	@abstract	Sets the option bits that control the panel's behavior.
	@discussion	The service browser controller options control the behavior of the panel.  Currently
				kIOBluetoothServiceBrowserControllerOptionsAutoStartInquiry is the only supported option.
				In the future more options will be added to control things like whether the connection to
				the device is closed when the controller is finished or if multiple selection is allowed.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@param		options	Options to control the panel's behavior.
*/

- (void)setOptions:(IOBluetoothServiceBrowserControllerOptions)options;

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
