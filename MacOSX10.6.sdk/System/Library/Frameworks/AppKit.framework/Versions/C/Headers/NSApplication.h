/*
	NSApplication.h
	Application Kit
	Copyright (c) 1994-2009, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSRunningApplication.h>

@class NSDate, NSDictionary, NSError, NSException, NSNotification;
@class NSGraphicsContext, NSImage, NSPasteboard, NSWindow;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
@class NSDockTile;
#endif
@protocol NSApplicationDelegate;

/* The version of the AppKit framework */
APPKIT_EXTERN const double NSAppKitVersionNumber;

#define NSAppKitVersionNumber10_0 577
#define NSAppKitVersionNumber10_1 620
#define NSAppKitVersionNumber10_2 663
#define NSAppKitVersionNumber10_2_3 663.6
#define NSAppKitVersionNumber10_3 743
#define NSAppKitVersionNumber10_3_2 743.14
#define NSAppKitVersionNumber10_3_3 743.2
#define NSAppKitVersionNumber10_3_5 743.24
#define NSAppKitVersionNumber10_3_7 743.33
#define NSAppKitVersionNumber10_3_9 743.36
#define NSAppKitVersionNumber10_4 824
#define NSAppKitVersionNumber10_4_1 824.1
#define NSAppKitVersionNumber10_4_3 824.23
#define NSAppKitVersionNumber10_4_4 824.33
#define NSAppKitVersionNumber10_4_7 824.41
#define NSAppKitVersionNumber10_5 949
#define NSAppKitVersionNumber10_5_2 949.27
#define NSAppKitVersionNumber10_5_3 949.33


/* Modes passed to NSRunLoop */
APPKIT_EXTERN NSString *NSModalPanelRunLoopMode;
APPKIT_EXTERN NSString *NSEventTrackingRunLoopMode;

/* Pre-defined return values for runModalFor: and runModalSession:. The system also reserves all values below these. */
enum {
    NSRunStoppedResponse			= (-1000),
    NSRunAbortedResponse			= (-1001),
    NSRunContinuesResponse		= (-1002)
};

/* used with NSRunLoop's performSelector:target:argument:order:modes: */
enum {
    NSUpdateWindowsRunLoopOrdering		= 500000
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/* Flags that comprise an application's presentationOptions */
enum {
    NSApplicationPresentationDefault                    = 0,
    NSApplicationPresentationAutoHideDock               = (1 <<  0),    // Dock appears when moused to
    NSApplicationPresentationHideDock                   = (1 <<  1),    // Dock is entirely unavailable

    NSApplicationPresentationAutoHideMenuBar            = (1 <<  2),    // Menu Bar appears when moused to
    NSApplicationPresentationHideMenuBar                = (1 <<  3),    // Menu Bar is entirely unavailable

