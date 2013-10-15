/*
	NSWindow.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <AppKit/NSResponder.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/AppKitDefines.h>
#import <Foundation/NSDate.h>
#import <ApplicationServices/ApplicationServices.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSAnimation.h>

@class NSButton, NSButtonCell, NSColor, NSImage, NSPasteboard, NSScreen;
@class NSNotification, NSText, NSView, NSMutableSet, NSSet, NSDate;
@class NSToolbar, NSGraphicsContext, NSURL;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
@class NSDockTile;
#endif

#define NSAppKitVersionNumberWithCustomSheetPosition 686.0

enum {
    NSBorderlessWindowMask		= 0,
    NSTitledWindowMask			= 1 << 0,
    NSClosableWindowMask		= 1 << 1,
    NSMiniaturizableWindowMask		= 1 << 2,
    NSResizableWindowMask		= 1 << 3
    
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
/* Specifies a window with textured background (eg. metal)
*/
enum {
    NSTexturedBackgroundWindowMask	= 1 << 8
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Specifies a window that ignores the userSpaceScaleFactor of the NSScreen on which it is created.  Currently restricted to borderless windows (NSBorderlessWindowMask)
*/
enum {
    NSUnscaledWindowMask		= 1 << 11
};

/* Specifies a window whose titlebar and toolbar have a unified look - that is, a continuous background
*/
enum {
    NSUnifiedTitleAndToolbarWindowMask	= 1 << 12
};

#endif

/* used with NSRunLoop's performSelector:target:argument:order:modes: */
enum {
    NSDisplayWindowRunLoopOrdering	= 600000,
    NSResetCursorRectsRunLoopOrdering	= 700000
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

enum {
	NSWindowSharingNone = 0,                // Window contents may not be read by another process
	NSWindowSharingReadOnly = 1,            // Window contents may be read but not modified by another process
	NSWindowSharingReadWrite = 2            // Window contents may be read or modified by another process
};

typedef NSUInteger NSWindowSharingType;

enum {
	NSWindowBackingLocationDefault = 0,		// System determines if window backing store is in VRAM or main memory
	NSWindowBackingLocationVideoMemory = 1,		// Window backing store is in VRAM
	NSWindowBackingLocationMainMemory = 2		// Window backing store is in main memory
};

typedef NSUInteger NSWindowBackingLocation;

enum {
  NSWindowCollectionBehaviorDefault = 0,
  NSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0,
  NSWindowCollectionBehaviorMoveToActiveSpace = 1 << 1
};

typedef NSUInteger NSWindowCollectionBehavior;

#endif

#define NSNormalWindowLevel              kCGNormalWindowLevel
#define NSFloatingWindowLevel		 kCGFloatingWindowLevel
#define NSSubmenuWindowLevel		 kCGTornOffMenuWindowLevel
#define NSTornOffMenuWindowLevel	 kCGTornOffMenuWindowLevel
#define NSMainMenuWindowLevel		 kCGMainMenuWindowLevel
#define NSStatusWindowLevel		 kCGStatusWindowLevel
// NSDockWindowLevel is deprecated
#define NSDockWindowLevel		 kCGDockWindowLevel
#define NSModalPanelWindowLevel          kCGModalPanelWindowLevel
#define NSPopUpMenuWindowLevel           kCGPopUpMenuWindowLevel
#define NSScreenSaverWindowLevel         kCGScreenSaverWindowLevel


enum {
    NSDirectSelection = 0,
    NSSelectingNext,
    NSSelectingPrevious
};
typedef NSUInteger NSSelectionDirection;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
// standard window buttons
enum {
    NSWindowCloseButton,
    NSWindowMiniaturizeButton,
    NSWindowZoomButton,
    NSWindowToolbarButton,
    NSWindowDocumentIconButton
};
typedef NSUInteger NSWindowButton;
#endif

@class NSWindowAuxiliary;
@class NSEvent;
@class NSWindowController;

@interface NSWindow : NSResponder
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
<NSAnimatablePropertyContainer, NSUserInterfaceValidations>
#else
<NSUserInterfaceValidations>
#endif
{
    /*All instance variables are private*/
    NSRect              _frame;
    id                  _contentView;
    id                  _delegate;
    NSResponder		*_firstResponder;
    NSView		*_lastLeftHit;
    NSView		*_lastRightHit;
    id                  _counterpart;
    id                  _fieldEditor;
    int                 _winEventMask;
    NSInteger               _windowNum;
    int			_level;
    NSColor		*_backgroundColor;
    id                  _borderView;
    unsigned char	_postingDisabled;
    unsigned char	_styleMask;
    unsigned char	_flushDisabled;
    unsigned char	_reservedWindow1;
    void		*_cursorRects;
    void		*_trectTable;
    NSImage		*_miniIcon;
    int			_unused;
    NSMutableSet	*_dragTypes;
    NSURL		*_representedURL;
    NSSize		*_sizeLimits;
    NSString		*_frameSaveName;
    NSSet		*_regDragTypes;
    struct __wFlags {
        unsigned int        backing:2;
        unsigned int        visible:1;
        unsigned int        isMainWindow:1;
        unsigned int        isKeyWindow:1;
        unsigned int        hidesOnDeactivate:1;
        unsigned int        dontFreeWhenClosed:1;
        unsigned int        oneShot:1;
        unsigned int        deferred:1;
        unsigned int        cursorRectsDisabled:1;
        unsigned int        haveFreeCursorRects:1;
        unsigned int        validCursorRects:1;
        unsigned int        docEdited:1;
        unsigned int        dynamicDepthLimit:1;
        unsigned int        worksWhenModal:1;
        unsigned int        limitedBecomeKey:1;
        unsigned int        needsFlush:1;
        unsigned int        viewsNeedDisplay:1;
        unsigned int        ignoredFirstMouse:1;
        unsigned int        repostedFirstMouse:1;
        unsigned int        windowDying:1;
        unsigned int        tempHidden:1;
        unsigned int        floatingPanel:1;
        unsigned int        wantsToBeOnMainScreen:1;
        unsigned int        optimizedDrawingOk:1;
        unsigned int        optimizeDrawing:1;
        unsigned int        titleIsRepresentedFilename:1;
        unsigned int        excludedFromWindowsMenu:1;
        unsigned int        depthLimit:4;
        unsigned int        delegateReturnsValidRequestor:1;
        unsigned int        lmouseupPending:1;
        unsigned int        rmouseupPending:1;
        unsigned int        wantsToDestroyRealWindow:1;
        unsigned int        wantsToRegDragTypes:1;
        unsigned int        sentInvalidateCursorRectsMsg:1;
        unsigned int        avoidsActivation:1;
        unsigned int        frameSavedUsingTitle:1;
        unsigned int        didRegDragTypes:1;
        unsigned int        delayedOneShot:1;
        unsigned int	    postedNeedsDisplayNote:1;
        unsigned int	    postedInvalidCursorRectsNote:1;
        unsigned int        initialFirstResponderTempSet:1;
        unsigned int        autodisplay:1;
        unsigned int        tossedFirstEvent:1;
        unsigned int        isImageCache:1;
        unsigned int        interfaceStyle:3;
        unsigned int        keyViewSelectionDirection:2;
        unsigned int        defaultButtonCellKETemporarilyDisabled:1;
        unsigned int        defaultButtonCellKEDisabled:1;
        unsigned int        menuHasBeenSet:1;
        unsigned int        wantsToBeModal:1;
        unsigned int        showingModalFrame:1;
        unsigned int        isTerminating:1;
        unsigned int        win32MouseActivationInProgress:1;
        unsigned int        makingFirstResponderForMouseDown:1;
        unsigned int        needsZoom:1;
        unsigned int 	    sentWindowNeedsDisplayMsg:1;
        unsigned int        liveResizeActive:1;
    }                   _wFlags;
    id			_defaultButtonCell;
    NSView 		*_initialFirstResponder;
    NSWindowAuxiliary   *_auxiliaryStorage;
}

+ (NSRect)frameRectForContentRect:(NSRect)cRect styleMask:(NSUInteger)aStyle;
+ (NSRect)contentRectForFrameRect:(NSRect)fRect styleMask:(NSUInteger)aStyle;
+ (CGFloat)minFrameWidthWithTitle:(NSString *)aTitle styleMask:(NSUInteger)aStyle;
+ (NSWindowDepth)defaultDepthLimit;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSRect)frameRectForContentRect:(NSRect)contentRect;
- (NSRect)contentRectForFrameRect:(NSRect)frameRect;
#endif

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag;
- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag screen:(NSScreen *)screen;

- (NSString *)title;
- (void)setTitle:(NSString *)aString;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* setRepresentedURL:
If url is not nil and its path is not empty, the window will show a document icon in the titlebar.  
If the url represents a filename or other resource with a known icon, that icon will be used as the document icon.  Otherwise the default document icon will be used.  The icon can be customized using [[NSWindow standardWindowButton:NSWindowDocumentIconButton] setImage:customImage].  If url is not nil and its path is not empty, the window will have a pop-up menu which can be shown via command-click on the area containing the document icon and title.  By default, this menu will display the path components of the url.  The presence and contents of this menu can be controlled by the delegate method window:shouldPopUpDocumentPathMenu:If the url is nil or has an empty path, the window will not show a document icon and will not have a pop-up menu available via command-click.
*/
- (void)setRepresentedURL:(NSURL *)url;
- (NSURL *)representedURL;
#endif
- (NSString *)representedFilename;
- (void)setRepresentedFilename:(NSString *)aString;
- (void)setTitleWithRepresentedFilename:(NSString *)filename;
- (void)setExcludedFromWindowsMenu:(BOOL)flag;
- (BOOL)isExcludedFromWindowsMenu;
- (void)setContentView:(NSView *)aView;
- (id)contentView;
- (void)setDelegate:(id)anObject;
- (id)delegate;
- (NSInteger)windowNumber;
- (NSUInteger)styleMask;
- (NSText *)fieldEditor:(BOOL)createFlag forObject:(id)anObject;
- (void)endEditingFor:(id)anObject;

- (NSRect)constrainFrameRect:(NSRect)frameRect toScreen:(NSScreen *)screen;
- (void)setFrame:(NSRect)frameRect display:(BOOL)flag;
- (void)setContentSize:(NSSize)aSize;
- (void)setFrameOrigin:(NSPoint)aPoint;
- (void)setFrameTopLeftPoint:(NSPoint)aPoint;
- (NSPoint)cascadeTopLeftFromPoint:(NSPoint)topLeftPoint;
- (NSRect)frame;

// smooth resize
// subclasses can override animationResizeTime: to control the total time for the frame change.
// newFrame is the rect passed into setFrame:display:animate:
- (NSTimeInterval)animationResizeTime:(NSRect)newFrame;
// setFrame:display:animate: is equivalent to setFrame:display: if animateFlag is NO
// If animationFlag is YES, this method will perform a smooth resize of the window, where the total time for the resize is specified by -animationResizeTime:
- (void)setFrame:(NSRect)frameRect display:(BOOL)displayFlag animate:(BOOL)animateFlag;

// show/hide resize corner (does not affect whether window is resizable)
- (void)setShowsResizeIndicator:(BOOL)show;
- (BOOL)showsResizeIndicator;

- (void)setResizeIncrements:(NSSize)increments;
- (NSSize)resizeIncrements;
- (void)setAspectRatio:(NSSize)ratio;
- (NSSize)aspectRatio;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setContentResizeIncrements:(NSSize)increments;
- (NSSize)contentResizeIncrements;
- (void)setContentAspectRatio:(NSSize)ratio;
- (NSSize)contentAspectRatio;
#endif

- (void)useOptimizedDrawing:(BOOL)flag;
- (void)disableFlushWindow;
- (void)enableFlushWindow;
- (BOOL)isFlushWindowDisabled;
- (void)flushWindow;
- (void)flushWindowIfNeeded;
- (void)setViewsNeedDisplay:(BOOL)flag;
- (BOOL)viewsNeedDisplay;
- (void)displayIfNeeded;
- (void)display;
- (void)setAutodisplay:(BOOL)flag;
- (BOOL)isAutodisplay;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)preservesContentDuringLiveResize;
- (void)setPreservesContentDuringLiveResize:(BOOL)flag;
#endif

