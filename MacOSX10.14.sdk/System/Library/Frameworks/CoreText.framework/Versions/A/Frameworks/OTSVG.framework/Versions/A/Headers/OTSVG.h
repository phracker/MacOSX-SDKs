//
//  OTSVG.h
//  OTSVG
//
//  Created by Myles C. Maxfield on 8/20/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef __OTSVG__
#define __OTSVG__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

// FIXME: Make Swift work, so Swift code doesn't have to call OTSVG*Release().
//CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

typedef const struct __OTSVGTable * OTSVGTableRef;
typedef const struct __OTSVGDocument * OTSVGDocumentRef;
typedef const struct __OTSVGGlyphRecording * OTSVGGlyphRecordingRef;

OTSVGTableRef __nullable OTSVGTableCreateFromData(CFDataRef __nullable svgTable, unsigned int unitsPerEm, CGFloat fontSize);
CFIndex OTSVGTableGetDocumentIndexForGlyph(OTSVGTableRef svgTable, CGGlyph glyph);
OTSVGDocumentRef __nullable OTSVGDocumentCreate(OTSVGTableRef svgTable, CFIndex documentIndex);
OTSVGGlyphRecordingRef __nullable OTSVGGlyphRecordingCreate(OTSVGDocumentRef svgDocument, CGGlyph glyph);
void OTSVGGlyphRecordingPlayback(OTSVGGlyphRecordingRef recording, CGContextRef context);
void OTSVGGlyphRecordingPlaybackRecordingsAtPositions(OTSVGGlyphRecordingRef __nullable * __nonnull recordings, const CGPoint *positions, size_t count, CGContextRef context);
CGRect OTSVGGlyphRecordingGetBoundingRect(OTSVGGlyphRecordingRef __nullable recording);
void OTSVGTableRelease(OTSVGTableRef __nullable svgTable);
void OTSVGDocumentRelease(OTSVGDocumentRef __nullable svgDocument);
void OTSVGGlyphRecordingRelease(OTSVGGlyphRecordingRef __nullable svgGlyphRecording);

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
//CF_IMPLICIT_BRIDGING_DISABLED

#endif
