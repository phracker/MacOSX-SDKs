#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSAttributedString.h>)
//
//  NSAttributedString.h
//  UIKit
//
//  Copyright (c) 2011-2018, Apple Inc. All rights reserved.
//

#import <Foundation/NSAttributedString.h>
#import <Foundation/NSItemProvider.h>
#import <UIKit/UIKitDefines.h>
@class NSAttributedString;
@class NSFileWrapper;
@class NSURL;

NS_ASSUME_NONNULL_BEGIN
/************************ Attributes ************************/

// Predefined character attributes for text. If the key is not present in the dictionary, it indicates the default value described below.
UIKIT_EXTERN NSAttributedStringKey const NSFontAttributeName API_AVAILABLE(macos(10.0), ios(6.0));                // UIFont, default Helvetica(Neue) 12
UIKIT_EXTERN NSAttributedStringKey const NSParagraphStyleAttributeName API_AVAILABLE(macos(10.0), ios(6.0));      // NSParagraphStyle, default defaultParagraphStyle
UIKIT_EXTERN NSAttributedStringKey const NSForegroundColorAttributeName API_AVAILABLE(macos(10.0), ios(6.0));     // UIColor, default blackColor
UIKIT_EXTERN NSAttributedStringKey const NSBackgroundColorAttributeName API_AVAILABLE(macos(10.0), ios(6.0));     // UIColor, default nil: no background
UIKIT_EXTERN NSAttributedStringKey const NSLigatureAttributeName API_AVAILABLE(macos(10.0), ios(6.0));            // NSNumber containing integer, default 1: default ligatures, 0: no ligatures
UIKIT_EXTERN NSAttributedStringKey const NSKernAttributeName API_AVAILABLE(macos(10.0), ios(6.0));                // NSNumber containing floating point value, in points; amount to modify default kerning. 0 means kerning is disabled.
UIKIT_EXTERN NSAttributedStringKey const NSStrikethroughStyleAttributeName API_AVAILABLE(macos(10.0), ios(6.0));  // NSNumber containing integer, default 0: no strikethrough
UIKIT_EXTERN NSAttributedStringKey const NSUnderlineStyleAttributeName API_AVAILABLE(macos(10.0), ios(6.0));      // NSNumber containing integer, default 0: no underline
UIKIT_EXTERN NSAttributedStringKey const NSStrokeColorAttributeName API_AVAILABLE(macos(10.0), ios(6.0));         // UIColor, default nil: same as foreground color
UIKIT_EXTERN NSAttributedStringKey const NSStrokeWidthAttributeName API_AVAILABLE(macos(10.0), ios(6.0));         // NSNumber containing floating point value, in percent of font point size, default 0: no stroke; positive for stroke alone, negative for stroke and fill (a typical value for outlined text would be 3.0)
UIKIT_EXTERN NSAttributedStringKey const NSShadowAttributeName API_AVAILABLE(macos(10.0), ios(6.0));              // NSShadow, default nil: no shadow
UIKIT_EXTERN NSAttributedStringKey const NSTextEffectAttributeName API_AVAILABLE(macos(10.10), ios(7.0));          // NSString, default nil: no text effect

UIKIT_EXTERN NSAttributedStringKey const NSAttachmentAttributeName API_AVAILABLE(macos(10.0), ios(7.0));          // NSTextAttachment, default nil
UIKIT_EXTERN NSAttributedStringKey const NSLinkAttributeName API_AVAILABLE(macos(10.0), ios(7.0));                // NSURL (preferred) or NSString
UIKIT_EXTERN NSAttributedStringKey const NSBaselineOffsetAttributeName API_AVAILABLE(macos(10.0), ios(7.0));      // NSNumber containing floating point value, in points; offset from baseline, default 0
UIKIT_EXTERN NSAttributedStringKey const NSUnderlineColorAttributeName API_AVAILABLE(macos(10.0), ios(7.0));      // UIColor, default nil: same as foreground color
UIKIT_EXTERN NSAttributedStringKey const NSStrikethroughColorAttributeName API_AVAILABLE(macos(10.0), ios(7.0));  // UIColor, default nil: same as foreground color
UIKIT_EXTERN NSAttributedStringKey const NSObliquenessAttributeName API_AVAILABLE(macos(10.0), ios(7.0));         // NSNumber containing floating point value; skew to be applied to glyphs, default 0: no skew
UIKIT_EXTERN NSAttributedStringKey const NSExpansionAttributeName API_AVAILABLE(macos(10.0), ios(7.0));           // NSNumber containing floating point value; log of expansion factor to be applied to glyphs, default 0: no expansion

