/*	
	NSAttributedString.h
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.

	This file defines Application Kit extensions to NSAttributedString and NSMutableAttributedString.
*/

#import <Foundation/NSAttributedString.h>
#import <AppKit/NSFontManager.h>
#import <AppKit/NSText.h>
#import <AppKit/AppKitDefines.h>
@class NSFileWrapper, NSURL, NSTextBlock, NSTextTable, NSTextList;

/* Predefined character attributes for text. If the key is not in the dictionary, then use the default values as described below.
*/
APPKIT_EXTERN NSString *NSFontAttributeName;             // NSFont, default Helvetica 12
APPKIT_EXTERN NSString *NSParagraphStyleAttributeName;   // NSParagraphStyle, default defaultParagraphStyle
APPKIT_EXTERN NSString *NSForegroundColorAttributeName;  // NSColor, default blackColor
APPKIT_EXTERN NSString *NSUnderlineStyleAttributeName;   // int, default 0: no underline
APPKIT_EXTERN NSString *NSSuperscriptAttributeName;      // int, default 0
APPKIT_EXTERN NSString *NSBackgroundColorAttributeName;  // NSColor, default nil: no background
APPKIT_EXTERN NSString *NSAttachmentAttributeName;       // NSTextAttachment, default nil
APPKIT_EXTERN NSString *NSLigatureAttributeName;         // int, default 1: default ligatures, 0: no ligatures, 2: all ligatures
APPKIT_EXTERN NSString *NSBaselineOffsetAttributeName;   // float, in points; offset from baseline, default 0
APPKIT_EXTERN NSString *NSKernAttributeName;             // float, amount to modify default kerning, if 0, kerning off
APPKIT_EXTERN NSString *NSLinkAttributeName;		 // NSURL (preferred) or NSString

APPKIT_EXTERN NSString *NSStrokeWidthAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // float, in percent of font point size, default 0: no stroke; positive for stroke alone, negative for stroke and fill (a typical value for outlined text would be 3.0)
APPKIT_EXTERN NSString *NSStrokeColorAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // NSColor, default nil: same as foreground color */
APPKIT_EXTERN NSString *NSUnderlineColorAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // NSColor, default nil: same as foreground color */
APPKIT_EXTERN NSString *NSStrikethroughStyleAttributeName	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // int, default 0: no strikethrough */
APPKIT_EXTERN NSString *NSStrikethroughColorAttributeName	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // NSColor, default nil: same as foreground color */
APPKIT_EXTERN NSString *NSShadowAttributeName			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // NSShadow, default nil: no shadow */
APPKIT_EXTERN NSString *NSObliquenessAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // float; skew to be applied to glyphs, default 0: no skew */
APPKIT_EXTERN NSString *NSExpansionAttributeName		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // float; log of expansion factor to be applied to glyphs, default 0: no expansion */
APPKIT_EXTERN NSString *NSCursorAttributeName			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // NSCursor, default IBeamCursor */
APPKIT_EXTERN NSString *NSToolTipAttributeName			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;  // NSString, default nil: no tooltip */

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

/* Values returned for the NSDocumentTypeDocumentAttribute key in the document attributes dictionary when reading text documents. Note that other values are possible, and this set might grow in the future.
*/
APPKIT_EXTERN NSString *NSPlainTextDocumentType;
APPKIT_EXTERN NSString *NSRTFTextDocumentType;
APPKIT_EXTERN NSString *NSRTFDTextDocumentType;
APPKIT_EXTERN NSString *NSMacSimpleTextDocumentType;
APPKIT_EXTERN NSString *NSHTMLTextDocumentType;
APPKIT_EXTERN NSString *NSDocFormatTextDocumentType	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSWordMLTextDocumentType	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSWebArchiveTextDocumentType	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The following are keys for various attributes that can be specified as document attributes in the text read/write APIs further below. Note that the items in the first set have been around since early 10.x releases; but the actual identifier shown below was added in 10.4. If you want your app to run on earlier systems, you need to continue using the actual string value that these identifiers represent. The actual string value is specified in the comments below.
*/
APPKIT_EXTERN NSString *NSPaperSizeDocumentAttribute    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"PaperSize", NSValue containing NSSize (in points)
APPKIT_EXTERN NSString *NSLeftMarginDocumentAttribute   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"LeftMargin", NSNumber containing floating point value (in points)
APPKIT_EXTERN NSString *NSRightMarginDocumentAttribute  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"RightMargin", NSNumber containing floating point value (in points)
APPKIT_EXTERN NSString *NSTopMarginDocumentAttribute    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"TopMargin", NSNumber containing floating point value (in points)
APPKIT_EXTERN NSString *NSBottomMarginDocumentAttribute AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"BottomMargin", NSNumber containing floating point value (in points)
APPKIT_EXTERN NSString *NSViewSizeDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"ViewSize", NSValue containing NSSize (in points)
APPKIT_EXTERN NSString *NSViewZoomDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"ViewZoom", NSNumber containing float (100 == 100% zoom)
APPKIT_EXTERN NSString *NSViewModeDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"ViewMode", NSNumber containing int; 0 = normal; 1 = page layout
APPKIT_EXTERN NSString *NSDocumentTypeDocumentAttribute AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"DocumentType", NSString indicating which document type was used to interpret the document (RTF, HTML, SimpleText, etc., as above)
APPKIT_EXTERN NSString *NSReadOnlyDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"ReadOnly", NSNumber containing int; if missing, or 0 or negative, not readonly; 1 or more, readonly. Note that this has nothing to do with the file system protection on the file, but instead, on how the file should be displayed to the user
APPKIT_EXTERN NSString *NSConvertedDocumentAttribute    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"Converted", NSNumber containing int; if missing, or 0, the file was originally in the format specified by document type; if negative, the file was originally in the format specified by document type, but the conversion to NSAttributedString may have been lossy; if 1 or more, it was converted to the specified type by a filter service
APPKIT_EXTERN NSString *NSCocoaVersionDocumentAttribute      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"CocoaRTFVersion", RTF files only.  Stores the version of Cocoa the file was created with.  NSNumber containing float.  Absence of this value indicates RTF file not created by Cocoa or its predecessors.  Values less than 100 are pre-Mac OS X; 100 is Mac OS X 10.0 and 10.1; 102 is Mac OS X 10.2 and 10.3; values greater than 102 correspond to values of NSAppKitVersionNumber on 10.4 and later systems.
APPKIT_EXTERN NSString *NSBackgroundColorDocumentAttribute      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"BackgroundColor", NSColor, representing the document-wide page background color
APPKIT_EXTERN NSString *NSHyphenationFactorDocumentAttribute    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"HyphenationFactor", NSNumber containing floating point value (0=off, 1=full hyphenation)
APPKIT_EXTERN NSString *NSDefaultTabIntervalDocumentAttribute   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"DefaultTabInterval", NSNumber containing float, representing the document-wide default tab stop interval, in points
APPKIT_EXTERN NSString *NSCharacterEncodingDocumentAttribute    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"CharacterEncoding", For reading and writing of plain text files, and writing of HTML; NSNumber containing int specifying NSStringEncoding for the file; default for plain text is the default encoding, default for HTML is UTF-8

/* These document attributes were added in 10.4.
*/
APPKIT_EXTERN NSString *NSTitleDocumentAttribute        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing document title
APPKIT_EXTERN NSString *NSCompanyDocumentAttribute      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing company or organization name
APPKIT_EXTERN NSString *NSCopyrightDocumentAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing document copyright info
APPKIT_EXTERN NSString *NSSubjectDocumentAttribute      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing subject of document
APPKIT_EXTERN NSString *NSAuthorDocumentAttribute       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing author name (not necessarily same as "last editor," see below)
APPKIT_EXTERN NSString *NSKeywordsDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSArray of NSString, containing keywords
APPKIT_EXTERN NSString *NSCommentDocumentAttribute      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing document comments
APPKIT_EXTERN NSString *NSEditorDocumentAttribute       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSString containing name of person who last edited the document
APPKIT_EXTERN NSString *NSCreationTimeDocumentAttribute AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSDate containing the creation date of the document; note that this is not the file system creation date of the file, but of the document, as it's stored in the document
APPKIT_EXTERN NSString *NSModificationTimeDocumentAttribute AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // NSDate containing the modification date of the document contents

