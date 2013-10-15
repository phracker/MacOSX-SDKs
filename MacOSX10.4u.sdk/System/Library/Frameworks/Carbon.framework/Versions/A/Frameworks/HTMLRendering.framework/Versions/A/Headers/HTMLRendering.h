/*
     File:       HTMLRendering/HTMLRendering.h
 
     Contains:   HTML Rendering Library Interfaces.
 
     Version:    HTMLRenderingLib-66.1~1791
 
     Copyright:  © 1999-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*
    HTMLRenderingLib has been deprecated. Please use WebKit instead for your OS X Carbon web widget needs.
 */
#ifndef __HTMLRENDERING__
#define __HTMLRENDERING__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
#endif

#ifndef __HITOOLBOX__
#include <HIToolbox/HIToolbox.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpaqueHRReference*       HRReference;
/*
 *  HRGetHTMLRenderingLibVersion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetHTMLRenderingLibVersion(NumVersion * returnVers)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#if TARGET_RT_MAC_CFM
#ifdef __cplusplus
    inline pascal Boolean HRHTMLRenderingLibAvailable() { return ((HRGetHTMLRenderingLibVersion != (void*)kUnresolvedCFragSymbolAddress) ); }
#else
    #define HRHTMLRenderingLibAvailable()   ((HRGetHTMLRenderingLibVersion != (void*)kUnresolvedCFragSymbolAddress) )
#endif
#elif TARGET_RT_MAC_MACHO
#ifdef __cplusplus
    inline pascal Boolean HRHTMLRenderingLibAvailable() { return true; }
#else
    #define HRHTMLRenderingLibAvailable()   (true)
#endif
#endif  /*  */

enum {
  kHRRendererHTML32Type         = 'ht32' /* HTML 3.2 */
};


