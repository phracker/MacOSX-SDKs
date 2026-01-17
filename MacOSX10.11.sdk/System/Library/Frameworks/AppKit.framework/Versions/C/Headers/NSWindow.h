/*
	NSWindow.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
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

NS_ASSUME_NONNULL_BEGIN

@class NSButton, NSButtonCell, NSColor, NSImage, NSPasteboard, NSScreen;
@class NSNotification, NSText, NSView, NSMutableSet, NSSet, NSDate;
@class NSToolbar, NSGraphicsContext, NSURL, NSColorSpace;
@class NSDockTile, NSViewController, NSTitlebarAccessoryViewController;

@protocol NSWindowDelegate;

#define NSAppKitVersionNumberWithCustomSheetPosition 686.0
#define NSAppKitVersionNumberWithDeferredWindowDisplaySupport		1019.0

enum {
    NSBorderlessWindowMask = 0,
    NSTitledWindowMask = 1 << 0,
    NSClosableWindowMask = 1 << 1,
    NSMiniaturizableWindowMask = 1 << 2,
    NSResizableWindowMask	= 1 << 3,
    
/* Specifies a window with textured background. Textured windows generally don't draw a top border line under the titlebar/toolbar. To get that line, use the NSUnifiedTitleAndToolbarWindowMask mask.
 */
    NSTexturedBackgroundWindowMask = 1 << 8,
    
/* Specifies a window whose titlebar and toolbar have a unified look - that is, a continuous background. Under the titlebar and toolbar a horizontal separator line will appear.
 */
    NSUnifiedTitleAndToolbarWindowMask = 1 << 12,
    
/* When set, the window will appear full screen. This mask is automatically toggled when toggleFullScreen: is called.
 */
    NSFullScreenWindowMask NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 14,
    
/* If set, the contentView will consume the full size of the window; it can be combined with other window style masks, but is only respected for windows with a titlebar.
    Utilizing this mask opts-in to layer-backing. Utilize the contentLayoutRect or auto-layout contentLayoutGuide to layout views underneath the titlebar/toolbar area.
 */
    NSFullSizeContentViewWindowMask NS_ENUM_AVAILABLE_MAC(10_10) = 1 << 15
};

// Additional NSModalResponse values
enum {
    NSModalResponseOK = 1,
    NSModalResponseCancel	= 0
} NS_ENUM_AVAILABLE_MAC(10_9);


/* used with NSRunLoop's performSelector:target:argument:order:modes: */
enum {
    NSDisplayWindowRunLoopOrdering	= 600000,
    NSResetCursorRectsRunLoopOrdering	= 700000
};

typedef NS_ENUM(NSUInteger, NSWindowSharingType) {
    NSWindowSharingNone = 0,                // Window contents may not be read by another process
    NSWindowSharingReadOnly = 1,            // Window contents may be read but not modified by another process
    NSWindowSharingReadWrite = 2            // Window contents may be read or modified by another process
} NS_ENUM_AVAILABLE_MAC(10_5);

typedef NS_ENUM(NSUInteger, NSWindowBackingLocation) {
    NSWindowBackingLocationDefault = 0,		// System determines if window backing store is in VRAM or main memory
    NSWindowBackingLocationVideoMemory = 1,		// Window backing store is in VRAM
    NSWindowBackingLocationMainMemory = 2		// Window backing store is in main memory
} NS_ENUM_AVAILABLE_MAC(10_5);


typedef NS_OPTIONS(NSUInteger, NSWindowCollectionBehavior) {
    NSWindowCollectionBehaviorDefault = 0,
    NSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0,
    NSWindowCollectionBehaviorMoveToActiveSpace = 1 << 1,
    
    /* You may specify at most one of NSWindowCollectionBehaviorManaged, NSWindowCollectionBehaviorTransient, or NSWindowCollectionBehaviorStationary.  If unspecified, the window gets the default behavior determined by its window level */
    NSWindowCollectionBehaviorManaged NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 2,         // participates in spaces, exposé.  Default behavior if windowLevel == NSNormalWindowLevel
    NSWindowCollectionBehaviorTransient NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 3,       // floats in spaces, hidden by exposé.  Default behavior if windowLevel != NSNormalWindowLevel
    NSWindowCollectionBehaviorStationary NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 4,      // unaffected by exposé.  Stays visible and stationary, like desktop window

    /* You may specify at most one of NSWindowCollectionBehaviorParticipatesInCycle or NSWindowCollectionBehaviorIgnoresCycle.  If unspecified, the window gets the default behavior determined by its window level */
    NSWindowCollectionBehaviorParticipatesInCycle NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 5,     // default behavior if windowLevel == NSNormalWindowLevel
    NSWindowCollectionBehaviorIgnoresCycle NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 6,            // default behavior if windowLevel != NSNormalWindowLevel
    
    /* You may specify at most one of NSWindowCollectionBehaviorFullScreenPrimary or NSWindowCollectionBehaviorFullScreenAuxiliary. */
    NSWindowCollectionBehaviorFullScreenPrimary NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 7,       // the frontmost window with this collection behavior will be the fullscreen window.
    NSWindowCollectionBehaviorFullScreenAuxiliary NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 8,     // windows with this collection behavior can be shown with the fullscreen window.
    
    /* 	You may specify at most one of NSWindowCollectionBehaviorFullScreenAllowsTiling or NSWindowCollectionBehaviorFullScreenDisallowsTiling, or an assertion will be raised.
     
     The default behavior is to allow any window to participate in full screen tiling, as long as it meets certain requirements, such as being resizable and not a panel or sheet. Windows which are not full screen capable can still become a secondary tile in full screen. A window can explicitly allow itself to be placed into a full screen tile by including NSWindowCollectionBehaviorFullScreenAllowsTiling. Even if a window allows itself to be placed in a tile, it still may not be put in the tile if its minFullScreenContentSize is too large to fit. A window can explicitly disallow itself from being placed in a full screen tile by including NSWindowCollectionBehaviorFullScreenDisallowsTiling. This is useful for non-full screen capable windows to explicitly prevent themselves from being tiled. It can also be used by a full screen window to prevent any other windows from being placed in its full screen tile. */
    NSWindowCollectionBehaviorFullScreenAllowsTiling NS_ENUM_AVAILABLE_MAC(10_11) = 1 << 11,       // This window can be a full screen tile window. It does not have to have FullScreenPrimary set.
    NSWindowCollectionBehaviorFullScreenDisallowsTiling NS_ENUM_AVAILABLE_MAC(10_11) = 1 << 12      // This window can NOT be made a full screen tile window; it still may be allowed to be a regular FullScreenPrimary window.
} NS_ENUM_AVAILABLE_MAC(10_5);