    NSApplicationPresentationDisableAppleMenu           = (1 <<  4),    // all Apple menu items are disabled
    NSApplicationPresentationDisableProcessSwitching    = (1 <<  5),    // Cmd+Tab UI is disabled
    NSApplicationPresentationDisableForceQuit           = (1 <<  6),    // Cmd+Opt+Esc panel is disabled
    NSApplicationPresentationDisableSessionTermination  = (1 <<  7),    // PowerKey panel and Restart/Shut Down/Log Out disabled
    NSApplicationPresentationDisableHideApplication     = (1 <<  8),    // Application "Hide" menu item is disabled
    NSApplicationPresentationDisableMenuBarTransparency = (1 <<  9)     // Menu Bar's transparent appearance is disabled
};
#endif
typedef NSUInteger NSApplicationPresentationOptions;

APPKIT_EXTERN id NSApp;

/* Information used by the system during modal sessions */
typedef struct _NSModalSession *NSModalSession;
// threading information
typedef struct NSThreadPrivate _NSThreadPrivate;

@interface NSApplication : NSResponder <NSUserInterfaceValidations>
{
    /*All instance variables are private*/
    NSEvent            *_currentEvent;
    id     		_windowList;
    id                  _keyWindow;
    id                  _mainWindow;
    id                  _delegate;
    id            	*_hiddenList;
    int                 _hiddenCount;
    NSInteger               _context;
    void		*_appleEventSuspensionID;
    __weak id			_previousKeyWindow;
    short               _unusedApp;
    short               _running;
    struct __appFlags {
	unsigned int        _hidden:1;
	unsigned int        _RESERVED1:1;
	unsigned int        _active:1;
	unsigned int        _hasBeenRun:1;
	unsigned int        _doingUnhide:1;
	unsigned int	    _delegateReturnsValidRequestor:1;
	unsigned int	    _deactPending:1;
	unsigned int        _invalidState:1;
	unsigned int        _invalidEvent:1;
	unsigned int        _postedWindowsNeedUpdateNote:1;
        unsigned int        _wantsToActivate:1;
        unsigned int        _doingHide:1;
	unsigned int	    _dontSendShouldTerminate:1;
        unsigned int        _skipWin32DelayedRestoreKeyWindowAfterHide:1;
        unsigned int        _finishedLaunching:1;
        unsigned int	    _hasEventDelegate:1;
        unsigned int        _appDying:1;
        unsigned int        _didNSOpenOrPrint:1;
        unsigned int	    _inDealloc:1;
        unsigned int	    _pendingDidFinish:1;
        unsigned int	    _hasKeyFocus:1;
        unsigned int	    _panelsNonactivating:1;
        unsigned int	    _hiddenOnLaunch:1;
        unsigned int	    _openStatus:2;
	unsigned int	    _batchOrdering:1;
        unsigned int        _waitingForTerminationReply:1;
        unsigned int        _windowMoveDisabled:1;
	unsigned int        _reserved:4;
    }                   _appFlags;
    id                  _mainMenu;
    id                  _appIcon;
    id                  _nameTable;	// unused
    id                  _eventDelegate;
    _NSThreadPrivate     *_threadingSupport;
}

+ (NSApplication *)sharedApplication;
- (void)setDelegate:(id <NSApplicationDelegate>)anObject;
- (id <NSApplicationDelegate>)delegate;
- (NSGraphicsContext*)context;
- (void)hide:(id)sender;
- (void)unhide:(id)sender;
- (void)unhideWithoutActivation;
- (NSWindow *)windowWithWindowNumber:(NSInteger)windowNum;
- (NSWindow *)mainWindow;
- (NSWindow *)keyWindow;
- (BOOL)isActive;
- (BOOL)isHidden;
- (BOOL)isRunning;
- (void)deactivate;
- (void)activateIgnoringOtherApps:(BOOL)flag;

- (void)hideOtherApplications:(id)sender;
- (void)unhideAllApplications:(id)sender;

- (void)finishLaunching;
- (void)run;
- (NSInteger)runModalForWindow:(NSWindow *)theWindow;
- (void)stop:(id)sender;
- (void)stopModal;
- (void)stopModalWithCode:(NSInteger)returnCode;
- (void)abortModal;
- (NSWindow *)modalWindow;
- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow;
- (NSInteger)runModalSession:(NSModalSession)session;
- (void)endModalSession:(NSModalSession)session;
- (void)terminate:(id)sender;

enum {
      NSCriticalRequest = 0,
      NSInformationalRequest = 10
};
typedef NSUInteger NSRequestUserAttentionType;

// inform the user that this application needs attention - call this method only if your application is not already active
- (NSInteger)requestUserAttention:(NSRequestUserAttentionType)requestType;
- (void)cancelUserAttentionRequest:(NSInteger)request;

/*
**  Present a sheet on the given window.  When the modal session is ended,
** the didEndSelector will be invoked in the modalDelegate.  The didEndSelector
** should have the following signature, and will be invoked when the modal session ends.
** This method should dismiss the sheet using orderOut:
** - (void)sheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
**
*/
- (void)beginSheet:(NSWindow *)sheet modalForWindow:(NSWindow *)docWindow modalDelegate:(id)modalDelegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;
- (void)endSheet:(NSWindow *)sheet;
- (void)endSheet:(NSWindow *)sheet returnCode:(NSInteger)returnCode;

- (NSEvent *)nextEventMatchingMask:(NSUInteger)mask untilDate:(NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSUInteger)mask beforeEvent:(NSEvent *)lastEvent;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
- (NSEvent *)currentEvent;

- (void)sendEvent:(NSEvent *)theEvent;
- (void)preventWindowOrdering;
- (NSWindow *)makeWindowsPerform:(SEL)aSelector inOrder:(BOOL)flag;
- (NSArray *)windows;
- (void)setWindowsNeedUpdate:(BOOL)needUpdate;
- (void)updateWindows;

- (void)setMainMenu:(NSMenu *)aMenu;
- (NSMenu *)mainMenu;

/* Set or get the Help menu for the app.  If a non-nil menu is set as the Help menu, Spotlight for Help will be installed in it; otherwise AppKit will install Spotlight for Help into a menu of its choosing (and that menu is not returned from -helpMenu).  If you wish to completely suppress Spotlight for Help, you can set a menu that does not appear in the menu bar.  NSApplicaton retains its Help menu and releases it when a different menu is set.
 
 */
- (void)setHelpMenu:(NSMenu *)helpMenu AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSMenu *)helpMenu AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)setApplicationIconImage:(NSImage *)image;
- (NSImage *)applicationIconImage;