- (void)update;
- (BOOL)makeFirstResponder:(NSResponder *)aResponder;
- (NSResponder *)firstResponder;
- (NSInteger)resizeFlags;
- (void)keyDown:(NSEvent *)theEvent;
- (void)close;
- (void)setReleasedWhenClosed:(BOOL)flag;
- (BOOL)isReleasedWhenClosed;
- (void)miniaturize:(id)sender;
- (void)deminiaturize:(id)sender;
- (BOOL)isZoomed;
- (void)zoom:(id)sender;
- (BOOL)isMiniaturized;
- (BOOL)tryToPerform:(SEL)anAction with:(id)anObject;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setContentBorderThickness:(CGFloat)thickness forEdge:(NSRectEdge)edge;
- (CGFloat)contentBorderThicknessForEdge:(NSRectEdge)edge;

- (void)setAutorecalculatesContentBorderThickness:(BOOL)flag forEdge:(NSRectEdge)edge;
- (BOOL)autorecalculatesContentBorderThicknessForEdge:(NSRectEdge)edge;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)setMovableByWindowBackground:(BOOL)flag;
- (BOOL)isMovableByWindowBackground;
#endif

- (void)setHidesOnDeactivate:(BOOL)flag;
- (BOOL)hidesOnDeactivate;

// indicate whether a window can be hidden during -[NSApplication hide:].  Default is YES
- (void)setCanHide:(BOOL)flag;
- (BOOL)canHide;