/*
 *  HRNewReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRNewReference(
  HRReference *  hrRef,
  OSType         rendererType,
  GrafPtr        grafPtr)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRNewReferenceInWindow()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use this API from  a Carbon App. All the contrrols created by the
 *    HTML renderer will be embedded in the root control of the window
 *    specified by the window ref.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Pointer to the new reference created and returned by the
 *      renderer.
 *    
 *    rendererType:
 *      Type of the renderer e.g. kHRRendererHTML32Type. Only this type
 *      is supported for now.
 *    
 *    inWindowRef:
 *      Reference to the window for which rendering area will be
 *      specified.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRNewReferenceInWindow(
  HRReference *  hrRef,
  OSType         rendererType,
  WindowRef      inWindowRef)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRDisposeReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRDisposeReference(HRReference hrRef)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  HRFreeMemory()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern SInt32 
HRFreeMemory(Size inBytesNeeded)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/* System level notifications */
/*
 *  HRScreenConfigurationChanged()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRScreenConfigurationChanged(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRIsHREvent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern Boolean 
HRIsHREvent(const EventRecord * eventRecord)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/* Drawing */
/*
 *  HRSetGrafPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRSetGrafPtr(
  HRReference   hrRef,
  GrafPtr       grafPtr)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRSetWindowRef()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use this API from  a Carbon App. All the contrrols created by the
 *    HTML renderer will be moved in the root control of the window
 *    specified by the window ref. All the drawing will now happen in
 *    the specified window.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    windowRef:
 *      new Reference to the window to be attached to the above hrRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRSetWindowRef(
  HRReference   hrRef,
  WindowRef     windowRef)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRSetEmbeddingControl()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use this API to tell the HTML Renderer to embed all the controls
 *    it has created so far and the new controls it creates after this
 *    call to be embedded in the given control. Useful if you wish to
 *    have an HTML displayed with in your dialog. e.g. Software Update
 *    needs this.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    controlRef:
 *      all the future controls created by renderer are embeded in this
 *      controlRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRSetEmbeddingControl(
  HRReference   hrRef,
  ControlRef    controlRef)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRActivate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRActivate(HRReference hrRef)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRDeactivate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRDeactivate(HRReference hrRef)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRDraw()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRDraw(
  HRReference   hrRef,
  RgnHandle     updateRgnH)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRDrawInPort()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use this API from  a Carbon App.  All the drawing will now happen
 *    in the specified port. This is the API you want to use to draw in
 *    an offscreen port, for example when printing. You could also use
 *    this API to draw in an on screen port.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    updateRgnH:
 *      Region to be updated.
 *    
 *    grafPtr:
 *      A graf pointer to render HTML into.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRDrawInPort(
  HRReference   hrRef,
  RgnHandle     updateRgnH,
  CGrafPtr      grafPtr)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRSetRenderingRect()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRSetRenderingRect(
  HRReference   hrRef,
  const Rect *  renderingRect)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetRenderedImageSize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetRenderedImageSize(
  HRReference   hrRef,
  Point *       renderingSize)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetRenderedImageSize32()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use this API when the rendered image could have coordinates
 *    larger than what SInt16 can hold.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    height:
 *      Height of the image is returned in this parameter.
 *    
 *    width:
 *      Width of the image is returned in this parameter.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGetRenderedImageSize32(
  HRReference   hrRef,
  UInt32 *      height,
  UInt32 *      width)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRScrollToLocation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRScrollToLocation(
  HRReference   hrRef,
  Point *       location)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRScrollToImageLocation32()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use this API when specifying location to scroll to. Location is
 *    specified in image space.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    h:
 *      Horizontal location.
 *    
 *    v:
 *      Vertical location.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRScrollToImageLocation32(
  HRReference   hrRef,
  SInt32        h,
  SInt32        v)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRForceQuickdraw()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRForceQuickdraw(
  HRReference   hrRef,
  Boolean       forceQuickdraw)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


typedef SInt16 HRScrollbarState;
enum {
  eHRScrollbarOn                = 0,
  eHRScrollbarOff               = 1,
  eHRScrollbarAuto              = 2
};

/*
 *  HRSetScrollbarState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRSetScrollbarState(
  HRReference        hrRef,
  HRScrollbarState   hScrollbarState,
  HRScrollbarState   vScrollbarState)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRSetDrawBorder()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRSetDrawBorder(
  HRReference   hrRef,
  Boolean       drawBorder)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRSetGrowboxCutout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRSetGrowboxCutout(
  HRReference   hrRef,
  Boolean       allowCutout)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Navigation */