typedef NS_ENUM(NSInteger, NSWindowAnimationBehavior) {
    NSWindowAnimationBehaviorDefault = 0,       // let AppKit infer animation behavior for this window
    NSWindowAnimationBehaviorNone = 2,          // suppress inferred animations (don't animate)

    NSWindowAnimationBehaviorDocumentWindow = 3,
    NSWindowAnimationBehaviorUtilityWindow = 4,
    NSWindowAnimationBehaviorAlertPanel = 5
} NS_ENUM_AVAILABLE_MAC(10_7);


/* Options used in +windowNumbersWithOptions:.  If no options are specified, the returned list contains window numbers for visible windows on the active space belonging to the calling application. */
enum {
    NSWindowNumberListAllApplications = 1 << 0,
    NSWindowNumberListAllSpaces = 1 << 4
} NS_ENUM_AVAILABLE_MAC(10_6);

typedef NS_OPTIONS(NSUInteger, NSWindowOcclusionState) {
    /* If set, at least part of the window is visible. If not set, the entire window is occluded. Windows with non-rectangular shapes may be completely occluded on screen but still count as visible, if their bounding box falls into a visible region. Windows that are completely transparent may also still count as visible. */
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


typedef NS_ENUM(NSUInteger, NSSelectionDirection) {
    NSDirectSelection = 0,
    NSSelectingNext,
    NSSelectingPrevious
};

/* Standard window buttons */
typedef NS_ENUM(NSUInteger, NSWindowButton) {
    NSWindowCloseButton,
    NSWindowMiniaturizeButton,
    NSWindowZoomButton,
    NSWindowToolbarButton,
    NSWindowDocumentIconButton,
    NSWindowDocumentVersionsButton NS_ENUM_AVAILABLE_MAC(10_7) = 6,
    NSWindowFullScreenButton NS_ENUM_AVAILABLE_MAC(10_7)
};

typedef NS_ENUM(NSInteger, NSWindowTitleVisibility) {
    /* The default mode has a normal window title and titlebar buttons. */
    NSWindowTitleVisible  = 0,
    /* The always hidden mode hides the title and moves the toolbar up into the area previously occupied by the title. */
    NSWindowTitleHidden = 1,
} NS_ENUM_AVAILABLE_MAC(10_10);

#define NSEventDurationForever  DBL_MAX

@class NSWindowAuxiliary;
@class NSEvent;
@class NSWindowController;

@interface NSWindow : NSResponder <NSAnimatablePropertyContainer, NSUserInterfaceValidations, NSUserInterfaceItemIdentification, NSAppearanceCustomization, NSAccessibilityElement, NSAccessibility>
{
    /*All instance variables are private*/
    NSRect              _frame;
    id                  _contentView;
    id                  _delegate;
    NSResponder		*_firstResponder;
    NSView		*_lastLeftHit;
    NSView		*_lastRightHit;
    id                  _unusedWindow2;
    id                  _fieldEditor;
    int                 _winEventMask;
    NSInteger           _windowNum;
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
    NSToolbar           *_toolbar;
    struct __wFlags {
        unsigned int  backing:2;
        unsigned int  visible:1;
        unsigned int  isMainWindow:1;
        unsigned int  isKeyWindow:1;
        unsigned int  hidesOnDeactivate:1;
        unsigned int  dontFreeWhenClosed:1;
        unsigned int  oneShot:1;
        unsigned int  deferred:1;
        unsigned int  cursorRectsDisabled:1;
        unsigned int  haveFreeCursorRects:1;
        unsigned int  validCursorRects:1;
        unsigned int  docEdited:1;
        unsigned int  dynamicDepthLimit:1;
        unsigned int  worksWhenModal:1;
        unsigned int  limitedBecomeKey:1;
        unsigned int  needsFlush:1;
        unsigned int  viewsNeedDisplay:1;
        unsigned int  ignoredFirstMouse:1;
        unsigned int  repostedFirstMouse:1;
        unsigned int  windowDying:1;
        unsigned int  tempHidden:1;
        unsigned int  floatingPanel:1;
        unsigned int  wantsToBeOnMainScreen:1;
        unsigned int  optimizedDrawingOk:1;
        unsigned int  optimizeDrawing:1;
        unsigned int  titleIsRepresentedFilename:1;
        unsigned int  excludedFromWindowsMenu:1;
        unsigned int  depthLimit:4;
        unsigned int  delegateReturnsValidRequestor:1;
        unsigned int  lmouseupPending:1;
        unsigned int  rmouseupPending:1;
        unsigned int  wantsToDestroyRealWindow:1;
        unsigned int  wantsToRegDragTypes:1;
        unsigned int  sentInvalidateCursorRectsMsg:1;
        unsigned int  avoidsActivation:1;
        unsigned int  frameSavedUsingTitle:1;
        unsigned int  didRegDragTypes:1;
        unsigned int  delayedOneShot:1;
        unsigned int  postedNeedsDisplayNote:1;
        unsigned int  postedInvalidCursorRectsNote:1;
        unsigned int  initialFirstResponderTempSet:1;
        unsigned int  autodisplay:1;
        unsigned int  tossedFirstEvent:1;
        unsigned int  isImageCache:1;
        unsigned int  autolayoutEngagedSomewhere:1;
        unsigned int  hasRegisteredBackdropViews:1;
        unsigned int  hasSubLevel:1;
        unsigned int  keyViewSelectionDirection:2;
        unsigned int  defaultButtonCellKETemporarilyDisabled:1;
        unsigned int  defaultButtonCellKEDisabled:1;
        unsigned int  menuHasBeenSet:1;
        unsigned int  wantsToBeModal:1;
        unsigned int  showingModalFrame:1;
        unsigned int  isTerminating:1;
        unsigned int  makingFirstResponderForMouseDown:1;
        unsigned int  needsZoom:1;
        unsigned int  sentWindowNeedsDisplayMsg:1;
        unsigned int  unused:2;
    } _wFlags;
    id _defaultButtonCell;
    NSView *_initialFirstResponder;
    NSWindowAuxiliary *_auxiliaryStorage;
}

+ (NSRect)frameRectForContentRect:(NSRect)cRect styleMask:(NSUInteger)aStyle;
+ (NSRect)contentRectForFrameRect:(NSRect)fRect styleMask:(NSUInteger)aStyle;
+ (CGFloat)minFrameWidthWithTitle:(NSString *)aTitle styleMask:(NSUInteger)aStyle;
+ (NSWindowDepth)defaultDepthLimit;

- (NSRect)frameRectForContentRect:(NSRect)contentRect;
- (NSRect)contentRectForFrameRect:(NSRect)frameRect;

- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag;
- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag screen:(nullable NSScreen *)screen;

@property (copy) NSString *title;

/* See the enum values for how this property works.
 */
@property NSWindowTitleVisibility titleVisibility NS_AVAILABLE_MAC(10_10); // Default value is NSWindowTitleVisible

/* When YES, the titlebar doesn't draw its background, allowing all buttons to show through, and "click through" to happen. In general, this is only useful when NSFullSizeContentViewWindowMask is set.
 */
@property BOOL titlebarAppearsTransparent NS_AVAILABLE_MAC(10_10);

/* The contentLayoutRect will return the area inside the window that is for non-obscured content. Typically, this is the same thing as the contentView's frame. However, for windows with the NSFullSizeContentViewWindowMask set, there needs to be a way to determine the portion that is not under the toolbar. The contentLayoutRect returns the portion of the layout that is not obscured under the toolbar. contentLayoutRect is in window coordinates. It is KVO compliant. */
@property (readonly) NSRect contentLayoutRect NS_AVAILABLE_MAC(10_10);

/* contentLayoutGuide is a corollary to contentLayoutRect. It can be used by autolayout constraints to automatically bind to the contentLayoutRect.
 */
@property (nullable, readonly) id contentLayoutGuide NS_AVAILABLE_MAC(10_10);

/* The following methods allow you to add accessory views to the titlebar/toolbar area of a window. See NSTitlebarAccessoryViewController for more details.
 */
@property (copy) NSArray<__kindof NSTitlebarAccessoryViewController *> *titlebarAccessoryViewControllers NS_AVAILABLE_MAC(10_10);
- (void)addTitlebarAccessoryViewController:(NSTitlebarAccessoryViewController *)childViewController NS_AVAILABLE_MAC(10_10);
- (void)insertTitlebarAccessoryViewController:(NSTitlebarAccessoryViewController *)childViewController atIndex:(NSInteger)index NS_AVAILABLE_MAC(10_10);
/* NOTE: you can use this method, or removeFromParentViewController, which ever is easier. */
- (void)removeTitlebarAccessoryViewControllerAtIndex:(NSInteger)index NS_AVAILABLE_MAC(10_10);


/* setRepresentedURL:
If url is not nil and its path is not empty, the window will show a document icon in the titlebar.  
If the url represents a filename or other resource with a known icon, that icon will be used as the document icon.  Otherwise the default document icon will be used.  The icon can be customized using [[NSWindow standardWindowButton:NSWindowDocumentIconButton] setImage:customImage].  If url is not nil and its path is not empty, the window will have a pop-up menu which can be shown via command-click on the area containing the document icon and title.  By default, this menu will display the path components of the url.  The presence and contents of this menu can be controlled by the delegate method window:shouldPopUpDocumentPathMenu:If the url is nil or has an empty path, the window will not show a document icon and will not have a pop-up menu available via command-click.
*/
@property (nullable, copy) NSURL *representedURL NS_AVAILABLE_MAC(10_5);
@property (copy) NSString *representedFilename;
- (void)setTitleWithRepresentedFilename:(NSString *)filename;
@property (getter=isExcludedFromWindowsMenu) BOOL excludedFromWindowsMenu;
@property (nullable, strong) __kindof NSView *contentView;
@property (nullable, assign) id<NSWindowDelegate> delegate;
@property (readonly) NSInteger windowNumber;
@property NSUInteger styleMask;
/* Valid styleMask settings have the same restrictions as the styleMask passed to -initWithContentRect:styleMask:backing:defer:.  Some styleMask changes will cause the view hierarchy to be rebuilt, since there is a different subclass for the top level view of a borderless window than for the top level view of a titled window. */
- (void)setStyleMask:(NSUInteger)styleMask NS_AVAILABLE_MAC(10_6);
- (nullable NSText *)fieldEditor:(BOOL)createFlag forObject:(nullable id)anObject;
- (void)endEditingFor:(nullable id)anObject;

- (NSRect)constrainFrameRect:(NSRect)frameRect toScreen:(nullable NSScreen *)screen;
- (void)setFrame:(NSRect)frameRect display:(BOOL)flag;
- (void)setContentSize:(NSSize)aSize;
- (void)setFrameOrigin:(NSPoint)aPoint;
- (void)setFrameTopLeftPoint:(NSPoint)aPoint;
- (NSPoint)cascadeTopLeftFromPoint:(NSPoint)topLeftPoint;
@property (readonly) NSRect frame;

// smooth resize
// subclasses can override animationResizeTime: to control the total time for the frame change.
// newFrame is the rect passed into setFrame:display:animate:
- (NSTimeInterval)animationResizeTime:(NSRect)newFrame;
// setFrame:display:animate: is equivalent to setFrame:display: if animateFlag is NO
// If animationFlag is YES, this method will perform a smooth resize of the window, where the total time for the resize is specified by -animationResizeTime:
- (void)setFrame:(NSRect)frameRect display:(BOOL)displayFlag animate:(BOOL)animateFlag;

@property (readonly) BOOL inLiveResize    NS_AVAILABLE_MAC(10_6);

// show/hide resize corner (does not affect whether window is resizable)
@property BOOL showsResizeIndicator;

@property NSSize resizeIncrements;
@property NSSize aspectRatio;

@property NSSize contentResizeIncrements;
@property NSSize contentAspectRatio;

- (void)disableFlushWindow;
- (void)enableFlushWindow;
@property (getter=isFlushWindowDisabled, readonly) BOOL flushWindowDisabled;
- (void)flushWindow;
- (void)flushWindowIfNeeded;
@property BOOL viewsNeedDisplay;
- (void)displayIfNeeded;
- (void)display;
@property (getter=isAutodisplay) BOOL autodisplay;

@property BOOL preservesContentDuringLiveResize;

- (void)update;

- (BOOL)makeFirstResponder:(nullable NSResponder *)aResponder;
/* firstResponder is Key Value Observing (KVO) compliant. */
@property (readonly, assign) NSResponder *firstResponder;

@property (readonly) NSInteger resizeFlags;
- (void)keyDown:(NSEvent *)theEvent;
- (void)close;
@property (getter=isReleasedWhenClosed) BOOL releasedWhenClosed;
- (void)miniaturize:(nullable id)sender;
- (void)deminiaturize:(nullable id)sender;
@property (getter=isZoomed, readonly) BOOL zoomed;
- (void)zoom:(nullable id)sender;
@property (getter=isMiniaturized, readonly) BOOL miniaturized;
- (BOOL)tryToPerform:(SEL)anAction with:(nullable id)anObject;
- (nullable id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;
@property (null_resettable, copy) NSColor *backgroundColor;

/* Indicates the thickness of a given border of the window. NSMinYEdge is the bottom edge of the window, while NSMaxYEdge is the top edge of the window. This method may throw an exception for values that don't apply to the current window styleMask; specifically, passing NSMaxYEdge for a non-textured window will always raise. The contentBorder does not include the titlebar or toolbar.
 */
- (void)setContentBorderThickness:(CGFloat)thickness forEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);
- (CGFloat)contentBorderThicknessForEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);

