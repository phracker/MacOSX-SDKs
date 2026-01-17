//
//  JRSFont.h
//  Copyright 2008 Apple Inc. All rights reserved.
//
//	Advanced font handling.
//

#import <ApplicationServices/ApplicationServices.h>
#import <JavaVM/jni.h>


typedef uint32_t JRSFontRenderingStyle;


// returns the desired text rendering style for sun.awt.SunHints
// FRACTIONALMETRICS and TEXT_ANTIALIASING
JRSFontRenderingStyle JRSFontGetRenderingStyleForHints(const jint fmHint, const jint aaHint);

// returns an altered style which is more appropriate for measuring, but not striking glyphs
//JRSFontRenderingStyle JRSFontAlignStyleForMeasurement(const JRSFontRenderingStyle style);

JRSFontRenderingStyle JRSFontAlignStyleForFractionalMeasurement(const JRSFontRenderingStyle style);

JRSFontRenderingStyle JRSFontAlignStyleForIntegerMeasurement(JRSFontRenderingStyle style);

// checks if this style represents a character strike that would returns a fractional sizes
bool JRSFontStyleUsesFractionalMetrics(const JRSFontRenderingStyle style);

// checks if this the style supports antialiasing
bool JRSFontStyleIsAntialiased(const JRSFontRenderingStyle style);


// returns the text rendering style on a context
JRSFontRenderingStyle JRSFontGetRenderingStyleForContext(const CGContextRef context);

// applies a text rendering style onto a context
void JRSFontSetRenderingStyleOnContext(const CGContextRef context, const JRSFontRenderingStyle style);


// creates or retains the provided font that can best cover the provided characters
CTFontRef JRSFontCreateFallbackFontForCharacters(const CTFontRef font, const UTF16Char *unichars, const CFIndex length);

// fills an array of advances for glyphs of a particular font, transform, and style
//	returns the total distance of the glyph run
CGFloat JRSFontGetAdvancesForGlyphsAndStyle(const CTFontRef font, const CGAffineTransform *tx, const JRSFontRenderingStyle style, const CGGlyph glyphs[], size_t count, CGSize advances[]);

// fills an array of bounding boxes for glyphs of a particular font, transform, and style
//	returns the bounding box of the overall bounding rect of the glyph run
CGRect JRSFontGetBoundingBoxesForGlyphsAndStyle(const CTFontRef font, const CGAffineTransform *tx, const JRSFontRenderingStyle style, const CGGlyph glyphs[], size_t count, CGRect bboxes[]);
