/*
    NSApplication.h
    Application Kit
    Copyright (c) 1994-2024, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <AppKit/NSResponder.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSRunningApplication.h>
#import <AppKit/NSUserActivity.h>
#import <AppKit/NSUserInterfaceLayout.h>
#import <AppKit/NSPrintInfo.h>
#import <AppKit/NSPasteboard.h>
#import <AppKit/NSAppearance.h>
#import <AppKit/NSMenu.h>

@protocol NSUserActivityRestoring;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSDate, NSDictionary, NSError, NSException, NSNotification;
@class NSGraphicsContext, NSImage, NSPasteboard, NSWindow;
@class NSDockTile;
@class NSUserActivity;
@class CKShareMetadata;
@class INIntent;
@protocol NSApplicationDelegate;

typedef double NSAppKitVersion NS_TYPED_EXTENSIBLE_ENUM;
/* The version of the AppKit framework */
APPKIT_EXTERN const NSAppKitVersion NSAppKitVersionNumber;
static const NSAppKitVersion NSAppKitVersionNumber10_0 = 577;
static const NSAppKitVersion NSAppKitVersionNumber10_1 = 620;
static const NSAppKitVersion NSAppKitVersionNumber10_2 = 663;
static const NSAppKitVersion NSAppKitVersionNumber10_2_3 = 663.6;
static const NSAppKitVersion NSAppKitVersionNumber10_3 = 743;
static const NSAppKitVersion NSAppKitVersionNumber10_3_2 = 743.14;
static const NSAppKitVersion NSAppKitVersionNumber10_3_3 = 743.2;
static const NSAppKitVersion NSAppKitVersionNumber10_3_5 = 743.24;
static const NSAppKitVersion NSAppKitVersionNumber10_3_7 = 743.33;
static const NSAppKitVersion NSAppKitVersionNumber10_3_9 = 743.36;
static const NSAppKitVersion NSAppKitVersionNumber10_4 = 824;
static const NSAppKitVersion NSAppKitVersionNumber10_4_1 = 824.1;
static const NSAppKitVersion NSAppKitVersionNumber10_4_3 = 824.23;
static const NSAppKitVersion NSAppKitVersionNumber10_4_4 = 824.33;
static const NSAppKitVersion NSAppKitVersionNumber10_4_7 = 824.41;
static const NSAppKitVersion NSAppKitVersionNumber10_5 = 949;
static const NSAppKitVersion NSAppKitVersionNumber10_5_2 = 949.27;
static const NSAppKitVersion NSAppKitVersionNumber10_5_3 = 949.33;
static const NSAppKitVersion NSAppKitVersionNumber10_6 = 1038;
static const NSAppKitVersion NSAppKitVersionNumber10_7 = 1138;
static const NSAppKitVersion NSAppKitVersionNumber10_7_2 = 1138.23;
static const NSAppKitVersion NSAppKitVersionNumber10_7_3 = 1138.32;
static const NSAppKitVersion NSAppKitVersionNumber10_7_4 = 1138.47;
static const NSAppKitVersion NSAppKitVersionNumber10_8 = 1187;
static const NSAppKitVersion NSAppKitVersionNumber10_9 = 1265;
static const NSAppKitVersion NSAppKitVersionNumber10_10 = 1343;
static const NSAppKitVersion NSAppKitVersionNumber10_10_2 = 1344;
static const NSAppKitVersion NSAppKitVersionNumber10_10_3 = 1347;
static const NSAppKitVersion NSAppKitVersionNumber10_10_4 = 1348;
static const NSAppKitVersion NSAppKitVersionNumber10_10_5 = 1348;
static const NSAppKitVersion NSAppKitVersionNumber10_10_Max = 1349;
static const NSAppKitVersion NSAppKitVersionNumber10_11 = 1404;
static const NSAppKitVersion NSAppKitVersionNumber10_11_1 = 1404.13;
static const NSAppKitVersion NSAppKitVersionNumber10_11_2 = 1404.34;
static const NSAppKitVersion NSAppKitVersionNumber10_11_3 = 1404.34;
static const NSAppKitVersion NSAppKitVersionNumber10_12 = 1504;
static const NSAppKitVersion NSAppKitVersionNumber10_12_1 = 1504.6;
static const NSAppKitVersion NSAppKitVersionNumber10_12_2 = 1504.76;
static const NSAppKitVersion NSAppKitVersionNumber10_13 = 1561;
static const NSAppKitVersion NSAppKitVersionNumber10_13_1 = 1561.1;
static const NSAppKitVersion NSAppKitVersionNumber10_13_2 = 1561.2;
static const NSAppKitVersion NSAppKitVersionNumber10_13_4 = 1561.4;
static const NSAppKitVersion NSAppKitVersionNumber10_14 = 1671;
static const NSAppKitVersion NSAppKitVersionNumber10_14_1 = 1671.1;
static const NSAppKitVersion NSAppKitVersionNumber10_14_2 = 1671.2;
static const NSAppKitVersion NSAppKitVersionNumber10_14_3 = 1671.3;
static const NSAppKitVersion NSAppKitVersionNumber10_14_4 = 1671.4;
static const NSAppKitVersion NSAppKitVersionNumber10_14_5 = 1671.5;
static const NSAppKitVersion NSAppKitVersionNumber10_15 = 1894;
static const NSAppKitVersion NSAppKitVersionNumber10_15_1 = 1894.1;
static const NSAppKitVersion NSAppKitVersionNumber10_15_2 = 1894.2;
static const NSAppKitVersion NSAppKitVersionNumber10_15_3 = 1894.3;
static const NSAppKitVersion NSAppKitVersionNumber10_15_4 = 1894.4;
static const NSAppKitVersion NSAppKitVersionNumber10_15_5 = 1894.5;
static const NSAppKitVersion NSAppKitVersionNumber10_15_6 = 1894.6;
static const NSAppKitVersion NSAppKitVersionNumber11_0 = 2022;
static const NSAppKitVersion NSAppKitVersionNumber11_1 = 2022.2;
static const NSAppKitVersion NSAppKitVersionNumber11_2 = 2022.3;
static const NSAppKitVersion NSAppKitVersionNumber11_3 = 2022.4;
static const NSAppKitVersion NSAppKitVersionNumber11_4 = 2022.5;
static const NSAppKitVersion NSAppKitVersionNumber11_5 = 2022.6;
static const NSAppKitVersion NSAppKitVersionNumber12_0 = 2113;
static const NSAppKitVersion NSAppKitVersionNumber12_1 = 2113.2;
static const NSAppKitVersion NSAppKitVersionNumber12_2 = 2113.3;
static const NSAppKitVersion NSAppKitVersionNumber12_3 = 2113.4;
static const NSAppKitVersion NSAppKitVersionNumber12_4 = 2113.5;
static const NSAppKitVersion NSAppKitVersionNumber12_5 = 2113.6;
static const NSAppKitVersion NSAppKitVersionNumber13_0 = 2299;
static const NSAppKitVersion NSAppKitVersionNumber13_1 = 2299.3;
static const NSAppKitVersion NSAppKitVersionNumber13_2 NS_SWIFT_NAME(macOS13_2)= 2299.3;
static const NSAppKitVersion NSAppKitVersionNumber13_3 NS_SWIFT_NAME(macOS13_3)= 2299.4;
static const NSAppKitVersion NSAppKitVersionNumber13_4 NS_SWIFT_NAME(macOS13_4)= 2299.5;
static const NSAppKitVersion NSAppKitVersionNumber13_5 NS_SWIFT_NAME(macOS13_5)= 2299.6;
static const NSAppKitVersion NSAppKitVersionNumber13_6 NS_SWIFT_NAME(macOS13_6)= 2299.7;
static const NSAppKitVersion NSAppKitVersionNumber14_0 NS_SWIFT_NAME(macOS14_0) = 2487;
static const NSAppKitVersion NSAppKitVersionNumber14_1 NS_SWIFT_NAME(macOS14_1) = 2487.2;