- (void)setAutorecalculatesContentBorderThickness:(BOOL)flag forEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);
- (BOOL)autorecalculatesContentBorderThicknessForEdge:(NSRectEdge)edge NS_AVAILABLE_MAC(10_5);

/* Calling -setMovable with a flag of NO will disable server-side dragging of the window via titlebar or background.  -setMovableByWindowBackground:YES is ignored on a window that returns NO from -isMovable.  When a window returns NO for -isMovable, it can be dragged between spaces only in spaces F8 mode, and its relative screen position is preserved.  Note that the a resizable window may still be resized, and the window frame may be changed programmatically.  Applications may choose to enable application-controlled window dragging after disabling server-side dragging (perhaps to achieve snapping or pinnning) by handling the mouseDown/mouseDragged/mouseUp sequence in -sendEvent: in an NSWindow subclass.  Note that a non movable window will also not be moved (or resized) by the system in response to a display reconfiguration. */
@property (getter=isMovable) BOOL movable NS_AVAILABLE_MAC(10_6);

@property (getter=isMovableByWindowBackground) BOOL movableByWindowBackground;

@property BOOL hidesOnDeactivate;

// indicate whether a window can be hidden during -[NSApplication hide:].  Default is YES
@property BOOL canHide;

- (void)center;
- (void)makeKeyAndOrderFront:(nullable id)sender;
- (void)orderFront:(nullable id)sender;
- (void)orderBack:(nullable id)sender;
- (void)orderOut:(nullable id)sender;
- (void)orderWindow:(NSWindowOrderingMode)place relativeTo:(NSInteger)otherWin;
- (void)orderFrontRegardless;

