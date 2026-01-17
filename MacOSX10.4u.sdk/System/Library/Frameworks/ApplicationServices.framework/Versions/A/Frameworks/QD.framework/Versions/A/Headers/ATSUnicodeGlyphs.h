/*
     File:       QD/ATSUnicodeGlyphs.h
 
     Contains:   ATSUI glyph handling functions.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 2003-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSUNICODEGLYPHS__
#define __ATSUNICODEGLYPHS__

#ifndef __ATSUNICODETYPES__
#include <QD/ATSUnicodeTypes.h>
#endif


/* ---------------------------------------------------------------------------- */
/* ATSUI glyph metrics                                                          */
/* ---------------------------------------------------------------------------- */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ATSUGlyphGetIdealMetrics()
 *  
 *  Summary:
 *    Obtains resolution-independent font metric information for glyphs
 *    associated with a given style object.
 *  
 *  Discussion:
 *    The advance width is the full horizontal width of the glyph as
 *    measured from its origin to the origin of the next glyph on the
 *    line, including the left-side and right-side bearings. For
 *    vertical text, the advance height is the sum of the top-side
 *    bearing, the bounding-box height, and the bottom-side bearing.
 *    You can call the ATSUGlyphGetIdealMetrics function to obtain an
 *    array of ATSGlyphIdealMetrics structures containing values for
 *    the specified glyphs' advance and side bearings.
 *    ATSUGlyphGetIdealMetrics can analyze both horizontal and vertical
 *    text, automatically producing the appropriate bearing values
 *    (oriented for width or height, respectively) for each. You should
 *    call ATSUGlyphGetIdealMetrics to obtain resolution-independent
 *    glyph metrics. To obtain device-adjusted (that is,
 *    resolution-dependent) glyph metrics, call the function
 *    ATSUGlyphGetScreenMetrics.
 *  
 *  Parameters:
 *    
 *    iATSUStyle:
 *      A style referring to a font you wish to obtain glyph metrics
 *      from.
 *    
 *    iNumOfGlyphs:
 *      The number of glyph IDs you are passing in to be examined. This
 *      value should be equal to the size of the array you are passing
 *      in for the iGlyphIDs parameter.
 *    
 *    iGlyphIDs:
 *      An array of glyph IDs referring to glyphs for which you wish to
 *      obtain metrics.
 *    
 *    iInputOffset:
 *      A ByteOffset value specifying the offset in bytes between glyph
 *      IDs in the iGlyphIDs array.
 *    
 *    oIdealMetrics:
 *      A pointer to memory you have allocated for an array of
 *      ATSGlyphIdealMetrics structures. On return, each structure
 *      contains advance and side-bearing values for a glyph. See
 *      ATSTypes.h for more information regarding the
 *      ATSGlyphIdealMetrics structure.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetIdealMetrics(
  ATSUStyle              iATSUStyle,
  ItemCount              iNumOfGlyphs,
  GlyphID                iGlyphIDs[],
  ByteOffset             iInputOffset,
  ATSGlyphIdealMetrics   oIdealMetrics[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGlyphGetScreenMetrics()
 *  
 *  Summary:
 *    Obtains device-adjusted font metric information for glyphs
 *    associated with a given style object.
 *  
 *  Discussion:
 *    You can call the ATSUGlyphGetScreenMetrics function to obtain an
 *    array of ATSGlyphScreenMetrics structures containing values for
 *    the specified glyphs' advance and side bearings, top left,
 *    height, and width. You should call ATSUGlyphGetScreenMetrics to
 *    obtain device-adjusted (that is, resolution-dependent) glyph
 *    metrics. To obtain resolution-independent glyph metrics, call the
 *    function ATSUGlyphGetIdealMetrics.
 *  
 *  Parameters:
 *    
 *    iATSUStyle:
 *      A style referring to a font you wish to obtain glyph metrics
 *      from.
 *    
 *    iNumOfGlyphs:
 *      The number of glyph IDs you are passing in to be examined. This
 *      value should be equal to the size of the array you are passing
 *      in for the iGlyphIDs parameter.
 *    
 *    iGlyphIDs:
 *      An array of glyph IDs referring to glyphs for which you wish to
 *      obtain metrics.
 *    
 *    iInputOffset:
 *      A ByteOffset value specifying the offset in bytes between glyph
 *      IDs in the iGlyphIDs array.
 *    
 *    iForcingAntiAlias:
 *      A Boolean value indicating whether anti-aliasing is forced for
 *      the style object.
 *    
 *    iAntiAliasSwitch:
 *      A Boolean value indicating whether anti-aliasing is currently
 *      on or off.
 *    
 *    oScreenMetrics:
 *      A pointer to memory you have allocated for an array of
 *      ATSGlyphScreenMetrics structures. On return, each structure
 *      contains advance and side-bearing values for a glyph. See
 *      ATSTypes.h for more information regarding the
 *      ATSGlyphScreenMetrics structure.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetScreenMetrics(
  ATSUStyle               iATSUStyle,
  ItemCount               iNumOfGlyphs,
  GlyphID                 iGlyphIDs[],
  ByteOffset              iInputOffset,
  Boolean                 iForcingAntiAlias,
  Boolean                 iAntiAliasSwitch,
  ATSGlyphScreenMetrics   oScreenMetrics[])                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/* ATSUI glyph curve access functions and callbacks                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUGetNativeCurveType()
 *  
 *  Summary:
 *    Returns the native curve format for a specific font.
 *  
 *  Discussion:
 *    Use this function to decide whether to call
 *    ATSUGlyphGetQuadraticPaths or ATSUGlyphGetCubicPaths. Both
 *    functions will return curves for all valid ATSUI fonts, but if
 *    the curve type you request is not the native curve type of the
 *    font, the curves you get back will be mathematically converted,
 *    rather than native font data. See the definition of ATSCurveType
 *    in ATSTypes.h for possible return values from this function.
 *  
 *  Parameters:
 *    
 *    iATSUStyle:
 *      A style referencing a font for which you wish to obtain the
 *      native curve type.
 *    
 *    oCurveType:
 *      On return, a value indicating the native curve type of the font
 *      referenced by iATSUStyle. See the definition of ATSCurveType in
 *      ATSTypes.h for a list of possible return values for this
 *      parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGetNativeCurveType(
  ATSUStyle       iATSUStyle,
  ATSCurveType *  oCurveType)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  ATSQuadraticNewPathProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to start a new drawing path.
 *  
 *  Parameters:
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetQuadraticPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetQuadraticPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSQuadraticNewPathProcPtr )(void * callBackDataPtr);
typedef STACK_UPP_TYPE(ATSQuadraticNewPathProcPtr)              ATSQuadraticNewPathUPP;
/*
 *  NewATSQuadraticNewPathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticNewPathUPP
NewATSQuadraticNewPathUPP(ATSQuadraticNewPathProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticNewPathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticNewPathUPP(ATSQuadraticNewPathUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticNewPathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticNewPathUPP(
  void *                  callBackDataPtr,
  ATSQuadraticNewPathUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSQuadraticLineProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to draw straight lines.
 *  
 *  Parameters:
 *    
 *    pt1:
 *      The starting point of the line.
 *    
 *    pt2:
 *      The end point of the line.
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetQuadraticPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetQuadraticPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSQuadraticLineProcPtr )(const Float32Point *pt1, const Float32Point *pt2, void *callBackDataPtr);
typedef STACK_UPP_TYPE(ATSQuadraticLineProcPtr)                 ATSQuadraticLineUPP;
/*
 *  NewATSQuadraticLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticLineUPP
NewATSQuadraticLineUPP(ATSQuadraticLineProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticLineUPP(ATSQuadraticLineUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticLineUPP(
  const Float32Point *  pt1,
  const Float32Point *  pt2,
  void *                callBackDataPtr,
  ATSQuadraticLineUPP   userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSQuadraticCurveProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to draw curves. The curve is a quadratic patch specified by a
 *    start point (pt1), and end point (pt2), and a single control
 *    point (controlPt).
 *  
 *  Parameters:
 *    
 *    pt1:
 *      The starting point of the curve.
 *    
 *    controlPt:
 *      The off-curve control point.
 *    
 *    pt2:
 *      The end point of the curve.
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetQuadraticPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetQuadraticPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSQuadraticCurveProcPtr )(const Float32Point *pt1, const Float32Point *controlPt, const Float32Point *pt2, void *callBackDataPtr);
typedef STACK_UPP_TYPE(ATSQuadraticCurveProcPtr)                ATSQuadraticCurveUPP;
/*
 *  NewATSQuadraticCurveUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticCurveUPP
NewATSQuadraticCurveUPP(ATSQuadraticCurveProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticCurveUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticCurveUPP(ATSQuadraticCurveUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticCurveUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticCurveUPP(
  const Float32Point *  pt1,
  const Float32Point *  controlPt,
  const Float32Point *  pt2,
  void *                callBackDataPtr,
  ATSQuadraticCurveUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSQuadraticClosePathProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to close the current drawing path.
 *  
 *  Parameters:
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetQuadraticPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetQuadraticPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSQuadraticClosePathProcPtr )(void * callBackDataPtr);
typedef STACK_UPP_TYPE(ATSQuadraticClosePathProcPtr)            ATSQuadraticClosePathUPP;
/*
 *  NewATSQuadraticClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticClosePathUPP
NewATSQuadraticClosePathUPP(ATSQuadraticClosePathProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticClosePathUPP(ATSQuadraticClosePathUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticClosePathUPP(
  void *                    callBackDataPtr,
  ATSQuadraticClosePathUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  ATSUGlyphGetQuadraticPaths()
 *  
 *  Summary:
 *    Uses a callback mechanism to obtain a set of Quadratic outlines
 *    for a specified glyph in a specified font.
 *  
 *  Discussion:
 *    This function will allow you to use callbacks to obtain the exact
 *    outline of a specified glyph, in quadratic form. Although this
 *    function will always return results for any valid ATSUI font, you
 *    should first use the function ATSUGetNativeCurveType to determine
 *    the native format of the glyph you are interested in. Then,
 *    either call ATSUGlyphGetQuadraticPaths or ATSUGlyphGetCubicPaths
 *    based on the result. Otherwise, you may end up with curves that
 *    are mathematically converted from cubic to quadratic (or vice
 *    versa), instead of getting native font data. See the definitions
 *    of ATSQuadraticNewPathProcPtr, ATSQuadraticLineProcPtr,
 *    ATSQuadraticCurveProcPtr, and ATSQuadraticClosePathProcPtr for
 *    more information about setting up the callbacks.
 *  
 *  Parameters:
 *    
 *    iATSUStyle:
 *      A style referring to a font you wish to obtain a set of glyph
 *      outlines from.
 *    
 *    iGlyphID:
 *      A ID number referring to the glyph for which you wish to obtain
 *      outline data. Use the ATSUI direct access functions in
 *      ATSUnicodeDirectAccess.h to obtain values to pass for this
 *      parameter.
 *    
 *    iNewPathProc:
 *      A pointer to a callback function for quadratic new path
 *      operations. See the definition of ATSQuadraticNewPathProcPtr
 *      for more information about creating, disposing, and invoking
 *      this type of Universal Procedure Pointer.
 *    
 *    iLineProc:
 *      A pointer to a callback function for quadratic LineTo
 *      operations. See the definition of ATSQuadraticLineProcPtr for
 *      more information about creating, disposing, and invoking this
 *      type of Universal Procedure Pointer.
 *    
 *    iCurveProc:
 *      A pointer to a callback function for quadratic curve
 *      operations. See the definition of ATSQuadraticCurveProcPtr for
 *      more information about creating, disposing, and invoking this
 *      type of Universal Procedure Pointer.
 *    
 *    iClosePathProc:
 *      A pointer to a callback function for quadratic close path
 *      operations. See the definition of ATSQuadraticClosePathProcPtr
 *      for more information about creating, disposing, and invoking
 *      this type of Universal Procedure Pointer.
 *    
 *    iCallbackDataPtr:
 *      Any valid pointer. Any application specific data you wish to
 *      pass to your callbacks may be sent through this parameter.
 *    
 *    oCallbackResult:
 *      On return, status returned by callback functions. If an error
 *      occurs, callbacks may communicate it through this parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetQuadraticPaths(
  ATSUStyle                  iATSUStyle,
  GlyphID                    iGlyphID,
  ATSQuadraticNewPathUPP     iNewPathProc,
  ATSQuadraticLineUPP        iLineProc,
  ATSQuadraticCurveUPP       iCurveProc,
  ATSQuadraticClosePathUPP   iClosePathProc,
  void *                     iCallbackDataPtr,
  OSStatus *                 oCallbackResult)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  ATSCubicMoveToProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to move the current pen location.
 *  
 *  Parameters:
 *    
 *    pt:
 *      The point to which to move the current pen location.
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetCubicPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetCubicPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSCubicMoveToProcPtr )(const Float32Point *pt, void *callBackDataPtr);
typedef STACK_UPP_TYPE(ATSCubicMoveToProcPtr)                   ATSCubicMoveToUPP;
/*
 *  NewATSCubicMoveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicMoveToUPP
NewATSCubicMoveToUPP(ATSCubicMoveToProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicMoveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicMoveToUPP(ATSCubicMoveToUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicMoveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicMoveToUPP(
  const Float32Point *  pt,
  void *                callBackDataPtr,
  ATSCubicMoveToUPP     userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSCubicLineToProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to draw straight lines.
 *  
 *  Parameters:
 *    
 *    pt:
 *      The end point of the line to be drawn. The starting point is
 *      whatever the current pen position is.
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetCubicPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetCubicPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSCubicLineToProcPtr )(const Float32Point *pt, void *callBackDataPtr);
typedef STACK_UPP_TYPE(ATSCubicLineToProcPtr)                   ATSCubicLineToUPP;
/*
 *  NewATSCubicLineToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicLineToUPP
NewATSCubicLineToUPP(ATSCubicLineToProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicLineToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicLineToUPP(ATSCubicLineToUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicLineToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicLineToUPP(
  const Float32Point *  pt,
  void *                callBackDataPtr,
  ATSCubicLineToUPP     userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSCubicCurveToProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to draw a curve. The curve is a Bezier patch defined by two
 *    off-curve control points (pt1 and pt2), and an endpoint (pt3).
 *    The starting point is whatever the current pen position is.
 *  
 *  Parameters:
 *    
 *    pt1:
 *      The first off-curve control point.
 *    
 *    pt2:
 *      The second off-curve control point.
 *    
 *    pt3:
 *      The end point of the curve.
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetCubicPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetCubicPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSCubicCurveToProcPtr )(const Float32Point *pt1, const Float32Point *pt2, const Float32Point *pt3, void *callBackDataPtr);
typedef STACK_UPP_TYPE(ATSCubicCurveToProcPtr)                  ATSCubicCurveToUPP;
/*
 *  NewATSCubicCurveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicCurveToUPP
NewATSCubicCurveToUPP(ATSCubicCurveToProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicCurveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicCurveToUPP(ATSCubicCurveToUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicCurveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicCurveToUPP(
  const Float32Point *  pt1,
  const Float32Point *  pt2,
  const Float32Point *  pt3,
  void *                callBackDataPtr,
  ATSCubicCurveToUPP    userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSCubicClosePathProcPtr
 *  
 *  Discussion:
 *    A pointer to a client supplied callback function for handling
 *    glyph curve drawing operations. This callback handles operations
 *    to close the current drawing path.
 *  
 *  Parameters:
 *    
 *    callBackDataPtr:
 *      A pointer to any application specific data that may have been
 *      passed to the callbacks through the iCallbackDataPtr parameter
 *      of the ATSUGlyphGetCubicPaths function.
 *  
 *  Result:
 *    Return status. Pass any errors you wish to propagate back to the
 *    original caller of ATSUGlyphGetCubicPaths through this return
 *    value. Note that any nonzero result from this callback will halt
 *    the curve drawing process.
 */
typedef CALLBACK_API( OSStatus , ATSCubicClosePathProcPtr )(void * callBackDataPtr);
typedef STACK_UPP_TYPE(ATSCubicClosePathProcPtr)                ATSCubicClosePathUPP;
/*
 *  NewATSCubicClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicClosePathUPP
NewATSCubicClosePathUPP(ATSCubicClosePathProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicClosePathUPP(ATSCubicClosePathUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicClosePathUPP(
  void *                callBackDataPtr,
  ATSCubicClosePathUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  ATSUGlyphGetCubicPaths()
 *  
 *  Summary:
 *    Uses a callback mechanism to obtain a set of Cubic outlines for a
 *    specified glyph in a specified font.
 *  
 *  Discussion:
 *    This function will allow you to use callbacks to obtain the exact
 *    outline of a specified glyph, in cubic form. Although this
 *    function will always return results for any valid ATSUI font, you
 *    should first use the function ATSUGetNativeCurveType to determine
 *    the native format of the glyph you are interested in. Then,
 *    either call ATSUGlyphGetQuadraticPaths or ATSUGlyphGetCubicPaths
 *    based on the result. Otherwise, you may end up with curves that
 *    are mathematically converted from quadratic to cubic (or vice
 *    versa), instead of getting native font data. See the definitions
 *    of ATSCubicMoveToProcPtr, ATSCubicLineToProcPtr,
 *    ATSCubicCurveToProcPtr, and ATSCubicClosePathProcPtr for more
 *    information about setting up the callbacks.
 *  
 *  Parameters:
 *    
 *    iATSUStyle:
 *      A style referring to a font you wish to obtain a set of glyph
 *      outlines from.
 *    
 *    iGlyphID:
 *      A ID number referring to the glyph for which you wish to obtain
 *      outline data. Use the ATSUI direct access functions in
 *      ATSUnicodeDirectAccess.h to obtain values to pass for this
 *      parameter.
 *    
 *    iMoveToProc:
 *      A pointer to a callback function for cubic MoveTo operations.
 *      See the definition of ATSCubicMoveToProcPtr for more
 *      information about creating, disposing, and invoking this type
 *      of Universal Procedure Pointer.
 *    
 *    iLineToProc:
 *      A pointer to a callback function for cubic LineTo operations.
 *      See the definition of ATSCubicLineToProcPtr for more
 *      information about creating, disposing, and invoking this type
 *      of Universal Procedure Pointer.
 *    
 *    iCurveToProc:
 *      A pointer to a callback function for cubic CurveTo operations.
 *      See the definition of ATSCubicCurveToProcPtr for more
 *      information about creating, disposing, and invoking this type
 *      of Universal Procedure Pointer.
 *    
 *    iClosePathProc:
 *      A pointer to a callback function for cubic MoveTo operations.
 *      See the definition of ATSCubicClosePathProcPtr for more
 *      information about creating, disposing, and invoking this type
 *      of Universal Procedure Pointer.
 *    
 *    iCallbackDataPtr:
 *      Any valid pointer. Any application specific data you wish to
 *      pass to your callbacks may be sent through this parameter.
 *    
 *    oCallbackResult:
 *      On return, status returned by callback functions. If an error
 *      occurs, callbacks may communicate it through this parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetCubicPaths(
  ATSUStyle              iATSUStyle,
  GlyphID                iGlyphID,
  ATSCubicMoveToUPP      iMoveToProc,
  ATSCubicLineToUPP      iLineToProc,
  ATSCubicCurveToUPP     iCurveToProc,
  ATSCubicClosePathUPP   iClosePathProc,
  void *                 iCallbackDataPtr,       /* can be NULL */
  OSStatus *             oCallbackResult)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGlyphGetCurvePaths()
 *  
 *  Summary:
 *    Obtains glyph curve data without the use of callbacks.
 *  
 *  Discussion:
 *    This function will return glyph curve data in a single data
 *    structure rather than through the use of callbacks, but you must
 *    parse the data structure yourself. ATSUGlyphGetCubicPaths and
 *    ATSUGlyphGetQuadraticPaths will parse the glyph data for you and
 *    use the callbacks you provide them to give you access to the
 *    individual points on the curves. Typically you use the function
 *    ATSUGlyphGetCurvePaths by calling it twice, as follows: (1) Pass
 *    a valid style and glyphID into the iATSUStyle and iGlyphID
 *    parameters, respectively, 0 for the ioBufferSize parameter, and
 *    NULL for the oPaths parameter. ATSUGlyphGetCurvePaths returns the
 *    size to use for the oPaths array in the ioBufferSize parameter.
 *    (2) Allocate enough space an array of the returned size, then
 *    call the ATSUGlyphGetCurvePaths again, passing a pointer to the
 *    array in the oPaths parameter. On return, the array contains the
 *    glyph outline data.
 *  
 *  Parameters:
 *    
 *    iATSUStyle:
 *      A style referring to a font you wish to obtain a set of glyph
 *      outlines from.
 *    
 *    iGlyphID:
 *      A ID number referring to the glyph for which you wish to obtain
 *      outline data. Use the ATSUI direct access functions in
 *      ATSUnicodeDirectAccess.h to obtain values to pass for this
 *      parameter.
 *    
 *    ioBufferSize:
 *      On input, the size of the buffer you have allocated for the
 *      oPaths parameter. On return, the actual size of the data
 *      structure that has been copied into the oPaths parameter.
 *    
 *    oPaths:
 *      On return, a data structure containing glyph outline
 *      information. See ATSTypes.h for a definition of this data
 *      structure.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetCurvePaths(
  ATSUStyle         iATSUStyle,
  GlyphID           iGlyphID,
  ByteCount *       ioBufferSize,
  ATSUCurvePaths *  oPaths)             /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Functions listed beyond this point are either deprecated or not recommended */

/* ---------------------------------------------------------------------------- */
/* ATSUI glyphInfo access (deprecated)                                          */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUGetGlyphInfo()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUnicodeDirectAccess.h functions instead.
 *  
 *  Summary:
 *    Obtains a copy of the style and layout information for each glyph
 *    in a line.
 *  
 *  Discussion:
 *    Please see ATSUnicodeDirectAccess.h for replacement functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGetGlyphInfo(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineStart,
  UniCharCount          iLineLength,
  ByteCount *           ioBufferSize,
  ATSUGlyphInfoArray *  oGlyphInfoPtr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  ATSUDrawGlyphInfo()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUnicodeDirectAccess.h functions instead.
 *  
 *  Summary:
 *    Draws glyphs at the specified location, based on style and layout
 *    information specified for each glyph.
 *  
 *  Discussion:
 *    Please see ATSUnicodeDirectAccess.h for replacement functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUDrawGlyphInfo(
  ATSUGlyphInfoArray *  iGlyphInfoArray,
  Float32Point          iLocation)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;



#ifdef __cplusplus
}
#endif

#endif /* __ATSUNICODEGLYPHS__ */