/* Modes passed to NSRunLoop */
APPKIT_EXTERN NSRunLoopMode NSModalPanelRunLoopMode;
APPKIT_EXTERN NSRunLoopMode NSEventTrackingRunLoopMode;


/* Pre-defined return values for -runModalFor: and -runModalSession:. The system also reserves all values below these. Other values can be used. */
typedef NSInteger NSModalResponse NS_TYPED_EXTENSIBLE_ENUM;
/// Also used as the default response for sheets
static const NSModalResponse NSModalResponseStop API_AVAILABLE(macos(10.9)) = (-1000);
static const NSModalResponse NSModalResponseAbort API_AVAILABLE(macos(10.9)) = (-1001);
static const NSModalResponse NSModalResponseContinue API_AVAILABLE(macos(10.9)) = (-1002);

/// Used with `NSRunLoop`'s `-performSelector:target:argument:order:modes:`.
enum {
    NSUpdateWindowsRunLoopOrdering		= 500000
};

/// Flags that comprise an application's @c presentationOptions.
typedef NS_OPTIONS(NSUInteger, NSApplicationPresentationOptions) {
    NSApplicationPresentationDefault                    = 0,
    
    /// Dock appears when moused to.
    NSApplicationPresentationAutoHideDock               = (1 <<  0),
    
    /// Dock is entirely unavailable.
    NSApplicationPresentationHideDock                   = (1 <<  1),

    /// Menu Bar appears when moused to.
    NSApplicationPresentationAutoHideMenuBar            = (1 <<  2),
    
    /// Menu Bar is entirely unavailable.
    NSApplicationPresentationHideMenuBar                = (1 <<  3),

    /// All Apple menu items are disabled.
    NSApplicationPresentationDisableAppleMenu           = (1 <<  4),
    
    /// Cmd+Tab UI is disabled.
    NSApplicationPresentationDisableProcessSwitching    = (1 <<  5),
    
    /// Cmd+Opt+Esc panel is disabled.
    NSApplicationPresentationDisableForceQuit           = (1 <<  6),
    
    /// PowerKey panel and Restart/Shut Down/Log Out disabled.
    NSApplicationPresentationDisableSessionTermination  = (1 <<  7),
    
    /// Application "Hide" menu item is disabled.
    NSApplicationPresentationDisableHideApplication     = (1 <<  8),
    
    /// Menu Bar's transparent appearance is disabled.
    NSApplicationPresentationDisableMenuBarTransparency = (1 <<  9),

    /// Application is in fullscreen mode.
    NSApplicationPresentationFullScreen API_AVAILABLE(macos(10.7)) = (1 << 10),
    
    /// Fullscreen window toolbar is detached from window and hides/shows on rollover.
    /// May be used only when both @c NSApplicationPresentationFullScreen is also set.
    NSApplicationPresentationAutoHideToolbar API_AVAILABLE(macos(10.7)) = (1 << 11),
    
    /// "Shake mouse pointer to locate" is disabled for this application.
    NSApplicationPresentationDisableCursorLocationAssistance API_AVAILABLE(macos(10.11.2)) = (1 << 12)
} API_AVAILABLE(macos(10.6));

typedef NS_OPTIONS(NSUInteger, NSApplicationOcclusionState) {
    /// If set, at least part of any window owned by this application is visible. If not set, all parts of all windows owned by this application are completely occluded. The menu bar does not count as a window owned by this application, so if only the menu bar is showing then the application is considered not visible. Status items, however, have windows owned by your application. If the status item is present in the menu bar, your application will be considered visible as long as the menu bar is visible.
    NSApplicationOcclusionStateVisible = 1UL << 1,
} API_AVAILABLE(macos(10.9));

