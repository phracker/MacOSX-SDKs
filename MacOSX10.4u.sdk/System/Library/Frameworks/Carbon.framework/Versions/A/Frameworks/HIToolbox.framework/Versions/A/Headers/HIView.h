/*
     File:       HIToolbox/HIView.h
 
     Contains:   HIView routines
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 2001-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __HIVIEW__
#define __HIVIEW__

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
#endif

#ifndef __CARBONEVENTS__
#include <HIToolbox/CarbonEvents.h>
#endif

#ifndef __HISHAPE__
#include <HIToolbox/HIShape.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef ControlRef                      HIViewRef;
typedef ControlID                       HIViewID;
/*
 *  kHIViewWindowContentID
 *  
 *  Discussion:
 *    The standard view ID for the content view of a window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern const HIViewID kHIViewWindowContentID                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/*
 *  kHIViewWindowGrowBoxID
 *  
 *  Discussion:
 *    The standard view ID for the grow box view of a window. Not all
 *    windows have grow boxes, so be aware that you might not find this
 *    view if you look for it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern const HIViewID kHIViewWindowGrowBoxID                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  Discussion:
 *    HIViewZOrderOp
 */
enum {

  /*
   * Indicates we wish to order a view above another view.
   */
  kHIViewZOrderAbove            = 1,

  /*
   * Indicates we wish to order a view below another view.
   */
  kHIViewZOrderBelow            = 2
};

typedef UInt32                          HIViewZOrderOp;

/*
 *  HIViewFrameMetrics
 *  
 *  Summary:
 *    Describes the offsets from the structure to the content area of a
 *    view; for example, the top metric is the difference between the
 *    vertical coordinate of the top edge of the view’s structure
 *    region and the vertical coordinate of the top edge of the view’s
 *    content region. This structure is returned by a view in response
 *    to a kEventControlGetFrameMetrics event.
 */
struct HIViewFrameMetrics {

  /*
   * Height of the top of the structure area.
   */
  float               top;

  /*
   * Width of the left of the structure area.
   */
  float               left;

  /*
   * Height of the bottom of the structure area.
   */
  float               bottom;

  /*
   * Width of the right of the structure area.
   */
  float               right;
};
typedef struct HIViewFrameMetrics       HIViewFrameMetrics;
/*==============================================================================*/
/*  ATTRIBUTES                                                                  */
/*==============================================================================*/

/*
 *  Summary:
 *    View attributes are generally determined by clients of the view;
 *    the view itself should observe the attributes and behave
 *    accordingly.
 *  
 *  Discussion:
 *    View Attributes
 */
enum {

  /*
   * When set, the control will send the command it generates to the
   * user focus and propagate as it would naturally from there. The
   * default is to send the command to itself and then to its parent
   * and so forth.
   */
  kHIViewAttributeSendCommandToUserFocus = 1 << 0,

  /*
   * Indicates that a text editing control should behave appropriately
   * for editing fields in a dialog; specifically, the control should
   * ignore the Return, Enter, Escape, and Tab keys, and allow them to
   * be processed by other participants in the event flow. Available on
   * Mac OS X 10.3 and later.
   */
  kHIViewAttributeIsFieldEditor = 1 << 1,

  /*
   * Legacy synonym for kHIViewAttributeSendCommandToUserFocus. Please
   * use it instead.
   */
  kHIViewSendCommandToUserFocus = kHIViewAttributeSendCommandToUserFocus
};


/*
 *  HIView features
 *  
 *  Summary:
 *    View feature flags are generally determined by the view itself,
 *    and are not typically changed by clients of the view.
 */
enum {

  /*
   * This view supports using the ghosting protocol when live tracking
   * is not enabled.
   */
  kHIViewFeatureSupportsGhosting = 1 << 0,

  /*
   * This view allows subviews to be embedded within it.
   */
  kHIViewFeatureAllowsSubviews  = 1 << 1,

  /*
   * If this view is clicked, the keyboard focus should be set to this
   * view automatically. This is primarily used for edit text controls.
   */
  kHIViewFeatureGetsFocusOnClick = 1 << 8,

  /*
   * This view supports the live feedback protocol. Necessary to
   * implement live scroll bar tracking. Clients of a view should never
   * disable this.
   */
  kHIViewFeatureSupportsLiveFeedback = 1 << 10,

  /*
   * This view can be put into a radio group. Radio buttons and bevel
   * buttons report this behavior.
   */
  kHIViewFeatureSupportsRadioBehavior = 1 << 11,

  /*
   * This view supports the auto-toggle protocol and should at the very
   * least auto- toggle from off to on and back. The view can support a
   * carbon event for more advanced auto-toggling of its value. The tab
   * view supports this, for example, so that when a tab is clicked its
   * value changes automatically.
   */
  kHIViewFeatureAutoToggles     = 1 << 14,

  /*
   * This is merely informational. Turning it off would not necessarily
   * disable any timer a view might be using, but it could obey this
   * bit if it so desired.
   */
  kHIViewFeatureIdlesWithTimer  = 1 << 23,

  /*
   * This tells the control manager that the up button part increases
   * the value of the control instead of decreasing it. For example,
   * the Little Arrows (Spinner) control increase its value when the up
   * button is pressed. Scroll bars, on the other hand, decrease the
   * value when their up buttons are pressed.
   */
  kHIViewFeatureInvertsUpDownValueMeaning = 1 << 24,

  /*
   * This is an optimization for determining a view's opaque region.
   * When set, the view system just uses the view's structure region,
   * and can usually avoid having to call the view at all.
   */
  kHIViewFeatureIsOpaque        = 1 << 25,

  /*
   * This is an optimization for determining what gets invalidated when
   * views are dirtied. For example, on a metal window, the content
   * view is actually fully transparent, so invalidating it doesn't
   * really help things. By telling the control manager that the view
   * is transparent and does not do any drawing, we can avoid trying to
   * invalidate it and instead invalidate views behind it.
   */
  kHIViewFeatureDoesNotDraw     = 1 << 27,

  /*
   * Indicates to the Control Manager that this view doesn't use the
   * special part codes for indicator, inactive, and disabled.
   * Available in Mac OS X 10.3 and later.
   */
  kHIViewFeatureDoesNotUseSpecialParts = 1 << 28,

  /*
   * This is an optimization for determining the clickable region of a
   * window (used for metal windows, for example, when doing async
   * window dragging). The presence of this bit tells us not to bother
   * asking the control for the clickable region. A view like the
   * visual separator would set this bit. It's typically used in
   * conjunction with the kHIViewFeatureDoesNotDraw bit.
   */
  kHIViewFeatureIgnoresClicks   = 1 << 29
};


/*
 *  HIView valid feature sets
 *  
 *  Summary:
 *    These are sets of features that are available on the version of
 *    Mac OS X corresponding to that named in the constant.
 */
enum {
  kHIViewValidFeaturesForPanther = 0x3B804D03
};


/*
 *  HIView feature synonyms
 *  
 *  Summary:
 *    Legacy synonyms for HIView feature bit names. Please use the
 *    newer names.
 */
enum {
  kHIViewSupportsGhosting       = kHIViewFeatureSupportsGhosting,
  kHIViewAllowsSubviews         = kHIViewFeatureAllowsSubviews,
  kHIViewGetsFocusOnClick       = kHIViewFeatureGetsFocusOnClick,
  kHIViewSupportsLiveFeedback   = kHIViewFeatureSupportsLiveFeedback,
  kHIViewSupportsRadioBehavior  = kHIViewFeatureSupportsRadioBehavior,
  kHIViewAutoToggles            = kHIViewFeatureAutoToggles,
  kHIViewIdlesWithTimer         = kHIViewFeatureIdlesWithTimer,
  kHIViewInvertsUpDownValueMeaning = kHIViewFeatureInvertsUpDownValueMeaning,
  kHIViewIsOpaque               = kHIViewFeatureIsOpaque,
  kHIViewDoesNotDraw            = kHIViewFeatureDoesNotDraw,
  kHIViewDoesNotUseSpecialParts = kHIViewFeatureDoesNotUseSpecialParts,
  kHIViewIgnoresClicks          = kHIViewFeatureIgnoresClicks
};


typedef UInt64                          HIViewFeatures;
/*==============================================================================*/
/*  VIEW PART CODES                                                             */
/*==============================================================================*/
typedef ControlPartCode                 HIViewPartCode;

/*
 *  HIViewPartCodes
 *  
 */
enum {
  kHIViewNoPart                 = 0,
  kHIViewIndicatorPart          = 129,
  kHIViewDisabledPart           = 254,
  kHIViewInactivePart           = 255,

  /*
   * Use this constant when not referring to a specific part, but
   * rather the entire view.
   */
  kHIViewEntireView             = kHIViewNoPart
};


/*
 *  HIView Meta-Parts
 *  
 *  Summary:
 *    A meta-part is a part used in a call to the HIViewCopyShape API.
 *    These parts are parts that might be defined by a view. They
 *    define a region of a view. Along with these parts, you can also
 *    pass in normal part codes to get the regions of those parts. Not
 *    all views fully support this feature.
 */
enum {

  /*
   * The structure region is the total area over which the view draws.
   */
  kHIViewStructureMetaPart      = -1,

  /*
   * The content region is only defined by views that can embed other
   * views. It is the area that embedded content can live.
   */
  kHIViewContentMetaPart        = -2,

  /*
   * Mac OS X 10.2 or later
   */
  kHIViewOpaqueMetaPart         = -3,

  /*
   * Mac OS X 10.3 or later, only used for async window dragging.
   * Default is structure region.
   */
  kHIViewClickableMetaPart      = -4
};


/*
 *  HIView Focus Parts
 *  
 */
enum {

  /*
   * Tells view to clear its focus
   */
  kHIViewFocusNoPart            = kHIViewNoPart,

  /*
   * Tells view to focus on the next part
   */
  kHIViewFocusNextPart          = -1,

  /*
   * Tells view to focus on the previous part
   */
  kHIViewFocusPrevPart          = -2
};

/*==============================================================================*/
/*  CONTENT                                                                     */
/*==============================================================================*/
typedef ControlContentType              HIViewImageContentType;
typedef ControlImageContentInfo         HIViewImageContentInfo;
typedef SInt16                          HIViewContentType;

/*
 *  HIViewContentTypes
 *  
 */
enum {

  /*
   * The view has no content besides text.
   */
  kHIViewContentTextOnly        = 0,

  /*
   * The view has no content.
   */
  kHIViewContentNone            = 0,

  /*
   * The view's content is an IconSuiteRef.
   */
  kHIViewContentIconSuiteRef    = 129,

  /*
   * The view's content is an IconRef.
   */
  kHIViewContentIconRef         = 132,

  /*
   * The view's content is a CGImageRef.
   */
  kHIViewContentCGImageRef      = 134
};


/*
 *  HIViewContentInfo
 */
struct HIViewContentInfo {

  /*
   * The type of content referenced in the content union.
   */
  HIViewContentType   contentType;
  union {
    IconSuiteRef        iconSuite;
    IconRef             iconRef;
    CGImageRef          imageRef;
  }                       u;
};
typedef struct HIViewContentInfo        HIViewContentInfo;
typedef HIViewContentInfo *             HIViewContentInfoPtr;
/*==============================================================================*/
/*  ERROR CODES                                                                 */
/*==============================================================================*/

/*
 *  Discussion:
 *    View/Control Error Codes
 */
enum {

  /*
   * This value will be returned from an HIView API or a Control
   * Manager API when an action that is only supported on a compositing
   * window is attempted on a non-compositing window. This doesn't
   * necessarily mean that the API is only callable for compositing
   * windows; sometimes the legality of the action is based on other
   * parameters of the API. See HIViewAddSubview for one particular use
   * of this error code.
   */
  errNeedsCompositedWindow      = -30598
};

/*==============================================================================*/
/*  HIOBJECT SUPPORT                                                            */
/*                                                                              */
/*  Setting Initial Bounds                                                      */
/*                                                                              */
/*  When creating a view using HIObjectCreate, you can set the initial bounds   */
/*  automatically by passing in an initialization event into HIObjectCreate     */
/*  with a kEventParamBounds parameter as typeHIRect or typeQDRectangle.        */
/*==============================================================================*/
/* The HIObject class ID for the HIView class. */
#define kHIViewClassID                  CFSTR("com.apple.hiview")
/*==============================================================================*/
/*  EMBEDDING                                                                   */
/*==============================================================================*/
/*
 *  HIViewGetRoot()
 *  
 *  Discussion:
 *    Returns the root view for a window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to get the root for.
 *  
 *  Result:
 *    The root view for the window, or NULL if an invalid window is
 *    passed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewRef 
HIViewGetRoot(WindowRef inWindow)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewAddSubview()
 *  
 *  Discussion:
 *    Adds a subview to the given parent. The new subview is added to
 *    the front of the list of subviews (i.e., it is made topmost).
 *    
 *    The subview being added is not retained by the new parent view.
 *    Do not release the view after adding it, or it will cease to
 *    exist. All views in a window will be released automatically when
 *    the window is destroyed.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inParent:
 *      The view which will receive the new subview.
 *    
 *    inNewChild:
 *      The subview being added.
 *  
 *  Result:
 *    An operating system result code. 
 *    errNeedsCompositedWindow will be returned when you try to embed
 *    into the content view in a non-compositing window; you can only
 *    embed into the content view in compositing windows.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewAddSubview(
  HIViewRef   inParent,
  HIViewRef   inNewChild)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewRemoveFromSuperview()
 *  
 *  Discussion:
 *    Removes a view from its parent. 
 *    The subview being removed from the parent is not released and
 *    still exists.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to remove.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewRemoveFromSuperview(HIViewRef inView)                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetSuperview()
 *  
 *  Discussion:
 *    Returns a view's parent view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose parent you are interested in getting.
 *  
 *  Result:
 *    An HIView reference, or NULL if this view has no parent or is
 *    invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewRef 
HIViewGetSuperview(HIViewRef inView)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetFirstSubview()
 *  
 *  Discussion:
 *    Returns the first subview of a container. The first subview is
 *    the topmost subview in z-order.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose subview you are fetching.
 *  
 *  Result:
 *    An HIView reference, or NULL if this view has no subviews or is
 *    invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewRef 
HIViewGetFirstSubview(HIViewRef inView)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetLastSubview()
 *  
 *  Discussion:
 *    Returns the last subview of a container. The last subview is the
 *    bottommost subview in z-order.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose subview you are fetching.
 *  
 *  Result:
 *    An HIView reference, or NULL if this view has no subviews or is
 *    invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewRef 
HIViewGetLastSubview(HIViewRef inView)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetNextView()
 *  
 *  Discussion:
 *    Returns the next view after the one given, in z-order.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to use as reference.
 *  
 *  Result:
 *    An HIView reference, or NULL if this view has no view behind it
 *    or is invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewRef 
HIViewGetNextView(HIViewRef inView)                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetPreviousView()
 *  
 *  Discussion:
 *    Returns the previous view before the one given, in z-order.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to use as reference.
 *  
 *  Result:
 *    An HIView reference, or NULL if this view has no view in front of
 *    it or is invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewRef 
HIViewGetPreviousView(HIViewRef inView)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewCountSubviews()
 *  
 *  Summary:
 *    Counts the number of subviews embedded in a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to count subviews.
 *    
 *    outSubviewCount:
 *  
 *  Result:
 *    The number of subviews of the specified view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
HIViewCountSubviews(HIViewRef inView)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetIndexedSubview()
 *  
 *  Summary:
 *    Get the Nth subview of a view.
 *  
 *  Discussion:
 *    Instead of calling HIViewGetIndexedSubview repeatedly, it may be
 *    more efficient to iterate through the subviews of a view with
 *    calls HIViewGetFirstSubview and HIViewGetNextView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose indexed sub-view is being requested.
 *    
 *    inSubviewIndex:
 *      The index of the subview to get.
 *    
 *    outSubview:
 *      An HIViewRef to be filled with the indexed subview.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetIndexedSubview(
  HIViewRef    inView,
  CFIndex      inSubviewIndex,
  HIViewRef *  outSubview)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetZOrder()
 *  
 *  Discussion:
 *    Allows you to change the front-to-back ordering of sibling views.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose Z-order you wish to change.
 *    
 *    inOp:
 *      Indicates to order inView above or below inOther.
 *    
 *    inOther:
 *      Another optional view to use as a reference. You can pass NULL
 *      to mean an absolute position. For example, passing
 *      kHIViewZOrderAbove and NULL will move a view to the front of
 *      all of its siblings. Likewise, passing kHIViewZOrderBelow and
 *      NULL will move it to the back.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetZOrder(
  HIViewRef        inView,
  HIViewZOrderOp   inOp,
  HIViewRef        inOther)       /* can be NULL */           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/*  STATE and VALUES                                                            */
