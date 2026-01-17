/*
     File:       DiscRecordingUI/DRBurnProgressPanel.h
 
     Contains:   Panel to display progress while burning data to media.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	
	@header 		DRBurnProgressPanel.h
	@abstract		Run and display progress while burning data to media.
	@discussion 	A @link //apple_ref/occ/cl/DRBurnProgressPanel DRBurnProgressPanel @/link object manages a panel that displays 
					and updates burn progress. The burn panel is responsible 
					for begining the burn. 
					
					The burn is begun and a progress panel is displayed on screen 
					by calling @link //apple_ref/occ/instm/DRBurnProgressPanel/beginProgressSheetForBurn:layout:modalForWindow: beginProgressSheetForBurn:layout:modalForWindow: @/link
					if a sheet interface is desired, or 
					@link //apple_ref/occ/instm/DRBurnProgressPanel/beginProgressPanelForBurn:layout: beginProgressPanelForBurn:layout: @/link for a non-modal panel.

					A @link //apple_ref/occ/cl/DRBurnProgressPanel DRBurnProgressPanel @/link sends a 
					@link //apple_ref/occ/instm/NSObject/burnProgressPanel:burnDidFinish: burnProgressPanel:burnDidFinish: @/link message to it's delegate 
					when the burn completes. This method allows the delegate 
					to take over end-of-burn handling from the burn progress 
					panel to customize error dialogs or user notification.
*/

#import <Cocoa/Cocoa.h>
#import <DiscRecording/DiscRecording.h>
#import <AvailabilityMacros.h>

/*!
	@const		DRBurnProgressPanelWillBeginNotification
	@abstract	Posted when the @link //apple_ref/occ/cl/DRBurnProgressPanel DRBurnProgressPanel @/link is about to begin
				displaying progress.
	@discussion	This notification contains a notification object but
				no userInfo dictionary. The notification object is the
				@link //apple_ref/occ/cl/DRBurnProgressPanel DRBurnProgressPanel @/link that will be displayed.
*/ 

extern NSString* const DRBurnProgressPanelWillBeginNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! 
	@const			DRBurnProgressPanelDidFinishNotification
	@abstract		Posted when the @link //apple_ref/occ/cl/DRBurnProgressPanel DRBurnProgressPanel @/link has finished 
					and is about to go away.
	@discussion		This notification contains a notification object but 
					no userInfo dictionary. The notification object is the 
					@link //apple_ref/occ/cl/DRBurnProgressPanel DRBurnProgressPanel @/link that will be closed.
*/
extern NSString* const DRBurnProgressPanelDidFinishNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! 
	@class			DRBurnProgressPanel
	@abstract 		Manages a panel that displays progress while burning data to media.
	@discussion		A DRBurnProgressPanel object manages a panel that displays 
					and updates burn progress. The burn panel is responsible 
					for begining the burn. 
					
					The burn is begun and a progress panel is displayed on screen 
					by calling @link //apple_ref/occ/instm/DRBurnProgressPanel/beginProgressSheetForBurn:layout:modalForWindow: beginProgressSheetForBurn:layout:modalForWindow: @/link
					if a sheet interface is desired, or 
					@link //apple_ref/occ/instm/DRBurnProgressPanel/beginProgressPanelForBurn:layout: beginProgressPanelForBurn:layout: @/link for a non-modal panel.

					A DRBurnProgressPanel sends a 
					@link //apple_ref/occ/instm/NSObject/burnProgressPanel:burnDidFinish: burnProgressPanel:burnDidFinish: @/link message to it's delegate 
					when the burn completes. This method allows the delegate 
					to take over end-of-burn handling from the burn progress 
					panel to customize error dialogs or user notification.
*/
@interface DRBurnProgressPanel : NSPanel
{
    /*All instance variables are private*/
	IBOutlet NSTextField*			_status;
	IBOutlet NSTextField*			_taskDescription;
	IBOutlet NSProgressIndicator*	_progress;
	IBOutlet NSImageView*			_icon;
	IBOutlet NSButton*				_stopButton;
	
	id						_owner;
	DRBurn*					_burnObject;
	NSSound*				_successSound;
	NSSound*				_failureSound;
	NSString*				_description;
 	BOOL					_verbose;
	NSString*				_curState;
}

/*! 
	@method			progressPanel
	@abstract		Creates and returns an instance of the burn progress panel.
	@result			A pointer to the newly created DRBurnProgressPanel.
*/
+ (DRBurnProgressPanel*) progressPanel;

/*!
	@method			beginProgressSheetForBurn:layout:modalForWindow:
	@abstract		Presents the progress panel as a sheet and begins the burn process.
	@discussion		This method returns control to the caller after it has displayed the 
					progress sheet and begun the burn. Once the method has returned the
					caller can perform other operations while the burn continues.
	@param			burn		The object performing the burn.
	@param			layout		The data to be burned to disc. See the
								@link //apple_ref/occ/cl/DRBurn DRBurn @/link documentation for information on
								valid layouts.
	@param			docWindow	The window the sheet will be attached to. If docWindow is 
								not nil, the panel slides down as a sheet running as a 
								document modal window. If owner is nil, this is an error.
*/
- (void) beginProgressSheetForBurn:(DRBurn*)burn layout:(id)layout modalForWindow:(NSWindow *)docWindow;

