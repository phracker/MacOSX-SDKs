/*
 *  NSPreferencePane.h
 *  PreferencePanes
 *
 *  Copyright (c) 2001-2010 Apple. All rights reserved.
 *
 */

#import <Cocoa/Cocoa.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)

typedef NS_ENUM(NSUInteger, NSPreferencePaneUnselectReply)
{
    NSUnselectCancel = 0,
    NSUnselectNow = 1,
    NSUnselectLater = 2
};

extern NSString * __nonnull const 	NSPreferencePaneDoUnselectNotification;
extern NSString * __nonnull const 	NSPreferencePaneCancelUnselectNotification;

extern NSString * __nonnull const	NSPreferencePaneSwitchToPaneNotification;
extern NSString * __nonnull const	NSPreferencePrefPaneIsAvailableNotification;
extern NSString * __nonnull const	NSPreferencePaneUpdateHelpMenuNotification;

// Help Menu support
APPKIT_EXTERN NSString * __nonnull const	NSPrefPaneHelpMenuInfoPListKey;
APPKIT_EXTERN NSString * __nonnull const	NSPrefPaneHelpMenuTitleKey;
APPKIT_EXTERN NSString * __nonnull const	NSPrefPaneHelpMenuAnchorKey;


#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7

#define kNSPrefPaneHelpMenuInfoPListKey		NSPrefPaneHelpMenuInfoPListKey	
#define kNSPrefPaneHelpMenuTitleKey			NSPrefPaneHelpMenuTitleKey		
#define kNSPrefPaneHelpMenuAnchorKey		NSPrefPaneHelpMenuAnchorKey		

#else /* MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_7 */

#define	kNSPrefPaneHelpMenuInfoPListKey		@"NSPrefPaneHelpAnchors"
#define	kNSPrefPaneHelpMenuTitleKey			@"title"		
#define	kNSPrefPaneHelpMenuAnchorKey		@"anchor"

#endif

@interface NSPreferencePane : NSObject
{
	@private
		//  Connect the _window outlet to a window in your main nib file.
		//  The loadMainView method will remove the content view from this
		//  window and set the main view of the preference pane to be the
		//  content view.  The window is then disposed.
		IBOutlet NSWindow * __nullable	_window;
	
		//  Connect these outlets to the initial, first and last keyboard
		//  focus chain views.  These views MUST be subviews of the main view.
		IBOutlet NSView * __nullable		_initialKeyView;
		IBOutlet NSView * __nullable		_firstKeyView;
		IBOutlet NSView * __nullable		_lastKeyView;
	
		NSView * __nonnull		_mainView;
		NSBundle * __nonnull		_bundle;
	
		__nullable id _reserved1;
		__nullable id _reserved2;
		__nullable id _reserved3;
}

- (nonnull instancetype) initWithBundle:(nonnull NSBundle *)bundle;

@property (readonly, strong, nonnull) NSBundle *bundle;

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
- (nonnull NSView *) loadMainView;

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
@property (readonly, strong, nonnull) NSString *mainNibName;

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
@property (readonly) NSPreferencePaneUnselectReply shouldUnselect;

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
//  Returns the main view of the preference pane.
//
@property (strong, nonnull) NSView *mainView;

//
//  Returns the view that should have the keyboard focus when the pane is selected.
//  The default implementation returns the _initialKeyView ivar which is an outlet
//  that can be connected in the nib file.
//
//  A subclass can override this method if it needs to determine the
//  initial key view dynamically.
//
@property (strong, nullable) NSView *initialKeyView;

//
//  Returns the view that is the first view in the keyboard focus chain.
//  The default implementation returns the _firstKeyView ivar which is an outlet
//  that can be connected in the nib file.
//
//  A subclass can override this method if it needs to determine the
//  first key view dynamically.
//
@property (strong, nullable) NSView *firstKeyView;

//
//  Returns the view that is the last view in the keyboard focus chain.
//  The default implementation returns the _lastKeyView ivar which is an outlet
//  that can be connected in the nib file.
//
//  A subclass can override this method if it needs to determine the
//  last key view dynamically.
//
@property (strong, nullable) NSView *lastKeyView;


// Default = YES
// If set to YES, text fields will be forced to give up their responder status
// before shouldUnselect is called on the preference pane.
// If overriden and set to NO, the preference pane will be responsible for 
// forcing the fields to give up their responder status before saving them.
//
@property (readonly) BOOL autoSaveTextFields;

// Returns YES if preference pane is currently selected by user,
// NO otherwise
//
@property (getter=isSelected, readonly) BOOL selected;

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
- (void) updateHelpMenuWithArray:(nullable NSArray<NSDictionary<NSString *, NSString *> *> *)inArrayOfMenuItems;
@end

API_UNAVAILABLE_END