UIKIT_EXTERN NSAttributedStringKey const NSWritingDirectionAttributeName API_AVAILABLE(macos(10.6), ios(7.0));    // NSArray of NSNumbers representing the nested levels of writing direction overrides as defined by Unicode LRE, RLE, LRO, and RLO characters.  The control characters can be obtained by masking NSWritingDirection and NSWritingDirectionFormatType values.  LRE: NSWritingDirectionLeftToRight|NSWritingDirectionEmbedding, RLE: NSWritingDirectionRightToLeft|NSWritingDirectionEmbedding, LRO: NSWritingDirectionLeftToRight|NSWritingDirectionOverride, RLO: NSWritingDirectionRightToLeft|NSWritingDirectionOverride,

UIKIT_EXTERN NSAttributedStringKey const NSVerticalGlyphFormAttributeName API_AVAILABLE(macos(10.7), ios(6.0));   // An NSNumber containing an integer value.  0 means horizontal text.  1 indicates vertical text.  If not specified, it could follow higher-level vertical orientation settings.  Currently on iOS, it's always horizontal.  The behavior for any other value is undefined.



/************************ Attribute values ************************/
// This defines currently supported values for NSUnderlineStyleAttributeName and NSStrikethroughStyleAttributeName. These values are or'ed together to produce an underline style.
// Underlines will be drawn with a solid pattern by default, so NSUnderlineStylePatternSolid does not need to be specified.
typedef NS_OPTIONS(NSInteger, NSUnderlineStyle) {
    NSUnderlineStyleNone                                    = 0x00,
    NSUnderlineStyleSingle                                  = 0x01,
    NSUnderlineStyleThick API_AVAILABLE(macos(10.0), ios(7.0))      = 0x02,
    NSUnderlineStyleDouble API_AVAILABLE(macos(10.0), ios(7.0))     = 0x09,

    NSUnderlineStylePatternSolid API_AVAILABLE(macos(10.0), ios(7.0))      = 0x0000,
    NSUnderlineStylePatternDot API_AVAILABLE(macos(10.0), ios(7.0))        = 0x0100,
    NSUnderlineStylePatternDash API_AVAILABLE(macos(10.0), ios(7.0))       = 0x0200,
    NSUnderlineStylePatternDashDot API_AVAILABLE(macos(10.0), ios(7.0))    = 0x0300,
    NSUnderlineStylePatternDashDotDot API_AVAILABLE(macos(10.0), ios(7.0)) = 0x0400,

    NSUnderlineStyleByWord API_AVAILABLE(macos(10.0), ios(7.0))            = 0x8000
} API_AVAILABLE(macos(10.0), ios(6.0));

// NSWritingDirectionFormatType values used by NSWritingDirectionAttributeName. It is or'ed with either NSWritingDirectionLeftToRight or NSWritingDirectionRightToLeft. Can specify the formatting controls defined by Unicode Bidirectional Algorithm.
typedef NS_ENUM(NSInteger, NSWritingDirectionFormatType) {
    NSWritingDirectionEmbedding     = (0 << 1),
    NSWritingDirectionOverride      = (1 << 1)
} API_AVAILABLE(macos(10.11), ios(9.0));

