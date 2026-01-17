/*
 *  NSPreferencePane.h
 *  PreferencePanes
 *
 *  Copyright (c) 2001 Apple. All rights reserved.
 *
 */

#import <Cocoa/Cocoa.h>

typedef enum NSPreferencePaneUnselectReply
{
    NSUnselectCancel = 0,
    NSUnselectNow = 1,
    NSUnselectLater = 2
} NSPreferencePaneUnselectReply;

extern NSString *NSPreferencePaneDoUnselectNotification;
extern NSString *NSPreferencePaneCancelUnselectNotification;


// Help Menu support
#define	kNSPrefPaneHelpMenuInfoPListKey			@"NSPrefPaneHelpAnchors"
#define	kNSPrefPaneHelpMenuTitleKey				@"title"		
#define	kNSPrefPaneHelpMenuAnchorKey			@"anchor"				


@interface NSPreferencePane : NSObject
{
	@private
		//  Connect the _window outlet to a window in your main nib file.
		//  The loadMainView method will remove the content view from this
		//  window and set the main view of the preference pane to be the
		//  content view.  The window is then disposed.
		IBOutlet NSWindow *_window;
	
		//  Connect these outlets to the initial, first and last keyboard
		//  focus chain views.  These views MUST be subviews of the main view.
		IBOutlet NSView *_initialKeyView;
		IBOutlet NSView *_firstKeyView;
		IBOutlet NSView *_lastKeyView;
	
		NSView *_mainView;
		
		NSBundle *_bundle;
	
		id _reserved1;
		id _reserved2;
		id _reserved3;
}

- (id)initWithBundle:(NSBundle *) bundle;

- (NSBundle *) bundle;

//
//  loadMainView loads the main nib file and invokes assignMainView to
//  set the main view of the preference pane.
//
//  NSPreferencePane subclasses should rarely need to override this method.
//
//  Override loadMainView if your NSPreferencePane subclass needs to use
//  a non-nib based technique for creating the main view.  loadMainView
//  should call setMainView: to set the main view of the preference pane
//  before it returns.  It should also call setInitialKeyView, setFirstKeyView
//  and setLastKeyView to set the initial, first and last keyboard focus views
//  respectively.
//
- (NSView *) loadMainView;

//
//  mainViewDidLoad is invoked by the default implementation of loadMainView
//  after the main nib file has been loaded and the main view of the preference
//  pane has been set.  The default implementation does nothing.  Override
//  this method to perform any setup that must be performed after the main
//  nib file has been loaded and the main view has been set.
//
- (void) mainViewDidLoad;

//
//  mainNibName is invoked by the default implementation of loadMainView.
//
//  The default implementation returns the value of the NSMainNibFile key
//  in the bundle's Info plist. You can override this if you want to
//  dynamically select the main nib file for this preference.
//
//  The value returned must NOT include the ".nib" extension.
//
- (NSString *) mainNibName;

//
//  assignMainView is invoked by the default implementation of loadMainView,
//  immediately after the main nib file has been loaded.  This method extracts
//  the content view from the window referenced by the _window
//  outlet and makes this view the main view of the preference pane.
//
//  Override assignMainView if your NSPreferencePane subclass needs to
//  dynamically choose a main view.  assignMainView should call setMainView:
//  to set the main view of the preference pane before it returns.  It should
//  also call setInitialKeyView, setFirstKeyView and setLastKeyView to set the
//  initial, first and last keyboard focus views respectively.
//
- (void) assignMainView;

//
//  These messages get sent to the a preference panel just before and
//  just after it becomes the currently selected preference panel.
//
- (void) willSelect;
- (void) didSelect;

//
//  Override shouldUnselect if your panel needs to cancel or delay an unselect
//  action.  The default implementation always returns NSUnselectNow.  If your
//  subclass overrides this method to return NSUnselectLater, it must call 
//  replyToShouldUnselect: when it has determined whether or not to allow the
//  unselect to occur.
//
- (NSPreferencePaneUnselectReply) shouldUnselect;

//
//  If you override shouldUnselect to return NSUnselectLater, you must call
//  replyToShouldUnselect when you have determined whether or not to unselect
//  the preference pane.
//
- (void) replyToShouldUnselect:(BOOL)shouldUnselect;

//
//  The willUnselect message gets sent to the currently selected preference panel
//  just before and just after it gets swapped out for another preference panel
//
- (void) willUnselect;
- (void) didUnselect;

//
//  Sets the main view of the preference pane. NSPreferencePane subclasses should
//  not need to call this directly unless they override loadMainView or
//  assignMainView.
//
- (void) setMainView:(NSView *)view;

//
//  Returns the main view of the preference pane.
//
- (NSView *) mainView;

//
//  Returns the view that should have the keyboard focus when the pane is selected.
//  The default implementation returns the _initialKeyView ivar which is an outlet
//  that can be connected in the nib file.
//
//  A subclass can override this method if it needs to determine the
//  initial key view dynamically.
//
- (NSView *) initialKeyView;

//
//  Sets _initialKeyView to view.
//
- (void) setInitialKeyView:(NSView *)view;

//
//  Returns the view that is the first view in the keyboard focus chain.
//  The default implementation returns the _firstKeyView ivar which is an outlet
//  that can be connected in the nib file.
//
//  A subclass can override this method if it needs to determine the
//  first key view dynamically.
//
- (NSView *) firstKeyView;

//
//  Sets _firstKeyView to view.
//
- (void) setFirstKeyView:(NSView *)view;

//
//  Returns the view that is the last view in the keyboard focus chain.
//  The default implementation returns the _lastKeyView ivar which is an outlet
//  that can be connected in the nib file.
//
//  A subclass can override this method if it needs to determine the
//  last key view dynamically.
//
- (NSView *) lastKeyView;

//
//  Sets _lastKeyView to view.
//
- (void) setLastKeyView:(NSView *)view;

// Default = YES
// If set to YES, text fields will be forced to give up their responder status
// before shouldUnselect is called on the preference pane.
// If overriden and set to NO, the preference pane will be responsible for 
// forcing the fields to give up their responder status before saving them.
//
- (BOOL) autoSaveTextFields;

// Returns YES if preference pane is currently selected by user,
// NO otherwise
//
- (BOOL) isSelected;

// Help Menu support
// A subclass can override this method if it needs to update help menu
// dynamically. If you have static help menu items specify them under
// @"NSPrefPaneHelpAnchors" key in Info.plist instead.
//
// Array must contain dictionaries with following keys:
//	<dict>					- describes every help menu item
//		<key>title</key>	- localized title for help menu item
//		<key>anchor</key>	- anchor reference for AHLookupAnchor as string
//	</dict>
//
- (void) updateHelpMenuWithArray:(NSArray *)inArrayOfMenuItems;
@end

