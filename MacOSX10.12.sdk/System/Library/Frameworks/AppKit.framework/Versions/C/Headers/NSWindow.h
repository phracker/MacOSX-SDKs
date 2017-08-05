/*
    NSWindow.h
    Application Kit
    Copyright (c) 1994-2016, Apple Inc.
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

#define NSWINDOW_TRACK_EVENTS_DECLARES_NULLABILITY APPKIT_SWIFT_SDK_EPOCH_AT_LEAST(3)

NS_ASSUME_NONNULL_BEGIN

@class NSButton, NSButtonCell, NSColor, NSImage, NSPasteboard, NSScreen, NSNotification, NSText, NSView, NSMutableSet, NSSet, NSDate, NSToolbar, NSGraphicsContext, NSURL, NSColorSpace, NSDockTile, NSViewController, NSTitlebarAccessoryViewController, NSWindowAuxiliary, NSEvent, NSWindowController;

@protocol NSWindowDelegate;

#define NSAppKitVersionNumberWithCustomSheetPosition 686.0
#define NSAppKitVersionNumberWithDeferredWindowDisplaySupport		1019.0

typedef NS_OPTIONS(NSUInteger, NSWindowStyleMask) {
    NSWindowStyleMaskBorderless = 0,
    NSWindowStyleMaskTitled = 1 << 0,
    NSWindowStyleMaskClosable = 1 << 1,
    NSWindowStyleMaskMiniaturizable = 1 << 2,
    NSWindowStyleMaskResizable	= 1 << 3,
    
    /* Specifies a window with textured background. Textured windows generally don't draw a top border line under the titlebar/toolbar. To get that line, use the NSUnifiedTitleAndToolbarWindowMask mask.
     */
    NSWindowStyleMaskTexturedBackground = 1 << 8,
    
    /* Specifies a window whose titlebar and toolbar have a unified look - that is, a continuous background. Under the titlebar and toolbar a horizontal separator line will appear.
     */
    NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
    
    /* When set, the window will appear full screen. This mask is automatically toggled when toggleFullScreen: is called.
     */
    NSWindowStyleMaskFullScreen NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 14,
    
    /* If set, the contentView will consume the full size of the window; it can be combined with other window style masks, but is only respected for windows with a titlebar.
     Utilizing this mask opts-in to layer-backing. Utilize the contentLayoutRect or auto-layout contentLayoutGuide to layout views underneath the titlebar/toolbar area.
     */
    NSWindowStyleMaskFullSizeContentView NS_ENUM_AVAILABLE_MAC(10_10) = 1 << 15,
    
    /* The following are only applicable for NSPanel (or a subclass thereof)
     */
    NSWindowStyleMaskUtilityWindow			= 1 << 4,
    NSWindowStyleMaskDocModalWindow 		= 1 << 6,
    NSWindowStyleMaskNonactivatingPanel		= 1 << 7, // Specifies that a panel that does not activate the owning application
    NSWindowStyleMaskHUDWindow NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 13 // Specifies a heads up display panel
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
    
    /* You may specify at most one of NSWindowCollectionBehaviorFullScreenPrimary, NSWindowCollectionBehaviorFullScreenAuxiliary, or NSWindowCollectionBehaviorFullScreenNone. */
    NSWindowCollectionBehaviorFullScreenPrimary NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 7,       // the frontmost window with this collection behavior will be the fullscreen window.
    NSWindowCollectionBehaviorFullScreenAuxiliary NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 8,     // windows with this collection behavior can be shown with the fullscreen window.
    NSWindowCollectionBehaviorFullScreenNone NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 9, // The window can not be made fullscreen when this bit is set
    
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
    NSWindowFullScreenButton NS_ENUM_DEPRECATED_MAC(10_7, 10_12, "The standard window button for NSWindowFullScreenButton is always nil; use NSWindowZoomButton instead"),
};

typedef NS_ENUM(NSInteger, NSWindowTitleVisibility) {
    /* The default mode has a normal window title and titlebar buttons. */
    NSWindowTitleVisible = 0,
    /* The always hidden mode hides the title and moves the toolbar up into the area previously occupied by the title. */
    NSWindowTitleHidden = 1,
} NS_ENUM_AVAILABLE_MAC(10_10);