/*==============================================================================*/

/*
 *  HIViewKind
 */
struct HIViewKind {

  /*
   * The signature of the view. Apple reserves all signatures made up
   * of only lowercase characters.
   */
  OSType              signature;

  /*
   * The kind of the view. Apple reserves all kinds made up of only
   * lowercase characters.
   */
  OSType              kind;
};
typedef struct HIViewKind               HIViewKind;

/*
 *  View signature kind
 *  
 */
enum {

  /*
   * The signature of all HIToolbox views.
   */
  kHIViewKindSignatureApple     = 'appl'
};

/*
 *  HIViewSetVisible()
 *  
 *  Discussion:
 *    Hides or shows a view. Marks the area the view will occupy or
 *    used to occupy as needing to be redrawn later.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to hide or show.
 *    
 *    inVisible:
 *      A boolean value which indicates whether you wish to hide the
 *      view (false) or show the view (true).
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetVisible(
  HIViewRef   inView,
  Boolean     inVisible)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewIsVisible()
 *  
 *  Summary:
 *    Returns whether a view is visible.
 *  
 *  Discussion:
 *    Note that HIViewIsVisible returns a view's effective visibility,
 *    which is determined both by the view's own visibility and the
 *    visibility of its parent views. If a parent view is invisible,
 *    then this view is considered to be invisible also. 
 *    
 *    Latent visibility can be determined with HIViewIsLatentlyVisible.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose visibility you wish to determine.
 *  
 *  Result:
 *    A boolean value indicating whether the view is visible (true) or
 *    hidden (false).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsVisible(HIViewRef inView)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewIsLatentlyVisible()
 *  
 *  Summary:
 *    Returns whether or not a view is latently visible.
 *  
 *  Discussion:
 *    The view's visibility is also affected by the visibility of its
 *    parents; if any parent view is invisible, this view is considered
 *    invisible as well. HIViewIsLatentlyVisible returns whether a view
 *    is latently visible, even if its parents are invisible.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose latent visibility is to be checked.
 *  
 *  Result:
 *    True if the view is latently visible, otherwise false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsLatentlyVisible(HIViewRef inView)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetHilite()
 *  
 *  Summary:
 *    Changes the highlighting of a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view on which to set the highlight.
 *    
 *    inHilitePart:
 *      An HIViewPartCode indicating the part of the view to highlight.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetHilite(
  HIViewRef        inView,
  HIViewPartCode   inHilitePart)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewIsActive()
 *  
 *  Summary:
 *    Returns whether or not a view is active.
 *  
 *  Discussion:
 *    The view's active state is also affected by the active state of
 *    its parents; if any parent view is inactive, this view is
 *    considered inactive as well. HIViewIsActive can optionally check
 *    to see if a view is latently active, even if its parents are
 *    inactive.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose active state is to be checked.
 *    
 *    outIsLatentActive:
 *      A pointer to a Boolean to be filled in with the latent active
 *      state of the view. The Boolean is set to true if the view is
 *      latently active, otherwise false. Can be NULL.
 *  
 *  Result:
 *    True if the view is active, otherwise false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsActive(
  HIViewRef   inView,
  Boolean *   outIsLatentActive)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetActivated()
 *  
 *  Summary:
 *    Sets whether or not a view is active or inactive. If any children
 *    of the view have a latent active state, they will be adjusted
 *    accordingly.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to activate or deactivate.
 *    
 *    inSetActivated:
 *      True if setting the view to active, false if setting the view
 *      to inactive.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetActivated(
  HIViewRef   inView,
  Boolean     inSetActivated)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewIsEnabled()
 *  
 *  Summary:
 *    Tests whether or not a view is enabled.
 *  
 *  Discussion:
 *    The view's enabled state is also affected by the enabled state of
 *    its parents; if any parent view is disabled, this view is
 *    considered disabled as well. HIViewIsEnabled can optionally check
 *    to see if a view is latently enabled, even if its parents are
 *    disabled.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to test.
 *    
 *    outIsLatentEnabled:
 *      A pointer to a Boolean to be filled in with the latent enabled
 *      state of the view. The Boolean is set to true if the view is
 *      latently enabled, otherwise false. Can be NULL.
 *  
 *  Result:
 *    True if the view is enabled, otherwise false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsEnabled(
  HIViewRef   inView,
  Boolean *   outIsLatentEnabled)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetEnabled()
 *  
 *  Summary:
 *    Sets whether or not a view (and any subviews) are enabled or
 *    disabled.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to enable or disable.
 *    
 *    inSetEnabled:
 *      True if setting the view to enabled, false if setting the view
 *      to disabled.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetEnabled(
  HIViewRef   inView,
  Boolean     inSetEnabled)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewIsCompositingEnabled()
 *  
 *  Summary:
 *    Returns whether a view is being used in a compositing hierarchy.
 *  
 *  Discussion:
 *    A view that supports both compositing mode and non-compositing
 *    mode can use this routine to determine which mode it is currently
 *    running in. Looking for a window's kWindowCompositingAttribute is
 *    not sufficient, since some windows with that attribute have some
 *    of its views in non-compositing mode and vice-versa.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose compositing state you wish to determine.
 *  
 *  Result:
 *    A boolean value indicating whether the view is in compositing
 *    mode (true) or non-compositing mode (false).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsCompositingEnabled(HIViewRef inView)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetText()
 *  
 *  Summary:
 *    Sets the text of a view to the specified string.
 *  
 *  Discussion:
 *    The "text" of the view is the text that will be displayed when
 *    drawing the view. This API first attempts to set the view's text
 *    (generally successful on views that handle the
 *    kControlEditTextCFStringTag SetControlData tag). If the attempt
 *    is unsuccessful, the view's title is set instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose text is being set.
 *    
 *    inText:
 *      The text to set for the view. The string is copied by the view,
 *      and may be released by the caller afterwards.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetText(
  HIViewRef     inView,
  CFStringRef   inText)                                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewCopyText()
 *  
 *  Summary:
 *    Makes a copy of the view's text as a CFString.
 *  
 *  Discussion:
 *    The "text" of the view is the text that will be displayed when
 *    drawing the view. This API first attempts to get the view's text
 *    (generally successful on views that handle the
 *    kControlEditTextCFStringTag GetControlData tag). If the attempt
 *    is unsuccessful, the view's title is copied instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the text.
 *  
 *  Result:
 *    A CFStringRef containing a copy of the view's text. The caller of
 *    HIViewCopyText is responsible for releasing the returned text.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
HIViewCopyText(HIViewRef inView)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetValue()
 *  
 *  Summary:
 *    Gets a view's value.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the value.
 *  
 *  Result:
 *    The view's value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern SInt32 
HIViewGetValue(HIViewRef inView)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetValue()
 *  
 *  Summary:
 *    Sets a view's value.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose value is to be set.
 *    
 *    inValue:
 *      The new value.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetValue(
  HIViewRef   inView,
  SInt32      inValue)                                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetMinimum()
 *  
 *  Summary:
 *    Gets a view's minimum value.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the minimum value.
 *  
 *  Result:
 *    The view's minimum value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern SInt32 
HIViewGetMinimum(HIViewRef inView)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetMinimum()
 *  
 *  Summary:
 *    Sets a view's minimum value.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose minimum value is to be set.
 *    
 *    inMinimum:
 *      The new minimum value.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetMinimum(
  HIViewRef   inView,
  SInt32      inMinimum)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetMaximum()
 *  
 *  Summary:
 *    Gets a view's maximum value.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the maximum value.
 *  
 *  Result:
 *    The view's maximum value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern SInt32 
HIViewGetMaximum(HIViewRef inView)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetMaximum()
 *  
 *  Summary:
 *    Sets a view's maximum value.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose maximum value is to be set.
 *    
 *    inMaximum:
 *      The new maximum value.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetMaximum(
  HIViewRef   inView,
  SInt32      inMaximum)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetViewSize()
 *  
 *  Summary:
 *    Gets a view's view size.
 *  
 *  Discussion:
 *    The view size is the size of the content to which a view's
 *    display is proportioned. Most commonly used to set the
 *    proportional size of a scroll bar's thumb indicator.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the view size.
 *  
 *  Result:
 *    The view size.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern SInt32 
HIViewGetViewSize(HIViewRef inView)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetViewSize()
 *  
 *  Summary:
 *    Sets a view's view size.
 *  
 *  Discussion:
 *    The view size is the size of the content to which a view's
 *    display is proportioned. Most commonly used to set the
 *    proportional size of a scroll bar's thumb indicator.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose view size is to be set.
 *    
 *    inViewSize:
 *      The new view size.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetViewSize(
  HIViewRef   inView,
  SInt32      inViewSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewIsValid()
 *  
 *  Summary:
 *    HIViewIsValid tests to see if the passed in view is a view that
 *    HIToolbox knows about. It does not sanity check the data in the
 *    view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to test for validity.
 *  
 *  Result:
 *    True if the view is a valid view, otherwise, false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsValid(HIViewRef inView)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetID()
 *  
 *  Summary:
 *    Sets the HIViewID of a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to set the ID.
 *    
 *    inID:
 *      The ID to set on the view.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetID(
  HIViewRef   inView,
  HIViewID    inID)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetID()
 *  
 *  Summary:
 *    Gets the HIViewID of a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the ID.
 *    
 *    outID:
 *      A pointer to an HIViewID to be filled with the view's ID.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetID(
  HIViewRef   inView,
  HIViewID *  outID)                                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetCommandID()
 *  
 *  Summary:
 *    Sets the command ID of a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to set the command ID.
 *    
 *    inCommandID:
 *      The command ID to set on the view.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetCommandID(
  HIViewRef   inView,
  UInt32      inCommandID)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetCommandID()
 *  
 *  Summary:
 *    Gets the command ID of a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to get the command ID.
 *    
 *    outCommandID:
 *      A pointer to a UInt32 to fill with the view's command id.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetCommandID(
  HIViewRef   inView,
  UInt32 *    outCommandID)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetKind()
 *  
 *  Summary:
 *    Returns the kind of the given view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose kind to get.
 *    
 *    outViewKind:
 *      On successful exit, this will contain the view signature and
 *      kind. See ControlDefinitions.h or HIView.h for the kinds of
 *      each system view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetKind(
  HIViewRef     inView,
  HIViewKind *  outViewKind)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*==============================================================================*/
/*  POSITIONING                                                                 */
/*==============================================================================*/
/*
 *  HIViewGetBounds()
 *  
 *  Discussion:
 *    Returns the local bounds of a view. The local bounds are the
 *    coordinate system that is completely view-relative. A view's top
 *    left coordinate starts out at 0, 0. Most operations are done in
 *    these local coordinates. Moving a view is done via the frame
 *    instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose bounds you wish to determine.
 *    
 *    outRect:
 *      The local bounds of the view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetBounds(
  HIViewRef   inView,
  HIRect *    outRect)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetFrame()
 *  
 *  Discussion:
 *    Returns the frame of a view. The frame is the bounds of a view
 *    relative to its parent's local coordinate system.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose frame you wish to determine.
 *    
 *    outRect:
 *      The frame of the view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetFrame(
  HIViewRef   inView,
  HIRect *    outRect)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetFrame()
 *  
 *  Discussion:
 *    Sets the frame of a view. This effectively moves the view within
 *    its parent. It also marks the view (and anything that was exposed
 *    behind it) to be redrawn.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose frame you wish to change.
 *    
 *    inRect:
 *      The new frame of the view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetFrame(
  HIViewRef       inView,
  const HIRect *  inRect)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewMoveBy()
 *  
 *  Discussion:
 *    Moves a view by a certain distance, relative to its current
 *    location. This affects a view's frame, but not its bounds.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view you wish to move.
 *    
 *    inDX:
 *      The horizontal distance to move the view. Negative values move
 *      the view to the left, positive values to the right.
 *    
 *    inDY:
 *      The vertical distance to move the view. Negative values move
 *      the view upward, positive values downward.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewMoveBy(
  HIViewRef   inView,
  float       inDX,
  float       inDY)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewPlaceInSuperviewAt()
 *  
 *  Discussion:
 *    Places a view at an absolute location within its parent. This
 *    affects the view's frame, but not its bounds.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view you wish to position.
 *    
 *    inX:
 *      The absolute horizontal coordinate at which to position the
 *      view.
 *    
 *    inY:
 *      The absolute vertical coordinate at which to position the view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewPlaceInSuperviewAt(
  HIViewRef   inView,
  float       inX,
  float       inY)                                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewReshapeStructure()
 *  
 *  Discussion:
 *    This is for use by custom views. If a view decides that its
 *    structure will change shape, it should call this. This tells the
 *    Toolbox to recalc things and invalidate as appropriate. You might
 *    use this when gaining/losing a focus ring, for example.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to reshape and invalidate.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewReshapeStructure(HIViewRef inView)                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewRegionChanged()
 *  
 *  Discussion:
 *    Allows a view to tell the view system that a region of itself has
 *    changed. The view system might choose to react in some way. For
 *    example, if a view's clickable region has changed, this can be
 *    called to tell the Toolbox to resync the region it uses for async
 *    window dragging, if enabled. Likewise, if a view's opaque region
 *    changes, we can adjust the window's opaque shape as well. When
 *    views are moved, resizes, this stuff is taken care of for you. So
 *    this only need be called when there's a change in your view that
 *    occurs outside of those times.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to deal with.
 *    
 *    inRegionCode:
 *      The region that was changed. This can only be the structure
 *      opaque, and clickable regions at present.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewRegionChanged(
  HIViewRef        inView,
  HIViewPartCode   inRegionCode)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewCopyShape()
 *  
 *  Summary:
 *    Copies the shape of a part of a view. See the discussion on
 *    meta-parts in this header for more information
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view for which to copy the shape.
 *    
 *    inPart:
 *      The part of the view whose shape is to be copied.
 *    
 *    outShape:
 *      On exit, contains a newly created shape. The caller of
 *      HIViewCopyShape is responsible for releasing the copied shape.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewCopyShape(
  HIViewRef        inView,
  HIViewPartCode   inPart,
  HIShapeRef *     outShape)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetOptimalBounds()
 *  
 *  Summary:
 *    Obtain a view's optimal size and/or text placement.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to examine.
 *    
 *    outBounds:
 *      A pointer to an HIRect to be filled with the view's optimal
 *      bounds. Can be NULL.
 *    
 *    outBaseLineOffset:
 *      A pointer to a float to be filled with the view's optimal text
 *      placement. Can be NULL.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetOptimalBounds(
  HIViewRef   inView,
  HIRect *    outBounds,               /* can be NULL */
  float *     outBaseLineOffset)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*==============================================================================*/