@property (nullable, strong) NSImage *miniwindowImage;
@property (null_resettable, copy) NSString *miniwindowTitle;

@property (readonly, strong) NSDockTile *dockTile NS_AVAILABLE_MAC(10_5);

@property (getter=isDocumentEdited) BOOL documentEdited;
@property (getter=isVisible, readonly) BOOL visible;
@property (getter=isKeyWindow, readonly) BOOL keyWindow;
@property (getter=isMainWindow, readonly) BOOL mainWindow;
@property (readonly) BOOL canBecomeKeyWindow;
@property (readonly) BOOL canBecomeMainWindow;
- (void)makeKeyWindow;
- (void)makeMainWindow;
- (void)becomeKeyWindow;
- (void)resignKeyWindow;
- (void)becomeMainWindow;
- (void)resignMainWindow;

@property (readonly) BOOL worksWhenModal;

/* Normally, application termination is prohibited when a modal window or sheet is open, without consulting the application delegate.  Some windows like the open panel or toolbar customization sheet should not prevent application termination.  -setPreventsApplicationTerminationWhenModal:NO on a modal window or sheet will override the default behavior and allow application termination to proceed, either through the sudden termination path if enabled, or on to the next step of consulting the application delegate.  By default, -preventsApplicationTerminationWhenModal returns YES */
@property BOOL preventsApplicationTerminationWhenModal NS_AVAILABLE_MAC(10_6);