#define NSEventDurationForever  DBL_MAX

typedef NS_ENUM(NSInteger, NSWindowUserTabbingPreference) {
    NSWindowUserTabbingPreferenceManual,
    NSWindowUserTabbingPreferenceAlways,
    NSWindowUserTabbingPreferenceInFullScreen,
} NS_ENUM_AVAILABLE_MAC(10_12);

typedef NS_ENUM(NSInteger, NSWindowTabbingMode) {
    NSWindowTabbingModeAutomatic, // The system automatically prefers to tab this window when appropriate
    NSWindowTabbingModePreferred, // The window explicitly should prefer to tab when shown
    NSWindowTabbingModeDisallowed // The window explicitly should not prefer to tab when shown
}  NS_ENUM_AVAILABLE_MAC(10_12);


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
    unsigned char	_ignoreResignEvent:1;
    unsigned char	_reservedWindow:7;
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
        unsigned int  staticDepthLimit:1;
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
        unsigned int  wasModalAtSometime:1;
        unsigned int  windowWillBecomeFS:1;
    } _wFlags;
    id _defaultButtonCell;
    NSView *_initialFirstResponder;
    NSWindowAuxiliary *_auxiliaryStorage;
}

+ (NSRect)frameRectForContentRect:(NSRect)cRect styleMask:(NSWindowStyleMask)style;
+ (NSRect)contentRectForFrameRect:(NSRect)fRect styleMask:(NSWindowStyleMask)style;
+ (CGFloat)minFrameWidthWithTitle:(NSString *)title styleMask:(NSWindowStyleMask)style;
+ (NSWindowDepth)defaultDepthLimit;

- (NSRect)frameRectForContentRect:(NSRect)contentRect;
- (NSRect)contentRectForFrameRect:(NSRect)frameRect;

- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag screen:(nullable NSScreen *)screen;
- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE; // Use initWithContentRect:. This method will throw an exception for coders that support allowsKeyedCoding, and is only available for compatability with non keyed coding.

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

/* NOTE: The styleMask can only be set on OS 10.6 and later. Valid styleMask settings have the same restrictions as the styleMask passed to -initWithContentRect:styleMask:backing:defer:.  Some styleMask changes will cause the view hierarchy to be rebuilt, since there is a different subclass for the top level view of a borderless window than for the top level view of a titled window. */
@property NSWindowStyleMask styleMask;

- (nullable NSText *)fieldEditor:(BOOL)createFlag forObject:(nullable id)object;
- (void)endEditingFor:(nullable id)object;

- (NSRect)constrainFrameRect:(NSRect)frameRect toScreen:(nullable NSScreen *)screen;
- (void)setFrame:(NSRect)frameRect display:(BOOL)flag;
- (void)setContentSize:(NSSize)size;
- (void)setFrameOrigin:(NSPoint)point;
- (void)setFrameTopLeftPoint:(NSPoint)point;
- (NSPoint)cascadeTopLeftFromPoint:(NSPoint)topLeftPoint;
@property (readonly) NSRect frame;

/*! Subclasses can override \c animationResizeTime: to control the total time for the frame change.
 \c newFrame is the rect passed into \c setFrame:display:animate:
 */
- (NSTimeInterval)animationResizeTime:(NSRect)newFrame;

/*! \c setFrame:display:animate: is equivalent to \c setFrame:display: if the \c animateFlag is NO.
    If the \c animationFlag is YES, this method will perform a smooth resize of the window, where the total time for the resize is specified by \c -animationResizeTime:
*/
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

- (BOOL)makeFirstResponder:(nullable NSResponder *)responder;
/* firstResponder is Key Value Observing (KVO) compliant. */
@property (readonly, assign) NSResponder *firstResponder;