/*  HIT TESTING/EVENT HANDLING                                                  */
/*==============================================================================*/
/*
 *  HIViewGetViewForMouseEvent()
 *  
 *  Discussion:
 *    Returns the appropriate view to handle a mouse event. This is a
 *    little higher-level than HIViewGetSubviewHit. This routine will
 *    find the deepest view that should handle the mouse event, but
 *    along the way, it sends Carbon Events to each view asking it to
 *    return the appropriate subview. This allows parent views to catch
 *    clicks on their subviews. This is the recommended function to use
 *    before processing mouse events. Using one of the more primitive
 *    functions may result in an undefined behavior. In general we
 *    recommend the use of the Standard Window Handler instead of
 *    calling this function yourself.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to start from. You should pass the window's root view.
 *    
 *    inEvent:
 *      The mouse event in question.
 *    
 *    outView:
 *      The view that the mouse event should be sent to.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetViewForMouseEvent(
  HIViewRef    inView,
  EventRef     inEvent,
  HIViewRef *  outView)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewClick()
 *  
 *  Discussion:
 *    After a successful call to HIViewGetViewForMouseEvent for a mouse
 *    down event, you should call this function to have the view handle
 *    the click. In general we recommend the use of the Standard Window
 *    Handler instead of calling this function yourself.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to handle the event.
 *    
 *    inEvent:
 *      The mouse event to handle.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewClick(
  HIViewRef   inView,
  EventRef    inEvent)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSimulateClick()
 *  
 *  Discussion:
 *    This function is used to simulate a mouse click on a given view.
 *    It sends a kEventControlSimulateHit event to the specified view,
 *    and also sends kEventControlHit and (if the Hit event is not
 *    handled) kEventCommandProcess events.
 *    
 *    Note that not all windows will respond to the events that are
 *    sent by this API. A fully Carbon-event-based window most likely
 *    will respond exactly as if the user had really clicked in the
 *    view. A window that is handled using classic EventRecord-based
 *    APIs (WaitNextEvent or ModalDialog) will typically not respond at
 *    all; to simulate a click in such a window, you may need to post a
 *    mouse-down/mouse-up pair, or use a Dialog Manager event filter
 *    proc to simulate a hit in a dialog item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to test the part hit.
 *    
 *    inPartToClick:
 *      The part the view should consider to be clicked.
 *    
 *    inModifiers:
 *      The modifiers the view can consider for its click action.
 *    
 *    outPartClicked:
 *      The part that was hit, can be kControlNoPart if no action
 *      occurred. May be NULL if you don't need the part code returned.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSimulateClick(
  HIViewRef         inView,
  HIViewPartCode    inPartToClick,
  UInt32            inModifiers,
  HIViewPartCode *  outPartClicked)       /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetPartHit()
 *  
 *  Discussion:
 *    Given a view, and a view-relative point, this function returns
 *    the part code hit as determined by the view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to test the part hit.
 *    
 *    inPoint:
 *      The view-relative point to use.
 *    
 *    outPart:
 *      The part hit by inPoint.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetPartHit(
  HIViewRef         inView,
  const HIPoint *   inPoint,
  HIViewPartCode *  outPart)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetSubviewHit()
 *  
 *  Discussion:
 *    Returns the child of the given view hit by the point passed in.
 *    This is more primitive than using HIViewGetViewForMouseEvent, and
 *    should be used only in non-event-handling cases.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view you wish to start from.
 *    
 *    inPoint:
 *      The mouse coordinate to use. This is passed in the local
 *      coordinate system of inView.
 *    
 *    inDeep:
 *      Pass true to find the deepest child hit, false to go only one
 *      level deep (just check direct children of inView).
 *    
 *    outView:
 *      The view hit by inPoint, or NULL if no subview was hit.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetSubviewHit(
  HIViewRef        inView,
  const HIPoint *  inPoint,
  Boolean          inDeep,
  HIViewRef *      outView)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/*  HIView-based tracking areas                                                 */
/*==============================================================================*/
typedef struct OpaqueHIViewTrackingAreaRef*  HIViewTrackingAreaRef;
enum {
  kEventParamHIViewTrackingArea = 'ctra', /* typeHIViewTrackingAreaRef*/
  typeHIViewTrackingAreaRef     = 'ctra'
};

/*
 *  kEventClassControl / kEventControlTrackingAreaEntered
 *  
 *  Summary:
 *    The mouse has entered a tracking area owned by your control.
 *  
 *  Discussion:
 *    If you have installed a mouse tracking area in your view, you
 *    will receive this event when the mouse enters that area. The
 *    tracking area reference is sent with the event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamHIViewTrackingArea (in, typeHIViewTrackingAreaRef)
 *          The tracking area that was entered.
 *    
 *    --> kEventParamKeyModifiers (in, typeUInt32)
 *          The keyboard modifiers that were in effect when the mouse
 *          entered.
 *    
 *    --> kEventParamMouseLocation (in, typeHIPoint)
 *          The location of the mouse in view coordinates.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventControlTrackingAreaEntered = 23
};

/*
 *  kEventClassControl / kEventControlTrackingAreaExited
 *  
 *  Summary:
 *    The mouse has exited a tracking area owned by your control.
 *  
 *  Discussion:
 *    If you have installed a mouse tracking area in your view, you
 *    will receive this event when the mouse leaves that area. The
 *    tracking area reference is sent with the event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamHIViewTrackingArea (in, typeHIViewTrackingAreaRef)
 *          The tracking area that was entered.
 *    
 *    --> kEventParamKeyModifiers (in, typeUInt32)
 *          The keyboard modifiers that were in effect when the mouse
 *          left.
 *    
 *    --> kEventParamMouseLocation (in, typeHIPoint)
 *          The location of the mouse in view coordinates. This point
 *          may or may not lie on the boundary of the mouse region. It
 *          is merely where the mouse was relative to the view when the
 *          exit event was generated.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventControlTrackingAreaExited = 24
};


typedef UInt64                          HIViewTrackingAreaID;
/*
 *  HIViewNewTrackingArea()
 *  
 *  Summary:
 *    Creates a new tracking area for a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to create a tracking area for.
 *    
 *    inShape:
 *      The shape to use. Pass NULL to indicate the entire structure
 *      region of the view is to be used.
 *    
 *    inID:
 *      An identifier for this tracking area. This value is completely
 *      up to the view to define. Pass zero if you don't care.
 *    
 *    outRef:
 *      A reference to the newly created tracking area. This references
 *      is NOT refcounted.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewNewTrackingArea(
  HIViewRef                inView,
  HIShapeRef               inShape,       /* can be NULL */
  HIViewTrackingAreaID     inID,
  HIViewTrackingAreaRef *  outRef)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewChangeTrackingArea()
 *  
 *  Summary:
 *    Alters the shape of an existing tracking area.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inArea:
 *      The area to change.
 *    
 *    inShape:
 *      The shape to use. Pass NULL to indicate the entire structure
 *      region of the view is to be used.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewChangeTrackingArea(
  HIViewTrackingAreaRef   inArea,
  HIShapeRef              inShape)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetTrackingAreaID()
 *  
 *  Summary:
 *    Retrieves the HIViewTrackingAreaID of an existing tracking area.
 *    This value was set upon creation of the HIViewTrackingArea.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inArea:
 *      The area whose HIViewTrackingAreaID to retrieve.
 *    
 *    outID:
 *      The HIViewTrackingAreaID for this tracking area.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetTrackingAreaID(
  HIViewTrackingAreaRef   inArea,
  HIViewTrackingAreaID *  outID)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewDisposeTrackingArea()
 *  
 *  Summary:
 *    Disposes an existing tracking area. The reference is considered
 *    to be invalid after calling this function.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inArea:
 *      The area to dispose.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewDisposeTrackingArea(HIViewTrackingAreaRef inArea)       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*==============================================================================*/
/*  DISPLAY                                                                     */
/*==============================================================================*/
/*
 *  HIViewGetNeedsDisplay()
 *  
 *  Discussion:
 *    Returns true if the view passed in or any subview of it requires
 *    redrawing (i.e. part of it has been invalidated).
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to inspect.
 *  
 *  Result:
 *    A boolean result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewGetNeedsDisplay(HIViewRef inView)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetNeedsDisplay()
 *  
 *  Discussion:
 *    Marks a view as needing to be completely redrawn, or completely
 *    valid. If the view is not visible, or is obscured completely by
 *    other views, no action is taken.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to mark dirty.
 *    
 *    inNeedsDisplay:
 *      A boolean which indicates whether inView needs to be redrawn or
 *      not.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetNeedsDisplay(
  HIViewRef   inView,
  Boolean     inNeedsDisplay)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetNeedsDisplayInRect()
 *  
 *  Discussion:
 *    Marks a portion of a view as needing to be redrawn, or valid. If
 *    the view is not visible, or is obscured completely by other
 *    views, no action is taken. The rectangle passed is effectively
 *    intersected with the view's visible region. It should be in
 *    view-relative coordinates.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to mark dirty.
 *    
 *    inRect:
 *      The rectangle encompassing the area to mark dirty or clean.
 *    
 *    inNeedsDisplay:
 *      A boolean which indicates whether or not inRect should be added
 *      to the invalid region or removed from it.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetNeedsDisplayInRect(
  HIViewRef       inView,
  const HIRect *  inRect,
  Boolean         inNeedsDisplay)                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetNeedsDisplayInShape()
 *  
 *  Discussion:
 *    Marks a portion of a view as needing to be redrawn, or valid. If
 *    the view is not visible, or is obscured completely by other
 *    views, no action is taken. The shape passed is effectively
 *    intersected with the view's visible region. It should be in
 *    view-relative coordinates.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to mark dirty.
 *    
 *    inArea:
 *      The area to mark dirty or clean.
 *    
 *    inNeedsDisplay:
 *      A boolean which indicates whether or not inArea should be added
 *      to the invalid region or removed from it.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetNeedsDisplayInShape(
  HIViewRef    inView,
  HIShapeRef   inArea,
  Boolean      inNeedsDisplay)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewSetNeedsDisplayInRegion()
 *  
 *  Discussion:
 *    Marks a portion of a view as needing to be redrawn, or valid. If
 *    the view is not visible, or is obscured completely by other
 *    views, no action is taken. The region passed is effectively
 *    intersected with the view's visible region. It should be in
 *    view-relative coordinates.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to mark dirty.
 *    
 *    inRgn:
 *      The region to mark dirty or clean.
 *    
 *    inNeedsDisplay:
 *      A boolean which indicates whether or not inRgn should be added
 *      to the invalid region or removed from it.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetNeedsDisplayInRegion(
  HIViewRef   inView,
  RgnHandle   inRgn,
  Boolean     inNeedsDisplay)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewRender()
 *  
 *  Discussion:
 *    Renders the invalid portions of a view (as marked with
 *    HIViewSetNeedsDisplay[InRegion]) immediately. Normally, these
 *    areas are redrawn at event loop time, but there might be
 *    situations where you need an immediate draw. Use this sparingly,
 *    as it does cause a fully composited draw for the area of the
 *    view; that is, all other views that intersect the area of the
 *    specified view will also be drawn. Calling this for several views
 *    at a particular level of a hierarchy can be costly. We highly
 *    recommend that you only pass the root view of a window to this
 *    API. The behavior of this API when passed a non-root view was
 *    poorly defined in Mac OS X 10.3 and has changed in Mac OS X 10.4.
 *    In 10.3, calling this API on a non-root view would entirely
 *    validate all of the views in the window that intersect the
 *    specified view, including portions that did not intersect the
 *    specified view and so were not actually drawn. In 10.4, calling
 *    this API on a non-root view will only validate those portions of
 *    each view that intersect the specified view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to draw.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewRender(HIViewRef inView)                                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewFlashDirtyArea()
 *  
 *  Discussion:
 *    Debugging aid. Flashes the region which would be redrawn at the
 *    next draw time for an entire window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The window to flash the dirty region for.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewFlashDirtyArea(WindowRef inWindow)                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetSizeConstraints()
 *  
 *  Discussion:
 *    Return the minimum and maximum size for a control. A control must
 *    respond to this protocol to get meaningful results. These sizes
 *    can be used to help autoposition subviews, for example.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to inspect.
 *    
 *    outMinSize:
 *      The minimum size the view can be. May be NULL if you don't need
 *      this information.
 *    
 *    outMaxSize:
 *      The maximum size the view can be. May be NULL if you don't need
 *      this information.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetSizeConstraints(
  HIViewRef   inView,
  HISize *    outMinSize,       /* can be NULL */
  HISize *    outMaxSize)       /* can be NULL */             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/*  COORDINATE SYSTEM CONVERSION                                                */
/*==============================================================================*/
/*
 *  HIViewConvertPoint()
 *  
 *  Discussion:
 *    Converts a point from one view to another. Both views must have a
 *    common ancestor, i.e. they must both be in the same window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    ioPoint:
 *      The point to convert.
 *    
 *    inSourceView:
 *      The view whose coordinate system ioPoint is starting out in.
 *      You can pass NULL to indicate that ioPoint is a window-relative
 *      point.
 *    
 *    inDestView:
 *      The view whose coordinate system ioPoint should end up in. You
 *      can pass NULL to indicate that ioPoint is a window-relative
 *      point.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewConvertPoint(
  HIPoint *   ioPoint,
  HIViewRef   inSourceView,
  HIViewRef   inDestView)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewConvertRect()
 *  
 *  Discussion:
 *    Converts a rectangle from one view to another. Both views must
 *    have a common ancestor, i.e. they must both be in the same window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    ioRect:
 *      The rectangle to convert.
 *    
 *    inSourceView:
 *      The view whose coordinate system ioRect is starting out in. You
 *      can pass NULL to indicate that ioRect is a window-relative
 *      rectangle.
 *    
 *    inDestView:
 *      The view whose coordinate system ioRect should end up in. You
 *      can pass NULL to indicate that ioRect is a window-relative
 *      rectangle.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewConvertRect(
  HIRect *    ioRect,
  HIViewRef   inSourceView,
  HIViewRef   inDestView)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewConvertRegion()
 *  
 *  Discussion:
 *    Converts a region from one view to another. Both views must have
 *    a common ancestor, i.e. they must both be in the same window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    ioRgn:
 *      The region to convert.
 *    
 *    inSourceView:
 *      The view whose coordinate system ioRgn is starting out in. You
 *      can pass NULL to indicate that ioRgn is a window-relative
 *      region.
 *    
 *    inDestView:
 *      The view whose coordinate system ioRgn should end up in. You
 *      can pass NULL to indicate that ioRgn is a window-relative
 *      region.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewConvertRegion(
  RgnHandle   ioRgn,
  HIViewRef   inSourceView,
  HIViewRef   inDestView)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetDrawingEnabled()
 *  
 *  Discussion:
 *    Turns control drawing on or off. You can use this to ensure that
 *    no drawing events are sent to the control. Even Draw1Control will
 *    not draw! HIViewSetNeedsDisplay is also rendered useless when
 *    drawing is off.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to enable or disable drawing for.
 *    
 *    inEnabled:
 *      A boolean value indicating whether drawing should be on (true)
 *      or off (false).
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetDrawingEnabled(
  HIViewRef   inView,
  Boolean     inEnabled)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewIsDrawingEnabled()
 *  
 *  Discussion:
 *    Determines if drawing is currently enabled for a control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to get the drawing state for.
 *  
 *  Result:
 *    A boolean value indicating whether drawing is on (true) or off
 *    (false).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsDrawingEnabled(HIViewRef inView)                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewScrollRect()
 *  
 *  Discussion:
 *    Scrolls a view's contents, or a portion thereof. A view's
 *    contents are the pixels that it or any of its descendent views
 *    has drawn into. This will actually blit the contents of the view
 *    as appropriate to scroll, and then invalidate those portions
 *    which need to be redrawn. Be warned that this is a raw bit
 *    scroll. Anything that might overlap the target view will get
 *    thrashed as well.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to scroll. The bits drawn by the view's descendent
 *      views will also be scrolled.
 *    
 *    inRect:
 *      The rect to scroll. Pass NULL to mean the entire view. The rect
 *      passed cannot be bigger than the view's bounds. It must be in
 *      the local coordinate system of the view.
 *    
 *    inDX:
 *      The horizontal distance to scroll. Positive values shift to the
 *      right, negative values shift to the left.
 *    
 *    inDY:
 *      The vertical distance to scroll. Positive values shift
 *      downward, negative values shift upward.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewScrollRect(
  HIViewRef       inView,
  const HIRect *  inRect,       /* can be NULL */
  float           inDX,
  float           inDY)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetBoundsOrigin()
 *  
 *  Discussion:
 *    This API sets the origin of the view. This effectively also moves
 *    all subcontrols of a view as well. This call will NOT invalidate
 *    the view. This is because you might want to move the contents
 *    with HIViewScrollRect instead of redrawing the complete content.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose origin you wish to adjust.
 *    
 *    inX:
 *      The X coordinate.
 *    
 *    inY:
 *      The Y coordinate.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetBoundsOrigin(
  HIViewRef   inView,
  float       inX,
  float       inY)                                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/*  KEYBOARD FOCUS                                                              */