/* New methods to convert window coordinates to screen coordinates */
- (NSRect)convertRectToScreen:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromScreen:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* New methods to convert to/from a pixel integral backing store space */
- (NSRect)convertRectToBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* Use NSIntegralRectWithOptions() to produce a backing store pixel aligned rectangle from the given input rectangle in window coordinates. */
- (NSRect)backingAlignedRect:(NSRect)aRect options:(NSAlignmentOptions)options NS_AVAILABLE_MAC(10_7);

/* Returns the scale factor representing the number of backing store pixels corresponding to each linear unit in window space on this NSWindow. This method is provided for rare cases when the explicit scale factor is needed. Please use -convert*ToBacking: methods whenever possible. */
@property (readonly) CGFloat backingScaleFactor NS_AVAILABLE_MAC(10_7); 

- (void)performClose:(nullable id)sender;
- (void)performMiniaturize:(nullable id)sender;
- (void)performZoom:(nullable id)sender;
@property (getter=isOneShot) BOOL oneShot;
- (NSData *)dataWithEPSInsideRect:(NSRect)rect;
- (NSData *)dataWithPDFInsideRect:(NSRect)rect;
- (void)print:(nullable id)sender;

- (void)disableCursorRects;
- (void)enableCursorRects;
- (void)discardCursorRects;
@property (readonly) BOOL areCursorRectsEnabled;
- (void)invalidateCursorRectsForView:(NSView *)aView;
- (void)resetCursorRects;

/*
 Default is NO. Set to YES to allow a window to display tooltips even when the application is in the background.  Note that, enabling tooltips in an inactive application will cause the app to do work any time the mouse passes over the window.  This can degrade system performance.
 Returns YES if this window displays tooltips even when the application is in the background.  To configure this setting you should call setAllowsToolTipsWhenApplicationIsInactive: instead of overriding -allowsToolTipsWhenApplicationIsInactive.
 */
@property BOOL allowsToolTipsWhenApplicationIsInactive;

@property NSBackingStoreType backingType;
@property NSInteger level;
@property NSWindowDepth depthLimit;
- (void)setDynamicDepthLimit:(BOOL)flag;
@property (readonly) BOOL hasDynamicDepthLimit;

/* The screen property returns the best screen for the window. If the window only intersects one screen, it returns that screen. If it intersects more than one screen, then it resolves the tie through based on what space it is mostly on. It may return nil if there are no available screens, or it is completely off screen.
 */
@property (nullable, readonly, strong) NSScreen *screen;
@property (nullable, readonly, strong) NSScreen *deepestScreen;

@property BOOL hasShadow;
- (void)invalidateShadow;
@property CGFloat alphaValue;
@property (getter=isOpaque) BOOL opaque;


/* -setSharingType: specifies whether the window content can be read and/or written from another process.  The default sharing type is NSWindowSharingReadOnly, which means other processes can read the window content (eg. for window capture) but cannot modify it.  If you set your window sharing type to NSWindowSharingNone, so that the content cannot be captured, your window will also not be able to participate in a number of system services, so this setting should be used with caution.  If you set your window sharing type to NSWindowSharingReadWrite, other processes can both read and modify the window content.
*/
@property NSWindowSharingType sharingType NS_AVAILABLE_MAC(10_5);

/* -setPreferredBackingLocation: sets the preferred location for the window backing store.  In general, you should not use this API unless indicated by performance measurement. -preferredBackingLocation gets the preferred location for the window backing store.  This may be different from the actual location.
*/
@property NSWindowBackingLocation preferredBackingLocation NS_AVAILABLE_MAC(10_5);
/* -backingLocation gets the current location of the window backing store.
*/
@property (readonly) NSWindowBackingLocation backingLocation NS_AVAILABLE_MAC(10_5);


/* Reports whether threading of view drawing is enabled for this window.  Defaults to YES.
*/
@property BOOL allowsConcurrentViewDrawing NS_AVAILABLE_MAC(10_6);

/* Sets whether threading of view drawing should be enabled for this window.  Defaults to YES.  When this is set to YES, AppKit's view system is allowed to perform -drawRect: activity for the window's views on threads other than the main thread, for views that have canDrawConcurrently == YES.  When this is set to NO, the window's views will be drawn serially as on 10.5 and earlier, even though some of the views may have canDrawConcurrently == YES.
*/

@property BOOL displaysWhenScreenProfileChanges;

- (void)disableScreenUpdatesUntilFlush;

/* This API controls whether the receiver is permitted onscreen before the user has logged in.  This property is off by default.  Alert panels and windows presented by input managers are examples of windows which should have this property set.
*/
@property BOOL canBecomeVisibleWithoutLogin NS_AVAILABLE_MAC(10_5);


@property NSWindowCollectionBehavior collectionBehavior NS_AVAILABLE_MAC(10_5);


/* Provides for per-window control over automatic orderFront/orderOut animation behaviors added in 10.7.  Can be set to NSWindowAnimationBehaviorNone to disable Appkit's automatic animations for a given window, or to one of the other non-Default NSWindowAnimationBehavior values to override AppKit's automatic inference of appropriate animation behavior based on the window's apparent type.
*/
@property NSWindowAnimationBehavior animationBehavior NS_AVAILABLE_MAC(10_7);


/* Returns YES if this window is associated with the active space.  For visible windows, this API indicates whether the window is currently visible on the active space.  For offscreen windows, it indicates whether ordering the window onscreen would make it bring it onto the active space */
@property (getter=isOnActiveSpace, readonly) BOOL onActiveSpace NS_AVAILABLE_MAC(10_6);