typedef NS_OPTIONS(NSInteger, NSWindowListOptions) {
    /// Onscreen application windows in front to back order. By default, -[NSApp windows] is used.
    NSWindowListOrderedFrontToBack = (1 << 0),
} API_AVAILABLE(macos(10.12));

/// Information used by the system during modal sessions.
typedef struct _NSModalSession *NSModalSession;

@interface NSApplication : NSResponder <NSUserInterfaceValidations, NSMenuItemValidation, NSAccessibilityElement, NSAccessibility>

APPKIT_EXTERN __kindof NSApplication * _Null_unspecified NSApp NS_SWIFT_UI_ACTOR;

@property (class, readonly, strong) __kindof NSApplication *sharedApplication;
@property (nullable, weak) id<NSApplicationDelegate> delegate;

- (void)hide:(nullable id)sender;
- (void)unhide:(nullable id)sender;
- (void)unhideWithoutActivation;
- (nullable NSWindow *)windowWithWindowNumber:(NSInteger)windowNum;

@property (nullable, readonly, weak) NSWindow *mainWindow;
@property (nullable, readonly, weak) NSWindow *keyWindow;
@property (getter=isActive, readonly) BOOL active;
@property (getter=isHidden, readonly) BOOL hidden;
@property (getter=isRunning, readonly) BOOL running;

/// A boolean value indicating whether your application should suppress HDR content based on established policy.
/// Built-in AppKit components such as NSImageView will automatically behave correctly with HDR content. You should use this value in conjunction with notifications (`NSApplicationShouldBeginSuppressingHighDynamicRangeContentNotification` and `NSApplicationShouldEndSuppressingHighDynamicRangeContentNotification`) to suppress HDR content in your application when signaled to do so.
@property (readonly) BOOL applicationShouldSuppressHighDynamicRangeContent API_AVAILABLE(macos(26.0));

#pragma mark - Activation and Deactivation

- (void)deactivate;

/// Makes the receiver the active app.
/// - Parameter ignoreOtherApps: If `NO`, the app is activated only if no other app is currently active. If `YES`, the app activates regardless.
- (void)activateIgnoringOtherApps:(BOOL)ignoreOtherApps API_DEPRECATED("This method will be deprecated in a future release. Use NSApp.activate instead.", macos(10.0, API_TO_BE_DEPRECATED));

/// Makes the receiver the active app, if possible.
///
/// You shouldn’t assume the app will be active immediately
/// after sending this message. The framework also does not
/// guarantee that the app will be activated at all.
///
/// For cooperative activation, the other application should
/// call `-yieldActivationToApplication:` or equivalent prior
/// to the target application invoking `-activate`.
///
/// Invoking `-activate` on an already-active application
/// cancels any pending activation yields by the receiver.
- (void)activate API_AVAILABLE(macos(14.0));

/// Explicitly allows another application to make itself active.
///
/// Calling this method will not deactivate the current app, nor
/// will it activate the other app. For cooperative or coordinated
/// activation, the other app should request to be activated at
/// some point in the future by calling `activate` or equivalent.
- (void)yieldActivationToApplication:(NSRunningApplication *)application API_AVAILABLE(macos(14.0)) NS_SWIFT_NAME(yieldActivation(to:));

/// Same as `-yieldActivationToApplication:`, but the provided
/// bundle identifier does not have to correspond to a currently
/// running application.
///
/// This method should be used to yield activation to apps that
/// may not be running at the time of invoking it. If it is known
/// that the target application is currently running, use
/// `-yieldActivationToApplication:` instead.
- (void)yieldActivationToApplicationWithBundleIdentifier:(NSString *)bundleIdentifier API_AVAILABLE(macos(14.0)) NS_SWIFT_NAME(yieldActivation(toApplicationWithBundleIdentifier:));

#pragma mark - Lifecycle

- (void)hideOtherApplications:(nullable id)sender;
- (void)unhideAllApplications:(nullable id)sender;

- (void)finishLaunching;
- (void)run;
- (NSModalResponse)runModalForWindow:(NSWindow *)window;
- (void)stop:(nullable id)sender;
- (void)stopModal;
- (void)stopModalWithCode:(NSModalResponse)returnCode;
- (void)abortModal;
@property (nullable, readonly, strong) NSWindow *modalWindow;
- (NSModalSession)beginModalSessionForWindow:(NSWindow *)window NS_RETURNS_INNER_POINTER;
- (NSModalResponse)runModalSession:(NSModalSession)session;
- (void)endModalSession:(NSModalSession)session;
- (void)terminate:(nullable id)sender;

typedef NS_ENUM(NSUInteger, NSRequestUserAttentionType) {
      NSCriticalRequest = 0,
      NSInformationalRequest = 10
};

/// Inform the user that this application needs attention - call this method only if your application is not already active.
- (NSInteger)requestUserAttention:(NSRequestUserAttentionType)requestType;
- (void)cancelUserAttentionRequest:(NSInteger)request;

/// Execute a block for each of the app's windows. Set `*stop = YES` if desired, to halt the enumeration early.
- (void)enumerateWindowsWithOptions:(NSWindowListOptions)options usingBlock:(void (NS_NOESCAPE ^)(NSWindow *window, BOOL *stop))block API_AVAILABLE(macos(10.12));

- (void)preventWindowOrdering;
@property (readonly, copy) NSArray<NSWindow *> *windows;
- (void)setWindowsNeedUpdate:(BOOL)needUpdate;
- (void)updateWindows;

@property (nullable, strong) NSMenu *mainMenu;

/**
 Set or get the Help menu for the app.  If a non-nil menu is set as the Help menu, Spotlight for Help will be installed in it; otherwise AppKit will install Spotlight for Help into a menu of its choosing (and that menu is not returned from `-helpMenu`).  If you wish to completely suppress Spotlight for Help, you can set a menu that does not appear in the menu bar.  @c NSApplication retains its Help menu and releases it when a different menu is set.
 */
