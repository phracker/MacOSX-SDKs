/*
	NSWindow.h
	Application Kit
	Copyright (c) 1994-2013, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSResponder.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/AppKitDefines.h>
#import <Foundation/NSDate.h>
#import <ApplicationServices/ApplicationServices.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSUserInterfaceItemIdentification.h>
#import <AppKit/NSAnimation.h>
#import <AppKit/NSAppearance.h>

@class NSButton, NSButtonCell, NSColor, NSImage, NSPasteboard, NSScreen;
@class NSNotification, NSText, NSView, NSMutableSet, NSSet, NSDate;
@class NSToolbar, NSGraphicsContext, NSURL, NSColorSpace;
@class NSDockTile;

@protocol NSWindowDelegate;

#define NSAppKitVersionNumberWithCustomSheetPosition 686.0
#define NSAppKitVersionNumberWithDeferredWindowDisplaySupport		1019.0

enum {
    NSBorderlessWindowMask		= 0,
    NSTitledWindowMask			= 1 << 0,
    NSClosableWindowMask		= 1 << 1,
    NSMiniaturizableWindowMask		= 1 << 2,
    NSResizableWindowMask		= 1 << 3
    
};

/* Specifies a window with textured background (eg. metal)
*/
enum {
    NSTexturedBackgroundWindowMask	= 1 << 8
};

/* NSUnscaledWindowMask is deprecated and has no effect. The scale factor for a window backing store is dynamic and dependent on the screen it is placed on. 
 */
enum {
    NSUnscaledWindowMask		= 1 << 11
} NS_ENUM_DEPRECATED_MAC(10_0, 10_9);

/* Specifies a window whose titlebar and toolbar have a unified look - that is, a continuous background
*/
enum {
    NSUnifiedTitleAndToolbarWindowMask	= 1 << 12
};


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
enum {
    NSFullScreenWindowMask      = 1 << 14
};
#endif

// Additional NSModalResponse values
enum {
    NSModalResponseOK		= 1,
    NSModalResponseCancel	= 0
} NS_ENUM_AVAILABLE_MAC(10_9);


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
#endif
typedef NSUInteger NSWindowSharingType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
	NSWindowBackingLocationDefault = 0,		// System determines if window backing store is in VRAM or main memory
	NSWindowBackingLocationVideoMemory = 1,		// Window backing store is in VRAM
	NSWindowBackingLocationMainMemory = 2		// Window backing store is in main memory
};
#endif
typedef NSUInteger NSWindowBackingLocation;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
  NSWindowCollectionBehaviorDefault = 0,
  NSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0,
  NSWindowCollectionBehaviorMoveToActiveSpace = 1 << 1
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/* You may specify at most one of NSWindowCollectionBehaviorManaged, NSWindowCollectionBehaviorTransient, or NSWindowCollectionBehaviorStationary.  If unspecified, the window gets the default behavior determined by its window level */
enum {
 NSWindowCollectionBehaviorManaged = 1 << 2,  		// participates in spaces, exposé.  Default behavior if windowLevel == NSNormalWindowLevel
 NSWindowCollectionBehaviorTransient = 1 << 3, 		// floats in spaces, hidden by exposé.  Default behavior if windowLevel != NSNormalWindowLevel
 NSWindowCollectionBehaviorStationary = 1 << 4, 	// unaffected by exposé.  Stays visible and stationary, like desktop window
};

/* You may specify at most one of NSWindowCollectionBehaviorParticipatesInCycle or NSWindowCollectionBehaviorIgnoresCycle.  If unspecified, the window gets the default behavior determined by its window level */
enum {
  NSWindowCollectionBehaviorParticipatesInCycle = 1 << 5,   // default behavior if windowLevel == NSNormalWindowLevel
  NSWindowCollectionBehaviorIgnoresCycle = 1 << 6           // default behavior if windowLevel != NSNormalWindowLevel
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
/* You may specify at most one of NSWindowCollectionBehaviorFullScreenPrimary or NSWindowCollectionBehaviorFullScreenAuxiliary. */
enum {
    NSWindowCollectionBehaviorFullScreenPrimary = 1 << 7,   // the frontmost window with this collection behavior will be the fullscreen window.  
    NSWindowCollectionBehaviorFullScreenAuxiliary = 1 << 8	  // windows with this collection behavior can be shown with the fullscreen window.  
};
#endif


typedef NSUInteger NSWindowCollectionBehavior;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
enum {
    NSWindowAnimationBehaviorDefault = 0,       // let AppKit infer animation behavior for this window
    NSWindowAnimationBehaviorNone = 2,          // suppress inferred animations (don't animate)