/* toggleFullScreen: enters or exits for full screeen. A window must have NSWindowCollectionBehaviorFullScreenAuxiliary or NSWindowCollectionBehaviorFullScreenPrimary included in the collectionBehavior property; if it does not, this method may simply do nothing.
 */
- (void)toggleFullScreen:(nullable id)sender NS_AVAILABLE_MAC(10_7);

@property (readonly, copy) NSString *stringWithSavedFrame;
- (void)setFrameFromString:(NSString *)string;
- (void)saveFrameUsingName:(NSString *)name;
// Set force=YES to use setFrameUsingName on a non-resizable window
- (BOOL)setFrameUsingName:(NSString *)name force:(BOOL)force;
- (BOOL)setFrameUsingName:(NSString *)name;
- (BOOL)setFrameAutosaveName:(NSString *)name;
@property (readonly, copy) NSString *frameAutosaveName;
+ (void)removeFrameUsingName:(NSString *)name;


- (void)cacheImageInRect:(NSRect)aRect;
- (void)restoreCachedImage;
- (void)discardCachedImage;

/* NOTE: minSize/contentMinSize and maxSize/contentMaxSize are ignored when using autolayout.
 */
@property NSSize minSize;
@property NSSize maxSize;
@property NSSize contentMinSize;
@property NSSize contentMaxSize;

/* These are the min and max values for a full screen tiled window.
 
 In general, one should not need to explicitly set the min/maxFullScreenContentSize. If an application does not change its window content upon entering full screen, then the normal auto layout min and max size will be sufficient, and one should not set these values. If an application does significantly rework the UI in full screen, then it may be necessary to set a min/maxFullScreenContentSize. This size is what is used to determine if a window can fit when it is in full screen in a tile. This property may be used even if the window does not support full screen, but are implicitly opted into supporting a full screen tile based on resizing behavior and window properties (see the collectionBehavior property). By default, the system uses auto layout to determine the min and max sizes. If auto layout is not used, contentMinSize and contentMaxSize are queried.
 */
@property NSSize minFullScreenContentSize NS_AVAILABLE_MAC(10_11);
@property NSSize maxFullScreenContentSize NS_AVAILABLE_MAC(10_11);

/* Tracks events matching the supplied mask with the supplied tracking handler until the tracking handler explicitly terminates tracking. Each event is removed from the event queue then passed to the tracking handler. If a matching event does not exist in the event queue, then the main thread blocks in the specified runloop mode until an event of the requested type is received or the timeout expires. If the timeout expires, the tracking handler is called with a nil event. A negative timeout is interpreted as 0. Use NSEventDurationForever to never timeout. Tracking continues until *stop is set to YES. Calls to -nextEventMatchingMask:… are allowed inside the trackingHandler block. This method returns once tracking is terminated.
 */
- (void)trackEventsMatchingMask:(NSEventMask)mask timeout:(NSTimeInterval)timeout mode:(NSString *)mode handler:(void(^)(NSEvent *event, BOOL *stop))trackingHandler NS_AVAILABLE_MAC(10_10);
- (nullable NSEvent *)nextEventMatchingMask:(NSUInteger)mask;
- (nullable NSEvent *)nextEventMatchingMask:(NSUInteger)mask untilDate:(nullable NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSUInteger)mask beforeEvent:(nullable NSEvent *)lastEvent;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
@property (nullable, readonly, strong) NSEvent *currentEvent;
@property BOOL acceptsMouseMovedEvents;
@property BOOL ignoresMouseEvents;
@property (readonly, copy) NSDictionary<NSString *, id> *deviceDescription;
- (void)sendEvent:(NSEvent *)theEvent;
@property (readonly) NSPoint mouseLocationOutsideOfEventStream;

@property (nullable, assign) __kindof NSWindowController *windowController;

/*
 This API presents modal-sheets on this window. It replaces NSApp's -beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo:.
 
 If the window already has a presented sheet, it will queue up sheets presented after that. Once the presented sheet is dismissed, the next queued sheet will be presented, and so forth.
 Critical sheets will skip this queuing process and be immediately presented on top of existing sheets. The presented sheet will be temporarily disabled and be able to be interacted with after the critical sheet is dismissed, and will then continue as normal. Critical sheets should only be used for time-critical or important events, when the presentation of the sheet needs to be guaranteed (Critical Alerts will automatically use this API).
*/
- (void)beginSheet:(NSWindow *)sheetWindow completionHandler:(void (^ __nullable)(NSModalResponse returnCode))handler NS_AVAILABLE_MAC(10_9);
- (void)beginCriticalSheet:(NSWindow *)sheetWindow completionHandler:(void (^ __nullable)(NSModalResponse returnCode))handler NS_AVAILABLE_MAC(10_9);
- (void)endSheet:(NSWindow *)sheetWindow NS_AVAILABLE_MAC(10_9);
- (void)endSheet:(NSWindow *)sheetWindow returnCode:(NSModalResponse)returnCode NS_AVAILABLE_MAC(10_9);
@property (readonly, copy) NSArray<__kindof NSWindow *> *sheets NS_AVAILABLE_MAC(10_9); // An ordered array of the sheets on the window. This consists of the presented sheets in top-to-bottom order, followed by queued sheets in the order they were queued. This does not include nested/sub-sheets.
@property (nullable, readonly, strong) NSWindow *attachedSheet; // Returns the top-most sheet if there is one or more sheets, or nil if there is no sheet.

@property (getter=isSheet, readonly) BOOL sheet;

/* Returns the window that the sheet is directly attached to. This is based on the logical attachment of the sheet, not appearance.
 This relationship exists starting when the sheet is begun (using NSApplication's -beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo: or NSWindow's -beginSheet:completionHandler:), and ending once it is ordered out.
 
 Returns nil if the window is not a sheet or has no sheet parent.
 */
@property (nullable, readonly, strong) NSWindow *sheetParent NS_AVAILABLE_MAC(10_9);