/*==============================================================================*/
/*
 *  HIViewAdvanceFocus()
 *  
 *  Discussion:
 *    Advances the focus to the next most appropriate view. Unless
 *    overriden in some fashion (either by overriding certain carbon
 *    events or using the HIViewSetNextFocus API), the Toolbox will use
 *    a spacially determinant method of focusing, attempting to focus
 *    left to right, top to bottom in a window, taking groups of
 *    controls into account.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inRootForFocus:
 *      The subtree to manipulate. The focus will never leave
 *      inRootToFocus. Typically you would pass the content of the
 *      window, or the root. If focused on the toolbar, for example,
 *      the focus is limited to the toolbar only. In this case, the
 *      Toolbox passes the toolbar view in as the focus root for
 *      example.
 *    
 *    inModifiers:
 *      The EventModifiers of the keyboard event that ultimately caused
 *      the call to HIViewAdvanceFocus. These modifiers are used to
 *      determine the focus direction as well as other alternate
 *      focusing behaviors.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewAdvanceFocus(
  HIViewRef        inRootForFocus,
  EventModifiers   inModifiers)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetFocusPart()
 *  
 *  Discussion:
 *    Returns the currently focused part of the given view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to inquire about.
 *    
 *    outFocusPart:
 *      The part currently focused.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetFocusPart(
  HIViewRef         inView,
  HIViewPartCode *  outFocusPart)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSubtreeContainsFocus()
 *  
 *  Discussion:
 *    Given a view, this function checks to see if it or any of its
 *    children currently are the keyboard focus. If so, true is
 *    returned as the function result.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSubtreeStart:
 *      The view to start searching at.
 *  
 *  Result:
 *    A boolean result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewSubtreeContainsFocus(HIViewRef inSubtreeStart)          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetNextFocus()
 *  
 *  Discussion:
 *    This function hard-wires the next sibling view to shift focus to
 *    whenever the keyboard focus is advanced.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to set the next focus view for. This parameter and the
 *      inNextFocus parameter must both have the same parent view.
 *    
 *    inNextFocus:
 *      The view to set focus to next. This parameter and the inView
 *      parameter must both have the same parent view. Pass NULL to
 *      tell the view system to use the default rules.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetNextFocus(
  HIViewRef   inView,
  HIViewRef   inNextFocus)       /* can be NULL */            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewSetFirstSubViewFocus()
 *  
 *  Discussion:
 *    This function hard-wires the first subview to shift focus to
 *    whenever the keyboard focus is advanced and the container view is
 *    entered.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inParent:
 *      The parent view.
 *    
 *    inSubView:
 *      The first child which should receive focus. Pass NULL to tell
 *      the view system to use the default rules.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetFirstSubViewFocus(
  HIViewRef   inParent,
  HIViewRef   inSubView)       /* can be NULL */              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/*  LAYOUT                                                                      */
/*                                                                              */
/*  Mac OS X 10.3 provides a layout engine for HIViews that allows applications */
/*  to specify the layout relationships between multiple views. The layout      */
/*  engine will automatically reposition and resize views that have layout      */
/*  information when necessary.                                                 */
/*==============================================================================*/

/*
 *  Summary:
 *    Since horizontal and vertical bindings are very similar in
 *    application, except along different axes, the binding kinds have
 *    been abstracted to minimum and maximum. Synonyms have been
 *    provided for convenience. You are encouraged to use them.
 *  
 *  Discussion:
 *    HIBindingKind constants.
 */
enum {

  /*
   * No binding is to occur.
   */
  kHILayoutBindNone             = 0,

  /*
   * Bind to the minimum of the axis.
   */
  kHILayoutBindMin              = 1,

  /*
   * Bind to the maximum of the axis.
   */
  kHILayoutBindMax              = 2,
  kHILayoutBindLeft             = kHILayoutBindMin,
  kHILayoutBindRight            = kHILayoutBindMax,

  /*
   * Synonyms for convenience and clarity.
   */
  kHILayoutBindTop              = kHILayoutBindMin,
  kHILayoutBindBottom           = kHILayoutBindMax
};

typedef UInt16                          HIBindingKind;

/*
 *  HISideBinding
 *  
 *  Summary:
 *    A binding for a side of an HIView.
 *  
 *  Discussion:
 *    A side binding is entirely related to the change of the parent's
 *    position or size (but only as the size affects the maximum edge
 *    position). A side binding doesn't mean "move to where my
 *    relative's side is" but rather "move as my relative's side has
 *    moved".
 */
struct HISideBinding {

  /*
   * An HIViewRef to the view to which this side is bound. Can be NULL,
   * indicating that the the side is bound to its parent view.
   */
  HIViewRef           toView;                 /* NULL means parent*/

  /*
   * An HIBindingKind indicating the bind kind.
   */
  HIBindingKind       kind;

  /*
   * Not currently used. Must be set to 0.
   */
  float               offset;
};
typedef struct HISideBinding            HISideBinding;
/*
    const HISideBinding kHISideNoBinding = { NULL, kHILayoutBindNone };
*/

/*
 *  HIBinding
 *  
 *  Summary:
 *    A set of Top, Left, Bottom, and Right bindings for an HIView.
 */
struct HIBinding {

  /*
   * The top side bindings.
   */
  HISideBinding       top;

  /*
   * The left side bindings.
   */
  HISideBinding       left;

  /*
   * The bottom side bindings.
   */
  HISideBinding       bottom;

  /*
   * The right side bindings.
   */
  HISideBinding       right;
};
typedef struct HIBinding                HIBinding;
/*
    const HIBinding kHINoBinding = { kHISideNoBinding, kHISideNoBinding, kHISideNoBinding, kHISideNoBinding };
*/

/*
 *  Discussion:
 *    HIScaleKind constants.
 */
enum {

  /*
   * The scale is determined from the axis size.
   */
  kHILayoutScaleAbsolute        = 0
};


typedef UInt16                          HIScaleKind;

/*
 *  HIAxisScale
 *  
 *  Summary:
 *    A scale description for an axis of an HIView.
 */
struct HIAxisScale {

  /*
   * An HIViewRef to the view to which this axis is scaled. Can be
   * NULL, indicating that the the axis is scaled relative to its
   * parent view.
   */
  HIViewRef           toView;                 /* NULL means parent*/

  /*
   * An HIScaleKind describing the type of scaling to be applied. 
   * Currently, this field can't be anything other than
   * kScalingAbsolute.
   */
  HIScaleKind         kind;

  /*
   * A float indicating how much to scale the HIView. 0 indicates no
   * scaling. A value of 1 indicates that the view is to always have
   * the same axial size.
   */
  float               ratio;
};
typedef struct HIAxisScale              HIAxisScale;

/*
 *  HIScaling
 *  
 *  Summary:
 *    A set of scaling descriptions for the axes of an HIView.
 */
struct HIScaling {

  /*
   * An HIAxisScale describing the horizontal scaling for an HIView.
   */
  HIAxisScale         x;
  HIAxisScale         y;
};
typedef struct HIScaling                HIScaling;

/*
 *  Summary:
 *    Since horizontal and vertical positions are very similar in
 *    application, except along different axes, the position kinds have
 *    been abstracted to minimum and maximum. Synonyms have been
 *    provided for convenience. You are encouraged to use them.
 *  
 *  Discussion:
 *    HIPositionKind constants.
 */
enum {

  /*
   * No positioning is to occur.
   */
  kHILayoutPositionNone         = 0,

  /*
   * Centered positioning will occur. The view will be centered
   * relative to the specified view.
   */
  kHILayoutPositionCenter       = 1,

  /*
   * Minimum positioning will occur. The view will be left or top
   * aligned relative to the specified view.
   */
  kHILayoutPositionMin          = 2,

  /*
   * Maximum positioning will occur. The view will be right or bottom
   * aligned relative to the specified view.
   */
  kHILayoutPositionMax          = 3,

  /*
   * Synonyms for convenience and clarity.
   */
  kHILayoutPositionLeft         = kHILayoutPositionMin,
  kHILayoutPositionRight        = kHILayoutPositionMax,
  kHILayoutPositionTop          = kHILayoutPositionMin,
  kHILayoutPositionBottom       = kHILayoutPositionMax
};


typedef UInt16                          HIPositionKind;

/*
 *  HIAxisPosition
 *  
 *  Summary:
 *    An axial position description for an HIView.
 */
struct HIAxisPosition {

  /*
   * An HIViewRef to the view relative to which a view will be
   * positioned. Can be NULL, indicating that the the view is
   * positioned relative to its parent view.
   */
  HIViewRef           toView;                 /* NULL means parent*/

  /*
   * An HIPositionKind indicating the kind of positioning to apply.
   */
  HIPositionKind      kind;

  /*
   * After the position kind has been applied, the origin component
   * that corresponds to the positioning axis is offet by this value.
   * (ex: Left aligned + 10 ).
   */
  float               offset;
};
typedef struct HIAxisPosition           HIAxisPosition;

/*
 *  HIPositioning
 *  
 *  Summary:
 *    A positioning description for an HIView.
 */
struct HIPositioning {

  /*
   * An HIAxisPosition describing the horizontal positioning for an
   * HIView.
   */
  HIAxisPosition      x;
  HIAxisPosition      y;
};
typedef struct HIPositioning            HIPositioning;

/*
 *  HILayoutInfo
 *  
 *  Summary:
 *    A layout description for an HIView.
 *  
 *  Discussion:
 *    The different layout transformations are applied sequentially to
 *    the HIView. First, the bindings are applied. Note that the
 *    bindings are applied recursively to a container's HIViews. This
 *    requires care on your part, especially when applying
 *    inter-relational bindings. Then the scaling (which could
 *    potentially override some of the previously applied bindings).
 *    Then the positioning (which could potentially override some of
 *    the previously applied bindings).
 */
struct HILayoutInfo {

  /*
   * The version of the structure. The current version is
   * kHILayoutInfoVersionZero.
   */
  UInt32              version;

  /*
   * An HIBinding structure describing the kinds of bindings to apply
   * to the sides of an HIView.
   */
  HIBinding           binding;

  /*
   * An HIScaling structure describing the axial scaling to apply to an
   * HIView.
   */
  HIScaling           scale;

  /*
   * An HIPositioning structure positioning to apply to an HIView.
   */
  HIPositioning       position;
};
typedef struct HILayoutInfo             HILayoutInfo;
enum {
  kHILayoutInfoVersionZero      = 0
};

/*

const HILayoutInfo kHILayoutInfoNone = {
    kHILayoutInfoVersionZero,
    kHINoBinding,
    { { NULL, 0.0 }, { NULL, 0.0 } },
    { { NULL, kHILayoutPositionNone }, { NULL, kHILayoutPositionNone } } };

*/
/*
 *  HIViewGetLayoutInfo()
 *  
 *  Summary:
 *    Get the layout info of an HIView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose layout info is to be retreived.
 *    
 *    outLayoutInfo:
 *      A pointer to an HILayoutInfo record into which to copy the
 *      layout info of the HIView. The version field of this record
 *      must be valid or the call will fail.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetLayoutInfo(
  HIViewRef       inView,
  HILayoutInfo *  outLayoutInfo)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewSetLayoutInfo()
 *  
 *  Summary:
 *    Set the layout info of an HIView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose layout info is to be retreived.
 *    
 *    inLayoutInfo:
 *      A pointer to an HILayoutInfo record from which to copy the
 *      layout info for the HIView.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSetLayoutInfo(
  HIViewRef             inView,
  const HILayoutInfo *  inLayoutInfo)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewSuspendLayout()
 *  
 *  Summary:
 *    Suspends all layout handling for this layout and its children.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose layout handling is to be suspended.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewSuspendLayout(HIViewRef inView)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewResumeLayout()
 *  
 *  Summary:
 *    Resumes all layout handling for this layout and its children.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose layout handling is to be resumed.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewResumeLayout(HIViewRef inView)                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewIsLayoutActive()
 *  
 *  Summary:
 *    Tests the view to determine if layout is active or suspended.
 *    Note that this test does not determine whether or not the view
 *    has a valid layout, only whether or not the layout engine is
 *    active for the view.
 *  
 *  Discussion:
 *    The view's layout active state is also affected by the layout
 *    active state of its parents; if any parent view has inactive
 *    layout, this view is considered to have inactive layout as well.
 *    See HIViewIsLayoutLatentlyActive if latent layout active state is
 *    required.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose layout handling is to be tested.
 *  
 *  Result:
 *    True if the view would respond to any linked relative's changes,
 *    otherwise false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsLayoutActive(HIViewRef inView)                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewIsLayoutLatentlyActive()
 *  
 *  Summary:
 *    The view's layout active state is also affected by the layout
 *    active state of its parents; if any parent view has inactive
 *    layout, this view is considered to have inactive layout as well.
 *    HIViewIsLayoutLatentlyActive returns whether a view's layout is
 *    latently active, even if one of its parent's layouts is not.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose latent layout handling is to be tested.
 *  
 *  Result:
 *    True if the view would latently respond to any linked relative's
 *    changes, otherwise false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIViewIsLayoutLatentlyActive(HIViewRef inView)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewApplyLayout()
 *  
 *  Summary:
 *    Applies the current layout into to the specified view. Side
 *    bindings have no effect, but positioning and scaling will occur,
 *    in that order.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView whose layout info is to be applied.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewApplyLayout(HIViewRef inView)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*==============================================================================*/
/*  MISCELLANEOUS                                                               */
/*==============================================================================*/
/*
 *  HIViewGetWindow()
 *  
 *  Discussion:
 *    Returns a reference to the window a given view is bound to. If
 *    the view reference passed is invalid, or the view is not embedded
 *    into any window, NULL is returned.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to query.
 *  
 *  Result:
 *    A window reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
HIViewGetWindow(HIViewRef inView)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewFindByID()
 *  
 *  Discussion:
 *    Allows you to find a particular view by its ID. Currently, this
 *    call uses the ControlID type as its IDs.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inStartView:
 *      The view to start searching at.
 *    
 *    inID:
 *      The ID of the view you are looking for.
 *    
 *    outControl:
 *      Receives the control if found.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewFindByID(
  HIViewRef    inStartView,
  HIViewID     inID,
  HIViewRef *  outControl)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetAttributes()
 *  
 *  Discussion:
 *    Allows you to get the attributes of a view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to inspect.
 *    
 *    outAttrs:
 *      The attributes of the view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetAttributes(
  HIViewRef     inView,
  OptionBits *  outAttrs)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewChangeAttributes()
 *  
 *  Discussion:
 *    Allows you to change the attributes of a view. You can
 *    simultaneously set and clear attributes.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to muck with.
 *    
 *    inAttrsToSet:
 *      The attributes you wish to set.
 *    
 *    inAttrsToClear:
 *      The attributes you wish to clear.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewChangeAttributes(
  HIViewRef    inView,
  OptionBits   inAttrsToSet,
  OptionBits   inAttrsToClear)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewCreateOffscreenImage()
 *  
 *  Discussion:
 *    Creates an CGImageRef for the view passed in. The view and any
 *    children it has are rendered in the resultant image.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view you wish to create an image of.
 *    
 *    inOptions:
 *      Options. Currently you must pass 0.
 *    
 *    outFrame:
 *      The frame of the view within the resultant image. It is in the
 *      coordinate system of the image, where 0,0 is the top left
 *      corner of the image. This is so you can know exactly where the
 *      control lives in the image when the control draws outside its
 *      bounds for things such as shadows.
 *    
 *    outImage:
 *      The image of the view, including anything that would be drawn
 *      outside the view's frame.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewCreateOffscreenImage(
  HIViewRef     inView,
  OptionBits    inOptions,
  HIRect *      outFrame,        /* can be NULL */
  CGImageRef *  outImage)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewDrawCGImage()
 *  
 *  Discussion:
 *    Draws an image in the right direction for an HIView. This is
 *    functionally the same as CGContextDrawImage, but it flips the
 *    context appropriately so that the image is drawn correctly.
 *    Because HIViews have their origin at the top, left, you are
 *    really drawing upside-down, so if you were to use the CG image
 *    drawing, you'd see what I mean! This call attempts to insulate
 *    you from that fact.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inContext:
 *      The context to draw in.
 *    
 *    inBounds:
 *      The bounds to draw the image into.
 *    
 *    inImage:
 *      The image to draw.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewDrawCGImage(
  CGContextRef    inContext,
  const HIRect *  inBounds,
  CGImageRef      inImage)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIViewGetFeatures()
 *  
 *  Discussion:
 *    Returns the features for the current view. This only returns
 *    feature bits for the HIView space. Older Control Manager features
 *    such as kControlSupportsDataAccess are not returned.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to query
 *    
 *    outFeatures:
 *      On output, the features for the view.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewGetFeatures(
  HIViewRef         inView,
  HIViewFeatures *  outFeatures)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIViewChangeFeatures()
 *  
 *  Discussion:
 *    Allows you to change a view's features on the fly. Typically,
 *    this is up to the view itself to control. For example, it might
 *    decide that under some situations it is opaque and other others
 *    it is transparent. In general entities outside of the view itself
 *    should not call this function. The only exception might be UI
 *    building tools, where it would want to make sure a view always
 *    responds to clicks, for example, so it could override mouse
 *    tracking to drag items around.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to change
 *    
 *    inFeaturesToSet:
 *      The features to enable
 *    
 *    inFeaturesToClear:
 *      The features to disable
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIViewChangeFeatures(
  HIViewRef        inView,
  HIViewFeatures   inFeaturesToSet,
  HIViewFeatures   inFeaturesToClear)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  Summary:
 *    Constants for use with the HICreateTransformedCGImage API.
 */