@property (readonly) NSInteger resizeFlags;
- (void)keyDown:(NSEvent *)event;
- (void)close;
@property (getter=isReleasedWhenClosed) BOOL releasedWhenClosed;
- (void)miniaturize:(nullable id)sender;
- (void)deminiaturize:(nullable id)sender;
@property (getter=isZoomed, readonly) BOOL zoomed;
- (void)zoom:(nullable id)sender;
@property (getter=isMiniaturized, readonly) BOOL miniaturized;
- (BOOL)tryToPerform:(SEL)action with:(nullable id)object;
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
- (NSRect)convertRectToScreen:(NSRect)rect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromScreen:(NSRect)rect NS_AVAILABLE_MAC(10_7);

/* New methods to convert to/from a pixel integral backing store space */
- (NSRect)convertRectToBacking:(NSRect)rect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromBacking:(NSRect)rect NS_AVAILABLE_MAC(10_7);

/* Use NSIntegralRectWithOptions() to produce a backing store pixel aligned rectangle from the given input rectangle in window coordinates. */
- (NSRect)backingAlignedRect:(NSRect)rect options:(NSAlignmentOptions)options NS_AVAILABLE_MAC(10_7);

/* Returns the scale factor representing the number of backing store pixels corresponding to each linear unit in window space on this NSWindow. This method is provided for rare cases when the explicit scale factor is needed. Please use -convert*ToBacking: methods whenever possible. */
@property (readonly) CGFloat backingScaleFactor NS_AVAILABLE_MAC(10_7); 

- (void)performClose:(nullable id)sender;
- (void)performMiniaturize:(nullable id)sender;
- (void)performZoom:(nullable id)sender;
@property (getter=isOneShot) BOOL oneShot;
- (NSData *)dataWithEPSInsideRect:(NSRect)rect;
- (NSData *)dataWithPDFInsideRect:(NSRect)rect;
- (void)print:(nullable id)sender;

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


- (void)cacheImageInRect:(NSRect)rect;
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

@property (readonly, copy) NSDictionary<NSString *, id> *deviceDescription;

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


+ (nullable NSButton *)standardWindowButton:(NSWindowButton)b forStyleMask:(NSWindowStyleMask)styleMask;
- (nullable NSButton *)standardWindowButton:(NSWindowButton)b;

- (void)addChildWindow:(NSWindow *)childWin ordered:(NSWindowOrderingMode)place;
- (void)removeChildWindow:(NSWindow *)childWin;
@property (nullable, readonly, copy) NSArray<__kindof NSWindow *> *childWindows;

@property (nullable, assign) NSWindow *parentWindow;

/* Returns NSGraphicsContext used to render the receiver's content on the screen for the calling thread.
*/
@property (nullable, readonly, strong) NSGraphicsContext *graphicsContext;

@property (nullable, strong) NSColorSpace *colorSpace NS_AVAILABLE_MAC(10_6);

/* canRepresentDisplayGamut: returns YES if the colorSpace of the receiving window, and the colorSpace of the screen containing that window, are capable of representing the given display gamut
*/
- (BOOL)canRepresentDisplayGamut:(NSDisplayGamut)displayGamut  NS_AVAILABLE_MAC(10_12);

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


#pragma mark - NSViewController Support

/* The main content view controller for the window. This provides the contentView of the window. Assigning this value will remove the existing contentView and will make the contentViewController.view the main contentView for the window. The default value is nil. The contentViewController only controls the contentView, and not the title of the window. The window title can easily be bound to the contentViewController with the following: [window bind:NSTitleBinding toObject:contentViewController withKeyPath:@"title" options:nil]. Setting the contentViewController will cause the window to resize based on the current size of the contentViewController. Autolayout should be used to restrict the size of the window. The value of the contentViewController is encoded in the NIB. Directly assigning a contentView will clear out the rootViewController.
 */
@property (nullable, strong) NSViewController *contentViewController NS_AVAILABLE_MAC(10_10);

/* Convenience method for creating an autoreleased titled window with the given contentViewController. A basic NSWindow with the following attributes is made: titled, closable, resizable, miniaturizable. The window's title is automatically bound to the contentViewController's title. The size of the window can easily be controlled by utilizing autolayout and applying size constraints to the view (or its subviews). The window has isReleasedWhenClosed set to NO, and it must be explicitly retained to keep the window instance alive. To have it automatically be freed when it is closed, do the following: [window retain] and [window setReleasedWhenClosed:YES].
 */
