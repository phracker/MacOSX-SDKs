/*
        NSGlyphGenerator.h
        Application Kit
        Copyright (c) 1993-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSAttributedString.h>
#import <AppKit/NSFont.h> // for NSGlyph

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* NSGlyphStorage layout options */
enum {
    NSShowControlGlyphs = (1 << 0), // if set, generates displayable glyphs for control chars
    NSShowInvisibleGlyphs = (1 << 1), // if set, generates displayable glyphs for invisible chars
    NSWantsBidiLevels = (1 << 2) // if set, generates bidi levels
};

@protocol NSGlyphStorage
- (void)insertGlyphs:(const NSGlyph *)glyphs length:(unsigned int)length forStartingGlyphAtIndex:(unsigned int)glyphIndex characterIndex:(unsigned int)charIndex;

// sets glyph attribute defined in NSLayoutManager.h
- (void)setIntAttribute:(int)attributeTag value:(int)val forGlyphAtIndex:(unsigned)glyphIndex;

- (NSAttributedString *)attributedString;
- (unsigned int)layoutOptions;
@end

@interface NSGlyphGenerator : NSObject
- (void)generateGlyphsForGlyphStorage:(id <NSGlyphStorage>)glyphStorage desiredNumberOfCharacters:(unsigned int)nChars glyphIndex:(unsigned int *)glyphIndex characterIndex:(unsigned int *)charIndex;

+ (id) sharedGlyphGenerator;
@end
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */
