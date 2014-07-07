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

#import <Cocoa/Cocoa.h>
#import <DiscRecording/DiscRecording.h>
#import <AvailabilityMacros.h>

/*" Posted when the DRBurnProgressPanel is about to begin displaying progress.

	This notification contains a notification object but no userInfo 
	dictionary. The notification object is the DRBurnProgressPanel that
	will be displayed.
"*/
extern NSString* const DRBurnProgressPanelWillBeginNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*" Posted when the DRBurnProgressPanel has finished and is about to go away.

	This notification contains a notification object but no userInfo 
	dictionary. The notification object is the DRBurnProgressPanel that
	will be closed.
"*/
extern NSString* const DRBurnProgressPanelDidFinishNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*" A DRBurnProgressPanel object manages a panel that displays and updates burn progress. 
	The burn panel is responsible for begining the burn. You start the burn and
	display the progress panel on screen by calling #beginProgressSheetForBurn:modalForWindow:
	if you want a sheet interface, or beginProgressPanelForBurn: if you want a non-modal
	panel. 
	
	A DRBurnProgressPanel is able to send a #burnProgressPanel:burnDidFinish: message
	to it's delegate when the burn completes. This method allows the delegate to take over 
	end-of-burn handling from the burn progress panel to customize error dialogs or
	user notification. "*/
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

/*" Creating a DRBurnProgressPanel "*/
+ (DRBurnProgressPanel*) progressPanel;

/*" Displaying progress for a burn "*/
- (void) beginProgressSheetForBurn:(DRBurn*)burn layout:(id)layout modalForWindow:(NSWindow *)docWindow;
- (void) beginProgressPanelForBurn:(DRBurn*)burn layout:(id)layout;

/*" Customizing the progress panel "*/
- (void) setDescription:(NSString*)description;
- (NSString*) description;

- (void) setVerboseProgressStatus:(BOOL)verbose;
- (BOOL) verboseProgressStatus;

/*" Action methods "*/
- (IBAction) stopBurn:(id)sender;

@end

@interface NSObject (DRBurnProgressPanelDelegateMethods)

/*" Sent by the default notification center immediately before a DRBurnProgressPanel is displayed. 
	aNotification is always DRBurnProgressPanelWillBeginNotification. You can retrieve the 
	DRBurnProgressPanel object in question by sending #object to aNotification. "*/
- (void) burnProgressPanelWillBegin:(NSNotification*)aNotification;

/*" Sent by the default notification center immediately before a DRBurnProgressPanel is closed. 
	aNotification is always DRBurnProgressPanelDidFinishNotification. You can retrieve the 
	DRBurnProgressPanel object in question by sending #object to aNotification. "*/
- (void) burnProgressPanelDidFinish:(NSNotification*)aNotification;

/*" Sent directly by the DRBurnProgressPanel to the delegate.
	This delegate method allows the delegate to handle the burn completion.
	Return %YES to indicate the delegate handled the burn completion. If this
	method returns %NO, the normal end-of-burn handling is performed 
	(displaying an error if appropriate, playing the "I'm done" sound, etc).
	The delegate is messaged before the progress panel is ordered out.
"*/
- (BOOL) burnProgressPanel:(DRBurnProgressPanel*)theBurnPanel burnDidFinish:(DRBurn*)burn;

@end