@property (nullable, strong) NSMenu *helpMenu API_AVAILABLE(macos(10.6));

@property (null_resettable, strong) NSImage *applicationIconImage;

/// @return The activation policy of the application.
- (NSApplicationActivationPolicy)activationPolicy API_AVAILABLE(macos(10.6));

/**
 Attempts to modify the application's activation policy.  In OS X 10.9, any policy may be set; prior to 10.9, the activation policy may be changed to @c NSApplicationActivationPolicyProhibited or @c NSApplicationActivationPolicyRegular, but may not be changed to @c NSApplicationActivationPolicyAccessory.  This returns @c YES if setting the activation policy is successful, and @c NO if not.
 */
- (BOOL)setActivationPolicy:(NSApplicationActivationPolicy)activationPolicy API_AVAILABLE(macos(10.6));


@property (readonly, strong) NSDockTile *dockTile API_AVAILABLE(macos(10.5));

- (void)reportException:(NSException *)exception;
+ (void)detachDrawingThread:(SEL)selector toTarget:(id)target withObject:(nullable id)argument;

/// If an application delegate returns NSTerminateLater from -applicationShouldTerminate:, -replyToApplicationShouldTerminate: must be called with YES or NO once the application decides if it can terminate.
- (void)replyToApplicationShouldTerminate:(BOOL)shouldTerminate;

typedef NS_ENUM(NSUInteger, NSApplicationDelegateReply) {
    NSApplicationDelegateReplySuccess = 0,
    NSApplicationDelegateReplyCancel = 1,
    NSApplicationDelegateReplyFailure = 2
};

/**
 If an application delegate encounters an error while handling `-application:openFiles:` or` -application:printFiles:`, `-replyToOpenOrPrint:` should be called with @c NSApplicationDelegateReplyFailure.  If the user cancels the operation, @c NSApplicationDelegateReplyCancel should be used, and if the operation succeeds, @c NSApplicationDelegateReplySuccess should be used .
*/
- (void)replyToOpenOrPrint:(NSApplicationDelegateReply)reply;

/// Opens the character palette.
- (void)orderFrontCharacterPalette:(nullable id)sender;

/**
 Gets or sets the @c presentationOptions that should be in effect for the system when this application is the active application.  Only certain combinations of @c NSApplicationPresentationOptions flags are allowed, as detailed in the AppKit Release Notes and the reference documentation for `-setPresentationOptions:`.  When given an invalid combination of option flags, `-setPresentationOptions:` raises an exception.
*/
@property NSApplicationPresentationOptions presentationOptions API_AVAILABLE(macos(10.6));

/// @return The set of application presentation options that are currently in effect for the system.
/// These are the presentation options that have been put into effect by the currently active application.
@property (readonly) NSApplicationPresentationOptions currentSystemPresentationOptions API_AVAILABLE(macos(10.6));

@property (readonly) NSApplicationOcclusionState occlusionState API_AVAILABLE(macos(10.9));

@property (readonly, getter=isProtectedDataAvailable) BOOL protectedDataAvailable API_AVAILABLE(macos(12.0));


@end

@interface NSApplication (NSAppearanceCustomization) <NSAppearanceCustomization>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wavailability"
@property (nullable, strong) NSAppearance *appearance API_AVAILABLE(macos(10.14));
@property (readonly, strong) NSAppearance *effectiveAppearance API_AVAILABLE(macos(10.14));
#pragma clang diagnostic pop
@end

@interface NSApplication(NSEvent)
- (void)sendEvent:(NSEvent *)event;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)atStart;
@property (nullable, readonly, strong) NSEvent *currentEvent;
- (nullable NSEvent *)nextEventMatchingMask:(NSEventMask)mask untilDate:(nullable NSDate *)expiration inMode:(NSRunLoopMode)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSEventMask)mask beforeEvent:(nullable NSEvent *)lastEvent;
@end

@interface NSApplication(NSResponder)
- (BOOL)sendAction:(SEL)action to:(nullable id)target from:(nullable id)sender;
- (nullable id)targetForAction:(SEL)action;
- (nullable id)targetForAction:(SEL)action to:(nullable id)target from:(nullable id)sender;
- (BOOL)tryToPerform:(SEL)action with:(nullable id)object;
- (nullable id)validRequestorForSendType:(nullable NSPasteboardType)sendType returnType:(nullable NSPasteboardType)returnType;
@end

@interface NSApplication(NSWindowsMenu)
@property (nullable, strong) NSMenu *windowsMenu;
- (void)arrangeInFront:(nullable id)sender;
- (void)removeWindowsItem:(NSWindow *)win;
- (void)addWindowsItem:(NSWindow *)win title:(NSString *)string filename:(BOOL)isFilename;
- (void)changeWindowsItem:(NSWindow *)win title:(NSString *)string filename:(BOOL)isFilename;
- (void)updateWindowsItem:(NSWindow *)win;
- (void)miniaturizeAll:(nullable id)sender;
@end

@interface NSApplication(NSFullKeyboardAccess)
/// A Boolean value indicating whether keyboard navigation is enabled in System Settings > Keyboard.
/// - Note: The value of this property is `YES` if keyboard navigation is enabled or `NO` if it’s not. You might use this value to implement your own key loop or to implement in-control tabbing behavior similar to `NSTableView`. Because of the nature of the preference storage, you won’t be notified of changes to this property if you attempt to observe it through key-value observing; however, accessing this property is fairly inexpensive, so you can access it directly rather than caching it.
/// - Note: This property’s value isn’t necessarily reflective of the separate accessibility setting named “Full Keyboard Access” in System Settings > Accessibility > Keyboard.
@property (getter=isFullKeyboardAccessEnabled, readonly) BOOL fullKeyboardAccessEnabled API_AVAILABLE(macos(10.6));
@end