enum {

  /*
   * No visual transform should be applied.
   */
  kHITransformNone              = 0x00,

  /*
   * The image should be transformed to use a disabled appearance. This
   * transform should not be combined with any other transform.
   */
  kHITransformDisabled          = 0x01,

  /*
   * The image should be transformed to use a selected appearance. This
   * transform should not be combined with any other transform.
   */
  kHITransformSelected          = 0x4000
};

/*
 *  HICreateTransformedCGImage()
 *  
 *  Summary:
 *    Creates a new CGImage with a standard selected or disabled
 *    appearance.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inImage:
 *      The original image.
 *    
 *    inTransform:
 *      The transform to apply to the image.
 *    
 *    outImage:
 *      The new image. This image should be released by the caller.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HICreateTransformedCGImage(
  CGImageRef    inImage,
  OptionBits    inTransform,
  CGImageRef *  outImage)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIViewGetEventTarget()
 *  
 *  Discussion:
 *    Returns the EventTargetRef for the specified view. Once you
 *    obtain this reference, you can send events to the target and
 *    install event handler on it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to return the target for.
 *  
 *  Result:
 *    An EventTargetRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern EventTargetRef 
HIViewGetEventTarget(HIViewRef inView)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*==============================================================================*/
/* HIGrowBoxView                                                                */
/*                                                                              */
/* The grow box view is a new view starting in Mac OS 10.2. It can be used in   */
/* both the new compositing mode, as well as the traditional control manager    */
/* mode. Like all new HIFoo views, this view is created invisibly. You must     */
/* show the view after creation if you want to, like, see it and stuff.         */
/*==============================================================================*/
/* The HIObject class ID for the HIGrowBoxView class. */
#define kHIGrowBoxViewClassID           CFSTR("com.apple.higrowboxview")
/* Control Kind*/
enum {
  kControlKindHIGrowBoxView     = 'grow'
};

/* Currently there is no direct creation API for the grow box, so you must use  */
/* HIObjectCreate if you wish to create one directly. Normally, a window will   */
/* create one for you, so you should generally never need to do this.           */
/*
 *  HIGrowBoxViewSetTransparent()
 *  
 *  Discussion:
 *    Sets a grow box view as transparent, meaning it will draw the
 *    grow box lines over any content below it. When not transparent,
 *    it's an opaque white square with the grow lines.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inGrowBoxView:
 *      The grow box view reference.
 *    
 *    inTransparent:
 *      Pass true to make the grow view use its transparent look, false
 *      to give it the opaque look.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIGrowBoxViewSetTransparent(
  HIViewRef   inGrowBoxView,
  Boolean     inTransparent)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIGrowBoxViewIsTransparent()
 *  
 *  Discussion:
 *    Returns true if a grow box view is set to be transparent.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inGrowBoxView:
 *      The grow box view reference.
 *  
 *  Result:
 *    A boolean result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIGrowBoxViewIsTransparent(HIViewRef inGrowBoxView)           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/*  HIScrollView                                                                */
/*                                                                              */
/* The scroll view is a new view starting in Mac OS 10.2. It can be used in     */
/* the new compositing mode ONLY due to the nature of how it works. Like all    */
/* new HIFoo views, this view is created invisibly. You must show the view      */
/* after creation if you want to, like, see it and stuff.                       */
/* The HIScrollView will set the frame of the contained view when its bounds    */
/* change, so it is not necessary to set up the layout of the embedded view.    */
/*                                                                              */
/* Using an HIScrollView requires a few steps:                                  */
/*                                                                              */
/* 1. Install your scrollable content view into the HIScrollView instance using */
/*    HIViewAddSubview.                                                         */
/*                                                                              */
/* 2. If the scrollable content view doesn't already handle the                 */
/*    kEventScrollableGetInfo and kEventScrollableScrollTo events, you must     */
/*    install handlers on your scrollable content view and handle those events  */
/*    manually. More details on those events can be found below.                */
/*                                                                              */
/* 3. If the scrollable content view doesn't already send out the               */
/*    kEventScrollableInfoChanged event to its parent view, you must send this  */
/*    event to the HIScrollView instance whenever your scrollable content       */
/*    view's size or origin changes. More details on this even can be found     */
/*    below.                                                                    */
/*==============================================================================*/
/* The HIObject class ID for the HIScrollView class. */
#define kHIScrollViewClassID            CFSTR("com.apple.HIScrollView")
/* Control Kind*/
enum {
  kControlKindHIScrollView      = 'scrl'
};

/*
    kEventClassScrollable quick reference:
    
    kEventScrollableGetInfo         = 1,
    kEventScrollableInfoChanged     = 2,
%%  kEventScrollableEmbedded        = 3,
%%  kEventScrollableRemoved         = 4,
    kEventScrollableScrollTo        = 10
*/
enum {
  kEventClassScrollable         = 'scrl'
};

enum {
  kEventParamImageSize          = 'imsz', /* typeHISize*/
  kEventParamViewSize           = 'vwsz', /* typeHISize*/
  kEventParamLineSize           = 'lnsz', /* typeHISize*/
  kEventParamOrigin             = 'orgn' /* typeHIPoint*/
};

/*
 *  kEventClassScrollable / kEventScrollableGetInfo
 *  
 *  Summary:
 *    Requests information from an HIScrollView’s scrollable view about
 *    its size and origin.
 *  
 *  Discussion:
 *    This event is sent by an HIScrollView to its scrollable view to
 *    determine the current size and origin of the scrollable view. A
 *    scrollable view must implement this event in order to scroll
 *    properly inside an HIScrollView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    <-- kEventParamImageSize (out, typeHISize)
 *          On exit, contains the size of the entire scrollable view.
 *    
 *    <-- kEventParamViewSize (out, typeHISize)
 *          On exit, contains the amount of the scrollable view that is
 *          visible.
 *    
 *    <-- kEventParamLineSize (out, typeHISize)
 *          On exit, contains the amount that should be scrolled in
 *          response to a single click on a scrollbar arrow.
 *    
 *    <-- kEventParamOrigin (out, typeHIPoint)
 *          On exit, contains the scrollable view’s current origin (the
 *          view-relative coordinate that is drawn at the top left
 *          corner of its frame). These coordinates should always be
 *          greater than or equal to zero. They should be less than or
 *          equal to the view’s image size minus its view size.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventScrollableGetInfo       = 1
};

/*
 *  kEventClassScrollable / kEventScrollableInfoChanged
 *  
 *  Summary:
 *    Notification that the size or origin of an HIScrollView’s
 *    scrollable view has changed.
 *  
 *  Discussion:
 *    This event is not sent by HIScrollView itself; rather, it may be
 *    sent to an instance of HIScrollView to notify the scroll view
 *    that the size or origin of its scrollable view have changed. The
 *    HIScrollView responds to this event by sending a
 *    kEventScrollableGetInfo to its scrollable view. It then updates
 *    the scroll bars appropriately to reflect the new reality of the
 *    scrollable view. It does NOT move the origin of the scrollable
 *    view at all. It is just a notification to allow the scroll view
 *    to sync up with its scrollable view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventScrollableInfoChanged   = 2
};

/*
 *  kEventClassScrollable / kEventScrollableScrollTo
 *  
 *  Summary:
 *    Requests that an HIScrollView’s scrollable view should scroll to
 *    a particular origin.
 *  
 *  Discussion:
 *    This event is sent by an HIScrollView to its scrollable view to
 *    request that the scrollable view update its current origin and
 *    redraw. Typically, a scrollable view will record its current
 *    origin in its own instance data; it should update the origin in
 *    response to this event. A scrollable view should also use either
 *    HIViewScrollRect to scroll its content, or HIViewSetNeedsDisplay
 *    to cause itself to redraw using the new origin point. A
 *    scrollable view must implement this event in order to scroll
 *    properly inside an HIScrollView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamOrigin (in, typeHIPoint)
 *          The new origin for the scrollable view. The origin
 *          coordinates will vary from (0,0) to scrollable view’s image
 *          size minus its view size.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventScrollableScrollTo      = 10
};


/*
 *  Summary:
 *    HIScrollView options
 */
enum {

  /*
   * This indicates that a vertical scroll bar is desired.
   */
  kHIScrollViewOptionsVertScroll = (1 << 0),

  /*
   * This indicates that a horizontal scroll bar is desired.
   */
  kHIScrollViewOptionsHorizScroll = (1 << 1),

  /*
   * This indicates that space for a grow box should be taken into
   * account when laying out scroll bars. On Mac OS X 10.3 and earlier,
   * if both the horizontal and vertical scroll bars are requested,
   * this attribute is assumed. On Mac OS X 10.4 and later, this
   * attribute is *NOT* assumed; this allows the scroll view to support
   * auto-hiding of the two scroll bars independently on Mac OS X 10.4
   * and later. If you want to preserve space for the grow box on all
   * systems, specify this option bit.
   */
  kHIScrollViewOptionsAllowGrow = (1 << 2),
  kHIScrollViewValidOptions     = (kHIScrollViewOptionsVertScroll | kHIScrollViewOptionsHorizScroll | kHIScrollViewOptionsAllowGrow)
};


/*
 *  HIScrollViewAction
 *  
 *  Summary:
 *    HIScrollView navigation actions. See HIScrollViewNavigate for
 *    more information.
 */
typedef UInt32 HIScrollViewAction;
enum {

  /*
   * The scroll view should move to the top of the content.
   */
  kHIScrollViewScrollToTop      = (1 << 0),

  /*
   * The scroll view should move to the bottom of the content.
   */
  kHIScrollViewScrollToBottom   = (1 << 1),

  /*
   * The scroll view should move to the left of the content.
   */
  kHIScrollViewScrollToLeft     = (1 << 2),

  /*
   * The scroll view should move to the right of the content.
   */
  kHIScrollViewScrollToRight    = (1 << 3),

  /*
   * The scroll view should page up.
   */
  kHIScrollViewPageUp           = (1 << 4),

  /*
   * The scroll view should page down.
   */
  kHIScrollViewPageDown         = (1 << 5),

  /*
   * The scroll view should page left.
   */
  kHIScrollViewPageLeft         = (1 << 6),

  /*
   * The scroll view should page right.
   */
  kHIScrollViewPageRight        = (1 << 7)
};

/*
 *  HIScrollViewCreate()
 *  
 *  Discussion:
 *    Creates a scroll view. This view has 3 parts, essentially. It can
 *    have one or two scroll bars (horizontal/vertical), and a view to
 *    be scrolled. The view to be scrolled is merely added via
 *    HIViewAddSubview. The scroll view will automatically connect it
 *    up appropriately. **** THIS MAY CHANGE
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options for our scroll view. You must specify either a
 *      horizontal or a vertical scroll bar. If neither is passed, an
 *      error is returned.
 *    
 *    outView:
 *      The new scroll view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIScrollViewCreate(
  OptionBits   inOptions,
  HIViewRef *  outView)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIScrollViewSetScrollBarAutoHide()
 *  
 *  Discussion:
 *    Sets a scroll view's scroll bars to auto-hide when the entire
 *    scrollable view it is managing can be fully displayed in its
 *    bounds. This is similar to the behavior you see in the Preview
 *    application.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to affect.
 *    
 *    inAutoHide:
 *      The new auto-hide setting (true == auto-hide).
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIScrollViewSetScrollBarAutoHide(
  HIViewRef   inView,
  Boolean     inAutoHide)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIScrollViewGetScrollBarAutoHide()
 *  
 *  Discussion:
 *    Gets a scroll view's current scroll bar auto-hide setting.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to examine.
 *  
 *  Result:
 *    A boolean result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIScrollViewGetScrollBarAutoHide(HIViewRef inView)            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIScrollViewNavigate()
 *  
 *  Discussion:
 *    Allows you to programmatically change what portion of a scroll
 *    view's target you are seeing. For example, you can move to the
 *    beginning or end of a document. You can also page up, down, left
 *    and right. In general, you should not call this from embedded
 *    content (i.e. the scrollable view inside the scroll view). For
 *    those cases, you should instead position yourself appropriately
 *    and tell the scroll view you changed via the
 *    kEventScrollableInfoChanged carbon event. This routine merely is
 *    a programmatic way to scroll as one would by hand using the
 *    scroll bars.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The scroll view to affect.
 *    
 *    inAction:
 *      The action to take.
 *  
 *  Result:
 *    A operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIScrollViewNavigate(
  HIViewRef            inView,
  HIScrollViewAction   inAction)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIScrollViewCanNavigate()
 *  
 *  Discussion:
 *    Allows you to tell whether it is currently possible to navigate
 *    somehow in a scroll view. For example, if a scroll view is
 *    already at the top of the scrollable content, it is not possible
 *    to navigate upward, so home and page up actions would not be
 *    possible. You might use this function to help you update the
 *    state of menu items or the like.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view to examine.
 *    
 *    inAction:
 *      The action to test.
 *  
 *  Result:
 *    A boolean result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIScrollViewCanNavigate(
  HIViewRef            inView,
  HIScrollViewAction   inAction)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*==============================================================================*/
/*  HIImageView                                                                 */
/*                                                                              */
/* The image view is a new view starting in Mac OS 10.2. It can only be used    */
/* in a compositing window. Like all new HIFoo views, this view is initially    */
/* invisible. You must show the view after creation.                            */
/*==============================================================================*/
/* The HIObject class ID for the HIImageView class. */
#define kHIImageViewClassID             CFSTR("com.apple.HIImageView")
/* ControlKind*/
enum {
  kControlKindHIImageView       = 'imag'
};

/*
 *  HIImageViewCreate()
 *  
 *  Discussion:
 *    Creates an image view. The view responds to the scrollable
 *    interface and can be used in a scrolling view. You can pass an
 *    image initially, or set one later.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inImage:
 *      An initial image, or NULL. You can set the image later via
 *      SetControlData.
 *    
 *    outControl:
 *      The new image view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIImageViewCreate(
  CGImageRef    inImage,          /* can be NULL */
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


enum {
  kHIImageViewImageTag          = 'imag' /* CGImageRef (THIS TAG IS GOING AWAY!!! USE THE APIS BELOW!)*/
};