+ (instancetype)windowWithContentViewController:(NSViewController *)contentViewController NS_AVAILABLE_MAC(10_10);

#pragma mark - Window Dragging

/* Call to start a drag (moving the window) in the Window Server process. In general, this can be done after a mouseDown event has come in and been examined by an application or view. The view may determine it wants to allow that portion of the window to start a window drag, and can hand off the work to the Window Server process by calling this method. This allows the window to participate in space switching, and other system features. Pass the original mouseDown event to the method. The method will return right away, and a mouseUp may not get sent.
 */
- (void)performWindowDragWithEvent:(NSEvent *)event NS_AVAILABLE_MAC(10_11);

#pragma mark - Keyboard UI support (Key View Loop)

@property (nullable, assign) NSView *initialFirstResponder;
- (void)selectNextKeyView:(nullable id)sender;
- (void)selectPreviousKeyView:(nullable id)sender;
- (void)selectKeyViewFollowingView:(NSView *)view;
- (void)selectKeyViewPrecedingView:(NSView *)view;
@property (readonly) NSSelectionDirection keyViewSelectionDirection;
@property (nullable, retain) NSButtonCell *defaultButtonCell;
- (void)disableKeyEquivalentForDefaultButtonCell;
- (void)enableKeyEquivalentForDefaultButtonCell;
@property BOOL autorecalculatesKeyViewLoop;
- (void)recalculateKeyViewLoop;

#pragma mark - Toolbar Support

@property (nullable, strong) NSToolbar *toolbar;
- (void)toggleToolbarShown:(nullable id)sender;
- (void)runToolbarCustomizationPalette:(nullable id)sender;
@property BOOL showsToolbarButton; // Does nothing in recent versions of the OS

#pragma mark - Automatic Window Tabbing

/* Allows automatic window tabbing when the value is YES. By default, this will be set to YES, but applications can explicitly opt out of all automatic tabbing by setting it to NO, and can still adoped explicit window tabbing, if desired. 
 */
@property (class) BOOL allowsAutomaticWindowTabbing NS_AVAILABLE_MAC(10_12);

/* Returns the user's tabbing preference as set in System Preferences. This value should be queried anytime a new window is made to see if the user wants to automatically show it in tabs.
 */
@property (class, readonly) NSWindowUserTabbingPreference userTabbingPreference NS_AVAILABLE_MAC(10_12);

/* Get and set the tabbing mode for this window. This should be set before a window is shown. The default value is NSWindowTabbingModeAutomatic. When the value is NSWindowTabbingModeAutomatic, the system will look at the userTabbingPreference and automatically tab windows together based on the tabbingIdentifier, when it is appropriate to do so.
 */
@property NSWindowTabbingMode tabbingMode NS_AVAILABLE_MAC(10_12);

/* Windows with the same tabbingIdentifier will have the ability to be tabbed together when a window is being shown. This allows aggregation of similiar windows. By default, the tabbingIdentifier will be generated based on inherit window properties, such as the window class name, the delegate class name, the window controller class name, and some additional state. Windows can be explicilty made to group together by using the same tabbingIdentifier. 
 */
@property (copy) NSString *tabbingIdentifier NS_AVAILABLE_MAC(10_12);

/* Actions that can be called to perform various tabbed window behaviors. UI that is hooked up to these items can be automatically validated by calling NSWindow's validateUserInterfaceItem.
 */
- (IBAction)selectNextTab:(nullable id)sender NS_AVAILABLE_MAC(10_12);
- (IBAction)selectPreviousTab:(nullable id)sender NS_AVAILABLE_MAC(10_12);
- (IBAction)moveTabToNewWindow:(nullable id)sender NS_AVAILABLE_MAC(10_12);
- (IBAction)mergeAllWindows:(nullable id)sender NS_AVAILABLE_MAC(10_12);
- (IBAction)toggleTabBar:(nullable id)sender NS_AVAILABLE_MAC(10_12);

/* Returns the entire group (stack) of windows that are all visually shown together in one virtual tabbed window and associated with this particular window. Operations can then be done on each window, as necessary. For instance, iterating over each window in the group and calling performClose: will close the entire stack. The result will be nil when the window is not tabbed at all (not showing a tab bar), and non-nil with at least one object when the tab bar is shown. The order of items in the array is the same order as the tabs visually shown (leading to trailing).
 */
