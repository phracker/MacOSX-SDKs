/*	
	NSAttributedString.h
	Copyright (c) 1994-2003, Apple Computer, Inc.
	All rights reserved.

	This file defines Application Kit extensions to NSAttributedString and NSMutableAttributedString.
*/

#import <Foundation/NSAttributedString.h>
#import <AppKit/NSFontManager.h>
#import <AppKit/NSText.h>
#import <AppKit/AppKitDefines.h>
@class NSFileWrapper, NSURL;

/* Predefined character attributes for text. If the key is not in the dictionary, then use the default values as described below.
*/
APPKIT_EXTERN NSString *NSFontAttributeName;             /* NSFont, default Helvetica 12 */
APPKIT_EXTERN NSString *NSParagraphStyleAttributeName;   /* NSParagraphStyle, default defaultParagraphStyle */
APPKIT_EXTERN NSString *NSForegroundColorAttributeName;  /* NSColor, default blackColor */
APPKIT_EXTERN NSString *NSUnderlineStyleAttributeName;   /* int, default 0: no underline */
APPKIT_EXTERN NSString *NSSuperscriptAttributeName;      /* int, default 0 */
APPKIT_EXTERN NSString *NSBackgroundColorAttributeName;  /* NSColor, default nil: no background */
APPKIT_EXTERN NSString *NSAttachmentAttributeName;       /* NSTextAttachment, default nil */
APPKIT_EXTERN NSString *NSLigatureAttributeName;         /* int, default 1: default ligatures, 0: no ligatures, 2: all ligatures */
APPKIT_EXTERN NSString *NSBaselineOffsetAttributeName;   /* float, in points; offset from baseline, default 0 */
APPKIT_EXTERN NSString *NSKernAttributeName;             /* float, amount to modify default kerning, if 0, kerning off */
APPKIT_EXTERN NSString *NSLinkAttributeName;		 /* ??? id <NSTextLink>; link */

APPKIT_EXTERN NSString *NSStrokeWidthAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* float, in percent of font point size, default 0: no stroke; positive for stroke alone, negative for stroke and fill (a typical value for outlined text would be 3.0) */
APPKIT_EXTERN NSString *NSStrokeColorAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* NSColor, default nil: same as foreground color */
APPKIT_EXTERN NSString *NSUnderlineColorAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* NSColor, default nil: same as foreground color */
APPKIT_EXTERN NSString *NSStrikethroughStyleAttributeName	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* int, default 0: no strikethrough */
APPKIT_EXTERN NSString *NSStrikethroughColorAttributeName	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* NSColor, default nil: same as foreground color */
APPKIT_EXTERN NSString *NSShadowAttributeName			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* NSShadow, default nil: no shadow */
APPKIT_EXTERN NSString *NSObliquenessAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* float; skew to be applied to glyphs, default 0: no skew */
APPKIT_EXTERN NSString *NSExpansionAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* float; log of expansion factor to be applied to glyphs, default 0: no expansion */
APPKIT_EXTERN NSString *NSCursorAttributeName			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* NSCursor, default IBeamCursor */
APPKIT_EXTERN NSString *NSToolTipAttributeName			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	/* NSString, default nil: no tooltip */

/* An integer value.  The value is interpreted as Apple Type Services kCharacterShapeType selector + 1.
 * default is 0 (disable). 1 is kTraditionalCharactersSelector and so on.
 * Refer to <ATS/SFNTLayoutTypes.h>
 */
APPKIT_EXTERN NSString *NSCharacterShapeAttributeName;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
/* An NSGlyphInfo object.  This provides a means to override the standard glyph generation.  NSLayoutManager will assign the glyph specified by this glyph info to the entire attribute range, provided that its contents match the specified base string, and that the specified glyph is available in the font specified by NSFontAttributeName.
*/
APPKIT_EXTERN NSString *NSGlyphInfoAttributeName;
#endif

/* This defines currently supported values for NSUnderlineStyleAttributeName and NSStrikethroughAttributeName, as of Mac OS X version 10.3.  The style, pattern, and optionally by-word mask are or'd together to produce the value.  The previous constants are still supported, but deprecated (except for NSUnderlineByWordMask); including NSUnderlineStrikethroughMask in the underline style will still produce a strikethrough, but that is deprecated in favor of setting NSStrikethroughStyleAttributeName using the values described here.
*/
enum {
    NSUnderlineStyleNone		= 0x00,
    NSUnderlineStyleSingle		= 0x01,
    NSUnderlineStyleThick		= 0x02,
    NSUnderlineStyleDouble		= 0x09
};