/// Return values for `-applicationShouldTerminate:`.
typedef NS_ENUM(NSUInteger, NSApplicationTerminateReply) {
    NSTerminateCancel = 0,
    NSTerminateNow = 1,
    NSTerminateLater = 2
};

/// Return values for `-application:printFiles:withSettings:showPrintPanels:`.
typedef NS_ENUM(NSUInteger, NSApplicationPrintReply) {
    NSPrintingCancelled = 0,
    NSPrintingSuccess = 1,
    NSPrintingReplyLater = 2,
    NSPrintingFailure = 3
};

@protocol NSApplicationDelegate <NSObject>
@optional
/**
 Allowable return values are:
 @c NSTerminateNow - it is ok to proceed with termination
 @c NSTerminateCancel - the application should not be terminated
 @c NSTerminateLater - it may be ok to proceed with termination later.  The application must call `-replyToApplicationShouldTerminate:` with @c YES or @c NO once the answer is known
 @note This return value is for delegates who need to provide document modal alerts (sheets) in order to decide whether to quit.
 */
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender NS_SWIFT_UI_ACTOR;

/**
 This will be called for any URLs your application is asked to open. This includes URL types (CFBundleURLTypes) defined in your Info.plist, and Document types (@c CFBundleDocumentTypes) that have no associated @c NSDocument class. Document URLs that have an associated @c NSDocument class will be opened through @c NSDocumentController. If this is implemented, `-application:openFiles:` and `-application:openFile:` will not be called.
 */
- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.13));

- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename NS_SWIFT_UI_ACTOR;
- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames NS_SWIFT_UI_ACTOR;
- (BOOL)application:(NSApplication *)sender openTempFile:(NSString *)filename NS_SWIFT_UI_ACTOR;
- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender NS_SWIFT_UI_ACTOR;
- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender NS_SWIFT_UI_ACTOR;
- (BOOL)application:(id)sender openFileWithoutUI:(NSString *)filename NS_SWIFT_UI_ACTOR;
- (BOOL)application:(NSApplication *)sender printFile:(NSString *)filename NS_SWIFT_UI_ACTOR;
- (NSApplicationPrintReply)application:(NSApplication *)application printFiles:(NSArray<NSString *> *)fileNames withSettings:(NSDictionary<NSPrintInfoAttributeKey, id> *)printSettings showPrintPanels:(BOOL)showPrintPanels NS_SWIFT_UI_ACTOR;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender NS_SWIFT_UI_ACTOR;
- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)hasVisibleWindows NS_SWIFT_UI_ACTOR;
- (nullable NSMenu *)applicationDockMenu:(NSApplication *)sender NS_SWIFT_UI_ACTOR;
- (NSError *)application:(NSApplication *)application willPresentError:(NSError *)error NS_SWIFT_UI_ACTOR;

- (void)application:(NSApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.7));
- (void)application:(NSApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.7));
- (void)application:(NSApplication *)application didReceiveRemoteNotification:(NSDictionary<NSString *, id> *)userInfo NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.7));

/**
 Method to opt-in to secure restorable state.
 
 When this returns @c YES:
 * NSCoders that are passed into the various @c NSWindowRestoration methods will @c requiresSecureCoding and have a @c decodingFailurePolicy of @c NSDecodingFailurePolicySetErrorAndReturn.
 * Any @c restorationClass set on a window must explicitly conform to @c NSWindowRestoration.
 
 This method will be called prior to any state encoding or restoration.
*/
- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(12.0));

/**
 @return The object capable of handling the specified intent.
 */
- (nullable id)application:(NSApplication *)application handlerForIntent:(INIntent *)intent NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(12.0));

/**
 Method called by `-[NSApplication encodeRestorableStateWithCoder:]` to give the delegate a chance to encode any additional state into the @c NSCoder. If the restorable state managed by the delegate changes, you must call `-[NSApplication invalidateRestorableState]` so that it will be re-encoded. See the header `NSWindowRestoration.h` for more information.
*/
- (void)application:(NSApplication *)app willEncodeRestorableState:(NSCoder *)coder NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.7));

/**
 Method called by `-[NSApplication restoreStateWithCoder:]` to give the delegate a chance to restore its own state, which it may decode from the @c NSCoder. See the header `NSWindowRestoration.h` for more information.
*/
- (void)application:(NSApplication *)app didDecodeRestorableState:(NSCoder *)coder NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.7));

#pragma mark - NSUserActivity support

/**
 
 This will be called on the main thread as soon as the user indicates they want to continue an activity in your application. The @c NSUserActivity object may not be available instantly, so use this as an opportunity to show the user that an activity will be continued shortly. Return @c YES to indicate that you are doing so. Return @c NO (or leave it unimplemented) and AppKit/UIKit will put up a default UI.
 
 For each `-application:willContinueUserActivityWithType:` invocation, you are guaranteed to get exactly one invocation of `-application:continueUserActivity:restorationHandler:` on success, or `-application:didFailToContinueUserActivityWithType:error:` if an error was encountered.
 */
- (BOOL)application:(NSApplication *)application willContinueUserActivityWithType:(NSString *)userActivityType NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.10));

/**
 This will be called on the main thread after the @c NSUserActivity object is available. Use the data you stored in the NSUserActivity object to re-create what the user was doing.
 
 @return @c YES to indicate that the activity was handled. Return @c NO (or leave it unimplemented) and AppKit will attempt to continue the user activity.
 
 You should create/fetch any restorable objects associated with the user activity, and pass them to the restorationHandler. They will then get the above `-restoreUserActivityState:` method invoked with the user activity. Invoking the @c restorationHandler is optional. It may be copied and invoked later, but must be invoked on the main thread.
 
 If this user activity was created automatically by having @c NSUbiquitousDocumentUserActivityType in a @c CFBundleDocumentTypes entry, AppKit can automatically restore the NSUserActivity on OS X if NO is returned, or this method is unimplemented. It will do so by creating a document of the appropriate type using the URL stored in the userInfo under the @c NSUserActivityDocumentURLKey. The document will have `-restoreUserActivity:` called on it.
 */
