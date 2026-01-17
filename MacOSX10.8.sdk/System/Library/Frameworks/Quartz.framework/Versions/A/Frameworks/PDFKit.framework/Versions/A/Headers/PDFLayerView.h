// =====================================================================================================================
//  PDFLayerView.h
// =====================================================================================================================


#import <Cocoa/Cocoa.h>
#import <PDFKit/PDFPage.h>


@class PDFDocument, PDFLayerViewPrivateVars;


@interface PDFLayerView : NSView
{
	PDFDocument				*_document;
	PDFDisplayBox			_displayBox;
	
@private
	PDFLayerViewPrivateVars	*_pdfPriv;
}

@property (nonatomic,retain)	PDFDocument		*document;
@property (nonatomic)			PDFDisplayBox	displayBox;

//- (void) setCurrentPage: (PDFPage *) page;
//- (PDFPage *) currentPage;

- (NSSize) idealSizeForContent;

@end