/*
 *  HRGoToFile()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGoToFile(
  HRReference     hrRef,
  const FSSpec *  fsspec,
  Boolean         addToHistory,
  Boolean         forceRefresh)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToURL()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGoToURL(
  HRReference   hrRef,
  const char *  url,
  Boolean       addToHistory,
  Boolean       forceRefresh)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToAnchor()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGoToAnchor(
  HRReference   hrRef,
  const char *  anchorName)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGoToPtr(
  HRReference   hrRef,
  char *        buffer,
  UInt32        bufferSize,
  Boolean       addToHistory,
  Boolean       forceRefresh)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToFSRef()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGoToFile,
 *    HRGoToURL, HRGoToAnchor and HRGoToPtr. These APIs are same in
 *    behavior with their old counter parts. The only difference is
 *    that they take FSRef, CFURLRef, CFString, and CFData as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    fref:
 *      Reference to HTML file that is be opened and rendered.
 *    
 *    addToHistory:
 *      true if this file URL should be added to history.
 *    
 *    forceRefresh:
 *      true if the rendering area should be refreshed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGoToFSRef(
  HRReference    hrRef,
  const FSRef *  fref,
  Boolean        addToHistory,
  Boolean        forceRefresh)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToCFURL()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGoToFile,
 *    HRGoToURL, HRGoToAnchor and HRGoToPtr. These APIs are same in
 *    behavior with their old counter parts. The only difference is
 *    that they take FSRef, CFURLRef, CFString, and CFData as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    url:
 *      Reference to url that is be rendered.
 *    
 *    addToHistory:
 *      true if this URL should be added to history.
 *    
 *    forceRefresh:
 *      true if the rendering area should be refreshed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGoToCFURL(
  HRReference   hrRef,
  CFURLRef      url,
  Boolean       addToHistory,
  Boolean       forceRefresh)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToAnchorCFString()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGoToFile,
 *    HRGoToURL, HRGoToAnchor and HRGoToPtr. These APIs are same in
 *    behavior with their old counter parts. The only difference is
 *    that they take FSRef, CFURLRef, CFString, and CFData as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    anchorName:
 *      Name of the anchor to be displayed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGoToAnchorCFString(
  HRReference   hrRef,
  CFStringRef   anchorName)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGoToData()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGoToFile,
 *    HRGoToURL, HRGoToAnchor and HRGoToPtr. These APIs are same in
 *    behavior with their old counter parts. The only difference is
 *    that they take FSRef, CFURLRef, CFString, and CFData as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    data:
 *      Reference to data in the memory that is be rendered.
 *    
 *    addToHistory:
 *      true if this file URL should be added to history.
 *    
 *    forceRefresh:
 *      true if the rendering area should be refreshed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGoToData(
  HRReference   hrRef,
  CFDataRef     data,
  Boolean       addToHistory,
  Boolean       forceRefresh)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Accessors */
/* either file url or url of <base> tag */
/*
 *  HRGetRootURL()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetRootURL(
  HRReference   hrRef,
  Handle        rootURLH)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* url of <base> tag */
/*
 *  HRGetBaseURL()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetBaseURL(
  HRReference   hrRef,
  Handle        baseURLH)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* file url */
/*
 *  HRGetHTMLURL()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetHTMLURL(
  HRReference   hrRef,
  Handle        HTMLURLH)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetTitle()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetTitle(
  HRReference   hrRef,
  StringPtr     title)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetHTMLFile()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRGetHTMLFile(
  HRReference   hrRef,
  FSSpec *      fsspec)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  HRGetRootURLAsCFString()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGetRootURL,
 *    HRGetBaseURL, HRGetHTMLURL, HRGetTitle and HRGetHTMLFile. These
 *    APIs are same in behavior with their old counter parts. The only
 *    difference is that they take CFString, CFURLRef, and FSRef as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    rootString:
 *      Get CFString equivalent for the root url.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGetRootURLAsCFString(
  HRReference    hrRef,
  CFStringRef *  rootString)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetBaseURLAsCFString()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGetRootURL,
 *    HRGetBaseURL, HRGetHTMLURL, HRGetTitle and HRGetHTMLFile. These
 *    APIs are same in behavior with their old counter parts. The only
 *    difference is that they take CFString, CFURLRef, and FSRef as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    baseString:
 *      Get CFString equivalent for the base url.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGetBaseURLAsCFString(
  HRReference    hrRef,
  CFStringRef *  baseString)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetHTMLURLAsCFURL()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGetRootURL,
 *    HRGetBaseURL, HRGetHTMLURL, HRGetTitle and HRGetHTMLFile. These
 *    APIs are same in behavior with their old counter parts. The only
 *    difference is that they take CFString, CFURLRef, and FSRef as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    theURL:
 *      Get currently displayed HTML as a CFURL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGetHTMLURLAsCFURL(
  HRReference   hrRef,
  CFURLRef *    theURL)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetTitleAsCFString()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGetRootURL,
 *    HRGetBaseURL, HRGetHTMLURL, HRGetTitle and HRGetHTMLFile. These
 *    APIs are same in behavior with their old counter parts. The only
 *    difference is that they take CFString, CFURLRef, and FSRef as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    title:
 *      Get title of the currently displayed HTML as a CFString.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGetTitleAsCFString(
  HRReference    hrRef,
  CFStringRef *  title)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRGetHTMLFileAsFSRef()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using HRGetRootURL,
 *    HRGetBaseURL, HRGetHTMLURL, HRGetTitle and HRGetHTMLFile. These
 *    APIs are same in behavior with their old counter parts. The only
 *    difference is that they take CFString, CFURLRef, and FSRef as
 *    parameters.
 *  
 *  Parameters:
 *    
 *    hrRef:
 *      Reference to the renderer object.
 *    
 *    fref:
 *      Get currently displayed HTML as a FSRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRGetHTMLFileAsFSRef(
  HRReference   hrRef,
  FSRef *       fref)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Utilities */