/*!
	@method			beginProgressPanelForBurn:layout:
	@abstract		Presents the progress panel on screen and begins the burn process.
	@discussion		This method returns control to the caller after it has displayed the 
					progress sheet and begun the burn. Once the method has returned the
					caller can perform other operations while the burn continues.
	@param			burn		The object performing the burn.
	@param			layout		The data to be burned to disc. See the
								@link //apple_ref/occ/cl/DRBurn DRBurn @/link documentation for information on
								valid layouts.
*/
- (void) beginProgressPanelForBurn:(DRBurn*)burn layout:(id)layout;

/*! 
	@method			setDescription:
	@abstract		Sets the panel text displayed to the user.
	@discussion		The panel's description is typically a short text string that gives an 
					indication to the user what operation is being performed. If no description
					is explicitly set, the progress panel uses a standard text string suitable
					to the burn.
	@param			description	The text to display.
*/
- (void) setDescription:(NSString*)description;

/*!
	@method			description
	@abstract		Returns the description string displayed in the panel.
	@discussion		If no description is explicitly set, this method will return the standard
					text string.
	@result			An NSString containing the text of the description.
*/
- (NSString*) description;

/*!
	@method			setVerboseProgressStatus:
	@abstract		Sets the vebosity of the progress feedback.
	@discussion		If verbose is <i>YES</i>, the panel will update status for every change. 
					If verbose is <i>NO</i>, the panel will filter some status messages and 
					only update for major changes. The default for the panel is filter the 
					status messages.
	@param			verbose	A BOOL value indicating how detailed the status panel feedback should be.
*/
- (void) setVerboseProgressStatus:(BOOL)verbose;

/*!
	@method			verboseProgressStatus
	@abstract		Returns the vebosity of the panel.
	@discussion		This method will return <i>YES</i> if the panel will update status 
					for every change and <i>NO</i> if the panel will filter some status 
					messages and only update for major changes.
	@result 		A BOOL value indicating how detailed the status panel feedback is.
*/
- (BOOL) verboseProgressStatus;

/*! 
	@method			stopBurn:
	@abstract		Invoked when the user clicks the panel's stop button.
*/
- (IBAction) stopBurn:(id)sender;

@end

/*!
   	@category		NSObject (DRBurnProgressPanelDelegateMethods)
	@discussion		This category defines a set of methods that
					delegates of the burn progress panel can implement to control the 
					behavior of the panel.
*/
@interface NSObject (DRBurnProgressPanelDelegateMethods)

/*!
	@method			burnProgressPanelWillBegin:
	@abstract		Notification sent by the panel before display.
	@discussion		If the delegate implements this method 
					it will receive the message immediately before the panel is displayed. 
	@param			aNotification	Always @link //apple_ref/occ/data/DRBurnProgressPanelWillBeginNotification DRBurnProgressPanelWillBeginNotification @/link. 
					You can retrieve the DRBurnProgressPanel object in question by sending
					@link //apple_ref/occ/instm/NSNotification/object object @/link message to aNotification.
*/
- (void) burnProgressPanelWillBegin:(NSNotification*)aNotification;

/*!
	@method			burnProgressPanelDidFinish:
	@abstract		Notification sent by the panel after ordering out.
	@discussion		If the delegate implements this method 
					it will receive the message after the panel is removed from display.
	@param			aNotification	Always @link //apple_ref/occ/data/DRBurnProgressPanelDidFinishNotification DRBurnProgressPanelDidFinishNotification @/link. 
					You can retrieve the DRBurnProgressPanel object in question by sending
					@link //apple_ref/occ/instm/NSNotification/object object @/link message to aNotification.
*/
- (void) burnProgressPanelDidFinish:(NSNotification*)aNotification;

/*! 
	@method			burnProgressPanel:burnDidFinish:
	@abstract		Allows the delegate to handle the end-of-burn feedback.
	@discussion		This method allows the delegate to handle or modify the end-of-burn
					feedback performed by the progress panel. Return <i>YES</i> to indicate the 
					delegate handled the burn completion and the standard feedback should 
					be supressed. If this method returns <i>NO</i>, the normal end-of-burn 
					handling is performed (displaying an error if appropriate, playing an 
					"I'm done" sound, etc).
					The delegate is messaged before the progress panel is ordered out so 
					a sheet may be displayed on a progress panel displayed as a window.
	@param			theBurnPanel	The progress panel
	@param			burn			The object that performed the burn.
	@result			A BOOL indicating whether the normal end-of-burn feedback should occur.
*/
- (BOOL) burnProgressPanel:(DRBurnProgressPanel*)theBurnPanel burnDidFinish:(DRBurn*)burn;

@end