    NSWindowAnimationBehaviorDocumentWindow = 3,
    NSWindowAnimationBehaviorUtilityWindow = 4,
    NSWindowAnimationBehaviorAlertPanel = 5
};
#endif
typedef NSInteger NSWindowAnimationBehavior;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/* Options used in +windowNumbersWithOptions:.  If no options are specified, the returned list contains window numbers for visible windows on the active space belonging to the calling application. */
enum {
    NSWindowNumberListAllApplications = 1 << 0,
    NSWindowNumberListAllSpaces = 1 << 4
};
#endif

typedef NS_OPTIONS(NSUInteger, NSWindowOcclusionState) {
    // If set, at least part of the window is visible. If not set, the entire window is occluded. Windows with non-rectangular shapes may be completely occluded on screen but still count as visible, if their bounding box falls into a visible region. Windows that are completely transparent may also still count as visible.
    NSWindowOcclusionStateVisible = 1UL << 1,
} NS_ENUM_AVAILABLE_MAC(10_9);

typedef NSUInteger NSWindowNumberListOptions;

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

// standard window buttons
enum {
    NSWindowCloseButton,
    NSWindowMiniaturizeButton,
    NSWindowZoomButton,
    NSWindowToolbarButton,
    NSWindowDocumentIconButton
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
enum {
    NSWindowDocumentVersionsButton = 6,
    NSWindowFullScreenButton
};
#endif
typedef NSUInteger NSWindowButton;

@class NSWindowAuxiliary;
@class NSEvent;
@class NSWindowController;

@interface NSWindow : NSResponder <NSAnimatablePropertyContainer, NSUserInterfaceValidations, NSUserInterfaceItemIdentification, NSAppearanceCustomization>
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
    void                *_trectTable;
    NSImage		*_miniIcon;
    int32_t		_bamboo;
    NSMutableSet	*_dragTypes;
    NSURL		*_representedURL;
    NSSize		*_sizeLimits;
    NSString		*_frameSaveName;
    id                  _reservedWindow2;
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
        unsigned int        autolayoutEngagedSomewhere:1;
        unsigned int        _unused:2;
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
        unsigned int        unused:1;
    }                   _wFlags;
    id			_defaultButtonCell;
    NSView 		*_initialFirstResponder;
    NSWindowAuxiliary   *_auxiliaryStorage;
}

+ (NSRect)frameRectForContentRect:(NSRect)cRect styleMask:(NSUInteger)aStyle;
+ (NSRect)contentRectForFrameRect:(NSRect)fRect styleMask:(NSUInteger)aStyle;
+ (CGFloat)minFrameWidthWithTitle:(NSString *)aTitle styleMask:(NSUInteger)aStyle;
+ (NSWindowDepth)defaultDepthLimit;

- (NSRect)frameRectForContentRect:(NSRect)contentRect;
- (NSRect)contentRectForFrameRect:(NSRect)frameRect;

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag;
- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag screen:(NSScreen *)screen;

- (NSString *)title;
- (void)setTitle:(NSString *)aString;
/* setRepresentedURL:
If url is not nil and its path is not empty, the window will show a document icon in the titlebar.  
If the url represents a filename or other resource with a known icon, that icon will be used as the document icon.  Otherwise the default document icon will be used.  The icon can be customized using [[NSWindow standardWindowButton:NSWindowDocumentIconButton] setImage:customImage].  If url is not nil and its path is not empty, the window will have a pop-up menu which can be shown via command-click on the area containing the document icon and title.  By default, this menu will display the path components of the url.  The presence and contents of this menu can be controlled by the delegate method window:shouldPopUpDocumentPathMenu:If the url is nil or has an empty path, the window will not show a document icon and will not have a pop-up menu available via command-click.
*/
- (void)setRepresentedURL:(NSURL *)url NS_AVAILABLE_MAC(10_5);
- (NSURL *)representedURL NS_AVAILABLE_MAC(10_5);
- (NSString *)representedFilename;
- (void)setRepresentedFilename:(NSString *)aString;
- (void)setTitleWithRepresentedFilename:(NSString *)filename;
- (void)setExcludedFromWindowsMenu:(BOOL)flag;
- (BOOL)isExcludedFromWindowsMenu;
- (void)setContentView:(NSView *)aView;
- (id)contentView;
- (void)setDelegate:(id <NSWindowDelegate>)anObject;
- (id <NSWindowDelegate>)delegate;
- (NSInteger)windowNumber;
- (NSUInteger)styleMask;
/* Valid styleMask settings have the same restrictions as the styleMask passed to -initWithContentRect:styleMask:backing:defer:.  Some styleMask changes will cause the view hierarchy to be rebuilt, since there is a different subclass for the top level view of a borderless window than for the top level view of a titled window. */
- (void)setStyleMask:(NSUInteger)styleMask NS_AVAILABLE_MAC(10_6);
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

