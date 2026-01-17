//
//  PDFSelection.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFSelection tracks a range of text on one or many pages, from a starting
//  to end position. From a selection over a range of text, you have the ability
//  to extract the plain-text string or decorated string. PDFSelections can be
//  combined together, combining as needed or keeping the several discrete and
//  non-overlapping selections apart. Selections can also grow and shrink as
//  needed.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFPage.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFPage;

// Enum used to determine the granularity at which text selections are created. Mirrors CGPDFSelectionType.
PDFKIT_ENUM_AVAILABLE(15_0, 18_0)
typedef NS_ENUM(NSUInteger, PDFSelectionGranularity) {
    PDFSelectionGranularityCharacter,
    PDFSelectionGranularityWord,
    PDFSelectionGranularityLine,
};

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFSelection : NSObject <NSCopying>
{
}


// -------- initialization

// Returns and empty PDFSelection. Generally this is not useful but you can use this empty PDFSelection as a container
// into which you -[addSelection] or -[addSelections] below.
- (instancetype)initWithDocument:(PDFDocument *)document PDFKIT_AVAILABLE(10_5, 11_0) NS_DESIGNATED_INITIALIZER;


// -------- accessors

// Array of pages covered by the selection. These are sorted by page index.
@property (nonatomic, readonly) NSArray<PDFPage*> *pages;

// If no color is ever specified, PDFSelections will draw using [NSColor selectedTextBackgroundColor] when active and 
// [NSColor secondarySelectedControlColor] when not active. Calling -[setColor] will force the specified color to be 
// used for both active and inactive drawing.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *color PDFKIT_AVAILABLE(10_5, 11_0);

// String representing the text covered by the selection. May contain line-feeds.
@property (nonatomic, readonly, nullable) NSString *string;
@property (nonatomic, readonly, nullable) NSAttributedString *attributedString;

// Given a PDFPage, returns the bounds in page-space of the text covered by the selection on that page.
// Note that the bounds are relative to the origin of the page content, not the origin of any particular PDFDisplayBox.
- (PDFRect)boundsForPage:(PDFPage *)page;

// Returns the number of contiguous ranges of text on the specified page. Returns zero if page is not in selection.
// A typical, simple selection will contain a single range of text.
- (NSUInteger)numberOfTextRangesOnPage:(PDFPage *)page PDFKIT_AVAILABLE(10_7, 11_0);

// Returns a range of contiguous text at index on the specified page.
// A typical, simple selection will contain a single range of text.
- (NSRange)rangeAtIndex:(NSUInteger)index onPage:(PDFPage *)page PDFKIT_AVAILABLE(10_7, 11_0);

// Returns an array of PDFSelection objects - one for each line of text covered by the receiver. For example if the
// receiver PDFSelection represents a selected paragraph, calling this method would return several PDFSelections - one 
// for each line of text in the paragraph.
- (NSArray<PDFSelection*>*)selectionsByLine PDFKIT_AVAILABLE(10_5, 11_0);

// -------- modifying

// Add a selection to this selection. Selections don't have to be contiguous. If the selection added overlaps with this 
// selection, overlaps are removed.
- (void)addSelection:(PDFSelection *)selection;

// For adding several selections, you can get better performance calling -[addSelections:] and passing in an array of
// PDFSelections than calling -[addSelection] above inside a loop. It is the "normalization" (removing the overlaps) 
// that can be slow when adding a selection to another. This function adds all the selections first and then 
// normalizes just once at the end.
- (void)addSelections:(NSArray<PDFSelection*> *)selections PDFKIT_AVAILABLE(10_5, 11_0);

// Extends the selection at either end. Selections can be extended right off onto neighboring pages even to include the 
// entire PDF document.
- (void)extendSelectionAtEnd:(NSInteger)succeed;
- (void)extendSelectionAtStart:(NSInteger)precede;

// Extend to the selection to the beginning and end of the currently selected lines of text. If the current selection is on a single
// line, then this will extend it to the entire line width. If the selection is across multiple lines, then the first and last
// lines are expected to wholly contain their respective rows of text.
- (void)extendSelectionForLineBoundaries PDFKIT_AVAILABLE(10_13, 11_0);

// -------- rendering

// Calls the below method passing kPDFDisplayBoxCropBox for box.
- (void)drawForPage:(PDFPage *)page active: (BOOL) active;

// Draws the selection in page space relative to the origin of box. Box can be kPDFDisplayBoxMediaBox, 
// kPDFDisplayBoxCropBox, kPDFDisplayBoxBleedBox, kPDFDisplayBoxTrimBox or kPDFDisplayBoxArtBox. If active is true, it 
// is drawn using -[NSColor selectedTextBackgroundColor], otherwise it is drawn using 
// -[NSColor secondarySelectedControlColor].
- (void)drawForPage:(PDFPage *)page withBox:(PDFDisplayBox)box active:(BOOL)active;

@end

NS_ASSUME_NONNULL_END
