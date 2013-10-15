/*
     File:       DiscRecordingUI/DREraseProgressPanel.h
 
     Contains:   Panel to display progress while erasing media.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	
	@header 		DREraseProgressPanel.h
	@abstract		Panel to display progress while erasing media.
	@discussion		A @link //apple_ref/occ/cl/DREraseProgressPanel DREraseProgressPanel @/link object manages a panel that displays 
					and updates erase progress. The erase panel is responsible 
					for begining the erase. 
					
					The erase is begun and a progress panel is displayed on screen 
					by calling @link //apple_ref/occ/instm/DREraseProgressPanel/beginProgressSheetForErase:modalForWindow: beginProgressSheetForErase:modalForWindow: @/link 
					if a sheet interface is desired, or 
					@link //apple_ref/occ/instm/DREraseProgressPanel/beginProgressPanelForErase: beginProgressPanelForErase:  @/link for a non-modal panel.

					A @link //apple_ref/occ/cl/DREraseProgressPanel DREraseProgressPanel @/link sends a 
					@link //apple_ref/occ/instm/NSObject/eraseProgressPanel:eraseDidFinish: eraseProgressPanel:eraseDidFinish: @/link message to it's delegate 
					when the erase completes. This method allows the delegate 
					to take over end-of-erase handling from the erase progress 
					panel to customize error dialogs or user notification.
*/

#import <Cocoa/Cocoa.h>
#import <DiscRecording/DiscRecording.h>
#import <AvailabilityMacros.h>

/*! 	
	@const			DREraseProgressPanelWillBeginNotification
	@abstract		Posted when the @link //apple_ref/occ/cl/DREraseProgressPanel DREraseProgressPanel @/link is about to begin 
					displaying progress.
	@discussion		This notification contains a notification object but 
					no userInfo dictionary. The notification object is the 
					@link //apple_ref/occ/cl/DREraseProgressPanel DREraseProgressPanel @/link thatwill be displayed.
*/
extern NSString* const DREraseProgressPanelWillBeginNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! 
	@const			DREraseProgressPanelDidFinishNotification
	@abstract		Posted when the @link //apple_ref/occ/cl/DREraseProgressPanel DREraseProgressPanel @/link has finished 
					and is about to go away.
	@discussion		This notification contains a notification object but 
					no userInfo dictionary. The notification object is the 
					@link //apple_ref/occ/cl/DREraseProgressPanel DREraseProgressPanel @/link that will be closed.
*/
extern NSString* const DREraseProgressPanelDidFinishNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@class			DREraseProgressPanel
	@abstract 		Manages a panel that displays progress while erasing media.
	@discussion		A DREraseProgressPanel object manages a panel that displays 
					and updates erase progress. The erase panel is responsible 
					for begining the erase. 
					
					The erase is begun and a progress panel is displayed on screen 
					by calling @link //apple_ref/occ/instm/DREraseProgressPanel/beginProgressSheetForErase:modalForWindow: beginProgressSheetForErase:modalForWindow: @/link 
					if a sheet interface is desired, or 
					@link //apple_ref/occ/instm/DREraseProgressPanel/beginProgressPanelForErase: beginProgressPanelForErase:  @/link for a non-modal panel.

					A DREraseProgressPanel sends a 
					@link //apple_ref/occ/instm/NSObject/eraseProgressPanel:eraseDidFinish: eraseProgressPanel:eraseDidFinish: @/link message to it's delegate 
					when the erase completes. This method allows the delegate 
					to take over end-of-erase handling from the erase progress 
					panel to customize error dialogs or user notification.
*/
@interface DREraseProgressPanel : NSPanel
{
    /*All instance variables are private*/
	IBOutlet NSTextField*			_taskDescription;
	IBOutlet NSProgressIndicator*	_progress;
	IBOutlet NSImageView*			_icon;
	
	id						_owner;
	DRErase*				_eraseObject;
	NSSound*				_successSound;
	NSSound*				_failureSound;
	NSString*				_description;
}