- (BOOL)inLiveResize    NS_AVAILABLE_MAC(10_6);

// show/hide resize corner (does not affect whether window is resizable)
- (void)setShowsResizeIndicator:(BOOL)show;
- (BOOL)showsResizeIndicator;

- (void)setResizeIncrements:(NSSize)increments;
- (NSSize)resizeIncrements;
- (void)setAspectRatio:(NSSize)ratio;
- (NSSize)aspectRatio;

- (void)setContentResizeIncrements:(NSSize)increments;
- (NSSize)contentResizeIncrements;
- (void)setContentAspectRatio:(NSSize)ratio;
- (NSSize)contentAspectRatio;

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

- (BOOL)preservesContentDuringLiveResize;
- (void)setPreservesContentDuringLiveResize:(BOOL)flag;

- (void)update;

- (BOOL)makeFirstResponder:(NSResponder *)aResponder;
/* firstResponder is Key Value Observing (KVO) compliant. */
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

/* Indicates the thickness of a given border of the window. NSMinYEdge is the bottom edge of the window, while NSMaxYEdge is the top edge of the window. This method may throw an exception for values that don't apply to the current window styleMask; specifically, passing NSMaxYEdge for a non-textured window will always raise. The contentBorder does not include the titlebar or toolbar.
 */
- (void)setContentBorderThickness:(CGFloat)thickness forEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);
- (CGFloat)contentBorderThicknessForEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);

- (void)setAutorecalculatesContentBorderThickness:(BOOL)flag forEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);
- (BOOL)autorecalculatesContentBorderThicknessForEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);

/* Calling -setMovable with a flag of NO will disable server-side dragging of the window via titlebar or background.  -setMovableByWindowBackground:YES is ignored on a window that returns NO from -isMovable.  When a window returns NO for -isMovable, it can be dragged between spaces only in spaces F8 mode, and its relative screen position is preserved.  Note that the a resizable window may still be resized, and the window frame may be changed programmatically.  Applications may choose to enable application-controlled window dragging after disabling server-side dragging (perhaps to achieve snapping or pinnning) by handling the mouseDown/mouseDragged/mouseUp sequence in -sendEvent: in an NSWindow subclass.  Note that a non movable window will also not be moved (or resized) by the system in response to a display reconfiguration. */
- (void)setMovable:(BOOL)flag NS_AVAILABLE_MAC(10_6);
- (BOOL)isMovable NS_AVAILABLE_MAC(10_6);

- (void)setMovableByWindowBackground:(BOOL)flag;
- (BOOL)isMovableByWindowBackground;

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

- (NSDockTile *)dockTile NS_AVAILABLE_MAC(10_5);

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

/* Normally, application termination is prohibited when a modal window or sheet is open, without consulting the application delegate.  Some windows like the open panel or toolbar customization sheet should not prevent application termination.  -setPreventsApplicationTerminationWhenModal:NO on a modal window or sheet will override the default behavior and allow application termination to proceed, either through the sudden termination path if enabled, or on to the next step of consulting the application delegate.  By default, -preventsApplicationTerminationWhenModal returns YES */
- (BOOL)preventsApplicationTerminationWhenModal NS_AVAILABLE_MAC(10_6);
- (void)setPreventsApplicationTerminationWhenModal:(BOOL)flag NS_AVAILABLE_MAC(10_6);

/* New methods to convert window coordinates to screen coordinates */
- (NSRect)convertRectToScreen:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromScreen:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* New methods to convert to/from a pixel integral backing store space */
- (NSRect)convertRectToBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* Use NSIntegralRectWithOptions() to produce a backing store pixel aligned rectangle from the given input rectangle in window coordinates. */
- (NSRect)backingAlignedRect:(NSRect)aRect options:(NSAlignmentOptions)options NS_AVAILABLE_MAC(10_7);

/* Returns the scale factor representing the number of backing store pixels corresponding to each linear unit in window space on this NSWindow. This method is provided for rare cases when the explicit scale factor is needed. Please use -convert*ToBacking: methods whenever possible. */
- (CGFloat)backingScaleFactor NS_AVAILABLE_MAC(10_7); 

/* The base/screen conversion methods are deprecated in 10.7 and later. Please use convertRectToScreen: or convertRectFromScreen: instead.  */
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

- (void)setAllowsToolTipsWhenApplicationIsInactive:(BOOL)allowWhenInactive;
	// Default is NO. Set to YES to allow a window to display tooltips even when the application is in the background.  Note that, enabling tooltips in an inactive application will cause the app to do work any time the mouse passes over the window.  This can degrade system performance.

