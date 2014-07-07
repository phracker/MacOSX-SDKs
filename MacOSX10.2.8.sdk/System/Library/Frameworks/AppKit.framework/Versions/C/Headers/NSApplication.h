/*
	NSApplication.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <AppKit/AppKitDefines.h>

@class NSDate, NSDictionary, NSException, NSNotification;
@class NSGraphicsContext, NSImage, NSPasteboard, NSWindow;

/* The version of the AppKit framework */
APPKIT_EXTERN const double NSAppKitVersionNumber;

#define NSAppKitVersionNumber10_0 577
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
#define NSAppKitVersionNumber10_1 620
#endif

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

APPKIT_EXTERN id NSApp;

/* Information used by the system during modal sessions */
typedef struct _NSModalSession *NSModalSession;
// threading information
typedef struct NSThreadPrivate _NSThreadPrivate;

@interface NSApplication : NSResponder
{
    /*All instance variables are private*/
    NSEvent            *_currentEvent;
    void     		*_windowList;
    id                  _keyWindow;
    id                  _mainWindow;
    id                  _delegate;
    id            	*_hiddenList;
    int                 _hiddenCount;
    void		*_context;
    id                  obsolete1;
    id			obsolete2;
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
	unsigned int        _reserved:10;
    }                   _appFlags;
    id                  _mainMenu;
    id                  _appIcon;
    id                  _nameTable;
    id                  _eventDelegate;
    _NSThreadPrivate     *_threadingSupport;
}

+ (NSApplication *)sharedApplication;
- (void)setDelegate:(id)anObject;
- (id)delegate;
- (NSGraphicsContext*)context;
- (void)hide:(id)sender;
- (void)unhide:(id)sender;
- (void)unhideWithoutActivation;
- (NSWindow *)windowWithWindowNumber:(int)windowNum;
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
- (int)runModalForWindow:(NSWindow *)theWindow;
- (void)stop:(id)sender;
- (void)stopModal;
- (void)stopModalWithCode:(int)returnCode;
- (void)abortModal;
- (NSWindow *)modalWindow;
- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow;
- (int)runModalSession:(NSModalSession)session;
- (void)endModalSession:(NSModalSession)session;
- (void)terminate:(id)sender;

typedef enum {
      NSCriticalRequest = 0,
      NSInformationalRequest = 10
} NSRequestUserAttentionType;

// inform the user that this application needs attention - call this method only if your application is not already active
- (int)requestUserAttention:(NSRequestUserAttentionType)requestType;
- (void)cancelUserAttentionRequest:(int)request;

/*
**  Present a sheet on the given window.  When the modal session is ended,
** the didEndSelector will be invoked in the modalDelegate.  The didEndSelector
** should have the following signature, and will be invoked when the modal session ends.
** This method should dimiss the sheet using orderOut:
** - (void)sheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
**
*/
- (void)beginSheet:(NSWindow *)sheet modalForWindow:(NSWindow *)docWindow modalDelegate:(id)modalDelegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;
- (void)endSheet:(NSWindow *)sheet;
- (void)endSheet:(NSWindow *)sheet returnCode:(int)returnCode;

/*
** runModalForWindow:relativeToWindow: is deprecated.  
** Please use beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:
*/
- (int)runModalForWindow:(NSWindow *)theWindow relativeToWindow:(NSWindow *)docWindow;