- (void)center;
- (void)makeKeyAndOrderFront:(id)sender;
- (void)orderFront:(id)sender;
- (void)orderBack:(id)sender;
- (void)orderOut:(id)sender;
- (void)orderWindow:(NSWindowOrderingMode)place relativeTo:(NSInteger)otherWin;
- (void)orderFrontRegardless;

- (void)setMiniwindowImage:(NSImage *)image;
- (void)setMiniwindowTitle:(NSString *)title;
- (NSImage *)miniwindowImage;
- (NSString *)miniwindowTitle;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSDockTile *)dockTile;
#endif

- (void)setDocumentEdited:(BOOL)flag;
- (BOOL)isDocumentEdited;
- (BOOL)isVisible;
- (BOOL)isKeyWindow;
- (BOOL)isMainWindow;
- (BOOL)canBecomeKeyWindow;
- (BOOL)canBecomeMainWindow;
- (void)makeKeyWindow;
- (void)makeMainWindow;
- (void)becomeKeyWindow;
- (void)resignKeyWindow;
- (void)becomeMainWindow;
- (void)resignMainWindow;

- (BOOL)worksWhenModal;
- (NSPoint)convertBaseToScreen:(NSPoint)aPoint;
- (NSPoint)convertScreenToBase:(NSPoint)aPoint;
- (void)performClose:(id)sender;
- (void)performMiniaturize:(id)sender;
- (void)performZoom:(id)sender;
- (NSInteger)gState;
- (void)setOneShot:(BOOL)flag;
- (BOOL)isOneShot;
- (NSData *)dataWithEPSInsideRect:(NSRect)rect;
- (NSData *)dataWithPDFInsideRect:(NSRect)rect;
- (void)print:(id)sender;