// NSTextEffectAttributeName values
typedef NSString * NSTextEffectStyle NS_TYPED_ENUM;
UIKIT_EXTERN NSTextEffectStyle const NSTextEffectLetterpressStyle API_AVAILABLE(macos(10.10), ios(7.0));


/************************ Attribute fixing ************************/

@interface NSMutableAttributedString (NSAttributedStringAttributeFixing)
// This method fixes attribute inconsistencies inside range.  It ensures NSFontAttributeName covers the characters, NSParagraphStyleAttributeName is only changing at paragraph boundaries, and NSTextAttachmentAttributeName is assigned to NSAttachmentCharacter.  NSTextStorage automatically invokes this method via -ensureAttributesAreFixedInRange:.
- (void)fixAttributesInRange:(NSRange)range API_AVAILABLE(macos(10.0), ios(7.0));

@end


/************************ Document formats ************************/

typedef NSString * NSAttributedStringDocumentType NS_TYPED_EXTENSIBLE_ENUM;

// Supported document types for the NSDocumentTypeDocumentAttribute key in the document attributes dictionary.
UIKIT_EXTERN NSAttributedStringDocumentType const NSPlainTextDocumentType API_AVAILABLE(macos(10.0), ios(7.0));
UIKIT_EXTERN NSAttributedStringDocumentType const NSRTFTextDocumentType  API_AVAILABLE(macos(10.0), ios(7.0));
UIKIT_EXTERN NSAttributedStringDocumentType const NSRTFDTextDocumentType API_AVAILABLE(macos(10.0), ios(7.0));
UIKIT_EXTERN NSAttributedStringDocumentType const NSHTMLTextDocumentType  API_AVAILABLE(macos(10.0), ios(7.0));

typedef NSString * NSTextLayoutSectionKey NS_TYPED_ENUM;

// Keys for NSLayoutOrientationSectionsAttribute.
UIKIT_EXTERN NSTextLayoutSectionKey const NSTextLayoutSectionOrientation API_AVAILABLE(macos(10.7), ios(7.0)); // NSNumber containing NSTextLayoutOrientation value. default: NSTextLayoutOrientationHorizontal
UIKIT_EXTERN NSTextLayoutSectionKey const NSTextLayoutSectionRange API_AVAILABLE(macos(10.7), ios(7.0)); // NSValue containing NSRange representing a character range. default: a range covering the whole document

// Supported values for NSTextScalingDocumentAttribute, NSSourceTextScalingDocumentAttribute, NSTargetTextScalingDocumentOption, NSSourceTextScalingDocumentOption
typedef NS_ENUM(NSInteger, NSTextScalingType) {
    NSTextScalingStandard = 0,  // Font sizes throughout the document should appear visually similar to how they would render on macOS and non-Apple platforms
    NSTextScalingiOS  // Font sizes throughout the document should appear visually similar to how they would render on iOS
} API_AVAILABLE(macos(10.15), ios(13.0));

typedef NSString * NSAttributedStringDocumentAttributeKey NS_TYPED_EXTENSIBLE_ENUM;

// Keys for options and document attributes dictionaries.  They are in and out document properties used by both read/write methods.

UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSDocumentTypeDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"DocumentType", one of the document types declared above.  For reader methods, this key in options can specify the document type for interpreting the contents.  Upon return, the document attributes can contain this key for indicating the actual format used to read the contents.  For write methods, this key specifies the format for generating the data.


// NSPlainTextDocumentType document attributes
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSCharacterEncodingDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"CharacterEncoding", NSNumber containing integer specifying NSStringEncoding for the file; default for plain text is the default encoding.  This key in options can specify the string encoding for reading the data.  Upon return, the document attributes can contain the actual encoding used.  For writing methods, this value is used for generating the plain text data.
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSDefaultAttributesDocumentAttribute API_AVAILABLE(macos(10.11), ios(7.0));  // @"DefaultAttributes", NSDictionary containing attributes to be applied to plain files.  Used by reader methods.  This key in options can specify the default attributes applied to the entire document contents.  The document attributes can contain this key indicating the actual attributes used.