+ (nullable NSButton *)standardWindowButton:(NSWindowButton)b forStyleMask:(NSUInteger)styleMask;
- (nullable NSButton *)standardWindowButton:(NSWindowButton)b;

- (void)addChildWindow:(NSWindow *)childWin ordered:(NSWindowOrderingMode)place;
- (void)removeChildWindow:(NSWindow *)childWin;
@property (nullable, readonly, copy) NSArray<__kindof NSWindow *> *childWindows;

@property (nullable, assign) NSWindow *parentWindow;

/* Returns NSGraphicsContext used to render the receiver's content on the screen for the calling thread.
*/
@property (nullable, readonly, strong) NSGraphicsContext *graphicsContext;

@property (nullable, strong) NSColorSpace *colorSpace NS_AVAILABLE_MAC(10_6);

/* windowNumbersWithOptions: returns an autoreleased array of NSNumbers containing windowNumbers for all visible windows satisfying options.  If no options are specified, only visible windows belonging to the calling application and on the active space are included.  If options include NSWindowNumberListAllApplications, visible windows belonging to all applications are included.  If options include NSWindowNumberListAllSpaces, visible windows on all spaces are included.  Windows on the active space are returned in z-order.  
   Examples: 
      To get an array of windowNumbers visible on the current space and belonging to the calling application:  
	windowNumbers = [NSWindow windowNumbersWithOptions:0];
      To get an array of windowNumbers visible on any space and belonging to any application:
	windowNumbers = [NSWindow windowNumbersWithOptions:NSWindowNumberListAllApplications|NSWindowNumberListAllSpaces];
      To get an array of windowNumbers visible on any space and belonging to the calling application:
	windowNumbers = [NSWindow windowNumbersWithOptions:NSWindowNumberListAllSpaces];
*/
+ (nullable NSArray<NSNumber *> *)windowNumbersWithOptions:(NSWindowNumberListOptions)options NS_AVAILABLE_MAC(10_6);

/* windowNumberAtPoint:belowWindowWithWindowNumber: returns the number of the frontmost window that would be hit by a mouseDown at the screen location "point".  "windowNum" can be specified to exclude a given window along with all windows above it, and may belong to any application.  If no windows are to be excluded, specify 0 for "windowNum".  The windowNumber returned may correspond to a window in another application.    
*/
+ (NSInteger)windowNumberAtPoint:(NSPoint)point belowWindowWithWindowNumber:(NSInteger)windowNumber NS_AVAILABLE_MAC(10_6);

@property (readonly) NSWindowOcclusionState occlusionState NS_AVAILABLE_MAC(10_9);


/* NSViewController Support */

/* The main content view controller for the window. This provides the contentView of the window. Assigning this value will remove the existing contentView and will make the contentViewController.view the main contentView for the window. The default value is nil. The contentViewController only controls the contentView, and not the title of the window. The window title can easily be bound to the contentViewController with the following: [window bind:NSTitleBinding toObject:contentViewController withKeyPath:@"title" options:nil]. Setting the contentViewController will cause the window to resize based on the current size of the contentViewController. Autolayout should be used to restrict the size of the window. The value of the contentViewController is encoded in the NIB. Directly assigning a contentView will clear out the rootViewController.
 */
@property (nullable, strong) NSViewController *contentViewController NS_AVAILABLE_MAC(10_10);

/* Convenience method for creating an autoreleased titled window with the given contentViewController. A basic NSWindow with the following attributes is made: titled, closable, resizable, miniaturizable. The window's title is automatically bound to the contentViewController's title. The size of the window can easily be controlled by utilizing autolayout and applying size constraints to the view (or its subviews). The window has isReleasedWhenClosed set to NO, and it must be explicitly retained to keep the window instance alive. To have it automatically be freed when it is closed, do the following: [window retain] and [window setReleasedWhenClosed:YES].
 */
+ (instancetype)windowWithContentViewController:(NSViewController *)contentViewController NS_AVAILABLE_MAC(10_10);

/* Call to start a drag (moving the window) in the Window Server process. In general, this can be done after a mouseDown event has come in and been examined by an application or view. The view may determine it wants to allow that portion of the window to start a window drag, and can hand off the work to the Window Server process by calling this method. This allows the window to participate in space switching, and other system features. Pass the original mouseDown event to the method. The method will return right away, and a mouseUp may not get sent.
 */
- (void)performWindowDragWithEvent:(NSEvent *)event NS_AVAILABLE_MAC(10_11);

@end

@interface NSWindow(NSKeyboardUI)
@property (nullable, assign) NSView *initialFirstResponder;
- (void)selectNextKeyView:(nullable id)sender;
- (void)selectPreviousKeyView:(nullable id)sender;
- (void)selectKeyViewFollowingView:(NSView *)aView;
- (void)selectKeyViewPrecedingView:(NSView *)aView;
@property (readonly) NSSelectionDirection keyViewSelectionDirection;
@property (nullable, retain) NSButtonCell *defaultButtonCell;
- (void)disableKeyEquivalentForDefaultButtonCell;
- (void)enableKeyEquivalentForDefaultButtonCell;
@property BOOL autorecalculatesKeyViewLoop;
- (void)recalculateKeyViewLoop;
@end

@interface NSWindow (NSToolbarSupport)
@property (nullable, strong) NSToolbar *toolbar;
- (void)toggleToolbarShown:(nullable id)sender;
- (void)runToolbarCustomizationPalette:(nullable id)sender;
@property BOOL showsToolbarButton;
@end

@interface NSWindow(NSDrag)
- (void)dragImage:(NSImage *)anImage at:(NSPoint)baseLocation offset:(NSSize)initialOffset event:(NSEvent *)event pasteboard:(NSPasteboard *)pboard source:(id)sourceObj slideBack:(BOOL)slideFlag;