@property (readonly, copy, nullable) NSArray<NSWindow *> *tabbedWindows NS_AVAILABLE_MAC(10_12);

/* Allows creating a group of tabbed windows, or adding a new window to an existing tabbed window group. The 'window' will be added to the receiver's tabbed window group, or create a group if needed. The tabbingIdentifier for the entire group should be the same for all the windows, otherwise an exception will be thrown. Use the ordered parameter with "NSWindowAbove" and "NSWindowBelow" to place the new window before or after the receiver's tab. Passing "NSWindowOut" will thrown an exception. Currently this method is not animatable, but that may change in the future.
 */
- (void)addTabbedWindow:(NSWindow *)window ordered:(NSWindowOrderingMode)ordered NS_AVAILABLE_MAC(10_12);

#pragma mark - Other

/* Retrieve the layout direction of the window titlebar: this includes the standard window buttons (close/minimize/maximize buttons) and the title for this window. In general, this will return "right to left" (RTL) if the primary system language is RTL. The layout direction may be RTL even in applications that do not have a RTL language localization. This value should be utilized if an application uses titlebarAppearsTransparent and places controls underneath the titlebar.
 */
@property (readonly) NSUserInterfaceLayoutDirection windowTitlebarLayoutDirection NS_AVAILABLE_MAC(10_12);

#pragma mark -

@end

@interface NSWindow(NSEvent)
/* Tracks events matching the supplied mask with the supplied tracking handler until the tracking handler explicitly terminates tracking. Each event is removed from the event queue then passed to the tracking handler. If a matching event does not exist in the event queue, then the main thread blocks in the specified runloop mode until an event of the requested type is received or the timeout expires. If the timeout expires, the tracking handler is called with a nil event. A negative timeout is interpreted as 0. Use NSEventDurationForever to never timeout. Tracking continues until *stop is set to YES. Calls to -nextEventMatchingMask:… are allowed inside the trackingHandler block. This method returns once tracking is terminated.
 */
#if NSWINDOW_TRACK_EVENTS_DECLARES_NULLABILITY
- (void)trackEventsMatchingMask:(NSEventMask)mask timeout:(NSTimeInterval)timeout mode:(NSString *)mode handler:(void(NS_NOESCAPE ^)(NSEvent *__nullable event, BOOL *stop))trackingHandler NS_AVAILABLE_MAC(10_10);
#endif
#if __LP64__
- (nullable NSEvent *)nextEventMatchingMask:(NSEventMask)mask;
- (nullable NSEvent *)nextEventMatchingMask:(NSEventMask)mask untilDate:(nullable NSDate *)expiration inMode:(NSRunLoopMode)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSEventMask)mask beforeEvent:(nullable NSEvent *)lastEvent;
#else
- (nullable NSEvent *)nextEventMatchingMask:(NSUInteger)mask;
- (nullable NSEvent *)nextEventMatchingMask:(NSUInteger)mask untilDate:(nullable NSDate *)expiration inMode:(NSRunLoopMode)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSUInteger)mask beforeEvent:(nullable NSEvent *)lastEvent;
#endif

- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
- (void)sendEvent:(NSEvent *)event;
@property (nullable, readonly, strong) NSEvent *currentEvent;
@property BOOL acceptsMouseMovedEvents;
@property BOOL ignoresMouseEvents;
@property (readonly) NSPoint mouseLocationOutsideOfEventStream;
@end

@interface NSWindow(NSCursorRect)
- (void)disableCursorRects;
- (void)enableCursorRects;
- (void)discardCursorRects;
@property (readonly) BOOL areCursorRectsEnabled;
- (void)invalidateCursorRectsForView:(NSView *)view;
- (void)resetCursorRects;
@end

