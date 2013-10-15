/*
     File:       DiscRecordingUI/DRBurnSetupPanel.h
 
     Contains:   Panel to create and configure a DRBurn object.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header		DRBurnSetupPanel.h
	@abstract	Panel to create and configure a @link //apple_ref/occ/cl/DRBurn DRBurn @/link object.
	@discussion The @link //apple_ref/occ/cl/DRBurnSetupPanel DRBurnSetupPanel @/link supports choosing the the device to use, whether or not
				to verify the burned data and how to handle the burned disc when it completes.
*/

#import <DiscRecording/DiscRecording.h>
#import <DiscRecordingUI/DRSetupPanel.h>

/*!
	@class		DRBurnSetupPanel
	@abstract 	Manages a panel that allows users to specify the parameters of an burn.
	@discussion	This class supports choosing the the device to use, whether or not
				to verify the burned data and how to handle the burned disc when it completes.
*/
@interface DRBurnSetupPanel : DRSetupPanel
{
    /*All instance variables are private*/
	IBOutlet id				_advancedItems;
	IBOutlet NSButton*		_expander;
	IBOutlet NSPopUpButton*	_burnSpeedPopup;
	IBOutlet NSButton*		_appendable;
	IBOutlet NSMatrix*		_completionActions;
	IBOutlet NSButton*		_testBurn;
	IBOutlet NSButton*		_verifyBurn;
	IBOutlet NSButton*		_eraseDisc;
	void*					_reservedBurnSetupPanel[4];
	void*					_bsp_privateStorage;
}

/* ----------------------------------------------------------------------------- */
/*	Panel creation */

/*!
	@method		setupPanel
	@abstract	Creates and return an instance of a burn setup panel.
	@result		A pointer to the newly created DRBurnSetupPanel.
*/
+ (DRBurnSetupPanel*) setupPanel;

/* ----------------------------------------------------------------------------- */
/*	Configuring the panel */

/*!
	@method		setDefaultButtonTitle:
	@abstract	Sets the title for the receiver's default button to title.
	@discussion	Normally, the default button is &ldquo;Burn&rdquo;.
*/
- (void) setDefaultButtonTitle:(NSString*)title;

/*!
	@method		setCanSelectTestBurn:
	@abstract	Specifies whether the user can choose to make a test burn.
	@discussion	This method controls whether a checkbox should be added to the
				receiver that allows the user to set the burn to be a test burn.
				By default, the test burn button is not displayed.
				
				This method must be called before the panel is displayed.
	
	@param		flag	<i>YES</i> to show the test burn checkbox, <i>NO</i> to hide it.
*/
- (void) setCanSelectTestBurn:(BOOL)flag;

/*!
	@method		setCanSelectAppendableMedia:
	@abstract	Specifies whether the user can choose to leave the disc appendable.
	@discussion	This method controls whether the appendable checkbox is enabled.
	
				If the data being writen to disc does not lend itself to having more data
				appended on to it, you can disable the ability of the user to leave the disc
				open.
				 
				This method must be called before the panel is displayed.
	@param		flag	<i>YES</i> to enable the appendable checkbox, <i>NO</i> to disable.
*/
- (void) setCanSelectAppendableMedia:(BOOL)flag;

/* ----------------------------------------------------------------------------- */
/* Getting the configured burn object */

/*!
	@method		burnObject
	@abstract	Creates and returns a new DRBurn object that's configured to write
				data to the currently selected device.
	@discussion	The new DRBurn object is configured based on the settings in the setup panel
				when the user clicks the OK button.
				
				Do not invoke this method within a modal session ( @link //apple_ref/occ/instm/DRSetupPanel/runSetupPanel runSetupPanel @/link or
				@link //apple_ref/occ/instm/DRSetupPanel/beginSetupSheetForWindow:modalDelegate:didEndSelector:contextInfo: beginSetupSheetForWindow:modalDelegate:didEndSelector:contextInfo: @/link )
				because the burn object information is only updated just before the
				modal session ends.
   @result  	A new DRBurn object.
*/
- (DRBurn*) burnObject;

/* ----------------------------------------------------------------------------- */
/* IB actions */

/*!
	@method		expand:
	@abstract	Invoked when the user clicks the panel's expand button.
*/
- (IBAction) expand:(id) sender;

/*!
	@method		burnSpeed:
	@abstract	Invoked when the user clicks the panel's burn speed popup button.
*/
- (IBAction) burnSpeed:(id) sender;

/*!
	@method		appendable:
	@abstract	Invoked when the user clicks the panel's appendable checkbox.
*/
- (IBAction) appendable:(id) sender;

/*!
	@method		completionAction:
	@abstract	Invoked when the user clicks one of the panel's completion action radio buttons.
*/
- (IBAction) completionAction:(id) sender;

/*!
	@method		testBurn:
	@abstract	Invoked when the user clicks the panel's test burn checkbox.
*/
- (IBAction) testBurn:(id) sender;

/*!
	@method		verifyBurn:
	@abstract	Invoked when the user clicks the panel's verify burn checkbox.
*/
- (IBAction) verifyBurn:(id) sender;

@end

/*!
	@const		DRBurnSetupPanelDefaultButtonDefaultTitle
	@discussion	Passing this to @link //apple_ref/occ/instm/DRBurnSetupPanel/setDefaultButtonTitle: setDefaultButtonTitle: @/link causes the panel to redisplay the 
				default button title.
*/ 
extern NSString* const DRBurnSetupPanelDefaultButtonDefaultTitle AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