/*
 *  HRUtilCreateFullURL()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRUtilCreateFullURL(
  const char *  rootURL,
  const char *  linkURL,
  Handle        fullURLH)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUtilGetFSSpecFromURL()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRUtilGetFSSpecFromURL(
  const char *  rootURL,
  const char *  linkURL,
  FSSpec *      destSpec)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* urlHandle should be valid on input */
/*
 *  HRUtilGetURLFromFSSpec()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern OSStatus 
HRUtilGetURLFromFSSpec(
  const FSSpec *  fsspec,
  Handle          urlHandle)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  HRUtilCreateFullCFURL()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using
 *    HRUtilCreateFullURL, HRUtilGetFSSpecFromURL,
 *    HRUtilGetURLFromFSSpec. These APIs are same in behavior with
 *    their old counter parts. The only difference is that they take
 *    CFURLRef, and FSRef as parameters.
 *  
 *  Parameters:
 *    
 *    rootString:
 *      a CFString for the root.
 *    
 *    linkString:
 *      a CFString for a partial link.
 *    
 *    url:
 *      Fully qualified URL is returned after attaching a link string
 *      to the root.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRUtilCreateFullCFURL(
  CFStringRef   rootString,
  CFStringRef   linkString,
  CFURLRef *    url)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUtilGetFSRefFromURL()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using
 *    HRUtilCreateFullURL, HRUtilGetFSSpecFromURL,
 *    HRUtilGetURLFromFSSpec. These APIs are same in behavior with
 *    their old counter parts. The only difference is that they take
 *    CFURLRef, and FSRef as parameters.
 *  
 *  Parameters:
 *    
 *    rootString:
 *      a CFString for the root.
 *    
 *    linkString:
 *      a CFString for a partial link.
 *    
 *    destRef:
 *      File reference is returned for the complete path created after
 *      attaching link string to the root. If File does not exist,
 *      fnfErr is returned as a function result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRUtilGetFSRefFromURL(
  CFStringRef   rootString,
  CFStringRef   linkString,
  FSRef *       destRef)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUtilGetURLFromFSRef()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use these API from  a Carbon App instead of using
 *    HRUtilCreateFullURL, HRUtilGetFSSpecFromURL,
 *    HRUtilGetURLFromFSSpec. These APIs are same in behavior with
 *    their old counter parts. The only difference is that they take
 *    CFURLRef, and FSRef as parameters.
 *  
 *  Parameters:
 *    
 *    fileRef:
 *      Refernce to a file whose URL is desired.
 *    
 *    url:
 *      a fully qualified URL is returned in this parameter. The
 *      returned URL gives the path of the file specified in the above
 *      parameter.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HRUtilGetURLFromFSRef(
  const FSRef *  fileRef,
  CFURLRef *     url)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
    Visited links

    If you register a function here, it will be called to determine
    whether or not the given URL has been visited. It should return
    true if the URL has been visited.
    
    In addition to the URLs that the application may add to the list
    of visited links, it should also add URLs that the user clicks
    on. These URLs can be caught by the "add URL to history" callback
    below.
 */