- (BOOL)application:(NSApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void(^)(NSArray<id<NSUserActivityRestoring>> *restorableObjects))restorationHandler NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.10));

/**
 There are instances where continuing a @c NSUserActivity may fail. This will get called on the main thread if it does so. If it is unimplemented, AppKit will present the error.
 */
- (void)application:(NSApplication *)application didFailToContinueUserActivityWithType:(NSString *)userActivityType error:(NSError *)error NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.10));

/**
 This will be called on the main thread when a user activity managed by AppKit/UIKit has been updated. You should use this as a last chance to add additional data to the @c userActivity.
 */
- (void)application:(NSApplication *)application didUpdateUserActivity:(NSUserActivity *)userActivity NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.10));


/**
 This will be called on the main thread after the user indicates they want to accept a CloudKit sharing invitation in your application.
 
 You should use the @c CKShareMetadata object's @c shareURL and containerIdentifier to schedule a @c CKAcceptSharesOperation, then start using the resulting @c CKShare and its associated record(s), which will appear in the @c CKContainer's shared database in a zone matching that of the record's owner.
*/
- (void)application:(NSApplication *)application userDidAcceptCloudKitShareWithMetadata:(CKShareMetadata *)metadata NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.12));

#pragma mark - Key Value Coding support

/// @return @c YES if the receiving delegate object can respond to key value coding messages for a specific keyed attribute, to-one relationship, or to-many relationship.  Return @c NO otherwise.
- (BOOL)application:(NSApplication *)sender delegateHandlesKey:(NSString *)key NS_SWIFT_UI_ACTOR;

 #pragma mark - NSMenu system-wide keyboard shortcut localization support

/**
 This method will be called once during application launch at `-[NSApplication finishLaunching]`.
 
 @return @c NO if the receiving delegate object wishes to opt-out of system-wide keyboard shortcut localization for all application-supplied menus. Return @c YES by default for apps linked against 12.0 and later SDK.
*/
- (BOOL)applicationShouldAutomaticallyLocalizeKeyEquivalents:(NSApplication *)application NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(12.0));

#pragma mark - Notifications

- (void)applicationWillFinishLaunching:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidFinishLaunching:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationWillHide:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidHide:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationWillUnhide:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidUnhide:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationWillBecomeActive:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidBecomeActive:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationWillResignActive:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidResignActive:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationWillUpdate:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidUpdate:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationWillTerminate:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidChangeScreenParameters:(NSNotification *)notification NS_SWIFT_UI_ACTOR;
- (void)applicationDidChangeOcclusionState:(NSNotification *)notification NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.9));
- (void)applicationProtectedDataWillBecomeUnavailable:(NSNotification *)notification NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(12.0));
- (void)applicationProtectedDataDidBecomeAvailable:(NSNotification *)notification NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(12.0));

@end

@interface NSApplication(NSServicesMenu)
@property (nullable, strong) NSMenu *servicesMenu;
- (void)registerServicesMenuSendTypes:(NSArray<NSPasteboardType> *)sendTypes returnTypes:(NSArray<NSPasteboardType> *)returnTypes;
@end

@protocol NSServicesMenuRequestor <NSObject>
@optional
- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray<NSPasteboardType> *)types;
- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
@end

@interface NSApplication(NSServicesHandling)
@property (nullable, strong) id servicesProvider;
@end

/// Optional keys in `-orderFrontStandardAboutPanelWithOptions:` @c optionsDictionary.
typedef NSString * NSAboutPanelOptionKey NS_TYPED_ENUM;

/// NSAttributedString displayed in the info area of the panel. If not specified, contents obtained from "Credits.rtf" (.rtfd, .html) in [NSBundle mainBundle]; if not available, blank. Note that  in applications built against the 10.14 SDK or earlier, the credits are shown in light appearance even when the application is running in dark appearance, except when the credits are specified as an attributed string, or come from a file are the text is just pure black. In applications built against the 10.15 SDK or newer, credits will be shown in dark appearance, using the "adaptive color mapping" setting in NSTextView.
APPKIT_EXTERN NSAboutPanelOptionKey const NSAboutPanelOptionCredits API_AVAILABLE(macos(10.13));
/// NSString displayed in place of the default app name. If not specified, uses the value of CFBundleName (localizable). Fallback is [[NSProcessInfo processInfo] processName].
APPKIT_EXTERN NSAboutPanelOptionKey const NSAboutPanelOptionApplicationName API_AVAILABLE(macos(10.13));
/// NSImage displayed in place of NSApplicationIcon. If not specified, use [NSImage imageNamed:@"NSApplicationIcon"]; if not available, generic icon.
APPKIT_EXTERN NSAboutPanelOptionKey const NSAboutPanelOptionApplicationIcon API_AVAILABLE(macos(10.13));
/// NSString containing the build version number of the application ("58.4", "1.2d3"); displayed as "Version 58.4" or "Version 1.0 (58.4) depending on the presence of ApplicationVersion. If not specified, obtain from the CFBundleVersion key in infoDictionary; if not specified or empty string, leave blank.
APPKIT_EXTERN NSAboutPanelOptionKey const NSAboutPanelOptionVersion API_AVAILABLE(macos(10.13));
/// NSString displayed as the marketing version  ("1.0", "Mac OS X", "3", "WebObjects 3.5", ...), before the build version. If not specified, obtain from CFBundleShortVersionString key in infoDictionary. Prefixed with word "Version" if it looks like a number.
APPKIT_EXTERN NSAboutPanelOptionKey const NSAboutPanelOptionApplicationVersion API_AVAILABLE(macos(10.13));