// NSRTFTextDocumentType and NSRTFDTextDocumentType document attributes
// Document dimension
// They are document attributes used by read/write methods.
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSPaperSizeDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"PaperSize", NSValue containing CGSize (in points)
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSPaperMarginDocumentAttribute API_AVAILABLE(ios(7.0));  // @"PaperMargin", NSValue containing UIEdgeInsets

UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSViewSizeDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"ViewSize", NSValue containing CGSize (in points)
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSViewZoomDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"ViewZoom", NSNumber containing floating point value (100 == 100% zoom)
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSViewModeDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"ViewMode", NSNumber containing integer; 0 = normal; 1 = page layout

// Document settings
// They are document attributes used by read/write methods.
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSReadOnlyDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"ReadOnly", NSNumber containing integer; if missing, or 0 or negative, not readonly; 1 or more, readonly. Note that this has nothing to do with the file system protection on the file, but instead, on how the file should be displayed to the user
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSBackgroundColorDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"BackgroundColor", UIColor, representing the document-wide page background color
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSHyphenationFactorDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"HyphenationFactor", NSNumber containing floating point value (0=off, 1=full hyphenation)
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSDefaultTabIntervalDocumentAttribute API_AVAILABLE(macos(10.0), ios(7.0));  // @"DefaultTabInterval", NSNumber containing floating point value, representing the document-wide default tab stop interval, in points
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSTextLayoutSectionsAttribute API_AVAILABLE(macos(10.7), ios(7.0));  // NSArray of dictionaries.  Each dictionary describing a layout orientation section.  The dictionary can have two attributes: NSTextLayoutSectionOrientation and NSTextLayoutSectionRange.  When there is a gap between sections, it's assumed to have NSTextLayoutOrientationHorizontal.

// Document text scaling and Cocoa version
// They are document attributes used by read/write methods.
UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSTextScalingDocumentAttribute API_AVAILABLE(macos(10.15), ios(13.0));  // @"TextScaling", one of the text scaling types declared above. Only affects RTF documents.  For reading methods, this indicates the type of text scaling used in the returned attributed string.  For write methods, this attribute can be used in two different ways: (1) Passing only this attribute will overwrite the text scaling metadata in the document, but will not perform any conversion on the font sizes in the document, or (2) Passing both this attribute and NSSourceTextScalingDocumentAttribute will convert the font sizes in the document from the source text scaling type to the text scaling type specified by this attribute.

UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSSourceTextScalingDocumentAttribute API_AVAILABLE(macos(10.15), ios(13.0));  // @"SourceTextScaling", one of the text scaling types declared above. Only affects RTF documents.  For writing methods, this indicates the type of text scaling in the attributed string that will be used as the base type for conversion.  Use this in conjunction with NSTextScalingDocumentAttribute to convert font point sizes between text scalings when writing attributed strings to RTF.  This attribute is optional and does nothing unless NSTextScalingDocumentAttribute is also specified.

UIKIT_EXTERN NSAttributedStringDocumentAttributeKey const NSCocoaVersionDocumentAttribute API_AVAILABLE(macos(10.4), ios(13.0));  // @"CocoaRTFVersion", NSNumber containing integer.  Stores the version of Cocoa the file was created with.  NSNumber containing float.  Absence of this value indicates file not labelled as being created by Cocoa or its predecessors.  Values less than 100 are pre-Mac OS X; 100 is Mac OS X 10.0 and 10.1; 102 is Mac OS X 10.2 and 10.3; values greater than 102 correspond to values of NSAppKitVersionNumber on 10.4-10.14 systems.  Beginning with iOS 13 and macOS 10.15, this version number does not have a one-to-one correspondence with any single system framework version, but is guaranteed to monotonically increase with each OS version.

typedef NSString * NSAttributedStringDocumentReadingOptionKey NS_TYPED_EXTENSIBLE_ENUM;

