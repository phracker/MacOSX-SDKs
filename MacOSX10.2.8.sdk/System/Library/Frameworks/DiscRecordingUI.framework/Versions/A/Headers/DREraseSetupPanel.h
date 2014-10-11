/*
     File:       DiscRecordingUI/DREraseSetupPanel.h
 
     Contains:   Panel to create and configure a DRErase object.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <DiscRecordingUI/DRSetupPanel.h>
#import <DiscRecording/DRErase.h>

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
					esclusive access is released.
*/
@interface DREraseSetupPanel : DRSetupPanel
{
    /*All instance variables are private*/
	IBOutlet NSMatrix*		_eraseTypes;

	id						_state;
	int						_exclusivity;
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
   @method 			eraseObject
   @abstract 		Returns a configured DRErase object which is ready 
   					to the disc in the currently selected device.
   @discussion		Do not invoke this method within a modal session
					(<b>runSetupPanel</b> or
					<b>setupPanelForWindow:modalDelegate:didEndSelector:contextInfo:</b>) 
					because the erase object information is
					only updated just before the modal session ends.
   @result  		A DRErase object.
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