@interface NSApplication(NSStandardAboutPanel)
- (void)orderFrontStandardAboutPanel:(nullable id)sender;
- (void)orderFrontStandardAboutPanelWithOptions:(NSDictionary<NSAboutPanelOptionKey, id> *)optionsDictionary;
@end

#pragma mark - Bi-directional User Interface

@interface NSApplication (NSApplicationLayoutDirection)
@property (readonly) NSUserInterfaceLayoutDirection userInterfaceLayoutDirection API_AVAILABLE(macos(10.6)); // Returns the application-wide user interface layout direction.
@end

@interface NSApplication (NSRestorableUserInterface)

/**
 Disable or reenable relaunching this app on login, if the app was running at the time the user logged out.  These methods increment and decrement a counter respectively; if the counter is 0 at the time the user logs out, then the app may be relaunched when the user logs back in.  The counter is initially zero, so by default apps are relaunched.
 
 If your app should not be relaunched because it launches via some other mechanism (e.g. launchd), then the recommended usage is to call `-[NSApp disableRelaunchOnLogin]` once, and never pair it with an -enable call.
 
 If your app should not be relaunched because it triggers a restart (e.g. an installer), then the recommended usage is to call `-[NSApp disableRelaunchOnLogin]` immediately before you attempt to trigger a restart, and `-[NSApp enableRelaunchOnLogin]` immediately after.  This is because the user may cancel restarting; if the user later restarts for another reason, then your app should be brought back.
 
 These methods are thread safe.
 */
- (void)disableRelaunchOnLogin API_AVAILABLE(macos(10.7));
- (void)enableRelaunchOnLogin API_AVAILABLE(macos(10.7));
@end

/// Soft deprecated.
/// Please use `NSApplication`'s `-registerForRemoteNotifications` along with `-requestAuthorizationWithOptions:` from the `UserNotifications.framework` to specify allowable notification types.
typedef NS_OPTIONS(NSUInteger, NSRemoteNotificationType) {
    NSRemoteNotificationTypeNone API_AVAILABLE(macos(10.7))    = 0,
    NSRemoteNotificationTypeBadge API_AVAILABLE(macos(10.7))   = 1 << 0,
    NSRemoteNotificationTypeSound API_AVAILABLE(macos(10.8))   = 1 << 1,
    NSRemoteNotificationTypeAlert API_AVAILABLE(macos(10.8))   = 1 << 2,
};

@interface NSApplication (NSRemoteNotifications)
- (void)registerForRemoteNotifications API_AVAILABLE(macos(10.14));
- (void)unregisterForRemoteNotifications API_AVAILABLE(macos(10.7));

/// @return @c YES if the application is currently registered for remote notifications, taking into account any systemwide settings; doesn't relate to connectivity.
@property(readonly, getter=isRegisteredForRemoteNotifications) BOOL registeredForRemoteNotifications API_AVAILABLE(macos(10.14));

/// The following are soft deprecated.
/// Please use the `-registerForRemoteNotifications` above and `-requestAuthorizationWithOptions:` from `UserNotifications.framework`.
- (void)registerForRemoteNotificationTypes:(NSRemoteNotificationType)types API_AVAILABLE(macos(10.7));
@property (readonly) NSRemoteNotificationType enabledRemoteNotificationTypes API_AVAILABLE(macos(10.7));
@end

/// An Application's startup function.
APPKIT_EXTERN int NSApplicationMain(int argc, const char *_Nonnull argv[_Nonnull]);

/// @c NSApplicationLoad should be called when loading a Cocoa bundle in a Carbon app in order to initialize @c NSApplication and other Cocoa objects.  Redundant calls are ignored.
APPKIT_EXTERN BOOL NSApplicationLoad(void);

/// @c NSShowsServicesMenuItem() always returns @c YES.
APPKIT_EXTERN BOOL NSShowsServicesMenuItem(NSString *itemName);

/// @c NSSetShowsServicesMenuItem() has no effect, and always returns 0.
APPKIT_EXTERN NSInteger NSSetShowsServicesMenuItem(NSString *itemName, BOOL enabled);

/// @c NSUpdateDynamicServices() causes the services information for the system to be updated.
/// This will only be necessary if your program adds dynamic services to the system (i.e. services not found in mach-o segments of executables).
APPKIT_EXTERN void NSUpdateDynamicServices(void);
APPKIT_EXTERN BOOL NSPerformService(NSString *itemName, NSPasteboard * _Nullable pboard);

typedef NSString * NSServiceProviderName NS_SWIFT_BRIDGED_TYPEDEF;

/// Apps should use -setServicesProvider.
APPKIT_EXTERN void NSRegisterServicesProvider(id _Nullable provider, NSServiceProviderName name);
APPKIT_EXTERN void NSUnregisterServicesProvider(NSServiceProviderName name);

#pragma mark - Notification Names

APPKIT_EXTERN NSNotificationName NSApplicationDidBecomeActiveNotification;
APPKIT_EXTERN NSNotificationName NSApplicationDidHideNotification;
APPKIT_EXTERN NSNotificationName NSApplicationDidFinishLaunchingNotification;
APPKIT_EXTERN NSNotificationName NSApplicationDidResignActiveNotification;
APPKIT_EXTERN NSNotificationName NSApplicationDidUnhideNotification;
APPKIT_EXTERN NSNotificationName NSApplicationDidUpdateNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillBecomeActiveNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillHideNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillFinishLaunchingNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillResignActiveNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillUnhideNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillUpdateNotification;
APPKIT_EXTERN NSNotificationName NSApplicationWillTerminateNotification;
APPKIT_EXTERN NSNotificationName NSApplicationDidChangeScreenParametersNotification;
APPKIT_EXTERN NSNotificationName NSApplicationProtectedDataWillBecomeUnavailableNotification API_AVAILABLE(macos(12.0));
APPKIT_EXTERN NSNotificationName NSApplicationProtectedDataDidBecomeAvailableNotification API_AVAILABLE(macos(12.0));
// Notifications that tell an app that it should either begin or end suppressing high dynamic range content.
APPKIT_EXTERN NSNotificationName NSApplicationShouldBeginSuppressingHighDynamicRangeContentNotification API_AVAILABLE(macos(26.0));
APPKIT_EXTERN NSNotificationName NSApplicationShouldEndSuppressingHighDynamicRangeContentNotification API_AVAILABLE(macos(26.0));