- (void)disableCursorRects;
- (void)enableCursorRects;
- (void)discardCursorRects;
- (BOOL)areCursorRectsEnabled;
- (void)invalidateCursorRectsForView:(NSView *)aView;
- (void)resetCursorRects;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setAllowsToolTipsWhenApplicationIsInactive:(BOOL)allowWhenInactive;
	// Default is NO. Set to YES to allow a window to display tooltips even when the application is in the background.  Note that, enabling tooltips in an inactive application will cause the app to do work any time the mouse passes over the window.  This can degrade system performance.

- (BOOL)allowsToolTipsWhenApplicationIsInactive;
	// Returns YES if this window displays tooltips even when the application is in the background.  To configure this setting you should call setAllowsToolTipsWhenApplicationIsInactive: instead of overriding -allowsToolTipsWhenApplicationIsInactive.
#endif

- (void)setBackingType:(NSBackingStoreType)bufferingType;
- (NSBackingStoreType)backingType;
- (void)setLevel:(NSInteger)newLevel;
- (NSInteger)level;
- (void)setDepthLimit:(NSWindowDepth)limit;
- (NSWindowDepth)depthLimit;
- (void)setDynamicDepthLimit:(BOOL)flag;
- (BOOL)hasDynamicDepthLimit;
- (NSScreen *)screen;
- (NSScreen *)deepestScreen;
- (BOOL)canStoreColor;
- (void)setHasShadow:(BOOL)hasShadow;
- (BOOL)hasShadow;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)invalidateShadow;
#endif
- (void)setAlphaValue:(CGFloat)windowAlpha;
- (CGFloat)alphaValue;
- (void)setOpaque:(BOOL)isOpaque;
- (BOOL)isOpaque;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* -setSharingType: specifies whether the window content can be read and/or written from another process.  The default sharing type is NSWindowSharingReadOnly, which means other processes can read the window content (eg. for window capture) but cannot modify it.  If you set your window sharing type to NSWindowSharingNone, so that the content cannot be captured, your window will also not be able to participate in a number of system services, so this setting should be used with caution.  If you set your window sharing type to NSWindowSharingReadWrite, other processes can both read and modify the window content.
*/
- (void)setSharingType:(NSWindowSharingType)type;
- (NSWindowSharingType)sharingType;

/* -setPreferredBackingLocation: sets the preferred location for the window backing store.  In general, you should not use this API unless indicated by performance measurement.
*/
- (void)setPreferredBackingLocation:(NSWindowBackingLocation)backingLocation;
/* -preferredBackingLocation gets the preferred location for the window backing store.  This may be different from the actual location.
*/
- (NSWindowBackingLocation)preferredBackingLocation;
/* -backingLocation gets the current location of the window backing store.
*/
- (NSWindowBackingLocation)backingLocation;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)displaysWhenScreenProfileChanges;
- (void)setDisplaysWhenScreenProfileChanges:(BOOL)flag;

- (void)disableScreenUpdatesUntilFlush;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* This API controls whether the receiver is permitted onscreen before the user has logged in.  This property is off by default.  Alert panels and windows presented by input managers are examples of windows which should have this property set.
*/
- (BOOL)canBecomeVisibleWithoutLogin;
- (void)setCanBecomeVisibleWithoutLogin:(BOOL)flag;


- (void)setCollectionBehavior:(NSWindowCollectionBehavior)behavior;
- (NSWindowCollectionBehavior)collectionBehavior;

#endif

/* -setCanBeVisibleOnAllSpaces: controls whether a window can be visible on all spaces (YES) or is associated with one space at a time (NO).  The default setting is NO.  
*/
-(BOOL)canBeVisibleOnAllSpaces                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED;
-(void)setCanBeVisibleOnAllSpaces:(BOOL)flag    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED;

- (NSString *)stringWithSavedFrame;
- (void)setFrameFromString:(NSString *)string;
- (void)saveFrameUsingName:(NSString *)name;
// Set force=YES to use setFrameUsingName on a non-resizable window
- (BOOL)setFrameUsingName:(NSString *)name force:(BOOL)force;
- (BOOL)setFrameUsingName:(NSString *)name;
- (BOOL)setFrameAutosaveName:(NSString *)name;
- (NSString *)frameAutosaveName;
+ (void)removeFrameUsingName:(NSString *)name;


- (void)cacheImageInRect:(NSRect)aRect;
- (void)restoreCachedImage;
- (void)discardCachedImage;

- (NSSize)minSize;
- (NSSize)maxSize;
- (void)setMinSize:(NSSize)size;
- (void)setMaxSize:(NSSize)size;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSSize)contentMinSize;
- (NSSize)contentMaxSize;
- (void)setContentMinSize:(NSSize)size;
- (void)setContentMaxSize:(NSSize)size;
#endif
- (NSEvent *)nextEventMatchingMask:(NSUInteger)mask;
- (NSEvent *)nextEventMatchingMask:(NSUInteger)mask untilDate:(NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSUInteger)mask beforeEvent:(NSEvent *)lastEvent;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
- (NSEvent *)currentEvent;
- (void)setAcceptsMouseMovedEvents:(BOOL)flag;
- (BOOL)acceptsMouseMovedEvents;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)setIgnoresMouseEvents:(BOOL)flag;
- (BOOL)ignoresMouseEvents;
#endif
- (NSDictionary *)deviceDescription;
- (void)sendEvent:(NSEvent *)theEvent;
- (NSPoint)mouseLocationOutsideOfEventStream;
+ (void)menuChanged:(NSMenu *)menu;

- (id)windowController;
- (void)setWindowController:(NSWindowController *)windowController;

- (BOOL)isSheet;
- (NSWindow *)attachedSheet;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
+ (NSButton *)standardWindowButton:(NSWindowButton)b forStyleMask:(NSUInteger)styleMask;
- (NSButton *)standardWindowButton:(NSWindowButton)b;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)addChildWindow:(NSWindow *)childWin ordered:(NSWindowOrderingMode)place;
- (void)removeChildWindow:(NSWindow *)childWin;
- (NSArray *)childWindows;

- (NSWindow *)parentWindow;
- (void)setParentWindow:(NSWindow *)window;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Returns NSGraphicsContext used to render the receiver's content on the screen for the calling thread.
*/
- (NSGraphicsContext *)graphicsContext;

/* Returns scale factor applied to view coordinate system to get to base coordinate system of window 
*/
- (CGFloat)userSpaceScaleFactor;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end

@interface NSWindow(NSKeyboardUI)
- (void)setInitialFirstResponder:(NSView *)view;
- (NSView *)initialFirstResponder;
- (void)selectNextKeyView:(id)sender;
- (void)selectPreviousKeyView:(id)sender;
- (void)selectKeyViewFollowingView:(NSView *)aView;
- (void)selectKeyViewPrecedingView:(NSView *)aView;
- (NSSelectionDirection)keyViewSelectionDirection;
- (void)setDefaultButtonCell:(NSButtonCell *)defButt;
- (NSButtonCell *)defaultButtonCell;
- (void)disableKeyEquivalentForDefaultButtonCell;
- (void)enableKeyEquivalentForDefaultButtonCell;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setAutorecalculatesKeyViewLoop:(BOOL)flag;
- (BOOL)autorecalculatesKeyViewLoop;
- (void)recalculateKeyViewLoop;
#endif
@end

@interface NSWindow (NSToolbarSupport)
- (void)setToolbar:(NSToolbar*)toolbar;
- (NSToolbar *)toolbar;
- (void)toggleToolbarShown:(id)sender;
- (void)runToolbarCustomizationPalette:(id)sender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setShowsToolbarButton:(BOOL)show;
- (BOOL)showsToolbarButton;
#endif
@end

@interface NSWindow(NSDrag)
- (void)dragImage:(NSImage *)anImage at:(NSPoint)baseLocation offset:(NSSize)initialOffset event:(NSEvent *)event pasteboard:(NSPasteboard *)pboard source:(id)sourceObj slideBack:(BOOL)slideFlag;

- (void)registerForDraggedTypes:(NSArray *)newTypes;
- (void)unregisterDraggedTypes;
@end

@interface NSWindow(NSCarbonExtensions)
// create an NSWindow for a Carbon window - windowRef must be a Carbon WindowRef - see MacWindows.h
- (NSWindow *)initWithWindowRef:(void * /* WindowRef */)windowRef;
// return the Carbon WindowRef for this window, creating if necessary: - see MacWindows.h
- (void * /* WindowRef */)windowRef;
@end


@interface NSObject(NSWindowNotifications)
- (void)windowDidResize:(NSNotification *)notification;
- (void)windowDidExpose:(NSNotification *)notification;
- (void)windowWillMove:(NSNotification *)notification;
- (void)windowDidMove:(NSNotification *)notification;
- (void)windowDidBecomeKey:(NSNotification *)notification;
- (void)windowDidResignKey:(NSNotification *)notification;
- (void)windowDidBecomeMain:(NSNotification *)notification;
- (void)windowDidResignMain:(NSNotification *)notification;
- (void)windowWillClose:(NSNotification *)notification;
- (void)windowWillMiniaturize:(NSNotification *)notification;
- (void)windowDidMiniaturize:(NSNotification *)notification;
- (void)windowDidDeminiaturize:(NSNotification *)notification;
- (void)windowDidUpdate:(NSNotification *)notification;
- (void)windowDidChangeScreen:(NSNotification *)notification;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)windowDidChangeScreenProfile:(NSNotification *)notification;
#endif
- (void)windowWillBeginSheet:(NSNotification *)notification;
- (void)windowDidEndSheet:(NSNotification *)notification;
@end

@interface NSObject(NSWindowDelegate)
- (BOOL)windowShouldClose:(id)sender;
- (id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(id)client;
- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize;
- (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)newFrame;
- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)newFrame;
- (NSUndoManager *)windowWillReturnUndoManager:(NSWindow *)window;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSRect)window:(NSWindow *)window willPositionSheet:(NSWindow *)sheet usingRect:(NSRect)rect;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* If a window has a representedURL, the window will by default show a path popup menu for a command-click on a rectangle containing the window document icon button and the window title.  The window delegate may implement -window:shouldPopupDocumentPathMenu: to override NSWindow's default behavior for path popup menu.  A return of NO will prevent the menu from being shown.  A return of YES will cause the window to show the menu passed to this method, which by default will contain a menuItem for each path component of the representedURL.  If the representedURL has no path components, the menu will have no menu items.  Before returning YES, the window delegate may customize the menu by changing the menuItems.  menuItems may be added or deleted, and each menuItem title, action, or target may be modified. 
*/
- (BOOL)window:(NSWindow *)window shouldPopUpDocumentPathMenu:(NSMenu *)menu;

/* The window delegate may implement -window:shouldDragDocumentWithEvent:from:withPasteboard: to override NSWindow document icon's default drag behavior.  The delegate can prohibit the drag by returning NO.  Before returning NO, the delegate may implement its own dragging behavior using -[NSWindow dragImage:at:offset:event:pasteboard:source:slideBack:].  Alternatively, the delegate can enable a drag by returning YES, for example to override NSWindow's default behavior of prohibiting the drag of an edited document.  Lastly, the delegate can customize the pasteboard contents before returning YES.
*/
- (BOOL)window:(NSWindow *)window shouldDragDocumentWithEvent:(NSEvent *)event from:(NSPoint)dragImageLocation withPasteboard:(NSPasteboard *)pasteboard;
#endif
@end


/* Notifications */
APPKIT_EXTERN NSString *NSWindowDidBecomeKeyNotification;
APPKIT_EXTERN NSString *NSWindowDidBecomeMainNotification;
APPKIT_EXTERN NSString *NSWindowDidChangeScreenNotification;
APPKIT_EXTERN NSString *NSWindowDidDeminiaturizeNotification;
APPKIT_EXTERN NSString *NSWindowDidExposeNotification;			// userInfo key:  @"NSExposedRect"
APPKIT_EXTERN NSString *NSWindowDidMiniaturizeNotification;
APPKIT_EXTERN NSString *NSWindowDidMoveNotification;
APPKIT_EXTERN NSString *NSWindowDidResignKeyNotification;
APPKIT_EXTERN NSString *NSWindowDidResignMainNotification;
APPKIT_EXTERN NSString *NSWindowDidResizeNotification;
APPKIT_EXTERN NSString *NSWindowDidUpdateNotification;
APPKIT_EXTERN NSString *NSWindowWillCloseNotification;
APPKIT_EXTERN NSString *NSWindowWillMiniaturizeNotification;
APPKIT_EXTERN NSString *NSWindowWillMoveNotification;
APPKIT_EXTERN NSString *NSWindowWillBeginSheetNotification;
APPKIT_EXTERN NSString *NSWindowDidEndSheetNotification;
APPKIT_EXTERN NSString *NSWindowDidChangeScreenProfileNotification  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