/*! 
	@method			progressPanel
	@abstract		Creates and returns an instance of the erase progress panel.
	@result			A pointer to the newly created DREraseProgressPanel.
*/
+ (DREraseProgressPanel*) progressPanel;

/*!
	@method			beginProgressSheetForErase:modalForWindow:
	@abstract		Presents the progress panel as a sheet and begins the erase process.
	@discussion		This method returns control to the caller after it has displayed the 
					progress sheet and begun the erase. Once the method has returned the
					caller can perform other operations while the erase continues.
	@param			erase		The object performing the erase.
	@param			docWindow	The window the sheet will be attached to. If docWindow is 
								not nil, the panel slides down as a sheet running as a 
								document modal window. If owner is nil, this is an error.
*/
- (void) beginProgressSheetForErase:(DRErase*)erase modalForWindow:(NSWindow *)docWindow;

/*!
	@method			beginProgressPanelForErase:
	@abstract		Presents the progress panel on screen and begins the erase process.
	@discussion		This method returns control to the caller after it has displayed the 
					progress sheet and begun the erase. Once the method has returned the
					caller can perform other operations while the erase continues.
	@param			erase		The object performing the erase.
*/
- (void) beginProgressPanelForErase:(DRErase*)erase;

/*! 
	@method			setDescription:
	@abstract		Sets the panel text displayed to the user.
	@discussion		The panel's description is typically a short text string that gives an 
					indication to the user what operation is being performed. If no description
					is explicitly set, the progress panel uses a standard text string suitable
					to the erase.
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

@end

/*!
   	@category		NSObject (DREraseProgressPanelDelegateMethods)
	@discussion		This category defines a set of methods that
					delegates of the burn progress panel can implement to control the 
					behavior of the panel.
*/
@interface NSObject (DREraseProgressPanelDelegateMethods)

/*!
	@method			eraseProgressPanelWillBegin:
	@abstract		Notification sent by the panel before display.
	@discussion		If the delegate implements this method 
					it will receive the message immediately before the panel is displayed. 
	@param			aNotification	Always @link //apple_ref/occ/data/DREraseProgressPanelWillBeginNotification DREraseProgressPanelWillBeginNotification @/link. 
					You can retrieve the DREraseProgressPanel object in question by sending
					@link //apple_ref/occ/instm/NSNotification/object object @/link message to aNotification.
*/
- (void) eraseProgressPanelWillBegin:(NSNotification*)aNotification;

/*!
	@method			eraseProgressPanelDidFinish:
	@abstract		Notification sent by the panel after ordering out.
	@discussion		If the delegate implements this method 
					it will receive the message after the panel is removed from display.
	@param			aNotification	Always @link //apple_ref/occ/data/DREraseProgressPanelDidFinishNotification DREraseProgressPanelDidFinishNotification @/link. 
					You can retrieve the DREraseProgressPanel object in question by sending
					@link //apple_ref/occ/instm/NSNotification/object object @/link message to aNotification.
*/
- (void) eraseProgressPanelDidFinish:(NSNotification*)aNotification;

/*! 
	@method			eraseProgressPanel:eraseDidFinish:
	@abstract		Allows the delegate to handle the end-of-erase feedback.
	@discussion		This method allows the delegate to handle or modify the end-of-erase
					feedback performed by the progress panel. Return <i>YES</i> to indicate the 
					delegate handled the erase completion and the standard feedback should 
					be supressed. If this method returns <i>NO</i>, the normal end-of-erase 
					handling is performed (displaying an error if appropriate, playing an 
					"I'm done" sound, etc).
					The delegate is messaged before the progress panel is ordered out so 
					a sheet may be displayed on a progress panel displayed as a window.
	@param			theErasePanel	The progress panel
	@param			erase			The object that performed the erase.
	@result			A BOOL indicating whether the normal end-of-erase feedback should occur.
*/
- (BOOL) eraseProgressPanel:(DREraseProgressPanel*)theErasePanel eraseDidFinish:(DRErase*)erase;

@end