/* Returns the activation policy of the application.
 */
- (NSApplicationActivationPolicy)activationPolicy AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Attempts to modify the application's activation policy.  Currently, NSApplicationActivationPolicyNone and NSApplicationActivationPolicyAccessory may be changed to NSApplicationActivationPolicyRegular, but other modifications are not supported.  This returns YES if setting the activation policy is successful, and NO if not.
 */
- (BOOL)setActivationPolicy:(NSApplicationActivationPolicy)activationPolicy AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSDockTile *)dockTile;
#endif

- (BOOL)sendAction:(SEL)theAction to:(id)theTarget from:(id)sender;
- (id)targetForAction:(SEL)theAction;
- (id)targetForAction:(SEL)theAction to:(id)theTarget from:(id)sender;
- (BOOL)tryToPerform:(SEL)anAction with:(id)anObject;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;

- (void)reportException:(NSException *)theException;
+ (void)detachDrawingThread:(SEL)selector toTarget:(id)target withObject:(id)argument;

/*  If an application delegate returns NSTerminateLater from -applicationShouldTerminate:, -replyToApplicationShouldTerminate: must be called with YES or NO once the application decides if it can terminate */
- (void)replyToApplicationShouldTerminate:(BOOL)shouldTerminate;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

enum {
    NSApplicationDelegateReplySuccess = 0,
    NSApplicationDelegateReplyCancel = 1,
    NSApplicationDelegateReplyFailure = 2
};
typedef NSUInteger NSApplicationDelegateReply;

/* If an application delegate encounters an error while handling -application:openFiles: or -application:printFiles:, -replyToOpenOrPrint: should be called with NSApplicationDelegateReplyFailure.  If the user cancels the operation, NSApplicationDelegateReplyCancel should be used, and if the operation succeeds, NSApplicationDelegateReplySuccess should be used */
- (void)replyToOpenOrPrint:(NSApplicationDelegateReply)reply;

/* Opens the character palette
*/
- (void)orderFrontCharacterPalette:(id)sender;
#endif

/* Gets or sets the presentationOptions that should be in effect for the system when this application is the active application.  Only certain combinations of NSApplicationPresentationOptions flags are allowed, as detailed in the AppKit Release Notes and the reference documentation for -setPresentationOptions:.  When given an invalid combination of option flags, -setPresentationOptions: raises an exception.
*/
- (NSApplicationPresentationOptions)presentationOptions AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setPresentationOptions:(NSApplicationPresentationOptions)newOptions AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the set of application presentation options that are currently in effect for the system.  These are the presentation options that have been put into effect by the currently active application.
*/
- (NSApplicationPresentationOptions)currentSystemPresentationOptions AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

@interface NSApplication(NSWindowsMenu)
- (void)setWindowsMenu:(NSMenu *)aMenu;
- (NSMenu *)windowsMenu;
- (void)arrangeInFront:(id)sender;
- (void)removeWindowsItem:(NSWindow *)win;
- (void)addWindowsItem:(NSWindow *)win title:(NSString *)aString filename:(BOOL)isFilename;
- (void)changeWindowsItem:(NSWindow *)win title:(NSString *)aString filename:(BOOL)isFilename;
- (void)updateWindowsItem:(NSWindow *)win;
- (void)miniaturizeAll:(id)sender;
@end

@interface NSApplication(NSFullKeyboardAccess)
/* Use this method to get the status of Full Keyboard Access, as configured in the Keyboard preference pane. You may use this status to implement your own key loop or to implement in-control tabbing behavior similar to NSTableView. Because of the nature of the preference storage, you will not be notified of changes to the key if you attempt to observe it via key-value observing; however, calling this method is fairly inexpensive, so you should always call it when you need the underlying value instead of caching it.
 */