/*
 *  HIImageViewSetOpaque()
 *  
 *  Discussion:
 *    Allows you to set whether an image view should be treated as
 *    opaque. If this is set to true, the image view can make certain
 *    optimizations for compositing and scrolling. The alpha-related
 *    image view APIs are rendered useless if opacity it set to true.
 *    An image view, when created, is transparent by default.
 *    
 *    NOTE: In Mac OS X 10.2, this control was documented as being
 *    opaque by default, but the implementation did not enforce that.
 *    So in Mac OS X 10.3 and beyond, the control is transparent by
 *    default, and you can make it opaque by calling
 *    HIImageViewSetOpaque.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to affect.
 *    
 *    inOpaque:
 *      The new opacity setting. Pass true to indicate you want the
 *      image to be treated as opaque.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIImageViewSetOpaque(
  HIViewRef   inView,
  Boolean     inOpaque)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewIsOpaque()
 *  
 *  Discussion:
 *    Allows you to determine whether an image view is opaque or not.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to query.
 *  
 *  Result:
 *    A boolean result, where true indicates the image view is opaque.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIImageViewIsOpaque(HIViewRef inView)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewSetAlpha()
 *  
 *  Discussion:
 *    Allows you to set the alpha for an image, making it more or less
 *    transparent. An alpha of 1.0 is fully opaque, and 0.0 is fully
 *    transparent. The default alpha for an image is 1.0.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to affect.
 *    
 *    inAlpha:
 *      The new alpha value.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIImageViewSetAlpha(
  HIViewRef   inView,
  float       inAlpha)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewGetAlpha()
 *  
 *  Discussion:
 *    Allows you to get the alpha for an image. An alpha of 1.0 is
 *    fully opaque, and 0.0 is fully transparent.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to query.
 *  
 *  Result:
 *    A floating point number representing the alpha from 0.0 through
 *    1.0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern float 
HIImageViewGetAlpha(HIViewRef inView)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewSetScaleToFit()
 *  
 *  Discussion:
 *    Normally an image view will clip to the view's bounds. Using this
 *    API, you can instead tell the image view to size the image to fit
 *    into the view bounds specified.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to affect.
 *    
 *    inScaleToFit:
 *      A boolean indicating whether the image should be scaled to fit
 *      the view bounds (true) or merely clip to the view bounds
 *      (false).
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIImageViewSetScaleToFit(
  HIViewRef   inView,
  Boolean     inScaleToFit)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewGetScaleToFit()
 *  
 *  Discussion:
 *    Returns whether or not an image view will scale the image it
 *    displays to the view bounds or merely clip to the view bounds. A
 *    true result means it scales.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to query.
 *  
 *  Result:
 *    A boolean result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIImageViewGetScaleToFit(HIViewRef inView)                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewSetImage()
 *  
 *  Discussion:
 *    Sets the image to display in an image view. The image passed in
 *    is retained by the view, so you may release the image after
 *    calling this API if you no longer need to reference it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to affect.
 *    
 *    inImage:
 *      The image to set.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIImageViewSetImage(
  HIViewRef    inView,
  CGImageRef   inImage)       /* can be NULL */               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIImageViewCopyImage()
 *  
 *  Discussion:
 *    Gets the image for an image view. If there is no image set on the
 *    view, or the view ref is invalid, NULL is returned. The image is
 *    retained, so you should take care to release it when you are
 *    finished with it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The image view to query.
 *  
 *  Result:
 *    A CoreGraphics (Quartz) image ref.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern CGImageRef 
HIImageViewCopyImage(HIViewRef inView)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==============================================================================*/
/* HIComboBox                                                                   */
/*                                                                              */
/* The combo box is a new view starting in Mac OS 10.2. It can be used in       */
/* both the new compositing mode, as well as the traditional control manager    */
/* mode. Like all new HIFoo views, this view is created invisible. You must     */
/* show the view after creation if you want to, like, see it and stuff.         */
/*==============================================================================*/
/* The HIObject class ID for the HIComboBox class. */
#define kHIComboBoxClassID              CFSTR("com.apple.HIComboBox")
/*
    kEventClassHIComboBox quick reference:
    
    kEventComboBoxListItemSelected  = 1
*/
enum {
  kEventClassHIComboBox         = 'hicb'
};

enum {
  kEventParamComboBoxListSelectedItemIndex = 'cbli'
};

/*
 *  kEventClassHIComboBox / kEventComboBoxListItemSelected
 *  
 *  Summary:
 *    Notification that an item in the ComboBox disclosure list has
 *    been selected.
 *  
 *  Discussion:
 *    This event is sent as a notification when an item in the ComboBox
 *    disclosure list has been selected.  This event is sent to all
 *    handlers installed on the control. This does not imply that the
 *    selection has been accepted; for that you will need to register
 *    for the kEventClassTextField/kEventTextAccepted event; you can
 *    register for that event in order to make live selections however.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeControlRef)
 *          The ComboBox view that has sent the notification.
 *    
 *    --> kEventParamComboBoxListSelectedItemIndex (in, typeCFIndex)
 *          The index of the combo box list item that has been selected.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventComboBoxListItemSelected = 1
};


/*
 *  Summary:
 *    ComboBox attributes
 */
enum {

  /*
   * A constant with value zero; the lack of any attributes.
   */
  kHIComboBoxNoAttributes       = 0L,

  /*
   * The control will attempt to auto complete the text the user is
   * typing with an item in the ComboBox list that is the closest
   * appropriate match.
   */
  kHIComboBoxAutoCompletionAttribute = (1L << 0),

  /*
   * The control will disclose the ComboBox list after the user enters
   * text.
   */
  kHIComboBoxAutoDisclosureAttribute = (1L << 1),

  /*
   * The items in the ComboBox list will be automatically sorted in
   * alphabetical order.
   */
  kHIComboBoxAutoSortAttribute  = (1L << 2),

  /*
   * The ComboBox list will be automatically sized to fit the Human
   * Interface Guidelines.
   */
  kHIComboBoxAutoSizeListAttribute = (1L << 3),

  /*
   * The minimum set of ComboBox attributes commonly used.
   */
  kHIComboBoxStandardAttributes = (kHIComboBoxAutoCompletionAttribute | kHIComboBoxAutoDisclosureAttribute | kHIComboBoxAutoSizeListAttribute)
};

/* ControlKind*/
enum {
  kControlKindHIComboBox        = 'cbbx'
};

/* ComboBox Part codes*/
enum {
  kHIComboBoxEditTextPart       = 5,
  kHIComboBoxDisclosurePart     = 28
};

/*
    The ComboBox view supports these tags previously defined for the EditUnicodeText control.
    These tags are available through Get/SetControlData with a ControlPartCode of kHIComboBoxEditTextPart:
    
        kControlFontStyleTag
        kControlEditTextFixedTextTag
        kControlEditTextTextTag
        kControlEditTextKeyFilterTag
        kControlEditTextValidationProcTag
        kControlEditUnicodeTextPostUpdateProcTag
        kControlEditTextSelectionTag
        kControlEditTextKeyScriptBehaviorTag
        kControlEditTextCharCount
        kControlEditTextCFStringTag
*/

/*
 *  Discussion:
 *    ComboBox ControlData tags available with Mac OS X 10.2 and later.
 */
enum {

  /*
   * Extract the contents of the ComboBox list as a CFArray. The
   * CFArray will be retained: if you get the array, you own it and
   * will be required to release it; if you set it the toolbox makes a
   * copy of it and you are free to release your reference.
   */
  kHIComboBoxListTag            = 'cbls', /* CFArrayRef; bumps the refCount on get/retains on set*/

  /*
   * The width of the ComboBox list. This can be customized. This
   * disables the autosize attribute.
   */
  kHIComboBoxListPixelWidthTag  = 'cblw', /* UInt32 */

  /*
   * The height of the ComboBox list. This can be customized. This
   * disables the autosize attribute.
   */
  kHIComboBoxListPixelHeightTag = 'cblh', /* UInt32*/

  /*
   * The number of visible items in the list. This can be customized.
   * This disables the autosize attribute.
   */
  kHIComboBoxNumVisibleItemsTag = 'cbni' /* UInt32*/
};

/*
 *  HIComboBoxCreate()
 *  
 *  Summary:
 *    Creates a combo box control. The new control is initially
 *    invisible.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    text:
 *      The default text in the editable portion of the control. Can be
 *      NULL.
 *    
 *    style:
 *      The font style of the both editable text and the text in the
 *      disclosure list. Can be NULL.
 *    
 *    list:
 *      The default values available in the disclosure list. Can be
 *      NULL.
 *    
 *    inAttributes:
 *      The default attributes of the combo box.
 *    
 *    outComboBox:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxCreate(
  const HIRect *               boundsRect,
  CFStringRef                  text,               /* can be NULL */
  const ControlFontStyleRec *  style,              /* can be NULL */
  CFArrayRef                   list,               /* can be NULL */
  OptionBits                   inAttributes,
  HIViewRef *                  outComboBox)                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxGetItemCount()
 *  
 *  Summary:
 *    Get the number of items in the combo box disclosure list.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box.
 *  
 *  Result:
 *    The number of items in the combo box disclosure list.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
HIComboBoxGetItemCount(HIViewRef inComboBox)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxInsertTextItemAtIndex()
 *  
 *  Summary:
 *    Inserts a CFString in the disclosure list
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box whose disclosure list the text will be inserted
 *      in.
 *    
 *    inIndex:
 *      The index that the text should be inserted in. If the index
 *      does not fall within the number of items in the combo box list,
 *      it will be appended to the end of the list.
 *    
 *    inText:
 *      The text item to be inserted in the combo box disclosure list.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxInsertTextItemAtIndex(
  HIViewRef     inComboBox,
  CFIndex       inIndex,
  CFStringRef   inText)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxAppendTextItem()
 *  
 *  Summary:
 *    Appends a text item to the combo box disclosure list.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box whose disclosure list the text will be appended
 *      to.
 *    
 *    inText:
 *      The text item to be appended to the combo box disclosure list.
 *    
 *    outIndex:
 *      On exit, the index of the new item. Can be NULL if the caller
 *      does not require this information.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxAppendTextItem(
  HIViewRef     inComboBox,
  CFStringRef   inText,
  CFIndex *     outIndex)         /* can be NULL */           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxCopyTextItemAtIndex()
 *  
 *  Summary:
 *    Copy the text from the combo box disclosure list
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box that contains the text item you would like to
 *      copy.
 *    
 *    inIndex:
 *      The index of the text item. Will return paramErr if the index
 *      is out of bounds of the combo box list.
 *    
 *    outString:
 *      A copy of the string at the given index. Remember this is now
 *      your copy that you will need to release.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxCopyTextItemAtIndex(
  HIViewRef      inComboBox,
  CFIndex        inIndex,
  CFStringRef *  outString)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxRemoveItemAtIndex()
 *  
 *  Summary:
 *    Remove an item from a combo box disclosure list.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box that contains the disclosure list that you would
 *      like to remove an item from.
 *    
 *    inIndex:
 *      The index of the item to remove.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxRemoveItemAtIndex(
  HIViewRef   inComboBox,
  CFIndex     inIndex)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxChangeAttributes()
 *  
 *  Summary:
 *    Change the attributes of a combo box
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box whose attributes you would like to change.
 *    
 *    inAttributesToSet:
 *      The attributes to set.
 *    
 *    inAttributesToClear:
 *      The attributes to clear.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxChangeAttributes(
  HIViewRef    inComboBox,
  OptionBits   inAttributesToSet,
  OptionBits   inAttributesToClear)                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxGetAttributes()
 *  
 *  Summary:
 *    Get the attributes of a combo box.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box whose attributes you would like to obtain.
 *    
 *    outAttributes:
 *      The attributes of the combo box.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxGetAttributes(
  HIViewRef     inComboBox,
  OptionBits *  outAttributes)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIComboBoxIsListVisible()
 *  
 *  Summary:
 *    Returns whether the combo box list is currently disclosed.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box whose list visibility you would like to obtain.
 *  
 *  Result:
 *    A boolean value indicating whether the combo box list is
 *    disclosed (true) or hidden (false).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIComboBoxIsListVisible(HIViewRef inComboBox)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIComboBoxSetListVisible()
 *  
 *  Summary:
 *    Hides or shows the combo box list.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inComboBox:
 *      The combo box whose list will be hidden or shown.
 *    
 *    inVisible:
 *      A boolean value indicating whether you wish to hide the list
 *      (false) or show the list (true).
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIComboBoxSetListVisible(
  HIViewRef   inComboBox,
  Boolean     inVisible)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*==============================================================================*/
/*  HISearchField                                                               */
/*                                                                              */
/*  HISearchField is a new view available in Mac OS X 10.3.                     */
/*  This view is designed to be used for applications that provide searching    */
/*  functionality. Visually, it is a standard text field optionally adorned     */
/*  with a search icon on the left and/or a cancel image on the right.          */
/*  When the user has accepted the text by pressing the return or enter key     */
/*  a Carbon Event of kEventClassTextField / kEventTextAccepted will be sent    */
/*  to the control. This will be the indication that the search should begin.   */
/*  This control will also respond to all the standard control tags that are    */
/*  used by the EditUnicodeText control.                                        */
/*==============================================================================*/
/* The HIObject class ID for the HISearchField class. */
#define kHISearchFieldClassID           CFSTR("com.apple.HISearchField")
/* ControlKind*/
enum {
  kControlKindHISearchField     = 'srfd'
};

/* HISearchField part codes*/
enum {
  kControlSearchFieldCancelPart = 30,
  kControlSearchFieldMenuPart   = 31
};

/*
    The SearchField view supports those tags previously defined for the EditUnicodeText control.
    These tags are available through Get/SetControlData with ControlPartCode of kControlEditTextPart:
        
        kControlFontStyleTag
        kControlEditTextFixedTextTag
        kControlEditTextTextTag
        kControlEditTextKeyFilterTag
        kControlEditTextValidationProcTag
        kControlEditUnicodeTextPostUpdateProcTag
        kControlEditTextSelectionTag
        kControlEditTextKeyScriptBehaviorTag
        kControlEditTextCharCount
        kControlEditTextCFStringTag
*/

/*
 *  Summary:
 *    HISearchField attributes
 */
enum {

  /*
   * A constant with value zero; the lack of any attributes.
   */
  kHISearchFieldNoAttributes    = 0,

  /*
   * This view contains the cancel icon in the text field.
   */
  kHISearchFieldAttributesCancel = (1 << 0),

  /*
   * This view contains the search icon in the text field. If a menu is
   * associated with the search field, this attribute is implicitly set
   * and the search icon will display with a menu disclosure badge.
   * Available in Mac OS X 10.4 and later.
   */
  kHISearchFieldAttributesSearchIcon = (1 << 1)
};

/* Event Classes*/
enum {
  kEventClassSearchField        = 'srfd'
};