UIKIT_EXTERN NSAttributedStringDocumentReadingOptionKey const NSDocumentTypeDocumentOption;  // @"DocumentType", NSString indicating a document type to be forced when loading the document, specified as one of the NSDocumentTypeDocumentAttribute constants listed above
UIKIT_EXTERN NSAttributedStringDocumentReadingOptionKey const NSDefaultAttributesDocumentOption;  // @"DefaultAttributes", for plain text only; NSDictionary containing attributes to be applied to plain files
UIKIT_EXTERN NSAttributedStringDocumentReadingOptionKey const NSCharacterEncodingDocumentOption;  // @"CharacterEncoding", for plain text and HTML; NSNumber containing integer specifying NSStringEncoding to be used to interpret the file

UIKIT_EXTERN NSAttributedStringDocumentReadingOptionKey const NSTargetTextScalingDocumentOption API_AVAILABLE(macos(10.15), ios(13.0));  // @"TargetTextScaling", one of the text scaling types declared above.  Only affects RTF documents.  For reading methods, you can pass this option to request that the returned attributed string uses the specified scaling.  The font point sizes in the document may be converted if necessary.  If this option is not provided, the system will deduce the target text scaling type based on application framework and platform.

UIKIT_EXTERN NSAttributedStringDocumentReadingOptionKey const NSSourceTextScalingDocumentOption API_AVAILABLE(macos(10.15), ios(13.0));  // @"SourceTextScaling", one of the text scaling types declared above.  Only affects RTF documents.  For reading methods, you can pass this option to indicate the source text scaling type of the RTF document being read.  Use this in conjunction with NSTargetTextScalingDocumentOption to control text scaling conversions on the font point sizes in the returned attributed string.  This option does nothing unless NSTargetTextScalingDocumentOption is also specified.  If this option is not provided, the system will deduce the source text scaling type based on the information in the document.


@interface NSAttributedString (NSAttributedStringDocumentFormats)
// Methods initializing the receiver contents with an external document data.  options specify document attributes for interpreting the document contents.  NSDocumentTypeDocumentAttribute, NSCharacterEncodingDocumentAttribute, and NSDefaultAttributesDocumentAttribute are supported options key.  When they are not specified, these methods will examine the data and do their best to detect the appropriate attributes.  If dict is non-NULL, it will return a dictionary with various document-wide attributes accessible via NS...DocumentAttribute keys.
- (nullable instancetype)initWithURL:(NSURL *)url options:(NSDictionary<NSAttributedStringDocumentReadingOptionKey, id> *)options documentAttributes:(NSDictionary<NSAttributedStringDocumentAttributeKey, id> * __nullable * __nullable)dict error:(NSError **)error API_AVAILABLE(macos(10.4), ios(9.0));
- (nullable instancetype)initWithData:(NSData *)data options:(NSDictionary<NSAttributedStringDocumentReadingOptionKey, id> *)options documentAttributes:(NSDictionary<NSAttributedStringDocumentAttributeKey, id> * __nullable * __nullable)dict error:(NSError **)error API_AVAILABLE(macos(10.0), ios(7.0));

// Generates an NSData object for the receiver contents in range.  It requires a document attributes dict specifying at least the NSDocumentTypeDocumentAttribute to determine the format to be written.
- (nullable NSData *)dataFromRange:(NSRange)range documentAttributes:(NSDictionary<NSAttributedStringDocumentAttributeKey, id> *)dict error:(NSError **)error API_AVAILABLE(macos(10.0), ios(7.0));

// Returns an NSFileWrapper object for the receiver contents in range.  It requires a document attributes dict specifying at least the NSDocumentTypeDocumentAttribute to determine the format to be written.  The method returns a directory file wrapper for those document types represented by a file package such as NSRTFDTextDocumentType; otherwise, it returns a regular-file file wrapper.
- (nullable NSFileWrapper *)fileWrapperFromRange:(NSRange)range documentAttributes:(NSDictionary<NSAttributedStringDocumentAttributeKey, id> *)dict error:(NSError **)error API_AVAILABLE(macos(10.0), ios(7.0));