/* Additional document attributes added in 10.4, for HTML writing only.  These provide control over the form of generated HTML.  NSExcludedElementsDocumentAttribute allows control over the tags used.  The recognized values in the NSExcludedElementsDocumentAttribute array are (case-insensitive) HTML tags, plus DOCTYPE (representing a doctype declaration) and XML (representing an XML declaration).  By default, if this attribute is not present, the excluded elements will be those deprecated in HTML 4 (APPLET, BASEFONT, CENTER, DIR, FONT, ISINDEX, MENU, S, STRIKE, and U) plus XML.  If XML is on the list, HTML forms will be used; if XML is not on the list, XHTML forms will be used where there is a distinction.  Either NSCharacterEncodingDocumentAttribute or NSTextEncodingNameDocumentAttribute may be used to control the encoding used for generated HTML; character entities will be used for characters not representable in the specified encoding.  Finally, NSPrefixSpacesDocumentAttribute allows some control over formatting.
*/
APPKIT_EXTERN NSString *NSExcludedElementsDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // for HTML writing only; NSArray containing NSStrings, representing HTML elements not to be used in generated HTML
APPKIT_EXTERN NSString *NSTextEncodingNameDocumentAttribute     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // for HTML writing only; NSString containing the name, IANA or otherwise, of a text encoding to be used; mutually exclusive with NSCharacterEncodingDocumentAttribute
APPKIT_EXTERN NSString *NSPrefixSpacesDocumentAttribute         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // for HTML writing only; NSNumber containing int, default 0, representing the number of spaces per level by which to indent certain nested HTML elements

/* The following are keys for various options that can be specified in the options dictionaries for the text import APIs below.  Except for NSTextSizeMultiplierDocumentOption, the values have been recognized for some time, but the actual identifier shown below was added in 10.4. If you want your app to run on earlier systems, you need to continue using the actual string value that these identifiers represent. The actual string value is specified in the comments below.
*/

APPKIT_EXTERN NSString *NSDocumentTypeDocumentOption            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"DocumentType", NSString indicating a document type to be forced when loading the document
APPKIT_EXTERN NSString *NSDefaultAttributesDocumentOption       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"DefaultAttributes", for plain text only; NSDictionary containing attributes to be applied to plain files
APPKIT_EXTERN NSString *NSCharacterEncodingDocumentOption       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"CharacterEncoding", for plain text and HTML; NSNumber containing int specifying NSStringEncoding used to interpret the file
APPKIT_EXTERN NSString *NSTextEncodingNameDocumentOption        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"TextEncodingName", for HTML only; NSString containing the name, IANA or otherwise, of a text encoding to be used if the encoding cannot be determined from the document; mutually exclusive with NSCharacterEncodingDocumentOption
APPKIT_EXTERN NSString *NSBaseURLDocumentOption                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"BaseURL", for HTML only; NSURL containing a URL to be treated as the base URL for the document
APPKIT_EXTERN NSString *NSTimeoutDocumentOption                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"Timeout", for HTML only; NSNumber containing float; time in seconds to wait for a document to finish loading; if not present or not positive, a default timeout will be used
APPKIT_EXTERN NSString *NSWebPreferencesDocumentOption          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"WebPreferences", for HTML only; WebPreferences; specifies a WebPreferences object describing a set of preferences; if not present, a default set of preferences will be used
APPKIT_EXTERN NSString *NSWebResourceLoadDelegateDocumentOption AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // @"WebResourceLoadDelegate", for HTML only; NSObject; specifies an object to serve as the WebResourceLoadDelegate; if not present, a default delegate will be used that will permit the loading of subsidiary resources but will not respond to authentication challenges
APPKIT_EXTERN NSString *NSTextSizeMultiplierDocumentOption      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // for HTML only; NSNumber containing float, default 1.0; specifies a scale factor for font sizes, corresponding to WebView's textSizeMultiplier

/* In Mac OS X 10.4 and later, WebKit is always used for HTML documents, and all of the above options are recognized.  In Mac OS X 10.3, there is an additional options key, @"UseWebKit" (NSNumber containing int; if present and positive, specifies that WebKit-based HTML importing is to be used).  In Mac OS X 10.3, the Timeout, WebPreferences, and WebResourceLoadDelegate options are recognized only when WebKit-based HTML importing is used.
*/

@interface NSAttributedString (NSAttributedStringKitAdditions)

- (NSDictionary *)fontAttributesInRange:(NSRange)range; /* Attributes which should be copied/pasted with "copy font" */
- (NSDictionary *)rulerAttributesInRange:(NSRange)range; /* Attributes which should be copied/pasted with "copy ruler" */

- (BOOL)containsAttachments;

/* Returns NSNotFound if no line break location found in the specified range; otherwise returns the index of the first character that should go on the NEXT line.
*/
- (unsigned)lineBreakBeforeIndex:(unsigned)location withinRange:(NSRange)aRange;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (unsigned)lineBreakByHyphenatingBeforeIndex:(unsigned)location withinRange:(NSRange)aRange;
#endif
- (NSRange)doubleClickAtIndex:(unsigned)location;
- (unsigned)nextWordFromIndex:(unsigned)location forward:(BOOL)isForward;