- (BOOL)allowsToolTipsWhenApplicationIsInactive;
	// Returns YES if this window displays tooltips even when the application is in the background.  To configure this setting you should call setAllowsToolTipsWhenApplicationIsInactive: instead of overriding -allowsToolTipsWhenApplicationIsInactive.

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
- (void)invalidateShadow;
- (void)setAlphaValue:(CGFloat)windowAlpha;
- (CGFloat)alphaValue;
- (void)setOpaque:(BOOL)isOpaque;
- (BOOL)isOpaque;


/* -setSharingType: specifies whether the window content can be read and/or written from another process.  The default sharing type is NSWindowSharingReadOnly, which means other processes can read the window content (eg. for window capture) but cannot modify it.  If you set your window sharing type to NSWindowSharingNone, so that the content cannot be captured, your window will also not be able to participate in a number of system services, so this setting should be used with caution.  If you set your window sharing type to NSWindowSharingReadWrite, other processes can both read and modify the window content.
*/
- (void)setSharingType:(NSWindowSharingType)type NS_AVAILABLE_MAC(10_5);
- (NSWindowSharingType)sharingType NS_AVAILABLE_MAC(10_5);

/* -setPreferredBackingLocation: sets the preferred location for the window backing store.  In general, you should not use this API unless indicated by performance measurement.
*/
- (void)setPreferredBackingLocation:(NSWindowBackingLocation)backingLocation NS_AVAILABLE_MAC(10_5);
/* -preferredBackingLocation gets the preferred location for the window backing store.  This may be different from the actual location.
*/
- (NSWindowBackingLocation)preferredBackingLocation NS_AVAILABLE_MAC(10_5);
/* -backingLocation gets the current location of the window backing store.
*/
- (NSWindowBackingLocation)backingLocation NS_AVAILABLE_MAC(10_5);


/* Reports whether threading of view drawing is enabled for this window.  Defaults to YES.
*/
- (BOOL)allowsConcurrentViewDrawing NS_AVAILABLE_MAC(10_6);

/* Sets whether threading of view drawing should be enabled for this window.  Defaults to YES.  When this is set to YES, AppKit's view system is allowed to perform -drawRect: activity for the window's views on threads other than the main thread, for views that have canDrawConcurrently == YES.  When this is set to NO, the window's views will be drawn serially as on 10.5 and earlier, even though some of the views may have canDrawConcurrently == YES.
*/
- (void)setAllowsConcurrentViewDrawing:(BOOL)flag NS_AVAILABLE_MAC(10_6);

- (BOOL)displaysWhenScreenProfileChanges;
- (void)setDisplaysWhenScreenProfileChanges:(BOOL)flag;

- (void)disableScreenUpdatesUntilFlush;

/* This API controls whether the receiver is permitted onscreen before the user has logged in.  This property is off by default.  Alert panels and windows presented by input managers are examples of windows which should have this property set.
*/
- (BOOL)canBecomeVisibleWithoutLogin NS_AVAILABLE_MAC(10_5);
- (void)setCanBecomeVisibleWithoutLogin:(BOOL)flag NS_AVAILABLE_MAC(10_5);


- (void)setCollectionBehavior:(NSWindowCollectionBehavior)behavior NS_AVAILABLE_MAC(10_5);
- (NSWindowCollectionBehavior)collectionBehavior NS_AVAILABLE_MAC(10_5);


/* Provides for per-window control over automatic orderFront/orderOut animation behaviors added in 10.7.  Can be set to NSWindowAnimationBehaviorNone to disable Appkit's automatic animations for a given window, or to one of the other non-Default NSWindowAnimationBehavior values to override AppKit's automatic inference of appropriate animation behavior based on the window's apparent type.
*/
- (NSWindowAnimationBehavior)animationBehavior NS_AVAILABLE_MAC(10_7);
- (void)setAnimationBehavior:(NSWindowAnimationBehavior)newAnimationBehavior NS_AVAILABLE_MAC(10_7);


/* -setCanBeVisibleOnAllSpaces: controls whether a window can be visible on all spaces (YES) or is associated with one space at a time (NO).  The default setting is NO.  
*/
-(BOOL)canBeVisibleOnAllSpaces                  NS_DEPRECATED_MAC(10_5, 10_5);
-(void)setCanBeVisibleOnAllSpaces:(BOOL)flag    NS_DEPRECATED_MAC(10_5, 10_5);

/* Returns YES if this window is associated with the active space.  For visible windows, this API indicates whether the window is currently visible on the active space.  For offscreen windows, it indicates whether ordering the window onscreen would make it bring it onto the active space */
- (BOOL)isOnActiveSpace NS_AVAILABLE_MAC(10_6);

