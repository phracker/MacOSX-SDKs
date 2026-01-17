//
//  JRSFont.h
//  Copyright 2008 Apple Inc. All rights reserved.
//
//	Advanced font handling.
//

#import <ApplicationServices/ApplicationServices.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

typedef uint32_t JRSFontRenderingStyle;


// returns the desired text rendering style for sun.awt.SunHints
// FRACTIONALMETRICS and TEXT_ANTIALIASING
JRS_EXPORT JRSFontRenderingStyle JRSFontGetRenderingStyleForHints(const int fmHint, const int aaHint);

// returns an altered style which is more appropriate for measuring, but not striking glyphs
//JRSFontRenderingStyle JRSFontAlignStyleForMeasurement(const JRSFontRenderingStyle style);

JRS_EXPORT JRSFontRenderingStyle JRSFontAlignStyleForFractionalMeasurement(const JRSFontRenderingStyle style);

JRS_EXPORT JRSFontRenderingStyle JRSFontAlignStyleForIntegerMeasurement(JRSFontRenderingStyle style) JRS_DEPRECATED_2020;

// checks if this style represents a character strike that would returns a fractional sizes
JRS_EXPORT bool JRSFontStyleUsesFractionalMetrics(const JRSFontRenderingStyle style);

// checks if this the style supports antialiasing
JRS_EXPORT bool JRSFontStyleIsAntialiased(const JRSFontRenderingStyle style) JRS_DEPRECATED_2020;


// returns the text rendering style on a context
JRS_EXPORT JRSFontRenderingStyle JRSFontGetRenderingStyleForContext(const CGContextRef context);

// applies a text rendering style onto a context
JRS_EXPORT void JRSFontSetRenderingStyleOnContext(const CGContextRef context, const JRSFontRenderingStyle style);


// creates or retains the provided font that can best cover the provided characters
JRS_EXPORT CTFontRef JRSFontCreateFallbackFontForCharacters(const CTFontRef font, const UTF16Char *unichars, const CFIndex length);

// fills an array of advances for glyphs of a particular font, transform, and style
//	returns the total distance of the glyph run
JRS_EXPORT CGFloat JRSFontGetAdvancesForGlyphsAndStyle(const CTFontRef font, const CGAffineTransform *tx, const JRSFontRenderingStyle style, const CGGlyph glyphs[], size_t count, CGSize advances[]) JRS_DEPRECATED_2020;

// fills an array of bounding boxes for glyphs of a particular font, transform, and style
//	returns the bounding box of the overall bounding rect of the glyph run
JRS_EXPORT CGRect JRSFontGetBoundingBoxesForGlyphsAndStyle(const CTFontRef font, const CGAffineTransform *tx, const JRSFontRenderingStyle style, const CGGlyph glyphs[], size_t count, CGRect bboxes[]);

JRS_END_DECLS