enum {
    NSUnderlinePatternSolid		= 0x0000,
    NSUnderlinePatternDot		= 0x0100,
    NSUnderlinePatternDash		= 0x0200,
    NSUnderlinePatternDashDot		= 0x0300,
    NSUnderlinePatternDashDotDot	= 0x0400
};

APPKIT_EXTERN unsigned NSUnderlineByWordMask; 

/* Values returned for the @"DocumentType" key in the document attributes dictionary when reading text documents. Note that other values are possible, and this set might grow in the future.
*/
APPKIT_EXTERN NSString *NSPlainTextDocumentType;
APPKIT_EXTERN NSString *NSRTFTextDocumentType;
APPKIT_EXTERN NSString *NSRTFDTextDocumentType;
APPKIT_EXTERN NSString *NSMacSimpleTextDocumentType;
APPKIT_EXTERN NSString *NSHTMLTextDocumentType;
APPKIT_EXTERN NSString *NSDocFormatTextDocumentType	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSWordMLTextDocumentType	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


@interface NSAttributedString (NSAttributedStringKitAdditions)

- (NSDictionary *)fontAttributesInRange:(NSRange)range; /* Attributes which should be copied/pasted with "copy font" */
- (NSDictionary *)rulerAttributesInRange:(NSRange)range; /* Attributes which should be copied/pasted with "copy ruler" */

- (BOOL)containsAttachments;

/* Returns NSNotFound if no line break location found in the specified range; otherwise returns the index of the first character that should go on the NEXT line.
*/
- (unsigned)lineBreakBeforeIndex:(unsigned)location withinRange:(NSRange)aRange;
#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (unsigned)lineBreakByHyphenatingBeforeIndex:(unsigned)location withinRange:(NSRange)aRange;
#endif
- (NSRange)doubleClickAtIndex:(unsigned)location;
- (unsigned)nextWordFromIndex:(unsigned)location forward:(BOOL)isForward;

/* Methods to determine what types can be loaded as NSAttributedStrings */
+ (NSArray *)textUnfilteredFileTypes;
+ (NSArray *)textUnfilteredPasteboardTypes;
+ (NSArray *)textFileTypes;
+ (NSArray *)textPasteboardTypes;

/* Methods to load text documents in various formats. The first two will examine the specified file and do their best to load it in whatever format it's in. The others load the file in the specified format. 
In all of these functions, if dict is not NULL, the init methods return a dictionary with various document-wide attributes. Currently supported attributes are:
    @"PaperSize" (NSValue containing NSSize)
    @"LeftMargin", @"RightMargin", @"TopMargin", @"BottomMargin" (all NSNumbers containing floats, in points)
    @"HyphenationFactor" (NSNumber containing float)
    @"ViewSize" (NSValue containing NSSize)
    @"ViewZoom" (NSNumber containing float; 100 == 100% zoom)
    @"ViewMode" (NSNumber containing int; 0 = normal; 1 = page layout)
    @"DocumentType" (Returns how the document was interpreted; one of the values above)
    @"CharacterEncoding" (For plain text files only; NSNumber containing int specifying NSStringEncoding used to interpret the file)
    @"CocoaRTFVersion" (If RTF file, stores the version of Cocoa the file was created with. NSNumber containing int. Absence of this value indicates RTF file not created by Cocoa or its predecessors. 100 is MacOSX; lower values are pre-MacOSX)
    @"ReadOnly" (NSNumber containing int; if missing, or 0 or negative, not readonly; 1 or more, readonly. Note that this has nothing to do with the file system protection on the file, but instead, on how the file should be displayed to the user)
    @"Converted" (NSNumber containing int; if missing, or 0, the file was originally in the format specified by document type; if negative, the file was originally in the format specified by document type, but the conversion to NSAttributedString may have been lossy; if 1 or more, it was converted to the specified type by a filter service)
    @"DefaultTabInterval" (NSNumber containing float, representing the document-wide default tab stop interval)
    @"BackgroundColor" (NSColor, representing the document-wide page background color)
*/
- (id)initWithPath:(NSString *)path documentAttributes:(NSDictionary **)dict;
- (id)initWithURL:(NSURL *)url documentAttributes:(NSDictionary **)dict;
- (id)initWithRTF:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithRTFD:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithRTFDFileWrapper:(NSFileWrapper *)wrapper documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data baseURL:(NSURL *)base documentAttributes:(NSDictionary **)dict;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (id)initWithDocFormat:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict;
    // See below for a description of the possible contents of the options dictionary.