- (void)registerForDraggedTypes:(NSArray<NSString *> *)newTypes;
- (void)unregisterDraggedTypes;
@end

@interface NSWindow(NSCarbonExtensions)

/* Create an NSWindow for a Carbon window - windowRef must be a Carbon WindowRef - see MacWindows.h. This method can only be called on NSWindow, and not subclasses of NSWindow. On 10.11, it will throw an exception if this is done.
 */
- (nullable NSWindow *)initWithWindowRef:(void * /* WindowRef */)windowRef;

/* return the Carbon WindowRef for this window, creating if necessary: - see MacWindows.h
 */
@property (readonly) void * /* WindowRef */windowRef NS_RETURNS_INNER_POINTER;
@end

@interface NSWindow(NSDeprecated)

+ (void)menuChanged:(NSMenu *)menu NS_DEPRECATED_MAC(10_0, 10_11, "This method does not do anything and should not be called.");

/* gState is unused and should not be called.
 */
- (NSInteger)gState NS_DEPRECATED_MAC(10_0, 10_10);

/* The base/screen conversion methods are deprecated in 10.7 and later. Please use convertRectToScreen: or convertRectFromScreen: instead.  */
- (NSPoint)convertBaseToScreen:(NSPoint)aPoint NS_DEPRECATED_MAC(10_0, 10_7, "Use -convertRectToScreen: instead");
- (NSPoint)convertScreenToBase:(NSPoint)aPoint NS_DEPRECATED_MAC(10_0, 10_7, "Use -convertRectFromScreen: instead");

/* -setCanBeVisibleOnAllSpaces: controls whether a window can be visible on all spaces (YES) or is associated with one space at a time (NO).  The default setting is NO.
 */
-(BOOL)canBeVisibleOnAllSpaces NS_DEPRECATED_MAC(10_5, 10_5);
-(void)setCanBeVisibleOnAllSpaces:(BOOL)flag NS_DEPRECATED_MAC(10_5, 10_5);

/* This method is deprecated and should not be used by applications targeting Mac OS X 10.7 or later.
 The implementation of this method will always return 1.0.  Please use -convertRectToBacking: and -backingScaleFactor instead.
 */
- (CGFloat)userSpaceScaleFactor NS_DEPRECATED_MAC(10_4, 10_7, "Use -convertRectToBacking: and -backingScaleFactor instead");

- (void)useOptimizedDrawing:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_10);

/* canStoreColor has not been needed or used in a while and is deprecated. */
- (BOOL)canStoreColor NS_DEPRECATED_MAC(10_0, 10_10);

@end

@protocol NSWindowDelegate <NSObject>
@optional
- (BOOL)windowShouldClose:(id)sender;
- (nullable id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(nullable id)client;
- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize;
- (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)newFrame;
- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)newFrame;
- (nullable NSUndoManager *)windowWillReturnUndoManager:(NSWindow *)window;

/* Tells the delegate that the window is about to show a sheet, and gives the delegate a chance to customize the location of the sheet.
 */
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
- (nullable NSArray<NSWindow *> *)customWindowsToEnterFullScreenForWindow:(NSWindow *)window NS_AVAILABLE_MAC(10_7);

/* The system has started its animation into fullscreen, including transitioning to a new space.  Start the window fullscreen animation immediately, and perform the animation with the given duration to  be in sync with the system animation.  This method is called only if customWindowToEnterFullScreenForWindow: returned non-nil. 
*/
- (void)window:(NSWindow *)window startCustomAnimationToEnterFullScreenWithDuration:(NSTimeInterval)duration NS_AVAILABLE_MAC(10_7);

/* In some cases, the transition to enter fullscreen will fail, due to being in the midst of handling some other animation or user gesture.  We will attempt to minimize these cases, but believe there is a need for failure handling.  This method indicates that there was an error, and the application should clean up any work it may have done to prepare to enter fullscreen.  This message will be sent whether or not the delegate indicated a custom animation by returning non-nil from  customWindowsToEnterFullScreenForWindow:.
*/
- (void)windowDidFailToEnterFullScreen:(NSWindow *)window NS_AVAILABLE_MAC(10_7);

/* The window is about to exit fullscreen mode.  The following API allows a window delegate to customize the animation when the window is about to exit fullscreen.  In order to manage windows on spaces, we need the window delegate to provide a list of windows involved in the animation.  If an application does not do a custom animation, this method can be unimplemented or can return nil.  window:startCustomAnimationToExitFullScreenWithDuration: will be called only if customWindowsToExitFullScreenForWindow: returns non-nil. 
*/
- (nullable NSArray<NSWindow *> *)customWindowsToExitFullScreenForWindow:(NSWindow *)window NS_AVAILABLE_MAC(10_7);

/* The system has started its animation out of fullscreen, including transitioning back to the desktop space.  Start the window animation immediately, and perform the animation with the given duration to  be in sync with the system animation.  This method is called only if customWindowsToExitFullScreenForWindow: returned non-nil. 
*/
- (void)window:(NSWindow *)window startCustomAnimationToExitFullScreenWithDuration:(NSTimeInterval)duration NS_AVAILABLE_MAC(10_7);

/* customWindowsToEnterFullScreenForWindow:onScreen: will be called in place of customWindowsToEnterFullScreenForWindow: if both are implemented */
- (nullable NSArray<NSWindow *> *)customWindowsToEnterFullScreenForWindow:(NSWindow *)window onScreen:(NSScreen *)screen NS_AVAILABLE_MAC(10_9);

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

/* NSUnscaledWindowMask is deprecated and has no effect. The scale factor for a window backing store is dynamic and dependent on the screen it is placed on.
 */
enum {
    NSUnscaledWindowMask		= 1 << 11
} NS_ENUM_DEPRECATED_MAC(10_0, 10_9);

NS_ASSUME_NONNULL_END

