/*
     File:       DiscRecordingUI/DREraseProgressPanel.h
 
     Contains:   Panel to display progress while erasing media.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Cocoa/Cocoa.h>
#import <DiscRecording/DiscRecording.h>
#import <AvailabilityMacros.h>

/*" Posted when the DREraseProgressPanel is about to begin displaying progress.

	This notification contains a notification object but no userInfo 
	dictionary. The notification object is the DREraseProgressPanel that
	will be displayed.
"*/
extern NSString* const DREraseProgressPanelWillBeginNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*" Posted when the DREraseProgressPanel has finished and is about to go away.

	This notification contains a notification object but no userInfo 
	dictionary. The notification object is the DREraseProgressPanel that
	will be closed.
"*/
extern NSString* const DREraseProgressPanelDidFinishNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*" A DREraseProgressPanel object manages a panel that displays and updates erase progress. 
	The erase panel is responsible for begining the erase. You start the erase and
	display the progress panel on screen by calling #beginProgressSheetForErase:modalForWindow:
	if you want a sheet interface, or beginProgressPanelForErase: if you want a non-modal
	panel. 
	
	A DREraseProgressPanel is able to send an #eraseProgressPanel:eraseDidFinish: message
	to it's delegate when the erase completes. This method allows the delegate to take over 
	end-of-erase handling from the erase progress panel to customize error dialogs or
	user notification. "*/
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

/*" Creating a DREraseProgressPanel "*/
+ (DREraseProgressPanel*) progressPanel;

/*" Displaying progress for an erase "*/
- (void) beginProgressSheetForErase:(DRErase*)erase modalForWindow:(NSWindow *)docWindow;
- (void) beginProgressPanelForErase:(DRErase*)erase;

/*" Customizing the progress panel "*/
- (void) setDescription:(NSString*)description;
- (NSString*) description;

@end

@interface NSObject (DREraseProgressPanelDelegateMethods)

/*" Sent by the default notification center immediately before a DREraseProgressPanel is displayed. 
	aNotification is always DREraseProgressPanelWillBeginNotification. You can retrieve the 
	DREraseProgressPanel object in question by sending #object to aNotification. "*/
- (void) eraseProgressPanelWillBegin:(NSNotification*)aNotification;

/*" Sent by the default notification center immediately before a DREraseProgressPanel is closed. 
	aNotification is always DREraseProgressPanelDidFinishNotification. You can retrieve the 
	DREraseProgressPanel object in question by sending #object to aNotification. "*/
- (void) eraseProgressPanelDidFinish:(NSNotification*)aNotification;

/*" Sent directly by the DREraseProgressPanel to the delegate.
	This delegate method allows the delegate to handle the erase completion.
	Return %YES to indicate the delegate handled the erase completion. If this
	method returns %NO, the normal end-of-erase handling is performed 
	(displaying an error if appropriate, playing the "I'm done" sound, etc).
	The delegate is messaged before the progress panel is ordered out.
"*/
- (BOOL) eraseProgressPanel:(DREraseProgressPanel*)theErasePanel eraseDidFinish:(DRErase*)erase;

@end