#pragma mark - User info keys for NSApplicationDidFinishLaunchingNotification

/**
 The following key is present in the userInfo of NSApplicationDidFinishLaunchingNotification.  Its value is an NSNumber containing a bool.  It will be NO if the app was launched to open or print a file, to perform a Service, if the app had saved state that will be restored, or if the app launch was in some other sense not a "default" launch.  Otherwise its value will be YES.
 */
APPKIT_EXTERN NSString * const NSApplicationLaunchIsDefaultLaunchKey API_AVAILABLE(macos(10.7));

/**
 The following key is present in the userInfo of NSApplicationDidFinishLaunchingNotification. It will be present if your application was launched because a user activated a notification in the Notification Center. Its value is an NSUserNotification object.
 */
APPKIT_EXTERN NSString * const NSApplicationLaunchUserNotificationKey API_AVAILABLE(macos(10.8));

#pragma mark - Deprecated keys for NSApplicationDidFinishLaunchingNotification
/**
 NSApplicationLaunchRemoteNotificationKey is unimplemented.  Please use NSApplicationLaunchUserNotificationKey to get the NSUserNotification object.  The NSUserNotification object has an isRemote property to indicate whether this application was launched as a result of a remote notification
 */
APPKIT_EXTERN NSString * const NSApplicationLaunchRemoteNotificationKey API_DEPRECATED("", macos(10.7,10.8));

/**
 Upon receiving this notification, you can query the NSApplication for its occlusion state. Note that this only notifies about changes in the state of the occlusion, not when the occlusion region changes. You can use this notification to increase responsiveness and save power, by halting any expensive calculations that the user can not see.
 */
APPKIT_EXTERN NSNotificationName const NSApplicationDidChangeOcclusionStateNotification API_AVAILABLE(macos(10.9));


#pragma mark -  Deprecated Methods

@interface NSApplication (NSDeprecated)

/**
 `-runModalForWindow:relativeToWindow:` was deprecated in Mac OS X 10.0. Please use `-[NSWindow beginSheet:completionHandler:]` instead.
 */
- (NSInteger)runModalForWindow:(null_unspecified NSWindow *)window relativeToWindow:(null_unspecified NSWindow *)docWindow API_DEPRECATED("Use -[NSWindow beginSheet:completionHandler:] instead", macos(10.0,10.0));

/**
 `-beginModalSessionForWindow:relativeToWindow:` was deprecated in Mac OS X 10.0. Please use `-[NSWindow beginSheet:completionHandler:]` instead.
 */
- (NSModalSession)beginModalSessionForWindow:(null_unspecified NSWindow *)window relativeToWindow:(null_unspecified NSWindow *)docWindow NS_RETURNS_INNER_POINTER API_DEPRECATED("Use -[NSWindow beginSheet:completionHandler:] instead", macos(10.0,10.0));

/**
 `-application:printFiles:` was deprecated in Mac OS X 10.4.
 Implement `-application:printFiles:withSettings:showPrintPanels:` in your application delegate instead.
 */
- (void)application:(null_unspecified NSApplication *)sender printFiles:(null_unspecified NSArray<NSString *> *)filenames API_DEPRECATED("", macos(10.3,10.4));

enum {
    NSRunStoppedResponse API_DEPRECATED("Use NSModalResponseStop instead", macos(10.0,10.10)) = (-1000),
    NSRunAbortedResponse API_DEPRECATED("Use NSModalResponseAbort instead", macos(10.0,10.10)) = (-1001),
    NSRunContinuesResponse API_DEPRECATED("Use NSModalResponseContinue instead", macos(10.0,10.10)) = (-1002)
};

/**
 `NSWindow`'s `-beginSheet:completionHandler:` and `-endSheet:returnCode:` should be used instead.  `NSApplication`'s `-beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:` will continue to work as it previously did, leaking contextInfo and failing when there is already an existing sheet.
 */
- (void)beginSheet:(NSWindow *)sheet modalForWindow:(NSWindow *)docWindow modalDelegate:(nullable id)modalDelegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(null_unspecified void *)contextInfo API_DEPRECATED("Use -[NSWindow beginSheet:completionHandler:] instead", macos(10.0,10.10));
- (void)endSheet:(NSWindow *)sheet API_DEPRECATED("Use -[NSWindow endSheet:] instead", macos(10.0,10.10));
- (void)endSheet:(NSWindow *)sheet returnCode:(NSInteger)returnCode API_DEPRECATED("Use -[NSWindow endSheet:returnCode:] instead", macos(10.0,10.10));

- (nullable NSWindow *)makeWindowsPerform:(SEL)selector inOrder:(BOOL)inOrder API_DEPRECATED("Use -enumerateWindowsWithOptions:usingBlock: instead", macos(10.0,10.14));

/**
 This method is deprecated as of macOS 10.12. Beginning in OS X 10.11 it would always return nil. Prior to this it would return an undefined graphics context that was not generally suitable for drawing.
 */
@property (nullable, readonly, strong) NSGraphicsContext *context API_DEPRECATED("This method always returns nil. If you need access to the current drawing context, use [NSGraphicsContext currentContext] inside of a draw operation.", macos(10.0,10.12));

@end



API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
