/*	
	NSGlyphInfo.h
	Copyright (c) 2002-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSString.h>
#import <AppKit/NSFont.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
typedef enum {
    NSIdentityMappingCharacterCollection = 0, // Identity mapping (CID == NSGlyph)
    NSAdobeCNS1CharacterCollection = 1, // Adobe-CNS1
    NSAdobeGB1CharacterCollection = 2, // Adobe-GB1
    NSAdobeJapan1CharacterCollection = 3, // Adobe-Japan1
    NSAdobeJapan2CharacterCollection = 4, // Adobe-Japan2
    NSAdobeKorea1CharacterCollection = 5, // Adobe-Korea1
} NSCharacterCollection;

@interface NSGlyphInfo : NSObject <NSCopying, NSCoding> {
    NSString *_baseString;
}

// Returns an NSGlyphInfo object for the glyph name such as "copyright."
+ (NSGlyphInfo *)glyphInfoWithGlyphName:(NSString *)glyphName forFont:(NSFont *)font baseString:(NSString *)theString;

// Returns an NSGlyphInfo object for the NSGlyph glyph
+ (NSGlyphInfo *)glyphInfoWithGlyph:(NSGlyph)glyph forFont:(NSFont *)font baseString:(NSString *)theString;

// Returns an NSGlyphInfo object for the CID/RO
+ (NSGlyphInfo *)glyphInfoWithCharacterIdentifier:(unsigned int)cid collection:(NSCharacterCollection)characterCollection baseString:(NSString *)theString;

// Returns the glyph name.  If the receiver is instantiated without glyph name, returns nil
- (NSString *)glyphName;

// Returns CID
- (unsigned int)characterIdentifier;

// Returns RO (character collection).  Returns NSIdentityMappingCharacterCollection if instantiated with NSGlyph or glyph name
- (NSCharacterCollection)characterCollection;
@end
#endif