- (void)toggleFullScreen:(id)sender NS_AVAILABLE_MAC(10_7);

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
- (NSSize)contentMinSize;
- (NSSize)contentMaxSize;
- (void)setContentMinSize:(NSSize)size;
- (void)setContentMaxSize:(NSSize)size;
- (NSEvent *)nextEventMatchingMask:(NSUInteger)mask;
- (NSEvent *)nextEventMatchingMask:(NSUInteger)mask untilDate:(NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSUInteger)mask beforeEvent:(NSEvent *)lastEvent;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
- (NSEvent *)currentEvent;
- (void)setAcceptsMouseMovedEvents:(BOOL)flag;
- (BOOL)acceptsMouseMovedEvents;
- (void)setIgnoresMouseEvents:(BOOL)flag;
- (BOOL)ignoresMouseEvents;
- (NSDictionary *)deviceDescription;
- (void)sendEvent:(NSEvent *)theEvent;
- (NSPoint)mouseLocationOutsideOfEventStream;
+ (void)menuChanged:(NSMenu *)menu;

- (id)windowController;
- (void)setWindowController:(NSWindowController *)windowController;

/*
 This API presents modal-sheets on this window. It replaces NSApp's -beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:.
 
 If the window already has a presented sheet, it will queue up sheets presented after that. Once the presented sheet is dismissed, the next queued sheet will be presented, and so forth.
 Critical sheets will skip this queuing process and be immediately presented on top of existing sheets. The presented sheet will be temporarily disabled and be able to be interacted with after the critical sheet is dismissed, and will then continue as normal. Critical sheets should only be used for time-critical or important events, when the presentation of the sheet needs to be guaranteed (Critical Alerts will automatically use this API).
*/
#if NS_BLOCKS_AVAILABLE
- (void)beginSheet:(NSWindow *)sheetWindow completionHandler:(void (^)(NSModalResponse returnCode))handler NS_AVAILABLE_MAC(10_9);
- (void)beginCriticalSheet:(NSWindow *)sheetWindow completionHandler:(void (^)(NSModalResponse returnCode))handler NS_AVAILABLE_MAC(10_9);
#endif
- (void)endSheet:(NSWindow *)sheetWindow NS_AVAILABLE_MAC(10_9);
- (void)endSheet:(NSWindow *)sheetWindow returnCode:(NSModalResponse)returnCode NS_AVAILABLE_MAC(10_9);
- (NSArray *)sheets NS_AVAILABLE_MAC(10_9); // An ordered array of the sheets on the window. This consists of the presented sheets in top-to-bottom order, followed by queued sheets in the order they were queued. This does not include nested/sub-sheets.
- (NSWindow *)attachedSheet; // Returns the top-most sheet if there is one or more sheets, or nil if there is no sheet.

- (BOOL)isSheet;
/* Returns the window that the sheet is directly attached to. This is based on the logical attachment of the sheet, not appearance.
 This relationship exists starting when the sheet is begun (using NSApplication's -beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo: or NSWindow's -beginSheet:completionHandler:), and ending once it is ordered out.
 
 Returns nil if the window is not a sheet or has no sheet parent.
 */
- (NSWindow *)sheetParent NS_AVAILABLE_MAC(10_9);


+ (NSButton *)standardWindowButton:(NSWindowButton)b forStyleMask:(NSUInteger)styleMask;
- (NSButton *)standardWindowButton:(NSWindowButton)b;

- (void)addChildWindow:(NSWindow *)childWin ordered:(NSWindowOrderingMode)place;
- (void)removeChildWindow:(NSWindow *)childWin;
- (NSArray *)childWindows;

- (NSWindow *)parentWindow;
- (void)setParentWindow:(NSWindow *)window;

/* Returns NSGraphicsContext used to render the receiver's content on the screen for the calling thread.
*/
- (NSGraphicsContext *)graphicsContext;

/* This method is deprecated and should not be used by applications targeting Mac OS X 10.7 or later.
 The implementation of this method will always return 1.0.  Please use -convertRectToBacking: and -backingScaleFactor instead.
 */
- (CGFloat)userSpaceScaleFactor;


- (void)setColorSpace:(NSColorSpace *)colorSpace NS_AVAILABLE_MAC(10_6);
- (NSColorSpace *)colorSpace NS_AVAILABLE_MAC(10_6);

/* windowNumbersWithOptions: returns an autoreleased array of NSNumbers containing windowNumbers for all visible windows satisfying options.  If no options are specified, only visible windows belonging to the calling application and on the active space are included.  If options include NSWindowNumberListAllApplications, visible windows belonging to all applications are included.  If options include NSWindowNumberListAllSpaces, visible windows on all spaces are included.  Windows on the active space are returned in z-order.  
   Examples: 
      To get an array of windowNumbers visible on the current space and belonging to the calling application:  
	windowNumbers = [NSWindow windowNumbersWithOptions:0];
      To get an array of windowNumbers visible on any space and belonging to any application:
	windowNumbers = [NSWindow windowNumbersWithOptions:NSWindowNumberListAllApplications|NSWindowNumberListAllSpaces];
      To get an array of windowNumbers visible on any space and belonging to the calling application:
	windowNumbers = [NSWindow windowNumbersWithOptions:NSWindowNumberListAllSpaces];
*/
+ (NSArray *)windowNumbersWithOptions:(NSWindowNumberListOptions)options NS_AVAILABLE_MAC(10_6);

/* windowNumberAtPoint:belowWindowWithWindowNumber: returns the number of the frontmost window that would be hit by a mouseDown at the screen location "point".  "windowNum" can be specified to exclude a given window along with all windows above it, and may belong to any application.  If no windows are to be excluded, specify 0 for "windowNum".  The windowNumber returned may correspond to a window in another application.    
*/
+ (NSInteger)windowNumberAtPoint:(NSPoint)point belowWindowWithWindowNumber:(NSInteger)windowNumber NS_AVAILABLE_MAC(10_6);

- (NSWindowOcclusionState)occlusionState NS_AVAILABLE_MAC(10_9);

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
- (void)setAutorecalculatesKeyViewLoop:(BOOL)flag;
- (BOOL)autorecalculatesKeyViewLoop;
- (void)recalculateKeyViewLoop;
@end

@interface NSWindow (NSToolbarSupport)
- (void)setToolbar:(NSToolbar*)toolbar;
- (NSToolbar *)toolbar;
- (void)toggleToolbarShown:(id)sender;
- (void)runToolbarCustomizationPalette:(id)sender;
- (void)setShowsToolbarButton:(BOOL)show;
- (BOOL)showsToolbarButton;
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
- (void * /* WindowRef */)windowRef NS_RETURNS_INNER_POINTER;
@end


@protocol NSWindowDelegate <NSObject>
@optional
- (BOOL)windowShouldClose:(id)sender;
- (id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(id)client;
- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize;
- (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)newFrame;
- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)newFrame;
- (NSUndoManager *)windowWillReturnUndoManager:(NSWindow *)window;
- (NSRect)window:(NSWindow *)window willPositionSheet:(NSWindow *)sheet usingRect:(NSRect)rect;
/* If a window has a representedURL, the window will by default show a path popup menu for a command-click on a rectangle containing the window document icon button and the window title.  The window delegate may implement -window:shouldPopupDocumentPathMenu: to override NSWindow's default behavior for path popup menu.  A return of NO will prevent the menu from being shown.  A return of YES will cause the window to show the menu passed to this method, which by default will contain a menuItem for each path component of the representedURL.  If the representedURL has no path components, the menu will have no menu items.  Before returning YES, the window delegate may customize the menu by changing the menuItems.  menuItems may be added or deleted, and each menuItem title, action, or target may be modified. 
*/
- (BOOL)window:(NSWindow *)window shouldPopUpDocumentPathMenu:(NSMenu *)menu NS_AVAILABLE_MAC(10_5);

/* The window delegate may implement -window:shouldDragDocumentWithEvent:from:withPasteboard: to override NSWindow document icon's default drag behavior.  The delegate can prohibit the drag by returning NO.  Before returning NO, the delegate may implement its own dragging behavior using -[NSWindow dragImage:at:offset:event:pasteboard:source:slideBack:].  Alternatively, the delegate can enable a drag by returning YES, for example to override NSWindow's default behavior of prohibiting the drag of an edited document.  Lastly, the delegate can customize the pasteboard contents before returning YES.
*/
- (BOOL)window:(NSWindow *)window shouldDragDocumentWithEvent:(NSEvent *)event from:(NSPoint)dragImageLocation withPasteboard:(NSPasteboard *)pasteboard NS_AVAILABLE_MAC(10_5);

- (NSSize)window:(NSWindow *)window willUseFullScreenContentSize:(NSSize)proposedSize NS_AVAILABLE_MAC(10_7);

- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions NS_AVAILABLE_MAC(10_7);

/* The default animation between a window and its fullscreen representation is a crossfade.  With knowledge of the layout of a window before and after it enters fullscreen, an application can do a much better job on the animation.  The following API allows a window delegate to customize the animation by providing a custom window or windows containing layers or other effects.  In order to manage windows on spaces, we need the window delegate to provide a list of windows involved in the animation.  If an application does not do a custom animation, this method can be unimplemented or can return nil.  window:startCustomAnimationToEnterFullScreenWithDuration: will be called only if customWindowsToEnterFullScreenForWindow: returns non-nil.  
 */
- (NSArray *)customWindowsToEnterFullScreenForWindow:(NSWindow *)window NS_AVAILABLE_MAC(10_7);

/* The system has started its animation into fullscreen, including transitioning to a new space.  Start the window fullscreen animation immediately, and perform the animation with the given duration to  be in sync with the system animation.  This method is called only if customWindowToEnterFullScreenForWindow: returned non-nil. 
*/
- (void)window:(NSWindow *)window startCustomAnimationToEnterFullScreenWithDuration:(NSTimeInterval)duration NS_AVAILABLE_MAC(10_7);

/* In some cases, the transition to enter fullscreen will fail, due to being in the midst of handling some other animation or user gesture.  We will attempt to minimize these cases, but believe there is a need for failure handling.  This method indicates that there was an error, and the application should clean up any work it may have done to prepare to enter fullscreen.  This message will be sent whether or not the delegate indicated a custom animation by returning non-nil from  customWindowsToEnterFullScreenForWindow:.
*/
- (void)windowDidFailToEnterFullScreen:(NSWindow *)window NS_AVAILABLE_MAC(10_7);

/* The window is about to exit fullscreen mode.  The following API allows a window delegate to customize the animation when the window is about to exit fullscreen.  In order to manage windows on spaces, we need the window delegate to provide a list of windows involved in the animation.  If an application does not do a custom animation, this method can be unimplemented or can return nil.  window:startCustomAnimationToExitFullScreenWithDuration: will be called only if customWindowsToExitFullScreenForWindow: returns non-nil. 
*/
- (NSArray *)customWindowsToExitFullScreenForWindow:(NSWindow *)window NS_AVAILABLE_MAC(10_7);

/* The system has started its animation out of fullscreen, including transitioning back to the desktop space.  Start the window animation immediately, and perform the animation with the given duration to  be in sync with the system animation.  This method is called only if customWindowsToExitFullScreenForWindow: returned non-nil. 
*/
- (void)window:(NSWindow *)window startCustomAnimationToExitFullScreenWithDuration:(NSTimeInterval)duration NS_AVAILABLE_MAC(10_7);

/* customWindowsToEnterFullScreenForWindow:onScreen: will be called in place of customWindowsToEnterFullScreenForWindow: if both are implemented */
- (NSArray *)customWindowsToEnterFullScreenForWindow:(NSWindow *)window onScreen:(NSScreen *)screen NS_AVAILABLE_MAC(10_9);

/* window:startCustomAnimationToEnterFullScreenOnScreen:withDuration: will be called in place of window:startCustomAnimationToEnterFullScreenWithDuration: if both are implemented */
- (void)window:(NSWindow *)window startCustomAnimationToEnterFullScreenOnScreen:(NSScreen *)screen withDuration:(NSTimeInterval)duration NS_AVAILABLE_MAC(10_9);

/* In some cases, the transition to exit fullscreen will fail, due to being in the midst of handling some other animation or user gesture.  We will attempt to minimize these cases, but believe there is a need for failure handling.  This method indicates that there was an error, and the application should clean up any work it may have done to prepare to exit fullscreen.  This message will be sent whether or not the delegate indicated a custom animation by returning non-nil from  customWindowsToExitFullScreenForWindow:.
*/
- (void)windowDidFailToExitFullScreen:(NSWindow *)window NS_AVAILABLE_MAC(10_7);


/* Windows entering the version browser will be resized to the size returned by this method. If either dimension of the returned size is larger than the maxPreferredFrameSize, the window will also be scaled down to ensure it fits properly in the version browser. Returned sizes larger than maxAllowedSize will be constrained to that size. If this method is not implemented, the version browser will use -window:willUseStandardFrame: to determine the resulting window frame size.
*/
- (NSSize)window:(NSWindow *)window willResizeForVersionBrowserWithMaxPreferredSize:(NSSize)maxPreferredFrameSize maxAllowedSize:(NSSize)maxAllowedFrameSize NS_AVAILABLE_MAC(10_7);


/* Method called by -[NSWindow encodeRestorableStateWithCoder:] to give the delegate a chance to encode any additional state into the NSCoder.  This state is available in the NSCoder passed to restoreWindowWithIdentifier:state:handler: . See the header NSWindowRestoration.h for more information.
*/
- (void)window:(NSWindow *)window willEncodeRestorableState:(NSCoder *)state NS_AVAILABLE_MAC(10_7);

/* Method called by -[NSWindow restoreStateWithCoder:] to give the delegate a chance to restore its own state, which it may decode from the NSCoder. See the header NSWindowRestoration.h for more information.
*/
- (void)window:(NSWindow *)window didDecodeRestorableState:(NSCoder *)state NS_AVAILABLE_MAC(10_7);

/* Notifications
*/
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
- (void)windowDidChangeScreenProfile:(NSNotification *)notification;
- (void)windowDidChangeBackingProperties:(NSNotification *)notification NS_AVAILABLE_MAC(10_7); // added in 10.7.3
- (void)windowWillBeginSheet:(NSNotification *)notification;
- (void)windowDidEndSheet:(NSNotification *)notification;
- (void)windowWillStartLiveResize:(NSNotification *)notification    NS_AVAILABLE_MAC(10_6);
- (void)windowDidEndLiveResize:(NSNotification *)notification   NS_AVAILABLE_MAC(10_6);
- (void)windowWillEnterFullScreen:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowDidEnterFullScreen:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowWillExitFullScreen:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowDidExitFullScreen:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowWillEnterVersionBrowser:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowDidEnterVersionBrowser:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowWillExitVersionBrowser:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowDidExitVersionBrowser:(NSNotification *)notification   NS_AVAILABLE_MAC(10_7);
- (void)windowDidChangeOcclusionState:(NSNotification *)notification NS_AVAILABLE_MAC(10_9);
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

/* NSWindowDidChangeBackingPropertiesNotification is posted on 10.7.3 and later, when a window's backingScaleFactor and/or its colorSpace changes.  When running on a system version where this new notification is available, applications should use it instead of NSWindowDidChangeScreenProfileNotification to watch for changes to either of these backing store properties.  Many applications won't have any need to watch for this notification, but those that perform sophisticated color handling or manually manage their own caches of window-resolution-and/or/colorspace-appropriate bitmapped images will find this notification useful, as a prompt to invalidate their caches or schedule other reassessment for the new resolution and/or color space as needed.  The notification's userInfo dictionary specifies the window's previous backingScaleFactor and colorSpace.  You can compare these with the window's new backingScaleFactor and colorSpace at the time of the notification, to determine which of these two properties (potentially both) changed.
*/
APPKIT_EXTERN NSString * const NSWindowDidChangeBackingPropertiesNotification NS_AVAILABLE_MAC(10_7); // added in 10.7.3; userInfo keys: NSBackingPropertyOldScaleFactorKey, NSBackingPropertyOldColorSpaceKey

APPKIT_EXTERN NSString * const NSBackingPropertyOldScaleFactorKey NS_AVAILABLE_MAC(10_7); // added in 10.7.3; an NSNumber
APPKIT_EXTERN NSString * const NSBackingPropertyOldColorSpaceKey NS_AVAILABLE_MAC(10_7);  // added in 10.7.3; an NSColorSpace


/* NSWindowDidChangeScreenProfileNotification is posted when a window's display's color profile changes, or when the window moves to a display that has a different color profile.  When running on 10.7.3 or later, this notification is still posted for compatibility, but modern applications should instead watch for NSWindowDidChangeBackingPropertiesNotification, which is posted for both color space and resolution changes, and facilitates handling both in a single update and redisplay pass.
*/
APPKIT_EXTERN NSString *NSWindowDidChangeScreenProfileNotification;

/* NSWindowWillStartLiveResizeNotification is sent when the user starts a live resize operation via a mouseDown in the resize corner.  The notification will be sent before the window size is changed.  Note that this notification is sent once for a sequence of window resize operations */
APPKIT_EXTERN NSString * const NSWindowWillStartLiveResizeNotification  NS_AVAILABLE_MAC(10_6);
/* NSWindowDidEndLiveResizeNotification is sent after the user ends a live resize operation via a mouseUp in the resize corner.  The notification will be sent after the final window size change.    Note that this notification is sent once for a sequence of window resize operations */
APPKIT_EXTERN NSString * const NSWindowDidEndLiveResizeNotification  NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSWindowWillEnterFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowDidEnterFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowWillExitFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowDidExitFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowWillEnterVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowDidEnterVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowWillExitVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSWindowDidExitVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
/* Upon receiving this notification, you can query the NSWindow for its current occlusion state. Note that this only notifies about changes in the state of the occlusion, not when the occlusion region changes. You can use this notification to increase responsiveness and save power, by halting any expensive calculations that the user can not see. */
APPKIT_EXTERN NSString * const NSWindowDidChangeOcclusionStateNotification NS_AVAILABLE_MAC(10_9);