/* Methods to determine what types can be loaded as NSAttributedStrings
*/
+ (NSArray *)textUnfilteredFileTypes;
+ (NSArray *)textUnfilteredPasteboardTypes;
+ (NSArray *)textFileTypes;
+ (NSArray *)textPasteboardTypes;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Convenience methods for calculating the range of an individual text block, range of an entire table, range of a list, and the index within a list.
*/
- (NSRange)rangeOfTextBlock:(NSTextBlock *)block atIndex:(unsigned)location;
- (NSRange)rangeOfTextTable:(NSTextTable *)table atIndex:(unsigned)location;
- (NSRange)rangeOfTextList:(NSTextList *)list atIndex:(unsigned)location;
- (int)itemNumberInTextList:(NSTextList *)list atIndex:(unsigned)location;
#endif

/* Methods to create an attributed string by loading text documents in various formats.  In all of these methods, if the document attributes dict is not NULL, it will return a dictionary with various document-wide attributes.  The various possible attributes are specified above, as NS...DocumentAttribute.  The attributes supported vary by document type; for RTF and RTFD, all are supported except CharacterEncoding.
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* These first two general methods supersede the previous versions shown below.  They take a dictionary of options to specify how the document should be loaded.  The various possible options are specified above, as NS...DocumentOption.  If NSDocumentTypeDocumentOption is specified, the document will be treated as being in the specified format.  If NSDocumentTypeDocumentOption is not specified, these methods will examine the document and do their best to load it using whatever format it seems to contain.
*/
- (id)initWithURL:(NSURL *)url options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict error:(NSError **)error;
- (id)initWithData:(NSData *)data options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict error:(NSError **)error;

#endif

/* These two superseded methods are similar to the first listed above except that they lack the options dictionary and error return arguments.  They will always attempt to determine the format from the document.
*/
- (id)initWithPath:(NSString *)path documentAttributes:(NSDictionary **)dict;
- (id)initWithURL:(NSURL *)url documentAttributes:(NSDictionary **)dict;

/* The following methods should now be considered as conveniences for various common document types.
*/
- (id)initWithRTF:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithRTFD:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data baseURL:(NSURL *)base documentAttributes:(NSDictionary **)dict;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (id)initWithDocFormat:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict;
#endif

/* A separate method is required for initializing from an RTFD file wrapper.  No options apply in this case.
*/
- (id)initWithRTFDFileWrapper:(NSFileWrapper *)wrapper documentAttributes:(NSDictionary **)dict;

/* Methods to produce data for saving text documents in various formats.  These methods take a document attributes dictionary to allow writing out various document-wide attributes.  The various possible attributes are specified above, as NS...DocumentAttribute.  The attributes supported vary by document type; for RTF and RTFD all are supported except NSCharacterEncodingDocumentAttribute, NSCocoaVersionDocumentAttribute, NSConvertedDocumentAttribute, and NSExcludedElementsDocumentAttribute.
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* These first two methods generalize on the more specific previous versions shown below.  They require a document attributes dict specifying at least the NSDocumentTypeDocumentAttribute to determine the format to be written.  The file wrapper method will return a directory file wrapper for those document types for which it is appropriate, otherwise a regular-file file wrapper.
*/
- (NSData *)dataFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict error:(NSError **)error;
- (NSFileWrapper *)fileWrapperFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict error:(NSError **)error;
#endif

/* The following methods should now be considered as conveniences for various common document types.  In these methods the document attributes dictionary is optional.
*/
- (NSData *)RTFFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
- (NSData *)RTFDFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
- (NSFileWrapper *)RTFDFileWrapperFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSData *)docFormatFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
#endif

@end


@interface NSMutableAttributedString (NSMutableAttributedStringKitAdditions)

/* Methods to set the contents of a mutable attributed string by loading text documents in various formats.
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* These first two general methods are similar to the corresponding initWith... methods shown above, but they act only on mutable attributed strings.  They supersede the previous versions shown below.
*/
- (BOOL)readFromURL:(NSURL *)url options:(NSDictionary *)opts documentAttributes:(NSDictionary **)dict error:(NSError **)error;
- (BOOL)readFromData:(NSData *)data options:(NSDictionary *)opts documentAttributes:(NSDictionary **)dict error:(NSError **)error;
#endif

/* These two superseded methods are similar to the two listed immediately above except that they lack the error return argument.
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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection range:(NSRange)range;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

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