/*
 *  kEventClassSearchField / kEventSearchFieldCancelClicked
 *  
 *  Summary:
 *    Notification that the cancel icon has been depressed.
 *  
 *  Discussion:
 *    This event is sent by the HISearchField view if the cancel icon
 *    is enabled (attribute of kHISearchFieldAtttributesCancel), and
 *    the cancel has been clicked.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeControlRef)
 *          The HISearchField that has sent the notification.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventSearchFieldCancelClicked = 1
};

/*
 *  kEventClassSearchField / kEventSearchFieldSearchClicked
 *  
 *  Summary:
 *    Notification that the search icon has been depressed.
 *  
 *  Discussion:
 *    This event is sent by the HISearchField view if the search icon
 *    is enabled (attribute of kHISearchFieldAttributesSearchIcon or a
 *    menu is associated with the search field), and the search icon
 *    has been clicked. If a menu is associated with the search field,
 *    the search field will handle the display and tracking of the menu
 *    by default. This event is sent to the search field only, it will
 *    not propagate.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeControlRef)
 *          The HISearchField that has sent the notification.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventSearchFieldSearchClicked = 2
};

/*
 *  HISearchFieldCreate()
 *  
 *  Summary:
 *    Creates a search field control. The new control is initially
 *    invisible.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inBounds:
 *      The initial bounds of the view. If this parameter is NULL, the
 *      view defaults to have empty bounds ( 0, 0, 0, 0 ).
 *    
 *    inAttributes:
 *      The initial attributes of the search field. Indicates whether
 *      the field should contain the cancel icon.
 *    
 *    inSearchMenu:
 *      The menu to be associated with this search field. If
 *      inSearchMenu is non-NULL, it will be retained by the search
 *      field and the search icon will be enabled in the left side of
 *      the text field. If this parameter is NULL, the view will not
 *      display the search icon in the left portion of the text field.
 *      You are expected to install handlers on this menu to handle the
 *      visual appearance of the menu (for example, to draw check marks
 *      or enable items when the menu receives the
 *      kEventMenuEnableItems Carbon Event), and to keep track of what
 *      action should be performed by associating HICommands with each
 *      menu item and installing a handler for the {
 *      kEventClassCommand, kEventCommandProcess } Carbon Event.
 *    
 *    inDescriptiveText:
 *      The text to be displayed in the text field when the field does
 *      not have focus and contains no user entered text. This is meant
 *      to be an indication of what the search criteria is. For
 *      example, you may wish to identify to the user that the search
 *      will cover the "Subject" or "Contents" of a selected range of
 *      items. If inDescriptiveText is non-NULL it will be retained by
 *      the search field.
 *    
 *    outRef:
 *      On exit, contains the new view.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldCreate(
  const HIRect *  inBounds,                /* can be NULL */
  OptionBits      inAttributes,
  MenuRef         inSearchMenu,            /* can be NULL */
  CFStringRef     inDescriptiveText,       /* can be NULL */
  HIViewRef *     outRef)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISearchFieldSetSearchMenu()
 *  
 *  Summary:
 *    Set the search menu associated with the view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSearchField:
 *      The search field to associate the search menu with.
 *    
 *    inSearchMenu:
 *      The menu to associate with the search field. If there is
 *      already a menu associated with the search field, that menu will
 *      be released. If inSearchMenu is non-NULL, it will be retained
 *      by the search field and the search icon will be enabled in the
 *      left side of the text field. You are expected to install
 *      handlers on this menu to handle the visual appearance of the
 *      menu (for example, to draw check marks or enable items when the
 *      menu receives the kEventMenuEnableItems Carbon Event), and to
 *      keep track of what action should be performed by associating
 *      HICommands with each menu item and installing a handler for the
 *      { kEventClassCommand, kEventCommandProcess } Carbon Event. If
 *      inSearchMenu is NULL, the search icon will be removed from the
 *      left side of the text field and no menu will be associated with
 *      this field.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldSetSearchMenu(
  HIViewRef   inSearchField,
  MenuRef     inSearchMenu)        /* can be NULL */          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISearchFieldGetSearchMenu()
 *  
 *  Summary:
 *    Get the menu that is associated with the search field
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSearchField:
 *      The search field you wish to retrieve the search menu from.
 *    
 *    outSearchMenu:
 *      On exit, will contain the menu that is associated with search
 *      field. The menu will _not_ be retained on output and this
 *      parameter cannot be NULL.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldGetSearchMenu(
  HIViewRef   inSearchField,
  MenuRef *   outSearchMenu)                                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISearchFieldChangeAttributes()
 *  
 *  Summary:
 *    Set the attributes for the given search field.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSearchField:
 *      The search field to change the attributes of.
 *    
 *    inAttributesToSet:
 *      The attributes to set.
 *    
 *    inAttributesToClear:
 *      The attributes to clear.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldChangeAttributes(
  HIViewRef    inSearchField,
  OptionBits   inAttributesToSet,
  OptionBits   inAttributesToClear)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISearchFieldGetAttributes()
 *  
 *  Summary:
 *    Returns the attributes of the search field.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSearchField:
 *      The search field to get the attributes of.
 *    
 *    outAttributes:
 *      On exit, will contain the attributes of the search field. This
 *      parameter cannot be NULL.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldGetAttributes(
  HIViewRef     inSearchField,
  OptionBits *  outAttributes)                                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISearchFieldSetDescriptiveText()
 *  
 *  Summary:
 *    Set the description of the search action of the search field.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSearchField:
 *      The search field to change the description of.
 *    
 *    inDescription:
 *      The new description for the search field. If the search field
 *      contains a description, it will be released. If inDescription
 *      is non-NULL, it will be retained by the search field. If it is
 *      NULL, no description will be associated with the search field.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldSetDescriptiveText(
  HIViewRef     inSearchField,
  CFStringRef   inDescription)       /* can be NULL */        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISearchFieldCopyDescriptiveText()
 *  
 *  Summary:
 *    Get the description that is associated with the search field.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSearchField:
 *      The search field you wish to retrieve the description from.
 *    
 *    outDescription:
 *      On exit, will contain the description that is associated with
 *      the search field. This parameter cannot be NULL. If there is no
 *      description associated with the search field, outDescription
 *      will be set to NULL. If there is a description, a CFStringRef
 *      will be created that contains the contents of the description.
 *      You posess ownership of this string and will need to release it
 *      when you no longer need it.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISearchFieldCopyDescriptiveText(
  HIViewRef      inSearchField,
  CFStringRef *  outDescription)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*==============================================================================*/
/*  Text field events                                                           */
/*                                                                              */
/*  A text field is the part of some controls that you can enter text into.     */
/*  A text field is common to the EditText, EditUnicodeText, ComboBox,          */
/*  HISearchField, and HITextView views. The kEventClassTextField event allows  */
/*  you to receive notifications when the text has been accepted by the user.   */
/*  For example, you can install a handler for a                                */
/*  kEventClassTextField / kEventTextAccepted event on a HISearchField view to  */
/*  receive a notification that the user has initiated a search by hitting the  */
/*  return or enter key. You can also filter the text that will replace a       */
/*  selection before the change has been made to either accept or reject the    */
/*  replacement.                                                                */
/*==============================================================================*/
/*
    kEventClassTextField quick reference:
    
    kEventTextAccepted              = 1,
    kEventTextShouldChangeInRange   = 2,
    kEventTextDidChange             = 3
*/
enum {
  kEventClassTextField          = 'txfd'
};

enum {
  kEventParamTextSelection      = 'txsl', /* typeCFRange*/
  kEventParamCandidateText      = 'tstx', /* typeCFStringRef*/
  kEventParamReplacementText    = 'trtx', /* typeCFStringRef*/
  kEventParamUnconfirmedRange   = 'tunr', /* typeCFRange*/
  kEventParamUnconfirmedText    = 'txun' /* typeCFStringRef*/
};

/*
 *  kEventClassTextField / kEventTextAccepted
 *  
 *  Summary:
 *    Notification that the text in a control's editable text field has
 *    been accepted.
 *  
 *  Discussion:
 *    This event is sent as a notification when the text contained in a
 *    control's editable text field has been accepted by the user. Text
 *    is accepted when the user presses return or enter on the keyboard
 *    for the EditUnicodeText, HIComboBox, and HISearchField controls,
 *    or when the text has changed in the field and the field loses
 *    focus for the EditUnicodeText, HIComboBox, HISearchField and
 *    HITextView controls. 
 *    
 *    This event is sent to the control containing the text field only,
 *    it will not propagate. It is sent to all handlers installed on
 *    the control containing the text field.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeControlRef)
 *          The editable text field that has sent the notification.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventTextAccepted            = 1
};

/*
 *  kEventClassTextField / kEventTextShouldChangeInRange
 *  
 *  Summary:
 *    Returns whether the text should be changed in editable text
 *    fields.
 *  
 *  Discussion:
 *    There are several editable text field views, such as the
 *    HIComboBox, HISearchField, HITextView, and EditUnicodeText
 *    controls. There are times when you may require fine-grained
 *    control over what text is inserted into the text field and either
 *    accept the changes, reject them or modify what is to be entered.
 *    This event is sent whenever the text is about to be modified in a
 *    text field, either by user input or in other scenarios such as a
 *    paste from the clipboard, spell-checking word correction, or Mac
 *    OS X Service operation. You can change what text is inserted by
 *    providing a replacement string as a parameter to this event. This
 *    event is only sent for Unicode text controls; it is not sent for
 *    the classic non-Unicode EditText control. 
 *    
 *    This event is not sent prior to programmatic modification of the
 *    text field contents using SetControlData. 
 *    
 *    This event is not sent while an active inline editing session is
 *    in progress. Once the inline text has been confirmed, this event
 *    will be sent prior to the confirmed text being inserted into the
 *    text field. If you need control over keystrokes during an inline
 *    editing session, you can use the kEventTextInputFilterText event.
 *    
 *    
 *    This event is sent to the control containing the text field only;
 *    it will not propagate.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamTextSelection (in, typeCFRange)
 *          The range of the selection that is about to be changed. The
 *          units of the selection are in the same units that are
 *          returned in a EditTextSelectionRec, when called with
 *          GetControlData using kControlEditTextSelectionTag.
 *    
 *    --> kEventParamCandidateText (in, typeCFStringRef)
 *          The text that is going to replace the selection. Note that
 *          this string was originally created with
 *          CFStringCreateWithCharactersNoCopy, and the original text
 *          has a limited lifespan. If for some reason you need to
 *          retain the text past the end of your event handler, you
 *          should extract the characters from the string with
 *          CFStringGetCharacters, and then store those characters or
 *          create a new CFString from them.
 *    
 *    <-- kEventParamReplacementText (out, typeCFStringRef)
 *          On output, can contain optional replacement text.
 *  
 *  Result:
 *    If noErr is returned from your handler and the
 *    kEventParamReplacementText parameter is added to the event, then
 *    the contents of that parameter, rather than the candidate text,
 *    will be added to the text field. 
 *    
 *    If noErr is returned from your handler and the
 *    kEventParamReplacementText parameter is _not_ added to the event,
 *    then the candidate text will be filtered out and no text will be
 *    entered in the text field. The current selection will be deleted,
 *    however. 
 *    
 *    If userCanceledErr is returned from your handler, then no text
 *    will be entered in the text field and the current selection will
 *    remain unchanged. Effectively, the editing operation will be
 *    ignored. 
 *    
 *    If eventNotHandledErr is returned from your handler, the contents
 *    of the kEventParamReplacementText parameter are ignored, and the
 *    candidate text will replace the selection. 
 *    
 *    Any other return value will result in the default behavior, as if
 *    eventNotHandledErr had been returned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventTextShouldChangeInRange = 2
};

/*
 *  kEventClassTextField / kEventTextDidChange
 *  
 *  Summary:
 *    Indicates that the contents of an editable text field have
 *    changed.
 *  
 *  Discussion:
 *    This event is sent by all of the Unicode-based editable text
 *    views: HIComboBox, HISearchField, HITextView and EditUnicodeText.
 *    This event is not sent for the classic non-Unicode EditText
 *    control. 
 *    
 *    Note that this event is sent after inline editing operations,
 *    such as pressing a dead key, or using a input method that creates
 *    an inline editing hole. Most clients of this event should ignore
 *    the event during inline editing, and only respond to changes to
 *    the text after inline editing completes. A client can check for
 *    the presence of the kEventParamUnconfirmedRange parameter to
 *    determine whether inline editing is currently active; if this
 *    parameter is present, the client may wish to ignore the event.
 *    
 *    
 *    This event is not sent after programmatic modification of the
 *    text field contents using SetControlData. 
 *    
 *    This event is sent only to the control containing the text field;
 *    it will not propagate. It is sent to all handlers registered for
 *    it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamUnconfirmedRange (in, typeCFRange)
 *          If the text field currently has an open inline hole, this
 *          parameter contains the range of text inside the hole. This
 *          parameter is optional and is only present during inline
 *          editing.
 *    
 *    --> kEventParamUnconfirmedText (in, typeCFStringRef)
 *          If the text field currently has an open inline hole, this
 *          parameter contains the non-confirmed text currently being
 *          edited inside the hole. This parameter is optional and is
 *          only present during inline editing. Note that this string
 *          was originally created with
 *          CFStringCreateWithCharactersNoCopy, and the original text
 *          has a limited lifespan. If for some reason you need to
 *          retain the text past the end of your event handler, you
 *          should extract the characters from the string with
 *          CFStringGetCharacters, and then store those characters or
 *          create a new CFString from them.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventTextDidChange           = 3
};

/*==============================================================================*/
/*  HIMenuView                                                                  */
/*                                                                              */
/*  HIMenuView and HIStandardMenuView are new views available in Mac OS X 10.3. */
/*  HIMenuView is intended for use as a base class for custom menu item views;  */
/*  it does not draw or handle events itself, but provides useful functionality */
/*  that all menu views need to implement. HIStandardMenuView is the standard   */
/*  HIView used by the Menu Manager to draw menu item content, beginning with   */
/*  Mac OS X 10.3. It can also be subclassed by custom menu item views.         */
/*  Both of these views are meant to be used only in compositing windows.       */
/*                                                                              */
/*  Because HIMenuView and HIStandardMenuView are not typically created         */
/*  directly by applications, no API is provided to create instances of these   */
/*  views. If you need to create an instance of either view, you can use        */
/*  HIObjectCreate.                                                             */
/*==============================================================================*/
/* the HIObject class ID for the HIMenuView class*/
#define kHIMenuViewClassID              CFSTR("com.apple.HIMenuView")
/* the HIObject class ID for the standard menu HIView class*/
#define kHIStandardMenuViewClassID      CFSTR("com.apple.HIStandardMenuView")
/* Control Kinds (only used in Mac OS X 10.4 and later)*/
enum {
  kControlKindHIMenuView        = 'menu',
  kControlKindHIStandardMenuView = 'smnu'
};

/*
    The kEventHIObjectInitialize event for HIMenuView and HIStandardMenuView is expected to contain
    the following parameters. Be sure to include these parameters in the init event if you create an
    instance of these views with HIObjectCreate.
    
    --> kEventParamMenuRef (in, typeMenuRef)
            The menu that the view should draw.
*/
/*
 *  kHIViewMenuContentID
 *  
 *  Summary:
 *    The HIViewID for the menu content view. The Menu Manager assigns
 *    this view ID to all menu content views.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern HIViewID kHIViewMenuContentID                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  HIMenuViewGetMenu()
 *  
 *  Summary:
 *    Returns the MenuRef that is associated with an HIView that is a
 *    subclass of HIMenuView.
 *  
 *  Discussion:
 *    An HIMenuView subclass might use this API to determine the menu
 *    that it should draw.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view whose menu to return.
 *  
 *  Result:
 *    The MenuRef associated with the HIView, or NULL if an HIView is
 *    passed that is not a subclass of HIMenuView.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern MenuRef 
HIMenuViewGetMenu(HIViewRef inView)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIMenuGetContentView()
 *  
 *  Summary:
 *    Returns the HIViewRef that will be used to draw menu content for
 *    this menu, if any.
 *  
 *  Discussion:
 *    If the content view has not yet been created, the Menu Manager
 *    will create the content view using the view class ID and
 *    initialization event associated with the menu. Note that the menu
 *    content view is not the same as the window content view; the menu
 *    content view is embedded inside the window content view. If the
 *    menu uses an MDEF instead of an HIView to draw its content, noErr
 *    is returned but the output HIViewRef is set to NULL.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu.
 *    
 *    inMenuType:
 *      The type of menu for which the menu content view should be
 *      returned. The same MenuRef may have multiple content views,
 *      depending on the menu type being displayed.
 *    
 *    outView:
 *      On exit, contains the view. May be set to NULL if the menu does
 *      not use an HIView to draw its content. The caller should not
 *      release this view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIMenuGetContentView(
  MenuRef         inMenu,
  ThemeMenuType   inMenuType,
  HIViewRef *     outView)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*==============================================================================*/