@interface NSWindow(NSDrag)
- (void)dragImage:(NSImage *)image at:(NSPoint)baseLocation offset:(NSSize)initialOffset event:(NSEvent *)event pasteboard:(NSPasteboard *)pboard source:(id)sourceObj slideBack:(BOOL)slideFlag;

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
APPKIT_EXTERN NSNotificationName NSWindowDidBecomeKeyNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidBecomeMainNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidChangeScreenNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidDeminiaturizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidExposeNotification;			// userInfo key:  @"NSExposedRect"
APPKIT_EXTERN NSNotificationName NSWindowDidMiniaturizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidMoveNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidResignKeyNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidResignMainNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidResizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidUpdateNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillCloseNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillMiniaturizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillMoveNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillBeginSheetNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidEndSheetNotification;

/* NSWindowDidChangeBackingPropertiesNotification is posted on 10.7.3 and later, when a window's backingScaleFactor and/or its colorSpace changes.  When running on a system version where this new notification is available, applications should use it instead of NSWindowDidChangeScreenProfileNotification to watch for changes to either of these backing store properties.  Many applications won't have any need to watch for this notification, but those that perform sophisticated color handling or manually manage their own caches of window-resolution-and/or/colorspace-appropriate bitmapped images will find this notification useful, as a prompt to invalidate their caches or schedule other reassessment for the new resolution and/or color space as needed.  The notification's userInfo dictionary specifies the window's previous backingScaleFactor and colorSpace.  You can compare these with the window's new backingScaleFactor and colorSpace at the time of the notification, to determine which of these two properties (potentially both) changed.
*/
APPKIT_EXTERN NSNotificationName const NSWindowDidChangeBackingPropertiesNotification NS_AVAILABLE_MAC(10_7); // added in 10.7.3; userInfo keys: NSBackingPropertyOldScaleFactorKey, NSBackingPropertyOldColorSpaceKey

APPKIT_EXTERN NSString * const NSBackingPropertyOldScaleFactorKey NS_AVAILABLE_MAC(10_7); // added in 10.7.3; an NSNumber
APPKIT_EXTERN NSString * const NSBackingPropertyOldColorSpaceKey NS_AVAILABLE_MAC(10_7);  // added in 10.7.3; an NSColorSpace


/* NSWindowDidChangeScreenProfileNotification is posted when a window's display's color profile changes, or when the window moves to a display that has a different color profile.  When running on 10.7.3 or later, this notification is still posted for compatibility, but modern applications should instead watch for NSWindowDidChangeBackingPropertiesNotification, which is posted for both color space and resolution changes, and facilitates handling both in a single update and redisplay pass.
*/
APPKIT_EXTERN NSNotificationName NSWindowDidChangeScreenProfileNotification;

/* NSWindowWillStartLiveResizeNotification is sent when the user starts a live resize operation via a mouseDown in the resize corner.  The notification will be sent before the window size is changed.  Note that this notification is sent once for a sequence of window resize operations */
APPKIT_EXTERN NSNotificationName const NSWindowWillStartLiveResizeNotification  NS_AVAILABLE_MAC(10_6);
/* NSWindowDidEndLiveResizeNotification is sent after the user ends a live resize operation via a mouseUp in the resize corner.  The notification will be sent after the final window size change.    Note that this notification is sent once for a sequence of window resize operations */
APPKIT_EXTERN NSNotificationName const NSWindowDidEndLiveResizeNotification  NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSNotificationName const NSWindowWillEnterFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowDidEnterFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowWillExitFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowDidExitFullScreenNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowWillEnterVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowDidEnterVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowWillExitVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSNotificationName const NSWindowDidExitVersionBrowserNotification NS_AVAILABLE_MAC(10_7);
/* Upon receiving this notification, you can query the NSWindow for its current occlusion state. Note that this only notifies about changes in the state of the occlusion, not when the occlusion region changes. You can use this notification to increase responsiveness and save power, by halting any expensive calculations that the user can not see. */
APPKIT_EXTERN NSNotificationName const NSWindowDidChangeOcclusionStateNotification NS_AVAILABLE_MAC(10_9);

/* NSUnscaledWindowMask is deprecated and has no effect. The scale factor for a window backing store is dynamic and dependent on the screen it is placed on.
 */
enum {
    NSUnscaledWindowMask		= 1 << 11
} NS_ENUM_DEPRECATED_MAC(10_0, 10_9);

