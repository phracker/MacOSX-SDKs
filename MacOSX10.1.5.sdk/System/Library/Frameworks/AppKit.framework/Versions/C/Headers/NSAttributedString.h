/*	
	NSAttributedString.h
	Copyright (c) 1994-2001, Apple Computer, Inc.
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

/* An integer value.  The value is interpreted as Apple Type Services kCharacterShapeType selector + 1.
 * default is 0 (disable). 1 is kTraditionalCharactersSelector and so on.
 * Refer to <ATS/SFNTLayoutTypes.h>
 */
APPKIT_EXTERN NSString *NSCharacterShapeAttributeName;

/* This defines currently supported values for NSUnderlineStyleAttributeName
*/
enum {
    NSNoUnderlineStyle = 0,
    NSSingleUnderlineStyle
};

/* Combine these with the desired underline style to create the given effect.  In other words, to get strikethrough, set NSUnderlineStyleAttribute to (NSNoUnderlineStyle|NSUnderlineStrikethroughMask).  To get both strikethrough and an underline, skipping intermediate whitespace, use (NSSingleUnderlineStyle|NSUnderlineByWordMask|NSUnderlineStrikethroughMask).
*/
APPKIT_EXTERN unsigned NSUnderlineByWordMask; 
APPKIT_EXTERN unsigned NSUnderlineStrikethroughMask;

/* Values returned for the @"DocumentType" key in the document attributes dictionary when reading text documents. Note that other values are possible, and this set might grow in the future.
*/
APPKIT_EXTERN NSString *NSPlainTextDocumentType;
APPKIT_EXTERN NSString *NSRTFTextDocumentType;
APPKIT_EXTERN NSString *NSRTFDTextDocumentType;
APPKIT_EXTERN NSString *NSMacSimpleTextDocumentType;
APPKIT_EXTERN NSString *NSHTMLTextDocumentType;


@interface NSAttributedString (NSAttributedStringKitAdditions)

- (NSDictionary *)fontAttributesInRange:(NSRange)range; /* Attributes which should be copied/pasted with "copy font" */
- (NSDictionary *)rulerAttributesInRange:(NSRange)range; /* Attributes which should be copied/pasted with "copy ruler" */

- (BOOL)containsAttachments;

/* Returns NSNotFound if no line break location found in the specified range; otherwise returns the index of the first character that should go on the NEXT line.
*/
- (unsigned)lineBreakBeforeIndex:(unsigned)location withinRange:(NSRange)aRange;
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
    @"Converted" (NSNumber containing int; if missing, or 0 or negative, the file was originally in the format specified by document type; 1 or more, it was converted to this type by a filter service)
*/
- (id)initWithPath:(NSString *)path documentAttributes:(NSDictionary **)dict;
- (id)initWithURL:(NSURL *)url documentAttributes:(NSDictionary **)dict;
- (id)initWithRTF:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithRTFD:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithRTFDFileWrapper:(NSFileWrapper *)wrapper documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data documentAttributes:(NSDictionary **)dict;
- (id)initWithHTML:(NSData *)data baseURL:(NSURL *)base documentAttributes:(NSDictionary **)dict;

/* These RTF/RTFD creation methods take an optional dictionary to allow writing out document-wide attributes (for RTF, @"PaperSize", @"LeftMargin", @"RightMargin", @"TopMargin", @"BottomMargin", and @"HyphenationFactor" are supported).
*/
- (NSData *)RTFFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
- (NSData *)RTFDFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;
- (NSFileWrapper *)RTFDFileWrapperFromRange:(NSRange)range documentAttributes:(NSDictionary *)dict;

@end


@interface NSMutableAttributedString (NSMutableAttributedStringKitAdditions)

/* Set the contents of the mutable attributed string from the file at the specified URL.  opts can contain:
     @"CharacterEncoding" (For plain text documents; NSNumber containing the unsigned int NSStringEncoding to be used if the encoding cannot be determined)
     @"BaseURL" (For HTML documents; NSURL containing base URL)
     @"DefaultAttributes" (NSDictionary containing attributes to be applied to plain files)
On return, the documentAttributes dictionary (if provided) contains the various keys described above (in the init methods).
*/
- (BOOL)readFromURL:(NSURL *)url options:(NSDictionary *)options documentAttributes:(NSDictionary **)dict;

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