/*  HISegmentedView                                                             */
/*                                                                              */
/*  HISegmentedView is a new view available in Mac OS X 10.3.                   */
/*  Examples of the segmented view are the Finder's icon/column/list view       */
/*  switcher, and the back/forward buttons in Open panels.                      */
/*  The segmented view operates as a group of buttons, each of which can be     */
/*  configured with different behaviors and content.                            */
/*                                                                              */
/*  Accessibility Notes: Those of you who wish to customize the accessibility   */
/*  information provided for individual segments of the segmented view -- by    */
/*  handling various kEventClassAccessibility Carbon Events, by calling         */
/*  HIObjectSetAuxiliaryAccessibilityAttribute, etc. -- need to know how to     */
/*  interpret and/or build AXUIElementRefs that represent individual segments.  */
/*  The AXUIElement representing an individual segment will/must be constructed */
/*  using the segmented view's HIViewRef and the UInt64 identifier of the       */
/*  one-based index of the segment the element refers to. As usual, a UInt64    */
/*  identifier of zero represents the segmented view as a whole. You must       */
/*  neither interpret nor create segmented view elements whose identifiers are  */
/*  greater than the count of segments in the segmented view.                   */
/*==============================================================================*/
/* The HIObject class ID for the HISegmentedView class. */
#define kHISegmentedViewClassID         CFSTR("com.apple.HISegmentedView")
/* Control Kind*/
enum {
  kHISegmentedViewKind          = 'sgmt'
};

/*
 *  HISegmentedViewCreate()
 *  
 *  Summary:
 *    Creates a segmented view. This is the type of view you would use
 *    to implement the icon/column/list view switcher as seen in the
 *    Finder. After creating a segmented view, you need to set the
 *    number of segments via HISegmentedViewSetSegmentCount. Each
 *    segment can be configured independently with via the other
 *    HISegmentedView APIs. Changing the number of segments and
 *    configuring each segment will change the appearance of the
 *    segmented view. After you configure the view, you may want to
 *    call GetBestControlRect on the view and resize it so the content
 *    will fit optimally. The value of the whole segmented view
 *    corresponds to the index of the currently selected segment with
 *    the radio behavior. If you set the value of the whole segmented
 *    view to n via SetControl32BitValue, every radio-behavior segment
 *    will have its value set to zero except for the segment at index
 *    n; if segment n also has the radio behavior, it will have its
 *    value set to one. When a radio-behavior segment is clicked, the
 *    value of the whole segmented view will be set to the segment's
 *    index. The segmented view works in both compositing and
 *    non-compositing modes.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inBounds:
 *      The bounds of the view to be created. Can be NULL, in which
 *      case the view is created with CGRectZero bounds.
 *    
 *    outRef:
 *      A valid pointer to an HIViewRef. On successful completion of
 *      this routine, the destination HIViewRef will be filled with the
 *      HIViewRef of the newly created view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewCreate(
  const HIRect *  inBounds,       /* can be NULL */
  HIViewRef *     outRef)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentCount()
 *  
 *  Summary:
 *    Sets the number of segments for the segmented view. Any previous
 *    segments beyond the new count will have their content released.
 *    All new segments beyond the previous count be initialized with
 *    the most basic settings possible: Momentary, no attributes, zero
 *    value, enabled, no command, no label, no content, and
 *    auto-calculated content width. You should configure any new
 *    segments to match your needs.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view for which the content is to be set.
 *    
 *    inSegmentCount:
 *      A positive integer indicating how many segments the view is to
 *      have.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentCount(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentCount)                                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentCount()
 *  
 *  Summary:
 *    Get the number of segments in the segmented view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view for which the content is to be set.
 *  
 *  Result:
 *    A UInt32 indicating the number of segments in the segmented view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
HISegmentedViewGetSegmentCount(HIViewRef inSegmentedView)     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  Summary:
 *    HISegmentBehavior constants
 */
enum {

  /*
   * Pops back up after being pressed, just like a push button.
   */
  kHISegmentBehaviorMomentary   = 1,

  /*
   * Stays pressed until another segment with the radio behavior is
   * pressed. This makes the segment behave like a radio button. After
   * this segment is clicked, the segmented view's value will be
   * changed to this segment's one-based index.
   */
  kHISegmentBehaviorRadio       = 2,

  /*
   * Like a check box. When clicked, it toggles back and forth between
   * checked and unchecked states.
   */
  kHISegmentBehaviorToggles     = 3,

  /*
   * After being pressed, this type of segment stays pressed until you
   * programatically unpress it.
   */
  kHISegmentBehaviorSticky      = 4
};


typedef UInt32                          HISegmentBehavior;
/*
 *  HISegmentedViewSetSegmentBehavior()
 *  
 *  Summary:
 *    Changes the behavior of an individual segment of a segmented
 *    view. By default, a segment has the kHISegmentBehaviorMomentary
 *    behavior.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose behavior you
 *      want to change.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose behavior you want to
 *      change. This must be a non-zero value that is no higher than
 *      the segmented view's current segment count.
 *    
 *    inBehavior:
 *      A HISegmentBehavior describing the behavior you wish the
 *      segment to have.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentBehavior(
  HIViewRef           inSegmentedView,
  UInt32              inSegmentIndexOneBased,
  HISegmentBehavior   inBehavior)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentBehavior()
 *  
 *  Summary:
 *    Returns the behavior of an individual segment of a segmented view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose behavior you desire.
 *      This must be a non-zero value that is no higher than the
 *      segmented view's current segment count.
 *  
 *  Result:
 *    A HISegmentBehavior describing the behavior of the given segment.
 *    If you pass an illegal segment index, the result is undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern HISegmentBehavior 
HISegmentedViewGetSegmentBehavior(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  Summary:
 *    HISegmentedView segment attributes
 *  
 *  Discussion:
 *    These attribute bits are for use with
 *    HISegmentedViewChangeSegmentAttributes and
 *    HISegmentedViewGetSegmentAttributes.
 */
enum {

  /*
   * Pass this to indicate no attributes at all.
   */
  kHISegmentNoAttributes        = 0,

  /*
   * If this attribute bit is set, the command that gets sent out when
   * the segment is clicked will be directed at the user focus instead
   * of up the segmented view's containment hierarchy.
   */
  kHISegmentSendCmdToUserFocus  = (1 << 0)
};

/*
 *  HISegmentedViewChangeSegmentAttributes()
 *  
 *  Summary:
 *    Changes the attributes of an individual segment of a segmented
 *    view. By default, a segment has no attribute bits set.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose attributes you
 *      want to change.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose attributes you want to
 *      change. This must be a non-zero value that is no higher than
 *      the segmented view's current segment count.
 *    
 *    inAttributesToSet:
 *      The attribute bits you wish to set/enable for the segment.
 *    
 *    inAttributesToClear:
 *      The attribute bits you wish to clear/disable for the segment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewChangeSegmentAttributes(
  HIViewRef    inSegmentedView,
  UInt32       inSegmentIndexOneBased,
  OptionBits   inAttributesToSet,
  OptionBits   inAttributesToClear)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentAttributes()
 *  
 *  Summary:
 *    Returns the attributes of an individual segment of a segmented
 *    view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose attributes you desire.
 *      This must be a non-zero value that is no higher than the
 *      segmented view's current segment count.
 *  
 *  Result:
 *    The attribute bits that are set/enabled for the given segment. If
 *    you pass an illegal segment index, the result is undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OptionBits 
HISegmentedViewGetSegmentAttributes(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentValue()
 *  
 *  Summary:
 *    Change the value of an individual segment of a segmented view.
 *    This is only meaningful for segments with the sticky, toggles, or
 *    radio behaviors. If you set the value of momentary segments to
 *    something other than zero, the behavior is undefined.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose value you want
 *      to change.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose value you want to
 *      change. This must be a non-zero value that is no higher than
 *      the segmented view's current segment count.
 *    
 *    inValue:
 *      The value you wish the segment to have. Zero means
 *      unpressed/unselected and one means pressed/selected. Other
 *      values will result in undefined behavior.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentValue(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased,
  SInt32      inValue)                                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentValue()
 *  
 *  Summary:
 *    Determine the value of an individual segment of a segmented view.
 *    This is only meaningful for segments with the sticky, toggles, or
 *    radio behaviors. The value of a momentary segment is undefined.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose value you desire. This
 *      must be a non-zero value that is no higher than the segmented
 *      view's current segment count.
 *  
 *  Result:
 *    A SInt32 indicating the value of the given segment. If you pass
 *    an illegal segment index, the result is undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern SInt32 
HISegmentedViewGetSegmentValue(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentEnabled()
 *  
 *  Summary:
 *    Enable or disable an individual segment of a segmented view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment to enable or disable.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to disable or enable. This
 *      must be a non-zero value that is no higher than the segmented
 *      view's current segment count.
 *    
 *    inEnabled:
 *      A Boolean indicating whether the segment is to become enabled
 *      or disabled.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentEnabled(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased,
  Boolean     inEnabled)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewIsSegmentEnabled()
 *  
 *  Summary:
 *    Test an individual segment of a segmented view to see if it is
 *    enabled or disabled.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to test. This must be a
 *      non-zero value that is no higher than the segmented view's
 *      current segment count.
 *  
 *  Result:
 *    True if the segment is enabled or false if the segment is
 *    disabled. If you pass an illegal segment index, the result is
 *    undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HISegmentedViewIsSegmentEnabled(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentCommand()
 *  
 *  Summary:
 *    Set the command ID for the given segment. By default, the command
 *    is zero. If you set any non-zero command ID, the segmented view
 *    will send an HICommand whenever the segment is clicked. By
 *    default, the command is sent to the segmented view and up the
 *    containment hierarchy. You can request that the command start at
 *    the user focus instead by turning on the
 *    kHISegmentSendCmdToUserFocus attribute for the segment.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose command you
 *      wish to set.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose command you wish to
 *      set. This must be a non-zero value that is no higher than the
 *      segmented view's current segment count.
 *    
 *    inCommand:
 *      The command ID you wish to associate with the segment. A value
 *      of zero signifies "no command".
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentCommand(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased,
  UInt32      inCommand)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentCommand()
 *  
 *  Summary:
 *    Get the command ID associated with the given segment.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to query. This must be a
 *      non-zero value that is no higher than the segmented view's
 *      current segment count.
 *  
 *  Result:
 *    Returns the command ID associated with the segment. If you pass
 *    an illegal segment index, the result is undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
HISegmentedViewGetSegmentCommand(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentLabel()
 *  
 *  Summary:
 *    Set the label string for the given segment. By default, a segment
 *    has no label string.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose label you wish
 *      to set.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose label you wish to set.
 *      This must be a non-zero value that is no higher than the
 *      segmented view's current segment count.
 *    
 *    inLabel:
 *      A CFStringRef with the text of the label. The segmented view
 *      will copy the string passed in. You may pass NULL or an empty
 *      CFStringRef if you wish to eliminate the label from the segment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentLabel(
  HIViewRef     inSegmentedView,
  UInt32        inSegmentIndexOneBased,
  CFStringRef   inLabel)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewCopySegmentLabel()
 *  
 *  Summary:
 *    Get the label associated with the given segment.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to query. This must be a
 *      non-zero value that is no higher than the segmented view's
 *      current segment count.
 *    
 *    outLabel:
 *      On exit, outLabel will be a copy of the label associated with
 *      the segment; you must release this string. If there is no label
 *      associated with the segment, outLabel will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewCopySegmentLabel(
  HIViewRef      inSegmentedView,
  UInt32         inSegmentIndexOneBased,
  CFStringRef *  outLabel)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentContentWidth()
 *  
 *  Summary:
 *    Sets whether you want the segment to automatically calculate its
 *    own width or whether you want to determine the segment's width
 *    manually. The content width is the horizontal area taken up by a
 *    segment's label and/or image.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose content width
 *      you wish to set.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose content width you wish
 *      to set. This must be a non-zero value that is no higher than
 *      the segmented view's current segment count.
 *    
 *    inAutoCalculateWidth:
 *      A Boolean indicating whether you want the segment to calculate
 *      its own width. If you pass true, the inWidth parameter is
 *      ignored.
 *    
 *    inWidth:
 *      If you passed false in inAutoCalculateWidth, this parameter
 *      specifies the width you want to manually associate with the
 *      segment. If you pass a negative width, the behavior is
 *      undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentContentWidth(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased,
  Boolean     inAutoCalculateWidth,
  float       inWidth)                                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentContentWidth()
 *  
 *  Summary:
 *    Get the content width of the given segment. This also optionall
 *    passes back a Boolean indicating whether the width was
 *    automatically calculated. The content width is the horizontal
 *    area taken up by a segment's label and/or image.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to query. This must be a
 *      non-zero value that is no higher than the segmented view's
 *      current segment count.
 *    
 *    outAutoCalculated:
 *      On exit, this is a Boolean indicating whether the width was
 *      automatically calculated. You may pass NULL if you don't need
 *      this information.
 *  
 *  Result:
 *    Returns the width of the content for the given segment. If you
 *    pass an illegal segment index, the result is undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern float 
HISegmentedViewGetSegmentContentWidth(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased,
  Boolean *   outAutoCalculated)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewSetSegmentImage()
 *  
 *  Summary:
 *    Sets or clears the image associated with a given segment.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment whose image you wish
 *      to set.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment whose image you wish to set.
 *      This must be a non-zero value that is no higher than the
 *      segmented view's current segment count.
 *    
 *    inImage:
 *      An HIViewImageContentInfo structure with the image information
 *      for the given segment. Segments only support three types of
 *      image content: kControlNoContent (no image),
 *      kControlContentIconRef, and kControlContentCGImageRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewSetSegmentImage(
  HIViewRef                       inSegmentedView,
  UInt32                          inSegmentIndexOneBased,
  const HIViewImageContentInfo *  inImage)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewGetSegmentImageContentType()
 *  
 *  Summary:
 *    Get the type of image content drawn by the given segment. You
 *    will need to call this before calling
 *    HISegmentedViewCopySegmentImage so you know what type of image
 *    content to request from the latter API.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to query. This must be a
 *      non-zero value that is no higher than the segmented view's
 *      current segment count.
 *  
 *  Result:
 *    Returns the image content type of the image drawn by the given
 *    segment. If you pass an illegal segment index, the result is
 *    undefined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern HIViewImageContentType 
HISegmentedViewGetSegmentImageContentType(
  HIViewRef   inSegmentedView,
  UInt32      inSegmentIndexOneBased)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HISegmentedViewCopySegmentImage()
 *  
 *  Summary:
 *    Gives you a copy of the image (if any) drawn by the given
 *    segment. You are responsible for releasing any image passed back
 *    by this function. You request the image by asking for a
 *    particular type of image. If the segment isn't using the
 *    requested type of image, an error will be returned. If you wish
 *    to know the actual type of image displayed by the segment, you
 *    can call HISegmentedViewGetSegmentImageContentType.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inSegmentedView:
 *      The segmented view which owns the segment being queried.
 *    
 *    inSegmentIndexOneBased:
 *      The one-based index of the segment to query. This must be a
 *      non-zero value that is no higher than the segmented view's
 *      current segment count.
 *    
 *    ioImage:
 *      On entry, you must fill out the contentType field of this
 *      structure with the type of image you desire. On exit, if that
 *      type of image is used by the segment, the appropriate field of
 *      the union will be filled in with a copy of the image. You are
 *      responsible for releasing the image.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HISegmentedViewCopySegmentImage(
  HIViewRef                 inSegmentedView,
  UInt32                    inSegmentIndexOneBased,
  HIViewImageContentInfo *  ioImage)                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*==============================================================================*/
/*  Clock view events                                                           */
/*==============================================================================*/
enum {
  kEventClassClockView          = 'cloc'
};

/*
 *  kEventClassClockView / kEventClockDateOrTimeChanged
 *  
 *  Summary:
 *    Allows clients to determine when the user has changed the date or
 *    time in the clock control.
 *  
 *  Discussion:
 *    This event is sent by the clock control when the user has changed
 *    the date or time. Clients could register for this notification in
 *    order to update some state based on the date or time in the
 *    clock, for instance. This event is sent to the view only, it will
 *    not propagate. It is sent to all handlers installed on the
 *    control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeControlRef)
 *          The view whose date has changed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventClockDateOrTimeChanged  = 1
};



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __HIVIEW__ */