#endif

/* These creation methods take an optional dictionary to allow writing out document-wide attributes (for RTF, all of the above attributes except @"DocumentType", @"CharacterEncoding", @"CocoaRTFVersion", and @"Converted" are supported).
*/
- (NSData *)RTFFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
- (NSData *)RTFDFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
- (NSFileWrapper *)RTFDFileWrapperFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSData *)docFormatFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
#endif

@end


@interface NSMutableAttributedString (NSMutableAttributedStringKitAdditions)

/* Set the contents of the mutable attributed string from the file at the specified URL.  opts can contain:
     @"CharacterEncoding" (For plain text or HTML documents; NSNumber containing the unsigned int NSStringEncoding to be used if the encoding cannot be determined from the document)
     @"BaseURL" (For HTML documents; NSURL containing base URL)
     @"DefaultAttributes" (NSDictionary containing attributes to be applied to plain files)
     @"DocumentType" (One of the NSStrings above, indicating a document type to be forced when loading the document)
On return, the documentAttributes dictionary (if provided) contains the various keys described above (in the init methods).

In Mac OS X 10.3, there are some additional options keys that are recognized for HTML documents, both by these methods and by -[NSAttributedString initWithHTML:options:documentAttributes:], as follows:
     @"UseWebKit" (NSNumber containing int; if present and positive, forces WebKit-based HTML importing be used; behavior in this case may differ from HTML import in Mac OS X 10.2 and before, particularly for tables)
     @"TextEncodingName" (NSString containing the name, IANA or otherwise, of a text encoding to be used if the encoding cannot be determined from the document; mutually exclusive with CharacterEncoding)
     @"Timeout" (NSNumber containing float; time in seconds to wait for a document to finish loading)
     @"WebPreferences" (WebPreferences; if WebKit-based HTML importing is used, specifies a WebPreferences object; if not present, a default set of preferences will be used)
     @"WebResourceLoadDelegate" (NSObject; if WebKit-based HTML importing is used, specifies an object to serve as the WebResourceLoadDelegate; if not present, a default delegate will be used that will permit the loading of subsidiary resources but will not respond to authentication challenges)
*/
- (BOOL)readFromURL:(NSURL *)url options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (BOOL)readFromData:(NSData *)data options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict;
#endif

/* Conveniences for setting character attributes
*/
- (void)superscriptRange:(NSRange)range; /* Increment superscript, make font smaller */
- (void)subscriptRange:(NSRange)range; /* Decrement superscript, make font smaller  */
- (void)unscriptRange:(NSRange)range; /* Undo any superscripting, removing effect of any prior super- or sub-scripting of the range */
- (void)applyFontTraits:(NSFontTraitMask)traitMask range:(NSRange)range; /* Multiple trait changes OK */
- (void)setAlignment:(NSTextAlignment)alignment range:(NSRange)range;

/* Methods to "fix" attributes after changes. In the abstract class these are not called automatically. The range arguments are the ranges in the final string.
*/
- (void)fixAttributesInRange:(NSRange)range; /* Calls below fix... methods */
- (void)fixFontAttributeInRange:(NSRange)range; /* Make sure the font attribute covers the characters */
- (void)fixParagraphStyleAttributeInRange:(NSRange)range; /* Make sure the paragraph style is valid. Might touch beyond range! */
- (void)fixAttachmentAttributeInRange:(NSRange)range; /* Make sure there are no attachments on non-attachment characters */

@end

/* Deprecated constants previously used for underline style.
*/
enum {
    NSNoUnderlineStyle = 0,
    NSSingleUnderlineStyle
};
APPKIT_EXTERN unsigned NSUnderlineStrikethroughMask;