typedef CALLBACK_API( Boolean , HRWasURLVisitedProcPtr )(const char *url, void *refCon);
typedef STACK_UPP_TYPE(HRWasURLVisitedProcPtr)                  HRWasURLVisitedUPP;
/*
 *  HRRegisterWasURLVisitedUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRRegisterWasURLVisitedUPP(
  HRWasURLVisitedUPP   inWasURLVisitedUPP,
  HRReference          hrRef,
  void *               inRefCon)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUnregisterWasURLVisitedUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRUnregisterWasURLVisitedUPP(HRReference hrRef)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
    Use these API from  a Carbon App instead of using HRRegisterWasURLVisitedUPP, HRUnregisterWasURLVisitedUPP. 
    These APIs are same in behavior with their old counter parts. The only difference is that they take 
    CFURLRef as parameters.
        
*/
typedef CALLBACK_API( Boolean , HRWasCFURLVisitedProcPtr )(CFURLRef url, void *refCon);
typedef STACK_UPP_TYPE(HRWasCFURLVisitedProcPtr)                HRWasCFURLVisitedUPP;
/*
 *  HRRegisterWasCFURLVisitedUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HRRegisterWasCFURLVisitedUPP(
  HRWasCFURLVisitedUPP   inWasCFURLVisitedUPP,
  HRReference            hrRef,
  void *                 inRefCon)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUnregisterWasCFURLVisitedUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HRUnregisterWasCFURLVisitedUPP(HRReference hrRef)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
    New URL

    If you register a function here, it will be called every time
    the renderer is going to display a new URL. A few examples of how
    you might use this include...
    
        (a) maintaining a history of URLs
        (b) maintainging a list of visited links
        (c) setting a window title based on the new URL
*/
typedef CALLBACK_API( OSStatus , HRNewURLProcPtr )(const char *url, const char *targetFrame, Boolean addToHistory, void *refCon);
typedef STACK_UPP_TYPE(HRNewURLProcPtr)                         HRNewURLUPP;
/*
 *  HRRegisterNewURLUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRRegisterNewURLUPP(
  HRNewURLUPP   inNewURLUPP,
  HRReference   hrRef,
  void *        inRefCon)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUnregisterNewURLUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRUnregisterNewURLUPP(HRReference hrRef)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/* 
    Use these API from  a Carbon App instead of using HRRegisterNewURLUPP, HRUnregisterNewURLUPP. 
    These APIs are same in behavior with their old counter parts. The only difference is that they take 
    CFURLRef as parameters.
*/
typedef CALLBACK_API( OSStatus , HRNewCFURLProcPtr )(CFURLRef url, CFStringRef targetString, Boolean addToHistory, void *refCon);
typedef STACK_UPP_TYPE(HRNewCFURLProcPtr)                       HRNewCFURLUPP;
/*
 *  HRRegisterNewCFURLUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HRRegisterNewCFURLUPP(
  HRNewCFURLUPP   inURLUPP,
  HRReference     hrRef,
  void *          inRefCon)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUnregisterNewCFURLUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HRUnregisterNewCFURLUPP(HRReference hrRef)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;





/*
    URL to FSSpec function

    If you register a function here, it will be called every time
    the renderer is going to locate a file. The function will be
    passed an enum indicating the type of file being asked for.
 */
typedef UInt16 URLSourceType;
enum {
  kHRLookingForHTMLSource       = 1,
  kHRLookingForImage            = 2,
  kHRLookingForEmbedded         = 3,
  kHRLookingForImageMap         = 4,
  kHRLookingForFrame            = 5
};

typedef CALLBACK_API( OSStatus , HRURLToFSSpecProcPtr )(const char *rootURL, const char *linkURL, FSSpec *fsspec, URLSourceType urlSourceType, void *refCon);
typedef STACK_UPP_TYPE(HRURLToFSSpecProcPtr)                    HRURLToFSSpecUPP;
/*
 *  HRRegisterURLToFSSpecUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRRegisterURLToFSSpecUPP(
  HRURLToFSSpecUPP   inURLToFSSpecUPP,
  HRReference        hrRef,
  void *             inRefCon)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUnregisterURLToFSSpecUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in HTMLRenderingLib 1.0 and later
 */