- (BOOL)isFullKeyboardAccessEnabled AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
@end

// return values for -applicationShouldTerminate:
enum {
        NSTerminateCancel = 0,
        NSTerminateNow = 1, 
        NSTerminateLater = 2
};
typedef NSUInteger NSApplicationTerminateReply;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
// return values for -application:printFiles:withSettings:showPrintPanels:.
enum {
    NSPrintingCancelled = 0,
    NSPrintingSuccess = 1, 
    NSPrintingFailure = 3,
    NSPrintingReplyLater = 2
};
typedef NSUInteger NSApplicationPrintReply;
#endif

@protocol NSApplicationDelegate <NSObject>
@optional
/* 
    Allowable return values are:
        NSTerminateNow - it is ok to proceed with termination
        NSTerminateCancel - the application should not be terminated
        NSTerminateLater - it may be ok to proceed with termination later.  The application must call -replyToApplicationShouldTerminate: with YES or NO once the answer is known
            this return value is for delegates who need to provide document modal alerts (sheets) in order to decide whether to quit.
*/
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)application:(NSApplication *)sender openFiles:(NSArray *)filenames;
#endif
- (BOOL)application:(NSApplication *)sender openTempFile:(NSString *)filename;
- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender;
- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender;
- (BOOL)application:(id)sender openFileWithoutUI:(NSString *)filename;
- (BOOL)application:(NSApplication *)sender printFile:(NSString *)filename;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSApplicationPrintReply)application:(NSApplication *)application printFiles:(NSArray *)fileNames withSettings:(NSDictionary *)printSettings showPrintPanels:(BOOL)showPrintPanels;
#endif
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;
- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag;
- (NSMenu *)applicationDockMenu:(NSApplication *)sender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSError *)application:(NSApplication *)application willPresentError:(NSError *)error;
#endif

/* Notifications:
 */
- (void)applicationWillFinishLaunching:(NSNotification *)notification;
- (void)applicationDidFinishLaunching:(NSNotification *)notification;
- (void)applicationWillHide:(NSNotification *)notification;
- (void)applicationDidHide:(NSNotification *)notification;
- (void)applicationWillUnhide:(NSNotification *)notification;
- (void)applicationDidUnhide:(NSNotification *)notification;
- (void)applicationWillBecomeActive:(NSNotification *)notification;
- (void)applicationDidBecomeActive:(NSNotification *)notification;
- (void)applicationWillResignActive:(NSNotification *)notification;
- (void)applicationDidResignActive:(NSNotification *)notification;
- (void)applicationWillUpdate:(NSNotification *)notification;
- (void)applicationDidUpdate:(NSNotification *)notification;
- (void)applicationWillTerminate:(NSNotification *)notification;
- (void)applicationDidChangeScreenParameters:(NSNotification *)notification;

@end

@interface NSApplication(NSServicesMenu)
- (void)setServicesMenu:(NSMenu *)aMenu;
- (NSMenu *)servicesMenu;
- (void)registerServicesMenuSendTypes:(NSArray *)sendTypes returnTypes:(NSArray *)returnTypes;
@end

@interface NSObject(NSServicesRequests)
- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
@end

@interface NSApplication(NSServicesHandling)
- (void)setServicesProvider:(id)provider;
- (id)servicesProvider;
@end

@interface NSApplication(NSStandardAboutPanel)
- (void)orderFrontStandardAboutPanel:(id)sender;
- (void)orderFrontStandardAboutPanelWithOptions:(NSDictionary *)optionsDictionary;


/* Optional keys in optionsDictionary:

@"Credits": NSAttributedString displayed in the info area of the panel. If
not specified, contents obtained from "Credits.rtf" in [NSBundle mainBundle];
if not available, blank.

@"ApplicationName": NSString displayed in place of the default app name. If
not specified, uses the value of CFBundleName (localizable). Fallback is [[NSProcessInfo processInfo] processName].

@"ApplicationIcon": NSImage displayed in place of NSApplicationIcon. If not
specified, use [NSImage imageNamed:@"NSApplicationIcon"]; if not available, generic icon.

@"Copyright": NSString containing the copyright string. If not specified,
obtain from the value of NSHumanReadableCopyright (localizable) in infoDictionary; if not available, leave blank.

@"Version": NSString containing the build version number of the application
("58.4", "1.2d3"); displayed as "Version 58.4" or "Version 1.0 (58.4) depending on the presence of ApplicationVersion. 
If not specified, obtain from the CFBundleVersion key in infoDictionary; if not specified or empty string, leave blank.

@"ApplicationVersion": NSString displayed as the marketing version  ("1.0", "Mac OS X", "3", "WebObjects 3.5", ...), before the build version.
If not specified, obtain from CFBundleShortVersionString key in infoDictionary. Prefixed with word "Version" if it looks like a number.
*/

