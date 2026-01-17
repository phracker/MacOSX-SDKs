/*
     File:       DiscRecordingUI/DRSetupPanel.h
 
     Contains:   Base class for the DiscRecordingUI setup panels.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header		DRSetupPanel.h
	@abstract	Base class for the DiscRecordingUI setup panels.
	@discussion	Provides a base framework for handling device
				selection, media ejection and confirming or cancelling the panel.
*/

#import <Cocoa/Cocoa.h>
#import <DiscRecording/DiscRecording.h>
#import <AvailabilityMacros.h>

/*!
	@class		DRSetupPanel
	@discussion	This class is the base class for setup panels in the DiscRecordingUI
				framework. It provides a base framework for handling device
				selection, media ejection and confirming or cancelling the panel.
*/
@interface DRSetupPanel : NSPanel
{
    /*All instance variables are private*/
	IBOutlet NSButton*		_ok;
	IBOutlet NSButton*		_cancel;
	IBOutlet NSButton*		_eject;
	IBOutlet NSTextField*	_userMessage;
	IBOutlet NSImageView*	_icon;
	IBOutlet id				_deviceChooser;
	void*					_sp_privateStorage;
	void*					_reservedSetupPanel[2];
}

/* ----------------------------------------------------------------------------- */
/*	Initializing the panel */

/*!
	@method		initWithNibName:
	@abstract	Initializes the receiver to use the panel from the nibName nib file.
	@param		nibName		Nib filename.
	@result		The receiver.
*/
- (id) initWithNibName:(NSString*)nibName;

/* ----------------------------------------------------------------------------- */
/*	Presenting the panel on screen */

/*!
	@method		runSetupPanel
	@abstract	Displays the receiver and begins its event loop.
	@discussion	Invokes NSApplication's @link //apple_ref/occ/instm/NSApplication/runModalForWindow: runModalForWindow: @/link method with self as the argument.
	@result		Returns @link //apple_ref/c/econst/NSOKButton NSOKButton @/link (if the user clicks the default button) or
				@link //apple_ref/c/econst/NSCancelButton NSCancelButton @/link (if the user clicks the Cancel button).
*/
- (int) runSetupPanel;

/*!
	@method		beginSetupSheetForWindow:modalDelegate:didEndSelector:contextInfo:
	@abstract	Presents a setup panel as a sheet.
	@param		owner				The window the sheet will be attached to. If owner is not nil, the setup
									panel slides down as a sheet running as a document modal
									window. If owner is nil, this is an error.
	@param		modalDelegate		The modal delegate. The object that implements the didEndSelector.
	@param		didEndSelector		Selector to invoke when the sheet ends. This selector is optional.
									If implemented by the modal delegate, this method is invoked after 
									the modal session has ended, but before dismissing the same panel. 
									didEndSelector may dismiss the save panel itself; otherwise it will 
									be dismissed on return from the method. didEndSelector should have 
									the following signature:
									<br/>

									<code>- (void)setupPanelDidEnd:(DRSetupPanel*)panel returnCode:(int)returnCode contextInfo:(void*)contextInfo;</code>
									
									<br/>
	@param		contextInfo			Context information to be passed when the selector named by didEndSelector
									is invoked.
*/
- (void) beginSetupSheetForWindow:(NSWindow*)owner modalDelegate:(id)modalDelegate didEndSelector:(SEL)didEndSelector contextInfo:(void*)contextInfo;

/* ----------------------------------------------------------------------------- */
/* Action methods */

/*!
	@method		ok:
	@abstract	Invoked when the user clicks the panel's default button.
	@param		sender		The object that invoked this method.
*/
- (IBAction) ok:(id)sender;

/*!
	@method		cancel:
	@abstract	Invoked when the user clicks the panel's cancel button.
	@param		sender		The object that invoked this method.
*/
- (IBAction) cancel:(id)sender;

/*!
	@method		eject:
	@abstract	Invoked when the user clicks the panel's eject button.
	@param		sender		The object that invoked this method.
*/
- (IBAction) eject:(id)sender;

/*!
	@method		open:
	@abstract	Invoked when the user clicks the panel's open button.
	@param		sender		The object that invoked this method.
*/
- (IBAction) open:(id)sender;

/*!
	@method		close:
	@abstract	Invoked when the user clicks the panel's close button.
	@param		sender		The object that invoked this method.
*/
- (IBAction) close:(id)sender;