@end

@interface NSMutableAttributedString (NSMutableAttributedStringDocumentFormats)
// Methods replacing the receiver contents with an external document data.  options specify document attributes for interpreting the document contents.  NSDocumentTypeDocumentAttribute, NSCharacterEncodingDocumentAttribute, and NSDefaultAttributesDocumentAttribute are supported options key.  When they are not specified, these methods will examine the data and do their best to detect the appropriate attributes.  If dict is non-NULL, it will return a dictionary with various document-wide attributes accessible via NS...DocumentAttribute keys.
- (BOOL)readFromURL:(NSURL *)url options:(NSDictionary<NSAttributedStringDocumentReadingOptionKey, id> *)opts documentAttributes:(NSDictionary<NSAttributedStringDocumentAttributeKey, id> * __nullable * __nullable)dict error:(NSError **)error  API_AVAILABLE(macosx(10.5), ios(9.0), watchos(2.0), tvos(9.0));
- (BOOL)readFromData:(NSData *)data options:(NSDictionary<NSAttributedStringDocumentReadingOptionKey, id> *)opts documentAttributes:(NSDictionary<NSAttributedStringDocumentAttributeKey, id> * __nullable * __nullable)dict error:(NSError **)error API_AVAILABLE(macos(10.0), ios(7.0));
@end


/************************ Misc methods ************************/
@interface NSAttributedString (NSAttributedStringKitAdditions)
// Returns YES if the receiver contains a property configured (NSAttachmentAttributeName with NSAttachmentCharacter) in range
- (BOOL)containsAttachmentsInRange:(NSRange)range API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface NSAttributedString (NSAttributedString_ItemProvider) <NSItemProviderReading, NSItemProviderWriting>
@end


/************************ Deprecated ************************/
// NSUnderlineByWord and the NSUnderlinePattern* values are soft deprecated starting with macOS 10.14/iOS 12 and will be officially deprecated in a future release.  Please use the NSUnderlineStyle* equivalents instead.
// Underlines will be drawn with a solid pattern by default, so NSUnderlinePatternSolid does not need to be specified.
static const NSUnderlineStyle NSUnderlinePatternSolid = NSUnderlineStylePatternSolid;
static const NSUnderlineStyle NSUnderlinePatternDot = NSUnderlineStylePatternDot;
static const NSUnderlineStyle NSUnderlinePatternDash = NSUnderlineStylePatternDash;
static const NSUnderlineStyle NSUnderlinePatternDashDot = NSUnderlineStylePatternDashDot;
static const NSUnderlineStyle NSUnderlinePatternDashDotDot = NSUnderlineStylePatternDashDotDot;
static const NSUnderlineStyle NSUnderlineByWord = NSUnderlineStyleByWord;


typedef NS_ENUM(NSInteger, NSTextWritingDirection) {
    NSTextWritingDirectionEmbedding     = (0 << 1),
    NSTextWritingDirectionOverride      = (1 << 1)
} API_DEPRECATED_WITH_REPLACEMENT("NSWritingDirectionFormatType", ios(7.0, 9.0)) API_UNAVAILABLE(tvos);

@interface NSAttributedString(NSDeprecatedKitAdditions)
- (nullable instancetype)initWithFileURL:(NSURL *)url options:(NSDictionary *)options documentAttributes:(NSDictionary* __nullable * __nullable)dict error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("initWithURL:options:documentAttributes:error:", ios(7.0, 9.0)) API_UNAVAILABLE(tvos);
@end

@interface NSMutableAttributedString (NSDeprecatedKitAdditions)
- (BOOL)readFromFileURL:(NSURL *)url options:(NSDictionary *)opts documentAttributes:(NSDictionary* __nullable * __nullable)dict error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("readFromURL:options:documentAttributes:error:", ios(7.0, 9.0)) API_UNAVAILABLE(tvos);
@end
NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/NSAttributedString.h>
#endif
