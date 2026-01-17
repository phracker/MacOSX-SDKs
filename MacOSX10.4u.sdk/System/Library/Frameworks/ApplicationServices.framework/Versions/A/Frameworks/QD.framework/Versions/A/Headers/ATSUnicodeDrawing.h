/*
     File:       QD/ATSUnicodeDrawing.h
 
     Contains:   ATSUI drawing, measuring, and highlighting functions.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 2003-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSUNICODEDRAWING__
#define __ATSUNICODEDRAWING__

#ifndef __ATSUNICODETYPES__
#include <QD/ATSUnicodeTypes.h>
#endif


/* ---------------------------------------------------------------------------- */
/*  ATSUI drawing and measuring                                                 */
/* ---------------------------------------------------------------------------- */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ATSUDrawText()
 *  
 *  Summary:
 *    Draws a specified range of text in a QuickDraw graphics port or
 *    Quartz graphics context.
 *  
 *  Discussion:
 *    Before calling ATSUDrawText, you will most likely want to call
 *    ATSUSetLayoutControls to set a value for the kATSUCGContextTag
 *    attribute in order to specify your current graphics context.
 *    Otherwise, ATSUI will attempt to draw using Quickdraw style text
 *    rendering in whatever Quickdraw GrafPort is currently active (use
 *    SetPort to determine the currently active Quickdraw GrafPort, see
 *    Quickdraw.h). Carbon applications can create a CGContext from a
 *    Quickdraw GrafPort using the functions QDBeginCGContext and
 *    QDEndCGContext (see Quickdraw.h). Cocoa applications can call the
 *    method "graphicsPort" on the current NSGraphicsContext in order
 *    to get a CGContextRef to pass into ATSUI (use the method
 *    "currentContext" to obtain the current NSGraphicsContext, see
 *    NSGraphicsContext.h for more information). ATSUDrawText examines
 *    the text layout object to ensure that each of the characters in
 *    the range is assigned to a style run. If there are gaps between
 *    style runs, ATSUI assigns the characters in the gap to the style
 *    run that precedes (in storage order) the gap. If there is no
 *    style run at the beginning of the text range, ATSUI assigns these
 *    characters to the first style run it finds. If there is no style
 *    run at the end of the text range, ATSUI assigns the remaining
 *    characters to the last style run it finds. If you want to draw a
 *    range of text that spans multiple lines, you should call
 *    ATSUDrawText for each line of text to draw, even if all the lines
 *    are in the same text layout object. You should adjust the
 *    iLineOffset parameter to reflect the beginning of each line to be
 *    drawn. Please note that when drawing into a GrafPort, calls to
 *    QDSwapTextFlags have no effect on ATSUI text rendering. The
 *    proper way to achieve Quartz text rendering from ATSUI is to use
 *    the kATSUCGContextTag attribute to specify a CGContextRef in each
 *    ATSUTextLayout before calling ATSUDrawText.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout containing text to draw.
 *    
 *    iLineOffset:
 *      The starting offset of the range of text to draw. To specify
 *      the beginning of the text buffer, pass kATSUFromTextBeginning
 *      for this parameter.
 *    
 *    iLineLength:
 *      The length of the range of text to draw. To specify a range
 *      that continues to the end of the text buffer, pass
 *      kATSUToTextEnd for this parameter.
 *    
 *    iLocationX:
 *      The x-coordinate of the origin (in either the current graphics
 *      port or Quartz graphics context) of the line containing the
 *      text range to render. Note that the ATSUTextMeasurement type is
 *      defined as a Fixed value, so you must ensure that your
 *      coordinates are converted to Fixed values before passing them
 *      to this function (see FixMath.h for conversion functions). Pass
 *      the constant kATSUUseGrafPortPenLoc to draw relative to the
 *      current pen location in the current graphics port.
 *    
 *    iLocationY:
 *      The y-coordinate of the origin (in either the current graphics
 *      port or Quartz graphics context) of the line containing the
 *      text range to render. Note that the ATSUTextMeasurement type is
 *      defined as a Fixed value, so you must ensure that your
 *      coordinates are converted to Fixed values before passing them
 *      to this function (see FixMath.h for conversion functions). Pass
 *      the constant kATSUUseGrafPortPenLoc to draw relative to the
 *      current pen location in the current graphics port.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUDrawText(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineOffset,
  UniCharCount          iLineLength,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetUnjustifiedBounds()
 *  
 *  Summary:
 *    Obtains the typographic bounding rectangle for a line of text
 *    prior to final layout.
 *  
 *  Discussion:
 *    This function calculates the typographic bounds (in coordinates
 *    independent of the rendering device) for a line of text. Note
 *    that ATSUGetUnjustifiedBounds calculates these bounds prior to
 *    the text's final layout, and therefore, the calculated bounds
 *    might not reflect those of the final laid-out line.
 *    Justification, truncation, and device level positioning are not
 *    taken into account. To obtain the typographic bounds of a line
 *    after it is laid out, you can call the function
 *    ATSUGetGlyphBounds. For more infomration about the difference
 *    between typographic and image bounds, please refer to the ATSUI
 *    documentation. Note that ATSUGetUnjustifiedBounds treats the
 *    specified text range as a single line. That is, if the range of
 *    text you specify is less than a line, it nevertheless treats the
 *    initial character in the range as the start of a line, for
 *    measuring purposes. If the range of text extends beyond a line,
 *    ATSUGetUnjustifiedBounds ignores soft line breaks, again,
 *    treating the text as a single line.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout object to obtain bounds information for.
 *    
 *    iLineStart:
 *      The start of the line of text to obtain bounds information for.
 *      To indicate that the line starts at the beginning of the text
 *      buffer, you can pass the constant kATSUFromTextBeginning . To
 *      specify the entire text buffer, pass kATSUFromTextBeginning in
 *      this parameter and kATSUToTextEnd in the iLineLength parameter.
 *    
 *    iLineLength:
 *      The length of the line to obtain bounds information for. If you
 *      want the line to extend to the end of the text buffer, you can
 *      pass the constant kATSUToTextEnd .
 *    
 *    oTextBefore:
 *      On return, the value specifies the starting point of the
 *      typographic bounds for the line, relative to the origin (0,0)
 *      of the line and taking into account cross-stream shifting. Note
 *      that the ATSUMeasureText function might produce negative values
 *      for the typographic starting point of the line if, for example,
 *      the initial character of the line is allowed to hang into the
 *      margin. For horizontal text, this value corresponds to the left
 *      side of the bounding rectangle.
 *    
 *    oTextAfter:
 *      On return, the end point of the typographic bounds for the
 *      line, relative to the origin (0,0) of the line and taking into
 *      account cross-stream shifting. For horizontal text, this value
 *      corresponds to the right side of the bounding rectangle.
 *    
 *    oAscent:
 *      On return, the typographic bounds for the line, relative to the
 *      origin (0,0) of the line and taking into account cross-stream
 *      shifting. For horizontal text, this value corresponds to the
 *      top side of the bounding rectangle.
 *    
 *    oDescent:
 *      On return, the typographic bounds for the line, relative to the
 *      origin (0,0) of the line and taking into account cross-stream
 *      shifting. For horizontal text, this value corresponds to the
 *      bottom side of the bounding rectangle.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUGetUnjustifiedBounds(
  ATSUTextLayout         iTextLayout,
  UniCharArrayOffset     iLineStart,
  UniCharCount           iLineLength,
  ATSUTextMeasurement *  oTextBefore,
  ATSUTextMeasurement *  oTextAfter,
  ATSUTextMeasurement *  oAscent,
  ATSUTextMeasurement *  oDescent)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUMeasureTextImage()
 *  
 *  Summary:
 *    Obtains the image bounding rectangle for a line of text after
 *    final layout.
 *  
 *  Discussion:
 *    This function obtains the image bounds of a laid-out line of
 *    text. These bounds are described by the smallest rectangle that
 *    completely encloses the filled or framed parts of a block of
 *    text—that is, the text's "inked" glyphs. In measuring the line,
 *    the ATSUMeasureTextImage function takes into account line
 *    rotation, alignment, and justification, as well as other
 *    characteristics that affect layout, such as hanging punctuation.
 *    (If the line is rotated, the sides of the rectangle are parallel
 *    to the coordinate axes and encompass the rotated line.) If no
 *    attributes are set for the line, ATSUMeasureTextImage uses the
 *    global attributes set for the text layout object. Because the
 *    height of the image bounding rectangle is determined by the
 *    actual device metrics, ATSUMeasureTextImage ignores any
 *    previously set line ascent and descent values for the line it is
 *    measuring.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout for which to obtain image bounds.
 *    
 *    iLineOffset:
 *      The first character of the line to examine. To indicate that
 *      the specified line starts at the beginning of the text buffer,
 *      you can pass the constant kATSUFromTextBeginning . To specify
 *      the entire text buffer, pass kATSUFromTextBeginning in this
 *      parameter and kATSUToTextEnd in the iLineLength parameter.
 *    
 *    iLineLength:
 *      The length of the text range. If you want the range of text to
 *      extend to the end of the text buffer, you can pass the constant
 *      kATSUToTextEnd . However, the image bounds is restricted to the
 *      line in which iLineOffset resides.
 *    
 *    iLocationX:
 *      The x-coordinate of the line's origin in the current graphics
 *      port or Quartz graphics context. Pass the constant
 *      kATSUUseGrafPortPenLoc for the dimensions of the bounds
 *      relative to the current pen location in the current graphics
 *      port or graphics context. You can pass 0to obtain only the
 *      dimensions of the bounding rectangle relative to one another,
 *      not their actual onscreen position.
 *    
 *    iLocationY:
 *      The y-coordinate of the line's origin in the current graphics
 *      port or Quartz graphics context. Pass the constant
 *      kATSUUseGrafPortPenLoc for the dimensions of the bounds
 *      relative to the current pen location in the current graphics
 *      port or graphics context. You can pass 0to obtain only the
 *      dimensions of the bounding rectangle relative to one another,
 *      not their actual onscreen position.
 *    
 *    oTextImageRect:
 *      On return, the dimensions of the image bounding rectangle for
 *      the text, offset by the values specified in the iLocationX and
 *      iLocationY parameters. If the line is rotated, the sides of the
 *      rectangle are parallel to the coordinate axis.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUMeasureTextImage(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineOffset,
  UniCharCount          iLineLength,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY,
  Rect *                oTextImageRect)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetGlyphBounds()
 *  
 *  Summary:
 *    Obtains the typographic bounds of a line of glyphs after final
 *    layout.
 *  
 *  Discussion:
 *    This function produces the enclosing trapezoid(s) that represent
 *    the typographic bounds for glyphs in a final, laid-out range of
 *    text. You typically call this function when you need to obtain an
 *    enclosing trapezoid for a line, taking rotation and all other
 *    layout attributes into account. ATSUI determines the height of
 *    each trapezoid by examining any line ascent and descent attribute
 *    values you may have set for the line. If you have not set these
 *    attributes for the line, the ATSUGetGlyphBounds function uses any
 *    line ascent and descent values you may have set for the text
 *    layout object containing the line. If these are not set,
 *    ATSUGetGlyphBounds uses the font's natural line ascent and
 *    descent values for the line. If these are previously set,
 *    ATSUGetGlyphBounds uses the ATSUStyle ascent and or
 *    descent/leading values. Note that the coordinates produced for
 *    the trapezoid(s) are offset by the amount specified in the
 *    iTextBasePointX and iTextBasePointY parameters. If your goal in
 *    calling the ATSUGetGlyphBounds function is to obtain metrics for
 *    drawing the typographic bounds on the screen, pass the position
 *    of the origin of the line in the current graphics port or
 *    graphics context in these parameters. This enables
 *    ATSUGetGlyphBounds to match the trapezoids to their onscreen
 *    image. When the range specified by the iBoundsCharStart and
 *    iBoundsCharLength parameters covers an entire line, you are
 *    guaranteed to receive only one trapezoid on return. Otherwise,
 *    multiple trapezoids may be returned to cover incomplete sections
 *    of bidi runs. In such cases, you would typically call
 *    ATSUGetGlyphBounds twice, as follows: (1) Pass NULL for the
 *    oGlyphBounds parameter, 0 for the iMaxNumberOfBounds parameter,
 *    and valid values for the other parameters. The ATSUGetGlyphBounds
 *    function returns the actual number of trapezoids needed to
 *    enclose the glyphs in the oActualNumberOfBounds parameter. (2)
 *    Allocate enough space for a buffer of the returned size, then
 *    call the function again, passing a valid pointer to the buffer in
 *    the oGlyphBounds parameter. On return, the buffer contains the
 *    trapezoids for the glyphs' typographic bounds. To obtain the
 *    typographic bounds of a line of text prior to line layout, call
 *    the function ATSUGetUnjustifiedBounds. To calculate the image
 *    bounding rectangle for a final laid-out line, call the function
 *    ATSUMeasureTextImage. For more infomration about the difference
 *    between typographic and image bounds, please refer to the ATSUI
 *    documentation.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout object for which glyph bounds are to be
 *      obtained.
 *    
 *    iTextBasePointX:
 *      The x-coordinate of the origin of the line containing the
 *      glyphs in the current graphics port or Quartz graphics context.
 *      Pass the constant kATSUUseGrafPortPenLoc to obtain the glyph
 *      bounds relative to the current pen location in the current
 *      graphics port or graphics context. You may pass 0 to obtain
 *      only the dimensions of the bounds relative to one another, not
 *      their actual onscreen position.
 *    
 *    iTextBasePointY:
 *      The y-coordinate of the origin of the line containing the
 *      glyphs in the current graphics port or Quartz graphics context.
 *      Pass the constant kATSUUseGrafPortPenLoc to obtain the glyph
 *      bounds relative to the current pen location in the current
 *      graphics port or graphics context. You may pass 0 to obtain
 *      only the dimensions of the bounds relative to one another, not
 *      their actual onscreen position.
 *    
 *    iBoundsCharStart:
 *      The offset from the beginning of the text buffer to the
 *      character corresponding to the first glyph to measure. To
 *      indicate that the text range starts at the beginning of the
 *      text buffer, you can pass the constant kATSUFromTextBeginning.
 *    
 *    iBoundsCharLength:
 *      The length of text range to measure. If you want the range to
 *      extend to the end of the text buffer, you can pass the constant
 *      kATSUToTextEnd.
 *    
 *    iTypeOfBounds:
 *      The type of bounds you wish to obtain. See ATSLayoutTypes.h for
 *      a list of possible values to pass in here.
 *    
 *    iMaxNumberOfBounds:
 *      The maximum number of bounding trapezoids to obtain. Typically,
 *      this is equivalent to the number of bounds in the oGlyphBounds
 *      array. To determine this value, see the Discussion.
 *    
 *    oGlyphBounds:
 *      A pointer to memory you have allocated for an array of
 *      ATSTrapezoid values. On return, the array contains a trapezoid
 *      representing the typographic bounds for glyphs in the text
 *      range. If the specified range of text encloses nested
 *      bidirectional text, ATSUGetGlyphBounds produces multiple
 *      trapezoids defining these regions.In ATSUI 1.1, the maximum
 *      number of enclosing trapezoids that can be returned is 31; in
 *      ATSUI 1.2, the maximum number is 127. If you pass a range that
 *      covers an entire line, ATSUGetGlyphBounds always returns only 1
 *      trapezoid. If you are uncertain of how much memory to allocate
 *      for this array, see the Discussion.
 *    
 *    oActualNumberOfBounds:
 *      On return, the value specifies the actual number of enclosing
 *      trapezoids bounding the specified characters. This may be
 *      greater than the value you provide in the iMaxNumberOfBounds
 *      parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetGlyphBounds(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iBoundsCharStart,
  UniCharCount          iBoundsCharLength,
  UInt16                iTypeOfBounds,
  ItemCount             iMaxNumberOfBounds,
  ATSTrapezoid          oGlyphBounds[],              /* can be NULL */
  ItemCount *           oActualNumberOfBounds)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI line breaking                                                         */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUBatchBreakLines()
 *  
 *  Summary:
 *    Soft wraps a range of text in a layout to a constant line width.
 *  
 *  Discussion:
 *    Equivalent to repeatedly calling the ATSUBreakLine function with
 *    the parameter iUseAsSoftLineBreak set to true. Use this function
 *    to gain a substantial performance increase over the use of
 *    ATSUBreakLine. It will set soft breaks in a layout for multiple
 *    lines in a single call. It assumes constant line width. Soft line
 *    breaks within a layout are what divide it into lines. You can
 *    manipulate the soft breaks that are currently set within a layout
 *    using the functions ATSUGetSoftLineBreaks, ATSUSetSoftLineBreak,
 *    and ATSUClearSoftLineBreaks.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout containing text to be soft wrapped.
 *    
 *    iRangeStart:
 *      Beginning offset for the rage of text to be soft wrapped.
 *    
 *    iRangeLength:
 *      The length of the range of text to be soft wrapped.
 *    
 *    iLineWidth:
 *      The line width at which to force soft wrapping of text. Note
 *      that this parameter is of type ATSUTextMeasurement, which is
 *      defined as Fixed. See FixMath.h for conversion routines for
 *      fixed point values.
 *    
 *    oBreakCount:
 *      On return, the number of soft breaks that were set in the
 *      layout. Use this to determine how much memory to allocate when
 *      calling ATSUGetSoftLineBreaks.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUBatchBreakLines(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iRangeStart,
  UniCharCount          iRangeLength,
  ATSUTextMeasurement   iLineWidth,
  ItemCount *           oBreakCount)        /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUBreakLine()
 *  
 *  Summary:
 *    Soft wraps a single line of text within a layout.
 *  
 *  Discussion:
 *    This function will automatically determine the optimal place to
 *    set a soft break in a given range of text. It suggests a soft
 *    line break each time it encounters a hard line break character
 *    such as a carriage return, line feed, form feed, line separator,
 *    or paragraph separator. If ATSUBreakLine does not encounter a
 *    hard line break, it uses the line width you specify to determine
 *    how many characters fit on a line and suggests soft line breaks
 *    accordingly. You can loop over ATSUBreakLine, repeatedly calling
 *    it on the same layout, until all the text in the entire layout
 *    has been soft wrapped. However, for maximum efficiency, you
 *    should use ATSUBatchBreakLines. ATSUBreakLine should only be used
 *    if you have special needs, such as a non-constant line width.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout containing text to be soft wrapped.
 *    
 *    iLineStart:
 *      The beginning of the line you wish to soft wrap. To specify the
 *      beginning of the text buffer, pass the constant
 *      kATSUFromTextBeginning.
 *    
 *    iLineWidth:
 *      The line width at which to force soft wrapping of text. Note
 *      that this parameter is of type ATSUTextMeasurement, which is
 *      defined as Fixed. See FixMath.h for conversion routines for
 *      fixed point values.
 *    
 *    iUseAsSoftLineBreak:
 *      A Boolean value indicating whether ATSUBreakLine should
 *      automatically set the line break produced in the oLineBreak
 *      parameter. If true ,ATSUBreakLine sets the line break and
 *      clears any previously-set soft line breaks that precede the new
 *      break in the line but lie after the offset specified by
 *      iLineStart. You should ususally pass true for this parameter,
 *      unless you plan to use ATSUSetSoftLineBreak to set the soft
 *      break somewhere other than what is suggested by ATSUBreakLine.
 *    
 *    oLineBreak:
 *      On return, the value specifies the soft line break as
 *      determined by ATSUBreakLine. If the value returned is the same
 *      value as specified in iLineStart , you have made an input
 *      parameter error. In this case, check to make sure that the line
 *      width specified in iLineWidth is big enough for ATSUBreakLine
 *      to perform line breaking. ATSUBreakLine does not return an
 *      error in this case.
 *  
 *  Result:
 *    On success, noErr is returned. TSUI usually calculates a soft
 *    line break to be at the beginning of the first word that does ont
 *    fit on the line. But if ATSUBreakLine calculates the most optimal
 *    line break to be in the middle of a word, it returns the result
 *    code kATSULineBreakInWord. Note that ATSUI produces a line break
 *    in the middle of a word only as a last resort. See MacErrors.h
 *    for other possible error codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUBreakLine(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineStart,
  ATSUTextMeasurement   iLineWidth,
  Boolean               iUseAsSoftLineBreak,
  UniCharArrayOffset *  oLineBreak)                /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetSoftLineBreak()
 *  
 *  Summary:
 *    Sets a soft line break at the specified point in a text layout.
 *  
 *  Discussion:
 *    You should typically only call ATSUSetSoftLineBreak to set line
 *    breaks when you are using your own line-breaking algorithm to
 *    calculate these breaks. For optimal performance, you should use
 *    ATSUBatchBreakLines to both calculate and set soft line breaks in
 *    your text. After calling ATSUSetSoftLineBreak , you should call
 *    the function ATSUGetUnjustifiedBounds to determine whether the
 *    characters still fit within the line, which is necessary due to
 *    end-of-line effects such as swashes.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which to set the soft break.
 *    
 *    iLineBreak:
 *      An offset into the text buffer specifying the location to set
 *      the soft break at.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetSoftLineBreak(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iLineBreak)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetSoftLineBreaks()
 *  
 *  Summary:
 *    Obtains the soft line breaks that are currently set in a given
 *    text range.
 *  
 *  Discussion:
 *    Typically you use the function ATSUGetSoftLineBreaks by calling
 *    it twice, as follows: (1) Pass valid values for the iTextLayout,
 *    iRangeStart, iRangeLength, and oBreakCount parameters. Pass NULL
 *    for the oBreaks parameter and 0 for the iMaximumBreaks parameter.
 *    ATSUGetSoftLineBreaks returns the size of the font array in the
 *    oBreakCount parameter. (2) Allocate enough space for an array of
 *    the returned size, then call the function again, passing a valid
 *    pointer in the oBreaks parameter. On return, the pointer refers
 *    to an array containing the text range's soft line breaks. If you
 *    have just called ATSUBatchBreakLines, the oBreakCount parameter
 *    will give you the value you would normally obtain from step 1,
 *    allowing you to skip this step in such cases.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A text layout to obtain a list of soft breaks from.
 *    
 *    iRangeStart:
 *      The beginning of the range of text for which to obtain a list
 *      of softbreaks. To indicate that the specified text range starts
 *      at the beginning of the text buffer, you can pass the constant
 *      kATSUFromTextBeginning, To specify the entire text buffer, pass
 *      kATSUFromTextBeginning in this parameter and kATSUToTextEnd in
 *      the iRangeLength parameter.
 *    
 *    iRangeLength:
 *      The end of the range of text for which to obtain a list of
 *      softbreaks. If you want the range of text to extend to the end
 *      of the text buffer, you can pass the constant kATSUToTextEnd.
 *    
 *    iMaximumBreaks:
 *      The maximum number of soft line breaks to obtain. Typically,
 *      this is equivalent to the number of UniCharArrayOffset values
 *      for which you have allocated memory in the oBreaks array. To
 *      determine this value, see the Discussion.
 *    
 *    oBreaks:
 *      On return, the array contains offsets from the beginning of the
 *      text buffer to each of the soft line breaks in the text range.
 *      If you are uncertain of how much memory to allocate for this
 *      array, see the Discussion.
 *    
 *    oBreakCount:
 *      On return, the number of soft breaks set in iTextLayout. Note
 *      that this value may be greater than what you pass in for
 *      iMaximumBreaks.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetSoftLineBreaks(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iRangeStart,
  UniCharCount         iRangeLength,
  ItemCount            iMaximumBreaks,
  UniCharArrayOffset   oBreaks[],            /* can be NULL */
  ItemCount *          oBreakCount)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearSoftLineBreaks()
 *  
 *  Summary:
 *    Unsets any currently set soft breaks in a range of text.
 *  
 *  Discussion:
 *    This function clears all previously set soft line breaks for the
 *    specified text range and clears any associated layout caches as
 *    well.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout object for which to remove line breaks.
 *    
 *    iRangeStart:
 *      The beginning of the text range over which to clear soft line
 *      breaks. To indicate that the specified text range starts at the
 *      beginning of the text buffer, you can pass the constant
 *      kATSUFromTextBeginning . To specify the entire text buffer,
 *      pass kATSUFromTextBeginning in this parameter and
 *      kATSUToTextEnd in the iRangeLength parameter.
 *    
 *    iRangeLength:
 *      The length of the text range over which to clear soft line
 *      breaks. If you want the range of text to extend to the end of
 *      the text buffer, you can pass the constant kATSUToTextEnd.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearSoftLineBreaks(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iRangeStart,
  UniCharCount         iRangeLength)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI highlighting                                                          */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetHighlightingMethod()
 *  
 *  Summary:
 *    Specifies the methods ATSUI will use for highlighting and
 *    unhighlighting text in a given layout.
 *  
 *  Discussion:
 *    By default, ATSUI highlights text by "inverting" the region
 *    containing the text, that is, its background color. Although
 *    inversion provides satisfactory highlighting in most cases, it
 *    does not always provide the best result for grayscale text. (Mac
 *    OS X sets a lower threshold for antialiasing, while in Mac OS 9
 *    grayscale text can be turned off by the user.) In Mac OS X, when
 *    using a Quartz graphics context, you can instruct ATSUI to use
 *    the redraw method of highlighting, rather than simple inversion.
 *    (Note that Cocoa applications always use the redraw method of
 *    highlighting.) The redraw method allows for accurate highlighting
 *    of more complex backgrounds, such as those containing multiple
 *    colors, patterns, or pictures. To set redrawing on, call the
 *    ATSUSetHighlightingMethod function and specify that the redraw
 *    method be used (by passing kRedrawHighlighting in the iMethod
 *    parameter). If you specify the redraw method of highlighting when
 *    you call ATSUSetHighlightingMethod, then you must also specify
 *    how the background is to be redrawn when the function
 *    ATSUUnhighlightText is called. ATSUI can restore the desired
 *    background in one of two ways, depending on the background's
 *    complexity: (1) When the background is a single color (such as
 *    white), ATSUI can readily unhighlight the background. In such a
 *    case, you specify the background color that ATSUI uses by calling
 *    ATSUSetHighlightingMethod and setting iUnhighlightData.dataType
 *    to kATSUBackgroundColor and providing the background color in
 *    iUnhighlightData.unhighlightData. With these settings defined,
 *    when you call ATSUUnhighlightText, ATSUI simply calculates the
 *    previously highlighted area, repaints it with the specified
 *    background color, and then redraws the text. (2) When the
 *    background is more complex (containing, for example, multiple
 *    colors, patterns, or pictures), you must provide a redraw
 *    background callback function when you call
 *    ATSUSetHighlightingMethod. You do this by setting
 *    iUnhighlightData.dataType to kATSUBackgroundCallback and
 *    providing a RedrawBackgroundUPP in
 *    iUnhighlightData.unhighlightData . Then when you call
 *    ATSUUnhighlightText and ATSUI calls your callback, you are
 *    responsible for redrawing the background of the unhighlighted
 *    area. If you choose to also redraw the text, then your callback
 *    should return false as a function result. If your callback
 *    returns true ATSUI redraws any text that needs to be redrawn. See
 *    RedrawBackgroundProcPtr for additional information.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout to which this highlight method should be applied.
 *    
 *    iMethod:
 *      The type of highlighting to use; inversion
 *      (kInvertHighlighting) or redrawing (kRedrawHighlighting). The
 *      default is inversion. If you are happy with that technique
 *      there is no reason to call this function.
 *    
 *    iUnhighlightData:
 *      Data needed to redraw the background or NULL if inversion is
 *      being chosen. See the definition of ATSUUnhighlightData for
 *      more information about the possible contents of this structure.
 *      Also see the Discussion for this function.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUSetHighlightingMethod(
  ATSUTextLayout               iTextLayout,
  ATSUHighlightMethod          iMethod,
  const ATSUUnhighlightData *  iUnhighlightData)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUHighlightText()
 *  
 *  Summary:
 *    Renders a highlighted range of text at a specified location in a
 *    QuickDraw graphics port or Quartz graphics context.
 *  
 *  Discussion:
 *    When the user selects a series of glyphs, the characters in
 *    memory corresponding to the glyphs make up the selection range
 *    and should be highlighted to indicate where the next editing
 *    operation is to occur. The characters in a selection range are
 *    always contiguous in memory, but their corresponding glyphs are
 *    not necessarily so onscreen. If the selection range crosses a
 *    direction boundary, it is appropriate to display discontinuous
 *    highlighting. The ATSUHighlightText function renders a
 *    highlighted range of text at a specified location in a QuickDraw
 *    graphics port or Quartz graphics context, using the highlight
 *    information in the graphics port or context. ATSUHighlightText
 *    automatically produces discontinuous highlighting, if needed. You
 *    typically call the ATSUHighlightText function every time you need
 *    to draw or redraw highlighted text.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout containing text to be highlighted.
 *    
 *    iTextBasePointX:
 *      The x-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iTextBasePointY:
 *      The y-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iHighlightStart:
 *      The first character of the text range to be highlighted. If the
 *      text range spans multiple lines, you should call
 *      ATSUHighlightText for each line, passing the offset
 *      corresponding to the beginning of the new line to draw with
 *      each call. To indicate that the specified text range starts at
 *      the beginning of the text buffer, you can pass the constant
 *      kATSUFromTextBeginning. To specify the entire text buffer, pass
 *      kATSUFromTextBeginning in this parameter and kATSUToTextEnd in
 *      the iHighlightLength parameter.
 *    
 *    iHighlightLength:
 *      The length of the text range to be highlighted. To indicate
 *      that the text range extends to the end of the text buffer, pass
 *      the constant kATSUToTextEnd.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUHighlightText(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUUnhighlightText()
 *  
 *  Summary:
 *    Renders a previously highlighted range of text in an
 *    unhighlighted state.
 *  
 *  Discussion:
 *    This function renders a previously highlighted range of text in
 *    an unhighlighted state. You should always call
 *    ATSUUnhighlightText after calling the function ATSUHighlightText
 *    to properly redraw the unhighlighted text and background. If the
 *    inversion method of highlighting was used, when you call
 *    ATSUUnhighlightText, it merely undoes the inversion and renders
 *    the text. If the redraw method of highlighting was used,
 *    ATSUUnhighlightText turns off the highlighting and restores the
 *    desired background. Depending on the complexity of the
 *    background, ATSUI restores the background in one of two ways:
 *    filling in a solid color, or repainting the background using a
 *    callback. See the function ATSUSetHighlightingMethod and the
 *    definition ATSUUnhighlightData for more information.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout containing text to be unhighlighted.
 *    
 *    iTextBasePointX:
 *      The x-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iTextBasePointY:
 *      The y-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iHighlightStart:
 *      The first character of the text range to be unhighlighted. If
 *      the text range spans multiple lines, you should call
 *      ATSUUnhighlightText for each line, passing the offset
 *      corresponding to the beginning of the new line to draw with
 *      each call. To indicate that the specified text range starts at
 *      the beginning of the text buffer, you can pass the constant
 *      kATSUFromTextBeginning. To specify the entire text buffer, pass
 *      kATSUFromTextBeginning in this parameter and kATSUToTextEnd in
 *      the iHighlightLength parameter.
 *    
 *    iHighlightLength:
 *      The length of the text range to be unhighlighted. To indicate
 *      that the text range extends to the end of the text buffer, pass
 *      the constant kATSUToTextEnd.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUUnhighlightText(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTextHighlight()
 *  
 *  Summary:
 *    Obtains the highlight region for a range of text.
 *  
 *  Discussion:
 *    Use this function to obtain the screen region that ATSUI would
 *    normally highlight automatically when ATSUHighlightText is
 *    called. This is useful if you wish to perform your own
 *    highlighting.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout containing text to be highlighted.
 *    
 *    iTextBasePointX:
 *      The x-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iTextBasePointY:
 *      The y-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iHighlightStart:
 *      The first character of the text range to be highlighted. If the
 *      text range spans multiple lines, you should call
 *      ATSUGetTextHighlight for each line, passing the offset
 *      corresponding to the beginning of the new line to draw with
 *      each call. To indicate that the specified text range starts at
 *      the beginning of the text buffer, you can pass the constant
 *      kATSUFromTextBeginning. To specify the entire text buffer, pass
 *      kATSUFromTextBeginning in this parameter and kATSUToTextEnd in
 *      the iHighlightLength parameter.
 *    
 *    iHighlightLength:
 *      The length of the text range to be highlighted. To indicate
 *      that the text range extends to the end of the text buffer, pass
 *      the constant kATSUToTextEnd.
 *    
 *    oHighlightRegion:
 *      On return, ATSUGetTextHighlight produces a MacRegion structure
 *      containing the highlight region for the specified range of
 *      text. In the case of discontinuous highlighting, the region
 *      consists of multiple components, with MacRegion.rgnBBox
 *      specifying the bounding box around the entire area of
 *      discontinuous highlighting.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetTextHighlight(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength,
  RgnHandle             oHighlightRegion)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUHighlightInactiveText()
 *  
 *  Summary:
 *    Highlights text using the standard Mac OS X UI convention for an
 *    inactive window or UI pane.
 *  
 *  Discussion:
 *    Use this function to redraw text when a window or UI pane
 *    containing highlighted text becomes inactive. Once the window or
 *    UI pane becomes active again, call ATSUHighlightText to
 *    rehighlight the text in active mode.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout containing text to be highlighted.
 *    
 *    iTextBasePointX:
 *      The x-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iTextBasePointY:
 *      The y-coordinate of the origin (in either the current graphics
 *      port or in a Quartz graphics context) of the line containing
 *      the text range. Pass the constant kATSUUseGrafPortPenLoc to
 *      draw relative to the current pen location in the current
 *      graphics port.
 *    
 *    iHighlightStart:
 *      The first character of the text range to be highlighted. If the
 *      text range spans multiple lines, you should call
 *      ATSUHighlightInactiveText for each line, passing the offset
 *      corresponding to the beginning of the new line to draw with
 *      each call. To indicate that the specified text range starts at
 *      the beginning of the text buffer, you can pass the constant
 *      kATSUFromTextBeginning. To specify the entire text buffer, pass
 *      kATSUFromTextBeginning in this parameter and kATSUToTextEnd in
 *      the iHighlightLength parameter.
 *    
 *    iHighlightLength:
 *      The length of the text range to be highlighted. To indicate
 *      that the text range extends to the end of the text buffer, pass
 *      the constant kATSUToTextEnd.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUHighlightInactiveText(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength)                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI hit-testing                                                           */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUPositionToOffset()
 *  
 *  Summary:
 *    Obtains the memory offset for the glyph edge nearest a mouse-down
 *    event.
 *  
 *  Discussion:
 *    The process of hit-testing text obtains the location of a
 *    mouse-down event relative both to the position of onscreen glyphs
 *    and to the corresponding offset between character codes in
 *    memory. You can then use the location information obtained by
 *    hit-testing to set the insertion point (that is, the caret) or
 *    selection range (for highlighting). Hit-testing text is
 *    complicated by the fact that a given line of text may be
 *    bidirectional. Therefore, the onscreen order of glyphs may not
 *    readily correspond to the storage order of the corresponding
 *    character codes. And the concept of which glyph comes "first" in
 *    a line of text cannot always be limited to the visual terms
 *    "left" and "right." Because of these complexities, it is more
 *    accurate to speak in terms of "leading" and "trailing" edges to
 *    glyphs. A "leading edge" is defined as the edge of a glyph that
 *    you first encounter when you read the text that includes that
 *    glyph. For example, when reading Roman text, you first encounter
 *    the left edge of a Roman glyph. Similarly, the "trailing edge" is
 *    defined as the edge of the glyph encountered last. This function
 *    produces the memory offset corresponding to the glyph edge
 *    nearest the event. If the mouse-down event occurs at a line
 *    direction boundary or within a glyph cluster,
 *    ATSUPositionToOffset produces two offsets. You can then provide
 *    the offset(s) to the ATSUOffsetToPosition function to obtain the
 *    actual caret position(s) for the event. When you call the
 *    ATSUPositionToOffset function, ATSUI examines the Unicode
 *    directionality of the character corresponding to the event
 *    location. The ATSUPositionToOffset function produces a value of
 *    true in the oIsLeading parameter if the offset is leading (that
 *    is, more closely associated with the subsequent character in
 *    memory and therefore indicative of a left-to-right line
 *    direction). It produces a value of false if the offset is
 *    trailing (that is, more closely associated with the preceding
 *    character in memory and indicative of a right-to-left line
 *    direction). Finally, note that when the event occurs beyond the
 *    leftmost or rightmost caret positions of the line (not taking
 *    into account line rotation), such that no glyph corresponds to
 *    the location of the hit, the ATSUPositionToOffset function
 *    produces the primary offset of the closest edge of the line to
 *    the input location. The oIsLeading flag depends on the
 *    directionality of the closest glyph and the side of the line to
 *    which the input location is closest. In this case, the secondary
 *    offset is equal to the primary offset, since no glyph was hit.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout object in which the mouse-down event occurred.
 *    
 *    iLocationX:
 *      The x-coordinate of the event, in local coordinates, relative
 *      to the origin of the line where the event occurred. That is, to
 *      specify the x-coordinate value, you should subtract the
 *      x-coordinate of the line origin from the x-coordinate of the
 *      hit point (in local coordinates). You can pass the constant
 *      kATSUUseGrafPortPenLoc for the location of the mouse-down event
 *      relative to the current pen location in the current graphics
 *      port.
 *    
 *    iLocationY:
 *      The y-coordinate of the event, in local coordinates, relative
 *      to the origin of the line where the event occurred. That is, to
 *      specify the y-coordinate value, you should subtract the
 *      y-coordinate of the line origin from the y-coordinate of the
 *      hit point (in local coordinates). You can pass the constant
 *      kATSUUseGrafPortPenLoc for the location of the mouse-down event
 *      relative to the current pen location in the current graphics
 *      port.
 *    
 *    ioPrimaryOffset:
 *      On input, a pointer to a UniCharArrayOffset value specifying
 *      the offset corresponding to the beginning of the line where the
 *      event occurred. On return, the value specifies the offset
 *      corresponding to the glyph edge that is visually closest to the
 *      event. To determine whether this offset indicates the leading
 *      or trailing edge of the glyph, you can examine the value
 *      produced in the oIsLeading parameter.
 *    
 *    oIsLeading:
 *      On return, the value indicates whether the offset produced in
 *      the ioPrimaryOffset parameter is leading or trailing. The
 *      function ATSUPositionToOffset produces a value of true if the
 *      offset is leading (that is, more closely associated with the
 *      subsequent character in memory). It produces a value of false
 *      if the offset is trailing (that is, more closely associated
 *      with the preceding character in memory).
 *    
 *    oSecondaryOffset:
 *      On return, the value typically specifies the same offset as
 *      that produced in the ioPrimaryOffset parameter, unless the
 *      event occurred within a glyph cluster or at a line direction
 *      boundary. If so, the value specifies a secondary offset. The
 *      secondary offset is associated with the glyph that has a
 *      different direction from the primary line direction.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUPositionToOffset(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY,
  UniCharArrayOffset *  ioPrimaryOffset,
  Boolean *             oIsLeading,
  UniCharArrayOffset *  oSecondaryOffset)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUOffsetToPosition()
 *  
 *  Summary:
 *    Obtains the caret position(s) corresponding to a memory offset.
 *  
 *  Discussion:
 *    This function produces two structures of type ATSUCaret. These
 *    structures contain the pen positioning information needed to draw
 *    the caret(s) for the event, specified relative to the origin of
 *    the line in the current graphics port or graphics context.
 *    Specifically, the ATSUCaret structures contain x-y coordinates
 *    for both the caret's starting and ending pen positions (the
 *    latter taking into account line rotation, caret slanting, and
 *    split-caret appearances). If the offset you pass to
 *    ATSUOffsetToPosition is at a line boundary, the structure
 *    produced in the oMainCaret parameter contains the starting and
 *    ending pen locations for the high caret, while the oSecondCaret
 *    parameter contains the corresponding values for the low caret. If
 *    the offset is not at a line boundary, both parameters contain the
 *    starting and ending pen locations of the main caret. Because you
 *    provide the ATSUOffsetToPosition function an offset relative to
 *    the origin of the line where the hit occurred,
 *    ATSUOffsetToPosition produces positioning information that is
 *    also relative. Therefore, you must transform the positions
 *    produced by the ATSUOffsetToPosition function before drawing the
 *    caret(s). To transform the caret location(s), add the starting
 *    and ending caret coordinates to the coordinates of the origin of
 *    the line in which the hit occurred. For example, if
 *    ATSUOffsetToPosition produces starting and ending pen locations
 *    of (25,0), (25,25) in the oMainCaret parameter (and the
 *    oSecondCaret parameter contains the same coordinates, meaning
 *    that the caret was not split), you would add these to the
 *    position of the origin of the line in the graphics port or
 *    context. If the position of the line origin was at (50,50), then
 *    the starting and ending pen locations of the caret would be
 *    (75,50), (75,75).
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout containing the offset.
 *    
 *    iOffset:
 *      The offset into the text buffer for which you wish to obtain a
 *      caret position. To respond to a mouse-down event, pass the
 *      offset returned in the ioPrimaryOffset parameter from the
 *      function ATSUPositionToOffset. That is, the offset
 *      corresponding to the glyph edge closest to the event.
 *    
 *    iIsLeading:
 *      A Boolean value indicating whether the offset corresponds to
 *      the leading or trailing edge of the glyph. You can obtain this
 *      information from the function ATSUPositionToOffset. This value
 *      is relevant if the offset occurs at a line direction boundary
 *      or within a glyph cluster.
 *    
 *    oMainCaret:
 *      On return, contains the starting and ending pen locations of
 *      the high caret if the value produced in oCaretIsSplit is true.
 *      If the value is false, the structure contains the starting and
 *      ending pen locations of the main caret.
 *    
 *    oSecondCaret:
 *      On return, contains the starting and ending pen locations of
 *      the low caret if the value passed back in the oCaretIsSplit
 *      parameter is true. If the value is false, the structure
 *      contains the starting and ending pen locations of the main
 *      caret (that is, the same values as the oMainCaret parameter).
 *    
 *    oCaretIsSplit:
 *      On return, indicates whether the offset specified in the
 *      iOffset parameter occurs at a line direction boundary. If true,
 *      the offset occurs at a line direction boundary; otherwise,
 *      false.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUOffsetToPosition(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iOffset,
  Boolean              iIsLeading,
  ATSUCaret *          oMainCaret,
  ATSUCaret *          oSecondCaret,
  Boolean *            oCaretIsSplit)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUPositionToCursorOffset()
 *  
 *  Summary:
 *    Obtains the memory offset for the glyph edge nearest a mouse-down
 *    event, after a move of the specified length.
 *  
 *  Discussion:
 *    This function produces the memory offset for the glyph edge
 *    nearest a mouse-down event, after a move of the specified length.
 *    This offset corresponds to where an insertion point would be
 *    placed after the move.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which the mouse down event occured.
 *    
 *    iLocationX:
 *      The x-coordinate of the event, in local coordinates, relative
 *      to the origin of the line where the event occurred. That is, to
 *      specify the x-coordinate value, you should subtract the
 *      x-coordinate of the line origin from the x-coordinate of the
 *      hit point (in local coordinates). You can pass the constant
 *      kATSUUseGrafPortPenLoc for the location of the mouse-down event
 *      relative to the current pen location in the current graphics
 *      port.
 *    
 *    iLocationY:
 *      The y-coordinate of the event, in local coordinates, relative
 *      to the origin of the line where the event occurred. That is, to
 *      specify the y-coordinate value, you should subtract the
 *      y-coordinate of the line origin from the y-coordinate of the
 *      hit point (in local coordinates). You can pass the constant
 *      kATSUUseGrafPortPenLoc for the location of the mouse-down event
 *      relative to the current pen location in the current graphics
 *      port.
 *    
 *    iMovementType:
 *      A constant specifying the type of cursor movement to use. See
 *      the definition of ATSUCursorMovementType for possible values to
 *      pass for this parameter.
 *    
 *    ioPrimaryOffset:
 *      On input, the offset corresponding to the beginning of the line
 *      where the event occurred. On return, the offset corresponding
 *      to the glyph edge nearest the event, after a movement of the
 *      specified type. This offset corresponds to where the insertion
 *      point would be placed after the move. To determine whether this
 *      offset indicates the leading or trailing edge of the glyph, you
 *      can examine the value produced in the oIsLeading parameter.
 *    
 *    oIsLeading:
 *      On return, the value indicates whether the offset produced in
 *      the ioPrimaryOffset parameter is leading or trailing. The
 *      ATSUPositionToOffset function produces a value of true if the
 *      offset is leading (that is, more closely associated with the
 *      subsequent character in memory). It produces a value of false
 *      if the offset is trailing (that is, more closely associated
 *      with the preceding character in memory).
 *    
 *    oSecondaryOffset:
 *      On return, the value typically specifies the same offset as
 *      that produced in the ioPrimaryOffset parameter, unless the
 *      event occurred within a glyph cluster or at a line direction
 *      boundary. If so, the value specifies the secondary offset, for
 *      the glyph edge furthest from the event.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.2.2 and later
 */
extern OSStatus 
ATSUPositionToCursorOffset(
  ATSUTextLayout           iTextLayout,
  ATSUTextMeasurement      iLocationX,
  ATSUTextMeasurement      iLocationY,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     ioPrimaryOffset,
  Boolean *                oIsLeading,
  UniCharArrayOffset *     oSecondaryOffset)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUOffsetToCursorPosition()
 *  
 *  Summary:
 *    Obtains the caret position(s) corresponding to a memory offset,
 *    after a move of the specified length.
 *  
 *  Discussion:
 *    Use this function in conjunction with ATSUPositionToCursorOffset
 *    to determine where to draw the caret after a mouse-down event.
 *    The movement type parameter allows you to have the cursor "snap"
 *    to different parts of the text depending on the type of movement
 *    selected (i.e., words or characters). See the definition of
 *    ATSUCursorMovementType for more information on possible values.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout object in which the mouse-down event occurred.
 *    
 *    iOffset:
 *      The offset corresponding to the glyph edge nearest the event,
 *      after a movement of the specified type. You can obtain this
 *      value by examining the offset produced in the ioPrimaryOffset
 *      parameter of the function ATSUPositionToCursorOffset.
 *    
 *    iIsLeading:
 *      A Boolean value indicating whether the specified offset
 *      corresponds to the leading or trailing edge of the glyph. You
 *      can obtain this information from the function
 *      ATSUPositionToCursorOffset . This value is relevant if the
 *      offset occurs at a line direction boundary or within a glyph
 *      cluster.
 *    
 *    iMovementType:
 *      A constant specifying the unit of cursor movement. See the
 *      definition of ATSUCursorMovementType for possible values to
 *      pass for this parameter.
 *    
 *    oMainCaret:
 *      On return, the structure contains the starting and ending pen
 *      locations of the high caret if the value produced in the
 *      oCaretIsSplit parameter is true. If the value is false, the
 *      structure contains the starting and ending pen locations of the
 *      main caret.
 *    
 *    oSecondCaret:
 *      On return, the structure contains the starting and ending pen
 *      locations of the low caret if the value passed back in the
 *      oCaretIsSplit parameter is true. If the value is false, the
 *      structure contains the starting and ending pen locations of the
 *      main caret (that is, the same values as the oMainCaret
 *      parameter).
 *    
 *    oCaretIsSplit:
 *      On return, the value indicates whether the offset specified in
 *      the iOffset parameter occurs at a line direction boundary. If
 *      true, the offset occurs at a line direction boundary;
 *      otherwise, false.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.2.2 and later
 */
extern OSStatus 
ATSUOffsetToCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOffset,
  Boolean                  iIsLeading,
  ATSUCursorMovementType   iMovementType,
  ATSUCaret *              oMainCaret,
  ATSUCaret *              oSecondCaret,
  Boolean *                oCaretIsSplit)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI cursor movement                                                       */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUNextCursorPosition()
 *  
 *  Summary:
 *    Obtains the memory offset for the insertion point that follows
 *    the current insertion point in storage order, as determined by a
 *    move of the specified length and type.
 *  
 *  Discussion:
 *    Together with ATSUPreviousCursorPosition, this function allows an
 *    application to "walk" the text buffer in storage order, moving
 *    the cursor by a specified amount and movement type at each step.
 *    To move through the text buffer in screen order, use the
 *    functions ATSURightwardCursorPosition and
 *    ATSULeftwardCursorPosition.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which to perform the cursor movement.
 *    
 *    iOldOffset:
 *      The previous cursor position.
 *    
 *    iMovementType:
 *      A constant specifying the unit of cursor movement. See the
 *      definition of ATSUCursorMovementType for possible values to
 *      pass for this parameter.
 *    
 *    oNewOffset:
 *      On return, the new cursor position.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUNextCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUPreviousCursorPosition()
 *  
 *  Summary:
 *    Obtains the memory offset for the insertion point that preceeds
 *    the current insertion point in storage order, as determined by a
 *    move of the specified length and type.
 *  
 *  Discussion:
 *    Together with ATSUNextCursorPosition, this function allows an
 *    application to "walk" the text buffer in storage order, moving
 *    the cursor by a specified amount and movement type at each step.
 *    To move through the text buffer in screen order, use the
 *    functions ATSURightwardCursorPosition and
 *    ATSULeftwardCursorPosition.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which to perform the cursor movement.
 *    
 *    iOldOffset:
 *      The previous cursor position.
 *    
 *    iMovementType:
 *      A constant specifying the unit of cursor movement. See the
 *      definition of ATSUCursorMovementType for possible values to
 *      pass for this parameter.
 *    
 *    oNewOffset:
 *      On return, the new cursor position.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUPreviousCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSURightwardCursorPosition()
 *  
 *  Summary:
 *    Obtains the memory offset for the insertion point that is to the
 *    right of the current insertion point, as determined by a move of
 *    the specified length and type.
 *  
 *  Discussion:
 *    Together with ATSULeftwardCursorPosition, this function allows an
 *    application to "walk" the text buffer in screen order, moving the
 *    cursor by a specified amount and movement type at each step. To
 *    move through the text buffer in storage order, use the functions
 *    ATSUNextCursorPosition and ATSUPreviousCursorPosition. Note that
 *    if you are drawing the cursor after a cursor move, you should use
 *    ATSUOffsetToPosition to obtain an ATSUCaret that determines the
 *    on screen location of the new cursor position. Always store the
 *    ATSUCaret from the previous cursor position as well, as this can
 *    help determine which caret to use in the case of a split caret.
 *    When performing leftward and rightward cursor movement, always
 *    use the caret closest to the previous caret. This maintains
 *    visual order when moving the cursor on screen.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which to perform the cursor movement.
 *    
 *    iOldOffset:
 *      The previous cursor position.
 *    
 *    iMovementType:
 *      A constant specifying the unit of cursor movement. See the
 *      definition of ATSUCursorMovementType for possible values to
 *      pass for this parameter.
 *    
 *    oNewOffset:
 *      On return, the new cursor position.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSURightwardCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSULeftwardCursorPosition()
 *  
 *  Summary:
 *    Obtains the memory offset for the insertion point that is to the
 *    left of the current insertion point, as determined by a move of
 *    the specified length and type.
 *  
 *  Discussion:
 *    Together with ATSURightwardCursorPosition, this function allows
 *    an application to "walk" the text buffer in screen order, moving
 *    the cursor by a specified amount and movement type at each step.
 *    To move through the text buffer in storage order, use the
 *    functions ATSUNextCursorPosition and ATSUPreviousCursorPosition.
 *    Note that if you are drawing the cursor after a cursor move, you
 *    should use ATSUOffsetToPosition to obtain an ATSUCaret that
 *    determines the on screen location of the new cursor position.
 *    Always store the ATSUCaret from the previous cursor position as
 *    well, as this can help determine which caret to use in the case
 *    of a split caret. When performing leftward and rightward cursor
 *    movement, always use the caret closest to the previous caret.
 *    This maintains visual order when moving the cursor on screen.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which to perform the cursor movement.
 *    
 *    iOldOffset:
 *      The previous cursor position.
 *    
 *    iMovementType:
 *      A constant specifying the unit of cursor movement. See the
 *      definition of ATSUCursorMovementType for possible values to
 *      pass for this parameter.
 *    
 *    oNewOffset:
 *      On return, the new cursor position.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSULeftwardCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Functions listed beyond this point are either deprecated or not recommended */

/*
 *  ATSUMeasureText()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUGetUnjustifiedBounds instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    ATSUGetUnjustifiedBounds instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUMeasureText(
  ATSUTextLayout         iTextLayout,
  UniCharArrayOffset     iLineStart,
  UniCharCount           iLineLength,
  ATSUTextMeasurement *  oTextBefore,
  ATSUTextMeasurement *  oTextAfter,
  ATSUTextMeasurement *  oAscent,
  ATSUTextMeasurement *  oDescent)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;



#ifdef __cplusplus
}
#endif

#endif /* __ATSUNICODEDRAWING__ */