@interface NSWindow(NSDeprecated)

+ (void)menuChanged:(NSMenu *)menu NS_DEPRECATED_MAC(10_0, 10_11, "This method does not do anything and should not be called.");

/* gState is unused and should not be called.
 */
- (NSInteger)gState NS_DEPRECATED_MAC(10_0, 10_10, "This method is unused and should not be called.");

/* The base/screen conversion methods are deprecated in 10.7 and later. Please use convertRectToScreen: or convertRectFromScreen: instead.  */
- (NSPoint)convertBaseToScreen:(NSPoint)point NS_DEPRECATED_MAC(10_0, 10_7, "Use -convertRectToScreen: instead");
- (NSPoint)convertScreenToBase:(NSPoint)point NS_DEPRECATED_MAC(10_0, 10_7, "Use -convertRectFromScreen: instead");

/* -setCanBeVisibleOnAllSpaces: controls whether a window can be visible on all spaces (YES) or is associated with one space at a time (NO).  The default setting is NO.
 */
-(BOOL)canBeVisibleOnAllSpaces NS_DEPRECATED_MAC(10_5, 10_5);
-(void)setCanBeVisibleOnAllSpaces:(BOOL)flag NS_DEPRECATED_MAC(10_5, 10_5);

/* This method is deprecated and should not be used by applications targeting Mac OS X 10.7 or later.
 The implementation of this method will always return 1.0.  Please use -convertRectToBacking: and -backingScaleFactor instead.
 */
- (CGFloat)userSpaceScaleFactor NS_DEPRECATED_MAC(10_4, 10_7, "Use -convertRectToBacking: and -backingScaleFactor instead");

- (void)useOptimizedDrawing:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_10, "This method does not do nothing");

/* canStoreColor has not been needed or used in a while and is deprecated. */
- (BOOL)canStoreColor NS_DEPRECATED_MAC(10_0, 10_10, "This method does not do anything");

@end

/* Deprecated legacy style mask constants. Prefer to use NSWindowStyleMask values instead.
 */
static const NSWindowStyleMask NSBorderlessWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskBorderless", macosx(10.0, 10.12)) = NSWindowStyleMaskBorderless;
static const NSWindowStyleMask NSTitledWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTitled", macosx(10.0, 10.12)) = NSWindowStyleMaskTitled;
static const NSWindowStyleMask NSClosableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskClosable", macosx(10.0, 10.12)) = NSWindowStyleMaskClosable;
static const NSWindowStyleMask NSMiniaturizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskMiniaturizable", macosx(10.0, 10.12)) = NSWindowStyleMaskMiniaturizable;
static const NSWindowStyleMask NSResizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskResizable", macosx(10.0, 10.12)) = NSWindowStyleMaskResizable;
static const NSWindowStyleMask NSTexturedBackgroundWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTexturedBackground", macosx(10.0, 10.12)) = NSWindowStyleMaskTexturedBackground;
static const NSWindowStyleMask NSUnifiedTitleAndToolbarWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUnifiedTitleAndToolbar", macosx(10.0, 10.12)) = NSWindowStyleMaskUnifiedTitleAndToolbar;
static const NSWindowStyleMask NSFullScreenWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullScreen", macosx(10.0, 10.12)) = NSWindowStyleMaskFullScreen;
static const NSWindowStyleMask NSFullSizeContentViewWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullSizeContentView", macosx(10.0, 10.12)) = NSWindowStyleMaskFullSizeContentView;
static const NSWindowStyleMask NSUtilityWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUtilityWindow", macosx(10.0, 10.12)) = NSWindowStyleMaskUtilityWindow;
static const NSWindowStyleMask NSDocModalWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskDocModalWindow", macosx(10.0, 10.12)) = NSWindowStyleMaskDocModalWindow;
static const NSWindowStyleMask NSNonactivatingPanelMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskNonactivatingPanel", macosx(10.0, 10.12)) = NSWindowStyleMaskNonactivatingPanel;
static const NSWindowStyleMask NSHUDWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskHUDWindow", macosx(10.0, 10.12)) = NSWindowStyleMaskHUDWindow;


NS_ASSUME_NONNULL_END

