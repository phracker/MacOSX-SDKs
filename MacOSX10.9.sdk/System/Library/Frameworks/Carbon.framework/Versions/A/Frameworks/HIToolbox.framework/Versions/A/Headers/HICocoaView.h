/*
     File:       HIToolbox/HICocoaView.h
 
     Contains:   HICocoaView routines
 
     Copyright:  © 2006-2008 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __HICOCOAVIEW__
#define __HICOCOAVIEW__

#ifndef __HIVIEW__
#include <HIToolbox/HIView.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
  to use this header you must use Objective-C.  This will be part of HIToolbox/HIToolbox.h and many people who include that header
  do not use Objective-C.
*/
#ifdef __OBJC__
@class NSView;
/*----------------------------------------------------------------------------*/
/*  HICocoaView                                                               */
/*----------------------------------------------------------------------------*/
/* The HIObject class ID for the HICocoaView class. */
#define kHICocoaViewClassID             CFSTR("com.apple.HICocoaView")
/* ControlKind tag */
enum {
  kControlKindHICocoaView       = 'hins'
};

/*----------------------------------------------------------------------------*/
/*  Parameter names and types                                                 */
/*----------------------------------------------------------------------------*/

/*
 */
enum {

  /*
   * The NSView that is to be associated with this HICocoaView.
   */
  kEventParamNSView             = 'nsvw' /* typeVoidPtr */
};


/*
    The kEventHIObjectInitialize event for HICocoaView can contain the
    following parameters.
    
    --> kEventParamAttributes (in, typeUInt32)
            Options for the view. This parameter is optional and assumed to be
            0 if it does not exist in the event.
            
    --> kEventParamNSView (in, typeVoidPtr)
            The NSView to be wrapped by the NSHIView. This parameter is optional
            and assumed to be nil if it does not exist in the event.
*/
#if !__LP64__
/*
 *  HICocoaViewCreate()
 *  
 *  Summary:
 *    Creates an HICocoaView wrapper that contains a NSView for
 *    embedding in a HIView hierarchy.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inNSView:
 *      The NSView to be wrapped by this view. This is retained by the
 *      HICocoaView and can subsequently be released by the caller.
 *      This parameter may be NULL in which case the view is an empty
 *      container that exists but does not respond to user interaction
 *      or draw.
 *    
 *    inOptions:
 *      Options for the view. Currently this parameter must be 0.
 *    
 *    outHIView:
 *      On exit contains the new view.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Carbon.framework [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HICocoaViewCreate(
  NSView *     inNSView,        /* can be NULL */
  OptionBits   inOptions,
  HIViewRef *  outHIView)                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  HICocoaViewGetView()
 *  
 *  Summary:
 *    Returns the NSView wrapped by the HICocoaView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inView:
 *      The HIView that contains the NSView you are interested in.
 *  
 *  Result:
 *    The NSView wrapped by the HICocoaView. If there is no NSView
 *    associated with the view or if the given HICocoaView is invalid,
 *    NULL is returned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Carbon.framework [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern NSView * 
HICocoaViewGetView(HIViewRef inView)                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  HICocoaViewSetView()
 *  
 *  Summary:
 *    Sets the NSView wrapped by the HICocoaView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inHIView:
 *      The wrapper view to contain the given NSView.
 *    
 *    inNSView:
 *      The NSView to be wrapped by the HICocoaView. This view is
 *      retained by the HICocoaView and can subsequently be released by
 *      the caller. This parameter may be NULL in which case the view
 *      is an empty container that exists but does not respond to user
 *      interaction or draw. If an NSView is wrapped by the HICocoaView
 *      when this API is called, it will be released.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Carbon.framework [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HICocoaViewSetView(
  HIViewRef   inHIView,
  NSView *    inNSView)                                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


#endif  /* !__LP64__ */

#endif  /* defined(__OBJC__) */


#ifdef __cplusplus
}
#endif

#endif /* __HICOCOAVIEW__ */