/* ----------------------------------------------------------------------------- */
/* Device state methods */

/*!
	@method		deviceSelectionChanged:
	@abstract	Invoked when the user changes the device selected in the device popup.
	@discussion	If the device currently selected is disconnected from the machine, the device 
				popup will remove the device from itself and select a new device. This will act 
				as if the user changed the device selected. Because of this, device may be nil
				if no eligible devices are currently connected to the machine.
	@param		device		The newly selected device, or nil.
*/
- (void) deviceSelectionChanged:(DRDevice*)device;

/*!
	@method		mediaStateChanged:
	@abstract	Invoked when the media state of the currently selected device changes. 
				This can include media being ejected, inserted, being used by another
				application, etc.
	@param		status		The new device status dictionary.
	@result		<i>YES</i> if the inserted media is valid for use, <i>NO</i> otherwise.
*/
- (BOOL) mediaStateChanged:(NSDictionary*)status;

/* ----------------------------------------------------------------------------- */
/* Setup routines */

/*!
	@method		setupForDisplay
	@abstract	This method is called immediately before panel is displayed on
				the screen. Any setup to be done in preparation for display should be
				done here.
*/
- (void) setupForDisplay;

@end

/*!
	@constant	DRSetupPanelDeviceSelectionChangedNotification
	@abstract	Type of notification sent when the device selection changes.
*/
extern NSString* const DRSetupPanelDeviceSelectionChangedNotification	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!	
	@constant	DRSetupPanelSelectedDeviceKey
	@abstract	Key in the userInfo dictionary when the
				@link DRSetupPanelDeviceSelectionChangedNotification DRSetupPanelDeviceSelectionChangedNotification @/link is received.
*/
extern NSString* const DRSetupPanelSelectedDeviceKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@category		NSObject(DRSetupPanelDelegate)
	@discussion		This category defines a set of methods that
					delegates of the setup panels can implement to control the 
					behavior of the panel.
*/
@interface NSObject(DRSetupPanelDelegate)

/*!
	@method		setupPanel:deviceCouldBeTarget:
	@abstract	Allows the delegate to determine if device can be used as a target.
	@discussion	This method is used to limit the menu to only those devices that you want
				to appear.  For example, a DVD burning application might use this
				to limit the menu to only devices that are capable of writing DVD-Rs.
	@param		aPanel		The panel.
	@param		device		The candidate device.
	@result		<i>YES</i> if the device is acceptable, <i>NO</i> if not.
*/
- (BOOL) setupPanel:(DRSetupPanel*)aPanel deviceCouldBeTarget:(DRDevice*)device;

/*!
	@method		setupPanelDeviceSelectionChanged:
	@abstract	Sent by the default notification center when the device selection in the
				panel has changed.
	@param		aNotification 	Notification object. This is always @link DRSetupPanelDeviceSelectionChangedNotification DRSetupPanelDeviceSelectionChangedNotification @/link. You can 
								retrieve the DRSetupPanel object in question by sending @link //apple_ref/occ/instm/NSNotification/object object @/link to aNotification. 
								The userInfo dictionary contains the single key DRSetupPanelSelectedDeviceKey whose
								value is the @link //apple_ref/occ/cl/DRDevice DRDevice @/link object that is currently selected.
*/
- (void) setupPanelDeviceSelectionChanged:(NSNotification*)aNotification;

/*!
	@method		setupPanelShouldHandleMediaReservations:
	@abstract	This delegate method allows the delegate to control how media reservations are handled.
	@param		aPanel 	The setup panel sending the message.
	@result		Return <i>NO</i> to indicate the delegate will handle media reservations. Return <i>YES</i> to
				indicate the setupPanel should handle media reservations itself.
*/
- (BOOL) setupPanelShouldHandleMediaReservations:(DRSetupPanel*)aPanel;

/*!
	@method		setupPanel:deviceContainsSuitableMedia:promptString:
	@abstract	This delegate method allows the delegate to determine if the media inserted in the 
				device is suitable for whatever operation is to be performed.
	@param		aPanel 	The setup panel sending the message.
	@param		device 	The device that contains the media being asked about.
	@param		prompt 	A pointer to storage for an NSString. Pass back an NSString object describing 
						the media state.
	@result		Return <i>NO</i> to disable the default button.
*/
- (BOOL) setupPanel:(DRSetupPanel*)aPanel deviceContainsSuitableMedia:(DRDevice*)device promptString:(NSString**)prompt;

@end
