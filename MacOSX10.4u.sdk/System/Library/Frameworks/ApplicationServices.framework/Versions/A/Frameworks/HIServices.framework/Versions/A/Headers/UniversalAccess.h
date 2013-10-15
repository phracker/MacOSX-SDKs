/*
     File:       HIServices/UniversalAccess.h
 
     Contains:   Universal Access Interfaces.
 
     Version:    HIServices-169~651
 
     Copyright:  © 2005-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __UNIVERSALACCESS__
#define __UNIVERSALACCESS__

#ifndef __COREGRAPHICS__
#include <CoreGraphics/CoreGraphics.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 *  Universal Access
 *  
 *  Discussion:
 *    Universal Access provides apps the ability to control the zoom
 *    focus. The following functions are provided so that applications
 *    can tell Universal Access what part of the UI needs focus.
 */

/*
 *  UAZoomChangeFocusType
 *  
 *  Summary:
 *    Universal Access Zoom Change Focus Types
 *  
 *  Discussion:
 *    The following constants are used to tell Universal Access Zoom
 *    the type of event that is driving the change in the zoom focus.
 */
typedef UInt32 UAZoomChangeFocusType;
enum {

  /*
   * Some event would like focus.
   */
  kUAZoomFocusTypeOther         = 0,

  /*
   * The text insertion point has moved.
   */
  kUAZoomFocusTypeInsertionPoint = 1
};


/*
 *  UAZoomEnabled()
 *  
 *  Summary:
 *    Determine if Universal Access Zoom is enabled.
 *  
 *  Discussion:
 *    This queries the state of Universal Access Zoom
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Result:
 *    TRUE if Universal Access Zoom is on, FALSE if Zoom is off or the
 *    user has zoomed all the way out.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
UAZoomEnabled(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  UAZoomChangeFocus()
 *  
 *  Summary:
 *    Tell Universal Access where Zoom should focus.
 *  
 *  Discussion:
 *    Tells Universal Access the frame of the element in focus and the
 *    part of the element that should be in focus.
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Parameters:
 *    
 *    inRect:
 *      - The frame of the element in focus in global 72dpi coordinates.
 *    
 *    inHighlightRect:
 *      - The frame of highlighted part of the element in focus in
 *      global 72dpi coordinates.  If the whole element is in focus,
 *      and not just a smaller part of it, pass the inRect parameter
 *      and pass NULL for inHighlightRect.
 *    
 *    inType:
 *      - Universal Access Zoom change focus type.
 *  
 *  Result:
 *    OSStatus - noErr if there were no problems or Universal Access
 *    Zoom is off or zoomed all the way out.  paramErr if inRect is
 *    NULL or inType is out of range.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
UAZoomChangeFocus(
  const CGRect *          inRect,
  const CGRect *          inHighlightRect,
  UAZoomChangeFocusType   inType)                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __UNIVERSALACCESS__ */