/* 
** beginModalSessionForWindow:relativeToWindow: is deprecated.
** Please use beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:
*/
- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow relativeToWindow:(NSWindow *)docWindow;
- (NSEvent *)nextEventMatchingMask:(unsigned int)mask untilDate:(NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(unsigned int)mask beforeEvent:(NSEvent *)lastEvent;
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

- (void)setApplicationIconImage:(NSImage *)image;
- (NSImage *)applicationIconImage;

- (BOOL)sendAction:(SEL)theAction to:(id)theTarget from:(id)sender;
- (id)targetForAction:(SEL)theAction;
- (id)targetForAction:(SEL)theAction to:(id)theTarget from:(id)sender;
- (BOOL)tryToPerform:(SEL)anAction with:(id)anObject;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;

- (void)reportException:(NSException *)theException;
+ (void)detachDrawingThread:(SEL)selector toTarget:(id)target withObject:(id)argument;

/*  If an application delegate returns NSTerminateLater to -applicationShouldTerminate:, -replyToApplicationShouldTerminate: must be called with YES or NO once the application decides if it can terminate */
- (void)replyToApplicationShouldTerminate:(BOOL)shouldTerminate;
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

@interface NSObject(NSApplicationNotifications)
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

// return values for -applicationShouldTerminate:
typedef enum NSApplicationTerminateReply {
        NSTerminateCancel = 0,
        NSTerminateNow = 1, 
        NSTerminateLater = 2
} NSApplicationTerminateReply;

@interface NSObject(NSApplicationDelegate)
/* 
    Allowable return values are:
        NSTerminateNow - it is ok to proceed with termination
        NSTerminateCancel - the application should not be terminated
        NSTerminateLater - it may be ok to proceed with termination later.  The application must call -replyToApplicationShouldTerminate: with YES or NO once the answer is known
            this return value is for delegates who need to provide document modal alerts (sheets) in order to decide whether to quit.
*/
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename;
- (BOOL)application:(NSApplication *)sender openTempFile:(NSString *)filename;
- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender;
- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender;
- (BOOL)application:(id)sender openFileWithoutUI:(NSString *)filename;
- (BOOL)application:(NSApplication *)sender printFile:(NSString *)filename;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;
- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag;
- (NSMenu *)applicationDockMenu:(NSApplication *)sender;
@end

@interface NSApplication(NSAppleMenu)
- (void)setAppleMenu:(NSMenu *)menu;
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
("58.4", "1.2d3"); displayed as "Version 58.4" or "1.0 (v58.4) depending on the presence of ApplicationVersion. 
If not specified, obtain from the CFBundleVersion key in infoDictionary; if not specified or empty string, leave blank.

@"ApplicationVersion": NSString displayed as the application version  ("1.0", "Mac OS X", "3", "WebObjects 3.5", ...), before the build version.
If not specified, obtain from CFBundleShortVersionString key in infoDictionary..
*/

@end

#ifdef WIN32
@interface NSApplication (NSWindowsExtensions)
+ (void)setApplicationHandle:(void * /*HINSTANCE*/)hInstance previousHandle:(void * /*HINSTANCE*/)PrevInstance commandLine:(NSString *)cmdLine show:(int)cmdShow;
+ (void)useRunningCopyOfApplication;
- (void * /*HINSTANCE*/)applicationHandle;
- (NSWindow *)windowWithWindowHandle:(void * /*HWND*/)hWnd; // does not create a new NSWindow
@end
#endif

/* An Application's startup function */

APPKIT_EXTERN int NSApplicationMain(int argc, const char *argv[]);

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
/* The startup function to call for a Cocoa bundle */

APPKIT_EXTERN BOOL NSApplicationLoad(void);
#endif

/*
 * Functions to enable/disable Services Menu items.  These should usually
 * only be called by service PROVIDERS (since they are the only ones who
 * know the name of the services, requestors don't).  The itemName in the
 * two functions below is the language-independent "Menu Item:" entry in
 * the __services section (which all provided services must have).  The
 * set function returns whether it was successful.
 * NSUpdateDynamicServices() causes the services information for the
 * system to be updated.  This will only be necessary if your program
 * adds dynamic services to the system (i.e. services not found in macho
 * segments of executables).
 */

APPKIT_EXTERN BOOL NSShowsServicesMenuItem(NSString * itemName);
APPKIT_EXTERN int NSSetShowsServicesMenuItem(NSString * itemName, BOOL enabled);
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

