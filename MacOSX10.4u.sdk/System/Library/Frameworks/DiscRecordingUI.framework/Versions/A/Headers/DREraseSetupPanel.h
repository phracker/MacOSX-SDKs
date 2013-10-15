/*
     File:       DiscRecordingUI/DREraseSetupPanel.h
 
     Contains:   Panel to create and configure a DRErase object.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header			DREraseSetupPanel.h
	@abstract		Panel to create and configure a DRErase object.
	@discussion		The @link //apple_ref/occ/cl/DREraseSetupPanel DREraseSetupPanel @/link supports choosing the 
					device to use and what sort of erase to perform.
*/

#import <DiscRecording/DiscRecording.h>
#import <DiscRecordingUI/DRSetupPanel.h>

/*!
	@class			DREraseSetupPanel
	@abstract		Manages a panel that allows users to specify the
					parameters of an erase. 
	@discussion		This class supports choosing the 
					device to use and what sort of erase to perform.
					
					When the panel is closed by the user choosing to
					erase the media in the device, the device is
					exclusively held by the application for its own use
					to prevent possible bad or corrupt media from
					causing problem for the rest of the system. This
					means that if the erase object obtained from the
					panel is not used to do an erase, the device will
					remain unavailable to other applications until the
					exclusive access is released.
*/
@interface DREraseSetupPanel : DRSetupPanel
{
    /*All instance variables are private*/
	IBOutlet NSMatrix*		_eraseTypes;
	void*					_reservedEraseSetupPanel[2];
	void*					_esp_privateStorage;
}

/* --------------------------------------------------------------------------- */
/* Panel creation */

/*! 
   @method 			setupPanel
   @abstract 		Returns an instance of a erase setup panel.
   @result  		An erase setup panel.
*/
+ (DREraseSetupPanel*) setupPanel;

/* --------------------------------------------------------------------------- */
/* Getting the configured erase object */

/*! 
	@method 	eraseObject
	@abstract	Creates and returns a new DRErase object that's configured to erase the disc in the currently selected device.
	@discussion	The new DRErase object is configured based on the settings in the setup panel
				when the user clicks the OK button.
				
				Do not invoke this method within a modal session (@link //apple_ref/occ/instm/DRSetupPanel/runSetupPanel runSetupPanel @/link or
				@link //apple_ref/occ/instm/DRSetupPanel/beginSetupSheetForWindow:modalDelegate:didEndSelector:contextInfo: beginSetupSheetForWindow:modalDelegate:didEndSelector:contextInfo: @/link)
				because the erase object information is only updated just before the
				modal session ends.
	@result  	A new DRErase object.
*/
- (DRErase*) eraseObject;

/* --------------------------------------------------------------------------- */
/* IB actions */

/*! 
   @method 			eraseType:
   @abstract 		Invoked when the user clicks one of the panel's 
   					erase type radio buttons.
   @param 			sender	The object that invoked this method.
*/
- (IBAction) eraseType:(id) sender;

@end