@end

/* Bi-directional User Interface
*/
enum {
    NSUserInterfaceLayoutDirectionLeftToRight = 0,
    NSUserInterfaceLayoutDirectionRightToLeft = 1
};
typedef NSInteger NSUserInterfaceLayoutDirection;

@interface NSApplication (NSApplicationLayoutDirection)
- (NSUserInterfaceLayoutDirection)userInterfaceLayoutDirection AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Returns the application-wide user interface layout direction.
@end

/* An Application's startup function */

APPKIT_EXTERN int NSApplicationMain(int argc, const char *argv[]);

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
/* NSApplicationLoad should be called when loading a Cocoa bundle in a Carbon app in order to initialize NSApplication and other Cocoa objects.  Redundant calls are ignored.
*/  
APPKIT_EXTERN BOOL NSApplicationLoad(void);
#endif

/* NSShowsServicesMenuItem() always returns YES. */
APPKIT_EXTERN BOOL NSShowsServicesMenuItem(NSString * itemName);

/* NSSetShowsServicesMenuItem() has no effect, and always returns 0. */
APPKIT_EXTERN NSInteger NSSetShowsServicesMenuItem(NSString * itemName, BOOL enabled);

/* NSUpdateDynamicServices() causes the services information for the system to be updated.  This will only be necessary if your program adds dynamic services to the system (i.e. services not found in macho segments of executables).
*/
APPKIT_EXTERN void NSUpdateDynamicServices(void);
APPKIT_EXTERN BOOL NSPerformService(NSString *itemName, NSPasteboard *pboard);

APPKIT_EXTERN void NSRegisterServicesProvider(id provider, NSString *name); // apps should use -setServicesProvider
APPKIT_EXTERN void NSUnregisterServicesProvider(NSString *name);

/* Notifications */
APPKIT_EXTERN NSString *NSApplicationDidBecomeActiveNotification;
APPKIT_EXTERN NSString *NSApplicationDidHideNotification;
APPKIT_EXTERN NSString *NSApplicationDidFinishLaunchingNotification;
APPKIT_EXTERN NSString *NSApplicationDidResignActiveNotification;
APPKIT_EXTERN NSString *NSApplicationDidUnhideNotification;
APPKIT_EXTERN NSString *NSApplicationDidUpdateNotification;
APPKIT_EXTERN NSString *NSApplicationWillBecomeActiveNotification;
APPKIT_EXTERN NSString *NSApplicationWillHideNotification;
APPKIT_EXTERN NSString *NSApplicationWillFinishLaunchingNotification;
APPKIT_EXTERN NSString *NSApplicationWillResignActiveNotification;
APPKIT_EXTERN NSString *NSApplicationWillUnhideNotification;
APPKIT_EXTERN NSString *NSApplicationWillUpdateNotification;
APPKIT_EXTERN NSString *NSApplicationWillTerminateNotification;
APPKIT_EXTERN NSString *NSApplicationDidChangeScreenParametersNotification;

/* Depcrecated Methods */
@interface NSApplication (NSDeprecated)

/*
 ** runModalForWindow:relativeToWindow: was deprecated in Mac OS 10.0.  
 ** Please use beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:
 */
- (NSInteger)runModalForWindow:(NSWindow *)theWindow relativeToWindow:(NSWindow *)docWindow DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER;

/* 
 ** beginModalSessionForWindow:relativeToWindow: was deprecated in Mac OS 10.0.
 ** Please use beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:
 */
- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow relativeToWindow:(NSWindow *)docWindow DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER;

// -application:printFiles: was deprecated in Mac OS 10.4. Implement application:printFiles:withSettings:showPrintPanels: in your application delegate instead.
- (void)application:(NSApplication *)sender printFiles:(NSArray *)filenames AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

@end