extern void 
HRUnregisterURLToFSSpecUPP(HRReference hrRef)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/* 
    Use these API from  a Carbon App instead of using HRRegisterURLToFSSpecUPP, HRUnregisterURLToFSSpecUPP. 
    These APIs are same in behavior with their old counter parts. The only difference is that they take 
    FSRef as parameters.
*/
typedef CALLBACK_API( OSStatus , HRURLToFSRefProcPtr )(CFStringRef rootString, CFStringRef linkString, FSRef *fref, URLSourceType urlSourceType, void *refCon);
typedef STACK_UPP_TYPE(HRURLToFSRefProcPtr)                     HRURLToFSRefUPP;
/*
 *  HRRegisterURLToFSRefUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HRRegisterURLToFSRefUPP(
  HRURLToFSRefUPP   inURLToFSRefUPP,
  HRReference       hrRef,
  void *            inRefCon)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  HRUnregisterURLToFSRefUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HRUnregisterURLToFSRefUPP(HRReference hrRef)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  NewHRWasURLVisitedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HRWasURLVisitedUPP
NewHRWasURLVisitedUPP(HRWasURLVisitedProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewHRWasCFURLVisitedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern HRWasCFURLVisitedUPP
NewHRWasCFURLVisitedUPP(HRWasCFURLVisitedProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewHRNewURLUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HRNewURLUPP
NewHRNewURLUPP(HRNewURLProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewHRNewCFURLUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern HRNewCFURLUPP
NewHRNewCFURLUPP(HRNewCFURLProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewHRURLToFSSpecUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HRURLToFSSpecUPP
NewHRURLToFSSpecUPP(HRURLToFSSpecProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewHRURLToFSRefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern HRURLToFSRefUPP
NewHRURLToFSRefUPP(HRURLToFSRefProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeHRWasURLVisitedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHRWasURLVisitedUPP(HRWasURLVisitedUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeHRWasCFURLVisitedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeHRWasCFURLVisitedUPP(HRWasCFURLVisitedUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeHRNewURLUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHRNewURLUPP(HRNewURLUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeHRNewCFURLUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeHRNewCFURLUPP(HRNewCFURLUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeHRURLToFSSpecUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHRURLToFSSpecUPP(HRURLToFSSpecUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeHRURLToFSRefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeHRURLToFSRefUPP(HRURLToFSRefUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeHRWasURLVisitedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeHRWasURLVisitedUPP(
  const char *        url,
  void *              refCon,
  HRWasURLVisitedUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeHRWasCFURLVisitedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeHRWasCFURLVisitedUPP(
  CFURLRef              url,
  void *                refCon,
  HRWasCFURLVisitedUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeHRNewURLUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeHRNewURLUPP(
  const char *  url,
  const char *  targetFrame,
  Boolean       addToHistory,
  void *        refCon,
  HRNewURLUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeHRNewCFURLUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus
InvokeHRNewCFURLUPP(
  CFURLRef       url,
  CFStringRef    targetString,
  Boolean        addToHistory,
  void *         refCon,
  HRNewCFURLUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeHRURLToFSSpecUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeHRURLToFSSpecUPP(
  const char *      rootURL,
  const char *      linkURL,
  FSSpec *          fsspec,
  URLSourceType     urlSourceType,
  void *            refCon,
  HRURLToFSSpecUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeHRURLToFSRefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus
InvokeHRURLToFSRefUPP(
  CFStringRef      rootString,
  CFStringRef      linkString,
  FSRef *          fref,
  URLSourceType    urlSourceType,
  void *           refCon,
  HRURLToFSRefUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#ifdef __cplusplus
}
#endif

#endif /* __HTMLRENDERING__ */

